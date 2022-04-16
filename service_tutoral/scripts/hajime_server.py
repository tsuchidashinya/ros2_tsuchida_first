from new_message.srv import Ningen

import rclpy
from rclpy.node import Node 

class MinimalService(Node):
    def __init__(self):
        super().__init__("minimal_service")
        self.srv = self.create_service(Ningen, 'tsuchida_service', self.service_callback)
    
    def service_callback(self, request, response):
        # respo = Ningen()
        # respo.Response.answer
        # respo.Request.a
        response.answer = str(request.a * request.b)
        return response 
def main(args=None):
    rclpy.init(args=args)
    minimal_service = MinimalService()
    rclpy.spin(minimal_service)
    rclpy.shutdown()

if __name__=='__main__':
    main()