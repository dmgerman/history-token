multiline_comment|/*&n; * Copyright (C) 2004  Maciej W. Rozycki&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_COMPILER_H
DECL|macro|_ASM_COMPILER_H
mdefine_line|#define _ASM_COMPILER_H
macro_line|#if __GNUC__ &gt; 3 || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt;= 4)
DECL|macro|GCC_REG_ACCUM
mdefine_line|#define GCC_REG_ACCUM &quot;$0&quot;
macro_line|#else
DECL|macro|GCC_REG_ACCUM
mdefine_line|#define GCC_REG_ACCUM &quot;accum&quot;
macro_line|#endif
macro_line|#endif /* _ASM_COMPILER_H */
eof
