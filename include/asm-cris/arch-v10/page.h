macro_line|#ifndef _CRIS_ARCH_PAGE_H
DECL|macro|_CRIS_ARCH_PAGE_H
mdefine_line|#define _CRIS_ARCH_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* This handles the memory map.. */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;KSEG_6   /* kseg_6 is mapped to physical ram */
macro_line|#else
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;KSEG_C   /* kseg_c is mapped to physical ram */
macro_line|#endif
multiline_comment|/* macros to convert between really physical and virtual addresses&n; * by stripping a selected bit, we can convert between KSEG_x and 0x40000000 where&n; * the DRAM really resides&n; */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
multiline_comment|/* we have DRAM virtually at 0x6 */
DECL|macro|__pa
mdefine_line|#define __pa(x)                 ((unsigned long)(x) &amp; 0xdfffffff)
DECL|macro|__va
mdefine_line|#define __va(x)                 ((void *)((unsigned long)(x) | 0x20000000))
macro_line|#else
multiline_comment|/* we have DRAM virtually at 0xc */
DECL|macro|__pa
mdefine_line|#define __pa(x)                 ((unsigned long)(x) &amp; 0x7fffffff)
DECL|macro|__va
mdefine_line|#define __va(x)                 ((void *)((unsigned long)(x) | 0x80000000))
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
