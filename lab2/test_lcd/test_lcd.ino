#include "C:\Users\owins\Documents\473_GSI\LCD_screen.h"

char line1[] = "ARDUINO RULES!"; //13 chars
char line2_1[] = "Roomba!       "; //14 chars
char line2_2[] = "BLE 4ever     ";//14 chars 

LCD_Screen lcd;
  
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(2,OUTPUT);
  int data_pins[4] = {A3,A2,A1,A0};
  lcd.initialize_class(A4,A5,2,data_pins);

  lcd.initialize_device();
  lcd.clear_display();
  lcd.return_home();
  lcd.set_display(1,1,0);
  lcd.print_message_at(line1,0,0);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
    lcd.print_message_at(line2_1,1,0);
    delay(2000);
    lcd.print_message_at(line2_2,1,0);
    delay(2000);
    
//    lcd.set_data_lines(0xFF);
//    lcd.set_data_lines(0x00);
//    lcd.pulseEnable();
//    lcd.setRSRW(0,0);
//    lcd.setRSRW(1,1);

}
