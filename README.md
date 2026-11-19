# ISE-VA-ESIGELEC

Coursework from my engineering degree at **ESIGELEC** (Rouen), major **Embedded Systems – Autonomous Vehicles (ISE-VA)**, 2023–2025.
Each folder is one module: lab reports, code and notebooks, mostly done in pairs.

![Python](https://img.shields.io/badge/Python-3776AB?logo=python&logoColor=white)
![C/C++](https://img.shields.io/badge/C%2FC%2B%2B-00599C?logo=cplusplus&logoColor=white)
![MATLAB](https://img.shields.io/badge/MATLAB-0076A8)
![ROS](https://img.shields.io/badge/ROS1%20Noetic-22314E?logo=ros&logoColor=white)
![CUDA](https://img.shields.io/badge/CUDA-76B900?logo=nvidia&logoColor=white)
![Unity](https://img.shields.io/badge/Unity-000000?logo=unity&logoColor=white)

## Modules

| Module | What I did | Tools |
|---|---|---|
| [Data Fusion for Localization](Fusion%20de%20Donn%C3%A9es%20pour%20la%20Localisation/) | Vehicle localization by sensor fusion (particle filter) | Python, Jupyter |
| [AI for Autonomous Vehicles](Intelligence%20Artificielle%20pour%20le%20V%C3%A9hicule%20Autonome/) | Machine-learning and neural-network labs for perception and decision | Python, scikit-learn, PyTorch, TensorFlow/Keras |
| [Software Quality Methods & Tools](M%C3%A9thodes%20et%20Outils%20pour%20la%20Qualit%C3%A9%20Logicielle/) | Code review, unit testing and MISRA-C static analysis on embedded C projects (cash register, robot) | C, CppCheck (MISRA) |
| [Trajectory Planning & Tracking](Planification%20%26%20Suivi%20de%20Trajectoire/) | TurtleBot3 simulation: mapping (gmapping), localization (AMCL), navigation in custom worlds | ROS1 Noetic, Gazebo |
| [Parallel Programming](Programmation%20Parall%C3%A8le/) | Benchmarks, then Conway's Game of Life parallelized with threads (CPU) and CUDA (GPU) | C/C++, threads, CUDA |
| [ADAS Prototyping with RT-Maps](Prototypage%20ADAS%20avec%20RT-Maps/) | LIDAR stream processing to detect cars and pedestrians | RT-Maps |
| [Mobile Robotics & Perception](Robotique%20Mobile%20%26%20Perception/) | Navigation and person-following with a DJI RoboMaster (camera-based detection) | Python, RoboMaster SDK |
| [Augmented Reality](R%C3%A9alit%C3%A9%20Augment%C3%A9e/) | Marker-based AR game ("chamboule-tout") | Unity, C# |
| [Computer Vision](Vision%20par%20Ordinateur/) | Color spaces, image enhancement, chroma key, template matching | MATLAB, Python, OpenCV |

## Getting started

```bash
git clone https://github.com/Baackuup/ISE-VA-ESIGELEC.git
cd ISE-VA-ESIGELEC
pip install -r requirements.txt   # for the Python notebooks
jupyter notebook
```

Module-specific setup:
- **ROS** (Trajectory Planning): ROS1 Noetic on Ubuntu 20.04, then `source /opt/ros/noetic/setup.bash`, build with `catkin_make` in `catkin_ws/` and run one of the `.launch` files. See the module's README.
- **RT-Maps**: requires a license (free for students), see the module's README.
- **Unity**: see the module's README.
- **MATLAB** scripts (Computer Vision) run as-is with the Image Processing Toolbox.

## Authors

- [Paul Bligny](https://github.com/Baackuup)
- Nathan Pivon, lab partner on most modules

Lab subjects and some starter code were provided by ESIGELEC teaching staff.

---

Contact: [github.com/Baackuup](https://github.com/Baackuup)
