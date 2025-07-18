/* $Id: neexe.h,v 1.1 1993/06/09 03:28:10 root Exp root $
 */
/*
 * Copyright  Robert J. Amstadt, 1993
 */
#ifndef NEEXE_H
#define NEEXE_H

/*
 * Old MZ header for DOS programs.  Actually just a couple of fields
 * from it, so that we can find the start of the NE header.
 */
struct mz_header_s
{
    unsigned char dont_care1[0x18];	/* MZ Header stuff			*/
    unsigned char must_be_0x40;	/* 0x40 for non-MZ program		*/
    unsigned char dont_care2[0x23];	/* More MZ header stuff			*/
    unsigned short ne_offset;		/* Offset to extended header		*/
};

/*
 * This is the Windows executable (NE) header.
 */
struct ne_header_s
{
    char    header_type[2];	/* Must contain 'N' 'E'			*/
    unsigned char  linker_version;	/* Linker version number		*/
    unsigned char  linker_revision;	/* Linker revision number		*/
    unsigned short entry_tab_offset;	/* Offset to entry table relative to NE */
    unsigned short entry_tab_length;	/* Length of etnry table in bytes	*/
    unsigned long  reserved1;		/* Reserved by Microsoft		*/
    unsigned short format_flags;	/* Flags that segments in this file	*/
    unsigned short auto_data_seg;	/* Automatic data segment number	*/
    unsigned short local_heap_length;	/* Initial size of local heap		*/
    unsigned short stack_length;	/* Initial size of stack		*/
    unsigned short ip;			/* Initial IP				*/
    unsigned short cs;			/* Initial CS				*/
    unsigned short sp;			/* Initial SP				*/
    unsigned short ss;			/* Initial SS				*/
    unsigned short n_segment_tab;	/* # of entries in segment table	*/
    unsigned short n_mod_ref_tab;	/* # of entries in module reference tab.*/
    unsigned short nrname_tab_length; 	/* Length of nonresident-name table     */
    unsigned short segment_tab_offset;	/* Offset to segment table		*/
    unsigned short resource_tab_offset;/* Offset to resource table		*/
    unsigned short rname_tab_offset;	/* Offset to resident-name table	*/
    unsigned short moduleref_tab_offset;/* Offset to module reference table	*/
    unsigned short iname_tab_offset;	/* Offset to imported name table	*/
    unsigned long  nrname_tab_offset;	/* Offset to nonresident-name table	*/
    unsigned short n_mov_entry_points;	/* # of movable entry points		*/
    unsigned short align_shift_count;	/* Logical sector alignment shift count */
    unsigned short n_resource_seg;	/* # of resource segments		*/
    unsigned char  operating_system;	/* Flags indicating target OS		*/
    unsigned char  additional_flags;	/* Additional information flags		*/
    unsigned short fastload_offset;	/* Offset to fast load area		*/
    unsigned short fastload_length;	/* Length of fast load area		*/
    unsigned short reserved2;		/* Reserved by Microsoft		*/
    unsigned short expect_version;	/* Expected Windows version number	*/
};

/*
 * NE Header FORMAT FLAGS
 */
#define NE_FFLAGS_SINGLEDATA	0x0001
#define NE_FFLAGS_MULTIPLEDATA	0x0002
#define NE_FFLAGS_SELFLOAD	0x0800
#define NE_FFLAGS_LINKERROR	0x2000
#define NE_FFLAGS_LIBMODULE	0x8000

/*
 * NE Header OPERATING SYSTEM
 */
#define NE_OSFLAGS_UNKNOWN	0x01
#define NE_OSFLAGS_WINDOWS	0x04

/*
 * NE Header ADDITIONAL FLAGS
 */
#define NE_AFLAGS_WIN2_PROTMODE	0x02
#define NE_AFLAGS_WIN2_PROFONTS	0x04
#define NE_AFLAGS_FASTLOAD	0x08

/*
 * Segment table entry
 */
struct ne_segment_table_entry_s
{
    unsigned short seg_data_offset;	/* Sector offset of segment data	*/
    unsigned short seg_data_length;	/* Length of segment data		*/
    unsigned short seg_flags;		/* Flags associated with this segment	*/
    unsigned short min_alloc;		/* Minimum allocation size for this	*/
};

/*
 * Segment Flags
 */
#define NE_SEGFLAGS_DATA	0x0001
#define NE_SEGFLAGS_ALLOCATED	0x0002
#define NE_SEGFLAGS_LOADED	0x0004
#define NE_SEGFLAGS_MOVEABLE	0x0010
#define NE_SEGFLAGS_SHAREABLE	0x0020
#define NE_SEGFLAGS_PRELOAD	0x0040
#define NE_SEGFLAGS_EXECUTEONLY	0x0080
#define NE_SEGFLAGS_READONLY	0x0080
#define NE_SEGFLAGS_RELOC_DATA	0x0100
#define NE_SEGFLAGS_DISCARDABLE	0x1000

/*
 * Relocation table entry
 */
struct relocation_entry_s
{
    unsigned char  address_type;	/* Relocation address type		*/
    unsigned char  relocation_type;	/* Relocation type			*/
    unsigned short offset;		/* Offset in segment to fixup		*/
    unsigned short target1;		/* Target specification			*/
    unsigned short target2;		/* Target specification			*/
};

/*
 * Relocation address types
 */
#define NE_RADDR_LOWBYTE	0
#define NE_RADDR_SELECTOR	2
#define NE_RADDR_POINTER32	3
#define NE_RADDR_OFFSET16	5
#define NE_RADDR_POINTER48	11
#define NE_RADDR_OFFSET32	13

/*
 * Relocation types
 */
#define NE_RELTYPE_INTERNAL	0
#define NE_RELTYPE_ORDINAL	1
#define NE_RELTYPE_NAME		2
#define NE_RELTYPE_OSFIXUP	3

/*
 * DOS PSP
 */
struct dos_psp_s
{
    unsigned short pspInt20;
    unsigned short pspNextParagraph;
    unsigned char  pspReserved1;
    unsigned char  pspDispatcher[5];
    unsigned long  pspTerminateVector;
    unsigned long  pspControlCVector;
    unsigned long  pspCritErrorVector;
    unsigned short pspReserved2[11];
    unsigned short pspEnvironment;
    unsigned short pspReserved3[23];
    unsigned char  pspFCB_1[16];
    unsigned char  pspFCB_2[16];
    unsigned char  pspCommandTailCount;
    unsigned char  pspCommandTail[128];
};

#endif /* NEEXE_H */
