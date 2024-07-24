## test_bd_insert.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all
import random
import uuid

client = TinyDbClient("127.0.0.1", 4083)

## mock table
def test_mock_table():
    sql = "create table Student (id varchar(48), name varchar(48), address varchar(100), primary key(id));"
    ret = client.execute(sql)
    assert ret["success"] == True


## test insert 3000 students
def test_3000_student():
    names = ["zhangsan", "lisi", "Sun", "July", "Kaili", "James", "Max"]
    address = ["beijing", "shanghai", "nanjing", "jinan", "zhengzhou", "xian", "guangzhou", "hongkong", "shenzhen", "wuhan", "zhejiang", "chognqing", "shengdu"]
    for i in range(1, 3000):
        sql = f"insert into Student values ('{uuid.uuid4()}', '{names[i % 7]}', '{address[random.randint(0,12)]}')"
        ret = client.execute(sql)
        assert ret["success"] == True


# query after inserting.
def test_query_student():
    sql = "select * from Student;"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["rows"] == 2999
