lib = File.expand_path("../lib/", __FILE__)
$:.unshift(lib) unless $:.include?(lib)

Gem::Specification.new do |s|
  s.name        = 'blah'
  s.version     = '1.0.9'
  s.date        = '2015-10-04'
  s.summary     = "Blah!"
  s.description = "Unusefull ruby gem with c extension"
  s.authors     = ["Luka Musin"]
  s.email       = 'lukapiske@gmail.com'
  s.files       = ["lib/blah.rb","ext/blah/blah.c", "ext/blah/extconf.rb"]
  s.homepage    =
    'http://lukapiske.com'
  s.license       = 'MIT'
  s.require_paths = ["lib"]
  s.extensions = ["ext/blah/extconf.rb"]
end
