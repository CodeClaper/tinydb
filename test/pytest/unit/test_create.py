# create_test.py
from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test create table
def test_create_table():
    ret = client.execute("create table A(id string, name string(16), age int, class int, sex char,  score float, phone string(11), address string(48), primary key(id))")
    assert ret["success"] == True

## test create already exist table.
def test_create_already_exist_table():
    ret = client.execute("create table A (id string, name string(16), age int, address string(48), primary key(id))")
    assert ret["success"] == False

## test create already exist table.
def test_create_table_lack_primary_key():
    ret = client.execute("create table A (id string, name string(16), age int, address string(48);")
    assert ret["success"] == False

## test create already exist table.
def test_create_table_unknown_data_type():
    ret = client.execute("create table A (id string, name string(16), age int, address text, primary key(id);")
    assert ret["success"] == False

## test drop table
def test_drop_table():
    ret = client.execute("drop table A;")
    assert ret["success"] == True
