multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;uclinux.c -- generic memory mapped MTD driver for uclinux&n; *&n; *&t;(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/****************************************************************************/
DECL|function|uclinux_read8
id|__u8
id|uclinux_read8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
(paren
id|__u8
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
)paren
suffix:semicolon
)brace
DECL|function|uclinux_read16
id|__u16
id|uclinux_read16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
)paren
suffix:semicolon
)brace
DECL|function|uclinux_read32
id|__u32
id|uclinux_read32
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|ofs
)paren
(brace
r_return
op_star
(paren
(paren
id|__u32
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
)paren
suffix:semicolon
)brace
DECL|function|uclinux_copy_from
r_void
id|uclinux_copy_from
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_void
op_star
id|to
comma
r_int
r_int
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy
c_func
(paren
id|to
comma
(paren
r_void
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|from
)paren
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|uclinux_write8
r_void
id|uclinux_write8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u8
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
(paren
id|__u8
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|uclinux_write16
r_void
id|uclinux_write16
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u16
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
(paren
id|__u16
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|uclinux_write32
r_void
id|uclinux_write32
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|d
comma
r_int
r_int
id|adr
)paren
(brace
op_star
(paren
(paren
id|__u32
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|uclinux_copy_to
r_void
id|uclinux_copy_to
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|to
comma
r_const
r_void
op_star
id|from
comma
id|ssize_t
id|len
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
id|to
)paren
comma
id|from
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************/
DECL|variable|uclinux_ram_map
r_struct
id|map_info
id|uclinux_ram_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;RAM&quot;
comma
dot
id|read8
op_assign
id|uclinux_read8
comma
dot
id|read16
op_assign
id|uclinux_read16
comma
dot
id|read32
op_assign
id|uclinux_read32
comma
dot
id|copy_from
op_assign
id|uclinux_copy_from
comma
dot
id|write8
op_assign
id|uclinux_write8
comma
dot
id|write16
op_assign
id|uclinux_write16
comma
dot
id|write32
op_assign
id|uclinux_write32
comma
dot
id|copy_to
op_assign
id|uclinux_copy_to
comma
)brace
suffix:semicolon
DECL|variable|uclinux_ram_mtdinfo
r_struct
id|mtd_info
op_star
id|uclinux_ram_mtdinfo
suffix:semicolon
multiline_comment|/****************************************************************************/
DECL|variable|uclinux_romfs
r_struct
id|mtd_partition
id|uclinux_romfs
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;ROMfs&quot;
comma
dot
id|offset
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define&t;NUM_PARTITIONS&t;(sizeof(uclinux_romfs) / sizeof(uclinux_romfs[0]))
multiline_comment|/****************************************************************************/
DECL|function|uclinux_point
r_int
id|uclinux_point
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
id|u_char
op_star
op_star
id|mtdbuf
)paren
(brace
r_struct
id|map_info
op_star
id|map
op_assign
(paren
r_struct
id|map_info
op_star
)paren
id|mtd-&gt;priv
suffix:semicolon
op_star
id|mtdbuf
op_assign
(paren
id|u_char
op_star
)paren
(paren
id|map-&gt;map_priv_1
op_plus
(paren
(paren
r_int
)paren
id|from
)paren
)paren
suffix:semicolon
op_star
id|retlen
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************************/
DECL|function|uclinux_mtd_init
r_int
id|__init
id|uclinux_mtd_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
r_struct
id|map_info
op_star
id|mapp
suffix:semicolon
r_extern
r_char
id|_ebss
suffix:semicolon
id|mapp
op_assign
op_amp
id|uclinux_ram_map
suffix:semicolon
id|mapp-&gt;map_priv_2
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_ebss
suffix:semicolon
id|mapp-&gt;size
op_assign
id|PAGE_ALIGN
c_func
(paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
(paren
op_amp
id|_ebss
)paren
op_plus
l_int|8
)paren
)paren
)paren
suffix:semicolon
id|mapp-&gt;buswidth
op_assign
l_int|4
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;uclinux[mtd]: RAM probe address=0x%x size=0x%x&bslash;n&quot;
comma
(paren
r_int
)paren
id|mapp-&gt;map_priv_2
comma
(paren
r_int
)paren
id|mapp-&gt;size
)paren
suffix:semicolon
id|mapp-&gt;map_priv_1
op_assign
(paren
r_int
r_int
)paren
id|ioremap_nocache
c_func
(paren
id|mapp-&gt;map_priv_2
comma
id|mapp-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapp-&gt;map_priv_1
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;uclinux[mtd]: ioremap_nocache() failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_ram&quot;
comma
id|mapp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;uclinux[mtd]: failed to find a mapping?&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|mapp-&gt;map_priv_1
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mtd-&gt;module
op_assign
id|THIS_MODULE
suffix:semicolon
id|mtd-&gt;point
op_assign
id|uclinux_point
suffix:semicolon
id|mtd-&gt;priv
op_assign
id|mapp
suffix:semicolon
id|uclinux_ram_mtdinfo
op_assign
id|mtd
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mtd
comma
id|uclinux_romfs
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;uclinux[mtd]: set %s to be root filesystem&bslash;n&quot;
comma
id|uclinux_romfs
(braket
l_int|0
)braket
dot
id|name
)paren
suffix:semicolon
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|MTD_BLOCK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************************/
DECL|function|uclinux_mtd_cleanup
r_void
id|__exit
id|uclinux_mtd_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|uclinux_ram_mtdinfo
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|uclinux_ram_mtdinfo
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|uclinux_ram_mtdinfo
)paren
suffix:semicolon
id|uclinux_ram_mtdinfo
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uclinux_ram_map.map_priv_1
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|uclinux_ram_map.map_priv_1
)paren
suffix:semicolon
id|uclinux_ram_map.map_priv_1
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/****************************************************************************/
DECL|variable|uclinux_mtd_init
id|module_init
c_func
(paren
id|uclinux_mtd_init
)paren
suffix:semicolon
DECL|variable|uclinux_mtd_cleanup
id|module_exit
c_func
(paren
id|uclinux_mtd_cleanup
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
l_string|&quot;Greg Ungerer &lt;gerg@snapgear.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic RAM based MTD for uClinux&quot;
)paren
suffix:semicolon
multiline_comment|/****************************************************************************/
eof
