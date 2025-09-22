cd ~/ros2_ws/src

wget https://raw.githubusercontent.com/rosmo-robot/rosmo-firmware/refs/heads/main/misc/flexbeWebUI_Install.sh

chmod +x install_flexbe_webui_ros2_full.sh

./install_flexbe_webui_ros2_full.sh

sudo apt install python3-catkin-*

pip install numpy lark empy catkin_pkg typeguard jinja2 pyyaml pytest

New terminal

ros2 launch flexbe_webui flexbe_ocs.launch.py


