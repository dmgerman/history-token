multiline_comment|/*&n; * Flash device on Lasat 100 and 200 boards&n; *&n; * (C) 2002 Brian Murphy &lt;brian@murphy.dk&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License version&n; * 2 as published by the Free Software Foundation.&n; *&n; * $Id: lasat.c,v 1.9 2004/11/04 13:24:15 gleixner Exp $&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/lasat/lasat.h&gt;
DECL|variable|lasat_mtd
r_static
r_struct
id|mtd_info
op_star
id|lasat_mtd
suffix:semicolon
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
id|LASAT_MTD_LAST
)braket
suffix:semicolon
DECL|variable|lasat_mtd_partnames
r_static
r_char
op_star
id|lasat_mtd_partnames
(braket
)braket
op_assign
(brace
l_string|&quot;Bootloader&quot;
comma
l_string|&quot;Service&quot;
comma
l_string|&quot;Normal&quot;
comma
l_string|&quot;Filesystem&quot;
comma
l_string|&quot;Config&quot;
)brace
suffix:semicolon
DECL|function|lasat_set_vpp
r_static
r_void
id|lasat_set_vpp
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
id|vpp
)paren
(brace
r_if
c_cond
(paren
id|vpp
)paren
op_star
id|lasat_misc-&gt;flash_wp_reg
op_or_assign
l_int|1
op_lshift
id|lasat_misc-&gt;flash_wp_bit
suffix:semicolon
r_else
op_star
id|lasat_misc-&gt;flash_wp_reg
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|lasat_misc-&gt;flash_wp_bit
)paren
suffix:semicolon
)brace
DECL|variable|lasat_map
r_static
r_struct
id|map_info
id|lasat_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LASAT flash&quot;
comma
dot
id|bankwidth
op_assign
l_int|4
comma
dot
id|set_vpp
op_assign
id|lasat_set_vpp
)brace
suffix:semicolon
DECL|function|init_lasat
r_static
r_int
id|__init
id|init_lasat
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* since we use AMD chips and set_vpp is not implimented&n;&t; * for these (yet) we still have to permanently enable flash write */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Unprotecting flash&bslash;n&quot;
)paren
suffix:semicolon
id|ENABLE_VPP
c_func
(paren
(paren
op_amp
id|lasat_map
)paren
)paren
suffix:semicolon
id|lasat_map.phys
op_assign
id|lasat_flash_partition_start
c_func
(paren
id|LASAT_MTD_BOOTLOADER
)paren
suffix:semicolon
id|lasat_map.virt
op_assign
id|ioremap_nocache
c_func
(paren
id|lasat_map.phys
comma
id|lasat_board_info.li_flash_size
)paren
suffix:semicolon
id|lasat_map.size
op_assign
id|lasat_board_info.li_flash_size
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|lasat_map
)paren
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
id|LASAT_MTD_LAST
suffix:semicolon
id|i
op_increment
)paren
id|partition_info
(braket
id|i
)braket
dot
id|name
op_assign
id|lasat_mtd_partnames
(braket
id|i
)braket
suffix:semicolon
id|lasat_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|lasat_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lasat_mtd
)paren
id|lasat_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;jedec_probe&quot;
comma
op_amp
id|lasat_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lasat_mtd
)paren
(brace
id|u32
id|size
comma
id|offset
op_assign
l_int|0
suffix:semicolon
id|lasat_mtd-&gt;owner
op_assign
id|THIS_MODULE
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
id|LASAT_MTD_LAST
suffix:semicolon
id|i
op_increment
)paren
(brace
id|size
op_assign
id|lasat_flash_partition_size
c_func
(paren
id|i
)paren
suffix:semicolon
id|partition_info
(braket
id|i
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|partition_info
(braket
id|i
)braket
dot
id|offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
id|size
suffix:semicolon
)brace
id|add_mtd_partitions
c_func
(paren
id|lasat_mtd
comma
id|partition_info
comma
id|LASAT_MTD_LAST
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|cleanup_lasat
r_static
r_void
id|__exit
id|cleanup_lasat
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|lasat_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|lasat_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|lasat_mtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lasat_map.virt
)paren
(brace
id|lasat_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|init_lasat
id|module_init
c_func
(paren
id|init_lasat
)paren
suffix:semicolon
DECL|variable|cleanup_lasat
id|module_exit
c_func
(paren
id|cleanup_lasat
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
l_string|&quot;Brian Murphy &lt;brian@murphy.dk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Lasat Safepipe/Masquerade MTD map driver&quot;
)paren
suffix:semicolon
eof
