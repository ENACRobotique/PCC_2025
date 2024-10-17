#include "encodeur.h"

Encodeur::Encodeur(uint ENCODER_PIN){
            pio_claim_free_sm_and_add_program(&quadrature_encoder_program,&this->_pio,&this->_sm, &this->_offset);
            this->_PIN = ENCODER_PIN;
            }

void Encodeur::init_encoder(){
    pio_add_program(this->_pio, &quadrature_encoder_program);
    quadrature_encoder_program_init(this->_pio, this->_sm, this->_PIN, 0);
    }

int Encodeur::get_value(){
    return quadrature_encoder_get_count(this->_pio, this->_sm);
    }