multiline_comment|/* -*- c -*- --------------------------------------------------------------- *&n; *&n; * linux/fs/autofs/inode.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/parser.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
macro_line|#include &lt;linux/module.h&gt;
DECL|function|ino_lnkfree
r_static
r_void
id|ino_lnkfree
c_func
(paren
r_struct
id|autofs_info
op_star
id|ino
)paren
(brace
r_if
c_cond
(paren
id|ino-&gt;u.symlink
)paren
(brace
id|kfree
c_func
(paren
id|ino-&gt;u.symlink
)paren
suffix:semicolon
id|ino-&gt;u.symlink
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|autofs4_init_ino
r_struct
id|autofs_info
op_star
id|autofs4_init_ino
c_func
(paren
r_struct
id|autofs_info
op_star
id|ino
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
id|mode_t
id|mode
)paren
(brace
r_int
id|reinit
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
)paren
(brace
id|reinit
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ino
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|ino-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|ino-&gt;mode
op_assign
id|mode
suffix:semicolon
id|ino-&gt;inode
op_assign
l_int|NULL
suffix:semicolon
id|ino-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
id|ino-&gt;size
op_assign
l_int|0
suffix:semicolon
id|ino-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
id|ino-&gt;sbi
op_assign
id|sbi
suffix:semicolon
r_if
c_cond
(paren
id|reinit
op_logical_and
id|ino-&gt;free
)paren
(paren
id|ino-&gt;free
)paren
(paren
id|ino
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ino-&gt;u
comma
l_int|0
comma
r_sizeof
(paren
id|ino-&gt;u
)paren
)paren
suffix:semicolon
id|ino-&gt;free
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|ino-&gt;free
op_assign
id|ino_lnkfree
suffix:semicolon
r_return
id|ino
suffix:semicolon
)brace
DECL|function|autofs4_free_ino
r_void
id|autofs4_free_ino
c_func
(paren
r_struct
id|autofs_info
op_star
id|ino
)paren
(brace
r_if
c_cond
(paren
id|ino-&gt;dentry
)paren
(brace
id|ino-&gt;dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ino-&gt;dentry-&gt;d_inode
)paren
id|dput
c_func
(paren
id|ino-&gt;dentry
)paren
suffix:semicolon
id|ino-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ino-&gt;free
)paren
(paren
id|ino-&gt;free
)paren
(paren
id|ino
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ino
)paren
suffix:semicolon
)brace
DECL|function|autofs4_put_super
r_static
r_void
id|autofs4_put_super
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
id|autofs4_sbi
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;catatonic
)paren
id|autofs4_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
multiline_comment|/* Free wait queues, close pipe */
id|kfree
c_func
(paren
id|sbi
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
DECL|variable|autofs4_sops
r_static
r_struct
id|super_operations
id|autofs4_sops
op_assign
(brace
dot
id|put_super
op_assign
id|autofs4_put_super
comma
dot
id|statfs
op_assign
id|simple_statfs
comma
)brace
suffix:semicolon
DECL|enumerator|Opt_err
DECL|enumerator|Opt_fd
DECL|enumerator|Opt_uid
DECL|enumerator|Opt_gid
DECL|enumerator|Opt_pgrp
DECL|enumerator|Opt_minproto
DECL|enumerator|Opt_maxproto
r_enum
(brace
id|Opt_err
comma
id|Opt_fd
comma
id|Opt_uid
comma
id|Opt_gid
comma
id|Opt_pgrp
comma
id|Opt_minproto
comma
id|Opt_maxproto
)brace
suffix:semicolon
DECL|variable|tokens
r_static
id|match_table_t
id|tokens
op_assign
(brace
(brace
id|Opt_fd
comma
l_string|&quot;fd=%u&quot;
)brace
comma
(brace
id|Opt_uid
comma
l_string|&quot;uid=%u&quot;
)brace
comma
(brace
id|Opt_gid
comma
l_string|&quot;gid=%u&quot;
)brace
comma
(brace
id|Opt_pgrp
comma
l_string|&quot;pgrp=%u&quot;
)brace
comma
(brace
id|Opt_minproto
comma
l_string|&quot;minproto=%u&quot;
)brace
comma
(brace
id|Opt_maxproto
comma
l_string|&quot;maxproto=%u&quot;
)brace
comma
(brace
id|Opt_err
comma
l_int|NULL
)brace
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
id|p
suffix:semicolon
id|substring_t
id|args
(braket
id|MAX_OPT_ARGS
)braket
suffix:semicolon
r_int
id|option
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
id|process_group
c_func
(paren
id|current
)paren
suffix:semicolon
op_star
id|minproto
op_assign
id|AUTOFS_MIN_PROTO_VERSION
suffix:semicolon
op_star
id|maxproto
op_assign
id|AUTOFS_MAX_PROTO_VERSION
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
id|p
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
r_int
id|token
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
r_continue
suffix:semicolon
id|token
op_assign
id|match_token
c_func
(paren
id|p
comma
id|tokens
comma
id|args
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|token
)paren
(brace
r_case
id|Opt_fd
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
id|args
comma
id|pipefd
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_uid
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
id|args
comma
op_amp
id|option
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|uid
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_gid
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
id|args
comma
op_amp
id|option
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|gid
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_pgrp
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
id|args
comma
op_amp
id|option
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|pgrp
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_minproto
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
id|args
comma
op_amp
id|option
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|minproto
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_maxproto
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
id|args
comma
op_amp
id|option
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|maxproto
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
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
DECL|function|autofs4_mkroot
r_static
r_struct
id|autofs_info
op_star
id|autofs4_mkroot
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
)paren
(brace
r_struct
id|autofs_info
op_star
id|ino
suffix:semicolon
id|ino
op_assign
id|autofs4_init_ino
c_func
(paren
l_int|NULL
comma
id|sbi
comma
id|S_IFDIR
op_or
l_int|0755
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|ino
suffix:semicolon
)brace
DECL|function|autofs4_fill_super
r_int
id|autofs4_fill_super
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
r_struct
id|autofs_info
op_star
id|ino
suffix:semicolon
r_int
id|minproto
comma
id|maxproto
suffix:semicolon
id|sbi
op_assign
(paren
r_struct
id|autofs_sb_info
op_star
)paren
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
id|s-&gt;s_fs_info
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
id|process_group
c_func
(paren
id|current
)paren
suffix:semicolon
id|sbi-&gt;sb
op_assign
id|s
suffix:semicolon
id|sbi-&gt;version
op_assign
l_int|0
suffix:semicolon
id|sbi-&gt;sub_version
op_assign
l_int|0
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|sbi-&gt;wq_sem
)paren
suffix:semicolon
id|sbi-&gt;queues
op_assign
l_int|NULL
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
id|autofs4_sops
suffix:semicolon
multiline_comment|/*&n;&t; * Get the root inode and dentry, but defer checking for errors.&n;&t; */
id|ino
op_assign
id|autofs4_mkroot
c_func
(paren
id|sbi
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
r_goto
id|fail_free
suffix:semicolon
id|root_inode
op_assign
id|autofs4_get_inode
c_func
(paren
id|s
comma
id|ino
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|fail_free
suffix:semicolon
id|root_inode-&gt;i_op
op_assign
op_amp
id|autofs4_root_inode_operations
suffix:semicolon
id|root_inode-&gt;i_fop
op_assign
op_amp
id|autofs4_root_operations
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
multiline_comment|/* Can this call block? */
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
id|maxproto
template_param
id|AUTOFS_MAX_PROTO_VERSION
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: kernel does not match daemon version &quot;
l_string|&quot;daemon (%d, %d) kernel (%d, %d)&bslash;n&quot;
comma
id|minproto
comma
id|maxproto
comma
id|AUTOFS_MIN_PROTO_VERSION
comma
id|AUTOFS_MAX_PROTO_VERSION
)paren
suffix:semicolon
r_goto
id|fail_dput
suffix:semicolon
)brace
id|sbi-&gt;version
op_assign
id|maxproto
OG
id|AUTOFS_MAX_PROTO_VERSION
ques
c_cond
id|AUTOFS_MAX_PROTO_VERSION
suffix:colon
id|maxproto
suffix:semicolon
id|sbi-&gt;sub_version
op_assign
id|AUTOFS_PROTO_SUBVERSION
suffix:semicolon
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
multiline_comment|/*&n;&t; * Failure ... clean up.&n;&t; */
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
multiline_comment|/* fall through */
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
DECL|function|autofs4_get_inode
r_struct
id|inode
op_star
id|autofs4_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|autofs_info
op_star
id|inf
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
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|inf-&gt;inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|inf-&gt;mode
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_root
)paren
(brace
id|inode-&gt;i_uid
op_assign
id|sb-&gt;s_root-&gt;d_inode-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|sb-&gt;s_root-&gt;d_inode-&gt;i_gid
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
)brace
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inf-&gt;mode
)paren
)paren
(brace
id|inode-&gt;i_nlink
op_assign
l_int|2
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|autofs4_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|autofs4_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inf-&gt;mode
)paren
)paren
(brace
id|inode-&gt;i_size
op_assign
id|inf-&gt;size
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|autofs4_symlink_inode_operations
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
eof
