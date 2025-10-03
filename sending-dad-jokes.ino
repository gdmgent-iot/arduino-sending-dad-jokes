#include "secrets.h"
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>

// Het domein van de API waar we grappen/facts ophalen
const char api[] = "official-joke-api.appspot.com";
const int api_port = 80;  // HTTP draait op poort 80

// TCP server en client initialiseren
WiFiServer server(5000);       // onze Arduino draait een server op poort 5000
WiFiClient wifiClient;               // WiFi client voor inkomende verbindingen
HttpClient httpClient(wifiClient, api, api_port); // HTTP-client om API-requests te doen

// Timers voor periodieke API-requests
unsigned long lastrequest = 0;    // wanneer hebben we voor het laatst data opgehaald
unsigned long interval = 10000;   // elke 10 seconden een nieuwe grap ophalen

// IP van een andere Arduino in het netwerk
const char* other_arduino_ip = "192.168.1.126";


// ---------------------- WIFI CONNECTIE ----------------------
void connectToWiFi() {
  int attempts = 0;

  // Probeer tot 5 keer om te verbinden met het netwerk
  while (WiFi.status() != WL_CONNECTED && attempts < 5) {
    Serial.print("Verbinden met netwerk: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    delay(2000);
    attempts++;
  }

  // Debug-informatie tonen
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected :-)");
    Serial.println("IP-adres is: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Kan niet verbinden...");
  }
}

// ---------------------- CONTROLEER OF WIFI VERBINDING NOG STEEDS BESTAAT ----------------------
void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi verloren, opnieuw verbinden...");
    connectToWiFi();
  }
}

// ---------------------- SERVER STARTEN ----------------------
void connectToServer() {
  if (WiFi.status() == WL_CONNECTED) {
    server.begin();
    Serial.println("TCP Server is actief op poort 5000");
  }
}

// ---------------------- SETUP ----------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Booting the arduino, hold your horses");
  delay(2000);

  connectToWiFi();
  connectToServer();
}

// ---------------------- LOOP ----------------------
void loop() {
  checkWiFiConnection();    // controleer of WiFi verbinding nog steeds bestaat
  listenToCatFact();         // regelmatig een grap ophalen van API
  listenToClientMessages();  // inkomende berichten van andere Arduino’s
}

// ---------------------- API CALL ----------------------
void listenToCatFact() {
  // Check of interval verstreken is
  if (millis() - lastrequest < interval) return;
  lastrequest = millis();

  Serial.println("Requesting a fact from the API");

  // Vraag een random grap op
  httpClient.get("/jokes/random");
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);

  // Indien succesvol (200 OK)
  if(statusCode == 200) {
    JSONVar jsonResponse = JSON.parse(response);

    // JSON geeft waarden terug als `const char*`, we casten naar String
    String fact = (const char*) jsonResponse["setup"];
    fact += " - ";
    fact += (const char*) jsonResponse["punchline"];

    Serial.print("Fact: ");
    Serial.println(fact);

    // Stuur de fact door naar andere Arduino
    WiFiClient client;
    if (client.connect(other_arduino_ip, 5000)) {
      Serial.println("Connected to other arduino, sending fact");
      client.println(fact);
      client.stop();
    } else {
      Serial.println("Connection to other arduino failed");
    }
    
  } else {
    Serial.print("Error in retrieving fact: ");
    Serial.println(statusCode);

  }
  httpClient.stop();
}

// ---------------------- BERICHTEN VAN CLIENTS ----------------------
void listenToClientMessages() {
    WiFiClient client = server.available();  // check of er een client verbinding maakt
    if (!client) return; // geen client, stoppen

    IPAddress clientIp = client.remoteIP();
    Serial.print("Client connected from IP: ");
    Serial.println(clientIp);

    while (client.connected()) {
        if (client.available()) {
            String msg = client.readStringUntil('\n'); // lees bericht
            Serial.print("Bericht van client: ");
            Serial.println(msg);
        }
    }
    client.stop();
}
