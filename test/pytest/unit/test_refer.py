# select_test.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all
client = TinyDbClient("127.0.0.1", 4083)

## create mock tables;
def test_create_mock_table():
    sql = "create table Class (id string primary key, location string);\n" \
          "create table Student (id string primary key, name string, age int, birth date, class Class);\n"  
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True

## insert mock data. 
def test_insert_mock_data():
    sql = "insert into Class values('C001', 'Northwest corner ');\n" \
          "insert into Class values('C002', 'Middle');\n" \
          "insert into Class values('C003', 'South side');\n" \
          "insert into Class values('C004', 'East side');\n" \
          "insert into Student values('S001', 'kail', 10, '2014-10-03', ref(id = 'C001'));\n" \
          "insert into Student values('S002', 'sun', 11, '2013-11-20', ref(id = 'C001'));\n" \
          "insert into Student values('S003', 'ben', 12, '2012-04-23', ref(id = 'C002'));\n" \
          "insert into Student values('S004', 'david', 14, '2010-01-05', ref(id = 'C002'));\n" \
          "insert into Student values('S005', 'kunting', 9, '2015-06-23', ref(id = 'C002'));\n" \
          "insert into Student values('S006', 'bob', 9, '2015-07-07', ref(id = 'C003'));\n" \
          "insert into Student values('S007', 'july', 11, '2013-03-05', ref(id = 'C003'));\n" \
          "insert into Student values('S008', 'alice', 13, '2011-08-08', ref(id = 'C004'));\n" 
    ret = client.execute(sql)
    assert_all(ret)

## test select one subcolumn.
def test_select_subcolumn():
    ret = client.execute("select (class).id as cid from Student where id = 'S001'")
    assert ret["success"] == True
    assert ret["data"] == [{ "cid": "C001"}]

## test select subcolumn json.
def test_select_subcolumn_json():
    ret = client.execute("select class{id as cid} from Student where id = 'S001'")
    assert ret["success"] == True
    assert ret["data"] == [{ "class" : {"cid": "C001"} }]

## test select subcolumn json.
def test_select_unknown_subcolumn():
    ret = client.execute("select class{x as cid} from Student where id = 'S001'")
    assert ret["success"] == False

## test select plain column and subcolumn.
def test_select_column_subcolumn():
    ret = client.execute("select id, class{id as cid} from Student where id = 'S001'")
    assert ret["success"] == True
    assert ret["data"] == [{ "id": "S001", "class" : {"cid": "C001"} }]

## test max for subcolumn.
def test_max_subcolumn():
    ret = client.execute("select max((class).id) from Student")
    assert ret["success"] == True
    assert ret["data"] == [{ "max": "C004" }]


## test delete reference.
def test_delete_reference():
    ret = client.execute("delete from Class where id = 'C001'")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test deleted subcolumn
def test_select_deleted_subcolumn_json():
    ret = client.execute("select class from Student where id = 'S001'")
    assert ret["success"] == True
    assert ret["rows"] == 1
    assert ret["data"] == [{ "class": None }]


## test deleted subcolumn
def test_select_deleted_subcolumn_json_detail():
    ret = client.execute("select class{id, location} from Student where id = 'S001'")
    assert ret["success"] == True
    assert ret["rows"] == 1
    assert ret["data"] == [{ "class": None }]


## test deleted subcolumn
def test_select_deleted_subcolumn_item():
    ret = client.execute("select (class).id, (class).location from Student where id = 'S001'")
    assert ret["success"] == True
    assert ret["rows"] == 1
    assert ret["data"] == [{ "id": None, "location": None}]


## drop mock tables   
def test_drop_mock_tables():
    sql = "drop table Student;\n"\
          "drop table Class;"
    ret = client.execute(sql)
    assert ret[0]["success"] == True
    assert ret[1]["success"] == True

