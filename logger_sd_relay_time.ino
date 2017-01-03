#define CH1 5 // Connect Digital Pin 8 on Arduino to CH1 on Relay Module
#define CH2 6
#define CH3 7 // Connect Digital Pin 7 on Arduino to CH3 on Relay Module
#define CH4 8
#define LED 2

#include <DS3231.h>
#include <SPI.h>
#include <SD.h>

DS3231 rtc(SDA, SCL);  // Init the DS3231 using the hardware interface
File logfile;

  int countl = 1;   //counters for logfile.txt
  int counth = 1;

 void setup(){
 //Setup all the Arduino Pins
   pinMode(CH1, OUTPUT);
   pinMode(CH2, OUTPUT);
   pinMode(CH3, OUTPUT);
   pinMode(CH4, OUTPUT);
   pinMode(LED, OUTPUT);   //for the led which blinks during sd-write
   
   digitalWrite(CH1, LOW);
   digitalWrite(CH2, LOW);
   digitalWrite(CH3, LOW);
   digitalWrite(CH4, LOW);
   delay(1000); //Wait 2 seconds before starting sequence

   rtc.begin();  //Initialize the rtc object
 
 //Setup SD module and Initialize SDCard   
   Serial.begin(9600);
     while(!Serial) 
     {
       ;
     }
    Serial.print("Initializing SD Card...\n");
    
    if (!SD.begin(4))
    {
      Serial.println("Initialization failed!\n");
      return;
    }
    else
    {
      Serial.println("Initialization done.\n");
    }
    
 //opens or create a file for logging and closes it
    if(logfile = SD.open("logfile.txt", FILE_WRITE))
    {
     Serial.print("Logfile is open and ready for the action.\n");
    }
   else
    {
     Serial.print("Error on file openning!\n"); 
    }
    logfile.close();
 }
  
  
  
  void loop(){
//define the bridge between SD and Relay module inetraction
  boolean bridge = false;
 
//does something with relay and instantly logs it to the SD Card by including real time with DS3231! (also lights the led up) 
  //change the relay
  digitalWrite(CH1, HIGH);
  bridge = true;
  if(bridge)
  {
  //open and write to the file
    logfile = SD.open("logfile.txt", FILE_WRITE);
    if (logfile) 
    {
      digitalWrite(2, HIGH);
      Serial.println("Logging...\n");
      delay(100);
      logfile.print(counth, DEC);
      logfile.print(rtc.getDOWStr());
      logfile.print(" - ");
      logfile.print(rtc.getDateStr());
      logfile.print(" -- ");
      logfile.print(rtc.getTimeStr());
      logfile.print(" -> ");
      logfile.println("High\n");
      delay(250);  //wait so that all write process completely done
    
      // close the file:
      logfile.close();
      digitalWrite(2,LOW);
      delay(250);
      counth = counth + 1;
      Serial.print("done.\n\n");
      
      bridge = false;
    }
  }
  
  delay(4650);

  
  //change the relay
  digitalWrite(CH1, LOW);
  bridge = true;
  if(bridge)
  {
  //open and write to the file
    logfile = SD.open("logfile.txt", FILE_WRITE);
    if (logfile) 
    {
      digitalWrite(2, HIGH);
      Serial.println("Logging...\n");
      delay(100);
      logfile.print(countl, DEC);
      logfile.print(rtc.getDOWStr());
      logfile.print(" - ");
      logfile.print(rtc.getDateStr());
      logfile.print(" -- ");
      logfile.print(rtc.getTimeStr());
      logfile.print(" -> ");
      logfile.print("Low\n");
      delay(250);
    
      // close the file:
      logfile.close();
      digitalWrite(2,LOW);
      delay(250);
      countl = countl + 1;
      Serial.print("done.\n");
      
      bridge = false;
    }
  }
  delay(4650);
  logfile.print("\n\n");
  }
