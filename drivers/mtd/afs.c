multiline_comment|/*======================================================================&n;&n;    drivers/mtd/afs.c: ARM Flash Layout/Partitioning&n;  &n;    Copyright (C) 2000 ARM Limited&n;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;  &n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;  &n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;  &n;   This is access code for flashes using ARM&squot;s flash partitioning &n;   standards.&n;&n;   $Id: afs.c,v 1.12 2003/06/13 15:31:06 rmk Exp $&n;&n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|struct|footer_struct
r_struct
id|footer_struct
(brace
DECL|member|image_info_base
id|u32
id|image_info_base
suffix:semicolon
multiline_comment|/* Address of first word of ImageFooter  */
DECL|member|image_start
id|u32
id|image_start
suffix:semicolon
multiline_comment|/* Start of area reserved by this footer */
DECL|member|signature
id|u32
id|signature
suffix:semicolon
multiline_comment|/* &squot;Magic&squot; number proves it&squot;s a footer   */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* Area type: ARM Image, SIB, customer   */
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
multiline_comment|/* Just this structure                   */
)brace
suffix:semicolon
DECL|struct|image_info_struct
r_struct
id|image_info_struct
(brace
DECL|member|bootFlags
id|u32
id|bootFlags
suffix:semicolon
multiline_comment|/* Boot flags, compression etc.          */
DECL|member|imageNumber
id|u32
id|imageNumber
suffix:semicolon
multiline_comment|/* Unique number, selects for boot etc.  */
DECL|member|loadAddress
id|u32
id|loadAddress
suffix:semicolon
multiline_comment|/* Address program should be loaded to   */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* Actual size of image                  */
DECL|member|address
id|u32
id|address
suffix:semicolon
multiline_comment|/* Image is executed from here           */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Null terminated                       */
DECL|member|headerBase
id|u32
id|headerBase
suffix:semicolon
multiline_comment|/* Flash Address of any stripped header  */
DECL|member|header_length
id|u32
id|header_length
suffix:semicolon
multiline_comment|/* Length of header in memory            */
DECL|member|headerType
id|u32
id|headerType
suffix:semicolon
multiline_comment|/* AIF, RLF, s-record etc.               */
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
multiline_comment|/* Image checksum (inc. this struct)     */
)brace
suffix:semicolon
r_static
r_int
DECL|function|afs_read_footer
id|afs_read_footer
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_int
op_star
id|img_start
comma
id|u_int
op_star
id|iis_start
comma
id|u_int
id|off
comma
id|u_int
id|mask
)paren
(brace
r_struct
id|footer_struct
id|fs
suffix:semicolon
id|u_int
id|ptr
op_assign
id|off
op_plus
id|mtd-&gt;erasesize
op_minus
r_sizeof
(paren
id|fs
)paren
suffix:semicolon
r_int
id|sz
suffix:semicolon
r_int
id|ret
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
id|ptr
comma
r_sizeof
(paren
id|fs
)paren
comma
op_amp
id|sz
comma
(paren
id|u_char
op_star
)paren
op_amp
id|fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
id|sz
op_ne
r_sizeof
(paren
id|fs
)paren
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFS: mtd read failed at 0x%x: %d&bslash;n&quot;
comma
id|ptr
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Does it contain the magic number?&n;&t; */
r_if
c_cond
(paren
id|fs.signature
op_ne
l_int|0xa0ffff9f
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t touch the SIB.&n;&t; */
r_if
c_cond
(paren
id|fs.type
op_eq
l_int|2
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
op_star
id|iis_start
op_assign
id|fs.image_info_base
op_amp
id|mask
suffix:semicolon
op_star
id|img_start
op_assign
id|fs.image_start
op_amp
id|mask
suffix:semicolon
multiline_comment|/*&n;&t; * Check the image info base.  This can not&n;&t; * be located after the footer structure.&n;&t; */
r_if
c_cond
(paren
op_star
id|iis_start
op_ge
id|ptr
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Check the start of this image.  The image&n;&t; * data can not be located after this block.&n;&t; */
r_if
c_cond
(paren
op_star
id|img_start
OG
id|off
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|afs_read_iis
id|afs_read_iis
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|image_info_struct
op_star
id|iis
comma
id|u_int
id|ptr
)paren
(brace
r_int
id|sz
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|memset
c_func
(paren
id|iis
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|iis
)paren
)paren
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
id|ptr
comma
r_sizeof
(paren
op_star
id|iis
)paren
comma
op_amp
id|sz
comma
(paren
id|u_char
op_star
)paren
id|iis
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
id|sz
op_ne
r_sizeof
(paren
op_star
id|iis
)paren
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFS: mtd read failed at 0x%x: %d&bslash;n&quot;
comma
id|ptr
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|parse_afs_partitions
r_static
r_int
id|parse_afs_partitions
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|mtd_partition
op_star
op_star
id|pparts
comma
r_int
r_int
id|origin
)paren
(brace
r_struct
id|mtd_partition
op_star
id|parts
suffix:semicolon
id|u_int
id|mask
comma
id|off
comma
id|idx
comma
id|sz
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
multiline_comment|/*&n;&t; * This is the address mask; we use this to mask off out of&n;&t; * range address bits.&n;&t; */
id|mask
op_assign
id|mtd-&gt;size
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * First, calculate the size of the array we need for the&n;&t; * partition information.  We include in this the size of&n;&t; * the strings.&n;&t; */
r_for
c_loop
(paren
id|idx
op_assign
id|off
op_assign
id|sz
op_assign
l_int|0
suffix:semicolon
id|off
OL
id|mtd-&gt;size
suffix:semicolon
id|off
op_add_assign
id|mtd-&gt;erasesize
)paren
(brace
r_struct
id|image_info_struct
id|iis
suffix:semicolon
id|u_int
id|iis_ptr
comma
id|img_ptr
suffix:semicolon
id|ret
op_assign
id|afs_read_footer
c_func
(paren
id|mtd
comma
op_amp
id|img_ptr
comma
op_amp
id|iis_ptr
comma
id|off
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|afs_read_iis
c_func
(paren
id|mtd
comma
op_amp
id|iis
comma
id|iis_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|sz
op_add_assign
r_sizeof
(paren
r_struct
id|mtd_partition
)paren
suffix:semicolon
id|sz
op_add_assign
id|strlen
c_func
(paren
id|iis.name
)paren
op_plus
l_int|1
suffix:semicolon
id|idx
op_add_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sz
)paren
r_return
id|ret
suffix:semicolon
id|parts
op_assign
id|kmalloc
c_func
(paren
id|sz
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|parts
comma
l_int|0
comma
id|sz
)paren
suffix:semicolon
id|str
op_assign
(paren
r_char
op_star
)paren
(paren
id|parts
op_plus
id|idx
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Identify the partitions&n;&t; */
r_for
c_loop
(paren
id|idx
op_assign
id|off
op_assign
l_int|0
suffix:semicolon
id|off
OL
id|mtd-&gt;size
suffix:semicolon
id|off
op_add_assign
id|mtd-&gt;erasesize
)paren
(brace
r_struct
id|image_info_struct
id|iis
suffix:semicolon
id|u_int
id|iis_ptr
comma
id|img_ptr
comma
id|size
suffix:semicolon
multiline_comment|/* Read the footer. */
id|ret
op_assign
id|afs_read_footer
c_func
(paren
id|mtd
comma
op_amp
id|img_ptr
comma
op_amp
id|iis_ptr
comma
id|off
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* Read the image info block */
id|ret
op_assign
id|afs_read_iis
c_func
(paren
id|mtd
comma
op_amp
id|iis
comma
id|iis_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|strcpy
c_func
(paren
id|str
comma
id|iis.name
)paren
suffix:semicolon
id|size
op_assign
id|mtd-&gt;erasesize
op_plus
id|off
op_minus
id|img_ptr
suffix:semicolon
multiline_comment|/*&n;&t;&t; * In order to support JFFS2 partitions on this layout,&n;&t;&t; * we must lie to MTD about the real size of JFFS2&n;&t;&t; * partitions; this ensures that the AFS flash footer&n;&t;&t; * won&squot;t be erased by JFFS2.  Please ensure that your&n;&t;&t; * JFFS2 partitions are given image numbers between&n;&t;&t; * 1000 and 2000 inclusive.&n;&t;&t; */
r_if
c_cond
(paren
id|iis.imageNumber
op_ge
l_int|1000
op_logical_and
id|iis.imageNumber
OL
l_int|2000
)paren
id|size
op_sub_assign
id|mtd-&gt;erasesize
suffix:semicolon
id|parts
(braket
id|idx
)braket
dot
id|name
op_assign
id|str
suffix:semicolon
id|parts
(braket
id|idx
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|parts
(braket
id|idx
)braket
dot
id|offset
op_assign
id|img_ptr
suffix:semicolon
id|parts
(braket
id|idx
)braket
dot
id|mask_flags
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  mtd%d: at 0x%08x, %5dKB, %8u, %s&bslash;n&quot;
comma
id|idx
comma
id|img_ptr
comma
id|parts
(braket
id|idx
)braket
dot
id|size
op_div
l_int|1024
comma
id|iis.imageNumber
comma
id|str
)paren
suffix:semicolon
id|idx
op_add_assign
l_int|1
suffix:semicolon
id|str
op_assign
id|str
op_plus
id|strlen
c_func
(paren
id|iis.name
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|idx
)paren
(brace
id|kfree
c_func
(paren
id|parts
)paren
suffix:semicolon
id|parts
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|pparts
op_assign
id|parts
suffix:semicolon
r_return
id|idx
ques
c_cond
id|idx
suffix:colon
id|ret
suffix:semicolon
)brace
DECL|variable|afs_parser
r_static
r_struct
id|mtd_part_parser
id|afs_parser
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|parse_fn
op_assign
id|parse_afs_partitions
comma
dot
id|name
op_assign
l_string|&quot;afs&quot;
comma
)brace
suffix:semicolon
DECL|function|afs_parser_init
r_static
r_int
id|__init
id|afs_parser_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_mtd_parser
c_func
(paren
op_amp
id|afs_parser
)paren
suffix:semicolon
)brace
DECL|function|afs_parser_exit
r_static
r_void
id|__exit
id|afs_parser_exit
c_func
(paren
r_void
)paren
(brace
id|deregister_mtd_parser
c_func
(paren
op_amp
id|afs_parser
)paren
suffix:semicolon
)brace
DECL|variable|afs_parser_init
id|module_init
c_func
(paren
id|afs_parser_init
)paren
suffix:semicolon
DECL|variable|afs_parser_exit
id|module_exit
c_func
(paren
id|afs_parser_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;ARM Ltd&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ARM Firmware Suite partition parser&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
