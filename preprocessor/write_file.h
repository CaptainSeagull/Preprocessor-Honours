/*===================================================================================================
  File:                    write_file.h
  Author:                  Jonathan Livingstone
  Email:                   seagull127@ymail.com
  Licence:                 Public Domain
                           No Warranty is offered or implied about the reliability,
                           suitability, or usability
                           The use of this code is at your own risk
                           Anyone can use this code, modify it, sell it to terrorists, etc.
  ===================================================================================================*/

#if !defined(_WRTIE_FILE_H)

#include "shared.h"

struct StructData;
struct EnumData;
struct File;

File write_data(Char *fname, StructData *struct_data, Int struct_count, EnumData *enum_data, Int enum_count);

#define _WRTIE_FILE_H
#endif
