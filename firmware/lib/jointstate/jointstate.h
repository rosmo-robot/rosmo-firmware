
#ifndef jointstate_H
#define jointstate_H

#include <Arduino.h>
#include <micro_ros_utilities/type_utilities.h>
#include <micro_ros_utilities/string_utilities.h>
#include <sensor_msgs/msg/joint_state.h>
#include "config.h"


class JointState
{
    public:
        JointState();
        void update(float rpm1, float rpm2, float rpm3, float rpm4);
        sensor_msgs__msg__JointState getData();

    private:

        sensor_msgs__msg__JointState joint_msg_;

};

#endif
