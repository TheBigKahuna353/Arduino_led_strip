/* F5 TEST FOR ESP2PY
 * Written by Junicchi
 * https://github.com/KebabLord/esp_to_python
 * It simply increases and returns a variable everytime a python req came */

#include "ESP_MICRO.h" //Include the micro library 
#include "ESP8266WiFi.h" 
#include "LEDS.h"
#include "webpage.h"


String func = "func1";


void setup(){
  Serial.begin(9600); // Starting serial port for seeing details
//  printNetworks();
  start("ORBI77 2.4 GHz","Clancastle123");  // EnAIt will connect to your wifi with given details
  Serial.println("it Worked???");
  delay(200);
  on_start();
}


void loop(){
  waitUntilNewReq();  //Waits until a new request from python come
  /* increases index when a new request came*/
  if (rule == "/") {
    printWebPage(LEDS_on, cur_func);
  }
  else if (rule == "/test") {
    returnThisStr("You are gay");
  }
  else if (rule == "/on") {
    LEDS_on = "on";
    sendToPage("/");
  }
  else if (rule == "/off") {
    LEDS_on = "off";
    black();
    sendToPage("/");
  }
  else if (rule.indexOf("?") != -1) {
    Serial.println("got rbg");
    int pos1 = rule.indexOf('r');
    int pos2 = rule.indexOf('g');
    int pos3 = rule.indexOf('b');
    int pos4 = rule.indexOf('&');
    String red = rule.substring(pos1+1, pos2);
    String green = rule.substring(pos2+1, pos3);
    String blue = rule.substring(pos3+1, pos4);
    solid = [red.toInt(), green.toInt(), blue.toInt()];
    cur_func = "solid";
    func = "solid";
    sendToPage("/");
  }
  else if (rule == "/start") {
    num = 3;
    returnThisStr("HTTP/1.1 200 OK");
  } else if (rule.indexOf("func") != -1) {
    rule.remove(0,1);
    func = rule;
    cur_func = func;
    sendToPage("/");
  }
  else if (rule == "/on_clap") {
    func = "on_clap";
    black();
    sendToPage("/");
  }
  else if (rule.indexOf("brightness") != -1)
  {
    int pos = rule.indexOf("%");
    setBright(rule.substring(pos+1, pos+3).toInt());
  }
  else {
    Serial.println(rule);
  }
  Serial.println(func);
}

void update_leds() {
  if (LEDS_on == "off") {
    return;
  }
  if (func == "func1") {
    func1();
  }
  else if (func == "func2") {
    func2();
  }
  else if (func == "func3") {
    func3();
  }
  else if (func == "func4") {
    func4();
  }
  else if (func == "func5") {
    func5();
  }
  else if (func == "on_clap") {
    on_clap();
  }
  else if (func == "solid") {
    fill(solid[0], solid[1], solid[2]);
  }
}

void waitUntilNewReq(){
  do {
    CheckNewReq();
    update_leds();
    } while (!isReqCame);
  isReqCame = false;
}
