macro_line|#ifndef __I386_DIV64
DECL|macro|__I386_DIV64
mdefine_line|#define __I386_DIV64
multiline_comment|/*&n; * do_div() is NOT a C function. It wants to return&n; * two values (the quotient and the remainder), but&n; * since that doesn&squot;t work very well in C, what it&n; * does is:&n; *&n; * - modifies the 64-bit dividend _in_place_&n; * - returns the 32-bit remainder&n; *&n; * This ends up being the most efficient &quot;calling&n; * convention&quot; on x86.&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;&t;unsigned long __upper, __low, __high, __mod; &bslash;&n;&t;asm(&quot;&quot;:&quot;=a&quot; (__low), &quot;=d&quot; (__high):&quot;A&quot; (n)); &bslash;&n;&t;__upper = __high; &bslash;&n;&t;if (__high) { &bslash;&n;&t;&t;__upper = __high % (base); &bslash;&n;&t;&t;__high = __high / (base); &bslash;&n;&t;} &bslash;&n;&t;asm(&quot;divl %2&quot;:&quot;=a&quot; (__low), &quot;=d&quot; (__mod):&quot;rm&quot; (base), &quot;0&quot; (__low), &quot;1&quot; (__upper)); &bslash;&n;&t;asm(&quot;&quot;:&quot;=A&quot; (n):&quot;a&quot; (__low),&quot;d&quot; (__high)); &bslash;&n;&t;__mod; &bslash;&n;})
multiline_comment|/*&n; * (long)X = ((long long)divs) / (long)div&n; * (long)rem = ((long long)divs) % (long)div&n; *&n; * Warning, this will do an exception if X overflows.&n; */
DECL|macro|div_long_long_rem
mdefine_line|#define div_long_long_rem(a,b,c) div_ll_X_l_rem(a,b,c)
r_extern
r_inline
r_int
DECL|function|div_ll_X_l_rem
id|div_ll_X_l_rem
c_func
(paren
r_int
r_int
id|divs
comma
r_int
id|div
comma
r_int
op_star
id|rem
)paren
(brace
r_int
id|dum2
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dum2
)paren
comma
l_string|&quot;=d&quot;
(paren
op_star
id|rem
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|div
)paren
comma
l_string|&quot;A&quot;
(paren
id|divs
)paren
)paren
suffix:semicolon
r_return
id|dum2
suffix:semicolon
)brace
macro_line|#endif
eof
