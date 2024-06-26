# Robot Arm Control Instructions

**Last updated by: Weibo**

## Declarations:
- Do not save any old or untested code in the main folder.
- Because unzipping these code files in Dropbox may cause some files to be lost due to too-long filenames in the code file folder, to avoid any unexpected running failure, the best way is to save a copy of the zipped files and extract them on your own PC locally.
- Do not cut/edit any code files, do copy only.
- This folder has been reorganized, where only the latest code that we successfully run are saved under the main folder.
- If you are looking for any older version files/code, check them in the Archive folder.

## Instructions:

### 1. CAN-based Tethered Robot Arm Control
- **ZCANpro software**: a visualizer to transport/receive CAN commands to/with robot arm.
- **Latest upper computer for V3S3 drivers**: reading/setting zero point for each robot arm joint actuator, check the affiliated instruction manual.
- **CAN communication protocol**: understand CAN command for joint actuators.
- - **Important Note!**:please download all the zip file, and then use 'cat largefile.zip.part-* > largefile.zip' to merge.


This option is the most fundamental but solid robot control method. Namely, you directly send CAN command to each robot arm’s joint motor via the CAN debugging software. However, because this method cannot efficiently and intuitively control the robot arm, we usually only use this method to test if the robot hardware is still working, or there are some hardware issues, like cable damages or encoder zero point lost.

### 2. Simple Webpage-based Robot Arm Upper Computer Software Code
Set up a Wi-Fi on LilyGo, then use your PC to connect to LilyGo’s Wi-Fi to read basic robot arm information and set zero point for the robot arm. This option does not provide any control functions on the robot arm.

### 3. Webpage-based Wireless Robot Arm Control Code
This is a Wi-Fi-based wireless control of the robot arm. In this mode, both your PC and LilyGo are connected to a public 3rd-party Wi-Fi. You are connecting with LilyGo to send robot arm control commands through the Wi-Fi, like using a wireless printer.

### 4. Robot Arm Control with a Simulator
This option is like an upgrade version of option 3, where you not only can wirelessly control the robot arm, you will also see a Unity-based .exe software that illustrates a real-time simulator of the robot arm. Your kinematics control commands sent through the software will be reflected by both the robot arm itself and this simulator simultaneously. 
- **Important Note!**:This software is so large to upload. So you can find the software in Google Drive file: to be filled
