#include <GSM.h>
#include <SPI.h>
#include <SD.h>

// =======================================================
// Out Red Led
// =======================================================

const int ledPin = 8;

// =======================================================
// Out Piezo
// =======================================================

const int piezoPin = 9;

// =======================================================
// Alarm
// =======================================================

int sensorPin = A0;
unsigned long alarmInterval = 30000;
unsigned long alarmDelay = 60000;
int sensorValue;
unsigned long lastAlarmTime = 0;
unsigned long elapsedTime = 0;

// =======================================================
// Logger
// =======================================================

String buffer;
bool sdCardAvailable = false;

// =======================================================
// Sms Sender
// =======================================================

int pinError = 5;
int pinReady = 6;
char* pin;
boolean isConnected = false;
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSM_SMS sms;

// =======================================================
// Program
// =======================================================

void setup() {
  Serial.begin(9600);

  // =======================================================
  // Alarm
  // =======================================================

  pinMode(sensorPin, INPUT);

  // =======================================================
  // Logger
  // =======================================================

  Serial.println("Initializing SD card...");

  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    sdCardAvailable = false;
  }
  else
  {
    Serial.println("SD card successfully initialized.");
    sdCardAvailable = true;
  }

  // =======================================================
  // Output
  // =======================================================

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // =======================================================
  // Start
  // =======================================================

  pinMode(pinError, OUTPUT);
  pinMode(pinReady, OUTPUT);

  connect();

  // =======================================================
  // Start
  // =======================================================

  loggerWrite("=======================================================");
  loggerWrite("Arduino started");
  loggerWrite("=======================================================");
}

void loop() {
  boolean isTriggered = isAlarmTriggered();

  if (isTriggered)
    triggerAlarm();

  delay(500);
}

void triggerAlarm()
{
  // led on
  digitalWrite(ledPin, HIGH);

  // make sound
  tone(piezoPin, 200, 500);
  delay(500);
  tone(piezoPin, 100, 500);
  delay(500);
  tone(piezoPin, 200, 500);
  delay(500);
  tone(piezoPin, 100, 500);
  delay(500);

  // send sms
  sendSMS("0723002252", "alarm acasa");

  // led off
  digitalWrite(ledPin, LOW);
}
