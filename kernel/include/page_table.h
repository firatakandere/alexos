#include <stdint.h>

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

typedef uint32_t* page_directory_t;
typedef uint32_t* page_table_t;

page_directory_t initialize_page_directory();
page_table_t get_page_table(page_directory_t pd, int i);

#endif // PAGE_TABLE_H