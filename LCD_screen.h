class LCD_Screen{
  public:
    LCD_Screen(){}
    
    void initialize_class(int new_RS, int new_RW, int new_E, int* new_DB){
      RS_Pin = new_RS;
      RW_Pin = new_RW;
      E_Pin = new_E;
      line_number = 0;
      column_number = 0;
      inc_dec = 1;
      for(int i  = 0; i < 4; i++){
        DB_Pins[i] = new_DB[i];
        }
    }

    void set_data_lines(int data){
      for(int i = 0; i < 4; i++){
//        if(data & (B0001 << i)){
//          digitalWrite(DB_Pins[i],HIGH);
//          }
//        else{
//          digitalWrite(DB_Pins[i],LOW);
//          }
//        }
        digitalWrite(DB_Pins[i],(data & (B0001 << i)));
      }
    }

    void set_data_lines(int* data_array){
      for(int i = 0; i < 4; i++){
//        if(data_array[i]){
//          digitalWrite(DB_Pins[i],HIGH);
//          }
//        else{
//          digitalWrite(DB_Pins[i],LOW);
//          }
          digitalWrite(DB_Pins[i],data_array[i]);
        }
      }
    void setRSRW(int RS_value, int RW_value){
//      if(RS_value
//      digitalWrite(RS_pin,
//      }
      digitalWrite(RS_Pin, RS_value);
      digitalWrite(RW_Pin, RW_value);
    }

    void pulseEnable(){
      digitalWrite(E_Pin,HIGH);
      delay(5);
      digitalWrite(E_Pin,LOW);
      delay(5);
    }


    void initialize_device(){
      delay(50);
      setRSRW(0,0);
      set_data_lines(B0011);
      pulseEnable(); //first function set
      delay(5);
      pulseEnable(); //second function set
      delay(5);
      pulseEnable();//third function set

      //block1
      set_data_lines(B0010); 
      pulseEnable(); 
      
      //block2
      set_data_lines(B0010); //not strictly necessary but reads clearer
      pulseEnable();
      set_data_lines(B1000); //nf
      pulseEnable(); 
      
      set_data_lines(B0000);
      pulseEnable();
      set_data_lines(B1000);
      pulseEnable();
      
      set_data_lines(B0000);
      pulseEnable();
      set_data_lines(B0001);
      pulseEnable();
      
      set_data_lines(B0000);
      pulseEnable();
      set_data_lines(B0110); //0 1 ID=1 S=0
      pulseEnable();
      delay(10);
      }

    void send_command(int RS_value, int RW_value, char data){
      setRSRW(RS_value,RW_value);
      set_data_lines(data >> 4);
      pulseEnable();
      set_data_lines(data & B00001111);
      pulseEnable();
      }

    void set_display(int display_value, int cursor_value, int blink_value){
      char data_value;

      display_on = display_value;
      cursor_on = cursor_value;
      blink_on = blink_value;
      data_value = B00001000+(display_value << 2) + (cursor_value << 1) + (blink_value);
      send_command(0,0,data_value);
      }

    void clear_display(){
      send_command(0,0,B00000001);
      }

    void return_home(){
      send_command(0,0,B00000010);
      line_number = 0;
      column_number = 0;
      }

    void toggle_IncDec(){
      char data_value;
      if(inc_dec){
        inc_dec = false;
        data_value = B00000100 + (inc_dec << 1) + shift;
        send_command(0,0,data_value);
        }
      else{
        inc_dec = true;
        data_value = B00000100 + (inc_dec << 1) + shift;
        send_command(0,0,data_value);
        }
      }

    void toggle_shift(){
      char data_value;
      if(shift){
        shift = false;
        data_value = B00000100 + (inc_dec << 1) + shift;
        send_command(0,0,data_value);
        }
      else{
        shift = true;
        data_value = B00000100 + (inc_dec << 1) + shift;
        send_command(0,0,data_value);
        }
      }

    void print_char(char to_print){
      send_command(1,0,to_print);
      trackCursor(inc_dec);
      }

    void print_message(char* to_print){
      int i = 0;
      //Serial.println("lmao");
      //Serial.println(i);
      //Serial.println(to_print[0]);
      while(to_print[i] != '\0'){
        //Serial.println(i);
        print_char(to_print[i]);
        i++;
        }
      }

    void shift_cursor(int rightNotLeft){
      char data_value;
      data_value = B00010000 + (rightNotLeft<<2);
      send_command(0,0,data_value);
      trackCursor(rightNotLeft);
      //delay(500);
      }

    void shift_display(int rightNotLeft){
      char data_value;
      data_value = B00010000 + B00001000 + (rightNotLeft<<2);
      send_command(0,0,data_value);
      }

    bool set_cursor(int new_line, int new_col){
      if((new_col > 40) || (new_col < 0) || (new_line < 0) || (new_line > 1)){
        return false;
        }
      if(new_line > line_number){
        while(new_line > line_number){
          shift_cursor(1);
          }
        }
      else if(new_line < line_number){
        while(new_line < line_number){
          shift_cursor(0);
          }
        }
      if(new_col > column_number){
        while(new_col > column_number){
          shift_cursor(1);
          }
        }
      else{
        while(new_col < column_number){
          shift_cursor(0);
          }
        }
      }

    void print_message_at(char* to_print, int new_line, int new_col){
        set_cursor(new_line,new_col);
        print_message(to_print);
      }
      
  private:
    int RS_Pin;
    int RW_Pin;
    int E_Pin;
    int DB_Pins[4];
    int line_number;
    int column_number;
    bool display_on;
    bool blink_on;
    bool cursor_on;
    bool inc_dec; //high means cursor increments, low means cursor decrements
    bool shift; //high means display shift

    
    void trackCursor(bool incOrDec){
      /*Serial.println("line_number");
      Serial.println(line_number);
      Serial.println("col number");
      Serial.println(column_number);
      Serial.println("inc or dec");
      Serial.println(incOrDec);*/
      if(incOrDec){
        column_number++;
        }
      else{
        column_number--;
        }
      if(column_number > 40){ //if reach end of column
          if(line_number == 0){ //if on line 0, cursor moves one line down
            line_number = 1;
            column_number -= 40;
            }
          else{
            column_number = 40;
            }
          }
      else if(column_number < 0){
        if(line_number == 1){ //if on line 1, cursor moves one line up
            line_number = 0;
            column_number += 40;
            }
          else{
            column_number = 0;
            }
        }
      }
    
  };