#include <WiFi.h>

// Reemplace con sus credenciales de red
const char* ssid = "Realme";
const char* password = "seb56581";

// Establezca el número de puerto del servidor web en 80
WiFiServer server(80);

// Variable para almacenar la solicitud HTTP
String header;

// Variables auxiliares para almacenar el estado de salida actual
String output2State = "off";
String output4State = "off";
String output18State = "off";
String output19State = "off";

// Asignar variables de salida a pines GPIO
const int delante = 18;
const int detras = 19;
const int izquierda = 5;
const int derecha = 17;

int OUTPUT4 = 16;
int OUTPUT3 = 5;
int OUTPUT2 = 4;
int OUTPUT1 = 0;

// Hora actual
unsigned long currentTime = millis();
// Tiempo anterior
unsigned long previousTime = 0; 
// Definir el tiempo de espera en milisegundos (ejemplo: 2000ms a 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Inicializar las variables de salida como salidas
  pinMode(delante, OUTPUT);
  pinMode(detras, OUTPUT);
  pinMode(izquierda, OUTPUT);
  pinMode(derecha, OUTPUT);
  // Establezca las salidas en BAJO
  digitalWrite(delante, LOW);
  digitalWrite(detras, LOW);
  digitalWrite(izquierda, LOW);
  digitalWrite(derecha, LOW);
  pinMode(OUTPUT4, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT1, OUTPUT);

    // Conéctese a la red Wi-Fi con SSID y contraseña
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   // Imprima la dirección IP local e inicie el servidor web
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();

  if(client) // Si hay un cliente
  {
    Serial.println("Nuevo Cliente");
    while(!client.available() && client.connected())
    {
      delay(1);
    }

    String linea1 = client.readStringUntil('r'); // Se lee lo que envie el cliente
    Serial.print("Linea: ");
    Serial.print(linea1);

    if(linea1.indexOf("ADELANTE") > 0)
    {
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 1);
      digitalWrite(OUTPUT3, 1);
      digitalWrite(OUTPUT4, 0);  
    }
    if(linea1.indexOf("ATRAS") > 0)
    {
      digitalWrite(OUTPUT1, 1);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 1);  
    }
    if(linea1.indexOf("DERECHA") > 0)
    {
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 1);
      digitalWrite(OUTPUT4, 0);  
    }
    if(linea1.indexOf("IZQUIERDA") > 0)
    {
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 1);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 0);  
    }
    if(linea1.indexOf("PARAR") > 0)
    {
      digitalWrite(OUTPUT1, 0);
      digitalWrite(OUTPUT2, 0);
      digitalWrite(OUTPUT3, 0);
      digitalWrite(OUTPUT4, 0);  
    }

    client.flush();
    Serial.println("Enviando respuesta...");
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><tittle>ROBOT MOVIL</tittle>");
    client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    client.println("<style>button{background-color:#f44336;border:none;color:white;padding:15px 32px;text-align:center;text-decoration:none;display:inline-block;font-size: 24px; transition-duration: 0.4s;}button</style>");
    client.println("</heat>");
    client.println("<body>");
    client.println("<div style='text-align:center;'>");
    client.println("<h1 align='center'>ROBOT MOVIL</h1>");
    client.println("<br />");
    client.println("<button onClick=location.href='./?ADELATE'>ADELANTE</button><br>");
    client.println("<button onClick=location.href='./?ATRAS'>ATRAS</button><br>");
    client.println("<button onClick=location.href='./?DERECHA'>DERECHA</button><br>");
    client.println("<button onClick=location.href='./?IZQUIERDA'>IZQUIERDA</button><br>");
    client.println("<button onClick=location.href='./?PARAR'>PARAR</button>");
    client.println("<br />");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
    Serial.println("RESPUESTA ENVIADA");
    Serial.println();    
  }
}
