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
#include <Ticker.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
//Directivas de preprocesador
#define btn 3
//Variables
volatile static bool estado;
float temperatura;
//Funciones de ISR
void ISR_temp(void);
void ISR_deteccion_btn(void);
//Constructor
Ticker isr_conseguir_temperatura(ISR_temp, 3000);
Ticker isr_valor_boton(ISR_deteccion_btn, 6000);
OneWire ourWire(5);
DallasTemperature sensor(&ourWire);

void setup() {
Serial.begin(9600);
isr_conseguir_temperatura.start();
isr_valor_boton.start();
sensor.begin(); 
}
void loop() {
  isr_conseguir_temperatura.update();
  isr_valor_boton.update();
}
void medicion(){
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  Serial.print("La temperatura es: ");
  Serial.print(temp);
  Serial.println(" C");
  }
void ISR_temp(){
   medicion(); 
}
void ISR_deteccion_btn(){
  bool estado_btn = digitalRead(btn);
  if(estado_btn == 1){
  Serial.println(" el boton activo");
}
if(estado_btn == 0){
  Serial.println("el boton inactivo");
}}
