# insert_test.py

from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test insert one.
def test_insert_one():
    ret = client.execute("insert into S values('S001', 'lili', 18, 'beijing');")
    assert ret["success"] == True
    ret = client.execute("insert into S values('S002', 'zhanglan', 24, 'shanghai');")
    assert ret["success"] == True

## test dupliacate key.
def test_duplicate_key():
    ret = client.execute("insert into S values('S001', 'zhangsan', 10, 'beijing');")
    assert ret["success"] == False

## test insert into not exist table.
def test_no_exist_table():
    ret = client.execute("insert into none_table values('S001', 'zhangsan', 10, 'beijing');")
    assert ret["success"] == False
