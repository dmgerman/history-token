macro_line|#ifndef _ASM_M32R_DIV64
DECL|macro|_ASM_M32R_DIV64
mdefine_line|#define _ASM_M32R_DIV64
multiline_comment|/* $Id$ */
multiline_comment|/* unsigned long long division.&n; * Input:&n; *  unsigned long long  n&n; *  unsigned long  base&n; * Output:&n; *  n = n / base;&n; *  return value = n % base;&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n, base)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _res, _high, _mid, _low;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_low = (n) &amp; 0xffffffffUL;&t;&t;&t;&t;&bslash;&n;&t;_high = (n) &gt;&gt; 32;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_high) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_mid = (_high % (unsigned long)(base)) &lt;&lt; 16;&t;&bslash;&n;&t;&t;_high = _high / (unsigned long)(base);&t;&t;&bslash;&n;&t;&t;_mid += _low &gt;&gt; 16;&t;&t;&t;&t;&bslash;&n;&t;&t;_low &amp;= 0x0000ffffUL;&t;&t;&t;&t;&bslash;&n;&t;&t;_low += (_mid % (unsigned long)(base)) &lt;&lt; 16;&t;&bslash;&n;&t;&t;_mid = _mid / (unsigned long)(base);&t;&t;&bslash;&n;&t;&t;_res = _low % (unsigned long)(base);&t;&t;&bslash;&n;&t;&t;_low = _low / (unsigned long)(base);&t;&t;&bslash;&n;&t;&t;n = _low + ((long long)_mid &lt;&lt; 16) +&t;&t;&bslash;&n;&t;&t;&t;((long long)_high &lt;&lt; 32);&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_res = _low % (unsigned long)(base);&t;&t;&bslash;&n;&t;&t;n = (_low / (unsigned long)(base));&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif  /* _ASM_M32R_DIV64 */
eof
