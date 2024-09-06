#define TSL1401_CLK 3 //  test pin
#define TSL1401_SI 4 //  test pin

void read_TSL1401_camera(void)
{
  digitalWrite(TSL1401_CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(TSL1401_CLK, LOW);
  delayMicroseconds(1);

  digitalWrite(TSL1401_SI, HIGH);
  delayMicroseconds(1);
  digitalWrite(TSL1401_SI, LOW);
  delayMicroseconds(1);

  for(int i =0; i< 128; i++)
  {
  digitalWrite(TSL1401_CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(TSL1401_CLK, LOW);
  delayMicroseconds(1);
  }
}


void setup() 
{
  // put your setup code here, to run once:
  pinMode(TSL1401_CLK, OUTPUT);
  pinMode(TSL1401_SI, OUTPUT);


}

void loop() 
{
  // put your main code here, to run repeatedly:
  read_TSL1401_camera();
  delay(5);
}
