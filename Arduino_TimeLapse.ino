// ========[ Pins ]===========
const int  a = 5;
const int  b = 7;
const int  c = 2;
const int  d = 4;
const int  e = 3;
const int  f = 0;
const int  g = 6;
const int  h = 1;

const int  led1 = 10;
const int  led2 = 9;
const int  led3 = 8;

const int  ON  = HIGH; 
const int  OFF = LOW;

const int  regulatorPin = A0;
const int  focusPin     = A1;
const int  cameraPin    = A2;
// ===========================

const int symbols[12][8] = {
//  f    h    c    e    d    a    g    b   
  {ON,  OFF, ON,  ON,  ON,  ON,  OFF, ON }, // 0
  {ON,  OFF, OFF, ON,  OFF, OFF, OFF, OFF}, // 1
  {OFF, OFF, OFF, ON,  ON,  ON,  ON,  ON }, // 2
  {ON,  OFF, OFF, ON,  ON,  ON,  ON,  OFF}, // 3
  {ON,  OFF, ON,  ON,  OFF, OFF, ON,  OFF}, // 4
  {ON,  OFF, ON,  OFF, ON,  ON,  ON,  OFF}, // 5
  {ON,  OFF, ON,  OFF, ON,  ON,  ON,  ON }, // 6
  {ON,  OFF, OFF, ON,  ON,  OFF, OFF, OFF}, // 7
  {ON,  OFF, ON,  ON,  ON,  ON,  ON,  ON }, // 8
  {ON,  OFF, ON,  ON,  ON,  ON,  ON,  OFF}, // 9
  {OFF, OFF, ON,  ON,  OFF, OFF, OFF, OFF}, // s
  {OFF, OFF, ON,  OFF, OFF, OFF, OFF, OFF}  // m
};

const int timerValues[32] = {
  1,   2,    3,    4,    5,    10,   15,   20,   
  30,  60,   120,  180,  240,  300,  360,  420, 
  480, 540,  600,  660,  720,  780,  840,  900, 
  960, 1020, 1080, 1140, 1200, 1800, 2400, 3600
};
  
const char* timerStrings[] = {
  "01s","02s","03s","04s","05s","10s","15s","20s",
  "30s","01m","02m","03m","04m","05m","06m","07m",
  "08m","09m","10m","11m","12m","13m","14m","15m",
  "16m","17m","18m","19m","20m","30m","40m","60m"
};

int sensorValue = 0;  // variable to store the value coming from the sensor
int index = 0;        // index of array
unsigned long lastTime; // time of last itteration
  
void setup() {
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
 
  pinMode(focusPin, OUTPUT);
  pinMode(cameraPin, OUTPUT); 
}

void loop() {
  // read the value from the sensor:
  if (sensorValue != analogRead(regulatorPin)) {
    sensorValue = analogRead(regulatorPin);
    index = (int) sensorValue/32;
    lastTime = millis();
  }
  
  updateLeds();
  
  if ((millis()-lastTime) >= timerValues[index]*1000) {
    takePicture();
    lastTime = millis();
  }  
}

void takePicture() {
  digitalWrite(focusPin, HIGH);
  digitalWrite(cameraPin, HIGH);
  delay(50);
  digitalWrite(focusPin, LOW); 
  digitalWrite(cameraPin, LOW); 
  
}

void updateLeds() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW); 
  digitalWrite(led3, LOW); 
  showLed(1);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH); 
  digitalWrite(led3, LOW);  
  showLed(2);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
  digitalWrite(led3, HIGH);
  showLed(3);
}

void showLed(int j) {
  int pos = returnSymbol(timerStrings[index][j]);
  for(int i=0; i<8; i++) {
    digitalWrite(i, symbols[pos][i]);
  }
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

