#include <ESP8266WiFi.h>
#include <espnow.h>

#define RELAY D4

typedef struct struct_message {
    int b;
    bool e;
} struct_message;


struct_message myData;


void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Int: ");
  Serial.println(myData.b);

  if(myData.b == 1)
  digitalWrite(RELAY,HIGH);
  else
  digitalWrite(RELAY,LOW);
}
 
void setup() {
  Serial.begin(115200);
  pinMode(RELAY,OUTPUT);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
