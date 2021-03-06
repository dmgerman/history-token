multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Ralf Baechle&n; */
macro_line|#ifndef _ASM_ASMMACRO_H
DECL|macro|_ASM_ASMMACRO_H
mdefine_line|#define _ASM_ASMMACRO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/hazards.h&gt;
macro_line|#ifdef CONFIG_MIPS32
macro_line|#include &lt;asm/asmmacro-32.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
macro_line|#include &lt;asm/asmmacro-64.h&gt;
macro_line|#endif
dot
id|macro
id|local_irq_enable
id|reg
op_assign
id|t0
id|mfc0
"&bslash;"
id|reg
comma
id|CP0_STATUS
DECL|variable|reg
DECL|variable|reg
id|ori
"&bslash;"
id|reg
comma
"&bslash;"
id|reg
comma
l_int|1
DECL|variable|reg
id|mtc0
"&bslash;"
id|reg
comma
id|CP0_STATUS
id|irq_enable_hazard
dot
id|endm
dot
id|macro
id|local_irq_disable
id|reg
op_assign
id|t0
id|mfc0
"&bslash;"
id|reg
comma
id|CP0_STATUS
DECL|variable|reg
DECL|variable|reg
id|ori
"&bslash;"
id|reg
comma
"&bslash;"
id|reg
comma
l_int|1
DECL|variable|reg
DECL|variable|reg
id|xori
"&bslash;"
id|reg
comma
"&bslash;"
id|reg
comma
l_int|1
DECL|variable|reg
id|mtc0
"&bslash;"
id|reg
comma
id|CP0_STATUS
id|irq_disable_hazard
dot
id|endm
macro_line|#ifdef CONFIG_CPU_SB1
dot
id|macro
id|fpu_enable_hazard
dot
id|set
id|push
dot
id|set
id|noreorder
dot
id|set
id|mips2
id|SSNOP
id|bnezl
"$"
l_int|0
comma
dot
op_plus
l_int|4
id|SSNOP
dot
id|set
id|pop
dot
id|endm
macro_line|#else
dot
id|macro
id|fpu_enable_hazard
dot
id|endm
macro_line|#endif
macro_line|#endif /* _ASM_ASMMACRO_H */
eof
