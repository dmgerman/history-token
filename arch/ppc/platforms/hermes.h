multiline_comment|/*&n; * Multidata HERMES-PRO ( / SL ) board specific definitions&n; * &n; * Copyright (c) 2000, 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_HERMES_H
DECL|macro|__MACH_HERMES_H
mdefine_line|#define __MACH_HERMES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|HERMES_IMMR_BASE
mdefine_line|#define&t;HERMES_IMMR_BASE    0xFF000000&t;/* phys. addr of IMMR&t;&t;&t;*/
DECL|macro|HERMES_IMAP_SIZE
mdefine_line|#define&t;HERMES_IMAP_SIZE   (64 * 1024)&t;/* size of mapped area&t;&t;&t;*/
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR     HERMES_IMMR_BASE&t;/* physical base address of IMMR area&t;*/
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE     HERMES_IMAP_SIZE&t;/* mapped size of IMMR area&t;&t;*/
DECL|macro|FEC_INTERRUPT
mdefine_line|#define&t;FEC_INTERRUPT&t; 9&t;&t;/* = SIU_LEVEL4&t;&t;&t;&t;*/
DECL|macro|CPM_INTERRUPT
mdefine_line|#define&t;CPM_INTERRUPT&t;11&t;&t;/* = SIU_LEVEL5 (was: SIU_LEVEL2)&t;*/
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif&t;/* __MACH_HERMES_H */
eof
