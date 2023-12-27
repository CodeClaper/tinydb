import socket
import readline

server_ip   = "127.0.0.1"
server_port =  4083

def start_up():
    
    # create a socket object.
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    client.connect((server_ip, server_port))

    try:
        while True:
            msg = input("tinydb > ")
            if msg.upper() == "EXIT":
                print("Goodbye.")
                break
            client.send(msg.encode("utf-8")[:1024])
            db_recv(client)
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.close()

def db_recv(client):
    while True:
        response = client.recv(1024)
        response = response.decode("utf-8").rstrip("\x00")
        if response.upper() == "OVER":
            break;
        print(response, end="")

readline.parse_and_bind('tab: complete')
start_up()
    
