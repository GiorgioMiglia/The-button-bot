/*********************************
 * TOB THE BUTTON BOT
 * 
 * telegram bot which sends emergency meeting pic (or any other pic)
 * when you press a physical button 
 * 
 * connection:
 * 
 * pin -- button -- GND
 * 
 *  * *****************************/

// ----------------------------
// Standard ESP8266 Libraries
// ----------------------------

#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "XXXXXXX";     // your network SSID (name)
char password[] = "XXXXXXXX"; // your network key

// Initialize Telegram BOT
#define BOTtoken "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" // your Bot Token (Get from @Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

String photo_url = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; //the url of the pic
#define buttonPin D1 //change D1 with your pin (must have pullup or it will need a 10k ohm resistor)
int old_status = 1;
String chat_id = "XXXXXXX"; // your or your group chat id (use @myidbot)

void setup() {
  client.setInsecure();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // attempt to connect to Wifi network:
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, old_status);
  if (digitalRead(buttonPin) == 0 && digitalRead(buttonPin) != old_status) { //prevent spamming (debouncing the button)
    old_status = 0;
    digitalWrite(LED_BUILTIN, old_status); // used for feedback
    bot.sendPhoto(chat_id, photo_url, ""); // you can write what you want as pic description between ""
  } else if (digitalRead(buttonPin) == 1){
    old_status = 1;
  }
  delay(10);
}
