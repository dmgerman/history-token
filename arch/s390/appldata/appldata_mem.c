multiline_comment|/*&n; * arch/s390/appldata/appldata_mem.c&n; *&n; * Data gathering module for Linux-VM Monitor Stream, Stage 1.&n; * Collects data related to memory management.&n; *&n; * Copyright (C) 2003 IBM Corporation, IBM Deutschland Entwicklung GmbH.&n; *&n; * Author: Gerald Schaefer &lt;geraldsc@de.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &quot;appldata.h&quot;
DECL|macro|MY_PRINT_NAME
mdefine_line|#define MY_PRINT_NAME &quot;appldata_mem&quot;&t;&t;/* for debug messages, etc. */
DECL|macro|P2K
mdefine_line|#define P2K(x) ((x) &lt;&lt; (PAGE_SHIFT - 10))&t;/* Converts #Pages to KB */
multiline_comment|/*&n; * Memory data&n; *&n; * This is accessed as binary data by z/VM. If changes to it can&squot;t be avoided,&n; * the structure version (product ID, see appldata_base.c) needs to be changed&n; * as well and all documentation and z/VM applications using it must be&n; * updated.&n; *&n; * The record layout is documented in the Linux for zSeries Device Drivers&n; * book:&n; * http://oss.software.ibm.com/developerworks/opensource/linux390/index.shtml&n; */
DECL|struct|appldata_mem_data
r_struct
id|appldata_mem_data
(brace
DECL|member|timestamp
id|u64
id|timestamp
suffix:semicolon
DECL|member|sync_count_1
id|u32
id|sync_count_1
suffix:semicolon
multiline_comment|/* after VM collected the record data, */
DECL|member|sync_count_2
id|u32
id|sync_count_2
suffix:semicolon
multiline_comment|/* sync_count_1 and sync_count_2 should be the&n;&t;&t;&t;&t;   same. If not, the record has been updated on&n;&t;&t;&t;&t;   the Linux side while VM was collecting the&n;&t;&t;&t;&t;   (possibly corrupt) data */
DECL|member|pgpgin
id|u64
id|pgpgin
suffix:semicolon
multiline_comment|/* data read from disk  */
DECL|member|pgpgout
id|u64
id|pgpgout
suffix:semicolon
multiline_comment|/* data written to disk */
DECL|member|pswpin
id|u64
id|pswpin
suffix:semicolon
multiline_comment|/* pages swapped in  */
DECL|member|pswpout
id|u64
id|pswpout
suffix:semicolon
multiline_comment|/* pages swapped out */
DECL|member|sharedram
id|u64
id|sharedram
suffix:semicolon
multiline_comment|/* sharedram is currently set to 0 */
DECL|member|totalram
id|u64
id|totalram
suffix:semicolon
multiline_comment|/* total main memory size */
DECL|member|freeram
id|u64
id|freeram
suffix:semicolon
multiline_comment|/* free main memory size  */
DECL|member|totalhigh
id|u64
id|totalhigh
suffix:semicolon
multiline_comment|/* total high memory size */
DECL|member|freehigh
id|u64
id|freehigh
suffix:semicolon
multiline_comment|/* free high memory size  */
DECL|member|bufferram
id|u64
id|bufferram
suffix:semicolon
multiline_comment|/* memory reserved for buffers, free cache */
DECL|member|cached
id|u64
id|cached
suffix:semicolon
multiline_comment|/* size of (used) cache, w/o buffers */
DECL|member|totalswap
id|u64
id|totalswap
suffix:semicolon
multiline_comment|/* total swap space size */
DECL|member|freeswap
id|u64
id|freeswap
suffix:semicolon
multiline_comment|/* free swap space */
singleline_comment|// New in 2.6 --&gt;
DECL|member|pgalloc
id|u64
id|pgalloc
suffix:semicolon
multiline_comment|/* page allocations */
DECL|member|pgfault
id|u64
id|pgfault
suffix:semicolon
multiline_comment|/* page faults (major+minor) */
DECL|member|pgmajfault
id|u64
id|pgmajfault
suffix:semicolon
multiline_comment|/* page faults (major only) */
singleline_comment|// &lt;-- New in 2.6
DECL|variable|appldata_mem_data
)brace
id|appldata_mem_data
suffix:semicolon
DECL|function|appldata_debug_print
r_static
r_inline
r_void
id|appldata_debug_print
c_func
(paren
r_struct
id|appldata_mem_data
op_star
id|mem_data
)paren
(brace
id|P_DEBUG
c_func
(paren
l_string|&quot;--- MEM - RECORD ---&bslash;n&quot;
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pgpgin     = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;pgpgin
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pgpgout    = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;pgpgout
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pswpin     = %8lu Pages&bslash;n&quot;
comma
id|mem_data-&gt;pswpin
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pswpout    = %8lu Pages&bslash;n&quot;
comma
id|mem_data-&gt;pswpout
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pgalloc    = %8lu &bslash;n&quot;
comma
id|mem_data-&gt;pgalloc
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pgfault    = %8lu &bslash;n&quot;
comma
id|mem_data-&gt;pgfault
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;pgmajfault = %8lu &bslash;n&quot;
comma
id|mem_data-&gt;pgmajfault
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;sharedram  = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;sharedram
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;totalram   = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;totalram
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;freeram    = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;freeram
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;totalhigh  = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;totalhigh
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;freehigh   = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;freehigh
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;bufferram  = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;bufferram
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;cached     = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;cached
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;totalswap  = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;totalswap
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;freeswap   = %8lu KB&bslash;n&quot;
comma
id|mem_data-&gt;freeswap
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;sync_count_1 = %u&bslash;n&quot;
comma
id|mem_data-&gt;sync_count_1
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;sync_count_2 = %u&bslash;n&quot;
comma
id|mem_data-&gt;sync_count_2
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;timestamp    = %lX&bslash;n&quot;
comma
id|mem_data-&gt;timestamp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * appldata_get_mem_data()&n; *&n; * gather memory data&n; */
DECL|function|appldata_get_mem_data
r_static
r_void
id|appldata_get_mem_data
c_func
(paren
r_void
op_star
id|data
)paren
(brace
multiline_comment|/*&n;&t; * don&squot;t put large structures on the stack, we are&n;&t; * serialized through the appldata_ops_lock and can use static&n;&t; */
r_static
r_struct
id|sysinfo
id|val
suffix:semicolon
r_static
r_struct
id|page_state
id|ps
suffix:semicolon
r_struct
id|appldata_mem_data
op_star
id|mem_data
suffix:semicolon
id|mem_data
op_assign
id|data
suffix:semicolon
id|mem_data-&gt;sync_count_1
op_increment
suffix:semicolon
id|get_full_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
id|mem_data-&gt;pgpgin
op_assign
id|ps.pgpgin
op_rshift
l_int|1
suffix:semicolon
id|mem_data-&gt;pgpgout
op_assign
id|ps.pgpgout
op_rshift
l_int|1
suffix:semicolon
id|mem_data-&gt;pswpin
op_assign
id|ps.pswpin
suffix:semicolon
id|mem_data-&gt;pswpout
op_assign
id|ps.pswpout
suffix:semicolon
id|mem_data-&gt;pgalloc
op_assign
id|ps.pgalloc_high
op_plus
id|ps.pgalloc_normal
op_plus
id|ps.pgalloc_dma
suffix:semicolon
id|mem_data-&gt;pgfault
op_assign
id|ps.pgfault
suffix:semicolon
id|mem_data-&gt;pgmajfault
op_assign
id|ps.pgmajfault
suffix:semicolon
id|si_meminfo
c_func
(paren
op_amp
id|val
)paren
suffix:semicolon
id|mem_data-&gt;sharedram
op_assign
id|val.sharedram
suffix:semicolon
id|mem_data-&gt;totalram
op_assign
id|P2K
c_func
(paren
id|val.totalram
)paren
suffix:semicolon
id|mem_data-&gt;freeram
op_assign
id|P2K
c_func
(paren
id|val.freeram
)paren
suffix:semicolon
id|mem_data-&gt;totalhigh
op_assign
id|P2K
c_func
(paren
id|val.totalhigh
)paren
suffix:semicolon
id|mem_data-&gt;freehigh
op_assign
id|P2K
c_func
(paren
id|val.freehigh
)paren
suffix:semicolon
id|mem_data-&gt;bufferram
op_assign
id|P2K
c_func
(paren
id|val.bufferram
)paren
suffix:semicolon
id|mem_data-&gt;cached
op_assign
id|P2K
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|nr_pagecache
)paren
op_minus
id|val.bufferram
)paren
suffix:semicolon
id|si_swapinfo
c_func
(paren
op_amp
id|val
)paren
suffix:semicolon
id|mem_data-&gt;totalswap
op_assign
id|P2K
c_func
(paren
id|val.totalswap
)paren
suffix:semicolon
id|mem_data-&gt;freeswap
op_assign
id|P2K
c_func
(paren
id|val.freeswap
)paren
suffix:semicolon
id|mem_data-&gt;timestamp
op_assign
id|get_clock
c_func
(paren
)paren
suffix:semicolon
id|mem_data-&gt;sync_count_2
op_increment
suffix:semicolon
macro_line|#ifdef APPLDATA_DEBUG
id|appldata_debug_print
c_func
(paren
id|mem_data
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|ops
r_static
r_struct
id|appldata_ops
id|ops
op_assign
(brace
dot
id|ctl_nr
op_assign
id|CTL_APPLDATA_MEM
comma
dot
id|name
op_assign
l_string|&quot;mem&quot;
comma
dot
id|record_nr
op_assign
id|APPLDATA_RECORD_MEM_ID
comma
dot
id|size
op_assign
r_sizeof
(paren
r_struct
id|appldata_mem_data
)paren
comma
dot
id|callback
op_assign
op_amp
id|appldata_get_mem_data
comma
dot
id|data
op_assign
op_amp
id|appldata_mem_data
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * appldata_mem_init()&n; *&n; * init_data, register ops&n; */
DECL|function|appldata_mem_init
r_static
r_int
id|__init
id|appldata_mem_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;sizeof(mem) = %lu&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|appldata_mem_data
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|appldata_register_ops
c_func
(paren
op_amp
id|ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;Error registering ops, rc = %i&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
r_else
(brace
id|P_DEBUG
c_func
(paren
l_string|&quot;%s-ops registered!&bslash;n&quot;
comma
id|ops.name
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * appldata_mem_exit()&n; *&n; * unregister ops&n; */
DECL|function|appldata_mem_exit
r_static
r_void
id|__exit
id|appldata_mem_exit
c_func
(paren
r_void
)paren
(brace
id|appldata_unregister_ops
c_func
(paren
op_amp
id|ops
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;%s-ops unregistered!&bslash;n&quot;
comma
id|ops.name
)paren
suffix:semicolon
)brace
DECL|variable|appldata_mem_init
id|module_init
c_func
(paren
id|appldata_mem_init
)paren
suffix:semicolon
DECL|variable|appldata_mem_exit
id|module_exit
c_func
(paren
id|appldata_mem_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerald Schaefer&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Linux-VM Monitor Stream, MEMORY statistics&quot;
)paren
suffix:semicolon
eof
