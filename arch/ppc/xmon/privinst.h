multiline_comment|/*&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|GETREG
mdefine_line|#define GETREG(reg)&t;&t;&bslash;&n;    static inline int get_ ## reg (void)&t;&bslash;&n;&t;{ int ret; asm volatile (&quot;mf&quot; #reg &quot; %0&quot; : &quot;=r&quot; (ret) :); return ret; }
DECL|macro|SETREG
mdefine_line|#define SETREG(reg)&t;&t;&bslash;&n;    static inline void set_ ## reg (int val)&t;&bslash;&n;&t;{ asm volatile (&quot;mt&quot; #reg &quot; %0&quot; : : &quot;r&quot; (val)); }
id|GETREG
c_func
(paren
id|msr
)paren
id|SETREG
c_func
(paren
id|msr
)paren
id|GETREG
c_func
(paren
id|cr
)paren
DECL|macro|GSETSPR
mdefine_line|#define GSETSPR(n, name)&t;&bslash;&n;    static inline int get_ ## name (void) &bslash;&n;&t;{ int ret; asm volatile (&quot;mfspr %0,&quot; #n : &quot;=r&quot; (ret) : ); return ret; } &bslash;&n;    static inline void set_ ## name (int val) &bslash;&n;&t;{ asm volatile (&quot;mtspr &quot; #n &quot;,%0&quot; : : &quot;r&quot; (val)); }
id|GSETSPR
c_func
(paren
l_int|0
comma
id|mq
)paren
id|GSETSPR
c_func
(paren
l_int|1
comma
id|xer
)paren
id|GSETSPR
c_func
(paren
l_int|4
comma
id|rtcu
)paren
id|GSETSPR
c_func
(paren
l_int|5
comma
id|rtcl
)paren
id|GSETSPR
c_func
(paren
l_int|8
comma
id|lr
)paren
id|GSETSPR
c_func
(paren
l_int|9
comma
id|ctr
)paren
id|GSETSPR
c_func
(paren
l_int|18
comma
id|dsisr
)paren
id|GSETSPR
c_func
(paren
l_int|19
comma
id|dar
)paren
id|GSETSPR
c_func
(paren
l_int|22
comma
id|dec
)paren
id|GSETSPR
c_func
(paren
l_int|25
comma
id|sdr1
)paren
id|GSETSPR
c_func
(paren
l_int|26
comma
id|srr0
)paren
id|GSETSPR
c_func
(paren
l_int|27
comma
id|srr1
)paren
id|GSETSPR
c_func
(paren
l_int|272
comma
id|sprg0
)paren
id|GSETSPR
c_func
(paren
l_int|273
comma
id|sprg1
)paren
id|GSETSPR
c_func
(paren
l_int|274
comma
id|sprg2
)paren
id|GSETSPR
c_func
(paren
l_int|275
comma
id|sprg3
)paren
id|GSETSPR
c_func
(paren
l_int|282
comma
id|ear
)paren
id|GSETSPR
c_func
(paren
l_int|287
comma
id|pvr
)paren
macro_line|#ifndef CONFIG_8xx
id|GSETSPR
c_func
(paren
l_int|528
comma
id|bat0u
)paren
id|GSETSPR
c_func
(paren
l_int|529
comma
id|bat0l
)paren
id|GSETSPR
c_func
(paren
l_int|530
comma
id|bat1u
)paren
id|GSETSPR
c_func
(paren
l_int|531
comma
id|bat1l
)paren
id|GSETSPR
c_func
(paren
l_int|532
comma
id|bat2u
)paren
id|GSETSPR
c_func
(paren
l_int|533
comma
id|bat2l
)paren
id|GSETSPR
c_func
(paren
l_int|534
comma
id|bat3u
)paren
id|GSETSPR
c_func
(paren
l_int|535
comma
id|bat3l
)paren
id|GSETSPR
c_func
(paren
l_int|1008
comma
id|hid0
)paren
id|GSETSPR
c_func
(paren
l_int|1009
comma
id|hid1
)paren
id|GSETSPR
c_func
(paren
l_int|1010
comma
id|iabr
)paren
id|GSETSPR
c_func
(paren
l_int|1013
comma
id|dabr
)paren
id|GSETSPR
c_func
(paren
l_int|1023
comma
id|pir
)paren
macro_line|#else
id|GSETSPR
c_func
(paren
l_int|144
comma
id|cmpa
)paren
id|GSETSPR
c_func
(paren
l_int|145
comma
id|cmpb
)paren
id|GSETSPR
c_func
(paren
l_int|146
comma
id|cmpc
)paren
id|GSETSPR
c_func
(paren
l_int|147
comma
id|cmpd
)paren
id|GSETSPR
c_func
(paren
l_int|158
comma
id|ictrl
)paren
macro_line|#endif
DECL|function|get_sr
r_static
r_inline
r_int
id|get_sr
c_func
(paren
r_int
id|n
)paren
(brace
r_int
id|ret
suffix:semicolon
id|asm
(paren
l_string|&quot; mfsrin %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|n
op_lshift
l_int|28
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|set_sr
r_static
r_inline
r_void
id|set_sr
c_func
(paren
r_int
id|n
comma
r_int
id|val
)paren
(brace
id|asm
(paren
l_string|&quot;mtsrin %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|n
op_lshift
l_int|28
)paren
)paren
suffix:semicolon
)brace
DECL|function|store_inst
r_static
r_inline
r_void
id|store_inst
c_func
(paren
r_void
op_star
id|p
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;dcbst 0,%0; sync; icbi 0,%0; isync&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|cflush
r_static
r_inline
r_void
id|cflush
c_func
(paren
r_void
op_star
id|p
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;dcbf 0,%0; icbi 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|cinval
r_static
r_inline
r_void
id|cinval
c_func
(paren
r_void
op_star
id|p
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;dcbi 0,%0; icbi 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
)paren
suffix:semicolon
)brace
eof
