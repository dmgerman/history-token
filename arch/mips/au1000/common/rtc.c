multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * RTC routines for PC style attached Dallas chip.&n; *&n; * Copyright (C) 1998, 2001 by Ralf Baechle&n; */
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
DECL|macro|PB1500_RTC_ADDR
mdefine_line|#define PB1500_RTC_ADDR 0xAC000000
DECL|function|std_rtc_read_data
r_int
r_char
id|std_rtc_read_data
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
id|offset
op_lshift_assign
l_int|2
suffix:semicolon
r_return
(paren
id|u8
)paren
(paren
id|au_readl
c_func
(paren
id|offset
op_plus
id|PB1500_RTC_ADDR
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|std_rtc_write_data
r_static
r_void
id|std_rtc_write_data
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|offset
)paren
(brace
id|offset
op_lshift_assign
l_int|2
suffix:semicolon
id|au_writel
c_func
(paren
id|data
comma
id|offset
op_plus
id|PB1500_RTC_ADDR
)paren
suffix:semicolon
)brace
DECL|function|std_rtc_bcd_mode
r_static
r_int
id|std_rtc_bcd_mode
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pb1500_rtc_ops
r_struct
id|rtc_ops
id|pb1500_rtc_ops
op_assign
(brace
op_amp
id|std_rtc_read_data
comma
op_amp
id|std_rtc_write_data
comma
op_amp
id|std_rtc_bcd_mode
)brace
suffix:semicolon
eof
