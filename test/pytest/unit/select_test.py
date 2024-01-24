
# select_test.py

from support.tinydb_cli import TinyDbClient


client = TinyDbClient("127.0.0.1", 4083)

## test select all
def test_select_all():
    ret = client.execute("select * from S");
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select one item
def test_select_one_item():
    ret = client.execute("select id from S");
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select multiple items
def test_select_items():
    ret = client.execute("select id, name from S");
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001", "name": "zhangsan" }


## test select not exists items.
def test_select_not_exist_items():
    ret = client.execute("select none from S");
    assert ret["success"] == False

## test select simple condition.
def test_select_simple_condition():
    ret = client.execute("select id from S where id = 'S001'");
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select complex condition
def test_select_complex_condition1():
    ret = client.execute("select id from S where age = 10 and address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select complex condition
def test_select_complex_condition2():
    ret = client.execute("select id from S where age > 100 and address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == []

## test select condition field not exist.
def test_select_not_exist_condition_filed():
    ret = client.execute("select id from S where none = 10")
    assert ret["success"] == False
