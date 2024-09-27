# cli.py

import readline
import os
import sys
import connector
import getpass

client = connector.TinyDbClient('127.0.0.1', 4083)

def completer(text, state):
    options = ['SELECT', 'UPDATE', 'DELETE', 'INSERT', 'DROP', 'CREATE', 'TABLE', 'FROM', 'WHERE', 
               'AND', 'OR', 'ALTER', 'DESC', 'DESCRIBE']
    options = [i for i in options if i.startswith(text.upper())]

    try:
        return options[state]
    except:
        pass

readline.set_completer(completer)
readline.parse_and_bind('tab: complete')
readline.parse_and_bind('Control-v: paste')

## exec exit.
def exit():
    print('Bye...')
    sys.exit(0)

## exec clear 
def clear():
    os.system("clear")


## execute tinydb
def tinydb(cmd):
    ret = client.execute(cmd)    
    print(ret)

## read command.
def readCmd():
    try:
        return input('tinydb > ')
    except KeyboardInterrupt:
        exit()

## source file.
def source(file):
    try:
        with open(file) as file:
            for line in file:
                sql = line.strip()
                ret = client.execute(sql)
                print (ret)
                if ret["success"] == False:
                    break
    except FileNotFoundError:
        print(f"file {file} not found")
        pass
    except KeyboardInterrupt:
        exit()


## Execute command.
def exec_cmd(cmd):
    if cmd.upper().startswith("SOURCE "):
        source(cmd.strip("SOURCE ").strip("source" ).strip())
    else:
        match cmd.upper():
            case 'EXIT':
                exit()
            case 'CLEAR':
                clear()
            case 'CLS':
                clear()
            case _:
                tinydb(cmd)

def login() -> bool:
    account = input("Your account: ")
    password = getpass.getpass("Your password: ")
    return client.login(account, password)


if __name__ == "__main__":
    if login():
        while True:
            cmd = readCmd()
            exec_cmd(cmd)
