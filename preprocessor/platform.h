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

#if !defined(_PLATFORM_H)

#include "shared.h"

// Memory.
Void *system_malloc(PtrSize size, PtrSize cnt/*= 1*/);
Bool system_free(Void *ptr);
Void *system_realloc(Void *ptr, PtrSize size);

// File IO.
struct File;
File read_entire_file_and_null_terminate(Char *fname, Void *memory);
Bool write_to_file(Char *fname, Void *data, PtrSize data_size);
PtrSize get_file_size(Char *fname);

// Utility stuff.
Uint64 system_get_performance_counter(void);
Void system_print_timer(Uint64 value);
Bool system_check_for_debugger(void);
Void system_write_to_console(Char *str);
Void system_write_to_stderr(Char *str);

#define _PLATFORM_H
#endif