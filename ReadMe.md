# IoT Project: Sensor Data Logging and Display with MPU6050, Arduino Mega, and SSD1306 OLED Display

## Overview
This project focuses on utilizing widely used sensors in IoT applications, specifically the MPU6050 (Accelerometer, Gyroscope, Temperature), along with the Arduino Mega development board, SSD1306 OLED Display, Full BreadBoard, microSD card, and servo motors. The goal is to create a circuit on Wokwi, establish necessary pin connections, and program these components to work together.

## Project Objectives
- Measure Accelerometer (m/s^2), Gyroscope (rps), and Temperature (°C) using MPU6050.
- Display measurement values on the SSD1306 OLED Display.
- Save measurement values to a file named `mpu6050.txt` on the microSD card.
- Control two servo motors using Gyroscope values from MPU6050:
  - The first Gyroscope value controls the first servo motor.
  - The second Gyroscope value controls the second servo motor.

## Components and Tools
- **Development Board:** Arduino Mega
- **Sensors and Modules:**
  - MPU6050 (Accelerometer, Gyroscope, Temperature)
  - SSD1306 OLED Display
  - microSD Card Module
  - Two Servo Motors
- **Additional Components:**
  - Full BreadBoard
  - Connecting wires

- **Simulation Platform:**  https://wokwi.com/projects/398311724408819713

## Programming the Arduino Mega
1. **Libraries Required:**
   - `Wire.h` for I2C communication
   - `Adafruit_SSD1306.h` and `Adafruit_GFX.h` for OLED display
   - `SD.h` for microSD card
   - `Servo.h` for servo motor control

2. **Functionality:**
   - Read sensor data from MPU6050.
   - Display data on the OLED screen.
   - Write data to `mpu6050.txt` on the microSD card.
   - Use Gyroscope values to control two servo motors.

=============================================================  
# Amaç:   
Nesnelerin İnterneti uygulamaları kapsamında yaygın kullanılan sensörlerden (MPU6050 (Accelerometer, Gyroscope, Temperature), ayrıca en yaygın kullanılan geliştirme kartlarından biri olan (ARDUINO MEGA) ve SSD1306 OLED Display, Full BreadBoard, microSD card, servo cihazlarını tanımak, ilgili devreyi wokwide oluşturup gerekli pin bağlantılarını sağlamak ve bunları programlayarak kullanabilmek. Bu noktada gerçekleştireceğiniz ödev sensör tarafından ölçülen Accelerometer (m/s^2), Gyroscope (rps) ve Temperature (degC) sonuçların farklı hedefe aktarılması olacaktır. OLED Ekranda görüntülenen ölçüm değerleri aynı zamanda microSD card içerisinde yer alan mpu6050.txt dosyasına da kaydedilmelidir. İki adet servo motor MPU6050’ye ait Gyroscope değerlerinden birincisi ilk servo motoru ikincisi ise ikincisi servoyu kontrol edecek şekilde düşünülmelidir.  

Eklenen kütüphaneler:  
#include <Adafruit_MPU6050.h>  
#include <Adafruit_Sensor.h>  
#include <Adafruit_SSD1306.h>  
#include <Adafruit_GFX.h>  
#include <Wire.h>  
#include <Servo.h>  
#include <SD.h> 
