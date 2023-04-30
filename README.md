# Citrus-Hack-Project
Project for Citrus Hack
Authors: [Christopher Gray](https://github.com/graycj42) [Tommy Grounds](https://github.com/PuttyXD) [Connor Claborn] [Iheanyi Kalu-Okere](https://github.com/Ikkoding)
## Project Description
Our group has chosen to build a automatic pill dispensing device to assist users in taking their medication on time. This deice utilizes a servo to automatically open the container so the user can retrieve their medication at a given time set by an rtc module. A passive buzzer chimes to verbally notify the user. An IR receiver is fitted within the device to manually open and close the device to allow the restocking of medication.
  
## Design Diagram
https://user-images.githubusercontent.com/114532865/235360212-c2329aaf-17d4-4a80-9ebf-46ad40c32ec3.jpg

https://user-images.githubusercontent.com/114532865/235360253-f8287d64-8ca5-4992-af24-5bc64290aa48.jpg
The is the state machine defining the menuing for the soon-to-be implemented touchscreen. Starting from a password menu, a correct password changes the state into the control menu state. From this state, administrative user can set up the alarm time, calibrate the clock, and set a new password. A global timer counting the time since the last touchscreen input changes the state machine back to the idle state if more than 5 seconds have been counted.
