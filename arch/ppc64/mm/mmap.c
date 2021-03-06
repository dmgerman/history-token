multiline_comment|/*&n; *  linux/arch/ppc64/mm/mmap.c&n; *&n; *  flexible mmap layout support&n; *&n; * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.&n; * All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *&n; * Started by Ingo Molnar &lt;mingo@elte.hu&gt;&n; */
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * Top of mmap area (just below the process stack).&n; *&n; * Leave an at least ~128 MB hole.&n; */
DECL|macro|MIN_GAP
mdefine_line|#define MIN_GAP (128*1024*1024)
DECL|macro|MAX_GAP
mdefine_line|#define MAX_GAP (TASK_SIZE/6*5)
DECL|function|mmap_base
r_static
r_inline
r_int
r_int
id|mmap_base
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|gap
op_assign
id|current-&gt;signal-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|gap
OL
id|MIN_GAP
)paren
id|gap
op_assign
id|MIN_GAP
suffix:semicolon
r_else
r_if
c_cond
(paren
id|gap
OG
id|MAX_GAP
)paren
id|gap
op_assign
id|MAX_GAP
suffix:semicolon
r_return
id|TASK_SIZE
op_minus
(paren
id|gap
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
DECL|function|mmap_is_legacy
r_static
r_inline
r_int
id|mmap_is_legacy
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Force standard allocation for 64 bit programs.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;personality
op_amp
id|ADDR_COMPAT_LAYOUT
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_cur
op_eq
id|RLIM_INFINITY
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|sysctl_legacy_va_layout
suffix:semicolon
)brace
multiline_comment|/*&n; * This function, called very early during the creation of a new&n; * process VM image, sets up which VM layout function to use:&n; */
DECL|function|arch_pick_mmap_layout
r_void
id|arch_pick_mmap_layout
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/*&n;&t; * Fall back to the standard layout if the personality&n;&t; * bit is set, or if the expected stack growth is unlimited:&n;&t; */
r_if
c_cond
(paren
id|mmap_is_legacy
c_func
(paren
)paren
)paren
(brace
id|mm-&gt;mmap_base
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
id|mm-&gt;get_unmapped_area
op_assign
id|arch_get_unmapped_area
suffix:semicolon
id|mm-&gt;unmap_area
op_assign
id|arch_unmap_area
suffix:semicolon
)brace
r_else
(brace
id|mm-&gt;mmap_base
op_assign
id|mmap_base
c_func
(paren
)paren
suffix:semicolon
id|mm-&gt;get_unmapped_area
op_assign
id|arch_get_unmapped_area_topdown
suffix:semicolon
id|mm-&gt;unmap_area
op_assign
id|arch_unmap_area_topdown
suffix:semicolon
)brace
)brace
eof
