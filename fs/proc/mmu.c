multiline_comment|/* mmu.c: mmu memory info files&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &quot;internal.h&quot;
DECL|function|get_vmalloc_info
r_void
id|get_vmalloc_info
c_func
(paren
r_struct
id|vmalloc_info
op_star
id|vmi
)paren
(brace
r_struct
id|vm_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|free_area_size
suffix:semicolon
r_int
r_int
id|prev_end
suffix:semicolon
id|vmi-&gt;used
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vmlist
)paren
(brace
id|vmi-&gt;largest_chunk
op_assign
id|VMALLOC_TOTAL
suffix:semicolon
)brace
r_else
(brace
id|vmi-&gt;largest_chunk
op_assign
l_int|0
suffix:semicolon
id|prev_end
op_assign
id|VMALLOC_START
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|vmlist
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;next
)paren
(brace
id|vmi-&gt;used
op_add_assign
id|vma-&gt;size
suffix:semicolon
id|free_area_size
op_assign
(paren
r_int
r_int
)paren
id|vma-&gt;addr
op_minus
id|prev_end
suffix:semicolon
r_if
c_cond
(paren
id|vmi-&gt;largest_chunk
OL
id|free_area_size
)paren
id|vmi-&gt;largest_chunk
op_assign
id|free_area_size
suffix:semicolon
id|prev_end
op_assign
id|vma-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|vma-&gt;addr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|VMALLOC_END
op_minus
id|prev_end
OG
id|vmi-&gt;largest_chunk
)paren
id|vmi-&gt;largest_chunk
op_assign
id|VMALLOC_END
op_minus
id|prev_end
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
)brace
)brace
eof
