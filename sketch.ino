#include <Adafruit_MPU6050.h>  // Adafruit MPU6050 kütüphanesini dahil eder. Bu kütüphane, MPU6050 sensörünün kullanımını sağlar.
#include <Adafruit_Sensor.h>   // Adafruit Sensor kütüphanesini dahil eder. Bu kütüphane, sensör verilerini okumak için gerekli fonksiyonları sağlar.
#include <Adafruit_SSD1306.h>  // Adafruit SSD1306 OLED ekran kütüphanesini dahil eder. Bu kütüphane, OLED ekranın kullanımını sağlar.
#include <Adafruit_GFX.h>      // Adafruit GFX grafik kütüphanesini dahil eder. Bu kütüphane, temel grafik işlemleri için kullanılır.
#include <Wire.h>              // I2C iletişim protokolü kütüphanesini dahil eder. MPU6050 ve SSD1306 gibi I2C cihazlarla iletişim kurmak için kullanılır.
#include <Servo.h>             // Servo motor kütüphanesini dahil eder. Bu kütüphane, servo motorların kontrol edilmesini sağlar.
#include <SD.h>                // SD kart kütüphanesini dahil eder. Bu kütüphane, SD kartın kullanımını ve veri kaydını sağlar.

#define EKRAN_GNSLK 128             // OLED ekran genişliği
#define EKRAN_YKSKLK 64             // OLED ekran yüksekliği
#define OLED_RESET -1               // OLED reset pini (-1 ise reset kullanılmaz)
#define OLED_ADDRESS 0x3C           // SSD1306 I2C adresi --onemli!!

Adafruit_SSD1306 ekran(EKRAN_GNSLK, EKRAN_YKSKLK, &Wire, OLED_RESET); // OLED "ekran" nesnesi oluşturulur

Adafruit_MPU6050 sensor;       // MPU6050 "sensor" nesnesi oluşturulur

Servo servoMotor1;          // servoMotor1 nesnesi oluşturulur
Servo servoMotor2;          // servoMotor2 nesnesi oluşturulur

const int cipSecim = 53;    // SD kart çip seçim pini 53 olarak bağlandı.
File dosya;                 //uzerine yazılacak "dosya" nesnesi File türünde oluşturulur

//-----------------------------------------------
void setup() // CIHAZLARI BASLATMA
{ // Serial port başlatılır
  Serial.begin(115200); // Arduino ile seri iletişim
  // Servo motorlar bağlanır
  servoMotor1.attach(9); //servo motor1 in V+ ile baglantı pini
  servoMotor2.attach(10); //servo motor2 nin V+ ile baglantı pini

  // sensor baslatma
  if (!sensor.begin()) { // Sensör başlatılamazsa konsol üzerinden aşağıdaki hata mesajı verilir
    Serial.println("MPU6050 sensoru baslatilamadi!");
    while (1) {
      delay(10);
    }
  }// Sensör başlatılırsa  konsol üzerinden aşağıdaki bilgi mesajı verilir
  Serial.println("MPU6050 sensoru baslatildi...");

  //OLED ekran başlatma
  if (!ekran.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) { // SSD1306_SWITCHCAPVCC, ekranın dahili voltaj regülatörünü kullanarak başlatılacağını belirtir.
    // OLED_ADDRESS => 0x3C, OLED ekranının I2C adresidir. (burası önemli çünkü 0x3d diye diğer secenekle karıştırılmamalıdır!)
    Serial.println(F("OLED ekran baslatilamadi!"));// Ekran başlatılamazsa konsol üzerinden bu hata mesajı verilir
    while (1);
  }
  Serial.println(F("OLED ekran baslatildi...")); // Ekran başlatılırsa konsol üzerinden bu bilgi mesajı verilir
  delay(10);

  // SD kart başlatılır
  if (!SD.begin(cipSecim)) {                // SD kart başlatılamazsa konsol üzerinden aşağıdaki hata mesajı verilir
    Serial.println("SD kart baslatilamadi!");
    return;
  }
  Serial.println("SD kart baslatildi...");  // SD kart başlatılırsa konsol üzerinden bu bilgi mesajı verilir
  delay(2000); //her sey hazır olduğunda 2 sn sonra simulasyon çalışmaya başlar

  // Accelerometer ve gyro aralıkları ayarlanır
  sensor.setAccelerometerRange(MPU6050_RANGE_8_G); //Sensörün ivmeölçerinin ölçebileceği maksimum ivme aralığını ayarlar.
  //MPU6050_RANGE_8_G değeri, ivmeölçerin ±8G'ye kadar olan ivmeleri ölçebilmesini sağlar.
  sensor.setGyroRange(MPU6050_RANGE_500_DEG);      //Gyroskopun ölçebileceği max açısal hız aralığını ayarlar.
  //MPU6050_RANGE_500_DEG değeri, gyroskopun ±500 derece/saniye'ye kadar olan açısal hızları ölçebilmesini sağlar.
  sensor.setFilterBandwidth(MPU6050_BAND_5_HZ);    //Sensörün filtre bant genişliğini ayarlar.
  //MPU6050_BAND_5_HZ değeri, sensör çıkışındaki yüksek frekanslı gürültünün azaltılmasına yardımcı olur.
}

//----------------------------------------------------------------------------
void loop() { // YAZDIRMA ISLEMLERİ
  Serial.println();
  Serial.println("SD karta yazılan ölçümler:"); //Konsol ekranına "SD karta yazılan ölçümler:" yazdırılır.
  // Sensör verileri alınır
  sensors_event_t a, g, temp; // sensors_event_t türünde a (ivme), g (gyro) ve temp (sıcaklık) değişkenleri tanımlanır
  sensor.getEvent(&a, &g, &temp); //a, g ve temp değişkenlerini günceller

  //------------------------------------------------------
  // CONSOLE EKRANI
  Serial.println("Accelerometer (m/s^2)"); //Konsol ekranına "Accelerometer (m/s^2)" yazdırılır.
  Serial.print(a.acceleration.x); //Konsol ekranına x eksenindeki ivme değeri yazdırılır.
  Serial.print(", "); //Konsol ekranına "," yazdırılır
  Serial.print(a.acceleration.y); //Konsol ekranına y eksenindeki ivme değeri yazdırılır.
  Serial.print(", "); //Konsol ekranına "," yazdırılır
  Serial.println(a.acceleration.z);  //Konsol ekranına z eksenindeki ivme değeri yazdırılır.

  Serial.println("Gyroscope - rps"); //Konsol ekranına "Gyroscope - rps" yazdırılır.
  Serial.print(g.gyro.x); // Gyroscope un x eksenindeki deger konsola yazdırılır.
  Serial.print(", ");//Konsol ekranına "," yazdırılır
  Serial.print(g.gyro.y); // Gyroscope un y eksenindeki deger konsola yazdırılır.
  Serial.print(", ");//Konsol ekranına "," yazdırılır
  Serial.println(g.gyro.z); // Gyroscope un z eksenindeki deger konsola yazdırılır.

  //map(value, fromLow, fromHigh, toLow, toHigh):
  //Bir değeri belirli bir aralıktan başka bir aralığa dönüştürür.
  int servoYon1 = map(g.gyro.x, -5, 5, 0, 180); //g.gyro.x değerini -5 ile 5 aralığından 0 ile 180 aralığına dönüştürür.
  servoMotor1.write(servoYon1); //servoMotor1'i servoYon1 konumuna ayarlar.
  int servoYon2 = map(g.gyro.y, -5, 5, 0, 180); // g.gyro.y değerini -5 ile 5 aralığından 0 ile 180 aralığına dönüştürür.
  servoMotor2.write(servoYon2); //servoMotor2'yi servoYon2 konumuna ayarlar.

  Serial.println("Temperature");//Konsol ekranına "Temperature" yazdırılır.
  Serial.print(temp.temperature); //Konsol ekranına alınan sıcaklık degeri yazdırılır
  Serial.println(" degC"); //yazılan degerin yanına "degC" yazılır.

  //------------------------------------------------------
  // EKRANA YAZDIRMA
  ekran.clearDisplay(); //Oled ekranı temizlenir.
  ekran.setTextSize(1); //ekranın yazı boyutu ayarlanır
  ekran.setTextColor(SSD1306_WHITE); //yazı rengi WHITE olarak secilir.
  ekran.setCursor(0, 0); //ekranda yazılacak metnin imlec konumu belirlenir

  ekran.print("Accelerometer-(m/s^2)"); //Oled ekranına "Accelerometer-(m/s^2)" yazdırılır.
  ekran.print(a.acceleration.x); //oled ekranına x eksenindeki ivme değeri yazdırılır.
  ekran.print(", "); //oled ekranına "," yazdırılır
  ekran.print(a.acceleration.y); //oled ekranına y eksenindeki ivme değeri yazdırılır.
  ekran.print(", "); //oled ekranına "," yazdırılır
  ekran.println(a.acceleration.z); //oled ekranına z eksenindeki ivme değeri yazdırılır.
  ekran.println();

  ekran.println("Gyroscope - rps"); //Oled ekranına "Gyroscope - rps" yazdırılır.
  ekran.print(g.gyro.x); // Gyroscope un x eksenindeki deger ekrana yazdırılır.
  ekran.print(", "); //oled ekranına "," yazdırılır
  ekran.print(g.gyro.y); // Gyroscope un y eksenindeki deger ekrana yazdırılır.
  ekran.print(", "); //oled ekranına "," yazdırılır
  ekran.println(g.gyro.z); // Gyroscope un z eksenindeki deger ekrana yazdırılır.
  ekran.println();

  ekran.println("Temperature"); //Oled ekranına "Temperature" yazdırılır.
  ekran.print(temp.temperature); //oled ekranına alınan sıcaklık degeri yazdırılır
  ekran.println(" degC"); //yazılan degerin yanına "degC" yazdırılır.

  ekran.display(); //ekrandaki görüntüyü güncellemek için kullanılır.

  //------------------------------------------------------
  // SD KARTA YAZMA ISLEMI
  dosya = SD.open("mpu6050.txt", FILE_WRITE); //mpu6050.txt dosyası açılır ve FILE_WRITE (yazma) modu açılır.
  if (dosya) { //dosya açılırsa...
    dosya.println("Accelerometer-(m/s^2)"); //Dosyaya "Accelerometer-(m/s^2)" yazdırılır.
    dosya.print(a.acceleration.x); //dosyaya x eksenindeki ivme değeri yazdırılır.
    dosya.print(", "); //dosyaya "," yazdırılır
    dosya.print(a.acceleration.y); //dosyaya y eksenindeki ivme değeri yazdırılır.
    dosya.print(", "); //dosyaya "," yazdırılır
    dosya.println(a.acceleration.z); //dosyaya z eksenindeki ivme değeri yazdırılır.

    dosya.println("Gyroscope-(rps)"); //Dosyaya "Gyroscope-(rps)" yazdırılır.
    dosya.print(g.gyro.x); // Gyroscope un x eksenindeki deger dosyaya yazdırılır.
    dosya.print(", "); //dosyaya "," yazdırılır
    dosya.print(g.gyro.y); // Gyroscope un y eksenindeki deger dosyaya yazdırılır.
    dosya.print(", "); //dosyaya "," yazdırılır
    dosya.println(g.gyro.z); // Gyroscope un z eksenindeki deger dosyaya yazdırılır.

    dosya.println("Temperature"); //Dosyaya "Temperature" yazdırılır.
    dosya.print(temp.temperature); //dosyaya alınan sıcaklık degeri yazdırılır
    dosya.println(" degC"); //yazılan degerin yanına "degC" yazdırılır.

    dosya.close(); //dosya kapatılır
    Serial.println("SD karta yazıldı..."); //if blogu calışmış olacagı için yazma işlemi basarılı geçmiş demektir.
  } else {
    Serial.println("Dosya acılamadi!");// if bloguna girilemediyse hata mesajı konsola verilir.
  }
}