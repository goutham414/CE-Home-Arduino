//Client Program
// I/O PINs available for Relays are : 0, 1, 3, 4, 5, 6, 7, 9 (8 PINs)

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>
#include "DHT.h"

#define SERVER_ADDRESS 1
#define CLIENT1_ADDRESS 2
#define CLIENT2_ADDRESS 3
#define DHTPIN 2
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
RH_NRF24 driver;

RHReliableDatagram manager(driver, CLIENT1_ADDRESS); 

void setup() 
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];


void loop()
{
  //Serial.print("OK");
  if (manager.available())
  {
    uint8_t len = sizeof(buf);
    uint8_t from;
    
    if (manager.recvfromAck(buf, &len, &from))
    {
      Serial.print("got request from : 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);
      
      
            
      float tmp = dht.readTemperature();  // Read temperature as Celsius
	  int tempC1 = (int)tmp;
	  int tempC2 = (int)(tmp - tempC1) * 100; // For two decimal points
	  char data[24] ;
	  sprintf(data, "%i.%i", tempC1, tempC2);
      
	  Serial.println(data);
      // Send a reply back to the originator client
      //uint8_t data[] = "Hi One";
	  if (!manager.sendtoWait((uint8_t *)data, sizeof(data), from))
        Serial.println("sendtoWait failed");
	 
    }
  }
}

