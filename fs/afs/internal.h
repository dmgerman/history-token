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
mdefine_line|#define kenter(FMT, a...)&t;printk(&quot;==&gt; %s(&quot;FMT&quot;)&bslash;n&quot;,__FUNCTION__ , ## a)
DECL|macro|kleave
mdefine_line|#define kleave(FMT, a...)&t;printk(&quot;&lt;== %s()&quot;FMT&quot;&bslash;n&quot;,__FUNCTION__ , ## a)
DECL|macro|kdebug
mdefine_line|#define kdebug(FMT, a...)&t;printk(FMT&quot;&bslash;n&quot; , ## a)
DECL|macro|kproto
mdefine_line|#define kproto(FMT, a...)&t;printk(&quot;### &quot;FMT&quot;&bslash;n&quot; , ## a)
DECL|macro|knet
mdefine_line|#define knet(FMT, a...)&t;&t;printk(FMT&quot;&bslash;n&quot; , ## a)
macro_line|#if 0
mdefine_line|#define _enter(FMT, a...)&t;kenter(FMT , ## a)
mdefine_line|#define _leave(FMT, a...)&t;kleave(FMT , ## a)
mdefine_line|#define _debug(FMT, a...)&t;kdebug(FMT , ## a)
mdefine_line|#define _proto(FMT, a...)&t;kproto(FMT , ## a)
mdefine_line|#define _net(FMT, a...)&t;&t;knet(FMT , ## a)
macro_line|#else
DECL|macro|_enter
mdefine_line|#define _enter(FMT, a...)&t;do { } while(0)
DECL|macro|_leave
mdefine_line|#define _leave(FMT, a...)&t;do { } while(0)
DECL|macro|_debug
mdefine_line|#define _debug(FMT, a...)&t;do { } while(0)
DECL|macro|_proto
mdefine_line|#define _proto(FMT, a...)&t;do { } while(0)
DECL|macro|_net
mdefine_line|#define _net(FMT, a...)&t;&t;do { } while(0)
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
mdefine_line|#define afs_cb_hash(SRV,FID) &bslash;&n;&t;afs_cb_hash_tbl[((unsigned long)(SRV) + (FID)-&gt;vid + (FID)-&gt;vnode + (FID)-&gt;unique) % &bslash;&n;&t;&t;&t;AFS_CB_HASH_COUNT]
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
