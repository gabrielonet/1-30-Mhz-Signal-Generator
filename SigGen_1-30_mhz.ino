#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 MCP4725;
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Wire.h>
// I have lost initial code, have to remake it from ground 0. Work In Progress !! 
// I use PU2CLR lib to adress multiple i2c extenders.

#include <pu2clr_mcp23008.h>


const byte rxPin = 4;
const byte txPin = 5;
double frecventa = 14000000;
// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);
String stopBit  ;
String dfd = "" ;
#define W_CLK 8   // Pin 8 - connect to AD9850 module word load clock pin (CLK)
#define FQ_UD 9   // Pin 9 - connect to freq update pin (FQ)
#define DATA 10   // Pin 10 - connect to serial data load pin (DATA)
#define RESET 11  // Pin 11 - connect to reset pin (RST) 
#define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }


MCP dividerA;
MCP dividerB;
MCP dividerC;
MCP dividerD;
// HMC472 truth table is reversed, we need to compute AND negate all 6 bits.

int att = 10   ; // Enter here value in dB
String freq ; 
String gain ;
String relative_att = "0" ;

String incomingByte = "" ; // for incoming serial data
int a = 0 ;
int b = 0 ;
int c = 0 ;
int d = 0 ;
int num;
int bit_0 ;
int bit_1 ;
int bit_2 ;
int bit_3 ;
int bit_4 ;
int bit_5 ;
String byte_A ;
String byte_B ;
String byte_C ;
String byte_D ;
int start = millis();

void setup()
    {
      dividerA.setup(0x20); dividerB.setup(0x21); dividerC.setup(0x22); dividerD.setup(0x23);
      dividerA.turnGpioOn(MCP_GPIO0);dividerA.turnGpioOn(MCP_GPIO1); dividerA.turnGpioOn(MCP_GPIO2);dividerA.turnGpioOn(MCP_GPIO3);dividerA.turnGpioOn(MCP_GPIO4);dividerA.turnGpioOn(MCP_GPIO5);dividerA.turnGpioOn(MCP_GPIO6);dividerA.turnGpioOn(MCP_GPIO7);
      dividerB.turnGpioOn(MCP_GPIO0);dividerB.turnGpioOn(MCP_GPIO1); dividerB.turnGpioOn(MCP_GPIO2);dividerB.turnGpioOn(MCP_GPIO3);dividerB.turnGpioOn(MCP_GPIO4);dividerB.turnGpioOn(MCP_GPIO5);dividerB.turnGpioOn(MCP_GPIO6);dividerB.turnGpioOn(MCP_GPIO7);
      dividerC.turnGpioOn(MCP_GPIO0);dividerC.turnGpioOn(MCP_GPIO1); dividerC.turnGpioOn(MCP_GPIO2);dividerC.turnGpioOn(MCP_GPIO3);dividerC.turnGpioOn(MCP_GPIO4);dividerC.turnGpioOn(MCP_GPIO5);dividerC.turnGpioOn(MCP_GPIO6);dividerC.turnGpioOn(MCP_GPIO7);
      dividerD.turnGpioOn(MCP_GPIO0);dividerD.turnGpioOn(MCP_GPIO1); dividerD.turnGpioOn(MCP_GPIO2);dividerD.turnGpioOn(MCP_GPIO3);dividerD.turnGpioOn(MCP_GPIO4);dividerD.turnGpioOn(MCP_GPIO5);dividerD.turnGpioOn(MCP_GPIO6);dividerD.turnGpioOn(MCP_GPIO7);
 pinMode(FQ_UD, OUTPUT);
  pinMode(W_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RESET, OUTPUT); 
  pulseHigh(RESET);
  pulseHigh(W_CLK);
  pulseHigh(FQ_UD);  // this pulse enables serial mode on the AD9850 - Datasheet page 12.
  ad9850(frecventa);
  MCP4725.begin(0x60);

      
      Serial.begin(9600);
      mySerial.begin(9600);
      compute() ;     
    }

void ad9850(double frequency) {  
  int32_t freq = frequency  * 4294967295/125000000;  // note 125 MHz clock on 9850.  You can make 'slight' tuning variations here by adjusting the clock frequency.
  for (int b_it = 0; b_it < 4; b_it++, freq>>=8) {
    ad9850_serial_send(freq & 0xFF);
  }
  ad9850_serial_send(0x000);   // Final control byte, all 0 for 9850 chip
  pulseHigh(FQ_UD);  // Done!  Should see output
}
void ad9850_serial_send(byte data)
{
  for (int i=0; i<8; i++, data>>=1) {
    digitalWrite(DATA, data & 0x01);
    pulseHigh(W_CLK);
  }
}




void compute()
{
   int  times = att / 30 ;
     if (times == 4) {
      a  = 30 , b=30, c = 30, d = att - (a + b +c) ;
      }

    if (times == 3) {
      a  = 30 , b = 30, c = 30, d = att - (a + b +c) ;
      }  
    if (times == 2) {
      a  = 0 , b = 30, c = 30, d = att - (a + b +c) ;
      }  
    if (times == 1) {
      a  = 0 , b = 0, c = 30, d = att - (a + b +c) ;
      }  
    if (times == 0) {
      a  = 0 , b = 0, c = 0, d = att - (a + b +c) ;
    }

num = a *2 ;
bit_0 = !bitRead(num, 5); if (bit_0 == 1){ dividerA.turnGpioOn(MCP_GPIO0);} else {dividerA.turnGpioOff(MCP_GPIO0);}
bit_1 = !bitRead(num, 4); if (bit_0 == 1){ dividerA.turnGpioOn(MCP_GPIO1);} else {dividerA.turnGpioOff(MCP_GPIO1);}
bit_2 = !bitRead(num, 3); if (bit_0 == 1){ dividerA.turnGpioOn(MCP_GPIO2);} else {dividerA.turnGpioOff(MCP_GPIO2);}
bit_3 = !bitRead(num, 2); if (bit_0 == 1){ dividerA.turnGpioOn(MCP_GPIO3);} else {dividerA.turnGpioOff(MCP_GPIO3);}
bit_4 = !bitRead(num, 1); if (bit_0 == 1){ dividerA.turnGpioOn(MCP_GPIO4);} else {dividerA.turnGpioOff(MCP_GPIO4);}
bit_5 = !bitRead(num, 0); if (bit_0 == 1){ dividerA.turnGpioOn(MCP_GPIO5);} else {dividerA.turnGpioOff(MCP_GPIO5);}
byte_A = String(bit_0) + "," + String(bit_1) + "," + String(bit_2) + "," + String(bit_3) + "," + String(bit_4) + "," + String(bit_5);


num = b *2 ;
bit_0 = !bitRead(num, 5); if (bit_0 == 1){ dividerB.turnGpioOn(MCP_GPIO0);} else {dividerB.turnGpioOff(MCP_GPIO0);}
bit_1 = !bitRead(num, 4); if (bit_0 == 1){ dividerB.turnGpioOn(MCP_GPIO1);} else {dividerB.turnGpioOff(MCP_GPIO1);}
bit_2 = !bitRead(num, 3); if (bit_0 == 1){ dividerB.turnGpioOn(MCP_GPIO2);} else {dividerB.turnGpioOff(MCP_GPIO2);}
bit_3 = !bitRead(num, 2); if (bit_0 == 1){ dividerB.turnGpioOn(MCP_GPIO3);} else {dividerB.turnGpioOff(MCP_GPIO3);}
bit_4 = !bitRead(num, 1); if (bit_0 == 1){ dividerB.turnGpioOn(MCP_GPIO4);} else {dividerB.turnGpioOff(MCP_GPIO4);}
bit_5 = !bitRead(num, 0); if (bit_0 == 1){ dividerB.turnGpioOn(MCP_GPIO5);} else {dividerB.turnGpioOff(MCP_GPIO5);}
byte_B = String(bit_0) + "," + String(bit_1) + "," + String(bit_2) + "," + String(bit_3) + "," + String(bit_4) + "," + String(bit_5);


num = c *2 ;
bit_0 = !bitRead(num, 5); if (bit_0 == 1){ dividerC.turnGpioOn(MCP_GPIO0);} else {dividerC.turnGpioOff(MCP_GPIO0);}
bit_1 = !bitRead(num, 4); if (bit_0 == 1){ dividerC.turnGpioOn(MCP_GPIO1);} else {dividerC.turnGpioOff(MCP_GPIO1);}
bit_2 = !bitRead(num, 3); if (bit_0 == 1){ dividerC.turnGpioOn(MCP_GPIO2);} else {dividerC.turnGpioOff(MCP_GPIO2);}
bit_3 = !bitRead(num, 2); if (bit_0 == 1){ dividerC.turnGpioOn(MCP_GPIO3);} else {dividerC.turnGpioOff(MCP_GPIO3);}
bit_4 = !bitRead(num, 1); if (bit_0 == 1){ dividerC.turnGpioOn(MCP_GPIO4);} else {dividerC.turnGpioOff(MCP_GPIO4);}
bit_5 = !bitRead(num, 0); if (bit_0 == 1){ dividerC.turnGpioOn(MCP_GPIO5);} else {dividerC.turnGpioOff(MCP_GPIO5);}
byte_C = String(bit_0) + "," + String(bit_1) + "," + String(bit_2) + "," + String(bit_3) + "," + String(bit_4) + "," + String(bit_5);


num = d *2 ;
bit_0 = !bitRead(num, 5); if (bit_0 == 1){ dividerD.turnGpioOn(MCP_GPIO0);} else {dividerD.turnGpioOff(MCP_GPIO0);}
bit_1 = !bitRead(num, 4); if (bit_0 == 1){ dividerD.turnGpioOn(MCP_GPIO1);} else {dividerD.turnGpioOff(MCP_GPIO1);}
bit_2 = !bitRead(num, 3); if (bit_0 == 1){ dividerD.turnGpioOn(MCP_GPIO2);} else {dividerD.turnGpioOff(MCP_GPIO2);}
bit_3 = !bitRead(num, 2); if (bit_0 == 1){ dividerD.turnGpioOn(MCP_GPIO3);} else {dividerD.turnGpioOff(MCP_GPIO3);}
bit_4 = !bitRead(num, 1); if (bit_0 == 1){ dividerD.turnGpioOn(MCP_GPIO4);} else {dividerD.turnGpioOff(MCP_GPIO4);}
bit_5 = !bitRead(num, 0); if (bit_0 == 1){ dividerD.turnGpioOn(MCP_GPIO5);} else {dividerD.turnGpioOff(MCP_GPIO5);}
byte_D = String(bit_0) + "," + String(bit_1) + "," + String(bit_2) + "," + String(bit_3) + "," + String(bit_4) + "," + String(bit_5);


int stop = millis();

// Here we should call 4 different instances of MCP23008 to write values into dividers via i2c bus.
Serial.println("Computing values for " + String(att) + "dB");  
Serial.println("Divider A attenuation = " + String(a) + "dB");
Serial.println("Divider B attenuation = " + String(b) + "dB");
Serial.println("Divider C attenuation = " + String(c) + "dB");
Serial.println("Divider D attenuation = " + String(d) + "dB");
////////////////////////////////////////////////////////////////////////////
Serial.println("writting divider A with " + byte_A );
Serial.println("writting divider B with " + byte_B );
Serial.println("writting divider C with " + byte_C );
Serial.println("writting divider D with " + byte_D );

//Serial.println("Compute time = " + String(stop - start) + " miliseconds" );
}

void loop()
{
 if (mySerial.available() > 0) {
    // read the incoming byte:
    char plm = char(mySerial.read());
    if (String(plm) == "S" ) {freq = incomingByte ; plm = "" ; incomingByte = "" ;}
    if (String(plm) == "T" ) {gain = incomingByte ; plm = "" ; incomingByte = "" ;}
    if (String(plm) == "Y" ) {relative_att  = incomingByte ; plm = "" ; incomingByte = "" ;}
    incomingByte += plm ;  
    freq.replace ("V", ""); gain.replace ("V", ""); relative_att.replace ("V", "");
    Serial.println(freq.toInt()); Serial.println(gain); Serial.println(relative_att);
    ad9850(freq.toInt());
    att = relative_att.toInt();
    compute();
    //MCP4725.setVoltage(4096 - gain.toInt(), false);
    
  }


}
