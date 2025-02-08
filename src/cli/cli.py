# cli.py
import os
import sys
import json
import socket
import connector
import getpass
import readline

client = connector.TinyDbClient('127.0.0.1', 4083)

## System keywords.
keywords = [
    'SELECT', 'UPDATE', 'DELETE', 'INSERT', 'DROP', 'CREATE', 'ALTER', 'DESC', 'DESCRIBE', 'SHOW', 'SET', ## operation.
    'TABLE', 'FROM', 'WHERE',  ## clause
    'AND', 'OR' ## logic
    'MAX', 'MIN', 'SUM', 'COUNT', 'AVG' ## aggregate functions
]

## Load keywords.
def completer(text, state):
    options = [i for i in keywords if i.startswith(text) or i.startswith(text.upper())]
    try:
        return options[state]
    except:
        pass

readline.set_completer(completer)
readline.parse_and_bind('tab: complete')
readline.parse_and_bind('Control-v: paste')

def clearCmd(cmd: str):
    return cmd.strip(';').strip()

## Hanle sql.
def handleSql(cmd: str):
    if not cmd.endswith(';'):
        cmd +=';'
    return cmd

## Execute exit.
def exit():
    client.close()
    print('\nBye...\n')
    sys.exit(0)

## Execute clear.
def clear():
    os.system("clear")

## Execute sql statement.
def tinydb(cmd):
    sql = handleSql(cmd)
    ret = client.execute(sql)    
    print(ret)

## Read command.
def readCmd():
    try:
        return input('tinydb > ')
    except KeyboardInterrupt:
        exit()

## Source sql file.
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

## Output result to file.
def output(cmd: str):
    list = cmd.split(">>")
    if (len(list) != 2):
        print("Error input for >>")
        return
    sql = handleSql(list[0].strip())
    filePath = list[1].rstrip(';').strip()
    ret = client.directExecute(sql)
    with open(filePath, 'w', encoding='utf-8') as file:
        file.write(ret)
    print(f"Result write into {filePath} successfully.")


def handle(cmd: str):
    cmd = clearCmd(cmd)
    list = cmd.split("|")
    if (len(list) != 2):
        print("Error input for |")
        return
    sql = handleSql(list[0].strip())
    hanler = list[1].strip().upper()
    ret = client.execute(sql)
    match hanler:
        case 'JQ':
            handleJsonpp(ret)
        case 'JSON_PP':
            handleJsonpp(ret)
        case _:
            print(f"Not support handler:{hanler}")
    

## JSON_PP
def handleJsonpp(raw: dict):
    jsonpp = json.dumps(
        raw, sort_keys=False, ensure_ascii=False, 
        indent=4, separators=(',', ':')
    )
    print(jsonpp)


## Execute command.
def exec_cmd(cmd):
    cmd = cmd.strip()
    if cmd.upper().startswith("SOURCE "):
        source(cmd.strip("SOURCE ").strip("source").strip())
    elif ">>" in cmd:
        output(cmd)
    elif '|' in cmd:
        handle(cmd)   
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

## Fetch Tables.
def fetchTables():
    ret = client.execute("show tables;")
    assert ret["success"] == True
    for item in ret["data"]:
        keywords.append(item["table_name"])


## Main.
if __name__ == "__main__":
    try:
        if login():
            fetchTables()
            while True:
                cmd = readCmd()
                exec_cmd(cmd)
    except KeyboardInterrupt:
        exit()
    except socket.timeout:
        print("timout.")
        exit()
    except Exception as e:
        print(f"Error:{e}")
        exit()
