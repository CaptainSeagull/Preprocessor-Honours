/*===================================================================================================
  File:                    preprocessor.cpp
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#include "platform.h"

internal Int
get_digit_count(Int value)
{
    Int res = 1;
    while((value /= 10) > 0) {
        ++res;
    }

    return(res);
}

internal Void
copy_int(Char *dest, Int value, Int start, Int count)
{
    assert(dest);

    Int end = start + count;
    for(Int index = end - 1; (index >= start); --index, value /= 10) {
        *(dest + index) = cast(Char)(value % 10 + 48);
    }

    dest[end] = 0;
}

internal Char *
int_to_string(Int value, Char *buf)
{
    assert(buf);

    Bool is_neg = (value < 0);
    Int abs_value = (is_neg) ? -value : value;
    Int num_digits = get_digit_count(abs_value);
    if(is_neg) {
        Char *ptr = buf;
        *ptr = '-';
        copy_int(ptr, abs_value, 1, num_digits);
    } else {
        Char *ptr = buf;
        copy_int(ptr, abs_value, 0, num_digits);
    }

    return(buf);
}

internal Char *
float_to_string(Float value, Int dec_accuracy, Char *buf)
{
    assert(buf);

    Bool is_neg = (value < 0);
    Float abs_value = (is_neg) ? -value : value;

    Int mul = 1;
    for(Int dec_index = 0; (dec_index < dec_accuracy); ++dec_index) {
        mul *= 10;
    }

    Int num_as_whole = cast(Int)(abs_value * mul);
    Int num_before_dec = num_as_whole / mul;
    Int num_after_dec = num_as_whole % mul;
    Int digit_count_before_dec = get_digit_count(num_before_dec);
    Int digit_count_after_dec = get_digit_count(num_after_dec);

    if(is_neg) {
        Char *ptr = buf;
        *ptr = '-';
        copy_int(ptr, num_before_dec, 1, digit_count_before_dec);
        *(ptr + digit_count_before_dec + 1) = '.';
        copy_int(ptr, num_after_dec, digit_count_before_dec + 2, digit_count_after_dec);
    } else {
        Char *ptr = buf;
        copy_int(ptr, num_before_dec, 0, digit_count_before_dec);
        *(ptr + digit_count_before_dec) = '.';
        copy_int(ptr, num_after_dec, digit_count_before_dec + 1, digit_count_after_dec);
    }

    return(buf);
}

internal Char *
bool_to_string(Bool b)
{
    Char *res = cast(Char *)((b) ? "true" : "false");

    return(res);
}

internal Bool
is_numeric(Char input)
{
    Bool res = ((input >= '0') && (input <= '9'));

    return(res);
}

// Printf replacement.
// %s     - Nul terminated string.
// %S     - String: Len and string.
// %d, %i - Integer.
// %u     - Unsigned Integer.
// %c     - Char
// %b     - Boolean
// %f     - Float
// TODO(Jonny): Print hex numbers for pointers.
internal Int
format_string_varargs(Char *buf, Int buf_len, Char *format, va_list args)
{
    assert((buf) && (buf_len) && (format));

    Char *dest = cast(Char *)buf;
    Int bytes_written = 0;
    Int float_precision = 1;
    Int next_fractional_digit = float_precision;

    // TODO(Jonny): Remove shadowing of temp_buffer.
    while(*format) {
        Char temp_buffer[1024] = {};
        Char c = *format;
        if(c == '%') {
            Char type = format[1];
            if(type == 'c') {
                *dest++ = cast(Char)va_arg(args, int);
                bytes_written++;
            } else {
                if(is_numeric(type)) {
                    next_fractional_digit = type - 48;
                    assert(format[2] == 'f');
                    type = 'f';
                    format++;
                }

                Char *replacement = 0;
                switch(type) {
                    case 'b': {
                        int boolean = va_arg(args, int);
                        replacement = bool_to_string(boolean != 0);
                    } break;

                    case 'd': case 'i': {
                        Int integer = va_arg(args, Int);
                        Char temp_buffer_2[1024] = {};
                        replacement = int_to_string(integer, temp_buffer_2);
                    } break;

                    case 'u': {
                        Uint unsigned_int = va_arg(args, Uint);
                        Char temp_buffer_2[1024] = {};
                        replacement = int_to_string(unsigned_int, temp_buffer_2);
                    } break;

                    case 'f': {
                        Float float_num = cast(Float)va_arg(args, Float64);
                        Char temp_buffer_2[1024] = {};
                        replacement = float_to_string(float_num, next_fractional_digit, temp_buffer_2);
                        next_fractional_digit = float_precision;
                    } break;

                    case 's': {
                        Char *str = va_arg(args, Char *);
                        replacement = str;
                    } break;

                    case 'S': {
                        Int len = va_arg(args, Int);
                        Char *str = va_arg(args, Char *);

                        assert(len < array_count(temp_buffer));
                        Char *at = temp_buffer;
                        for(Int str_index = 0; (str_index < len); ++str_index, ++at) {
                            *at = str[str_index];
                        }

                        *at = 0;

                        replacement = temp_buffer;
                    } break;

                    case '%': {
                        temp_buffer[0] = '%';
                        replacement = temp_buffer;
                    }
                }

                if(replacement) {
                    while(*replacement) {
                        *dest++ = *replacement++;
                        bytes_written++;
                    }
                }
            }

            format++;
        } else {
            *dest++ = c;
            bytes_written++;
        }

        format++;
    }

    *dest = 0;

    assert(bytes_written < buf_len);

    return(bytes_written);
}

internal Int
format_string(Char *buf, Int buf_len, Char *format, ...)
{
    assert((buf) && (buf_len) && (format));

    va_list args;
    va_start(args, format);
    Int bytes_written = format_string_varargs(buf, buf_len, format, args);
    assert((bytes_written > 0) && (bytes_written < buf_len));
    va_end(args);

    return(bytes_written);
}

struct OutputBuffer {
    Char *buffer;
    Int index;
    Int size;
};

internal Void
write_to_output_buffer(OutputBuffer *ob, Char *format, ...)
{
    assert((ob) && (ob->buffer) && (ob->size > 0) && (ob->index < ob->size));
    assert(format);

    va_list args;
    va_start(args, format);
    ob->index += format_string_varargs(ob->buffer + ob->index, ob->size - ob->index, format, args);
    va_end(args);
}

internal OutputBuffer
create_output_buffer(Int size, Memory *memory)
{
    assert((size > 0) && (memory));

    OutputBuffer res = {};
    res.buffer = cast(Char *)push_permanent_memory(memory, size);
    res.size = size;

    return(res);
}

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
    TokenType_hash,
    TokenType_equals,
    TokenType_comma,
    TokenType_tilde,
    TokenType_period,
    TokenType_var_args,

    TokenType_number,
    TokenType_identifier,
    TokenType_string,

    TokenType_end_of_stream,
};

struct Token {
    Char *e;
    Int len;

    TokenType type;
};

struct Tokenizer {
    Char *at;
};

struct String {
    Char *e;
    Int len;
};

internal String
token_to_string(Token token)
{
    assert(token.type != TokenType_unknown);

    String res = {};
    res.e = token.e;
    res.len = token.len;

    return(res);
}

internal Char *
token_to_string(Token token, Char *buffer, Int size)
{
    assert((token.type) && (buffer) && (size >= token.len));

    zero_memory_block(buffer, size);
    for(Int str_index = 0; (str_index < token.len); ++str_index) {
        buffer[str_index] = token.e[str_index];
    }

    return(buffer);
}

internal Bool
string_compare(Char *a, Char *b, Int len)
{
    assert((a) && (b) && (len > 0));

    Bool res = true;

    for(Int string_index = 0; (string_index < len); ++string_index) {
        if(a[string_index] != b[string_index]) {
            res = false;
            break; // while
        }
    }

    return(res);
}

internal Void
eat_whitespace(Tokenizer *tokenizer)
{
    assert(tokenizer);

    for(;;) {
        if(is_whitespace(tokenizer->at[0])) { // Whitespace
            ++tokenizer->at;
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '/')) { // C++ comments.
            tokenizer->at += 2;
            while((tokenizer->at[0]) && (!is_end_of_line(tokenizer->at[0]))) {
                ++tokenizer->at;
            }
        } else if((tokenizer->at[0] == '/') && (tokenizer->at[1] == '*')) { // C comments.
            tokenizer->at += 2;
            while((tokenizer->at[0] != '\0') && !((tokenizer->at[0] == '*') && (tokenizer->at[1] == '/'))) {
                ++tokenizer->at;
            }

            if(tokenizer->at[0] == '*') {
                tokenizer->at += 2;
            }
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
                            if(level != 0) {
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

internal Bool
is_alphabetical(Char c)
{
    Bool res = (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));

    return(res);
}

internal Bool
is_num(Char c)
{
    Bool res = ((c >= '0') && (c <= '9'));

    return(res);
}

internal Void
parse_number(Tokenizer *tokenizer)
{
    assert(tokenizer);

    // TODO(Jonny): Implement.
}

internal Token get_token(Tokenizer *tokenizer); // Because C++...

#define eat_token(tokenizer) eat_tokens(tokenizer, 1);
internal Void
eat_tokens(Tokenizer *tokenizer, Int num_tokens_to_eat)
{
    assert(tokenizer);

    for(Int token_index = 0; (token_index < num_tokens_to_eat); ++token_index) {
        get_token(tokenizer);
    }
}

// TODO(Jonny): Parse var_args (...) as it's own Token.
// TODO(Jonny): Parse #if 0 blocks as whitespace. Also the #else of #if 1 blocks should also be whitespace.
internal Token
get_token(Tokenizer *tokenizer)
{
    assert(tokenizer);

    eat_whitespace(tokenizer);

    Token res = {};
    res.len = 1;
    res.e = tokenizer->at;
    Char c = tokenizer->at[0];
    ++tokenizer->at;

    switch(c) {
        case '\0': { res.type = TokenType_end_of_stream;  } break;

        case '(':  { res.type = TokenType_open_paren;     } break;
        case ')':  { res.type = TokenType_close_param;    } break;
        case ':':  { res.type = TokenType_colon;          } break;
        case ';':  { res.type = TokenType_semi_colon;     } break;
        case '*':  { res.type = TokenType_asterisk;       } break;
        case '[':  { res.type = TokenType_open_bracket;   } break;
        case ']':  { res.type = TokenType_close_bracket;  } break;
        case '{':  { res.type = TokenType_open_brace;     } break;
        case '}':  { res.type = TokenType_close_brace;    } break;
        case '=':  { res.type = TokenType_equals;         } break;
        case ',':  { res.type = TokenType_comma;          } break;
        case '~':  { res.type = TokenType_tilde;          } break;
        case '#':  { res.type = TokenType_hash;           } break;

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

            if(!var_args) {
                res.type = TokenType_period;
            }
        } break;

        case '"': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '"')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { // TODO(Jonny): Is this right??
                    ++tokenizer->at;
                }

                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '"') {
                ++tokenizer->at;
            }
        } break;

        case '\'': {
            res.e = tokenizer->at;
            while((tokenizer->at[0]) && (tokenizer->at[0] != '\'')) {
                if((tokenizer->at[0] == '\\') && (tokenizer->at[1])) { // TODO(Jonny): Is this right??
                    ++tokenizer->at;
                }

                ++tokenizer->at;
            }

            res.type = TokenType_string;
            res.len = safe_truncate_size_64(tokenizer->at - res.e);
            if(tokenizer->at[0] == '\'') {
                ++tokenizer->at;
            }
        } break;

        default: {
            if((is_alphabetical(c)) || (tokenizer->at[0] == '_')) {
                while((is_alphabetical(tokenizer->at[0])) || (is_num(tokenizer->at[0])) || (tokenizer->at[0] == '_')) {
                    ++tokenizer->at;
                }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_identifier;
            } else if(is_num(c)) {
                while(is_num(tokenizer->at[0])) {
                    ++tokenizer->at;
                }

                res.len = safe_truncate_size_64(tokenizer->at - res.e);
                res.type = TokenType_number;
            } else {
                res.type = TokenType_unknown;
            }
        } break;
    }

    return(res);
}

internal Token
peak_token(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Tokenizer cpy = *tokenizer;
    Token res = get_token(&cpy);

    return(res);
}

internal Bool
token_equals(Token token, Char *str)
{
    assert(str);

    Bool res = false;

    Char *at = str;
    for(Int str_index = 0; (str_index < token.len); ++str_index, ++at) {
        if((*at == '\0') == (*at == token.e[str_index])) {
            goto exit_func;
        }
    }

    res = (*at == 0);

exit_func:

    return(res);
}

struct ResultInt {
    Int e;
    Bool success;
};

internal ResultInt
char_to_int(Char C)
{
    ResultInt res = {};
    switch(C) {
        case '0': { res.e = 0; res.success = true; } break;
        case '1': { res.e = 1; res.success = true; } break;
        case '2': { res.e = 2; res.success = true; } break;
        case '3': { res.e = 3; res.success = true; } break;
        case '4': { res.e = 4; res.success = true; } break;
        case '5': { res.e = 5; res.success = true; } break;
        case '6': { res.e = 6; res.success = true; } break;
        case '7': { res.e = 7; res.success = true; } break;
        case '8': { res.e = 8; res.success = true; } break;
        case '9': { res.e = 9; res.success = true; } break;

        default: { assert(0); } break;
    }

    return(res);
}

internal ResultInt
string_to_int(String str)
{
    ResultInt res = {};

    for(Int str_index = 0; (str_index < str.len); ++str_index) {
        ResultInt temp_int = char_to_int(str.e[str_index]);
        if(!temp_int.success) {
            break; // for
        }

        res.e *= 10;
        res.e += temp_int.e;

        if(str_index == str.len - 1) {
            res.success = true;
        }
    }

    assert(res.success);
    return(res);
}

internal ResultInt
token_to_int(Token t)
{
    String str = token_to_string(t);
    ResultInt res = string_to_int(str);

    return(res);
}

internal ResultInt
string_to_int(Char *str)
{
    String string = {};
    string.e = str;
    string.len = string_length(str);
    ResultInt res = string_to_int(string);

    return(res);
}

struct Variable {
    String type;
    String name;
    Bool is_ptr;
    Int array_count; // This is 1 if it's not an array.
};

internal Variable
parse_member(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Variable res = {};
    res.array_count = 1;
    res.type = token_to_string(get_token(tokenizer));

    Bool parsing = true;
    while(parsing) {
        Token token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_asterisk: {
                res.is_ptr = true;
            } break;

            case TokenType_open_bracket: {
                Token size_token = get_token(tokenizer);
                if(size_token.type == TokenType_number) {
                    Char buffer[256] = {};
                    token_to_string(size_token, buffer, array_count(buffer));
                    ResultInt arr_coount = string_to_int(buffer);
                    if(arr_coount.success) {
                        res.array_count = arr_coount.e;
                    }
                }
            } break;

            case TokenType_identifier: {
                res.name = token_to_string(token);
            } break;

            case TokenType_semi_colon: case TokenType_end_of_stream: {
                parsing = false;
            } break;
        }
    }

    return(res);
}

internal Bool
require_token(Tokenizer *tokenizer, TokenType desired_type)
{
    assert(tokenizer);

    Token token = get_token(tokenizer);
    Bool res = (token.type == desired_type);

    return(res);
}

internal Bool
is_stupid_class_keyword(Token t)
{
    assert(t.type != TokenType_unknown);
    Bool result = false;

    Char *keywords[] = {"private", "public", "protected"};
    for(Int keyword_index = 0, num_keywords = array_count(keywords); (keyword_index < num_keywords); ++keyword_index) {
        if(string_compare(keywords[keyword_index], t.e, t.len)) {
            result = true;
        }
    }

    return(result);
}

struct FunctionData {
    String linkage;
    String ret_type;
    String name;
    Variable params[32];
    Int param_count;
};

struct StructData {
    String name;
    Int member_count;
    Variable *members;

    FunctionData *func_data;
    Int func_count;
};

internal Void
skip_to_matching_bracket(Tokenizer *tokenizer)
{
    assert(tokenizer);

    Int brace_count = 1;
    Token token = {};
    Bool should_loop = true;
    while(should_loop) {
        token = get_token(tokenizer);
        switch(token.type) {
            case TokenType_close_brace: {
                --brace_count;
                if(!brace_count) {
                    should_loop = false;
                }
            } break;

            case TokenType_open_brace: {
                ++brace_count;
            } break;
        }
    }
}

internal Variable
parse_variable(Tokenizer *tokenizer, TokenType end_token_type_1, TokenType end_token_type_2 = TokenType_unknown)
{
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
        if(token.type == TokenType_open_bracket) {
            token = get_token(tokenizer);
            ResultInt num = token_to_int(token);
            if(num.success) {
                res.array_count = num.e;
                eat_token(tokenizer); // Eat the second ']'.
            } else {
                // TODO(Jonny): Error case.
            }
        } else {
            // TODO(Jonny): Error case.
        }
    } else {
        res.array_count = 1;
    }

    return(res);
}

// TODO(Jonny): This needs some way to ignore member functions.
internal StructData
parse_struct(Tokenizer *tokenizer, Memory *memory)
{
    assert((tokenizer) && (memory));

    StructData res = {};

    Token name = {};
    name = get_token(tokenizer);
    if(name.len > 1) {
        res.name = token_to_string(name);

        Token inherited_from = {};
        Token peaked_token = peak_token(tokenizer);
        if(peaked_token.type == TokenType_colon) {
            eat_tokens(tokenizer, 2);
            inherited_from = get_token(tokenizer);
        }

        if(require_token(tokenizer, TokenType_open_brace)) {
            res.member_count = 0;
            Char *member_pos[256] = {};
            res.func_data = push_permanent_array(memory, FunctionData, 32);
            for(;;) {
                Token token = get_token(tokenizer);
                if((!is_stupid_class_keyword(token))) {
                    if((token.type != TokenType_colon) && (token.type != TokenType_tilde)) {
                        if(token.type == TokenType_close_brace) {
                            break; // for
                        } else if(token.type == TokenType_hash) {
                            while(tokenizer->at[0] != '\n') {
                                ++tokenizer->at;
                            }
                        } else {
                            Bool is_func = false, inline_func = false;

                            Tokenizer tokenizer_copy = *tokenizer;
                            Token temp = get_token(&tokenizer_copy);
                            while(temp.type != TokenType_semi_colon) {
                                if(temp.type == TokenType_open_paren) {
                                    is_func = true;
                                }

                                if(temp.type == TokenType_open_brace) {
                                    is_func = true;
                                    inline_func = true;
                                    break; // while
                                }

                                temp = get_token(&tokenizer_copy);
                            }

                            if(!is_func) {
                                member_pos[res.member_count++] = token.e;
                            } else {
                                if(inline_func) {
                                    skip_to_matching_bracket(&tokenizer_copy);
                                }

                                // Get member function name and return type.
                                Tokenizer second_copy = *tokenizer;
                                FunctionData fd = {};
                                //fd.linkage = ;
                                fd.ret_type = token_to_string(token);
                                fd.name = token_to_string(get_token(&second_copy));

                                eat_token(&second_copy);

                                // Parse the parameters.
                                Token next = {};
                                while(next.type != TokenType_close_param) {
                                    fd.params[fd.param_count++] = parse_variable(&second_copy, TokenType_comma, TokenType_close_param);

                                    next = peak_token(&second_copy);
                                    assert((next.type == TokenType_comma) || (next.type == TokenType_close_param));
                                    if(next.type == TokenType_comma) {
                                        eat_token(&second_copy);
                                    }
                                }

                                // Now store the function data.
                                res.func_data[res.func_count++] = fd;
                            }

                            *tokenizer = tokenizer_copy;
                        }
                    }
                }
            }

            res.members = push_permanent_array(memory, Variable, res.member_count);
            for(Int member_index = 0; (member_index < res.member_count); ++member_index) {
                Tokenizer fake_tokenizer = { member_pos[member_index] };
                res.members[member_index] = parse_member(&fake_tokenizer);
            }
        }
    }

    return(res);
}

internal Char *
get_serialize_struct_implementation(Char *def_struct_code, Memory *mem)
{
    assert((def_struct_code) && (mem));

    Int res_size = 10000;
    Char *res = cast(Char *)push_permanent_memory(mem, res_size);
    if(res) {
        format_string(res, res_size,
                      "/* Function to serialize a struct to a char array buffer. */\n"
                      "size_t\n"
                      "serialize_struct__(void *var, MemberDefinition members_of_Something[], int indent, size_t num_members, char *buffer, size_t buf_size, size_t bytes_written)\n"
                      "{\n"
                      "    char indent_buf[256];\n"
                      "    unsigned indent_index = 0, member_index = 0, arr_index = 0;\n"
                      "\n"
                      "    memset(indent_buf, 0, 256);\n"
                      "\n"
                      "    assert((var) && (members_of_Something) && (num_members > 0) && (buffer) && (buf_size > 0));\n"
                      "    memset(buffer + bytes_written, 0, buf_size - bytes_written);\n"
                      "    for(indent_index = 0; (indent_index < indent); ++indent_index) {\n"
                      "        indent_buf[indent_index] = ' ';\n"
                      "    }\n"
                      "\n"
                      "    for(member_index = 0; (member_index < num_members); ++member_index) {\n"
                      "        MemberDefinition *member = members_of_Something + member_index;\n"
                      "\n"
                      "         void *member_ptr = (char *)var + member->offset;\n"
                      "         switch(member->type) {\n"
                      "            case meta_type_float: {\n"
                      "                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {\n"
                      "                    float *value = (member->is_ptr) ? *(float **)member_ptr : (float *)member_ptr;\n"
                      "                    if(member->arr_size > 1) {\n"
                      "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s[%%d] : %%f\", indent_buf, member->name, arr_index, value[arr_index]);\n"
                      "                    } else {\n"
                      "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s : %%f\", indent_buf, member->name, value[arr_index]);\n"
                      "                    }\n"
                      "                }\n"
                      "            } break;\n"
                      "\n"
                      "            case meta_type_short: case meta_type_int: case meta_type_long: {\n"
                      "                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {\n"
                      "                    int *value = (member->is_ptr) ? *(int **)member_ptr : (int *)member_ptr;\n"
                      "                    if(member->arr_size > 1) {\n"
                      "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s[%%d] : %%d\", indent_buf, member->name, arr_index, value[arr_index]);\n"
                      "                    } else {\n"
                      "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sint %%s : %%d\", indent_buf, member->name, value[arr_index]);\n"
                      "                    }\n"
                      "                }\n"
                      "            } break;\n"
                      "\n"
                      "            case meta_type_char: {\n"
                      "                if(member->is_ptr) {\n"
                      "                    bytes_written += sprintf(buffer + bytes_written, \"\\n%%schar * %%s : %%s\", indent_buf, member->name, *(char **)member_ptr);\n"
                      "                } else {\n"
                      "                    bytes_written += sprintf(buffer + bytes_written, \"\\n%%schar %%s : %%c\", indent_buf, member->name, *(char *)member_ptr);\n"
                      "                }\n"
                      "            } break;\n"
                      "\n"
                      "            case meta_type_double: {\n"
                      "                for(arr_index = 0; (arr_index < member->arr_size); ++arr_index) {\n"
                      "                    double *value = (member->is_ptr) ? *(double **)member_ptr : (double *)member_ptr;\n"
                      "                    if(member->arr_size > 1) {\n"
                      "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s[%%d] : %%f\", indent_buf, member->name, arr_index, value[arr_index]);\n"
                      "                    } else {\n"
                      "                        bytes_written += sprintf((char *)buffer + bytes_written, \"\\n%%sfloat %%s : %%f\", indent_buf, member->name, value[arr_index]);\n"
                      "                    }\n"
                      "                }\n"
                      "            } break;\n"
                      "\n"
                      "            default: {\n"
                      "                %s\n"
                      "            } break; /* default */\n"
                      "        }\n"
                      "    }\n"
                      "\n"
                      "    return(bytes_written);\n"
                      "}\0",
                      def_struct_code
                     );
    }

    return(res);
}

struct EnumData {
    String name;
    String type;
    Bool is_struct;
};

internal EnumData
add_token_to_enum(Token name, Token type, Bool is_enum_struct)
{
    assert(name.type == TokenType_identifier);
    assert((type.type == TokenType_identifier) || (type.type == TokenType_unknown));

    EnumData res = {};
    res.is_struct = is_enum_struct;
    res.name = token_to_string(name);
    if(type.type == TokenType_identifier) {
        res.type = token_to_string(type);
    }

    return(res);
}

internal Bool
str_compare(String a, String b)
{
    Bool res = false;

    if(a.len == b.len) {
        res = true;

        for(Int str_index = 0; (str_index < a.len); ++str_index) {
            if(a.e[str_index] != b.e[str_index]) {
                res = false;
                break; // for
            }
        }
    }

    return(res);
}

internal Bool
is_meta_type_already_in_array(String *array, Int len, String test)
{
    Bool res = false;

    for(Int arr_index = 0; (arr_index < len); ++arr_index) {
        if(str_compare(array[arr_index], test)) {
            res = true;
            break; // for
        }
    }

    return(res);
}

internal Int
set_primitive_type(String *array)
{
    assert(array);

    Int res = 0;

    array[res].e = "char";
    array[res].len = string_length(array[res].e);
    ++res;

    array[res].e = "short";
    array[res].len = string_length(array[res].e);
    ++res;

    array[res].e = "int";
    array[res].len = string_length(array[res].e);
    ++res;

    array[res].e = "long";
    array[res].len = string_length(array[res].e);
    ++res;

    array[res].e = "float";
    array[res].len = string_length(array[res].e);
    ++res;

    array[res].e = "double";
    array[res].len = string_length(array[res].e);
    ++res;

    return(res);
}

#define copy_literal_to_char_buffer(buf, index, lit) copy_literal_to_char_buffer_(buf, index, lit, sizeof(lit) - 1)
internal Int
copy_literal_to_char_buffer_(Char *buf, Int index, Char *literal, Int literal_len)
{
    assert(buf);
    assert((literal) && (literal_len));

    buf += index;

    for(Int str_index = 0; (str_index < literal_len); ++str_index) {
        buf[str_index] = literal[str_index];
    }

    Int res = index + literal_len;
    return(res);
}

internal Char *
get_default_struct_string(void)
{
    Char *res = "                    case meta_type_%S: {\n"
                "                        if(member->is_ptr) {\n"
                "                            bytes_written += serialize_struct_(**(char **)member_ptr, %S, indent + 4, buffer, buf_size - bytes_written, bytes_written);\n"
                "                        } else {\n"
                "                            bytes_written += serialize_struct_(*(char *)member_ptr, %S, indent + 4, buffer, buf_size - bytes_written, bytes_written);\n"
                "                        }\n"
                "                    } break;\n ";

    return(res);
}


internal void
skip_to_end_of_line(Tokenizer *tokenizer)
{
    while(*tokenizer->at != '\n') {
        ++tokenizer->at;
    }
}

struct ParseFunctionResult {
    FunctionData func_data;
    Bool success;
};

internal ParseFunctionResult
attempt_to_parse_function(Tokenizer *tokenizer, Token token)
{
    assert((tokenizer) && (token.type));

    ParseFunctionResult res = {};

    // Try to parse as a function.
    Tokenizer copy_tokenizer = *tokenizer;
    Token linkage = {};
    Token return_type = {};
    if((token_equals(token, "static")) || (token_equals(token, "inline")) || (token_equals(token, "internal"))) {
        linkage = token;
        return_type = get_token(&copy_tokenizer);
    } else {
        return_type = token;
    }

    if(return_type.type == TokenType_identifier) {
        if((!token_equals(return_type, "if")) && (!token_equals(return_type, "do")) && (!token_equals(return_type, "while")) && (!token_equals(return_type, "switch"))) { // TODO(Jonny): Extra check...
            Token name = get_token(&copy_tokenizer);
            if(name.type == TokenType_identifier) {
                // Don't forward declare main.
                if((!token_equals(name, "main")) && (!token_equals(name, "WinMain")) && (!token_equals(name, "_mainCRTStartup")) && (!token_equals(name, "_WinMainCRTStartup")) && (!token_equals(name, "__DllMainCRTStartup"))) {
                    if((linkage.type == TokenType_identifier) || (linkage.type == TokenType_unknown)) {
                        Token should_be_open_brace = get_token(&copy_tokenizer);
                        if(should_be_open_brace.type == TokenType_open_paren) {
                            res.success = true;

                            *tokenizer = copy_tokenizer;

                            if(linkage.type == TokenType_identifier) {
                                res.func_data.linkage = token_to_string(linkage);
                            }

                            res.func_data.ret_type = token_to_string(return_type);
                            res.func_data.name = token_to_string(name);

                            // Set the array size to 1 for all the variables...
                            for(Int param_index = 0; (param_index < array_count(res.func_data.params)); ++param_index) {
                                res.func_data.params[param_index].array_count = 1;
                            }

                            Bool parsing = true;
                            Variable *var = res.func_data.params + res.func_data.param_count;

                            // If there aren't any parameters then just skip them.
                            {
                                Tokenizer copy = *tokenizer;
                                Token token = get_token(&copy);
                                if(token_equals(token, "void")) {
                                    Token next = get_token(&copy);
                                    if(next.type == TokenType_close_param) {
                                        parsing = false;
                                    }
                                }
                            }

                            // Parse the parameters.
                            while(parsing) {
                                Token token = get_token(tokenizer);
                                switch(token.type) {
                                    case TokenType_asterisk: {
                                        var->is_ptr = true;
                                    } break;

                                    case TokenType_open_bracket: {
                                        Token SizeToken = get_token(tokenizer);
                                        if(SizeToken.type == TokenType_number) {
                                            Char buffer[256] = {};
                                            token_to_string(SizeToken, buffer, array_count(buffer));
                                            ResultInt arr_count = string_to_int(buffer);
                                            if(arr_count.success) {
                                                var->array_count = arr_count.e;
                                            }
                                        }
                                    } break;

                                    case TokenType_identifier: {
                                        if(var->type.len == 0) {
                                            var->type = token_to_string(token);
                                        } else {
                                            var->name = token_to_string(token);
                                            ++res.func_data.param_count;
                                        }
                                    } break;

                                    case TokenType_comma: {
                                        ++var;
                                    } break;

                                    case TokenType_end_of_stream: case TokenType_open_brace: {
                                        parsing = false; // TODO(Jonny): Something baaaad happened...
                                    } break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return(res);
}

internal StuffToWrite
write_data(Memory *memory, StructData *struct_data, Int struct_count, FunctionData *func_data, Int func_count,
           EnumData *enum_data, Int enum_count, String *union_data, Int union_count)
{
    assert((memory) && (struct_data) && (func_data) && (enum_data) && (union_data));

    //
    // Source file.
    //
    StuffToWrite res = {};

    OutputBuffer source_output = create_output_buffer(256 * 256, memory); // TODO(Jonny): Random size...

    write_to_output_buffer(&source_output, "#if !defined(GENERATED_CPP)\n\n#include \"generated.h\"\n#include <string.h>\n#include <assert.h>\n\n");

    // Recreated Structs.
    write_to_output_buffer(&source_output, "/* Recreated structs. */\n");
    for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
        StructData *sd = struct_data + struct_index;
        write_to_output_buffer(&source_output, "typedef struct %S {\n", sd->name.len, sd->name.e);
        for(Int member_index = 0; (member_index < sd->member_count); ++member_index) {
            Variable *md = sd->members + member_index;
            Char *arr = cast(Char *)((md->array_count > 1) ? "[%u]" : "");
            Char arr_buffer[256] = {};
            if(md->array_count > 1) {
                format_string(arr_buffer, 256, arr, md->array_count);
            }

            write_to_output_buffer(&source_output, "    %S %s%S%s;\n",
                                   md->type.len, md->type.e,
                                   (md->is_ptr) ? "*" : "",
                                   md->name.len, md->name.e,
                                   (md->array_count > 1) ? arr_buffer : arr);

        }

        write_to_output_buffer(&source_output, "} %S;\n\n", sd->name.len, sd->name.e);
    }

    // Struct Meta Data
    write_to_output_buffer(&source_output, "\n/* Struct meta data. */\n\n");
    for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
        StructData *sd = struct_data + struct_index;
        write_to_output_buffer(&source_output, "/* Meta data for: %S. */\n", sd->name.len, sd->name.e);
        write_to_output_buffer(&source_output, "MemberDefinition members_of_%S[] = {\n", sd->name.len, sd->name.e);
        for(Int member_index = 0; (member_index < sd->member_count); ++member_index) {
            Variable *md = sd->members + member_index;
            write_to_output_buffer(&source_output, "    {meta_type_%S, \"%S\", (size_t)&((%S *)0)->%S, %d, %d},\n",
                                   md->type.len, md->type.e,
                                   md->name.len, md->name.e,
                                   sd->name.len, sd->name.e,
                                   md->name.len, md->name.e,
                                   md->is_ptr,
                                   md->array_count);
        }

        write_to_output_buffer(&source_output, "};\n");
    }

    // Function meta data.
    write_to_output_buffer(&source_output, "\n\n/* Function meta data. */\n");
    for(Int func_index = 0; (func_index < func_count); ++func_index) {
        FunctionData *fd = func_data + func_index;
        write_to_output_buffer(&source_output, "/* Meta data for: %S. */\nFunctionMetaData function_data_%S = {\n",
                               fd->name.len, fd->name.e, fd->name.len, fd->name.e);

        Char buf[256] = {};

        if(fd->linkage.len > 0) {
            Char *meta_data = "    \"%S\",\n"
                              "    \"%S\",\n"
                              "    \"%S\",\n"
                              "    %u,\n";
            format_string(buf, array_count(buf), meta_data,
                          fd->linkage.len, fd->linkage.e,
                          fd->ret_type.len, fd->ret_type.e,
                          fd->name.len, fd->name.e,
                          fd->param_count);
        } else {
            Char *meta_data = "    0,\n"
                              "    \"%S\",\n"
                              "    \"%S\",\n"
                              "    %u,\n";
            format_string(buf, array_count(buf), meta_data,
                          fd->ret_type.len, fd->ret_type.e,
                          fd->name.len, fd->name.e,
                          fd->param_count);
        }

        write_to_output_buffer(&source_output, buf);

        write_to_output_buffer(&source_output, "    {\n");
        for(Int param_index = 0; (param_index < fd->param_count); ++param_index) {
            Variable *param = fd->params + param_index;
            write_to_output_buffer(&source_output, "        {\"%S\", \"%S\"}", param->type.len, param->type.e, param->name.len, param->name.e);
            if(param_index != fd->param_count - 1) {
                write_to_output_buffer(&source_output, ",\n");
            }
        }

        write_to_output_buffer(&source_output, "\n    }\n};\n\n");
    }

    // Method meta data.
    for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
        StructData *sd = struct_data + struct_index;

        if(sd->func_count) {
            write_to_output_buffer(&source_output, "// %S's methods.", sd->name.len, sd->name.e);

            for(Int method_index = 0; (method_index < sd->func_count); ++method_index) {
                FunctionData *md = sd->func_data + method_index;

                write_to_output_buffer(&source_output, "\nFunctionMetaData method_data_%S%S = {\n",
                                       sd->name.len, sd->name.e,
                                       md->name.len, md->name.e);
                Char buf[1024] = {};
                if(md->linkage.len) {
                    Char *meta_data = "    \"%S\",\n"
                                      "    \"%S\",\n"
                                      "    \"%S\",\n"
                                      "    %u,\n";
                    format_string(buf, array_count(buf), meta_data,
                                  md->linkage.len, md->linkage.e,
                                  md->ret_type.len, md->ret_type.e,
                                  md->name.len, md->name.e,
                                  md->param_count);
                } else {
                    Char *meta_data = "    0,\n"
                                      "    \"%S\",\n"
                                      "    \"%S\",\n"
                                      "    %u,\n";
                    format_string(buf, array_count(buf), meta_data,
                                  md->ret_type.len, md->ret_type.e,
                                  md->name.len, md->name.e,
                                  md->param_count);
                }

                write_to_output_buffer(&source_output, buf);

                write_to_output_buffer(&source_output, "    {\n");
                for(Int param_index = 0; (param_index < md->param_count); ++param_index) {
                    Variable *param = md->params + param_index;

                    write_to_output_buffer(&source_output, "        {\"%S\", \"%S\"}", param->type.len, param->type.e, param->name.len, param->name.e);
                    if(param_index != md->param_count - 1) {
                        write_to_output_buffer(&source_output, ",\n");
                    }
                }

                write_to_output_buffer(&source_output, "\n    }\n};\n\n");
            }
        }
    }

    // Serialize func stuff.
    write_to_output_buffer(&source_output, "\n\n");

    Int def_struct_code_size = 256 * 256;
    Char *def_struct_code = cast(Char *)push_permanent_memory(memory, def_struct_code_size);
    if(def_struct_code) {
        Int index = 0;
        index = copy_literal_to_char_buffer(def_struct_code, index, "switch(member->type) {\n");
        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
            StructData *sd = struct_data + struct_index;
            Char *DefaultStructString = get_default_struct_string();
            index += format_string(def_struct_code + index, def_struct_code_size, DefaultStructString,
                                   sd->name.len, sd->name.e, sd->name.len, sd->name.e, sd->name.len, sd->name.e);

        }

        index = copy_literal_to_char_buffer(def_struct_code, index, "                }");
    }

    Char *serialize_struct_implementation = get_serialize_struct_implementation(def_struct_code, memory);
    write_to_output_buffer(&source_output, "%s", serialize_struct_implementation);

    // Serialize func.
    Char *serialize_func_implementation = "\n"
                                          "\n"
                                          "/* Function to serialize a function into a char buffer. */\n"
                                          "size_t\n"
                                          "serialize_function_(FunctionMetaData func, char *buf, size_t buf_size)\n"
                                          "{\n"
                                          "    size_t bytes_written = 0;\n"
                                          "    int param_index = 0;\n"
                                          "\n"
                                          "    bytes_written = sprintf(buf, \"Function %%s\\n    Linkage: %%s\\n    Return Type: %%s\\n    Param Count: %%u\\n\",\n"
                                          "                            func.name, (func.linkage) ? func.linkage : \"normal\", func.ret_type, func.param_count);\n"
                                          "\n"
                                          "    for(param_index = 0; (param_index < func.param_count); ++param_index) {\n"
                                          "        Variable *param = func.params + param_index;\n"
                                          ""
                                          "        bytes_written += sprintf(buf + bytes_written, \"        Param %%u : %%s %%s\\n\", param_index + 1, param->ret_type, param->name);\n"
                                          "    }\n"
                                          "\n"
                                          "    assert(bytes_written <  buf_size);\n"
                                          "    return(bytes_written);\n"
                                          "}\n";
    write_to_output_buffer(&source_output, serialize_func_implementation);

    // # Guard stuff
    write_to_output_buffer(&source_output, "\n\n#define GENERATED_CPP\n");
    write_to_output_buffer(&source_output, "#endif /* #if !defined(GENERATED_CPP) */\n");

    res.source_size = source_output.index;
    res.source_data = source_output.buffer;

    //
    // Header file.
    //
    OutputBuffer header_output = create_output_buffer(256 * 256, memory);

    write_to_output_buffer(&header_output, "#if !defined(GENERATED_H)\n\n#include \"static_generated.h\"\n#include <stdio.h>\n\n");

    // Write out meta types
    TempMemory types_memory = push_temp_arr(memory, String, 256);
    {
        String *types = cast(String *)types_memory.block;
        Int type_count = set_primitive_type(types);
        for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
            StructData *sd = struct_data + struct_index;

            if(!is_meta_type_already_in_array(types, type_count, sd->name)) {
                types[type_count++] = sd->name;
            }

            for(Int member_index = 0; (member_index < sd->member_count); ++member_index) {
                Variable *md = sd->members + member_index;

                if(!is_meta_type_already_in_array(types, type_count, md->type)) {
                    types[type_count++] = md->type;
                }
            }
        }

        write_to_output_buffer(&header_output, "/* Enum with field for every type detected. */\n");
        write_to_output_buffer(&header_output, "typedef enum MetaType {\n");
        for(Int type_index = 0; (type_index < type_count); ++type_index) {
            String *type = types + type_index;
            write_to_output_buffer(&header_output, "    meta_type_%S,\n", type->len, type->e);
        }
        write_to_output_buffer(&header_output, "} MetaType;\n\n");
    }
    pop_temp_memory(&types_memory);

    // Struct meta data.
    write_to_output_buffer(&header_output, "/* Struct meta data. */\n\n");
    for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
        StructData *sd = &struct_data[struct_index];
        write_to_output_buffer(&header_output, "/* Meta Data for: %S */\n", sd->name.len, sd->name.e);
        write_to_output_buffer(&header_output, "extern MemberDefinition members_of_%S[];\n", sd->name.len, sd->name.e);
        write_to_output_buffer(&header_output, "static size_t const num_members_for_%S = %u;\n\n", sd->name.len, sd->name.e, sd->member_count);
    }

    // Function meta data.
    write_to_output_buffer(&header_output, "\n/* Function meta data. */\n\n");

    for(Int func_index = 0; (func_index < func_count); ++func_index) {
        FunctionData *fd = func_data + func_index;

        write_to_output_buffer(&header_output, "/* Meta Data for: %S */\n", fd->name.len, fd->name.e);

        Char buf[256] = {};
        if(fd->linkage.len > 0) {
            Char *meta_data = "extern FunctionMetaData function_data_%S;\n";
            format_string(buf, array_count(buf), meta_data,
                          fd->name.len, fd->name.e);
        } else {
            Char *meta_data = "extern FunctionMetaData function_data_%S;\n";
            format_string(buf, array_count(buf), meta_data,
                          fd->name.len, fd->name.e);
        }

        write_to_output_buffer(&header_output, buf);
    }

    for(Int struct_index = 0; (struct_index < struct_count); ++struct_index) {
        StructData *sd = struct_data + struct_index;

        if(sd->func_count) {
            write_to_output_buffer(&header_output, "\n// %S's methods.\n", sd->name.len, sd->name.e);
            for(Int method_index = 0; (method_index < sd->func_count); ++method_index) {
                FunctionData *md = sd->func_data + method_index;

                Char buf[256] = {};
                if(md->linkage.len) {
                    // TODO(Jonny): Implement.
                } else {
                    Char *meta_data = "extern FunctionMetaData method_data_%S%S;\n";
                    format_string(buf, array_count(buf), meta_data,
                                  sd->name.len, sd->name.e,
                                  md->name.len, md->name.e);
                }

                write_to_output_buffer(&header_output, buf);
            }
        }
    }

    // # Guard macro.
    write_to_output_buffer(&header_output, "\n\n#define GENERATED_H\n#endif /* !defined(GENERATED_H) */\n");

    res.header_size = header_output.index;
    res.header_data = header_output.buffer;

    return(res);
}

StuffToWrite
start_parsing(AllFiles all_files, Memory *memory)
{
    assert(memory);

    EnumData *enum_data = push_permanent_array(memory, EnumData, 256);
    Int enum_count = 0;

    StructData *struct_data = push_permanent_array(memory, StructData, 256);
    Int struct_count = 0;

    String *union_data = push_permanent_array(memory, String,  256);
    Int union_count = 0;

    FunctionData *func_data = push_permanent_array(memory, FunctionData, 256);
    Int func_count = 0;

    for(Int file_index = 0; (file_index < all_files.count); ++file_index) {
        Char *file = all_files.file[file_index];

        if(file) {
            Tokenizer tokenizer = { file };

            Bool parsing = true;
            while(parsing) {
                Token token = get_token(&tokenizer);
                switch(token.type) {
                    case TokenType_end_of_stream: {
                        parsing = false;
                    } break;

                    case TokenType_hash: {
                        skip_to_end_of_line(&tokenizer);
                    }

                    case TokenType_identifier: {
                        if((token_equals(token, "struct")) || (token_equals(token, "class"))) { // TODO(Jonny): Support typedef sturcts.
                            struct_data[struct_count++] = parse_struct(&tokenizer, memory); // TODO(Jonny): This fails at a struct declared within a struct/union.

                        } else if((token_equals(token, "union"))) {
                            Token name = get_token(&tokenizer);
                            union_data[union_count++] = token_to_string(name);

                        } else if((token_equals(token, "enum"))) {
                            Token name = get_token(&tokenizer);
                            Bool is_enum_struct = false;
                            if((token_equals(name, "class")) || (token_equals(name, "struct"))) {
                                is_enum_struct = true;
                                name = get_token(&tokenizer);
                            }

                            if(name.type == TokenType_identifier) {
                                // If the enum has an underlying type, get it.
                                Token underlying_type = {};
                                Token next = get_token(&tokenizer);
                                if(next.type == TokenType_colon) {
                                    underlying_type = get_token(&tokenizer);
                                    next = get_token(&tokenizer);
                                }

                                if(next.type == TokenType_open_brace) {
                                    enum_data[enum_count++] = add_token_to_enum(name, underlying_type, is_enum_struct);
                                }
                            }
                        } else {
                            ParseFunctionResult pfr = attempt_to_parse_function(&tokenizer, token);
                            if(pfr.success) {
                                func_data[func_count++] = pfr.func_data;
                            }
                        }
                    } break;
                }
            }
        }
    }

    StuffToWrite res = write_data(memory, struct_data, struct_count, func_data, func_count, enum_data, enum_count,
                                  union_data, union_count);


    return(res);
}
