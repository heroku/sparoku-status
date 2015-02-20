desc "Compile firmware to firmware.bin"
task :compile do
  out = `spark compile . firmware.bin`
  # can't rely on exit status :{
  unless out.include?("Compiled firmware downloaded")
    abort("Compilation failed:\n\n#{out}")
  end
  puts "Compiled"
end

desc "Flash device specified in SPARK_DEVICE with latest compiled firmware"
task :flash do
  unless ENV["SPARK_DEVICE"]
    abort("Missing SPARK_DEVICE.")
  end
  system "spark flash #{ENV["SPARK_DEVICE"]} firmware.bin"
end

desc "Simulate a call from Sparoku Drain"
task :simulate do
  unless ENV["STATE"]
    abort("Missing STATE.")
  end

  states_map = {
    down:    0,
    up:      1,
    serving: 2,
    error:   3,
    crashed: 4,
    booting: 5,
    idle:    6,
  }

  state = ENV["STATE"].split(",").map { |s| states_map[s.to_sym] }

  state.each do |id|
    unless id
      abort("Invalid state: #{ENV["STATE"]}")
    end
  end

  system "spark call #{ENV["SPARK_DEVICE"]} update '#{state.join(';')};'"
end

desc "Reset all colors on the button"
task :reset do
  system "spark call #{ENV["SPARK_DEVICE"]} update '0;0;0;0;0;0;0;0;0;0;0;'"
end

task :default => [:compile, :flash]
