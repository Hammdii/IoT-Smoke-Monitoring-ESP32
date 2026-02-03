# IoT-Smoke-Monitoring-ESP32
# IoT Smoke Monitoring System using ESP32 & MQ-135

An Internet of Things (IoT)–based system for real-time cigarette smoke monitoring using ESP32 and MQ-135 gas sensor. The system collects air quality data, processes it on the microcontroller, and displays the results in real time via cloud and mobile applications.

---

## 🔧 Technologies Used
- **Microcontroller:** ESP32  
- **Sensor:** MQ-135 Gas Sensor  
- **Programming Language:** C / C++ (Arduino IDE)  
- **Cloud Platform:** Firebase Realtime Database  
- **Mobile App:** MIT App Inventor  
- **Visualization Platform:** Blynk  
- **Communication:** Wi-Fi (HTTP / Realtime Database)

---

## 📖 Project Description
This project was developed to monitor cigarette smoke concentration in indoor environments. The MQ-135 sensor detects air quality levels, which are processed by the ESP32 and transmitted to a cloud database. Users can monitor air quality data in real time through a mobile application.

The system is designed to support environmental monitoring and promote healthier indoor air conditions.

---

## ⚙️ System Features
- Real-time smoke concentration monitoring  
- Continuous sensor data acquisition with ±2 second interval  
- Cloud-based data storage using Firebase Realtime Database  
- Mobile application for live monitoring  
- Threshold-based alerts for unsafe air quality levels  

---

## 🧠 System Architecture
1. MQ-135 sensor detects smoke concentration  
2. ESP32 processes sensor data  
3. Data sent to Firebase via Wi-Fi  
4. Mobile app retrieves and displays data in real time  
