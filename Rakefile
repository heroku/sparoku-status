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
  unless ENV["DYNO"] && ENV["COLOR"]
    abort("Missing DYNO/COLOR.")
  end

  color = {
    off: 0,
    green: 1,
    yellow: 2,
    red: 3,
    blue: 4,
  }[ENV["COLOR"].to_sym]

  unless color
    abort("Invalid color: #{ENV["COLOR"]}")
  end

  system "spark call #{ENV["SPARK_DEVICE"]} update '#{ENV["DYNO"]}=#{color};'"
end

desc "Reset all colors on the button"
task :reset do
  system "spark call #{ENV["SPARK_DEVICE"]} update '0=0;1=0;2=0;3=0;4=0;5=0;6=0;7=0;8=0;9=0;'"
end

task :default => [:compile, :flash]
