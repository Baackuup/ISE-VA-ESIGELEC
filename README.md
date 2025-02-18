# ISE-VA-ESIGELEC

Welcome to the **ISE-VA-ESIGELEC** department repository! This repo combines several modules covered in class: data fusion, artificial intelligence, trajectory planning and tracking, and software quality methods and tools.

## Table of Contents

- [Repository Description](#repository-description)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [Contributors](#contributors)
- [License](#license)

## Repository Description

This repository consists of several modules:

1. **Data Fusion for Localization**: Implementation of advanced data fusion methods to improve the accuracy and reliability of vehicle localization (e.g., Particle Filter).
2. **Artificial Intelligence for Autonomous Vehicles**: Decision-making algorithms based on neural networks and machine learning.
3. **Software Quality Methods and Tools**: Unit testing, verification tools, and best practices to ensure software robustness.
4. **Trajectory Planning & Tracking**: Implementation of algorithms to plan and follow optimal trajectories on ROS1 Neotic.
5. **Parallel Programming**: Exploration of parallel programming techniques to enhance application performance.
6. **ADAS Prototyping with RT-Maps**: Usage of RT-Maps to visualize a LIDAR stream and identify car and pedestrian targets.
7. **Mobile Robotics and Perception**: Implementation of algorithms for mobile robot navigation and environmental perception.
8. **Augmented Reality**: Development of augmented reality applications to enhance user interaction and visualization.

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
|-- Fusion de Données pour la Localisation/
|-- Intelligence Artificielle pour le Véhicule Autonome/
|-- Méthodes et Outils pour la Qualité Logicielle/
|-- Planification & Suivi de Trajectoire/
|-- Programmation Parallèle/
|-- Prototypage ADAS avec RT-Maps/
|-- Robotique Mobile & Perception/
|-- Réalité Augmentée/
|-- Vision par Ordinateur
|-- README.md
|-- SECURITY.md
|-- requirements.txt
```

- Each folder contains folders and files related to a specific module.
- `requirements.txt` includes the necessary Python dependencies.

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
   - Set up your ROS environment:
     ```bash
     source /opt/ros/noetic/setup.bash
     ```
   - Launch ROS nodes:
     ```bash
     roslaunch [current_package] [application].launch
     ```

## Contributors

- [Paul BLIGNY](https://github.com/Baackuup)

## License

This project is licensed under the [MIT](LICENSE). You are free to use, modify, and distribute it, provided you retain the copyright and license.

---

Contact: blignypaul@gmail.com
