/*
 * This file is part of libci.
 *
 *  libci is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libci is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with libci.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2015 Nicolas CARRIER <carrier dot nicolas0 at gmail dot com>
 */
/**
 * @file ci_command.c
 * @brief Implementation of the communication protocol between a vehicle and the
 * controlling device.
 *
 * @date 25 sept. 2014
 * @author carrier.nicolas0@gmail.com
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#ifndef EINVAL
#define EINVAL 22
#endif /* EINVAL */

#include <ci_command.h>

/**
 * @def DUMP_BUF_SIZE
 * @brief maximum size of the buffer used for logging a command
 */
#define DUMP_BUF_SIZE 0x400

/**
 * Compute a simplist checksum by xor-ing all the bytes in a buffer
 * @param cmd command to compute the checksum of
 * @return 0xFF if cmd is NULL, the checksum otherwise
 */
static uint8_t checksum(struct ci_command *cmd)
{
	size_t len;
	uint8_t *buf;
	uint8_t checksum = 0;

	if (cmd == NULL)
		return 0xFF;

	len = sizeof(*cmd) - 1;
	buf = (uint8_t *)cmd;

	while (len--)
		checksum ^= buf[len];

	return checksum;
}

int ci_command_complete(struct ci_command *cmd)
{
	if (cmd == NULL)
		return -EINVAL;

	cmd->start_byte = CI_COMMAND_START;
	cmd->checksum = checksum(cmd);

	return 0;
}

void ci_command_dump(struct ci_command *cmd,
		void (*printer)(const char *))
{
	char buf[DUMP_BUF_SIZE];

	snprintf(buf, DUMP_BUF_SIZE,
			"servo_angle %"PRIu8
			", left_motor_speed %"PRIi16
			", right_motor_speed %"PRIi16
			", camera_x_angle %"PRIu8
			", camera_z_angle %"PRIu8
			", beep %d",
			cmd->servo_angle,
			cmd->left_motor_speed,
			cmd->right_motor_speed,
			cmd->camera_x_angle,
			cmd->camera_z_angle,
			cmd->beep);

	printer(buf);
}

bool ci_command_is_valid(struct ci_command *cmd)
{
	return checksum(cmd) == cmd->checksum &&
			cmd->start_byte == CI_COMMAND_START;
}
