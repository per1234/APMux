/*
 https://github.com/elpsk/APMux
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

  uint32_t muxDelay = 10;

  void enableMux(MuxPosition position, MuxMode mode);

private:
  uint32_t _control0 = 5;
  uint32_t _control1 = 4;
  uint32_t _control2 = 3;
  uint32_t _control3 = 2;

  int mux0array[16];
  int mux1array[16];
  int mux2array[16];

  void enableMux_0_DO();
  void enableMux_1_DO();
  void enableMux_2_DO();

  void enableMux_0_DI();
  void enableMux_1_DI();
  void enableMux_2_DI();

  void enableMux_0_AI();
  void enableMux_1_AI();
  void enableMux_2_AI();

  void printData();
  int* getData(MuxPosition position);

};

#endif
