#include <Servo.h>
#include <RTClib.h>
#include <IRremote.h>
#define IR_RECEIVE_PIN 5
#define IR_BUTTON_1 12
#define IR_BUTTON_2 24
#define IR_BUTTON_3 94
#define IR_BUTTON_4 8
#define IR_BUTTON_5 28
#define IR_BUTTON_6 90
#define IR_BUTTON_7 66
#define IR_BUTTON_8 82
#define IR_BUTTON_9 74
#define IR_BUTTON_0 22
#define IR_BUTTON_POWER 69

Servo servo;
RTC_DS3231 rtc;

int buzzerPin = 7;
int button = 6;
int masterButton = 4;

int angle = 0;
int musicCounter = 0;
int time = 0;

int scheduledTimeHour[10];
int scheduledTimeMinute[10];


void MasterRemote(int command) {
  switch (command) {
    case IR_BUTTON_0:
      servo.write(0);
      break;
    case IR_BUTTON_1:
      servo.write(25);
      break;
    case IR_BUTTON_2:
      servo.write(57);
      break;
    case IR_BUTTON_3:
      servo.write(78);
      break;
    case IR_BUTTON_4:
      servo.write(110);
      break;
    case IR_BUTTON_5:
      servo.write(135);
      break;
    case IR_BUTTON_6:
      servo.write(160);
      break;
    case IR_BUTTON_7:
      servo.write(270);
      break;
    default:
      break;
  }
}

void PlayMusic() {
  switch (musicCounter) {
    case 0:
      tone(buzzerPin, 349.23, 1000);  // F4
      break;
    case 1:
      tone(buzzerPin, 440, 1000);  // A4
      break;
    case 2:
      tone(buzzerPin, 392, 1000);  // G4
      break;
    case 3:
      tone(buzzerPin, 261.63, 2000);  // C4
      break;
    case 5:
      tone(buzzerPin, 349.23, 1000);  // F4
      break;
    case 6:
      tone(buzzerPin, 392, 1000);  // G4
      break;
    case 7:
      tone(buzzerPin, 440, 1000);  // A4
      break;
    case 8:
      tone(buzzerPin, 349.23, 2000);  // F4
      break;
    case 10:
      tone(buzzerPin, 440, 1000);  // A4
      break;
    case 11:
      tone(buzzerPin, 349.23, 1000);  // F4
      break;
    case 12:
      tone(buzzerPin, 392, 1000);  // G4
      break;
    case 13:
      tone(buzzerPin, 261.63, 2000);  // C4
      break;
    case 15:
      tone(buzzerPin, 261.63, 1000);  // C4
      break;
    case 16:
      tone(buzzerPin, 392, 1000);  // G4
      break;
    case 17:
      tone(buzzerPin, 440, 1000);  // A4
      break;
    case 18:
      tone(buzzerPin, 349.23, 2000);  // F4
      break;
    case 20:
      noTone(buzzerPin);
      musicCounter = -1;
    default:
      break;
  }
}

enum hardware_States { H_INIT,
                       H_Idle,
                       H_TimeT,
                       H_Buzz } h_state;

void H_Tick() {
  DateTime rtcTime = rtc.now();
  switch (h_state) {
    case H_INIT:
      h_state = H_Idle;
      break;
    case H_Idle:
      // for(int i = 0; i < 10; ++i)
      // {
      //   if(rtcTime.hour() == scheduledTimeHour[i] && rtcTime.minute() == scheduledTimeMinute[i] && rtcTime.second() == 0)
      //   {
      //     h_state = H_TimeT;
      //   }
      // }
      if (rtcTime.second() == 0) {
        h_state = H_TimeT;
      } else {
        h_state = H_Idle;
      }
      break;
  }
  switch (h_state) {
    case H_INIT:
      break;
    case H_Idle:
      break;
    case H_TimeT:
      h_state = H_Buzz;
      switch (rtcTime.dayOfTheWeek()) {
        case 0:
          servo.write(25);
          break;
        case 1:
          servo.write(57);
          break;
        case 2:
          servo.write(78);
          break;
        case 3:
          servo.write(110);
          break;
        case 4:
          servo.write(135);
          break;
        case 5:
          servo.write(160);
          break;
        case 6:
          servo.write(270);
          break;
        default:
          break;
      }
      break;
    case H_Buzz:
      PlayMusic();
      musicCounter = musicCounter + 1;
      if (digitalRead(button) == HIGH) {
        h_state = H_Idle;
        servo.write(0);
        musicCounter = 0;
        rtc.adjust(DateTime(rtcTime.year(), rtcTime.month(), rtcTime.day() + 1, rtcTime.twelveHour(), rtcTime.minute(), rtcTime.second())); //Will not adjust rtc in real enviornment, just for demo purposes
      }
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(9600);
  servo.attach(8);
  servo.write(angle);
  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin, 1000, 2000);
  rtc.begin();
  IrReceiver.begin(IR_RECEIVE_PIN);
  rtc.adjust(DateTime(2023, 5, 1, 12, 0, 0));
  h_state = H_INIT;
}
void loop() {

    H_Tick();
    delay(1000);

  if(digitalRead(masterButton) == HIGH)
  {
    bool done = false;
    bool wait = true;
    IrReceiver.begin(IR_RECEIVE_PIN);
    while(!done)
    {
      if (IrReceiver.decode()) {
       int command = IrReceiver.decodedIRData.command;
       Serial.println(command);
       MasterRemote(command);
       IrReceiver.resume();
      }
      if(wait && digitalRead(masterButton) == LOW)
      {
        wait = false;
      }
      if(!wait && digitalRead(masterButton) == HIGH)
      {
        done = true;
      }
    }
  }

  //Serial.println(h_state);

  DateTime rtcTime = rtc.now();

  int ss = rtcTime.second();
  int mm = rtcTime.minute();
  int hh = rtcTime.twelveHour();
  int DD = rtcTime.dayOfTheWeek();
  int dd = rtcTime.day();
  int MM = rtcTime.month();
  int yyyy = rtcTime.year();

  Serial.print(MM);
  Serial.print("/");
  Serial.print(dd);
  Serial.print("/");
  Serial.print(yyyy);
  Serial.print(" ");
  Serial.print(DD);
  Serial.print(" ");
  Serial.print(hh);
  Serial.print(":");
  Serial.print(mm);
  Serial.print(":");
  Serial.print(ss);
  Serial.print("\n");
}

//References for servo motor and RTC
//Gotten from research online

// scan from 0 to 180 degrees
// for(angle = 0; angle < 200; angle++)
// {
//   servo.write(angle);
//   delay(15);
// }
// // now scan back from 180 to 0 degrees
// for(angle = 200; angle > 0; angle--)
// {
//   servo.write(angle);
//   delay(15);
// }
// DateTime rtcTime = rtc.now();

// int ss = rtcTime.second();
// int mm = rtcTime.minute();
// int hh = rtcTime.twelveHour();
// int DD = rtcTime.dayOfTheWeek();
// int dd = rtcTime.day();
// int MM = rtcTime.month();
// int yyyy = rtcTime.year();

// Serial.print(MM);
// Serial.print("/");
// Serial.print(dd);
// Serial.print("/");
// Serial.print(yyyy);
// Serial.print(" ");
// Serial.print(DD);
// Serial.print(" ");
// Serial.print(hh);
// Serial.print(":");
// Serial.print(mm);
// Serial.print(":");
// Serial.print(ss);
// Serial.print("\n");
// delay(1000);