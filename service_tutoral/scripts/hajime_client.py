import sys 
from new_message.srv import Ningen
import rclpy
from rclpy.node import Node

class MinimalClient(Node):
    def __init__(self):
        super().__init__("minimal_client")
        self.client1 = self.create_client(Ningen, 'tsuchida_service')
        while not self.client1.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = Ningen.Request()
    
    def send_request(self):
        self.req.a = int(sys.argv[1])
        self.req.b = int(sys.argv[2])
        self.future = self.client1.call_async(self.req)
    
def main(args=None):
    rclpy.init(args=args)
    minimal_client = MinimalClient()
    minimal_client.send_request()
    print("f1")
    while rclpy.ok():
        print("f2")
        rclpy.spin_once(minimal_client)
        print("f3")
        if minimal_client.future.done():
            try:
                response = minimal_client.future.result()
            except Exception as e:
                minimal_client.get_logger().info('Service call failed %r' % (e, ))
            else:
                minimal_client.get_logger().info(
                    'Result of servoce: for %d + %d = %s' %
                    (minimal_client.req.a, minimal_client.req.b, response.answer))
                break
    minimal_client.destroy_node()
    rclpy.shutdown()

if __name__=='__main__':
    main()
            