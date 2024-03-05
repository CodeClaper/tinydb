
from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

nameList = [ "zhangsan", "lisi", "wangwu", "zhaoliu" ]
classList = ["C0001", "C0002", "C0003", "C0004"]

## test insert one.
def test_insert1():
    for i in range(1, 10000):
        client.execute("insert into Student values('{}', '{}', {}, '{}', ref(id='{}'));".format(i, nameList[i % 4], 10, 'M', classList[i % 4]))

