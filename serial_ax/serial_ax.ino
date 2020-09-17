void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  char strout[2] = {' ','X'};
  char incomingByte; 
  if(Serial.available()){
    incomingByte = Serial.read();
    strout[0] = incomingByte;
    Serial.println(strout);
    }
}
