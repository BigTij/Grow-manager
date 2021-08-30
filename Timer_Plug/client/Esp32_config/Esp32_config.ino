#include <string.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WiFi.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#define MAX 80
#define PORT 1025
#define SA struct sockaddr

const int RELAY1_pin = 34; // gpio pin connected to relay trigger
const int RELAY2_pin = 35;
const int RELAY3_pin = 32;
const int RELAY4_pin = 33;

int randomNumberPin = 0; //choose an analog pin that is not connected
                         //to anything
int PublicKey[2];

// Wifi config:
const char* ssid     = "Lussier";
const char* password = "************";
byte mac[6];

//IPAddress server_addr(10,0,0,14);
WiFiServer server(PORT);

void setup() {
  Serial.begin(115200);
  delay(10);

  // connect to wifi network
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  IPAddress local_IP(10,0,0,111);
  IPAddress gateway(10,0,0,1);
  IPAddress subnet(255,255,0,0);
  IPAddress primaryDNS(1,1,1,1);
  IPAddress secondaryDNS(1,0,0,1);

  if(!WiFi.config(local_IP,gateway,subnet,primaryDNS,secondaryDNS)){
    Serial.println("Failed to set static IP");
  }

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  WiFi.macAddress(mac);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  pinMode(RELAY1_pin, OUTPUT);
  pinMode(RELAY2_pin, OUTPUT);
  pinMode(RELAY3_pin, OUTPUT);
  pinMode(RELAY4_pin, OUTPUT);

  randomSeed(analogRead(randomNumberPin));
}

void TreatDigitalOutputs(bool timer_active_P[4], int time_on_P[4], int time_off_P[4], bool state_P[4], int counter){
  if(timer_active_P[0] && counter == time_on_P[0]){
    digitalWrite(RELAY1_pin, HIGH);
    state_P[0] = true;
   }
  else if(timer_active_P[0] && counter == time_off_P[0]){
    digitalWrite(RELAY1_pin, LOW);
    state_P[0] = false;
   }
  if(timer_active_P[1] && counter == time_on_P[1]){
    digitalWrite(RELAY2_pin, HIGH);
    state_P[1] = true;
   }
  else if(timer_active_P[1] && counter == time_off_P[1]){
    digitalWrite(RELAY2_pin, LOW);
    state_P[1] = false;
   }
  if(timer_active_P[2] && counter == time_on_P[2]){
    digitalWrite(RELAY3_pin, HIGH);
    state_P[2] = true;
   }
  else if(timer_active_P[2] && counter == time_off_P[2]){
    digitalWrite(RELAY3_pin, LOW);
    state_P[2] = false;
   }
  if(timer_active_P[3] && counter == time_on_P[3]){
    digitalWrite(RELAY4_pin, HIGH);
    state_P[3] = true;
   }
  else if(timer_active_P[3] && counter == time_off_P[3]){
    digitalWrite(RELAY4_pin, LOW);
    state_P[3] = false;
   }
  if(!timer_active_P[0] && state_P[0]){
    digitalWrite(RELAY1_pin, HIGH);
   }
  else if(!timer_active_P[0] && !state_P[0]){
    digitalWrite(RELAY1_pin, LOW);
   }
  if(!timer_active_P[1] && state_P[1]){
    digitalWrite(RELAY2_pin, HIGH);
   }
  else if(!timer_active_P[1] && !state_P[1]){
    digitalWrite(RELAY2_pin, LOW);
   }
  if(!timer_active_P[2] && state_P[2]){
    digitalWrite(RELAY3_pin, HIGH);
   }
  else if(!timer_active_P[2] && !state_P[2]){
    digitalWrite(RELAY3_pin, LOW);
   }
  if(!timer_active_P[3] && state_P[3]){
    digitalWrite(RELAY4_pin, HIGH);
   }
  else if(!timer_active_P[3] && !state_P[3]){
    digitalWrite(RELAY4_pin, LOW);
   }
}

// function that treats server/client interractions

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long start_time = millis(); // get start time
  
  WiFiClient client = server.available();

  if(client){
    if(client.connected()){
      Serial.println("Client connected");
    }
    while(client.connected()){
      char* command;
      while(client.available()>0){
        Serial.println(client.read());
        //strcat(command,client.read());
      }
      Serial.println(command);
    }
  }

  
    //bzero(buff, sizeof(buff));
    //read(sockfd, buff, sizeof(buff));

    //char * buff_copy = buff;
    //char * command = strtok(buff_copy, " ");
    char * commands = strtok(command, " ");
    int nb_of_commands;
    /*while(command != NULL){
      nb_of_commands++;
    }

    char *commands[nb_of_commands];
    buff_copy = buff;
    command = strtok(buff_copy, " ");
    int n = 0;
    while(command != NULL){
      commands[n] = command;
      n++;
    }
    */
    if(commands[0] == "timer-set"){

      if(commands[1] == "P1"){
        time_on_P[0] = atoi(commands[2]);
        time_off_P[0] = atoi(commands[3]);
        if(time_on_P[0] == NULL || time_off_P[0] == NULL){
          Serial.println("Invalid value sent from server");
          continue;
        }
        else{
          // to be erased later
          Serial.print("time on: ");
          Serial.println(time_on_P[0]);
          Serial.print("time off: ");
          Serial.println(time_off_P[0]);
          // ---------------------
          timer_active_P[0] = true;
        }

      }
      else if(commands[1] == "P2"){
        time_on_P[1] = atoi(commands[2]);
        time_off_P[1] = atoi(commands[3]);
        if(time_on_P[1] == NULL || time_off_P[1] == NULL){
          Serial.println("Invalid value sent from server");
          continue;
        }
        else{
          // to be erased later
          Serial.print("time on: ");
          Serial.println(time_on_P[1]);
          Serial.print("time off: ");
          Serial.println(time_off_P[1]);
          // -------------------------
          timer_active_P[1] = true;
        }
      }
      else if(commands[1] == "P3"){
        time_on_P[2] = atoi(commands[2]);
        time_off_P[2] = atoi(commands[3]);
        if(time_on_P[2] == NULL || time_off_P[2] == NULL){
          Serial.println("Invalid value sent from server");
          continue;
        }
        else{
          // to be erased later
          Serial.print("time on: ");
          Serial.println(time_on_P[2]);
          Serial.print("time off: ");
          Serial.println(time_off_P[2]);
          // -------------------------
          timer_active_P[2] = true;
        }
      }
      else if(commands[1] == "P4"){
        time_on_P[3] = atoi(commands[2]);
        time_off_P[3] = atoi(commands[3]);
        if(time_on_P[3] == NULL || time_off_P[3] == NULL){
          Serial.println("Invalid value sent from server");
          continue;
        }
        else{
          // to be erased later
          Serial.print("time on: ");
          Serial.println(time_on_P[3]);
          Serial.print("time off: ");
          Serial.println(time_off_P[3]);
          // -------------------------
          timer_active_P[3] = true;
        }
      }
      else{
        Serial.print("Wrong command sent by server: ");
        Serial.println(commands[1]);
        continue;
      }
    }
   // disable timer on specific outlet
   else if(commands[0] == "timer-off"){
    if(commands[1] == "P1"){
      timer_active_P[0] = false;
    }
    else if(commands[1] == "P2"){
      timer_active_P[1] = false;
    }
    else if(commands[1] == "P3"){
      timer_active_P[2] = false;
    }
    else if(commands[1] == "P4"){
      timer_active_P[3] = false;
    }
   }

   else{
    Serial.print("wrong command sent by server: ");
    Serial.println(commands[0]);
    continue;
   }
   // activates or deactivates relay depending on settings:
   TreatDigitalOutputs(timer_active_P, time_on_P, time_off_P, state_P, counter);

   counter++;
   if(counter >= 86400){ //nb of seconds in a day
     counter = 0;
   }

   unsigned long Elapsed_time = start_time - millis();
   Serial.print("Elapsed time: ");
   Serial.print(Elapsed_time);
   if(Elapsed_time < 1000){
    delay(1000 - Elapsed_time); // loop every seconds
   }
  }

char * Decrypt(){

}
