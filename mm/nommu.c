multiline_comment|/*&n; *  linux/mm/nommu.c&n; *&n; *  Replacement code for mm functions to support CPU&squot;s that don&squot;t&n; *  have any form of memory management unit (thus no virtual memory).&n; *&n; *  Copyright (c) 2000-2003 David McCullough &lt;davidm@snapgear.com&gt;&n; *  Copyright (c) 2000-2001 D Jeff Dionne &lt;jeff@uClinux.org&gt;&n; *  Copyright (c) 2002      Greg Ungerer &lt;gerg@snapgear.com&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|high_memory
r_void
op_star
id|high_memory
suffix:semicolon
DECL|variable|mem_map
r_struct
id|page
op_star
id|mem_map
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|max_mapnr
r_int
r_int
id|max_mapnr
suffix:semicolon
DECL|variable|num_physpages
r_int
r_int
id|num_physpages
suffix:semicolon
DECL|variable|askedalloc
DECL|variable|realalloc
r_int
r_int
id|askedalloc
comma
id|realalloc
suffix:semicolon
DECL|variable|vm_committed_space
id|atomic_t
id|vm_committed_space
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|sysctl_overcommit_memory
r_int
id|sysctl_overcommit_memory
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* default is heuristic overcommit */
DECL|variable|sysctl_overcommit_ratio
r_int
id|sysctl_overcommit_ratio
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* default is 50% */
multiline_comment|/*&n; * Handle all mappings that got truncated by a &quot;truncate()&quot;&n; * system call.&n; *&n; * NOTE! We have to be ready to update the memory sharing&n; * between the file and the memory map for a potential last&n; * incomplete page.  Ugly, but necessary.&n; */
DECL|function|vmtruncate
r_int
id|vmtruncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|loff_t
id|offset
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_int
r_int
id|limit
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OL
id|offset
)paren
r_goto
id|do_expand
suffix:semicolon
id|i_size_write
c_func
(paren
id|inode
comma
id|offset
)paren
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
id|mapping
comma
id|offset
)paren
suffix:semicolon
r_goto
id|out_truncate
suffix:semicolon
id|do_expand
suffix:colon
id|limit
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_FSIZE
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|limit
op_ne
id|RLIM_INFINITY
op_logical_and
id|offset
OG
id|limit
)paren
r_goto
id|out_sig
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|inode-&gt;i_sb-&gt;s_maxbytes
)paren
r_goto
id|out
suffix:semicolon
id|i_size_write
c_func
(paren
id|inode
comma
id|offset
)paren
suffix:semicolon
id|out_truncate
suffix:colon
r_if
c_cond
(paren
id|inode-&gt;i_op
op_logical_and
id|inode-&gt;i_op-&gt;truncate
)paren
id|inode-&gt;i_op
op_member_access_from_pointer
id|truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_sig
suffix:colon
id|send_sig
c_func
(paren
id|SIGXFSZ
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|EFBIG
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the total memory allocated for this pointer, not&n; * just what the caller asked for.&n; *&n; * Doesn&squot;t have to be accurate, i.e. may have races.&n; */
DECL|function|kobjsize
r_int
r_int
id|kobjsize
c_func
(paren
r_const
r_void
op_star
id|objp
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|objp
op_logical_or
op_logical_neg
(paren
(paren
id|page
op_assign
id|virt_to_page
c_func
(paren
id|objp
)paren
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|PageSlab
c_func
(paren
id|page
)paren
)paren
r_return
id|ksize
c_func
(paren
id|objp
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|page-&gt;index
OL
l_int|0
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|page-&gt;index
op_ge
id|MAX_ORDER
)paren
suffix:semicolon
r_return
(paren
id|PAGE_SIZE
op_lshift
id|page-&gt;index
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The nommu dodgy version :-)&n; */
DECL|function|get_user_pages
r_int
id|get_user_pages
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
id|write
comma
r_int
id|force
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_struct
id|vm_area_struct
op_star
op_star
id|vmas
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_struct
id|vm_area_struct
id|dummy_vma
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pages
)paren
(brace
id|pages
(braket
id|i
)braket
op_assign
id|virt_to_page
c_func
(paren
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages
(braket
id|i
)braket
)paren
id|page_cache_get
c_func
(paren
id|pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vmas
)paren
id|vmas
(braket
id|i
)braket
op_assign
op_amp
id|dummy_vma
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|variable|vmlist_lock
id|rwlock_t
id|vmlist_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|vmlist
r_struct
id|vm_struct
op_star
id|vmlist
suffix:semicolon
DECL|function|vfree
r_void
id|vfree
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|kfree
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__vmalloc
r_void
op_star
id|__vmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|gfp_mask
comma
id|pgprot_t
id|prot
)paren
(brace
multiline_comment|/*&n;&t; * kmalloc doesn&squot;t like __GFP_HIGHMEM for some reason&n;&t; */
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|gfp_mask
op_amp
op_complement
id|__GFP_HIGHMEM
)paren
suffix:semicolon
)brace
DECL|function|vmalloc_to_page
r_struct
id|page
op_star
id|vmalloc_to_page
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|virt_to_page
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|vread
r_int
id|vread
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|addr
comma
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|vwrite
r_int
id|vwrite
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
multiline_comment|/* Don&squot;t allow overflow */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
id|count
OL
id|count
)paren
id|count
op_assign
op_minus
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|memcpy
c_func
(paren
id|addr
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;vmalloc  -  allocate virtually continguos memory&n; *&n; *&t;@size:&t;&t;allocation size&n; *&n; *&t;Allocate enough pages to cover @size from the page level&n; *&t;allocator and map them into continguos kernel virtual space.&n; *&n; *&t;For tight cotrol over page level allocator and protection flags&n; *&t;use __vmalloc() instead.&n; */
DECL|function|vmalloc
r_void
op_star
id|vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;vmalloc_32  -  allocate virtually continguos memory (32bit addressable)&n; *&n; *&t;@size:&t;&t;allocation size&n; *&n; *&t;Allocate enough 32bit PA addressable pages to cover @size from the&n; *&t;page level allocator and map them into continguos kernel virtual space.&n; */
DECL|function|vmalloc_32
r_void
op_star
id|vmalloc_32
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|vmap
r_void
op_star
id|vmap
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
r_int
id|count
comma
r_int
r_int
id|flags
comma
id|pgprot_t
id|prot
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|vunmap
r_void
id|vunmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  sys_brk() for the most part doesn&squot;t need the global kernel&n; *  lock, except when an application is doing something nasty&n; *  like trying to un-brk an area that has already been mapped&n; *  to a regular file.  in this case, the unmapping will need&n; *  to invoke file system routines that need the global lock.&n; */
DECL|function|sys_brk
id|asmlinkage
r_int
r_int
id|sys_brk
c_func
(paren
r_int
r_int
id|brk
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|brk
OL
id|mm-&gt;end_code
op_logical_or
id|brk
template_param
id|mm-&gt;context.end_brk
)paren
r_return
id|mm-&gt;brk
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;brk
op_eq
id|brk
)paren
r_return
id|mm-&gt;brk
suffix:semicolon
multiline_comment|/*&n;&t; * Always allow shrinking brk&n;&t; */
r_if
c_cond
(paren
id|brk
op_le
id|mm-&gt;brk
)paren
(brace
id|mm-&gt;brk
op_assign
id|brk
suffix:semicolon
r_return
id|brk
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ok, looks good - let it rip.&n;&t; */
r_return
id|mm-&gt;brk
op_assign
id|brk
suffix:semicolon
)brace
multiline_comment|/*&n; * Combine the mmap &quot;prot&quot; and &quot;flags&quot; argument into one &quot;vm_flags&quot; used&n; * internally. Essentially, translate the &quot;PROT_xxx&quot; and &quot;MAP_xxx&quot; bits&n; * into &quot;VM_xxx&quot;.&n; */
DECL|function|calc_vm_flags
r_static
r_inline
r_int
r_int
id|calc_vm_flags
c_func
(paren
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
)paren
(brace
DECL|macro|_trans
mdefine_line|#define _trans(x,bit1,bit2) &bslash;&n;((bit1==bit2)?(x&amp;bit1):(x&amp;bit1)?bit2:0)
r_int
r_int
id|prot_bits
comma
id|flag_bits
suffix:semicolon
id|prot_bits
op_assign
id|_trans
c_func
(paren
id|prot
comma
id|PROT_READ
comma
id|VM_READ
)paren
op_or
id|_trans
c_func
(paren
id|prot
comma
id|PROT_WRITE
comma
id|VM_WRITE
)paren
op_or
id|_trans
c_func
(paren
id|prot
comma
id|PROT_EXEC
comma
id|VM_EXEC
)paren
suffix:semicolon
id|flag_bits
op_assign
id|_trans
c_func
(paren
id|flags
comma
id|MAP_GROWSDOWN
comma
id|VM_GROWSDOWN
)paren
op_or
id|_trans
c_func
(paren
id|flags
comma
id|MAP_DENYWRITE
comma
id|VM_DENYWRITE
)paren
op_or
id|_trans
c_func
(paren
id|flags
comma
id|MAP_EXECUTABLE
comma
id|VM_EXECUTABLE
)paren
suffix:semicolon
r_return
id|prot_bits
op_or
id|flag_bits
suffix:semicolon
DECL|macro|_trans
macro_line|#undef _trans
)brace
macro_line|#ifdef DEBUG
DECL|function|show_process_blocks
r_static
r_void
id|show_process_blocks
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_tblock_struct
op_star
id|tblock
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process blocks %d:&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tblock
op_assign
op_amp
id|current-&gt;mm-&gt;context.tblock
suffix:semicolon
id|tblock
suffix:semicolon
id|tblock
op_assign
id|tblock-&gt;next
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %p: %p&quot;
comma
id|tblock
comma
id|tblock-&gt;rblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tblock-&gt;rblock
)paren
id|printk
c_func
(paren
l_string|&quot; (%d @%p #%d)&quot;
comma
id|kobjsize
c_func
(paren
id|tblock-&gt;rblock-&gt;kblock
)paren
comma
id|tblock-&gt;rblock-&gt;kblock
comma
id|tblock-&gt;rblock-&gt;refcount
)paren
suffix:semicolon
id|printk
c_func
(paren
id|tblock-&gt;next
ques
c_cond
l_string|&quot; -&gt;&quot;
suffix:colon
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* DEBUG */
DECL|function|do_mmap_pgoff
r_int
r_int
id|do_mmap_pgoff
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|pgoff
)paren
(brace
r_void
op_star
id|result
suffix:semicolon
r_struct
id|mm_tblock_struct
op_star
id|tblock
suffix:semicolon
r_int
r_int
id|vm_flags
suffix:semicolon
multiline_comment|/*&n;&t; * Get the !CONFIG_MMU specific checks done first&n;&t; */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|MAP_SHARED
)paren
op_logical_and
(paren
id|prot
op_amp
id|PROT_WRITE
)paren
op_logical_and
(paren
id|file
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MAP_SHARED not supported (cannot write mappings to disk)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|prot
op_amp
id|PROT_WRITE
)paren
op_logical_and
(paren
id|flags
op_amp
id|MAP_PRIVATE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Private writable mappings not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;now all the standard checks&n;&t; */
r_if
c_cond
(paren
id|file
op_logical_and
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
op_logical_neg
id|file-&gt;f_op-&gt;mmap
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
op_eq
l_int|0
)paren
r_return
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* offset overflow? */
r_if
c_cond
(paren
(paren
id|pgoff
op_plus
(paren
id|len
op_rshift
id|PAGE_SHIFT
)paren
)paren
OL
id|pgoff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Do simple checking here so the lower-level routines won&squot;t have&n;&t; * to. we assume access permissions have been handled by the open&n;&t; * of the memory object, so we don&squot;t do any here.&n;&t; */
id|vm_flags
op_assign
id|calc_vm_flags
c_func
(paren
id|prot
comma
id|flags
)paren
multiline_comment|/* | mm-&gt;def_flags */
op_or
id|VM_MAYREAD
op_or
id|VM_MAYWRITE
op_or
id|VM_MAYEXEC
suffix:semicolon
multiline_comment|/*&n;&t; * determine the object being mapped and call the appropriate&n;&t; * specific mapper. &n;&t; */
r_if
c_cond
(paren
id|file
)paren
(brace
r_struct
id|vm_area_struct
id|vma
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|vma.vm_start
op_assign
id|addr
suffix:semicolon
id|vma.vm_end
op_assign
id|addr
op_plus
id|len
suffix:semicolon
id|vma.vm_flags
op_assign
id|vm_flags
suffix:semicolon
id|vma.vm_pgoff
op_assign
id|pgoff
suffix:semicolon
macro_line|#ifdef MAGIC_ROM_PTR
multiline_comment|/* First, try simpler routine designed to give us a ROM pointer. */
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;romptr
op_logical_and
op_logical_neg
(paren
id|prot
op_amp
id|PROT_WRITE
)paren
)paren
(brace
id|error
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|romptr
c_func
(paren
id|file
comma
op_amp
id|vma
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;romptr mmap returned %d, start 0x%.8x&bslash;n&quot;
comma
id|error
comma
id|vma.vm_start
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
r_return
id|vma.vm_start
suffix:semicolon
r_else
r_if
c_cond
(paren
id|error
op_ne
op_minus
id|ENOSYS
)paren
r_return
id|error
suffix:semicolon
)brace
r_else
macro_line|#endif /* MAGIC_ROM_PTR */
multiline_comment|/* Then try full mmap routine, which might return a RAM pointer,&n;&t;&t;   or do something truly complicated. */
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;mmap
)paren
(brace
id|error
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|mmap
c_func
(paren
id|file
comma
op_amp
id|vma
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;f_op-&gt;mmap() returned %d/%lx&bslash;n&quot;
comma
id|error
comma
id|vma.vm_start
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
r_return
id|vma.vm_start
suffix:semicolon
r_else
r_if
c_cond
(paren
id|error
op_ne
op_minus
id|ENOSYS
)paren
r_return
id|error
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* No mapping operations defined */
multiline_comment|/* An ENOSYS error indicates that mmap isn&squot;t possible (as opposed to&n;&t;&t;   tried but failed) so we&squot;ll fall through to the copy. */
)brace
id|tblock
op_assign
(paren
r_struct
id|mm_tblock_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mm_tblock_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tblock
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Allocation of tblock for %lu byte allocation from process %d failed&bslash;n&quot;
comma
id|len
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|tblock-&gt;rblock
op_assign
(paren
r_struct
id|mm_rblock_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mm_rblock_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tblock-&gt;rblock
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Allocation of rblock for %lu byte allocation from process %d failed&bslash;n&quot;
comma
id|len
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|result
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Allocation of length %lu from process %d failed&bslash;n&quot;
comma
id|len
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock-&gt;rblock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|tblock-&gt;rblock-&gt;refcount
op_assign
l_int|1
suffix:semicolon
id|tblock-&gt;rblock-&gt;kblock
op_assign
id|result
suffix:semicolon
id|tblock-&gt;rblock-&gt;size
op_assign
id|len
suffix:semicolon
id|realalloc
op_add_assign
id|kobjsize
c_func
(paren
id|result
)paren
suffix:semicolon
id|askedalloc
op_add_assign
id|len
suffix:semicolon
macro_line|#ifdef WARN_ON_SLACK&t;
r_if
c_cond
(paren
(paren
id|len
op_plus
id|WARN_ON_SLACK
)paren
op_le
id|kobjsize
c_func
(paren
id|result
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Allocation of %lu bytes from process %d has %lu bytes of slack&bslash;n&quot;
comma
id|len
comma
id|current-&gt;pid
comma
id|kobjsize
c_func
(paren
id|result
)paren
op_minus
id|len
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|file
)paren
(brace
r_int
id|error
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|error
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|file
comma
(paren
r_char
op_star
)paren
id|result
comma
id|len
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|result
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock-&gt;rblock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
OL
id|len
)paren
id|memset
c_func
(paren
id|result
op_plus
id|error
comma
l_char|&squot;&bslash;0&squot;
comma
id|len
op_minus
id|error
)paren
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
id|result
comma
l_char|&squot;&bslash;0&squot;
comma
id|len
)paren
suffix:semicolon
)brace
id|realalloc
op_add_assign
id|kobjsize
c_func
(paren
id|tblock
)paren
suffix:semicolon
id|askedalloc
op_add_assign
r_sizeof
(paren
r_struct
id|mm_tblock_struct
)paren
suffix:semicolon
id|realalloc
op_add_assign
id|kobjsize
c_func
(paren
id|tblock-&gt;rblock
)paren
suffix:semicolon
id|askedalloc
op_add_assign
r_sizeof
(paren
r_struct
id|mm_rblock_struct
)paren
suffix:semicolon
id|tblock-&gt;next
op_assign
id|current-&gt;mm-&gt;context.tblock.next
suffix:semicolon
id|current-&gt;mm-&gt;context.tblock.next
op_assign
id|tblock
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;do_mmap:&bslash;n&quot;
)paren
suffix:semicolon
id|show_process_blocks
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;  
r_return
(paren
r_int
r_int
)paren
id|result
suffix:semicolon
)brace
DECL|function|do_munmap
r_int
id|do_munmap
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_struct
id|mm_tblock_struct
op_star
id|tblock
comma
op_star
id|tmp
suffix:semicolon
macro_line|#ifdef MAGIC_ROM_PTR
multiline_comment|/*&n;&t; * For efficiency&squot;s sake, if the pointer is obviously in ROM,&n;&t; * don&squot;t bother walking the lists to free it.&n;&t; */
r_if
c_cond
(paren
id|is_in_rom
c_func
(paren
id|addr
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;do_munmap:&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|tmp
op_assign
op_amp
id|mm-&gt;context.tblock
suffix:semicolon
multiline_comment|/* dummy head */
r_while
c_loop
(paren
(paren
id|tblock
op_assign
id|tmp-&gt;next
)paren
op_logical_and
id|tblock-&gt;rblock
op_logical_and
id|tblock-&gt;rblock-&gt;kblock
op_ne
(paren
r_void
op_star
)paren
id|addr
)paren
id|tmp
op_assign
id|tblock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tblock
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;munmap of non-mmaped memory by process %d (%s): %p&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tblock-&gt;rblock
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|tblock-&gt;rblock-&gt;refcount
)paren
(brace
r_if
c_cond
(paren
id|tblock-&gt;rblock-&gt;kblock
)paren
(brace
id|realalloc
op_sub_assign
id|kobjsize
c_func
(paren
id|tblock-&gt;rblock-&gt;kblock
)paren
suffix:semicolon
id|askedalloc
op_sub_assign
id|tblock-&gt;rblock-&gt;size
suffix:semicolon
id|kfree
c_func
(paren
id|tblock-&gt;rblock-&gt;kblock
)paren
suffix:semicolon
)brace
id|realalloc
op_sub_assign
id|kobjsize
c_func
(paren
id|tblock-&gt;rblock
)paren
suffix:semicolon
id|askedalloc
op_sub_assign
r_sizeof
(paren
r_struct
id|mm_rblock_struct
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock-&gt;rblock
)paren
suffix:semicolon
)brace
)brace
id|tmp-&gt;next
op_assign
id|tblock-&gt;next
suffix:semicolon
id|realalloc
op_sub_assign
id|kobjsize
c_func
(paren
id|tblock
)paren
suffix:semicolon
id|askedalloc
op_sub_assign
r_sizeof
(paren
r_struct
id|mm_tblock_struct
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tblock
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|show_process_blocks
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;  
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Release all mmaps. */
DECL|function|exit_mmap
r_void
id|exit_mmap
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_struct
id|mm_tblock_struct
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_return
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Exit_mmap:&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|mm-&gt;context.tblock.next
)paren
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;rblock
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|tmp-&gt;rblock-&gt;refcount
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;rblock-&gt;kblock
)paren
(brace
id|realalloc
op_sub_assign
id|kobjsize
c_func
(paren
id|tmp-&gt;rblock-&gt;kblock
)paren
suffix:semicolon
id|askedalloc
op_sub_assign
id|tmp-&gt;rblock-&gt;size
suffix:semicolon
id|kfree
c_func
(paren
id|tmp-&gt;rblock-&gt;kblock
)paren
suffix:semicolon
)brace
id|realalloc
op_sub_assign
id|kobjsize
c_func
(paren
id|tmp-&gt;rblock
)paren
suffix:semicolon
id|askedalloc
op_sub_assign
r_sizeof
(paren
r_struct
id|mm_rblock_struct
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp-&gt;rblock
)paren
suffix:semicolon
)brace
id|tmp-&gt;rblock
op_assign
l_int|0
suffix:semicolon
)brace
id|mm-&gt;context.tblock.next
op_assign
id|tmp-&gt;next
suffix:semicolon
id|realalloc
op_sub_assign
id|kobjsize
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|askedalloc
op_sub_assign
r_sizeof
(paren
r_struct
id|mm_tblock_struct
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|show_process_blocks
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;  
)brace
DECL|function|sys_munmap
id|asmlinkage
r_int
id|sys_munmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|do_munmap
c_func
(paren
id|mm
comma
id|addr
comma
id|len
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_brk
r_int
r_int
id|do_brk
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|find_vma
r_struct
id|vm_area_struct
op_star
id|find_vma
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|follow_page
r_struct
id|page
op_star
id|follow_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
r_int
id|write
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|remap_page_range
r_int
id|remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|function|get_unmapped_area
r_int
r_int
id|get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|file
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|pte_chain_init
r_void
id|pte_chain_init
c_func
(paren
r_void
)paren
(brace
)brace
eof
