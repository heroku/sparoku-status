task :compile do
  out = `spark compile . firmware.bin`
  # can't rely on exit status :{
  unless out.include?("Compiled firmware downloaded")
    abort("Compilation failed:\n\n#{out}")
  end
  puts "Compiled"
end

task :flash do
  unless ENV["SPARK_DEVICE"]
    abort("Missing SPARK_DEVICE.")
  end
  system "spark flash #{ENV["SPARK_DEVICE"]} firmware.bin"
end

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

task :default => [:compile, :flash]
