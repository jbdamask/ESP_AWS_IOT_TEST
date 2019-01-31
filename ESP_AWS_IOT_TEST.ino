// This include is for the AWS IOT library that we installed
#include <AWS_IOT.h>
// This include is for Wifi functionality
#include <WiFi.h>

// Declare an instance of the AWS IOT library
AWS_IOT hornbill;

// Wifi credentials
char WIFI_SSID[]="...";
char WIFI_PASSWORD[]="...";

// Thing details
char HOST_ADDRESS[]="...";
char CLIENT_ID[]= "...";
char TOPIC_NAME[]= "...";

// Connection status
int status = WL_IDLE_STATUS;
// Payload array to store thing shadow JSON document
char payload[512];
// Counter for iteration
int counter = 0;

void setup(){
    WiFi.disconnect(true);
    Serial.begin(115200);
    // initialise AWS connection
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Wifi network: ");
        Serial.println(WIFI_SSID);
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(5000);
    }
    Serial.println("Connected to Wifi!");
    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0) {
        Serial.println("Connected to AWS, bru");
        delay(1000);
    } else {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }    
}

void loop()
{   
  counter++;
  sprintf(payload,"{\"state\":{\"reported\":{\"counter\":\"%d\"}}}",counter);
  Serial.println(payload);
  if(hornbill.publish(TOPIC_NAME,payload) == 0) {
    Serial.println("Message published successfully");
  }
  else {
    Serial.println("Message was not published");
  }
  delay(5000);  
}