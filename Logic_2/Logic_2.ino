#define pin_test 3


void setup() {
  // put your setup code here, to run once:
  pinMode(pin_test, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(pin_test, HIGH);
  delay(1);
  digitalWrite(pin_test, LOW);
  delay(1);
   
}
