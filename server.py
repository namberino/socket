import socket

IP = "127.0.0.1"
PORT = 5500

username = ""
password = ""

def start_server():
    global username
    global password

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((IP, PORT))
    server_socket.listen(1)
    
    print(f"Server listening on port {PORT}...")

    conn, addr = server_socket.accept()
    print(f"Connection from {addr}")

    print("\nReceiving username and password...")

    while True:
        name = conn.recv(1024).decode('utf-8')
        pwd = conn.recv(1024).decode('utf-8')

        if name == "nam" and pwd == "1234":
            data = "Confirmed\0"
            username = name
            password = pwd
            conn.send(data.encode())
        else:
            data = "Failed\0"
            conn.send(data.encode())

            name = ""
            pwd = ""

        if username and password:
            print("Confirmed username and password\n")
            print("**********************************")
            print("*   Login Successful. Welcome!   *")
            print("**********************************")
            
            break
        else:
            print("Invalid username and password\n")

    conn.close()



start_server()
