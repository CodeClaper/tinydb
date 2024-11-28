
## assert all
def assert_all(ret):
    for ele in ret:
        if ele["success"] == False:
            raise Exception(f"Not satisfy: {ele['message']}")
    
