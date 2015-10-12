gem "minitest"
require "minitest/autorun"
require "blah"

class TestBlah < Minitest::Test

  def test_hello_world
    assert_equal 'hello world', Blah.hello_world
  end

  def test_match
    assert_equal ["10"], Blah.match("10.2.32.104","(\\w+)")
    assert_equal ["10.2.32.104"], Blah.match("10.2.32.104","([^[:space:]]+)")
    assert_equal ["10.2.32.104"], Blah.match("10.2.32.104","(\\S+)")

    string = "10.2.32.104/255.255.255.0 via 10.2.32.1 at d4:be:d9:ad:23:d8 (Static Address)"
    regex = "^(\\S+)/(\\S+) via (\\S+) at (\\S+) \\((.*)\\)$"
    assert_equal ["10.2.32.104", "255.255.255.0", "10.2.32.1", "d4:be:d9:ad:23:d8", "Static Address"], Blah.match(string, regex)

  end
end

