/**
 * @file ci_command.h
 * @brief Implementation of the communication protocol between the arduino and
 * the controlling computer.
 *
 * @date 25 sept. 2014
 * @author carrier.nicolas0@gmail.com
 */
#ifndef CI_COMMAND_H_
#define CI_COMMAND_H_
#include <stdbool.h>
#include <inttypes.h>


#ifdef __cplusplus
extern "C" {
#endif

#define CI_COMMAND_START 0x55

struct __attribute__ ((__packed__)) ci_command {
	uint8_t start_byte;
	int16_t left_motor_speed;
	int16_t right_motor_speed;
	uint8_t servo_angle;
	uint8_t camera_x_angle;
	uint8_t camera_z_angle;
	uint8_t beep; /* boolean, but uint8_t required to control the size */
	uint8_t checksum;
};

#define CI_COMMAND_LENGTH (sizeof(struct ci_command))

int ci_command_complete(struct ci_command *cmd);

void ci_command_dump(struct ci_command *cmd, void (*printer)(const char *));

bool ci_command_is_valid(struct ci_command *cmd);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CI_COMMAND_H_ */
