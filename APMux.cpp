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

void APMux::enableMux(MuxPosition position, MuxMode mode) {
  switch (position) {
    case MUX_0:
      switch (mode) {
        case DIGITAL_INPUT:
          enableMux_0_DI();
          break;
        case DIGITAL_OUTPUT:
          enableMux_0_DO();
          break;
        case ANALOG_INPUT:
          enableMux_0_AI();
          break;
      }
      break;
    case MUX_1:
    switch (mode) {
      case DIGITAL_INPUT:
        enableMux_1_DI();
        break;
      case DIGITAL_OUTPUT:
        enableMux_1_DO();
        break;
      case ANALOG_INPUT:
        enableMux_1_AI();
        break;
    }
    break;
    case MUX_2:
    switch (mode) {
      case DIGITAL_INPUT:
        enableMux_2_DI();
        break;
      case DIGITAL_OUTPUT:
        enableMux_2_DO();
        break;
      case ANALOG_INPUT:
        enableMux_2_AI();
        break;
    }
    break;
  }
}

// -----------------------------------------------------------------------------

void APMux::enableMux_0_DO() {

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

}

void APMux::enableMux_1_DO() {

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

void APMux::enableMux_2_DO() {

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

// -----------------------------------------------------------------------------

void APMux::enableMux_0_DI() {
  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i=0; i<16; i++)
  {
    //The following 4 commands set the correct logic for the control pins to select the desired input
    //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
    //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
    digitalWrite(_control0, (i&15)>>3);
    digitalWrite(_control1, (i&7)>>2);
    digitalWrite(_control2, (i&3)>>1);
    digitalWrite(_control3, (i&1));

    //Read and store the input
    //Since internal pullup is on, the pin goes low on changing, so the value needs to be flipped from 0 to 1 (!)
    mux0array[i] = !digitalRead(14);
  }
}

void APMux::enableMux_1_DI() {
  //This for loop is used to scroll through the SECOND multiplexer
  for (int i=0; i<16; i++)
  {
    digitalWrite(_control0, (i&15)>>3);
    digitalWrite(_control1, (i&7)>>2);
    digitalWrite(_control2, (i&3)>>1);
    digitalWrite(_control3, (i&1));
    mux1array[i] = !digitalRead(15);
  }
}

void APMux::enableMux_2_DI() {
  //This for loop is used to scroll through the THIRD multiplexer
  for (int i=0; i<16; i++)
  {
    digitalWrite(_control0, (i&15)>>3);
    digitalWrite(_control1, (i&7)>>2);
    digitalWrite(_control2, (i&3)>>1);
    digitalWrite(_control3, (i&1));
    mux2array[i] = !digitalRead(16);
  }
}

// -----------------------------------------------------------------------------

void APMux::enableMux_0_AI() {
  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i=0; i<16; i++)
  {
    //The following 4 commands set the correct logic for the control pins to select the desired input
    //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
    //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
    digitalWrite(_control0, (i&15)>>3);
    digitalWrite(_control1, (i&7)>>2);
    digitalWrite(_control2, (i&3)>>1);
    digitalWrite(_control3, (i&1));

    //Read and store the input value at a location in the array
    mux0array[i] = analogRead(0);
  }
}

void APMux::enableMux_1_AI() {
  //This for loop is used to scroll through the SECOND multiplexer
  for (int i=0; i<16; i++)
  {
    digitalWrite(_control0, (i&15)>>3);
    digitalWrite(_control1, (i&7)>>2);
    digitalWrite(_control2, (i&3)>>1);
    digitalWrite(_control3, (i&1));
    mux1array[i] = analogRead(1);
  }
}

void APMux::enableMux_2_AI() {
  //This for loop is used to scroll through the THIRD multiplexer
  for (int i=0; i<16; i++)
  {
    digitalWrite(_control0, (i&15)>>3);
    digitalWrite(_control1, (i&7)>>2);
    digitalWrite(_control2, (i&3)>>1);
    digitalWrite(_control3, (i&1));
    mux2array[i] = analogRead(2);
  }
}

// -----------------------------------------------------------------------------

void APMux::printData() {
  //The following lines are for printing out results of array0
  Serial.print("mux0array: ");
  for (int i=0; i<16; i++)
  {
    Serial.print(mux0array[i]);
    Serial.print("-");
  }
  Serial.println();  //line feed

  //The following lines are for printing out results of array1
  Serial.print("mux1array: ");
  for (int i=0; i<16; i++)
  {
    Serial.print(mux1array[i]);
    Serial.print("-");
  }
  Serial.println();

  //The following lines are for printing out results of array2
  Serial.print("mux2array: ");
  for (int i=0; i<16; i++)
  {
    Serial.print(mux2array[i]);
    Serial.print("-");
  }
  Serial.println();
}

// -----------------------------------------------------------------------------

int* APMux::getData(MuxPosition position) {
  switch ( position ) {
    case MUX_0:
      return mux0array;
    case MUX_1:
      return mux1array;
    case MUX_2:
      return mux2array;
  }
}
