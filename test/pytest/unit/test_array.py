# test_array.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all

client = TinyDbClient("127.0.0.1", 4083)    

## create mock table
def test_create_mock_tables():
    sql = "create table Pointer(x float, y float);\n"\
          "create table Square(p Pointer[]);\n"\
          "create table Scheduler(id int primary key, trigger string, timers timestamp[]);"
    ret = client.execute(sql)
    assert_all(ret)

## insert array data
def test_insert_array_data():
    sql = "insert into Square values([(20, 30), (30, 30), (20, 40), (30, 40)]);\n"\
          "insert into Square values([(40, 40), (50, 40), (50, 40), (50, 50)]);"
    ret = client.execute(sql)
    assert_all(ret)

def test_select_array_data():
    sql = "select * from Square;"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["rows"] == 2
    assert ret["data"][0] == {
        "p": [
            { "x": 20, "y": 30 },
            { "x": 30, "y": 30 },
            { "x": 20, "y": 40 },
            { "x": 30, "y": 40 }
        ]
    }

## test insert right type data
def test_insert_right_type_data():
    sql = "insert into Scheduler values(1, 'check code test.', ['2024-04-24 10:00:00', '2024-04-24 16:00:00']);\n"\
          "insert into Scheduler values(2, 'push code.', ['2024-04-24 17:30:00']);\n"\
          "insert into Scheduler values(3, 'clock in.', ['2024-04-24 08:00:00', '2024-04-24 17:30:00']);\n"
    ret = client.execute(sql)
    assert_all(ret)

## test insert wrong type data
def test_insert_wrong_type_data():
    sql = "insert into Scheduler values(1, 'check code test.', ['2024-04-24', '2024-04-24 16:00:00']);\n"
    ret = client.execute(sql)
    assert ret["success"] == False

## test drop tables
def test_drop_mock_tables():
    sql = "drop table Square;\n"\
          "drop table Pointer;\n" \
          "drop table Scheduler;\n" 
    ret = client.execute(sql)
    assert_all(ret)
