
#!/bin/bash
rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState "model_name: 'turtlebot3_burger'
pose:
  position:
    x: -1.0
    y: 1.5
    z: 0.0
  orientation:
    x: 0.0
    y: 0.0
    z: 0.0
    w: 1.0
twist:
  linear:
    x: 0.0
    y: 0.0
    z: 0.0
  angular:
    x: 0.0
    y: 0.0
    z: 0.0
reference_frame: 'world'"
