multiline_comment|/*&n; * include/asm-v850/macrology.h -- Various useful CPP macros&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
DECL|macro|macrology_paste
mdefine_line|#define macrology_paste(arg1, arg2)&t;macrology_paste_1(arg1, arg2)
DECL|macro|macrology_paste_1
mdefine_line|#define macrology_paste_1(arg1, arg2)&t;arg1 ## arg2
DECL|macro|macrology_stringify
mdefine_line|#define macrology_stringify(sym)&t;macrology_stringify_1(sym)
DECL|macro|macrology_stringify_1
mdefine_line|#define macrology_stringify_1(sym)&t;#sym
eof
