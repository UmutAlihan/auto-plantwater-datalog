#define CH1 5 // Connect Digital Pin 8 on Arduino to CH1 on Relay Module
#define CH2 6
#define CH3 7 // Connect Digital Pin 7 on Arduino to CH3 on Relay Module
#define CH4 8
#define LED 2

#include <DS3231.h>
#include <SPI.h>
#include <SD.h>
#include <string.h>

DS3231 rtc(SDA, SCL);  // Init the DS3231 using the hardware interface
File logfile;

int countl = 1;   //counters for logfile.txt
int counth = 1;
char *strTime;
char *open_Time;
char *close_Time;

void setup()
{
  pin_ayarla();
  rtc.begin();
  Serial.begin(9600);
  sd_ayarla();

}

void loop()
{

strTime = rtc.getTimeStr(FORMAT_SHORT);
if(strcmp(strTime, open_Time) == 0)
{
	digitalWrite(CH1,HIGH);
	logla(1);
}
if(strcmp(strTime, close_Time) == 0)
{
	digitalWrite(CH1, LOW);
	logla(0);
}
}


void logla(int a)
{
	//open file for logging and log
	logfile = SD.open("logfile.txt", FILE_WRITE);
	if(logfile)
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
		if(a == 1)
		{
			logfile.println("HIGH\n");
		}
		else if(a == 0)
		{
			logfile.println("LOW\n");
		}
		
	}
	// close the file:
	logfile.close();
	digitalWrite(2,LOW);
	delay(250);
	counth = counth + 1;
	Serial.print("done.\n\n");
	return;
}

void pin_ayarla()
{
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
}

void sd_ayarla()
{
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