/*Code for driving motorized potentionmeter in amplifier.
 *Rotating rotary encoder moves motor in small steps and
 *sets led brightness to volume level.
 *
 *In future this will read ADC 0V..5.65V to determine actual
 *volume level. (Motor should stop when voltage 0.00 or 5.65).
 *
 *Ketturi Fox 2015
 */

#include <Encoder.h>
Encoder myEnc(2, 3); //Rotary encoder connected in pin 2 and 3 (INT0&INT1)

int led1 = 5;           
int led2 = 6; 
int led3 = 10; 
int led4 = 11; 

int vol_up = 8; //if motor turn in wrong direction, swap these
int vol_dn = 9;
int m_delay = 5; //5ms min length, 50ms max length of drive pulses. Motor turns fast on continuous drive!

void setup() {
  Serial.begin(9600);
  Serial.println("Encoder position debug:");

    pinMode(led1, OUTPUT); //set some outputs
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(vol_up, OUTPUT);
    pinMode(vol_dn, OUTPUT);
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read(); //myEnc.read() Returns the accumulated position. This number can be positive or negative.
   if (newPosition >= 255) { myEnc.write(255); } //If position goes out of range, resets it. (255 volume steps)
   if (newPosition <= 0)   { myEnc.write(0);   } 
   
   if (newPosition != oldPosition) {
      if (newPosition > oldPosition) { DriveMotor(1,m_delay); } //increase volume
      if (newPosition < oldPosition) { DriveMotor(0,m_delay); } //decrease volume
   
   oldPosition = newPosition;
   SetLedBrightness(newPosition);
   Serial.println(newPosition);
  }

}

void DriveMotor(int dir, int motor_delay){ //Turn volume motor 1=CW, 0=CCW for given timee
  if (dir=1){
    digitalWrite(vol_up, HIGH); //turn motor drive for n milliseconds
    delay(motor_delay);
    digitalWrite(vol_up, LOW);
  }
  if (dir=0){
    digitalWrite(vol_dn, HIGH);
    delay(motor_delay);
    digitalWrite(vol_dn, LOW);
  }
}

void SetLedBrightness(int pwm-level){
  analogWrite(led1, pwm-level);
  analogWrite(led2, pwm-level);
  analogWrite(led3, pwm-level);
  analogWrite(led4, pwm-level);
}

