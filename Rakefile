task :compile do
  out = `spark compile . firmware.bin`
  # can't rely on exit status :{
  unless out.include?("Compiled firmware downloaded")
    abort("Compilation failed:\n\n#{out}")
  end
  puts "Compiled"
end

task :flash do
  system "spark flash herokore firmware.bin"
end

task :default => [:compile, :flash]
