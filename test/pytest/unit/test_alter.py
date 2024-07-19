# test_alter.py
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all

client = TinyDbClient("127.0.0.1", 4083)    

## mock tables.
def test_create_mock_table():
    sql = "create table Student (id varchar(32) primary key, name varchar(32), age int);"
    ret = client.execute(sql)
    assert ret["success"] == True

##  mock some data.
def test_mock_table_data():
    sql = "insert into Student values ('S0001', 'zhangchuran', 10);\n" \
          "insert into Student values ('S0002', 'chengzhen', 11);\n" \
          "insert into Student values ('S0003', 'dongxiaojun', 8);\n" 
    ret = client.execute(sql)
    assert_all(ret)

## test_alter_add_column
def test_add_column():
    sql = "alter table Student add column sex char default 'M' comment 'M if man and W if women' before age;"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["message"] == "Add column 'sex' for table 'Student' successfully."

## test desc table aftert add column
def test_desc_table_after_add_column():
    sql = "desc Student"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["data"][2] == { "field": "sex", "key": None, "type": "char", "length": 1, "array": False, "default": "M", "comment": "M if man and W if women" }

## select data alter add column
def test_query_data_after_add_column():
    sql = "select * from Student where id = 'S0001';"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["data"][0] ==  {'age': 10, 'id': 'S0001', 'name': 'zhangchuran', 'sex': 'M'}

## test_alter_add_column
def test_add_column2():
    sql = "alter table Student add column address varchar(64) comment 'Your home address';"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["message"] == "Add column 'address' for table 'Student' successfully."

## select data alter add column
def test_query_data_after_add_column2():
    sql = "select * from Student where id = 'S0001';"
    ret = client.execute(sql)
    assert ret["success"] == True
    assert ret["data"][0] ==  {'age': 10, 'id': 'S0001', 'name': 'zhangchuran', 'sex': 'M', 'address': None}

## test add column that already exists.
def test_add_column_ready_exist():
    sql = "alter table Student add column name varchar(32) not null;"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Table 'Student' already exists column 'name'."

## test add column with postion that its column not exists.
def test_add_column_not_exist_postion():
    sql = "alter table Student add column phone varchar(13) comment 'your phone number or your parent`s.' after parentName;"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Unknown column 'parentName' in table 'Student'."

## test add primary-key column 
def test_add_primary_key_column():
    sql = "alter table Student add column idCard varchar(48) primary key;"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Not support add primary-key column through alter table."

## drop mock table
def test_drop_mock_table():
    sql = "drop table Student"
    ret = client.execute(sql)
    assert ret["success"] == True


