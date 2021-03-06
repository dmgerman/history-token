multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001-2003 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@infradead.org&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: fs.c,v 1.51 2004/11/28 12:19:37 dedekind Exp $&n; *&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &quot;nodelist.h&quot;
r_static
r_int
id|jffs2_flash_setup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
suffix:semicolon
DECL|function|jffs2_do_setattr
r_static
r_int
id|jffs2_do_setattr
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_struct
id|jffs2_full_dnode
op_star
id|old_metadata
comma
op_star
id|new_metadata
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|jffs2_raw_inode
op_star
id|ri
suffix:semicolon
r_int
r_int
id|dev
suffix:semicolon
r_int
r_char
op_star
id|mdata
op_assign
l_int|NULL
suffix:semicolon
r_int
id|mdatalen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ivalid
suffix:semicolon
r_uint32
id|phys_ofs
comma
id|alloclen
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_setattr(): ino #%lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|iattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* Special cases - we don&squot;t want more than one data node&n;&t;   for these types on the medium at any time. So setattr&n;&t;   must read the original data associated with the node&n;&t;   (i.e. the device numbers or the target name) and write&n;&t;   it out again with the appropriate data attached */
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* For these, we don&squot;t actually need to read the old node */
id|dev
op_assign
id|old_encode_dev
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|mdata
op_assign
(paren
r_char
op_star
)paren
op_amp
id|dev
suffix:semicolon
id|mdatalen
op_assign
r_sizeof
(paren
id|dev
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_setattr(): Writing %d bytes of kdev_t&bslash;n&quot;
comma
id|mdatalen
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|mdatalen
op_assign
id|f-&gt;metadata-&gt;size
suffix:semicolon
id|mdata
op_assign
id|kmalloc
c_func
(paren
id|f-&gt;metadata-&gt;size
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mdata
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|jffs2_read_dnode
c_func
(paren
id|c
comma
id|f
comma
id|f-&gt;metadata
comma
id|mdata
comma
l_int|0
comma
id|mdatalen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree
c_func
(paren
id|mdata
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_setattr(): Writing %d bytes of symlink target&bslash;n&quot;
comma
id|mdatalen
)paren
)paren
suffix:semicolon
)brace
id|ri
op_assign
id|jffs2_alloc_raw_inode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ri
)paren
(brace
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|kfree
c_func
(paren
id|mdata
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ret
op_assign
id|jffs2_reserve_space
c_func
(paren
id|c
comma
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|mdatalen
comma
op_amp
id|phys_ofs
comma
op_amp
id|alloclen
comma
id|ALLOC_NORMAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|jffs2_free_raw_inode
c_func
(paren
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
)paren
id|kfree
c_func
(paren
id|mdata
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|ivalid
op_assign
id|iattr-&gt;ia_valid
suffix:semicolon
id|ri-&gt;magic
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_MAGIC_BITMASK
)paren
suffix:semicolon
id|ri-&gt;nodetype
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_NODETYPE_INODE
)paren
suffix:semicolon
id|ri-&gt;totlen
op_assign
id|cpu_to_je32
c_func
(paren
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|mdatalen
)paren
suffix:semicolon
id|ri-&gt;hdr_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|ri
comma
r_sizeof
(paren
r_struct
id|jffs2_unknown_node
)paren
op_minus
l_int|4
)paren
)paren
suffix:semicolon
id|ri-&gt;ino
op_assign
id|cpu_to_je32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ri-&gt;version
op_assign
id|cpu_to_je32
c_func
(paren
op_increment
id|f-&gt;highest_version
)paren
suffix:semicolon
id|ri-&gt;uid
op_assign
id|cpu_to_je16
c_func
(paren
(paren
id|ivalid
op_amp
id|ATTR_UID
)paren
ques
c_cond
id|iattr-&gt;ia_uid
suffix:colon
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|ri-&gt;gid
op_assign
id|cpu_to_je16
c_func
(paren
(paren
id|ivalid
op_amp
id|ATTR_GID
)paren
ques
c_cond
id|iattr-&gt;ia_gid
suffix:colon
id|inode-&gt;i_gid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ivalid
op_amp
id|ATTR_MODE
)paren
r_if
c_cond
(paren
id|iattr-&gt;ia_mode
op_amp
id|S_ISGID
op_logical_and
op_logical_neg
id|in_group_p
c_func
(paren
id|je16_to_cpu
c_func
(paren
id|ri-&gt;gid
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FSETID
)paren
)paren
id|ri-&gt;mode
op_assign
id|cpu_to_jemode
c_func
(paren
id|iattr-&gt;ia_mode
op_amp
op_complement
id|S_ISGID
)paren
suffix:semicolon
r_else
id|ri-&gt;mode
op_assign
id|cpu_to_jemode
c_func
(paren
id|iattr-&gt;ia_mode
)paren
suffix:semicolon
r_else
id|ri-&gt;mode
op_assign
id|cpu_to_jemode
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|ri-&gt;isize
op_assign
id|cpu_to_je32
c_func
(paren
(paren
id|ivalid
op_amp
id|ATTR_SIZE
)paren
ques
c_cond
id|iattr-&gt;ia_size
suffix:colon
id|inode-&gt;i_size
)paren
suffix:semicolon
id|ri-&gt;atime
op_assign
id|cpu_to_je32
c_func
(paren
id|I_SEC
c_func
(paren
(paren
id|ivalid
op_amp
id|ATTR_ATIME
)paren
ques
c_cond
id|iattr-&gt;ia_atime
suffix:colon
id|inode-&gt;i_atime
)paren
)paren
suffix:semicolon
id|ri-&gt;mtime
op_assign
id|cpu_to_je32
c_func
(paren
id|I_SEC
c_func
(paren
(paren
id|ivalid
op_amp
id|ATTR_MTIME
)paren
ques
c_cond
id|iattr-&gt;ia_mtime
suffix:colon
id|inode-&gt;i_mtime
)paren
)paren
suffix:semicolon
id|ri-&gt;ctime
op_assign
id|cpu_to_je32
c_func
(paren
id|I_SEC
c_func
(paren
(paren
id|ivalid
op_amp
id|ATTR_CTIME
)paren
ques
c_cond
id|iattr-&gt;ia_ctime
suffix:colon
id|inode-&gt;i_ctime
)paren
)paren
suffix:semicolon
id|ri-&gt;offset
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ri-&gt;csize
op_assign
id|ri-&gt;dsize
op_assign
id|cpu_to_je32
c_func
(paren
id|mdatalen
)paren
suffix:semicolon
id|ri-&gt;compr
op_assign
id|JFFS2_COMPR_NONE
suffix:semicolon
r_if
c_cond
(paren
id|ivalid
op_amp
id|ATTR_SIZE
op_logical_and
id|inode-&gt;i_size
OL
id|iattr-&gt;ia_size
)paren
(brace
multiline_comment|/* It&squot;s an extension. Make it a hole node */
id|ri-&gt;compr
op_assign
id|JFFS2_COMPR_ZERO
suffix:semicolon
id|ri-&gt;dsize
op_assign
id|cpu_to_je32
c_func
(paren
id|iattr-&gt;ia_size
op_minus
id|inode-&gt;i_size
)paren
suffix:semicolon
id|ri-&gt;offset
op_assign
id|cpu_to_je32
c_func
(paren
id|inode-&gt;i_size
)paren
suffix:semicolon
)brace
id|ri-&gt;node_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|ri
comma
r_sizeof
(paren
op_star
id|ri
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdatalen
)paren
id|ri-&gt;data_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|mdata
comma
id|mdatalen
)paren
)paren
suffix:semicolon
r_else
id|ri-&gt;data_crc
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|new_metadata
op_assign
id|jffs2_write_dnode
c_func
(paren
id|c
comma
id|f
comma
id|ri
comma
id|mdata
comma
id|mdatalen
comma
id|phys_ofs
comma
id|ALLOC_NORMAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|kfree
c_func
(paren
id|mdata
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|new_metadata
)paren
)paren
(brace
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_free_raw_inode
c_func
(paren
id|ri
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|new_metadata
)paren
suffix:semicolon
)brace
multiline_comment|/* It worked. Update the inode */
id|inode-&gt;i_atime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;atime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;ctime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;mtime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|jemode_to_cpu
c_func
(paren
id|ri-&gt;mode
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|je16_to_cpu
c_func
(paren
id|ri-&gt;uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|je16_to_cpu
c_func
(paren
id|ri-&gt;gid
)paren
suffix:semicolon
id|old_metadata
op_assign
id|f-&gt;metadata
suffix:semicolon
r_if
c_cond
(paren
id|ivalid
op_amp
id|ATTR_SIZE
op_logical_and
id|inode-&gt;i_size
OG
id|iattr-&gt;ia_size
)paren
id|jffs2_truncate_fraglist
(paren
id|c
comma
op_amp
id|f-&gt;fragtree
comma
id|iattr-&gt;ia_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ivalid
op_amp
id|ATTR_SIZE
op_logical_and
id|inode-&gt;i_size
OL
id|iattr-&gt;ia_size
)paren
(brace
id|jffs2_add_full_dnode_to_inode
c_func
(paren
id|c
comma
id|f
comma
id|new_metadata
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|iattr-&gt;ia_size
suffix:semicolon
id|f-&gt;metadata
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|f-&gt;metadata
op_assign
id|new_metadata
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_metadata
)paren
(brace
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|old_metadata-&gt;raw
)paren
suffix:semicolon
id|jffs2_free_full_dnode
c_func
(paren
id|old_metadata
)paren
suffix:semicolon
)brace
id|jffs2_free_raw_inode
c_func
(paren
id|ri
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
multiline_comment|/* We have to do the vmtruncate() without f-&gt;sem held, since&n;&t;   some pages may be locked and waiting for it in readpage(). &n;&t;   We are protected from a simultaneous write() extending i_size&n;&t;   back past iattr-&gt;ia_size, because do_truncate() holds the&n;&t;   generic inode semaphore. */
r_if
c_cond
(paren
id|ivalid
op_amp
id|ATTR_SIZE
op_logical_and
id|inode-&gt;i_size
OG
id|iattr-&gt;ia_size
)paren
id|vmtruncate
c_func
(paren
id|inode
comma
id|iattr-&gt;ia_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_setattr
r_int
id|jffs2_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_return
id|jffs2_do_setattr
c_func
(paren
id|dentry-&gt;d_inode
comma
id|iattr
)paren
suffix:semicolon
)brace
DECL|function|jffs2_statfs
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
id|kstatfs
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
id|spin_lock
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
id|c-&gt;resv_blocks_write
)paren
id|avail
op_sub_assign
id|c-&gt;sector_size
op_star
id|c-&gt;resv_blocks_write
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
id|D2
c_func
(paren
id|jffs2_dump_block_lists
c_func
(paren
id|c
)paren
)paren
suffix:semicolon
id|spin_unlock
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
DECL|function|jffs2_clear_inode
r_void
id|jffs2_clear_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
multiline_comment|/* We can forget about this inode for now - drop all &n;&t; *  the nodelists associated with it, etc.&n;&t; */
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_clear_inode(): ino #%lu mode %o&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_mode
)paren
)paren
suffix:semicolon
id|jffs2_do_clear_inode
c_func
(paren
id|c
comma
id|f
)paren
suffix:semicolon
)brace
DECL|function|jffs2_read_inode
r_void
id|jffs2_read_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|jffs2_inode_info
op_star
id|f
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_struct
id|jffs2_raw_inode
id|latest_node
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_inode(): inode-&gt;i_ino == %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|jffs2_init_inode_info
c_func
(paren
id|f
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_do_read_inode
c_func
(paren
id|c
comma
id|f
comma
id|inode-&gt;i_ino
comma
op_amp
id|latest_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_assign
id|jemode_to_cpu
c_func
(paren
id|latest_node.mode
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|je16_to_cpu
c_func
(paren
id|latest_node.uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|je16_to_cpu
c_func
(paren
id|latest_node.gid
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|je32_to_cpu
c_func
(paren
id|latest_node.isize
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|latest_node.atime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|latest_node.mtime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|ITIME
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|latest_node.ctime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|f-&gt;inocache-&gt;nlink
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
suffix:semicolon
r_switch
c_cond
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
(brace
id|jint16_t
id|rdev
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_symlink_inode_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
(brace
r_struct
id|jffs2_full_dirent
op_star
id|fd
suffix:semicolon
r_for
c_loop
(paren
id|fd
op_assign
id|f-&gt;dents
suffix:semicolon
id|fd
suffix:semicolon
id|fd
op_assign
id|fd-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|fd-&gt;type
op_eq
id|DT_DIR
op_logical_and
id|fd-&gt;ino
)paren
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
)brace
multiline_comment|/* and &squot;..&squot; */
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
multiline_comment|/* Root dir gets i_nlink 3 for some reason */
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
l_int|1
)paren
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|jffs2_dir_operations
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|S_IFREG
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|jffs2_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|jffs2_file_address_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;nrpages
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFBLK
suffix:colon
r_case
id|S_IFCHR
suffix:colon
multiline_comment|/* Read the device numbers from the media */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Reading device numbers from flash&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jffs2_read_dnode
c_func
(paren
id|c
comma
id|f
comma
id|f-&gt;metadata
comma
(paren
r_char
op_star
)paren
op_amp
id|rdev
comma
l_int|0
comma
r_sizeof
(paren
id|rdev
)paren
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* Eep */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Read device numbers for inode %lu failed&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|jffs2_do_clear_inode
c_func
(paren
id|c
comma
id|f
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
id|S_IFSOCK
suffix:colon
r_case
id|S_IFIFO
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|jffs2_file_inode_operations
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|old_decode_dev
c_func
(paren
(paren
id|je16_to_cpu
c_func
(paren
id|rdev
)paren
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jffs2_read_inode(): Bogus imode %o for ino %lu&bslash;n&quot;
comma
id|inode-&gt;i_mode
comma
(paren
r_int
r_int
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_inode() returning&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_dirty_inode
r_void
id|jffs2_dirty_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|iattr
id|iattr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY_DATASYNC
)paren
)paren
(brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_dirty_inode() not calling setattr() for ino #%lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_dirty_inode() calling setattr() for ino #%lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
id|iattr.ia_valid
op_assign
id|ATTR_MODE
op_or
id|ATTR_UID
op_or
id|ATTR_GID
op_or
id|ATTR_ATIME
op_or
id|ATTR_MTIME
op_or
id|ATTR_CTIME
suffix:semicolon
id|iattr.ia_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|iattr.ia_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|iattr.ia_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|iattr.ia_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|iattr.ia_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|iattr.ia_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|jffs2_do_setattr
c_func
(paren
id|inode
comma
op_amp
id|iattr
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
multiline_comment|/* We stop if it was running, then restart if it needs to.&n;&t;   This also catches the case where it was stopped and this&n;&t;   is just a remount to restart it.&n;&t;   Flush the writebuffer, if neccecary, else we loose it */
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
(brace
id|jffs2_stop_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
id|jffs2_flush_wbuf_pad
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
)brace
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
op_star
id|flags
op_or_assign
id|MS_NOATIME
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
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_write_super()&bslash;n&quot;
)paren
)paren
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
comma
l_int|0
)paren
suffix:semicolon
id|jffs2_flush_wbuf_gc
c_func
(paren
id|c
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* jffs2_new_inode: allocate a new inode and inocache, add it to the hash,&n;   fill in the raw_inode while you&squot;re at it. */
DECL|function|jffs2_new_inode
r_struct
id|inode
op_star
id|jffs2_new_inode
(paren
r_struct
id|inode
op_star
id|dir_i
comma
r_int
id|mode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir_i-&gt;i_sb
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_struct
id|jffs2_inode_info
op_star
id|f
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_new_inode(): dir_i %ld, mode 0x%x&bslash;n&quot;
comma
id|dir_i-&gt;i_ino
comma
id|mode
)paren
)paren
suffix:semicolon
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
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
op_logical_neg
id|inode
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|jffs2_init_inode_info
c_func
(paren
id|f
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ri
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ri
)paren
)paren
suffix:semicolon
multiline_comment|/* Set OS-specific defaults for new inodes */
id|ri-&gt;uid
op_assign
id|cpu_to_je16
c_func
(paren
id|current-&gt;fsuid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir_i-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|ri-&gt;gid
op_assign
id|cpu_to_je16
c_func
(paren
id|dir_i-&gt;i_gid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
(brace
id|ri-&gt;gid
op_assign
id|cpu_to_je16
c_func
(paren
id|current-&gt;fsgid
)paren
suffix:semicolon
)brace
id|ri-&gt;mode
op_assign
id|cpu_to_jemode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_do_new_inode
(paren
id|c
comma
id|f
comma
id|mode
comma
id|ri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|je32_to_cpu
c_func
(paren
id|ri-&gt;ino
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|jemode_to_cpu
c_func
(paren
id|ri-&gt;mode
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|je16_to_cpu
c_func
(paren
id|ri-&gt;gid
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|je16_to_cpu
c_func
(paren
id|ri-&gt;uid
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|ri-&gt;atime
op_assign
id|ri-&gt;mtime
op_assign
id|ri-&gt;ctime
op_assign
id|cpu_to_je32
c_func
(paren
id|I_SEC
c_func
(paren
id|inode-&gt;i_mtime
)paren
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|jffs2_do_fill_super
r_int
id|jffs2_do_fill_super
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
id|ret
suffix:semicolon
r_int
id|blocks
suffix:semicolon
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_JFFS2_FS_NAND
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;type
op_eq
id|MTD_NANDFLASH
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jffs2: Cannot operate on NAND flash unless jffs2 NAND support is compiled in.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
id|c-&gt;flash_size
op_assign
id|c-&gt;mtd-&gt;size
suffix:semicolon
multiline_comment|/* &n;&t; * Check, if we have to concatenate physical blocks to larger virtual blocks&n;&t; * to reduce the memorysize for c-&gt;blocks. (kmalloc allows max. 128K allocation)&n;&t; */
id|c-&gt;sector_size
op_assign
id|c-&gt;mtd-&gt;erasesize
suffix:semicolon
id|blocks
op_assign
id|c-&gt;flash_size
op_div
id|c-&gt;sector_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|c-&gt;mtd-&gt;flags
op_amp
id|MTD_NO_VIRTBLOCKS
)paren
)paren
(brace
r_while
c_loop
(paren
(paren
id|blocks
op_star
r_sizeof
(paren
r_struct
id|jffs2_eraseblock
)paren
)paren
OG
(paren
l_int|128
op_star
l_int|1024
)paren
)paren
(brace
id|blocks
op_rshift_assign
l_int|1
suffix:semicolon
id|c-&gt;sector_size
op_lshift_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Size alignment check&n;&t; */
r_if
c_cond
(paren
(paren
id|c-&gt;sector_size
op_star
id|blocks
)paren
op_ne
id|c-&gt;flash_size
)paren
(brace
id|c-&gt;flash_size
op_assign
id|c-&gt;sector_size
op_star
id|blocks
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;jffs2: Flash size not aligned to erasesize, reducing to %dKiB&bslash;n&quot;
comma
id|c-&gt;flash_size
op_div
l_int|1024
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;sector_size
op_ne
id|c-&gt;mtd-&gt;erasesize
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;jffs2: Erase block size too small (%dKiB). Using virtual blocks size (%dKiB) instead&bslash;n&quot;
comma
id|c-&gt;mtd-&gt;erasesize
op_div
l_int|1024
comma
id|c-&gt;sector_size
op_div
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;flash_size
OL
l_int|5
op_star
id|c-&gt;sector_size
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jffs2: Too few erase blocks (%d)&bslash;n&quot;
comma
id|c-&gt;flash_size
op_div
id|c-&gt;sector_size
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|c-&gt;cleanmarker_size
op_assign
r_sizeof
(paren
r_struct
id|jffs2_unknown_node
)paren
suffix:semicolon
multiline_comment|/* Joern -- stick alignment for weird 8-byte-page flash here */
multiline_comment|/* NAND (or other bizarre) flash... do setup accordingly */
id|ret
op_assign
id|jffs2_flash_setup
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|c-&gt;inocache_list
op_assign
id|kmalloc
c_func
(paren
id|INOCACHE_HASHSIZE
op_star
r_sizeof
(paren
r_struct
id|jffs2_inode_cache
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;inocache_list
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_wbuf
suffix:semicolon
)brace
id|memset
c_func
(paren
id|c-&gt;inocache_list
comma
l_int|0
comma
id|INOCACHE_HASHSIZE
op_star
r_sizeof
(paren
r_struct
id|jffs2_inode_cache
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|jffs2_do_mount_fs
c_func
(paren
id|c
)paren
)paren
)paren
r_goto
id|out_inohash
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_fill_super(): Getting root inode&bslash;n&quot;
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
l_string|&quot;jffs2_do_fill_super(): d_alloc_root()&bslash;n&quot;
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
l_int|0
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
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;flags
op_amp
id|MTD_NO_VIRTBLOCKS
)paren
id|vfree
c_func
(paren
id|c-&gt;blocks
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|c-&gt;blocks
)paren
suffix:semicolon
id|out_inohash
suffix:colon
id|kfree
c_func
(paren
id|c-&gt;inocache_list
)paren
suffix:semicolon
id|out_wbuf
suffix:colon
id|jffs2_flash_cleanup
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_gc_release_inode
r_void
id|jffs2_gc_release_inode
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
)paren
(brace
id|iput
c_func
(paren
id|OFNI_EDONI_2SFFJ
c_func
(paren
id|f
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_gc_fetch_inode
r_struct
id|jffs2_inode_info
op_star
id|jffs2_gc_fetch_inode
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_int
id|inum
comma
r_int
id|nlink
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|jffs2_inode_cache
op_star
id|ic
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nlink
)paren
(brace
multiline_comment|/* The inode has zero nlink but its nodes weren&squot;t yet marked&n;&t;&t;   obsolete. This has to be because we&squot;re still waiting for &n;&t;&t;   the final (close() and) iput() to happen.&n;&n;&t;&t;   There&squot;s a possibility that the final iput() could have &n;&t;&t;   happened while we were contemplating. In order to ensure&n;&t;&t;   that we don&squot;t cause a new read_inode() (which would fail)&n;&t;&t;   for the inode in question, we use ilookup() in this case&n;&t;&t;   instead of iget().&n;&n;&t;&t;   The nlink can&squot;t _become_ zero at this point because we&squot;re &n;&t;&t;   holding the alloc_sem, and jffs2_do_unlink() would also&n;&t;&t;   need that while decrementing nlink on any inode.&n;&t;&t;*/
id|inode
op_assign
id|ilookup
c_func
(paren
id|OFNI_BS_2SFFJ
c_func
(paren
id|c
)paren
comma
id|inum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ilookup() failed for ino #%u; inode is probably deleted.&bslash;n&quot;
comma
id|inum
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|c-&gt;inocache_lock
)paren
suffix:semicolon
id|ic
op_assign
id|jffs2_get_ino_cache
c_func
(paren
id|c
comma
id|inum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ic
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Inode cache for ino #%u is gone.&bslash;n&quot;
comma
id|inum
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|c-&gt;inocache_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ic-&gt;state
op_ne
id|INO_STATE_CHECKEDABSENT
)paren
(brace
multiline_comment|/* Wait for progress. Don&squot;t just loop */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Waiting for ino #%u in state %d&bslash;n&quot;
comma
id|ic-&gt;ino
comma
id|ic-&gt;state
)paren
)paren
suffix:semicolon
id|sleep_on_spinunlock
c_func
(paren
op_amp
id|c-&gt;inocache_wq
comma
op_amp
id|c-&gt;inocache_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock
c_func
(paren
op_amp
id|c-&gt;inocache_lock
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Inode has links to it still; they&squot;re not going away because&n;&t;&t;   jffs2_do_unlink() would need the alloc_sem and we have it.&n;&t;&t;   Just iget() it, and if read_inode() is necessary that&squot;s OK.&n;&t;&t;*/
id|inode
op_assign
id|iget
c_func
(paren
id|OFNI_BS_2SFFJ
c_func
(paren
id|c
)paren
comma
id|inum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Eep. read_inode() failed for ino #%u. nlink %d&bslash;n&quot;
comma
id|inum
comma
id|nlink
)paren
suffix:semicolon
multiline_comment|/* NB. This will happen again. We need to do something appropriate here. */
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
r_return
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|jffs2_gc_fetch_page
r_int
r_char
op_star
id|jffs2_gc_fetch_page
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_int
r_int
id|offset
comma
r_int
r_int
op_star
id|priv
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|OFNI_EDONI_2SFFJ
c_func
(paren
id|f
)paren
suffix:semicolon
r_struct
id|page
op_star
id|pg
suffix:semicolon
id|pg
op_assign
id|read_cache_page
c_func
(paren
id|inode-&gt;i_mapping
comma
id|offset
op_rshift
id|PAGE_CACHE_SHIFT
comma
(paren
r_void
op_star
)paren
id|jffs2_do_readpage_unlock
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|pg
)paren
)paren
r_return
(paren
r_void
op_star
)paren
id|pg
suffix:semicolon
op_star
id|priv
op_assign
(paren
r_int
r_int
)paren
id|pg
suffix:semicolon
r_return
id|kmap
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
DECL|function|jffs2_gc_release_page
r_void
id|jffs2_gc_release_page
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_int
r_char
op_star
id|ptr
comma
r_int
r_int
op_star
id|priv
)paren
(brace
r_struct
id|page
op_star
id|pg
op_assign
(paren
r_void
op_star
)paren
op_star
id|priv
suffix:semicolon
id|kunmap
c_func
(paren
id|pg
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
DECL|function|jffs2_flash_setup
r_static
r_int
id|jffs2_flash_setup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|jffs2_cleanmarker_oob
c_func
(paren
id|c
)paren
)paren
(brace
multiline_comment|/* NAND flash... do setup accordingly */
id|ret
op_assign
id|jffs2_nand_flash_setup
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* add setups for other bizarre flashes here... */
r_if
c_cond
(paren
id|jffs2_nor_ecc
c_func
(paren
id|c
)paren
)paren
(brace
id|ret
op_assign
id|jffs2_nor_ecc_flash_setup
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_flash_cleanup
r_void
id|jffs2_flash_cleanup
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|jffs2_cleanmarker_oob
c_func
(paren
id|c
)paren
)paren
(brace
id|jffs2_nand_flash_cleanup
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/* add cleanups for other bizarre flashes here... */
r_if
c_cond
(paren
id|jffs2_nor_ecc
c_func
(paren
id|c
)paren
)paren
(brace
id|jffs2_nor_ecc_flash_cleanup
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
eof
