multiline_comment|/*&n; *  linux/fs/adfs/inode.c&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;adfs.h&quot;
multiline_comment|/*&n; * Lookup/Create a block at offset &squot;block&squot; into &squot;inode&squot;.  We currently do&n; * not support creation of new blocks, so we return -EIO for this case.&n; */
r_int
DECL|function|adfs_get_block
id|adfs_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|block
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|create
)paren
(brace
r_if
c_cond
(paren
id|block
OL
l_int|0
)paren
r_goto
id|abort_negative
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
(brace
r_if
c_cond
(paren
id|block
op_ge
id|inode-&gt;i_blocks
)paren
r_goto
id|abort_toobig
suffix:semicolon
id|block
op_assign
id|__adfs_block_map
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
)paren
id|map_bh
c_func
(paren
id|bh
comma
id|inode-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* don&squot;t support allocation of blocks yet */
r_return
op_minus
id|EIO
suffix:semicolon
id|abort_negative
suffix:colon
id|adfs_error
c_func
(paren
id|inode-&gt;i_sb
comma
l_string|&quot;block %d &lt; 0&quot;
comma
id|block
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
id|abort_toobig
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adfs_writepage
r_static
r_int
id|adfs_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|adfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|adfs_readpage
r_static
r_int
id|adfs_readpage
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
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|adfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|adfs_prepare_write
r_static
r_int
id|adfs_prepare_write
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
comma
r_int
r_int
id|from
comma
r_int
r_int
id|to
)paren
(brace
r_return
id|cont_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|adfs_get_block
comma
op_amp
id|ADFS_I
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
op_member_access_from_pointer
id|mmu_private
)paren
suffix:semicolon
)brace
DECL|function|_adfs_bmap
r_static
id|sector_t
id|_adfs_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|sector_t
id|block
)paren
(brace
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|adfs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|adfs_aops
r_static
r_struct
id|address_space_operations
id|adfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|adfs_readpage
comma
dot
id|writepage
op_assign
id|adfs_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|adfs_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|_adfs_bmap
)brace
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|adfs_filetype
id|adfs_filetype
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
id|type
suffix:semicolon
r_if
c_cond
(paren
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|stamped
)paren
id|type
op_assign
(paren
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|loadaddr
op_rshift
l_int|8
)paren
op_amp
l_int|0xfff
suffix:semicolon
r_else
id|type
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
id|type
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert ADFS attributes and filetype to Linux permission.&n; */
r_static
id|umode_t
DECL|function|adfs_atts2mode
id|adfs_atts2mode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|filetype
comma
id|attr
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|attr
suffix:semicolon
id|umode_t
id|mode
comma
id|rmask
suffix:semicolon
r_struct
id|adfs_sb_info
op_star
id|asb
op_assign
id|ADFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|ADFS_NDA_DIRECTORY
)paren
(brace
id|mode
op_assign
id|S_IRUGO
op_amp
id|asb-&gt;s_owner_mask
suffix:semicolon
r_return
id|S_IFDIR
op_or
id|S_IXUGO
op_or
id|mode
suffix:semicolon
)brace
id|filetype
op_assign
id|adfs_filetype
c_func
(paren
id|inode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|filetype
)paren
(brace
r_case
l_int|0xfc0
suffix:colon
multiline_comment|/* LinkFS */
r_return
id|S_IFLNK
op_or
id|S_IRWXUGO
suffix:semicolon
r_case
l_int|0xfe6
suffix:colon
multiline_comment|/* UnixExec */
id|rmask
op_assign
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|rmask
op_assign
id|S_IRUGO
suffix:semicolon
)brace
id|mode
op_assign
id|S_IFREG
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|ADFS_NDA_OWNER_READ
)paren
id|mode
op_or_assign
id|rmask
op_amp
id|asb-&gt;s_owner_mask
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|ADFS_NDA_OWNER_WRITE
)paren
id|mode
op_or_assign
id|S_IWUGO
op_amp
id|asb-&gt;s_owner_mask
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|ADFS_NDA_PUBLIC_READ
)paren
id|mode
op_or_assign
id|rmask
op_amp
id|asb-&gt;s_other_mask
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|ADFS_NDA_PUBLIC_WRITE
)paren
id|mode
op_or_assign
id|S_IWUGO
op_amp
id|asb-&gt;s_other_mask
suffix:semicolon
r_return
id|mode
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert Linux permission to ADFS attribute.  We try to do the reverse&n; * of atts2mode, but there is not a 1:1 translation.&n; */
r_static
r_int
DECL|function|adfs_mode2atts
id|adfs_mode2atts
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|umode_t
id|mode
suffix:semicolon
r_int
id|attr
suffix:semicolon
r_struct
id|adfs_sb_info
op_star
id|asb
op_assign
id|ADFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* FIXME: should we be able to alter a link? */
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|attr
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|attr
op_assign
id|ADFS_NDA_DIRECTORY
suffix:semicolon
r_else
id|attr
op_assign
l_int|0
suffix:semicolon
id|mode
op_assign
id|inode-&gt;i_mode
op_amp
id|asb-&gt;s_owner_mask
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IRUGO
)paren
id|attr
op_or_assign
id|ADFS_NDA_OWNER_READ
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IWUGO
)paren
id|attr
op_or_assign
id|ADFS_NDA_OWNER_WRITE
suffix:semicolon
id|mode
op_assign
id|inode-&gt;i_mode
op_amp
id|asb-&gt;s_other_mask
suffix:semicolon
id|mode
op_and_assign
op_complement
id|asb-&gt;s_owner_mask
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IRUGO
)paren
id|attr
op_or_assign
id|ADFS_NDA_PUBLIC_READ
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IWUGO
)paren
id|attr
op_or_assign
id|ADFS_NDA_PUBLIC_WRITE
suffix:semicolon
r_return
id|attr
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert an ADFS time to Unix time.  ADFS has a 40-bit centi-second time&n; * referenced to 1 Jan 1900 (til 2248)&n; */
r_static
r_int
r_int
DECL|function|adfs_adfs2unix_time
id|adfs_adfs2unix_time
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
id|high
comma
id|low
suffix:semicolon
r_if
c_cond
(paren
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|stamped
op_eq
l_int|0
)paren
r_return
id|get_seconds
c_func
(paren
)paren
suffix:semicolon
id|high
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|loadaddr
op_lshift
l_int|24
suffix:semicolon
id|low
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|execaddr
suffix:semicolon
id|high
op_or_assign
id|low
op_rshift
l_int|8
suffix:semicolon
id|low
op_and_assign
l_int|255
suffix:semicolon
multiline_comment|/* Files dated pre  01 Jan 1970 00:00:00. */
r_if
c_cond
(paren
id|high
OL
l_int|0x336e996a
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Files dated post 18 Jan 2038 03:14:05. */
r_if
c_cond
(paren
id|high
op_ge
l_int|0x656e9969
)paren
r_return
l_int|0x7ffffffd
suffix:semicolon
multiline_comment|/* discard 2208988800 (0x336e996a00) seconds of time */
id|high
op_sub_assign
l_int|0x336e996a
suffix:semicolon
multiline_comment|/* convert 40-bit centi-seconds to 32-bit seconds */
r_return
(paren
(paren
(paren
id|high
op_mod
l_int|100
)paren
op_lshift
l_int|8
)paren
op_plus
id|low
)paren
op_div
l_int|100
op_plus
(paren
id|high
op_div
l_int|100
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert an Unix time to ADFS time.  We only do this if the entry has a&n; * time/date stamp already.&n; */
r_static
r_void
DECL|function|adfs_unix2adfs_time
id|adfs_unix2adfs_time
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|secs
)paren
(brace
r_int
r_int
id|high
comma
id|low
suffix:semicolon
r_if
c_cond
(paren
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|stamped
)paren
(brace
multiline_comment|/* convert 32-bit seconds to 40-bit centi-seconds */
id|low
op_assign
(paren
id|secs
op_amp
l_int|255
)paren
op_star
l_int|100
suffix:semicolon
id|high
op_assign
(paren
id|secs
op_div
l_int|256
)paren
op_star
l_int|100
op_plus
(paren
id|low
op_rshift
l_int|8
)paren
op_plus
l_int|0x336e996a
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|loadaddr
op_assign
(paren
id|high
op_rshift
l_int|24
)paren
op_or
(paren
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|loadaddr
op_amp
op_complement
l_int|0xff
)paren
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|execaddr
op_assign
(paren
id|low
op_amp
l_int|255
)paren
op_or
(paren
id|high
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Fill in the inode information from the object information.&n; *&n; * Note that this is an inode-less filesystem, so we can&squot;t use the inode&n; * number to reference the metadata on the media.  Instead, we use the&n; * inode number to hold the object ID, which in turn will tell us where&n; * the data is held.  We also save the parent object ID, and with these&n; * two, we can locate the metadata.&n; *&n; * This does mean that we rely on an objects parent remaining the same at&n; * all times - we cannot cope with a cross-directory rename (yet).&n; */
r_struct
id|inode
op_star
DECL|function|adfs_iget
id|adfs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|object_info
op_star
id|obj
)paren
(brace
r_struct
id|inode
op_star
id|inode
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
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|ADFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|ADFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_gid
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|obj-&gt;file_id
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|obj-&gt;size
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|2
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
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
multiline_comment|/*&n;&t; * we need to save the parent directory ID so that&n;&t; * write_inode can update the directory information&n;&t; * for this file.  This will need special handling&n;&t; * for cross-directory renames.&n;&t; */
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|parent_id
op_assign
id|obj-&gt;parent_id
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|loadaddr
op_assign
id|obj-&gt;loadaddr
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|execaddr
op_assign
id|obj-&gt;execaddr
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|attr
op_assign
id|obj-&gt;attr
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|stamped
op_assign
(paren
(paren
id|obj-&gt;loadaddr
op_amp
l_int|0xfff00000
)paren
op_eq
l_int|0xfff00000
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|adfs_atts2mode
c_func
(paren
id|sb
comma
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_mtime.tv_sec
op_assign
id|inode-&gt;i_atime.tv_sec
op_assign
id|inode-&gt;i_ctime.tv_sec
op_assign
id|adfs_adfs2unix_time
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_mtime.tv_nsec
op_assign
id|inode-&gt;i_ctime.tv_nsec
op_assign
id|inode-&gt;i_atime.tv_nsec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|adfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|adfs_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|adfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|adfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|adfs_aops
suffix:semicolon
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * Validate and convert a changed access mode/time to their ADFS equivalents.&n; * adfs_write_inode will actually write the information back to the directory&n; * later.&n; */
r_int
DECL|function|adfs_notify_change
id|adfs_notify_change
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
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
r_int
id|ia_valid
op_assign
id|attr-&gt;ia_valid
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we can&squot;t change the UID or GID of any file -&n;&t; * we have a global UID/GID in the superblock&n;&t; */
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
id|ATTR_UID
op_logical_and
id|attr-&gt;ia_uid
op_ne
id|ADFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_uid
)paren
op_logical_or
(paren
id|ia_valid
op_amp
id|ATTR_GID
op_logical_and
id|attr-&gt;ia_gid
op_ne
id|ADFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_gid
)paren
)paren
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_SIZE
)paren
id|error
op_assign
id|vmtruncate
c_func
(paren
id|inode
comma
id|attr-&gt;ia_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MTIME
)paren
(brace
id|inode-&gt;i_mtime
op_assign
id|attr-&gt;ia_mtime
suffix:semicolon
id|adfs_unix2adfs_time
c_func
(paren
id|inode
comma
id|attr-&gt;ia_mtime.tv_sec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * FIXME: should we make these == to i_mtime since we don&squot;t&n;&t; * have the ability to represent them in our filesystem?&n;&t; */
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_ATIME
)paren
id|inode-&gt;i_atime
op_assign
id|attr-&gt;ia_atime
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_CTIME
)paren
id|inode-&gt;i_ctime
op_assign
id|attr-&gt;ia_ctime
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|attr
op_assign
id|adfs_mode2atts
c_func
(paren
id|sb
comma
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|adfs_atts2mode
c_func
(paren
id|sb
comma
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * FIXME: should we be marking this inode dirty even if&n;&t; * we don&squot;t have any metadata to write back?&n;&t; */
r_if
c_cond
(paren
id|ia_valid
op_amp
(paren
id|ATTR_SIZE
op_or
id|ATTR_MTIME
op_or
id|ATTR_MODE
)paren
)paren
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * write an existing inode back to the directory, and therefore the disk.&n; * The adfs-specific inode data has already been updated by&n; * adfs_notify_change()&n; */
DECL|function|adfs_write_inode
r_void
id|adfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|unused
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|object_info
id|obj
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|obj.file_id
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|obj.name_len
op_assign
l_int|0
suffix:semicolon
id|obj.parent_id
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|parent_id
suffix:semicolon
id|obj.loadaddr
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|loadaddr
suffix:semicolon
id|obj.execaddr
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|execaddr
suffix:semicolon
id|obj.attr
op_assign
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|attr
suffix:semicolon
id|obj.size
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|adfs_dir_update
c_func
(paren
id|sb
comma
op_amp
id|obj
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
