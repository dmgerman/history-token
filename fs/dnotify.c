multiline_comment|/*&n; * Directory notifications for Linux.&n; *&n; * Copyright (C) 2000,2001,2002 Stephen Rothwell&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
r_extern
r_void
id|send_sigio
c_func
(paren
r_struct
id|fown_struct
op_star
id|fown
comma
r_int
id|fd
comma
r_int
id|band
)paren
suffix:semicolon
DECL|variable|dir_notify_enable
r_int
id|dir_notify_enable
op_assign
l_int|1
suffix:semicolon
DECL|variable|dn_lock
r_static
id|rwlock_t
id|dn_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|dn_cache
r_static
id|kmem_cache_t
op_star
id|dn_cache
suffix:semicolon
DECL|function|redo_inode_mask
r_static
r_void
id|redo_inode_mask
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|new_mask
suffix:semicolon
r_struct
id|dnotify_struct
op_star
id|dn
suffix:semicolon
id|new_mask
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|dn
op_assign
id|inode-&gt;i_dnotify
suffix:semicolon
id|dn
op_ne
l_int|NULL
suffix:semicolon
id|dn
op_assign
id|dn-&gt;dn_next
)paren
id|new_mask
op_or_assign
id|dn-&gt;dn_mask
op_amp
op_complement
id|DN_MULTISHOT
suffix:semicolon
id|inode-&gt;i_dnotify_mask
op_assign
id|new_mask
suffix:semicolon
)brace
DECL|function|dnotify_flush
r_void
id|dnotify_flush
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|fl_owner_t
id|id
)paren
(brace
r_struct
id|dnotify_struct
op_star
id|dn
suffix:semicolon
r_struct
id|dnotify_struct
op_star
op_star
id|prev
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|dn_lock
)paren
suffix:semicolon
id|prev
op_assign
op_amp
id|inode-&gt;i_dnotify
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dn
op_assign
op_star
id|prev
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|dn-&gt;dn_owner
op_eq
id|id
)paren
op_logical_and
(paren
id|dn-&gt;dn_filp
op_eq
id|filp
)paren
)paren
(brace
op_star
id|prev
op_assign
id|dn-&gt;dn_next
suffix:semicolon
id|redo_inode_mask
c_func
(paren
id|inode
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|dn_cache
comma
id|dn
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|prev
op_assign
op_amp
id|dn-&gt;dn_next
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|dn_lock
)paren
suffix:semicolon
)brace
DECL|function|fcntl_dirnotify
r_int
id|fcntl_dirnotify
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|dnotify_struct
op_star
id|dn
suffix:semicolon
r_struct
id|dnotify_struct
op_star
id|odn
suffix:semicolon
r_struct
id|dnotify_struct
op_star
op_star
id|prev
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|fl_owner_t
id|id
op_assign
id|current-&gt;files
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|arg
op_amp
op_complement
id|DN_MULTISHOT
)paren
op_eq
l_int|0
)paren
(brace
id|dnotify_flush
c_func
(paren
id|filp
comma
id|id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir_notify_enable
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|ENOTDIR
suffix:semicolon
id|dn
op_assign
id|kmem_cache_alloc
c_func
(paren
id|dn_cache
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|dn_lock
)paren
suffix:semicolon
id|prev
op_assign
op_amp
id|inode-&gt;i_dnotify
suffix:semicolon
r_while
c_loop
(paren
(paren
id|odn
op_assign
op_star
id|prev
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|odn-&gt;dn_owner
op_eq
id|id
)paren
op_logical_and
(paren
id|odn-&gt;dn_filp
op_eq
id|filp
)paren
)paren
(brace
id|odn-&gt;dn_fd
op_assign
id|fd
suffix:semicolon
id|odn-&gt;dn_mask
op_or_assign
id|arg
suffix:semicolon
id|inode-&gt;i_dnotify_mask
op_or_assign
id|arg
op_amp
op_complement
id|DN_MULTISHOT
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|prev
op_assign
op_amp
id|odn-&gt;dn_next
suffix:semicolon
)brace
id|error
op_assign
id|f_setown
c_func
(paren
id|filp
comma
id|current-&gt;pid
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_free
suffix:semicolon
id|dn-&gt;dn_mask
op_assign
id|arg
suffix:semicolon
id|dn-&gt;dn_fd
op_assign
id|fd
suffix:semicolon
id|dn-&gt;dn_filp
op_assign
id|filp
suffix:semicolon
id|dn-&gt;dn_owner
op_assign
id|id
suffix:semicolon
id|inode-&gt;i_dnotify_mask
op_or_assign
id|arg
op_amp
op_complement
id|DN_MULTISHOT
suffix:semicolon
id|dn-&gt;dn_next
op_assign
id|inode-&gt;i_dnotify
suffix:semicolon
id|inode-&gt;i_dnotify
op_assign
id|dn
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|dn_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|out_free
suffix:colon
id|kmem_cache_free
c_func
(paren
id|dn_cache
comma
id|dn
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|__inode_dir_notify
r_void
id|__inode_dir_notify
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|event
)paren
(brace
r_struct
id|dnotify_struct
op_star
id|dn
suffix:semicolon
r_struct
id|dnotify_struct
op_star
op_star
id|prev
suffix:semicolon
r_struct
id|fown_struct
op_star
id|fown
suffix:semicolon
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|dn_lock
)paren
suffix:semicolon
id|prev
op_assign
op_amp
id|inode-&gt;i_dnotify
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dn
op_assign
op_star
id|prev
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|dn-&gt;dn_mask
op_amp
id|event
)paren
op_eq
l_int|0
)paren
(brace
id|prev
op_assign
op_amp
id|dn-&gt;dn_next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fown
op_assign
op_amp
id|dn-&gt;dn_filp-&gt;f_owner
suffix:semicolon
id|send_sigio
c_func
(paren
id|fown
comma
id|dn-&gt;dn_fd
comma
id|POLL_MSG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn-&gt;dn_mask
op_amp
id|DN_MULTISHOT
)paren
id|prev
op_assign
op_amp
id|dn-&gt;dn_next
suffix:semicolon
r_else
(brace
op_star
id|prev
op_assign
id|dn-&gt;dn_next
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|dn_cache
comma
id|dn
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|changed
)paren
id|redo_inode_mask
c_func
(paren
id|inode
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|dn_lock
)paren
suffix:semicolon
)brace
DECL|function|dnotify_init
r_static
r_int
id|__init
id|dnotify_init
c_func
(paren
r_void
)paren
(brace
id|dn_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;dnotify_cache&quot;
comma
r_sizeof
(paren
r_struct
id|dnotify_struct
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dn_cache
)paren
id|panic
c_func
(paren
l_string|&quot;cannot create dnotify slab cache&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|dnotify_init
)paren
eof
