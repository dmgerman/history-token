multiline_comment|/**&n; * &bslash;file drm_memory.h &n; * Memory management wrappers for DRM.&n; *&n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
DECL|struct|drm_mem_stats
r_typedef
r_struct
id|drm_mem_stats
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|succeed_count
r_int
id|succeed_count
suffix:semicolon
DECL|member|free_count
r_int
id|free_count
suffix:semicolon
DECL|member|fail_count
r_int
id|fail_count
suffix:semicolon
DECL|member|bytes_allocated
r_int
r_int
id|bytes_allocated
suffix:semicolon
DECL|member|bytes_freed
r_int
r_int
id|bytes_freed
suffix:semicolon
DECL|typedef|drm_mem_stats_t
)brace
id|drm_mem_stats_t
suffix:semicolon
DECL|variable|mem_lock
r_static
id|spinlock_t
id|DRM
c_func
(paren
id|mem_lock
)paren
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|ram_available
r_static
r_int
r_int
id|DRM
c_func
(paren
id|ram_available
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* In pages */
DECL|variable|ram_used
r_static
r_int
r_int
id|DRM
c_func
(paren
id|ram_used
)paren
op_assign
l_int|0
suffix:semicolon
r_static
id|drm_mem_stats_t
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
)braket
op_assign
(brace
(braket
id|DRM_MEM_DMA
)braket
op_assign
(brace
l_string|&quot;dmabufs&quot;
)brace
comma
(braket
id|DRM_MEM_SAREA
)braket
op_assign
(brace
l_string|&quot;sareas&quot;
)brace
comma
(braket
id|DRM_MEM_DRIVER
)braket
op_assign
(brace
l_string|&quot;driver&quot;
)brace
comma
(braket
id|DRM_MEM_MAGIC
)braket
op_assign
(brace
l_string|&quot;magic&quot;
)brace
comma
(braket
id|DRM_MEM_IOCTLS
)braket
op_assign
(brace
l_string|&quot;ioctltab&quot;
)brace
comma
(braket
id|DRM_MEM_MAPS
)braket
op_assign
(brace
l_string|&quot;maplist&quot;
)brace
comma
(braket
id|DRM_MEM_VMAS
)braket
op_assign
(brace
l_string|&quot;vmalist&quot;
)brace
comma
(braket
id|DRM_MEM_BUFS
)braket
op_assign
(brace
l_string|&quot;buflist&quot;
)brace
comma
(braket
id|DRM_MEM_SEGS
)braket
op_assign
(brace
l_string|&quot;seglist&quot;
)brace
comma
(braket
id|DRM_MEM_PAGES
)braket
op_assign
(brace
l_string|&quot;pagelist&quot;
)brace
comma
(braket
id|DRM_MEM_FILES
)braket
op_assign
(brace
l_string|&quot;files&quot;
)brace
comma
(braket
id|DRM_MEM_QUEUES
)braket
op_assign
(brace
l_string|&quot;queues&quot;
)brace
comma
(braket
id|DRM_MEM_CMDS
)braket
op_assign
(brace
l_string|&quot;commands&quot;
)brace
comma
(braket
id|DRM_MEM_MAPPINGS
)braket
op_assign
(brace
l_string|&quot;mappings&quot;
)brace
comma
(braket
id|DRM_MEM_BUFLISTS
)braket
op_assign
(brace
l_string|&quot;buflists&quot;
)brace
comma
(braket
id|DRM_MEM_AGPLISTS
)braket
op_assign
(brace
l_string|&quot;agplist&quot;
)brace
comma
(braket
id|DRM_MEM_SGLISTS
)braket
op_assign
(brace
l_string|&quot;sglist&quot;
)brace
comma
(braket
id|DRM_MEM_TOTALAGP
)braket
op_assign
(brace
l_string|&quot;totalagp&quot;
)brace
comma
(braket
id|DRM_MEM_BOUNDAGP
)braket
op_assign
(brace
l_string|&quot;boundagp&quot;
)brace
comma
(braket
id|DRM_MEM_CTXBITMAP
)braket
op_assign
(brace
l_string|&quot;ctxbitmap&quot;
)brace
comma
(braket
id|DRM_MEM_CTXLIST
)braket
op_assign
(brace
l_string|&quot;ctxlist&quot;
)brace
comma
(braket
id|DRM_MEM_STUB
)braket
op_assign
(brace
l_string|&quot;stub&quot;
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
)brace
multiline_comment|/* Last entry must be null */
)brace
suffix:semicolon
DECL|function|mem_init
r_void
id|DRM
c_func
(paren
id|mem_init
)paren
(paren
r_void
)paren
(brace
id|drm_mem_stats_t
op_star
id|mem
suffix:semicolon
r_struct
id|sysinfo
id|si
suffix:semicolon
r_for
c_loop
(paren
id|mem
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
suffix:semicolon
id|mem-&gt;name
suffix:semicolon
op_increment
id|mem
)paren
(brace
id|mem-&gt;succeed_count
op_assign
l_int|0
suffix:semicolon
id|mem-&gt;free_count
op_assign
l_int|0
suffix:semicolon
id|mem-&gt;fail_count
op_assign
l_int|0
suffix:semicolon
id|mem-&gt;bytes_allocated
op_assign
l_int|0
suffix:semicolon
id|mem-&gt;bytes_freed
op_assign
l_int|0
suffix:semicolon
)brace
id|si_meminfo
c_func
(paren
op_amp
id|si
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|ram_available
)paren
op_assign
id|si.totalram
suffix:semicolon
id|DRM
c_func
(paren
id|ram_used
)paren
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* drm_mem_info is called whenever a process reads /dev/drm/mem. */
DECL|function|_mem_info
r_static
r_int
id|DRM
c_func
(paren
id|_mem_info
)paren
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|request
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
id|drm_mem_stats_t
op_star
id|pt
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|DRM_PROC_LIMIT
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|eof
op_assign
l_int|0
suffix:semicolon
op_star
id|start
op_assign
op_amp
id|buf
(braket
id|offset
)braket
suffix:semicolon
id|DRM_PROC_PRINT
c_func
(paren
l_string|&quot;&t;&t;  total counts&t;&t;&t;&quot;
l_string|&quot; |    outstanding  &bslash;n&quot;
)paren
suffix:semicolon
id|DRM_PROC_PRINT
c_func
(paren
l_string|&quot;type&t;   alloc freed fail&t;bytes&t;   freed&quot;
l_string|&quot; | allocs      bytes&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|DRM_PROC_PRINT
c_func
(paren
l_string|&quot;%-9.9s %5d %5d %4d %10lu kB         |&bslash;n&quot;
comma
l_string|&quot;system&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DRM
c_func
(paren
id|ram_available
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|DRM_PROC_PRINT
c_func
(paren
l_string|&quot;%-9.9s %5d %5d %4d %10lu kB         |&bslash;n&quot;
comma
l_string|&quot;locked&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|DRM
c_func
(paren
id|ram_used
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
id|DRM_PROC_PRINT
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
suffix:semicolon
id|pt-&gt;name
suffix:semicolon
id|pt
op_increment
)paren
(brace
id|DRM_PROC_PRINT
c_func
(paren
l_string|&quot;%-9.9s %5d %5d %4d %10lu %10lu | %6d %10ld&bslash;n&quot;
comma
id|pt-&gt;name
comma
id|pt-&gt;succeed_count
comma
id|pt-&gt;free_count
comma
id|pt-&gt;fail_count
comma
id|pt-&gt;bytes_allocated
comma
id|pt-&gt;bytes_freed
comma
id|pt-&gt;succeed_count
op_minus
id|pt-&gt;free_count
comma
(paren
r_int
)paren
id|pt-&gt;bytes_allocated
op_minus
(paren
r_int
)paren
id|pt-&gt;bytes_freed
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|request
op_plus
id|offset
)paren
r_return
id|request
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
op_minus
id|offset
suffix:semicolon
)brace
DECL|function|mem_info
r_int
id|DRM
c_func
(paren
id|mem_info
)paren
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|DRM
c_func
(paren
id|_mem_info
)paren
(paren
id|buf
comma
id|start
comma
id|offset
comma
id|len
comma
id|eof
comma
id|data
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|alloc
r_void
op_star
id|DRM
c_func
(paren
id|alloc
)paren
(paren
r_int
id|size
comma
r_int
id|area
)paren
(brace
r_void
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Allocating 0 bytes&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|bytes_allocated
op_add_assign
id|size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|pt
suffix:semicolon
)brace
DECL|function|calloc
r_void
op_star
id|DRM
c_func
(paren
id|calloc
)paren
(paren
r_int
id|nmemb
comma
r_int
id|size
comma
r_int
id|area
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
id|addr
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
id|nmemb
op_star
id|size
comma
id|area
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ne
l_int|NULL
)paren
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
l_int|0
comma
id|size
op_star
id|nmemb
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
DECL|function|realloc
r_void
op_star
id|DRM
c_func
(paren
id|realloc
)paren
(paren
r_void
op_star
id|oldpt
comma
r_int
id|oldsize
comma
r_int
id|size
comma
r_int
id|area
)paren
(brace
r_void
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
id|size
comma
id|area
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|oldpt
op_logical_and
id|oldsize
)paren
(brace
id|memcpy
c_func
(paren
id|pt
comma
id|oldpt
comma
id|oldsize
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|free
)paren
(paren
id|oldpt
comma
id|oldsize
comma
id|area
)paren
suffix:semicolon
)brace
r_return
id|pt
suffix:semicolon
)brace
DECL|function|free
r_void
id|DRM
c_func
(paren
id|free
)paren
(paren
r_void
op_star
id|pt
comma
r_int
id|size
comma
r_int
id|area
)paren
(brace
r_int
id|alloc_count
suffix:semicolon
r_int
id|free_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pt
)paren
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Attempt to free NULL pointer&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|pt
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|bytes_freed
op_add_assign
id|size
suffix:semicolon
id|free_count
op_assign
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|free_count
suffix:semicolon
id|alloc_count
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|succeed_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
OG
id|alloc_count
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Excess frees: %d frees, %d allocs&bslash;n&quot;
comma
id|free_count
comma
id|alloc_count
)paren
suffix:semicolon
)brace
)brace
DECL|function|alloc_pages
r_int
r_int
id|DRM
c_func
(paren
id|alloc_pages
)paren
(paren
r_int
id|order
comma
r_int
id|area
)paren
(brace
r_int
r_int
id|address
suffix:semicolon
r_int
r_int
id|bytes
op_assign
id|PAGE_SIZE
op_lshift
id|order
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|DRM
c_func
(paren
id|ram_used
)paren
op_rshift
id|PAGE_SHIFT
)paren
OG
(paren
id|DRM_RAM_PERCENT
op_star
id|DRM
c_func
(paren
id|ram_available
)paren
)paren
op_div
l_int|100
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|address
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|bytes_allocated
op_add_assign
id|bytes
suffix:semicolon
id|DRM
c_func
(paren
id|ram_used
)paren
op_add_assign
id|bytes
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
multiline_comment|/* Zero outside the lock */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|address
comma
l_int|0
comma
id|bytes
)paren
suffix:semicolon
multiline_comment|/* Reserve */
r_for
c_loop
(paren
id|addr
op_assign
id|address
comma
id|sz
op_assign
id|bytes
suffix:semicolon
id|sz
OG
l_int|0
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|sz
op_sub_assign
id|PAGE_SIZE
)paren
(brace
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
r_return
id|address
suffix:semicolon
)brace
DECL|function|free_pages
r_void
id|DRM
c_func
(paren
id|free_pages
)paren
(paren
r_int
r_int
id|address
comma
r_int
id|order
comma
r_int
id|area
)paren
(brace
r_int
r_int
id|bytes
op_assign
id|PAGE_SIZE
op_lshift
id|order
suffix:semicolon
r_int
id|alloc_count
suffix:semicolon
r_int
id|free_count
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|address
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Attempt to free address 0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Unreserve */
r_for
c_loop
(paren
id|addr
op_assign
id|address
comma
id|sz
op_assign
id|bytes
suffix:semicolon
id|sz
OG
l_int|0
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|sz
op_sub_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
id|free_pages
c_func
(paren
id|address
comma
id|order
)paren
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|free_count
op_assign
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|free_count
suffix:semicolon
id|alloc_count
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|area
)braket
dot
id|bytes_freed
op_add_assign
id|bytes
suffix:semicolon
id|DRM
c_func
(paren
id|ram_used
)paren
op_sub_assign
id|bytes
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
OG
id|alloc_count
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|area
comma
l_string|&quot;Excess frees: %d frees, %d allocs&bslash;n&quot;
comma
id|free_count
comma
id|alloc_count
)paren
suffix:semicolon
)brace
)brace
DECL|function|ioremap
r_void
op_star
id|DRM
c_func
(paren
id|ioremap
)paren
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_void
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_MAPPINGS
comma
l_string|&quot;Mapping 0 bytes at 0x%08lx&bslash;n&quot;
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt
op_assign
id|drm_ioremap
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|bytes_allocated
op_add_assign
id|size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|pt
suffix:semicolon
)brace
DECL|function|ioremap_nocache
r_void
op_star
id|DRM
c_func
(paren
id|ioremap_nocache
)paren
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_void
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_MAPPINGS
comma
l_string|&quot;Mapping 0 bytes at 0x%08lx&bslash;n&quot;
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt
op_assign
id|drm_ioremap_nocache
c_func
(paren
id|offset
comma
id|size
comma
id|dev
)paren
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|bytes_allocated
op_add_assign
id|size
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|pt
suffix:semicolon
)brace
DECL|function|ioremapfree
r_void
id|DRM
c_func
(paren
id|ioremapfree
)paren
(paren
r_void
op_star
id|pt
comma
r_int
r_int
id|size
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|alloc_count
suffix:semicolon
r_int
id|free_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pt
)paren
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_MAPPINGS
comma
l_string|&quot;Attempt to free NULL pointer&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|drm_ioremapfree
c_func
(paren
id|pt
comma
id|size
comma
id|dev
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|bytes_freed
op_add_assign
id|size
suffix:semicolon
id|free_count
op_assign
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|free_count
suffix:semicolon
id|alloc_count
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_MAPPINGS
)braket
dot
id|succeed_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
OG
id|alloc_count
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_MAPPINGS
comma
l_string|&quot;Excess frees: %d frees, %d allocs&bslash;n&quot;
comma
id|free_count
comma
id|alloc_count
)paren
suffix:semicolon
)brace
)brace
macro_line|#if __OS_HAS_AGP
DECL|function|alloc_agp
id|DRM_AGP_MEM
op_star
id|DRM
c_func
(paren
id|alloc_agp
)paren
(paren
r_int
id|pages
comma
id|u32
id|type
)paren
(brace
id|DRM_AGP_MEM
op_star
id|handle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pages
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_TOTALAGP
comma
l_string|&quot;Allocating 0 pages&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|handle
op_assign
id|DRM
c_func
(paren
id|agp_allocate_memory
)paren
(paren
id|pages
comma
id|type
)paren
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_TOTALAGP
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_TOTALAGP
)braket
dot
id|bytes_allocated
op_add_assign
id|pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|handle
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_TOTALAGP
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|free_agp
r_int
id|DRM
c_func
(paren
id|free_agp
)paren
(paren
id|DRM_AGP_MEM
op_star
id|handle
comma
r_int
id|pages
)paren
(brace
r_int
id|alloc_count
suffix:semicolon
r_int
id|free_count
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_TOTALAGP
comma
l_string|&quot;Attempt to free NULL AGP handle&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DRM
c_func
(paren
id|agp_free_memory
)paren
(paren
id|handle
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|free_count
op_assign
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_TOTALAGP
)braket
dot
id|free_count
suffix:semicolon
id|alloc_count
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_TOTALAGP
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_TOTALAGP
)braket
dot
id|bytes_freed
op_add_assign
id|pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
OG
id|alloc_count
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_TOTALAGP
comma
l_string|&quot;Excess frees: %d frees, %d allocs&bslash;n&quot;
comma
id|free_count
comma
id|alloc_count
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|bind_agp
r_int
id|DRM
c_func
(paren
id|bind_agp
)paren
(paren
id|DRM_AGP_MEM
op_star
id|handle
comma
r_int
r_int
id|start
)paren
(brace
r_int
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_BOUNDAGP
comma
l_string|&quot;Attempt to bind NULL AGP handle&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|retcode
op_assign
id|DRM
c_func
(paren
id|agp_bind_memory
)paren
(paren
id|handle
comma
id|start
)paren
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_BOUNDAGP
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_BOUNDAGP
)braket
dot
id|bytes_allocated
op_add_assign
id|handle-&gt;page_count
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_BOUNDAGP
)braket
dot
id|fail_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
DECL|function|unbind_agp
r_int
id|DRM
c_func
(paren
id|unbind_agp
)paren
(paren
id|DRM_AGP_MEM
op_star
id|handle
)paren
(brace
r_int
id|alloc_count
suffix:semicolon
r_int
id|free_count
suffix:semicolon
r_int
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_BOUNDAGP
comma
l_string|&quot;Attempt to unbind NULL AGP handle&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|retcode
op_assign
id|DRM
c_func
(paren
id|agp_unbind_memory
)paren
(paren
id|handle
)paren
)paren
)paren
r_return
id|retcode
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
id|free_count
op_assign
op_increment
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_BOUNDAGP
)braket
dot
id|free_count
suffix:semicolon
id|alloc_count
op_assign
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_BOUNDAGP
)braket
dot
id|succeed_count
suffix:semicolon
id|DRM
c_func
(paren
id|mem_stats
)paren
(braket
id|DRM_MEM_BOUNDAGP
)braket
dot
id|bytes_freed
op_add_assign
id|handle-&gt;page_count
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|DRM
c_func
(paren
id|mem_lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_count
OG
id|alloc_count
)paren
(brace
id|DRM_MEM_ERROR
c_func
(paren
id|DRM_MEM_BOUNDAGP
comma
l_string|&quot;Excess frees: %d frees, %d allocs&bslash;n&quot;
comma
id|free_count
comma
id|alloc_count
)paren
suffix:semicolon
)brace
r_return
id|retcode
suffix:semicolon
)brace
macro_line|#endif
eof
