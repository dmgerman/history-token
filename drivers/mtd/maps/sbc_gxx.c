multiline_comment|/* sbc_gxx.c -- MTD map driver for Arcom Control Systems SBC-MediaGX,&n;                SBC-GXm and SBC-GX1 series boards.&n; &n;   Copyright (C) 2001 Arcom Control System Ltd&n; &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n; &n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n; &n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA&n;&n;   $Id: sbc_gxx.c,v 1.33 2004/11/28 09:40:40 dwmw2 Exp $&n;&n;The SBC-MediaGX / SBC-GXx has up to 16 MiB of &n;Intel StrataFlash (28F320/28F640) in x8 mode.  &n;&n;This driver uses the CFI probe and Intel Extended Command Set drivers.&n;&n;The flash is accessed as follows:&n;&n;   16 KiB memory window at 0xdc000-0xdffff&n;   &n;   Two IO address locations for paging&n;   &n;   0x258&n;       bit 0-7: address bit 14-21&n;   0x259&n;       bit 0-1: address bit 22-23&n;       bit 7:   0 - reset/powered down&n;                1 - device enabled&n;&n;The single flash device is divided into 3 partition which appear as &n;separate MTD devices.&n;&n;25/04/2001 AJL (Arcom)  Modified signon strings and partition sizes&n;                        (to support bzImages up to 638KiB-ish)&n;*/
singleline_comment|// Includes
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
singleline_comment|// Defines
singleline_comment|// - Hardware specific
DECL|macro|WINDOW_START
mdefine_line|#define WINDOW_START 0xdc000
multiline_comment|/* Number of bits in offset. */
DECL|macro|WINDOW_SHIFT
mdefine_line|#define WINDOW_SHIFT 14
DECL|macro|WINDOW_LENGTH
mdefine_line|#define WINDOW_LENGTH (1 &lt;&lt; WINDOW_SHIFT)
multiline_comment|/* The bits for the offset into the window. */
DECL|macro|WINDOW_MASK
mdefine_line|#define WINDOW_MASK (WINDOW_LENGTH-1)
DECL|macro|PAGE_IO
mdefine_line|#define PAGE_IO 0x258
DECL|macro|PAGE_IO_SIZE
mdefine_line|#define PAGE_IO_SIZE 2
multiline_comment|/* bit 7 of 0x259 must be 1 to enable device. */
DECL|macro|DEVICE_ENABLE
mdefine_line|#define DEVICE_ENABLE 0x8000
singleline_comment|// - Flash / Partition sizing
DECL|macro|MAX_SIZE_KiB
mdefine_line|#define MAX_SIZE_KiB             16384
DECL|macro|BOOT_PARTITION_SIZE_KiB
mdefine_line|#define BOOT_PARTITION_SIZE_KiB  768
DECL|macro|DATA_PARTITION_SIZE_KiB
mdefine_line|#define DATA_PARTITION_SIZE_KiB  1280
DECL|macro|APP_PARTITION_SIZE_KiB
mdefine_line|#define APP_PARTITION_SIZE_KiB   6144
singleline_comment|// Globals
DECL|variable|page_in_window
r_static
r_volatile
r_int
id|page_in_window
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// Current page in window.
DECL|variable|iomapadr
r_static
r_void
id|__iomem
op_star
id|iomapadr
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|sbc_gxx_spin
)paren
suffix:semicolon
multiline_comment|/* partition_info gives details on the logical partitions that the split the &n; * single flash device into. If the size if zero we use up to the end of the&n; * device. */
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS 3
DECL|function|sbc_gxx_page
r_static
r_inline
r_void
id|sbc_gxx_page
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
r_int
r_int
id|page
op_assign
id|ofs
op_rshift
id|WINDOW_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|page
op_ne
id|page_in_window
)paren
(brace
id|outw
c_func
(paren
id|page
op_or
id|DEVICE_ENABLE
comma
id|PAGE_IO
)paren
suffix:semicolon
id|page_in_window
op_assign
id|page
suffix:semicolon
)brace
)brace
DECL|function|sbc_gxx_read8
r_static
id|map_word
id|sbc_gxx_read8
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
id|map_word
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
id|sbc_gxx_page
c_func
(paren
id|map
comma
id|ofs
)paren
suffix:semicolon
id|ret.x
(braket
l_int|0
)braket
op_assign
id|readb
c_func
(paren
id|iomapadr
op_plus
(paren
id|ofs
op_amp
id|WINDOW_MASK
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sbc_gxx_copy_from
r_static
r_void
id|sbc_gxx_copy_from
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
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
r_int
id|thislen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
(paren
id|WINDOW_LENGTH
op_minus
(paren
id|from
op_amp
id|WINDOW_MASK
)paren
)paren
)paren
id|thislen
op_assign
id|WINDOW_LENGTH
op_minus
(paren
id|from
op_amp
id|WINDOW_MASK
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
id|sbc_gxx_page
c_func
(paren
id|map
comma
id|from
)paren
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|to
comma
id|iomapadr
op_plus
(paren
id|from
op_amp
id|WINDOW_MASK
)paren
comma
id|thislen
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
id|to
op_add_assign
id|thislen
suffix:semicolon
id|from
op_add_assign
id|thislen
suffix:semicolon
id|len
op_sub_assign
id|thislen
suffix:semicolon
)brace
)brace
DECL|function|sbc_gxx_write8
r_static
r_void
id|sbc_gxx_write8
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
id|map_word
id|d
comma
r_int
r_int
id|adr
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
id|sbc_gxx_page
c_func
(paren
id|map
comma
id|adr
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|d.x
(braket
l_int|0
)braket
comma
id|iomapadr
op_plus
(paren
id|adr
op_amp
id|WINDOW_MASK
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
)brace
DECL|function|sbc_gxx_copy_to
r_static
r_void
id|sbc_gxx_copy_to
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
r_int
r_int
id|thislen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
(paren
id|WINDOW_LENGTH
op_minus
(paren
id|to
op_amp
id|WINDOW_MASK
)paren
)paren
)paren
id|thislen
op_assign
id|WINDOW_LENGTH
op_minus
(paren
id|to
op_amp
id|WINDOW_MASK
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
id|sbc_gxx_page
c_func
(paren
id|map
comma
id|to
)paren
suffix:semicolon
id|memcpy_toio
c_func
(paren
id|iomapadr
op_plus
(paren
id|to
op_amp
id|WINDOW_MASK
)paren
comma
id|from
comma
id|thislen
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sbc_gxx_spin
)paren
suffix:semicolon
id|to
op_add_assign
id|thislen
suffix:semicolon
id|from
op_add_assign
id|thislen
suffix:semicolon
id|len
op_sub_assign
id|thislen
suffix:semicolon
)brace
)brace
DECL|variable|sbc_gxx_map
r_static
r_struct
id|map_info
id|sbc_gxx_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SBC-GXx flash&quot;
comma
dot
id|phys
op_assign
id|NO_XIP
comma
dot
id|size
op_assign
id|MAX_SIZE_KiB
op_star
l_int|1024
comma
multiline_comment|/* this must be set to a maximum possible amount&n;&t;&t;&t; of flash so the cfi probe routines find all&n;&t;&t;&t; the chips */
dot
id|bankwidth
op_assign
l_int|1
comma
dot
id|read
op_assign
id|sbc_gxx_read8
comma
dot
id|copy_from
op_assign
id|sbc_gxx_copy_from
comma
dot
id|write
op_assign
id|sbc_gxx_write8
comma
dot
id|copy_to
op_assign
id|sbc_gxx_copy_to
)brace
suffix:semicolon
multiline_comment|/* MTD device for all of the flash. */
DECL|variable|all_mtd
r_static
r_struct
id|mtd_info
op_star
id|all_mtd
suffix:semicolon
DECL|function|cleanup_sbc_gxx
r_static
r_void
id|cleanup_sbc_gxx
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|all_mtd
)paren
(brace
id|del_mtd_partitions
c_func
(paren
id|all_mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|all_mtd
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|iomapadr
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|PAGE_IO
comma
id|PAGE_IO_SIZE
)paren
suffix:semicolon
)brace
DECL|function|init_sbc_gxx
r_static
r_int
id|__init
id|init_sbc_gxx
c_func
(paren
r_void
)paren
(brace
id|iomapadr
op_assign
id|ioremap
c_func
(paren
id|WINDOW_START
comma
id|WINDOW_LENGTH
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iomapadr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to ioremap memory region&bslash;n&quot;
comma
id|sbc_gxx_map.name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|PAGE_IO
comma
id|PAGE_IO_SIZE
comma
l_string|&quot;SBC-GXx flash&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: IO ports 0x%x-0x%x in use&bslash;n&quot;
comma
id|sbc_gxx_map.name
comma
id|PAGE_IO
comma
id|PAGE_IO
op_plus
id|PAGE_IO_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|iomapadr
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: IO:0x%x-0x%x MEM:0x%x-0x%x&bslash;n&quot;
comma
id|sbc_gxx_map.name
comma
id|PAGE_IO
comma
id|PAGE_IO
op_plus
id|PAGE_IO_SIZE
op_minus
l_int|1
comma
id|WINDOW_START
comma
id|WINDOW_START
op_plus
id|WINDOW_LENGTH
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Probe for chip. */
id|all_mtd
op_assign
id|do_map_probe
c_func
(paren
l_string|&quot;cfi_probe&quot;
comma
op_amp
id|sbc_gxx_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all_mtd
)paren
(brace
id|cleanup_sbc_gxx
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|all_mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* Create MTD devices for each partition. */
id|add_mtd_partitions
c_func
(paren
id|all_mtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_sbc_gxx
id|module_init
c_func
(paren
id|init_sbc_gxx
)paren
suffix:semicolon
DECL|variable|cleanup_sbc_gxx
id|module_exit
c_func
(paren
id|cleanup_sbc_gxx
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
l_string|&quot;Arcom Control Systems Ltd.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for SBC-GXm and SBC-GX1 series boards&quot;
)paren
suffix:semicolon
eof
