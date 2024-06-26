#include "wenjian.h"

static const char *TAG = "spiffs";
esp_vfs_spiffs_conf_t conf = {
    .base_path = "/spiffs",
    .partition_label = NULL,
    .max_files = 5,
    .format_if_mount_failed = true};

// 初始化spiffs
void init_spiffs(void)
{
    ESP_LOGI(TAG, "Initialzing spiffs");

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount or format filesystem ");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG, " Failed to find SPIFFS partition");
        }
        else
        {
            ESP_LOGE(TAG, " Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }
#ifdef CONFIG_EXAMPLE_SPIFFS_CHECK_ON_START
    ESP_LOGI(TAG, "Performing spiffs check SPIFFS check().");
    ret = esp_spiffs_check(conf.partition_label);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "SPIFFS_check() failed (%s)",esp_err_to_name(ret));
        return;
    }
    else
    {
        ESP_LOGI(TAG,"SPIFFS_check() successful");
    }
    #endif
    //获取文件系统已经使用的大小和剩余大小
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get SPIffS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(conf.partition_label);
        return;
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    //检查分区大小信息
    if(used > total)
    {
        ESP_LOGW(TAG, "Number of used bytes cannot be larger than total. Performing SPIffS_check().");
        ret = esp_spiffs_check(conf.partition_label);
    // 也可以用来修复损坏的wen件，清理未引用的页面等
    // More info at https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiif 
    if (ret != ESP_OK)
    {
    ESP_LOGE(TAG, "SPIFFS_check() failed (%s)",esp_err_to_name(ret));
    return;
    }
    else
    {
        ESP_LOGI(TAG,"SPIFFS_check() successful");
    }
    }
}

//测试spiffs的例子
void ds_spiffs_test(void)
{
// Use PoSIX and c standard library functions to work with files.
// First create a file.
//创建文件并写
    ESP_LOGI(TAG, "Opening file");
    FILE* f = fopen("/spiffs/hello.txt", "w");//建立一个名为/spiffs/hello.txt的只写文件
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, "Hello World!\n");//写入字符
    fclose(f);//关闭文件
    ESP_LOGI(TAG,"File written");
    //重命名之前检查目标文件是否存在
    struct stat st;
    if(stat("/spiffs/fo0.txt", &st) == 0)//获取文件信息，获取成功返回0
    {
        //从文件系统中shan除一个名称。
        //如果名称是文件的最后一个连接，并且没有其它进程将文件打开，
        //名称对应的文件会实际被删除。
        unlink("/spiffs/foo.txt");
    }
    //重命名创建的文件
    ESP_LOGI(TAG,"Renaming file");
    if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") !=0)
    {
        ESP_LOGE(TAG, "Rename failed");
        return;
    }

    //打开重命名的文件并读取
    ESP_LOGI(TAG, "Reading file");
    f = fopen("/spiffs/foo.txt", "r");
    if (f == NULL)
    {
        ESP_LOGE(TAG,"Failed to open file for reading");
        return ;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);

    char* pos = strchr(line,'\n');//指针pos指向第一个找到"\n'
    if (pos)
    {
        *pos = '\0';//将'\n'换为'\0’
    }
    ESP_LOGI(TAG, "Read from file:'%s'", line);
}
//卸载文件系统
void ds_spiffs_deinit(void)
{
    // All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(conf.partition_label);
    ESP_LOGI(TAG, "SPIFFS unmounted");
}