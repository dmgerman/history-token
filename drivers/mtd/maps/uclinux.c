multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;uclinux.c -- generic memory mapped MTD driver for uclinux&n; *&n; *&t;(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)&n; *&n; * &t;$Id: uclinux.c,v 1.10 2005/01/05 18:05:13 dwmw2 Exp $&n; */
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
id|map-&gt;virt
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
id|mapp-&gt;phys
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
id|mapp-&gt;bankwidth
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
id|mapp-&gt;virt
op_assign
id|ioremap_nocache
c_func
(paren
id|mapp-&gt;phys
comma
id|mapp-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapp-&gt;virt
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
id|simple_map_init
c_func
(paren
id|mapp
)paren
suffix:semicolon
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
id|mapp-&gt;virt
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|mtd-&gt;owner
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
id|uclinux_ram_map.virt
)paren
suffix:semicolon
id|uclinux_ram_map.virt
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
