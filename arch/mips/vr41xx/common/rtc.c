multiline_comment|/*&n; *  rtc.c, RTC(has only timer function) routines for NEC VR4100 series.&n; *&n; *  Copyright (C) 2003  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|variable|rtc1_base
r_static
r_uint32
id|rtc1_base
suffix:semicolon
DECL|variable|rtc2_base
r_static
r_uint32
id|rtc2_base
suffix:semicolon
DECL|variable|previous_elapsedtime
r_static
r_uint64
id|previous_elapsedtime
suffix:semicolon
DECL|variable|remainder_per_sec
r_static
r_int
r_int
id|remainder_per_sec
suffix:semicolon
DECL|variable|cycles_per_sec
r_static
r_int
r_int
id|cycles_per_sec
suffix:semicolon
DECL|variable|cycles_per_jiffy
r_static
r_int
r_int
id|cycles_per_jiffy
suffix:semicolon
DECL|variable|epoch_time
r_static
r_int
r_int
id|epoch_time
suffix:semicolon
DECL|macro|CYCLES_PER_JIFFY
mdefine_line|#define CYCLES_PER_JIFFY&t;(CLOCK_TICK_RATE / HZ)
DECL|macro|REMAINDER_PER_SEC
mdefine_line|#define REMAINDER_PER_SEC&t;(CLOCK_TICK_RATE - (CYCLES_PER_JIFFY * HZ))
DECL|macro|CYCLES_PER_100USEC
mdefine_line|#define CYCLES_PER_100USEC&t;((CLOCK_TICK_RATE + (10000 / 2)) / 10000)
DECL|macro|ETIMELREG_TYPE1
mdefine_line|#define ETIMELREG_TYPE1&t;&t;KSEG1ADDR(0x0b0000c0)
DECL|macro|TCLKLREG_TYPE1
mdefine_line|#define TCLKLREG_TYPE1&t;&t;KSEG1ADDR(0x0b0001c0)
DECL|macro|ETIMELREG_TYPE2
mdefine_line|#define ETIMELREG_TYPE2&t;&t;KSEG1ADDR(0x0f000100)
DECL|macro|TCLKLREG_TYPE2
mdefine_line|#define TCLKLREG_TYPE2&t;&t;KSEG1ADDR(0x0f000120)
multiline_comment|/* RTC 1 registers */
DECL|macro|ETIMELREG
mdefine_line|#define ETIMELREG&t;&t;0x00
DECL|macro|ETIMEMREG
mdefine_line|#define ETIMEMREG&t;&t;0x02
DECL|macro|ETIMEHREG
mdefine_line|#define ETIMEHREG&t;&t;0x04
multiline_comment|/* RFU */
DECL|macro|ECMPLREG
mdefine_line|#define ECMPLREG&t;&t;0x08
DECL|macro|ECMPMREG
mdefine_line|#define ECMPMREG&t;&t;0x0a
DECL|macro|ECMPHREG
mdefine_line|#define ECMPHREG&t;&t;0x0c
multiline_comment|/* RFU */
DECL|macro|RTCL1LREG
mdefine_line|#define RTCL1LREG&t;&t;0x10
DECL|macro|RTCL1HREG
mdefine_line|#define RTCL1HREG&t;&t;0x12
DECL|macro|RTCL1CNTLREG
mdefine_line|#define RTCL1CNTLREG&t;&t;0x14
DECL|macro|RTCL1CNTHREG
mdefine_line|#define RTCL1CNTHREG&t;&t;0x16
DECL|macro|RTCL2LREG
mdefine_line|#define RTCL2LREG&t;&t;0x18
DECL|macro|RTCL2HREG
mdefine_line|#define RTCL2HREG&t;&t;0x1a
DECL|macro|RTCL2CNTLREG
mdefine_line|#define RTCL2CNTLREG&t;&t;0x1c
DECL|macro|RTCL2CNTHREG
mdefine_line|#define RTCL2CNTHREG&t;&t;0x1e
multiline_comment|/* RTC 2 registers */
DECL|macro|TCLKLREG
mdefine_line|#define TCLKLREG&t;&t;0x00
DECL|macro|TCLKHREG
mdefine_line|#define TCLKHREG&t;&t;0x02
DECL|macro|TCLKCNTLREG
mdefine_line|#define TCLKCNTLREG&t;&t;0x04
DECL|macro|TCLKCNTHREG
mdefine_line|#define TCLKCNTHREG&t;&t;0x06
multiline_comment|/* RFU */
DECL|macro|RTCINTREG
mdefine_line|#define RTCINTREG&t;&t;0x1e
DECL|macro|TCLOCK_INT
mdefine_line|#define TCLOCK_INT&t;&t;0x08
DECL|macro|RTCLONG2_INT
mdefine_line|#define RTCLONG2_INT&t;&t;0x04
DECL|macro|RTCLONG1_INT
mdefine_line|#define RTCLONG1_INT&t;&t;0x02
DECL|macro|ELAPSEDTIME_INT
mdefine_line|#define ELAPSEDTIME_INT&t;0x01
DECL|macro|read_rtc1
mdefine_line|#define read_rtc1(offset)&t;readw(rtc1_base + (offset))
DECL|macro|write_rtc1
mdefine_line|#define write_rtc1(val, offset)&t;writew((val), rtc1_base + (offset))
DECL|macro|read_rtc2
mdefine_line|#define read_rtc2(offset)&t;readw(rtc2_base + (offset))
DECL|macro|write_rtc2
mdefine_line|#define write_rtc2(val, offset)&t;writew((val), rtc2_base + (offset))
DECL|function|read_elapsedtime_counter
r_static
r_inline
r_uint64
id|read_elapsedtime_counter
c_func
(paren
r_void
)paren
(brace
r_uint64
id|first
comma
id|second
suffix:semicolon
r_uint32
id|first_mid
comma
id|first_low
suffix:semicolon
r_uint32
id|second_mid
comma
id|second_low
suffix:semicolon
r_do
(brace
id|first_low
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|ETIMELREG
)paren
suffix:semicolon
id|first_mid
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|ETIMEMREG
)paren
suffix:semicolon
id|first
op_assign
(paren
r_uint64
)paren
id|read_rtc1
c_func
(paren
id|ETIMEHREG
)paren
suffix:semicolon
id|second_low
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|ETIMELREG
)paren
suffix:semicolon
id|second_mid
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|ETIMEMREG
)paren
suffix:semicolon
id|second
op_assign
(paren
r_uint64
)paren
id|read_rtc1
c_func
(paren
id|ETIMEHREG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|first_low
op_ne
id|second_low
op_logical_or
id|first_mid
op_ne
id|second_mid
op_logical_or
id|first
op_ne
id|second
)paren
suffix:semicolon
r_return
(paren
id|first
op_lshift
l_int|32
)paren
op_or
(paren
r_uint64
)paren
(paren
(paren
id|first_mid
op_lshift
l_int|16
)paren
op_or
id|first_low
)paren
suffix:semicolon
)brace
DECL|function|write_elapsedtime_counter
r_static
r_inline
r_void
id|write_elapsedtime_counter
c_func
(paren
r_uint64
id|time
)paren
(brace
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
id|time
comma
id|ETIMELREG
)paren
suffix:semicolon
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
(paren
id|time
op_rshift
l_int|16
)paren
comma
id|ETIMEMREG
)paren
suffix:semicolon
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
(paren
id|time
op_rshift
l_int|32
)paren
comma
id|ETIMEHREG
)paren
suffix:semicolon
)brace
DECL|function|write_elapsedtime_compare
r_static
r_inline
r_void
id|write_elapsedtime_compare
c_func
(paren
r_uint64
id|time
)paren
(brace
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
id|time
comma
id|ECMPLREG
)paren
suffix:semicolon
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
(paren
id|time
op_rshift
l_int|16
)paren
comma
id|ECMPMREG
)paren
suffix:semicolon
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
(paren
id|time
op_rshift
l_int|32
)paren
comma
id|ECMPHREG
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_set_rtclong1_cycle
r_void
id|vr41xx_set_rtclong1_cycle
c_func
(paren
r_uint32
id|cycles
)paren
(brace
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
id|cycles
comma
id|RTCL1LREG
)paren
suffix:semicolon
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
(paren
id|cycles
op_rshift
l_int|16
)paren
comma
id|RTCL1HREG
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_read_rtclong1_counter
r_uint32
id|vr41xx_read_rtclong1_counter
c_func
(paren
r_void
)paren
(brace
r_uint32
id|first_high
comma
id|first_low
suffix:semicolon
r_uint32
id|second_high
comma
id|second_low
suffix:semicolon
r_do
(brace
id|first_low
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL1CNTLREG
)paren
suffix:semicolon
id|first_high
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL1CNTHREG
)paren
suffix:semicolon
id|second_low
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL1CNTLREG
)paren
suffix:semicolon
id|second_high
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL1CNTHREG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|first_low
op_ne
id|second_low
op_logical_or
id|first_high
op_ne
id|second_high
)paren
suffix:semicolon
r_return
(paren
id|first_high
op_lshift
l_int|16
)paren
op_or
id|first_low
suffix:semicolon
)brace
DECL|function|vr41xx_set_rtclong2_cycle
r_void
id|vr41xx_set_rtclong2_cycle
c_func
(paren
r_uint32
id|cycles
)paren
(brace
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
id|cycles
comma
id|RTCL2LREG
)paren
suffix:semicolon
id|write_rtc1
c_func
(paren
(paren
r_uint16
)paren
(paren
id|cycles
op_rshift
l_int|16
)paren
comma
id|RTCL2HREG
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_read_rtclong2_counter
r_uint32
id|vr41xx_read_rtclong2_counter
c_func
(paren
r_void
)paren
(brace
r_uint32
id|first_high
comma
id|first_low
suffix:semicolon
r_uint32
id|second_high
comma
id|second_low
suffix:semicolon
r_do
(brace
id|first_low
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL2CNTLREG
)paren
suffix:semicolon
id|first_high
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL2CNTHREG
)paren
suffix:semicolon
id|second_low
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL2CNTLREG
)paren
suffix:semicolon
id|second_high
op_assign
(paren
r_uint32
)paren
id|read_rtc1
c_func
(paren
id|RTCL2CNTHREG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|first_low
op_ne
id|second_low
op_logical_or
id|first_high
op_ne
id|second_high
)paren
suffix:semicolon
r_return
(paren
id|first_high
op_lshift
l_int|16
)paren
op_or
id|first_low
suffix:semicolon
)brace
DECL|function|vr41xx_set_tclock_cycle
r_void
id|vr41xx_set_tclock_cycle
c_func
(paren
r_uint32
id|cycles
)paren
(brace
id|write_rtc2
c_func
(paren
(paren
r_uint16
)paren
id|cycles
comma
id|TCLKLREG
)paren
suffix:semicolon
id|write_rtc2
c_func
(paren
(paren
r_uint16
)paren
(paren
id|cycles
op_rshift
l_int|16
)paren
comma
id|TCLKHREG
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_read_tclock_counter
r_uint32
id|vr41xx_read_tclock_counter
c_func
(paren
r_void
)paren
(brace
r_uint32
id|first_high
comma
id|first_low
suffix:semicolon
r_uint32
id|second_high
comma
id|second_low
suffix:semicolon
r_do
(brace
id|first_low
op_assign
(paren
r_uint32
)paren
id|read_rtc2
c_func
(paren
id|TCLKCNTLREG
)paren
suffix:semicolon
id|first_high
op_assign
(paren
r_uint32
)paren
id|read_rtc2
c_func
(paren
id|TCLKCNTHREG
)paren
suffix:semicolon
id|second_low
op_assign
(paren
r_uint32
)paren
id|read_rtc2
c_func
(paren
id|TCLKCNTLREG
)paren
suffix:semicolon
id|second_high
op_assign
(paren
r_uint32
)paren
id|read_rtc2
c_func
(paren
id|TCLKCNTHREG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|first_low
op_ne
id|second_low
op_logical_or
id|first_high
op_ne
id|second_high
)paren
suffix:semicolon
r_return
(paren
id|first_high
op_lshift
l_int|16
)paren
op_or
id|first_low
suffix:semicolon
)brace
DECL|function|vr41xx_timer_ack
r_static
r_void
id|vr41xx_timer_ack
c_func
(paren
r_void
)paren
(brace
r_uint64
id|cur
suffix:semicolon
id|write_rtc2
c_func
(paren
id|ELAPSEDTIME_INT
comma
id|RTCINTREG
)paren
suffix:semicolon
id|previous_elapsedtime
op_add_assign
(paren
r_uint64
)paren
id|cycles_per_jiffy
suffix:semicolon
id|cycles_per_sec
op_add_assign
id|cycles_per_jiffy
suffix:semicolon
r_if
c_cond
(paren
id|cycles_per_sec
op_ge
id|CLOCK_TICK_RATE
)paren
(brace
id|cycles_per_sec
op_assign
l_int|0
suffix:semicolon
id|remainder_per_sec
op_assign
id|REMAINDER_PER_SEC
suffix:semicolon
)brace
id|cycles_per_jiffy
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|cycles_per_jiffy
op_add_assign
id|CYCLES_PER_JIFFY
suffix:semicolon
r_if
c_cond
(paren
id|remainder_per_sec
OG
l_int|0
)paren
(brace
id|cycles_per_jiffy
op_increment
suffix:semicolon
id|remainder_per_sec
op_decrement
suffix:semicolon
)brace
id|cur
op_assign
id|read_elapsedtime_counter
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cur
op_ge
id|previous_elapsedtime
op_plus
(paren
r_uint64
)paren
id|cycles_per_jiffy
)paren
suffix:semicolon
id|write_elapsedtime_compare
c_func
(paren
id|previous_elapsedtime
op_plus
(paren
r_uint64
)paren
id|cycles_per_jiffy
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_hpt_init
r_static
r_void
id|vr41xx_hpt_init
c_func
(paren
r_int
r_int
id|count
)paren
(brace
)brace
DECL|function|vr41xx_hpt_read
r_static
r_int
r_int
id|vr41xx_hpt_read
c_func
(paren
r_void
)paren
(brace
r_uint64
id|cur
suffix:semicolon
id|cur
op_assign
id|read_elapsedtime_counter
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|cur
suffix:semicolon
)brace
DECL|function|vr41xx_gettimeoffset
r_static
r_int
r_int
id|vr41xx_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_uint64
id|cur
suffix:semicolon
r_int
r_int
id|gap
suffix:semicolon
id|cur
op_assign
id|read_elapsedtime_counter
c_func
(paren
)paren
suffix:semicolon
id|gap
op_assign
(paren
r_int
r_int
)paren
(paren
id|cur
op_minus
id|previous_elapsedtime
)paren
suffix:semicolon
id|gap
op_assign
id|gap
op_div
id|CYCLES_PER_100USEC
op_star
l_int|100
suffix:semicolon
multiline_comment|/* usec */
r_return
id|gap
suffix:semicolon
)brace
DECL|function|vr41xx_get_time
r_static
r_int
r_int
id|vr41xx_get_time
c_func
(paren
r_void
)paren
(brace
r_uint64
id|counts
suffix:semicolon
id|counts
op_assign
id|read_elapsedtime_counter
c_func
(paren
)paren
suffix:semicolon
id|counts
op_rshift_assign
l_int|15
suffix:semicolon
r_return
id|epoch_time
op_plus
(paren
r_int
r_int
)paren
id|counts
suffix:semicolon
)brace
DECL|function|vr41xx_set_time
r_static
r_int
id|vr41xx_set_time
c_func
(paren
r_int
r_int
id|sec
)paren
(brace
r_if
c_cond
(paren
id|sec
OL
id|epoch_time
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sec
op_sub_assign
id|epoch_time
suffix:semicolon
id|write_elapsedtime_counter
c_func
(paren
(paren
r_uint64
)paren
id|sec
op_lshift
l_int|15
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vr41xx_set_epoch_time
r_void
id|vr41xx_set_epoch_time
c_func
(paren
r_int
r_int
id|time
)paren
(brace
id|epoch_time
op_assign
id|time
suffix:semicolon
)brace
DECL|function|vr41xx_time_init
r_void
id|__init
id|vr41xx_time_init
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_VR4111
suffix:colon
r_case
id|CPU_VR4121
suffix:colon
id|rtc1_base
op_assign
id|ETIMELREG_TYPE1
suffix:semicolon
id|rtc2_base
op_assign
id|TCLKLREG_TYPE1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
r_case
id|CPU_VR4133
suffix:colon
id|rtc1_base
op_assign
id|ETIMELREG_TYPE2
suffix:semicolon
id|rtc2_base
op_assign
id|TCLKLREG_TYPE2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unexpected CPU of NEC VR4100 series&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mips_timer_ack
op_assign
id|vr41xx_timer_ack
suffix:semicolon
id|mips_hpt_init
op_assign
id|vr41xx_hpt_init
suffix:semicolon
id|mips_hpt_read
op_assign
id|vr41xx_hpt_read
suffix:semicolon
id|mips_hpt_frequency
op_assign
id|CLOCK_TICK_RATE
suffix:semicolon
r_if
c_cond
(paren
id|epoch_time
op_eq
l_int|0
)paren
id|epoch_time
op_assign
id|mktime
c_func
(paren
l_int|1970
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|rtc_get_time
op_assign
id|vr41xx_get_time
suffix:semicolon
id|rtc_set_time
op_assign
id|vr41xx_set_time
suffix:semicolon
)brace
DECL|function|vr41xx_timer_setup
r_void
id|__init
id|vr41xx_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|do_gettimeoffset
op_assign
id|vr41xx_gettimeoffset
suffix:semicolon
id|remainder_per_sec
op_assign
id|REMAINDER_PER_SEC
suffix:semicolon
id|cycles_per_jiffy
op_assign
id|CYCLES_PER_JIFFY
suffix:semicolon
r_if
c_cond
(paren
id|remainder_per_sec
OG
l_int|0
)paren
(brace
id|cycles_per_jiffy
op_increment
suffix:semicolon
id|remainder_per_sec
op_decrement
suffix:semicolon
)brace
id|previous_elapsedtime
op_assign
id|read_elapsedtime_counter
c_func
(paren
)paren
suffix:semicolon
id|write_elapsedtime_compare
c_func
(paren
id|previous_elapsedtime
op_plus
(paren
r_uint64
)paren
id|cycles_per_jiffy
)paren
suffix:semicolon
id|write_rtc2
c_func
(paren
id|ELAPSEDTIME_INT
comma
id|RTCINTREG
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|ELAPSEDTIME_IRQ
comma
id|irq
)paren
suffix:semicolon
)brace
eof
