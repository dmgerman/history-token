multiline_comment|/*&n; * include/asm-v850/asm.h -- Macros for writing assembly code&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
DECL|macro|G_ENTRY
mdefine_line|#define G_ENTRY(name)&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   .align 4;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   .globl name;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   .type  name,@function;&t;&t;&t;&t;&t;&t;      &bslash;&n;   name
DECL|macro|END
mdefine_line|#define END(name)&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   .size  name,.-name
DECL|macro|L_ENTRY
mdefine_line|#define L_ENTRY(name)&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   .align 4;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;   .type  name,@function;&t;&t;&t;&t;&t;&t;      &bslash;&n;   name
eof
