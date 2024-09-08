#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/c4e9550e-1345-4044-a8ef-b59c37795212 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  bool green;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/
#include "ModbusMaster.h" //https://github.com/4-20ma/ModbusMaster
#define Slave_ID 1
#define RX_PIN 26
#define TX_PIN 27
ModbusMaster modbus;
#include "thingProperties.h"
#include "Arduino.h"
#include "PCF8574.h" // https://github.com/xreef/PCF8574_library
#define I2C_Address 0x20
#define I2C_SDA_Pin 21
#define I2C_SCL_Pin 22
// Instantiate Wire for generic use at 100kHz
TwoWire I2Ctwo = TwoWire(1);
// Set i2c address
PCF8574 pcf8574(&I2Ctwo, I2C_Address, I2C_SDA_Pin, I2C_SCL_Pin);




void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  
  pcf8574.pinMode(0, OUTPUT);
  pcf8574.pinMode(1, OUTPUT);
  pcf8574.pinMode(2, OUTPUT);
  pcf8574.pinMode(3, OUTPUT);
  pcf8574.begin();

  Serial.begin(9600, SERIAL_8N1);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  modbus.begin(Slave_ID, Serial2);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  
  
}


void onYellowChange()  {
  if(yellow==1){
    Serial.println("yellow-->ON");
    pcf8574.digitalWrite(1, HIGH); delay(500);
  }else{
    Serial.println("yellow-->OFF");
    pcf8574.digitalWrite(1, LOW); delay(500);
}
}

/*
  Since Red is READ_WRITE variable, onRedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRedChange()  {
  // Add your code here to act upon Red change
  if(red==1){
    Serial.println("red-->ON");
    pcf8574.digitalWrite(2, HIGH); delay(500);
  }else{
    Serial.println("red-->OFF");
    pcf8574.digitalWrite(2, LOW); delay(500);
  }
}

/*
  Since White is READ_WRITE variable, onWhiteChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onWhiteChange()  {
   if(white==1){
    Serial.println("white-->ON");
    pcf8574.digitalWrite(3, HIGH); delay(500);
  }else{
    Serial.println("white-->OFF");
    pcf8574.digitalWrite(3, LOW); delay(500);
  }
  // Add your code here to act upon White change
}

/*
  Since Tempp is READ_WRITE variable, onTemppChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemppChange()  {
   long currentMillis = millis();
  if (currentMillis - lastMillis > 1000) {
    uint8_t result = modbus.readInputRegisters(1, 2);
    if (getResultMsg(&modbus, result)) {
    Serial.println();
    double res_dbl = modbus.getResponseBuffer(0) / 10;
    String res = "Temperature: " + String(res_dbl) + " C\r\n";
    res_dbl = modbus.getResponseBuffer(1) / 10;
    res += "Humidity: " + String(res_dbl) + " %";
    Serial.println(res);
    tempp = String(res_dbl);
  }
  lastMillis = currentMillis;
  }

}
bool getResultMsg(ModbusMaster *node, uint8_t result) {
String tmpstr2 = "\r\n";
switch (result) {
case node->ku8MBSuccess:
return true;
break;
case node->ku8MBIllegalFunction:
tmpstr2 += "Illegal Function";
break;
case node->ku8MBIllegalDataAddress:
tmpstr2 += "Illegal Data Address";
break;
case node->ku8MBIllegalDataValue:
tmpstr2 += "Illegal Data Value";
break;
case node->ku8MBSlaveDeviceFailure:
tmpstr2 += "Slave Device Failure";
break;
case node->ku8MBInvalidSlaveID:
tmpstr2 += "Invalid Slave ID";
break;
case node->ku8MBInvalidFunction:
tmpstr2 += "Invalid Function";
break;
case node->ku8MBResponseTimedOut:
tmpstr2 += "Response Timed Out";
break;
case node->ku8MBInvalidCRC:
tmpstr2 += "Invalid CRC";
break;
default:
tmpstr2 += "Unknown error: " + String(result);
break;
}
Serial.println(tmpstr2);
return false;
}
  // Add your code here to act upon Tempp change
}


/*
  Since Green is READ_WRITE variable, onGreenChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onGreenChange()  {
  if(green==1){
    Serial.println("Green-->ON");
    pcf8574.digitalWrite(0, HIGH); delay(500);
  }else{
    Serial.println("Green-->OFF");
    pcf8574.digitalWrite(0, LOW); delay(500);
  }
}
  
  
 

 