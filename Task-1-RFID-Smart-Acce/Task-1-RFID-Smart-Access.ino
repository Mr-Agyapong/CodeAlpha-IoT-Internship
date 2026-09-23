#include <Servo.h>

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Setup RFID
#define SS_PIN 10
#define RST_PIN 7
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Setting up the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Servo
Servo doorServo;
#define SERVO_PIN 6

//Setting up Outputs
#define BUZZER 4
#define LED_GREEN 3 //Access Granted
#define LED_RED 2   //Access Denied


//Putting my card here. With ID 27 10 D5 31
byte masterCard[4] = {0x27, 0x10, 0xD5, 0X31};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);  //Door locked


  pinMode(BUZZER, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);


  //Startingg with LEDs off
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Scan Your Card ");
  lcd.setCursor(0,1);
  lcd.print("----------------");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Check for new Card
  if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;



  //Show UID on the LCD + Serial
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Card UID:");
  lcd.setCursor(0,1);
  for(byte i = 0; i< mfrc522.uid.size;i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    lcd.print(mfrc522.uid.uidByte[i] < 0x10? " 0" : " ");
    lcd.print(mfrc522.uid.uidByte[i], HEX);
  }

  delay(800);



  //Checking if it is the master card
  if(compareUID(mfrc522.uid.uidByte, masterCard)){
    //Access Granted 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ACCESS GRANTED");
    lcd.setCursor(0, 1);
    lcd.print(" Welcome Emma");

    digitalWrite(LED_GREEN, HIGH);   //Turn on the Green LED
    digitalWrite(LED_RED, LOW);      //Turn off the Red LED
    beep(1, 1000);  //2 shorts beeps
    delay(1500);
    digitalWrite(LED_GREEN, LOW);   //Turn of after .5s

    //unlock door
    doorServo.write(180);
    delay(5000);

    //lock door again
    doorServo.write(0);

  }  else{
    //Access Denied
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ACCESS DENIED");
    lcd.setCursor(0,1);
    lcd.print(" Wrong Card!");

    digitalWrite(LED_RED, HIGH);  //Turn on the red LED
    digitalWrite(LED_GREEN, LOW);   //Turn off the Green LED
    beep(2, 1000);                    //One long beep
    delay(1500);
    digitalWrite(LED_RED, LOW);   //Turn off after 1.5s
  }

  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan Your Card");
  mfrc522.PICC_HaltA();
}


//Function to compare 2 UIDs
boolean compareUID(byte card[], byte master[]){
  for(byte i = 0; i < 4; i++){
    if(card[i]!= master[i])  return false;

  }
  return true;
}

//Function to beep buzzer
void beep(int times, int duration){
  for (int i =0; i<times; i++){
    digitalWrite(BUZZER, HIGH);
    delay(duration);
    digitalWrite(BUZZER, LOW);
    delay(duration);


  }

}

  



  



#include <Servo.h>

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Setup RFID
#define SS_PIN 10
#define RST_PIN 7
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Setting up the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Servo
Servo doorServo;
#define SERVO_PIN 6

//Setting up Outputs
#define BUZZER 4
#define LED_GREEN 3 //Access Granted
#define LED_RED 2   //Access Denied


//Putting my card here. With ID 27 10 D5 31
byte masterCard[4] = {0x27, 0x10, 0xD5, 0X31};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);  //Door locked


  pinMode(BUZZER, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);


  //Startingg with LEDs off
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Scan Your Card ");
  lcd.setCursor(0,1);
  lcd.print("----------------");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Check for new Card
  if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;



  //Show UID on the LCD + Serial
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Card UID:");
  lcd.setCursor(0,1);
  for(byte i = 0; i< mfrc522.uid.size;i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    lcd.print(mfrc522.uid.uidByte[i] < 0x10? " 0" : " ");
    lcd.print(mfrc522.uid.uidByte[i], HEX);
  }

  delay(800);



  //Checking if it is the master card
  if(compareUID(mfrc522.uid.uidByte, masterCard)){
    //Access Granted 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ACCESS GRANTED");
    lcd.setCursor(0, 1);
    lcd.print(" Welcome Emma");

    digitalWrite(LED_GREEN, HIGH);   //Turn on the Green LED
    digitalWrite(LED_RED, LOW);      //Turn off the Red LED
    beep(1, 1000);  //2 shorts beeps
    delay(1500);
    digitalWrite(LED_GREEN, LOW);   //Turn of after .5s

    //unlock door
    doorServo.write(180);
    delay(5000);

    //lock door again
    doorServo.write(0);

  }  else{
    //Access Denied
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ACCESS DENIED");
    lcd.setCursor(0,1);
    lcd.print(" Wrong Card!");

    digitalWrite(LED_RED, HIGH);  //Turn on the red LED
    digitalWrite(LED_GREEN, LOW);   //Turn off the Green LED
    beep(2, 1000);                    //One long beep
    delay(1500);
    digitalWrite(LED_RED, LOW);   //Turn off after 1.5s
  }

  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan Your Card");
  mfrc522.PICC_HaltA();
}


//Function to compare 2 UIDs
boolean compareUID(byte card[], byte master[]){
  for(byte i = 0; i < 4; i++){
    if(card[i]!= master[i])  return false;

  }
  return true;
}

//Function to beep buzzer
void beep(int times, int duration){
  for (int i =0; i<times; i++){
    digitalWrite(BUZZER, HIGH);
    delay(duration);
    digitalWrite(BUZZER, LOW);
    delay(duration);


  }

}

  



  



