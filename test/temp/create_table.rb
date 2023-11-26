RSpec.describe 'main' do
  before do
    `rm -f /data/test.dbt`
  end
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
  it 'create table test' do
      result = run_script([
         'create table test (id int, name string, age int, address string, primary key(id));',
         'exit'
      ])
      expect(result).to match_array([
          "tinydb > Table 'test' created successfully.",
          "tinydb > Goodbye.",
      ])
  end
end
