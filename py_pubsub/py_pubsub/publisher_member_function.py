#!/usr/bin/env python3
from sympy import Min, arg
import rclpy
from rclpy.node import Node
import time


from std_msgs.msg import String 

class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher = self.create_publisher(String, 'topic', 10)
        self.i = 0
        self.rate = self.create_rate(1)
        
    def sleep_func(self):
        time.sleep(1.5)
    
    def publish1(self):
        msg = String()
        msg.data = "Hello World: %d" % self.i
        self.publisher.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1
    
def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = MinimalPublisher()
    while 1:
        minimal_publisher.publish1()
        minimal_publisher.sleep_func()
    rclpy.shutdown()
    
if __name__=='__main__':
    main()
        