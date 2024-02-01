
# select_test.py

from support.tinydb_cli import TinyDbClient


client = TinyDbClient("127.0.0.1", 4083)

## test select all
def test_select_all():
    ret = client.execute("select * from S");
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select one item
def test_select_one_item():
    ret = client.execute("select id from S");
    assert ret["success"] == True
    assert ret["data"] == [{ "id": "S001" }, {"id": "S002"}]

## test select multiple items
def test_select_items():
    ret = client.execute("select id, name from S");
    assert ret["success"] == True
    assert ret["data"] == [{ "id": "S001", "name": "lili" }, { "id": "S002", "name": "zhanglan" }]


## test select not exists items.
def test_select_not_exist_items():
    ret = client.execute("select none from S");
    assert ret["success"] == False

## test select condition field not exist.
def test_select_not_exist_condition_filed():
    ret = client.execute("select id from S where none = 10")
    assert ret["success"] == False

## test select simple condition.
def test_select_simple_condition():
    ret = client.execute("select id from S where id = 'S001'");
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select complex condition
def test_select_complex_condition1():
    ret = client.execute("select id from S where age = 18 and address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select complex condition
def test_select_complex_condition2():
    ret = client.execute("select id from S where age > 100 and address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == []

## test select complex condition
def test_select_complex_condition3():
    ret = client.execute("select id from S where age < 20 and age > 10 or address = 'shanghai'")
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select complex condition
def test_select_complex_condition4():
    ret = client.execute("select id from S where (age < 20 and age > 10 or address = 'beijing')")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select like predicate.
def test_select_like_predicate1():
    ret = client.execute("select id from S where address like 'bei%'")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select like predicate.
def test_select_like_predicate2():
    ret = client.execute("select id from S where address like '%hai'")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select like predicate.
def test_select_like_predicate3():
    ret = client.execute("select id from S where address like '%ng%'")
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select like predicate.
def test_select_like_predicate4():
    ret = client.execute("select id from S where address like 'shanghai'")
    assert ret["success"] == True
    assert ret["rows"] == 1


## test select in predicate.
def test_select_in_predicate1():
    ret = client.execute("select id from S where id in ('S001')")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select in predicate.
def test_select_in_predicate2():
    ret = client.execute("select id from S where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select in predicate.
def test_select_in_predicate3():
    ret = client.execute("select id from S where id in ('S004', 'S005')")
    assert ret["success"] == True
    assert ret["rows"] == 0

## test max function.
def test_max_function1():
    ret = client.execute("select max(age) from S where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 24 }

## test max function.
def test_max_function2():
    ret = client.execute("select max(age), id from S where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 24, "id": "S001" }

## test max function.
def test_max_function3():
    ret = client.execute("select max(*) from S where id in ('S001', 'S002')")
    assert ret["success"] == False

## test max function.
def test_max_function4():
    ret = client.execute("select max(100) from S where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 100 }

## test max function.
def test_max_function5():
    ret = client.execute("select max(id) from S where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 'S002' }

## test min function.
def test_min_function1():
    ret = client.execute("select min(id) from S where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": "S001" }

## test min function.
def test_min_function2():
    ret = client.execute("select min(age), name from S where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": 18, "name": "lili" }

## test min function.
def test_min_function3():
    ret = client.execute("select min(age), max(name) from S where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": 18, "max": "zhanglan" }

## test min function.
def test_min_function4():
    ret = client.execute("select min(10) from S where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": 10 }

## test count function.
def test_count_function1():
    ret = client.execute("select count(1) from S")
    assert ret["success"] == True
    assert ret["data"] == { "count": 2 }

## test count function.
def test_count_function2():
    ret = client.execute("select count(10) from S")
    assert ret["success"] == True
    assert ret["data"] == { "count": 2 }

## test count function.
def test_count_function3():
    ret = client.execute("select count(age) from S")
    assert ret["success"] == True
    assert ret["data"] == { "count": 2 }

## test count function.
def test_count_function4():
    ret = client.execute("select count(id) from S")
    assert ret["success"] == True
    assert ret["data"] == { "count": 2 }

## test sum function.
def test_sum_function1():
    ret = client.execute("select sum(id) from S")
    assert ret["success"] == True
    assert ret["data"] == { "sum": 0 }


## test sum function.
def test_sum_function2():
    ret = client.execute("select sum(age) from S")
    assert ret["success"] == True
    assert ret["data"] == { "sum": 42 }

## test avg function.
def test_avg_function1():
    ret = client.execute("select avg(age) from S")
    assert ret["success"] == True
    assert ret["data"] == { "avg": 21 }

## test avg function.
def test_avg_function2():
    ret = client.execute("select avg(id) from S")
    assert ret["success"] == True
    assert ret["data"] == { "avg": 0.0 }
