multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *&n; *   Copyright 2002 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,&n; *   Bostom MA 02111-1307, USA; either version 2 of the License, or&n; *   (at your option) any later version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * raid6algos.c&n; *&n; * Algorithm list and algorithm selection for RAID-6&n; */
macro_line|#include &quot;raid6.h&quot;
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#endif
DECL|variable|raid6_call
r_struct
id|raid6_calls
id|raid6_call
suffix:semicolon
multiline_comment|/* Various routine sets */
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_intx1
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_intx2
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_intx4
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_intx8
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_intx16
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_intx32
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_mmxx1
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_mmxx2
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_sse1x1
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_sse1x2
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_sse2x1
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_sse2x2
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_sse2x4
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_altivec1
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_altivec2
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_altivec4
suffix:semicolon
r_extern
r_const
r_struct
id|raid6_calls
id|raid6_altivec8
suffix:semicolon
DECL|variable|raid6_algos
r_const
r_struct
id|raid6_calls
op_star
r_const
id|raid6_algos
(braket
)braket
op_assign
(brace
op_amp
id|raid6_intx1
comma
op_amp
id|raid6_intx2
comma
op_amp
id|raid6_intx4
comma
op_amp
id|raid6_intx8
comma
macro_line|#if defined(__ia64__)
op_amp
id|raid6_intx16
comma
op_amp
id|raid6_intx32
comma
macro_line|#endif
macro_line|#if defined(__i386__)
op_amp
id|raid6_mmxx1
comma
op_amp
id|raid6_mmxx2
comma
op_amp
id|raid6_sse1x1
comma
op_amp
id|raid6_sse1x2
comma
op_amp
id|raid6_sse2x1
comma
op_amp
id|raid6_sse2x2
comma
macro_line|#endif
macro_line|#if defined(__x86_64__)
op_amp
id|raid6_sse2x1
comma
op_amp
id|raid6_sse2x2
comma
op_amp
id|raid6_sse2x4
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ALTIVEC
op_amp
id|raid6_altivec1
comma
op_amp
id|raid6_altivec2
comma
op_amp
id|raid6_altivec4
comma
op_amp
id|raid6_altivec8
comma
macro_line|#endif
l_int|NULL
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|RAID6_TIME_JIFFIES_LG2
mdefine_line|#define RAID6_TIME_JIFFIES_LG2&t;4
macro_line|#else
multiline_comment|/* Need more time to be stable in userspace */
DECL|macro|RAID6_TIME_JIFFIES_LG2
mdefine_line|#define RAID6_TIME_JIFFIES_LG2&t;9
macro_line|#endif
multiline_comment|/* Try to pick the best algorithm */
multiline_comment|/* This code uses the gfmul table as convenient data set to abuse */
DECL|function|raid6_select_algo
r_int
id|__init
id|raid6_select_algo
c_func
(paren
r_void
)paren
(brace
r_const
r_struct
id|raid6_calls
op_star
r_const
op_star
id|algo
suffix:semicolon
r_const
r_struct
id|raid6_calls
op_star
id|best
suffix:semicolon
r_char
op_star
id|syndromes
suffix:semicolon
r_void
op_star
id|dptrs
(braket
(paren
l_int|65536
op_div
id|PAGE_SIZE
)paren
op_plus
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|disks
suffix:semicolon
r_int
r_int
id|perf
comma
id|bestperf
suffix:semicolon
r_int
id|bestprefer
suffix:semicolon
r_int
r_int
id|j0
comma
id|j1
suffix:semicolon
id|disks
op_assign
(paren
l_int|65536
op_div
id|PAGE_SIZE
)paren
op_plus
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|disks
op_minus
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dptrs
(braket
id|i
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
id|raid6_gfmul
)paren
op_plus
id|PAGE_SIZE
op_star
id|i
suffix:semicolon
)brace
multiline_comment|/* Normal code - use a 2-page allocation to avoid D$ conflict */
id|syndromes
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|syndromes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid6: Yikes!  No memory available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dptrs
(braket
id|disks
op_minus
l_int|2
)braket
op_assign
id|syndromes
suffix:semicolon
id|dptrs
(braket
id|disks
op_minus
l_int|1
)braket
op_assign
id|syndromes
op_plus
id|PAGE_SIZE
suffix:semicolon
id|bestperf
op_assign
l_int|0
suffix:semicolon
id|bestprefer
op_assign
l_int|0
suffix:semicolon
id|best
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|algo
op_assign
id|raid6_algos
suffix:semicolon
op_star
id|algo
suffix:semicolon
id|algo
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|valid
op_logical_or
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|valid
c_func
(paren
)paren
)paren
(brace
id|perf
op_assign
l_int|0
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|j0
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
(paren
id|j1
op_assign
id|jiffies
)paren
op_eq
id|j0
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|jiffies
op_minus
id|j1
)paren
OL
(paren
l_int|1
op_lshift
id|RAID6_TIME_JIFFIES_LG2
)paren
)paren
(brace
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|gen_syndrome
c_func
(paren
id|disks
comma
id|PAGE_SIZE
comma
id|dptrs
)paren
suffix:semicolon
id|perf
op_increment
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|prefer
OG
id|bestprefer
op_logical_or
(paren
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|prefer
op_eq
id|bestprefer
op_logical_and
id|perf
OG
id|bestperf
)paren
)paren
(brace
id|best
op_assign
op_star
id|algo
suffix:semicolon
id|bestprefer
op_assign
id|best-&gt;prefer
suffix:semicolon
id|bestperf
op_assign
id|perf
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;raid6: %-8s %5ld MB/s&bslash;n&quot;
comma
(paren
op_star
id|algo
)paren
op_member_access_from_pointer
id|name
comma
(paren
id|perf
op_star
id|HZ
)paren
op_rshift
(paren
l_int|20
op_minus
l_int|16
op_plus
id|RAID6_TIME_JIFFIES_LG2
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|best
)paren
id|printk
c_func
(paren
l_string|&quot;raid6: using algorithm %s (%ld MB/s)&bslash;n&quot;
comma
id|best-&gt;name
comma
(paren
id|bestperf
op_star
id|HZ
)paren
op_rshift
(paren
l_int|20
op_minus
l_int|16
op_plus
id|RAID6_TIME_JIFFIES_LG2
)paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;raid6: Yikes!  No algorithm found!&bslash;n&quot;
)paren
suffix:semicolon
id|raid6_call
op_assign
op_star
id|best
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|syndromes
comma
l_int|1
)paren
suffix:semicolon
r_return
id|best
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
