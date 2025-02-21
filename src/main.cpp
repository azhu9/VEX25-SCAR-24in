#include "main.h"
#include <string>
#include "pros/motors.h"
#include "subsystems.hpp"
#include "helpers.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {2, -3, 4, -5, -6},      // Left Chassis Ports (negative port will reverse it!)
    {11, -12, 13, -14, 15},  // Right Chassis Ports (negative port will reverse it!)

    8,    // IMU Port
    2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    600);  // Wheel RPM

// void lbMove(int target, int timeout){
//   int target_position = target;
//   int pressTime = pros::millis();

//   while (abs(position) < target_position) {
//     int curTime = pros::millis();
//     position = lb_rotation.get_position();
//     ladyBrown.move(40); //55
//     pros::delay(20);

//     if(curTime - pressTime > timeout) break;
//   }
  
// }

void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(2);     // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(2.5, 3.5);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  default_constants();

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      // Auton("BLUE Positive goal rush \n Use Alignemnt tool", blueMatch),
      // Auton("RED Positive goal rush \n Use Alignemnt tool", redMatch),
      // Auton("RED SAFE Positive goal rush \n Use Alignemnt tool", redMatchSafe),
      // Auton("RED SAFE Positive goal rush \n Use Alignemnt tool", intakeTest),
      Auton("SKILLS \n Align against wallstake", skills),
      // Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      // Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      // Auton("Combine all 3 movements", combining_movements),
      // Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
  lb_rotation.reset();

  // ez::Piston flipper('G');   //UNCOMMENT FOR DRIVER CODE
  // flipper.set(true);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

void opcontrol() {
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_BRAKE;

  chassis.drive_brake_set(driver_preference_brake);

  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);



  lb_rotation.set_position(0);
  int lastPressTime = 0;
  const int doublePressThreshold = 175;


  while (true) {
    // chassis.opcontrol_tank();  // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT);  // Standard split arcade

    if (master.get_digital(DIGITAL_R1)) {
      intake.move(127);
      conveyor.move(127);
    } else if (master.get_digital(DIGITAL_R2)) {
      intake.move(-127);
      conveyor.move(-127);
    } else {
      intake.brake();
      conveyor.brake();
    }

    clampPiston.button_toggle(master.get_digital(DIGITAL_B));

    leftDoinker.set(master.get_digital(DIGITAL_Y) && !flipperPiston.get());

    rightDoinker.set(master.get_digital(DIGITAL_RIGHT) && !flipperPiston.get());

    flipperPiston.set(master.get_digital(DIGITAL_DOWN) && !rightDoinker.get() && !leftDoinker.get());


    position = lb_rotation.get_position();

    if(position == INT_MAX || position == INT_MIN) master.set_text(0, 0, "LB ERROR");

    pros::lcd::print(1, "Rotation: %i", position);
    master.set_text(0, 0, "r : " +std::to_string(position));

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      int currentTime = pros::millis();

      if (currentTime - lastPressTime <= doublePressThreshold) {
        lbMove(3000, 1000); //function in helpers.hpp
  
        ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        master.rumble(".");
      }

      lastPressTime = currentTime; // Update last press time
  }

    if (master.get_digital(DIGITAL_L1)) {
      ladyBrown.move(127);
    } else if (master.get_digital(DIGITAL_L2)) {
      ladyBrown.move(-127);
      pros::delay(80);
      lb_rotation.set_position(0);
    } else {
      ladyBrown.brake();
    }




    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}