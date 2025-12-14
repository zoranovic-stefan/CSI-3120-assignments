import socket
import sys

class NetworkClient:
    def __init__(self, server_ip, server_port):
        self._server_ip = server_ip
        self._server_port = server_port
        self._socket = None
        self._connected = False
    
    def _create_socket(self):
        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            return True
        except socket.error:
            print("socket() failed")
            return False
    
    def _connect_to_server(self):
        try:
            self._socket.connect((self._server_ip, self._server_port))
            self._connected = True
            return True
        except socket.error:
            print("connect() failed")
            return False
    
    def connect(self):
        if not self._create_socket():
            sys.exit(0)
        if not self._connect_to_server():
            sys.exit(0)
    
    def send_message(self, message):
        if self._connected and self._socket:
            self._socket.send(message.encode())
    
    def close(self):
        if self._socket:
            self._socket.close()

class ClientApplication:
    def __init__(self):
        self._client = NetworkClient("127.0.0.1", 60000) 
        
    def run(self):
        self._client.connect()
        
        while True:
            text = input("Send? ")
            if text == "quit":
                break
            self._client.send_message(text)
        
        self._client.close()

if __name__ == "__main__":
    app = ClientApplication()
    app.run()