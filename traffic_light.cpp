#include"traffic_light.hpp"
#include "pico/time.h"
#include <iostream>
#include "pico/multicore.h"
#include"hardware/gpio.h"
//constructor
TrafficLight::TrafficLight(uint redPin,uint yellowPin,uint greenPin,uint pedestrian,uint button):
               
               red(redPin),yellow(yellowPin),green(greenPin),pedestrian(pedestrian),led_On_Blink(false){
                    gpio_init(red);
                    gpio_init(yellow);
                    gpio_init(green);

                    //button
                    gpio_init(button);

                    gpio_set_dir(red,GPIO_OUT);
                    gpio_set_dir(yellow,GPIO_OUT);
                    gpio_set_dir(green,GPIO_OUT);

                    //button
                    gpio_set_dir(button,GPIO_IN);

                    stdio_init_all();

                    multicore_launch_core1(checkBtnStatOnCore1);
                    

                }

void TrafficLight::setLedValue(const uint value){
    gpio_put(red,value&RED_LED_ON);
    gpio_put(yellow,value&YELLOW_LED_ON);
    gpio_put(green,value&GREEN_LED_ON);


}

//superloop
void TrafficLight::start(){

   

    while(true){
    if (multicore_fifo_rvalid()) {
    uint32_t is_btn_pressed=multicore_fifo_pop_blocking();
        if(is_btn_pressed){
            led_On_Blink=!led_On_Blink;
        //pedestrian_crossing();
       multicore_fifo_drain();
       std::cout<<"button pressed"<<std::endl;
        }

    }
    if(led_On_Blink){
    setLedValue(RED_LED_ON|YELLOW_LED_ON|GREEN_LED_ON);
    std::cout<<"Lights are blinking!"<<std::endl;
    sleep_ms(100);
    setLedValue(0);
    sleep_ms(100);
    }
    else{
       // setLedValue(RED_LED_ON);
       setLedValue(0);
    }
    sleep_ms(1000);
}
}
    //std::cout<<"Red on"<<std::endl;
    //setLedValue(YELLOW_LED_ON);
    //sleep_ms(2000);
    ////std::cout<<"Yellow on"<<std::endl;
    ////setLedValue(GREEN_LED_ON);
    //sleep_ms(5000);
    //std::cout<<"Green on"<<std::endl;


      

   //// }
//}


void TrafficLight::pedestrian_crossing(){
  for(int i =1;i>0; i--){
   std::cout<<"Pedestrian Crossing:"<<i<<std::endl;
   gpio_put(pedestrian,1);
   sleep_ms(250);
   gpio_put(pedestrian,0);
   sleep_ms(250);

        
          

   
   }
std::cout<<"Do NOT walk!!"<<std::endl;
}

//Two core
void TrafficLight::checkBtnStatOnCore1(){
   while(true){
    bool btnStatus=gpio_get(button);
    if(btnStatus){
   //this function is a rpp sdk pushes stat to core zero and blocks until read
    multicore_fifo_push_blocking(btnStatus);
    //
    sleep_ms(10);

    while(gpio_get(button)){
sleep_ms(10);

    }

}
    //not make busy running aka save power
   sleep_ms(100);

   }
   }
