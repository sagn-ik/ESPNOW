#include <ESP8266WiFi.h>
#include <espnow.h>

#define Switch D4

uint8_t broadcastAddress[] = {};

typedef struct struct_message {
    int b;
    bool e;
} struct_message;


struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) 
{
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {

  Serial.begin(115200);
 pinMode(Switch,INPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    myData.b=0;
    if(digitalRead(Switch)==LOW)
    myData.b=1;
    myData.e = false;

    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  }
}
