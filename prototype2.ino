#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3);//Pin 9,10 used as Rx and Tx
int sensor=4; //output of PIR sensor connected to pin 7
//int push_switch=6; // push button connected to pin 6
//int buzzer=8; // buzzer connected at pin 8
int sensor_value; //variable to hold sensor value
int sms_count=0;
void setup()
{
pinMode(sensor,INPUT); // configuring pin 7 as Input
//pinMode(push_switch,INPUT); // configuring pin 6 as Input
//pinMode(buzzer,OUTPUT); // configuring pin 8 as OUTPUT
mySerial.begin(9600);
}

void loop()
{
Check_Burglar();// check sensor status
Check_Reset(); // check if alarm reset switch pressed or not
}

void Check_Burglar()
{
sensor_value=digitalRead(sensor); // Reading sensor value from pin 7
if(sensor_value==HIGH) // Checking if PIR sensor output is high
{
  //digitalWrite(buzzer,HIGH); // Activating the buzzer 
  while(sms_count<2) //Number of SMS Alerts to be sent limited at 2
    {  
      SendTextMessage(); // Function to send AT Commands to GSM module
    }
}}

void Check_Reset()
{
//if(digitalRead(push_switch==HIGH))// Checking if pushbutton was press
{
//digitalWrite(buzzer,LOW); // turning OFF the buzzer 
sms_count=0; // Reactivating the SMS Alert
}}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919870736966\"\r"); //Phone no 
  delay(1000);
  mySerial.println("INTRUDER INSIDE THE HOME ");//content of the message
  mySerial.write(0x1a);
  delay(200);
  mySerial.println((char)26);//stopping character
  delay(500);
  sms_count++;
}
