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
  unless ENV["COLOR"]
    abort("Missing COLOR.")
  end

  color_map = {
    off: 0,
    green: 1,
    yellow: 2,
    red: 3,
    blue: 4,
  }

  colors = ENV["COLOR"].split(",").map { |c| color_map[c.to_sym] }

  colors.each do |id|
    unless id
      abort("Invalid color: #{ENV["COLOR"]}")
    end
  end

  system "spark call #{ENV["SPARK_DEVICE"]} update '#{colors.join(';')};'"
end

desc "Reset all colors on the button"
task :reset do
  system "spark call #{ENV["SPARK_DEVICE"]} update '0;0;0;0;0;0;0;0;0;0;0;'"
end

task :default => [:compile, :flash]
