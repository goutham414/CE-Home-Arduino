//Server Program

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>

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

RH_NRF24 driver;


// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, SERVER_ADDRESS);
String serialRead = "";
int i;

void setup() 
{
  Serial.begin(9600);  
  if (!manager.init())
  {
    Serial.println("init failed");
  }

  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
}

int a;
// Dont put this on the stack:
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

void loop()
{
  
  a = 0;
  if (Serial.available())
  {
    
    char sRead = Serial.read();
    i = 1;
    if (sRead == 'e')
    {
      //Serial.println(serialRead);
      i = 0;
      if (serialRead[0] == '1')
      {
        a = 1;
      }
      else if (serialRead[0] == '2')
      {
        a = 2;
      }
      else if (serialRead[0] == '3')
      {
        a = 3;
      }
      else
      {
        a = 99;      
      }
      
      //serialRead = "";
      sRead = NULL;

    }

    if (i == 1)
    {
      serialRead.concat(sRead); 
      a = 0;
    }


    if (a == 1)
    {
      a = 0;
      char data[10];
      serialRead.toCharArray(data, 10);
      //Serial.print("Hereis:");
      //Serial.println(data);
      //Serial.println("Pinging..One");
      // Send a message to manager_server
      if (manager.sendtoWait((uint8_t *)data, sizeof(data), CLIENT1_ADDRESS))
      {
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
        {
          /*Serial.print("got reply from : 0x");
          Serial.print(from, HEX);
          Serial.print(": ");
          Serial.println((char*)buf);*/
          if (from == 2)
          {
            if (buf[0] == 'E')
            {
              Serial.write("E1");
            }
            else
            {
              Serial.write((char*)buf);
              Serial.println("");
            }
          }
        }
        else
        {
          Serial.write("1CRE");
        }
      }
      else
      {
        Serial.write("1CCE");
      }
      serialRead = "";      
    }
    if (a == 2)
    {
      a = 0;
      char data[10];
      serialRead.toCharArray(data, 10);
      /*Serial.print("Hereis:");
      Serial.println(data);
      Serial.println("Pinging..Two");    */
      if (manager.sendtoWait((uint8_t *)data, sizeof(data), CLIENT2_ADDRESS))
      {        
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
        {
          /*Serial.print("got reply from : 0x");
           			  Serial.print(from);
           			  Serial.print(": ");
           Serial.println((char*)buf);*/
          if (from == 3)
          {
            if (buf[0] == 'E')
            {
              Serial.write("E2");
            }
            else
            {              
              Serial.write((char*)buf);
              Serial.println("");
            }
          }
        }
        else
        {
          Serial.write("2CRE");
        }
      }
      else
      {
        Serial.write("2CCE");
      }      
      serialRead = "";
    }
    if (a == 3)
    {
      a = 0;
      char data[10];
      serialRead.toCharArray(data, 10);
      /*Serial.println("Hereis:");
      Serial.println(data);		
      Serial.println("Pinging..Tri");	*/	
      if (manager.sendtoWait((uint8_t *)data, sizeof(data), CLIENT3_ADDRESS))
      {						
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
        {
          /*Serial.print("got reply from : 0x");
           				Serial.print(from, HEX);
           				Serial.print(": ");*/
          if (from == 4)
          {
            if (buf[0] == 'E')
            {
              Serial.write("E3");
            }
            else
            {
              Serial.write((char*)buf);
              Serial.println("");
            }
          }
        }
        else
        {
          Serial.write("3CRE");
        }
      }
      else
      {
        Serial.write("3CCE");
      }  
      serialRead = "";    
    }
    if (a == 99)
    {
      serialRead = "";
      Serial.println("Invalid Command !!");
    }
  }
}






