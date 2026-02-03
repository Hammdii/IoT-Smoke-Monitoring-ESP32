#include <FirebaseESP32.h>
#include <WiFi.h>

// Informasi Wi-Fi
const char* ssid = "eril1234"; 
const char* password = "eril1234";

// Informasi Firebase
#define FIREBASE_HOST "https://monitoringasaprokok-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "sa0RC8H0GKilpkh2n4S8slg2ulmjh8dpXMUfoszD"
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Pin untuk sensor dan output
const int mq135_pin = 34;  // Pin ADC untuk MQ135
const int buzzerPin = 25;  // Pin untuk buzzer
const int relayPin = 26;   // Pin untuk relay

// Variabel sensor dan ambang batas
int sensitivity = 800;
int air_quality = 0;
const int mqThreshold = 100;

// Fungsi membaca sensor MQ135
void readMQ() {
    int sensorVal = analogRead(mq135_pin);
    air_quality = sensorVal * sensitivity / 4096;
}

// Setup koneksi WiFi
void setup_wifi() {
    Serial.print("Menghubungkan ke WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi terhubung!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Setup utama
void setup() {
    Serial.begin(115200);
    setup_wifi();

    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    pinMode(mq135_pin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(relayPin, OUTPUT);

    digitalWrite(relayPin, LOW); // Matikan relay saat boot

    Serial.println("Monitoring Asap Rokok dengan Sensor MQ135 dan Firebase");
}

// Loop utama
void loop() {
    readMQ();

    Serial.print("Air Quality (MQ135): ");
    Serial.print(air_quality);
    Serial.println(" PPM");

    if (Firebase.setInt(firebaseData, "/monitoring/air_quality", air_quality)) {
        Serial.println("Data terkirim ke Firebase.");
    } else {
        Serial.print("Gagal mengirim data: ");
        Serial.println(firebaseData.errorReason());
    }

    if (air_quality > mqThreshold) {
        Serial.println("Peringatan: Kadar Asap Berbahaya (> 200 PPM)!");

        digitalWrite(relayPin, LOW); // Nyalakan relay
        Firebase.setString(firebaseData, "/monitoring/relay_status", "ON");

        for (int i = 0; i < 5; i++) {
            digitalWrite(buzzerPin, HIGH);
            delay(200);
            digitalWrite(buzzerPin, LOW);
            delay(200);
        }
    } else {
        Serial.println("Kadar Asap Normal.");

        digitalWrite(relayPin, HIGH); // Matikan relay
        Firebase.setString(firebaseData, "/monitoring/relay_status", "OFF");

        digitalWrite(buzzerPin, LOW);
    }

    delay(1000);
}
