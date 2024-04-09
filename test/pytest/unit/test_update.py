## update_test.py
from support.tinydb_cli import TinyDbClient
client = TinyDbClient("127.0.0.1", 4083)

## create mock table;
def test_create_mock_table():
    sql = "create table A (id string, name string, primary key(id));\n" \
          "create table B (id string, a A, primary key(id));"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True

## insert mock data
def test_insert_mock_data():
    sql = "insert into A values ('1', 'A01');\n" \
          "insert into A values ('2', 'A02');\n" \
          "insert into A values ('3', 'A03');\n"\
          "insert into A values ('4', 'A03');\n"\
          "insert into B values ('1', ref(id = '1')); \n"\
          "insert into B values ('2', ref(id = '2')); \n"\
          "insert into B values ('3', ref(id = '3')); \n"\
          "insert into B values ('3', ref(id = '4')); \n"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True
    assert ret[2]["success"] == True
    assert ret[3]["success"] == True
    assert ret[4]["success"] == True
    assert ret[5]["success"] == True
    assert ret[6]["success"] == True

## delete mock table;
def test_delete_mock_table():
    sql = "drop table B;\n" \
          "drop table A;"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True
