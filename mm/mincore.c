multiline_comment|/*&n; *&t;linux/mm/mincore.c&n; *&n; * Copyright (C) 1994-1999  Linus Torvalds&n; */
multiline_comment|/*&n; * The mincore() system call.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * Later we can get more picky about what &quot;in core&quot; means precisely.&n; * For now, simply check to see if the page is in the page cache,&n; * and is up to date; i.e. that no page-in operation would be required&n; * at this time if an application were to map and access this page.&n; */
DECL|function|mincore_page
r_static
r_int
r_char
id|mincore_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|pgoff
)paren
(brace
r_int
r_char
id|present
op_assign
l_int|0
suffix:semicolon
r_struct
id|address_space
op_star
id|as
op_assign
id|vma-&gt;vm_file-&gt;f_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|find_get_page
c_func
(paren
id|as
comma
id|pgoff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|present
op_assign
id|PageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|present
suffix:semicolon
)brace
DECL|function|mincore_vma
r_static
r_int
id|mincore_vma
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
r_char
id|__user
op_star
id|vec
)paren
(brace
r_int
id|error
comma
id|i
comma
id|remaining
suffix:semicolon
r_int
r_char
op_star
id|tmp
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
)paren
r_return
id|error
suffix:semicolon
id|start
op_assign
(paren
(paren
id|start
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_plus
id|vma-&gt;vm_pgoff
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|vma-&gt;vm_end
)paren
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|end
op_assign
(paren
(paren
id|end
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_plus
id|vma-&gt;vm_pgoff
suffix:semicolon
id|error
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|tmp
op_assign
(paren
r_int
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
id|error
suffix:semicolon
multiline_comment|/* (end - start) is # of pages, and also # of bytes in &quot;vec */
id|remaining
op_assign
(paren
id|end
op_minus
id|start
)paren
comma
id|error
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|remaining
OG
l_int|0
suffix:semicolon
id|remaining
op_sub_assign
id|PAGE_SIZE
comma
id|i
op_increment
)paren
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
r_int
id|thispiece
op_assign
(paren
id|remaining
OL
id|PAGE_SIZE
)paren
ques
c_cond
id|remaining
suffix:colon
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|j
OL
id|thispiece
)paren
id|tmp
(braket
id|j
op_increment
)braket
op_assign
id|mincore_page
c_func
(paren
id|vma
comma
id|start
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|vec
op_plus
id|PAGE_SIZE
op_star
id|i
comma
id|tmp
comma
id|thispiece
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|tmp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * The mincore(2) system call.&n; *&n; * mincore() returns the memory residency status of the pages in the&n; * current process&squot;s address space specified by [addr, addr + len).&n; * The status is returned in a vector of bytes.  The least significant&n; * bit of each byte is 1 if the referenced page is in memory, otherwise&n; * it is zero.&n; *&n; * Because the status of a page can change after mincore() checks it&n; * but before it returns to the application, the returned vector may&n; * contain stale information.  Only locked pages are guaranteed to&n; * remain in memory.&n; *&n; * return values:&n; *  zero    - success&n; *  -EFAULT - vec points to an illegal address&n; *  -EINVAL - addr is not a multiple of PAGE_CACHE_SIZE,&n; *&t;&t;or len has a nonpositive value&n; *  -ENOMEM - Addresses in the range [addr, addr + len] are&n; *&t;&t;invalid for the address space of this process, or&n; *&t;&t;specify one or more pages which are not currently&n; *&t;&t;mapped&n; *  -EAGAIN - A kernel resource was temporarily unavailable.&n; */
DECL|function|sys_mincore
id|asmlinkage
r_int
id|sys_mincore
c_func
(paren
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
r_char
id|__user
op_star
id|vec
)paren
(brace
r_int
id|index
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|unmapped_error
op_assign
l_int|0
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_amp
op_complement
id|PAGE_CACHE_MASK
)paren
r_goto
id|out
suffix:semicolon
id|len
op_assign
(paren
id|len
op_plus
op_complement
id|PAGE_CACHE_MASK
)paren
op_amp
id|PAGE_CACHE_MASK
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|vec
comma
id|len
op_rshift
id|PAGE_SHIFT
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|start
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * If the interval [start,end) covers some unmapped address&n;&t; * ranges, just ignore them, but return -ENOMEM at the end.&n;&t; */
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|start
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* Still start &lt; end. */
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Here start &lt; vma-&gt;vm_end. */
r_if
c_cond
(paren
id|start
OL
id|vma-&gt;vm_start
)paren
(brace
id|unmapped_error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|start
op_assign
id|vma-&gt;vm_start
suffix:semicolon
)brace
multiline_comment|/* Here vma-&gt;vm_start &lt;= start &lt; vma-&gt;vm_end. */
r_if
c_cond
(paren
id|end
op_le
id|vma-&gt;vm_end
)paren
(brace
r_if
c_cond
(paren
id|start
OL
id|end
)paren
(brace
id|error
op_assign
id|mincore_vma
c_func
(paren
id|vma
comma
id|start
comma
id|end
comma
op_amp
id|vec
(braket
id|index
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
id|unmapped_error
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Here vma-&gt;vm_start &lt;= start &lt; vma-&gt;vm_end &lt; end. */
id|error
op_assign
id|mincore_vma
c_func
(paren
id|vma
comma
id|start
comma
id|vma-&gt;vm_end
comma
op_amp
id|vec
(braket
id|index
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|index
op_add_assign
(paren
id|vma-&gt;vm_end
op_minus
id|start
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|start
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
id|out
suffix:colon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
