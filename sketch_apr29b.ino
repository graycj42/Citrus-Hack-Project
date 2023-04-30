#include <RTClib.h>

enum menu_states{Idle, Password, Control, Open_Container, Set_Pass, Clock_Setup, Set_Time, Set_Alarm} 

menu_states curr_states;

int last_press; 
Password Pass;
string pass_entry;
int scheduledTimeHour[10];
int scheduledTimeMin[10];
int curr_alarm = 1;
String pw = "";
String curr_button;
RTC_DS3231 rtc;
DateTime date = rtc.now();


void menu_tick(){
  date = rtc.now();
  switch(curr_states){
    case Password:
      if(key_press && pw.length() < 4){
        pw += curr_button;
      }
      if(last_press > 5 || exit_button){
        curr_states = Idle;
        pw = "";
      }
      if(pass.attemptlogin(pw)){
        curr_state = Control;
        pw = "";
      }
    case Control:
      if(last_press > 5){
        curr_states = Idle;
      }
      if(open_button){
        curr_state = Open_Container;
        open_button = false;
      }
      if(pw_button){
        curr_states = Set_Password;
        pw_button = false;
      }
      if(clock_button){
        curr_states = Clock_Setup;
        clock_button = false;
      }
    case Open_Container:
      if(last_press > 5){
        curr_states = Idle;
      }
      if(Exit_Button){
        curr_states = Control;
        Exit_Button = false;
      }
    case Set_Password:
      if(last_press > 5){
        curr_states = Idle;
        pw = "";
        num_entered = 0;
      }
      if(button_press && pw.length() < 4){
        pw += curr_button;
      }
      if(confirm_button && pw.length() > 3){
        pass.setSavePassword(pw);
        pw = "";
        curr_state = Control;
      }
    case Clock_Setup:
      if(last_press > 5){
        curr_state = Idle;
      }
      if(set_alarm_button){
        curr_state = Set_Alarm;
        set_alarm_button = false;
      }
      if(set_time_button){
        curr_state = Set_Time;
        set_time_button = false;
      }
    case Set_Alarm:
      if(last_press > 5){
        curr_state = Idle;
      }
      if(confirm_button){
        curr_state = Clock_Setup;
        confirm_button = false;
      }
      if(hour_up){
        scheduledTimeHour[curr_alarm]++;
        curr_state = Set_Alarm;
      }
      if(hour_down){
        scheduledTimeHour[curr_alarm]--;
        curr_state = Set_Alarm;
        hour_down = false;
      }
      if(min_up){
        scheduledTimeMin[curr_alarm]++;
        curr_state = Set_Alarm;
        min_up = false;
      }
      if(min_down){
        scheduledTimeMin[curr_alarm]--;
        curr_state = Set_Alarm;
      }
      if(next_alarm && curr_alarm < 10){
        curr_alarm++;
      }
      if(next_alarm && curr_alarm > 1){
        curr_alarm--;
      }
    case Set_Time:
      if(last_press > 5){
        curr_state = Idle;
      }
      if(confirm_button){
        curr_state = Control;
        confirm_button = false;
      }
      if(hour_up){
        rtc.adjust(DateTime(date.year(), date.month(), date.day(), date.hour()++, date.minute()));
        hour_up = false;
        curr_state = Set_Alarm;
      }
      if(hour_down){
        rtc.adjust(DateTime(date.year(), date.month(), date.day(), date.hour()--, date.minute()));
        curr_state = Set_Alarm;
        hour_down = false;
      }
      if(min_up){
        rtc.adjust(DateTime(date.year(), date.month(), date.day(), date.hour(), date.minute()++));
        curr_state = Set_Alarm;
        min_up = false;
      }
      if(min_down){
        rtc.adjust(DateTime(date.year(), date.month(), date.day(), date.hour(), date.minute()--));
        curr_state = Set_Alarm;
      }

  }

  switch(curr_state){
    case Password:
      //password_menu.print();
      //check for button presses
      
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
