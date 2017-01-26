/*===================================================================================================
  File:                    lexer.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "lexer.h"

struct MacroData {
    String iden;
    String res;
};
static MacroData *macro_data = 0;
static Int macro_count = 0;

// TODO(Jonny): Rename some of these so they're more clear.
enum TokenType {
    TokenType_unknown,

    TokenType_open_paren,
    TokenType_close_paren,
    TokenType_colon,
    TokenType_close_param,
    TokenType_semi_colon,
    TokenType_asterisk,
    TokenType_open_bracket,
    TokenType_close_bracket,
    TokenType_open_brace,
    TokenType_close_brace,
    TokenType_open_angle_bracket,
    TokenType_close_angle_bracket,
    TokenType_hash,
    TokenType_assign,
    TokenType_comma,
    TokenType_tilde,
    TokenType_period,
    TokenType_ampersand,
    TokenType_inclusive_or,
    TokenType_not,
    TokenType_var_args,


    TokenType_plus,
    TokenType_minus,
    TokenType_divide,

    TokenType_number,
    TokenType_identifier,
    TokenType_string,

    TokenType_equal,
    TokenType_not_equal,
    TokenType_greater_than_or_equal,
    TokenType_less_than_or_equal,

    TokenType_error,

    TokenType_end_of_stream,
};

struct Token {
    Char *e;
    Int len;

    TokenType type;
};

struct Tokenizer {
    Char *at;
    // TODO(Jonny): Might be nice to have a line variable in here.
};

static Bool is_end_of_line(Char c) {
    Bool res = ((c == '\n') || (c == '\r'));

    return(res);
}

static Bool is_whitespace(Char c) {
    Bool res = ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\f') || (is_end_of_line(c)));

    return(res);
}

static Void skip_to_end_of_line(Tokenizer *tokenizer) {
    while(is_end_of_line(*tokenizer->at)) {
        ++tokenizer->at;
    }
}

static String token_to_string(Token token) {
    String res = { token.e, token.len };

    return(res);
}

static Void token_to_string(Token token, Char *buf, Int size) {
    assert(size > token.len);
    for(Int i = 0; (i < token.len); ++i, ++buf) { *buf = token.e[i]; }

    *buf = 0;
}

static Bool token_compare(Token a, Token b) {
    Bool res = false;

    if(a.len == b.len) {
        res = true;

        for(Int i = 0; (i < a.len); ++i) {
            if(a.e[i] != b.e[i]) {
                res = false;
                break; // for
            }
        }
    }

    return(res);
}

static ResultInt token_to_int(Token t) {
    String str = token_to_string(t);
    ResultInt res = string_to_int(str);

    return(res);
}

static Token get_token(Tokenizer *tokenizer); // Because C++...

static Variable parse_member(Tokenizer *tokenizer) {
    Variable res = {};
    res.array_count = 1;
    res.type = token_to_string(get_token(tokenizer));

    Bool parsing = true;
    while(parsing) {
        Token token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_asterisk:                                 { res.is_ptr = true;                 } break;
            case TokenType_identifier:                               { res.name = token_to_string(token); } break;
            case TokenType_semi_colon: case TokenType_end_of_stream: { parsing = false;                   } break;

            case TokenType_open_bracket: {
                Token size_token = get_token(tokenizer);
                if(size_token.type == TokenType_number) {
                    Char *buffer = cast(Char *)push_scratch_memory();

                    token_to_string(size_token, buffer, scratch_memory_size);
                    ResultInt arr_count = string_to_int(buffer);
                    if(arr_count.success) { res.array_count = arr_count.e;                      }
                    else                  { push_error(ErrorType_failed_to_find_size_of_array); }

                    clear_scratch_memory();
                } else {
                    // TODO(Jonny): Something _bad_ happened...
                }
            } break;
        }
    }

    return(res);
}

static Void eat_whitespace(Tokenizer *tokenizer) {
    for(;;) {
        if(is_whitespace(tokenizer->at[0])) { // Whitespace
            ++tokenizer->at;
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '/')) { // C++ comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && (!is_end_of_line(tokenizer->at[0]))) { ++tokenizer->at; }
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '*')) { // C comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && !((tokenizer->at[0] == '*') && (tokenizer->at[1] == '/'))) { ++tokenizer->at; }

            if(tokenizer->at[0] == '*') { tokenizer->at += 2; }
        } else if(tokenizer->at[0] == '#') { // #if 0 blocks.
            Char *hash_if_zero = "#if 0";
            Int hash_if_zero_length = string_length(hash_if_zero);

            Char *hash_if_one = "#if 1";
            Int hash_if_one_length = string_length(hash_if_one);

            if(string_compare(tokenizer->at, hash_if_zero, hash_if_zero_length)) {
                tokenizer->at += hash_if_zero_length;

                Char *hash_end_if = "#endif";
                Int hash_end_if_length = string_length(hash_end_if);

                Int level = 0;
                while(++tokenizer->at) {
                    if(tokenizer->at[0] == '#') {
                        if((tokenizer->at[1] == 'i') && (tokenizer->at[2] == 'f')) {
                            ++level;

                        } else if(string_compare(tokenizer->at, hash_end_if, hash_end_if_length)) {
                            if(level) {
                                --level;
                            } else {
                                tokenizer->at += hash_end_if_length;
                                eat_whitespace(tokenizer);

                                break; // for
                            }
                        }
                    }
                }
            } else if(string_compare(tokenizer->at, hash_if_one, hash_if_one_length)) { // #if 1 #else blocks.
                tokenizer->at += hash_if_zero_length;

                Char *hash_else = "#else";
                Int hash_else_length = string_length(hash_else);

                Char *hash_end_if = "#endif";
                Int hash_end_if_length = string_length(hash_end_if);

                Int level = 0;
                while(++tokenizer->at) {
                    if(tokenizer->at[0] == '#') {
                        if((tokenizer->at[1] == 'i') && (tokenizer->at[2] == 'f')) {
                            ++level;
                        } else if(string_compare(tokenizer->at, hash_end_if, hash_end_if_length)) {
                            if(level != 0) {
                                --level;
                            } else {
                                tokenizer->at += hash_end_if_length;
                                break; // for
                            }
                        } else if(string_compare(tokenizer->at, hash_else, hash_else_length)) {
                            if(level == 0) {
                                tokenizer->at += hash_else_length;
                                Int Level2 = 0;

                                while(++tokenizer->at) {
                                    if(tokenizer->at[0] == '#') {
                                        if((tokenizer->at[1] == 'i') && (tokenizer->at[2] == 'f')) {
                                            ++Level2;

                                        } else if(string_compare(tokenizer->at, hash_end_if, hash_end_if_length)) {
                                            if(Level2 != 0) {
                                                --Level2;
                                            } else {
                                                tokenizer->at += hash_end_if_length;
                                                eat_whitespace(tokenizer);

                                                break; // for
                                            }
                                        }
                                    }

                                    tokenizer->at[0] = ' ';
                                }

                                break; // for
                            }
                        }
                    }
                }
            }

            break; // for
        } else {
            break; // for
        }
    }
}

static Bool is_alphabetical(Char c) {
    Bool res = (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));

    return(res);
}

static Bool is_num(Char c) {
    Bool res = ((c >= '0') && (c <= '9'));

    return(res);
}

static Void parse_number(Tokenizer *tokenizer) {
    // TODO(Jonny): Implement.
}

#define eat_token(tokenizer) eat_tokens(tokenizer, 1)
static Void eat_tokens(Tokenizer *tokenizer, Int num_tokens_to_eat) {
    for(Int i = 0; (i < num_tokens_to_eat); ++i) {
        get_token(tokenizer);
    }
}

static Bool require_token(Tokenizer *tokenizer, TokenType desired_type) {
    Token token = get_token(tokenizer);
    Bool res = (token.type == desired_type);

    return(res);
}

static Bool peak_require_token(Tokenizer *tokenizer, Char *str) {
    Bool res = false;
    Tokenizer cpy = *tokenizer;
    Token token = get_token(&cpy);

    if(string_compare(token.e, str, token.len)) { res = true; }

    return(res);
}

static Bool is_stupid_class_keyword(Token t) {
    Char *keywords[] = { "private", "public", "protected" };
    for(Int i = 0, cnt = array_count(keywords); (i < cnt); ++i) {
        if(string_compare(keywords[i], t.e, t.len)) { return(true); }
    }

    return(false);
}

static Void skip_to_matching_bracket(Tokenizer *tokenizer) {
    Int brace_count = 1;
    Token token = {};
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_open_brace: {
                ++brace_count;
            } break;

            case TokenType_close_brace: {
                --brace_count;
                if(!brace_count) { should_loop = false; }
            } break;
        }
    }
}

static Void parse_template(Tokenizer *tokenizer) {
    Int angle_bracket_count = 1;
    Token token;
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_open_angle_bracket: {
                ++angle_bracket_count;
            } break;

            case TokenType_close_angle_bracket: {
                --angle_bracket_count;
                if(!angle_bracket_count) { should_loop = false; }
            } break;
        }
    }
}

static Token peak_token(Tokenizer *tokenizer) {
    Tokenizer cpy = *tokenizer;
    Token res = get_token(&cpy);

    return(res);
}

static Variable parse_variable(Tokenizer *tokenizer, TokenType end_token_type_1, TokenType end_token_type_2 = TokenType_unknown) {
    Variable res = {};

    // Return type.
    Token token = get_token(tokenizer);
    res.type = token_to_string(token);

    // Is pointer?
    token = get_token(tokenizer);
    if(token.type == TokenType_asterisk) {
        res.is_ptr = true;
        token = get_token(tokenizer);
    }

    // Name.
    res.name = token_to_string(token);

    // Is array?
    token = peak_token(tokenizer);
    if((token.type != end_token_type_1) && (token.type != end_token_type_2)) {
        eat_token(tokenizer);
        if(token.type != TokenType_open_bracket) { push_error(ErrorType_failed_parsing_variable); }
        else {
            token = get_token(tokenizer);
            ResultInt num = token_to_int(token);
            if(!num.success) { push_error(ErrorType_failed_parsing_variable); }
            else {
                res.array_count = num.e;
                eat_token(tokenizer); // Eat the second ']'.
            }
        }
    } else {
        res.array_count = 1;
    }

    // Skip over any assignment at the end.
    // TODO(Jonny): This won't work if a variable is assigned to a function.
    if(token.type == TokenType_assign) { eat_token(tokenizer); }

    return(res);
}

// TODO(Jonny): Create a token_equals_keyword function. This could also test macro'd aliases for keywords,
//              as well as the actual keyword.

static Bool token_equals(Token token, Char *str) {
    Bool res = false;

    Int len = string_length(str);
    if(len == token.len) { res = string_compare(token.e, str, len); }

    return(res);
}

struct ParseStructResult {
    StructData sd;
    Bool success;
};
static ParseStructResult parse_struct(Tokenizer *tokenizer, StructType struct_type) {
    ParseStructResult res = {};

    res.sd.struct_type = struct_type;

    Bool have_name = false;
    Token name = peak_token(tokenizer);
    if(name.type == TokenType_identifier) {
        have_name = true;
        res.sd.name = token_to_string(name);
        eat_token(tokenizer);
    }

    Token peaked_token = peak_token(tokenizer);
    if(peaked_token.type == TokenType_colon) {
        res.sd.inherited = alloc_arr(String, 8);

        eat_token(tokenizer);

        Token next = get_token(tokenizer);
        while(next.type != TokenType_open_brace) {
            if(!(is_stupid_class_keyword(next)) && (next.type != TokenType_comma)) {
                // TODO(Jonny): Fix properly.
                /*if(res.sd.inherited_count + 1 >= cast(Int)(get_alloc_size(res.sd.inherited) / sizeof(String))) {
                    Void *p = realloc(res.sd.inherited);
                    if(p) { res.sd.inherited = cast(String *)p; }
                }*/

                res.sd.inherited[res.sd.inherited_count++] = token_to_string(next);
            }

            next = peak_token(tokenizer);
            if(next.type != TokenType_open_brace) { eat_token(tokenizer); }
        }
    }

    if(require_token(tokenizer, TokenType_open_brace)) {
        res.success = true;

        res.sd.member_count = 0;

        struct MemberInfo {
            Char *pos;
            Bool is_inside_anonymous_struct;
        };

        MemberInfo member_info[256] = {}; // TODO(Jonny): Random number.

#if 0
        Int func_max = 8;
        res.sd.func_data = malloc_array(base_type(res.sd.func_data), func_max);
        if(!res.sd.func_data) {
            push_error(ErrorType_ran_out_of_memory);
        }
#endif

        // TODO(Jonny): Support anonymus (or however you spell it) structs in here...
        Bool inside_anonymous_struct = false;
        for(;;) {
            Token token = get_token(tokenizer);
            if((!is_stupid_class_keyword(token))) {
                // TODO(Jonny): This could be the end of an anonymous struct, so ignore it.
                if(token_equals(token, "struct")) {
                    eat_token(tokenizer); // Eat the open brace.
                    token = get_token(tokenizer);
                    inside_anonymous_struct = true;
                }

                if((token.type != TokenType_colon) && (token.type != TokenType_tilde)) {
                    if(token.type == TokenType_close_brace) {
                        if(inside_anonymous_struct) {
                            inside_anonymous_struct = false;
                            eat_token(tokenizer); // Eat semi colon.
                            continue;
                        } else if(!have_name) {
                            name = get_token(tokenizer);
                            if(name.type == TokenType_identifier) { res.sd.name = token_to_string(name);                }
                            else                                  { push_error(ErrorType_could_not_detect_struct_name); }
                        }

                        break; // for
                    } else if(token.type == TokenType_hash) {
                        while(tokenizer->at[0] != '\n') { ++tokenizer->at; }
                    } else {
                        Bool is_func = false;

                        Tokenizer tokenizer_copy = *tokenizer;
                        Token temp = get_token(&tokenizer_copy);
                        while(temp.type != TokenType_semi_colon) {
                            if(temp.type == TokenType_open_paren) { is_func = true; }

                            if(temp.type == TokenType_open_brace) {
                                is_func = true;
                                break; // while
                            }

                            temp = get_token(&tokenizer_copy);
                        }

                        if(!is_func) {
                            MemberInfo *mi = member_info + res.sd.member_count++;

                            mi->pos = token.e;
                            mi->is_inside_anonymous_struct = inside_anonymous_struct;
                        } else {
                            if(temp.type == TokenType_open_brace) { skip_to_matching_bracket(&tokenizer_copy); }
                        } /*else {
                            // This is commented out because I'm not sure I really _need_ member functions...
                            // TODO(Jonny): This fails for constructors (and probably destructors).
                            if(inline_func) {
                                skip_to_matching_bracket(&tokenizer_copy);
                            }

                            if(!token_compare(token, name)) {
                                // Get member function name and return type.
                                Tokenizer second_copy = *tokenizer;
                                FunctionData fd = {};
                                //fd.linkage = ;
                                fd.ret_type = token_to_string(token);
                                fd.name = token_to_string(get_token(&second_copy));

                                eat_token(&second_copy);

                                // Parse the parameters.
                                Token next = peak_token(&second_copy);
                                while(next.type != TokenType_close_param) {
                                    fd.params[fd.param_count++] = parse_variable(&second_copy, TokenType_comma, TokenType_close_param);

                                    next = peak_token(&second_copy);
                                    assert((next.type == TokenType_comma) || (next.type == TokenType_close_param));
                                    if(next.type == TokenType_comma) {
                                        eat_token(&second_copy);
                                    }
                                }

                                // Now store the function data.
                                res.sd.func_data[res.sd.func_count++] = fd;
                            }
                        } */

                        *tokenizer = tokenizer_copy;
                    }
                }
            }
        }

        if(res.sd.member_count > 0) {
            res.sd.members = alloc_arr(Variable, res.sd.member_count);
            if(res.sd.members) {
                for(Int i = 0; (i < res.sd.member_count); ++i) {
                    Tokenizer fake_tokenizer = { member_info[i].pos };
                    res.sd.members[i] = parse_member(&fake_tokenizer);
                    res.sd.members[i].is_inside_anonymous_struct = member_info[i].is_inside_anonymous_struct;
                }
            }
        }
    }

    return(res);
}

struct ParseEnumResult {
    EnumData ed;
    Bool success;
};
static ParseEnumResult parse_enum(Tokenizer *tokenizer) {
    ParseEnumResult res = {};

    Token name = get_token(tokenizer);
    Bool is_enum_struct = false;
    if((token_equals(name, "class")) || (token_equals(name, "struct"))) {
        is_enum_struct = true;
        name = get_token(tokenizer);
    }

    if(name.type == TokenType_identifier) {
        // If the enum has an underlying type, get it.
        Token underlying_type = {};
        Token next = get_token(tokenizer);
        if(next.type == TokenType_colon) {
            underlying_type = get_token(tokenizer);
            next = get_token(tokenizer);
        }

        if(next.type == TokenType_open_brace) {
            //res = add_token_to_enum(name, underlying_type, is_enum_struct, &tokenizer);
            assert(name.type == TokenType_identifier);
            assert((underlying_type.type == TokenType_identifier) || (underlying_type.type == TokenType_unknown));

            Token token = {};

            res.ed.is_struct = is_enum_struct;

            // If I call token_to_string here, Visual Studio 2010 ends up generating code which uses MOVAPS on unaligned memory
            // and crashes. So that's why I didn't...
            res.ed.name.e = name.e; res.ed.name.len = name.len;

            if(underlying_type.type == TokenType_identifier) { res.ed.type = token_to_string(underlying_type); }

            Tokenizer copy = *tokenizer;
            res.ed.no_of_values = 1;
            token = get_token(&copy);
            while(token.type != TokenType_close_brace) {
                // TODO(Jonny): It was stupid to count the number of commas. Instead, actually count
                //              the number of enums.
                if(token.type == TokenType_comma) {
                    Token tmp = get_token(&copy);
                    if(tmp.type == TokenType_identifier)       { ++res.ed.no_of_values; }
                    else if(tmp.type == TokenType_close_brace) { break;                 }
                }

                token = get_token(&copy);
            }

            res.ed.values = alloc_arr(EnumValue, res.ed.no_of_values);
            if(res.ed.values) {
                for(Int i = 0, count = 0; (i < res.ed.no_of_values); ++i, ++count) {
                    EnumValue *ev = res.ed.values + i;

                    Token temp_token = {};
                    while(temp_token.type != TokenType_identifier) { temp_token = get_token(tokenizer); }

                    ev->name = token_to_string(temp_token);
                    if(peak_token(tokenizer).type == TokenType_assign) {
                        eat_token(tokenizer);
                        Token num = get_token(tokenizer);

                        ResultInt r = token_to_int(num);
                        if(r.success) { count = r.e;                                }
                        else          { push_error(ErrorType_failed_to_parse_enum); }
                    }

                    ev->value = count;
                }

                res.success = true;
            }
        }
    }

    return(res);
}

static TokenType get_token_type(String s) {
    assert(s.len);

    TokenType res = TokenType_unknown;
    switch(s.e[0]) {
        case 0:   { res = TokenType_end_of_stream; } break;

        case '(': { res = TokenType_open_paren;    } break;
        case ')': { res = TokenType_close_param;   } break;
        case ':': { res = TokenType_colon;         } break;
        case ';': { res = TokenType_semi_colon;    } break;
        case '*': { res = TokenType_asterisk;      } break;
        case '[': { res = TokenType_open_bracket;  } break;
        case ']': { res = TokenType_close_bracket; } break;
        case '{': { res = TokenType_open_brace;    } break;
        case '}': { res = TokenType_close_brace;   } break;
        case ',': { res = TokenType_comma;         } break;
        case '~': { res = TokenType_tilde;         } break;
        case '#': { res = TokenType_hash;          } break;
        case '&': { res = TokenType_ampersand;     } break;
        case '+': { res = TokenType_plus;          } break;
        case '-': { res = TokenType_minus;         } break;
        case '/': { res = TokenType_divide;        } break;
        case '|': { res = TokenType_inclusive_or;  } break;

        case '=': {
            if(s.len == 1)                           { res = TokenType_assign; }
            else if((s.len == 2) && (s.e[1] == '=')) { res = TokenType_equal;  }
            else                                     { assert(0);              }
        } break;

        case '!': {
            if(s.len == 1)                           { res = TokenType_not; }
            else if((s.len == 2) && (s.e[1] == '=')) { res = TokenType_not_equal; }
        } break;

        case '>': {
            if(s.len == 1)                           { res = TokenType_open_angle_bracket;    }
            else if((s.len == 2) && (s.e[1] == '=')) { res = TokenType_greater_than_or_equal; }
            else                                     { assert(0);                             }
        } break;

        case '<': {
            if(s.len == 1)                           { res = TokenType_open_angle_bracket; }
            else if((s.len == 2) && (s.e[1] == '=')) { res = TokenType_less_than_or_equal; }
            else                                     { assert(0);                          }
        } break;

        default: {
            if(is_num(s.e[0])) { res = TokenType_number;     }
            else               { res = TokenType_identifier; }
        } break;
    }

    return(res);
}

static Token string_to_token(String str) {
    Token res = {};

    res.e = str.e;
    res.len = str.len;
    res.type = get_token_type(str);

    return(res);
}

static Token get_token(Tokenizer *tokenizer) {
    eat_whitespace(tokenizer);

    Token res = {};
    res.len = 1;
    res.e = tokenizer->at;
    Char c = tokenizer->at[0];
    ++tokenizer->at;

    switch(c) {
        case 0:   { res.type = TokenType_end_of_stream; } break;

        case '(': { res.type = TokenType_open_paren;    } break;
        case ')': { res.type = TokenType_close_param;   } break;
        case ':': { res.type = TokenType_colon;         } break;
        case ';': { res.type = TokenType_semi_colon;    } break;
        case '*': { res.type = TokenType_asterisk;      } break;
        case '[': { res.type = TokenType_open_bracket;  } break;
        case ']': { res.type = TokenType_close_bracket; } break;
        case '{': { res.type = TokenType_open_brace;    } break;
        case '}': { res.type = TokenType_close_brace;   } break;
        case ',': { res.type = TokenType_comma;         } break;
        case '~': { res.type = TokenType_tilde;         } break;
        case '#': { res.type = TokenType_hash;          } break;
        case '&': { res.type = TokenType_ampersand;     } break;
        case '+': { res.type = TokenType_plus;          } break;
        case '-': { res.type = TokenType_minus;         } break;
        case '/': { res.type = TokenType_divide;        } break;
        case '|': { res.type = TokenType_inclusive_or;  } break;

        case '=': {
            Token next = peak_token(tokenizer);
            if(next.type == TokenType_assign) { res.type = TokenType_equal;  res.len = 2; }
            else                              { res.type = TokenType_assign;              }
        } break;

        case '!': {
            Token next = peak_token(tokenizer);
            if(next.type == TokenType_assign) { res.type = TokenType_not_equal; res.len = 2; }
            else                              { res.type = TokenType_not;                    }
        } break;

        case '>': {
            Token next = peak_token(tokenizer);
            if(next.type == TokenType_assign) { res.type = TokenType_greater_than_or_equal; res.len = 2; }
            else                              { res.type = TokenType_close_angle_bracket;                }
        } break;

        case '<': {
            Token next = peak_token(tokenizer);
            if(next.type == TokenType_assign) { res.type = TokenType_less_than_or_equal; res.len = 2; }
            else                              { res.type = TokenType_open_angle_bracket;              }
        } break;

        case '.':  {
            Bool var_args = false;
            Tokenizer tokenizer_copy = *tokenizer;
            Token next = get_token(&tokenizer_copy);
            if(next.type == TokenType_period) {
                next = get_token(&tokenizer_copy);
                if(next.type == TokenType_period) {
                    var_args = true;

                    res.type = TokenType_var_args;
                    res.len = 3;

                    eat_tokens(tokenizer, 2);
                }
            }

            if(!var_args) { res.type = TokenType_period; }
        } break;

        case '"': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '"')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { ++tokenizer->at; }
                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '"') { ++tokenizer->at; }
        } break;

        case '\'': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '\'')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { ++tokenizer->at; }
                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '\'') { ++tokenizer->at; }
        } break;

        default: {
            if((is_alphabetical(c)) || (c == '_')) {
                while((is_alphabetical(tokenizer->at[0])) || (is_num(tokenizer->at[0])) || (tokenizer->at[0] == '_')) {
                    ++tokenizer->at;
                }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_identifier;
            } else if(is_num(c)) {
                while(is_num(tokenizer->at[0])) { ++tokenizer->at; }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_number;
            } else {
                res.type = TokenType_unknown;
            }
        } break;
    }

    if(res.type == TokenType_identifier) {
        Bool changed = false;
        do {
            changed = false;
            for(Int i = 0; (i < macro_count); ++i) {
                MacroData *md = macro_data + i;

                String token_as_string = token_to_string(res);
                if(string_compare(token_as_string, md->iden)) {
                    res = string_to_token(md->res);
                    changed = true;
                }
            }
        } while(changed);
    }

    //if(res.type == TokenType_unknown) { push_error(ErrorType_unknown_token_found); }

    return(res);
}

ParseResult parse_stream(Char *stream) {
    ParseResult res = {};

    Int enum_max = 8;
    res.enum_data = alloc_arr(EnumData, enum_max);

    Int struct_max = 32;
    res.struct_data = alloc_arr(StructData, struct_max);

    Int macro_max = 32;
    macro_data = alloc_arr(MacroData, macro_max);

    if((res.enum_data)  && (res.struct_data) && (macro_data)) {
        Tokenizer tokenizer = { stream };

        Bool parsing = true;
        while(parsing) {
            Token token = get_token(&tokenizer);
            switch(token.type) {
                case TokenType_end_of_stream: { parsing = false; } break;

                case TokenType_hash: {
                    if(peak_require_token(&tokenizer, "define")) {
                        eat_token(&tokenizer);

                        MacroData *md = macro_data + macro_count++;
                        memset(md, 0, sizeof(*md));

                        md->iden = token_to_string(get_token(&tokenizer));
                        eat_whitespace(&tokenizer);
                        md->res.e = tokenizer.at;
                        while(!is_end_of_line(*tokenizer.at)) {
                            ++md->res.len;
                            ++tokenizer.at;
                        }
                    } else { skip_to_end_of_line(&tokenizer); }
                } break;

                case TokenType_identifier: {
                    // TODO(Jonny): I may need to keep the template header, so that the generated structs still work.
                    if(token_equals(token, "template")) {
                        eat_token(&tokenizer);
                        parse_template(&tokenizer);
                    } else if((token_equals(token, "struct")) || (token_equals(token, "class")) || (token_equals(token, "union"))) {
                        StructType struct_type = StructType_unknown;

                        if(token_equals(token, "struct"))     { struct_type = StructType_struct; }
                        else if(token_equals(token, "class")) { struct_type = StructType_class;  }
                        else if(token_equals(token, "union")) { struct_type = StructType_union;  }

                        if(res.struct_cnt + 1 >= struct_max) {
                            struct_max *= 2;
                            Void *p = realloc(res.struct_data, struct_max);
                            if(p) { res.struct_data = cast(StructData *)p; }
                        }

                        ParseStructResult r = parse_struct(&tokenizer, struct_type);

                        // TODO(Jonny): This fails at a struct declared within a struct/union.
                        if(r.success) { res.struct_data[res.struct_cnt++] = r.sd; }
                    } else if(token_equals(token, "enum")) {
                        if(res.enum_cnt + 1 >= enum_max) {
                            enum_max *= 2;
                            Void *p = realloc(res.enum_data, enum_max);
                            if(p) { res.enum_data = cast(EnumData *)p; }
                        }

                        ParseEnumResult r = parse_enum(&tokenizer);
                        if(r.success) { res.enum_data[res.enum_cnt++] = r.ed; }
                    } else if(token_equals(token, "union")) {
                        StructType struct_or_class =
                            token_equals(token, "struct") ? StructType_struct : StructType_class;
                        if(res.struct_cnt + 1 >= struct_max) {
                            struct_max *= 2;
                            Void *p = realloc(res.struct_data, struct_max);
                            if(p) { res.struct_data = cast(StructData *)p; }
                        }

                        ParseStructResult r = parse_struct(&tokenizer, struct_or_class);

                        // TODO(Jonny): This fails at a struct declared within a struct/union.
                        if(r.success) { res.struct_data[res.struct_cnt++] = r.sd; }
                    }
                } break;
            }
        }

        free(macro_data);
    }


    return(res);
}
