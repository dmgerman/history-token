multiline_comment|/*&n; *  arch/mips/ddb5074/time.c -- Timer routines&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
DECL|function|ddb_rtc_read_data
r_static
r_int
r_char
id|ddb_rtc_read_data
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|outb_p
c_func
(paren
id|addr
comma
id|RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|inb_p
c_func
(paren
id|RTC_PORT
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|ddb_rtc_write_data
r_static
r_void
id|ddb_rtc_write_data
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
id|outb_p
c_func
(paren
id|addr
comma
id|RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
comma
id|RTC_PORT
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|ddb_rtc_bcd_mode
r_static
r_int
id|ddb_rtc_bcd_mode
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ddb_rtc_ops
r_struct
id|rtc_ops
id|ddb_rtc_ops
op_assign
(brace
id|ddb_rtc_read_data
comma
id|ddb_rtc_write_data
comma
id|ddb_rtc_bcd_mode
)brace
suffix:semicolon
eof
