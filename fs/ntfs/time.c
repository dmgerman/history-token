multiline_comment|/*&n; * time.c - NTFS time conversion functions. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/sched.h&gt;&t;/* For CURRENT_TIME. */
macro_line|#include &lt;asm/div64.h&gt;&t;&t;/* For do_div(). */
macro_line|#include &quot;ntfs.h&quot;
DECL|macro|NTFS_TIME_OFFSET
mdefine_line|#define NTFS_TIME_OFFSET ((s64)(369 * 365 + 89) * 24 * 3600 * 10000000)
multiline_comment|/**&n; * utc2ntfs - convert Linux time to NTFS time&n; * @time:&t;&t;Linux time to convert to NTFS&n; *&n; * Convert the Linux time @time to its corresponding NTFS time and return that&n; * in little endian format.&n; *&n; * Linux stores time in a long at present and measures it as the number of&n; * 1-second intervals since 1st January 1970, 00:00:00 UTC.&n; *&n; * NTFS uses Microsoft&squot;s standard time format which is stored in a s64 and is&n; * measured as the number of 100 nano-second intervals since 1st January 1601,&n; * 00:00:00 UTC.&n; */
DECL|function|utc2ntfs
r_inline
id|s64
id|utc2ntfs
c_func
(paren
r_const
id|time_t
id|time
)paren
(brace
multiline_comment|/* Convert to 100ns intervals and then add the NTFS time offset. */
r_return
id|cpu_to_sle64
c_func
(paren
(paren
id|s64
)paren
id|time
op_star
l_int|10000000
op_plus
id|NTFS_TIME_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * get_current_ntfs_time - get the current time in little endian NTFS format&n; *&n; * Get the current time from the Linux kernel, convert it to its corresponding&n; * NTFS time and return that in little endian format.&n; */
DECL|function|get_current_ntfs_time
r_inline
id|s64
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
id|CURRENT_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs2utc - convert NTFS time to Linux time&n; * @time:&t;&t;NTFS time (little endian) to convert to Linux&n; *&n; * Convert the little endian NTFS time @time to its corresponding Linux time&n; * and return that in cpu format.&n; *&n; * Linux stores time in a long at present and measures it as the number of&n; * 1-second intervals since 1st January 1970, 00:00:00 UTC.&n; *&n; * NTFS uses Microsoft&squot;s standard time format which is stored in a s64 and is&n; * measured as the number of 100 nano-second intervals since 1st January 1601,&n; * 00:00:00 UTC.&n; */
DECL|function|ntfs2utc
r_inline
id|time_t
id|ntfs2utc
c_func
(paren
r_const
id|s64
id|time
)paren
(brace
multiline_comment|/* Subtract the NTFS time offset, then convert to 1s intervals. */
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
id|do_div
c_func
(paren
id|t
comma
l_int|10000000
)paren
suffix:semicolon
r_return
(paren
id|time_t
)paren
id|t
suffix:semicolon
)brace
eof
