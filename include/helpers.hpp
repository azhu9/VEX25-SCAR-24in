#pragma once
#include "api.h"
#include "subsystems.hpp"

// Drive constants for Autons
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;


//intake helper methods
inline void intakeStart(int voltage){
    intake.move(voltage);
}

inline void intakeStart(int voltage, int ms){
    intake.move(voltage);
    pros::delay(ms);
    intake.brake();
}

inline void intakeStop(){
    intake.brake();
}

//conveyor helper methods
inline void conveyorStart(int voltage){
    conveyor.move(voltage);
}


inline void conveyorStart(int voltage, int ms){
    conveyor.move(voltage);
    pros::delay(ms);
    conveyor.brake();
}

inline void conveyorStop(){
    conveyor.brake();
}

//both intake and conveyor methods
inline void comboStart(int voltage){
    intake.move(voltage);
    conveyor.move(voltage);
}

inline void comboStart(int voltage, int ms){
    intake.move(voltage);
    conveyor.move(voltage);
    pros::delay(ms);
    intake.brake();
    conveyor.brake();
}

inline void comboStop(){
    intake.brake();
    conveyor.brake();
}

//piston helpers

inline void clampIn(){
    clampPiston.set(true);
}

inline void clampOut(){
    clampPiston.set(false);
}

inline void flipperIn(){
    flipperPiston.set(true);
}

inline void flipperOut(){
    flipperPiston.set(false);
}

inline void leftDoinkerIn(){
    leftDoinker.set(true);
}

inline void leftDoinkerOut(){
    leftDoinker.set(false);
}

inline void rightDoinkerIn(){
    rightDoinker.set(true);
}

inline void rightDoinkerOut(){
    rightDoinker.set(false);
}


inline void lbMove(int target, int timeout){
    int target_position = target;
    int pressTime = pros::millis();
  
    while (abs(position) < target_position) {
      int curTime = pros::millis();
      position = lb_rotation.get_position();
      ladyBrown.move(40); //55
      pros::delay(20);
  
      if(curTime - pressTime > timeout) break;
    }
    
  }