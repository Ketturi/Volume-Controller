/*Code for driving motorized potentiometer in amplifier.
 *Motorized potentiometer is connected trough H-bridge
 *to arduino. Pulse encoder is connected INT0 and INT1
 *interupts.
 *
 *Ketturi Fox 2015
 */

#include <Encoder.h>
Encoder myEnc(2, 3);      // Rotary encoder connected in pin 2 and 3 (INT0&INT1)

const int vol_up = 8;     // H-Bridge input pins
const int vol_dn = 9;     // If motor turn in wrong direction, swap these
const int volumeRef = A0; // Analog input for position feedback (0-5V)

const int speed_max = 100; // Max value for accumulated speed
const int LOOP_DELAY = 5;  // Varying these two, adjust feel can be made pleasant
long vspeed = 0;

void setup() {
//Serial.begin(9600);
  pinMode(vol_up, OUTPUT);
  pinMode(vol_dn, OUTPUT);
}


void loop() {
    // Read change since last call and reset the reading.
    long delta = myEnc.read();
    vspeed += delta;
    myEnc.write(0);

    // Limit accumulated speed.
    if (vspeed > speed_max) vspeed = speed_max;
    else if (vspeed < -speed_max) vspeed = -speed_max; 
    
    // Stop motor at ends, there will be some latency. (Mechanical stoper in potentiometer)
    if (analogRead(volumeRef) < 10 && vspeed < 0) {
        vspeed = 0;
    } else if (analogRead(volumeRef) > 1020 && vspeed > 0) {
        vspeed = 0;
    }

    if (vspeed > 0) {
        digitalWrite(vol_dn, LOW);
        delay(LOOP_DELAY);
        digitalWrite(vol_up, HIGH);
    } else if (vspeed < 0) {
        digitalWrite(vol_up, LOW);
        delay(LOOP_DELAY);
        digitalWrite(vol_dn, HIGH);
    } else {
        digitalWrite(vol_up, LOW);
        digitalWrite(vol_dn, LOW);
        delay(LOOP_DELAY);        
    }

    if (vspeed > 0) vspeed--;
    else if (vspeed < 0) vspeed++;

//   Serial.print(vspeed);
//   Serial.print(" ");
//   Serial.println(analogRead(volumeRef));
}


