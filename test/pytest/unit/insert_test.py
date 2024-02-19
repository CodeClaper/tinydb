# insert_test.py

from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test insert one.
def test_insert1():
    ret = client.execute("insert into Students values('S001', 'lili', 8, 3, 'F', '13001332823', 'beijing');")
    assert ret["success"] == True

## test insert one.
def test_insert2():
    ret = client.execute("insert into Students values('S002', 'wanglang', 10, 5, 'M', '18856239982', 'beijing');")
    assert ret["success"] == True

## test insert one.
def test_insert3():
    ret = client.execute("insert into Students values('S003', 'zhaoxia', 7, 2, 'F', '18167655223', 'shanghai');")
    assert ret["success"] == True

## test dupliacate key.
def test_duplicate_key():
    ret = client.execute("insert into Students values('S001', 'Jack', 9, 5, 'M', '17232323223', 'NewYork');")
    assert ret["success"] == False

## test insert into not exist table.
def test_no_exist_table():
    ret = client.execute("insert into NotTable values('S001', 'Jack', 9, 5, 'M', '17232323223', 'NewYork');")
    assert ret["success"] == False
