/* ESP8266 TO PY: THE MICRO LIBRARY
 * Written by Junicchi
 * https://github.com/Kebablord

 * MAP
 - start(ssid,password)---> Connects to wifi with given username and password
 - waitUntilNewReq() -----> Waits until a new python request come, checks for requests regularly
 - returnThisInt(data) ---> sends your Integer data to localhost (python)
 - returnThisStr(data) ---> sends your String data to localhost (python)
 - getPath() -------------> gets the request path as string, ex: https://192.113.133/ledON -> "ledON"
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <SPI.h>

// PORT
WiFiServer server(80);
WiFiClient client;
String rule;

void start(String ssid, String pass){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(),pass.c_str());
  IPAddress ip(192, 168, 1, 46);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 0, 0);
  WiFi.config(ip, gateway, subnet);

  Serial.println("");
// Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
// Setting up mDNS responder
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
// Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");
// Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
}

void printNetworks() {
  int num = WiFi.scanNetworks();
  for (int i = 0; i < num; i++) {
    Serial.println(WiFi.SSID(i));
  }
}

bool isReqCame = false;

void setBright(int bright)
{
  FastLED.setBrightness(bright);
}

void CheckNewReq(){
  client = server.available();
  if (!client) {
    return;
  }
  Serial.println("");
  Serial.println("NEW REQUEST");
// Waiting client to connect
  while (client.connected() && !client.available()) {
    return;
  }
// Read the first line of HTTP request
  String req = client.readStringUntil('\r');
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    Serial.print("Invalid request: ");
    Serial.println(req);
    return;
  }
  req = req.substring(addr_start + 1, addr_end);
  Serial.print("Requested Path: ");
  Serial.println(req);

  rule = req;
  isReqCame = true;
  client.flush();
}
//void waitUntilNewReq(){
//  do {CheckNewReq();} while (!isReqCame);
//  isReqCame = false;
//}

void returnThisStr(String final_data){
  String s;
  //HTTP Protocol code.
//  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += final_data; //Our final raw data to return
  client.print(s);
  Serial.println("Returned to client.");
}
void returnThisInt(int final_data){
  returnThisStr(String(final_data));
}

String getPath(){
  return rule;
}

void sendToPage(String page) {
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta http-equiv='Refresh' content=\"0; url='/'\" />");
}

String LEDS_on = "on";
String cur_func = "func1";
