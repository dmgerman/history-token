multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001, 2002 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: write.c,v 1.60 2002/09/09 16:29:08 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &quot;nodelist.h&quot;
DECL|function|jffs2_do_new_inode
r_int
id|jffs2_do_new_inode
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
r_uint32
id|mode
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
)paren
(brace
r_struct
id|jffs2_inode_cache
op_star
id|ic
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
op_minus
id|ENOMEM
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
op_increment
id|c-&gt;highest_ino
suffix:semicolon
id|f-&gt;inocache-&gt;state
op_assign
id|INO_STATE_PRESENT
suffix:semicolon
id|ri-&gt;ino
op_assign
id|cpu_to_je32
c_func
(paren
id|f-&gt;inocache-&gt;ino
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_new_inode(): Assigned ino# %d&bslash;n&quot;
comma
id|f-&gt;inocache-&gt;ino
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
id|PAD
c_func
(paren
r_sizeof
(paren
op_star
id|ri
)paren
)paren
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
id|ri-&gt;mode
op_assign
id|cpu_to_je32
c_func
(paren
id|mode
)paren
suffix:semicolon
id|f-&gt;highest_version
op_assign
l_int|1
suffix:semicolon
id|ri-&gt;version
op_assign
id|cpu_to_je32
c_func
(paren
id|f-&gt;highest_version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|writecheck
r_static
r_void
id|writecheck
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_uint32
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
r_int
id|retlen
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
id|ret
op_assign
id|jffs2_flash_read
c_func
(paren
id|c
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
op_logical_or
(paren
id|retlen
op_ne
l_int|16
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
l_string|&quot;ARGH. About to write node to 0x%08x on flash, but there are data already there:&bslash;n&quot;
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
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
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
r_uint32
id|datalen
comma
r_uint32
id|flash_ofs
comma
r_uint32
op_star
id|writelen
)paren
(brace
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
r_int
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
r_int
r_int
id|cnt
op_assign
l_int|2
suffix:semicolon
id|D1
c_func
(paren
r_if
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;hdr_crc
)paren
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
id|c
comma
id|flash_ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;totlen
)paren
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
id|je32_to_cpu
c_func
(paren
id|ri-&gt;totlen
)paren
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
r_sizeof
(paren
op_star
id|ri
)paren
op_plus
id|datalen
)paren
suffix:semicolon
id|raw-&gt;next_phys
op_assign
l_int|NULL
suffix:semicolon
id|fn-&gt;ofs
op_assign
id|je32_to_cpu
c_func
(paren
id|ri-&gt;offset
)paren
suffix:semicolon
id|fn-&gt;size
op_assign
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
suffix:semicolon
id|fn-&gt;frags
op_assign
l_int|0
suffix:semicolon
id|fn-&gt;raw
op_assign
id|raw
suffix:semicolon
multiline_comment|/* check number of valid vecs */
r_if
c_cond
(paren
op_logical_neg
id|datalen
op_logical_or
op_logical_neg
id|data
)paren
id|cnt
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|jffs2_flash_writev
c_func
(paren
id|c
comma
id|vecs
comma
id|cnt
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
id|raw-&gt;flash_offset
op_or_assign
id|REF_OBSOLETE
suffix:semicolon
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
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
r_if
c_cond
(paren
id|datalen
op_eq
id|PAGE_CACHE_SIZE
)paren
id|raw-&gt;flash_offset
op_or_assign
id|REF_PRISTINE
suffix:semicolon
r_else
id|raw-&gt;flash_offset
op_or_assign
id|REF_NORMAL
suffix:semicolon
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
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
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;node_crc
)paren
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;data_crc
)paren
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;totlen
)paren
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
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
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
r_uint32
id|namelen
comma
r_uint32
id|flash_ofs
comma
r_uint32
op_star
id|writelen
)paren
(brace
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
r_int
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
id|je32_to_cpu
c_func
(paren
id|rd-&gt;pino
)paren
comma
id|name
comma
id|name
comma
id|je32_to_cpu
c_func
(paren
id|rd-&gt;ino
)paren
comma
id|je32_to_cpu
c_func
(paren
id|rd-&gt;name_crc
)paren
)paren
)paren
suffix:semicolon
id|writecheck
c_func
(paren
id|c
comma
id|flash_ofs
)paren
suffix:semicolon
id|D1
c_func
(paren
r_if
(paren
id|je32_to_cpu
c_func
(paren
id|rd-&gt;hdr_crc
)paren
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
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
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
id|je32_to_cpu
c_func
(paren
id|rd-&gt;version
)paren
suffix:semicolon
id|fd-&gt;ino
op_assign
id|je32_to_cpu
c_func
(paren
id|rd-&gt;ino
)paren
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
id|jffs2_flash_writev
c_func
(paren
id|c
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
id|raw-&gt;flash_offset
op_or_assign
id|REF_OBSOLETE
suffix:semicolon
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
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
id|raw-&gt;flash_offset
op_or_assign
id|REF_PRISTINE
suffix:semicolon
id|jffs2_add_physical_node_ref
c_func
(paren
id|c
comma
id|raw
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
multiline_comment|/* The OS-specific code fills in the metadata in the jffs2_raw_inode for us, so that&n;   we don&squot;t have to go digging in struct inode or its equivalent. It should set:&n;   mode, uid, gid, (starting)isize, atime, ctime, mtime */
DECL|function|jffs2_write_inode_range
r_int
id|jffs2_write_inode_range
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
r_struct
id|jffs2_raw_inode
op_star
id|ri
comma
r_int
r_char
op_star
id|buf
comma
r_uint32
id|offset
comma
r_uint32
id|writelen
comma
r_uint32
op_star
id|retlen
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_uint32
id|writtenlen
op_assign
l_int|0
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_write_inode_range(): Ino #%u, ofs 0x%x, len 0x%x&bslash;n&quot;
comma
id|f-&gt;inocache-&gt;ino
comma
id|offset
comma
id|writelen
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|writelen
)paren
(brace
r_struct
id|jffs2_full_dnode
op_star
id|fn
suffix:semicolon
r_int
r_char
op_star
id|comprbuf
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|comprtype
op_assign
id|JFFS2_COMPR_NONE
suffix:semicolon
r_uint32
id|phys_ofs
comma
id|alloclen
suffix:semicolon
r_uint32
id|datalen
comma
id|cdatalen
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_commit_write() loop: 0x%x to write to 0x%x&bslash;n&quot;
comma
id|writelen
comma
id|offset
)paren
)paren
suffix:semicolon
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
id|JFFS2_MIN_DATA_LEN
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
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space returned %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
id|datalen
op_assign
id|writelen
suffix:semicolon
id|cdatalen
op_assign
id|min
c_func
(paren
id|alloclen
op_minus
r_sizeof
(paren
op_star
id|ri
)paren
comma
id|writelen
)paren
suffix:semicolon
id|comprbuf
op_assign
id|kmalloc
c_func
(paren
id|cdatalen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|comprbuf
)paren
(brace
id|comprtype
op_assign
id|jffs2_compress
c_func
(paren
id|buf
comma
id|comprbuf
comma
op_amp
id|datalen
comma
op_amp
id|cdatalen
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|comprtype
op_eq
id|JFFS2_COMPR_NONE
)paren
(brace
multiline_comment|/* Either compression failed, or the allocation of comprbuf failed */
r_if
c_cond
(paren
id|comprbuf
)paren
id|kfree
c_func
(paren
id|comprbuf
)paren
suffix:semicolon
id|comprbuf
op_assign
id|buf
suffix:semicolon
id|datalen
op_assign
id|cdatalen
suffix:semicolon
)brace
multiline_comment|/* Now comprbuf points to the data to be written, be it compressed or not.&n;&t;&t;   comprtype holds the compression type, and comprtype == JFFS2_COMPR_NONE means&n;&t;&t;   that the comprbuf doesn&squot;t need to be kfree()d. &n;&t;&t;*/
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
id|cdatalen
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
id|f-&gt;inocache-&gt;ino
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
id|ri-&gt;isize
op_assign
id|cpu_to_je32
c_func
(paren
id|max
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;isize
)paren
comma
id|offset
op_plus
id|datalen
)paren
)paren
suffix:semicolon
id|ri-&gt;offset
op_assign
id|cpu_to_je32
c_func
(paren
id|offset
)paren
suffix:semicolon
id|ri-&gt;csize
op_assign
id|cpu_to_je32
c_func
(paren
id|cdatalen
)paren
suffix:semicolon
id|ri-&gt;dsize
op_assign
id|cpu_to_je32
c_func
(paren
id|datalen
)paren
suffix:semicolon
id|ri-&gt;compr
op_assign
id|comprtype
suffix:semicolon
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
id|comprbuf
comma
id|cdatalen
)paren
)paren
suffix:semicolon
id|fn
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
id|comprbuf
comma
id|cdatalen
comma
id|phys_ofs
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|comprtype
op_ne
id|JFFS2_COMPR_NONE
)paren
id|kfree
c_func
(paren
id|comprbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fn
)paren
)paren
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|fn
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
r_break
suffix:semicolon
)brace
id|ret
op_assign
id|jffs2_add_full_dnode_to_inode
c_func
(paren
id|c
comma
id|f
comma
id|fn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;metadata
)paren
(brace
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|f-&gt;metadata-&gt;raw
)paren
suffix:semicolon
id|jffs2_free_full_dnode
c_func
(paren
id|f-&gt;metadata
)paren
suffix:semicolon
id|f-&gt;metadata
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* Eep */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Eep. add_full_dnode_to_inode() failed in commit_write, returned %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|fn-&gt;raw
)paren
suffix:semicolon
id|jffs2_free_full_dnode
c_func
(paren
id|fn
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
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|datalen
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Eep. We didn&squot;t actually write any data in jffs2_write_inode_range()&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;increasing writtenlen by %d&bslash;n&quot;
comma
id|datalen
)paren
)paren
suffix:semicolon
id|writtenlen
op_add_assign
id|datalen
suffix:semicolon
id|offset
op_add_assign
id|datalen
suffix:semicolon
id|writelen
op_sub_assign
id|datalen
suffix:semicolon
id|buf
op_add_assign
id|datalen
suffix:semicolon
)brace
op_star
id|retlen
op_assign
id|writtenlen
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_do_create
r_int
id|jffs2_do_create
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
id|dir_f
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_struct
id|jffs2_raw_inode
op_star
id|ri
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
r_struct
id|jffs2_raw_dirent
op_star
id|rd
suffix:semicolon
r_struct
id|jffs2_full_dnode
op_star
id|fn
suffix:semicolon
r_struct
id|jffs2_full_dirent
op_star
id|fd
suffix:semicolon
r_uint32
id|alloclen
comma
id|phys_ofs
suffix:semicolon
r_uint32
id|writtenlen
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Try to reserve enough space for both node and dirent. &n;&t; * Just the node will do for now, though &n;&t; */
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
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_create(): reserved 0x%x bytes&bslash;n&quot;
comma
id|alloclen
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ri-&gt;data_crc
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
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
id|fn
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
l_int|NULL
comma
l_int|0
comma
id|phys_ofs
comma
op_amp
id|writtenlen
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_do_create created file with mode 0x%x&bslash;n&quot;
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;mode
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fn
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
l_string|&quot;jffs2_write_dnode() failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Eeek. Wave bye bye */
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
r_return
id|PTR_ERR
c_func
(paren
id|fn
)paren
suffix:semicolon
)brace
multiline_comment|/* No data here. Only a metadata node, which will be &n;&t;   obsoleted by the first data write&n;&t;*/
id|f-&gt;metadata
op_assign
id|fn
suffix:semicolon
multiline_comment|/* Work out where to put the dirent node now. */
id|writtenlen
op_assign
id|PAD
c_func
(paren
id|writtenlen
)paren
suffix:semicolon
id|phys_ofs
op_add_assign
id|writtenlen
suffix:semicolon
id|alloclen
op_sub_assign
id|writtenlen
suffix:semicolon
id|up
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alloclen
OL
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
)paren
(brace
multiline_comment|/* Not enough space left in this chunk. Get some more */
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
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
id|rd
)paren
op_plus
id|namelen
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
multiline_comment|/* Eep. */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_reserve_space() for dirent failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
id|rd
op_assign
id|jffs2_alloc_raw_dirent
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rd
)paren
(brace
multiline_comment|/* Argh. Now we treat it like a normal delete */
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
id|rd-&gt;magic
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_MAGIC_BITMASK
)paren
suffix:semicolon
id|rd-&gt;nodetype
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_NODETYPE_DIRENT
)paren
suffix:semicolon
id|rd-&gt;totlen
op_assign
id|cpu_to_je32
c_func
(paren
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
)paren
suffix:semicolon
id|rd-&gt;hdr_crc
op_assign
id|cpu_to_je32
c_func
(paren
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
suffix:semicolon
id|rd-&gt;pino
op_assign
id|cpu_to_je32
c_func
(paren
id|dir_f-&gt;inocache-&gt;ino
)paren
suffix:semicolon
id|rd-&gt;version
op_assign
id|cpu_to_je32
c_func
(paren
op_increment
id|dir_f-&gt;highest_version
)paren
suffix:semicolon
id|rd-&gt;ino
op_assign
id|ri-&gt;ino
suffix:semicolon
id|rd-&gt;mctime
op_assign
id|ri-&gt;ctime
suffix:semicolon
id|rd-&gt;nsize
op_assign
id|namelen
suffix:semicolon
id|rd-&gt;type
op_assign
id|DT_REG
suffix:semicolon
id|rd-&gt;node_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|rd
comma
r_sizeof
(paren
op_star
id|rd
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|rd-&gt;name_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|name
comma
id|namelen
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|jffs2_write_dirent
c_func
(paren
id|c
comma
id|dir_f
comma
id|rd
comma
id|name
comma
id|namelen
comma
id|phys_ofs
comma
op_amp
id|writtenlen
)paren
suffix:semicolon
id|jffs2_free_raw_dirent
c_func
(paren
id|rd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fd
)paren
)paren
(brace
multiline_comment|/* dirent failed to write. Delete the inode normally &n;&t;&t;   as if it were the final unlink() */
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/* Link the fd into the inode&squot;s list, obsoleting an old&n;&t;   one if necessary. */
id|jffs2_add_fd_to_list
c_func
(paren
id|c
comma
id|fd
comma
op_amp
id|dir_f-&gt;dents
)paren
suffix:semicolon
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_do_unlink
r_int
id|jffs2_do_unlink
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
id|dir_f
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|jffs2_inode_info
op_star
id|dead_f
)paren
(brace
r_struct
id|jffs2_raw_dirent
op_star
id|rd
suffix:semicolon
r_struct
id|jffs2_full_dirent
op_star
id|fd
suffix:semicolon
r_uint32
id|alloclen
comma
id|phys_ofs
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|rd
op_assign
id|jffs2_alloc_raw_dirent
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|rd
)paren
op_plus
id|namelen
comma
op_amp
id|phys_ofs
comma
op_amp
id|alloclen
comma
id|ALLOC_DELETION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|jffs2_free_raw_dirent
c_func
(paren
id|rd
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
id|dir_f-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* Build a deletion node */
id|rd-&gt;magic
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_MAGIC_BITMASK
)paren
suffix:semicolon
id|rd-&gt;nodetype
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_NODETYPE_DIRENT
)paren
suffix:semicolon
id|rd-&gt;totlen
op_assign
id|cpu_to_je32
c_func
(paren
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
)paren
suffix:semicolon
id|rd-&gt;hdr_crc
op_assign
id|cpu_to_je32
c_func
(paren
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
suffix:semicolon
id|rd-&gt;pino
op_assign
id|cpu_to_je32
c_func
(paren
id|dir_f-&gt;inocache-&gt;ino
)paren
suffix:semicolon
id|rd-&gt;version
op_assign
id|cpu_to_je32
c_func
(paren
op_increment
id|dir_f-&gt;highest_version
)paren
suffix:semicolon
id|rd-&gt;ino
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|rd-&gt;mctime
op_assign
id|cpu_to_je32
c_func
(paren
id|CURRENT_TIME
)paren
suffix:semicolon
id|rd-&gt;nsize
op_assign
id|namelen
suffix:semicolon
id|rd-&gt;type
op_assign
id|DT_UNKNOWN
suffix:semicolon
id|rd-&gt;node_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|rd
comma
r_sizeof
(paren
op_star
id|rd
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|rd-&gt;name_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|name
comma
id|namelen
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|jffs2_write_dirent
c_func
(paren
id|c
comma
id|dir_f
comma
id|rd
comma
id|name
comma
id|namelen
comma
id|phys_ofs
comma
l_int|NULL
)paren
suffix:semicolon
id|jffs2_free_raw_dirent
c_func
(paren
id|rd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fd
)paren
)paren
(brace
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/* File it. This will mark the old one obsolete. */
id|jffs2_add_fd_to_list
c_func
(paren
id|c
comma
id|fd
comma
op_amp
id|dir_f-&gt;dents
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* dead_f is NULL if this was a rename not a real unlink */
multiline_comment|/* Also catch the !f-&gt;inocache case, where there was a dirent&n;&t;   pointing to an inode which didn&squot;t exist. */
r_if
c_cond
(paren
id|dead_f
op_logical_and
id|dead_f-&gt;inocache
)paren
(brace
id|down
c_func
(paren
op_amp
id|dead_f-&gt;sem
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dead_f-&gt;dents
)paren
(brace
multiline_comment|/* There can be only deleted ones */
id|fd
op_assign
id|dead_f-&gt;dents
suffix:semicolon
id|dead_f-&gt;dents
op_assign
id|fd-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|fd-&gt;ino
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Deleting inode #%u with active dentry &bslash;&quot;%s&bslash;&quot;-&gt;ino #%u&bslash;n&quot;
comma
id|dead_f-&gt;inocache-&gt;ino
comma
id|fd-&gt;name
comma
id|fd-&gt;ino
)paren
suffix:semicolon
)brace
r_else
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Removing deletion dirent for &bslash;&quot;%s&bslash;&quot; from dir ino #%u&bslash;n&quot;
comma
id|fd-&gt;name
comma
id|dead_f-&gt;inocache-&gt;ino
)paren
)paren
suffix:semicolon
)brace
id|jffs2_mark_node_obsolete
c_func
(paren
id|c
comma
id|fd-&gt;raw
)paren
suffix:semicolon
id|jffs2_free_full_dirent
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
id|dead_f-&gt;inocache-&gt;nlink
op_decrement
suffix:semicolon
multiline_comment|/* NB: Caller must set inode nlink if appropriate */
id|up
c_func
(paren
op_amp
id|dead_f-&gt;sem
)paren
suffix:semicolon
)brace
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_do_link
r_int
id|jffs2_do_link
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|dir_f
comma
r_uint32
id|ino
comma
r_uint8
id|type
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
r_struct
id|jffs2_raw_dirent
op_star
id|rd
suffix:semicolon
r_struct
id|jffs2_full_dirent
op_star
id|fd
suffix:semicolon
r_uint32
id|alloclen
comma
id|phys_ofs
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|rd
op_assign
id|jffs2_alloc_raw_dirent
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|rd
)paren
op_plus
id|namelen
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
id|jffs2_free_raw_dirent
c_func
(paren
id|rd
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
id|dir_f-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* Build a deletion node */
id|rd-&gt;magic
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_MAGIC_BITMASK
)paren
suffix:semicolon
id|rd-&gt;nodetype
op_assign
id|cpu_to_je16
c_func
(paren
id|JFFS2_NODETYPE_DIRENT
)paren
suffix:semicolon
id|rd-&gt;totlen
op_assign
id|cpu_to_je32
c_func
(paren
r_sizeof
(paren
op_star
id|rd
)paren
op_plus
id|namelen
)paren
suffix:semicolon
id|rd-&gt;hdr_crc
op_assign
id|cpu_to_je32
c_func
(paren
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
suffix:semicolon
id|rd-&gt;pino
op_assign
id|cpu_to_je32
c_func
(paren
id|dir_f-&gt;inocache-&gt;ino
)paren
suffix:semicolon
id|rd-&gt;version
op_assign
id|cpu_to_je32
c_func
(paren
op_increment
id|dir_f-&gt;highest_version
)paren
suffix:semicolon
id|rd-&gt;ino
op_assign
id|cpu_to_je32
c_func
(paren
id|ino
)paren
suffix:semicolon
id|rd-&gt;mctime
op_assign
id|cpu_to_je32
c_func
(paren
id|CURRENT_TIME
)paren
suffix:semicolon
id|rd-&gt;nsize
op_assign
id|namelen
suffix:semicolon
id|rd-&gt;type
op_assign
id|type
suffix:semicolon
id|rd-&gt;node_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|rd
comma
r_sizeof
(paren
op_star
id|rd
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|rd-&gt;name_crc
op_assign
id|cpu_to_je32
c_func
(paren
id|crc32
c_func
(paren
l_int|0
comma
id|name
comma
id|namelen
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|jffs2_write_dirent
c_func
(paren
id|c
comma
id|dir_f
comma
id|rd
comma
id|name
comma
id|namelen
comma
id|phys_ofs
comma
l_int|NULL
)paren
suffix:semicolon
id|jffs2_free_raw_dirent
c_func
(paren
id|rd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|fd
)paren
)paren
(brace
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/* File it. This will mark the old one obsolete. */
id|jffs2_add_fd_to_list
c_func
(paren
id|c
comma
id|fd
comma
op_amp
id|dir_f-&gt;dents
)paren
suffix:semicolon
id|jffs2_complete_reservation
c_func
(paren
id|c
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir_f-&gt;sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
