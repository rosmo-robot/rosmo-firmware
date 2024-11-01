/* Encoder Library, for measuring quadrature encoded signals
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 * Copyright (c) 2011,2013 PJRC.COM, LLC - Paul Stoffregen <paul@pjrc.com>
 *
 * Version 1.2 - fix -2 bug in C-only code
 * Version 1.1 - expand to support boards with up to 60 interrupts
 * Version 1.0 - initial release
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef Encoder_h_
#define Encoder_h_
#include "Arduino.h"

#include <ESP32Encoder.h>
class Encoder
{
private:
	int counts_per_rev_ = -1;
        ESP32Encoder encoder_;
	unsigned long prev_update_time_;
        int64_t prev_encoder_ticks_;
public:
	Encoder(int pin1, int pin2, int counts_per_rev, bool invert = false) {
		int temp_pin = pin1;
		if (pin1 < 0 || pin2 < 0) return; // unused encoder
		if(invert)
		{
			pin1 = pin2;
			pin2 = temp_pin;
		}
		counts_per_rev_ = counts_per_rev;
		encoder_.attachHalfQuad(pin1, pin2);
	}
	float getRPM() {
	        if (counts_per_rev_ < 0) return 0.0;
		int64_t encoder_ticks = encoder_.getCount();
		//this function calculates the motor's RPM based on encoder ticks and delta time
		unsigned long current_time = micros();
		unsigned long dt = current_time - prev_update_time_;

		//convert the time from milliseconds to minutes
		double dtm = (double)dt / 60000000;
		int64_t delta_ticks = encoder_ticks - prev_encoder_ticks_;

		//calculate wheel's speed (RPM)
		prev_update_time_ = current_time;
		prev_encoder_ticks_ = encoder_ticks;

		return (((double) delta_ticks / counts_per_rev_) / dtm);
	}
	inline int32_t read() {
	        if (counts_per_rev_ < 0) return 0;
		return  encoder_.getCount();
	}
        inline void write(int32_t p) {
	        if (counts_per_rev_ < 0) return;
	        encoder_.setCount(p);
	}
};

#endif
