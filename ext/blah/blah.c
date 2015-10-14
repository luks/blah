#include <ruby.h>
#include <stdio.h> //remove latter
#include <regex.h>
#include <string.h> //strlen
#include <stdlib.h> //malloc, memcpy

/*
  header
*/
typedef struct {
    int numerator, denominator;
    double value;
} ratio_s;


typedef struct {
    const char *string;
    const char *regex;
    char ***substrings;
    _Bool use_case;
} regex_fn_s;


#define regex_match(...) regex_match_base((regex_fn_s){__VA_ARGS__})
int regex_match_base(regex_fn_s in);


enum {
  ERROR_REGEX_NOT_COMPILED = -1,
  ERROR_NOT_INPUT_STRING = -2,
  ERROR_NOT_INPUT_REGEX = -3,
};

/*
  end of header
*/

static int count_parens(const char *string)
{
    int out = 0;
    int last_was_backslash = 0;
    for(const char *step=string; *step !='\0'; step++){
        if (*step == '\\' && !last_was_backslash){
            last_was_backslash = 1;
            continue;
        }
        if (*step == ')' && !last_was_backslash)
            out++;
        last_was_backslash = 0;
    }
    return out;
}

int regex_match_base(regex_fn_s in)
{
    regex_t re;
    int matchcount = 0;
    if (!in.string) return ERROR_NOT_INPUT_STRING;
    if (!in.regex)  return ERROR_NOT_INPUT_REGEX;
    if (in.substrings) matchcount = count_parens(in.regex);
    regmatch_t result[matchcount+1];
    int compiled_ok = !regcomp(&re, in.regex, REG_EXTENDED
                                            + (in.use_case ? 0 : REG_ICASE)
                                            + (in.substrings ? 0 : REG_NOSUB) );
    if (!compiled_ok) return ERROR_REGEX_NOT_COMPILED;

    int found = !regexec(&re, in.string, matchcount+1, result, 0);
    if (!found) return 0;
    if (in.substrings){
         *in.substrings = malloc(sizeof(char*) * matchcount);
         char **substrings = *in.substrings;
        //match zero is the whole string; ignore it.
        for (int i=0; i< matchcount; i++){
            if (result[i+1].rm_eo > 0){//GNU peculiarity: match-to-empty marked with -1.
                int length_of_match = result[i+1].rm_eo - result[i+1].rm_so;
                substrings[i] = malloc(strlen(in.string)+1);
                memcpy(substrings[i], in.string + result[i+1].rm_so, length_of_match);
                substrings[i][length_of_match] = '\0';
            } else { //empty match
                substrings[i] = malloc(1);
                substrings[i][0] = '\0';
            }
        }
        in.string += result[0].rm_eo; //end of whole match;
    }
    regfree(&re);
    return matchcount;
}

ratio_s new_ratio(int num, int den)
{
    return (ratio_s){.numerator=num, .denominator=den, .value=num/(double)den};
}

ratio_s ratio_add(ratio_s left, ratio_s right)
{
    return (ratio_s){
        .numerator=left.numerator*right.denominator
                     + right.numerator*left.denominator,
        .denominator=left.denominator * right.denominator,
        .value=left.value + right.value
    };
}

static VALUE c_match;

static VALUE match(VALUE self, VALUE string, VALUE regex)
{

  char **substrings;
  int match_ct =  regex_match(RSTRING_PTR(string), RSTRING_PTR(regex), &substrings);
  VALUE result = rb_ary_new();

  if(match_ct > 0) {
    for (int i=0; i< match_ct; i++){
        rb_ary_push(result, rb_str_new2(substrings[i]));
        free(substrings[i]);
    }
    free(substrings);
  }
  return result;
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

void Init_blah()
{
  VALUE mBlah = rb_define_module("Blah");
  c_match = rb_define_class_under(mBlah, "Match", rb_cObject);
  rb_define_singleton_method(mBlah, "hello_world", hello_world, 0);
  rb_define_singleton_method(mBlah, "print_ratio", print_ratio, 2);
  rb_define_singleton_method(mBlah, "match", match, 2);

}



