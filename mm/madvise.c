multiline_comment|/*&n; *&t;linux/mm/madvise.c&n; *&n; * Copyright (C) 1999  Linus Torvalds&n; * Copyright (C) 2002  Christoph Hellwig&n; */
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
multiline_comment|/*&n; * We can potentially split a vm area into separate&n; * areas, each area with its own behavior.&n; */
DECL|function|madvise_behavior
r_static
r_int
id|madvise_behavior
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
id|behavior
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ne
id|vma-&gt;vm_start
)paren
(brace
id|error
op_assign
id|split_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|start
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end
op_ne
id|vma-&gt;vm_end
)paren
(brace
id|error
op_assign
id|split_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|vma-&gt;vm_raend
op_assign
l_int|0
suffix:semicolon
id|VM_ClearReadHint
c_func
(paren
id|vma
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|behavior
)paren
(brace
r_case
id|MADV_SEQUENTIAL
suffix:colon
id|vma-&gt;vm_flags
op_or_assign
id|VM_SEQ_READ
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MADV_RANDOM
suffix:colon
id|vma-&gt;vm_flags
op_or_assign
id|VM_RAND_READ
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Schedule all required I/O operations, then run the disk queue&n; * to make sure they are started.  Do not wait for completion.&n; */
DECL|function|madvise_willneed
r_static
r_int
id|madvise_willneed
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
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
r_int
id|size
comma
id|rlim_rss
suffix:semicolon
multiline_comment|/* Doesn&squot;t work if there&squot;s no mapped file. */
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
)paren
r_return
id|error
suffix:semicolon
id|file
op_assign
id|vma-&gt;vm_file
suffix:semicolon
id|size
op_assign
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
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
multiline_comment|/* Make sure this doesn&squot;t exceed the process&squot;s max rss. */
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
id|rlim_rss
op_assign
id|current-&gt;rlim
ques
c_cond
id|current-&gt;rlim
(braket
id|RLIMIT_RSS
)braket
dot
id|rlim_cur
suffix:colon
id|LONG_MAX
suffix:semicolon
multiline_comment|/* default: see resource.h */
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_mm-&gt;rss
op_plus
(paren
id|end
op_minus
id|start
)paren
)paren
OG
id|rlim_rss
)paren
r_return
id|error
suffix:semicolon
id|do_page_cache_readahead
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
comma
id|file
comma
id|start
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Application no longer needs these pages.  If the pages are dirty,&n; * it&squot;s OK to just throw them away.  The app will be more careful about&n; * data it wants to keep.  Be sure to free swap resources too.  The&n; * zap_page_range call sets things up for refill_inactive to actually free&n; * these pages later if no one else has touched them in the meantime,&n; * although we could add these pages to a global reuse list for&n; * refill_inactive to pick up before reclaiming other pages.&n; *&n; * NB: This interface discards data rather than pushes it out to swap,&n; * as some implementations do.  This has performance implications for&n; * applications like large transactional databases which want to discard&n; * pages in anonymous maps after committing to backing store the data&n; * that was kept in them.  There is no reason to write this data out to&n; * the swap area if the application is discarding it.&n; *&n; * An interface that causes the system to free clean pages and flush&n; * dirty pages is already available as msync(MS_INVALIDATE).&n; */
DECL|function|madvise_dontneed
r_static
r_int
id|madvise_dontneed
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
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|zap_page_range
c_func
(paren
id|vma
comma
id|start
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|madvise_vma
r_static
r_int
id|madvise_vma
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
id|behavior
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_switch
c_cond
(paren
id|behavior
)paren
(brace
r_case
id|MADV_NORMAL
suffix:colon
r_case
id|MADV_SEQUENTIAL
suffix:colon
r_case
id|MADV_RANDOM
suffix:colon
id|error
op_assign
id|madvise_behavior
c_func
(paren
id|vma
comma
id|start
comma
id|end
comma
id|behavior
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MADV_WILLNEED
suffix:colon
id|error
op_assign
id|madvise_willneed
c_func
(paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MADV_DONTNEED
suffix:colon
id|error
op_assign
id|madvise_dontneed
c_func
(paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * The madvise(2) system call.&n; *&n; * Applications can use madvise() to advise the kernel how it should&n; * handle paging I/O in this VM area.  The idea is to help the kernel&n; * use appropriate read-ahead and caching techniques.  The information&n; * provided is advisory only, and can be safely disregarded by the&n; * kernel without affecting the correct operation of the application.&n; *&n; * behavior values:&n; *  MADV_NORMAL - the default behavior is to read clusters.  This&n; *&t;&t;results in some read-ahead and read-behind.&n; *  MADV_RANDOM - the system should read the minimum amount of data&n; *&t;&t;on any access, since it is unlikely that the appli-&n; *&t;&t;cation will need more than what it asks for.&n; *  MADV_SEQUENTIAL - pages in the given range will probably be accessed&n; *&t;&t;once, so they can be aggressively read ahead, and&n; *&t;&t;can be freed soon after they are accessed.&n; *  MADV_WILLNEED - the application is notifying the system to read&n; *&t;&t;some pages ahead.&n; *  MADV_DONTNEED - the application is finished with the given range,&n; *&t;&t;so the kernel can free resources associated with it.&n; *&n; * return values:&n; *  zero    - success&n; *  -EINVAL - start + len &lt; 0, start is not page-aligned,&n; *&t;&t;&quot;behavior&quot; is not a valid value, or application&n; *&t;&t;is attempting to release locked or shared pages.&n; *  -ENOMEM - addresses in the specified range are not currently&n; *&t;&t;mapped, or are outside the AS of the process.&n; *  -EIO    - an I/O error occurred while paging in data.&n; *  -EBADF  - map exists, but area maps something that isn&squot;t a file.&n; *  -EAGAIN - a kernel resource was temporarily unavailable.&n; */
DECL|function|sys_madvise
id|asmlinkage
r_int
id|sys_madvise
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
id|behavior
)paren
(brace
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
id|down_write
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
id|PAGE_MASK
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
id|PAGE_MASK
)paren
op_amp
id|PAGE_MASK
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
id|madvise_vma
c_func
(paren
id|vma
comma
id|start
comma
id|end
comma
id|behavior
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
id|madvise_vma
c_func
(paren
id|vma
comma
id|start
comma
id|vma-&gt;vm_end
comma
id|behavior
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
id|up_write
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
