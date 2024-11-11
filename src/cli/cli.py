# cli.py

import readline
import os
import sys
import connector
import getpass

client = connector.TinyDbClient('127.0.0.1', 4083)
keywords = ['SELECT', 'UPDATE', 'DELETE', 'INSERT', 'DROP', 'CREATE', 'TABLE', 'FROM', 'WHERE', 
           'AND', 'OR', 'ALTER', 'DESC', 'DESCRIBE']

def completer(text, state):
    options = [i for i in keywords if i.startswith(text) or i.startswith(text.upper())]
    try:
        return options[state]
    except:
        pass

readline.set_completer(completer)
readline.parse_and_bind('tab: complete')
readline.parse_and_bind('Control-v: paste')

def generateSql(cmd: str):
    if not cmd.endswith(';'):
        cmd +=';'
    return cmd

## exec exit.
def exit():
    print('\nBye...\n')
    sys.exit(0)

## exec clear 
def clear():
    os.system("clear")


## execute tinydb
def tinydb(cmd):
    sql = generateSql(cmd)
    ret = client.execute(sql)    
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

def output(cmd: str):
    list = cmd.split(">>")
    if (len(list) != 2):
        print("Error input for >>")
        return
    sql = generateSql(list[0].strip())
    filePath = list[1].rstrip(';').strip()
    ret = client.directExecute(sql)
    with open(filePath, 'w', encoding='utf-8') as file:
        file.write(ret)
    print(f"Result write into {filePath} successfully.")


## Execute command.
def exec_cmd(cmd):
    if cmd.upper().startswith("SOURCE "):
        source(cmd.strip("SOURCE ").strip("source" ).strip())
    elif ">>" in cmd:
        output(cmd)
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

## Login 
def login() -> bool:
    account = input("Your account: ")
    password = getpass.getpass("Your password: ")
    clear()
    return client.login(account, password)

def fetchTables():
    ret = client.execute("show tables;")
    assert ret["success"] == True
    for item in ret["data"]:
        keywords.append(item["table_name"])


if __name__ == "__main__":
    try:
        if login():
            fetchTables()
            while True:
                cmd = readCmd()
                exec_cmd(cmd)
    except KeyboardInterrupt:
        exit()
