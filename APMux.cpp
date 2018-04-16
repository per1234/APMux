#include "APMux.h"
#include "Arduino.h"

APMux::APMux()
{
  pinMode(_control0, OUTPUT);
  pinMode(_control1, OUTPUT);
  pinMode(_control2, OUTPUT);
  pinMode(_control3, OUTPUT);
}

APMux::~APMux()
{
}

void APMux::enableMux(MuxPosition position) {
  switch (position) {
    case MUX_0:
      enableMux_0();
      break;
    case MUX_1:
      enableMux_1();
      break;
    case MUX_2:
      enableMux_2();
      break;
  }
}

void APMux::enableAllMux() {
  enableMux_0();
  enableMux_1();
  enableMux_2();
}

void APMux::enableMux_0() {

  //pin 14 (MUX 0)
  pinMode(14, OUTPUT);     //pin 14 (MUX 0)
  pinMode(15, INPUT);      //pin 15 (MUX 1)
  pinMode(16, INPUT);      //pin 16 (MUX 2)

  // ciclo su tutti i pin
  for (int i=0; i<16; i++) {
    digitalWrite(_control0, (i&15)>>3); //S3
    digitalWrite(_control1, (i&7)>>2);  //S2
    digitalWrite(_control2, (i&3)>>1);  //S1
    digitalWrite(_control3, (i&1));     //S0

    digitalWrite(14, HIGH);
    delay(muxDelay);
    digitalWrite(14, LOW);
    delay(muxDelay);
  }

  // attivo solo il pin 0 ??!??
  digitalWrite(_control0, 0);  //S3
  digitalWrite(_control1, 0);  //S2
  digitalWrite(_control2, 0);  //S1
  digitalWrite(_control3, 0);  //S0

}

void APMux::enableMux_1() {

  // pin 15 (MUX 1)
  pinMode(14, INPUT);
  pinMode(15, OUTPUT);
  pinMode(16, INPUT);

  for (int i=0; i<16; i++) {
    digitalWrite(_control0, (i&15)>>3); //S3
    digitalWrite(_control1, (i&7)>>2);  //S2
    digitalWrite(_control2, (i&3)>>1);  //S1
    digitalWrite(_control3, (i&1));     //S0

    digitalWrite(15, HIGH);
    delay(muxDelay);
    digitalWrite(15, LOW);
    delay(muxDelay);
  }

}

void APMux::enableMux_2() {

  //pin 16 (MUX 2)
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, OUTPUT);

  for (int i=0; i<16; i++) {
    digitalWrite(_control0, (i&15)>>3); //S3
    digitalWrite(_control1, (i&7)>>2);  //S2
    digitalWrite(_control2, (i&3)>>1);  //S1
    digitalWrite(_control3, (i&1));     //S0

    digitalWrite(16, HIGH);
    delay(muxDelay);
    digitalWrite(16, LOW);
    delay(muxDelay);
  }

}
