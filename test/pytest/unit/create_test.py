# create_test.py

from pytest.tinydb_cli import TinyDbClient

## test create table
def test_create_table():
    client = TinyDbClient("127.0.0.1", 4083)    
    client.execute("Create table Student (id strig, name string(16), age int, address string(48), primary key(id))")

