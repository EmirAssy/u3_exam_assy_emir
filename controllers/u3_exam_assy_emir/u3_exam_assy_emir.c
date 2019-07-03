#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <math.h>
#include <stdio.h>

#define PI 3.1416
#define TIME_STEP 64
#define OBSTACLE_DISTANCE 20.0

int main(int argc, char **argv)
{

  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);

  int pressed_key;
  
   double ds_value1 = 0;
   double ds_value2 = 0;
   double Encoder1 = 0;
   double Encoder2 = 0;
   double Encoder3 = 0;
   double Comparador = 0;
   int turn_left = 0;
   int turn_right = 0;
  
    // Motor devices
   WbDeviceTag wheelR = wb_robot_get_device("wheel1");
   WbDeviceTag wheelL = wb_robot_get_device("wheel2");
   WbDeviceTag wheelB = wb_robot_get_device("wheel3");

   wb_motor_set_position (wheelR, INFINITY);
   wb_motor_set_position (wheelL, INFINITY);
   wb_motor_set_position (wheelB, INFINITY);

   //Distance sensor devices
   WbDeviceTag dist_sensor1 = wb_robot_get_device("distance_sensor1");
   WbDeviceTag dist_sensor2 = wb_robot_get_device("distance_sensor2");
   wb_distance_sensor_enable(dist_sensor1, TIME_STEP);
   wb_distance_sensor_enable(dist_sensor2, TIME_STEP);
   
   //encoder devices
   WbDeviceTag encoder_1 = wb_robot_get_device("encoder1");
   WbDeviceTag encoder_2 = wb_robot_get_device("encoder2");
   WbDeviceTag encoder_3 = wb_robot_get_device("encoder3");
   wb_position_sensor_enable(encoder_1, TIME_STEP);
   wb_position_sensor_enable(encoder_2, TIME_STEP);
   wb_position_sensor_enable(encoder_3, TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1) {

     pressed_key= wb_keyboard_get_key();

     ds_value1 = wb_distance_sensor_get_value (dist_sensor1);
     printf("Distance sensor1: %lf\n", ds_value1);
     ds_value2 = wb_distance_sensor_get_value (dist_sensor2);
     printf("Distance sensor2: %lf\n", ds_value2);
   
     Encoder1 = wb_position_sensor_get_value(encoder_1);
     printf("encoder_1: %lf\n", Encoder1);
     Encoder2 = wb_position_sensor_get_value(encoder_2);
     printf("encoder_2: %lf\n", Encoder2);
     Encoder3 = wb_position_sensor_get_value(encoder_3);
     printf("encoder_3: %lf\n", Encoder3);

     printf("Comparador: %lf\n",Comparador ); 

     if (pressed_key == WB_KEYBOARD_UP)
     {
       wb_motor_set_velocity (wheelR, -6.36);
       wb_motor_set_velocity (wheelL, 6.36);
       wb_motor_set_velocity (wheelB, 0);
     }
    
     else if (pressed_key == WB_KEYBOARD_DOWN)
     {
       wb_motor_set_velocity (wheelR, 6.36);
       wb_motor_set_velocity (wheelL, -6.36);
       wb_motor_set_velocity (wheelB, 0);
     }
    
     else if (pressed_key == WB_KEYBOARD_RIGHT)
     {
       wb_motor_set_velocity (wheelR, 6.36);
       wb_motor_set_velocity (wheelL, 0);
       wb_motor_set_velocity (wheelB, -6.36);
     }
    
     else if (pressed_key == WB_KEYBOARD_LEFT)
     {
       wb_motor_set_velocity (wheelR, 0);
       wb_motor_set_velocity (wheelL, -6.36);
       wb_motor_set_velocity (wheelB, 6.36);
     }
    
     else if(pressed_key == 'S' ){
      Comparador = Encoder1 + 0.785398;
      turn_left = 1;
     }

     else if(turn_left == 1){

      if(Encoder1 <= Comparador){
       wb_motor_set_velocity(wheelL, 6.36);
       wb_motor_set_velocity(wheelR, 6.36);
       wb_motor_set_velocity(wheelB, 6.36);
     }
    
     else{
       wb_motor_set_velocity(wheelL, 0);
       wb_motor_set_velocity(wheelR, 0);
       wb_motor_set_velocity(wheelB, 0);
       turn_left = 0;
     }

     }

     else if(pressed_key == 'A' ){
       Comparador = Encoder1 - 0.785398;
       turn_right = 1;
     }
    
     else if(turn_right == 1){

      if(Encoder1 >= Comparador){
        wb_motor_set_velocity(wheelL, -6.36);
        wb_motor_set_velocity(wheelR, -6.36);
        wb_motor_set_velocity(wheelB, -6.36);
      }

      else{
        wb_motor_set_velocity(wheelL, 0);
        wb_motor_set_velocity(wheelR, 0);
        wb_motor_set_velocity(wheelB, 0);
        turn_right = 0;
      }
     }

     else{
        wb_motor_set_velocity(wheelL, 0);
        wb_motor_set_velocity(wheelR, 0);
        wb_motor_set_velocity(wheelB, 0);
     }
  };

  wb_robot_cleanup();

  return 0;
}