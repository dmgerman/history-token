multiline_comment|/*&n; * NV-RAM memory access on autcpu12 &n; * (C) 2002 Thomas Gleixner (gleixner@autronix.de)&n; *&n; * $Id: autcpu12-nvram.c,v 1.1 2002/02/22 09:30:24 gleixner Exp $ &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/autcpu12.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|function|autcpu12_read8
id|__u8
id|autcpu12_read8
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
id|__raw_readb
c_func
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_read16
id|__u16
id|autcpu12_read16
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
id|__raw_readw
c_func
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_read32
id|__u32
id|autcpu12_read32
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
id|__raw_readl
c_func
(paren
id|map-&gt;map_priv_1
op_plus
id|ofs
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_write8
r_void
id|autcpu12_write8
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
id|__raw_writeb
c_func
(paren
id|d
comma
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_write16
r_void
id|autcpu12_write16
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
id|__raw_writew
c_func
(paren
id|d
comma
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_write32
r_void
id|autcpu12_write32
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
id|__raw_writel
c_func
(paren
id|d
comma
id|map-&gt;map_priv_1
op_plus
id|adr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_copy_from
r_void
id|autcpu12_copy_from
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
id|memcpy_fromio
c_func
(paren
id|to
comma
id|map-&gt;map_priv_1
op_plus
id|from
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|autcpu12_copy_to
r_void
id|autcpu12_copy_to
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
r_while
c_loop
(paren
id|len
)paren
(brace
id|__raw_writeb
c_func
(paren
op_star
(paren
r_int
r_char
op_star
)paren
id|from
comma
id|map-&gt;map_priv_1
op_plus
id|to
)paren
suffix:semicolon
id|from
op_increment
suffix:semicolon
id|to
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
)brace
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
id|name
suffix:colon
l_string|&quot;SRAM&quot;
comma
id|size
suffix:colon
l_int|32768
comma
id|buswidth
suffix:colon
l_int|8
comma
id|read8
suffix:colon
id|autcpu12_read8
comma
id|read16
suffix:colon
id|autcpu12_read16
comma
id|read32
suffix:colon
id|autcpu12_read32
comma
id|copy_from
suffix:colon
id|autcpu12_copy_from
comma
id|write8
suffix:colon
id|autcpu12_write8
comma
id|write16
suffix:colon
id|autcpu12_write16
comma
id|write32
suffix:colon
id|autcpu12_write32
comma
id|copy_to
suffix:colon
id|autcpu12_copy_to
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
id|autcpu12_sram_map.map_priv_1
op_assign
(paren
r_int
r_int
)paren
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
id|autcpu12_sram_map.map_priv_1
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
multiline_comment|/* &n;&t; * Check for 32K/128K &n;&t; * read ofs 0 &n;&t; * read ofs 0x10000 &n;&t; * Write complement to ofs 0x100000&n;&t; * Read&t;and check result on ofs 0x0&n;&t; * Restore contents&n;&t; */
id|save0
op_assign
id|autcpu12_read32
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
id|autcpu12_read32
c_func
(paren
op_amp
id|autcpu12_sram_map
comma
l_int|0x10000
)paren
suffix:semicolon
id|autcpu12_write32
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
id|autcpu12_read32
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
id|autcpu12_write32
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
id|autcpu12_write32
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
id|sram_mtd-&gt;module
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
l_string|&quot;NV-RAM device size %ldK registered on AUTCPU12&bslash;n&quot;
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
id|autcpu12_sram_map.map_priv_1
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
id|autcpu12_sram_map.map_priv_1
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
