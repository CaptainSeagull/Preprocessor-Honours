/*===================================================================================================
  File:                    platform.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

// TODO(Jonny):
// Generate metadata for enums so they can be converted to strings.
// Rewrite the union parser. I'm not sure if metadata for a union could really be generated, but possibly?
// Build without crt and only link to kernel32.
// Convert all the Char * string stuff to use the string struct.
// I'll need some way to track overloaded functions, because this'll flop right now with them...
// Make a slots/signal system.
// Make a "lose" keyword. The use-case for this is write_to_output_buffer in preprocessor.cpp.

#include <stdarg.h>
#include <stdint.h>
#include <string.h>

typedef uint64_t Uint64;
typedef uint32_t Uint32;
typedef uint16_t Uint16;
typedef uint8_t Uint8;

typedef int64_t Int64;
typedef int32_t Int32;
typedef int16_t Int16;
typedef int8_t Int8;

typedef bool Bool;
typedef void Void;
typedef char Char;

typedef Int32 Int; // Int guaranteed to be 32-bits.
typedef Uint32 Uint;

typedef Uint8 Byte;
typedef intptr_t PtrSize;

typedef float Float;
typedef double Float64;

#define internal static
#define persist static
#define global static

#define cast(type) (type)

#if INTERNAL
    #define assert(Expression) do { persist Bool Ignore = false; if(!Ignore) { if(!(Expression)) { *cast(int volatile *)0 = 0; } } } while(0)
#else
    #define assert(Expression) { /*Empty*/ }
#endif

#define array_count(arr) (sizeof(arr) / (sizeof((arr)[0])))

internal Uint32
safe_truncate_size_64(Uint64 value)
{
    assert(value <= 0xFFFFFFFF);
    Uint32 res = cast(Uint32)value;

    return(res);
}

//
// Memory stuff.
//
internal Void
copy_memory_block(Void *dest, Void *source, PtrSize size)
{
    assert((dest) && (source) && (size));

    Byte *dest8 = cast(Byte *)dest, *source8 = cast(Byte *)source;

    while(size-- > 0) {
        *dest8++ = *source8++;
    }
}

internal Void
zero_memory_block(Void *dest, PtrSize size)
{
    assert((dest) && (size));

    Byte *dest8 = cast(Byte *)dest;

    while(size-- > 0) {
        *dest8++ = 0;
    }
}

struct Memory {
    Void *file_memory;
    PtrSize file_index;
    PtrSize file_size;

    Void *permanent_memory;
    PtrSize permanent_index;
    PtrSize permanent_size;

    Void *temp_memory;
    PtrSize temp_index;
    PtrSize temp_size;
};

internal Memory
create_memory(Void *all_memory, PtrSize file_size, PtrSize permanent_size, PtrSize temp_size)
{
    assert((all_memory) && (file_size) && (permanent_size) && (temp_size));

    zero_memory_block(all_memory, file_size + permanent_size + temp_size);

    Memory res = {};
    res.file_memory = all_memory;
    res.file_size = file_size;

    res.permanent_memory = cast(Char *)all_memory + file_size;
    res.permanent_size = permanent_size;

    res.temp_memory = cast(Char *)all_memory + file_size + permanent_size;
    res.temp_size = temp_size;

    return(res);
}

global Int default_memory_alignment = 4;

internal Int
get_alignment_offset(Void *memory, PtrSize index, Int desired_alignment = default_memory_alignment)
{
    assert(memory);

    Int res = 0;

    PtrSize result_pointer = cast(PtrSize)(cast(Char *)memory + index);
    Int alignment_mask = desired_alignment - 1;
    if(result_pointer & alignment_mask) {
        res = desired_alignment - (result_pointer & alignment_mask);
    }

    return(res);
}

internal Char *
push_file_memory(Memory *memory, Int size, Int alignment = default_memory_alignment)
{
    assert((memory) && (size));

    Int alignment_offset = get_alignment_offset(memory->file_memory, memory->file_index, alignment);
    assert(memory->file_index + alignment_offset + size <= memory->file_size);

    Char *res = cast(Char *)memory->file_memory + (memory->file_index + alignment_offset);

    memory->file_index += size + alignment_offset;

    return(res);
}

#define push_permanent_struct(memory, type, ...) cast(type *)push_permanent_memory(memory, sizeof(type), ##__VA_ARGS__)
#define push_permanent_array(memory, type, len, ...) cast(type *)push_permanent_memory(memory, sizeof(type) * len, ##__VA_ARGS__)
internal Void *
push_permanent_memory(Memory *memory, Int size, Int alignment = default_memory_alignment)
{
    assert((memory) && (size));

    Int alignment_offset = get_alignment_offset(memory->permanent_memory, memory->permanent_index, alignment);
    assert(memory->permanent_index + alignment_offset + size <= memory->permanent_size);

    Void *res = cast(Char *)memory->permanent_memory + (memory->permanent_index + alignment_offset);

    memory->permanent_index += size + alignment_offset;

    return(res);
}

struct TempMemory {
    Memory *full_memory_block;
    Char *block;
    Int size;
    Int used;
    Int alignment_offset;
};

// Temp memory.
#define push_temp_struct(memory, Type, ...) push_temp_memory(memory, sizeof(Type), ##__VA_ARGS__)
#define push_temp_arr(memory, Type, len, ...) push_temp_memory(memory, sizeof(Type) * len, ##__VA_ARGS__)
internal TempMemory
push_temp_memory(Memory *memory, Int size, Int alignment = default_memory_alignment)
{
    assert((memory) && (size));

    Int alignment_offset = get_alignment_offset(memory->temp_memory, memory->temp_index, alignment);
    assert(memory->temp_index + alignment_offset + size <= memory->temp_size);

    TempMemory res = {};
    res.full_memory_block = memory;
    res.alignment_offset = alignment_offset;
    res.block = cast(Char *)memory->temp_memory + (memory->temp_index + res.alignment_offset);

    res.size = size;
    res.used = 0;
    memory->temp_index += size + res.alignment_offset;
    zero_memory_block(res.block, res.size);

    return(res);
}

internal Void
pop_temp_memory(TempMemory *temp_memory)
{
    assert(temp_memory);
    assert((temp_memory->full_memory_block) && (temp_memory->block) && (temp_memory->size));

    temp_memory->full_memory_block->temp_index -= temp_memory->size + temp_memory->alignment_offset;
    zero_memory_block(temp_memory, sizeof(*temp_memory));
}

#define push_struct_off_temp_memory(temp_memory, Type, ...) cast(Type *)push_off_temp_memory(temp_memory, sizeof(Type), ##__VA_ARGS__)
#define push_array_off_temp_memory(temp_memory, Type, len, ...) cast(Type *)push_off_temp_memory(temp_memory, sizeof(Type) * len, ##__VA_ARGS__)
internal Void *
push_off_temp_memory(TempMemory *temp_memory, Int size, Int alignment = default_memory_alignment)
{
    assert((temp_memory) && (size));

    Int alignment_offset = get_alignment_offset(temp_memory->block, temp_memory->used, alignment);
    Void *res = temp_memory->block + temp_memory->used + alignment_offset;
    assert(temp_memory->used + alignment_offset <= temp_memory->size);

    temp_memory->used += size + alignment_offset;

    return(res);
}

//
// Utils.
//

internal Bool
is_end_of_line(Char c)
{
    Bool res = ((c == '\n') || (c == '\r'));

    return(res);
}

internal Bool
is_whitespace(Char c)
{
    Bool res = ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\f') || (is_end_of_line(c)));

    return(res);
}

internal Int
string_length(Char *str)
{
    assert(str);

    Int res = 0;
    while(*str) {
        ++res;
        ++str;
    }

    return(res);
}

enum ExtensionType {
    ExtensionType_unknown,
    ExtensionType_cpp,
    ExtensionType_c,
};

internal ExtensionType
get_extension_from_str(Char *str)
{
    assert(str);

    ExtensionType res = ExtensionType_unknown;

    Int len = string_length(str);
    // TODO(Jonny): Do this properly...
    if((str[len - 1] == 'c') && (str[len - 2] == '.')) {
        res = ExtensionType_c;
    } else if((str[len - 1] == 'p') && (str[len - 2] == 'p') && (str[len - 3] == 'c') && (str[len - 4] == '.') ) {
        res = ExtensionType_cpp;
    }

    return(res);
}

//
// Start Parsing function.
//
struct AllFiles {
    Char *file[16]; // TODO(Jonny): Random size.
    Int count;
};

struct StuffToWrite {
    Int header_size;
    Void *header_data;

    Int source_size;
    Void *source_data;
};

StuffToWrite start_parsing(AllFiles all_files, Memory *memory);
