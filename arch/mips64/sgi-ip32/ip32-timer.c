multiline_comment|/*&n; * IP32 timer calibration&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001 Keith M Wesolowski&n; */
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/ip32/crime.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
r_extern
id|u32
id|cc_interval
suffix:semicolon
multiline_comment|/* An arbitrary time; this can be decreased if reliability looks good */
DECL|macro|WAIT_MS
mdefine_line|#define WAIT_MS 10
DECL|macro|PER_MHZ
mdefine_line|#define PER_MHZ (1000000 / 2 / HZ)
DECL|function|ip32_timer_setup
r_void
id|__init
id|ip32_timer_setup
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|u64
id|crime_time
suffix:semicolon
id|u32
id|cc_tick
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Calibrating system timer... &quot;
)paren
suffix:semicolon
id|crime_time
op_assign
id|crime_read_64
(paren
id|CRIME_TIME
)paren
op_amp
id|CRIME_TIME_MASK
suffix:semicolon
id|cc_tick
op_assign
id|read_32bit_cp0_register
(paren
id|CP0_COUNT
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|crime_read_64
(paren
id|CRIME_TIME
)paren
op_amp
id|CRIME_TIME_MASK
)paren
op_minus
id|crime_time
OL
id|WAIT_MS
op_star
l_int|1000000
op_div
id|CRIME_NS_PER_TICK
)paren
suffix:semicolon
id|cc_tick
op_assign
id|read_32bit_cp0_register
(paren
id|CP0_COUNT
)paren
op_minus
id|cc_tick
suffix:semicolon
id|cc_interval
op_assign
id|cc_tick
op_div
id|HZ
op_star
(paren
l_int|1000
op_div
id|WAIT_MS
)paren
suffix:semicolon
multiline_comment|/* The round-off seems unnecessary; in testing, the error of the&n;&t; * above procedure is &lt; 100 ticks, which means it gets filtered&n;&t; * out by the HZ adjustment. &n;&t; */
id|cc_interval
op_assign
(paren
id|cc_interval
op_div
id|PER_MHZ
)paren
op_star
id|PER_MHZ
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d MHz CPU detected&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|cc_interval
op_div
id|PER_MHZ
)paren
)paren
suffix:semicolon
id|setup_irq
(paren
id|CLOCK_IRQ
comma
id|irq
)paren
suffix:semicolon
)brace
eof
