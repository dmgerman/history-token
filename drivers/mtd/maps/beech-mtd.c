multiline_comment|/*&n; * $Id: beech-mtd.c,v 1.10 2004/11/04 13:24:14 gleixner Exp $&n; * &n; * drivers/mtd/maps/beech-mtd.c MTD mappings and partition tables for &n; *                              IBM 405LP Beech boards.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Copyright (C) 2002, International Business Machines Corporation&n; * All Rights Reserved.&n; *&n; * Bishop Brock&n; * IBM Research, Austin Center for Low-Power Computing&n; * bcbrock@us.ibm.com&n; * March 2002&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME     &quot;Beech Linux Flash&quot;
DECL|macro|PADDR
mdefine_line|#define PADDR    BEECH_BIGFLASH_PADDR
DECL|macro|SIZE
mdefine_line|#define SIZE     BEECH_BIGFLASH_SIZE
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH 1
multiline_comment|/* Flash memories on these boards are memory resources, accessed big-endian. */
DECL|variable|beech_mtd_map
r_static
r_struct
id|map_info
id|beech_mtd_map
op_assign
(brace
dot
id|name
op_assign
id|NAME
comma
dot
id|size
op_assign
id|SIZE
comma
dot
id|bankwidth
op_assign
id|BUSWIDTH
comma
dot
id|phys
op_assign
id|PADDR
)brace
suffix:semicolon
DECL|variable|beech_mtd
r_static
r_struct
id|mtd_info
op_star
id|beech_mtd
suffix:semicolon
DECL|variable|beech_partitions
r_static
r_struct
id|mtd_partition
id|beech_partitions
(braket
l_int|2
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;Linux Kernel&quot;
comma
dot
id|size
op_assign
id|BEECH_KERNEL_SIZE
comma
dot
id|offset
op_assign
id|BEECH_KERNEL_OFFSET
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Free Area&quot;
comma
dot
id|size
op_assign
id|BEECH_FREE_AREA_SIZE
comma
dot
id|offset
op_assign
id|BEECH_FREE_AREA_OFFSET
)brace
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|init_beech_mtd
id|init_beech_mtd
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: 0x%08x at 0x%08x&bslash;n&quot;
comma
id|NAME
comma
id|SIZE
comma
id|PADDR
)paren
suffix:semicolon
id|beech_mtd_map.virt
op_assign
id|ioremap
c_func
(paren
id|PADDR
comma
id|SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|beech_mtd_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: failed to ioremap 0x%x&bslash;n&quot;
comma
id|NAME
comma
id|PADDR
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
id|beech_mtd_map
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: probing %d-bit flash bus&bslash;n&quot;
comma
id|NAME
comma
id|BUSWIDTH
op_star
l_int|8
)paren
suffix:semicolon
id|beech_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|beech_mtd_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|beech_mtd
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|beech_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
id|add_mtd_partitions
c_func
(paren
id|beech_mtd
comma
id|beech_partitions
comma
l_int|2
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cleanup_beech_mtd
id|cleanup_beech_mtd
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|beech_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|beech_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|beech_mtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|beech_mtd_map.virt
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_beech_mtd
id|module_init
c_func
(paren
id|init_beech_mtd
)paren
suffix:semicolon
DECL|variable|cleanup_beech_mtd
id|module_exit
c_func
(paren
id|cleanup_beech_mtd
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
l_string|&quot;Bishop Brock &lt;bcbrock@us.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map and partitions for IBM 405LP Beech boards&quot;
)paren
suffix:semicolon
eof
