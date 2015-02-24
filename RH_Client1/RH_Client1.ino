//Client Program
// I/O PINs available for Relays are : 0, 1, 3, 4, 5, 6, 7, 9 (8 PINs)

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>
#include "DHT.h"

#define SERVER_ADDRESS 1
#define CLIENT1_ADDRESS 2
#define CLIENT2_ADDRESS 3
#define CLIENT3_ADDRESS 4
#define CLIENT4_ADDRESS 5
#define CLIENT5_ADDRESS 6
#define CLIENT6_ADDRESS 7
#define CLIENT7_ADDRESS 8
#define CLIENT8_ADDRESS 9
#define CLIENT9_ADDRESS 10

#define DHTPIN 2
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
RH_NRF24 driver;

RHReliableDatagram manager(driver, CLIENT1_ADDRESS);
int A = 3;
int B = 4;
int C = 5;
int D = 6;
int s;

void setup()
{
	Serial.begin(9600);

	pinMode(A, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(C, OUTPUT);
	pinMode(D, OUTPUT);

	if (!manager.init())
	{
	}	
	// Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

void loop()
{ 
	s = 0;
	if (manager.available())
	{
		uint8_t len = sizeof(buf);
		uint8_t from;

		if (manager.recvfromAck(buf, &len, &from))
		{
			if (buf[0] == '1')
			{
				Serial.println((char*)buf);

				if (buf[1] == '1')
				{
					digitalWrite(A, HIGH);
				}
				else if(buf[1] == '0')
				{
					digitalWrite(A, LOW);
				}
				else
				{
					Serial.println("ERROR: Invalid A state from server");
					s = 1;
				}

				if (buf[2] == '1')
				{
					digitalWrite(B, HIGH);
				}
				else if (buf[2] == '0')
				{
					digitalWrite(B, LOW);
				}
				else
				{
					Serial.println("ERROR: Invalid B state from server");
					s = 1;
				}

				if (buf[3] == '1')
				{
					digitalWrite(C, HIGH);
				}
				else if (buf[3] == '0')
				{
					digitalWrite(C, LOW);
				}
				else
				{
					Serial.println("ERROR: Invalid C state from server");
					s = 1;
				}

				if (buf[4] == '1')
				{
					digitalWrite(D, HIGH);
				}
				else if (buf[4] == '0')
				{
					digitalWrite(D, LOW);
				}
				else
				{
					Serial.println("ERROR: Invalid D state from server");
					s = 1;
				}

				if (s == 0)
				{
					float tmp = dht.readTemperature();  // Read temperature as Celsius
					int tempC1 = (int)tmp;
					int tempC2 = (int)(tmp - tempC1) * 100; // For two decimal points
					char data[10];
					sprintf(data, "%i.%i", tempC1, tempC2);
					if (!manager.sendtoWait((uint8_t *)data, sizeof(data), from))
					{
						Serial.println("Failed: cannot send reply to server");
					}
					else
					{
						Serial.println("Success: Reply sent to server.");
					}
				}
				else if (s == 1)
				{
					char err[10] = "E";
					
					manager.sendtoWait((uint8_t *)err, sizeof(err), from);
				}
				
			}
			else
			{
				Serial.println("Wrong ping received");
			}
			
		}
	}
}

