multiline_comment|/*&n; * hugetlbpage-backed filesystem.  Based on ramfs.&n; *&n; * William Irwin, 2002&n; *&n; * Copyright (C) 2002 Linus Torvalds.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;&t;/* remove ASAP */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/pagevec.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* some random number */
DECL|macro|HUGETLBFS_MAGIC
mdefine_line|#define HUGETLBFS_MAGIC&t;0x958458f6
DECL|variable|hugetlbfs_ops
r_static
r_struct
id|super_operations
id|hugetlbfs_ops
suffix:semicolon
DECL|variable|hugetlbfs_aops
r_static
r_struct
id|address_space_operations
id|hugetlbfs_aops
suffix:semicolon
DECL|variable|hugetlbfs_file_operations
r_struct
id|file_operations
id|hugetlbfs_file_operations
suffix:semicolon
DECL|variable|hugetlbfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|hugetlbfs_dir_inode_operations
suffix:semicolon
DECL|variable|hugetlbfs_backing_dev_info
r_static
r_struct
id|backing_dev_info
id|hugetlbfs_backing_dev_info
op_assign
(brace
dot
id|ra_pages
op_assign
l_int|0
comma
multiline_comment|/* No readahead */
dot
id|memory_backed
op_assign
l_int|1
comma
multiline_comment|/* Does not contribute to dirty memory */
)brace
suffix:semicolon
DECL|function|hugetlbfs_file_mmap
r_static
r_int
id|hugetlbfs_file_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
op_amp
op_complement
id|HPAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_amp
op_complement
id|HPAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
OL
id|HPAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|UPDATE_ATIME
c_func
(paren
id|inode
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_HUGETLB
op_or
id|VM_RESERVED
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|hugetlb_vm_ops
suffix:semicolon
id|ret
op_assign
id|hugetlb_prefault
c_func
(paren
id|mapping
comma
id|vma
)paren
suffix:semicolon
id|len
op_assign
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
op_plus
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
OL
id|len
)paren
id|inode-&gt;i_size
op_assign
id|len
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a page. Again trivial. If it didn&squot;t already exist&n; * in the page cache, it is zero-filled.&n; */
DECL|function|hugetlbfs_readpage
r_static
r_int
id|hugetlbfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|hugetlbfs_prepare_write
r_static
r_int
id|hugetlbfs_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|hugetlbfs_commit_write
r_static
r_int
id|hugetlbfs_commit_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|huge_pagevec_release
r_void
id|huge_pagevec_release
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_int
id|i
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
id|pagevec_count
c_func
(paren
id|pvec
)paren
suffix:semicolon
op_increment
id|i
)paren
id|huge_page_release
c_func
(paren
id|pvec-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
id|pagevec_reinit
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
DECL|function|truncate_partial_hugepage
r_void
id|truncate_partial_hugepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|partial
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_int
id|piece
op_assign
id|partial
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_const
r_int
id|tailstart
op_assign
id|PAGE_SIZE
op_minus
id|piece
suffix:semicolon
r_const
r_int
id|whole_pages
op_assign
id|partial
op_div
id|PAGE_SIZE
suffix:semicolon
r_const
r_int
id|last_page_offset
op_assign
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
op_minus
id|whole_pages
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
id|last_page_offset
suffix:semicolon
op_increment
id|i
)paren
id|memclear_highpage_flush
c_func
(paren
op_amp
id|page
(braket
id|i
)braket
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|piece
)paren
r_return
suffix:semicolon
id|memclear_highpage_flush
c_func
(paren
op_amp
id|page
(braket
id|last_page_offset
op_minus
l_int|1
)braket
comma
id|tailstart
comma
id|piece
)paren
suffix:semicolon
)brace
DECL|function|truncate_huge_page
r_void
id|truncate_huge_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_ne
id|mapping
)paren
r_return
suffix:semicolon
id|clear_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|remove_from_page_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|huge_page_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|truncate_hugepages
r_void
id|truncate_hugepages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|loff_t
id|lstart
)paren
(brace
r_const
id|pgoff_t
id|start
op_assign
(paren
id|lstart
op_plus
id|HPAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|HPAGE_SHIFT
suffix:semicolon
r_const
r_int
id|partial
op_assign
id|lstart
op_amp
(paren
id|HPAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_struct
id|pagevec
id|pvec
suffix:semicolon
id|pgoff_t
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pvec
comma
l_int|0
)paren
suffix:semicolon
id|next
op_assign
id|start
suffix:semicolon
r_while
c_loop
(paren
id|pagevec_lookup
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
id|next
comma
id|PAGEVEC_SIZE
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pagevec_count
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pvec.pages
(braket
id|i
)braket
suffix:semicolon
id|pgoff_t
id|page_index
op_assign
id|page-&gt;index
suffix:semicolon
r_if
c_cond
(paren
id|page_index
OG
id|next
)paren
id|next
op_assign
id|page_index
suffix:semicolon
op_increment
id|next
suffix:semicolon
r_if
c_cond
(paren
id|TestSetPageLocked
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|truncate_huge_page
c_func
(paren
id|mapping
comma
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|huge_pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|partial
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|find_lock_page
c_func
(paren
id|mapping
comma
id|start
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
id|truncate_partial_hugepage
c_func
(paren
id|page
comma
id|partial
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|huge_page_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
id|next
op_assign
id|start
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pagevec_lookup
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
id|next
comma
id|PAGEVEC_SIZE
)paren
)paren
(brace
r_if
c_cond
(paren
id|next
op_eq
id|start
)paren
r_break
suffix:semicolon
id|next
op_assign
id|start
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pagevec_count
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pvec.pages
(braket
id|i
)braket
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
OG
id|next
)paren
id|next
op_assign
id|page-&gt;index
suffix:semicolon
op_increment
id|next
suffix:semicolon
id|truncate_huge_page
c_func
(paren
id|mapping
comma
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|huge_pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|lstart
op_logical_and
id|mapping-&gt;nrpages
)paren
suffix:semicolon
)brace
DECL|function|hugetlbfs_delete_inode
r_static
r_void
id|hugetlbfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|inode-&gt;i_state
op_or_assign
id|I_FREEING
suffix:semicolon
id|inodes_stat.nr_inodes
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_data.nrpages
)paren
id|truncate_hugepages
c_func
(paren
op_amp
id|inode-&gt;i_data
comma
l_int|0
)paren
suffix:semicolon
id|security_inode_delete
c_func
(paren
id|inode
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|destroy_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|hugetlbfs_forget_inode
r_static
r_void
id|hugetlbfs_forget_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|super_block
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
)paren
r_goto
id|out_truncate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
(paren
id|I_DIRTY
op_or
id|I_LOCK
)paren
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_list
comma
op_amp
id|inode_unused
)paren
suffix:semicolon
)brace
id|inodes_stat.nr_unused
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|super_block
op_or
(paren
id|super_block-&gt;s_flags
op_amp
id|MS_ACTIVE
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* write_inode_now() ? */
id|inodes_stat.nr_unused
op_decrement
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_hash
)paren
suffix:semicolon
id|out_truncate
suffix:colon
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_list
)paren
suffix:semicolon
id|inode-&gt;i_state
op_or_assign
id|I_FREEING
suffix:semicolon
id|inodes_stat.nr_inodes
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_data.nrpages
)paren
id|truncate_hugepages
c_func
(paren
op_amp
id|inode-&gt;i_data
comma
l_int|0
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|destroy_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|hugetlbfs_drop_inode
r_static
r_void
id|hugetlbfs_drop_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
id|hugetlbfs_delete_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|hugetlbfs_forget_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|hugetlb_vmtruncate_list
r_static
r_void
id|hugetlb_vmtruncate_list
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_int
r_int
id|pgoff
)paren
(brace
r_int
r_int
id|start
comma
id|end
comma
id|length
comma
id|delta
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|vma
comma
id|list
comma
id|shared
)paren
(brace
id|start
op_assign
id|vma-&gt;vm_start
suffix:semicolon
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|length
op_assign
id|end
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_pgoff
op_ge
id|pgoff
)paren
(brace
id|zap_hugepage_range
c_func
(paren
id|vma
comma
id|start
comma
id|length
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|length
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|delta
op_assign
id|pgoff
op_assign
id|vma-&gt;vm_pgoff
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_ge
id|length
)paren
r_continue
suffix:semicolon
id|start
op_add_assign
id|delta
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|length
op_assign
(paren
id|length
op_minus
id|delta
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|zap_hugepage_range
c_func
(paren
id|vma
comma
id|start
comma
id|length
)paren
suffix:semicolon
)brace
)brace
DECL|function|hugetlb_vmtruncate
r_static
r_int
id|hugetlb_vmtruncate
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
r_int
r_int
id|pgoff
suffix:semicolon
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
id|pgoff
op_assign
(paren
id|offset
op_plus
id|HPAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|HPAGE_SHIFT
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
id|inode-&gt;i_size
op_assign
id|offset
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mapping-&gt;i_shared_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap
)paren
op_logical_and
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_shared
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap
)paren
)paren
id|hugetlb_vmtruncate_list
c_func
(paren
op_amp
id|mapping-&gt;i_mmap
comma
id|pgoff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_shared
)paren
)paren
id|hugetlb_vmtruncate_list
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_shared
comma
id|pgoff
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|mapping-&gt;i_shared_sem
)paren
suffix:semicolon
id|truncate_hugepages
c_func
(paren
id|mapping
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
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
id|inode-&gt;i_size
op_assign
id|offset
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
DECL|function|hugetlbfs_setattr
r_static
r_int
id|hugetlbfs_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
r_int
id|ia_valid
op_assign
id|attr-&gt;ia_valid
suffix:semicolon
r_int
r_int
id|dn_mask
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
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
id|error
op_assign
id|security_inode_setattr
c_func
(paren
id|dentry
comma
id|attr
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
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
id|ATTR_UID
op_logical_and
id|attr-&gt;ia_uid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_or
(paren
id|ia_valid
op_amp
id|ATTR_GID
op_logical_and
id|attr-&gt;ia_gid
op_ne
id|inode-&gt;i_gid
)paren
)paren
id|error
op_assign
id|DQUOT_TRANSFER
c_func
(paren
id|inode
comma
id|attr
)paren
ques
c_cond
op_minus
id|EDQUOT
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_SIZE
)paren
(brace
id|error
op_assign
id|hugetlb_vmtruncate
c_func
(paren
id|inode
comma
id|attr-&gt;ia_size
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
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
id|error
op_assign
id|inode_setattr
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|dn_mask
op_assign
id|setattr_mask
c_func
(paren
id|ia_valid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn_mask
)paren
id|dnotify_parent
c_func
(paren
id|dentry
comma
id|dn_mask
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_static
r_struct
id|inode
op_star
DECL|function|hugetlbfs_get_inode
id|hugetlbfs_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|mode
comma
id|dev_t
id|dev
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|NODEV
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hugetlbfs_aops
suffix:semicolon
id|inode-&gt;i_mapping-&gt;backing_dev_info
op_assign
op_amp
id|hugetlbfs_backing_dev_info
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_switch
c_cond
(paren
id|mode
op_amp
id|S_IFMT
)paren
(brace
r_default
suffix:colon
id|init_special_inode
c_func
(paren
id|inode
comma
id|mode
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFREG
suffix:colon
id|inode-&gt;i_fop
op_assign
op_amp
id|hugetlbfs_file_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|hugetlbfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
multiline_comment|/* directory inodes start off with i_nlink == 2 (for &quot;.&quot; entry) */
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * File creation. Allocate an inode, and we&squot;re done..&n; */
multiline_comment|/* SMP-safe */
r_static
r_int
DECL|function|hugetlbfs_mknod
id|hugetlbfs_mknod
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
id|dev_t
id|dev
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|hugetlbfs_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|mode
comma
id|dev
)paren
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Extra count - pin the dentry in core */
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|hugetlbfs_mkdir
r_static
r_int
id|hugetlbfs_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_int
id|retval
op_assign
id|hugetlbfs_mknod
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
op_or
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hugetlbfs_create
r_static
r_int
id|hugetlbfs_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_return
id|hugetlbfs_mknod
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
op_or
id|S_IFREG
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|hugetlbfs_symlink
r_static
r_int
id|hugetlbfs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|inode
op_assign
id|hugetlbfs_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|S_IFLNK
op_or
id|S_IRWXUGO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|symname
)paren
op_plus
l_int|1
suffix:semicolon
id|error
op_assign
id|page_symlink
c_func
(paren
id|inode
comma
id|symname
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_else
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|variable|hugetlbfs_aops
r_static
r_struct
id|address_space_operations
id|hugetlbfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|hugetlbfs_readpage
comma
dot
id|prepare_write
op_assign
id|hugetlbfs_prepare_write
comma
dot
id|commit_write
op_assign
id|hugetlbfs_commit_write
)brace
suffix:semicolon
DECL|variable|hugetlbfs_file_operations
r_struct
id|file_operations
id|hugetlbfs_file_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|write
op_assign
id|generic_file_write
comma
dot
id|mmap
op_assign
id|hugetlbfs_file_mmap
comma
dot
id|fsync
op_assign
id|simple_sync_file
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|hugetlbfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|hugetlbfs_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|hugetlbfs_create
comma
dot
id|lookup
op_assign
id|simple_lookup
comma
dot
id|link
op_assign
id|simple_link
comma
dot
id|unlink
op_assign
id|simple_unlink
comma
dot
id|symlink
op_assign
id|hugetlbfs_symlink
comma
dot
id|mkdir
op_assign
id|hugetlbfs_mkdir
comma
dot
id|rmdir
op_assign
id|simple_rmdir
comma
dot
id|mknod
op_assign
id|hugetlbfs_mknod
comma
dot
id|rename
op_assign
id|simple_rename
comma
dot
id|setattr
op_assign
id|hugetlbfs_setattr
comma
)brace
suffix:semicolon
DECL|variable|hugetlbfs_ops
r_static
r_struct
id|super_operations
id|hugetlbfs_ops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
comma
dot
id|drop_inode
op_assign
id|hugetlbfs_drop_inode
comma
)brace
suffix:semicolon
DECL|function|hugetlbfs_fill_super
r_static
r_int
id|hugetlbfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|HUGETLBFS_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|hugetlbfs_ops
suffix:semicolon
id|inode
op_assign
id|hugetlbfs_get_inode
c_func
(paren
id|sb
comma
id|S_IFDIR
op_or
l_int|0755
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sb-&gt;s_root
op_assign
id|root
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hugetlbfs_get_sb
r_static
r_struct
id|super_block
op_star
id|hugetlbfs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_nodev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|hugetlbfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|hugetlbfs_fs_type
r_static
r_struct
id|file_system_type
id|hugetlbfs_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hugetlbfs&quot;
comma
dot
id|get_sb
op_assign
id|hugetlbfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|variable|hugetlbfs_vfsmount
r_static
r_struct
id|vfsmount
op_star
id|hugetlbfs_vfsmount
suffix:semicolon
DECL|variable|hugetlbfs_counter
r_static
id|atomic_t
id|hugetlbfs_counter
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|function|hugetlb_zero_setup
r_struct
id|file
op_star
id|hugetlb_zero_setup
c_func
(paren
r_int
id|size
)paren
(brace
r_int
id|error
comma
id|n
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
comma
op_star
id|root
suffix:semicolon
r_struct
id|qstr
id|quick_string
suffix:semicolon
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EPERM
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_hugepage_mem_enough
c_func
(paren
id|size
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|n
op_assign
id|atomic_read
c_func
(paren
op_amp
id|hugetlbfs_counter
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|hugetlbfs_counter
)paren
suffix:semicolon
id|root
op_assign
id|hugetlbfs_vfsmount-&gt;mnt_root
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
l_int|16
comma
l_string|&quot;%d&quot;
comma
id|n
)paren
suffix:semicolon
id|quick_string.name
op_assign
id|buf
suffix:semicolon
id|quick_string.len
op_assign
id|strlen
c_func
(paren
id|quick_string.name
)paren
suffix:semicolon
id|quick_string.hash
op_assign
l_int|0
suffix:semicolon
id|dentry
op_assign
id|d_alloc
c_func
(paren
id|root
comma
op_amp
id|quick_string
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENFILE
suffix:semicolon
id|file
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out_dentry
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|inode
op_assign
id|hugetlbfs_get_inode
c_func
(paren
id|root-&gt;d_sb
comma
id|S_IFREG
op_or
id|S_IRWXUGO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_file
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|size
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|file-&gt;f_vfsmnt
op_assign
id|mntget
c_func
(paren
id|hugetlbfs_vfsmount
)paren
suffix:semicolon
id|file-&gt;f_dentry
op_assign
id|dentry
suffix:semicolon
id|file-&gt;f_op
op_assign
op_amp
id|hugetlbfs_file_operations
suffix:semicolon
id|file-&gt;f_mode
op_assign
id|FMODE_WRITE
op_or
id|FMODE_READ
suffix:semicolon
r_return
id|file
suffix:semicolon
id|out_file
suffix:colon
id|put_filp
c_func
(paren
id|file
)paren
suffix:semicolon
id|out_dentry
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
DECL|function|init_hugetlbfs_fs
r_static
r_int
id|__init
id|init_hugetlbfs_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|vfsmount
op_star
id|vfsmount
suffix:semicolon
id|error
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|hugetlbfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|vfsmount
op_assign
id|kern_mount
c_func
(paren
op_amp
id|hugetlbfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|vfsmount
)paren
)paren
(brace
id|hugetlbfs_vfsmount
op_assign
id|vfsmount
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|vfsmount
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|exit_hugetlbfs_fs
r_static
r_void
id|__exit
id|exit_hugetlbfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|hugetlbfs_fs_type
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_hugetlbfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_hugetlbfs_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
