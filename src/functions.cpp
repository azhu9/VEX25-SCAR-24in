#include "EZ-Template/util.hpp"
#include "main.h"

#include "pros/misc.hpp"
#include "subsystems.hpp"



void colorSorting(bool isRed){
    if(isRed){

    }
    else{

    }
}

void lbMove(){

}

void unJamFunction(){
    pros::delay(2000);
    while(true){
        int velocity = conveyor.get_actual_velocity();
        if(pros::competition::is_autonomous()){
            if(velocity < 10){
                conveyor.move(-127);
                pros::delay(300);
                conveyor.move(127);
            }
        }
        pros::delay(ez::util::DELAY_TIME);
    }
}
pros::Task unjam(unJamFunction);
//todo: color sorting task
//      lady brown task
//      unjam task
