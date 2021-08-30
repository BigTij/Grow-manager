#include <WiFi.h>
#include <MySQL_Connection.h>
//#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <MySQL_Cursor.h>
#include <stdio.h>

char mysqlUser[] = "esp8266_01";
char mysqlPWD[] = "***********";
char TableName[] = "VEG_ROOM_01";
char db[] = "Lighting";

char* ssid = "**********";
char* pwd = "***********";

const int RELAY_1_pin = 0;
const int RELAY_2_pin = 2;

int time_on_r1 = 43200;
int time_off_r1 = 86400;
int time_on_r2 = 43200;
int time_off_r2 = 86400;

int time_in_sec = 0;
unsigned long startTime;
unsigned long elapsedTime;

IPAddress MySQL_server(10,0,0,14);

// Start tcp server on port 5045:
WiFiServer server(5045);
MySQL_Connection conn((Client *)&client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.disconnect(); // Prevent connecting to wifi based on 
                     // previous configuration
                                                                                                                                                                                                                                           
  
  IPAddress local_IP(10,0,0,19);
  IPAddress gateway(10,0,0,1);
  IPAddress subnet(255,255,0,0);
  IPAddress primaryDNS(1,1,1,1);
  IPAddress secondaryDNS(1,0,0,1);
  
  WiFi.config(local_IP,subnet,gateway,primaryDNS);
  
  WiFi.begin(ssid,pwd);
  Serial.println();
  
  //Wait for connection
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to "); Serial.println(ssid);
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  // Start the TCP server
  server.begin();
  
  pinMode(RELAY_1_pin,OUTPUT);
  pinMode(RELAY_2_pin,OUTPUT);
}



int * Validate_command(char *message){ // command format ex: "r1 12:00 24:00"
  
  bool valid_command = true;
  char *copy = "";
  strcpy(copy, message);
  char *ptr = strtok(copy, " ");
  
  int time_on = 0;
  int time_off = 0;
  int sql_log[4]; // [hr_on, min_on, hr_off, min_off]  
  
  int counter = 0;
  while(ptr != NULL){
    counter++;
  }
  
  char *commands[counter];
  ptr = strtok(message, " ");
  counter = 0;
  while(ptr != NULL){
    commands[counter] = ptr;
    counter++;
  }

  if(commands[0] == "r1" || commands[0] == "r2"){
    
    // validate time command format ex: "12:00" 
    if((strchr(commands[1],':') != NULL) && (strlen(commands[1]) == 5)){
      strcpy(copy, commands[1]);
      ptr = strtok(copy,":");
      counter = 0;

      // convert time in sec
      while(ptr != NULL){
        if(counter == 0 && atoi(ptr) != NULL){
          time_on += atoi(ptr) * 3600;
          sql_log[0] = atoi(ptr);
        }
        else if(counter == 1 && atoi(ptr) != NULL){
          time_on += atoi(ptr) * 60;
          sql_log[1] = atoi(ptr);
        }
        else{
          valid_command = false;
        }
        counter++;
      }
      
      if((strchr(commands[2],':') != NULL) && (strlen(commands[2]) == 5)){
        strcpy(copy, commands[2]);
        ptr = strtok(copy,":");
        counter = 0;
        while(ptr != NULL){
          if(counter == 0 && atoi(ptr) != 0){
             time_off += atoi(ptr) * 3600;
             sql_log[2] = atoi(ptr);
          }
          else if(counter == 1 && atoi(ptr) != 0){
            time_off += atoi(ptr) * 60;
            sql_log[3] = atoi(ptr);
          }
          else{
            valid_command = false;
          }
          Serial.println(ptr);
          counter++;
        }
      }
      else{
        valid_command = false;
      }
    }
    else{
      valid_command = false;
    }
  }
  else{
    valid_command = false;
  }
  if(valid_command){
    if(commands[0] == "r1"){
      time_on_r1 = time_on;
      time_off_r1 = time_off;
    }
    else if(commands[0] == "r2"){
      time_on_r2 = time_on;
      time_off_r2 = time_off;
    }
    return sql_log;
  }
  int arr[4];
  return arr;
}
void Update_relay(int relay_pin, bool flag){
  digitalWrite(relay_pin,flag);
}

void WriteTime_logs_mysql(int times_on_off[4]){
  char INSERT_DATA[80];
  char buff_hr_on[2];
  char buff_min_on[2];
  char buff_hr_off[2];
  char buff_min_off[2];
  sprintf(buff_hr_on,"%i", times_on_off[0]);
  sprintf(buff_min_on,"%i", times_on_off[1]);
  sprintf(buff_hr_off,"%i", times_on_off[2]);
  sprintf(buff_min_off,"%i", times_on_off[3]);

  strcat(INSERT_DATA, "INSERT INTO ");
  strcat(INSERT_DATA, db);
  strcat(INSERT_DATA, " . ");
  strcat(INSERT_DATA, TableName);
  strcat(INSERT_DATA, " (hr_on, min_on, hr_off, min_off) VALUES ('");
  strcat(INSERT_DATA, buff_hr_on);
  strcat(INSERT_DATA, "','");
  strcat(INSERT_DATA, buff_min_on);
  strcat(INSERT_DATA, "','");
  strcat(INSERT_DATA, buff_hr_off);
  strcat(INSERT_DATA, "','");
  strcat(INSERT_DATA, buff_min_off);
  strcat(INSERT_DATA, "');");

  Serial.print("Command: "); Serial.println(INSERT_DATA);

  if(conn.connect(MySQL_server,3306,mysqlUser,mysqlPWD)){
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute(INSERT_DATA);
    delete cur_mem;
  }
  else{
    Serial.println("Failed to send data to mysql");
  }
  conn.close();
}

void TCP_server(){
  WiFiClient client = server.available();
  if(client){
    Serial.println("Client connected");
    int counter = 0;
    char Buffer[30];
    while(client.connected()){
      if(counter < 30){
        Buffer[counter] = client.read();
      }
      else{
        Serial.println("Buffer overflow, connection closed.");
      }
      counter++;
    }
    Serial.print("Command received: ");
    Serial.println(Buffer);
    char *command = Buffer;
    //Do something with command:
    int *time_logs = Validate_command(command);
    if(!(time_logs[0] == 0 && time_logs[1] == 0 && time_logs[2] == 0 && time_logs[3])){
      WriteTime_logs_mysql(time_logs);
      Serial.print("valid command: ");
      Serial.println(command);
    }
    else{
      Serial.print("Invalid command: ");
      Serial.println(command);
    }
    client.stop();
  }
}

void loop() {
  startTime = millis();
  Serial.println(WiFi.localIP());
  // put your main code here, to run repeatedly:
  //TCP_server();
  
  if(time_in_sec == time_on_r1){
    Update_relay(RELAY_1_pin,HIGH);
  }
  else if(time_in_sec == time_off_r1){
    Update_relay(RELAY_1_pin,LOW);
  }
  if(time_in_sec == time_on_r2){
    Update_relay(RELAY_2_pin,HIGH);
  }
  else if(time_in_sec == time_off_r2){
    Update_relay(RELAY_2_pin,LOW);
  }
  
  time_in_sec++;
  if(time_in_sec == 86400){
    time_in_sec = 0;
  }
  elapsedTime = millis();
  Serial.print("ElapsedTime: ");   
  Serial.println(elapsedTime - startTime);
  delay(1000 - elapsedTime); 
}
