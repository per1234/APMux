##Arduino Multiplexer controller library.

Control your multiplexer and switch from all of your new **45 pins** easily!

###Example of use:


	#include "APMux.h"
	
	APMux mux;
	
	void setup() {
	  mux.muxDelay = 1000; // millis
	}
	
	void loop() {
	
	  // values are MUX_0, MUX_1, MUX_2
	  mux.enableMux(mux.MUX_1); // to enable a single block
	  
	  // use instead 
	  mux.enableAllMux(); // to enable all 3 blocks
	
	}

