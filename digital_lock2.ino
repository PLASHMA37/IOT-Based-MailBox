#include <Keypad.h>
#include <Servo.h>

Servo s1;
const byte Rows = 4;
const byte  Col = 4;
char keys[Rows][Col] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte RowPins[Rows] = {9, 8, 7, 6};
byte ColPins[Col] = {5, 4, 3, 2};
Keypad customKeypad = Keypad(makeKeymap(keys), RowPins, ColPins, Rows, Col);

char inputdisp[5];
byte inputIndex = 0;
char password[5] = "1234";
bool settingNewPassword = false;
bool verifyOldPassword = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Keypad Test Starting...");
  s1.attach(12);
  s1.write(0);
  Serial.println("Enter Password:");
}

void loop() {
  char customkey = customKeypad.getKey();

  if (customkey) {
    if (customkey == '*') {
      Serial.println("Enter current password to set a new one:");
      verifyOldPassword = true;
      inputIndex = 0;
      clearInput();
    } else if (customkey == 'A') {
      Serial.println("Closing the servo...");
      s1.write(0);
    } else if (inputIndex < 4 && isDigit(customkey)) {
      inputdisp[inputIndex] = customkey;
      Serial.print("Entered: ");
      Serial.println(inputdisp);
      inputIndex++;
    }

    if (inputIndex == 4) {
      inputdisp[4] = '\0';

      if (verifyOldPassword) {
        if (strcmp(inputdisp, password) == 0) {
          Serial.println("Correct! Enter new 4-digit password:");
          settingNewPassword = true;
        } else {
          Serial.println("Incorrect current password! Try again.");
          Serial.println("Enter Password:");
        }
        verifyOldPassword = false;
      } else if (settingNewPassword) {
        strcpy(password, inputdisp);
        Serial.println("New password set successfully!");
        Serial.println("Enter Password:");
        settingNewPassword = false;
      } else {
        if (strcmp(inputdisp, password) == 0) {
          Serial.println("Password correct! Moving servo...");
          servomove();
        } else {
          Serial.println("Wrong password! Try again.");
        }
        Serial.println("Enter Password:");
      }

      inputIndex = 0;
      clearInput(); 
    }
  }
}

void servomove() {
  s1.write(90);
}

void clearInput() {
  for (int i = 0; i < 5; i++) {
    inputdisp[i] = '\0'; 
  }
}


