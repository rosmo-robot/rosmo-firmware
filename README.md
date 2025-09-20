This firmware is a derivative of https://github.com/hippo5329/linorobot2_hardware and has much of the functionality.

It is compatible with this code on your main robot computer https://github.com/hippo5329/linorobot2 the robot computer can communicate with the ESP32 over wifi

The target hardware is https://rosmo-robot.github.io/ 


For launching docker
sudo docker run -p 6080:80 --security-opt seccomp=unconfined --privileged -t -i --device=/dev/tty/ACM0 --shm-size=512m rosmo:latest

Inside docker
ros2 launch linorobot2_description descirption.launch.py
