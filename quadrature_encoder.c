/**
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "config.h"
#include "hardware/pwm.h"
#include "quadrature_encoder.pio.h"
#include <math.h>



#define step_to_mm 108/289
#define PWM_WRAP 31250
typedef struct {
  uint sliceA;
  uint sliceB;
  uint channelA;
  uint channelB;
} moteur_t;

int new_value1 = 0;
int new_value2 = 0;
float dist1 = 0;
float dist2 = 0;
// Base pin to connect the A phase of the encoder.
// The B phase must be connected to the next pin
const uint ENC1_AB = ENC1_A; //10-11 and 19-20
const uint ENC2_AB = ENC2_A; //10-11 and 19-20
PIO pio_enc1 = pio0;
PIO pio_enc2 = pio1;
const uint sm1 = 0;
const uint sm2 = 0;
uint slice_1A,channel_1A,slice_1B,channel_1B,slice_2,channel_2 ;

//
void setup_encoder(uint ENCODER,PIO encoder,uint sm){
    pio_add_program(encoder, &quadrature_encoder_program);
    quadrature_encoder_program_init(encoder, sm, ENCODER, 0);
};

int get_encoder_value(PIO encoder,uint sm){
        new_value1 = quadrature_encoder_get_count(encoder, sm);
        return new_value1;
}

void init_motor(moteur_t* moteur, uint mot_a, uint mot_b, uint mot_en) {
    gpio_init(mot_en);
    gpio_set_dir(mot_en,GPIO_OUT);
    gpio_put(mot_en,true);
    gpio_set_function(mot_a, GPIO_FUNC_PWM);
    gpio_set_function(mot_b, GPIO_FUNC_PWM);

    moteur->sliceA = pwm_gpio_to_slice_num(mot_a);
    moteur->channelA=pwm_gpio_to_channel(mot_a);

    pwm_set_clkdiv_int_frac ((*moteur).sliceA, 1, 0);
    pwm_set_wrap((*moteur).sliceA, PWM_WRAP);
    pwm_set_enabled((*moteur).sliceA, true);

    moteur->sliceB = pwm_gpio_to_slice_num(mot_b);
    moteur->channelB=pwm_gpio_to_channel(mot_b);
    pwm_set_clkdiv_int_frac ((*moteur).sliceB, 1, 0);
    pwm_set_wrap((*moteur).sliceB, PWM_WRAP);
    pwm_set_enabled((*moteur).sliceB, true);

    //...
}
void set_motor(moteur_t * moteur, float rc){
    // on veut tourner à droite

    if (rc>0){
        rc=fmin(1,rc);
        pwm_set_chan_level((*moteur).sliceA, (*moteur).channelA, PWM_WRAP * rc); 
        pwm_set_chan_level((*moteur).sliceB, (*moteur).channelB, 0); 

        // on veut tourner à gauche
    }else{
        rc=fmax(-1,rc);
        pwm_set_chan_level((*moteur).sliceB, (*moteur).channelB, PWM_WRAP * (-rc)); 
        pwm_set_chan_level((*moteur).sliceA, (*moteur).channelA, 0); 
    }

}

 // 125e6/4000 Pico Clock at 125MHz and 4KHz wanted for l293D


int main() {

    stdio_init_all();
    setup_encoder(ENC1_A,pio_enc1,sm1);
    moteur_t moteur1;
    moteur_t moteur2;
    init_motor(&moteur1, MOT1_A, MOT1_B, MOT1_EN);
    init_motor(&moteur2, MOT2_A,MOT2_B,MOT2_EN);

    set_motor(&moteur1,-0.5);




    while (1) {

        int a=get_encoder_value(pio_enc1,sm1);
        printf("%d \n",a);
    }
}

