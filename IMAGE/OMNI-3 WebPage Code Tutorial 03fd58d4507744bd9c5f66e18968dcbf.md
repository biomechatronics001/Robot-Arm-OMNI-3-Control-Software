# OMNI-3 WebPage Code Tutorial

**There are 5 steps to control our OMNI-3 Robotic Arm through WebPage Interface on PC**

If you are starting from scratch and need to set up the environment on your **own PC**, please follow the steps below:

1: System Connection

2: System Requirements

3: Backend Code

4: Frontend Code

5: Control via PC

If you are **use our lab PC** with the environment already configured, you can skip the "System Requirements" section in Step 2 and the part about **configuring platformio** in Step 3: Back-end Code.

# **1: System Connection**

![Indepent Omni-Robot Arm](image.png)

Indepent Omni-Robot Arm

Here is our robotic arm, named the **Omni-robot arm**. The robotic arm has a cable extending from it, which contains **four wires: CAN In, CAN Out, Power In, and Power Out**. We connect the Power In and Power Out to a 24V power supply generator. The CAN In and CAN Out need to be connected to the LilyGO development board, as shown below.

![Lilygo Overview](image%201.png)

Lilygo Overview

This is our LilyGO, a Wi-Fi module based on the ESP32. Its function is to transmit webpage data to the robotic arm via the local network, enabling wireless control. Connect the robotic arm's cable to 1. the CAN port, making sure to observe the correct polarity.

<aside>
💡

Currently, the robotic arm has already been assemblied with the AGV. LilyGO boards are fixed inside the AGV box. The CAN connection between LilyGO and robotic arm has been well set up.

![Inside structure of AGV](AGV_Box.jpg)

Inside structure of AGV

If you would like to upload new code onto LilyGO board, you need to open the AGV box.

</aside>

To flash the code onto the LilyGO, we need to use a USB-A to Micro USB cable to connect 2. the USB port on LilyGO to the computer's USB port. After connecting, double-check that the connection is correct 

(it **must be USB-A**; USB-C lacks the necessary drivers, and **it must be a Windows system**—no Mac, no Linux).

Troubleshoot: If the LilyGO is not recognized by the computer, refer to [https://community.lilygo.cc/topic/21/windows-not-detects-usb-drivers/3](https://community.lilygo.cc/topic/21/windows-not-detects-usb-drivers/3) for a solution.

![**Wire Connection**](image%202.png)

**Wire Connection**

![**System Connection**](image%203.png)

**System Connection**

# **2: System Requirement**

1: Install Vscode **(Please ensure that the system is Windows, No Linux, no Mac)**

2: Open Vscode, search for "PlatformIO" in the extensions section, and click to download. This is an **embedded C/C++ development tool that allows us to develop for the LilyGO module** (Please ensure again that the system is Windows, No Linux, no Mac).

![Platformio Installion Guide](image%204.png)

Platformio Installion Guide

3: If you're interested in learning more about ESP32, you can refer to [https://docs.platformio.org/en/latest/platforms/espressif32.html](https://docs.platformio.org/en/latest/platforms/espressif32.html)

4: The following display indicates the download is complete.

![Finish Download.](image%205.png)

Finish Download.

# 3:Backend Code

First, download the code from the following link: [https://github.com/biomechatronics001/Robot-Arm-OMNI-3-Control-Software/tree/main/1.%20Webpage%20based%20wireless%20joint%20space%20control](https://github.com/biomechatronics001/Robot-Arm-OMNI-3-Control-Software/tree/main/1.%20Webpage%20based%20wireless%20joint%20space%20control).

<aside>
💡

You might need to request the access permission to the GitHub repo from **senior PhD students** or Professor.

</aside>

The code is divided into two parts: **CODE/Webpage wireless control with LilyGo** (backend control of the robotic arm) and **Webpage OMNI3 Robot arm control_EN.html** (frontend input control interface).

![Structure of our code in Github](image%206.png)

Structure of our code in Github

After downloading the code to PC, click on the green circle in the bottom left corner to enter the **PlatformIO homepage (PIO Home)**.

![Press Ant in Green Circle to enter](image%207.png)

Press Ant in Green Circle to enter

Click on **OPEN Project**, then navigate to and open the **CODE/Webpage wireless control with LilyGo** folder.

![image.png](image%208.png)

Note that the `.ini` file is the project configuration file and does not need to be modified. When you open the project for the first time, you may see that the dependent `.h` header files are highlighted in red. This is because the necessary development environment and packages need to be automatically configured and downloaded based on the `.ini` file. Please wait for the auto environment configuration process to complete.

![In lower-right corner, The downloading process would start automaticly.](image%209.png)

In lower-right corner, The downloading process would start automaticly.

Once the environment configuration completes, you will see that the `.h` libraries have been successfully located and the red highlights will disappear.

![The red underline in h would disappear](image%2010.png)

The red underline in h would disappear

Afterward, you will see an interface with the following icons:

- The ☑️ represents **Build** the project, converting the cpp codes to the format readable by LilyGO.
- The ➡️ icon is used to **upload the code to the LilyGO**.
- The **AUTO** on the right represents the USB serial port, indicating which USB port the LilyGO is connected to on your computer.

![image.png](image%2011.png)

First, click on **Build** (☑️). Once the **Build** is complete, if you see the message as shown in the image below, it means the code has no bugs. At this point, you can proceed to click on the upload button to send the code to the **ESP32 development board**.

![image.png](image%2012.png)

At this stage, it's crucial to ensure that the **USB serial port** is correctly selected for the serial communcation in the later operations!

![image.png](image%2013.png)

# 3.1: LilyGo Connected to our Route

Additionally, you will need a router. The lab has a small router, and once it's turned on, you can click on your computer's Wi-Fi and see the router-generated Wi-Fi name, which is **GL-SFT1200-004**. The password for this Wi-Fi is **goodlife**. Make sure to take note of it for future use.

![image.png](image%2014.png)

Back to the code in the last step, in the `main.cpp` file under the `SRC` directory, we can see that `192.168.1.200` is the static IP address of the LilyGo development board within the configured local area network (LAN), as shown in the line 12 in the figure below. This IP address is known as the **static IP address** of the LilyGo board. A static IP is manually assigned to a device and does not change every time it connects to the network, allowing other devices to access it using this fixed IP address. 

![image.png](image%2015.png)

In this setup, **if you want to connect LilyGO to other Wi-Fi network**, you need to change the ninth and tenth lines to the other Wi-Fi’s username and password, and comment the line 12,13 and 14. **(If you're using the router in our lab, as mentioned earlier, the Wi-Fi name is GL-SFT1200-004, and the password is goodlife)**. This will allow the LilyGO board to connect to the local network.

If you are using the router in our Lab, you can check if the LilyGO board has successfully connected to the LAN by reviewing the network information on your computer. To do this, enter the router's admin page by typing **192.168.8.1** in your web browser. The admin password is **goodlife3217**.

If an "unknown" device with IP **192.168.8.200** appears in the list of online clients as shown in the figure below (the static IP of LilyGO was set to 192.168.8.211 in the previous development process), it means that the LilyGO board has successfully connected to the network, and you can move on to the next step.

![In the image, IP address 192.168.8.211 is what we used before. It should be same as what you set in backend code.](image%2016.png)

In the image, IP address 192.168.8.211 is what we used before. It should be same as what you set in backend code.

The figure below shows an example connecting the LilyGO to one another Wi-Fi network instead of **GL-SFT1200-004**, the device name is esp32-50747C and its IP address is dynamically assigned.

![image.png](image%2017.png)

After you finishing the upload in the last step, open the **serial monitor**, where you will see the message "try to connect to existing network." Once the connection is successful, you will receive a confirmation message indicating that LilyGO has successfully connected and its static IP is **192.168.1.200**.

![image.png](image%2018.png)

At this point, the backend code setup is complete, and you can disconnect the LilyGO from the computer. However, remember to provide power to the LilyGO (If you turn on the power switch on the AGV box, LilyGO is continuously powered).

# 4: Frontend Code

Then, open the HTML file inside the downloaded repo folder (open the file with a code editing tool like vscode). You need to modify the IP address in the webpage code at lines 107 and 108 (in the .html file) to control the dual arms separately. The adjustment required is to ensure the IP address in the WebSocket matches the one specified in line 12 of our backend code:

![image%2019.png](image%2019.png)

The IP address must be set differently for each arm and should correspond to the one burned into the respective code. After making the changes, be sure to save them.

**Important**: The IP addresses for `ws1` and `ws2` must be different! Since we currently only have `ws1` (one robotic arm is used), you only need to modify the IP for `ws1` to match, then save the changes.

![image.png](image%2020.png)

Also, You need to change the display info:

![image.png](image%2021.png)

Remember to save the changes.

# 5: Control via PC

1: Ensure that the computer is also connected to the same Wi-Fi, as shown below.

![image.png](image%2022.png)

2: Open the HTML file in a browser. You will see the following interface webpage.

![image.png](11112.png)

<aside>
💡

**Before you start to enabling the robotic arm, please ensure the robotic arm is powered.**

In the current Lab setting, the robotic arm is powered by the battery inside the AGV box. Once you turn on the power switch on the AGV box, as shown below, the robotic arm and also AGV will be powered. The blue LED on one LilyGO board inside the AGV box could be an indicator for powering the system.

![90ab0d0249775bb8bfedb2b5020cba6.jpg](90ab0d0249775bb8bfedb2b5020cba6.jpg)

</aside>

3: Following the yellow arrow on the figure above, click **"Connect to WebSocket"**. After clicking, you should see the message **"Hello from ESP32"**, which indicates that the computer has successfully connected to the robotic arm.

Next, sequentially enter the numbers into the green input boxes:

- Enter **1**, then click **"Enable"**.
- Enter **2**, then click **"Enable"**.
- Enter **3**, then click **"Enable"**.
- Enter **4**, then click **"Enable"**.
- Enter **5**, then click **"Enable"**.
- Enter **6**, then click **"Enable"**.
- Continue this until you enter **7** and click **"Enable"**.

At this point, gently touch the robotic arm. If each joint is powered and cannot be moved manually, it indicates that the arm has been successfully enabled.

![image.png](11112.png)

4: Next, in the **ID 1 position** section, enter the desired position (an absolute position relative to the zero point in degrees) and speed (in RPM). After inputting the values, click **"Send All Commands"** to see the robotic arm move according to the position and speed you have entered.

5: You can refer to this video for further guidance: [https://www.youtube.com/watch?v=8ONOsnArxnQ&ab_channel=BiomechatronicsandIntelligentRoboticsLab](https://www.youtube.com/watch?v=8ONOsnArxnQ&ab_channel=BiomechatronicsandIntelligentRoboticsLab).
