cd ~/ros2_ws/src

wget https://raw.githubusercontent.com/rosmo-robot/rosmo-firmware/refs/heads/main/misc/flexbeWebUI_Install.sh

chmod +x install_flexbe_webui_ros2_full.sh

./install_flexbe_webui_ros2_full.sh

sudo apt install python3-catkin-*

pip install numpy lark empy catkin_pkg typeguard jinja2 pyyaml pytest


-New terminal

git clone https://github.com/flexbe/flexbe_turtlesim_demo.git

rosdep update

rosdep install --from-paths src --ignore-src

colcon build

source install/local_setup.bash

export TURTLEBOT3_MODEL=burger

ros2 launch flexbe_app flexbe_ocs.launch.py use_sim_time:=True

- In webui play with behaviours


-New terminal 

source install/local_setup.bash

export TURTLEBOT3_MODEL=burger

ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py







