import slamware_controller
import time
controller = slamware_controller.SlamwareVelocityController("192.168.11.1")
controller.set_velocity(0.01, 0, 0.0)
time.sleep(1)
controller.stop()


