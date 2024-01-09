
import pytest
from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test drop table
@pytest.mark.run(order = 1000)
def test_drop_table():
    ret = client.execute("drop table S")
    assert ret["success"] == True

## test drop not exist table.
@pytest.mark.run(order = 1001)
def test_drop_not_exist_table():
    ret = client.execute("drop table none")
    assert ret["success"] == False

