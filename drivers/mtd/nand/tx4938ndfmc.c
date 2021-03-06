multiline_comment|/*&n; * drivers/mtd/nand/tx4938ndfmc.c&n; *&n; *  Overview:&n; *   This is a device driver for the NAND flash device connected to&n; *   TX4938 internal NAND Memory Controller.&n; *   TX4938 NDFMC is almost same as TX4925 NDFMC, but register size are 64 bit.&n; *&n; * Author: source@mvista.com&n; *&n; * Based on spia.c by Steven J. Hill&n; *&n; * $Id: tx4938ndfmc.c,v 1.4 2004/10/05 13:50:20 gleixner Exp $&n; *&n; * Copyright (C) 2000-2001 Toshiba Corporation &n; *&n; * 2003 (c) MontaVista Software, Inc. This file is licensed under the&n; * terms of the GNU General Public License version 2. This program is&n; * licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/nand_ecc.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/tx4938/rbtx4938.h&gt;
r_extern
r_struct
id|nand_oobinfo
id|jffs2_oobinfo
suffix:semicolon
multiline_comment|/*&n; * MTD structure for TX4938 NDFMC&n; */
DECL|variable|tx4938ndfmc_mtd
r_static
r_struct
id|mtd_info
op_star
id|tx4938ndfmc_mtd
suffix:semicolon
multiline_comment|/*&n; * Define partitions for flash device&n; */
DECL|macro|flush_wb
mdefine_line|#define flush_wb()&t;(void)tx4938_ndfmcptr-&gt;mcr;
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS  &t;3
DECL|macro|NUMBER_OF_CIS_BLOCKS
mdefine_line|#define NUMBER_OF_CIS_BLOCKS&t;24
DECL|macro|SIZE_OF_BLOCK
mdefine_line|#define SIZE_OF_BLOCK&t;&t;0x00004000
DECL|macro|NUMBER_OF_BLOCK_PER_ZONE
mdefine_line|#define NUMBER_OF_BLOCK_PER_ZONE 1024
DECL|macro|SIZE_OF_ZONE
mdefine_line|#define SIZE_OF_ZONE&t;&t;(NUMBER_OF_BLOCK_PER_ZONE * SIZE_OF_BLOCK)
macro_line|#ifndef CONFIG_MTD_CMDLINE_PARTS
multiline_comment|/*&n; * You can use the following sample of MTD partitions &n; * on the NAND Flash Memory 32MB or more.&n; *&n; * The following figure shows the image of the sample partition on&n; * the 32MB NAND Flash Memory. &n; *&n; *   Block No.&n; *    0 +-----------------------------+ ------&n; *      |             CIS             |   ^&n; *   24 +-----------------------------+   |&n; *      |         kernel image        |   | Zone 0&n; *      |                             |   |&n; *      +-----------------------------+   |&n; * 1023 |         unused area         |   v&n; *      +-----------------------------+ ------&n; * 1024 |            JFFS2            |   ^&n; *      |                             |   |&n; *      |                             |   | Zone 1&n; *      |                             |   |&n; *      |                             |   |&n; *      |                             |   v&n; * 2047 +-----------------------------+ ------&n; *&n; */
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
id|NUM_PARTITIONS
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;RBTX4938 CIS Area&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
(paren
id|NUMBER_OF_CIS_BLOCKS
op_star
id|SIZE_OF_BLOCK
)paren
comma
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* This partition is NOT writable */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;RBTX4938 kernel image&quot;
comma
dot
id|offset
op_assign
id|MTDPART_OFS_APPEND
comma
dot
id|size
op_assign
l_int|8
op_star
l_int|0x00100000
comma
multiline_comment|/* 8MB (Depends on size of kernel image) */
dot
id|mask_flags
op_assign
id|MTD_WRITEABLE
multiline_comment|/* This partition is NOT writable */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;Root FS (JFFS2)&quot;
comma
dot
id|offset
op_assign
(paren
l_int|0
op_plus
id|SIZE_OF_ZONE
)paren
comma
multiline_comment|/* start address of next zone */
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|tx4938ndfmc_hwcontrol
r_static
r_void
id|tx4938ndfmc_hwcontrol
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NAND_CTL_SETCLE
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_or_assign
id|TX4938_NDFMCR_CLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRCLE
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_and_assign
op_complement
id|TX4938_NDFMCR_CLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETALE
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_or_assign
id|TX4938_NDFMCR_ALE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRALE
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_and_assign
op_complement
id|TX4938_NDFMCR_ALE
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* TX4938_NDFMCR_CE bit is 0:high 1:low */
r_case
id|NAND_CTL_SETNCE
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_or_assign
id|TX4938_NDFMCR_CE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRNCE
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_and_assign
op_complement
id|TX4938_NDFMCR_CE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETWP
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_or_assign
id|TX4938_NDFMCR_WE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRWP
suffix:colon
id|tx4938_ndfmcptr-&gt;mcr
op_and_assign
op_complement
id|TX4938_NDFMCR_WE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|tx4938ndfmc_dev_ready
r_static
r_int
id|tx4938ndfmc_dev_ready
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
id|flush_wb
c_func
(paren
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|tx4938_ndfmcptr-&gt;sr
op_amp
id|TX4938_NDFSR_BUSY
)paren
suffix:semicolon
)brace
DECL|function|tx4938ndfmc_calculate_ecc
r_static
r_void
id|tx4938ndfmc_calculate_ecc
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
id|dat
comma
id|u_char
op_star
id|ecc_code
)paren
(brace
id|u32
id|mcr
op_assign
id|tx4938_ndfmcptr-&gt;mcr
suffix:semicolon
id|mcr
op_and_assign
op_complement
id|TX4938_NDFMCR_ECC_ALL
suffix:semicolon
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|mcr
op_or
id|TX4938_NDFMCR_ECC_OFF
suffix:semicolon
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|mcr
op_or
id|TX4938_NDFMCR_ECC_READ
suffix:semicolon
id|ecc_code
(braket
l_int|1
)braket
op_assign
id|tx4938_ndfmcptr-&gt;dtr
suffix:semicolon
id|ecc_code
(braket
l_int|0
)braket
op_assign
id|tx4938_ndfmcptr-&gt;dtr
suffix:semicolon
id|ecc_code
(braket
l_int|2
)braket
op_assign
id|tx4938_ndfmcptr-&gt;dtr
suffix:semicolon
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|mcr
op_or
id|TX4938_NDFMCR_ECC_OFF
suffix:semicolon
)brace
DECL|function|tx4938ndfmc_enable_hwecc
r_static
r_void
id|tx4938ndfmc_enable_hwecc
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|mode
)paren
(brace
id|u32
id|mcr
op_assign
id|tx4938_ndfmcptr-&gt;mcr
suffix:semicolon
id|mcr
op_and_assign
op_complement
id|TX4938_NDFMCR_ECC_ALL
suffix:semicolon
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|mcr
op_or
id|TX4938_NDFMCR_ECC_RESET
suffix:semicolon
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|mcr
op_or
id|TX4938_NDFMCR_ECC_OFF
suffix:semicolon
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|mcr
op_or
id|TX4938_NDFMCR_ECC_ON
suffix:semicolon
)brace
DECL|function|tx4938ndfmc_nand_read_byte
r_static
id|u_char
id|tx4938ndfmc_nand_read_byte
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
r_return
id|tx4938_read_nfmc
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
suffix:semicolon
)brace
DECL|function|tx4938ndfmc_nand_write_byte
r_static
r_void
id|tx4938ndfmc_nand_write_byte
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
id|tx4938_write_nfmc
c_func
(paren
id|byte
comma
id|this-&gt;IO_ADDR_W
)paren
suffix:semicolon
)brace
DECL|function|tx4938ndfmc_nand_write_buf
r_static
r_void
id|tx4938ndfmc_nand_write_buf
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
id|tx4938_write_nfmc
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
)brace
DECL|function|tx4938ndfmc_nand_read_buf
r_static
r_void
id|tx4938ndfmc_nand_read_buf
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
id|buf
(braket
id|i
)braket
op_assign
id|tx4938_read_nfmc
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
suffix:semicolon
)brace
DECL|function|tx4938ndfmc_nand_verify_buf
r_static
r_int
id|tx4938ndfmc_nand_verify_buf
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
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_ne
id|tx4938_read_nfmc
c_func
(paren
id|this-&gt;IO_ADDR_R
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Send command to NAND device&n; */
DECL|function|tx4938ndfmc_nand_command
r_static
r_void
id|tx4938ndfmc_nand_command
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|command
comma
r_int
id|column
comma
r_int
id|page_addr
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
multiline_comment|/* Begin command latch cycle */
id|this
op_member_access_from_pointer
id|hwcontrol
c_func
(paren
id|mtd
comma
id|NAND_CTL_SETCLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Write out the command to the device.&n;&t; */
r_if
c_cond
(paren
id|command
op_eq
id|NAND_CMD_SEQIN
)paren
(brace
r_int
id|readcmd
suffix:semicolon
r_if
c_cond
(paren
id|column
op_ge
id|mtd-&gt;oobblock
)paren
(brace
multiline_comment|/* OOB area */
id|column
op_sub_assign
id|mtd-&gt;oobblock
suffix:semicolon
id|readcmd
op_assign
id|NAND_CMD_READOOB
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|column
OL
l_int|256
)paren
(brace
multiline_comment|/* First 256 bytes --&gt; READ0 */
id|readcmd
op_assign
id|NAND_CMD_READ0
suffix:semicolon
)brace
r_else
(brace
id|column
op_sub_assign
l_int|256
suffix:semicolon
id|readcmd
op_assign
id|NAND_CMD_READ1
suffix:semicolon
)brace
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
id|readcmd
)paren
suffix:semicolon
)brace
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
id|command
)paren
suffix:semicolon
multiline_comment|/* Set ALE and clear CLE to start address cycle */
id|this
op_member_access_from_pointer
id|hwcontrol
c_func
(paren
id|mtd
comma
id|NAND_CTL_CLRCLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|column
op_ne
op_minus
l_int|1
op_logical_or
id|page_addr
op_ne
op_minus
l_int|1
)paren
(brace
id|this
op_member_access_from_pointer
id|hwcontrol
c_func
(paren
id|mtd
comma
id|NAND_CTL_SETALE
)paren
suffix:semicolon
multiline_comment|/* Serially input address */
r_if
c_cond
(paren
id|column
op_ne
op_minus
l_int|1
)paren
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
id|column
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_addr
op_ne
op_minus
l_int|1
)paren
(brace
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
(paren
r_int
r_char
)paren
(paren
id|page_addr
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
(paren
r_int
r_char
)paren
(paren
(paren
id|page_addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
multiline_comment|/* One more address cycle for higher density devices */
r_if
c_cond
(paren
id|mtd-&gt;size
op_amp
l_int|0x0c000000
)paren
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
(paren
r_int
r_char
)paren
(paren
(paren
id|page_addr
op_rshift
l_int|16
)paren
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Latch in address */
id|this
op_member_access_from_pointer
id|hwcontrol
c_func
(paren
id|mtd
comma
id|NAND_CTL_CLRALE
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * program and erase have their own busy handlers &n;&t; * status and sequential in needs no delay&n;&t;*/
r_switch
c_cond
(paren
id|command
)paren
(brace
r_case
id|NAND_CMD_PAGEPROG
suffix:colon
multiline_comment|/* Turn off WE */
id|this-&gt;hwcontrol
(paren
id|mtd
comma
id|NAND_CTL_CLRWP
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|NAND_CMD_SEQIN
suffix:colon
multiline_comment|/* Turn on WE */
id|this-&gt;hwcontrol
(paren
id|mtd
comma
id|NAND_CTL_SETWP
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|NAND_CMD_ERASE1
suffix:colon
r_case
id|NAND_CMD_ERASE2
suffix:colon
r_case
id|NAND_CMD_STATUS
suffix:colon
r_return
suffix:semicolon
r_case
id|NAND_CMD_RESET
suffix:colon
r_if
c_cond
(paren
id|this-&gt;dev_ready
)paren
r_break
suffix:semicolon
id|this
op_member_access_from_pointer
id|hwcontrol
c_func
(paren
id|mtd
comma
id|NAND_CTL_SETCLE
)paren
suffix:semicolon
id|this
op_member_access_from_pointer
id|write_byte
c_func
(paren
id|mtd
comma
id|NAND_CMD_STATUS
)paren
suffix:semicolon
id|this
op_member_access_from_pointer
id|hwcontrol
c_func
(paren
id|mtd
comma
id|NAND_CTL_CLRCLE
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|this
op_member_access_from_pointer
id|read_byte
c_func
(paren
id|mtd
)paren
op_amp
l_int|0x40
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* This applies to read commands */
r_default
suffix:colon
(brace
)brace
multiline_comment|/* &n;&t;&t; * If we don&squot;t have access to the busy pin, we apply the given&n;&t;&t; * command delay&n;&t;&t;*/
r_if
c_cond
(paren
op_logical_neg
id|this-&gt;dev_ready
)paren
(brace
id|udelay
(paren
id|this-&gt;chip_delay
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* wait until command is processed */
r_while
c_loop
(paren
op_logical_neg
id|this
op_member_access_from_pointer
id|dev_ready
c_func
(paren
id|mtd
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_CMDLINE_PARTS
r_extern
r_int
id|parse_cmdline_partitions
c_func
(paren
r_struct
id|mtd_info
op_star
id|master
comma
r_struct
id|mtd_partition
op_star
op_star
id|pparts
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Main initialization routine&n; */
DECL|function|tx4938ndfmc_init
r_int
id|__init
id|tx4938ndfmc_init
(paren
r_void
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
suffix:semicolon
r_int
id|bsprt
op_assign
l_int|0
comma
id|hold
op_assign
l_int|0xf
comma
id|spw
op_assign
l_int|0xf
suffix:semicolon
r_int
r_protected
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|rbtx4938_piosel_ptr
op_amp
l_int|0x0c
)paren
op_ne
l_int|0x08
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TX4938 NDFMC: disabled by IOC PIOSEL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|bsprt
op_assign
l_int|1
suffix:semicolon
id|hold
op_assign
l_int|2
suffix:semicolon
id|spw
op_assign
l_int|9
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* 8 GBUSCLK = 80ns (@ GBUSCLK 100MHz) */
r_if
c_cond
(paren
(paren
id|tx4938_ccfgptr-&gt;pcfg
op_amp
(paren
id|TX4938_PCFG_ATA_SEL
op_or
id|TX4938_PCFG_ISA_SEL
op_or
id|TX4938_PCFG_NDF_SEL
)paren
)paren
op_ne
id|TX4938_PCFG_NDF_SEL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TX4938 NDFMC: disabled by PCFG.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* reset NDFMC */
id|tx4938_ndfmcptr-&gt;rstr
op_or_assign
id|TX4938_NDFRSTR_RST
suffix:semicolon
r_while
c_loop
(paren
id|tx4938_ndfmcptr-&gt;rstr
op_amp
id|TX4938_NDFRSTR_RST
)paren
suffix:semicolon
multiline_comment|/* setup BusSeparete, Hold Time, Strobe Pulse Width */
id|tx4938_ndfmcptr-&gt;mcr
op_assign
id|bsprt
ques
c_cond
id|TX4938_NDFMCR_BSPRT
suffix:colon
l_int|0
suffix:semicolon
id|tx4938_ndfmcptr-&gt;spr
op_assign
id|hold
op_lshift
l_int|4
op_or
id|spw
suffix:semicolon
multiline_comment|/* Allocate memory for MTD device structure and private data */
id|tx4938ndfmc_mtd
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
id|tx4938ndfmc_mtd
)paren
(brace
id|printk
(paren
l_string|&quot;Unable to allocate TX4938 NDFMC MTD device structure.&bslash;n&quot;
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
id|tx4938ndfmc_mtd
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
id|tx4938ndfmc_mtd
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
id|tx4938ndfmc_mtd-&gt;priv
op_assign
id|this
suffix:semicolon
multiline_comment|/* Set address of NAND IO lines */
id|this-&gt;IO_ADDR_R
op_assign
(paren
r_int
r_int
)paren
op_amp
id|tx4938_ndfmcptr-&gt;dtr
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_int
r_int
)paren
op_amp
id|tx4938_ndfmcptr-&gt;dtr
suffix:semicolon
id|this-&gt;hwcontrol
op_assign
id|tx4938ndfmc_hwcontrol
suffix:semicolon
id|this-&gt;dev_ready
op_assign
id|tx4938ndfmc_dev_ready
suffix:semicolon
id|this-&gt;calculate_ecc
op_assign
id|tx4938ndfmc_calculate_ecc
suffix:semicolon
id|this-&gt;correct_data
op_assign
id|nand_correct_data
suffix:semicolon
id|this-&gt;enable_hwecc
op_assign
id|tx4938ndfmc_enable_hwecc
suffix:semicolon
id|this-&gt;eccmode
op_assign
id|NAND_ECC_HW3_256
suffix:semicolon
id|this-&gt;chip_delay
op_assign
l_int|100
suffix:semicolon
id|this-&gt;read_byte
op_assign
id|tx4938ndfmc_nand_read_byte
suffix:semicolon
id|this-&gt;write_byte
op_assign
id|tx4938ndfmc_nand_write_byte
suffix:semicolon
id|this-&gt;cmdfunc
op_assign
id|tx4938ndfmc_nand_command
suffix:semicolon
id|this-&gt;write_buf
op_assign
id|tx4938ndfmc_nand_write_buf
suffix:semicolon
id|this-&gt;read_buf
op_assign
id|tx4938ndfmc_nand_read_buf
suffix:semicolon
id|this-&gt;verify_buf
op_assign
id|tx4938ndfmc_nand_verify_buf
suffix:semicolon
multiline_comment|/* Scan to find existance of the device */
r_if
c_cond
(paren
id|nand_scan
(paren
id|tx4938ndfmc_mtd
comma
l_int|1
)paren
)paren
(brace
id|kfree
(paren
id|tx4938ndfmc_mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
r_protected
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;TX4938 NDFMC: write protected.&bslash;n&quot;
)paren
suffix:semicolon
id|tx4938ndfmc_mtd-&gt;flags
op_and_assign
op_complement
(paren
id|MTD_WRITEABLE
op_or
id|MTD_ERASEABLE
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_CMDLINE_PARTS
(brace
r_int
id|mtd_parts_nb
op_assign
l_int|0
suffix:semicolon
r_struct
id|mtd_partition
op_star
id|mtd_parts
op_assign
l_int|0
suffix:semicolon
id|mtd_parts_nb
op_assign
id|parse_cmdline_partitions
c_func
(paren
id|tx4938ndfmc_mtd
comma
op_amp
id|mtd_parts
comma
l_string|&quot;tx4938ndfmc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd_parts_nb
OG
l_int|0
)paren
id|add_mtd_partitions
c_func
(paren
id|tx4938ndfmc_mtd
comma
id|mtd_parts
comma
id|mtd_parts_nb
)paren
suffix:semicolon
r_else
id|add_mtd_device
c_func
(paren
id|tx4938ndfmc_mtd
)paren
suffix:semicolon
)brace
macro_line|#else
id|add_mtd_partitions
c_func
(paren
id|tx4938ndfmc_mtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tx4938ndfmc_init
id|module_init
c_func
(paren
id|tx4938ndfmc_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up routine&n; */
DECL|function|tx4938ndfmc_cleanup
r_static
r_void
id|__exit
id|tx4938ndfmc_cleanup
(paren
r_void
)paren
(brace
multiline_comment|/* Release resources, unregister device */
id|nand_release
(paren
id|tx4938ndfmc_mtd
)paren
suffix:semicolon
multiline_comment|/* Free the MTD device structure */
id|kfree
(paren
id|tx4938ndfmc_mtd
)paren
suffix:semicolon
)brace
DECL|variable|tx4938ndfmc_cleanup
id|module_exit
c_func
(paren
id|tx4938ndfmc_cleanup
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
l_string|&quot;Alice Hennessy &lt;ahennessy@mvista.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Board-specific glue layer for NAND flash on TX4938 NDFMC&quot;
)paren
suffix:semicolon
eof
