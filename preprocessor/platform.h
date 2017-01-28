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

#include "utils.h"

// Memory.
Void *system_malloc(PtrSize size, PtrSize cnt/*= 1*/);
Bool system_free(Void *ptr);
Void *system_realloc(Void *ptr, PtrSize size);

// Utility stuff.
Uint64 system_get_performance_counter(void);
Void system_print_timer(Uint64 value);
Bool system_check_for_debugger(void);

#define _PLATFORM_H
#endif