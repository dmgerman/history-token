multiline_comment|/*&n; * MTD driver for the 28F160F3 Flash Memory (non-CFI) on LART.&n; *&n; * $Id: lart.c,v 1.5 2003/05/20 21:03:07 dwmw2 Exp $&n; *&n; * Author: Abraham vd Merwe &lt;abraham@2d3d.co.za&gt;&n; *&n; * Copyright (c) 2001, 2d3D, Inc.&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * References:&n; *&n; *    [1] 3 Volt Fast Boot Block Flash Memory&quot; Intel Datasheet&n; *           - Order Number: 290644-005&n; *           - January 2000&n; *&n; *    [2] MTD internal API documentation&n; *           - http://www.linux-mtd.infradead.org/tech/&n; *&n; * Limitations:&n; *&n; *    Even though this driver is written for 3 Volt Fast Boot&n; *    Block Flash Memory, it is rather specific to LART. With&n; *    Minor modifications, notably the without data/address line&n; *    mangling and different bus settings, etc. it should be&n; *    trivial to adapt to other platforms.&n; *&n; *    If somebody would sponsor me a different board, I&squot;ll&n; *    adapt the driver (:&n; */
multiline_comment|/* debugging */
singleline_comment|//#define LART_DEBUG
multiline_comment|/* partition support */
DECL|macro|HAVE_PARTITIONS
mdefine_line|#define HAVE_PARTITIONS
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#ifdef HAVE_PARTITIONS
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#endif
macro_line|#ifndef CONFIG_SA1100_LART
macro_line|#error This is for LART architecture only
macro_line|#endif
DECL|variable|module_name
r_static
r_char
id|module_name
(braket
)braket
op_assign
l_string|&quot;lart&quot;
suffix:semicolon
multiline_comment|/*&n; * These values is specific to 28Fxxxx3 flash memory.&n; * See section 2.3.1 in &quot;3 Volt Fast Boot Block Flash Memory&quot; Intel Datasheet&n; */
DECL|macro|FLASH_BLOCKSIZE_PARAM
mdefine_line|#define FLASH_BLOCKSIZE_PARAM&t;&t;(4096 * BUSWIDTH)
DECL|macro|FLASH_NUMBLOCKS_16m_PARAM
mdefine_line|#define FLASH_NUMBLOCKS_16m_PARAM&t;8
DECL|macro|FLASH_NUMBLOCKS_8m_PARAM
mdefine_line|#define FLASH_NUMBLOCKS_8m_PARAM&t;8
multiline_comment|/*&n; * These values is specific to 28Fxxxx3 flash memory.&n; * See section 2.3.2 in &quot;3 Volt Fast Boot Block Flash Memory&quot; Intel Datasheet&n; */
DECL|macro|FLASH_BLOCKSIZE_MAIN
mdefine_line|#define FLASH_BLOCKSIZE_MAIN&t;&t;(32768 * BUSWIDTH)
DECL|macro|FLASH_NUMBLOCKS_16m_MAIN
mdefine_line|#define FLASH_NUMBLOCKS_16m_MAIN&t;31
DECL|macro|FLASH_NUMBLOCKS_8m_MAIN
mdefine_line|#define FLASH_NUMBLOCKS_8m_MAIN&t;&t;15
multiline_comment|/*&n; * These values are specific to LART&n; */
multiline_comment|/* general */
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH&t;&t;&t;4&t;&t;&t;&t;/* don&squot;t change this - a lot of the code _will_ break if you change this */
DECL|macro|FLASH_OFFSET
mdefine_line|#define FLASH_OFFSET&t;&t;0xe8000000&t;&t;/* see linux/arch/arm/mach-sa1100/lart.c */
multiline_comment|/* blob */
DECL|macro|NUM_BLOB_BLOCKS
mdefine_line|#define NUM_BLOB_BLOCKS&t;&t;FLASH_NUMBLOCKS_16m_PARAM
DECL|macro|BLOB_START
mdefine_line|#define BLOB_START&t;&t;&t;0x00000000
DECL|macro|BLOB_LEN
mdefine_line|#define BLOB_LEN&t;&t;&t;(NUM_BLOB_BLOCKS * FLASH_BLOCKSIZE_PARAM)
multiline_comment|/* kernel */
DECL|macro|NUM_KERNEL_BLOCKS
mdefine_line|#define NUM_KERNEL_BLOCKS&t;7
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;&t;(BLOB_START + BLOB_LEN)
DECL|macro|KERNEL_LEN
mdefine_line|#define KERNEL_LEN&t;&t;&t;(NUM_KERNEL_BLOCKS * FLASH_BLOCKSIZE_MAIN)
multiline_comment|/* initial ramdisk */
DECL|macro|NUM_INITRD_BLOCKS
mdefine_line|#define NUM_INITRD_BLOCKS&t;24
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START&t;&t;(KERNEL_START + KERNEL_LEN)
DECL|macro|INITRD_LEN
mdefine_line|#define INITRD_LEN&t;&t;&t;(NUM_INITRD_BLOCKS * FLASH_BLOCKSIZE_MAIN)
multiline_comment|/*&n; * See section 4.0 in &quot;3 Volt Fast Boot Block Flash Memory&quot; Intel Datasheet&n; */
DECL|macro|READ_ARRAY
mdefine_line|#define READ_ARRAY&t;&t;&t;0x00FF00FF&t;&t;/* Read Array/Reset */
DECL|macro|READ_ID_CODES
mdefine_line|#define READ_ID_CODES&t;&t;0x00900090&t;&t;/* Read Identifier Codes */
DECL|macro|ERASE_SETUP
mdefine_line|#define ERASE_SETUP&t;&t;&t;0x00200020&t;&t;/* Block Erase */
DECL|macro|ERASE_CONFIRM
mdefine_line|#define ERASE_CONFIRM&t;&t;0x00D000D0&t;&t;/* Block Erase and Program Resume */
DECL|macro|PGM_SETUP
mdefine_line|#define PGM_SETUP&t;&t;&t;0x00400040&t;&t;/* Program */
DECL|macro|STATUS_READ
mdefine_line|#define STATUS_READ&t;&t;&t;0x00700070&t;&t;/* Read Status Register */
DECL|macro|STATUS_CLEAR
mdefine_line|#define STATUS_CLEAR&t;&t;0x00500050&t;&t;/* Clear Status Register */
DECL|macro|STATUS_BUSY
mdefine_line|#define STATUS_BUSY&t;&t;&t;0x00800080&t;&t;/* Write State Machine Status (WSMS) */
DECL|macro|STATUS_ERASE_ERR
mdefine_line|#define STATUS_ERASE_ERR&t;0x00200020&t;&t;/* Erase Status (ES) */
DECL|macro|STATUS_PGM_ERR
mdefine_line|#define STATUS_PGM_ERR&t;&t;0x00100010&t;&t;/* Program Status (PS) */
multiline_comment|/*&n; * See section 4.2 in &quot;3 Volt Fast Boot Block Flash Memory&quot; Intel Datasheet&n; */
DECL|macro|FLASH_MANUFACTURER
mdefine_line|#define FLASH_MANUFACTURER&t;&t;&t;0x00890089
DECL|macro|FLASH_DEVICE_8mbit_TOP
mdefine_line|#define FLASH_DEVICE_8mbit_TOP&t;&t;0x88f188f1
DECL|macro|FLASH_DEVICE_8mbit_BOTTOM
mdefine_line|#define FLASH_DEVICE_8mbit_BOTTOM&t;0x88f288f2
DECL|macro|FLASH_DEVICE_16mbit_TOP
mdefine_line|#define FLASH_DEVICE_16mbit_TOP&t;&t;0x88f388f3
DECL|macro|FLASH_DEVICE_16mbit_BOTTOM
mdefine_line|#define FLASH_DEVICE_16mbit_BOTTOM&t;0x88f488f4
multiline_comment|/***************************************************************************************************/
multiline_comment|/*&n; * The data line mapping on LART is as follows:&n; * &n; *   &t; U2  CPU |   U3  CPU&n; *   &t; -------------------&n; *   &t;  0  20  |   0   12&n; *   &t;  1  22  |   1   14&n; *   &t;  2  19  |   2   11&n; *   &t;  3  17  |   3   9&n; *   &t;  4  24  |   4   0&n; *   &t;  5  26  |   5   2&n; *   &t;  6  31  |   6   7&n; *   &t;  7  29  |   7   5&n; *   &t;  8  21  |   8   13&n; *   &t;  9  23  |   9   15&n; *   &t;  10 18  |   10  10&n; *   &t;  11 16  |   11  8&n; *   &t;  12 25  |   12  1&n; *   &t;  13 27  |   13  3&n; *   &t;  14 30  |   14  6&n; *   &t;  15 28  |   15  4&n; */
multiline_comment|/* Mangle data (x) */
DECL|macro|DATA_TO_FLASH
mdefine_line|#define DATA_TO_FLASH(x)&t;&t;&t;&t;&bslash;&n;&t;(&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((x) &amp; 0x08009000) &gt;&gt; 11)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00002000) &gt;&gt; 10)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x04004000) &gt;&gt; 8)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000010) &gt;&gt; 4)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x91000820) &gt;&gt; 3)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x22080080) &gt;&gt; 2)&t;+&t;&bslash;&n;&t;&t;((x) &amp; 0x40000400)&t;&t;&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00040040) &lt;&lt; 1)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00110000) &lt;&lt; 4)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00220100) &lt;&lt; 5)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00800208) &lt;&lt; 6)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00400004) &lt;&lt; 9)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000001) &lt;&lt; 12)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000002) &lt;&lt; 13)&t;&t;&bslash;&n;&t;)
multiline_comment|/* Unmangle data (x) */
DECL|macro|FLASH_TO_DATA
mdefine_line|#define FLASH_TO_DATA(x)&t;&t;&t;&t;&bslash;&n;&t;(&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((x) &amp; 0x00010012) &lt;&lt; 11)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000008) &lt;&lt; 10)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00040040) &lt;&lt; 8)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000001) &lt;&lt; 4)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x12200104) &lt;&lt; 3)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x08820020) &lt;&lt; 2)&t;+&t;&bslash;&n;&t;&t;((x) &amp; 0x40000400)&t;&t;&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00080080) &gt;&gt; 1)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x01100000) &gt;&gt; 4)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x04402000) &gt;&gt; 5)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x20008200) &gt;&gt; 6)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x80000800) &gt;&gt; 9)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00001000) &gt;&gt; 12)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00004000) &gt;&gt; 13)&t;&t;&bslash;&n;&t;)
multiline_comment|/* &n; * The address line mapping on LART is as follows:&n; *&n; *   &t; U3  CPU |   U2  CPU&n; *   &t; -------------------&n; *   &t;  0  2   |   0   2&n; *   &t;  1  3   |   1   3&n; *   &t;  2  9   |   2   9&n; *   &t;  3  13  |   3   8&n; *   &t;  4  8   |   4   7&n; *   &t;  5  12  |   5   6&n; *   &t;  6  11  |   6   5&n; *   &t;  7  10  |   7   4&n; *   &t;  8  4   |   8   10&n; *   &t;  9  5   |   9   11&n; *   &t; 10  6   |   10  12&n; *   &t; 11  7   |   11  13&n; *&n; *   &t; BOOT BLOCK BOUNDARY&n; *&n; *   &t; 12  15  |   12  15&n; *   &t; 13  14  |   13  14&n; *   &t; 14  16  |   14  16&n; * &n; *   &t; MAIN BLOCK BOUNDARY&n; *&n; *   &t; 15  17  |   15  18&n; *   &t; 16  18  |   16  17&n; *   &t; 17  20  |   17  20&n; *   &t; 18  19  |   18  19&n; *   &t; 19  21  |   19  21&n; *&n; * As we can see from above, the addresses aren&squot;t mangled across&n; * block boundaries, so we don&squot;t need to worry about address&n; * translations except for sending/reading commands during&n; * initialization&n; */
multiline_comment|/* Mangle address (x) on chip U2 */
DECL|macro|ADDR_TO_FLASH_U2
mdefine_line|#define ADDR_TO_FLASH_U2(x)&t;&t;&t;&t;&bslash;&n;&t;(&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000f00) &gt;&gt; 4)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00042000) &lt;&lt; 1)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x0009c003) &lt;&lt; 2)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00021080) &lt;&lt; 3)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000010) &lt;&lt; 4)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000040) &lt;&lt; 5)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000024) &lt;&lt; 7)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000008) &lt;&lt; 10)&t;&t;&bslash;&n;&t;)
multiline_comment|/* Unmangle address (x) on chip U2 */
DECL|macro|FLASH_U2_TO_ADDR
mdefine_line|#define FLASH_U2_TO_ADDR(x)&t;&t;&t;&t;&bslash;&n;&t;(&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((x) &lt;&lt; 4) &amp; 0x00000f00)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 1) &amp; 0x00042000)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 2) &amp; 0x0009c003)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 3) &amp; 0x00021080)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 4) &amp; 0x00000010)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 5) &amp; 0x00000040)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 7) &amp; 0x00000024)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 10) &amp; 0x00000008)&t;&t;&bslash;&n;&t;)
multiline_comment|/* Mangle address (x) on chip U3 */
DECL|macro|ADDR_TO_FLASH_U3
mdefine_line|#define ADDR_TO_FLASH_U3(x)&t;&t;&t;&t;&bslash;&n;&t;(&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000080) &gt;&gt; 3)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000040) &gt;&gt; 1)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00052020) &lt;&lt; 1)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00084f03) &lt;&lt; 2)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00029010) &lt;&lt; 3)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000008) &lt;&lt; 5)&t;+&t;&bslash;&n;&t;&t;(((x) &amp; 0x00000004) &lt;&lt; 7)&t;&t;&bslash;&n;&t;)
multiline_comment|/* Unmangle address (x) on chip U3 */
DECL|macro|FLASH_U3_TO_ADDR
mdefine_line|#define FLASH_U3_TO_ADDR(x)&t;&t;&t;&t;&bslash;&n;&t;(&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((x) &lt;&lt; 3) &amp; 0x00000080)&t;+&t;&bslash;&n;&t;&t;(((x) &lt;&lt; 1) &amp; 0x00000040)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 1) &amp; 0x00052020)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 2) &amp; 0x00084f03)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 3) &amp; 0x00029010)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 5) &amp; 0x00000008)&t;+&t;&bslash;&n;&t;&t;(((x) &gt;&gt; 7) &amp; 0x00000004)&t;&t;&bslash;&n;&t;)
multiline_comment|/***************************************************************************************************/
DECL|function|read8
r_static
id|__u8
id|read8
(paren
id|__u32
id|offset
)paren
(brace
r_volatile
id|__u8
op_star
id|data
op_assign
(paren
id|__u8
op_star
)paren
(paren
id|FLASH_OFFSET
op_plus
id|offset
)paren
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(): 0x%.8x -&gt; 0x%.2x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|offset
comma
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
op_star
id|data
)paren
suffix:semicolon
)brace
DECL|function|read32
r_static
id|__u32
id|read32
(paren
id|__u32
id|offset
)paren
(brace
r_volatile
id|__u32
op_star
id|data
op_assign
(paren
id|__u32
op_star
)paren
(paren
id|FLASH_OFFSET
op_plus
id|offset
)paren
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(): 0x%.8x -&gt; 0x%.8x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|offset
comma
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
op_star
id|data
)paren
suffix:semicolon
)brace
DECL|function|write32
r_static
r_void
id|write32
(paren
id|__u32
id|x
comma
id|__u32
id|offset
)paren
(brace
r_volatile
id|__u32
op_star
id|data
op_assign
(paren
id|__u32
op_star
)paren
(paren
id|FLASH_OFFSET
op_plus
id|offset
)paren
suffix:semicolon
op_star
id|data
op_assign
id|x
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(): 0x%.8x &lt;- 0x%.8x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|offset
comma
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/***************************************************************************************************/
multiline_comment|/*&n; * Probe for 16mbit flash memory on a LART board without doing&n; * too much damage. Since we need to write 1 dword to memory,&n; * we&squot;re f**cked if this happens to be DRAM since we can&squot;t&n; * restore the memory (otherwise we might exit Read Array mode).&n; *&n; * Returns 1 if we found 16mbit flash memory on LART, 0 otherwise.&n; */
DECL|function|flash_probe
r_static
r_int
id|flash_probe
(paren
r_void
)paren
(brace
id|__u32
id|manufacturer
comma
id|devtype
suffix:semicolon
multiline_comment|/* setup &quot;Read Identifier Codes&quot; mode */
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|READ_ID_CODES
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* probe U2. U2/U3 returns the same data since the first 3&n;&t;* address lines is mangled in the same way */
id|manufacturer
op_assign
id|FLASH_TO_DATA
(paren
id|read32
(paren
id|ADDR_TO_FLASH_U2
(paren
l_int|0x00000000
)paren
)paren
)paren
suffix:semicolon
id|devtype
op_assign
id|FLASH_TO_DATA
(paren
id|read32
(paren
id|ADDR_TO_FLASH_U2
(paren
l_int|0x00000001
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* put the flash back into command mode */
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|READ_ARRAY
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
r_return
(paren
id|manufacturer
op_eq
id|FLASH_MANUFACTURER
op_logical_and
(paren
id|devtype
op_eq
id|FLASH_DEVICE_16mbit_TOP
op_logical_or
id|FLASH_DEVICE_16mbit_BOTTOM
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Erase one block of flash memory at offset ``offset&squot;&squot; which is any&n; * address within the block which should be erased.&n; *&n; * Returns 1 if successful, 0 otherwise.&n; */
DECL|function|erase_block
r_static
r_inline
r_int
id|erase_block
(paren
id|__u32
id|offset
)paren
(brace
id|__u32
id|status
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(): 0x%.8x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|offset
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* erase and confirm */
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|ERASE_SETUP
)paren
comma
id|offset
)paren
suffix:semicolon
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|ERASE_CONFIRM
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* wait for block erase to finish */
r_do
(brace
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|STATUS_READ
)paren
comma
id|offset
)paren
suffix:semicolon
id|status
op_assign
id|FLASH_TO_DATA
(paren
id|read32
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_complement
id|status
op_amp
id|STATUS_BUSY
)paren
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* put the flash back into command mode */
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|READ_ARRAY
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* was the erase successfull? */
r_if
c_cond
(paren
(paren
id|status
op_amp
id|STATUS_ERASE_ERR
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: erase error at address 0x%.8x.&bslash;n&quot;
comma
id|module_name
comma
id|offset
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|flash_erase
r_static
r_int
id|flash_erase
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|erase_info
op_star
id|instr
)paren
(brace
id|__u32
id|addr
comma
id|len
suffix:semicolon
r_int
id|i
comma
id|first
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(addr = 0x%.8x, len = %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|instr-&gt;addr
comma
id|instr-&gt;len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* sanity checks */
r_if
c_cond
(paren
id|instr-&gt;addr
op_plus
id|instr-&gt;len
OG
id|mtd-&gt;size
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;* check that both start and end of the requested erase are&n;&t;* aligned with the erasesize at the appropriate addresses.&n;&t;*&n;&t;* skip all erase regions which are ended before the start of&n;&t;* the requested erase. Actually, to save on the calculations,&n;&t;* we skip to the first erase region which starts after the&n;&t;* start of the requested erase, and then go back one.&n;&t;*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|mtd-&gt;numeraseregions
op_logical_and
id|instr-&gt;addr
op_ge
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;* ok, now i is pointing at the erase region in which this&n;&t;* erase request starts. Check the start of the requested&n;&t;* erase range is aligned with the erase size which is in&n;&t;* effect here.&n;&t;*/
r_if
c_cond
(paren
id|instr-&gt;addr
op_amp
(paren
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|erasesize
op_minus
l_int|1
)paren
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* Remember the erase region we start on */
id|first
op_assign
id|i
suffix:semicolon
multiline_comment|/*&n;&t;* next, check that the end of the requested erase is aligned&n;&t;* with the erase region at that address.&n;&t;*&n;&t;* as before, drop back one to point at the region in which&n;&t;* the address actually falls&n;&t;*/
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|mtd-&gt;numeraseregions
op_logical_and
id|instr-&gt;addr
op_plus
id|instr-&gt;len
op_ge
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
multiline_comment|/* is the end aligned on a block boundary? */
r_if
c_cond
(paren
(paren
id|instr-&gt;addr
op_plus
id|instr-&gt;len
)paren
op_amp
(paren
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|erasesize
op_minus
l_int|1
)paren
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|addr
op_assign
id|instr-&gt;addr
suffix:semicolon
id|len
op_assign
id|instr-&gt;len
suffix:semicolon
id|i
op_assign
id|first
suffix:semicolon
multiline_comment|/* now erase those blocks */
r_while
c_loop
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|erase_block
(paren
id|addr
)paren
)paren
(brace
id|instr-&gt;state
op_assign
id|MTD_ERASE_FAILED
suffix:semicolon
r_return
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
id|addr
op_add_assign
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|erasesize
suffix:semicolon
id|len
op_sub_assign
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|erasesize
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|offset
op_plus
(paren
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|erasesize
op_star
id|mtd-&gt;eraseregions
(braket
id|i
)braket
dot
id|numblocks
)paren
)paren
id|i
op_increment
suffix:semicolon
)brace
id|instr-&gt;state
op_assign
id|MTD_ERASE_DONE
suffix:semicolon
r_if
c_cond
(paren
id|instr-&gt;callback
)paren
id|instr-&gt;callback
(paren
id|instr
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|flash_read
r_static
r_int
id|flash_read
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
id|buf
)paren
(brace
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(from = 0x%.8x, len = %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
(paren
id|__u32
)paren
id|from
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* sanity checks */
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from
op_plus
id|len
OG
id|mtd-&gt;size
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* we always read len bytes */
op_star
id|retlen
op_assign
id|len
suffix:semicolon
multiline_comment|/* first, we read bytes until we reach a dword boundary */
r_if
c_cond
(paren
id|from
op_amp
(paren
id|BUSWIDTH
op_minus
l_int|1
)paren
)paren
(brace
r_int
id|gap
op_assign
id|BUSWIDTH
op_minus
(paren
id|from
op_amp
(paren
id|BUSWIDTH
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|gap
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
id|read8
(paren
id|from
op_increment
)paren
comma
id|len
op_decrement
suffix:semicolon
)brace
multiline_comment|/* now we read dwords until we reach a non-dword boundary */
r_while
c_loop
(paren
id|len
op_ge
id|BUSWIDTH
)paren
(brace
op_star
(paren
(paren
id|__u32
op_star
)paren
id|buf
)paren
op_assign
id|read32
(paren
id|from
)paren
suffix:semicolon
id|buf
op_add_assign
id|BUSWIDTH
suffix:semicolon
id|from
op_add_assign
id|BUSWIDTH
suffix:semicolon
id|len
op_sub_assign
id|BUSWIDTH
suffix:semicolon
)brace
multiline_comment|/* top up the last unaligned bytes */
r_if
c_cond
(paren
id|len
op_amp
(paren
id|BUSWIDTH
op_minus
l_int|1
)paren
)paren
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
id|read8
(paren
id|from
op_increment
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write one dword ``x&squot;&squot; to flash memory at offset ``offset&squot;&squot;. ``offset&squot;&squot;&n; * must be 32 bits, i.e. it must be on a dword boundary.&n; *&n; * Returns 1 if successful, 0 otherwise.&n; */
DECL|function|write_dword
r_static
r_inline
r_int
id|write_dword
(paren
id|__u32
id|offset
comma
id|__u32
id|x
)paren
(brace
id|__u32
id|status
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(): 0x%.8x &lt;- 0x%.8x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|offset
comma
id|x
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* setup writing */
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|PGM_SETUP
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* write the data */
id|write32
(paren
id|x
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* wait for the write to finish */
r_do
(brace
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|STATUS_READ
)paren
comma
id|offset
)paren
suffix:semicolon
id|status
op_assign
id|FLASH_TO_DATA
(paren
id|read32
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_complement
id|status
op_amp
id|STATUS_BUSY
)paren
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* put the flash back into command mode */
id|write32
(paren
id|DATA_TO_FLASH
(paren
id|READ_ARRAY
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* was the write successfull? */
r_if
c_cond
(paren
(paren
id|status
op_amp
id|STATUS_PGM_ERR
)paren
op_logical_or
id|read32
(paren
id|offset
)paren
op_ne
id|x
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: write error at address 0x%.8x.&bslash;n&quot;
comma
id|module_name
comma
id|offset
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|flash_write
r_static
r_int
id|flash_write
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|to
comma
r_int
id|len
comma
r_int
op_star
id|retlen
comma
r_const
id|u_char
op_star
id|buf
)paren
(brace
id|__u8
id|tmp
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s(to = 0x%.8x, len = %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
(paren
id|__u32
)paren
id|to
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
op_star
id|retlen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* sanity checks */
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|to
op_plus
id|len
OG
id|mtd-&gt;size
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* first, we write a 0xFF.... padded byte until we reach a dword boundary */
r_if
c_cond
(paren
id|to
op_amp
(paren
id|BUSWIDTH
op_minus
l_int|1
)paren
)paren
(brace
id|__u32
id|aligned
op_assign
id|to
op_amp
op_complement
(paren
id|BUSWIDTH
op_minus
l_int|1
)paren
suffix:semicolon
r_int
id|gap
op_assign
id|to
op_minus
id|aligned
suffix:semicolon
id|i
op_assign
id|n
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|gap
op_decrement
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_int|0xFF
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|i
OL
id|BUSWIDTH
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
id|buf
(braket
id|n
op_increment
)braket
comma
id|len
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|BUSWIDTH
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_int|0xFF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_dword
(paren
id|aligned
comma
op_star
(paren
(paren
id|__u32
op_star
)paren
id|tmp
)paren
)paren
)paren
r_return
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|to
op_add_assign
id|n
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
op_star
id|retlen
op_add_assign
id|n
suffix:semicolon
)brace
multiline_comment|/* now we write dwords until we reach a non-dword boundary */
r_while
c_loop
(paren
id|len
op_ge
id|BUSWIDTH
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|write_dword
(paren
id|to
comma
op_star
(paren
(paren
id|__u32
op_star
)paren
id|buf
)paren
)paren
)paren
r_return
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|to
op_add_assign
id|BUSWIDTH
suffix:semicolon
id|buf
op_add_assign
id|BUSWIDTH
suffix:semicolon
op_star
id|retlen
op_add_assign
id|BUSWIDTH
suffix:semicolon
id|len
op_sub_assign
id|BUSWIDTH
suffix:semicolon
)brace
multiline_comment|/* top up the last unaligned bytes, padded with 0xFF.... */
r_if
c_cond
(paren
id|len
op_amp
(paren
id|BUSWIDTH
op_minus
l_int|1
)paren
)paren
(brace
id|i
op_assign
id|n
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
id|buf
(braket
id|n
op_increment
)braket
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|BUSWIDTH
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_int|0xFF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_dword
(paren
id|to
comma
op_star
(paren
(paren
id|__u32
op_star
)paren
id|tmp
)paren
)paren
)paren
r_return
(paren
op_minus
id|EIO
)paren
suffix:semicolon
op_star
id|retlen
op_add_assign
id|n
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/***************************************************************************************************/
DECL|macro|NB_OF
mdefine_line|#define NB_OF(x) (sizeof (x) / sizeof (x[0]))
DECL|variable|mtd
r_static
r_struct
id|mtd_info
id|mtd
suffix:semicolon
DECL|variable|erase_regions
r_static
r_struct
id|mtd_erase_region_info
id|erase_regions
(braket
)braket
op_assign
(brace
multiline_comment|/* parameter blocks */
(brace
dot
id|offset
op_assign
l_int|0x00000000
comma
dot
id|erasesize
op_assign
id|FLASH_BLOCKSIZE_PARAM
comma
dot
id|numblocks
op_assign
id|FLASH_NUMBLOCKS_16m_PARAM
comma
)brace
comma
multiline_comment|/* main blocks */
(brace
dot
id|offset
op_assign
id|FLASH_BLOCKSIZE_PARAM
op_star
id|FLASH_NUMBLOCKS_16m_PARAM
comma
dot
id|erasesize
op_assign
id|FLASH_BLOCKSIZE_MAIN
comma
dot
id|numblocks
op_assign
id|FLASH_NUMBLOCKS_16m_MAIN
comma
)brace
)brace
suffix:semicolon
macro_line|#ifdef HAVE_PARTITIONS
DECL|variable|lart_partitions
r_static
r_struct
id|mtd_partition
id|lart_partitions
(braket
)braket
op_assign
(brace
multiline_comment|/* blob */
(brace
dot
id|name
op_assign
l_string|&quot;blob&quot;
comma
dot
id|offset
op_assign
id|BLOB_START
comma
dot
id|size
op_assign
id|BLOB_LEN
comma
)brace
comma
multiline_comment|/* kernel */
(brace
dot
id|name
op_assign
l_string|&quot;kernel&quot;
comma
dot
id|offset
op_assign
id|KERNEL_START
comma
multiline_comment|/* MTDPART_OFS_APPEND */
dot
id|size
op_assign
id|KERNEL_LEN
comma
)brace
comma
multiline_comment|/* initial ramdisk / file system */
(brace
dot
id|name
op_assign
l_string|&quot;file system&quot;
comma
dot
id|offset
op_assign
id|INITRD_START
comma
multiline_comment|/* MTDPART_OFS_APPEND */
dot
id|size
op_assign
id|INITRD_LEN
comma
multiline_comment|/* MTDPART_SIZ_FULL */
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|function|lart_flash_init
r_int
id|__init
id|lart_flash_init
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
id|memset
(paren
op_amp
id|mtd
comma
l_int|0
comma
r_sizeof
(paren
id|mtd
)paren
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;MTD driver for LART. Written by Abraham vd Merwe &lt;abraham@2d3d.co.za&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: Probing for 28F160x3 flash on LART...&bslash;n&quot;
comma
id|module_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flash_probe
(paren
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: Found no LART compatible flash device&bslash;n&quot;
comma
id|module_name
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENXIO
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;%s: This looks like a LART board to me.&bslash;n&quot;
comma
id|module_name
)paren
suffix:semicolon
id|mtd.name
op_assign
id|module_name
suffix:semicolon
id|mtd.type
op_assign
id|MTD_NORFLASH
suffix:semicolon
id|mtd.flags
op_assign
id|MTD_CAP_NORFLASH
suffix:semicolon
id|mtd.size
op_assign
id|FLASH_BLOCKSIZE_PARAM
op_star
id|FLASH_NUMBLOCKS_16m_PARAM
op_plus
id|FLASH_BLOCKSIZE_MAIN
op_star
id|FLASH_NUMBLOCKS_16m_MAIN
suffix:semicolon
id|mtd.erasesize
op_assign
id|FLASH_BLOCKSIZE_MAIN
suffix:semicolon
id|mtd.numeraseregions
op_assign
id|NB_OF
(paren
id|erase_regions
)paren
suffix:semicolon
id|mtd.eraseregions
op_assign
id|erase_regions
suffix:semicolon
id|mtd.erase
op_assign
id|flash_erase
suffix:semicolon
id|mtd.read
op_assign
id|flash_read
suffix:semicolon
id|mtd.write
op_assign
id|flash_write
suffix:semicolon
id|mtd.owner
op_assign
id|THIS_MODULE
suffix:semicolon
macro_line|#ifdef LART_DEBUG
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;mtd.name = %s&bslash;n&quot;
l_string|&quot;mtd.size = 0x%.8x (%uM)&bslash;n&quot;
l_string|&quot;mtd.erasesize = 0x%.8x (%uK)&bslash;n&quot;
l_string|&quot;mtd.numeraseregions = %d&bslash;n&quot;
comma
id|mtd.name
comma
id|mtd.size
comma
id|mtd.size
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
comma
id|mtd.erasesize
comma
id|mtd.erasesize
op_div
l_int|1024
comma
id|mtd.numeraseregions
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd.numeraseregions
)paren
r_for
c_loop
(paren
id|result
op_assign
l_int|0
suffix:semicolon
id|result
OL
id|mtd.numeraseregions
suffix:semicolon
id|result
op_increment
)paren
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&bslash;n&quot;
l_string|&quot;mtd.eraseregions[%d].offset = 0x%.8x&bslash;n&quot;
l_string|&quot;mtd.eraseregions[%d].erasesize = 0x%.8x (%uK)&bslash;n&quot;
l_string|&quot;mtd.eraseregions[%d].numblocks = %d&bslash;n&quot;
comma
id|result
comma
id|mtd.eraseregions
(braket
id|result
)braket
dot
id|offset
comma
id|result
comma
id|mtd.eraseregions
(braket
id|result
)braket
dot
id|erasesize
comma
id|mtd.eraseregions
(braket
id|result
)braket
dot
id|erasesize
op_div
l_int|1024
comma
id|result
comma
id|mtd.eraseregions
(braket
id|result
)braket
dot
id|numblocks
)paren
suffix:semicolon
macro_line|#ifdef HAVE_PARTITIONS
id|printk
(paren
l_string|&quot;&bslash;npartitions = %d&bslash;n&quot;
comma
id|NB_OF
(paren
id|lart_partitions
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|result
op_assign
l_int|0
suffix:semicolon
id|result
OL
id|NB_OF
(paren
id|lart_partitions
)paren
suffix:semicolon
id|result
op_increment
)paren
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&bslash;n&quot;
l_string|&quot;lart_partitions[%d].name = %s&bslash;n&quot;
l_string|&quot;lart_partitions[%d].offset = 0x%.8x&bslash;n&quot;
l_string|&quot;lart_partitions[%d].size = 0x%.8x (%uK)&bslash;n&quot;
comma
id|result
comma
id|lart_partitions
(braket
id|result
)braket
dot
id|name
comma
id|result
comma
id|lart_partitions
(braket
id|result
)braket
dot
id|offset
comma
id|result
comma
id|lart_partitions
(braket
id|result
)braket
dot
id|size
comma
id|lart_partitions
(braket
id|result
)braket
dot
id|size
op_div
l_int|1024
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifndef HAVE_PARTITIONS
id|result
op_assign
id|add_mtd_device
(paren
op_amp
id|mtd
)paren
suffix:semicolon
macro_line|#else
id|result
op_assign
id|add_mtd_partitions
(paren
op_amp
id|mtd
comma
id|lart_partitions
comma
id|NB_OF
(paren
id|lart_partitions
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|result
)paren
suffix:semicolon
)brace
DECL|function|lart_flash_exit
r_void
id|__exit
id|lart_flash_exit
(paren
r_void
)paren
(brace
macro_line|#ifndef HAVE_PARTITIONS
id|del_mtd_device
(paren
op_amp
id|mtd
)paren
suffix:semicolon
macro_line|#else
id|del_mtd_partitions
(paren
op_amp
id|mtd
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|lart_flash_init
id|module_init
(paren
id|lart_flash_init
)paren
suffix:semicolon
DECL|variable|lart_flash_exit
id|module_exit
(paren
id|lart_flash_exit
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
l_string|&quot;Abraham vd Merwe &lt;abraham@2d3d.co.za&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD driver for Intel 28F160F3 on LART board&quot;
)paren
suffix:semicolon
eof
