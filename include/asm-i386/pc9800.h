multiline_comment|/*&n; *  PC-9800 machine types.&n; *&n; *  Copyright (C) 1999&t;TAKAI Kosuke &lt;tak@kmc.kyoto-u.ac.jp&gt;&n; *&t;&t;&t;(Linux/98 Project)&n; */
macro_line|#ifndef _ASM_PC9800_H_
DECL|macro|_ASM_PC9800_H_
mdefine_line|#define _ASM_PC9800_H_
macro_line|#include &lt;asm/pc9800_sca.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|__PC9800SCA
mdefine_line|#define __PC9800SCA(type, pa)&t;(*(type *) phys_to_virt(pa))
DECL|macro|__PC9800SCA_TEST_BIT
mdefine_line|#define __PC9800SCA_TEST_BIT(pa, n)&t;&bslash;&n;&t;((__PC9800SCA(u8, pa) &amp; (1U &lt;&lt; (n))) != 0)
DECL|macro|PC9800_HIGHRESO_P
mdefine_line|#define PC9800_HIGHRESO_P()&t;__PC9800SCA_TEST_BIT(PC9800SCA_BIOS_FLAG, 3)
DECL|macro|PC9800_8MHz_P
mdefine_line|#define PC9800_8MHz_P()&t;&t;__PC9800SCA_TEST_BIT(PC9800SCA_BIOS_FLAG, 7)
multiline_comment|/* 0x2198 is 98 21 on memory... */
DECL|macro|PC9800_9821_P
mdefine_line|#define PC9800_9821_P()&t;&t;(__PC9800SCA(u16, PC9821SCA_ROM_ID) == 0x2198)
multiline_comment|/* Note PC9821_...() are valid only when PC9800_9821_P() was true. */
DECL|macro|PC9821_IDEIF_DOUBLE_P
mdefine_line|#define PC9821_IDEIF_DOUBLE_P()&t;__PC9800SCA_TEST_BIT(PC9821SCA_ROM_FLAG4, 4)
macro_line|#endif
eof
