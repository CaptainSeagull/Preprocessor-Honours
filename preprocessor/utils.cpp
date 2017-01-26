/*===================================================================================================
  File:                    lexer.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#define MEM_ROOT_FILE
#include "utils.h"

//
// Error stuff.
//
static Error global_errors[32];
static Int global_error_count = 0;

Char *ErrorTypeToString(ErrorType e) {
    Char *res = 0;

#define ERROR_TYPE_TO_STRING(err) err: { res = #err; } break

    switch(e) {
        case ERROR_TYPE_TO_STRING(ErrorType_ran_out_of_memory);
        case ERROR_TYPE_TO_STRING(ErrorType_assert_failed);
        case ERROR_TYPE_TO_STRING(ErrorType_no_parameters);
        case ERROR_TYPE_TO_STRING(ErrorType_cannot_find_file);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_write_to_disk);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_load_file);
        case ERROR_TYPE_TO_STRING(ErrorType_no_files_pass_in);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_find_mallocd_ptr);
        case ERROR_TYPE_TO_STRING(ErrorType_memory_not_freed);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_find_struct);
        case ERROR_TYPE_TO_STRING(ErrorType_unknown_token_found);
        case ERROR_TYPE_TO_STRING(ErrorType_failed_to_parse_enum);
        case ERROR_TYPE_TO_STRING(ErrorType_failed_parsing_variable);
        case ERROR_TYPE_TO_STRING(ErrorType_failed_to_find_size_of_array);
        case ERROR_TYPE_TO_STRING(ErrorType_could_not_detect_struct_name);
    }

    if(res) {
        Int offset = string_length("ErrorType_");
        res += offset;
    }

#undef ERROR_TYPE_TO_STRING

    return(res);
}

Void push_error_(ErrorType type, Char *guid) {
    if(global_error_count + 1 < array_count(global_errors)) {
        Error *e = global_errors + global_error_count++;

        e->type = type;
        e->guid = guid;
    }
}

Bool print_errors(void) {
    Bool res = false;

    if(global_error_count) {
        res = true;

        // TODO(Jonny): Write errors to disk.
        fprintf(stderr, "\nPreprocessor errors:\n");
        for(Int i = 0; (i < global_error_count); ++i) {
            fprintf(stderr, "%s %s\n\n",
                    global_errors[i].guid, ErrorTypeToString(global_errors[i].type));
        }
        fprintf(stderr, "Preprocessor finished with %d error(s).\n\n\n", global_error_count);

        //if(system_check_for_debugger()) { assert(0); }
    }

    return(res);
}

//
// Scratch memory.
//
// A quick-to-access temp region of memory. Should be frequently cleared.
static Int scratch_memory_index = 0;
static Void *global_scratch_memory = 0;
Void *push_scratch_memory(Int size/*= scratch_memory_size*/) {
    if(!global_scratch_memory) {
        global_scratch_memory = malloc(scratch_memory_size + 1);
        memset(global_scratch_memory, 0, scratch_memory_size + 1);
    }

    Void *res = 0;
    if(global_scratch_memory) {
        assert(scratch_memory_size + 1 > scratch_memory_index + size);
        res = cast(Byte *)global_scratch_memory + scratch_memory_index;
        scratch_memory_index += size;
    }

    return(res);
}

Void clear_scratch_memory(void) {
    if(global_scratch_memory) {
        memset(global_scratch_memory, 0, scratch_memory_index);
        scratch_memory_index = 0;
    }
}

Void free_scratch_memory() {
    if(global_scratch_memory) {
        free(global_scratch_memory);
    }
}

//
// Strings.
//
String create_string(Char *str, Int len/*= 0*/) {
    String res = {str, (len) ? len : string_length(str)};

    return(res);
}

Int string_length(Char *str) {
    Int res = 0;
    while(*str++) { ++res; }

    return(res);
}

Bool string_concat(Char *dest, Int len, Char *a, Int a_len, Char *b, Int b_len) {
    Bool res = false;

    if(len > a_len + b_len) {
        for(Int i = 0; (i < a_len); ++i) { *dest++ = *a++; }
        for(Int i = 0; (i < b_len); ++i) { *dest++ = *b++; }

        res = true;
    }

    return(res);
}

Bool string_compare(Char *a, Char *b, Int len) {
    for(Int i = 0; (i < len); ++i, ++a, ++b) { if(*a != *b) { return(false); } }

    return(true);
}

Bool string_compare(Char *a, Char *b) {
    for(;; ++a, ++b) {
        if((*a == 0) && (*b == 0)) { return(true);  }
        else if(*a != *b)          { return(false); }
    }
}

Bool string_compare(String a, String b) {
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

Bool string_compare_array(String *a, String *b, Int len) {
    Bool res = true;
    for(Int i = 0; (i < len); ++i) {
        if(!string_compare(a[i], b[i])) {
            res = false;
            break; // for
        }
    }

    return(res);
}

//
// Stuff
//
ResultInt char_to_int(Char c) {
    ResultInt res = {};
    switch(c) {
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
    }

    return(res);
}

ResultInt string_to_int(String str) {
    ResultInt res = {};

    for(Int i = 0; (i < str.len); ++i) {
        ResultInt temp_int = char_to_int(str.e[i]);
        if(!temp_int.success) { break; } // for

        res.e *= 10;
        res.e += temp_int.e;

        if(i == str.len - 1) { res.success = true; }
    }

    return(res);
}

ResultInt string_to_int(Char *str) {
    String string;
    string.e = str;
    string.len = string_length(str);
    ResultInt res = string_to_int(string);

    return(res);
}

ResultInt calculator_string_to_int(Char *str) {
    ResultInt res = {};

    /* TODO(Jonny);
        - Make sure each element in the string is either a number or a operator.
        - Do the calculator in order (multiply, divide, add, subtract).
    */
    String *arr = alloc_arr(String, 256); // TODO(Jonny): Random size.
    if(arr) {
        Char *at = str;
        arr[0].e = at;
        Int cnt = 0;
        for(; (*at); ++at, ++arr[cnt].len) {
            if(*at == ' ') {
                ++at;
                arr[++cnt].e = at;
            }
        }
        ++cnt;

        Int *nums = alloc_arr(Int, cnt);
        Char *ops = alloc_arr(Char, cnt);
        if((nums) && (ops)) {
            for(Int i = 0, j = 0; (j < cnt); ++i, j += 2) {
                ResultInt r = string_to_int(arr[j]);
                if(r.success) { nums[i] = r.e; }
                else          { goto clean_up; }
            }

            for(Int i = 0, j = 1; (j < cnt); ++i, j += 2) {
                assert(arr[j].len == 1);
                ops[i] = *arr[j].e;
            }

            // TODO(Jonny): At this point, I have all the numbers and ops in seperate arrays.

clean_up:;
            free(ops);
            free(nums);
        }

        free(arr);
    }

    return(res);
}

Uint32 safe_truncate_size_64(Uint64 v) {
    assert(v <= 0xFFFFFFFF);
    Uint32 res = cast(Uint32)v;

    return(res);
}

Variable create_variable(Char *type, Char *name, Bool is_ptr/*= false*/, Int array_count/*= 1*/) {
    Variable res;
    res.type = create_string(type);
    res.name = create_string(name);
    res.is_ptr = is_ptr;
    res.array_count = array_count;

    return(res);
}

Bool compare_variable(Variable a, Variable b) {
    Bool res = true;

    if(!string_compare(a.type, b.type))      { res = false; }
    else if(!string_compare(a.name, b.name)) { res = false; }
    else if(a.is_ptr != b.is_ptr)            { res = false; }
    else if(a.array_count != b.array_count)  { res = false; }

    return(res);
}

Bool compare_variable_array(Variable *a, Variable *b, Int count) {
    for(Int i = 0; (i < count); ++i) {
        if(!compare_variable(a[i], b[i])) { return(false); }
    }

    return(true);
}
