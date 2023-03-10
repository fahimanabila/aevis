#include <IRremote.h>
#include <Servo.h>
#include <virtuabotixRTC.h>

Servo servo;
virtuabotixRTC myRTC(4, 5, 6);

int infraRed = 7;
int ledMerah = 9;
int ledHijau = 8;

int pagi, siang;

int jikaLEDon[] = {0,0,0,0};

#define tombol1 12495
#define tombol2 6375
#define tombol3 31365

IRrecv irrecv (infraRed);
decode_results result;

void setup() {
Serial.begin(9600);
irrecv.enableIRIn();

pinMode (ledMerah, OUTPUT);
pinMode (ledHijau, OUTPUT);
servo.attach(3);
// seconds, minutes, hours, day of the week, day of the month, month, year
myRTC.setDS1302Time(15, 42, 19, 3, 21, 12, 2022);
}

void loop() {
myRTC.updateTime();

switch(myRTC.hours){
    case 9:
        digitalWrite(ledMerah, HIGH);
        digitalWrite(ledHijau, LOW);
        servo.write(180);
        delay(1000);
        servo.write(-180);
        delay(1000);
        servo.write(0);
    break;

    case 11:
        digitalWrite(ledHijau, HIGH);
        digitalWrite(ledMerah, LOW);
        servo.write(180);
        delay(1000);
        servo.write(-180);
        delay(1000);
        servo.write(0);
    break;
}

if (irrecv.decode(&result)){
unsigned int nilai = result.value;
Serial.println(nilai);
Serial.println(myRTC.hours);

 switch(myRTC.hours){
  case 9:
  pagi = 1;
  siang = 0;
  break;

  case 11:
  pagi = 0;
  siang = 1;
  break;
 }


switch (nilai){
  case tombol1 :
    if (pagi == 1){
        digitalWrite(ledMerah, HIGH);
        digitalWrite(ledHijau, LOW);
        servo.write(120);
        delay(200);
        servo.write(-120);
        delay(200);
        servo.write(0);
        delay(200);
        servo.write(120);
        delay(200);
        servo.write(-120);
        delay(200);
    }else{
        digitalWrite(ledMerah, HIGH);
        delay(100);
        digitalWrite(ledMerah, LOW);
        servo.write(0);
        delay(200);
        servo.write(-120);
        delay(200);
        servo.write(120);
        delay(200);
        servo.write(-120);
        delay(200);
    }
  break;

  case tombol2 :
  if (siang == 1){
        digitalWrite(ledHijau, HIGH);
        digitalWrite(ledMerah, LOW);
        servo.write(120);
        delay(200);
        servo.write(-120);
        delay(200);
        servo.write(0);
        delay(200);
        servo.write(120);
        delay(200);
        servo.write(-120);
        delay(200);
  }else{
        digitalWrite(ledHijau, HIGH);
        delay(100);
        digitalWrite(ledHijau, LOW);
        servo.write(120);
        delay(200);
        servo.write(0);
        delay(200);
        servo.write(120);
        servo.write(-120);
        delay(200);
  }
  break;
  
}
Serial.println (nilai);
//irrecv.resume(); 
}

}
