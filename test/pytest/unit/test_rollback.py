
# test_trans.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all
client1 = TinyDbClient("127.0.0.1", 4083)
client2 = TinyDbClient("127.0.0.1", 4083)


## create mock table:
def test_create_mock_table():
    sql = "create table Class (id string primary key, location string);\n" \
          "create table Student (id string primary key, name string, age int, birth date, class Class);\n"  
    ret = client1.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True


## begin transaction and insert one row data.
def test_insert_data():
    sql = "begin;\n" \
          "insert into Student values ('S001', 'zhangsan', 10, '2014-10-12', ('C001', 'mid of third'));\n"
    ret = client1.execute(sql)
    assert_all(ret)


## query first
def test_select_data1():
    sql = "select * from Student;"
    ret1 = client1.execute(sql)
    ret2 = client2.execute(sql)
    assert ret1["success"] == True and ret1["rows"] == 1
    assert ret2["success"] == True and ret2["rows"] == 0


## rollback
def test_rollback():
    sql = "rollback"
    ret = client1.execute(sql)
    assert ret["success"] == True 


## query first
def test_select_data2():
    sql = "select * from Student;"
    ret1 = client1.execute(sql)
    ret2 = client2.execute(sql)
    assert ret1["success"] == True and ret1["rows"] == 0
    assert ret2["success"] == True and ret2["rows"] == 0

## test drop table
def test_drop_mock_tables():
    sql = "drop table Student;\n"\
          "drop table Class;"
    ret = client1.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True

