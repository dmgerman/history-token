multiline_comment|/* elan-104nc.c -- MTD map driver for Arcom Control Systems ELAN-104NC&n; &n;   Copyright (C) 2000 Arcom Control System Ltd&n; &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n; &n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n; &n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA&n;&n;   $Id: elan-104nc.c,v 1.17 2003/05/21 15:15:07 dwmw2 Exp $&n;&n;The ELAN-104NC has up to 8 Mibyte of Intel StrataFlash (28F320/28F640) in x16&n;mode.  This drivers uses the CFI probe and Intel Extended Command Set drivers.&n;&n;The flash is accessed as follows:&n;&n;   32 kbyte memory window at 0xb0000-0xb7fff&n;   &n;   16 bit I/O port (0x22) for some sort of paging.&n;&n;The single flash device is divided into 3 partition which appear as seperate&n;MTD devices.&n;&n;Linux thinks that the I/O port is used by the PIC and hence check_region() will&n;always fail.  So we don&squot;t do it.  I just hope it doesn&squot;t break anything.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
DECL|macro|WINDOW_START
mdefine_line|#define WINDOW_START 0xb0000
multiline_comment|/* Number of bits in offset. */
DECL|macro|WINDOW_SHIFT
mdefine_line|#define WINDOW_SHIFT 15
DECL|macro|WINDOW_LENGTH
mdefine_line|#define WINDOW_LENGTH (1 &lt;&lt; WINDOW_SHIFT)
multiline_comment|/* The bits for the offset into the window. */
DECL|macro|WINDOW_MASK
mdefine_line|#define WINDOW_MASK (WINDOW_LENGTH-1)
DECL|macro|PAGE_IO
mdefine_line|#define PAGE_IO 0x22
DECL|macro|PAGE_IO_SIZE
mdefine_line|#define PAGE_IO_SIZE 2
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
r_int
r_int
id|iomapadr
suffix:semicolon
DECL|variable|elan_104nc_spin
r_static
id|spinlock_t
id|elan_104nc_spin
op_assign
id|SPIN_LOCK_UNLOCKED
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
mdefine_line|#define NUM_PARTITIONS (sizeof(partition_info)/sizeof(partition_info[0]))
multiline_comment|/*&n; * If no idea what is going on here.  This is taken from the FlashFX stuff.&n; */
DECL|macro|ROMCS
mdefine_line|#define ROMCS 1
DECL|function|elan_104nc_setup
r_static
r_inline
r_void
id|elan_104nc_setup
c_func
(paren
r_void
)paren
(brace
id|u16
id|t
suffix:semicolon
id|outw
c_func
(paren
l_int|0x0023
op_plus
id|ROMCS
op_star
l_int|2
comma
id|PAGE_IO
)paren
suffix:semicolon
id|t
op_assign
id|inb
c_func
(paren
id|PAGE_IO
op_plus
l_int|1
)paren
suffix:semicolon
id|t
op_assign
(paren
id|t
op_amp
l_int|0xf9
)paren
op_or
l_int|0x04
suffix:semicolon
id|outw
c_func
(paren
(paren
(paren
l_int|0x0023
op_plus
id|ROMCS
op_star
l_int|2
)paren
op_or
(paren
id|t
op_lshift
l_int|8
)paren
)paren
comma
id|PAGE_IO
)paren
suffix:semicolon
)brace
DECL|function|elan_104nc_page
r_static
r_inline
r_void
id|elan_104nc_page
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
r_int
id|cmd1
suffix:semicolon
r_int
id|cmd2
suffix:semicolon
id|cmd1
op_assign
(paren
id|page
op_amp
l_int|0x700
)paren
op_plus
l_int|0x0833
op_plus
id|ROMCS
op_star
l_int|0x4000
suffix:semicolon
id|cmd2
op_assign
(paren
(paren
id|page
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_plus
l_int|0x0032
suffix:semicolon
id|outw
c_func
(paren
id|cmd1
comma
id|PAGE_IO
)paren
suffix:semicolon
id|outw
c_func
(paren
id|cmd2
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
DECL|function|elan_104nc_read8
r_static
id|__u8
id|elan_104nc_read8
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
id|__u8
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
c_func
(paren
id|map
comma
id|ofs
)paren
suffix:semicolon
id|ret
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
id|elan_104nc_spin
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|elan_104nc_read16
r_static
id|__u16
id|elan_104nc_read16
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
id|__u16
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
c_func
(paren
id|map
comma
id|ofs
)paren
suffix:semicolon
id|ret
op_assign
id|readw
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
id|elan_104nc_spin
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|elan_104nc_read32
r_static
id|__u32
id|elan_104nc_read32
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
id|__u32
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
c_func
(paren
id|map
comma
id|ofs
)paren
suffix:semicolon
id|ret
op_assign
id|readl
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
id|elan_104nc_spin
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|elan_104nc_copy_from
r_static
r_void
id|elan_104nc_copy_from
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
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
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
id|elan_104nc_spin
)paren
suffix:semicolon
(paren
id|__u8
op_star
)paren
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
DECL|function|elan_104nc_write8
r_static
r_void
id|elan_104nc_write8
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
id|spin_lock
c_func
(paren
op_amp
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
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
id|d
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
id|elan_104nc_spin
)paren
suffix:semicolon
)brace
DECL|function|elan_104nc_write16
r_static
r_void
id|elan_104nc_write16
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
id|spin_lock
c_func
(paren
op_amp
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
c_func
(paren
id|map
comma
id|adr
)paren
suffix:semicolon
id|writew
c_func
(paren
id|d
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
id|elan_104nc_spin
)paren
suffix:semicolon
)brace
DECL|function|elan_104nc_write32
r_static
r_void
id|elan_104nc_write32
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
id|spin_lock
c_func
(paren
op_amp
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
c_func
(paren
id|map
comma
id|adr
)paren
suffix:semicolon
id|writel
c_func
(paren
id|d
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
id|elan_104nc_spin
)paren
suffix:semicolon
)brace
DECL|function|elan_104nc_copy_to
r_static
r_void
id|elan_104nc_copy_to
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
id|elan_104nc_spin
)paren
suffix:semicolon
id|elan_104nc_page
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
id|elan_104nc_spin
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
DECL|variable|elan_104nc_map
r_static
r_struct
id|map_info
id|elan_104nc_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ELAN-104NC flash&quot;
comma
dot
id|phys
op_assign
id|NO_XIP
comma
dot
id|size
op_assign
l_int|8
op_star
l_int|1024
op_star
l_int|1024
comma
multiline_comment|/* this must be set to a maximum possible amount&n;&t;&t;&t;of flash so the cfi probe routines find all&n;&t;&t;&t;the chips */
dot
id|buswidth
op_assign
l_int|2
comma
dot
id|read8
op_assign
id|elan_104nc_read8
comma
dot
id|read16
op_assign
id|elan_104nc_read16
comma
dot
id|read32
op_assign
id|elan_104nc_read32
comma
dot
id|copy_from
op_assign
id|elan_104nc_copy_from
comma
dot
id|write8
op_assign
id|elan_104nc_write8
comma
dot
id|write16
op_assign
id|elan_104nc_write16
comma
dot
id|write32
op_assign
id|elan_104nc_write32
comma
dot
id|copy_to
op_assign
id|elan_104nc_copy_to
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
DECL|function|cleanup_elan_104nc
r_static
r_void
id|cleanup_elan_104nc
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
(paren
r_void
op_star
)paren
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
DECL|function|init_elan_104nc
r_int
id|__init
id|init_elan_104nc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Urg! We use I/O port 0x22 without request_region()ing it */
multiline_comment|/*&n;&t;if (check_region(PAGE_IO,PAGE_IO_SIZE) != 0) {&n;&t;&t;printk( KERN_ERR&quot;%s: IO ports 0x%x-0x%x in use&bslash;n&quot;,&n;&t;&t;&t;elan_104nc_map.name,&n;&t;&t;&t;PAGE_IO, PAGE_IO+PAGE_IO_SIZE-1 );&n;&t;&t;return -EAGAIN;&n;&t;}&n;&t;*/
id|iomapadr
op_assign
(paren
r_int
r_int
)paren
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
id|elan_104nc_map.name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t;request_region( PAGE_IO, PAGE_IO_SIZE, &quot;ELAN-104NC flash&quot; );&n;&t;*/
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: IO:0x%x-0x%x MEM:0x%x-0x%x&bslash;n&quot;
comma
id|elan_104nc_map.name
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
id|elan_104nc_setup
c_func
(paren
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
id|elan_104nc_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all_mtd
)paren
(brace
id|cleanup_elan_104nc
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
DECL|variable|init_elan_104nc
id|module_init
c_func
(paren
id|init_elan_104nc
)paren
suffix:semicolon
DECL|variable|cleanup_elan_104nc
id|module_exit
c_func
(paren
id|cleanup_elan_104nc
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
l_string|&quot;MTD map driver for Arcom Control Systems ELAN-104NC&quot;
)paren
suffix:semicolon
eof
