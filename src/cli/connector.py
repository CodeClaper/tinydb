#connector.py

import io
import socket
import json

class TinyDbClient:
    def __init__(self, ip, port):
        # create a socket object.
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect((ip, port))

    def login(self, account, password) -> bool:
        self.client.send(f"{account}/{password}".encode("utf-8"))
        resp_bytes = self.client.recv(65535)
        response = resp_bytes.decode("utf-8").rstrip("\x00")
        print(response)
        return response != 'No access.'

    def show_bytes(self, byte_data):
        hex_values = ' '.join(hex(b)[2:].zfill(2) for b in byte_data)
        print(hex_values)

    def show_bytes2(self, string_data):
        hex_values = ' '.join(hex(ord(c))[2:].zfill(2) for c in string_data)
        print(hex_values)

    def execute(self, sql) -> dict:
        try:
            self.client.send(sql.encode("utf-8")[:65535])
            writer = io.StringIO()
            while True:
                resp_bytes = self.client.recv(65535)
                response = resp_bytes.decode("utf-8").strip("\x00")
                if response.upper() == "OVER":
                    break
                writer.write(response)
            ret = writer.getvalue()
            writer.close()
            return json.loads(ret)
               
        except ConnectionError:
            exit(1)
        except Exception as e:
            print(f"Error: {e}")

        return {}

    def close(self):
        self.client.close()
