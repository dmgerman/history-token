multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * The original JFFS, from which the design for JFFS2 was derived,&n; * was designed and implemented by Axis Communications AB.&n; *&n; * The contents of this file are subject to the Red Hat eCos Public&n; * License Version 1.1 (the &quot;Licence&quot;); you may not use this file&n; * except in compliance with the Licence.  You may obtain a copy of&n; * the Licence at http://www.redhat.com/&n; *&n; * Software distributed under the Licence is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.&n; * See the Licence for the specific language governing rights and&n; * limitations under the Licence.&n; *&n; * The Original Code is JFFS2 - Journalling Flash File System, version 2&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the RHEPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the RHEPL or the GPL.&n; *&n; * $Id: write.c,v 1.30 2001/12/30 16:01:11 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/jffs2.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &quot;nodelist.h&quot;
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
id|jffs2_inode_cache
op_star
id|ic
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
id|ic
op_assign
id|jffs2_alloc_inode_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ic
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ic
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ic
)paren
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
(brace
id|jffs2_free_inode_cache
c_func
(paren
id|ic
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
multiline_comment|/* Alloc jffs2_inode_info when that&squot;s split in 2.5 */
id|f
op_assign
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|f-&gt;inocache
op_assign
id|ic
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|f-&gt;inocache-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|f-&gt;inocache-&gt;nodes
op_assign
(paren
r_struct
id|jffs2_raw_node_ref
op_star
)paren
id|f-&gt;inocache
suffix:semicolon
id|f-&gt;inocache-&gt;ino
op_assign
id|ri-&gt;ino
op_assign
id|inode-&gt;i_ino
op_assign
op_increment
id|c-&gt;highest_ino
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_new_inode(): Assigned ino# %d&bslash;n&quot;
comma
id|ri-&gt;ino
)paren
)paren
suffix:semicolon
id|jffs2_add_ino_cache
c_func
(paren
id|c
comma
id|f-&gt;inocache
)paren
suffix:semicolon
id|ri-&gt;magic
op_assign
id|JFFS2_MAGIC_BITMASK
suffix:semicolon
id|ri-&gt;nodetype
op_assign
id|JFFS2_NODETYPE_INODE
suffix:semicolon
id|ri-&gt;totlen
op_assign
id|PAD
c_func
(paren
r_sizeof
(paren
op_star
id|ri
)paren
)paren
suffix:semicolon
id|ri-&gt;hdr_crc
op_assign
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
suffix:semicolon
id|ri-&gt;mode
op_assign
id|mode
suffix:semicolon
id|f-&gt;highest_version
op_assign
id|ri-&gt;version
op_assign
l_int|1
suffix:semicolon
id|ri-&gt;uid
op_assign
id|current-&gt;fsuid
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
id|dir_i-&gt;i_gid
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
id|ri-&gt;mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
(brace
id|ri-&gt;gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_assign
id|ri-&gt;mode
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|ri-&gt;gid
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|ri-&gt;uid
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|ri-&gt;atime
op_assign
id|ri-&gt;mtime
op_assign
id|ri-&gt;ctime
op_assign
id|CURRENT_TIME
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
multiline_comment|/* This ought to be in core MTD code. All registered MTD devices without writev should have&n;   this put in place. Bug the MTD maintainer */
DECL|function|mtd_fake_writev
r_static
r_int
id|mtd_fake_writev
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|iovec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|totlen
op_assign
l_int|0
comma
id|thislen
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mtd
op_member_access_from_pointer
id|write
c_func
(paren
id|mtd
comma
id|to
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_len
comma
op_amp
id|thislen
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_base
)paren
suffix:semicolon
id|totlen
op_add_assign
id|thislen
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_or
id|thislen
op_ne
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_break
suffix:semicolon
id|to
op_add_assign
id|vecs
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retlen
)paren
op_star
id|retlen
op_assign
id|totlen
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mtd_writev
r_static
r_inline
r_int
id|mtd_writev
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|iovec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
(brace
r_if
c_cond
(paren
id|mtd-&gt;writev
)paren
r_return
id|mtd
op_member_access_from_pointer
id|writev
c_func
(paren
id|mtd
comma
id|vecs
comma
id|count
comma
id|to
comma
id|retlen
)paren
suffix:semicolon
r_else
r_return
id|mtd_fake_writev
c_func
(paren
id|mtd
comma
id|vecs
comma
id|count
comma
id|to
comma
id|retlen
)paren
suffix:semicolon
)brace
DECL|function|writecheck
r_static
r_void
id|writecheck
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|__u32
id|ofs
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
id|ssize_t
id|retlen
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|read
c_func
(paren
id|mtd
comma
id|ofs
comma
l_int|16
comma
op_amp
id|retlen
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
id|retlen
op_ne
l_int|16
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;read failed or short in writecheck(). ret %d, retlen %d&bslash;n&quot;
comma
id|ret
comma
id|retlen
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_ne
l_int|0xff
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ARGH. About to write node to 0x%08x on flash, but there&squot;s data already there:&bslash;n&quot;
comma
id|ofs
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;0x%08x: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
id|ofs
comma
id|buf
(braket
l_int|0
)braket
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
comma
id|buf
(braket
l_int|4
)braket
comma
id|buf
(braket
l_int|5
)braket
comma
id|buf
(braket
l_int|6
)braket
comma
id|buf
(braket
l_int|7
)braket
comma
id|buf
(braket
l_int|8
)braket
comma
id|buf
(braket
l_int|9
)braket
comma
id|buf
(braket
l_int|10
)braket
comma
id|buf
(braket
l_int|11
)braket
comma
id|buf
(braket
l_int|12
)braket
comma
id|buf
(braket
l_int|13
)braket
comma
id|buf
(braket
l_int|14
)braket
comma
id|buf
(braket
l_int|15
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* jffs2_write_dnode - given a raw_inode, allocate a full_dnode for it, &n;   write it to the flash, link it into the existing inode/fragment list */
DECL|function|jffs2_write_dnode
r_struct
id|jffs2_full_dnode
op_star
id|jffs2_write_dnode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
comma
r_const
r_int
r_char
op_star
id|data
comma
id|__u32
id|datalen
comma
id|__u32
id|flash_ofs
comma
id|__u32
op_star
id|writelen
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
r_struct
id|jffs2_raw_node_ref
op_star
id|raw
suffix:semicolon
r_struct
id|jffs2_full_dnode
op_star
id|fn
suffix:semicolon
id|ssize_t
id|retlen
suffix:semicolon
r_struct
id|iovec
id|vecs
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|D1
c_func
(paren
r_if
(paren
id|ri-&gt;hdr_crc
op_ne
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
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Eep. CRC not correct in jffs2_write_dnode()&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)paren
suffix:semicolon
id|vecs
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|ri
suffix:semicolon
id|vecs
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
r_sizeof
(paren
op_star
id|ri
)paren
suffix:semicolon
id|vecs
(braket
l_int|1
)braket
dot
id|iov_base
op_assign
(paren
r_int
r_char
op_star
)paren
id|data
suffix:semicolon
id|vecs
(braket
l_int|1
)braket
dot
id|iov_len
op_assign
id|datalen
suffix:semicolon
id|writecheck
c_func
(paren
id|c-&gt;mtd
comma
id|flash_ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;totlen
op_ne
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|datalen
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jffs2_write_dnode: ri-&gt;totlen (0x%08x) != sizeof(*ri) (0x%08x) + datalen (0x%08x)&bslash;n&quot;
comma
id|ri-&gt;totlen
comma
r_sizeof
(paren
op_star
id|ri
)paren
comma
id|datalen
)paren
suffix:semicolon
)brace
id|raw
op_assign
id|jffs2_alloc_raw_node_ref
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|fn
op_assign
id|jffs2_alloc_full_dnode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
(brace
id|jffs2_free_raw_node_ref
c_func
(paren
id|raw
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|raw-&gt;flash_offset
op_assign
id|flash_ofs
suffix:semicolon
id|raw-&gt;totlen
op_assign
id|PAD
c_func
(paren
id|ri-&gt;totlen
)paren
suffix:semicolon
id|raw-&gt;next_phys
op_assign
l_int|NULL
suffix:semicolon
id|fn-&gt;ofs
op_assign
id|ri-&gt;offset
suffix:semicolon
id|fn-&gt;size
op_assign
id|ri-&gt;dsize
suffix:semicolon
id|fn-&gt;frags
op_assign
l_int|0
suffix:semicolon
id|fn-&gt;raw
op_assign
id|raw
suffix:semicolon
id|ret
op_assign
id|mtd_writev
c_func
(paren
id|c-&gt;mtd
comma
id|vecs
comma
l_int|2
comma
id|flash_ofs
comma
op_amp
id|retlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_or
(paren
id|retlen
op_ne
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|datalen
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Write of %d bytes at 0x%08x failed. returned %d, retlen %d&bslash;n&quot;
comma
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|datalen
comma
id|flash_ofs
comma
id|ret
comma
id|retlen
)paren
suffix:semicolon
multiline_comment|/* Mark the space as dirtied */
r_if
c_cond
(paren
id|retlen
)paren
(brace
multiline_comment|/* Doesn&squot;t belong to any inode */
id|raw-&gt;next_in_ino
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Don&squot;t change raw-&gt;size to match retlen. We may have &n;&t;&t;&t;   written the node header already, and only the data will&n;&t;&t;&t;   seem corrupted, in which case the scan would skip over&n;&t;&t;&t;   any node we write before the original intended end of &n;&t;&t;&t;   this node */
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
comma
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|datalen
comma
l_int|1
)paren
suffix:semicolon
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|raw
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Not marking the space at 0x%08x as dirty because the flash driver returned retlen zero&bslash;n&quot;
comma
id|raw-&gt;flash_offset
)paren
suffix:semicolon
id|jffs2_free_raw_node_ref
c_func
(paren
id|raw
)paren
suffix:semicolon
)brace
multiline_comment|/* Release the full_dnode which is now useless, and return */
id|jffs2_free_full_dnode
c_func
(paren
id|fn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writelen
)paren
op_star
id|writelen
op_assign
id|retlen
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
ques
c_cond
id|ret
suffix:colon
op_minus
id|EIO
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark the space used */
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
comma
id|retlen
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Link into per-inode list */
id|raw-&gt;next_in_ino
op_assign
id|f-&gt;inocache-&gt;nodes
suffix:semicolon
id|f-&gt;inocache-&gt;nodes
op_assign
id|raw
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_write_dnode wrote node at 0x%08x with dsize 0x%x, csize 0x%x, node_crc 0x%08x, data_crc 0x%08x, totlen 0x%08x&bslash;n&quot;
comma
id|flash_ofs
comma
id|ri-&gt;dsize
comma
id|ri-&gt;csize
comma
id|ri-&gt;node_crc
comma
id|ri-&gt;data_crc
comma
id|ri-&gt;totlen
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writelen
)paren
op_star
id|writelen
op_assign
id|retlen
suffix:semicolon
id|f-&gt;inocache-&gt;nodes
op_assign
id|raw
suffix:semicolon
r_return
id|fn
suffix:semicolon
)brace
DECL|function|jffs2_write_dirent
r_struct
id|jffs2_full_dirent
op_star
id|jffs2_write_dirent
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|jffs2_raw_dirent
op_star
id|rd
comma
r_const
r_int
r_char
op_star
id|name
comma
id|__u32
id|namelen
comma
id|__u32
id|flash_ofs
comma
id|__u32
op_star
id|writelen
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
r_struct
id|jffs2_raw_node_ref
op_star
id|raw
suffix:semicolon
r_struct
id|jffs2_full_dirent
op_star
id|fd
suffix:semicolon
id|ssize_t
id|retlen
suffix:semicolon
r_struct
id|iovec
id|vecs
(braket
l_int|2
)braket
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
l_string|&quot;jffs2_write_dirent(ino #%u, name at *0x%p &bslash;&quot;%s&bslash;&quot;-&gt;ino #%u, name_crc 0x%08x)&bslash;n&quot;
comma
id|rd-&gt;pino
comma
id|name
comma
id|name
comma
id|rd-&gt;ino
comma
id|rd-&gt;name_crc
)paren
)paren
suffix:semicolon
id|writecheck
c_func
(paren
id|c-&gt;mtd
comma
id|flash_ofs
)paren
suffix:semicolon
id|D1
c_func
(paren
r_if
(paren
id|rd-&gt;hdr_crc
op_ne
id|crc32
c_func
(paren
l_int|0
comma
id|rd
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
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Eep. CRC not correct in jffs2_write_dirent()&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)paren
suffix:semicolon
id|vecs
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|rd
suffix:semicolon
id|vecs
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
r_sizeof
(paren
op_star
id|rd
)paren
suffix:semicolon
id|vecs
(braket
l_int|1
)braket
dot
id|iov_base
op_assign
(paren
r_int
r_char
op_star
)paren
id|name
suffix:semicolon
id|vecs
(braket
l_int|1
)braket
dot
id|iov_len
op_assign
id|namelen
suffix:semicolon
id|raw
op_assign
id|jffs2_alloc_raw_node_ref
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|fd
op_assign
id|jffs2_alloc_full_dirent
c_func
(paren
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fd
)paren
(brace
id|jffs2_free_raw_node_ref
c_func
(paren
id|raw
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|raw-&gt;flash_offset
op_assign
id|flash_ofs
suffix:semicolon
id|raw-&gt;totlen
op_assign
id|PAD
c_func
(paren
id|rd-&gt;totlen
)paren
suffix:semicolon
id|raw-&gt;next_in_ino
op_assign
id|f-&gt;inocache-&gt;nodes
suffix:semicolon
id|f-&gt;inocache-&gt;nodes
op_assign
id|raw
suffix:semicolon
id|raw-&gt;next_phys
op_assign
l_int|NULL
suffix:semicolon
id|fd-&gt;version
op_assign
id|rd-&gt;version
suffix:semicolon
id|fd-&gt;ino
op_assign
id|rd-&gt;ino
suffix:semicolon
id|fd-&gt;nhash
op_assign
id|full_name_hash
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
id|fd-&gt;type
op_assign
id|rd-&gt;type
suffix:semicolon
id|memcpy
c_func
(paren
id|fd-&gt;name
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|fd-&gt;name
(braket
id|namelen
)braket
op_assign
l_int|0
suffix:semicolon
id|fd-&gt;raw
op_assign
id|raw
suffix:semicolon
id|ret
op_assign
id|mtd_writev
c_func
(paren
id|c-&gt;mtd
comma
id|vecs
comma
l_int|2
comma
id|flash_ofs
comma
op_amp
id|retlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_or
(paren
id|retlen
op_ne
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Write of %d bytes at 0x%08x failed. returned %d, retlen %d&bslash;n&quot;
comma
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
comma
id|flash_ofs
comma
id|ret
comma
id|retlen
)paren
suffix:semicolon
multiline_comment|/* Mark the space as dirtied */
r_if
c_cond
(paren
id|retlen
)paren
(brace
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
comma
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
comma
l_int|1
)paren
suffix:semicolon
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|raw
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Not marking the space at 0x%08x as dirty because the flash driver returned retlen zero&bslash;n&quot;
comma
id|raw-&gt;flash_offset
)paren
suffix:semicolon
id|jffs2_free_raw_node_ref
c_func
(paren
id|raw
)paren
suffix:semicolon
)brace
multiline_comment|/* Release the full_dnode which is now useless, and return */
id|jffs2_free_full_dirent
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writelen
)paren
op_star
id|writelen
op_assign
id|retlen
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
ques
c_cond
id|ret
suffix:colon
op_minus
id|EIO
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark the space used */
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
comma
id|retlen
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writelen
)paren
op_star
id|writelen
op_assign
id|retlen
suffix:semicolon
id|f-&gt;inocache-&gt;nodes
op_assign
id|raw
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
eof
