multiline_comment|/*&n; *  linux/arch/arm/mm/mmap.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|COLOUR_ALIGN
mdefine_line|#define COLOUR_ALIGN(addr,pgoff)&t;&t;&bslash;&n;&t;((((addr)+SHMLBA-1)&amp;~(SHMLBA-1)) +&t;&bslash;&n;&t; (((pgoff)&lt;&lt;PAGE_SHIFT) &amp; (SHMLBA-1)))
multiline_comment|/*&n; * We need to ensure that shared mappings are correctly aligned to&n; * avoid aliasing issues with VIPT caches.  We need to ensure that&n; * a specific page of an object is always mapped at a multiple of&n; * SHMLBA bytes.&n; *&n; * We unconditionally provide this function for all cases, however&n; * in the VIVT case, we optimise out the alignment rules.&n; */
r_int
r_int
DECL|function|arch_get_unmapped_area
id|arch_get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|start_addr
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_V6
r_int
r_int
id|cache_type
suffix:semicolon
r_int
id|do_align
op_assign
l_int|0
comma
id|aliasing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We only need to do colour alignment if either the I or D&n;&t; * caches alias.  This is indicated by bits 9 and 21 of the&n;&t; * cache type register.&n;&t; */
id|cache_type
op_assign
id|read_cpuid
c_func
(paren
id|CPUID_CACHETYPE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache_type
op_ne
id|read_cpuid
c_func
(paren
id|CPUID_ID
)paren
)paren
(brace
id|aliasing
op_assign
(paren
id|cache_type
op_or
id|cache_type
op_rshift
l_int|12
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aliasing
)paren
id|do_align
op_assign
id|filp
op_logical_or
id|flags
op_amp
id|MAP_SHARED
suffix:semicolon
)brace
macro_line|#else
mdefine_line|#define do_align 0
mdefine_line|#define aliasing 0
macro_line|#endif
multiline_comment|/*&n;&t; * We should enforce the MAP_FIXED case.  However, currently&n;&t; * the generic kernel code doesn&squot;t allow us to handle this.&n;&t; */
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
(brace
r_if
c_cond
(paren
id|aliasing
op_logical_and
id|flags
op_amp
id|MAP_SHARED
op_logical_and
id|addr
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
(brace
r_if
c_cond
(paren
id|do_align
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
comma
id|pgoff
)paren
suffix:semicolon
r_else
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
op_ge
id|addr
op_logical_and
(paren
op_logical_neg
id|vma
op_logical_or
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
)paren
r_return
id|addr
suffix:semicolon
)brace
id|start_addr
op_assign
id|addr
op_assign
id|mm-&gt;free_area_cache
suffix:semicolon
id|full_search
suffix:colon
r_if
c_cond
(paren
id|do_align
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
comma
id|pgoff
)paren
suffix:semicolon
r_else
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vma || addr &lt; vma-&gt;vm_end). */
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
OL
id|addr
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Start a new search - just in case we missed&n;&t;&t;&t; * some holes.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|start_addr
op_ne
id|TASK_UNMAPPED_BASE
)paren
(brace
id|start_addr
op_assign
id|addr
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
r_goto
id|full_search
suffix:semicolon
)brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Remember the place where we stopped the search:&n;&t;&t;&t; */
id|mm-&gt;free_area_cache
op_assign
id|addr
op_plus
id|len
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
id|addr
op_assign
id|vma-&gt;vm_end
suffix:semicolon
r_if
c_cond
(paren
id|do_align
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
comma
id|pgoff
)paren
suffix:semicolon
)brace
)brace
eof
