multiline_comment|/*&n; * $Id: redboot.c,v 1.6 2001/10/25 09:16:06 dwmw2 Exp $&n; *&n; * Parse RedBoot-style Flash Image System (FIS) tables and&n; * produce a Linux partition array to match.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|struct|fis_image_desc
r_struct
id|fis_image_desc
(brace
DECL|member|name
r_int
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
singleline_comment|// Null terminated name
DECL|member|flash_base
r_int
r_int
id|flash_base
suffix:semicolon
singleline_comment|// Address within FLASH of image
DECL|member|mem_base
r_int
r_int
id|mem_base
suffix:semicolon
singleline_comment|// Address in memory where it executes
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
singleline_comment|// Length of image
DECL|member|entry_point
r_int
r_int
id|entry_point
suffix:semicolon
singleline_comment|// Execution entry point
DECL|member|data_length
r_int
r_int
id|data_length
suffix:semicolon
singleline_comment|// Length of actual data
DECL|member|_pad
r_int
r_char
id|_pad
(braket
l_int|256
op_minus
(paren
l_int|16
op_plus
l_int|7
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
DECL|member|desc_cksum
r_int
r_int
id|desc_cksum
suffix:semicolon
singleline_comment|// Checksum over image descriptor
DECL|member|file_cksum
r_int
r_int
id|file_cksum
suffix:semicolon
singleline_comment|// Checksum over image data
)brace
suffix:semicolon
DECL|struct|fis_list
r_struct
id|fis_list
(brace
DECL|member|img
r_struct
id|fis_image_desc
op_star
id|img
suffix:semicolon
DECL|member|next
r_struct
id|fis_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|function|redboot_checksum
r_static
r_inline
r_int
id|redboot_checksum
c_func
(paren
r_struct
id|fis_image_desc
op_star
id|img
)paren
(brace
multiline_comment|/* RedBoot doesn&squot;t actually write the desc_cksum field yet AFAICT */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parse_redboot_partitions
r_int
id|parse_redboot_partitions
c_func
(paren
r_struct
id|mtd_info
op_star
id|master
comma
r_struct
id|mtd_partition
op_star
op_star
id|pparts
)paren
(brace
r_int
id|nrparts
op_assign
l_int|0
suffix:semicolon
r_struct
id|fis_image_desc
op_star
id|buf
suffix:semicolon
r_struct
id|mtd_partition
op_star
id|parts
suffix:semicolon
r_struct
id|fis_list
op_star
id|fl
op_assign
l_int|NULL
comma
op_star
id|tmp_fl
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
r_int
id|retlen
suffix:semicolon
r_char
op_star
id|names
suffix:semicolon
r_int
id|namelen
op_assign
l_int|0
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Read the start of the last erase block */
id|ret
op_assign
id|master
op_member_access_from_pointer
id|read
c_func
(paren
id|master
comma
id|master-&gt;size
op_minus
id|master-&gt;erasesize
comma
id|PAGE_SIZE
comma
op_amp
id|retlen
comma
(paren
r_void
op_star
)paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|retlen
op_ne
id|PAGE_SIZE
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* RedBoot image could appear in any of the first three slots */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buf
(braket
id|i
)braket
dot
id|name
comma
l_string|&quot;RedBoot&quot;
comma
l_int|8
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|3
)paren
(brace
multiline_comment|/* Didn&squot;t find it */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;No RedBoot partition table detected in %s&bslash;n&quot;
comma
id|master-&gt;name
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|fis_image_desc
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|fis_list
op_star
id|new_fl
comma
op_star
op_star
id|prev
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
dot
id|name
(braket
l_int|0
)braket
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|redboot_checksum
c_func
(paren
op_amp
id|buf
(braket
id|i
)braket
)paren
)paren
r_break
suffix:semicolon
id|new_fl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|fis_list
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|namelen
op_add_assign
id|strlen
c_func
(paren
id|buf
(braket
id|i
)braket
dot
id|name
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_fl
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|new_fl-&gt;img
op_assign
op_amp
id|buf
(braket
id|i
)braket
suffix:semicolon
id|buf
(braket
id|i
)braket
dot
id|flash_base
op_and_assign
id|master-&gt;size
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* I&squot;m sure the JFFS2 code has done me permanent damage.&n;&t;&t; * I now think the following is _normal_&n;&t;&t; */
id|prev
op_assign
op_amp
id|fl
suffix:semicolon
r_while
c_loop
(paren
op_star
id|prev
op_logical_and
(paren
op_star
id|prev
)paren
op_member_access_from_pointer
id|img-&gt;flash_base
OL
id|new_fl-&gt;img-&gt;flash_base
)paren
(brace
id|prev
op_assign
op_amp
(paren
op_star
id|prev
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
id|new_fl-&gt;next
op_assign
op_star
id|prev
suffix:semicolon
op_star
id|prev
op_assign
id|new_fl
suffix:semicolon
id|nrparts
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fl-&gt;img-&gt;flash_base
)paren
id|nrparts
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|tmp_fl
op_assign
id|fl
suffix:semicolon
id|tmp_fl-&gt;next
suffix:semicolon
id|tmp_fl
op_assign
id|tmp_fl-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tmp_fl-&gt;img-&gt;flash_base
op_plus
id|tmp_fl-&gt;img-&gt;size
op_plus
id|master-&gt;erasesize
OL
id|tmp_fl-&gt;next-&gt;img-&gt;flash_base
)paren
id|nrparts
op_increment
suffix:semicolon
)brace
id|parts
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|parts
)paren
op_star
id|nrparts
op_plus
id|namelen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parts
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|names
op_assign
(paren
r_char
op_star
)paren
op_amp
id|parts
(braket
id|nrparts
)braket
suffix:semicolon
id|memset
c_func
(paren
id|parts
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|parts
)paren
op_star
id|nrparts
op_plus
id|namelen
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;img-&gt;flash_base
)paren
(brace
id|parts
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;unallocated space&quot;
suffix:semicolon
id|parts
(braket
l_int|0
)braket
dot
id|size
op_assign
id|fl-&gt;img-&gt;flash_base
suffix:semicolon
id|parts
(braket
l_int|0
)braket
dot
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|nrparts
suffix:semicolon
id|i
op_increment
)paren
(brace
id|parts
(braket
id|i
)braket
dot
id|size
op_assign
id|fl-&gt;img-&gt;size
suffix:semicolon
id|parts
(braket
id|i
)braket
dot
id|offset
op_assign
id|fl-&gt;img-&gt;flash_base
suffix:semicolon
id|parts
(braket
id|i
)braket
dot
id|name
op_assign
id|names
suffix:semicolon
id|strcpy
c_func
(paren
id|names
comma
id|fl-&gt;img-&gt;name
)paren
suffix:semicolon
id|names
op_add_assign
id|strlen
c_func
(paren
id|names
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;next
op_logical_and
id|fl-&gt;img-&gt;flash_base
op_plus
id|fl-&gt;img-&gt;size
op_plus
id|master-&gt;erasesize
OL
id|fl-&gt;next-&gt;img-&gt;flash_base
)paren
(brace
id|i
op_increment
suffix:semicolon
id|parts
(braket
id|i
)braket
dot
id|offset
op_assign
id|parts
(braket
id|i
op_minus
l_int|1
)braket
dot
id|size
op_plus
id|parts
(braket
id|i
op_minus
l_int|1
)braket
dot
id|offset
suffix:semicolon
id|parts
(braket
id|i
)braket
dot
id|size
op_assign
id|fl-&gt;next-&gt;img-&gt;flash_base
op_minus
id|parts
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
id|parts
(braket
id|i
)braket
dot
id|name
op_assign
l_string|&quot;unallocated space&quot;
suffix:semicolon
)brace
id|tmp_fl
op_assign
id|fl
suffix:semicolon
id|fl
op_assign
id|fl-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|tmp_fl
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|nrparts
suffix:semicolon
op_star
id|pparts
op_assign
id|parts
suffix:semicolon
id|out
suffix:colon
r_while
c_loop
(paren
id|fl
)paren
(brace
r_struct
id|fis_list
op_star
id|old
op_assign
id|fl
suffix:semicolon
id|fl
op_assign
id|fl-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|parse_redboot_partitions
id|EXPORT_SYMBOL
c_func
(paren
id|parse_redboot_partitions
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat, Inc. - David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Parsing code for RedBoot Flash Image System (FIS) tables&quot;
)paren
suffix:semicolon
eof
