#include <Wire.h>

uint8_t ADDR = 0x70;
 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
}
 
 
void loop()
{
  print_bin(get_ir_sensor_value());

  delay(100);
}

void print_bin(int var) {
  for (unsigned int test = 0x8000; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
  Serial.println();
}

uint16_t get_ir_sensor_value()
{
  uint8_t WRITEVALS[] = {0x00, 0x08};
  
  int i;
  uint16_t value;
  uint8_t readvals[2];
  
  // Write correct data before reading
  Wire.beginTransmission(ADDR);
  for(i=0; i<2; i++)
  {
    Wire.write(WRITEVALS[i]);
  }
  Wire.endTransmission();

  // Get data
  Wire.requestFrom(ADDR, 2);
  i = 0;
  while(Wire.available())
  {
    readvals[i] = Wire.read();
    i++;
  }

  value = (readvals[0] << 8) + readvals[1];

  return(value);
}
