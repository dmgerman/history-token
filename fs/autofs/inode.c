multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/inode.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
DECL|function|autofs_put_super
r_static
r_void
id|autofs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;catatonic
)paren
id|autofs_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
multiline_comment|/* Free wait queues, close pipe */
id|autofs_hash_nuke
c_func
(paren
op_amp
id|sbi-&gt;dirhash
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|AUTOFS_MAX_SYMLINKS
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
)paren
id|kfree
c_func
(paren
id|sbi-&gt;symlink
(braket
id|n
)braket
dot
id|data
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|sb-&gt;u.generic_sbp
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: shutting down&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|autofs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
DECL|variable|autofs_sops
r_static
r_struct
id|super_operations
id|autofs_sops
op_assign
(brace
dot
id|read_inode
op_assign
id|autofs_read_inode
comma
dot
id|put_super
op_assign
id|autofs_put_super
comma
dot
id|statfs
op_assign
id|simple_statfs
comma
)brace
suffix:semicolon
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|pipefd
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
comma
id|pid_t
op_star
id|pgrp
comma
r_int
op_star
id|minproto
comma
r_int
op_star
id|maxproto
)paren
(brace
r_char
op_star
id|this_char
comma
op_star
id|value
suffix:semicolon
op_star
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
op_star
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
op_star
id|pgrp
op_assign
id|current-&gt;pgrp
suffix:semicolon
op_star
id|minproto
op_assign
op_star
id|maxproto
op_assign
id|AUTOFS_PROTO_VERSION
suffix:semicolon
op_star
id|pipefd
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_char
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_char
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|this_char
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;fd&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|pipefd
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|uid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|gid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;pgrp&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|pgrp
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;minproto&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|minproto
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;maxproto&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|maxproto
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
(paren
op_star
id|pipefd
OL
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|autofs_fill_super
r_int
id|autofs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
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
id|root_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
r_struct
id|file
op_star
id|pipe
suffix:semicolon
r_int
id|pipefd
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
suffix:semicolon
r_int
id|minproto
comma
id|maxproto
suffix:semicolon
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sbi
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
r_goto
id|fail_unlock
suffix:semicolon
id|memset
c_func
(paren
id|sbi
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sbi
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: starting up, sbi = %p&bslash;n&quot;
comma
id|sbi
)paren
)paren
suffix:semicolon
id|s-&gt;u.generic_sbp
op_assign
id|sbi
suffix:semicolon
id|sbi-&gt;magic
op_assign
id|AUTOFS_SBI_MAGIC
suffix:semicolon
id|sbi-&gt;catatonic
op_assign
l_int|0
suffix:semicolon
id|sbi-&gt;exp_timeout
op_assign
l_int|0
suffix:semicolon
id|sbi-&gt;oz_pgrp
op_assign
id|current-&gt;pgrp
suffix:semicolon
id|autofs_initialize_hash
c_func
(paren
op_amp
id|sbi-&gt;dirhash
)paren
suffix:semicolon
id|sbi-&gt;queues
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sbi-&gt;symlink_bitmap
comma
l_int|0
comma
r_sizeof
(paren
r_int
)paren
op_star
id|AUTOFS_SYMLINK_BITMAP_LEN
)paren
suffix:semicolon
id|sbi-&gt;next_dir_ino
op_assign
id|AUTOFS_FIRST_DIR_INO
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|AUTOFS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|autofs_sops
suffix:semicolon
id|root_inode
op_assign
id|iget
c_func
(paren
id|s
comma
id|AUTOFS_ROOT_INO
)paren
suffix:semicolon
id|root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|pipe
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
r_goto
id|fail_iput
suffix:semicolon
multiline_comment|/* Can this call block?  - WTF cares? s is locked. */
r_if
c_cond
(paren
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|pipefd
comma
op_amp
id|root_inode-&gt;i_uid
comma
op_amp
id|root_inode-&gt;i_gid
comma
op_amp
id|sbi-&gt;oz_pgrp
comma
op_amp
id|minproto
comma
op_amp
id|maxproto
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: called with bogus options&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
multiline_comment|/* Couldn&squot;t this be tested earlier? */
r_if
c_cond
(paren
id|minproto
OG
id|AUTOFS_PROTO_VERSION
op_logical_or
id|maxproto
OL
id|AUTOFS_PROTO_VERSION
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: kernel does not match daemon version&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs: pipe fd = %d, pgrp = %u&bslash;n&quot;
comma
id|pipefd
comma
id|sbi-&gt;oz_pgrp
)paren
)paren
suffix:semicolon
id|pipe
op_assign
id|fget
c_func
(paren
id|pipefd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pipe
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: could not open pipe file descriptor&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pipe-&gt;f_op
op_logical_or
op_logical_neg
id|pipe-&gt;f_op-&gt;write
)paren
r_goto
id|fail_fput
suffix:semicolon
id|sbi-&gt;pipe
op_assign
id|pipe
suffix:semicolon
multiline_comment|/*&n;&t; * Success! Install the root dentry now to indicate completion.&n;&t; */
id|s-&gt;s_root
op_assign
id|root
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail_fput
suffix:colon
id|printk
c_func
(paren
l_string|&quot;autofs: pipe file descriptor does not contain proper ops&bslash;n&quot;
)paren
suffix:semicolon
id|fput
c_func
(paren
id|pipe
)paren
suffix:semicolon
id|fail_dput
suffix:colon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_goto
id|fail_free
suffix:semicolon
id|fail_iput
suffix:colon
id|printk
c_func
(paren
l_string|&quot;autofs: get root dentry failed&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|fail_free
suffix:colon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
id|fail_unlock
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|autofs_read_inode
r_static
r_void
id|autofs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|ino_t
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
multiline_comment|/* Initialize to the default case (stub directory) */
id|inode-&gt;i_op
op_assign
op_amp
id|simple_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
id|AUTOFS_ROOT_INO
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
op_or
id|S_IWUSR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|autofs_root_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|autofs_root_operations
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Changed in read_super */
r_return
suffix:semicolon
)brace
id|inode-&gt;i_uid
op_assign
id|inode-&gt;i_sb-&gt;s_root-&gt;d_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|inode-&gt;i_sb-&gt;s_root-&gt;d_inode-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
id|AUTOFS_FIRST_SYMLINK
op_logical_and
id|ino
OL
id|AUTOFS_FIRST_DIR_INO
)paren
(brace
multiline_comment|/* Symlink inode - should be in symlink list */
r_struct
id|autofs_symlink
op_star
id|sl
suffix:semicolon
id|n
op_assign
id|ino
op_minus
id|AUTOFS_FIRST_SYMLINK
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|AUTOFS_MAX_SYMLINKS
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: Looking for bad symlink inode %u&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
op_amp
id|autofs_symlink_inode_operations
suffix:semicolon
id|sl
op_assign
op_amp
id|sbi-&gt;symlink
(braket
id|n
)braket
suffix:semicolon
id|inode-&gt;u.generic_ip
op_assign
id|sl
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
id|S_IRWXUGO
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|sl-&gt;mtime
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|sl-&gt;len
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
)brace
eof
