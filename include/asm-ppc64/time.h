multiline_comment|/*&n; * Common time prototypes and such for all ppc machines.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) to merge&n; * Paul Mackerras&squot; version and mine for PReP and Pmac.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __PPC64_TIME_H
DECL|macro|__PPC64_TIME_H
mdefine_line|#define __PPC64_TIME_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/HvCall.h&gt;
multiline_comment|/* time.c */
r_extern
r_int
r_int
id|tb_ticks_per_jiffy
suffix:semicolon
r_extern
r_int
r_int
id|tb_ticks_per_usec
suffix:semicolon
r_extern
r_int
r_int
id|tb_ticks_per_sec
suffix:semicolon
r_extern
r_int
r_int
id|tb_to_xs
suffix:semicolon
r_extern
r_int
id|tb_to_us
suffix:semicolon
r_extern
r_int
r_int
id|tb_last_stamp
suffix:semicolon
r_struct
id|rtc_time
suffix:semicolon
r_extern
r_void
id|to_tm
c_func
(paren
r_int
id|tim
comma
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
r_extern
id|time_t
id|last_rtc_update
suffix:semicolon
multiline_comment|/*&n; * By putting all of this stuff into a single struct we &n; * reduce the number of cache lines touched by do_gettimeofday.&n; * Both by collecting all of the data in one cache line and&n; * by touching only one TOC entry&n; */
DECL|struct|gettimeofday_vars
r_struct
id|gettimeofday_vars
(brace
DECL|member|tb_to_xs
r_int
r_int
id|tb_to_xs
suffix:semicolon
DECL|member|stamp_xsec
r_int
r_int
id|stamp_xsec
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gettimeofday_struct
r_struct
id|gettimeofday_struct
(brace
DECL|member|tb_orig_stamp
r_int
r_int
id|tb_orig_stamp
suffix:semicolon
DECL|member|tb_ticks_per_sec
r_int
r_int
id|tb_ticks_per_sec
suffix:semicolon
DECL|member|vars
r_struct
id|gettimeofday_vars
id|vars
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|varp
r_struct
id|gettimeofday_vars
op_star
r_volatile
id|varp
suffix:semicolon
DECL|member|var_idx
r_int
id|var_idx
suffix:semicolon
DECL|member|tb_to_us
r_int
id|tb_to_us
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|div_result
r_struct
id|div_result
(brace
DECL|member|result_high
r_int
r_int
id|result_high
suffix:semicolon
DECL|member|result_low
r_int
r_int
id|result_low
suffix:semicolon
)brace
suffix:semicolon
r_int
id|via_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_tb
r_static
id|__inline__
r_int
r_int
id|get_tb
c_func
(paren
r_void
)paren
(brace
r_return
id|mftb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Accessor functions for the decrementer register. */
DECL|function|get_dec
r_static
id|__inline__
r_int
r_int
id|get_dec
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|mfspr
c_func
(paren
id|SPRN_DEC
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_dec
r_static
id|__inline__
r_void
id|set_dec
c_func
(paren
r_int
id|val
)paren
(brace
macro_line|#ifdef CONFIG_PPC_ISERIES
r_struct
id|paca_struct
op_star
id|lpaca
op_assign
id|get_paca
c_func
(paren
)paren
suffix:semicolon
r_int
id|cur_dec
suffix:semicolon
r_if
c_cond
(paren
id|lpaca-&gt;lppaca.shared_proc
)paren
(brace
id|lpaca-&gt;lppaca.virtual_decr
op_assign
id|val
suffix:semicolon
id|cur_dec
op_assign
id|get_dec
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_dec
OG
id|val
)paren
id|HvCall_setVirtualDecr
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|mtspr
c_func
(paren
id|SPRN_DEC
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|tb_ticks_since
r_static
r_inline
r_int
r_int
id|tb_ticks_since
c_func
(paren
r_int
r_int
id|tstamp
)paren
(brace
r_return
id|get_tb
c_func
(paren
)paren
op_minus
id|tstamp
suffix:semicolon
)brace
DECL|macro|mulhwu
mdefine_line|#define mulhwu(x,y) &bslash;&n;({unsigned z; asm (&quot;mulhwu %0,%1,%2&quot; : &quot;=r&quot; (z) : &quot;r&quot; (x), &quot;r&quot; (y)); z;})
DECL|macro|mulhdu
mdefine_line|#define mulhdu(x,y) &bslash;&n;({unsigned long z; asm (&quot;mulhdu %0,%1,%2&quot; : &quot;=r&quot; (z) : &quot;r&quot; (x), &quot;r&quot; (y)); z;})
r_int
id|mulhwu_scale_factor
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|div128_by_32
c_func
(paren
r_int
r_int
id|dividend_high
comma
r_int
r_int
id|dividend_low
comma
r_int
id|divisor
comma
r_struct
id|div_result
op_star
id|dr
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __PPC64_TIME_H */
eof
