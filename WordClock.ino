#include "config.h"

#include <FastLED.h>
// https://github.com/arduino-libraries/NTPClient
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define NUM_LEDS 126
#define DATA_PIN 4
#define BRIGHTNESS 64

#define DEBUG   true

int debugMinutes;
int debugHours;

CRGB leds[NUM_LEDS];
bool ledsactive[NUM_LEDS];
CRGB color[NUM_LEDS];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID_NAME, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  timeClient.begin();
  delay(5000);
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  if (DEBUG) {
    debugMinutes = 0;
    debugHours = 0;
    initTest();
  }

  DisplayTime();
}

void loop() {
  timeClient.update();

  DisplayTime();
  
  if (DEBUG) {
    delay(1000);
  } else {
    delay(59000);
  }
}

void DisplayTime() {
  clearAll();
  setColorAllWhite();
  setLedAfterTime();
  showLEDs();
}

int getCurrentMinutes() {
  if (DEBUG) {
    debugMinutes++;
    if (debugMinutes >= 60) {
      debugHours++;
    }
    debugMinutes = debugMinutes % 60;
    return debugMinutes;
  } else {
    return timeClient.getMinutes();
  }
}

int getCurrentHour() {
  if (DEBUG) {
    //debugHours++;
    return debugHours % 24;
  } else {
    return timeClient.getHours();
  }
}

void setLedAfterTime() {
  int minutes = getCurrentMinutes();
  int hour = getCurrentHour();

  if (DEBUG) {
    Serial.print(hour);
    Serial.print(":");
    Serial.println(minutes);
  }

  enableEsIst();

  if (minutes == 0) {
    enableGenau();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 4) {
    enableKurz();
    enableNach();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 5) {
    enable5M();
    enableNach();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 9) {
    enableNach();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 10) {
    enable10M();
    enableNach();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  hour++;
  if (minutes <= 14) {
    enableKurz();
    enableVor();
    enableViertel();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 15) {
    enableGenau();
    enableViertel();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 19) {
    enableKurz();
    enableNach();
    enableViertel();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 20) {
    enable10M();
    enableVor();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 24) {
    enableVor();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 25) {
    enable5M();
    enableVor();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 29) {
    enableKurz();
    enableVor();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 30) {
    enableGenau();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 34) {
    enableKurz();
    enableNach();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 35) {
    enable5M();
    enableNach();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 39) {
    enableNach();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 40) {
    enable10M();
    enableNach();
    enableHalb();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 44) {
    enableKurz();
    enableVor();
    enableDreiviertel();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 45) {
    enableGenau();
    enableDreiviertel();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 49) {
    enableKurz();
    enableNach();
    enableDreiviertel();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 50) {
    enable10M();
    enableVor();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 54) {
    enableVor();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes == 55) {
    enable5M();
    enableVor();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
  if (minutes <= 59) {
    enableKurz();
    enableVor();
    enableUm();
    setHourLedAfterTime(hour);
    return;
  }
}

void setHourLedAfterTime(int hour) {
  if (hour == 24) {
    hour = 0;
  }
  switch (hour) {
    case 0:
      enableZwoelf();
      enableNachts();
      break;
    case 1:
      enableEins();
      enableNachts();
      break;
    case 2:
      enableZwei();
      enableNachts();
      break;
    case 3:
      enableDrei();
      enableNachts();
      break;
    case 4:
      enableVier();
      enableNachts();
      break;
    case 5:
      enableFuenf();
      enableFrueh();
      break;
    case 6:
      enableSechs();
      enableFrueh();
      break;
    case 7:
      enableSieben();
      enableFrueh();
      break;
    case 8:
      enableAcht();
      enableFrueh();
      break;
    case 9:
      enableNeun();
      enableAm();
      enableVormittag();
      break;
    case 10:
      enableZehn();
      enableAm();
      enableVormittag();
      break;
    case 11:
      enableElf();
      enableAm();
      enableVormittag();
      break;
    case 12:
      enableZwoelf();
      enableAm();
      enableMittag();
      break;
    case 13:
      enableEins();
      enableAm();
      enableMittag();
      break;
    case 14:
      enableZwei();
      enableAm();
      enableNachmittag();
      break;
    case 15:
      enableDrei();
      enableAm();
      enableNachmittag();
      break;
    case 16:
      enableVier();
      enableAm();
      enableNachmittag();
      break;
    case 17:
      enableFuenf();
      enableAm();
      enableNachmittag();
      break;
    case 18:
      enableSechs();
      enableAm();
      enableAbend();
      break;
    case 19:
      enableSieben();
      enableAm();
      enableAbend();
      break;
    case 20:
      enableAcht();
      enableAm();
      enableAbend();
      break;
    case 21:
      enableNeun();
      enableAm();
      enableAbend();
      break;
    case 22:
      enableZehn();
      enableAm();
      enableAbend();
      break;
    case 23:
      enableElf();
      enableNachts();
      break;
  }
}

void showLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (ledsactive[i]) {
      leds[i] = color[i];
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
  if (DEBUG) {
    flashOperationDone();
  }
}

void flashOperationDone() {
  for (int i = 0; i < 4; i++) {
    leds[108] = CRGB::Green;
    FastLED.show();
    delay(25);
    leds[108] = CRGB::Black;
    FastLED.show();
    delay(25);
  }
}

void clearAll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = false;
    color[i] = CRGB::Black;
  }
  showLEDs();
}

void enableEsIst() {
  ledsactive[120] = true;
  ledsactive[121] = true;
  ledsactive[122] = true;
  ledsactive[124] = true;
  ledsactive[125] = true;
}

void enableGenau() {
  ledsactive[109] = true;
  ledsactive[110] = true;
  ledsactive[111] = true;
  ledsactive[112] = true;
  ledsactive[113] = true;
}

void enableKurz() {
  ledsactive[115] = true;
  ledsactive[116] = true;
  ledsactive[117] = true;
  ledsactive[118] = true;
}

void enable5M() {
  ledsactive[92] = true;
}

void enable10M() {
  ledsactive[90] = true;
  ledsactive[91] = true;
}

void enableNach() {
  ledsactive[94] = true;
  ledsactive[95] = true;
  ledsactive[96] = true;
  ledsactive[97] = true;
}

void enableVor() {
  ledsactive[98] = true;
  ledsactive[99] = true;
  ledsactive[100] = true;
}

void enableUm() {
  ledsactive[102] = true;
  ledsactive[103] = true;
}

void enableViertel() {
  ledsactive[79] = true;
  ledsactive[80] = true;
  ledsactive[81] = true;
  ledsactive[82] = true;
  ledsactive[83] = true;
  ledsactive[84] = true;
  ledsactive[85] = true;
}

void enableHalb() {
  ledsactive[104] = true;
  ledsactive[105] = true;
  ledsactive[106] = true;
  ledsactive[107] = true;
}

void enableDreiviertel() {
  ledsactive[79] = true;
  ledsactive[80] = true;
  ledsactive[81] = true;
  ledsactive[82] = true;
  ledsactive[83] = true;
  ledsactive[84] = true;
  ledsactive[85] = true;
  ledsactive[86] = true;
  ledsactive[87] = true;
  ledsactive[88] = true;
  ledsactive[89] = true;
}

void enableEins() {
  ledsactive[48] = true;
  ledsactive[49] = true;
  ledsactive[50] = true;
  ledsactive[51] = true;
}

void enableZwei() {
  ledsactive[50] = true;
  ledsactive[51] = true;
  ledsactive[52] = true;
  ledsactive[53] = true;
}

void enableDrei() {
  ledsactive[58] = true;
  ledsactive[59] = true;
  ledsactive[60] = true;
  ledsactive[61] = true;
}

void enableVier() {
  ledsactive[18] = true;
  ledsactive[19] = true;
  ledsactive[20] = true;
  ledsactive[21] = true;
}

void enableFuenf() {
  ledsactive[67] = true;
  ledsactive[68] = true;
  ledsactive[69] = true;
  ledsactive[70] = true;
  ledsactive[71] = true;
}

void enableSechs() {
  ledsactive[44] = true;
  ledsactive[45] = true;
  ledsactive[46] = true;
  ledsactive[47] = true;
  ledsactive[48] = true;
}

void enableSieben() {
  ledsactive[39] = true;
  ledsactive[40] = true;
  ledsactive[41] = true;
  ledsactive[42] = true;
  ledsactive[43] = true;
  ledsactive[44] = true;
}

void enableAcht() {
  ledsactive[63] = true;
  ledsactive[64] = true;
  ledsactive[65] = true;
  ledsactive[66] = true;
}

void enableNeun() {
  ledsactive[36] = true;
  ledsactive[37] = true;
  ledsactive[38] = true;
  ledsactive[39] = true;
}

void enableZehn() {
  ledsactive[54] = true;
  ledsactive[55] = true;
  ledsactive[56] = true;
  ledsactive[57] = true;
}

void enableElf() {
  ledsactive[72] = true;
  ledsactive[73] = true;
  ledsactive[74] = true;
}

void enableZwoelf() {
  ledsactive[72] = true;
  ledsactive[73] = true;
  ledsactive[74] = true;
  ledsactive[75] = true;
  ledsactive[76] = true;
  ledsactive[77] = true;
}

void enableAm() {
  ledsactive[30] = true;
  ledsactive[31] = true;
}

void enableNachts() {
  ledsactive[24] = true;
  ledsactive[25] = true;
  ledsactive[26] = true;
  ledsactive[27] = true;
  ledsactive[28] = true;
  ledsactive[29] = true;
}

void enableFrueh() {
  ledsactive[32] = true;
  ledsactive[33] = true;
  ledsactive[34] = true;
  ledsactive[35] = true;
}

void enableVormittag() {
  ledsactive[5] = true;
  ledsactive[6] = true;
  ledsactive[7] = true;
  ledsactive[8] = true;
  ledsactive[9] = true;
  ledsactive[10] = true;
  ledsactive[15] = true;
  ledsactive[16] = true;
  ledsactive[17] = true;
}

void enableMittag() {
  ledsactive[5] = true;
  ledsactive[6] = true;
  ledsactive[7] = true;
  ledsactive[8] = true;
  ledsactive[9] = true;
  ledsactive[10] = true;
}

void enableNachmittag() {
  ledsactive[5] = true;
  ledsactive[6] = true;
  ledsactive[7] = true;
  ledsactive[8] = true;
  ledsactive[9] = true;
  ledsactive[10] = true;
  ledsactive[11] = true;
  ledsactive[12] = true;
  ledsactive[13] = true;
  ledsactive[14] = true;
}

void enableAbend() {
  ledsactive[0] = true;
  ledsactive[1] = true;
  ledsactive[2] = true;
  ledsactive[3] = true;
  ledsactive[4] = true;
}

void initTest() {
  Lauflicht();
  clearAll();
  delay(2000);
  showAllRed();
  delay(1000);
  showAllOrange();
  delay(1000);
  showAllYellow();
  delay(1000);
  showAllGreen();
  delay(1000);
  showAllBlue();
  delay(1000);
  showAllPurple();
  delay(1000);
  clearAll();
}



void Lauflicht() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    delay(10);
    leds[dot] = CRGB::Black;
    delay(20);
  }
}

void setColorAllWhite() {
  for (int i = 0; i < NUM_LEDS; i++) {
    color[i] = CRGB::White;
  }
}

void showAllRed() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = true;
    color[i] = CRGB::Red;
  }
  showLEDs();
}

void showAllOrange() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = true;
    color[i] = CRGB::Orange;
  }
  showLEDs();  
}

void showAllYellow() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = true;
    color[i] = CRGB::Yellow;
  }
  showLEDs();
}

void showAllGreen() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = true;
    color[i] = CRGB::Green;
  }
  showLEDs();
}

void showAllBlue() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = true;
    color[i] = CRGB::Blue;
  }
  showLEDs();
}

void showAllPurple() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsactive[i] = true;
    color[i] = CRGB::Purple;
  }
  showLEDs();
}
