multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;sm_afsk2400_7.c  -- soundcard radio modem driver, 2400 baud AFSK modem&n; *&n; *&t;Copyright (C) 1996  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; */
multiline_comment|/*&n; * This driver is intended to be compatible with TCM3105 modems&n; * overclocked to 7.3728MHz. The mark and space frequencies therefore&n; * lie at 3658 and 1996 Hz.&n; * Note that I do _not_ recommend the building of such links, I provide&n; * this only for the users who live in the coverage area of such&n; * a &quot;legacy&quot; link.&n; */
macro_line|#include &quot;sm.h&quot;
macro_line|#include &quot;sm_tbl_afsk2400_7.h&quot;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|demod_state_afsk24
r_struct
id|demod_state_afsk24
(brace
DECL|member|shreg
r_int
r_int
id|shreg
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
DECL|member|last_rxbit
r_int
r_char
id|last_rxbit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mod_state_afsk24
r_struct
id|mod_state_afsk24
(brace
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|member|tx_bit
r_int
r_char
id|tx_bit
suffix:semicolon
DECL|member|bit_pll
r_int
r_int
id|bit_pll
suffix:semicolon
DECL|member|tx_seq
r_int
r_int
id|tx_seq
suffix:semicolon
DECL|member|phinc
r_int
r_int
id|phinc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|dds_inc
r_static
r_const
r_int
id|dds_inc
(braket
l_int|2
)braket
op_assign
(brace
id|AFSK24_TX_FREQ_LO
op_star
l_int|0x10000
op_div
id|AFSK24_SAMPLERATE
comma
id|AFSK24_TX_FREQ_HI
op_star
l_int|0x10000
op_div
id|AFSK24_SAMPLERATE
)brace
suffix:semicolon
DECL|function|modulator_2400_u8
r_static
r_void
id|modulator_2400_u8
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
id|mod_state_afsk24
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_afsk24
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
id|st-&gt;tx_seq
OL
l_int|0x5555
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
id|st-&gt;tx_bit
op_assign
(paren
id|st-&gt;tx_bit
op_xor
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
)paren
op_amp
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;phinc
op_assign
id|dds_inc
(braket
id|st-&gt;tx_bit
op_amp
l_int|1
)braket
suffix:semicolon
)brace
id|st-&gt;tx_seq
op_add_assign
l_int|0x5555
suffix:semicolon
id|st-&gt;tx_seq
op_and_assign
l_int|0xffff
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
DECL|function|modulator_2400_s16
r_static
r_void
id|modulator_2400_s16
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
id|mod_state_afsk24
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_afsk24
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
id|st-&gt;tx_seq
OL
l_int|0x5555
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
id|st-&gt;tx_bit
op_assign
(paren
id|st-&gt;tx_bit
op_xor
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
)paren
op_amp
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;phinc
op_assign
id|dds_inc
(braket
id|st-&gt;tx_bit
op_amp
l_int|1
)braket
suffix:semicolon
)brace
id|st-&gt;tx_seq
op_add_assign
l_int|0x5555
suffix:semicolon
id|st-&gt;tx_seq
op_and_assign
l_int|0xffff
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
DECL|function|convolution14_u8
r_static
id|__inline__
r_int
id|convolution14_u8
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
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|12
)braket
op_star
id|coeff
(braket
l_int|12
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|13
)braket
op_star
id|coeff
(braket
l_int|13
)braket
)paren
suffix:semicolon
id|sum
op_rshift_assign
l_int|7
suffix:semicolon
r_return
id|sum
op_star
id|sum
suffix:semicolon
)brace
DECL|function|convolution14_s16
r_static
id|__inline__
r_int
id|convolution14_s16
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
op_add_assign
(paren
id|st
(braket
op_minus
l_int|12
)braket
op_star
id|coeff
(braket
l_int|12
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|13
)braket
op_star
id|coeff
(braket
l_int|13
)braket
)paren
suffix:semicolon
id|sum
op_rshift_assign
l_int|15
suffix:semicolon
r_return
id|sum
op_star
id|sum
suffix:semicolon
)brace
DECL|function|do_filter_2400_u8
r_static
id|__inline__
r_int
id|do_filter_2400_u8
c_func
(paren
r_const
r_int
r_char
op_star
id|buf
)paren
(brace
r_int
id|sum
op_assign
id|convolution14_u8
c_func
(paren
id|buf
comma
id|afsk24_tx_lo_i
comma
id|SUM_AFSK24_TX_LO_I
)paren
suffix:semicolon
id|sum
op_add_assign
id|convolution14_u8
c_func
(paren
id|buf
comma
id|afsk24_tx_lo_q
comma
id|SUM_AFSK24_TX_LO_Q
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution14_u8
c_func
(paren
id|buf
comma
id|afsk24_tx_hi_i
comma
id|SUM_AFSK24_TX_HI_I
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution14_u8
c_func
(paren
id|buf
comma
id|afsk24_tx_hi_q
comma
id|SUM_AFSK24_TX_HI_Q
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
DECL|function|do_filter_2400_s16
r_static
id|__inline__
r_int
id|do_filter_2400_s16
c_func
(paren
r_const
r_int
op_star
id|buf
)paren
(brace
r_int
id|sum
op_assign
id|convolution14_s16
c_func
(paren
id|buf
comma
id|afsk24_tx_lo_i
comma
id|SUM_AFSK24_TX_LO_I
)paren
suffix:semicolon
id|sum
op_add_assign
id|convolution14_s16
c_func
(paren
id|buf
comma
id|afsk24_tx_lo_q
comma
id|SUM_AFSK24_TX_LO_Q
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution14_s16
c_func
(paren
id|buf
comma
id|afsk24_tx_hi_i
comma
id|SUM_AFSK24_TX_HI_I
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution14_s16
c_func
(paren
id|buf
comma
id|afsk24_tx_hi_q
comma
id|SUM_AFSK24_TX_HI_Q
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_2400_u8
r_static
r_void
id|demodulator_2400_u8
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
id|demod_state_afsk24
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk24
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|sum
suffix:semicolon
r_int
r_char
id|newsample
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
id|sum
op_assign
id|do_filter_2400_u8
c_func
(paren
id|buf
)paren
suffix:semicolon
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|AFSK24_BITPLL_INC
suffix:semicolon
id|newsample
op_assign
(paren
id|sum
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;last_sample
op_xor
id|newsample
)paren
(brace
id|st-&gt;last_sample
op_assign
id|newsample
suffix:semicolon
id|st-&gt;dcd_shreg
op_or_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;bit_pll
OL
(paren
l_int|0x8000
op_plus
id|AFSK24_BITPLL_INC
op_div
l_int|2
)paren
)paren
id|st-&gt;bit_pll
op_add_assign
id|AFSK24_BITPLL_INC
op_div
l_int|2
suffix:semicolon
r_else
id|st-&gt;bit_pll
op_sub_assign
id|AFSK24_BITPLL_INC
op_div
l_int|2
suffix:semicolon
id|j
op_assign
multiline_comment|/* 2 * */
id|hweight8
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x1c
)paren
op_minus
id|hweight16
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x1e0
)paren
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
id|j
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;last_sample
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
l_int|120
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
l_int|0xffff
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
id|st-&gt;last_rxbit
op_xor
id|st-&gt;last_sample
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
id|st-&gt;last_rxbit
op_assign
id|st-&gt;last_sample
suffix:semicolon
id|diag_trigger
c_func
(paren
id|sm
)paren
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
)brace
id|diag_add
c_func
(paren
id|sm
comma
(paren
(paren
(paren
r_int
)paren
op_star
id|buf
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
comma
id|sum
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_2400_s16
r_static
r_void
id|demodulator_2400_s16
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
id|demod_state_afsk24
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk24
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|sum
suffix:semicolon
r_int
r_char
id|newsample
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
id|sum
op_assign
id|do_filter_2400_s16
c_func
(paren
id|buf
)paren
suffix:semicolon
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|AFSK24_BITPLL_INC
suffix:semicolon
id|newsample
op_assign
(paren
id|sum
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;last_sample
op_xor
id|newsample
)paren
(brace
id|st-&gt;last_sample
op_assign
id|newsample
suffix:semicolon
id|st-&gt;dcd_shreg
op_or_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;bit_pll
OL
(paren
l_int|0x8000
op_plus
id|AFSK24_BITPLL_INC
op_div
l_int|2
)paren
)paren
id|st-&gt;bit_pll
op_add_assign
id|AFSK24_BITPLL_INC
op_div
l_int|2
suffix:semicolon
r_else
id|st-&gt;bit_pll
op_sub_assign
id|AFSK24_BITPLL_INC
op_div
l_int|2
suffix:semicolon
id|j
op_assign
multiline_comment|/* 2 * */
id|hweight8
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x1c
)paren
op_minus
id|hweight16
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x1e0
)paren
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
id|j
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;last_sample
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
l_int|120
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
l_int|0xffff
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
id|st-&gt;last_rxbit
op_xor
id|st-&gt;last_sample
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
id|st-&gt;last_rxbit
op_assign
id|st-&gt;last_sample
suffix:semicolon
id|diag_trigger
c_func
(paren
id|sm
)paren
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
)brace
id|diag_add
c_func
(paren
id|sm
comma
op_star
id|buf
comma
id|sum
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demod_init_2400
r_static
r_void
id|demod_init_2400
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
r_struct
id|demod_state_afsk24
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk24
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
id|st-&gt;dcd_time
op_assign
l_int|120
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|sm_afsk2400_7_tx
r_const
r_struct
id|modem_tx_info
id|sm_afsk2400_7_tx
op_assign
(brace
l_string|&quot;afsk2400_7&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_afsk24
)paren
comma
id|AFSK24_SAMPLERATE
comma
l_int|2400
comma
id|modulator_2400_u8
comma
id|modulator_2400_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_afsk2400_7_rx
r_const
r_struct
id|modem_rx_info
id|sm_afsk2400_7_rx
op_assign
(brace
l_string|&quot;afsk2400_7&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_afsk24
)paren
comma
id|AFSK24_SAMPLERATE
comma
l_int|2400
comma
l_int|14
comma
id|AFSK24_SAMPLERATE
op_div
l_int|2400
comma
id|demodulator_2400_u8
comma
id|demodulator_2400_s16
comma
id|demod_init_2400
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
eof
