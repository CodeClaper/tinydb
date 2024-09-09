
from support.tinydb_cli import TinyDbClient
from support.asserts import assert_all

client = TinyDbClient("127.0.0.1", 4083)    

def test_read_sql_script():
    with open('test/pytest/bigData/sql/bo_qdbixlsx_sheet2.sql', encoding= 'utf-8') as file:
        for line in file:
            sql = line.strip()
            ret = client.execute(sql)
            assert ret["success"] == True
