multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001-2003 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: read.c,v 1.37 2004/11/16 15:45:13 dedekind Exp $&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &quot;nodelist.h&quot;
macro_line|#include &quot;compr.h&quot;
DECL|function|jffs2_read_dnode
r_int
id|jffs2_read_dnode
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
id|jffs2_full_dnode
op_star
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|ofs
comma
r_int
id|len
)paren
(brace
r_struct
id|jffs2_raw_inode
op_star
id|ri
suffix:semicolon
r_int
id|readlen
suffix:semicolon
r_uint32
id|crc
suffix:semicolon
r_int
r_char
op_star
id|decomprbuf
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
op_star
id|readbuf
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|jffs2_flash_read
c_func
(paren
id|c
comma
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
comma
r_sizeof
(paren
op_star
id|ri
)paren
comma
op_amp
id|readlen
comma
(paren
r_char
op_star
)paren
id|ri
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Error reading node from 0x%08x: %d&bslash;n&quot;
comma
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|readlen
op_ne
r_sizeof
(paren
op_star
id|ri
)paren
)paren
(brace
id|jffs2_free_raw_inode
c_func
(paren
id|ri
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Short read from 0x%08x: wanted 0x%zx bytes, got 0x%zx&bslash;n&quot;
comma
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
comma
r_sizeof
(paren
op_star
id|ri
)paren
comma
id|readlen
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|crc
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
op_star
id|ri
)paren
op_minus
l_int|8
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Node read from %08x: node_crc %08x, calculated CRC %08x. dsize %x, csize %x, offset %x, buf %p&bslash;n&quot;
comma
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;node_crc
)paren
comma
id|crc
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
id|ri-&gt;offset
)paren
comma
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crc
op_ne
id|je32_to_cpu
c_func
(paren
id|ri-&gt;node_crc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Node CRC %08x != calculated CRC %08x for node at %08x&bslash;n&quot;
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;node_crc
)paren
comma
id|crc
comma
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_ri
suffix:semicolon
)brace
multiline_comment|/* There was a bug where we wrote hole nodes out with csize/dsize&n;&t;   swapped. Deal with it */
r_if
c_cond
(paren
id|ri-&gt;compr
op_eq
id|JFFS2_COMPR_ZERO
op_logical_and
op_logical_neg
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
op_logical_and
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
)paren
(brace
id|ri-&gt;dsize
op_assign
id|ri-&gt;csize
suffix:semicolon
id|ri-&gt;csize
op_assign
id|cpu_to_je32
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|D1
c_func
(paren
r_if
(paren
id|ofs
op_plus
id|len
OG
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;jffs2_read_dnode() asked for %d bytes at %d from %d-byte node&bslash;n&quot;
comma
id|len
comma
id|ofs
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_ri
suffix:semicolon
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;compr
op_eq
id|JFFS2_COMPR_ZERO
)paren
(brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
r_goto
id|out_ri
suffix:semicolon
)brace
multiline_comment|/* Cases:&n;&t;   Reading whole node and it&squot;s uncompressed - read directly to buffer provided, check CRC.&n;&t;   Reading whole node and it&squot;s compressed - read into comprbuf, check CRC and decompress to buffer provided &n;&t;   Reading partial node and it&squot;s uncompressed - read into readbuf, check CRC, and copy &n;&t;   Reading partial node and it&squot;s compressed - read into readbuf, check checksum, decompress to decomprbuf and copy&n;&t;*/
r_if
c_cond
(paren
id|ri-&gt;compr
op_eq
id|JFFS2_COMPR_NONE
op_logical_and
id|len
op_eq
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
)paren
(brace
id|readbuf
op_assign
id|buf
suffix:semicolon
)brace
r_else
(brace
id|readbuf
op_assign
id|kmalloc
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|readbuf
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_ri
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ri-&gt;compr
op_ne
id|JFFS2_COMPR_NONE
)paren
(brace
r_if
c_cond
(paren
id|len
OL
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
)paren
(brace
id|decomprbuf
op_assign
id|kmalloc
c_func
(paren
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|decomprbuf
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_readbuf
suffix:semicolon
)brace
)brace
r_else
(brace
id|decomprbuf
op_assign
id|buf
suffix:semicolon
)brace
)brace
r_else
(brace
id|decomprbuf
op_assign
id|readbuf
suffix:semicolon
)brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Read %d bytes to %p&bslash;n&quot;
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
comma
id|readbuf
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_flash_read
c_func
(paren
id|c
comma
(paren
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
)paren
op_plus
r_sizeof
(paren
op_star
id|ri
)paren
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
comma
op_amp
id|readlen
comma
id|readbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|readlen
op_ne
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_decomprbuf
suffix:semicolon
id|crc
op_assign
id|crc32
c_func
(paren
l_int|0
comma
id|readbuf
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crc
op_ne
id|je32_to_cpu
c_func
(paren
id|ri-&gt;data_crc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Data CRC %08x != calculated CRC %08x for node at %08x&bslash;n&quot;
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;data_crc
)paren
comma
id|crc
comma
id|ref_offset
c_func
(paren
id|fd-&gt;raw
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_decomprbuf
suffix:semicolon
)brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Data CRC matches calculated CRC %08x&bslash;n&quot;
comma
id|crc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;compr
op_ne
id|JFFS2_COMPR_NONE
)paren
(brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Decompress %d bytes from %p to %d bytes at %p&bslash;n&quot;
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;csize
)paren
comma
id|readbuf
comma
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
comma
id|decomprbuf
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|jffs2_decompress
c_func
(paren
id|c
comma
id|f
comma
id|ri-&gt;compr
op_or
(paren
id|ri-&gt;usercompr
op_lshift
l_int|8
)paren
comma
id|readbuf
comma
id|decomprbuf
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
id|ri-&gt;dsize
)paren
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
id|KERN_WARNING
l_string|&quot;Error: jffs2_decompress returned %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_decomprbuf
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
OL
id|je32_to_cpu
c_func
(paren
id|ri-&gt;dsize
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|decomprbuf
op_plus
id|ofs
comma
id|len
)paren
suffix:semicolon
)brace
id|out_decomprbuf
suffix:colon
r_if
c_cond
(paren
id|decomprbuf
op_ne
id|buf
op_logical_and
id|decomprbuf
op_ne
id|readbuf
)paren
(brace
id|kfree
c_func
(paren
id|decomprbuf
)paren
suffix:semicolon
)brace
id|out_readbuf
suffix:colon
r_if
c_cond
(paren
id|readbuf
op_ne
id|buf
)paren
(brace
id|kfree
c_func
(paren
id|readbuf
)paren
suffix:semicolon
)brace
id|out_ri
suffix:colon
id|jffs2_free_raw_inode
c_func
(paren
id|ri
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_read_inode_range
r_int
id|jffs2_read_inode_range
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
r_char
op_star
id|buf
comma
r_uint32
id|offset
comma
r_uint32
id|len
)paren
(brace
r_uint32
id|end
op_assign
id|offset
op_plus
id|len
suffix:semicolon
r_struct
id|jffs2_node_frag
op_star
id|frag
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
l_string|&quot;jffs2_read_inode_range: ino #%u, range 0x%08x-0x%08x&bslash;n&quot;
comma
id|f-&gt;inocache-&gt;ino
comma
id|offset
comma
id|offset
op_plus
id|len
)paren
)paren
suffix:semicolon
id|frag
op_assign
id|jffs2_lookup_node_frag
c_func
(paren
op_amp
id|f-&gt;fragtree
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* XXX FIXME: Where a single physical node actually shows up in two&n;&t;   frags, we read it twice. Don&squot;t do that. */
multiline_comment|/* Now we&squot;re pointing at the first frag which overlaps our page */
r_while
c_loop
(paren
id|offset
OL
id|end
)paren
(brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_read_inode_range: offset %d, end %d&bslash;n&quot;
comma
id|offset
comma
id|end
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|frag
op_logical_or
id|frag-&gt;ofs
OG
id|offset
)paren
)paren
(brace
r_uint32
id|holesize
op_assign
id|end
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|frag
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Eep. Hole in ino #%u fraglist. frag-&gt;ofs = 0x%08x, offset = 0x%08x&bslash;n&quot;
comma
id|f-&gt;inocache-&gt;ino
comma
id|frag-&gt;ofs
comma
id|offset
)paren
)paren
suffix:semicolon
id|holesize
op_assign
id|min
c_func
(paren
id|holesize
comma
id|frag-&gt;ofs
op_minus
id|offset
)paren
suffix:semicolon
id|D2
c_func
(paren
id|jffs2_print_frag_list
c_func
(paren
id|f
)paren
)paren
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Filling non-frag hole from %d-%d&bslash;n&quot;
comma
id|offset
comma
id|offset
op_plus
id|holesize
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|holesize
)paren
suffix:semicolon
id|buf
op_add_assign
id|holesize
suffix:semicolon
id|offset
op_add_assign
id|holesize
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|frag-&gt;node
)paren
)paren
(brace
r_uint32
id|holeend
op_assign
id|min
c_func
(paren
id|end
comma
id|frag-&gt;ofs
op_plus
id|frag-&gt;size
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Filling frag hole from %d-%d (frag 0x%x 0x%x)&bslash;n&quot;
comma
id|offset
comma
id|holeend
comma
id|frag-&gt;ofs
comma
id|frag-&gt;ofs
op_plus
id|frag-&gt;size
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|holeend
op_minus
id|offset
)paren
suffix:semicolon
id|buf
op_add_assign
id|holeend
op_minus
id|offset
suffix:semicolon
id|offset
op_assign
id|holeend
suffix:semicolon
id|frag
op_assign
id|frag_next
c_func
(paren
id|frag
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
r_uint32
id|readlen
suffix:semicolon
r_uint32
id|fragofs
suffix:semicolon
multiline_comment|/* offset within the frag to start reading */
id|fragofs
op_assign
id|offset
op_minus
id|frag-&gt;ofs
suffix:semicolon
id|readlen
op_assign
id|min
c_func
(paren
id|frag-&gt;size
op_minus
id|fragofs
comma
id|end
op_minus
id|offset
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Reading %d-%d from node at 0x%08x (%d)&bslash;n&quot;
comma
id|frag-&gt;ofs
op_plus
id|fragofs
comma
id|frag-&gt;ofs
op_plus
id|fragofs
op_plus
id|readlen
comma
id|ref_offset
c_func
(paren
id|frag-&gt;node-&gt;raw
)paren
comma
id|ref_flags
c_func
(paren
id|frag-&gt;node-&gt;raw
)paren
)paren
)paren
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
id|frag-&gt;node
comma
id|buf
comma
id|fragofs
op_plus
id|frag-&gt;ofs
op_minus
id|frag-&gt;node-&gt;ofs
comma
id|readlen
)paren
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;node read done&bslash;n&quot;
)paren
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
l_string|&quot;jffs2_read_inode_range error %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|readlen
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|buf
op_add_assign
id|readlen
suffix:semicolon
id|offset
op_add_assign
id|readlen
suffix:semicolon
id|frag
op_assign
id|frag_next
c_func
(paren
id|frag
)paren
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;node read was OK. Looping&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Core function to read symlink target. */
DECL|function|jffs2_getlink
r_char
op_star
id|jffs2_getlink
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
r_char
op_star
id|buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|f-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;metadata
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;No metadata for symlink inode #%u&bslash;n&quot;
comma
id|f-&gt;inocache-&gt;ino
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
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
id|buf
op_assign
id|kmalloc
c_func
(paren
id|f-&gt;metadata-&gt;size
op_plus
l_int|1
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
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
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|buf
(braket
id|f-&gt;metadata-&gt;size
)braket
op_assign
l_int|0
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
id|buf
comma
l_int|0
comma
id|f-&gt;metadata-&gt;size
)paren
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
id|ret
)paren
(brace
id|kfree
c_func
(paren
id|buf
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
r_return
id|buf
suffix:semicolon
)brace
eof
