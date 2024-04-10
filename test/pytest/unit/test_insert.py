# insert_test.py

from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all

client = TinyDbClient("127.0.0.1", 4083)    

# create table
def test_create_table():
    ret = client.execute("create table Student(id string primary key, name string, age int, grade int, sex char, birth date, phone string, address string, createdTime timestamp);")
    assert ret["success"] == True

## test insert one.
def test_insert1():
    sql = "insert into Student values('S001', 'lili', 8, 3, 'F', '2010-11-12', '13001332823', 'beijing', '2024-04-01 15:54:00');\n" \
          "insert into Student values('S002', 'wanglang', 10, 5, 'M', '2013-03-05', '18856239982', 'beijing', '2024-03-20 16:08:30');\n"
    ret = client.execute(sql)
    assert_all(ret)

## test dupliacate key.
def test_duplicate_key():
    ret = client.execute("insert into Student values('S001', 'Jack', 9, 5, 'M', '2009-10-12', '17232323223', 'NewYork', '2023-12-12 09:30:21');")
    assert ret["success"] == False

## test lack column.
def test_lack_column():
    ret = client.execute("insert into Student values('S001', 9, 5, 'M', '17232323223', 'NewYork', '2023-08-09 10:20:00');")
    assert ret["success"] == False
    assert ret["message"] == "Column count doesn`t match value count: 9 != 7."

## test date data type
def test_date_data_type():
    ret = client.execute("insert into Student values('S001', 'Jerry', 9, 5, 'M', '2009/03/05', '17232323223', 'NewYork', '2023-08-09 10:20:00');")
    assert ret["success"] == False
    assert ret["message"] == "Try to convert value '2009/03/05' to date value fail."

## test date data type
def test_timestamp_data_type():
    ret = client.execute("insert into Student values('S001', 'Jerry', 9, 5, 'M', '2009-03-05', '17232323223', 'NewYork', '2023-08-09T10:20:00');")
    assert ret["success"] == False
    assert ret["message"] == "Try to convert value '2023-08-09T10:20:00' to timestamp value fail."

## test char data type
def test_char_data_type():
    ret = client.execute("insert into Student values('S001', 'Jerry',  9, 5, 'MALE', '2009-03-05', '17232323223', 'NewYork', '2023-08-09T10:20:00');")
    assert ret["success"] == False
    assert ret["message"] == "Try to convert value 'MALE' to char value type fail."

## test char data type
def test_string_data_type():
    ret = client.execute("insert into Student values('S001', 'Jerry', 9, 5, 'M', '2009-03-05', 17232323223, 'NewYork', '2023-08-09T10:20:00');")
    assert ret["success"] == False

## test insert into not exist table.
def test_no_exist_table():
    ret = client.execute("insert into X values('S001', 'lili', 8, 3, 'F', '2010-11-12', '13001332823', 'beijing', '2024-04-01 15:54:00');")
    assert ret["success"] == False

## drop table
def test_drop_table():
    ret = client.execute("drop table Student")
    assert ret["success"] == True

