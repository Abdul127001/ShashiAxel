#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

int Led_OnBoard = 2;                  // Initialize the Led_OnBoard 

//----------I assume you have successfully accessed the sensors. And below is the variable. I made it an arbitrary value.
int MQ7     = 100;
int MQ4     = 200;
int MQ131   = 300;
//----------

const char* ssid = "your_wifi_name";                  // Your wifi Name       
const char* password = "your_wifi_password";          // Your wifi Password

const char *host = "192.168.1.1"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);       // Initialize the Led_OnBoard pin as an output
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
  }

  digitalWrite(Led_OnBoard, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;    //Declare object of class HTTPClient

  //-------------------------------------------to send data to the database
  String MQ7Post, MQ4Post, MQ131Post, postData;
  MQ7Post = String(MQ7);   //String to interger conversion
  MQ4Post = String(MQ4);   //String to interger conversion
  MQ131Post = String(MQ131);   //String to interger conversion
  
  postData = "mq7val=" + MQ7Post + "&mq4val=" + MQ4Post + "&mq131val=" + MQ131Post;
  
  http.begin("http://192.168.1.1/nodemcu_post_database/InsertDB.php");               //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");                  //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  //-------------------------------------------
  
  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println("MQ7= " + MQ7Post + " MQ4= " + MQ4Post + " MQ131= " + MQ131Post);
  
  http.end();  //Close connection

  delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
}
