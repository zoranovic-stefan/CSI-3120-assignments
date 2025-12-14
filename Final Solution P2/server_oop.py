import socket
import sys

class NetworkServer:
    def __init__(self, listen_port, buffer_size=1024):
        self._listen_port = listen_port
        self._buffer_size = buffer_size
        self._listen_socket = None
        self._client_socket = None
    
    def _create_socket(self):
        try:
            self._listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            return True
        except socket.error:
            print("socket() failed")
            return False
    
    def _bind_socket(self):
        try:
            self._listen_socket.bind(('', self._listen_port))
            return True
        except socket.error:
            print("bind() failed")
            return False
    
    def _start_listening(self):
        try:
            self._listen_socket.listen(5)
            return True
        except socket.error:
            print("listen() failed")
            return False
    
    def initialize(self):
        if not self._create_socket():
            sys.exit(0)
        if not self._bind_socket():
            sys.exit(0)
        if not self._start_listening():
            sys.exit(0)
    
    def accept_client(self):
        self._client_socket, addr = self._listen_socket.accept()
    
    def receive_message(self):
        if self._client_socket:
            data = self._client_socket.recv(self._buffer_size)
            return data.decode().strip()
        return None
    
    def close(self):
        if self._client_socket:
            self._client_socket.close()
        if self._listen_socket:
            self._listen_socket.close()

class ServerApplication:
    def __init__(self):
        self._server = NetworkServer(60000)
    
    def run(self):
        self._server.initialize()
        self._server.accept_client()
        
        while True:
            message = self._server.receive_message()
            if message:
                print(f"Received: {message}")
                if message == "shutdown":
                    break
        
        self._server.close()

if __name__ == "__main__":
    app = ServerApplication()
    app.run()