multiline_comment|/*&n; *  drivers/mtd/nand/au1550nd.c&n; *&n; *  Copyright (C) 2004 Embedded Edge, LLC&n; *&n; * $Id: au1550nd.c,v 1.9 2004/10/20 05:58:30 ppopov Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* fixme: this is ugly */
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2, 6, 0)
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
macro_line|#ifdef CONFIG_MIPS_PB1550
macro_line|#include &lt;asm/mach-pb1x00/pb1550.h&gt; 
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1550
macro_line|#include &lt;asm/mach-db1x00/db1x00.h&gt; 
macro_line|#endif
macro_line|#else
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#ifdef CONFIG_MIPS_PB1550
macro_line|#include &lt;asm/pb1550.h&gt; 
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1550
macro_line|#include &lt;asm/db1x00.h&gt; 
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * MTD structure for NAND controller&n; */
DECL|variable|au1550_mtd
r_static
r_struct
id|mtd_info
op_star
id|au1550_mtd
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|p_nand
r_static
r_void
id|__iomem
op_star
id|p_nand
suffix:semicolon
DECL|variable|nand_width
r_static
r_int
id|nand_width
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* default x8*/
DECL|macro|NAND_CS
mdefine_line|#define NAND_CS 1
multiline_comment|/*&n; * Define partitions for flash device&n; */
DECL|variable|partition_info
r_const
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_MIPS_PB1550
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS            2
(brace
dot
id|name
op_assign
l_string|&quot;Pb1550 NAND FS 0&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Pb1550 NAND FS 1&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1550
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS            2
(brace
dot
id|name
op_assign
l_string|&quot;Db1550 NAND FS 0&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Db1550 NAND FS 1&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
)brace
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/**&n; * au_read_byte -  read one byte from the chip&n; * @mtd:&t;MTD device structure&n; *&n; *  read function for 8bit buswith&n; */
DECL|function|au_read_byte
r_static
id|u_char
id|au_read_byte
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|u_char
id|ret
op_assign
id|readb
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * au_write_byte -  write one byte to the chip&n; * @mtd:&t;MTD device structure&n; * @byte:&t;pointer to data byte to write&n; *&n; *  write function for 8it buswith&n; */
DECL|function|au_write_byte
r_static
r_void
id|au_write_byte
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
id|byte
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|writeb
c_func
(paren
id|byte
comma
id|this-&gt;IO_ADDR_W
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * au_read_byte16 -  read one byte endianess aware from the chip&n; * @mtd:&t;MTD device structure&n; *&n; *  read function for 16bit buswith with &n; * endianess conversion&n; */
DECL|function|au_read_byte16
r_static
id|u_char
id|au_read_byte16
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|u_char
id|ret
op_assign
(paren
id|u_char
)paren
id|cpu_to_le16
c_func
(paren
id|readw
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * au_write_byte16 -  write one byte endianess aware to the chip&n; * @mtd:&t;MTD device structure&n; * @byte:&t;pointer to data byte to write&n; *&n; *  write function for 16bit buswith with&n; * endianess conversion&n; */
DECL|function|au_write_byte16
r_static
r_void
id|au_write_byte16
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
id|byte
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|writew
c_func
(paren
id|le16_to_cpu
c_func
(paren
(paren
id|u16
)paren
id|byte
)paren
comma
id|this-&gt;IO_ADDR_W
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * au_read_word -  read one word from the chip&n; * @mtd:&t;MTD device structure&n; *&n; *  read function for 16bit buswith without &n; * endianess conversion&n; */
DECL|function|au_read_word
r_static
id|u16
id|au_read_word
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|u16
id|ret
op_assign
id|readw
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * au_write_word -  write one word to the chip&n; * @mtd:&t;MTD device structure&n; * @word:&t;data word to write&n; *&n; *  write function for 16bit buswith without &n; * endianess conversion&n; */
DECL|function|au_write_word
r_static
r_void
id|au_write_word
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u16
id|word
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|writew
c_func
(paren
id|word
comma
id|this-&gt;IO_ADDR_W
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * au_write_buf -  write buffer to chip&n; * @mtd:&t;MTD device structure&n; * @buf:&t;data buffer&n; * @len:&t;number of bytes to write&n; *&n; *  write function for 8bit buswith&n; */
DECL|function|au_write_buf
r_static
r_void
id|au_write_buf
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writeb
c_func
(paren
id|buf
(braket
id|i
)braket
comma
id|this-&gt;IO_ADDR_W
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * au_read_buf -  read chip data into buffer &n; * @mtd:&t;MTD device structure&n; * @buf:&t;buffer to store date&n; * @len:&t;number of bytes to read&n; *&n; *  read function for 8bit buswith&n; */
DECL|function|au_read_buf
r_static
r_void
id|au_read_buf
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|buf
(braket
id|i
)braket
op_assign
id|readb
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * au_verify_buf -  Verify chip data against buffer &n; * @mtd:&t;MTD device structure&n; * @buf:&t;buffer containing the data to compare&n; * @len:&t;number of bytes to compare&n; *&n; *  verify function for 8bit buswith&n; */
DECL|function|au_verify_buf
r_static
r_int
id|au_verify_buf
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_ne
id|readb
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * au_write_buf16 -  write buffer to chip&n; * @mtd:&t;MTD device structure&n; * @buf:&t;data buffer&n; * @len:&t;number of bytes to write&n; *&n; *  write function for 16bit buswith&n; */
DECL|function|au_write_buf16
r_static
r_void
id|au_write_buf16
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|u16
op_star
id|p
op_assign
(paren
id|u16
op_star
)paren
id|buf
suffix:semicolon
id|len
op_rshift_assign
l_int|1
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writew
c_func
(paren
id|p
(braket
id|i
)braket
comma
id|this-&gt;IO_ADDR_W
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * au_read_buf16 -  read chip data into buffer &n; * @mtd:&t;MTD device structure&n; * @buf:&t;buffer to store date&n; * @len:&t;number of bytes to read&n; *&n; *  read function for 16bit buswith&n; */
DECL|function|au_read_buf16
r_static
r_void
id|au_read_buf16
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|u16
op_star
id|p
op_assign
(paren
id|u16
op_star
)paren
id|buf
suffix:semicolon
id|len
op_rshift_assign
l_int|1
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
(braket
id|i
)braket
op_assign
id|readw
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * au_verify_buf16 -  Verify chip data against buffer &n; * @mtd:&t;MTD device structure&n; * @buf:&t;buffer containing the data to compare&n; * @len:&t;number of bytes to compare&n; *&n; *  verify function for 16bit buswith&n; */
DECL|function|au_verify_buf16
r_static
r_int
id|au_verify_buf16
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
id|u_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|u16
op_star
id|p
op_assign
(paren
id|u16
op_star
)paren
id|buf
suffix:semicolon
id|len
op_rshift_assign
l_int|1
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
id|i
)braket
op_ne
id|readw
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|au1550_hwcontrol
r_static
r_void
id|au1550_hwcontrol
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|cmd
)paren
(brace
r_register
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NAND_CTL_SETCLE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
id|p_nand
op_plus
id|MEM_STNAND_CMD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRCLE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
id|p_nand
op_plus
id|MEM_STNAND_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETALE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
id|p_nand
op_plus
id|MEM_STNAND_ADDR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRALE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
id|p_nand
op_plus
id|MEM_STNAND_DATA
suffix:semicolon
multiline_comment|/* FIXME: Nobody knows why this is neccecary, &n;&t;&t; * but it works only that way */
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETNCE
suffix:colon
multiline_comment|/* assert (force assert) chip enable */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|MEM_STNDCTL
)paren
op_or
(paren
l_int|1
op_lshift
(paren
l_int|4
op_plus
id|NAND_CS
)paren
)paren
comma
id|MEM_STNDCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRNCE
suffix:colon
multiline_comment|/* deassert chip enable */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|MEM_STNDCTL
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|4
op_plus
id|NAND_CS
)paren
)paren
comma
id|MEM_STNDCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|this-&gt;IO_ADDR_R
op_assign
id|this-&gt;IO_ADDR_W
suffix:semicolon
multiline_comment|/* Drain the writebuffer */
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|au1550_device_ready
r_int
id|au1550_device_ready
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_int
id|ret
op_assign
(paren
id|au_readl
c_func
(paren
id|MEM_STSTAT
)paren
op_amp
l_int|0x1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Main initialization routine&n; */
DECL|function|au1550_init
r_int
id|__init
id|au1550_init
(paren
r_void
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
suffix:semicolon
id|u16
id|boot_swapboot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* default value */
r_int
id|retval
suffix:semicolon
multiline_comment|/* Allocate memory for MTD device structure and private data */
id|au1550_mtd
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|mtd_info
)paren
op_plus
r_sizeof
(paren
r_struct
id|nand_chip
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|au1550_mtd
)paren
(brace
id|printk
(paren
l_string|&quot;Unable to allocate NAND MTD dev structure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* Get pointer to private data */
id|this
op_assign
(paren
r_struct
id|nand_chip
op_star
)paren
(paren
op_amp
id|au1550_mtd
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Initialize structures */
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|au1550_mtd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mtd_info
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|this
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|nand_chip
)paren
)paren
suffix:semicolon
multiline_comment|/* Link the private data with the MTD structure */
id|au1550_mtd-&gt;priv
op_assign
id|this
suffix:semicolon
multiline_comment|/* MEM_STNDCTL: disable ints, disable nand boot */
multiline_comment|/* disable interrupts */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|MEM_STNDCTL
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
id|MEM_STNDCTL
)paren
suffix:semicolon
multiline_comment|/* disable NAND boot */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|MEM_STNDCTL
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
id|MEM_STNDCTL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS_PB1550
multiline_comment|/* set gpio206 high */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|GPIO2_DIR
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
id|GPIO2_DIR
)paren
suffix:semicolon
id|boot_swapboot
op_assign
(paren
id|au_readl
c_func
(paren
id|MEM_STSTAT
)paren
op_amp
(paren
l_int|0x7
op_lshift
l_int|1
)paren
)paren
op_or
(paren
(paren
id|bcsr-&gt;status
op_rshift
l_int|6
)paren
op_amp
l_int|0x1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|boot_swapboot
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|8
suffix:colon
r_case
l_int|0xC
suffix:colon
r_case
l_int|0xD
suffix:colon
multiline_comment|/* x16 NAND Flash */
id|nand_width
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|0xE
suffix:colon
r_case
l_int|0xF
suffix:colon
multiline_comment|/* x8 NAND Flash */
id|nand_width
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Pb1550 NAND: bad boot:swap&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|outmem
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Configure RCE1 - should be done by YAMON */
id|au_writel
c_func
(paren
l_int|0x5
op_or
(paren
id|nand_width
op_lshift
l_int|22
)paren
comma
l_int|0xB4001010
)paren
suffix:semicolon
multiline_comment|/* MEM_STCFG1 */
id|au_writel
c_func
(paren
id|NAND_TIMING
comma
l_int|0xB4001014
)paren
suffix:semicolon
multiline_comment|/* MEM_STTIME1 */
id|au_sync
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup and enable chip select, MEM_STADDR1 */
multiline_comment|/* we really need to decode offsets only up till 0x20 */
id|au_writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|28
)paren
op_or
(paren
id|NAND_PHYS_ADDR
op_rshift
l_int|4
)paren
op_or
(paren
(paren
(paren
id|NAND_PHYS_ADDR
op_plus
l_int|0x1000
)paren
op_minus
l_int|1
)paren
op_amp
(paren
l_int|0x3fff
op_lshift
l_int|18
)paren
op_rshift
l_int|18
)paren
comma
id|MEM_STADDR1
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
id|p_nand
op_assign
(paren
r_void
id|__iomem
op_star
)paren
id|ioremap
c_func
(paren
id|NAND_PHYS_ADDR
comma
l_int|0x1000
)paren
suffix:semicolon
multiline_comment|/* Set address of hardware control function */
id|this-&gt;hwcontrol
op_assign
id|au1550_hwcontrol
suffix:semicolon
id|this-&gt;dev_ready
op_assign
id|au1550_device_ready
suffix:semicolon
multiline_comment|/* 30 us command delay time */
id|this-&gt;chip_delay
op_assign
l_int|30
suffix:semicolon
id|this-&gt;eccmode
op_assign
id|NAND_ECC_SOFT
suffix:semicolon
id|this-&gt;options
op_assign
id|NAND_NO_AUTOINCR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nand_width
)paren
id|this-&gt;options
op_or_assign
id|NAND_BUSWIDTH_16
suffix:semicolon
id|this-&gt;read_byte
op_assign
(paren
op_logical_neg
id|nand_width
)paren
ques
c_cond
id|au_read_byte16
suffix:colon
id|au_read_byte
suffix:semicolon
id|this-&gt;write_byte
op_assign
(paren
op_logical_neg
id|nand_width
)paren
ques
c_cond
id|au_write_byte16
suffix:colon
id|au_write_byte
suffix:semicolon
id|this-&gt;write_word
op_assign
id|au_write_word
suffix:semicolon
id|this-&gt;read_word
op_assign
id|au_read_word
suffix:semicolon
id|this-&gt;write_buf
op_assign
(paren
op_logical_neg
id|nand_width
)paren
ques
c_cond
id|au_write_buf16
suffix:colon
id|au_write_buf
suffix:semicolon
id|this-&gt;read_buf
op_assign
(paren
op_logical_neg
id|nand_width
)paren
ques
c_cond
id|au_read_buf16
suffix:colon
id|au_read_buf
suffix:semicolon
id|this-&gt;verify_buf
op_assign
(paren
op_logical_neg
id|nand_width
)paren
ques
c_cond
id|au_verify_buf16
suffix:colon
id|au_verify_buf
suffix:semicolon
multiline_comment|/* Scan to find existence of the device */
r_if
c_cond
(paren
id|nand_scan
(paren
id|au1550_mtd
comma
l_int|1
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|outio
suffix:semicolon
)brace
multiline_comment|/* Register the partitions */
id|add_mtd_partitions
c_func
(paren
id|au1550_mtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|outio
suffix:colon
id|iounmap
(paren
(paren
r_void
op_star
)paren
id|p_nand
)paren
suffix:semicolon
id|outmem
suffix:colon
id|kfree
(paren
id|au1550_mtd
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|au1550_init
id|module_init
c_func
(paren
id|au1550_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up routine&n; */
macro_line|#ifdef MODULE
DECL|function|au1550_cleanup
r_static
r_void
id|__exit
id|au1550_cleanup
(paren
r_void
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
op_assign
(paren
r_struct
id|nand_chip
op_star
)paren
op_amp
id|au1550_mtd
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Release resources, unregister device */
id|nand_release
(paren
id|au1550_mtd
)paren
suffix:semicolon
multiline_comment|/* Free the MTD device structure */
id|kfree
(paren
id|au1550_mtd
)paren
suffix:semicolon
multiline_comment|/* Unmap */
id|iounmap
(paren
(paren
r_void
op_star
)paren
id|p_nand
)paren
suffix:semicolon
)brace
DECL|variable|au1550_cleanup
id|module_exit
c_func
(paren
id|au1550_cleanup
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Embedded Edge, LLC&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Board-specific glue layer for NAND flash on Pb1550 board&quot;
)paren
suffix:semicolon
eof
