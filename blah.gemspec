lib = File.expand_path("../lib/", __FILE__)
$:.unshift(lib) unless $:.include?(lib)

Gem::Specification.new do |s|
  s.name        = 'blah'
  s.version     = '1.1.1'
  s.date        = '2015-10-04'
  s.summary     = "Blah!"
  s.description = "Unusefull ruby gem with c extension"
  s.authors     = ["Luka Musin"]
  s.email       = 'lukapiske@gmail.com'
  s.files       = Dir['lib/**/*.rb'] + Dir['ext/**/*.so'] + Dir['ext/**/*.c']
  s.homepage    = 'http://lukapiske.com'
  s.license       = 'MIT'
  s.require_paths = ['lib', 'ext']
  s.extensions = Dir['ext/**/extconf.rb']
end
