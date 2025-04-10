#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <regex>
#include <string>

// Slamware SDK headers
#include <rpos/robot_platforms/slamware_core_platform.h>
#include <rpos/features/motion_planner.h>
#include <rpos/features/location_provider/map.h>   // If you really need this
#include <rpos/features/motion_planner/velocity_control_move_action.h>

namespace py = pybind11;

using namespace rpos::robot_platforms;
using namespace rpos::features;
using namespace rpos::actions;

// A small regex to validate basic IPv4 format
static const char* ipReg = "\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}";

class SlamwareVelocityController {
public:
    // Constructor
    explicit SlamwareVelocityController(const std::string& ipAddress)
    {
        std::cout << "You open Slamware Velocity Controller." << std::endl;
        // Validate IP
        if (!std::regex_match(ipAddress, std::regex(ipReg))) {
            throw std::invalid_argument("Invalid IP address format");
        }

        // Connect to Slamware
        try {
            // IMPORTANT: assign to the class member sdp_, not a local variable
            sdp_ = SlamwareCorePlatform::connect(ipAddress, 1445);
            std::cout << "[Slamware CXX velocity controller] Connection established!\n";
            velocityAction_ = sdp_.velocityControl();
        }
        catch (ConnectionTimeOutException &e) {
            std::cerr << "[Slamware CXX velocity controller] Connection timed out: " << e.what() << std::endl;
            throw;
        }
        catch (ConnectionFailException &e) {
            std::cerr << "[Slamware CXX velocity controller] Connection failed: " << e.what() << std::endl;
            throw;
        }
    }

    ~SlamwareVelocityController() {
        // In most cases the default destructor is fine.
        // If you want to handle cleanup, do it here.
    }

    void set_velocity(float vx, float vy, float omega)
    {
        try {
            velocityAction_.setVelocity(vx, vy, omega);
        }
        catch (ConnectionFailException &e) {
            throw std::runtime_error(std::string("Connection failed: ") + e.what());
        }
        catch (RequestTimeOutException &e) {
            throw std::runtime_error(std::string("Request timed out: ") + e.what());
        }
    }

    // Stop the robot by setting velocity to zero
    void stop()
    {
        set_velocity(0.0f, 0.0f, 0.0f);
    }

private:
    SlamwareCorePlatform sdp_;
    VelocityControlMoveAction velocityAction_;
};

// Expose via Pybind11
PYBIND11_MODULE(slamware_controller, m) {
    py::class_<SlamwareVelocityController>(m, "SlamwareVelocityController")
        .def(py::init<const std::string &>(),
             py::arg("ip_address"),
             "Create a controller and connect to the given Slamware IP.")
        .def("set_velocity",
             &SlamwareVelocityController::set_velocity,
             py::arg("vx"), py::arg("vy"), py::arg("omega"),
             "Set velocity for the robot (vx, vy, omega).")
        .def("stop",
             &SlamwareVelocityController::stop,
             "Stop the robot by setting velocity to zero.");
}
