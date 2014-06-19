/******************** RDM8800 *************************
This vesion source code of RDM8800 firmware reads Singapore's EZLink cards.
They use 13.56MHZ RFID Tag type ISO 14443 Type B[1] / CEPAS protocol.

From the original source code written by Stan Lee(Lizq@iteadstudio.com).

When a card is detected it returns as a comma seperated list of text fields.
They are the card number, balance, number of days since 1995-01-01 to expire 
and number of days since 1995-01-01 created.

So for example:

Presenting a card will return:

1000130019390060,8.38,9107,6915

Which can be broken up into the following comma seperated fields:

Number: 1000130019390060
Balance: 8.38
Expire days: 9107
Created days: 6915



By Bill - bill@anantya.com                      19/Jun/2014
************************************************************/

#include <PN532Lib.h>
#include <SPI.h>


uint8_t cardDataIn[128];

uint8_t cardDataOut[] = {
  0x01,  // target number (always 1)
  0x90,  // command class 
  0x32,  // INS - read purse
  0x03,  // purse #3
  0x00,  // param 1
  0x00,  // param 2
  0x00,  // LC 
  0x00   // ??
};


const int LED = 3;

#define PN532_CS 10

PN532Lib nfc(PN532_CS);

void setup(void) {
  // setup serial at 9600 baud
  Serial.begin(9600);
  
  // startup the nfc card reader
  nfc.begin();
  nfc.SAMConfig();

  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
}


void loop(void) {
  
  
  // look for EzLink cards
  uint32_t id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443B, PN532_CARDTYPEB);

  // if random tag id number then we have a card
  if (id != 0) {
    // now request the card data
    if ( nfc.dataExchange(cardDataOut, sizeof(cardDataOut), cardDataIn, sizeof(cardDataIn)) ) {
      // if card data found set the LED to on
      digitalWrite(LED,HIGH);

      // send out the card number
      uint8_t i;
      for ( i = 0; i < 8; i ++ ) {
        Serial.print((cardDataIn[8 + i] >> 4) & 0x0F, HEX);
        Serial.print(cardDataIn[8 + i] & 0x0F, HEX);
      }
    
      // send out the balance
      double balance = (cardDataIn[2] <<  16 ) | (cardDataIn[3] << 8 ) | (cardDataIn[4] );
      Serial.print(",");
      Serial.print(balance / 100);

      // send out the expired day count from 1995
      uint32_t expireDays = (cardDataIn[24] << 8 ) | (cardDataIn[25]);
      Serial.print(",");
      Serial.print(expireDays);

      // send out the created days
      uint32_t createDays = (cardDataIn[26] << 8 ) | (cardDataIn[27]);
      Serial.print(",");
      Serial.print(createDays);
  
      // send the end or record cr/lf
      Serial.println("");

      // wait a bit for the LED
      delay(20);
      
      // off LED
      digitalWrite(LED,LOW);
    }
  }
  // loop delay before the next read attempt
  delay(100);
}


