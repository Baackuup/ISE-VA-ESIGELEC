# ISE-VA-ESIGELEC

Welcome to the **ISE-VA-ESIGELEC** department repository! This repo combines several modules covered in class: data fusion, artificial intelligence, trajectory planning and tracking, and software quality methods and tools.

## Table of Contents

- [Project Description](#project-description)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [Usage](#usage)
- [Contributors](#contributors)
- [License](#license)

## Repository Description

This repository consists of several modules:

- **Data Fusion for Localization**: Implementation of advanced data fusion methods to improve the accuracy and reliability of vehicle localization.
- **Artificial Intelligence for Autonomous Vehicles**: Decision-making algorithms based on neural networks and machine learning.
- **Software Quality Methods and Tools**: Unit testing, verification tools, and best practices to ensure software robustness.
- **Trajectory Planning & Tracking**: Implementation of algorithms to plan and follow optimal trajectories.

## Prerequisites

Before starting, make sure you have the following tools and environments installed:

- **Python** (>= 3.8)
- **ROS1**
- **Python Libraries**:
  - `numpy`
  - `pandas`
  - `matplotlib`
  - `scikit-learn`
- **CMake** and a compatible compiler (GCC or Clang)
- Jupyter Notebook (if you wish to run the included notebooks)

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/Baackuup/ISE-VA-ESIGELEC.git
   cd ISE-VA-ESIGELEC
   ```
2. Install Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Set up ROS and CMake environments depending on the modules you wish to use.

## Project Structure

The repository is organized as follows:

```plaintext
ISE-VA-ESIGELEC/
|— Data Fusion for Localization/
|— Artificial Intelligence for Autonomous Vehicles/
|— Software Quality Methods and Tools/
|— Trajectory Planning & Tracking/
    |— catkin_ws/
|— README.md
|— requirements.txt
```

- Each folder contains files related to a specific module.
- `requirements.txt` includes the necessary Python dependencies.

## Usage

### Example of Running a Module

1. **Data Fusion for Localization**:
   - Navigate to the corresponding folder:
     ```bash
     cd "Data Fusion for Localization"
     ```
   - Launch a Jupyter notebook:
     ```bash
     jupyter notebook
     ```
   - Run the cells to view the results.

2. **Trajectory Planning & Tracking**:
   - Set up your ROS2 environment:
     ```bash
     source /opt/ros/foxy/setup.bash
     ```
   - Launch ROS nodes:
     ```bash
     ros launch trajectoire_planner planner_launch.py
     ```

## Contributors

- [Paul BLIGNY](https://github.com/Baackuup)

## License

This project is licensed under the [MIT](LICENSE). You are free to use, modify, and distribute it, provided you retain the copyright and license.

---

Contact: blignypaul@gmail.com
