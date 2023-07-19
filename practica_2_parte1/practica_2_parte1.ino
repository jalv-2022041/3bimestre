/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Electronica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de electronica digital y reparación de computadoras I
 * Nombre: josue david
 * Carnet: 2022041
 * Proyecto: 2
*/
//Directivas de preprocesador
#define porcentaje A6
#define led 3

//Variables
int intensidad;
int posicion;
  

void setup() {
  Serial.begin(9600);
 pinMode(led, OUTPUT);
 pinMode(porcentaje, INPUT);
}

void loop() {
  intensidad = analogRead(porcentaje);
  posicion = map(intensidad, 0, 1023, 0, 225);
  analogWrite(led, posicion);
}
