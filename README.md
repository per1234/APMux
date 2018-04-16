## Arduino Multiplexer controller library.

Control your multiplexer and switch from all of your new **45 pins** easily!

### Example of use:


	#include "APMux.h"

	APMux mux;

	void setup() {
	  mux.muxDelay = 1000; // millis
	}

	void loop() {

	  // values are MUX_0, MUX_1, MUX_2
    mux.enableMux(mux.MUX_0, mux.DIGITAL_OUTPUT);  // to enable a single block

    // get data from INPUTs
    // mux.getData(mux.MUX_0);

	}


### MuxMode and MuxPosition:

  enum MuxMode
  {
    DIGITAL_OUTPUT = 0,
    DIGITAL_INPUT = 1,
    ANALOG_INPUT = 2
  };

  enum MuxPosition
  {
    MUX_0 = 0,
    MUX_1 = 1,
    MUX_2 = 2
  };
