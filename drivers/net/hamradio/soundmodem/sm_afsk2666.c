multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;sm_afsk2666.c  -- soundcard radio modem driver, 2666 baud AFSK modem&n; *&n; *&t;Copyright (C) 1997  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; */
macro_line|#include &quot;sm.h&quot;
macro_line|#include &quot;sm_tbl_afsk2666.h&quot;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|demod_state_afsk26
r_struct
id|demod_state_afsk26
(brace
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|member|descram
r_int
r_int
id|descram
suffix:semicolon
DECL|member|dem_sum
r_int
id|dem_sum
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|dem_sum_mean
r_int
id|dem_sum_mean
suffix:semicolon
DECL|member|dem_cnt
r_int
id|dem_cnt
suffix:semicolon
DECL|member|bit_pll
r_int
r_int
id|bit_pll
suffix:semicolon
DECL|member|last_sample
r_int
r_char
id|last_sample
suffix:semicolon
DECL|member|dcd_shreg
r_int
r_int
id|dcd_shreg
suffix:semicolon
DECL|member|dcd_sum0
DECL|member|dcd_sum1
DECL|member|dcd_sum2
r_int
id|dcd_sum0
comma
id|dcd_sum1
comma
id|dcd_sum2
suffix:semicolon
DECL|member|dcd_time
r_int
r_int
id|dcd_time
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mod_state_afsk26
r_struct
id|mod_state_afsk26
(brace
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|member|scram
r_int
r_int
id|scram
suffix:semicolon
DECL|member|bit_pll
r_int
r_int
id|bit_pll
suffix:semicolon
DECL|member|phinc
r_int
r_int
id|phinc
suffix:semicolon
DECL|member|tx_seq
r_int
r_int
id|tx_seq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|DESCRAM_TAP1
mdefine_line|#define DESCRAM_TAP1 0x20000
DECL|macro|DESCRAM_TAP2
mdefine_line|#define DESCRAM_TAP2 0x01000
DECL|macro|DESCRAM_TAP3
mdefine_line|#define DESCRAM_TAP3 0x00001
DECL|macro|DESCRAM_TAPSH1
mdefine_line|#define DESCRAM_TAPSH1 17
DECL|macro|DESCRAM_TAPSH2
mdefine_line|#define DESCRAM_TAPSH2 12
DECL|macro|DESCRAM_TAPSH3
mdefine_line|#define DESCRAM_TAPSH3 0
DECL|macro|SCRAM_TAP1
mdefine_line|#define SCRAM_TAP1 0x20000 /* X^17 */
DECL|macro|SCRAM_TAPN
mdefine_line|#define SCRAM_TAPN 0x00021 /* X^0+X^5 */
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_2666_u8
r_static
r_void
id|modulator_2666_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_afsk26
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_afsk26
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;scram
op_assign
(paren
(paren
id|st-&gt;scram
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;scram
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;scram
op_xor_assign
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;scram
op_amp
(paren
id|SCRAM_TAP1
op_lshift
l_int|1
)paren
)paren
id|st-&gt;scram
op_xor_assign
id|SCRAM_TAPN
op_lshift
l_int|1
suffix:semicolon
id|st-&gt;phinc
op_assign
id|afsk26_carfreq
(braket
op_logical_neg
(paren
id|st-&gt;scram
op_amp
(paren
id|SCRAM_TAP1
op_lshift
l_int|2
)paren
)paren
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|6
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
id|OFFSCOS
c_func
(paren
id|st-&gt;bit_pll
)paren
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|st-&gt;phinc
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_2666_s16
r_static
r_void
id|modulator_2666_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_afsk26
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_afsk26
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;scram
op_assign
(paren
(paren
id|st-&gt;scram
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;scram
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;scram
op_xor_assign
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;scram
op_amp
(paren
id|SCRAM_TAP1
op_lshift
l_int|1
)paren
)paren
id|st-&gt;scram
op_xor_assign
id|SCRAM_TAPN
op_lshift
l_int|1
suffix:semicolon
id|st-&gt;phinc
op_assign
id|afsk26_carfreq
(braket
op_logical_neg
(paren
id|st-&gt;scram
op_amp
(paren
id|SCRAM_TAP1
op_lshift
l_int|2
)paren
)paren
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|6
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
id|COS
c_func
(paren
id|st-&gt;bit_pll
)paren
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|st-&gt;phinc
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|convolution12_u8
r_static
id|__inline__
r_int
id|convolution12_u8
c_func
(paren
r_const
r_int
r_char
op_star
id|st
comma
r_const
r_int
op_star
id|coeff
comma
r_int
id|csum
)paren
(brace
r_int
id|sum
op_assign
op_minus
l_int|0x80
op_star
id|csum
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
l_int|0
)braket
op_star
id|coeff
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|1
)braket
op_star
id|coeff
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|2
)braket
op_star
id|coeff
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|3
)braket
op_star
id|coeff
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|4
)braket
op_star
id|coeff
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|5
)braket
op_star
id|coeff
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|6
)braket
op_star
id|coeff
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|7
)braket
op_star
id|coeff
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|8
)braket
op_star
id|coeff
(braket
l_int|8
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|9
)braket
op_star
id|coeff
(braket
l_int|9
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|10
)braket
op_star
id|coeff
(braket
l_int|10
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|11
)braket
op_star
id|coeff
(braket
l_int|11
)braket
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
DECL|function|convolution12_s16
r_static
id|__inline__
r_int
id|convolution12_s16
c_func
(paren
r_const
r_int
op_star
id|st
comma
r_const
r_int
op_star
id|coeff
comma
r_int
id|csum
)paren
(brace
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
l_int|0
)braket
op_star
id|coeff
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|1
)braket
op_star
id|coeff
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|2
)braket
op_star
id|coeff
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|3
)braket
op_star
id|coeff
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|4
)braket
op_star
id|coeff
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|5
)braket
op_star
id|coeff
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|6
)braket
op_star
id|coeff
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|7
)braket
op_star
id|coeff
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|8
)braket
op_star
id|coeff
(braket
l_int|8
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|9
)braket
op_star
id|coeff
(braket
l_int|9
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|10
)braket
op_star
id|coeff
(braket
l_int|10
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|11
)braket
op_star
id|coeff
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|sum
op_rshift_assign
l_int|8
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
macro_line|#if 0
r_static
r_int
id|binexp
c_func
(paren
r_int
r_int
id|i
)paren
(brace
r_int
id|ret
op_assign
l_int|31
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0x10000LU
)paren
(brace
id|i
op_lshift_assign
l_int|16
suffix:semicolon
id|ret
op_sub_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0x1000000LU
)paren
(brace
id|i
op_lshift_assign
l_int|8
suffix:semicolon
id|ret
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0x10000000LU
)paren
(brace
id|i
op_lshift_assign
l_int|4
suffix:semicolon
id|ret
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0x40000000LU
)paren
(brace
id|i
op_lshift_assign
l_int|2
suffix:semicolon
id|ret
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0x80000000LU
)paren
id|ret
op_sub_assign
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_const
id|sqrt_tab
(braket
l_int|16
)braket
op_assign
(brace
l_int|00000
comma
l_int|16384
comma
l_int|23170
comma
l_int|28378
comma
l_int|32768
comma
l_int|36636
comma
l_int|40132
comma
l_int|43348
comma
l_int|46341
comma
l_int|49152
comma
l_int|51811
comma
l_int|54340
comma
l_int|56756
comma
l_int|59073
comma
l_int|61303
comma
l_int|63455
)brace
suffix:semicolon
r_static
r_int
r_int
id|int_sqrt_approx
c_func
(paren
r_int
r_int
id|i
)paren
(brace
r_int
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|16
)paren
r_return
id|sqrt_tab
(braket
id|i
)braket
op_rshift
l_int|14
suffix:semicolon
id|j
op_assign
id|binexp
c_func
(paren
id|i
)paren
op_rshift
l_int|1
suffix:semicolon
id|i
op_rshift_assign
(paren
id|j
op_star
l_int|2
op_minus
l_int|2
)paren
suffix:semicolon
r_return
(paren
id|sqrt_tab
(braket
id|i
op_amp
l_int|0xf
)braket
op_lshift
id|j
)paren
op_rshift
l_int|15
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|est_pwr
r_extern
r_int
r_int
id|est_pwr
c_func
(paren
r_int
id|i
comma
r_int
id|q
)paren
(brace
r_int
r_int
id|ui
op_assign
id|abs
c_func
(paren
id|i
)paren
suffix:semicolon
r_int
r_int
id|uq
op_assign
id|abs
c_func
(paren
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uq
OG
id|ui
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|ui
suffix:semicolon
id|ui
op_assign
id|uq
suffix:semicolon
id|uq
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uq
OG
(paren
id|ui
op_rshift
l_int|1
)paren
)paren
r_return
l_int|7
op_star
(paren
id|ui
op_rshift
l_int|3
)paren
op_plus
l_int|9
op_star
(paren
id|uq
op_rshift
l_int|4
)paren
suffix:semicolon
r_else
r_return
id|ui
op_plus
(paren
id|uq
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demod_one_sample
r_static
r_void
id|demod_one_sample
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_struct
id|demod_state_afsk26
op_star
id|st
comma
r_int
id|curval
comma
r_int
id|loi
comma
r_int
id|loq
comma
r_int
id|hii
comma
r_int
id|hiq
)paren
(brace
r_static
r_const
r_int
id|pll_corr
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|0xa00
comma
l_int|0xa00
)brace
suffix:semicolon
r_int
r_char
id|curbit
suffix:semicolon
r_int
r_int
id|descx
suffix:semicolon
r_int
id|val
suffix:semicolon
multiline_comment|/* &n;&t; * estimate power&n;&t; */
id|val
op_assign
id|est_pwr
c_func
(paren
id|hii
comma
id|hiq
)paren
op_minus
id|est_pwr
c_func
(paren
id|loi
comma
id|loq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * estimate center value&n;&t; */
id|st-&gt;dem_sum
(braket
l_int|0
)braket
op_add_assign
id|val
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
op_increment
id|st-&gt;dem_cnt
)paren
op_ge
l_int|256
)paren
(brace
id|st-&gt;dem_cnt
op_assign
l_int|0
suffix:semicolon
id|st-&gt;dem_sum_mean
op_assign
(paren
id|st-&gt;dem_sum
(braket
l_int|0
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|1
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|2
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|3
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|4
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|5
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|6
)braket
op_plus
id|st-&gt;dem_sum
(braket
l_int|7
)braket
)paren
op_rshift
l_int|3
suffix:semicolon
id|memmove
c_func
(paren
id|st-&gt;dem_sum
op_plus
l_int|1
comma
id|st-&gt;dem_sum
comma
r_sizeof
(paren
id|st-&gt;dem_sum
)paren
op_minus
r_sizeof
(paren
id|st-&gt;dem_sum
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|st-&gt;dem_sum
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * decision and bit clock regen&n;&t; */
id|val
op_sub_assign
id|st-&gt;dem_sum_mean
suffix:semicolon
id|diag_add
c_func
(paren
id|sm
comma
id|curval
comma
id|val
)paren
suffix:semicolon
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x1555
suffix:semicolon
id|curbit
op_assign
(paren
id|val
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;last_sample
op_xor
id|curbit
)paren
(brace
id|st-&gt;dcd_shreg
op_or_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
id|st-&gt;bit_pll
OL
(paren
l_int|0x8000
op_plus
l_int|0x1555
)paren
)braket
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
l_int|4
op_star
id|hweight8
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x1e
)paren
op_minus
id|hweight16
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0xfe00
)paren
suffix:semicolon
)brace
id|st-&gt;last_sample
op_assign
id|curbit
suffix:semicolon
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|curbit
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_decrement
id|st-&gt;dcd_time
)paren
op_le
l_int|0
)paren
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
(paren
id|st-&gt;dcd_sum0
op_plus
id|st-&gt;dcd_sum1
op_plus
id|st-&gt;dcd_sum2
)paren
OL
l_int|0
)paren
suffix:semicolon
id|st-&gt;dcd_sum2
op_assign
id|st-&gt;dcd_sum1
suffix:semicolon
id|st-&gt;dcd_sum1
op_assign
id|st-&gt;dcd_sum0
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* slight bias */
id|st-&gt;dcd_time
op_assign
l_int|400
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;bit_pll
op_ge
l_int|0x10000
)paren
(brace
id|st-&gt;bit_pll
op_and_assign
l_int|0xffffu
suffix:semicolon
id|st-&gt;descram
op_assign
(paren
id|st-&gt;descram
op_lshift
l_int|1
)paren
op_or
id|curbit
suffix:semicolon
id|descx
op_assign
id|st-&gt;descram
op_xor
(paren
id|st-&gt;descram
op_rshift
l_int|1
)paren
suffix:semicolon
id|descx
op_xor_assign
(paren
(paren
id|descx
op_rshift
id|DESCRAM_TAPSH1
)paren
op_xor
(paren
id|descx
op_rshift
id|DESCRAM_TAPSH2
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
op_logical_neg
(paren
id|descx
op_amp
l_int|1
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
(brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;shreg
op_rshift
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_assign
l_int|0x10000
suffix:semicolon
)brace
id|diag_trigger
c_func
(paren
id|sm
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_2666_u8
r_static
r_void
id|demodulator_2666_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|demod_state_afsk26
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk26
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
id|demod_one_sample
c_func
(paren
id|sm
comma
id|st
comma
(paren
op_star
id|buf
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|0
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_0_0
)paren
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|0
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_0_0
)paren
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|1
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_0_1
)paren
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|1
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_0_1
)paren
)paren
suffix:semicolon
id|demod_one_sample
c_func
(paren
id|sm
comma
id|st
comma
(paren
op_star
id|buf
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|0
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_1_0
)paren
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|0
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_1_0
)paren
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|1
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_1_1
)paren
comma
id|convolution12_u8
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|1
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_1_1
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_2666_s16
r_static
r_void
id|demodulator_2666_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_const
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|demod_state_afsk26
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk26
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
id|demod_one_sample
c_func
(paren
id|sm
comma
id|st
comma
op_star
id|buf
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|0
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_0_0
)paren
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|0
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_0_0
)paren
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|1
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_0_1
)paren
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|0
)braket
(braket
l_int|1
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_0_1
)paren
)paren
suffix:semicolon
id|demod_one_sample
c_func
(paren
id|sm
comma
id|st
comma
op_star
id|buf
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|0
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_1_0
)paren
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|0
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_1_0
)paren
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|1
)braket
dot
id|i
comma
id|AFSK26_DEM_SUM_I_1_1
)paren
comma
id|convolution12_s16
c_func
(paren
id|buf
comma
id|afsk26_dem_tables
(braket
l_int|1
)braket
(braket
l_int|1
)braket
dot
id|q
comma
id|AFSK26_DEM_SUM_Q_1_1
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demod_init_2666
r_static
r_void
id|demod_init_2666
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
r_struct
id|demod_state_afsk26
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk26
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
id|st-&gt;dcd_time
op_assign
l_int|400
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|sm_afsk2666_tx
r_const
r_struct
id|modem_tx_info
id|sm_afsk2666_tx
op_assign
(brace
l_string|&quot;afsk2666&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_afsk26
)paren
comma
id|AFSK26_SAMPLERATE
comma
l_int|2666
comma
id|modulator_2666_u8
comma
id|modulator_2666_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_afsk2666_rx
r_const
r_struct
id|modem_rx_info
id|sm_afsk2666_rx
op_assign
(brace
l_string|&quot;afsk2666&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_afsk26
)paren
comma
id|AFSK26_SAMPLERATE
comma
l_int|2666
comma
l_int|12
comma
l_int|6
comma
id|demodulator_2666_u8
comma
id|demodulator_2666_s16
comma
id|demod_init_2666
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
eof
