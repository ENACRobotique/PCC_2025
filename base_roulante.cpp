#include "base_roulante.h"

Base_roulante::Base_roulante(float dist_roues,float phi_roues,float step_to_mm){
    this->_dist_roues=dist_roues;
    this->_phi_roues=phi_roues;
    this->_step_to_mm=step_to_mm;
}
void Base_roulante::translate(float dist){
    moteur_left.set_motor(_speed);
    moteur_right.set_motor(-_speed);
    
}