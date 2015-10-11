#include <ruby.h>
#include <stdio.h>

typedef struct {
    int numerator, denominator;
    double value;
} ratio_s;

ratio_s new_ratio(int num, int den){
    return (ratio_s){.numerator=num, .denominator=den, .value=num/(double)den};
}

ratio_s ratio_add(ratio_s left, ratio_s right){
    return (ratio_s){
        .numerator=left.numerator*right.denominator
                     + right.numerator*left.denominator,
        .denominator=left.denominator * right.denominator,
        .value=left.value + right.value
    };
}

static VALUE print_ratio(VALUE self, VALUE num, VALUE den)
{
  ratio_s ratio;
  int n = FIX2INT(num);
  int d = FIX2INT(den);
  ratio = new_ratio(n, d);
  return rb_float_new(ratio.value);
}


static VALUE hello_world(VALUE mod)
{
  return rb_str_new2("hello world");
}


static VALUE hello(VALUE self, VALUE arg) {
  char* name = RSTRING_PTR(arg);
  printf("Hello %s!\n", name);
  return Qnil;
}

static VALUE goodbye(VALUE class) {
  printf("Later dude!\n");
  return Qnil;
}

void Init_blah()
{
  VALUE mBlah = rb_define_module("Blah");
  rb_define_singleton_method(mBlah, "hello_world", hello_world, 0);
  rb_define_singleton_method(mBlah, "print_ratio", print_ratio, 2);
  rb_define_method(mBlah, "hello_world", hello_world, 0);
  rb_define_method(mBlah, "hello", hello, 1);
  rb_define_method(mBlah, "goodbye", goodbye, 0);

}



