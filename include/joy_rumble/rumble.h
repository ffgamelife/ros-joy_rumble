/*
 * rumble.h
 *
 *  Created on: 22.09.2014
 *      Author: fnolden
 */

#ifndef RUMBLE_H_
#define RUMBLE_H_

#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <joy_rumble/Rumble_msg.h>
#include <boost/circular_buffer.hpp>

class Rumble {
public:
	Rumble();
	void init(ros::NodeHandle &nh);
	bool open_device();
	void write_force(uint16_t length = 0x00f0, uint16_t direction = 0x8000, uint16_t weak = 0x0, uint16_t strong = 0xffff );
	void callback_imu(const sensor_msgs::Imu::ConstPtr &msg );
	void callback_rumble(const joy_rumble::Rumble_msg::ConstPtr &msg );
	uint16_t calculate_force(double delta, double min, double max);
	//bool callback_rumble_msg(sensor_msgs::ImuPtr &ptr );
	ros::Subscriber sub_rumble;
	ros::Subscriber sub_imu;
	double imu_velo_old[3];
	double imu_acc_old[3];
	double max_delta_acc;
	double max_delta_velo;
	uint16_t min_rumble;
	double velo_delta[2]; // min, max vibration at delta
	double acc_delta[2];
	int ff_fd;

	virtual ~Rumble();
private:
	std::string event;
	std::string sub_topic_imu;
	std::string sub_topic_rumble;
	int update_rate;
	int nr_simultaneous_effects;
	boost::circular_buffer<input_event> *ptr_effect_buffer;
	std::string node_name;

};

#endif /* RUMBLE_H_ */
