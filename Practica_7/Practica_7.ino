#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

#define direccion_lcd 0x27
#define filas 2
#define columnas 16

#define RST_PIN  9   
#define SS_PIN  10  
#define pinvoltaje A0   
#define corriente A7 
#define configRTC 6 

float Sensibilidad = 0.185;
byte Year ;
byte Month ;
byte Date ;
byte DoW ;
byte Hour ;
byte Minute ;
byte Second ;
bool Century  = false;
bool h12 ;
bool PM ;

byte ActualUID[4]; 
byte Usuario2[4]= {0x79, 0x02, 0x9B, 0xD5} ; 
byte Usuario1[4]= {0xF9, 0x90, 0xF8, 0xB3} ;

MFRC522 mfrc522(SS_PIN, RST_PIN); 
DS3231 Clock;
LiquidCrystal_I2C JOSUE_LCD(direccion_lcd, columnas, filas);
void setup() {
  Wire.begin();
  Serial.begin(9600); 
  SPI.begin();      
  mfrc522.PCD_Init(); 
  Serial.println("EEGSA - KINAL");
  pinMode(pinvoltaje, INPUT);
  pinMode(corriente, INPUT);
  pinMode(configRTC, INPUT);
  JOSUE_LCD.init();
  JOSUE_LCD.backlight();
  if(digitalRead(configRTC) == HIGH){
    setDate(); }
    JOSUE_LCD.setCursor(0,0);
    JOSUE_LCD.print(" EEGSA - KINAL  ");
    JOSUE_LCD.setCursor(0,1);
    JOSUE_LCD.print("                ");}
void loop() {
  if ( mfrc522.PICC_IsNewCardPresent())  {  
 if ( mfrc522.PICC_ReadCardSerial())   {
 for (byte i = 0; i < mfrc522.uid.size; i++) {
      ActualUID[i]=mfrc522.uid.uidByte[i];           } 
    Serial.print("     ");                  
 if(compareArray(ActualUID,Usuario1)){
   Serial.println("Verificado: ALV002");
   Serial.print("Fecha de acceso: ");
   Serial.print(Clock.getDate(), DEC);
   Serial.print("/");
   Serial.print(Clock.getMonth(Century), DEC);
   Serial.print(" ");
   Serial.print(Clock.getHour(h12, PM), DEC);
   Serial.print(":");
   Serial.print(Clock.getMinute(), DEC);
   Serial.print(":");
   Serial.println(Clock.getSecond(), DEC);
        calculos();}
 else if(compareArray(ActualUID,Usuario2)){
   Serial.println("Verificado: PADILLA");
   Serial.print("Fecha de acceso: ");
   Serial.print(Clock.getDate(), DEC);
   Serial.print("/");
   Serial.print(Clock.getMonth(Century), DEC);
   Serial.print(" ");   
   Serial.print(Clock.getHour(h12, PM), DEC);
   Serial.print(":");
   Serial.print(Clock.getMinute(), DEC);
   Serial.print(":");
   Serial.println(Clock.getSecond(), DEC);
     calculos();}
 else{
    Serial.println("Acceso fallido");
   JOSUE_LCD.setCursor(0,1);
   JOSUE_LCD.print("NO REGISTRADO");
   Serial.print("Fecha de intento de acceso: ");
   Serial.print(Clock.getDate(), DEC);
   Serial.print("/");
   Serial.print(Clock.getMonth(Century), DEC);
   Serial.print(" ");
   Serial.print(Clock.getHour(h12, PM), DEC); 
   Serial.print(":");
   Serial.print(Clock.getMinute(), DEC);
   Serial.print(":");
   Serial.println(Clock.getSecond(), DEC);
   delay(2000);
  }
    mfrc522.PICC_HaltA();          
   } }
else{
  JOSUE_LCD.setCursor(0,0);
  JOSUE_LCD.print(" EEGSA - KINAL  ");
  JOSUE_LCD.setCursor(0,1);
  JOSUE_LCD.print("MEDIDOR ENERGIA ");   
}}
 boolean compareArray(byte array1[],byte array2[];
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
  void setDate( ) {
  if (digitalRead(configRTC) == HIGH) {
    GetDateStuff(Year, Month, Date, DoW, Hour, Minute, Second);
    Clock.setClockMode(false);  
    Clock.setSecond(Second);
    Clock.setMinute(Minute);
    Clock.setHour(Hour);
    Clock.setDate(Date);
    Clock.setMonth(Month);
    Clock.setYear(Year);
    Clock.setDoW(DoW); }}
void GetDateStuff(byte& Year, byte& Month, byte& Day, byte& DoW, byte& Hour, byte& Minute, byte& Second) { /* function GetDateStuff */
  boolean GotString = false;
  char InChar;
  byte Temp1, Temp2;
  char InString[20];
  byte j = 0;
  while (!GotString) {
    if (Serial.available()) {
      InChar = Serial.read();
      InString[j] = InChar;
      j += 1;
      if (InChar == 'x') {
        GotString = true;} } }
  Serial.println(InString);
  Temp1 = (byte)InString[0] - 48;
  Temp2 = (byte)InString[1] - 48;
  Year = Temp1 * 10 + Temp2; // año
  Temp1 = (byte)InString[2] - 48;
  Temp2 = (byte)InString[3] - 48;
  Month = Temp1 * 10 + Temp2;// mes
  Temp1 = (byte)InString[4] - 48;
  Temp2 = (byte)InString[5] - 48;
  Day = Temp1 * 10 + Temp2; 
  DoW = (byte)InString[6] - 48;// dia
  Temp1 = (byte)InString[7] - 48;
  Temp2 = (byte)InString[8] - 48;
  Hour = Temp1 * 10 + Temp2; // hora
  Temp1 = (byte)InString[9] - 48;
  Temp2 = (byte)InString[10] - 48;
  Minute = Temp1 * 10 + Temp2;//minutos
  Temp1 = (byte)InString[11] - 48;
  Temp2 = (byte)InString[12] - 48;
  Second = Temp1 * 10 + Temp2;// segundos 
}
void calculos(){
  JOSUE_LCD.setCursor(0,1);
  JOSUE_LCD.print("                ");
  JOSUE_LCD.setCursor(2,1);
  JOSUE_LCD.print("V: ");
  float voltaje =  (float)25*analogRead(pinvoltaje)/1023;
  JOSUE_LCD.print(voltaje);
  JOSUE_LCD.print(" V   ");//  Voltaje
  delay(2000); 
  JOSUE_LCD.setCursor(2,1);
  JOSUE_LCD.print("I: ");
  float med = analogRead(corriente)*(5.0/1023.0);
  float I = abs((2.5 - med)/Sensibilidad);
  if(abs(I) >= 1 ){
  JOSUE_LCD.print(I,3);
  JOSUE_LCD.print(" A   ");
  }
  if(abs(I) < 1 ){
  JOSUE_LCD.print(I*1000,0);
  JOSUE_LCD.print(" mA   ");//  Corriente
  }
  delay(2000);
  JOSUE_LCD.setCursor(2,1);
  float P = voltaje * I;
  JOSUE_LCD.print("P: ");
  if(abs(P) >= 1 ){
  JOSUE_LCD.print(I,3);
  JOSUE_LCD.print(" W   ");
  }
  if(abs(P) < 1 ){
  JOSUE_LCD.print(P*1000,0);
  JOSUE_LCD.print(" mW   ");//  Potencia
  }
  delay(2000);
  }
