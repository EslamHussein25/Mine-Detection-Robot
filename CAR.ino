#include <SoftwareSerial.h>


#define MOTOR1A  2
#define MOTOR1B  3

#define MOTOR2A  4
#define MOTOR2B  5

#define RX       8
#define TX       7

#define Detect   9
#define Start    10
//SD CARD 
#define MOSI  11
#define MISO  12
#define SCK   13 

#define Fan      A2


int counter = 0 ; 



SoftwareSerial BlueCtrl(RX, TX); // rx with 8  and  tx with 7 


void Forword();
void RIGHT();
void LEFT();
void BACK();
void STOP();
void BREAK();


char Bluetoothdata; // to read the data from bluetooth 
float Temp = 0 ;
String GPSDATA ;
int Distance = 0;
bool StopFlag = true ;

void setup() 
{
  //Mine Detection pins 
pinMode(Detect , INPUT); // if detect mine // and this pin of the mine 
pinMode(Start , OUTPUT); // send signel to node to send the location of the mine 
pinMode(Fan , OUTPUT);  
pinMode(TRIG , OUTPUT);
pinMode(ECHO , INPUT);
digitalWrite(Fan , LOW);

  //motor 1 , 2 
pinMode(MOTOR1A , OUTPUT);
pinMode(MOTOR1B , OUTPUT);

 // motor 3 , 4
pinMode(MOTOR2A , OUTPUT);
pinMode(MOTOR2B , OUTPUT);
Serial.begin(9600);
BlueCtrl.begin(9600); // buad rate and start communication between arduino and bluetooth 
//NodeData.begin(9600);
RTDSensor.begin();
SD.begin();
delay(10);
Serial.println("Hello");
}

void loop() 
{

//LM35
/*
Temp = analogRead(A1);
  Temp = Temp * 0.48828125;
  if(Temp >= 40)
  {
     digitalWrite(Fan , HIGH); 
  }
  else 
  {
     digitalWrite(Fan , LOW);
  }
*/
// Distance = UltrRead();//30 CM 

  if(BlueCtrl.available())
  {
    Bluetoothdata = BlueCtrl.read();
    if(Bluetoothdata == 'F')
    {
      Serial.println('f');
	  Forword();
     
    }
    else if (Bluetoothdata == 'B')
    {
       Serial.println('b');
        BACK();
    }
    else if (Bluetoothdata == 'L')
    {
       Serial.println('l');
       LEFT();
    }
    else if (Bluetoothdata == 'R')
    {
      RIGHT();
    }
    else if (Bluetoothdata == 'S')
    {
      Serial.println('s');
      STOP();
    }
  }

  if(digitalRead(Detect) == HIGH)
  {
      digitalWrite(Start , HIGH);
      delay(10);
  }
  else if(digitalRead(Detect) == LOW )
  {
    digitalWrite(Start , LOW);
  }
}


void Forword()
{
    digitalWrite(MOTOR1A ,LOW); 
    digitalWrite(MOTOR1B ,HIGH);   
    digitalWrite(MOTOR2A ,LOW);
    digitalWrite(MOTOR2B ,HIGH);
}

void RIGHT()
{
    digitalWrite(MOTOR1A ,HIGH); 
    digitalWrite(MOTOR1B ,LOW);
    digitalWrite(MOTOR2A ,LOW);
    digitalWrite(MOTOR2B ,HIGH);
}

void LEFT()
{
    digitalWrite(MOTOR1A ,LOW); 
    digitalWrite(MOTOR1B ,HIGH);
    digitalWrite(MOTOR2A ,HIGH);
    digitalWrite(MOTOR2B ,LOW);
}

void BACK()
{
    digitalWrite(MOTOR1A ,HIGH); 
    digitalWrite(MOTOR1B ,LOW);
    digitalWrite(MOTOR2A ,HIGH);
    digitalWrite(MOTOR2B ,LOW);
}

void STOP()
{
    digitalWrite(MOTOR1A ,LOW); 
    digitalWrite(MOTOR1B ,LOW);
    digitalWrite(MOTOR2A ,LOW);
    digitalWrite(MOTOR2B ,LOW);
}

void BREAK()
{
    digitalWrite(MOTOR1A ,HIGH); 
    digitalWrite(MOTOR1B ,HIGH);
    digitalWrite(MOTOR2A ,HIGH);
    digitalWrite(MOTOR2B ,HIGH);
}






