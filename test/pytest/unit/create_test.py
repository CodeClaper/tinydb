# create_test.py

from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test create table
def test_create_table():
    ret = client.execute("create table S (id string, name string(16), age int, address string(48), primary key(id))")
    assert ret["success"] == True

## test create already exist table.
def test_create_already_exist_table():
    ret = client.execute("create table S (id string, name string(16), age int, address string(48), primary key(id))")
    assert ret["success"] == False

