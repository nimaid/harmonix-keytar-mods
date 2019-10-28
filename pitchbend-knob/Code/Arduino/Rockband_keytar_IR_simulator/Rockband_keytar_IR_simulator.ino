// Works but is not fast enough...

#include <Wire.h>

uint8_t ADDR = 0x70;

bool respond = false;
 
void setup()
{
  Wire.begin(ADDR);
  Wire.onReceive(process_recieve);
  Wire.onRequest(process_request);
}
 
 
void loop()
{
  
}


void process_request()
{
  if(respond)
  {
    uint8_t writevals[10];

    writevals[0] = 0b00001000;
    writevals[1] = 0b00000000;
    
    Wire.write(writevals, 2);
  }

  respond = false;
}


void process_recieve(int num_bytes)
{
  int i;
  uint8_t readvals[2];

  // Get data
  i = 0;
  while(Wire.available())
  {
    readvals[i] = Wire.read();
    i++;
  }

  if((readvals[0] == 0x00) && (readvals[1] == 0x08))
  {
    respond = true;
  }
}
