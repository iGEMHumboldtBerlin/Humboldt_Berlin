/**
* #########################
* # Humbold University zu Berlin
* # iGEM 2019 on Chlaydomonas cultivation
*
* #########################
* # @version  0.5
* # @platform  arduino AT Mega 2560 
* # @clock  16mHz
* # @created  20190614
* # @changed  2011018
* # @user
      
      epicness
      tet
*
* #########################
* # selftest, rining wires, light on big to grow, break in for sensoring
* # grow-30sec, break-1sec
*
* #########################
*/
//#####################################################################
// general import declaration
#include <Arduino.h>

//#####################################################################
// pcb wiring - input analog of sensors
int sensorPinMainVCC   = A0;    // vcc level in volt of 5 Volt system
int sensorPinCurrent1  = A1;    // current used via shunt in mV/
int irSensorLeft = A2;          // opt 101  sense 680nm in mV
int sensorPinCurrent2  = A3;    // current used via shunt in mV/
int irSensorMiddle = A4;        // opt 101  sense 680nm in mV
int sensorPinCurrent3  = A5;    // current used via shunt in mV/
int irSensorRight = A6;         // opt 101  sense 680nm in mV   // Water Temp. Sensor DS18B20

// pcb wiring - input digital

 int whitePin = 3;
 int redPin   = 4;
 int greenPin = 5;
 int bluePin  = 6;

 int pumpLeftIn    = 8;
 int pumpLeftOut   = 7;
 int pumpMiddleIn = 10;
 int pumpMiddleOut = 9;
 int pumpRightIn  = 12;
 int pumpRightOut = 11;

 int sensorPinTempSense = 14;
 int airValve = 13;

 //
  int irLEDLeft   = 15;
  int irLEDMiddle = 16;
  int irLEDRight  = 17;

//#####################################################################
//  member variables - variable, to calc and screw
int analogRead0 = 0;     // vcc main supply of the system
int analogRead1 = 0;     // opt101 current value
int readLeftSensor = 0;  // opt101 sensor value
int analogRead3 = 0;     // opt101 current value
int readMiddleSensor = 0;// opt101 sensor value
int analogRead5 = 0;     // opt101 current value
int readRightSensor = 0; // opt101 sensor value
int analogRead7 = 0;     // no function yet

int digitalRead0 = 0; // vcc main supply
int digitalRead1 = 0; // 
int digitalRead2 = 0; // 
int digitalRead3 = 0; // WhiteLED
int digitalRead4 = 0; // RedLED
int digitalRead5 = 0; // GreenLED
int digitalRead6 = 0; // BlueLED
int digitalRead7 = 0; // pumpLeftOut
int digitalRead8 = 0; // pumpLeftIn
int digitalRead9 = 0; // pumpMiddleOut
int digitalRead10 = 0;// pumpMiddleIn
int digitalRead11 = 0;// pumpRightOut
int digitalRead12 = 0;// pumpRightIn
int digitalRead13 = 0;// airValve to stop gas flow to the chambers
int digitalRead14 = 0;

int inByte = 0;         // incoming serial byte

int roundCycle = 0; // number of measurments


int brightnessWhite = 0; // value between 0 und 255 – for intensity of white LEDs
int brightnessRed = 0; // value between 0 und 255 – for intensity of red LEDs
int brightnessGreen = 0; // value between 0 und 255 – for intensity of green LEDs
int brightnessBlue = 0; // value between 0 und 255 – for intensity of blue LEDs
int airValveStatus = 0; // dont touch!
//#####################################################################
// member variables - timing
unsigned long previousMillis = 0;   // will store last time
const long interval = 10*60*1000;        // 10 minutes x 60 sec * 1000 milli
const int pumpTime = 5000; // 

//#####################################################################

/**
 * shift the value to the external module ( MOSFET )
 */
void setColor() {
  analogWrite(redPin, brightnessRed);
  analogWrite(greenPin,brightnessGreen);
  analogWrite(bluePin, brightnessBlue);
  analogWrite(whitePin, brightnessWhite);
  analogWrite(airValve, airValveStatus);
  delay(100);
}

/**
##########################################################################
 * set white, red and blue to 255 and green to 50;
 */
 void setAllLLightOn() {
    brightnessWhite = 255;
    brightnessRed = 255;
    brightnessGreen = 255;
    brightnessBlue = 255;
    airValveStatus = 0;
    setColor();
    delay(100);
 }

 /**
  * set white, red and blue to 255 and green to 50;
  */
  void setLightOff() {
     brightnessWhite = 0;
     brightnessRed = 0;
     brightnessGreen = 0;
     brightnessBlue = 0;
     airValveStatus = 0;
     setColor();
     delay(100);
     
  }


/**
 * set white, red and blue to your wished intensity and color ;
 */
 void setGrowLight() {
    brightnessWhite = 150;
    brightnessRed = 150;
    brightnessGreen = 150;
    brightnessBlue = 150;
    
    airValveStatus = 255;
    setColor();
 }



/**
* prepare and init variables and io procedure 
*/
void setup() {

  // monitoring on a remote computer 
  Serial.begin(9600);
  while (!Serial) {
    ; // getReadyStateLike
  }

  delay(2222);  // time to get upset done 

  // ready we guess....
  if (Serial.available() == 0 && Serial.availableForWrite() > 0) { // ready for serial output
    //Serial.available()
    Serial.print("SERIAL["); 
    Serial.print(Serial.available()); 
    Serial.print("|");
    Serial.print(Serial.availableForWrite());
    Serial.print("|");
    Serial.print(Serial.getTimeout());
    Serial.println("]");
    delay(Serial.getTimeout()*1.41);

  }

  // gpio - input // Arduino pin selction 

  pinMode(sensorPinMainVCC, INPUT); // analog0
  pinMode(sensorPinCurrent1, INPUT); // analog1
  pinMode(irSensorLeft, INPUT); // analog3
  pinMode(sensorPinCurrent2, INPUT); // analog4
  pinMode(irSensorMiddle, INPUT); // analog5
  pinMode(sensorPinCurrent3, INPUT); // analog6
  pinMode(irSensorRight, INPUT); // analog7
  pinMode(sensorPinTempSense, INPUT); // digital13
  // gpio - output
  pinMode(whitePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(pumpLeftIn, OUTPUT);
  pinMode(pumpLeftOut, OUTPUT);
  pinMode(pumpMiddleIn, OUTPUT);
  pinMode(pumpMiddleOut, OUTPUT);
  pinMode(pumpRightIn, OUTPUT);
  pinMode(pumpRightOut, OUTPUT);
  pinMode(airValve, OUTPUT);

  pinMode(irLEDLeft, OUTPUT);
  pinMode(irLEDMiddle, OUTPUT);
  pinMode(irLEDRight, OUTPUT);


  // informing the serial monitor, which source file was used ....
  Serial.println("using file for this project: OpenPBR-0.4.cpp");
//####################
  // log header
  Serial.println("INIT[roundCycle,Vcc,Vin LeftChamber,Vout LeftChamber ,Vin MiddleChamber,Vout MiddleChamber,Vin rightChamber,Vout rightChamber,Temp.]");  

  Serial.print("INTERVAL,");// first line in log for interval
  Serial.print(interval);
  Serial.println(",");
//#####################

  Serial.print("INPUTPORT["); 
  Serial.print(millis());
  Serial.print(",");
  Serial.print(sensorPinMainVCC);
  Serial.print(",");
  Serial.print(sensorPinCurrent1); //Vin LeftChamber
  Serial.print(",");
  Serial.print(sensorPinCurrent2); //Vin MiddleChamber
  Serial.print(",");
  Serial.print(sensorPinCurrent3); //Vin rightChamber
  Serial.print(",");
  Serial.print(irSensorLeft); //Vout LeftChamber
  Serial.print(",");
  Serial.print(irSensorMiddle); //Vout MiddleChamber
  Serial.print(",");
  Serial.print(irSensorRight); //Vout rightChamber
  Serial.print(",");
  Serial.print(sensorPinTempSense);
  Serial.println(",");
/*
//this could be used for button control in future
  Serial.print("OUTPUTPORT[");
  Serial.print(ledPWR);
  Serial.print("|");
  Serial.print(ledRDY);
  Serial.print("|");
  Serial.print(ledBSY);
  Serial.println("]");
*/

Serial.print("UPDATE[");
Serial.print(interval);
Serial.println(",");

  // led check, on and off
  Serial.println("running all led to ON");
  delay(2222);
  setAllLLightOn();
  delay(2222);
  Serial.println("running all led to OFF");
  setLightOff();
  delay(2222);


  Serial.println("SETUP[done]");
}


//#####################################################################
// from here on running code for non blocking behaviour// ab hier echtes programm
//#####################################################################


/**
* read values from wired inputs
* send data via serial to host computer, for logging
*/
void doTheLogging() { //logging of sensor values
  //if ( isItTime == 1 ) {
    // get incoming byte:
    inByte = Serial.read(); // start serial monitor
    //#####################################################################
    analogRead0 = analogRead(sensorPinMainVCC); //real values
    analogRead1 = analogRead(sensorPinCurrent1);
    //readLeftSensor = analogRead(irSensorLeft);
    analogRead3 = analogRead(sensorPinCurrent2);
    //readMiddleSensor = analogRead(irSensorMiddle);
    analogRead5 = analogRead(sensorPinCurrent3);
    //readRightSensor = analogRead(irSensorRight);
    

    // read switch, map it to 0 or 255 //for buttons in future
  //  digitalRead0 = map(digitalRead(digitalPinInput), 0, 1, 0, 255); // for buttons in future
    //#####################################################################
    // send sensor values:
    Serial.print("DATA ,");
    Serial.print(roundCycle);
    Serial.print(",");
    Serial.print(analogRead0 * ( 5.0 / 1023 )); // divide 5V through 1023 
    Serial.print(",");
    Serial.print(analogRead1 * ( 5.0 / 1023 ));
    Serial.print(",");
    Serial.print(readLeftSensor * ( 5.0 / 1023 ));
    Serial.print(",");
    Serial.print(analogRead3 * ( 5.0 / 1023 ));
    Serial.print(",");
    Serial.print(readMiddleSensor * ( 5.0 / 1023 ));
    Serial.print(",");
    Serial.print(analogRead5 * ( 5.0 / 1023 ));
    Serial.print(",");
    Serial.print(readRightSensor * ( 5.0 / 1023 ));
    Serial.print(",");
    Serial.print(digitalRead13);// temp senseor
    Serial.println(",");
  //} else {
    // nothing
    // Serial.println("SERIAL[UNRESOLVED]");
    // @todo could count the unused case here :/
//}
    roundCycle++; // number of measurments  +1
}


/**
//for buttons
* timer check and update 
* blinks then
*/
void checTimeAndLog(){ //
  unsigned long currentMillis = millis(); // holt laufzeit seit setup()
  if ((currentMillis - previousMillis) >= interval) { // es so weit

    // save time
    previousMillis = currentMillis;
    setLightOff();
    delay(500);
    doTheLogging();
    delay(500);
  } else {
    setGrowLight();
  }

//  } else {
    // come back later and use above
//  }

}

/**
  * switch ir led on, read value from opt101 sensor, switch ir led off
  */
void measureDensity(){
    // put ir led on
    digitalWrite(irLEDLeft, HIGH);
    digitalWrite(irLEDMiddle, HIGH);
    digitalWrite(irLEDRight, HIGH);
  
  

    delay(1000);    // give the sensor some time, to swing in

    // measure density with sesor opt101
     readLeftSensor = analogRead(irSensorLeft);
     readMiddleSensor = analogRead(irSensorMiddle);
     readRightSensor = analogRead(irSensorRight);

     digitalWrite(irLEDLeft, LOW);
     digitalWrite(irLEDMiddle, LOW);
     digitalWrite(irLEDRight, LOW);
  
     

     delay(1000);   // wait, till measruing is done
  // switch ir led OFF
}

/*
#################################
Pump controll
*/
void checkDensityAndPump(){

  setGrowLight();
  
  //Serial.print("readLeftSensor: ");
  //Serial.println(readLeftSensor);

  if ( readLeftSensor <= 195 ) { // decide on density == 1 (example OD 1 [a.u.] = 0.95v on Vout of opt101. Divide 1024 by 5 volt times the Vout value you want to dilute the culture by)   
    // stop cycle and pump medium out
    //Serial.println("pumping chamber left out");
    digitalWrite(pumpLeftOut, HIGH);
    delay(pumpTime*3);   //  run pump for x seconds
    digitalWrite(pumpLeftOut, LOW);
    delay(2222);    // wait for some time

    // when medium is exported, refill with fresh medium
    //Serial.println("pumping chamber left in");
    digitalWrite(pumpLeftIn, HIGH);
    delay(pumpTime);   //  run pump for x seconds
    digitalWrite(pumpLeftIn, LOW);
    delay(2222);    // wait for some time
  }

  //Serial.print("readMiddleSensor: ");
  //Serial.println(readMiddleSensor);
  if ( readMiddleSensor <= 195 ) { // decide on density == 1 (example OD 1 [a.u.] = 0.95v on Vout of opt101. Divide 1024 by 5 volt times the Vout value you want to dilute the culture by)
    //Serial.println("pumping chamber left out");
    // stop cycle and pump medium out
    digitalWrite(pumpMiddleOut, HIGH);
    delay(pumpTime*3);   //  run pump for x seconds
    digitalWrite(pumpMiddleOut, LOW);
    delay(2222);    // wait for some time

    // when medium is exported, refill with fresh medium
   // Serial.println("pumping chamber middle in");
    digitalWrite(pumpLeftIn, HIGH);
    delay(pumpTime);   //  run pump for x seconds
    digitalWrite(pumpLeftIn, LOW);
    delay(2222);    // wait for some time
  }

  //Serial.print("readRightSensor: ");
 // Serial.println(readRightSensor);
  if ( readRightSensor <= 195 ) { // decide on density == 1 (example OD 1 [a.u.] = 0.95v on Vout of opt101. Divide 1024 by 5 volt times the Vout value you want to dilute the culture by)
    // stop cycle and pump medium out
    //Serial.println("pumping chamber right in");
    digitalWrite(pumpRightOut, HIGH);
    delay(pumpTime*3);   //  run pump for x seconds
    digitalWrite(pumpRightOut, LOW);
    delay(2222);    // wait for some time

    // when medium is exported, refill with fresh medium
    //Serial.println("pumping chamber right out");
    digitalWrite(pumpRightIn, HIGH);
    delay(pumpTime);   //  run pump for x seconds
    digitalWrite(pumpRightIn, LOW);
    delay(2222);    // wait for some time
  }
}
/**
* do the heavy shit in here
* used methods should be declared before, top->down compiling :/
*/
void loop() {

  //doTheLogging();
  measureDensity();
  checkDensityAndPump();
  //setGrowLight();
  // up and down check
  checTimeAndLog(); // benutz die methode abfragen nach zeit zum messen

}
