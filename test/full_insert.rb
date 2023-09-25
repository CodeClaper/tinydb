 
def run_script(commands) 
   raw_output = nil
   IO.popen("./tinydb", "r+") do |pipe|
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
   raw_output.split("\n")
end
`rm -f data/test.dbt`
run_script(["create table test (id int, name string, age int, address string, primary key(id));"])
insert_script = (1..95).map do |i|
   if i == 58
   "insert into test values (#{100 + i}, 'lisi', 20, 'beijing');"
   else
   "insert into test values (#{100 + i}, 'zhangsan', 20, 'beijing');"
   end
end
insert_script << "exit"
run_script(insert_script)
