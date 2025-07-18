#ifndef WINE_DOS_MY_LDT_H
#define WINE_DOS_MY_LDT_H

#ifdef __DJGPP__

struct modify_ldt_ldt_s {
    unsigned int  entry_number;
    unsigned long base_addr;
    unsigned int  limit;
    unsigned int  seg_32bit:1;
    unsigned int  contents:2;
    unsigned int  read_exec_only:1;
    unsigned int  limit_in_pages:1;
    unsigned int  seg_not_present:1;
    unsigned int  useable:1;
};

#define MODIFY_LDT_CONTENTS_DATA  0
#define MODIFY_LDT_CONTENTS_STACK 1
#define MODIFY_LDT_CONTENTS_CODE  2

#else /* __DJGPP__ */

#include <linux/ldt.h>

#endif /* __DJGPP__ */

#endif /* WINE_DOS_MY_LDT_H */
