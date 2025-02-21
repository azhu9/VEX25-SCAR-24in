#pragma once

#include "EZ-Template/piston.hpp"
#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

// inline pros::MotorGroup intake({7, -16});
inline pros::Motor intake(-16);
inline pros::Motor conveyor(21);
inline pros::Rotation lb_rotation(18);
inline pros::MotorGroup ladyBrown({19, -7});

inline int position = lb_rotation.get_position();

// inline pros::Optical color(10);

inline ez::Piston clampPiston('A', false);
inline ez::Piston flipperPiston('G', false);
inline ez::Piston leftDoinker('H', false);
inline ez::Piston rightDoinker('D', false);