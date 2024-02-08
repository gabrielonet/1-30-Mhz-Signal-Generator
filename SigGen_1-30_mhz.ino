// I have lost initial code, have to remake it from ground 0. Work In Progress !! 
// I use PU2CLR lib to adress multiple i2c extenders.

#include <pu2clr_mcp23008.h>
MCP dividerA;
MCP dividerB;
MCP dividerC;
MCP dividerD;
// HMC472 truth table is reversed, we need to compute AND negate all 6 bits.

int att = 38 ; // Enter here value in dB

int incomingByte = 0; // for incoming serial data
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
      
      Serial.begin(9600);
      SerialUSB.begin(9600);
      compute() ;     
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
 if (SerialUSB.available() > 0) {
    // read the incoming byte:
    incomingByte = SerialUSB.read();
    att = incomingByte;
    compute();
  }
}
