#define BLYNK_TEMPLATE_ID "TMPL3wzxF2CLc"
#define BLYNK_TEMPLATE_NAME "IOT BASED MAILBOXREAL"
#define BLYNK_AUTH_TOKEN "x_dWp_EgD_hKz9QfP8Udiq95aQmS1AO3"
#define RXp2 16
#define TXp2 17
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SSID";
char pass[] = "PASSWORD";
bool notified = false;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  if (Serial2.available() > 0) {
    String message = Serial2.readStringUntil('\n');
    message.trim();

    if (message == "IR DETECTED" && !notified) {
      Blynk.logEvent("tamper_detection", "Someone is attempting to access your mailbox");
      Serial2.println(message);
      notified=true;
    }
    else if (message == "IR NOT DETECTED" && notified) {
      notified=false;
    }
    else if (message == "NEW PACKAGE") {
      Blynk.logEvent("package_delivery", "New Package has arrived");
      Serial2.println(message);
    }
    else if (message == "NEW LETTER") {
      Blynk.logEvent("letter_delivery", "New Letter has arrived");
      Serial2.println(message);
    }
  }
}
