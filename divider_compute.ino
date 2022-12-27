int debug = 1 ; // set 1 to enable serial console debugging, it slows down computing time
float att = 90 ; // value in dB

int a = 0 ;
int b = 0 ;
int c = 0 ;
float d = 0 ;
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

void setup()
    {
      Serial.begin(9600);
      compute() ;
      if (debug == 1){debuging();}
    }

void compute()
{
   int  times = att / 30 ;
     if (times == 4) {
      a  = 30 , b=30, c = 30, d = 30 ;
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
bit_0 = bitRead(num, 5);
bit_1 = bitRead(num, 4);
bit_2 = bitRead(num, 3);
bit_3 = bitRead(num, 2);
bit_4 = bitRead(num, 1);
bit_5 = bitRead(num, 0);
byte_A = String(bit_0) +  String(bit_1) + String(bit_2) + String(bit_3) + String(bit_4) +  String(bit_5);

num = b *2 ;
bit_0 = bitRead(num, 5);
bit_1 = bitRead(num, 4);
bit_2 = bitRead(num, 3);
bit_3 = bitRead(num, 2);
bit_4 = bitRead(num, 1);
bit_5 = bitRead(num, 0);
byte_B = String(bit_0) +  String(bit_1) + String(bit_2) + String(bit_3) + String(bit_4) +  String(bit_5);
num = c *2 ;
bit_0 = bitRead(num, 5);
bit_1 = bitRead(num, 4);
bit_2 = bitRead(num, 3);
bit_3 = bitRead(num, 2);
bit_4 = bitRead(num, 1);
bit_5 = bitRead(num, 0);
byte_C = String(bit_0) +  String(bit_1) + String(bit_2) + String(bit_3) + String(bit_4) +  String(bit_5);
num = d *2 ;
bit_0 = bitRead(num, 5);
bit_1 = bitRead(num, 4);
bit_2 = bitRead(num, 3);
bit_3 = bitRead(num, 2);
bit_4 = bitRead(num, 1);
bit_5 = bitRead(num, 0);
byte_D = String(bit_0) +  String(bit_1) + String(bit_2) + String(bit_3) + String(bit_4) +  String(bit_5);
}


void debuging()
{
Serial.println("Divider A attenuation = " + String(a) + "dB");
Serial.println("Divider B attenuation = " + String(b) + "dB");
Serial.println("Divider C attenuation = " + String(c) + "dB");
Serial.println("Divider D attenuation = " + String(d) + "dB");
//////////////////////////////////////////////////////////////////////////
Serial.println("writting divider A with " + byte_A );
Serial.println("writting divider B with " + byte_B );
Serial.println("writting divider C with " + byte_C );
Serial.println("writting divider D with " + byte_D );
}

void loop()
{
 delay(1000000000) ;  // do nothing here
}
