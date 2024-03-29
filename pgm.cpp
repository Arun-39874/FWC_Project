#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include"libr_pgm.h"

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
  <h2>TO FIND THE MID POINTS OF THE SIDES OF THE TRIANGLE</h2> 
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
    double **A,**B,**C,**D,**E,**F;
    int m=2,n=1;
    A=loadser("A.dat",2,1);
    B=loadser("B.dat",2,1);
    C=loadser("C.dat",2,1);
    D=midpoint(B,C,m,n);
    E=midpoint(C,A,m,n);
    F=midpoint(A,B,m,n);
    H=line_intersect(m3,B,m1,C,m,n); 
    request->send(200, "text/html", "The coordinates to the mid points of the sides of the triangle ABC are: "+ "["String(D[0][0],2)+String(D[1][0],2) + "]"<br>"["String(E[0][0],2)+String(E[1][0],2) + "]"<br>"["String(F[0][0],2)+String(F[1][0],2) + "]"<br><a href=\"/\">Return to Home Page</a>");

  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
