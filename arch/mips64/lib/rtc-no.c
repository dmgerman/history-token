multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Stub RTC routines to keep Linux from crashing on machine which don&squot;t&n; * have a RTC chip.&n; *&n; * Copyright (C) 1998, 2001 by Ralf Baechle&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
DECL|function|no_rtc_read_data
r_static
r_int
r_char
id|no_rtc_read_data
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;no_rtc_read_data called - shouldn&squot;t happen.&quot;
)paren
suffix:semicolon
)brace
DECL|function|no_rtc_write_data
r_static
r_void
id|no_rtc_write_data
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;no_rtc_write_data called - shouldn&squot;t happen.&quot;
)paren
suffix:semicolon
)brace
DECL|function|no_rtc_bcd_mode
r_static
r_int
id|no_rtc_bcd_mode
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;no_rtc_bcd_mode called - shouldn&squot;t happen.&quot;
)paren
suffix:semicolon
)brace
DECL|variable|no_rtc_ops
r_struct
id|rtc_ops
id|no_rtc_ops
op_assign
(brace
op_amp
id|no_rtc_read_data
comma
op_amp
id|no_rtc_write_data
comma
op_amp
id|no_rtc_bcd_mode
)brace
suffix:semicolon
eof
