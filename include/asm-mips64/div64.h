multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_DIV64_H
DECL|macro|_ASM_DIV64_H
mdefine_line|#define _ASM_DIV64_H
multiline_comment|/*&n; * Don&squot;t use this one in new code&n; */
DECL|macro|do_div64_32
mdefine_line|#define do_div64_32(res, high, low, base) ({ &bslash;&n;&t;unsigned int __quot, __mod; &bslash;&n;&t;unsigned long __div; &bslash;&n;&t;unsigned int __low, __high, __base; &bslash;&n;&t;&bslash;&n;&t;__high = (high); &bslash;&n;&t;__low = (low); &bslash;&n;&t;__div = __high; &bslash;&n;&t;__div = __div &lt;&lt; 32 | __low; &bslash;&n;&t;__base = (base); &bslash;&n;&t;&bslash;&n;&t;__mod = __div % __base; &bslash;&n;&t;__div = __div / __base; &bslash;&n;&t;&bslash;&n;&t;__quot = __div; &bslash;&n;&t;(res) = __quot; &bslash;&n;&t;__mod; })
multiline_comment|/*&n; * Hey, we&squot;re already 64-bit, no&n; * need to play games..&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n, base) ({ &bslash;&n;&t;unsigned long __quot; &bslash;&n;&t;unsigned int __mod; &bslash;&n;&t;unsigned long __div; &bslash;&n;&t;unsigned int __base; &bslash;&n;&t;&bslash;&n;&t;__div = (n); &bslash;&n;&t;__base = (base); &bslash;&n;&t;&bslash;&n;&t;__mod = __div % __base; &bslash;&n;&t;__quot = __div / __base; &bslash;&n;&t;&bslash;&n;&t;(n) = __quot; &bslash;&n;&t;__mod; })
macro_line|#endif /* _ASM_DIV64_H */
eof
