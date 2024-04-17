# create_test.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all

client = TinyDbClient("127.0.0.1", 4083)    

## test create table
def test_create_table():
    ret = client.execute("create table A(id varchar(32), name varchar(16), age int, class int, sex char,  score float, phone varchar(11), address varchar(48), primary key(id))")
    assert ret["success"] == True

## test create already exist table.
def test_create_already_exist_table():
    ret = client.execute("create table A (id varchar(32), name varchar(16), age int, address varchar(48), primary key(id))")
    assert ret["success"] == False

## test create already exist table.
def test_create_table_lack_primary_key():
    ret = client.execute("create table A (id varchar(32), name varchar(16), age int, address varchar(48);")
    assert ret["success"] == False

## test create already exist table.
def test_create_table_unknown_data_type():
    ret = client.execute("create table A (id varchar(32), name varchar(16), age int, address text, primary key(id);")
    assert ret["success"] == False

## test create test without user-level primary key
def test_create_table_without_priamry_key():
    sql = "CREATE TABLE Pointer(x int, y int);\n" \
          "CREATE TABLE Circle(r float, p Pointer);\n"
    ret = client.execute(sql)
    assert_all(ret)

## test drop table
def test_drop_table():
    sql = "DROP TABLE A;\n"\
          "DROP TABLE Circle;\n" \
          "DROP TABLE Pointer;\n"
    ret = client.execute(sql)
    assert_all(ret)
