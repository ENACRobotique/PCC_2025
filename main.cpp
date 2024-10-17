#include "config.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "encodeur.h"
#include "moteur.h"

const uint ENC1_AB = ENC1_A; //10-11 and 19-20
const uint ENC2_AB = ENC2_A; //10-11 and 19-20
const uint MOT1A = MOT1_A;
const uint MOT1B=MOT1_B;
const uint MOT1EN=MOT1_EN;

Encodeur encodeur1(ENC1_AB);
Moteur moteur1(MOT1A,MOT1B,MOT1EN);


const uint MOT2A = MOT2_A;
const uint MOT2B=MOT2_B;
const uint MOT2EN=MOT2_EN;

Encodeur encodeur2(ENC2_AB);
Moteur moteur2(MOT2A,MOT2B,MOT2EN);

int main() {
    stdio_init_all();
    encodeur1.init_encoder();
    moteur1.init_motor();
    encodeur2.init_encoder();
    moteur2.init_motor();
    while(1){
        printf("value 1  = %d  value 2 = %d \n",encodeur1.get_value(),encodeur2.get_value());
        moteur1.set_motor(-0.5);
        moteur2.set_motor(0.5);


    }
}