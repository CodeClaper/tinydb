## test_insert_with_select.py
from support.tinydb_cli import TinyDbClient
import threading
import random
import uuid
import time

threads = []
share_resource = {}

client1 = TinyDbClient("127.0.0.1", 4083)    
client1.login("root", "Zc120130211")

client2 = TinyDbClient("127.0.0.1", 4083)    
client2.login("root", "Zc120130211")

# thread to insert.
def thread_insert():
    try:
        names = ["zhangsan", "lisi", "Sun", "July", "Kaili", "James", "Max"]
        for i in range(1, 20000):
            sql = f"insert into Student values ('{i}', '{names[i % 7]}', { random.randint(6, 15) });"
            ret = client1.execute(sql)
            assert ret["success"] == True
    except Exception as e:
        share_resource["insert_exception"] = e

# thread to select
def thread_select():
    try:
        for _ in range(1, 60):
            sql = "select count(1) from Student;"
            ret = client2.execute(sql)
            assert ret["success"] == True
            count = ret["data"][0]["count"]
            assert (count >= 0 and count <= 20000)
            time.sleep(0.5)
    except Exception as e:
        share_resource["select_exception"] = e


threads.append(threading.Thread(target=thread_insert))
threads.append(threading.Thread(target=thread_select))


# mock table
def test_mock_table():
    sql = "create table Student(id varchar(48), name varchar(48), age int, primary key(id));"
    ret = client1.execute(sql)
    assert ret["success"] == True

# test insert with select.
def test_insert_with_select():
    for t in threads:
        t.start()
    for t in threads:
        t.join()

    if 'select_exception' in share_resource:
        raise share_resource['select_exception']
    if 'insert_exception' in share_resource:
        raise share_resource['insert_exception']

# drop mock table
def test_drop_mock_table():
    sql = "drop table Student;"
    ret = client1.execute(sql)
    assert ret["success"] == True
    client1.close()
    client2.close()


