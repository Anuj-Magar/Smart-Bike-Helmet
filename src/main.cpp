#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ---------- Function Declaration (IMPORTANT FIX) ----------
void sendSMS(String lat, String lng);

// ---------------- WiFi Credentials ----------------
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ---------------- SMS API ----------------
String API_KEY = "YOUR_STRING_SMS_API_KEY";
String recipient = "YOUR_RECEPIENT_NUMBER";

// ---------------- MPU6050 ----------------
Adafruit_MPU6050 mpu;
float accidentThreshold = 2.5;   // g-force threshold

// ---------------- GPS ----------------
TinyGPSPlus gps;
HardwareSerial GPSSerial(2);     // UART2 (RX=16, TX=17)
String latitude = "";
String longitude = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // -------- WiFi --------
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  // -------- MPU6050 --------
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("MPU6050 not detected!");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 initialized");

  // -------- GPS --------
  GPSSerial.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("GPS initialized");
}

void loop() {
  // -------- Read MPU6050 --------
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  // Convert m/s² to g
  float ax = accel.acceleration.x / 9.81;
  float ay = accel.acceleration.y / 9.81;
  float az = accel.acceleration.z / 9.81;

  float totalAcc = sqrt(ax * ax + ay * ay + az * az);

  // -------- Accident Detection --------
  if (totalAcc > accidentThreshold) {
    Serial.println("Accident Detected!");

    // Read GPS data for 3 seconds
    unsigned long start = millis();
    while (millis() - start < 3000) {
      while (GPSSerial.available()) {
        gps.encode(GPSSerial.read());
      }
    }

    if (gps.location.isValid()) {
      latitude = String(gps.location.lat(), 6);
      longitude = String(gps.location.lng(), 6);
    } else {
      latitude = "0.000000";
      longitude = "0.000000";
    }

    sendSMS(latitude, longitude);

    delay(15000); // Prevent multiple triggers
  }

  delay(200);
}

// ---------------- SEND SMS FUNCTION ----------------
void sendSMS(String lat, String lng) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String message = "Accident%20Detected!%20Location:%20https://maps.google.com/?q=" +
                     lat + "," + lng;

    String url = "https://api.smsmobileapi.com/sendsms?apikey=" + API_KEY +
                 "&recipients=" + recipient +
                 "&message=" + message +
                 "&sendsms=1";

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("SMS Sent Successfully");
    } else {
      Serial.println("SMS Sending Failed");
    }

    http.end();
  }
}
