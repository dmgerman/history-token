multiline_comment|/* drm_vm.h -- Memory mapping for DRM -*- linux-c -*-&n; * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;drmP.h&quot;
DECL|variable|vm_ops
r_struct
id|vm_operations_struct
id|DRM
c_func
(paren
id|vm_ops
)paren
op_assign
(brace
id|nopage
suffix:colon
id|DRM
c_func
(paren
id|vm_nopage
)paren
comma
id|open
suffix:colon
id|DRM
c_func
(paren
id|vm_open
)paren
comma
id|close
suffix:colon
id|DRM
c_func
(paren
id|vm_close
)paren
comma
)brace
suffix:semicolon
DECL|variable|vm_shm_ops
r_struct
id|vm_operations_struct
id|DRM
c_func
(paren
id|vm_shm_ops
)paren
op_assign
(brace
id|nopage
suffix:colon
id|DRM
c_func
(paren
id|vm_shm_nopage
)paren
comma
id|open
suffix:colon
id|DRM
c_func
(paren
id|vm_open
)paren
comma
id|close
suffix:colon
id|DRM
c_func
(paren
id|vm_shm_close
)paren
comma
)brace
suffix:semicolon
DECL|variable|vm_dma_ops
r_struct
id|vm_operations_struct
id|DRM
c_func
(paren
id|vm_dma_ops
)paren
op_assign
(brace
id|nopage
suffix:colon
id|DRM
c_func
(paren
id|vm_dma_nopage
)paren
comma
id|open
suffix:colon
id|DRM
c_func
(paren
id|vm_open
)paren
comma
id|close
suffix:colon
id|DRM
c_func
(paren
id|vm_close
)paren
comma
)brace
suffix:semicolon
DECL|variable|vm_sg_ops
r_struct
id|vm_operations_struct
id|DRM
c_func
(paren
id|vm_sg_ops
)paren
op_assign
(brace
id|nopage
suffix:colon
id|DRM
c_func
(paren
id|vm_sg_nopage
)paren
comma
id|open
suffix:colon
id|DRM
c_func
(paren
id|vm_open
)paren
comma
id|close
suffix:colon
id|DRM
c_func
(paren
id|vm_close
)paren
comma
)brace
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
DECL|function|vm_nopage
r_int
r_int
id|DRM
c_func
(paren
id|vm_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#else
multiline_comment|/* Return type changed in 2.3.23 */
r_struct
id|page
op_star
id|DRM
c_func
(paren
id|vm_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#endif
(brace
macro_line|#if __REALLY_HAVE_AGP
id|drm_file_t
op_star
id|priv
op_assign
id|vma-&gt;vm_file-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_map_t
op_star
id|map
op_assign
l_int|NULL
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
multiline_comment|/*&n;         * Find the right map&n;         */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp-&gt;cant_use_aperture
)paren
(brace
r_goto
id|vm_nopage_error
suffix:semicolon
)brace
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|dev-&gt;maplist-&gt;head
)paren
(brace
id|r_list
op_assign
(paren
id|drm_map_list_t
op_star
)paren
id|list
suffix:semicolon
id|map
op_assign
id|r_list-&gt;map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;offset
op_eq
id|VM_OFFSET
c_func
(paren
id|vma
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map
op_logical_and
id|map-&gt;type
op_eq
id|_DRM_AGP
)paren
(brace
r_int
r_int
id|offset
op_assign
id|address
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_int
r_int
id|baddr
op_assign
id|VM_OFFSET
c_func
(paren
id|vma
)paren
op_plus
id|offset
suffix:semicolon
r_struct
id|drm_agp_mem
op_star
id|agpmem
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
macro_line|#if __alpha__
multiline_comment|/*&n;                 * Adjust to a bus-relative address&n;                 */
id|baddr
op_sub_assign
id|dev-&gt;hose-&gt;mem_space-&gt;start
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;                 * It&squot;s AGP memory - find the real physical page to map&n;                 */
r_for
c_loop
(paren
id|agpmem
op_assign
id|dev-&gt;agp-&gt;memory
suffix:semicolon
id|agpmem
suffix:semicolon
id|agpmem
op_assign
id|agpmem-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|agpmem-&gt;bound
op_le
id|baddr
op_logical_and
id|agpmem-&gt;bound
op_plus
id|agpmem-&gt;pages
op_star
id|PAGE_SIZE
OG
id|baddr
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|agpmem
)paren
r_goto
id|vm_nopage_error
suffix:semicolon
multiline_comment|/*&n;                 * Get the page, inc the use count, and return it&n;                 */
id|offset
op_assign
(paren
id|baddr
op_minus
id|agpmem-&gt;bound
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|agpmem-&gt;memory-&gt;memory
(braket
id|offset
)braket
op_and_assign
id|dev-&gt;agp-&gt;page_mask
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|agpmem-&gt;memory-&gt;memory
(braket
id|offset
)braket
)paren
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;baddr = 0x%lx page = 0x%p, offset = 0x%lx&bslash;n&quot;
comma
id|baddr
comma
id|__va
c_func
(paren
id|agpmem-&gt;memory-&gt;memory
(braket
id|offset
)braket
)paren
comma
id|offset
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#else
r_return
id|page
suffix:semicolon
macro_line|#endif
)brace
id|vm_nopage_error
suffix:colon
macro_line|#endif /* __REALLY_HAVE_AGP */
r_return
id|NOPAGE_SIGBUS
suffix:semicolon
multiline_comment|/* Disallow mremap */
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
DECL|function|vm_shm_nopage
r_int
r_int
id|DRM
c_func
(paren
id|vm_shm_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#else
multiline_comment|/* Return type changed in 2.3.23 */
r_struct
id|page
op_star
id|DRM
c_func
(paren
id|vm_shm_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#endif
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
id|drm_map_t
op_star
id|map
op_assign
(paren
id|drm_map_t
op_star
)paren
id|vma-&gt;vm_private_data
suffix:semicolon
macro_line|#else
id|drm_map_t
op_star
id|map
op_assign
(paren
id|drm_map_t
op_star
)paren
id|vma-&gt;vm_pte
suffix:semicolon
macro_line|#endif
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
comma
id|entry
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|address
OG
id|vma-&gt;vm_end
)paren
r_return
id|NOPAGE_SIGBUS
suffix:semicolon
multiline_comment|/* Disallow mremap */
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_return
id|NOPAGE_OOM
suffix:semicolon
multiline_comment|/* Nothing allocated */
id|offset
op_assign
id|address
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|i
op_assign
(paren
r_int
r_int
)paren
id|map-&gt;handle
op_plus
id|offset
suffix:semicolon
multiline_comment|/* We have to walk page tables here because we need large SAREA&squot;s, and&n;&t; * they need to be virtually contiguous in kernel space.&n;&t; */
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_present
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|oom
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|oom
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|i
)paren
suffix:semicolon
id|entry
op_assign
op_star
id|pte
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|entry
)paren
)paren
r_goto
id|oom
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
id|entry
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;shm_nopage 0x%lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#else
r_return
id|page
suffix:semicolon
macro_line|#endif
id|oom
suffix:colon
r_return
id|NOPAGE_OOM
suffix:semicolon
)brace
multiline_comment|/* Special close routine which deletes map information if we are the last&n; * person to close a mapping and its not in the global maplist.&n; */
DECL|function|vm_shm_close
r_void
id|DRM
c_func
(paren
id|vm_shm_close
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|vma-&gt;vm_file-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_vma_entry_t
op_star
id|pt
comma
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|found_maps
op_assign
l_int|0
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;0x%08lx,0x%08lx&bslash;n&quot;
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020333
id|MOD_DEC_USE_COUNT
suffix:semicolon
multiline_comment|/* Needed before Linux 2.3.51 */
macro_line|#endif
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;vma_count
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
id|map
op_assign
id|vma-&gt;vm_private_data
suffix:semicolon
macro_line|#else
id|map
op_assign
id|vma-&gt;vm_pte
suffix:semicolon
macro_line|#endif
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|dev-&gt;vmalist
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|pt
suffix:semicolon
id|pt
op_assign
id|next
)paren
(brace
id|next
op_assign
id|pt-&gt;next
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
r_if
c_cond
(paren
id|pt-&gt;vma-&gt;vm_private_data
op_eq
id|map
)paren
id|found_maps
op_increment
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|pt-&gt;vma-&gt;vm_pte
op_eq
id|map
)paren
id|found_maps
op_increment
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|pt-&gt;vma
op_eq
id|vma
)paren
(brace
r_if
c_cond
(paren
id|prev
)paren
(brace
id|prev-&gt;next
op_assign
id|pt-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;vmalist
op_assign
id|pt-&gt;next
suffix:semicolon
)brace
id|DRM
c_func
(paren
id|free
)paren
(paren
id|pt
comma
r_sizeof
(paren
op_star
id|pt
)paren
comma
id|DRM_MEM_VMAS
)paren
suffix:semicolon
)brace
r_else
(brace
id|prev
op_assign
id|pt
suffix:semicolon
)brace
)brace
multiline_comment|/* We were the only map that was found */
r_if
c_cond
(paren
id|found_maps
op_eq
l_int|1
op_logical_and
id|map-&gt;flags
op_amp
id|_DRM_REMOVABLE
)paren
(brace
multiline_comment|/* Check to see if we are in the maplist, if we are not, then&n;&t;&t; * we delete this mappings information.&n;&t;&t; */
id|found_maps
op_assign
l_int|0
suffix:semicolon
id|list
op_assign
op_amp
id|dev-&gt;maplist-&gt;head
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|dev-&gt;maplist-&gt;head
)paren
(brace
id|r_list
op_assign
(paren
id|drm_map_list_t
op_star
)paren
id|list
suffix:semicolon
r_if
c_cond
(paren
id|r_list-&gt;map
op_eq
id|map
)paren
id|found_maps
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found_maps
)paren
(brace
r_switch
c_cond
(paren
id|map-&gt;type
)paren
(brace
r_case
id|_DRM_REGISTERS
suffix:colon
r_case
id|_DRM_FRAME_BUFFER
suffix:colon
macro_line|#if __REALLY_HAVE_MTRR
r_if
c_cond
(paren
id|map-&gt;mtrr
op_ge
l_int|0
)paren
(brace
r_int
id|retcode
suffix:semicolon
id|retcode
op_assign
id|mtrr_del
c_func
(paren
id|map-&gt;mtrr
comma
id|map-&gt;offset
comma
id|map-&gt;size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;mtrr_del = %d&bslash;n&quot;
comma
id|retcode
)paren
suffix:semicolon
)brace
macro_line|#endif
id|DRM
c_func
(paren
id|ioremapfree
)paren
(paren
id|map-&gt;handle
comma
id|map-&gt;size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_SHM
suffix:colon
id|vfree
c_func
(paren
id|map-&gt;handle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_AGP
suffix:colon
r_case
id|_DRM_SCATTER_GATHER
suffix:colon
r_break
suffix:semicolon
)brace
id|DRM
c_func
(paren
id|free
)paren
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
DECL|function|vm_dma_nopage
r_int
r_int
id|DRM
c_func
(paren
id|vm_dma_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#else
multiline_comment|/* Return type changed in 2.3.23 */
r_struct
id|page
op_star
id|DRM
c_func
(paren
id|vm_dma_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#endif
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|vma-&gt;vm_file-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|page_nr
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
id|NOPAGE_SIGBUS
suffix:semicolon
multiline_comment|/* Error */
r_if
c_cond
(paren
id|address
OG
id|vma-&gt;vm_end
)paren
r_return
id|NOPAGE_SIGBUS
suffix:semicolon
multiline_comment|/* Disallow mremap */
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;pagelist
)paren
r_return
id|NOPAGE_OOM
suffix:semicolon
multiline_comment|/* Nothing allocated */
id|offset
op_assign
id|address
op_minus
id|vma-&gt;vm_start
suffix:semicolon
multiline_comment|/* vm_[pg]off[set] should be 0 */
id|page_nr
op_assign
id|offset
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
(paren
id|dma-&gt;pagelist
(braket
id|page_nr
)braket
op_plus
(paren
id|offset
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
)paren
)paren
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;dma_nopage 0x%lx (page %lu)&bslash;n&quot;
comma
id|address
comma
id|page_nr
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#else
r_return
id|page
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
DECL|function|vm_sg_nopage
r_int
r_int
id|DRM
c_func
(paren
id|vm_sg_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#else
multiline_comment|/* Return type changed in 2.3.23 */
r_struct
id|page
op_star
id|DRM
c_func
(paren
id|vm_sg_nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|unused
)paren
macro_line|#endif
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
id|drm_map_t
op_star
id|map
op_assign
(paren
id|drm_map_t
op_star
)paren
id|vma-&gt;vm_private_data
suffix:semicolon
macro_line|#else
id|drm_map_t
op_star
id|map
op_assign
(paren
id|drm_map_t
op_star
)paren
id|vma-&gt;vm_pte
suffix:semicolon
macro_line|#endif
id|drm_file_t
op_star
id|priv
op_assign
id|vma-&gt;vm_file-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_sg_mem_t
op_star
id|entry
op_assign
id|dev-&gt;sg
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|map_offset
suffix:semicolon
r_int
r_int
id|page_offset
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
id|NOPAGE_SIGBUS
suffix:semicolon
multiline_comment|/* Error */
r_if
c_cond
(paren
id|address
OG
id|vma-&gt;vm_end
)paren
r_return
id|NOPAGE_SIGBUS
suffix:semicolon
multiline_comment|/* Disallow mremap */
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;pagelist
)paren
r_return
id|NOPAGE_OOM
suffix:semicolon
multiline_comment|/* Nothing allocated */
id|offset
op_assign
id|address
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|map_offset
op_assign
id|map-&gt;offset
op_minus
id|dev-&gt;sg-&gt;handle
suffix:semicolon
id|page_offset
op_assign
(paren
id|offset
op_rshift
id|PAGE_SHIFT
)paren
op_plus
(paren
id|map_offset
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|page
op_assign
id|entry-&gt;pagelist
(braket
id|page_offset
)braket
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020317
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#else
r_return
id|page
suffix:semicolon
macro_line|#endif
)brace
DECL|function|vm_open
r_void
id|DRM
c_func
(paren
id|vm_open
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|vma-&gt;vm_file-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_vma_entry_t
op_star
id|vma_entry
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;0x%08lx,0x%08lx&bslash;n&quot;
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;vma_count
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020333
multiline_comment|/* The map can exist after the fd is closed. */
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* Needed before Linux 2.3.51 */
macro_line|#endif
id|vma_entry
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
r_sizeof
(paren
op_star
id|vma_entry
)paren
comma
id|DRM_MEM_VMAS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma_entry
)paren
(brace
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|vma_entry-&gt;vma
op_assign
id|vma
suffix:semicolon
id|vma_entry-&gt;next
op_assign
id|dev-&gt;vmalist
suffix:semicolon
id|vma_entry-&gt;pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|dev-&gt;vmalist
op_assign
id|vma_entry
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|vm_close
r_void
id|DRM
c_func
(paren
id|vm_close
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|vma-&gt;vm_file-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_vma_entry_t
op_star
id|pt
comma
op_star
id|prev
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;0x%08lx,0x%08lx&bslash;n&quot;
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020333
id|MOD_DEC_USE_COUNT
suffix:semicolon
multiline_comment|/* Needed before Linux 2.3.51 */
macro_line|#endif
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;vma_count
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|dev-&gt;vmalist
comma
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|pt
suffix:semicolon
id|prev
op_assign
id|pt
comma
id|pt
op_assign
id|pt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|pt-&gt;vma
op_eq
id|vma
)paren
(brace
r_if
c_cond
(paren
id|prev
)paren
(brace
id|prev-&gt;next
op_assign
id|pt-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;vmalist
op_assign
id|pt-&gt;next
suffix:semicolon
)brace
id|DRM
c_func
(paren
id|free
)paren
(paren
id|pt
comma
r_sizeof
(paren
op_star
id|pt
)paren
comma
id|DRM_MEM_VMAS
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
)brace
DECL|function|mmap_dma
r_int
id|DRM
c_func
(paren
id|mmap_dma
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
suffix:semicolon
r_int
r_int
id|length
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;start = 0x%lx, end = 0x%lx, offset = 0x%lx&bslash;n&quot;
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
comma
id|VM_OFFSET
c_func
(paren
id|vma
)paren
)paren
suffix:semicolon
multiline_comment|/* Length must match exact page count */
r_if
c_cond
(paren
op_logical_neg
id|dma
op_logical_or
(paren
id|length
op_rshift
id|PAGE_SHIFT
)paren
op_ne
id|dma-&gt;page_count
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|DRM
c_func
(paren
id|vm_dma_ops
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
multiline_comment|/* Don&squot;t swap */
macro_line|#if LINUX_VERSION_CODE &lt; 0x020203 /* KERNEL_VERSION(2,2,3) */
multiline_comment|/* In Linux 2.2.3 and above, this is&n;&t;&t;&t;&t;   handled in do_mmap() in mm/mmap.c. */
op_increment
id|filp-&gt;f_count
suffix:semicolon
macro_line|#endif
id|vma-&gt;vm_file
op_assign
id|filp
suffix:semicolon
multiline_comment|/* Needed for drm_vm_open() */
id|DRM
c_func
(paren
id|vm_open
)paren
(paren
id|vma
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef DRIVER_GET_MAP_OFS
DECL|macro|DRIVER_GET_MAP_OFS
mdefine_line|#define DRIVER_GET_MAP_OFS()&t;(map-&gt;offset)
macro_line|#endif
macro_line|#ifndef DRIVER_GET_REG_OFS
macro_line|#ifdef __alpha__
DECL|macro|DRIVER_GET_REG_OFS
mdefine_line|#define DRIVER_GET_REG_OFS()&t;(dev-&gt;hose-&gt;dense_mem_base -&t;&bslash;&n;&t;&t;&t;&t; dev-&gt;hose-&gt;mem_space-&gt;start)
macro_line|#else
DECL|macro|DRIVER_GET_REG_OFS
mdefine_line|#define DRIVER_GET_REG_OFS()&t;0
macro_line|#endif
macro_line|#endif
DECL|function|mmap
r_int
id|DRM
c_func
(paren
id|mmap
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_map_t
op_star
id|map
op_assign
l_int|NULL
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;start = 0x%lx, end = 0x%lx, offset = 0x%lx&bslash;n&quot;
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
comma
id|VM_OFFSET
c_func
(paren
id|vma
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv-&gt;authenticated
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|VM_OFFSET
c_func
(paren
id|vma
)paren
)paren
r_return
id|DRM
c_func
(paren
id|mmap_dma
)paren
(paren
id|filp
comma
id|vma
)paren
suffix:semicolon
multiline_comment|/* A sequential search of a linked list is&n;&t;&t;&t;&t;   fine here because: 1) there will only be&n;&t;&t;&t;&t;   about 5-10 entries in the list and, 2) a&n;&t;&t;&t;&t;   DRI client only has to do this mapping&n;&t;&t;&t;&t;   once, so it doesn&squot;t have to be optimized&n;&t;&t;&t;&t;   for performance, even if the list was a&n;&t;&t;&t;&t;   bit longer. */
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|dev-&gt;maplist-&gt;head
)paren
(brace
r_int
r_int
id|off
suffix:semicolon
id|r_list
op_assign
(paren
id|drm_map_list_t
op_star
)paren
id|list
suffix:semicolon
id|map
op_assign
id|r_list-&gt;map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_continue
suffix:semicolon
id|off
op_assign
id|DRIVER_GET_MAP_OFS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
op_eq
id|VM_OFFSET
c_func
(paren
id|vma
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|map
op_logical_or
(paren
(paren
id|map-&gt;flags
op_amp
id|_DRM_RESTRICTED
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Check for valid size. */
r_if
c_cond
(paren
id|map-&gt;size
op_ne
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_and
(paren
id|map-&gt;flags
op_amp
id|_DRM_READ_ONLY
)paren
)paren
(brace
id|vma-&gt;vm_flags
op_and_assign
id|VM_MAYWRITE
suffix:semicolon
macro_line|#if defined(__i386__)
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_and_assign
op_complement
id|_PAGE_RW
suffix:semicolon
macro_line|#else
multiline_comment|/* Ye gads this is ugly.  With more thought&n;                                   we could move this up higher and use&n;                                   `protection_map&squot; instead.  */
id|vma-&gt;vm_page_prot
op_assign
id|__pgprot
c_func
(paren
id|pte_val
c_func
(paren
id|pte_wrprotect
c_func
(paren
id|__pte
c_func
(paren
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
)paren
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_switch
c_cond
(paren
id|map-&gt;type
)paren
(brace
r_case
id|_DRM_AGP
suffix:colon
macro_line|#if defined(__alpha__)
multiline_comment|/*&n;                 * On Alpha we can&squot;t talk to bus dma address from the&n;                 * CPU, so for memory of type DRM_AGP, we&squot;ll deal with&n;                 * sorting out the real physical pages and mappings&n;                 * in nopage()&n;                 */
id|vma-&gt;vm_ops
op_assign
op_amp
id|DRM
c_func
(paren
id|vm_ops
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
multiline_comment|/* fall through to _DRM_FRAME_BUFFER... */
r_case
id|_DRM_FRAME_BUFFER
suffix:colon
r_case
id|_DRM_REGISTERS
suffix:colon
r_if
c_cond
(paren
id|VM_OFFSET
c_func
(paren
id|vma
)paren
op_ge
id|__pa
c_func
(paren
id|high_memory
)paren
)paren
(brace
macro_line|#if defined(__i386__)
r_if
c_cond
(paren
id|boot_cpu_data.x86
OG
l_int|3
op_logical_and
id|map-&gt;type
op_ne
id|_DRM_AGP
)paren
(brace
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_or_assign
id|_PAGE_PCD
suffix:semicolon
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_and_assign
op_complement
id|_PAGE_PWT
suffix:semicolon
)brace
macro_line|#elif defined(__ia64__)
r_if
c_cond
(paren
id|map-&gt;type
op_ne
id|_DRM_AGP
)paren
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_writecombine
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
macro_line|#elif defined(__powerpc__)
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_or_assign
id|_PAGE_NO_CACHE
op_or
id|_PAGE_GUARDED
suffix:semicolon
macro_line|#endif
id|vma-&gt;vm_flags
op_or_assign
id|VM_IO
suffix:semicolon
multiline_comment|/* not in core dump */
)brace
id|offset
op_assign
id|DRIVER_GET_REG_OFS
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef __sparc__
r_if
c_cond
(paren
id|io_remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|VM_OFFSET
c_func
(paren
id|vma
)paren
op_plus
id|offset
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
comma
l_int|0
)paren
)paren
macro_line|#else
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|VM_OFFSET
c_func
(paren
id|vma
)paren
op_plus
id|offset
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
macro_line|#endif
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;   Type = %d; start = 0x%lx, end = 0x%lx,&quot;
l_string|&quot; offset = 0x%lx&bslash;n&quot;
comma
id|map-&gt;type
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
comma
id|VM_OFFSET
c_func
(paren
id|vma
)paren
op_plus
id|offset
)paren
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|DRM
c_func
(paren
id|vm_ops
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_SHM
suffix:colon
id|vma-&gt;vm_ops
op_assign
op_amp
id|DRM
c_func
(paren
id|vm_shm_ops
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
id|vma-&gt;vm_private_data
op_assign
(paren
r_void
op_star
)paren
id|map
suffix:semicolon
macro_line|#else
id|vma-&gt;vm_pte
op_assign
(paren
r_int
r_int
)paren
id|map
suffix:semicolon
macro_line|#endif
multiline_comment|/* Don&squot;t let this area swap.  Change when&n;&t;&t;&t;&t;   DRM_KERNEL advisory is supported. */
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_SCATTER_GATHER
suffix:colon
id|vma-&gt;vm_ops
op_assign
op_amp
id|DRM
c_func
(paren
id|vm_sg_ops
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020300
id|vma-&gt;vm_private_data
op_assign
(paren
r_void
op_star
)paren
id|map
suffix:semicolon
macro_line|#else
id|vma-&gt;vm_pte
op_assign
(paren
r_int
r_int
)paren
id|map
suffix:semicolon
macro_line|#endif
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* This should never happen. */
)brace
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
multiline_comment|/* Don&squot;t swap */
macro_line|#if LINUX_VERSION_CODE &lt; 0x020203 /* KERNEL_VERSION(2,2,3) */
multiline_comment|/* In Linux 2.2.3 and above, this is&n;&t;&t;&t;&t;   handled in do_mmap() in mm/mmap.c. */
op_increment
id|filp-&gt;f_count
suffix:semicolon
macro_line|#endif
id|vma-&gt;vm_file
op_assign
id|filp
suffix:semicolon
multiline_comment|/* Needed for drm_vm_open() */
id|DRM
c_func
(paren
id|vm_open
)paren
(paren
id|vma
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
