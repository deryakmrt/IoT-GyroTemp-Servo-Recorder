Projemin Wokwi Linki: https://wokwi.com/projects/398311724408819713
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
