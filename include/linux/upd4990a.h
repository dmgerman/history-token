multiline_comment|/*&n; *  Constant and architecture independent procedures&n; *  for NEC uPD4990A serial I/O real-time clock.&n; *&n; *  Copyright 2001  TAKAI Kousuke &lt;tak@kmc.kyoto-u.ac.jp&gt;&n; *&t;&t;    Kyoto University Microcomputer Club (KMC).&n; *&n; *  References:&n; *&t;uPD4990A serial I/O real-time clock users&squot; manual (Japanese)&n; *&t;No. S12828JJ4V0UM00 (4th revision), NEC Corporation, 1999.&n; */
macro_line|#ifndef _LINUX_uPD4990A_H
DECL|macro|_LINUX_uPD4990A_H
mdefine_line|#define _LINUX_uPD4990A_H
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/upd4990a.h&gt;
multiline_comment|/* Serial commands (4 bits) */
DECL|macro|UPD4990A_REGISTER_HOLD
mdefine_line|#define UPD4990A_REGISTER_HOLD&t;&t;&t;(0x0)
DECL|macro|UPD4990A_REGISTER_SHIFT
mdefine_line|#define UPD4990A_REGISTER_SHIFT&t;&t;&t;(0x1)
DECL|macro|UPD4990A_TIME_SET_AND_COUNTER_HOLD
mdefine_line|#define UPD4990A_TIME_SET_AND_COUNTER_HOLD&t;(0x2)
DECL|macro|UPD4990A_TIME_READ
mdefine_line|#define UPD4990A_TIME_READ&t;&t;&t;(0x3)
DECL|macro|UPD4990A_TP_64HZ
mdefine_line|#define UPD4990A_TP_64HZ&t;&t;&t;(0x4)
DECL|macro|UPD4990A_TP_256HZ
mdefine_line|#define UPD4990A_TP_256HZ&t;&t;&t;(0x5)
DECL|macro|UPD4990A_TP_2048HZ
mdefine_line|#define UPD4990A_TP_2048HZ&t;&t;&t;(0x6)
DECL|macro|UPD4990A_TP_4096HZ
mdefine_line|#define UPD4990A_TP_4096HZ&t;&t;&t;(0x7)
DECL|macro|UPD4990A_TP_1S
mdefine_line|#define UPD4990A_TP_1S&t;&t;&t;&t;(0x8)
DECL|macro|UPD4990A_TP_10S
mdefine_line|#define UPD4990A_TP_10S&t;&t;&t;&t;(0x9)
DECL|macro|UPD4990A_TP_30S
mdefine_line|#define UPD4990A_TP_30S&t;&t;&t;&t;(0xA)
DECL|macro|UPD4990A_TP_60S
mdefine_line|#define UPD4990A_TP_60S&t;&t;&t;&t;(0xB)
DECL|macro|UPD4990A_INTERRUPT_RESET
mdefine_line|#define UPD4990A_INTERRUPT_RESET&t;&t;(0xC)
DECL|macro|UPD4990A_INTERRUPT_TIMER_START
mdefine_line|#define UPD4990A_INTERRUPT_TIMER_START&t;&t;(0xD)
DECL|macro|UPD4990A_INTERRUPT_TIMER_STOP
mdefine_line|#define UPD4990A_INTERRUPT_TIMER_STOP&t;&t;(0xE)
DECL|macro|UPD4990A_TEST_MODE_SET
mdefine_line|#define UPD4990A_TEST_MODE_SET&t;&t;&t;(0xF)
multiline_comment|/* Parallel commands (3 bits)&n;   0-6 are same with serial commands.  */
DECL|macro|UPD4990A_PAR_SERIAL_MODE
mdefine_line|#define UPD4990A_PAR_SERIAL_MODE&t;&t;7
macro_line|#ifndef UPD4990A_DELAY
macro_line|# include &lt;linux/delay.h&gt;
DECL|macro|UPD4990A_DELAY
macro_line|# define UPD4990A_DELAY(usec)&t;udelay((usec))
macro_line|#endif
macro_line|#ifndef UPD4990A_OUTPUT_DATA
DECL|macro|UPD4990A_OUTPUT_DATA
macro_line|# define UPD4990A_OUTPUT_DATA(bit)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;UPD4990A_OUTPUT_DATA_CLK((bit), 0);&t;&bslash;&n;&t;&t;UPD4990A_DELAY(1); /* t-DSU */&t;&t;&bslash;&n;&t;&t;UPD4990A_OUTPUT_DATA_CLK((bit), 1);&t;&bslash;&n;&t;&t;UPD4990A_DELAY(1); /* t-DHLD */&t;&bslash;&n;&t;} while (0)
macro_line|#endif
DECL|function|upd4990a_serial_command
r_static
id|__inline__
r_void
id|upd4990a_serial_command
c_func
(paren
r_int
id|command
)paren
(brace
id|UPD4990A_OUTPUT_DATA
c_func
(paren
id|command
op_rshift
l_int|0
)paren
suffix:semicolon
id|UPD4990A_OUTPUT_DATA
c_func
(paren
id|command
op_rshift
l_int|1
)paren
suffix:semicolon
id|UPD4990A_OUTPUT_DATA
c_func
(paren
id|command
op_rshift
l_int|2
)paren
suffix:semicolon
id|UPD4990A_OUTPUT_DATA
c_func
(paren
id|command
op_rshift
l_int|3
)paren
suffix:semicolon
id|UPD4990A_DELAY
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* t-HLD */
id|UPD4990A_OUTPUT_STROBE
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|UPD4990A_DELAY
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* t-STB &amp; t-d1 */
id|UPD4990A_OUTPUT_STROBE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 19 microseconds extra delay is needed&n;&t;   iff previous mode is TIME READ command  */
)brace
DECL|struct|upd4990a_raw_data
r_struct
id|upd4990a_raw_data
(brace
DECL|member|sec
id|u8
id|sec
suffix:semicolon
multiline_comment|/* BCD */
DECL|member|min
id|u8
id|min
suffix:semicolon
multiline_comment|/* BCD */
DECL|member|hour
id|u8
id|hour
suffix:semicolon
multiline_comment|/* BCD */
DECL|member|mday
id|u8
id|mday
suffix:semicolon
multiline_comment|/* BCD */
macro_line|#if   defined __LITTLE_ENDIAN_BITFIELD
DECL|member|wday
r_int
id|wday
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 0-6 */
DECL|member|mon
r_int
id|mon
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 1-based */
macro_line|#elif defined __BIG_ENDIAN_BITFIELD
DECL|member|mon
r_int
id|mon
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 1-based */
DECL|member|wday
r_int
id|wday
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 0-6 */
macro_line|#else
macro_line|# error Unknown bitfield endian!
macro_line|#endif
DECL|member|year
id|u8
id|year
suffix:semicolon
multiline_comment|/* BCD */
)brace
suffix:semicolon
DECL|function|upd4990a_get_time
r_static
id|__inline__
r_void
id|upd4990a_get_time
c_func
(paren
r_struct
id|upd4990a_raw_data
op_star
id|buf
comma
r_int
id|leave_register_hold
)paren
(brace
r_int
id|byte
suffix:semicolon
id|upd4990a_serial_command
c_func
(paren
id|UPD4990A_TIME_READ
)paren
suffix:semicolon
id|upd4990a_serial_command
c_func
(paren
id|UPD4990A_REGISTER_SHIFT
)paren
suffix:semicolon
id|UPD4990A_DELAY
c_func
(paren
l_int|19
)paren
suffix:semicolon
multiline_comment|/* t-d2 - t-d1 */
r_for
c_loop
(paren
id|byte
op_assign
l_int|0
suffix:semicolon
id|byte
OL
l_int|6
suffix:semicolon
id|byte
op_increment
)paren
(brace
id|u8
id|tmp
suffix:semicolon
r_int
id|bit
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
comma
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|8
suffix:semicolon
id|bit
op_increment
)paren
(brace
id|tmp
op_assign
(paren
id|tmp
op_or
(paren
id|UPD4990A_READ_DATA
c_func
(paren
)paren
op_lshift
l_int|8
)paren
)paren
op_rshift
l_int|1
suffix:semicolon
id|UPD4990A_OUTPUT_CLK
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|UPD4990A_DELAY
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|UPD4990A_OUTPUT_CLK
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|UPD4990A_DELAY
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
(paren
(paren
id|u8
op_star
)paren
id|buf
)paren
(braket
id|byte
)braket
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* The uPD4990A users&squot; manual says that we should issue `Register&n;&t;   Hold&squot; command after each data retrieval, or next `Time Read&squot;&n;&t;   command may not work correctly.  */
r_if
c_cond
(paren
op_logical_neg
id|leave_register_hold
)paren
id|upd4990a_serial_command
c_func
(paren
id|UPD4990A_REGISTER_HOLD
)paren
suffix:semicolon
)brace
DECL|function|upd4990a_set_time
r_static
id|__inline__
r_void
id|upd4990a_set_time
c_func
(paren
r_const
r_struct
id|upd4990a_raw_data
op_star
id|data
comma
r_int
id|time_set_only
)paren
(brace
r_int
id|byte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|time_set_only
)paren
id|upd4990a_serial_command
c_func
(paren
id|UPD4990A_REGISTER_SHIFT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|byte
op_assign
l_int|0
suffix:semicolon
id|byte
OL
l_int|6
suffix:semicolon
id|byte
op_increment
)paren
(brace
r_int
id|bit
suffix:semicolon
id|u8
id|tmp
op_assign
(paren
(paren
r_const
id|u8
op_star
)paren
id|data
)paren
(braket
id|byte
)braket
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|8
suffix:semicolon
id|bit
op_increment
comma
id|tmp
op_rshift_assign
l_int|1
)paren
id|UPD4990A_OUTPUT_DATA
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|upd4990a_serial_command
c_func
(paren
id|UPD4990A_TIME_SET_AND_COUNTER_HOLD
)paren
suffix:semicolon
multiline_comment|/* Release counter hold and start the clock.  */
r_if
c_cond
(paren
op_logical_neg
id|time_set_only
)paren
id|upd4990a_serial_command
c_func
(paren
id|UPD4990A_REGISTER_HOLD
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_uPD4990A_H */
eof
