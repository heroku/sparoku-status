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
  state = ENV["STATE"] || (0..6).to_a.join
  state.each_char do |char|
    unless char =~ /\d/ && (0..6).include?(char.to_i)
      abort("Invalid state: #{ENV['STATE']}")
    end
  end
  puts "calling with #{state}"
  system "spark call #{ENV["SPARK_DEVICE"]} update '#{state}'"
end

desc "Reset all colors on the button"
task :reset do
  system "spark call #{ENV["SPARK_DEVICE"]} update '#{"0" * 12}'"
end

task :default => [:compile, :flash]
