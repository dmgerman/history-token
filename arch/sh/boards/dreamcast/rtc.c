multiline_comment|/* arch/sh/kernel/rtc-aica.c&n; *&n; * Dreamcast AICA RTC routines.&n; *&n; * Copyright (c) 2001, 2002 M. R. Brown &lt;mrbrown@0xd6.org&gt;&n; * Copyright (c) 2002 Paul Mundt &lt;lethal@chaoticdreams.org&gt;&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; *&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_void
(paren
op_star
id|rtc_get_time
)paren
(paren
r_struct
id|timespec
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|rtc_set_time
)paren
(paren
r_const
id|time_t
)paren
suffix:semicolon
multiline_comment|/* The AICA RTC has an Epoch of 1/1/1950, so we must subtract 20 years (in&n;   seconds to get the standard Unix Epoch when getting the time, and add 20&n;   years when setting the time. */
DECL|macro|TWENTY_YEARS
mdefine_line|#define TWENTY_YEARS ((20 * 365LU + 5) * 86400)
multiline_comment|/* The AICA RTC is represented by a 32-bit seconds counter stored in 2 16-bit&n;   registers.*/
DECL|macro|AICA_RTC_SECS_H
mdefine_line|#define AICA_RTC_SECS_H&t;&t;0xa0710000
DECL|macro|AICA_RTC_SECS_L
mdefine_line|#define AICA_RTC_SECS_L&t;&t;0xa0710004
multiline_comment|/**&n; * aica_rtc_gettimeofday - Get the time from the AICA RTC&n; * @ts: pointer to resulting timespec&n; *&n; * Grabs the current RTC seconds counter and adjusts it to the Unix Epoch.&n; */
DECL|function|aica_rtc_gettimeofday
r_void
id|aica_rtc_gettimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|ts
)paren
(brace
r_int
r_int
id|val1
comma
id|val2
suffix:semicolon
r_do
(brace
id|val1
op_assign
(paren
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_H
)paren
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_L
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|val2
op_assign
(paren
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_H
)paren
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_L
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|val1
op_ne
id|val2
)paren
suffix:semicolon
id|ts-&gt;tv_sec
op_assign
id|val1
op_minus
id|TWENTY_YEARS
suffix:semicolon
multiline_comment|/* Can&squot;t get nanoseconds with just a seconds counter. */
id|ts-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * aica_rtc_settimeofday - Set the AICA RTC to the current time&n; * @secs: contains the time_t to set&n; *&n; * Adjusts the given @tv to the AICA Epoch and sets the RTC seconds counter.&n; */
DECL|function|aica_rtc_settimeofday
r_int
id|aica_rtc_settimeofday
c_func
(paren
r_const
id|time_t
id|secs
)paren
(brace
r_int
r_int
id|val1
comma
id|val2
suffix:semicolon
r_int
r_int
id|adj
op_assign
id|secs
op_plus
id|TWENTY_YEARS
suffix:semicolon
r_do
(brace
id|ctrl_outl
c_func
(paren
(paren
id|adj
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
comma
id|AICA_RTC_SECS_H
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
(paren
id|adj
op_amp
l_int|0xffff
)paren
comma
id|AICA_RTC_SECS_L
)paren
suffix:semicolon
id|val1
op_assign
(paren
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_H
)paren
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_L
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|val2
op_assign
(paren
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_H
)paren
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ctrl_inl
c_func
(paren
id|AICA_RTC_SECS_L
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|val1
op_ne
id|val2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aica_time_init
r_void
id|aica_time_init
c_func
(paren
r_void
)paren
(brace
id|rtc_get_time
op_assign
id|aica_rtc_gettimeofday
suffix:semicolon
id|rtc_set_time
op_assign
id|aica_rtc_settimeofday
suffix:semicolon
)brace
eof
