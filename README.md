# Proximity-activated-security-camera
ESP32-CAM streams video over Wi-Fi + uses ultrasonic sensor to detect objects within 50cm. Automatically captures images &amp; sends via FTP when triggered. Perfect for smart security systems!

# Components

•	ESP32-Cam.

•	5V Step Down Converter.

•	9V Battery.

•	Ultrasonic Sensor.

•	FTDI converter (not needed while operating).

# Concept

The ESP32-CAM will be streaming over Wi-Fi, it will also be connected to the Ultrasonic sensor, the Ultrasonic sensor is going to measure the distance between the person/object in front of it and will send the data to the ESP32, the ESP32 will process the data, and if the distance falls below a threshold (50 CM), it will take a picture and send it to the connected computer via an FTP-Server.

# Circuit Diagram

![image](https://github.com/Ahmed-Taha28/Proximity-activated-security-camera/blob/main/images/circuit_diagram.png?raw=true)

# Code

## Declaring the code constants

```cpp
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
```
## Connecting to Wi-Fi
```cpp
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
```
## Calculating the Distance using the Ultrasonic
```cpp
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm = duration * SOUND_SPEED/2;
```
## Taking the picture
```c
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
```
## Sending the image via the FTP-SERVER
```cpp
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
```
# Uploading the code

To upload the code, we first need to short pins: IO0 and GND.

We will be using the Arduino IDE to upload our code
After connecting the computer to the FTDI connector via USB, we choose the corresponding COM port on the Arduino IDE and hit upload, then we will see the following message:

![image](https://github.com/photo.jpg)
We hit the RST button on the ESP32, and it will start uploading, then we will see this message when it finishes

[<img width="623" height="151" alt="image" src="https://github.com/user-attachments/assets/18962bda-3ace-4ab5-aa5f-62ffb6ffc546" />](https://github.com/Ahmed-Taha28/Proximity-activated-security-camera/blob/main/images/start_upload.png)

# Connecting to the stream

After disconnecting pins IO0 and GND, we will see the following on the serial monitor inside the Arduino IDE

Using a web-browser we connect to the ip shown, and we will see a live-feed from the ESP32-CAM.

![image](https://github.com/Ahmed-Taha28/Proximity-activated-security-camera/blob/main/images/Connecting%20to%20the%20stream.png)
