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

task :default => [:compile, :flash]
