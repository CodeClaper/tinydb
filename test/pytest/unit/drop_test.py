
from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test drop table
def test_drop_table():
    ret = client.execute("drop table Students")
    assert ret["success"] == True

## test drop not exist table.
def test_drop_not_exist_table():
    ret = client.execute("drop table Notable")
    assert ret["success"] == False

