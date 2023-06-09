/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Electronica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de electronica digital y reparación de computadoras I
 * Nombre: Josue David Alvizurs 
 * Carnet: 2022041
 * Proyecto: Practica 1
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define direccion_lcd 0x3F
#define filas 2
#define columnas 16
#define divisor_v A0 
int medicionR();
LiquidCrystal_I2C LCD_ALV(direccion_lcd, columnas, filas); 
  void setup() {
    Serial.begin(9600);
    pinMode(divisor_v, INPUT);
     LCD_ALV.init();
  LCD_ALV.backlight();
}
void loop() {
  LCD_ALV.setCursor(0,0);
  LCD_ALV.print("  Resistencia   ");
  unsigned long int ohms = medicionR();
  LCD_ALV.setCursor(0,1);
  LCD_ALV.print(ohms);
  LCD_ALV.print(" ohms");
}
 int medicionR(){
    int lectura = 0;   //Valor de voltaje en el divisor de voltaje
    int Ve = 5;   // Vcc
    float VR2 = 0;    //Voltaje en la R2
    float R1 = 10000;     // Valor de la Resistencia de referencia
    float R2 = 0;         // Variable de la resistencia a encontrar
    float relacion = 0;
     lectura = analogRead(divisor_v);
   if(lectura) //Si detecta una resistencia
  {
    relacion = lectura * Ve;  // Opera el valor de la lectura del divisor por el voltaje de alimentacion
    VR2 = (relacion)/1024.0;  //hace la relacion en la escala raw para voltaje 
  relacion = (Ve/VR2) -1;    //en la operacion sule existir un 1 que no deveria de estar entonces se le resta 1 para poder obtener el verdadero resultado
    R2= (R1 * relacion)-20;  //para tener mayor precicion
    Serial.print("el valor es de :");
    Serial.println(R2);
    return R2;
  } else {
    Serial.println("no hay resistencia");
    return 0;
    }
  }
