

​​Sharing Knowledge and Solutions for Common CNC Laser Machine and MCU Tech Issues​ and Scenes

# List
- Display non ASCII Japanese on GUISlice
- Build a cloud based remote wireless grbl controller for PC/Laptop
- Fixing Serial Failed on WIN11

  








# Display non ASCII Japanese on GUISlice

  -OS here is Windows 9-11
  -Microcontroller to use here is ESP32 wroom 32E
  -You can directly use the vlw file in the GUISliceJapaneseCharacters folder and Upload to your MCU 

## Step one download TTF and Install Font on OS: 

We use open source free font——M PLUS 1p, which you can download from https://fonts.google.com/specimen/M+PLUS+1p

We choose the 8px version as following img shows for 3.5-4 inch LCD screen: 

   <img width="1151" alt="1751354905114" src="https://github.com/user-attachments/assets/03418612-4dd2-458c-ad0d-5b1304892cf0" />

Unpack/Unzip the zip downloaded and click to the unzip folder to choose font you wanna use:
   <img width="321" alt="965d7ecca8894adfccdeb98a561b25e" src="https://github.com/user-attachments/assets/58b6db03-f207-4f48-9a66-516fdcbb0ae6" />

In this case ,we use the MPLUS1p-Regular.ttf, right click the filename and select install.


## Step Two Convert TTF to VLW:

Open Proccessing IDE and click Tool->Create Font->Find the font you just installed on OS e.g  MPLUS1p-Regular ->set the size and click OK

<img width="857" alt="f6c4be7e30f1ea88f9325489d8ac356" src="https://github.com/user-attachments/assets/ac4a3478-f122-497d-8cde-56f0c93915a9" />

After doing this, click File->Open to confirm the path your vlw file is.


## Step Three Create the Arduino Project 

![image](https://github.com/user-attachments/assets/10293714-0957-4836-b152-1f628367e22d)



## Step Four Upload VLW file to MCU Flash

1. Create a folder named "data" under the path of project folder
<img width="193" alt="f77ec3974c9f96814319656cc76b8fd" src="https://github.com/user-attachments/assets/ad153fd3-0a5e-42ef-ac3a-41c0357858c5" />

2. Copy the vlw file to the data folder
3. Install Ardunio IDE plugin for uploading files to MCU Flash
   -For Arduino IDE 1.8.x 
      *Install the ESP32 Filesystem Uploader plugin from this GitHub release https://github.com/me-no-dev/arduino-esp32fs-plugin/releases.  
      *Create a data folder in your sketch, add files, and use Tools > ESP32 Sketch Data Upload to select SPIFFS or LittleFS.  
      *Close the Serial Monitor and press the BOOT button if needed during upload.

   -For Arduino IDE 2.x.x 
      *Download the .vsix file for the LittleFS uploader from this GitHub release. The latest version is 1.2.0 as of recent discussions.
      *Place the .vsix file in the plugins folder:Windows: C:\Users\<username>\.arduinoIDE\plugins (create the folder if needed).
      *Restart the Arduino IDE.

4. upload vlw file
    -For Arduino IDE 1.8.x
     Click Tool->ESP32 DATA Sketch Upload 
    -For Arduino IDE 2.x.x
     Press Ctrl + Shift + P (Windows) to open the command palette, search for "Upload LittleFS to Pico/ESP8266/ESP32," and select it.


## Step Five Coding and Upload Firmware 
 -Add this code inside the SetUp():
 ```
      if (!SPIFFS.begin(true)) { 
       return;
       }
 ``` 
 -Add E_MPLUS1P_REGULAR_12V or other Macro name for the Font in the enum for Fonts：
 ```
    enum {E_BUILTIN10X16,E_MPLUS1P_REGULAR_9V,MAX_FONT};
 ```
 -Add this code to the InitGUIslice_gen function:
 ```
        if (!gslc_FontSet(&m_gui,E_MPLUS1P_REGULAR_12V,GSLC_FONTREF_FNAME,"MPLUS1p-Light-12",12)) { return; }
         gslc_FontSetMode(&m_gui, E_MPLUS1P_REGULAR_12V, GSLC_FONTREF_MODE_1);
 ```

## Compile and Upload firmware to ESP32 

![7fdc6608ad5accc0de7a50e18c39060](https://github.com/user-attachments/assets/842a14fd-b34a-4a50-b3e8-a24a09221ed8)

<br>

<br>

<br>

<br>
<br>

<br>
<br>

<br>
<br>

<br>


# Build a cloud based remote wireless grbl controller for PC/Laptop

## Prepare: 
- One ESP32 Development board for PC side
- One Genmitsu USB wifi module for CNC side
- CNC Device:Genmitsu 3018,3020,4040,3030,4030,6050
- CH340 USB 2 Serial Converter
- Dunpoints cables 

## Create New Deployment on EMQX Cloud Platform
- Click New Deployment
<img width="1280" alt="048ecbf1a1f2de2ca1d2b9f4950a982" src="https://github.com/user-attachments/assets/3387c336-09b8-4206-a803-63e33caa6228" />
- Choose Deployment Plan,here we recommand Serverless, choose the region 
<img width="954" alt="65df600ea7f8c9901ec0b83f2a15af6" src="https://github.com/user-attachments/assets/484d1427-6f23-4097-8f2d-0656f80e6e84" />
- Set Spend Limit and Project name and then click payment
<img width="954" alt="bf4796be52a9767fe9fb7ab73ddd5b6" src="https://github.com/user-attachments/assets/9e35e9a7-92a9-422a-90a8-a3ef01ad33e5" />
For more pricing details ,pls check https://docs.emqx.com/en/cloud/latest/price/pricing.html
-Upon accepting the terms, the deployment will begin. The deployment's progress can be tracked on the Projects page.
 Once the status updates to Running, your deployment is successfully established and is now operational.
 After the deployment is created, it will appear on the EMQX Platform console home page. Click the Serverless deployment card to enter the deployment overview page.
 On the overview page, you can check the real-time status and connection information for your deployment.


## Add Authentication Information

- Click "Access Control" to get to Client Authentication page.
<img width="598" alt="657ecaf7ac1f116c29e9d49547e47dd" src="https://github.com/user-attachments/assets/be8233bd-d3dc-43bd-baab-6e0b11af1e3a" />
- On the Client Authentication page, select + Add. Enter the username and password in the input fields and click the Confirm button to complete the addition of authentication information.
 In this case , we should add two pairs of username and password :
 --Username1:PCHost   password:20250630
 --Username2:CNCDEVICE   password:20250701

  
# Edit demo code and Upload firmware for ESP32 development board (For PC side) 

- Download Wireless_GrblBridge_Host project to local
- Open the Wireless_GrblBridge_Host.ino , which you can find in the project/folder "Wireless_GrblBridge_Host" 
- Fullfill the mqtt broker address and port in code
<img width="617" alt="354d536f169b3c43fd0b05646844ca4" src="https://github.com/user-attachments/assets/203413a9-3c2f-4fbe-9b92-21e390a8b397" />
  
- Fullfill your wifi network SSID/NetworkName and password in code
<img width="327" alt="1751442128227" src="https://github.com/user-attachments/assets/bbbda270-a6e4-431b-a113-f1f1ecff5545" />
  
- Fullfill one of the mqtt username and password you just set on the EMQX cloud platform "default projects"->your deployment->"Access Control" Page
  Username1:PCHost   password:20250630
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
  here we use Username2:CNCDEVICE   password:20250701
  <img width="228" alt="1751443127640" src="https://github.com/user-attachments/assets/d483b10b-831a-4318-b39f-e741b894aef8" />
- Compile and upload the code to ESP32 development board
  Wiring as the following pic for uploading 
  <img width="820" alt="517b4d020bb1ad24302c7af581c4401" src="https://github.com/user-attachments/assets/296e1235-30cd-4c0f-a3b8-9ae3d862963f" />


# Connect ESP32 Dev board/Genmitsu USB WiFi Module to PC/CNC Device 

<img width="301" alt="7d48fb7dd7283aa93bc19ce6d2c33e4" src="https://github.com/user-attachments/assets/7f2ae942-c6ac-4c0f-baec-32ffd4745e70" />
<img width="671" alt="832c555fc9b87344062a0402b29d19c" src="https://github.com/user-attachments/assets/e2a2af3f-f0c4-4edd-bf85-23fa7751c6b8" />


# Turn on Candle/gSender and select the COM port that ESP32 Dev board is using 


