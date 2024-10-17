#pragma once

#include "moteur.h"
#include "encodeur.h"

extern Moteur moteur_left;
extern Moteur moteur_right;
extern Encodeur encodeur_left;
extern Encodeur encodeur_right;
typedef struct{
  float x;
  float y;
  float theta;
} coord;


class Base_roulante{
    private:
    float _dist_roues;
    float _phi_roues;        //diametre
    float _step_to_mm;
    coord _coord;
    float _speed;
    


    public:
    Base_roulante(float dist_roues,float phi_roues,float step_to_mm);
    void turn(float theta);
    void translate(float dist);
    void odometry();
    void move(coord dest);
    void translate_point(float x , float y);


    void set_speed(float speed){this->_speed=speed;}
    coord get_current_position(){return _coord;}
    void set_current_position(coord pos){_coord = pos;}

};

