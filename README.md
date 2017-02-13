# Overview
This ROS package creates a ROS node which publishes raw data from the Thalmic Labs Myo Armband (tested with firmware version 1.1.4.2) in the form of both standard and custom ROS messages. These messages can be subscribed to and used in standard ROS architectures. To learn more about how to run the ros-myo examples or on the topics and messages involved, see the [wiki](https://github.com/roboTJ101/ros_myo/wiki) page.

Special thanks to Danny Zhu for creating the initial [myo-raw](https://github.com/dzhu/myo-raw) interface, which allowed for access to the raw data streaming from the Myo.

# Requirements
 - python >=2.6
 - pySerial
 - enum34

# Topics and Messages
There are three topics generated by the myo-rawNode.py node. These are:
  1. /myo_imu - a standard IMU message with quaternion pose, accelerometer and gyro axes
  2. /myo_arm - Arm: a custom arm Arm message populated after calibration that shows current arm and orientation on the arm
  3. /myo_emg - EmgArray: a custom message that is comprised of the EMG readings from the eight sensors
  4. /myo_gest - Gesture data populated after calibration (UInt8 value of enumerated poses)

# License
ros_myo is released with the MIT License. For full terms and conditions, see the [LICENSE](LICENSE) file

# Aggiunte

per trovare BT
ls /dev/ttyACM*

per i permessi:
sudo chmod a+rw /dev/ttyACM0
sudo chmod a+rw /dev/ttyACM1

MYO DATA
rosrun ros_myo myo-rawNode.py /dev/ttyACM0 -c con1
rosrun ros_myo myo-rawNode.py /dev/ttyACM1 -c con2

Feedback
rostopic pub /myo_vib1 std_msgs/UInt8 1