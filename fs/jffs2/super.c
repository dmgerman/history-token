multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * The original JFFS, from which the design for JFFS2 was derived,&n; * was designed and implemented by Axis Communications AB.&n; *&n; * The contents of this file are subject to the Red Hat eCos Public&n; * License Version 1.1 (the &quot;Licence&quot;); you may not use this file&n; * except in compliance with the Licence.  You may obtain a copy of&n; * the Licence at http://www.redhat.com/&n; *&n; * Software distributed under the Licence is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.&n; * See the Licence for the specific language governing rights and&n; * limitations under the Licence.&n; *&n; * The Original Code is JFFS2 - Journalling Flash File System, version 2&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the RHEPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the RHEPL or the GPL.&n; *&n; * $Id: super.c,v 1.48 2001/10/02 09:16:23 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jffs2.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;nodelist.h&quot;
macro_line|#ifndef MTD_BLOCK_MAJOR
DECL|macro|MTD_BLOCK_MAJOR
mdefine_line|#define MTD_BLOCK_MAJOR 31
macro_line|#endif
r_extern
r_void
id|jffs2_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|jffs2_put_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_void
id|jffs2_write_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|jffs2_statfs
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
r_int
id|jffs2_remount_fs
(paren
r_struct
id|super_block
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|jffs2_clear_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|variable|jffs2_super_operations
r_static
r_struct
id|super_operations
id|jffs2_super_operations
op_assign
(brace
id|read_inode
suffix:colon
id|jffs2_read_inode
comma
singleline_comment|//&t;delete_inode:&t;jffs2_delete_inode,
id|put_super
suffix:colon
id|jffs2_put_super
comma
id|write_super
suffix:colon
id|jffs2_write_super
comma
id|statfs
suffix:colon
id|jffs2_statfs
comma
id|remount_fs
suffix:colon
id|jffs2_remount_fs
comma
id|clear_inode
suffix:colon
id|jffs2_clear_inode
)brace
suffix:semicolon
DECL|function|jffs2_statfs
r_static
r_int
id|jffs2_statfs
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
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|avail
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|JFFS2_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
l_int|1
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|c-&gt;flash_size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|buf-&gt;f_files
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|JFFS2_MAX_NAME_LEN
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|avail
op_assign
id|c-&gt;dirty_size
op_plus
id|c-&gt;free_size
suffix:semicolon
r_if
c_cond
(paren
id|avail
OG
id|c-&gt;sector_size
op_star
id|JFFS2_RESERVED_BLOCKS_WRITE
)paren
id|avail
op_sub_assign
id|c-&gt;sector_size
op_star
id|JFFS2_RESERVED_BLOCKS_WRITE
suffix:semicolon
r_else
id|avail
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
op_assign
id|avail
op_rshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#if CONFIG_JFFS2_FS_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;STATFS:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;flash_size: %08x&bslash;n&quot;
comma
id|c-&gt;flash_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;used_size: %08x&bslash;n&quot;
comma
id|c-&gt;used_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dirty_size: %08x&bslash;n&quot;
comma
id|c-&gt;dirty_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;free_size: %08x&bslash;n&quot;
comma
id|c-&gt;free_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;erasing_size: %08x&bslash;n&quot;
comma
id|c-&gt;erasing_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bad_size: %08x&bslash;n&quot;
comma
id|c-&gt;bad_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sector_size: %08x&bslash;n&quot;
comma
id|c-&gt;sector_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;nextblock
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;nextblock: 0x%08x&bslash;n&quot;
comma
id|c-&gt;nextblock-&gt;offset
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;nextblock: NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;gcblock
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;gcblock: 0x%08x&bslash;n&quot;
comma
id|c-&gt;gcblock-&gt;offset
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;gcblock: NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;clean_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;clean_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;clean_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;clean_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;dirty_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dirty_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;dirty_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dirty_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;erasing_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;erasing_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;erasing_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;erasing_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;erase_pending_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;erase_pending_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;erase_pending_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;erase_pending_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;free_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;free_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;free_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;free_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;bad_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bad_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;bad_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bad_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|c-&gt;bad_used_list
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bad_used_list: empty&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|c-&gt;bad_used_list
)paren
(brace
r_struct
id|jffs2_eraseblock
op_star
id|jeb
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|jffs2_eraseblock
comma
id|list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bad_used_list: %08x&bslash;n&quot;
comma
id|jeb-&gt;offset
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_JFFS2_FS_DEBUG */
id|spin_unlock_bh
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_read_super
r_static
r_struct
id|super_block
op_star
id|jffs2_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
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
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_struct
id|inode
op_star
id|root_i
suffix:semicolon
r_int
id|i
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2: read_super for device %s&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|major
c_func
(paren
id|sb-&gt;s_dev
)paren
op_ne
id|MTD_BLOCK_MAJOR
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2: attempt to mount non-MTD device %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|c
)paren
)paren
suffix:semicolon
id|c-&gt;mtd
op_assign
id|get_mtd_device
c_func
(paren
l_int|NULL
comma
id|MINOR
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;mtd
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2: MTD device #%u doesn&squot;t appear to exist&bslash;n&quot;
comma
id|MINOR
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|c-&gt;sector_size
op_assign
id|c-&gt;mtd-&gt;erasesize
suffix:semicolon
id|c-&gt;free_size
op_assign
id|c-&gt;flash_size
op_assign
id|c-&gt;mtd-&gt;size
suffix:semicolon
id|c-&gt;nr_blocks
op_assign
id|c-&gt;mtd-&gt;size
op_div
id|c-&gt;mtd-&gt;erasesize
suffix:semicolon
id|c-&gt;blocks
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|jffs2_eraseblock
)paren
op_star
id|c-&gt;nr_blocks
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;blocks
)paren
r_goto
id|out_mtd
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
id|c-&gt;nr_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|list
)paren
suffix:semicolon
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|offset
op_assign
id|i
op_star
id|c-&gt;sector_size
suffix:semicolon
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|free_size
op_assign
id|c-&gt;sector_size
suffix:semicolon
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|dirty_size
op_assign
l_int|0
suffix:semicolon
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|used_size
op_assign
l_int|0
suffix:semicolon
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|first_node
op_assign
l_int|NULL
suffix:semicolon
id|c-&gt;blocks
(braket
id|i
)braket
dot
id|last_node
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|c-&gt;nodelist_lock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|c-&gt;erase_wait
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|c-&gt;erase_completion_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|c-&gt;inocache_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;clean_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;dirty_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;erasing_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;erase_pending_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;erase_complete_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;free_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;bad_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|c-&gt;bad_used_list
)paren
suffix:semicolon
id|c-&gt;highest_ino
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|jffs2_build_filesystem
c_func
(paren
id|c
)paren
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;build_fs failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out_nodes
suffix:semicolon
)brace
id|sb-&gt;s_op
op_assign
op_amp
id|jffs2_super_operations
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_super(): Getting root inode&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|root_i
op_assign
id|iget
c_func
(paren
id|sb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|root_i
)paren
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;get root inode failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out_nodes
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_super(): d_alloc_root()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
r_goto
id|out_root_i
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20403
id|sb-&gt;s_maxbytes
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
macro_line|#endif
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|JFFS2_SUPER_MAGIC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
id|jffs2_start_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|out_root_i
suffix:colon
id|iput
c_func
(paren
id|root_i
)paren
suffix:semicolon
id|out_nodes
suffix:colon
id|jffs2_free_ino_caches
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_free_raw_node_refs
c_func
(paren
id|c
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c-&gt;blocks
)paren
suffix:semicolon
id|out_mtd
suffix:colon
id|put_mtd_device
c_func
(paren
id|c-&gt;mtd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|jffs2_put_super
r_void
id|jffs2_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2: jffs2_put_super()&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
id|jffs2_stop_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_free_ino_caches
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_free_raw_node_refs
c_func
(paren
id|c
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c-&gt;blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;sync
)paren
id|c-&gt;mtd
op_member_access_from_pointer
id|sync
c_func
(paren
id|c-&gt;mtd
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|c-&gt;mtd
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_put_super returning&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_remount_fs
r_int
id|jffs2_remount_fs
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;flags
op_amp
id|JFFS2_SB_FLAG_RO
op_logical_and
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/* We stop if it was running, then restart if it needs to.&n;&t;   This also catches the case where it was stopped and this&n;&t;   is just a remount to restart it */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
id|jffs2_stop_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
id|jffs2_start_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_assign
(paren
id|sb-&gt;s_flags
op_amp
op_complement
id|MS_RDONLY
)paren
op_or
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_write_super
r_void
id|jffs2_write_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
suffix:semicolon
id|jffs2_garbage_collect_trigger
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_erase_pending_blocks
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_mark_erased_blocks
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|jffs2_fs_type
comma
l_string|&quot;jffs2&quot;
comma
id|jffs2_read_super
)paren
suffix:semicolon
DECL|function|init_jffs2_fs
r_static
r_int
id|__init
id|init_jffs2_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;JFFS2 version 2.1. (C) 2001 Red Hat, Inc., designed by Axis Communications AB.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef JFFS2_OUT_OF_KERNEL
multiline_comment|/* sanity checks. Could we do these at compile time? */
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|jffs2_sb_info
)paren
OG
r_sizeof
(paren
(paren
(paren
r_struct
id|super_block
op_star
)paren
l_int|NULL
)paren
op_member_access_from_pointer
id|u
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: struct jffs2_sb_info (%d bytes) doesn&squot;t fit in the super_block union (%d bytes)&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|jffs2_sb_info
)paren
comma
r_sizeof
(paren
(paren
(paren
r_struct
id|super_block
op_star
)paren
l_int|NULL
)paren
op_member_access_from_pointer
id|u
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|jffs2_inode_info
)paren
OG
r_sizeof
(paren
(paren
(paren
r_struct
id|inode
op_star
)paren
l_int|NULL
)paren
op_member_access_from_pointer
id|u
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: struct jffs2_inode_info (%d bytes) doesn&squot;t fit in the inode union (%d bytes)&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|jffs2_inode_info
)paren
comma
r_sizeof
(paren
(paren
(paren
r_struct
id|inode
op_star
)paren
l_int|NULL
)paren
op_member_access_from_pointer
id|u
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#endif
id|ret
op_assign
id|jffs2_create_slab_caches
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: Failed to initialise slab caches&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|jffs2_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: Failed to register filesystem&bslash;n&quot;
)paren
suffix:semicolon
id|jffs2_destroy_slab_caches
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|exit_jffs2_fs
r_static
r_void
id|__exit
id|exit_jffs2_fs
c_func
(paren
r_void
)paren
(brace
id|jffs2_destroy_slab_caches
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|jffs2_fs_type
)paren
suffix:semicolon
)brace
DECL|variable|init_jffs2_fs
id|module_init
c_func
(paren
id|init_jffs2_fs
)paren
suffix:semicolon
DECL|variable|exit_jffs2_fs
id|module_exit
c_func
(paren
id|exit_jffs2_fs
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;The Journalling Flash File System, v2&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
singleline_comment|// Actually dual-licensed, but it doesn&squot;t matter for 
singleline_comment|// the sake of this tag. It&squot;s Free Software.
eof
