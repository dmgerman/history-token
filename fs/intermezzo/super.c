multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 1998 Peter J. Braam &lt;braam@clusterfs.com&gt;&n; *  Copyright (C) 2000 Stelias Computing, Inc.&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  presto&squot;s super.c&n; */
r_static
r_char
id|rcsid
(braket
)braket
id|__attribute
(paren
(paren
id|unused
)paren
)paren
op_assign
l_string|&quot;$Id: super.c,v 1.4 2002/10/12 02:16:19 rread Exp $&quot;
suffix:semicolon
DECL|macro|INTERMEZZO_VERSION
mdefine_line|#define INTERMEZZO_VERSION &quot;$Revision: 1.4 $&quot;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
macro_line|#ifdef PRESTO_DEBUG
DECL|variable|presto_vmemory
r_int
id|presto_vmemory
op_assign
l_int|0
suffix:semicolon
DECL|variable|presto_kmemory
r_int
id|presto_kmemory
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* returns an allocated string, copied out from data if opt is found */
DECL|function|opt_read
r_static
r_char
op_star
id|opt_read
c_func
(paren
r_const
r_char
op_star
id|opt
comma
r_char
op_star
id|data
)paren
(brace
r_char
op_star
id|value
suffix:semicolon
r_char
op_star
id|retval
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;option: %s, data %s&bslash;n&quot;
comma
id|opt
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|opt
comma
id|data
comma
id|strlen
c_func
(paren
id|opt
)paren
)paren
)paren
r_return
l_int|NULL
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
id|data
comma
l_char|&squot;=&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|value
op_increment
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|retval
comma
id|strlen
c_func
(paren
id|value
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: Out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|retval
comma
id|value
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;Assigned option: %s, value %s&bslash;n&quot;
comma
id|opt
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|opt_store
r_static
r_void
id|opt_store
c_func
(paren
r_char
op_star
op_star
id|dst
comma
r_char
op_star
id|opt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
id|CERROR
c_func
(paren
l_string|&quot;intermezzo: store_opt, error dst == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dst
)paren
id|PRESTO_FREE
c_func
(paren
op_star
id|dst
comma
id|strlen
c_func
(paren
op_star
id|dst
)paren
op_plus
l_int|1
)paren
suffix:semicolon
op_star
id|dst
op_assign
id|opt
suffix:semicolon
)brace
DECL|function|opt_set_default
r_static
r_void
id|opt_set_default
c_func
(paren
r_char
op_star
op_star
id|dst
comma
r_char
op_star
id|defval
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
id|CERROR
c_func
(paren
l_string|&quot;intermezzo: store_opt, error dst == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dst
)paren
id|PRESTO_FREE
c_func
(paren
op_star
id|dst
comma
id|strlen
c_func
(paren
op_star
id|dst
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|defval
)paren
(brace
r_char
op_star
id|def_alloced
suffix:semicolon
id|PRESTO_ALLOC
c_func
(paren
id|def_alloced
comma
id|strlen
c_func
(paren
id|defval
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|def_alloced
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: Out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|def_alloced
comma
id|defval
)paren
suffix:semicolon
op_star
id|dst
op_assign
id|def_alloced
suffix:semicolon
)brace
)brace
multiline_comment|/* Find the options for InterMezzo in &quot;options&quot;, saving them into the&n; * passed pointers.  If the pointer is null, the option is discarded.&n; * Copy out all non-InterMezzo options into cache_data (to be passed&n; * to the read_super operation of the cache).  The return value will&n; * be a pointer to the end of the cache_data.&n; */
DECL|function|presto_options
r_static
r_char
op_star
id|presto_options
c_func
(paren
r_struct
id|file_system_type
op_star
id|fstype
comma
r_char
op_star
id|options
comma
r_char
op_star
id|cache_data
comma
r_char
op_star
op_star
id|cache_type
comma
r_char
op_star
op_star
id|fileset
comma
r_char
op_star
op_star
id|channel
)paren
(brace
r_char
op_star
id|this_char
suffix:semicolon
r_char
op_star
id|opt_ptr
op_assign
id|options
suffix:semicolon
r_char
op_star
id|cache_data_end
op_assign
id|cache_data
suffix:semicolon
multiline_comment|/* set the defaults */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|fstype-&gt;name
comma
l_string|&quot;intermezzo&quot;
)paren
op_eq
l_int|0
)paren
id|opt_set_default
c_func
(paren
id|cache_type
comma
l_string|&quot;ext3&quot;
)paren
suffix:semicolon
r_else
id|opt_set_default
c_func
(paren
id|cache_type
comma
l_string|&quot;tmpfs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
id|cache_data
)paren
r_return
id|cache_data_end
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;parsing options&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_char
op_assign
id|strsep
(paren
op_amp
id|opt_ptr
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|opt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_char
)paren
r_continue
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;this_char %s&bslash;n&quot;
comma
id|this_char
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|opt
op_assign
id|opt_read
c_func
(paren
l_string|&quot;fileset&quot;
comma
id|this_char
)paren
)paren
)paren
(brace
id|opt_store
c_func
(paren
id|fileset
comma
id|opt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|opt
op_assign
id|opt_read
c_func
(paren
l_string|&quot;cache_type&quot;
comma
id|this_char
)paren
)paren
)paren
(brace
id|opt_store
c_func
(paren
id|cache_type
comma
id|opt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|opt
op_assign
id|opt_read
c_func
(paren
l_string|&quot;channel&quot;
comma
id|this_char
)paren
)paren
)paren
(brace
id|opt_store
c_func
(paren
id|channel
comma
id|opt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cache_data_end
op_add_assign
id|sprintf
c_func
(paren
id|cache_data_end
comma
l_string|&quot;%s%s&quot;
comma
id|cache_data_end
op_ne
id|cache_data
ques
c_cond
l_string|&quot;,&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|this_char
)paren
suffix:semicolon
)brace
r_return
id|cache_data_end
suffix:semicolon
)brace
DECL|function|presto_set_channel
r_static
r_int
id|presto_set_channel
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
r_char
op_star
id|channel
)paren
(brace
r_int
id|minor
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|channel
)paren
(brace
id|minor
op_assign
id|izo_psdev_get_free_channel
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|minor
op_assign
id|simple_strtoul
c_func
(paren
id|channel
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|minor
OL
l_int|0
op_logical_or
id|minor
op_ge
id|MAX_CHANNEL
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;all channels in use or channel too large %d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cache-&gt;cache_psdev
op_assign
op_amp
(paren
id|izo_channels
(braket
id|minor
)braket
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|cache-&gt;cache_channel_list
comma
op_amp
id|cache-&gt;cache_psdev-&gt;uc_cache_list
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|minor
suffix:semicolon
)brace
multiline_comment|/* We always need to remove the presto options before passing &n;   mount options to cache FS */
r_struct
id|super_block
op_star
DECL|function|presto_get_sb
id|presto_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|izo_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|file_system_type
op_star
id|fstype
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|cache_data
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|cache_data_end
suffix:semicolon
r_char
op_star
id|cache_type
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|fileset
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|channel
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|minor
suffix:semicolon
id|ENTRY
suffix:semicolon
multiline_comment|/* reserve space for the cache&squot;s data */
id|PRESTO_ALLOC
c_func
(paren
id|cache_data
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_data
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto_read_super: Cannot allocate data page.&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* read and validate options */
id|cache_data_end
op_assign
id|presto_options
c_func
(paren
id|izo_type
comma
id|data
comma
id|cache_data
comma
op_amp
id|cache_type
comma
op_amp
id|fileset
comma
op_amp
id|channel
)paren
suffix:semicolon
multiline_comment|/* was there anything for the cache filesystem in the data? */
r_if
c_cond
(paren
id|cache_data_end
op_eq
id|cache_data
)paren
(brace
id|PRESTO_FREE
c_func
(paren
id|cache_data
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|cache_data_end
op_assign
id|cache_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;cache_data at %p is: %s&bslash;n&quot;
comma
id|cache_data
comma
id|cache_data
)paren
suffix:semicolon
)brace
multiline_comment|/* set up the cache */
id|cache
op_assign
id|presto_cache_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto_read_super: failure allocating cache.&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|cache-&gt;cache_type
op_assign
id|cache_type
suffix:semicolon
multiline_comment|/* link cache to channel */
id|minor
op_assign
id|presto_set_channel
c_func
(paren
id|cache
comma
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;Presto: type=%s, fset=%s, dev= %d, flags %x&bslash;n&quot;
comma
id|cache_type
comma
id|fileset
ques
c_cond
id|fileset
suffix:colon
l_string|&quot;NULL&quot;
comma
id|minor
comma
id|cache-&gt;cache_flags
)paren
suffix:semicolon
multiline_comment|/* get the filter for the cache */
id|fstype
op_assign
id|get_fs_type
c_func
(paren
id|cache_type
)paren
suffix:semicolon
id|cache-&gt;cache_filter
op_assign
id|filter_get_filter_fs
c_func
(paren
(paren
r_const
r_char
op_star
)paren
id|cache_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fstype
op_logical_or
op_logical_neg
id|cache-&gt;cache_filter
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Presto: unrecognized fs type or cache type&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|sb
op_assign
id|fstype
op_member_access_from_pointer
id|get_sb
c_func
(paren
id|fstype
comma
id|flags
comma
id|devname
comma
id|cache_data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
op_logical_or
id|IS_ERR
c_func
(paren
id|sb
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;InterMezzo: cache mount failure.&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* can we in fact mount the cache */
r_if
c_cond
(paren
id|sb-&gt;s_bdev
op_logical_and
(paren
id|strcmp
c_func
(paren
id|fstype-&gt;name
comma
l_string|&quot;vintermezzo&quot;
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;vintermezzo must not be used with a  block device&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* this might have been freed above */
r_if
c_cond
(paren
id|cache_data
)paren
(brace
id|PRESTO_FREE
c_func
(paren
id|cache_data
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|cache_data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|cache-&gt;cache_sb
op_assign
id|sb
suffix:semicolon
id|cache-&gt;cache_root
op_assign
id|dget
c_func
(paren
id|sb-&gt;s_root
)paren
suffix:semicolon
multiline_comment|/* we now know the dev of the cache: hash the cache */
id|presto_cache_add
c_func
(paren
id|cache
)paren
suffix:semicolon
id|err
op_assign
id|izo_prepare_fileset
c_func
(paren
id|sb-&gt;s_root
comma
id|fileset
)paren
suffix:semicolon
id|filter_setup_journal_ops
c_func
(paren
id|cache-&gt;cache_filter
comma
id|cache-&gt;cache_type
)paren
suffix:semicolon
multiline_comment|/* make sure we have our own super operations: sb&n;           still contains the cache operations */
id|filter_setup_super_ops
c_func
(paren
id|cache-&gt;cache_filter
comma
id|sb-&gt;s_op
comma
op_amp
id|presto_super_ops
)paren
suffix:semicolon
id|sb-&gt;s_op
op_assign
id|filter_c2usops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
multiline_comment|/* get izo directory operations: sb-&gt;s_root-&gt;d_inode exists now */
id|filter_setup_dir_ops
c_func
(paren
id|cache-&gt;cache_filter
comma
id|sb-&gt;s_root-&gt;d_inode
comma
op_amp
id|presto_dir_iops
comma
op_amp
id|presto_dir_fops
)paren
suffix:semicolon
id|filter_setup_dentry_ops
c_func
(paren
id|cache-&gt;cache_filter
comma
id|sb-&gt;s_root-&gt;d_op
comma
op_amp
id|presto_dentry_ops
)paren
suffix:semicolon
id|sb-&gt;s_root-&gt;d_inode-&gt;i_op
op_assign
id|filter_c2udiops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
id|sb-&gt;s_root-&gt;d_inode-&gt;i_fop
op_assign
id|filter_c2udfops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
id|sb-&gt;s_root-&gt;d_op
op_assign
id|filter_c2udops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|out_err
suffix:colon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;out_err called&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache
)paren
id|PRESTO_FREE
c_func
(paren
id|cache
comma
r_sizeof
(paren
r_struct
id|presto_cache
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache_data
)paren
id|PRESTO_FREE
c_func
(paren
id|cache_data
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fileset
)paren
id|PRESTO_FREE
c_func
(paren
id|fileset
comma
id|strlen
c_func
(paren
id|fileset
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel
)paren
id|PRESTO_FREE
c_func
(paren
id|channel
comma
id|strlen
c_func
(paren
id|channel
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache_type
)paren
id|PRESTO_FREE
c_func
(paren
id|cache_type
comma
id|strlen
c_func
(paren
id|cache_type
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_MALLOC
comma
l_string|&quot;mount error exit: kmem %ld, vmem %ld&bslash;n&quot;
comma
id|presto_kmemory
comma
id|presto_vmemory
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
macro_line|#ifdef PRESTO_DEVEL
r_static
id|DECLARE_FSTYPE
c_func
(paren
id|presto_fs_type
comma
l_string|&quot;izo&quot;
comma
id|presto_read_super
comma
id|FS_REQUIRES_DEV
)paren
suffix:semicolon
r_static
id|DECLARE_FSTYPE
c_func
(paren
id|vpresto_fs_type
comma
l_string|&quot;vintermezzo&quot;
comma
id|presto_read_super
comma
id|FS_LITTER
)paren
suffix:semicolon
macro_line|#else 
DECL|variable|vpresto_fs_type
r_static
r_struct
id|file_system_type
id|vpresto_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;vintermezzo&quot;
comma
dot
id|get_sb
op_assign
id|presto_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|variable|presto_fs_type
r_static
r_struct
id|file_system_type
id|presto_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;intermezzo&quot;
comma
dot
id|get_sb
op_assign
id|presto_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|init_intermezzo_fs
r_int
id|__init
id|init_intermezzo_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|status
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;InterMezzo Kernel/Intersync communications &quot;
id|INTERMEZZO_VERSION
l_string|&quot; info@clusterfs.com&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|presto_psdev_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;Problem (%d) in init_intermezzo_psdev&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|status
op_assign
id|init_intermezzo_sysctl
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto: failed in init_intermezzo_sysctl!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|presto_cache_init_hash
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|presto_init_ddata_cache
c_func
(paren
)paren
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|status
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|presto_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto: failed in register_filesystem!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|status
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|vpresto_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;vpresto: failed in register_filesystem!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|exit_intermezzo_fs
r_void
id|__exit
id|exit_intermezzo_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|unregister_filesystem
c_func
(paren
op_amp
id|presto_fs_type
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;presto: failed to unregister filesystem&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|unregister_filesystem
c_func
(paren
op_amp
id|vpresto_fs_type
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;vpresto: failed to unregister filesystem&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|presto_psdev_cleanup
c_func
(paren
)paren
suffix:semicolon
id|cleanup_intermezzo_sysctl
c_func
(paren
)paren
suffix:semicolon
id|presto_cleanup_ddata_cache
c_func
(paren
)paren
suffix:semicolon
id|CERROR
c_func
(paren
l_string|&quot;after cleanup: kmem %ld, vmem %ld&bslash;n&quot;
comma
id|presto_kmemory
comma
id|presto_vmemory
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Cluster Filesystems Inc. &lt;info@clusterfs.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;InterMezzo Kernel/Intersync communications &quot;
id|INTERMEZZO_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|init_intermezzo_fs
)paren
id|module_exit
c_func
(paren
id|exit_intermezzo_fs
)paren
eof
