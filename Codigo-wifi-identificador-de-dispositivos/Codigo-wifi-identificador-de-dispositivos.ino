#include <WiFi.h>
#include <esp_wifi.h>
#include <tcpip_adapter.h>

const char* ssid = "KINAL-NO-2022041";
const char* password = "A2022041";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Configurar el ESP32 como un punto de acceso con contraseña
  WiFi.softAP(ssid, password);

  Serial.println("Punto de acceso iniciado");
  Serial.print("Nombre de red (SSID): ");
  Serial.println(ssid);
  Serial.print("Contraseña: ");
  Serial.println(password);

  // Mostrar la cantidad de clientes conectados y sus direcciones IP

}

void loop() {
    // Obtener la lista de direcciones IP de los clientes conectados
  tcpip_adapter_sta_list_t list;

  // Mostrar la cantidad de clientes conectados
Serial.print("Clientes conectados: ");
  Serial.println(WiFi.softAPgetStationNum());
  // Mostrar las direcciones IP de los clientes conectados
  Serial.println("Direcciones IP de los clientes:");
  delay(5000);
  for (int i = 0; i < WiFi.softAPgetStationNum(); i++) {
    tcpip_adapter_sta_info_t station = list.sta[i];
    Serial.print("Cliente ");
    Serial.print(i + 1);
    Serial.print(" IP: ");
    Serial.println(IPAddress(station.ip.addr));
    delay(5000);
}
}