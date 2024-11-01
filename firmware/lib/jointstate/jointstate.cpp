
#include "jointstate.h"

JointState::JointState()
{

    rosidl_runtime_c__String string_buffer[4];

    joint_msg_.name.data = string_buffer;
    joint_msg_.name.size = 0;
    joint_msg_.name.capacity = 4;


    for (int i = 0; i < 4; i++)
    {
        //joint_msg_.name.data[i].data = names[i];
        joint_msg_.name.data[i].size = 4;
        joint_msg_.name.data[i].capacity = 20;
    }

    char m1[] = "motor1";
    char m2[] = "motor2";
    char m3[] = "motor3";
    char m4[] = "motor4";

    joint_msg_.name.data[0].data = m1;
    joint_msg_.name.data[1].data = m2;
    joint_msg_.name.data[2].data = m3;
    joint_msg_.name.data[3].data = m4;

    double joint_states_pos_buffer[] = {0,0,0,0};
    double joint_states_vel_buffer[] = {0,0,0,0};
    double joint_states_eff_buffer[] = {0,0,0,0};

    joint_msg_.position.data = joint_states_pos_buffer;
    joint_msg_.position.size = 4;
    joint_msg_.position.capacity = 4;

    joint_msg_.velocity.data = joint_states_vel_buffer;
    joint_msg_.velocity.size = 4;
    joint_msg_.velocity.capacity = 4;

    joint_msg_.effort.data = joint_states_eff_buffer;
    joint_msg_.effort.size = 4;
    joint_msg_.effort.capacity = 4;


}

void JointState::update(float rpm1, float rpm2, float rpm3, float rpm4)
{
    joint_msg_.velocity.data[0] = rpm1;
    joint_msg_.velocity.data[1] = rpm2;
    joint_msg_.velocity.data[2] = rpm3;
    joint_msg_.velocity.data[3] = rpm4;
    
}

sensor_msgs__msg__JointState JointState::getData()
{
    return joint_msg_;
}

