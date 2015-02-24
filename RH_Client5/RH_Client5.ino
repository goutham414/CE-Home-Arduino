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

RHReliableDatagram manager(driver, CLIENT5_ADDRESS);
int red = 3;
int green = 4;

void setup()
{
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	if (!manager.init()){
	}	
	// Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];


void loop()
{
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
	if (manager.available())
	{
		uint8_t len = sizeof(buf);
		uint8_t from;

		if (manager.recvfromAck(buf, &len, &from))
		{
			float tmp = dht.readTemperature();  // Read temperature as Celsius
			int tempC1 = (int)tmp;
			int tempC2 = (int)(tmp - tempC1) * 100; // For two decimal points
			char data[24];
			sprintf(data, "%i.%i", tempC1, tempC2);
			if (!manager.sendtoWait((uint8_t *)data, sizeof(data), from))
			{
				digitalWrite(red, HIGH);
			}
			else
			{
				digitalWrite(green, HIGH);
			}
		}
	}
}

