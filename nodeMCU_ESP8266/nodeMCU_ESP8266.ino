#include <ESP8266WiFi.h>

const char *ssid = "KIRO310v2";
const char *password="kiro24578";
const char *serverIP = "192.168.0.3";
const int  serverPort = 8080;

uint8_t   POWER_PIN = D0;
uint8_t   LED_PIN = D1;
uint8_t   POWER_VALUE = 0;

void ICACHE_RAM_ATTR IntCallback();

WiFiClient  client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // WIFI connection
  WiFi.begin(ssid, password);
  Serial.println(WiFi.SSID());
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.waitForConnectResult();
  Serial.println(WiFi.localIP());
  
  client.connect(serverIP, serverPort);

  // GPIO D0 interrupt setup
  pinMode(LED_PIN, OUTPUT);
  pinMode(POWER_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(POWER_PIN), IntCallback, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t  value;

  value = digitalRead(POWER_PIN);
  if (value != POWER_VALUE)
  {
    POWER_VALUE = value;
    Serial.println(POWER_VALUE);
    client.print("Power :");
    client.println(value);
  }
  delay(50);

}

void ICACHE_RAM_ATTR IntCallback()
{
  /*
  uint8_t value;

  value = digitalRead(POWER_PIN);
  Serial.print("D0 : ");
  Serial.println(value);
  digitalWrite(LED_PIN, value);
  */
}
