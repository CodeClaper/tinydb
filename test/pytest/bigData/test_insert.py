from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all
import random
import uuid

client = TinyDbClient("127.0.0.1", 4083)    
client.login("root", "Zc120130211")

# mock table
def test_mock_table():
    sql = "create table Student(id varchar(48), name varchar(48), age int, primary key(id));"
    ret = client.execute(sql)
    assert ret["success"] == True

## test insert 1000 students
def test_1000_student_insert():
    names = ["zhangsan", "lisi", "Sun", "July", "Kaili", "James", "Max"]
    for i in range(1, 1000):
        sql = f"insert into Student values ('{uuid.uuid4()}', '{names[i % 7]}', { random.randint(6, 15) });"
        ret = client.execute(sql)
        assert ret["success"] == True

# drop mock table
def test_drop_mock_table():
    sql = "drop table Student;"
    ret = client.execute(sql)
    assert ret["success"] == True
