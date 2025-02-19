#include "helpers.hpp";
#include "main.h"
#include "subsystems.hpp"


/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///
void blueMatch() {
  ez::Piston flipper('G');

  flipper.set(false);

  ez::Piston leftDoinker('D');
  ez::Piston rightDoinker('H');

  chassis.pid_drive_set(25_in, 127, true);
  chassis.pid_wait_until(4_in);
  rightDoinker.set(true);
  chassis.pid_wait();

  rightDoinker.set(false);

  chassis.pid_drive_set(-15_in, 127, true);
  chassis.pid_wait();

  rightDoinker.set(true);

  chassis.pid_drive_set(-5_in, 100, true);
  chassis.pid_wait();

  rightDoinker.set(false);

  pros::delay(300);

  chassis.pid_turn_relative_set(-172_deg, TURN_SPEED);
  chassis.pid_wait();

  // pros::delay(3000);

  chassis.pid_drive_set(-24_in, 40, true);
  chassis.pid_wait();

  // chassis.pid_swing_relative_set(ez::LEFT_SWING, -15_deg, SWING_SPEED, 80);
  // chassis.pid_wait();

  ez::Piston clamp('A');

  clamp.set(true);

  conveyor.move(127);

  chassis.pid_turn_relative_set(20_deg, TURN_SPEED);
  chassis.pid_wait();

  conveyor.brake();

  intake.move(127);
  conveyor.move(127);

  chassis.pid_drive_set(44_in, 50, true);
  chassis.pid_wait();

  intake.brake();
  // conveyor.brake();

  chassis.pid_swing_relative_set(ez::LEFT_SWING, 85_deg, 70, 0);
  chassis.pid_wait();

  conveyor.brake();

  chassis.pid_drive_set(-4_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-10_deg, TURN_SPEED);
  chassis.pid_wait();

  leftDoinker.set(true);
  pros::delay(1000);

  chassis.pid_turn_relative_set(90_deg, 40);
  chassis.pid_wait();

  leftDoinker.set(false);

  chassis.pid_swing_relative_set(ez::LEFT_SWING, 85_deg, 70, 40);
  chassis.pid_wait();

  // chassis.pid_turn_relative_set(90_deg, 40);
  // chassis.pid_wait();

  clamp.set(false);

  chassis.pid_swing_relative_set(ez::LEFT_SWING, 85_deg, 70, 10);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-125_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, 70, true);
  chassis.pid_wait();

  rightDoinker.set(true);

  pros::delay(300);

  chassis.pid_drive_set(-30_in, 70, true);
  chassis.pid_wait();

  rightDoinker.set(false);

  pros::delay(1000);

  chassis.pid_turn_relative_set(-165_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-15_in, 50, true);
  chassis.pid_wait();

  clamp.set(true);

  intake.move(127);
  conveyor.move(127);
  chassis.pid_drive_set(10_in, 80, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-180_deg, TURN_SPEED);
  chassis.pid_wait();

  intake.brake();

  conveyor.brake();

  chassis.pid_drive_set(18_in, 50, true);
  chassis.pid_wait();

  ladyBrown.move(127);
  pros::delay(1000);

  ladyBrown.brake();
}

///
// Turn Example
///
void redMatch() {
  ez::Piston flipper('G');

  flipper.set(false);

  ez::Piston leftDoinker('D');
  ez::Piston rightDoinker('H');

  chassis.pid_drive_set(25_in, 127, true);
  chassis.pid_wait_until(4_in);
  leftDoinker.set(true);
  chassis.pid_wait();

  leftDoinker.set(false);

  chassis.pid_drive_set(-15_in, 127, true);
  chassis.pid_wait();

  leftDoinker.set(true);

  chassis.pid_drive_set(-5_in, 100, true);
  chassis.pid_wait();

  leftDoinker.set(false);

  pros::delay(300);

  chassis.pid_turn_relative_set(172_deg, TURN_SPEED);
  chassis.pid_wait();

  // pros::delay(3000);

  chassis.pid_drive_set(-24_in, 40, true);
  chassis.pid_wait();

  // chassis.pid_swing_relative_set(ez::LEFT_SWING, -15_deg, SWING_SPEED, 80);
  // chassis.pid_wait();

  ez::Piston clamp('A');

  clamp.set(true);

  conveyor.move(127);

  pros::delay(1000);

  conveyor.brake();

  chassis.pid_turn_relative_set(-20_deg, TURN_SPEED);
  chassis.pid_wait();

  conveyor.brake();

  intake.move(127);
  conveyor.move(127);

  chassis.pid_drive_set(44_in, 50, true);
  chassis.pid_wait();

  intake.brake();
  // conveyor.brake();

  chassis.pid_swing_relative_set(ez::RIGHT_SWING, -85_deg, 70, 0);
  chassis.pid_wait();

  conveyor.brake();

  chassis.pid_drive_set(-4_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(10_deg, TURN_SPEED);
  chassis.pid_wait();

  rightDoinker.set(true);
  pros::delay(1000);

  chassis.pid_turn_relative_set(-90_deg, 40);
  chassis.pid_wait();

  rightDoinker.set(false);

  chassis.pid_swing_relative_set(ez::RIGHT_SWING, -85_deg, 70, 40);
  chassis.pid_wait();

  // chassis.pid_turn_relative_set(90_deg, 40);
  // chassis.pid_wait();

  clamp.set(false);

  chassis.pid_swing_relative_set(ez::RIGHT_SWING, -85_deg, 70, 10);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(140_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, 70, true);
  chassis.pid_wait();

  leftDoinker.set(true);

  pros::delay(300);

  chassis.pid_drive_set(-30_in, 70, true);
  chassis.pid_wait();

  leftDoinker.set(false);

  // pros::delay(1000);

  // chassis.pid_turn_relative_set(165_deg, TURN_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-15_in, 50, true);
  // chassis.pid_wait();

  // clamp.set(true);

  // intake.move(127);
  // conveyor.move(127);
  // chassis.pid_drive_set(10_in, 80, true);
  // chassis.pid_wait();

  // chassis.pid_turn_relative_set(180_deg, TURN_SPEED);
  // chassis.pid_wait();

  // intake.brake();

  // conveyor.brake();

  // chassis.pid_drive_set(18_in, 50, true);
  // chassis.pid_wait();

  // ladyBrown.move(127);
  // pros::delay(1000);

  // ladyBrown.brake();
}

///
// Combining Turn + Drive
///
void redMatchSafe() {
  ez::Piston flipper('G');

  flipper.set(false);

  ez::Piston leftDoinker('D');
  ez::Piston rightDoinker('H');

  chassis.pid_drive_set(40_in, 127, true);
  chassis.pid_wait_until(10_in);
  rightDoinker.set(true);
  chassis.pid_wait();

  rightDoinker.set(false);

  chassis.pid_drive_set(-30_in, 127, true);
  chassis.pid_wait();

  rightDoinker.set(true);

  chassis.pid_drive_set(-5_in, 100, true);
  chassis.pid_wait();

  rightDoinker.set(false);
}

///
// Wait Until and Changing Max Speed
///
void skills() {
  comboStart(127);
  chassis.pid_drive_set(12_in, 100, true);
  pros::delay(500);

  chassis.pid_wait();

  comboStop();

  chassis.pid_drive_set(-11_in, 100, true);
  chassis.pid_wait();
  comboStart(127, 2500);

  chassis.pid_swing_set(ez::LEFT_SWING, 90_deg, SWING_SPEED, 15);
  chassis.pid_wait();

  chassis.pid_drive_set(42_in, 80, true);
  chassis.pid_wait_until(30_in);
  intakeStart(127);
  chassis.pid_wait();

  pros::delay(500);
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-22_in, 50, true);
  chassis.pid_wait();
  intakeStop();
  clampIn();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(200);

  comboStart(127);
  chassis.pid_drive_set(24_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(500);

  chassis.pid_drive_set(36_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 55);
  chassis.pid_wait();
  pros::delay(200);

  chassis.pid_drive_set(20_in, 40, true);
  chassis.pid_wait();


  // chassis.pid_drive_set( 36_in, 80, true);
  // chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .