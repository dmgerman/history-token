multiline_comment|/*&n; *&n; *&n; *  Copyright (C) 2000 Stelias Computing, Inc.&n; *  Copyright (C) 2000 Red Hat, Inc.&n; *&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_upcall.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
multiline_comment|/*&n;   This file contains the routines associated with managing a&n;   cache of files for InterMezzo.  These caches have two reqs:&n;   - need to be found fast so they are hashed by the device, &n;     with an attempt to have collision chains of length 1.&n;   The methods for the cache are set up in methods.&n;*/
multiline_comment|/* the intent of this hash is to have collision chains of length 1 */
DECL|macro|CACHES_BITS
mdefine_line|#define CACHES_BITS 8
DECL|macro|CACHES_SIZE
mdefine_line|#define CACHES_SIZE (1 &lt;&lt; CACHES_BITS)
DECL|macro|CACHES_MASK
mdefine_line|#define CACHES_MASK CACHES_SIZE - 1
DECL|variable|presto_caches
r_static
r_struct
id|list_head
id|presto_caches
(braket
id|CACHES_SIZE
)braket
suffix:semicolon
DECL|function|presto_cache_hash
r_static
r_inline
r_int
id|presto_cache_hash
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
(paren
id|CACHES_MASK
)paren
op_amp
(paren
(paren
r_int
r_int
)paren
id|sb
op_div
id|L1_CACHE_BYTES
)paren
suffix:semicolon
)brace
DECL|function|presto_cache_add
r_inline
r_void
id|presto_cache_add
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
id|list_add
c_func
(paren
op_amp
id|cache-&gt;cache_chain
comma
op_amp
id|presto_caches
(braket
id|presto_cache_hash
c_func
(paren
id|sb
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|function|presto_init_cache_hash
r_inline
r_void
id|presto_init_cache_hash
c_func
(paren
r_void
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
id|CACHES_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|presto_caches
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* map a device to a cache */
DECL|function|presto_find_cache
r_struct
id|presto_cache
op_star
id|presto_find_cache
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|tmp
suffix:semicolon
id|lh
op_assign
id|tmp
op_assign
op_amp
(paren
id|presto_caches
(braket
id|presto_cache_hash
c_func
(paren
id|sb
)paren
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|lh-&gt;next
)paren
op_ne
id|lh
)paren
(brace
id|cache
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|presto_cache
comma
id|cache_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;cache_sb
op_eq
id|sb
)paren
r_return
id|cache
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* map an inode to a cache */
DECL|function|presto_get_cache
r_struct
id|presto_cache
op_star
id|presto_get_cache
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
multiline_comment|/* find the correct presto_cache here, based on the device */
id|cache
op_assign
id|presto_find_cache
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: no presto cache for dev %s, ino %ld&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|cache
suffix:semicolon
)brace
multiline_comment|/* list cache mount points for ioctl&squot;s or /proc/fs/intermezzo/mounts */
DECL|function|presto_sprint_mounts
r_int
id|presto_sprint_mounts
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|buflen
comma
r_int
id|minor
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
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
id|CACHES_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|head
op_assign
id|tmp
op_assign
op_amp
id|presto_caches
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|tmp-&gt;next
)paren
op_ne
id|head
)paren
(brace
id|cache
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|presto_cache
comma
id|cache_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache-&gt;cache_root_fileset
op_logical_or
op_logical_neg
id|cache-&gt;cache_mtpt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|minor
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
id|cache-&gt;cache_psdev-&gt;uc_minor
op_ne
id|minor
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cache-&gt;cache_root_fileset
)paren
op_plus
id|strlen
c_func
(paren
id|cache-&gt;cache_mtpt
)paren
op_plus
id|strlen
c_func
(paren
id|cache-&gt;cache_psdev-&gt;uc_devname
)paren
op_plus
l_int|4
OG
id|buflen
op_minus
id|len
)paren
r_break
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s %s %s&bslash;n&quot;
comma
id|cache-&gt;cache_root_fileset
comma
id|cache-&gt;cache_mtpt
comma
id|cache-&gt;cache_psdev-&gt;uc_devname
)paren
suffix:semicolon
)brace
)brace
id|buf
(braket
id|buflen
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KREINT
multiline_comment|/* get mount point by volname&n;       Arthur Ma, 2000.12.25&n; */
DECL|function|presto_get_mount
r_int
id|presto_get_mount
(paren
r_char
op_star
id|buf
comma
r_int
id|buflen
comma
r_char
op_star
id|volname
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|tmp
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
id|path
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
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
id|CACHES_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|head
op_assign
id|tmp
op_assign
op_amp
id|presto_caches
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|tmp-&gt;next
)paren
op_ne
id|head
)paren
(brace
id|cache
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|presto_cache
comma
id|cache_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache-&gt;cache_root_fileset
op_logical_or
op_logical_neg
id|cache-&gt;cache_mtpt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cache-&gt;cache_root_fileset
comma
id|volname
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cache
op_ne
l_int|NULL
)paren
id|path
op_assign
id|cache-&gt;cache_mtpt
suffix:semicolon
id|strncpy
(paren
id|buf
comma
id|path
comma
id|buflen
)paren
suffix:semicolon
r_return
id|strlen
(paren
id|buf
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* another debugging routine: check fs is InterMezzo fs */
DECL|function|presto_ispresto
r_int
id|presto_ispresto
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|0
suffix:semicolon
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|inode-&gt;i_sb
op_eq
id|cache-&gt;cache_sb
)paren
suffix:semicolon
)brace
multiline_comment|/* setup a cache structure when we need one */
DECL|function|presto_init_cache
r_struct
id|presto_cache
op_star
id|presto_init_cache
c_func
(paren
r_void
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
multiline_comment|/* make a presto_cache structure for the hash */
id|PRESTO_ALLOC
c_func
(paren
id|cache
comma
r_struct
id|presto_cache
op_star
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
id|cache
)paren
(brace
id|memset
c_func
(paren
id|cache
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|presto_cache
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cache-&gt;cache_chain
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cache-&gt;cache_fset_list
)paren
suffix:semicolon
)brace
id|cache-&gt;cache_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|cache-&gt;cache_reserved
op_assign
l_int|0
suffix:semicolon
r_return
id|cache
suffix:semicolon
)brace
multiline_comment|/* free a cache structure and all of the memory it is pointing to */
DECL|function|presto_free_cache
r_inline
r_void
id|presto_free_cache
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
r_return
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|cache-&gt;cache_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;cache_mtpt
)paren
id|PRESTO_FREE
c_func
(paren
id|cache-&gt;cache_mtpt
comma
id|strlen
c_func
(paren
id|cache-&gt;cache_mtpt
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;cache_type
)paren
id|PRESTO_FREE
c_func
(paren
id|cache-&gt;cache_type
comma
id|strlen
c_func
(paren
id|cache-&gt;cache_type
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache-&gt;cache_root_fileset
)paren
id|PRESTO_FREE
c_func
(paren
id|cache-&gt;cache_root_fileset
comma
id|strlen
c_func
(paren
id|cache-&gt;cache_root_fileset
)paren
op_plus
l_int|1
)paren
suffix:semicolon
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
)brace
DECL|function|presto_reserve_space
r_int
id|presto_reserve_space
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
id|loff_t
id|req
)paren
(brace
r_struct
id|filter_fs
op_star
id|filter
suffix:semicolon
id|loff_t
id|avail
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|cache-&gt;cache_sb
suffix:semicolon
id|filter
op_assign
id|cache-&gt;cache_filter
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filter
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|filter-&gt;o_trops
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|filter-&gt;o_trops-&gt;tr_avail
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|avail
op_assign
id|filter-&gt;o_trops
op_member_access_from_pointer
id|tr_avail
c_func
(paren
id|cache
comma
id|sb
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ESC::%ld +++&gt; %ld &bslash;n&quot;
comma
(paren
r_int
)paren
id|cache-&gt;cache_reserved
comma
(paren
r_int
)paren
(paren
id|cache-&gt;cache_reserved
op_plus
id|req
)paren
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ESC::Avail::%ld &bslash;n&quot;
comma
(paren
r_int
)paren
id|avail
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_plus
id|cache-&gt;cache_reserved
OG
id|avail
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|cache-&gt;cache_reserved
op_add_assign
id|req
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|presto_release_space
r_void
id|presto_release_space
c_func
(paren
r_struct
id|presto_cache
op_star
id|cache
comma
id|loff_t
id|req
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;ESC::%ld ---&gt; %ld &bslash;n&quot;
comma
(paren
r_int
)paren
id|cache-&gt;cache_reserved
comma
(paren
r_int
)paren
(paren
id|cache-&gt;cache_reserved
op_minus
id|req
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
id|cache-&gt;cache_reserved
op_sub_assign
id|req
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cache-&gt;cache_lock
)paren
suffix:semicolon
)brace
eof
