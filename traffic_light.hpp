
#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include "pico/stdlib.h"
#include "pico/time.h"


class TrafficLight {

    public: 
        
        TrafficLight(uint redPin,uint yellowPin,uint greenPin,uint pedestrian,uint button);
        void start();
    private:
        const uint red;
        const uint yellow;
        const uint green;
        //toggle buzzer
        const uint pedestrian;
        //button
       static const uint button= 16;

       //blink
       bool led_On_Blink;

        static const uint RED_LED_ON = 0b001;
        static const uint YELLOW_LED_ON = 0b010;
        static const uint GREEN_LED_ON = 0b100;

    void setLedValue(const uint value);
    void pedestrian_crossing();
    static void checkBtnStatOnCore1();

    
};

#endif
