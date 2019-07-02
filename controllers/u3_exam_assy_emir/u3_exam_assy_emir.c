#include <stdio.h>
#include <webots/motor.h>
#include <webots/robot.h>

static WbDeviceTag wheels[3];

static double cmd[5][3] = {
  {-2, 1, 1}, {0, 1, -1}, {2, -1, -1}, {0, -1, 1}, {2, 2, 2},
};

static double SPEED_FACTOR = 4.0;

int main() {
  int i, j, k;

  // initialize Webots
  wb_robot_init();

  for (i = 0; i < 3; i++) {
    char name[64];
    sprintf(name, "wheel%d", i + 1);
    wheels[i] = wb_robot_get_device(name);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  while (1) {
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 3; j++)
        wb_motor_set_velocity(wheels[j], cmd[i][j] * SPEED_FACTOR);

      for (k = 0; k < 100; k++)
        wb_robot_step(8);
    }
  }

  return 0;
}