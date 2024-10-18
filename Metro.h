//Code extracted from Metro Library
//Copyright (c) 2013 thomasfredericks
//Under MIT License

//Edited to be compliant with pico lib in 2024 by EnacRobotique

#ifndef METRO
#define METRO
#include "pico/time.h"

uint32_t  get_time_millis(){
    return to_ms_since_boot(get_absolute_time());}

uint32_t  get_time_micros(){
    return to_us_since_boot(get_absolute_time());}

// Chronometer/stopwatch library that counts the time passed since started.
// Time is in milli-seconds
class Metro_millis {
    public:
        Metro_millis(uint32_t millis_): interval_millis(millis_) {}
        
        void interval(uint32_t millis_){
            this->interval_millis = millis_;
        }
        //returns True if the desired elapsed time is reached
        bool check(){
            uint32_t now = get_time_millis();
            if (interval_millis == 0){
                previous_millis = now;
                return true;
            }
            if ((now-previous_millis) >= interval_millis){
                
                #ifdef NOCATCHUP
                previous_millis = now;
                #else
                previous_millis += interval_millis;
                #endif
                return true;
            }
            return false;
        }
        void reset(){
            this->previous_millis = get_time_millis();
        }
    private:
        uint32_t previous_millis, interval_millis;
};

// Chronometer/stopwatch library that counts the time passed since started.
// Time is in micro-seconds
class Metro_micros {
    public:
        Metro_micros(uint32_t micros_): interval_micros(micros_) {}
        
        void interval(uint32_t micros_){
            this->interval_micros = micros_;
        }
        //returns True if the desired elapsed time is reached
        bool check(){
            uint32_t now = get_time_micros();
            if (interval_micros == 0){
                previous_micros = now;
                return true;
            }
            if ((now-previous_micros) >= interval_micros){
                
                #ifdef NOCATCHUP
                previous_micros = now;
                #else
                previous_micros += interval_micros;
                #endif
                return true;
            }
            return false;
        }
        void reset(){
            this->previous_micros = get_time_micros();
        }
    private:
        uint32_t previous_micros, interval_micros;
};

#endif