#define A0pin A0           
#define SIpin 23           
#define CLKpin 22       
#define NPIXELS 128 
#define FASTADC 1    
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))  
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

byte Pixel[NPIXELS];   
byte Threshold_Data[NPIXELS];

int LineSensor_Data[NPIXELS];
int LineSensor_Data_Adaption[NPIXELS];
int MAX_LineSensor_Data[NPIXELS];
int MIN_LineSensor_Data[NPIXELS];
int flag_line_adapation;  

void setup()
{
  int i;
  for (i = 0; i < NPIXELS; ++i)
  {
    LineSensor_Data[i] = 0;          
    LineSensor_Data_Adaption[i] = 0;  
    MAX_LineSensor_Data[i] = 1023;   
    MIN_LineSensor_Data[i] = 0;      
  }
  pinMode(SIpin, OUTPUT); 
  pinMode(CLKpin, OUTPUT); 
  pinMode(A0pin, INPUT);   

  digitalWrite(SIpin, LOW); 
  digitalWrite(CLKpin, LOW);

#if FASTADC
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
#endif

  flag_line_adapation = 0;

  Serial.begin(115200);    
  Serial.println("TSL1401"); 

void threshold_line_image(int threshold_value)
{
  for (int i = 0; i < NPIXELS; ++i)
  {
    if (Pixel[i] >= threshold_value)
    {
      Threshold_Data[i] = 255;
    }
    else
    {
      Threshold_Data[i] = 0;  
    }
  }
}

void read_line_camera(void)
{
  int i;
  delay(1); 

  digitalWrite(CLKpin, LOW); 
  digitalWrite(SIpin, HIGH);  
  digitalWrite(CLKpin, HIGH); 
  digitalWrite(SIpin, LOW);   
  delayMicroseconds(1);      

  for (i = 0; i < NPIXELS; ++i)
  {
    Pixel[i] = analogRead(A0pin) / 4; 
    digitalWrite(CLKpin, LOW);     
    delayMicroseconds(1);         
    digitalWrite(CLKpin, HIGH);      
  }
  digitalWrite(CLKpin, LOW); 
}

double line_COM(void)
{
  double COM = 0.0; 
  double mass_sum = 0.0;  
  for (int i = 0; i < NPIXELS; ++i)
  {
    mass_sum += Threshold_Data[i]; 
    COM += Threshold_Data[i] * i;
  }

  if (mass_sum == 0)
  {
    return -1;
  }

  COM = COM / mass_sum; 

  return COM; 
}

void loop()
{
  double cx = 0;
  read_line_camera();        
  threshold_line_image(150);  
  cx = line_COM();          

  for (int i = 0; i < NPIXELS; i++)
  {
    Serial.print(Pixel[i]);                
    Serial.print(",");                   
    Serial.print(Threshold_Data[i]); 
    Serial.print(",");                       
    Serial.print((i == (int)cx) ? 255 : 0);
    Serial.println();                     
  }
  delay(100);
}
