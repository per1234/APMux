// http://mayhewlabs.com/arduino-mux-shield

/*
 S0   S1  S2  S3  PIN
  0   0   0   0   0
  1   0   0   0   1
  0   1   0   0   2
  1   1   0   0   3
  0   0   1   0   4
  1   0   1   0   5
  0   1   1   0   6
  1   1   1   0   7
  0   0   0   1   8
  1   0   0   1   9
  0   1   0   1   10
  1   1   0   1   11
  0   0   1   1   12
  1   0   1   1   13
  0   1   1   1   14
  1   1   1   1   15
*/

/*
  for (int i=0; i<16; i++) {
    int s3 = (i&1);
    int s2 = (i&3)>>1;
    int s1 = (i&7)>>2;
    int s0 = (i&15)>>3;
    printf("[%d]\t-\t%d %d %d %d", i, s3, s2, s1, s0);
  }
*/

#ifndef APMUX_H
#define APMUX_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class APMux
{
public:
	APMux();
	~APMux();

	enum MuxPosition
	{
		MUX_0 = 0,
		MUX_1 = 1,
		MUX_2 = 2
	};

  uint32_t muxDelay = 10;

  void enableMux(MuxPosition position);
  void enableAllMux();

private:
  uint32_t _control0 = 5;
  uint32_t _control1 = 4;
  uint32_t _control2 = 3;
  uint32_t _control3 = 2;

  void enableMux_0();
  void enableMux_1();
  void enableMux_2();
};

#endif
