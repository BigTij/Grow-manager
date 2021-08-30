#include <WiFi.h>
#include <SPI.h>
#include <MySQL_Connection.h>
#include <DHT.h>

#define DHTPIN 34
#define DHTTYPE DHT22

const int DHT22_pin = 34;

char* ssid = "******";
char* pwd = "*******";

IPAddress ip(10,0,0,12);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255,255,0,0);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  WiFi.config(ip,gateway,subnet);

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid,pwd);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

float * GetClimate(){
  float Climate[2];
  for(int i = 0; i < 100; i++){
    Climate[0] += dht.readHumidity();
    Climate[1] += dht.readTemperature();
    delay(2000);
  }
  Climate[0] = Climate[0] / 100;
  Climate[1] = Climate[1] / 100;
  return Climate;
}

void loop() {
  // put your main code here, to run repeatedly:
  float * climate = GetClimate();
  Serial.print("Humidity: ");
  Serial.println(climate[0]);
  Serial.print("Temperature: ");
  Serial.println(climate[1]);
}
