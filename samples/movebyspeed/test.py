import slamware_controller
import time
controller = slamware_controller.SlamwareVelocityController("192.168.11.1")
controller.set_velocity(-0.5, 0, -2.0)
time.sleep(1)
controller.stop()


