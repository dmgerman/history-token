multiline_comment|/*&n; * NV-RAM memory access on autcpu12 &n; * (C) 2002 Thomas Gleixner (gleixner@autronix.de)&n; *&n; * $Id: autcpu12-nvram.c,v 1.8 2004/11/04 13:24:14 gleixner Exp $ &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/autcpu12.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|variable|sram_mtd
r_static
r_struct
id|mtd_info
op_star
id|sram_mtd
suffix:semicolon
DECL|variable|autcpu12_sram_map
r_struct
id|map_info
id|autcpu12_sram_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SRAM&quot;
comma
dot
id|size
op_assign
l_int|32768
comma
dot
id|bankwidth
op_assign
l_int|4
comma
dot
id|phys
op_assign
l_int|0x12000000
comma
)brace
suffix:semicolon
DECL|function|init_autcpu12_sram
r_static
r_int
id|__init
id|init_autcpu12_sram
(paren
r_void
)paren
(brace
r_int
id|err
comma
id|save0
comma
id|save1
suffix:semicolon
id|autcpu12_sram_map.virt
op_assign
id|ioremap
c_func
(paren
l_int|0x12000000
comma
id|SZ_128K
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|autcpu12_sram_map.virt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to ioremap autcpu12 NV-RAM space&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|simple_map_init
c_func
(paren
op_amp
id|autcpu_sram_map
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Check for 32K/128K &n;&t; * read ofs 0 &n;&t; * read ofs 0x10000 &n;&t; * Write complement to ofs 0x100000&n;&t; * Read&t;and check result on ofs 0x0&n;&t; * Restore contents&n;&t; */
id|save0
op_assign
id|map_read32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
l_int|0
)paren
suffix:semicolon
id|save1
op_assign
id|map_read32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
l_int|0x10000
)paren
suffix:semicolon
id|map_write32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
op_complement
id|save0
comma
l_int|0x10000
)paren
suffix:semicolon
multiline_comment|/* if we find this pattern on 0x0, we have 32K size &n;&t; * restore contents and exit&n;&t; */
r_if
c_cond
(paren
id|map_read32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
l_int|0
)paren
op_ne
id|save0
)paren
(brace
id|map_write32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
id|save0
comma
l_int|0x0
)paren
suffix:semicolon
r_goto
id|map
suffix:semicolon
)brace
multiline_comment|/* We have a 128K found, restore 0x10000 and set size&n;&t; * to 128K&n;&t; */
id|map_write32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
id|save1
comma
l_int|0x10000
)paren
suffix:semicolon
id|autcpu12_sram_map.size
op_assign
id|SZ_128K
suffix:semicolon
id|map
suffix:colon
id|sram_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;map_ram&quot;
comma
op_amp
id|autcpu12_sram_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sram_mtd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NV-RAM probe failed&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|out_ioremap
suffix:semicolon
)brace
id|sram_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|sram_mtd-&gt;erasesize
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|add_mtd_device
c_func
(paren
id|sram_mtd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NV-RAM device addition failed&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_probe
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;NV-RAM device size %ldKiB registered on AUTCPU12&bslash;n&quot;
comma
id|autcpu12_sram_map.size
op_div
id|SZ_1K
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_probe
suffix:colon
id|map_destroy
c_func
(paren
id|sram_mtd
)paren
suffix:semicolon
id|sram_mtd
op_assign
l_int|0
suffix:semicolon
id|out_ioremap
suffix:colon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|autcpu12_sram_map.virt
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cleanup_autcpu12_maps
r_static
r_void
id|__exit
id|cleanup_autcpu12_maps
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sram_mtd
)paren
(brace
id|del_mtd_device
c_func
(paren
id|sram_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|sram_mtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|autcpu12_sram_map.virt
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_autcpu12_sram
id|module_init
c_func
(paren
id|init_autcpu12_sram
)paren
suffix:semicolon
DECL|variable|cleanup_autcpu12_maps
id|module_exit
c_func
(paren
id|cleanup_autcpu12_maps
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Thomas Gleixner&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;autcpu12 NV-RAM map driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
