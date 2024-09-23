#connector.py

import io
import socket
import json

class TinyDbClient:
    def __init__(self, ip, port):
        # create a socket object.
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect((ip, port))

    def execute(self, sql) -> dict:
        try:
            self.client.send(sql.encode("utf-8")[:65535])
            writer = io.StringIO()
            while True:
                response = self.client.recv(65535)
                response = response.decode("utf-8").rstrip("\x00").lstrip("\x00").strip()
                if response.upper() == "OVER":
                    break
                writer.write(response)
            ret = writer.getvalue()
            writer.close()
            return json.loads(ret)
               
        except Exception as e:
            print(f"Error: {e}")

        return {}

    def close(self):
        self.client.close()
