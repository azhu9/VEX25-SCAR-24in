#include "autons.hpp"

#include "helpers.hpp"
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

pros::Task unjam(unJamFunction);  // unjam function in helpers
pros::Task colorSorting(colorSortingFunction);

void lbMoveAuto(int target) {
  int target_position = target;
  int pressTime = pros::millis();
  // int position = lb_rotation.get_position();

  // printf("Rotation: %i\n", position);

  while (abs(position) < target_position) {
    pros::lcd::print(1, "Rotation: %i", position);
    master.set_text(0, 0, "LB: " + std::to_string(position));

    // int curTime = pros::millis();
    position = lb_rotation.get_position();
    ladyBrown.move(40);  // 55
    pros::delay(100);

    // if (curTime - pressTime > timeout) break;
  }
}
///
// Drive Example
///

void colorTest() {
  // colorSorting.resume();

  groupStart(127, 10000);
}

void intakeTest() {
  // unjam.resume();
  // clampIn();
  // pros::delay(1000);
  // groupStart(127, 2000);
  // unjam.suspend();

  unjam.suspend();

  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  ladyBrown.move(127);
  pros::delay(100);
  ladyBrown.brake();

  groupStart(127);

  chassis.pid_drive_set(9_in, 60, true);
  chassis.pid_wait();

  pros::delay(1500);

  groupStop();

  chassis.pid_drive_set(6_in, 60, true);
  chassis.pid_wait();

  pros::delay(1000);

  ladyBrown.move(64);
  pros::delay(500);
  ladyBrown.brake();

  pros::delay(1000);

  chassis.pid_drive_set(-20_in, 60, true);
  chassis.pid_wait();

  // chassis.pid_drive_set(0_in, 0, true);
  // chassis.pid_wait();

  ladyBrown.move(-60);
  pros::delay(1000);
  ladyBrown.brake();
}

void lbTest() {
  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  ladyBrown.move(127);
  pros::delay(120);
  ladyBrown.brake();

  pros::delay(2000);

  ladyBrown.move(64);
  pros::delay(500);
  ladyBrown.brake();
}

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

  // chassis.pid_swing_relative_set(ez::LEFT_SWING, 85_deg, 70, 40);
  chassis.pid_wait();

  clampOut();
  // chassis.pid_turn_relative_set(90_deg, 40);
  // chassis.pid_wait();

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

  // chassis.pid_swing_relative_set(ez::RIGHT_SWING, -85_deg, 70, 40);
  chassis.pid_wait();
  clampOut();

  // chassis.pid_turn_relative_set(90_deg, 40);
  // chassis.pid_wait();
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
  // uncomment start
  // lbMove(3000, 1000);

  // pros::delay(5000);
  // unjam.resume();

  unjam.suspend();
  colorSorting.suspend();

  intakeStart(127);
  chassis.pid_drive_set(12_in, 60, true);
  pros::delay(500);
  chassis.pid_wait();

  intakeStop();

  chassis.pid_drive_set(-11_in, 60, true);
  chassis.pid_wait();
  groupStart(127, 1000);
  // unjam.suspend();

  // First TUrn
  chassis.pid_swing_set(ez::LEFT_SWING, 90_deg, SWING_SPEED, 15);
  chassis.pid_wait();

  chassis.pid_drive_set(42_in, 60, true);
  chassis.pid_wait_until(30_in);
  intakeStart(127);
  chassis.pid_wait();

  // Second Turn
  pros::delay(300);
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_drive_set(-22_in, 50, true);
  chassis.pid_wait();
  intakeStop();
  clampIn();
  pros::delay(600);

  // unjam.resume();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(200);

  groupStart(127);
  chassis.pid_drive_set(24_in, 50, true);
  chassis.pid_wait();

  pros::delay(200);
  chassis.pid_drive_set(-24_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, 50, true);
  chassis.pid_wait();

  pros::delay(1500);

  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(1000);
  // leftDoinkerOut();
  groupStop();
  // unjam.suspend();
  // unjam.resume();
  intakeStart(127);
  // pros::delay(1000);

  // unjam.suspend();

  pros::delay(1000);

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 60);
  chassis.pid_wait();
  pros::delay(200);
  groupStart(127);

  unjam.resume();
  conveyor.move(127);
  chassis.pid_drive_set(12_in, 30, true);
  chassis.pid_wait();

  pros::delay(1000);
  //
  // unjam.suspend();

  // unjam.suspend();

  chassis.pid_drive_set(-14_in, 40, true);
  chassis.pid_wait();
  groupStop();
  conveyor.move(127);

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  groupStop();
  chassis.pid_drive_set(-30_in, 60, true);
  chassis.pid_wait();

  conveyor.move(127);

  chassis.pid_drive_set(-44_in, 60, true);
  chassis.pid_wait();

  conveyor.brake();

  chassis.pid_turn_relative_set(185_deg, TURN_SPEED);
  chassis.pid_wait();

  leftDoinkerOut();
  chassis.pid_wait();

  chassis.pid_turn_relative_set(45_deg, 20);
  chassis.pid_wait();

  chassis.pid_drive_set(-1_in, 40, true);
  chassis.pid_wait();

  leftDoinkerIn();

  pros::delay(500);

  // unjam.resume();
  groupStart(127);

  chassis.pid_drive_set(15_in, 40, true);
  chassis.pid_wait();

  // pros::delay(1000);

  chassis.pid_drive_set(-5_in, 40, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-45_deg, 60);
  chassis.pid_wait();
  chassis.pid_drive_set(-5_in, 40, true);
  chassis.pid_wait();
  groupStop();
  // unjam.suspend();
  clampOut();
  chassis.pid_drive_set(-5_in, 40, true);
  chassis.pid_wait();

  // full MOGO

  chassis.pid_drive_set(18_in, 40, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0, 60);
  chassis.pid_wait();

  chassis.pid_drive_set(49_in, 60, true);
  chassis.pid_wait();
  // chassis.drive_angle_set(90_deg);
  intakeStart(127);

  chassis.pid_turn_set(90, 60);
  chassis.pid_wait();

  intakeStart(127);

  chassis.pid_drive_set(6_in, 60, true);
  chassis.pid_wait();
  // pros::delay(500);

  intakeStop();

  // unjam.suspend();
  unjam.suspend();
  // chassis.drive_angle_set(90_deg);
  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // ladybrown sequence

  ladyBrown.move(60);
  pros::delay(200);
  ladyBrown.brake();

  groupStart(127);

  chassis.pid_drive_set(10_in, 50, true);
  chassis.pid_wait();

  pros::delay(1000);

  groupStop();

  // chassis.pid_drive_set(4_in, 60, true);
  // chassis.pid_wait();

  // pros::delay(1000);
  chassis.pid_drive_set(4_in, 80, true);
  chassis.pid_wait();

  ladyBrown.move(100);
  chassis.pid_wait();
  chassis.pid_drive_set(2_in, 80, true);

  pros::delay(600);
  ladyBrown.brake();

  chassis.pid_drive_set(3_in, 60, true);
  chassis.pid_wait();

  pros::delay(1000);

  intakeStart(-127);

  chassis.pid_drive_set(-24_in, 60, true);
  chassis.pid_wait();

  intakeStop();

  // chassis.pid_drive_set(0_in, 0, true);
  // chassis.pid_wait();

  ladyBrown.move(-60);
  pros::delay(1000);
  ladyBrown.brake();

  // chassis.pid_wait();

  //end

  chassis.pid_drive_set(3_in, 40, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-34_in, 40, true);
  chassis.pid_wait();

  clampIn();
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  colorSorting.resume();

  groupStart(127);
  unjam.resume();
  chassis.pid_drive_set(28_in, 40, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, 40, true);
  chassis.pid_wait();

  colorSorting.suspend();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  groupStop();
  groupStart(127);

  // uncomment end

  leftDoinkerOut();
  // chassis.pid_wait();

  // chassis.drive_angle_set(45_deg);
  // chassis.pid_wait();

  chassis.pid_drive_set(13_in, 80, true);
  chassis.pid_wait();
  groupStop();

  chassis.pid_drive_set(-0.5_in, 80, true);
  chassis.pid_wait();

  chassis.pid_turn_set(125_deg, 40);
  chassis.pid_wait();

  leftDoinkerIn();

  chassis.pid_drive_set(-1.5_in, 80, true);
  chassis.pid_wait();

  chassis.pid_turn_set(60_deg, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, 80);
  chassis.pid_wait();

  chassis.pid_turn_set(-125_deg, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, 80);
  chassis.pid_wait();

  clampOut();

  pros::delay(500);

  chassis.pid_drive_set(26_in, 80);
  chassis.pid_wait();

  intakeStart(127);

  chassis.pid_turn_set(-90_deg, 80);
  chassis.pid_wait();

  conveyor.move(15);
  pros::delay(600);
  conveyor.brake();

  chassis.pid_drive_set(15_in, 80);
  chassis.pid_wait();

  intakeStop();

  leftDoinkerOut();
  chassis.pid_turn_set(-80_deg, 80);
  chassis.pid_wait();

  pros::delay(500);

  // chassis.pid_turn_set(270_deg, 40);
  // chassis.pid_wait();

  chassis.pid_turn_set(90_deg, 80);
  chassis.pid_wait();

  chassis.pid_drive_set(-33_in, 80);
  chassis.pid_wait();

  leftDoinkerIn();

  clampIn();

  conveyor.move(90);
  pros::delay(1200);
  conveyor.brake();

  chassis.pid_drive_set(-6_in, 80);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, 80);
  chassis.pid_wait();

  groupStart(127);

  chassis.pid_drive_set(12_in, 80);
  chassis.pid_wait();

  pros::delay(500);
  groupStop();
  conveyor.brake();

  // chassis.pid_turn_set(0_deg, 40);
  // chassis.pid_wait();

  // chassis.pid_turn_set(225_deg, TURN_SPEED);
  // chassis.pid_wait();
  // pros::delay(500);

  // chassis.pid_drive_set(-25_in, 80, true);
  // clampOut();
  // chassis.pid_wait();
  // unjam.suspend();

  // groupStop();
  // pros::delay(500);
  // chassis.pid_drive_set(50_in, 80, true);
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