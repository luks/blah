require "rubygems"
require "rake"
require 'rake/testtask'

require "rake/extensiontask"
Rake::ExtensionTask.new("blah") do |extension|
  extension.lib_dir = "lib/blah"
end


Rake::TestTask.new do |t|
  t.libs << 'test'
end

desc "Run tests"
task :default => :test