#include <WiFi.h>
#include <ESP32FtpServer.h>

// Wi-Fi credentials
const char* ssid = "WIFI_NETWORK_NAME";
const char* password = "WIFI_NETWORK_PASSWORD";

// FTP-SERVER credentials
char ftp_server[] = "192.168.1.13";
char ftp_user[] = "ESP";
char ftp_pass[] = "123";

// Sensor Pins
const int trigPin = 14;
const int echoPin = 13;

// Speed of sound in cm/μS
const float SOUND_SPEED = 0.034;

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distanceCm = duration * SOUND_SPEED/2;
if(distanceCm < 50){
  char name[50];
  n = sprintf(name, "Pic%d.jpg", N_FILE);
  N_FILE++;
  Serial.println("Taking a photo...");
  
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  Serial.printf("Picture file name: %s\n", name);

ftp.OpenConnection();
Serial.println("---FTP Connected---");
ftp.InitFile("Type I");
ftp.NewFile(name);
Serial.println("---FTP Connection--- file is made");
ftp.WriteData(fb->buf, fb->len);
Serial.println("---FTP Connected--- Data is written");
ftp.CloseFile();
ftp.CloseConnection();
Serial.println("---FTP Connection Closed---");
esp_camera_fb_return(fb);
}
