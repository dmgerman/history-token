multiline_comment|/*&n; * include/asm-v850/clinkage.h -- Macros to reflect C symbol-naming conventions&n; *&n; *  Copyright (C) 2001,02  NEC Corporatione&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __CLINKAGE_H__
DECL|macro|__V850_CLINKAGE_H__
mdefine_line|#define __V850_CLINKAGE_H__
macro_line|#include &lt;asm/macrology.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
DECL|macro|C_SYMBOL_NAME
mdefine_line|#define C_SYMBOL_NAME(name) &t;macrology_paste(_, name)
DECL|macro|C_SYMBOL_STRING
mdefine_line|#define C_SYMBOL_STRING(name)&t;macrology_stringify(C_SYMBOL_NAME(name))
DECL|macro|C_ENTRY
mdefine_line|#define C_ENTRY(name)&t;&t;G_ENTRY(C_SYMBOL_NAME(name))
DECL|macro|C_END
mdefine_line|#define C_END(name)&t;&t;END(C_SYMBOL_NAME(name))
macro_line|#endif /* __V850_CLINKAGE_H__ */
eof
