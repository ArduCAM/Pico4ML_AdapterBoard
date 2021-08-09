## Getting started
See Getting Started with the Raspberry Pi Pico and the README in the pico-sdk for information on getting up and running.
## Get Arducam
```
git clone https://github.com/ArduCAM/Pico4ML_AdapterBoard.git
```

## Pico4ML_AdapterBoard Examples
+ HM01B0
* HM0360
+ MagicWand
- PICO_SPI_Camera
+ pico-wake-word
+ tflmicro


## HM01B0 Or HM0360
This example demonstrates how to display the image data collected by the HM01B0 or HM0360 camera on the screen.
The following demo is based on HM01B0 as an example
### Compile
```
cd  Pico4ML_AdapterBoard/HM01B0
mkdir build
cd build
cmake ..
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/HM01B0_cmake.png)
```
make 
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/HM01B0_make.png)
### Results the following
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/HM01B0_demo.jpg)


## MagicWand
This example demonstrates the recognition of gestures and displays the recognition results on the screen.
```
cd  Pico4ML_AdapterBoard/MagicWand
mkdir build
cd build
cmake ..
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/MagicWand_cmake.png)
```
make 
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/MagicWand_make.png)
**This project provides two examples**
| Folder                                                       | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| magic_wand										|This example can recognize Solpe, Ring, and Wing gestures, and display the recognition results on the screen.|
| magic_wand_ble									|This example can recognize 0-9 gestures, display the recognition results on the screen, and send the data to the web page through the Bluetooth module.|
### Solpe, Ring, Wing gestures are as follows
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/Slope.gif)
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/Ring.gif)
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/Wing.gif)


## PICO_SPI_Camera
This example demonstrates how to use an SPI camera. This example supports two models: OV2640 and 0V5642.
### Now Supported Cameras
-	OV2640		2MP	JPEG
-	OV5642		5MP	JPEG

### Compile
```
cd  Pico4ML_AdapterBoard/PICO_SPI_Camera
mkdir build
cd build
cmake ..
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/SPICamera_cmake.png)
```
make 
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/SPICamera_make.png)
### Results the following(OV2640)
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/SPICamera_Demo.png)



## pico-wake-word
This is an application of Wake word detection.Use a pre-trained speech detection model to provide always-on wake-word detection.
### Compile
```
cd  Pico4ML_AdapterBoard/pico-wake-word
mkdir build
cd build
cmake ..
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/mic_cmake.png)
```
make 
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/mic_make.png)




## tflmicro
This is an application of person_detection.
Classify Images captured by a camera to recognize if a person is in the camera input or not.
### Compile
```
cd  Pico4ML_AdapterBoard/tflmicro
mkdir build
cd build
cmake ..
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/person_cmake.png)
```
make 
```
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/person_make.png)
**This project provides two examples**
| Folder                                                       | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| person_detection_screen										|This example uses the HM01BO or HM0360 camera to detect people and displays the recognition results on the screen.|
| person_detection									|This example uses the OV2640 camera for person detection, and displays the recognition result through the person_detection_display script.|
**HM01B0 camera for face recognition**
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/person_demo.png)
**OV2640 camera for face recognition**
![EasyBehavior](https://github.com/UCTRONICS/pic/blob/master/pico4ml_extend_Picture/person_ov2640.png)