#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

Servo s1;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte Rows = 4;
const byte Col = 4;
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
//default password will be 1234
char password[5] = "1234"; 
bool settingNewPassword = false;
bool verifyOldPassword = false;

void displayMessage(const char* message);
void processKey(char customkey);
void verifyPassword();
void setNewPassword();
void moveServo();
void closeServo();

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  
  // Initial message
  displayMessage("Keypad Test Start");
  s1.attach(12);
  s1.write(0);

  delay(2000);
  displayMessage("Enter Password:");
}

void loop() {
  char customkey = customKeypad.getKey();
  if (customkey) {
    processKey(customkey);
  }
}

void processKey(char customkey) {
  if (customkey == '*') {
    displayMessage("Enter current pwd:");
    verifyOldPassword = true;
    inputIndex = 0;
  } else if (customkey == 'A') {
    closeServo();
  } else if (inputIndex < 4 && isDigit(customkey)) {
    inputdisp[inputIndex] = customkey;
    lcd.setCursor(inputIndex, 1);
    lcd.print('*');
    inputIndex++;
  }

  if (inputIndex == 4) { 
    inputdisp[4] = '\0';

    if (verifyOldPassword) {
      verifyPassword();
    } else if (settingNewPassword) {
      setNewPassword();
    } else {
      moveServo();
    }
    inputIndex = 0;
  }
}

void verifyPassword() {
  if (strcmp(inputdisp, password) == 0) {
    displayMessage("Correct! New pwd:");
    settingNewPassword = true;
  } else {
    displayMessage("Wrong Password!");
    delay(2000);
    displayMessage("Enter Password:");
  }
  verifyOldPassword = false;
}

void setNewPassword() {
  strcpy(password, inputdisp);
  displayMessage("New pwd set!");
  delay(2000);
  displayMessage("Enter Password:");
  settingNewPassword = false;
}

void moveServo() {
  if (strcmp(inputdisp, password) == 0) {
    displayMessage("Pwd correct!");
    s1.write(90);
  } else {
    displayMessage("Wrong Password!");
    delay(2000);
    displayMessage("Enter Password:");
  }
}


void closeServo() {
  displayMessage("Closing Servo...");
  s1.write(0); 
  delay(2000); 
  displayMessage("Enter Password:");
}

void displayMessage(const char* message) {
  lcd.clear();
  lcd.print(message);
  Serial.println(message);
}

