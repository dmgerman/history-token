multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 1998 Peter J. Braam &lt;braam@clusterfs.com&gt;&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *  Copyright (C) 2000 Los Alamos National Laboratory&n; *  Copyright (C) 2000 TurboLinux, Inc.&n; *  Copyright (C) 2001 Mountain View Data, Inc.&n; *  Copyright (C) 2001 Tacit Networks, Inc. &lt;phil@off.net&gt;&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#if defined(CONFIG_TMPFS)
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#if defined(CONFIG_EXT3)
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
macro_line|#if defined(CONFIG_TMPFS)
multiline_comment|/* space requirements: &n;   presto_do_truncate: &n;        used to truncate the KML forward to next fset-&gt;chunksize boundary&n;          - zero partial block&n;          - update inode&n;   presto_write_record: &n;        write header (&lt; one block) &n;        write one path (&lt; MAX_PATHLEN) &n;        possibly write another path (&lt; MAX_PATHLEN)&n;        write suffix (&lt; one block) &n;   presto_update_last_rcvd&n;        write one block&n;*/
DECL|function|presto_tmpfs_freespace
r_static
id|loff_t
id|presto_tmpfs_freespace
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
(paren
l_int|1
op_lshift
l_int|30
)paren
suffix:semicolon
)brace
multiline_comment|/* start the filesystem journal operations */
DECL|function|presto_tmpfs_trans_start
r_static
r_void
op_star
id|presto_tmpfs_trans_start
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|op
)paren
(brace
r_return
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
DECL|function|presto_tmpfs_trans_commit
r_static
r_void
id|presto_tmpfs_trans_commit
c_func
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_void
op_star
id|handle
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|presto_tmpfs_journal_file_data
r_static
r_void
id|presto_tmpfs_journal_file_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* The logic here is a slightly modified version of ext3/inode.c:block_to_path&n; */
DECL|function|presto_tmpfs_has_all_data
r_static
r_int
id|presto_tmpfs_has_all_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|presto_tmpfs_journal_ops
r_struct
id|journal_ops
id|presto_tmpfs_journal_ops
op_assign
(brace
dot
id|tr_all_data
op_assign
id|presto_tmpfs_has_all_data
comma
dot
id|tr_avail
op_assign
id|presto_tmpfs_freespace
comma
dot
id|tr_start
op_assign
id|presto_tmpfs_trans_start
comma
dot
id|tr_commit
op_assign
id|presto_tmpfs_trans_commit
comma
dot
id|tr_journal_data
op_assign
id|presto_tmpfs_journal_file_data
comma
dot
id|tr_ilookup
op_assign
id|presto_tmpfs_ilookup
comma
dot
id|tr_add_ilookup
op_assign
id|presto_add_ilookup_dentry
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_EXT3_FS */
eof
