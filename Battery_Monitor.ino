double voltage;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  voltage = analogRead(A1)*3.5/1023*7.1/5.6;
  Serial.println(voltage);
}
