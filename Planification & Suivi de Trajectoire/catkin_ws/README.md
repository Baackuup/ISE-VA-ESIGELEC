# ROS Noetic Installation and Testing Guide

This guide provides step-by-step instructions for setting up ROS 1 - Noetic on a virtual machine using VMware and Ubuntu 20.04. By the end, you will have a functional ROS environment, complete with testing using Turtlesim.

---

## Prerequisites
- **VMware Workstation Player**: A free, non-commercial virtualization software.
- **Ubuntu 20.04 ISO file**: A compatible operating system for ROS Noetic.
- **Internet Access**: Required for downloading and updating packages.

---

## Installation Steps

### 1. Download VMware Workstation Player
- Visit the official VMware website and download the free version of VMware Workstation Player:
  [VMware Workstation Player](https://www.vmware.com/au/products/workstation-player/workstation-player-evaluation.html)

### 2. Download Ubuntu 20.04
- Download the Ubuntu 20.04 ISO file from the official Ubuntu releases page:
  [Ubuntu 20.04 Download](https://releases.ubuntu.com/focal/)

### 3. Install Ubuntu 20.04 on VMware
- Open VMware Workstation Player.
- Select **"Create a New Virtual Machine"**.
- Follow the on-screen instructions and use the Ubuntu 20.04 ISO file downloaded in step 2.
- Complete the setup process to install Ubuntu.

### 4. Install ROS 1 - Noetic
- Once Ubuntu is installed and running in VMware, open a terminal.
- Follow the official ROS Noetic installation guide:
  [ROS Noetic Installation Guide](https://wiki.ros.org/noetic/Installation/Ubuntu)

### 5. Test the ROS Installation

#### a. Start the ROS Master
- Open a terminal and type the following command:
  ```bash
  roscore
  ```
- You should see output confirming that the ROS Master has started successfully.

#### b. Launch Turtlesim
- Open a new terminal and run:
  ```bash
  rosrun turtlesim turtlesim_node
  ```
- A Turtlesim window should appear, showing a turtle in a virtual environment.

#### c. Control the Turtle
- Open another terminal and type:
  ```bash
  rosrun turtlesim turtle_teleop_key
  ```
- Use your keyboard to control the turtle in the Turtlesim window.

---

## Notes

1. **Password Management**
   - Students will require a password to log in to VMware and access ROS. It is recommended to assign a general password for all users.

2. **Internet Access**
   - Ensure students have internet access (without admin permissions) to update and install ROS packages during the course.

3. **Additional Support**
   - If you encounter issues or have questions, refer to the [ROS Wiki](https://wiki.ros.org/) or reach out to the course instructor.

---

This concludes the installation and testing process. Happy learning with ROS!
