#tinydb_cli.py

import io
import socket

class TinyDbClient:
    
    def __init__(self, ip, port):
        # create a socket object.
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect((ip, port))

    def execute(self, sql) -> str:
        try:
            self.client.send(sql.encode("utf-8")[:1024])
            writer = io.StringIO()
            while True:
                response = self.client.recv(1024)
                response = response.decode("utf-8").rstrip("\x00")
                if response.upper() == "OVER":
                    break
                writer.write(response)
            return writer.getvalue()
               
        except Exception as e:
            print(f"Error: {e}")

        return ""

    def close(self):
        self.client.close()
