multiline_comment|/*&n; * time.h - NTFS time conversion functions.  Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_TIME_H
DECL|macro|_LINUX_NTFS_TIME_H
mdefine_line|#define _LINUX_NTFS_TIME_H
macro_line|#include &lt;linux/time.h&gt;&t;&t;/* For current_kernel_time(). */
macro_line|#include &lt;asm/div64.h&gt;&t;&t;/* For do_div(). */
macro_line|#include &quot;endian.h&quot;
DECL|macro|NTFS_TIME_OFFSET
mdefine_line|#define NTFS_TIME_OFFSET ((s64)(369 * 365 + 89) * 24 * 3600 * 10000000)
multiline_comment|/**&n; * utc2ntfs - convert Linux UTC time to NTFS time&n; * @ts:&t;&t;Linux UTC time to convert to NTFS time&n; *&n; * Convert the Linux UTC time @ts to its corresponding NTFS time and return&n; * that in little endian format.&n; *&n; * Linux stores time in a struct timespec consisting of a time_t (long at&n; * present) tv_sec and a long tv_nsec where tv_sec is the number of 1-second&n; * intervals since 1st January 1970, 00:00:00 UTC and tv_nsec is the number of&n; * 1-nano-second intervals since the value of tv_sec.&n; *&n; * NTFS uses Microsoft&squot;s standard time format which is stored in a s64 and is&n; * measured as the number of 100-nano-second intervals since 1st January 1601,&n; * 00:00:00 UTC.&n; */
DECL|function|utc2ntfs
r_static
r_inline
id|sle64
id|utc2ntfs
c_func
(paren
r_const
r_struct
id|timespec
id|ts
)paren
(brace
multiline_comment|/*&n;&t; * Convert the seconds to 100ns intervals, add the nano-seconds&n;&t; * converted to 100ns intervals, and then add the NTFS time offset.&n;&t; */
r_return
id|cpu_to_sle64
c_func
(paren
(paren
id|s64
)paren
id|ts.tv_sec
op_star
l_int|10000000
op_plus
id|ts.tv_nsec
op_div
l_int|100
op_plus
id|NTFS_TIME_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * get_current_ntfs_time - get the current time in little endian NTFS format&n; *&n; * Get the current time from the Linux kernel, convert it to its corresponding&n; * NTFS time and return that in little endian format.&n; */
DECL|function|get_current_ntfs_time
r_static
r_inline
id|sle64
id|get_current_ntfs_time
c_func
(paren
r_void
)paren
(brace
r_return
id|utc2ntfs
c_func
(paren
id|current_kernel_time
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs2utc - convert NTFS time to Linux time&n; * @time:&t;NTFS time (little endian) to convert to Linux UTC&n; *&n; * Convert the little endian NTFS time @time to its corresponding Linux UTC&n; * time and return that in cpu format.&n; *&n; * Linux stores time in a struct timespec consisting of a time_t (long at&n; * present) tv_sec and a long tv_nsec where tv_sec is the number of 1-second&n; * intervals since 1st January 1970, 00:00:00 UTC and tv_nsec is the number of&n; * 1-nano-second intervals since the value of tv_sec.&n; *&n; * NTFS uses Microsoft&squot;s standard time format which is stored in a s64 and is&n; * measured as the number of 100 nano-second intervals since 1st January 1601,&n; * 00:00:00 UTC.&n; */
DECL|function|ntfs2utc
r_static
r_inline
r_struct
id|timespec
id|ntfs2utc
c_func
(paren
r_const
id|sle64
id|time
)paren
(brace
r_struct
id|timespec
id|ts
suffix:semicolon
multiline_comment|/* Subtract the NTFS time offset. */
id|s64
id|t
op_assign
id|sle64_to_cpu
c_func
(paren
id|time
)paren
op_minus
id|NTFS_TIME_OFFSET
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the time to 1-second intervals and the remainder to&n;&t; * 1-nano-second intervals.&n;&t; */
id|ts.tv_nsec
op_assign
id|do_div
c_func
(paren
id|t
comma
l_int|10000000
)paren
op_star
l_int|100
suffix:semicolon
id|ts.tv_sec
op_assign
id|t
suffix:semicolon
r_return
id|ts
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_NTFS_TIME_H */
eof
