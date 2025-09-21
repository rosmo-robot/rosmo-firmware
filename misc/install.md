cd ~/ros2_ws/src
chmod +x install_flexbe_webui_ros2_full.sh
./install_flexbe_webui_ros2_full.sh


New terminal

source ~/ros2_ws/install/setup.bash
source ~/ros2_ws/.flexbe_env
ros2 launch flexbe_webui flexbe_ocs.launch.py
