#include "moteur.h"

Moteur::Moteur( uint pinA, uint pinB, uint pinEN){
    this->_pinA=pinA;
    this->_pinB=pinB;
    this->_pinEN=pinEN;
}
void Moteur::init_motor() {
    gpio_init(this->_pinEN);
    gpio_set_dir(this->_pinEN,GPIO_OUT);
    gpio_put(this->_pinEN,true);
    gpio_set_function(this->_pinA, GPIO_FUNC_PWM);
    gpio_set_function(this->_pinB, GPIO_FUNC_PWM);

    this->_sliceA = pwm_gpio_to_slice_num(this->_pinA);
    this->_channelA=pwm_gpio_to_channel(this->_pinA);

    pwm_set_clkdiv_int_frac (this->_sliceA, 1, 0);
    pwm_set_wrap(this->_sliceA, PWM_WRAP);
    pwm_set_enabled(this->_sliceA, true);

    this->_sliceB = pwm_gpio_to_slice_num(this->_pinB);
    this->_channelB=pwm_gpio_to_channel(this->_pinB);
    pwm_set_clkdiv_int_frac (this->_sliceB, 1, 0);
    pwm_set_wrap(this->_sliceB, PWM_WRAP);
    pwm_set_enabled(this->_sliceB, true);

    //...
}
void Moteur::set_motor( float rc){
    // on veut tourner à droite

    if (rc>0){
        rc=fmin(1,rc);
        pwm_set_chan_level(this->_sliceA,  this->_channelA, PWM_WRAP * rc); 
        pwm_set_chan_level(this->_sliceB,  this->_channelB, 0); 

        // on veut tourner à gauche
    }else{
        rc=fmax(-1,rc);
        pwm_set_chan_level(this->_sliceB,  this->_channelB, PWM_WRAP * (-rc)); 
        pwm_set_chan_level(this->_sliceA,  this->_channelA, 0); 
    }

}

 // 125e6/4000 Pico Clock at 125MHz and 4KHz wanted for l293D


