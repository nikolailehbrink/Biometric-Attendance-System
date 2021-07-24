#include <Adafruit_Fingerprint.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//EREIGNISSE
const byte E_INITIAL = 0;
const byte E_FINGER_ON_SCANNER = 1;
const byte E_ADMIN_INVALID = 2;
const byte E_ADMIN_VALID = 3;

//ZUSTÄNDE
const byte Z_WAIT_FOR_ADMIN_FINGER = 0;
const byte Z_CHECK_ADMIN_FINGER = 1;
const byte Z_ADMIN_CHECK_FAILED = 2;
const byte Z_ADMIN_CHECK_SUCCEEDED = 3;

byte b_ereignis = E_INITIAL;
byte b_zustand = Z_WAIT_FOR_ADMIN_FINGER;

uint8_t adminFingerID = 0;
bool adminFingerprint = false;
uint8_t id;
bool newFingerStored = false;
bool mainloopOutput = true;

//globaler Status, 0 für mainloop, dann nach reihenfolge
int globalState = 0;
bool abgebrochen = false;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 6000;

//password relevant
const byte PINLENGTH = 4;
char pinCode[PINLENGTH + 1] = {'1', '2', '3', '4'};
char keyBuffer[PINLENGTH + 1] = {'-', '-', '-', '-'};
byte pinCodeWrongCounter = 0;
