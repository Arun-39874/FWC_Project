#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include"lib_sides.h"

AsyncWebServer server(80);

const char* ssid = "RedmiNote10S";
const char* password = "arunkumar1";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* matrix1[2]={input_parameter00,input_parameter01};
const char* matrix2[2]={input_parameter10,input_parameter11};
const char* matrix3[2]={input_parameter20,input_parameter21};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>COLLINEARITY</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>TO FIND THE SIDES AND ANGLES OF THE TRIANGLE</h2> 
  <p>Enter the values of points A,B,C
  <form action="/get">
    Enter the values of Point A: <input type="number" name="input00"><br><input type="number" name="input01"><br>
    Enter the values of Point B: <input type="number" name="input10"><br><input type="number" name="input11"><br>
    Enter the values of Point C: <input type="number" name="input20"><br><input type="number" name="input21"><br>
    <input type="submit" value="Submit">
    

  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    double **A,**B,**C,**a,**b,**c,**angA,**angB,**angC;
    int m=2,n=1;
    A=loadser("A.dat",2,1);
    B=loadser("B.dat",2,1);
    C=loadser("C.dat",2,1);
    a = distance(B, C);
    b = distance(C, A);
    c = distance(A, B);
    m1=dir_vec(A,B,m,n);
    m2=dir_vec(B,C,m,n);
    m3=dir_vec(C,A,m,n);
    angA = acos(Matdot(m1, m3, m) / (distance(A, B) * distance(C, A))) * 180.0 / M_PI;
    angB = acos(Matdot(m1, m2, m) / (distance(A, B) * distance(B, C))) * 180.0 / M_PI;
    angC = acos(Matdot(m2, m3, m) / (distance(B, C) * distance(C, A))) * 180.0 / M_PI;

    request->send(200, "text/html", "The length of sides and the angles of the triangle ABC are: "+ "["String(a,2) + "]"<br>"["String(b,2) + "]"<br>"["String(c,2) + "]"<br>"["String(angA,2) + "]"<br>"["String(angB,2) + "]"<br>"["String(angC,2) + "]"<br><a href=\"/\">Return to Home Page</a>");

  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}