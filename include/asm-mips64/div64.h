multiline_comment|/* $Id: div64.h,v 1.1 2000/01/28 23:18:55 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_DIV64_H
DECL|macro|_ASM_DIV64_H
mdefine_line|#define _ASM_DIV64_H
multiline_comment|/*&n; * Hey, we&squot;re already 64-bit, no&n; * need to play games..&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;&t;int __res; &bslash;&n;&t;__res = ((unsigned long) n) % (unsigned) base; &bslash;&n;&t;n = ((unsigned long) n) / (unsigned) base; &bslash;&n;&t;__res; })
macro_line|#endif /* _ASM_DIV64_H */
eof
