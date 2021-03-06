multiline_comment|/*&n; * Mapping for Ocotea user flash&n; *&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * Copyright 2002-2004 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ibm44x.h&gt;
macro_line|#include &lt;platforms/4xx/ocotea.h&gt;
DECL|variable|flash
r_static
r_struct
id|mtd_info
op_star
id|flash
suffix:semicolon
DECL|variable|ocotea_small_map
r_static
r_struct
id|map_info
id|ocotea_small_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Ocotea small flash&quot;
comma
dot
id|size
op_assign
id|OCOTEA_SMALL_FLASH_SIZE
comma
dot
id|buswidth
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|ocotea_large_map
r_static
r_struct
id|map_info
id|ocotea_large_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Ocotea large flash&quot;
comma
dot
id|size
op_assign
id|OCOTEA_LARGE_FLASH_SIZE
comma
dot
id|buswidth
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|ocotea_small_partitions
r_static
r_struct
id|mtd_partition
id|ocotea_small_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;pibs&quot;
comma
dot
id|offset
op_assign
l_int|0x0
comma
dot
id|size
op_assign
l_int|0x100000
comma
)brace
)brace
suffix:semicolon
DECL|variable|ocotea_large_partitions
r_static
r_struct
id|mtd_partition
id|ocotea_large_partitions
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;fs&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|0x300000
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;firmware&quot;
comma
dot
id|offset
op_assign
l_int|0x300000
comma
dot
id|size
op_assign
l_int|0x100000
comma
)brace
)brace
suffix:semicolon
DECL|macro|NB_OF
mdefine_line|#define NB_OF(x)  (sizeof(x)/sizeof(x[0]))
DECL|function|init_ocotea
r_int
id|__init
id|init_ocotea
c_func
(paren
r_void
)paren
(brace
id|u8
id|fpga0_reg
suffix:semicolon
id|u8
op_star
id|fpga0_adr
suffix:semicolon
r_int
r_int
r_int
id|small_flash_base
comma
id|large_flash_base
suffix:semicolon
id|fpga0_adr
op_assign
id|ioremap64
c_func
(paren
id|OCOTEA_FPGA_ADDR
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpga0_adr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|fpga0_reg
op_assign
id|readb
c_func
(paren
(paren
r_int
r_int
)paren
id|fpga0_adr
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|fpga0_adr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OCOTEA_BOOT_LARGE_FLASH
c_func
(paren
id|fpga0_reg
)paren
)paren
(brace
id|small_flash_base
op_assign
id|OCOTEA_SMALL_FLASH_HIGH
suffix:semicolon
id|large_flash_base
op_assign
id|OCOTEA_LARGE_FLASH_LOW
suffix:semicolon
)brace
r_else
(brace
id|small_flash_base
op_assign
id|OCOTEA_SMALL_FLASH_LOW
suffix:semicolon
id|large_flash_base
op_assign
id|OCOTEA_LARGE_FLASH_HIGH
suffix:semicolon
)brace
id|ocotea_small_map.phys
op_assign
id|small_flash_base
suffix:semicolon
id|ocotea_small_map.virt
op_assign
id|ioremap64
c_func
(paren
id|small_flash_base
comma
id|ocotea_small_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ocotea_small_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap flash&bslash;n&quot;
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
op_amp
id|ocotea_small_map
)paren
suffix:semicolon
id|flash
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_rom&quot;
comma
op_amp
id|ocotea_small_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flash
)paren
(brace
id|flash-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|flash
comma
id|ocotea_small_partitions
comma
id|NB_OF
c_func
(paren
id|ocotea_small_partitions
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;map probe failed for flash&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|ocotea_large_map.phys
op_assign
id|large_flash_base
suffix:semicolon
id|ocotea_large_map.virt
op_assign
id|ioremap64
c_func
(paren
id|large_flash_base
comma
id|ocotea_large_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ocotea_large_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap flash&bslash;n&quot;
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
op_amp
id|ocotea_large_map
)paren
suffix:semicolon
id|flash
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|ocotea_large_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flash
)paren
(brace
id|flash-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|flash
comma
id|ocotea_large_partitions
comma
id|NB_OF
c_func
(paren
id|ocotea_large_partitions
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;map probe failed for flash&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_ocotea
r_static
r_void
id|__exit
id|cleanup_ocotea
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|flash
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|flash
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|flash
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ocotea_small_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocotea_small_map.virt
)paren
suffix:semicolon
id|ocotea_small_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ocotea_large_map.virt
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ocotea_large_map.virt
)paren
suffix:semicolon
id|ocotea_large_map.virt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|init_ocotea
id|module_init
c_func
(paren
id|init_ocotea
)paren
suffix:semicolon
DECL|variable|cleanup_ocotea
id|module_exit
c_func
(paren
id|cleanup_ocotea
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
l_string|&quot;Matt Porter &lt;mporter@kernel.crashing.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map and partitions for IBM 440GX Ocotea boards&quot;
)paren
suffix:semicolon
eof
