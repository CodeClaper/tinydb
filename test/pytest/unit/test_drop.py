
from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test create table
def test_create_table():
    ret = client.execute("create table A(id string primary key, name string)")
    assert ret["success"] == True

## test drop table
def test_drop_table():
    ret = client.execute("drop table A")
    assert ret["success"] == True

## test drop not exist table.
def test_drop_not_exist_table():
    ret = client.execute("drop table B")
    assert ret["success"] == False

