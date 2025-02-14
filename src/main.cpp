#include "main.h"
#include "pros/motors.h"

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
      // Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      // Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
  lb_rotation.reset();

  ez::Piston flipper('G');
  flipper.set(true);
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

  ez::Piston clamp('A', false);
  ez::Piston flipper('G', false);
  ez::Piston leftDoinker('H', false);
  ez::Piston rightDoinker('D', false);

  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  bool clampDeployed = false;
  bool flipperDeployed = false;
  bool leftDoinkerDeployed = false;
  bool rightDoinkerDeployed = false;

  int position = lb_rotation.get_position();

  ez::PID lbPID{0.2, 0.001, 0.02, 0.0, "ladyBrown"};
  lb_rotation.set_position(0);
  int lastPressTime = 0;
  const int doublePressThreshold = 200;


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

    // if (master.get_digital_new_press(DIGITAL_B)) {
    //   clampDeployed = !clampDeployed;
    //   clamp.set(clampDeployed);
    // }
    clamp.button_toggle(master.get_digital(DIGITAL_B));

    if (master.get_digital(DIGITAL_Y) && !flipperDeployed) {
      leftDoinkerDeployed = true;
    }else{
      leftDoinkerDeployed = false;
    }

    if(leftDoinkerDeployed){
      leftDoinker.set(true);
    }else{
      leftDoinker.set(false);
    }

    if (master.get_digital(DIGITAL_RIGHT) && !flipperDeployed) {
      rightDoinkerDeployed = true;
    }else{
      rightDoinkerDeployed = false;
    }

    if(rightDoinkerDeployed){
      rightDoinker.set(true);
    }else{
      rightDoinker.set(false);
    }

    if (master.get_digital(DIGITAL_DOWN) && !rightDoinkerDeployed && !leftDoinkerDeployed) {
      flipperDeployed = true;
    }else{
      flipperDeployed = false;
    }

    if(flipperDeployed){
      flipper.set(true);
    }else{
      flipper.set(false);
    }


    position = lb_rotation.get_position();
    pros::lcd::print(1, "Rotation: %i", position);


    // if (master.get_digital_new_press(DIGITAL_X)) {

    //   // lb_rotation.reset_position();
    //   int target_position = 2400;
    //   int slow_speed = 127;

    //   while (abs(position) < target_position) {
    //     position = lb_rotation.get_position();
    //     ladyBrown.move(40);
    //     pros::delay(20);
    //   }

    //   ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    //   master.rumble(".");

    //   // ladyBrown.brake();
    // }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      int currentTime = pros::millis();

      if (currentTime - lastPressTime <= doublePressThreshold) {
        int target_position = 3000;
        int slow_speed = 127;
  
        while (abs(position) < target_position) {
          position = lb_rotation.get_position();
          ladyBrown.move(55);
          pros::delay(20);
        }
  
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