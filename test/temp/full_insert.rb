 
def run_script(commands) 
   raw_output = nil
   IO.popen("./tinydb-cli", "r+") do |pipe|
     commands.each do |command|
       begin
         pipe.puts command
       rescue Errno::EPIPE
         break
       end
     end
     pipe.close_write
     raw_output = pipe.gets(nil)
   end
   raw_output.split("\n").each do |msg|
        puts msg
   end
end
##`rm -f data/test.dbt`
#run_script(["create table test (id int, name string, age int, address string, primary key(id));"])
insert_script = (1..1000).map do |i|
   "insert into test values (#{100 + i}, 'zhangsan', 20, 'beijing');"
end
insert_script << "exit"
run_script(insert_script)