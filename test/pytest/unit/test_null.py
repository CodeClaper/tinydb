# insert_test.py

from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all

client = TinyDbClient("127.0.0.1", 4083)    

## create table
def test_create_tables():
    sql = "create table Demo(id varchar(32) primary key, name varchar(48) not null, age int, phone varchar(13), idCard varchar(20) not null);\n"\
          "create table Array(id varchar(32) primary key, name varchar(48) not null, array int[]);\n"
    ret = client.execute(sql)
    assert_all(ret)

## insert allow null data
def test_insert_allow_null_data():
    sql = "insert into Demo values('S001', 'shangsan', 10, null, '37023237472877674672');"
    ret = client.execute(sql)
    assert ret['success'] == True

## test query null value
def test_select_null_value():
    sql = "select * from Demo;"
    ret = client.execute(sql)
    assert ret['success'] == True
    assert ret["data"] == [{ "id": "S001", "name": "shangsan", "age": 10, "phone": None, "idCard": "37023237472877674672"}]

## insert allow null data
def test_insert_not_allow_null_data():
    sql = "insert into Demo values('S002', 'daly', 10, null, null);"
    ret = client.execute(sql)
    assert ret['success'] == False
    assert ret['message'] == "Column 'idCard' can`t be null."

## insert allow null data
def test_insert_null_primary_key():
    sql = "insert into Demo values(null, 'Jim', 10, '1300223232', '370083342324672');"
    ret = client.execute(sql)
    assert ret['success'] == False
    assert ret['message'] == "Column 'id' can`t be null."

## insert allow null data
def test_insert_null_array():
    sql = "insert into Array values('001', 'kil', null);"
    ret = client.execute(sql)
    assert ret['success'] == True

## test query null value
def test_select_null_array_value():
    sql = "select * from Array;"
    ret = client.execute(sql)
    assert ret['success'] == True
    assert ret["data"] == [{ "id": "001", "name": "kil", "array": None }]


## drop table
def test_drop_table():
    sql = "drop table Demo;\n"\
          "drop table Array;\n"
    ret = client.execute(sql)
    assert_all(ret)


