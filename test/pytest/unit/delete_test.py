## delete_test.py

from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## Firstly create table.
def create_table():
    sql = "create table t_delete_test(id string, name string, score float, primary key (id));"
    ret = client.execute(sql)
    assert ret["success"] == True

## insert some data
def batch_inset_test():
    sql = "insert into t_delete_test('S001', 'BOBN', 98.3);" \
          "insert into t_delete_test('S002', 'JKD', 99.2);" \
          "insert into t_delete_test('S003', 'MOOR', 87.2);" \
          "insert into t_delete_test('S004', 'LOU', 86.2);" \
          "insert into t_delete_test('S005', 'LISA', 33.2);" 
    ret = client.execute(sql)
    assert ret["success"] == True

## test delete with condition.
def delete_with_condition():
    sql = "delete from t_delete_test where name = 'BOBN';"\
          "select * from t_delete_test;"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[0]["rows"] == 1
    assert ret[1]["success"] == True
    assert ret[1]["rows"] == 4

## test delete with condition.
def delete_with_fake_condition():
    sql = "delete from t_delete_test where name = 'BOB';"\
          "select * from t_delete_test;"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[0]["rows"] == 0
    assert ret[1]["success"] == True
    assert ret[1]["rows"] == 4

## test delete with condition.
def delete_without_condition():
    sql = "delete from t_delete_test;"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[0]["rows"] == 4

## Finally drop table.
def drop_table():
    sql = "drop table t_delete_test"
    ret = client.execute(sql)
    assert ret["success"] == True
