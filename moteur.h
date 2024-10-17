#pragma once 

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include <math.h>
#define PWM_WRAP 31250



class Moteur{
    private:
        uint _sliceA;
        uint _sliceB;
        uint _channelA;
        uint _channelB;
        uint _pinA;
        uint _pinB;
        uint _pinEN;
    public:
        Moteur( uint pinA, uint pinB, uint pinEN);
        void init_motor();
        void set_motor(float rc);
};
