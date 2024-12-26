#include <WiFi.h>
#include <WiFiAP.h>

// Wi-Fi credentials for the existing network
const char* ssid_STA = "o2-WLAN63";
const char* password_STA = "B6PB4QP43MEZXQ36";

// Credentials for the ESP32-C3 Wi-Fi extender AP
const char* ssid_AP = "ESP32";
const char* password_AP = "aliali";

// Define the AP IP range
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to the existing Wi-Fi network
  WiFi.begin(ssid_STA, password_STA);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi network as STA");
  Serial.print("STA IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the ESP32 as an Access Point
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid_AP, password_AP);
  Serial.println("ESP32 AP started");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start scanning for new devices
  WiFi.onEvent(WiFiEvent);
}

void loop() {

}

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  if (event == IP_EVENT_AP_STAIPASSIGNED) {
    Serial.print("New device connected, IP address: ");
    Serial.println(WiFi.softAPIP());
  }
}

