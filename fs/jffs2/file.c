multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001-2003 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: file.c,v 1.98 2004/03/19 16:41:09 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/jffs2.h&gt;
macro_line|#include &quot;nodelist.h&quot;
r_extern
r_int
id|generic_file_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
id|loff_t
id|generic_file_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
DECL|function|jffs2_fsync
r_int
id|jffs2_fsync
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
multiline_comment|/* Trigger GC to flush any pending writes for this inode */
id|jffs2_flush_wbuf_gc
c_func
(paren
id|c
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jffs2_file_operations
r_struct
id|file_operations
id|jffs2_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|open
op_assign
id|generic_file_open
comma
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
id|ioctl
op_assign
id|jffs2_ioctl
comma
dot
id|mmap
op_assign
id|generic_file_readonly_mmap
comma
dot
id|fsync
op_assign
id|jffs2_fsync
comma
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,29)
dot
id|sendfile
op_assign
id|generic_file_sendfile
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* jffs2_file_inode_operations */
DECL|variable|jffs2_file_inode_operations
r_struct
id|inode_operations
id|jffs2_file_inode_operations
op_assign
(brace
dot
id|setattr
op_assign
id|jffs2_setattr
)brace
suffix:semicolon
DECL|variable|jffs2_file_address_operations
r_struct
id|address_space_operations
id|jffs2_file_address_operations
op_assign
(brace
dot
id|readpage
op_assign
id|jffs2_readpage
comma
dot
id|prepare_write
op_assign
id|jffs2_prepare_write
comma
dot
id|commit_write
op_assign
id|jffs2_commit_write
)brace
suffix:semicolon
DECL|function|jffs2_do_readpage_nolock
r_int
id|jffs2_do_readpage_nolock
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|pg
)paren
(brace
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
r_char
op_star
id|pg_buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_readpage_nolock(): ino #%lu, page at offset 0x%lx&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|pg
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|pg
)paren
suffix:semicolon
id|pg_buf
op_assign
id|kmap
c_func
(paren
id|pg
)paren
suffix:semicolon
multiline_comment|/* FIXME: Can kmap fail? */
id|ret
op_assign
id|jffs2_read_inode_range
c_func
(paren
id|c
comma
id|f
comma
id|pg_buf
comma
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ClearPageUptodate
c_func
(paren
id|pg
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
r_else
(brace
id|SetPageUptodate
c_func
(paren
id|pg
)paren
suffix:semicolon
id|ClearPageError
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
id|flush_dcache_page
c_func
(paren
id|pg
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|pg
)paren
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;readpage finished&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_do_readpage_unlock
r_int
id|jffs2_do_readpage_unlock
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|pg
)paren
(brace
r_int
id|ret
op_assign
id|jffs2_do_readpage_nolock
c_func
(paren
id|inode
comma
id|pg
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|pg
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_readpage
r_int
id|jffs2_readpage
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|page
op_star
id|pg
)paren
(brace
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|pg-&gt;mapping-&gt;host
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_do_readpage_unlock
c_func
(paren
id|pg-&gt;mapping-&gt;host
comma
id|pg
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_prepare_write
r_int
id|jffs2_prepare_write
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|page
op_star
id|pg
comma
r_int
id|start
comma
r_int
id|end
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|pg-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
r_uint32
id|pageofs
op_assign
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_prepare_write()&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pageofs
OG
id|inode-&gt;i_size
)paren
(brace
multiline_comment|/* Make new hole frag from old EOF to new page */
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|jffs2_raw_inode
id|ri
suffix:semicolon
r_struct
id|jffs2_full_dnode
op_star
id|fn
suffix:semicolon
r_uint32
id|phys_ofs
comma
id|alloc_len
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Writing new hole frag 0x%x-0x%x between current EOF and new page&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_size
comma
id|pageofs
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_reserve_space
c_func
(paren
id|c
comma
r_sizeof
(paren
id|ri
)paren
comma
op_amp
id|phys_ofs
comma
op_amp
id|alloc_len
comma
id|ALLOC_NORMAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ri
comma
l_int|0
comma
r_sizeof
(paren
id|ri
)paren
)paren
suffix:semicolon
id|ri.magic
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_MAGIC_BITMASK
)paren
suffix:semicolon
id|ri.nodetype
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_NODETYPE_INODE
)paren
suffix:semicolon
id|ri.totlen
op_assign
id|cpu_to_je32
c_func
(paren
r_sizeof
(paren
id|ri
)paren
)paren
suffix:semicolon
id|ri.hdr_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
op_amp
id|ri
comma
r_sizeof
(paren
r_struct
id|jffs2_unknown_node
)paren
op_minus
l_int|4
)paren
)paren
suffix:semicolon
id|ri.ino
op_assign
id|cpu_to_je32
c_func
(paren
id|f-&gt;inocache-&gt;ino
)paren
suffix:semicolon
id|ri.version
op_assign
id|cpu_to_je32
c_func
(paren
op_increment
id|f-&gt;highest_version
)paren
suffix:semicolon
id|ri.mode
op_assign
id|cpu_to_jemode
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|ri.uid
op_assign
id|cpu_to_je16
c_func
(paren
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|ri.gid
op_assign
id|cpu_to_je16
c_func
(paren
id|inode-&gt;i_gid
)paren
suffix:semicolon
id|ri.isize
op_assign
id|cpu_to_je32
c_func
(paren
id|max
c_func
(paren
(paren
r_uint32
)paren
id|inode-&gt;i_size
comma
id|pageofs
)paren
)paren
suffix:semicolon
id|ri.atime
op_assign
id|ri.ctime
op_assign
id|ri.mtime
op_assign
id|cpu_to_je32
c_func
(paren
id|get_seconds
c_func
(paren
)paren
)paren
suffix:semicolon
id|ri.offset
op_assign
id|cpu_to_je32
c_func
(paren
id|inode-&gt;i_size
)paren
suffix:semicolon
id|ri.dsize
op_assign
id|cpu_to_je32
c_func
(paren
id|pageofs
op_minus
id|inode-&gt;i_size
)paren
suffix:semicolon
id|ri.csize
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ri.compr
op_assign
id|JFFS2_COMPR_ZERO
suffix:semicolon
id|ri.node_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
op_amp
id|ri
comma
r_sizeof
(paren
id|ri
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|ri.data_crc
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|fn
op_assign
id|jffs2_write_dnode
c_func
(paren
id|c
comma
id|f
comma
op_amp
id|ri
comma
l_int|NULL
comma
l_int|0
comma
id|phys_ofs
comma
id|ALLOC_NORMAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fn
)paren
)paren
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|fn
)paren
suffix:semicolon
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|jffs2_add_full_dnode_to_inode
c_func
(paren
id|c
comma
id|f
comma
id|fn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;metadata
)paren
(brace
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|f-&gt;metadata-&gt;raw
)paren
suffix:semicolon
id|jffs2_free_full_dnode
c_func
(paren
id|f-&gt;metadata
)paren
suffix:semicolon
id|f-&gt;metadata
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Eep. add_full_dnode_to_inode() failed in prepare_write, returned %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|fn-&gt;raw
)paren
suffix:semicolon
id|jffs2_free_full_dnode
c_func
(paren
id|fn
)paren
suffix:semicolon
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|pageofs
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
)brace
multiline_comment|/* Read in the page if it wasn&squot;t already present, unless it&squot;s a whole page */
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|pg
)paren
op_logical_and
(paren
id|start
op_logical_or
id|end
OL
id|PAGE_CACHE_SIZE
)paren
)paren
(brace
id|down
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_do_readpage_nolock
c_func
(paren
id|inode
comma
id|pg
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;end prepare_write(). pg-&gt;flags %lx&bslash;n&quot;
comma
id|pg-&gt;flags
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_commit_write
r_int
id|jffs2_commit_write
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|page
op_star
id|pg
comma
r_int
id|start
comma
r_int
id|end
)paren
(brace
multiline_comment|/* Actually commit the write from the page cache page we&squot;re looking at.&n;&t; * For now, we write the full page out each time. It sucks, but it&squot;s simple&n;&t; */
r_struct
id|inode
op_star
id|inode
op_assign
id|pg-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|jffs2_raw_inode
op_star
id|ri
suffix:semicolon
r_int
id|aligned_start
op_assign
id|start
op_amp
op_complement
l_int|3
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_uint32
id|writtenlen
op_assign
l_int|0
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_commit_write(): ino #%lu, page at 0x%lx, range %d-%d, flags %lx&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
comma
id|start
comma
id|end
comma
id|pg-&gt;flags
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start
op_logical_and
id|end
op_eq
id|PAGE_CACHE_SIZE
)paren
(brace
multiline_comment|/* We need to avoid deadlock with page_cache_read() in&n;&t;&t;   jffs2_garbage_collect_pass(). So we have to mark the&n;&t;&t;   page up to date, to prevent page_cache_read() from &n;&t;&t;   trying to re-lock it. */
id|SetPageUptodate
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
id|ri
op_assign
id|jffs2_alloc_raw_inode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ri
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_commit_write(): Allocation of raw inode failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* Set the fields that the generic jffs2_write_inode_range() code can&squot;t find */
id|ri-&gt;ino
op_assign
id|cpu_to_je32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ri-&gt;mode
op_assign
id|cpu_to_jemode
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|ri-&gt;uid
op_assign
id|cpu_to_je16
c_func
(paren
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|ri-&gt;gid
op_assign
id|cpu_to_je16
c_func
(paren
id|inode-&gt;i_gid
)paren
suffix:semicolon
id|ri-&gt;isize
op_assign
id|cpu_to_je32
c_func
(paren
(paren
r_uint32
)paren
id|inode-&gt;i_size
)paren
suffix:semicolon
id|ri-&gt;atime
op_assign
id|ri-&gt;ctime
op_assign
id|ri-&gt;mtime
op_assign
id|cpu_to_je32
c_func
(paren
id|get_seconds
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* In 2.4, it was already kmapped by generic_file_write(). Doesn&squot;t&n;&t;   hurt to do it again. The alternative is ifdefs, which are ugly. */
id|kmap
c_func
(paren
id|pg
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_write_inode_range
c_func
(paren
id|c
comma
id|f
comma
id|ri
comma
id|page_address
c_func
(paren
id|pg
)paren
op_plus
id|aligned_start
comma
(paren
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|aligned_start
comma
id|end
op_minus
id|aligned_start
comma
op_amp
id|writtenlen
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|pg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* There was an error writing. */
id|SetPageError
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
multiline_comment|/* Adjust writtenlen for the padding we did, so we don&squot;t confuse our caller */
r_if
c_cond
(paren
id|writtenlen
OL
(paren
id|start
op_amp
l_int|3
)paren
)paren
id|writtenlen
op_assign
l_int|0
suffix:semicolon
r_else
id|writtenlen
op_sub_assign
(paren
id|start
op_amp
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writtenlen
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_size
OL
(paren
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|start
op_plus
id|writtenlen
)paren
(brace
id|inode-&gt;i_size
op_assign
(paren
id|pg-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|start
op_plus
id|writtenlen
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;ctime
)paren
)paren
suffix:semicolon
)brace
)brace
id|jffs2_free_raw_inode
c_func
(paren
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_plus
id|writtenlen
OL
id|end
)paren
(brace
multiline_comment|/* generic_file_write has written more to the page cache than we&squot;ve&n;&t;&t;   actually written to the medium. Mark the page !Uptodate so that &n;&t;&t;   it gets reread */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_commit_write(): Not all bytes written. Marking page !uptodate&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|pg
)paren
suffix:semicolon
id|ClearPageUptodate
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_commit_write() returning %d&bslash;n&quot;
comma
id|writtenlen
ques
c_cond
id|writtenlen
suffix:colon
id|ret
)paren
)paren
suffix:semicolon
r_return
id|writtenlen
ques
c_cond
id|writtenlen
suffix:colon
id|ret
suffix:semicolon
)brace
eof
