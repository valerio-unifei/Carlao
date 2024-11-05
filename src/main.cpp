#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-Carlao";
const char* password = "valeriomoraes";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<html><body><h1>ESP do Carlao</h1><p>Teste do ESP32 na aula de ECOP11A</p></body></html>");
  Serial.println("Pagina Enviada ao Cliente");
}

void handleControl(){
  if (server.hasArg("action")) {
    String action = server.arg("action");
    if (action == "acionar") {
      Serial.println("Botão Acionar pressionado");
      digitalWrite(26, !digitalRead(26));
    }
  }
  server.send(200, "text/html", "<html><body><h1>Controle</h1><form action=\"/control\" method=\"POST\"><button type=\"submit\" name=\"action\" value=\"acionar\">Acionar</button></form></body></html>");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password,10);

  pinMode(26, OUTPUT);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/control", handleControl);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}