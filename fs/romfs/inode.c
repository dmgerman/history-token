multiline_comment|/*&n; * ROMFS file system, Linux implementation&n; *&n; * Copyright (C) 1997-1999  Janos Farkas &lt;chexum@shadow.banki.hu&gt;&n; *&n; * Using parts of the minix filesystem&n; * Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; * and parts of the affs filesystem additionally&n; * Copyright (C) 1993  Ray Burr&n; * Copyright (C) 1996  Hans-Joachim Widmaier&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Changes&n; *&t;&t;&t;&t;&t;Changed for 2.1.19 modules&n; *&t;Jan 1997&t;&t;&t;Initial release&n; *&t;Jun 1997&t;&t;&t;2.1.43+ changes&n; *&t;&t;&t;&t;&t;Proper page locking in readpage&n; *&t;&t;&t;&t;&t;Changed to work with 2.1.45+ fs&n; *&t;Jul 1997&t;&t;&t;Fixed follow_link&n; *&t;&t;&t;2.1.47&n; *&t;&t;&t;&t;&t;lookup shouldn&squot;t return -ENOENT&n; *&t;&t;&t;&t;&t;from Horst von Brand:&n; *&t;&t;&t;&t;&t;  fail on wrong checksum&n; *&t;&t;&t;&t;&t;  double unlock_super was possible&n; *&t;&t;&t;&t;&t;  correct namelen for statfs&n; *&t;&t;&t;&t;&t;spotted by Bill Hawes:&n; *&t;&t;&t;&t;&t;  readlink shouldn&squot;t iput()&n; *&t;Jun 1998&t;2.1.106&t;&t;from Avery Pennarun: glibc scandir()&n; *&t;&t;&t;&t;&t;  exposed a problem in readdir&n; *&t;&t;&t;2.1.107&t;&t;code-freeze spellchecker run&n; *&t;Aug 1998&t;&t;&t;2.1.118+ VFS changes&n; *&t;Sep 1998&t;2.1.122&t;&t;another VFS change (follow_link)&n; *&t;Apr 1999&t;2.2.7&t;&t;no more EBADF checking in&n; *&t;&t;&t;&t;&t;  lookup/readdir, use ERR_PTR&n; *&t;Jun 1999&t;2.3.6&t;&t;d_alloc_root use changed&n; *&t;&t;&t;2.3.9&t;&t;clean up usage of ENOENT/negative&n; *&t;&t;&t;&t;&t;  dentries in lookup&n; *&t;&t;&t;&t;&t;clean up page flags setting&n; *&t;&t;&t;&t;&t;  (error, uptodate, locking) in&n; *&t;&t;&t;&t;&t;  in readpage&n; *&t;&t;&t;&t;&t;use init_special_inode for&n; *&t;&t;&t;&t;&t;  fifos/sockets (and streamline) in&n; *&t;&t;&t;&t;&t;  read_inode, fix _ops table order&n; *&t;Aug 1999&t;2.3.16&t;&t;__initfunc() =&gt; __init change&n; *&t;Oct 1999&t;2.3.24&t;&t;page-&gt;owner hack obsoleted&n; *&t;Nov 1999&t;2.3.27&t;&t;2.3.25+ page-&gt;offset =&gt; index change&n; */
multiline_comment|/* todo:&n; *&t;- see Documentation/filesystems/romfs.txt&n; *&t;- use allocated, not stack memory for file names?&n; *&t;- considering write access...&n; *&t;- network (tftp) files?&n; *&t;- merge back some _op tables&n; */
multiline_comment|/*&n; * Sorry about some optimizations and for some goto&squot;s.  I just wanted&n; * to squeeze some more bytes out of this code.. :)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/romfs_fs.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
id|__s32
DECL|function|romfs_checksum
id|romfs_checksum
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|__s32
id|sum
comma
op_star
id|ptr
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
id|ptr
op_assign
id|data
suffix:semicolon
id|size
op_rshift_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|sum
op_add_assign
id|ntohl
c_func
(paren
op_star
id|ptr
op_increment
)paren
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_return
id|sum
suffix:semicolon
)brace
DECL|variable|romfs_ops
r_static
r_struct
id|super_operations
id|romfs_ops
suffix:semicolon
r_static
r_struct
id|super_block
op_star
DECL|function|romfs_read_super
id|romfs_read_super
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
id|buffer_head
op_star
id|bh
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
r_struct
id|romfs_super_block
op_star
id|rsb
suffix:semicolon
r_int
id|sz
suffix:semicolon
multiline_comment|/* I would parse the options here, but there are none.. :) */
id|set_blocksize
c_func
(paren
id|dev
comma
id|ROMBSIZE
)paren
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
id|ROMBSIZE
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
id|ROMBSBITS
suffix:semicolon
id|s-&gt;u.generic_sbp
op_assign
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
id|s-&gt;s_maxbytes
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
multiline_comment|/* XXX merge with other printk? */
id|printk
(paren
l_string|&quot;romfs: unable to read superblock&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|outnobh
suffix:semicolon
)brace
id|rsb
op_assign
(paren
r_struct
id|romfs_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|sz
op_assign
id|ntohl
c_func
(paren
id|rsb-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsb-&gt;word0
op_ne
id|ROMSB_WORD0
op_logical_or
id|rsb-&gt;word1
op_ne
id|ROMSB_WORD1
op_logical_or
id|sz
OL
id|ROMFH_SIZE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
(paren
l_string|&quot;VFS: Can&squot;t find a romfs filesystem on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|romfs_checksum
c_func
(paren
id|rsb
comma
id|min_t
c_func
(paren
r_int
comma
id|sz
comma
l_int|512
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;romfs: bad initial checksum on dev &quot;
l_string|&quot;%s.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s-&gt;s_magic
op_assign
id|ROMFS_MAGIC
suffix:semicolon
id|s-&gt;u.romfs_sb.s_maxsize
op_assign
id|sz
suffix:semicolon
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
multiline_comment|/* Find the start of the fs */
id|sz
op_assign
(paren
id|ROMFH_SIZE
op_plus
id|strnlen
c_func
(paren
id|rsb-&gt;name
comma
id|ROMFS_MAXFN
)paren
op_plus
l_int|1
op_plus
id|ROMFH_PAD
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|romfs_ops
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|s
comma
id|sz
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
r_goto
id|outnobh
suffix:semicolon
multiline_comment|/* Ehrhm; sorry.. :)  And thanks to Hans-Joachim Widmaier  :) */
r_if
c_cond
(paren
l_int|0
)paren
(brace
id|out
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|outnobh
suffix:colon
id|s
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/* That&squot;s simple too. */
r_static
r_int
DECL|function|romfs_statfs
id|romfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
id|buf-&gt;f_type
op_assign
id|ROMFS_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|ROMBSIZE
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_ffree
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
(paren
id|sb-&gt;u.romfs_sb.s_maxsize
op_plus
id|ROMBSIZE
op_minus
l_int|1
)paren
op_rshift
id|ROMBSBITS
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|ROMFS_MAXFN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* some helper routines */
r_static
r_int
DECL|function|romfs_strnlen
id|romfs_strnlen
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|avail
comma
id|maxsize
comma
id|res
suffix:semicolon
id|maxsize
op_assign
id|i-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|maxsize
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* strnlen is almost always valid */
r_if
c_cond
(paren
id|count
OG
id|maxsize
op_logical_or
id|offset
op_plus
id|count
OG
id|maxsize
)paren
id|count
op_assign
id|maxsize
op_minus
id|offset
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|i-&gt;i_sb
comma
id|offset
op_rshift
id|ROMBSBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* error */
id|avail
op_assign
id|ROMBSIZE
op_minus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
suffix:semicolon
id|maxsize
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
comma
id|avail
)paren
suffix:semicolon
id|res
op_assign
id|strnlen
c_func
(paren
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
comma
id|maxsize
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
id|maxsize
)paren
r_return
id|res
suffix:semicolon
multiline_comment|/* found all of it */
r_while
c_loop
(paren
id|res
OL
id|count
)paren
(brace
id|offset
op_add_assign
id|maxsize
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|i-&gt;i_sb
comma
id|offset
op_rshift
id|ROMBSBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|maxsize
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
op_minus
id|res
comma
id|ROMBSIZE
)paren
suffix:semicolon
id|avail
op_assign
id|strnlen
c_func
(paren
id|bh-&gt;b_data
comma
id|maxsize
)paren
suffix:semicolon
id|res
op_add_assign
id|avail
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|avail
OL
id|maxsize
)paren
r_return
id|res
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
r_static
r_int
DECL|function|romfs_copyfrom
id|romfs_copyfrom
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_void
op_star
id|dest
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|avail
comma
id|maxsize
comma
id|res
suffix:semicolon
id|maxsize
op_assign
id|i-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|maxsize
op_logical_or
id|count
OG
id|maxsize
op_logical_or
id|offset
op_plus
id|count
OG
id|maxsize
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|i-&gt;i_sb
comma
id|offset
op_rshift
id|ROMBSBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* error */
id|avail
op_assign
id|ROMBSIZE
op_minus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
suffix:semicolon
id|maxsize
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
comma
id|avail
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
)paren
op_plus
(paren
id|offset
op_amp
id|ROMBMASK
)paren
comma
id|maxsize
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|res
op_assign
id|maxsize
suffix:semicolon
multiline_comment|/* all of it */
r_while
c_loop
(paren
id|res
OL
id|count
)paren
(brace
id|offset
op_add_assign
id|maxsize
suffix:semicolon
id|dest
op_add_assign
id|maxsize
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|i-&gt;i_sb
comma
id|offset
op_rshift
id|ROMBSBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|maxsize
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
op_minus
id|res
comma
id|ROMBSIZE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
id|bh-&gt;b_data
comma
id|maxsize
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|res
op_add_assign
id|maxsize
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|variable|romfs_dtype_table
r_static
r_int
r_char
id|romfs_dtype_table
(braket
)braket
op_assign
(brace
id|DT_UNKNOWN
comma
id|DT_DIR
comma
id|DT_REG
comma
id|DT_LNK
comma
id|DT_BLK
comma
id|DT_CHR
comma
id|DT_SOCK
comma
id|DT_FIFO
)brace
suffix:semicolon
r_static
r_int
DECL|function|romfs_readdir
id|romfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|inode
op_star
id|i
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|romfs_inode
id|ri
suffix:semicolon
r_int
r_int
id|offset
comma
id|maxoff
suffix:semicolon
r_int
id|j
comma
id|ino
comma
id|nextfh
suffix:semicolon
r_int
id|stored
op_assign
l_int|0
suffix:semicolon
r_char
id|fsname
(braket
id|ROMFS_MAXFN
)braket
suffix:semicolon
multiline_comment|/* XXX dynamic? */
id|maxoff
op_assign
id|i-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
id|offset
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
(brace
id|offset
op_assign
id|i-&gt;i_ino
op_amp
id|ROMFH_MASK
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|i
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_return
id|stored
suffix:semicolon
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
multiline_comment|/* Not really failsafe, but we are read-only... */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|offset
op_logical_or
id|offset
op_ge
id|maxoff
)paren
(brace
id|offset
op_assign
id|maxoff
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|stored
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_assign
id|offset
suffix:semicolon
multiline_comment|/* Fetch inode info */
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|i
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_return
id|stored
suffix:semicolon
id|j
op_assign
id|romfs_strnlen
c_func
(paren
id|i
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
r_sizeof
(paren
id|fsname
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|0
)paren
r_return
id|stored
suffix:semicolon
id|fsname
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
id|romfs_copyfrom
c_func
(paren
id|i
comma
id|fsname
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|j
)paren
suffix:semicolon
id|ino
op_assign
id|offset
suffix:semicolon
id|nextfh
op_assign
id|ntohl
c_func
(paren
id|ri.next
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nextfh
op_amp
id|ROMFH_TYPE
)paren
op_eq
id|ROMFH_HRD
)paren
id|ino
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|fsname
comma
id|j
comma
id|offset
comma
id|ino
comma
id|romfs_dtype_table
(braket
id|nextfh
op_amp
id|ROMFH_TYPE
)braket
)paren
OL
l_int|0
)paren
(brace
r_return
id|stored
suffix:semicolon
)brace
id|stored
op_increment
suffix:semicolon
id|offset
op_assign
id|nextfh
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
)brace
r_static
r_struct
id|dentry
op_star
DECL|function|romfs_lookup
id|romfs_lookup
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
)paren
(brace
r_int
r_int
id|offset
comma
id|maxoff
suffix:semicolon
r_int
id|fslen
comma
id|res
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
id|fsname
(braket
id|ROMFS_MAXFN
)braket
suffix:semicolon
multiline_comment|/* XXX dynamic? */
r_struct
id|romfs_inode
id|ri
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* got from dentry */
r_int
id|len
suffix:semicolon
id|res
op_assign
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* placeholder for &quot;no data here&quot; */
id|offset
op_assign
id|dir-&gt;i_ino
op_amp
id|ROMFH_MASK
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|dir
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|maxoff
op_assign
id|dir-&gt;i_sb-&gt;u.romfs_sb.s_maxsize
suffix:semicolon
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
multiline_comment|/* OK, now find the file whose name is in &quot;dentry&quot; in the&n;&t; * directory specified by &quot;dir&quot;.  */
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
id|len
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|offset
op_logical_or
id|offset
op_ge
id|maxoff
)paren
r_goto
id|out0
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|dir
comma
op_amp
id|ri
comma
id|offset
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* try to match the first 16 bytes of name */
id|fslen
op_assign
id|romfs_strnlen
c_func
(paren
id|dir
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|ROMFH_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|ROMFH_SIZE
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
id|fslen
)paren
(brace
multiline_comment|/* both are shorter, and same size */
id|romfs_copyfrom
c_func
(paren
id|dir
comma
id|fsname
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
(paren
id|name
comma
id|fsname
comma
id|len
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|fslen
op_ge
id|ROMFH_SIZE
)paren
(brace
multiline_comment|/* both are longer; XXX optimize max size */
id|fslen
op_assign
id|romfs_strnlen
c_func
(paren
id|dir
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
r_sizeof
(paren
id|fsname
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|fslen
)paren
(brace
id|romfs_copyfrom
c_func
(paren
id|dir
comma
id|fsname
comma
id|offset
op_plus
id|ROMFH_SIZE
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
id|fsname
comma
id|len
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* next entry */
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.next
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
multiline_comment|/* Hard link handling */
r_if
c_cond
(paren
(paren
id|ntohl
c_func
(paren
id|ri.next
)paren
op_amp
id|ROMFH_TYPE
)paren
op_eq
id|ROMFH_HRD
)paren
id|offset
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|offset
)paren
)paren
)paren
r_goto
id|outi
suffix:semicolon
multiline_comment|/*&n;&t; * it&squot;s a bit funky, _lookup needs to return an error code&n;&t; * (negative) or a NULL, both as a dentry.  ENOENT should not&n;&t; * be returned, instead we need to create a negative dentry by&n;&t; * d_add(dentry, NULL); and return 0 as no error.&n;&t; * (Although as I see, it only matters on writable file&n;&t; * systems).&n;&t; */
id|out0
suffix:colon
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|outi
suffix:colon
id|res
op_assign
l_int|0
suffix:semicolon
id|d_add
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, we do readpage, to be able to execute programs.  Unfortunately,&n; * we can&squot;t use bmap, since we may have looser alignments.&n; */
r_static
r_int
DECL|function|romfs_readpage
id|romfs_readpage
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
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
r_int
id|offset
comma
id|avail
comma
id|readlen
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|buf
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_goto
id|err_out
suffix:semicolon
multiline_comment|/* 32 bit warning -- but not for us :) */
id|offset
op_assign
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
id|inode-&gt;i_size
)paren
(brace
id|avail
op_assign
id|inode-&gt;i_size
op_minus
id|offset
suffix:semicolon
id|readlen
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|avail
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|inode
comma
id|buf
comma
id|inode-&gt;u.romfs_i.i_dataoffset
op_plus
id|offset
comma
id|readlen
)paren
op_eq
id|readlen
)paren
(brace
r_if
c_cond
(paren
id|readlen
OL
id|PAGE_SIZE
)paren
(brace
id|memset
c_func
(paren
id|buf
op_plus
id|readlen
comma
l_int|0
comma
id|PAGE_SIZE
op_minus
id|readlen
)paren
suffix:semicolon
)brace
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
)paren
(brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|err_out
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Mapping from our types to the kernel */
DECL|variable|romfs_aops
r_static
r_struct
id|address_space_operations
id|romfs_aops
op_assign
(brace
id|readpage
suffix:colon
id|romfs_readpage
)brace
suffix:semicolon
DECL|variable|romfs_dir_operations
r_static
r_struct
id|file_operations
id|romfs_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|romfs_readdir
comma
)brace
suffix:semicolon
DECL|variable|romfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|romfs_dir_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|romfs_lookup
comma
)brace
suffix:semicolon
DECL|variable|romfs_modemap
r_static
id|mode_t
id|romfs_modemap
(braket
)braket
op_assign
(brace
l_int|0
comma
id|S_IFDIR
op_plus
l_int|0644
comma
id|S_IFREG
op_plus
l_int|0644
comma
id|S_IFLNK
op_plus
l_int|0777
comma
id|S_IFBLK
op_plus
l_int|0600
comma
id|S_IFCHR
op_plus
l_int|0600
comma
id|S_IFSOCK
op_plus
l_int|0644
comma
id|S_IFIFO
op_plus
l_int|0644
)brace
suffix:semicolon
r_static
r_void
DECL|function|romfs_read_inode
id|romfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_int
id|nextfh
comma
id|ino
suffix:semicolon
r_struct
id|romfs_inode
id|ri
suffix:semicolon
id|ino
op_assign
id|i-&gt;i_ino
op_amp
id|ROMFH_MASK
suffix:semicolon
id|i-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Loop for finding the real hard link */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|romfs_copyfrom
c_func
(paren
id|i
comma
op_amp
id|ri
comma
id|ino
comma
id|ROMFH_SIZE
)paren
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;romfs: read error for inode 0x%x&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* XXX: do romfs_checksum here too (with name) */
id|nextfh
op_assign
id|ntohl
c_func
(paren
id|ri.next
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nextfh
op_amp
id|ROMFH_TYPE
)paren
op_ne
id|ROMFH_HRD
)paren
r_break
suffix:semicolon
id|ino
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
op_amp
id|ROMFH_MASK
suffix:semicolon
)brace
id|i-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Hard to decide.. */
id|i-&gt;i_size
op_assign
id|ntohl
c_func
(paren
id|ri.size
)paren
suffix:semicolon
id|i-&gt;i_mtime
op_assign
id|i-&gt;i_atime
op_assign
id|i-&gt;i_ctime
op_assign
l_int|0
suffix:semicolon
id|i-&gt;i_uid
op_assign
id|i-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Precalculate the data offset */
id|ino
op_assign
id|romfs_strnlen
c_func
(paren
id|i
comma
id|ino
op_plus
id|ROMFH_SIZE
comma
id|ROMFS_MAXFN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_ge
l_int|0
)paren
id|ino
op_assign
(paren
(paren
id|ROMFH_SIZE
op_plus
id|ino
op_plus
l_int|1
op_plus
id|ROMFH_PAD
)paren
op_amp
id|ROMFH_MASK
)paren
suffix:semicolon
r_else
id|ino
op_assign
l_int|0
suffix:semicolon
id|i-&gt;u.romfs_i.i_metasize
op_assign
id|ino
suffix:semicolon
id|i-&gt;u.romfs_i.i_dataoffset
op_assign
id|ino
op_plus
(paren
id|i-&gt;i_ino
op_amp
id|ROMFH_MASK
)paren
suffix:semicolon
multiline_comment|/* Compute permissions */
id|ino
op_assign
id|romfs_modemap
(braket
id|nextfh
op_amp
id|ROMFH_TYPE
)braket
suffix:semicolon
multiline_comment|/* only &quot;normal&quot; files have ops */
r_switch
c_cond
(paren
id|nextfh
op_amp
id|ROMFH_TYPE
)paren
(brace
r_case
l_int|1
suffix:colon
id|i-&gt;i_size
op_assign
id|i-&gt;u.romfs_i.i_metasize
suffix:semicolon
id|i-&gt;i_op
op_assign
op_amp
id|romfs_dir_inode_operations
suffix:semicolon
id|i-&gt;i_fop
op_assign
op_amp
id|romfs_dir_operations
suffix:semicolon
r_if
c_cond
(paren
id|nextfh
op_amp
id|ROMFH_EXEC
)paren
id|ino
op_or_assign
id|S_IXUGO
suffix:semicolon
id|i-&gt;i_mode
op_assign
id|ino
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|i-&gt;i_fop
op_assign
op_amp
id|generic_ro_fops
suffix:semicolon
id|i-&gt;i_data.a_ops
op_assign
op_amp
id|romfs_aops
suffix:semicolon
r_if
c_cond
(paren
id|nextfh
op_amp
id|ROMFH_EXEC
)paren
id|ino
op_or_assign
id|S_IXUGO
suffix:semicolon
id|i-&gt;i_mode
op_assign
id|ino
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|i-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|i-&gt;i_data.a_ops
op_assign
op_amp
id|romfs_aops
suffix:semicolon
id|i-&gt;i_mode
op_assign
id|ino
op_or
id|S_IRWXUGO
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* depending on MBZ for sock/fifos */
id|nextfh
op_assign
id|ntohl
c_func
(paren
id|ri.spec
)paren
suffix:semicolon
id|nextfh
op_assign
id|kdev_t_to_nr
c_func
(paren
id|MKDEV
c_func
(paren
id|nextfh
op_rshift
l_int|16
comma
id|nextfh
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
id|init_special_inode
c_func
(paren
id|i
comma
id|ino
comma
id|nextfh
)paren
suffix:semicolon
)brace
)brace
DECL|variable|romfs_ops
r_static
r_struct
id|super_operations
id|romfs_ops
op_assign
(brace
id|read_inode
suffix:colon
id|romfs_read_inode
comma
id|statfs
suffix:colon
id|romfs_statfs
comma
)brace
suffix:semicolon
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|romfs_fs_type
comma
l_string|&quot;romfs&quot;
comma
id|romfs_read_super
)paren
suffix:semicolon
DECL|function|init_romfs_fs
r_static
r_int
id|__init
id|init_romfs_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|romfs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_romfs_fs
r_static
r_void
id|__exit
id|exit_romfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|romfs_fs_type
)paren
suffix:semicolon
)brace
multiline_comment|/* Yes, works even as a module... :) */
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_romfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_romfs_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
