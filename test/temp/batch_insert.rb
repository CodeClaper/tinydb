RSpec.describe 'main' do
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
  it 'batch insert and make page full' do
    script = (1..100).map do |i|
        "insert into test values (#{100 + i}, 'zhangsan', 20, 'beijing');"
    end
    script << "exit"
    result = run_script(script)
    expect(result.last(2)).to match_array([
          "tinydb > Successfully insert 1 row data.",
          "tinydb > Goodbye.",
          "tinydb > ",
    ])
  end
end
