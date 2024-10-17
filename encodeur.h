#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "quadrature_encoder.pio.h"

class Encodeur
{
    private:
        PIO _pio;
        uint _sm;
        uint _PIN;
        uint _offset = 0;
        
    public:
        Encodeur(uint ENCODER_PIN);
        void init_encoder();
        int get_value();
};