#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Servo.h>
Servo myservo;

int on, off;
char* status;

char* ssid = "Galaxy F418FB2";
char* pass = "jaygopal";

WiFiClient client;

char ip[] = "184.106.153.149";   // ip address of thingspeak-this will remain same for all
long id = 2322342;// this will change
char* api = "ST9GZCVSXFLGWT0C"; //this will change

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi Connected");
  ThingSpeak.begin(client);
  pinMode (D7, INPUT);
  myservo.attach(D8);
  myservo.write(180);
  pinMode(D6, OUTPUT);
}

void loop() {

  if (client.connect(ip, 80)) {
    long state = digitalRead(D7);
    if (state == LOW) {
      Serial.println("Object detected! ");
      Serial.println(!state);
      myservo.write(0);
      digitalWrite (D6, HIGH);
     
      delay(2000);
//      myservo.write(180);
       on = !state;
       status="Open";
      ThingSpeak.setField(1, on);
      ThingSpeak.setField(2, status);
      ThingSpeak.writeFields(id, api);
    } else {
      Serial.println("Object absent!");
      myservo.write(180);
      digitalWrite (D6, LOW);
       off= !state;
       status="Close";
      ThingSpeak.setField(1, off);
      ThingSpeak.setField(2, status);
      ThingSpeak.writeFields(id, api);
    }
   
  }
  client.stop();

}
