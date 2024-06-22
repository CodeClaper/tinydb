from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

## test create table
def test_create_table():
    ret = client.execute("create table A(id varchar(8), name varchar(16), age int, class int, sex char,  score float, phone varchar(11), address varchar(48), primary key(id))")
    assert ret["success"] == True

## test overflow varchar.
def test_overflow_varchar():
    sql = "INSERT INTO A values('S00000000001', 'jack', 10, 2, 'M', 3.23, '130012323482333', 'beijing');"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Exceed the limit of data length: 12 > 8, for column 'id'. "

## test overflow varchar.
def test_overflow_varchar2():
    sql = "INSERT INTO A values('S001', 'jack', 10, 2, 'M', 3.23, '130012323482333', 'beijing');"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Exceed the limit of data length: 15 > 11, for column 'phone'. "

## test overflow char.
def test_overflow_char():
    sql = "INSERT INTO A values('S001', 'jack', 10, 2, 'MAN', 3.23, '13001542702', 'beijing');"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Try to convert value 'MAN' to char value type fail."


## test overflow char.
def test_overflow_int():
    sql = "INSERT INTO A values('S001', 'jack', 1314232272847489294756329290476549394673, 2, 'M', 3.23, '13001542702', 'beijing');"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "'1314232272847489294756329290476549394673' is overflow."


## test overflow char.
def test_invalid_number():
    sql = "INSERT INTO A values('S001', 'jack', 1223232323erwswq, 2, 'M', 3.23, '13001542702', 'beijing');"
    ret = client.execute(sql)
    assert ret["success"] == False
    assert ret["message"] == "Sql syntax error near [erwswq]."

## test for drop table.
def test_drop_table():
    sql = "DROP TABLE A;"
    ret = client.execute(sql)
    assert ret["success"] == True

