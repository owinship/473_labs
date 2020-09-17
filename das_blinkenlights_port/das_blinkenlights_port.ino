int setBitNumber(int n){
  if(n & B1000){
    return B1000;
    }
  else if(n & B0100){
    return B0100;
    }
  else if(n & B0010){
    return B0010;
    }
  else if(n & B0001){
    return B0001;
    }
  else{
    return B0000;
    }
  }

void setup() {
  // put your setup code here, to run once:
  DDRD = DDRD | B11110000;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  int out = setBitNumber(val >> 6);
  PORTD = out << 4;
}
