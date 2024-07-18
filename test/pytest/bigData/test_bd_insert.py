## test_bd_insert.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all
import random
import uuid

client = TinyDbClient("127.0.0.1", 4083)    

# mock table
def test_mock_table():
    sql = "create table Student(id varchar(48), name varchar(48), age int, primary key(id));"
    ret = client.execute(sql)
    assert ret["success"] == True

## test insert 1000 students
def test_1000_student_insert():
    names = ["zhangsan", "lisi", "Sun", "July", "Kaili", "James", "Max"]
    for i in range(1, 1000):
        sql = f"insert into Student values ('{uuid.uuid4()}', '{names[i % 7]}', { random.randint(6, 15) })"
        ret = client.execute(sql)
        assert ret["success"] == True


## test add new column
def test_add_new_column():
    sql = "alter table Student add column sex char default 'M' comment 'M if man Woman if W' before age;"
    ret = client.execute(sql)
    assert ret["success"] == True


## desc table
def test_desc_tables():
    sql = "desc Student;"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["data"][2] == { "field": "sex", "key": None, "type": "char", "length": 1, "array": False, "default": "M", "comment": "M if man Woman if W" }

# drop mock table
#def test_drop_mock_table():
#    sql = "drop table Student"
#    ret = client.execute(sql)
#    assert ret["success"] == True
