gem "minitest"
require "minitest/autorun"
require "blah"

class TestBlah < Minitest::Test

  def test_hello_world
    assert_equal 'hello world', Blah.hello_world
  end
end

