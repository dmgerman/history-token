multiline_comment|/*&n; * LANTEC board specific definitions&n; * &n; * Copyright (c) 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_LANTEC_H
DECL|macro|__MACH_LANTEC_H
mdefine_line|#define __MACH_LANTEC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR&t;0xFFF00000&t;/* physical base address of IMMR area&t;*/
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;(64 * 1024)&t;/* mapped size of IMMR area&t;&t;*/
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif&t;/* __MACH_LANTEC_H */
eof
