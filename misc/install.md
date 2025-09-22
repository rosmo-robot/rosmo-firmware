cd ~/ros2_ws/src

wget https://raw.githubusercontent.com/rosmo-robot/rosmo-firmware/refs/heads/main/misc/flexbeWebUI_Install.sh

chmod +x install_flexbe_webui_ros2_full.sh

./install_flexbe_webui_ros2_full.sh

sudo apt install python3-catkin-*

pip install numpy lark empy catkin_pkg typeguard jinja2 pyyaml pytest


New terminal
git clone https://github.com/flexbe/flexbe_turtlesim_demo.git
rosdep update
rosdep install --from-paths src --ignore-src
colcon build
setup.bash


export TURTLEBOT3_MODEL=burger

ros2 launch flex_nav_turtlebot3_demo flex_nav_turtlebot3_demo.launch.py


