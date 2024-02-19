
from support.tinydb_cli import TinyDbClient

client = TinyDbClient("127.0.0.1", 4083)    

nameList = [ "zhangsan", "lisi", "wangwu", "zhaoliu" ]
classList = ["C001", "C002"]

## test select.
def test_select():
    for i in range(1, 20000):
        ret = client.execute("select * from Student");
        assert ret["success"] == True
