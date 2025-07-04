

# List
- Build a cloud based remote wireless grbl controller for PC/Laptop
- Fixing Serial Failed on WIN11

  
<br>

<br>

# Build a cloud based remote wireless grbl controller for PC/Laptop

## Prepare: 
- One ESP32 Development board for PC side
- One Genmitsu USB wifi module for CNC side
- CNC Device:Genmitsu 3018,3020,4040,3030,4030,6050
- CH340 USB 2 Serial Converter
- Dunpoints cables  
- Circuit Breadboard

## Create New Deployment on EMQX Cloud Platform
- Click New Deployment
<img width="1280" alt="048ecbf1a1f2de2ca1d2b9f4950a982" src="https://github.com/user-attachments/assets/3387c336-09b8-4206-a803-63e33caa6228" />

- Choose Deployment Plan,here we recommand Serverless, choose the region 
<img width="954" alt="65df600ea7f8c9901ec0b83f2a15af6" src="https://github.com/user-attachments/assets/484d1427-6f23-4097-8f2d-0656f80e6e84" />

- Set Spend Limit and Project name and then click payment
<img width="954" alt="bf4796be52a9767fe9fb7ab73ddd5b6" src="https://github.com/user-attachments/assets/9e35e9a7-92a9-422a-90a8-a3ef01ad33e5" />

For more pricing details ,pls check https://docs.emqx.com/en/cloud/latest/price/pricing.html

- Upon accepting the terms, the deployment will begin. The deployment's progress can be tracked on the Projects page.
   Once the status updates to Running, your deployment is successfully established and is now operational.
   After the deployment is created, it will appear on the EMQX Platform console home page. Click the Serverless deployment card to enter the deployment overview page.
   On the overview page, you can check the real-time status and connection information for your deployment.


## Add Authentication Information on EMQX Cloud

- Click "Access Control" to get to Client Authentication page.
<img width="598" alt="657ecaf7ac1f116c29e9d49547e47dd" src="https://github.com/user-attachments/assets/be8233bd-d3dc-43bd-baab-6e0b11af1e3a" />

- On the Client Authentication page, select + Add. Enter the username and password in the input fields and click the Confirm button to complete the addition of authentication information.
  In this case , we should add two pairs of username and password <br>
  1: Username:PCHost   password:20250630 <br>
  2: Username:CNCDEVICE   password:20250701 <br>
For more details about adding devices on EMQX Cloud, please check:https://docs.emqx.com/en/cloud/latest/deployments/default_auth.html
  
# Edit demo code and Upload firmware for ESP32 development board (For PC side) 

- Download Wireless_GrblBridge_Host project to local
- Open the Wireless_GrblBridge_Host.ino , which you can find in the project/folder "Wireless_GrblBridge_Host" 
- Fullfill the mqtt broker address and port in code
<img width="617" alt="354d536f169b3c43fd0b05646844ca4" src="https://github.com/user-attachments/assets/203413a9-3c2f-4fbe-9b92-21e390a8b397" />
  
- Fullfill your wifi network SSID/NetworkName and password in code
<img width="327" alt="1751442128227" src="https://github.com/user-attachments/assets/bbbda270-a6e4-431b-a113-f1f1ecff5545" />
  
- Fullfill one of the mqtt username and password you just set on the EMQX cloud platform "default projects"->your deployment->"Access Control" Page
  Username:PCHost   password:20250630
<img width="228" alt="1751443127640" src="https://github.com/user-attachments/assets/d483b10b-831a-4318-b39f-e741b894aef8" />

- Compile and upload the code to ESP32 development board
![image](https://github.com/user-attachments/assets/8279ee3e-95e9-4bd9-8c81-df7a3b93d2ec)



# Edit demo code and Upload firmware for Genmitsu USB WiFi Module (For CNC Device side) 


- Download Wireless_GrblBridge_Device project to local
- Open the Wireless_GrblBridge_Device.ino , which you can find in the project/folder "Wireless_GrblBridge_Device"
  
- Fullfill the mqtt broker address and port in code
<img width="617" alt="354d536f169b3c43fd0b05646844ca4" src="https://github.com/user-attachments/assets/203413a9-3c2f-4fbe-9b92-21e390a8b397" />

- Fullfill your wifi network SSID/NetworkName and password in code
<img width="327" alt="1751442128227" src="https://github.com/user-attachments/assets/bbbda270-a6e4-431b-a113-f1f1ecff5545" />

- Fullfill one of the mqtt username and password you just set on the EMQX cloud platform "default projects"->your deployment->"Access Control" Page
  here we use Username:CNCDEVICE   password:20250701
<img width="228" alt="1751443127640" src="https://github.com/user-attachments/assets/d483b10b-831a-4318-b39f-e741b894aef8" />

- Compile and upload the code to ESP32 development board
  Wiring as the following pic for uploading 
<img width="820" alt="517b4d020bb1ad24302c7af581c4401" src="https://github.com/user-attachments/assets/296e1235-30cd-4c0f-a3b8-9ae3d862963f" />


# Connect ESP32 Dev board/Genmitsu USB WiFi Module to PC/CNC Device 

<img width="301" alt="7d48fb7dd7283aa93bc19ce6d2c33e4" src="https://github.com/user-attachments/assets/7f2ae942-c6ac-4c0f-baec-32ffd4745e70" />

<br>

<br>

<img width="671" alt="832c555fc9b87344062a0402b29d19c" src="https://github.com/user-attachments/assets/e2a2af3f-f0c4-4edd-bf85-23fa7751c6b8" />


# Turn on Candle/gSender and select the COM port that ESP32 Dev board is using 
- Now you can open Candle or gSender to control your CNC wireless and remotely 
<br>
<br>

<br>
<br>

<br>
<br>

<br>


# Fixing CNC CH340 Serial Connection Failed on WIN11

### Genmistu CNC 3018,4030,6050 USB port connection issue

When connecting a CNC machine to a Windows 11 PC via a serial port (e.g., USB-to-serial adapter using a CH340 chip), you may encounter connection failures in software like Candle or gSender. 
This is often caused by an outdated or incompatible CH340 driver on Windows 11, which prevents proper communication with the CNC controller.


###  Solution: Update the CH340 Driver

To resolve the issue, update the CH340 driver using the stable driver installation file provided in the CH340_STABLE_DRIVER folder. 
Follow these steps:Locate the Driver:Navigate to the CH340_STABLE_DRIVER folder on your PC.
Find the driver installation file (e.g., CH340SER.EXE or similar).
<br>

<br>

- Install the Driver:
1. Double-click the driver installation file to run it.
2. Follow the on-screen instructions to install the updated CH340 driver.
3. If prompted, allow the installer to make changes to your system.

<br>

<br>

- Test the Connection:Open Candle or gSender.
1. Select the correct COM port (as shown in Device Manager).
2. Attempt to connect to your CNC machine.
3. If the connection succeeds, the issue is resolved.



