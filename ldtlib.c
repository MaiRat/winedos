/* $Id$
 */
/*
 * Copyright  Robert J. Amstadt, 1993
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#ifdef __DJGPP__
# include <dos.h>
# include <dpmi.h>
# include <go32.h>
#else
# include <linux/unistd.h>
# include <linux/head.h>
#endif
#include "my_ldt.h"

#ifndef __DJGPP__
_syscall2(int, modify_ldt, int, func, void *, ptr)
#else
static int modify_ldt(int func, void *ptr)
{
    struct modify_ldt_ldt_s *info = (struct modify_ldt_ldt_s *)ptr;
    __dpmi_regs regs;
    unsigned short sel;
    unsigned int rights;

    if (func != 1 || info == NULL)
    {
        errno = ENOSYS;
        return -1;
    }

    sel = (info->entry_number << 3) | 7;

    /* Set base address */
    regs.x.ax = 0x000a;
    regs.x.cx = sel;
    regs.d.eax = info->base_addr;
    __dpmi_int(0x31, &regs);
    if (regs.x.flags & 1)
        return -1;

    /* Set segment limit and flags */
    regs.x.ax = 0x000b;
    regs.x.cx = sel;
    regs.d.eax = info->limit;
    regs.h.dh = 0;
    if (info->limit_in_pages)
        regs.h.dh |= 0x80;
    if (info->seg_32bit)
        regs.h.dh |= 0x40;
    __dpmi_int(0x31, &regs);
    if (regs.x.flags & 1)
        return -1;

    /* Compute access rights */
    if (info->contents == MODIFY_LDT_CONTENTS_CODE)
        rights = info->read_exec_only ? 0x9a : 0xfa;
    else if (info->contents == MODIFY_LDT_CONTENTS_STACK)
        rights = info->read_exec_only ? 0x96 : 0xf6;
    else
        rights = info->read_exec_only ? 0x92 : 0xf2;

    regs.x.ax = 0x000c;
    regs.x.cx = sel;
    regs.x.dx = rights;
    __dpmi_int(0x31, &regs);
    if (regs.x.flags & 1)
        return -1;

    return 0;
}
#endif

int
get_ldt(void *buffer)
{
    return modify_ldt(0, buffer);
}

int
set_ldt_entry(int entry, unsigned long base, unsigned int limit,
	      int seg_32bit_flag, int contents, int read_only_flag,
	      int limit_in_pages_flag)
{
    struct modify_ldt_ldt_s ldt_info;

    ldt_info.entry_number   = entry;
    ldt_info.base_addr      = base;
    ldt_info.limit          = limit;
    ldt_info.seg_32bit      = seg_32bit_flag;
    ldt_info.contents       = contents;
    ldt_info.read_exec_only = read_only_flag;
    ldt_info.limit_in_pages = limit_in_pages_flag;

    return modify_ldt(1, &ldt_info);
}
