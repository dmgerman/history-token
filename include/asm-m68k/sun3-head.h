multiline_comment|/* $Id: head.h,v 1.32 1996/12/04 00:12:48 ecd Exp $ */
macro_line|#ifndef __SUN3_HEAD_H
DECL|macro|__SUN3_HEAD_H
mdefine_line|#define __SUN3_HEAD_H
DECL|macro|KERNBASE
mdefine_line|#define KERNBASE        0xE000000  /* First address the kernel will eventually be */
DECL|macro|LOAD_ADDR
mdefine_line|#define LOAD_ADDR       0x4000      /* prom jumps to us here unless this is elf /boot */
DECL|macro|BI_START
mdefine_line|#define BI_START (KERNBASE + 0x3000) /* beginning of the bootinfo records */
DECL|macro|FC_CONTROL
mdefine_line|#define FC_CONTROL  3
DECL|macro|FC_SUPERD
mdefine_line|#define FC_SUPERD    5
DECL|macro|FC_CPU
mdefine_line|#define FC_CPU      7
macro_line|#endif __SUN3_HEAD_H
eof
