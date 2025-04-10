# Readme

This code repo is used for export slamware robot c++ sdk to python modules. Generally, we can access most of the functions of slamware functions by http based RESTful APIs, but two functions are only supported by cpp APIs:
1. move with specific linear speed and angular speed. (when you use joystick to control the robot, you hope to convert the jostick command to speed).
2. read stmc map. stmc map is a custom format designed by slamware. You can only parse it by c++ sdk.

This repos is based on [the official sdks with GCC-9.0](https://www.slamtec.com/en/support#apollo). I have implmented the above function 1.

## Quick Start
```bash
cd samples/movebyspeed
make all
python test.py
```
Backups:
1. You may need to check your python version and specify the python path in `./samples/movebyspeed/Makefile:5`
2. You may need to download `pybind11` before exporting cpp program to python module.

