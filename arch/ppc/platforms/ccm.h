multiline_comment|/*&n; * Siemens Card Controller Module specific definitions&n; * &n; * Copyright (c) 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_CCM_H
DECL|macro|__MACH_CCM_H
mdefine_line|#define __MACH_CCM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|CCM_IMMR_BASE
mdefine_line|#define&t;CCM_IMMR_BASE    0xF0000000&t;/* phys. addr of IMMR&t;&t;&t;*/
DECL|macro|CCM_IMAP_SIZE
mdefine_line|#define&t;CCM_IMAP_SIZE   (64 * 1024)&t;/* size of mapped area&t;&t;&t;*/
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR     CCM_IMMR_BASE&t;/* physical base address of IMMR area&t;*/
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE     CCM_IMAP_SIZE&t;/* mapped size of IMMR area&t;&t;*/
DECL|macro|FEC_INTERRUPT
mdefine_line|#define&t;FEC_INTERRUPT&t;15&t;&t;/* = SIU_LEVEL7&t;&t;&t;&t;*/
DECL|macro|DEC_INTERRUPT
mdefine_line|#define&t;DEC_INTERRUPT&t;13&t;&t;/* = SIU_LEVEL6&t;&t;&t;&t;*/
DECL|macro|CPM_INTERRUPT
mdefine_line|#define&t;CPM_INTERRUPT&t;11&t;&t;/* = SIU_LEVEL5 (was: SIU_LEVEL2)&t;*/
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif&t;/* __MACH_CCM_H */
eof
