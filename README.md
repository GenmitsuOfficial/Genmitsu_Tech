

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
