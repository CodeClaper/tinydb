# select_test.py

from support.tinydb_cli import TinyDbClient


client = TinyDbClient("127.0.0.1", 4083)

## test select all
def test_select_all():
    ret = client.execute("select * from Students");
    assert ret["success"] == True
    assert ret["rows"] == 3

## test select one item
def test_select_one_item():
    ret = client.execute("select id from Students");
    assert ret["success"] == True
    assert ret["data"] == [{ "id": "S001" }, {"id": "S002"}, { "id": "S003" }]

## test select multiple items
def test_select_items():
    ret = client.execute("select id, name from Students");
    assert ret["success"] == True
    assert ret["data"] == [{ "id": "S001", "name": "lili" }, { "id": "S002", "name": "wanglang" }, { "id": "S003", "name": "zhaoxia" }]


## test select not exists items.
def test_select_not_exist_items():
    ret = client.execute("select email from Students");
    assert ret["success"] == False

## test select condition field not exist.
def test_select_not_exist_condition_filed():
    ret = client.execute("select id from Students where email = '947762323@qq.com'")
    assert ret["success"] == False

## test select simple condition.
def test_select_simple_condition():
    ret = client.execute("select id from Students where id = 'S001'");
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select complex condition
def test_select_complex_condition1():
    ret = client.execute("select id from Students where age = 8 and address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == { "id": "S001" }

## test select complex condition
def test_select_complex_condition2():
    ret = client.execute("select id from Students where age > 20 and address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == []

## test select complex condition
def test_select_complex_condition3():
    ret = client.execute("select id from Students where age < 10 and age > 5 or address = 'shanghai'")
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select complex condition
def test_select_complex_condition4():
    ret = client.execute("select id from Students where (age < 10 and age > 5 or address = 'beijing')")
    assert ret["success"] == True
    assert ret["rows"] == 3

## test select like predicate.
def test_select_like_predicate1():
    ret = client.execute("select id from Students where address like 'bei%'")
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select like predicate.
def test_select_like_predicate2():
    ret = client.execute("select id from Students where address like '%hai'")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select like predicate.
def test_select_like_predicate3():
    ret = client.execute("select id from Students where address like '%ng%'")
    assert ret["success"] == True
    assert ret["rows"] == 3

## test select like predicate.
def test_select_like_predicate4():
    ret = client.execute("select id from Students where address like 'shanghai'")
    assert ret["success"] == True
    assert ret["rows"] == 1


## test select in predicate.
def test_select_in_predicate1():
    ret = client.execute("select id from Students where id in ('S001')")
    assert ret["success"] == True
    assert ret["rows"] == 1

## test select in predicate.
def test_select_in_predicate2():
    ret = client.execute("select id from Students where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["rows"] == 2

## test select in predicate.
def test_select_in_predicate3():
    ret = client.execute("select id from Students where id in ('S004', 'S005')")
    assert ret["success"] == True
    assert ret["rows"] == 0

## test max function.
def test_max_function1():
    ret = client.execute("select max(age) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "max": 10 }

## test max function.
def test_max_function2():
    ret = client.execute("select max(age), id from Students where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 10, "id": "S001" }

## test max function.
def test_max_function3():
    ret = client.execute("select max(*) from Students where id in ('S001', 'S002')")
    assert ret["success"] == False

## test max function.
def test_max_function4():
    ret = client.execute("select max(100) from Students where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 100 }

## test max function.
def test_max_function5():
    ret = client.execute("select max(id) from Students where id in ('S001', 'S002')")
    assert ret["success"] == True
    assert ret["data"] == { "max": 'S002' }

## test min function.
def test_min_function1():
    ret = client.execute("select min(id) from Students where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": "S001" }

## test min function.
def test_min_function2():
    ret = client.execute("select min(age), name from Students where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": 7, "name": "lili" }

## test min function.
def test_min_function3():
    ret = client.execute("select min(age), max(name) from Students where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": 7, "max": "zhaoxia" }

## test min function.
def test_min_function4():
    ret = client.execute("select min(10) from Students where id like 'S%'")
    assert ret["success"] == True
    assert ret["data"] == { "min": 10 }

## test count function.
def test_count_function1():
    ret = client.execute("select count(1) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "count": 3 }

## test count function.
def test_count_function2():
    ret = client.execute("select count(10) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "count": 3 }

## test count function.
def test_count_function3():
    ret = client.execute("select count(age) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "count": 3 }

## test count function.
def test_count_function4():
    ret = client.execute("select count(id) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "count": 3 }

## test sum function.
def test_sum_function1():
    ret = client.execute("select sum(id) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "sum": 0 }


## test sum function.
def test_sum_function2():
    ret = client.execute("select sum(age) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "sum": 25 }

## test avg function.
def test_avg_function1():
    ret = client.execute("select avg(age) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "avg": 8.333333}

## test avg function.
def test_avg_function2():
    ret = client.execute("select avg(id) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "avg": 0.0 }

## test calculate selection
def test_calculate_selection_add1():
    ret = client.execute("select count(id) + count(1) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "add": 6 }

## test calculate selection
def test_calculate_selection_add2():
    ret = client.execute("select age + age from Students")
    assert ret["success"] == True
    assert ret["data"] == [{ "add": 16 }, { "add": 20 }, { "add": 14 }]

## test calculate selection
def test_calculate_selection_add3():
    ret = client.execute("select age + age from Students where id = 'S001'")
    assert ret["success"] == True
    assert ret["data"] == { "add": 16 }

## test calculate selection
def test_calculate_selection_sub1():
    ret = client.execute("select sum(age) - sum(class) from Students")
    assert ret["success"] == True
    assert ret["data"] == { "sub": 15 }

## test calculate selection
def test_calculate_selection_sub2():
    ret = client.execute("select sum(age) - sum(class) from Students where address = 'beijing'")
    assert ret["success"] == True
    assert ret["data"] == { "sub": 10 }

## test calculate select not exists column
def test_calculate_selection_none_column():
    ret = client.execute("select age - none from Students where address = 'beijing'")
    assert ret["success"] == False
    
