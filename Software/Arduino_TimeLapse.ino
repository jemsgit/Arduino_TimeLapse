// ========[ Pins ]===========
const int  a = 5;
const int  b = 7;
const int  c = 2;
const int  d = 4;
const int  e = 3;
const int  f = 0;
const int  g = 6;
const int  h = 1;

const int  led1 = 9;
const int  led2 = 10;
const int  led3 = 8;

const int  ON  = HIGH; 
const int  OFF = LOW;

const int  regulatorPin = A0;
const int  focusPin     = A1;
const int  cameraPin    = A2;

const int showLedDelay = 7;
const int LedsDelay = 10000;
// ===========================

const int symbols[12][8] = {
//  f    h    c    e    d    a    g    b   
  {ON,  OFF, ON,  ON,  ON,  ON,  OFF,  ON}, // 0
  {OFF, OFF, ON,  OFF, OFF, OFF, OFF,  ON}, // 1
  {OFF, OFF, OFF, ON,  ON,  ON,  ON,   ON}, // 2
  {OFF, OFF, ON,  OFF, ON,  ON,  ON,   ON}, // 3
  {ON,  OFF, ON,  OFF, OFF, OFF, ON,   ON}, // 4
  {ON,  OFF, ON,  OFF, ON,  ON,  ON,   OFF}, // 5
  {ON,  OFF, ON,  ON,  ON,  ON,  ON,   OFF}, // 6
  {OFF, OFF, ON,  OFF, OFF, ON,  OFF,  ON}, // 7
  {ON,  OFF, ON,  ON,  ON,  ON,  ON,   ON}, // 8
  {ON,  OFF, ON,  OFF, ON,  ON,  ON,   ON}, // 9
  {ON,  OFF, OFF, OFF, OFF, OFF, OFF,  ON}, // s
  {ON,  OFF, OFF, OFF, OFF, OFF, OFF, OFF}  // m
};

const int timerValues[32] = {
  1,   2,    3,    4,    5,    10,   /*15,*/   20,   
  30,  60,   /*120,  180,  240, */ 300, /* 360,  420, 
  480, 540, */ 600, /* 660,  720,  780,  840,*/  900, 
  /*960, 1020, 1080, 1140,*/ 1200, 1800, 2400, 3600
};
  
const char* timerStrings[] = {
  "01s","02s","03s","04s","05s","10s",/*"15s",*/"20s",
  "30s","01m",/*"02m","03m","04m",*/"05m",/*"06m","07m",
  "08m","09m",*/"10m",/*"11m","12m","13m","14m",*/"15m",
  /*"16m","17m","18m","19m",*/"20m","30m","40m","60m"
};

const int leds[3] = {led1, led2, led3};

int sensorValue = 0;  // variable to store the value coming from the sensor
int index = 0;        // index of array
unsigned long lastTime; // time of last itteration
unsigned long lastLED; 
int first = 0;
  
void setup() {
  //Serial.begin(9600); 
  
  initLeds();
 
  pinMode(focusPin, OUTPUT);
  pinMode(cameraPin, OUTPUT); 
}

void loop() {
  // read the value from the sensor:
  sensorValue = (int) analogRead(regulatorPin)*16/990; 
  if (index !=  sensorValue) {
    index = sensorValue;
    lastTime = millis();
    lastLED = millis();
    first = 0;
    //Serial.print(sensorValue);
    //Serial.print(" - ");
    //Serial.println(analogRead(regulatorPin));
  }
  
  if ((millis()-lastLED) <= LedsDelay) {
    updateLeds();
  } else {
    clearLeds();
  }
  
  if (((millis()-lastTime) >= timerValues[index]*1000) || 
      ((first == 0) && ((millis()-lastTime) >= 1000))) {
    //Serial.print("[");
    //Serial.print(first);
    //Serial.print("]");
    //Serial.print(millis());
    //Serial.print(" - ");
    //Serial.print(millis()-lastTime);
    //Serial.print(" = ");
    //Serial.println(timerValues[index]*1000);
    first++;
     
    takePicture();
    lastTime = millis();
  }  
}

void takePicture() {
 // digitalWrite(focusPin, HIGH);
  digitalWrite(cameraPin, HIGH);
  delay(60);
 // digitalWrite(focusPin, LOW); 
  digitalWrite(cameraPin, LOW); 
  
}

void initLeds() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);  
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(h, OUTPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
  digitalWrite(led3, LOW); 
}

void updateLeds() {
  for (int i=0; i<3; i++) {
    showLed(i);
  }
}

void showLed(int j) {
  clearLeds(); 
  int pos = returnSymbol(timerStrings[index][j]);
  for(int i=0; i<8; i++) {   
    if ((j == 2) && (i == 1) && ((millis()-lastTime) >= 1000)) {
      digitalWrite(i, ON);
    } else {
      digitalWrite(i, symbols[pos][i]);
    }
  }
  setLed(j);
  delay(showLedDelay);
}

int returnSymbol (char Symbol) {
  if (Symbol == 's') {
    return 10;
  } else if (Symbol == 'm') {
    return 11;
  } else {
    return ((int)Symbol)-48;
  }
}

void setLed(int i) {
  for (int j=0; j<3; j++) {
    if (j==i) {
      digitalWrite(leds[j], HIGH);
    } else {
      digitalWrite(leds[j], LOW);
    }
  }
}

void clearLeds() {
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW); 
  digitalWrite(leds[2], LOW); 
}

