multiline_comment|/*&n; * include/asm-sh/ubc.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; * Copyright (C) 2002, 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_SH_UBC_H
DECL|macro|__ASM_SH_UBC_H
mdefine_line|#define __ASM_SH_UBC_H
macro_line|#include &lt;asm/cpu/ubc.h&gt;
multiline_comment|/* User Break Controller */
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7709)
DECL|macro|UBC_TYPE_SH7729
mdefine_line|#define UBC_TYPE_SH7729&t;(cpu_data-&gt;type == CPU_SH7729)
macro_line|#else
DECL|macro|UBC_TYPE_SH7729
mdefine_line|#define UBC_TYPE_SH7729&t;0
macro_line|#endif
DECL|macro|BAMR_ASID
mdefine_line|#define BAMR_ASID&t;&t;(1 &lt;&lt; 2)
DECL|macro|BAMR_NONE
mdefine_line|#define BAMR_NONE&t;&t;0
DECL|macro|BAMR_10
mdefine_line|#define BAMR_10&t;&t;&t;0x1
DECL|macro|BAMR_12
mdefine_line|#define BAMR_12&t;&t;&t;0x2
DECL|macro|BAMR_ALL
mdefine_line|#define BAMR_ALL&t;&t;0x3
DECL|macro|BAMR_16
mdefine_line|#define BAMR_16&t;&t;&t;0x8
DECL|macro|BAMR_20
mdefine_line|#define BAMR_20&t;&t;&t;0x9
DECL|macro|BBR_INST
mdefine_line|#define BBR_INST&t;&t;(1 &lt;&lt; 4)
DECL|macro|BBR_DATA
mdefine_line|#define BBR_DATA&t;&t;(2 &lt;&lt; 4)
DECL|macro|BBR_READ
mdefine_line|#define BBR_READ&t;&t;(1 &lt;&lt; 2)
DECL|macro|BBR_WRITE
mdefine_line|#define BBR_WRITE&t;&t;(2 &lt;&lt; 2)
DECL|macro|BBR_BYTE
mdefine_line|#define BBR_BYTE&t;&t;0x1
DECL|macro|BBR_HALF
mdefine_line|#define BBR_HALF&t;&t;0x2
DECL|macro|BBR_LONG
mdefine_line|#define BBR_LONG&t;&t;0x3
DECL|macro|BBR_QUAD
mdefine_line|#define BBR_QUAD&t;&t;(1 &lt;&lt; 6)&t;/* SH7750 */
DECL|macro|BBR_CPU
mdefine_line|#define BBR_CPU&t;&t;&t;(1 &lt;&lt; 6)&t;/* SH7709A,SH7729 */
DECL|macro|BBR_DMA
mdefine_line|#define BBR_DMA&t;&t;&t;(2 &lt;&lt; 6)&t;/* SH7709A,SH7729 */
DECL|macro|BRCR_CMFA
mdefine_line|#define BRCR_CMFA&t;&t;(1 &lt;&lt; 15)
DECL|macro|BRCR_CMFB
mdefine_line|#define BRCR_CMFB&t;&t;(1 &lt;&lt; 14)
DECL|macro|BRCR_PCTE
mdefine_line|#define BRCR_PCTE&t;&t;(1 &lt;&lt; 11)
DECL|macro|BRCR_PCBA
mdefine_line|#define BRCR_PCBA&t;&t;(1 &lt;&lt; 10)&t;/* 1: after execution */
DECL|macro|BRCR_DBEB
mdefine_line|#define BRCR_DBEB&t;&t;(1 &lt;&lt; 7)
DECL|macro|BRCR_PCBB
mdefine_line|#define BRCR_PCBB&t;&t;(1 &lt;&lt; 6)
DECL|macro|BRCR_SEQ
mdefine_line|#define BRCR_SEQ&t;&t;(1 &lt;&lt; 3)
DECL|macro|BRCR_UBDE
mdefine_line|#define BRCR_UBDE&t;&t;(1 &lt;&lt; 0)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* arch/sh/kernel/ubc.S */
r_extern
r_void
id|ubc_wakeup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ubc_sleep
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_SH_UBC_H */
eof
