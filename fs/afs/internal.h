multiline_comment|/* internal.h: internal AFS stuff&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef AFS_INTERNAL_H
DECL|macro|AFS_INTERNAL_H
mdefine_line|#define AFS_INTERNAL_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
multiline_comment|/*&n; * debug tracing&n; */
DECL|macro|kenter
mdefine_line|#define kenter(FMT,...)&t;printk(&quot;==&gt; %s(&quot;FMT&quot;)&bslash;n&quot;,__FUNCTION__,##__VA_ARGS__)
DECL|macro|kleave
mdefine_line|#define kleave(FMT,...)&t;printk(&quot;&lt;== %s()&quot;FMT&quot;&bslash;n&quot;,__FUNCTION__,##__VA_ARGS__)
DECL|macro|kdebug
mdefine_line|#define kdebug(FMT,...)&t;printk(FMT&quot;&bslash;n&quot;,##__VA_ARGS__)
DECL|macro|kproto
mdefine_line|#define kproto(FMT,...)&t;printk(&quot;### &quot;FMT&quot;&bslash;n&quot;,##__VA_ARGS__)
DECL|macro|knet
mdefine_line|#define knet(FMT,...)&t;printk(FMT&quot;&bslash;n&quot;,##__VA_ARGS__)
macro_line|#if 0
mdefine_line|#define _enter(FMT,...)&t;kenter(FMT,##__VA_ARGS__)
mdefine_line|#define _leave(FMT,...)&t;kleave(FMT,##__VA_ARGS__)
mdefine_line|#define _debug(FMT,...)&t;kdebug(FMT,##__VA_ARGS__)
mdefine_line|#define _proto(FMT,...)&t;kproto(FMT,##__VA_ARGS__)
mdefine_line|#define _net(FMT,...)&t;knet(FMT,##__VA_ARGS__)
macro_line|#else
DECL|macro|_enter
mdefine_line|#define _enter(FMT,...)&t;do { } while(0)
DECL|macro|_leave
mdefine_line|#define _leave(FMT,...)&t;do { } while(0)
DECL|macro|_debug
mdefine_line|#define _debug(FMT,...)&t;do { } while(0)
DECL|macro|_proto
mdefine_line|#define _proto(FMT,...)&t;do { } while(0)
DECL|macro|_net
mdefine_line|#define _net(FMT,...)&t;do { } while(0)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt;= KERNEL_VERSION(2,5,0)
DECL|macro|wait_on_page_locked
mdefine_line|#define wait_on_page_locked wait_on_page
DECL|macro|PageUptodate
mdefine_line|#define PageUptodate Page_Uptodate
DECL|function|PDE
r_static
r_inline
r_struct
id|proc_dir_entry
op_star
id|PDE
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
)brace
macro_line|#endif
DECL|function|afs_discard_my_signals
r_static
r_inline
r_void
id|afs_discard_my_signals
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|siginfo_t
id|sinfo
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|dequeue_signal
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|sinfo
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * cell.c&n; */
r_extern
r_struct
id|rw_semaphore
id|afs_proc_cells_sem
suffix:semicolon
r_extern
r_struct
id|list_head
id|afs_proc_cells
suffix:semicolon
multiline_comment|/*&n; * dir.c&n; */
r_extern
r_struct
id|inode_operations
id|afs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|afs_dir_file_operations
suffix:semicolon
multiline_comment|/*&n; * file.c&n; */
r_extern
r_struct
id|address_space_operations
id|afs_fs_aops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|afs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|afs_file_file_operations
suffix:semicolon
multiline_comment|/*&n; * inode.c&n; */
r_extern
r_int
id|afs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|afs_fid_t
op_star
id|fid
comma
r_struct
id|inode
op_star
op_star
id|_inode
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,0)
r_extern
r_int
id|afs_inode_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
suffix:semicolon
macro_line|#else
r_extern
r_void
id|afs_read_inode2
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|opaque
)paren
suffix:semicolon
r_extern
r_int
id|afs_inode_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|afs_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/*&n; * mntpt.c&n; */
r_extern
r_struct
id|inode_operations
id|afs_mntpt_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|afs_mntpt_file_operations
suffix:semicolon
r_extern
r_int
id|afs_mntpt_check_symlink
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
)paren
suffix:semicolon
multiline_comment|/*&n; * super.c&n; */
r_extern
r_int
id|afs_fs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|afs_fs_exit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|AFS_CB_HASH_COUNT
mdefine_line|#define AFS_CB_HASH_COUNT (PAGE_SIZE/sizeof(struct list_head))
r_extern
r_struct
id|list_head
id|afs_cb_hash_tbl
(braket
)braket
suffix:semicolon
r_extern
id|spinlock_t
id|afs_cb_hash_lock
suffix:semicolon
DECL|macro|afs_cb_hash
mdefine_line|#define afs_cb_hash(SRV,FID) &bslash;&n;&t;afs_cb_hash_tbl[((unsigned)(SRV) + (FID)-&gt;vid + (FID)-&gt;vnode + (FID)-&gt;unique) % &bslash;&n;&t;&t;&t;AFS_CB_HASH_COUNT]
multiline_comment|/*&n; * proc.c&n; */
r_extern
r_int
id|afs_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|afs_proc_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|afs_proc_cell_setup
c_func
(paren
id|afs_cell_t
op_star
id|cell
)paren
suffix:semicolon
r_extern
r_void
id|afs_proc_cell_remove
c_func
(paren
id|afs_cell_t
op_star
id|cell
)paren
suffix:semicolon
macro_line|#endif /* AFS_INTERNAL_H */
eof
