multiline_comment|/* linux/drivers/mtd/nand/s3c2410.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Samsung S3C2410 NAND driver&n; *&n; * Changelog:&n; *&t;21-Sep-2004  BJD  Initial version&n; *&t;23-Sep-2004  BJD  Mulitple device support&n; *&t;28-Sep-2004  BJD  Fixed ECC placement for Hardware mode&n; *&t;12-Oct-2004  BJD  Fixed errors in use of platform data&n; *&n; * $Id: s3c2410.c,v 1.7 2005/01/05 18:05:14 dwmw2 Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;config/mtd/nand/s3c2410/hwecc.h&gt;
macro_line|#include &lt;config/mtd/nand/s3c2410/debug.h&gt;
macro_line|#ifdef CONFIG_MTD_NAND_S3C2410_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/nand_ecc.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/clock.h&gt;
macro_line|#include &lt;asm/arch/regs-nand.h&gt;
macro_line|#include &lt;asm/arch/nand.h&gt;
DECL|macro|PFX
mdefine_line|#define PFX &quot;s3c2410-nand: &quot;
macro_line|#ifdef CONFIG_MTD_NAND_S3C2410_HWECC
DECL|variable|hardware_ecc
r_static
r_int
id|hardware_ecc
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|hardware_ecc
r_static
r_int
id|hardware_ecc
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* new oob placement block for use with hardware ecc generation&n; */
DECL|variable|nand_hw_eccoob
r_static
r_struct
id|nand_oobinfo
id|nand_hw_eccoob
op_assign
(brace
dot
id|useecc
op_assign
id|MTD_NANDECC_AUTOPLACE
comma
dot
id|eccbytes
op_assign
l_int|3
comma
dot
id|eccpos
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
)brace
comma
dot
id|oobfree
op_assign
(brace
(brace
l_int|8
comma
l_int|8
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/* controller and mtd information */
r_struct
id|s3c2410_nand_info
suffix:semicolon
DECL|struct|s3c2410_nand_mtd
r_struct
id|s3c2410_nand_mtd
(brace
DECL|member|mtd
r_struct
id|mtd_info
id|mtd
suffix:semicolon
DECL|member|chip
r_struct
id|nand_chip
id|chip
suffix:semicolon
DECL|member|set
r_struct
id|s3c2410_nand_set
op_star
id|set
suffix:semicolon
DECL|member|info
r_struct
id|s3c2410_nand_info
op_star
id|info
suffix:semicolon
DECL|member|scan_res
r_int
id|scan_res
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* overview of the s3c2410 nand state */
DECL|struct|s3c2410_nand_info
r_struct
id|s3c2410_nand_info
(brace
multiline_comment|/* mtd info */
DECL|member|controller
r_struct
id|nand_hw_control
id|controller
suffix:semicolon
DECL|member|mtds
r_struct
id|s3c2410_nand_mtd
op_star
id|mtds
suffix:semicolon
DECL|member|platform
r_struct
id|s3c2410_platform_nand
op_star
id|platform
suffix:semicolon
multiline_comment|/* device info */
DECL|member|device
r_struct
id|device
op_star
id|device
suffix:semicolon
DECL|member|area
r_struct
id|resource
op_star
id|area
suffix:semicolon
DECL|member|clk
r_struct
id|clk
op_star
id|clk
suffix:semicolon
DECL|member|regs
r_void
op_star
id|regs
suffix:semicolon
DECL|member|mtd_count
r_int
id|mtd_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* conversion functions */
DECL|function|s3c2410_nand_mtd_toours
r_static
r_struct
id|s3c2410_nand_mtd
op_star
id|s3c2410_nand_mtd_toours
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_return
id|container_of
c_func
(paren
id|mtd
comma
r_struct
id|s3c2410_nand_mtd
comma
id|mtd
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_nand_mtd_toinfo
r_static
r_struct
id|s3c2410_nand_info
op_star
id|s3c2410_nand_mtd_toinfo
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_return
id|s3c2410_nand_mtd_toours
c_func
(paren
id|mtd
)paren
op_member_access_from_pointer
id|info
suffix:semicolon
)brace
DECL|function|to_nand_info
r_static
r_struct
id|s3c2410_nand_info
op_star
id|to_nand_info
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|to_nand_plat
r_static
r_struct
id|s3c2410_platform_nand
op_star
id|to_nand_plat
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;platform_data
suffix:semicolon
)brace
multiline_comment|/* timing calculations */
DECL|macro|NS_IN_KHZ
mdefine_line|#define NS_IN_KHZ 10000000
DECL|function|s3c2410_nand_calc_rate
r_static
r_int
id|s3c2410_nand_calc_rate
c_func
(paren
r_int
id|wanted
comma
r_int
r_int
id|clk
comma
r_int
id|max
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
(paren
id|wanted
op_star
id|NS_IN_KHZ
)paren
op_div
id|clk
suffix:semicolon
id|result
op_increment
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;result %d from %ld, %d&bslash;n&quot;
comma
id|result
comma
id|clk
comma
id|wanted
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
id|max
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%d ns is too big for current clock rate %ld&bslash;n&quot;
comma
id|wanted
comma
id|clk
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
l_int|1
)paren
id|result
op_assign
l_int|1
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|to_ns
mdefine_line|#define to_ns(ticks,clk) (((clk) * (ticks)) / NS_IN_KHZ)
multiline_comment|/* controller setup */
DECL|function|s3c2410_nand_inithw
r_static
r_int
id|s3c2410_nand_inithw
c_func
(paren
r_struct
id|s3c2410_nand_info
op_star
id|info
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|s3c2410_platform_nand
op_star
id|plat
op_assign
id|to_nand_plat
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|tacls
comma
id|twrph0
comma
id|twrph1
suffix:semicolon
r_int
r_int
id|clkrate
op_assign
id|clk_get_rate
c_func
(paren
id|info-&gt;clk
)paren
suffix:semicolon
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/* calculate the timing information for the controller */
r_if
c_cond
(paren
id|plat
op_ne
l_int|NULL
)paren
(brace
id|tacls
op_assign
id|s3c2410_nand_calc_rate
c_func
(paren
id|plat-&gt;tacls
comma
id|clkrate
comma
l_int|8
)paren
suffix:semicolon
id|twrph0
op_assign
id|s3c2410_nand_calc_rate
c_func
(paren
id|plat-&gt;twrph0
comma
id|clkrate
comma
l_int|8
)paren
suffix:semicolon
id|twrph1
op_assign
id|s3c2410_nand_calc_rate
c_func
(paren
id|plat-&gt;twrph1
comma
id|clkrate
comma
l_int|8
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* default timings */
id|tacls
op_assign
l_int|8
suffix:semicolon
id|twrph0
op_assign
l_int|8
suffix:semicolon
id|twrph1
op_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tacls
OL
l_int|0
op_logical_or
id|twrph0
OL
l_int|0
op_logical_or
id|twrph1
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot get timings suitable for board&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;timing: Tacls %ldns, Twrph0 %ldns, Twrph1 %ldns&bslash;n&quot;
comma
id|to_ns
c_func
(paren
id|tacls
comma
id|clkrate
)paren
comma
id|to_ns
c_func
(paren
id|twrph0
comma
id|clkrate
)paren
comma
id|to_ns
c_func
(paren
id|twrph1
comma
id|clkrate
)paren
)paren
suffix:semicolon
id|cfg
op_assign
id|S3C2410_NFCONF_EN
suffix:semicolon
id|cfg
op_or_assign
id|S3C2410_NFCONF_TACLS
c_func
(paren
id|tacls
op_minus
l_int|1
)paren
suffix:semicolon
id|cfg
op_or_assign
id|S3C2410_NFCONF_TWRPH0
c_func
(paren
id|twrph0
op_minus
l_int|1
)paren
suffix:semicolon
id|cfg
op_or_assign
id|S3C2410_NFCONF_TWRPH1
c_func
(paren
id|twrph1
op_minus
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
id|PFX
l_string|&quot;NF_CONF is 0x%lx&bslash;n&quot;
comma
id|cfg
)paren
suffix:semicolon
id|writel
c_func
(paren
id|cfg
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* select chip */
DECL|function|s3c2410_nand_select_chip
r_static
r_void
id|s3c2410_nand_select_chip
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|chip
)paren
(brace
r_struct
id|s3c2410_nand_info
op_star
id|info
suffix:semicolon
r_struct
id|s3c2410_nand_mtd
op_star
id|nmtd
suffix:semicolon
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
r_int
r_int
id|cur
suffix:semicolon
id|nmtd
op_assign
id|this-&gt;priv
suffix:semicolon
id|info
op_assign
id|nmtd-&gt;info
suffix:semicolon
id|cur
op_assign
id|readl
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip
op_eq
op_minus
l_int|1
)paren
(brace
id|cur
op_or_assign
id|S3C2410_NFCONF_nFCE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|chip
OG
id|nmtd-&gt;set-&gt;nr_chips
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;chip %d out of range&bslash;n&quot;
comma
id|chip
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;platform
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;platform-&gt;select_chip
op_ne
l_int|NULL
)paren
(paren
id|info-&gt;platform-&gt;select_chip
)paren
(paren
id|nmtd-&gt;set
comma
id|chip
)paren
suffix:semicolon
)brace
id|cur
op_and_assign
op_complement
id|S3C2410_NFCONF_nFCE
suffix:semicolon
)brace
id|writel
c_func
(paren
id|cur
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
)brace
multiline_comment|/* command and control functions */
DECL|function|s3c2410_nand_hwcontrol
r_static
r_void
id|s3c2410_nand_hwcontrol
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
r_struct
id|s3c2410_nand_info
op_star
id|info
op_assign
id|s3c2410_nand_mtd_toinfo
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_int
r_int
id|cur
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NAND_CTL_SETNCE
suffix:colon
id|cur
op_assign
id|readl
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
id|cur
op_and_assign
op_complement
id|S3C2410_NFCONF_nFCE
suffix:semicolon
id|writel
c_func
(paren
id|cur
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRNCE
suffix:colon
id|cur
op_assign
id|readl
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
id|cur
op_or_assign
id|S3C2410_NFCONF_nFCE
suffix:semicolon
id|writel
c_func
(paren
id|cur
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* we don&squot;t need to implement these */
r_case
id|NAND_CTL_SETCLE
suffix:colon
r_case
id|NAND_CTL_CLRCLE
suffix:colon
r_case
id|NAND_CTL_SETALE
suffix:colon
r_case
id|NAND_CTL_CLRALE
suffix:colon
id|pr_debug
c_func
(paren
id|PFX
l_string|&quot;s3c2410_nand_hwcontrol(%d) unusedn&quot;
comma
id|cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* s3c2410_nand_command&n; *&n; * This function implements sending commands and the relevant address&n; * information to the chip, via the hardware controller. Since the&n; * S3C2410 generates the correct ALE/CLE signaling automatically, we&n; * do not need to use hwcontrol.&n;*/
DECL|function|s3c2410_nand_command
r_static
r_void
id|s3c2410_nand_command
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
id|s3c2410_nand_info
op_star
id|info
op_assign
id|s3c2410_nand_mtd_toinfo
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_register
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
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
id|writeb
c_func
(paren
id|readcmd
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCMD
)paren
suffix:semicolon
)brace
id|writeb
c_func
(paren
id|command
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCMD
)paren
suffix:semicolon
multiline_comment|/* Set ALE and clear CLE to start address cycle */
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
multiline_comment|/* Serially input address */
r_if
c_cond
(paren
id|column
op_ne
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Adjust columns for 16 bit buswidth */
r_if
c_cond
(paren
id|this-&gt;options
op_amp
id|NAND_BUSWIDTH_16
)paren
id|column
op_rshift_assign
l_int|1
suffix:semicolon
id|writeb
c_func
(paren
id|column
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFADDR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page_addr
op_ne
op_minus
l_int|1
)paren
(brace
id|writeb
c_func
(paren
(paren
r_int
r_char
)paren
(paren
id|page_addr
)paren
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFADDR
)paren
suffix:semicolon
id|writeb
c_func
(paren
(paren
r_int
r_char
)paren
(paren
id|page_addr
op_rshift
l_int|8
)paren
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFADDR
)paren
suffix:semicolon
multiline_comment|/* One more address cycle for higher density devices */
r_if
c_cond
(paren
id|this-&gt;chipsize
op_amp
l_int|0x0c000000
)paren
id|writeb
c_func
(paren
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
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFADDR
)paren
suffix:semicolon
)brace
multiline_comment|/* Latch in address */
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
r_case
id|NAND_CMD_ERASE1
suffix:colon
r_case
id|NAND_CMD_ERASE2
suffix:colon
r_case
id|NAND_CMD_SEQIN
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
id|udelay
c_func
(paren
id|this-&gt;chip_delay
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|NAND_CMD_STATUS
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCMD
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
multiline_comment|/* Apply this short delay always to ensure that we do wait tWB in&n;&t; * any case on any machine. */
id|ndelay
(paren
l_int|100
)paren
suffix:semicolon
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
multiline_comment|/* s3c2410_nand_devready()&n; *&n; * returns 0 if the nand is busy, 1 if it is ready&n;*/
DECL|function|s3c2410_nand_devready
r_static
r_int
id|s3c2410_nand_devready
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_struct
id|s3c2410_nand_info
op_star
id|info
op_assign
id|s3c2410_nand_mtd_toinfo
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
id|readb
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFSTAT
)paren
op_amp
id|S3C2410_NFSTAT_BUSY
suffix:semicolon
)brace
multiline_comment|/* ECC handling functions */
DECL|function|s3c2410_nand_correct_data
r_static
r_int
id|s3c2410_nand_correct_data
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|dat
comma
id|u_char
op_star
id|read_ecc
comma
id|u_char
op_star
id|calc_ecc
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_nand_correct_data(%p,%p,%p,%p)&bslash;n&quot;
comma
id|mtd
comma
id|dat
comma
id|read_ecc
comma
id|calc_ecc
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;eccs: read %02x,%02x,%02x vs calc %02x,%02x,%02x&bslash;n&quot;
comma
id|read_ecc
(braket
l_int|0
)braket
comma
id|read_ecc
(braket
l_int|1
)braket
comma
id|read_ecc
(braket
l_int|2
)braket
comma
id|calc_ecc
(braket
l_int|0
)braket
comma
id|calc_ecc
(braket
l_int|1
)braket
comma
id|calc_ecc
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_ecc
(braket
l_int|0
)braket
op_eq
id|calc_ecc
(braket
l_int|0
)braket
op_logical_and
id|read_ecc
(braket
l_int|1
)braket
op_eq
id|calc_ecc
(braket
l_int|1
)braket
op_logical_and
id|read_ecc
(braket
l_int|2
)braket
op_eq
id|calc_ecc
(braket
l_int|2
)braket
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we curently have no method for correcting the error */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|s3c2410_nand_enable_hwecc
r_static
r_void
id|s3c2410_nand_enable_hwecc
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
r_struct
id|s3c2410_nand_info
op_star
id|info
op_assign
id|s3c2410_nand_mtd_toinfo
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_int
r_int
id|ctrl
suffix:semicolon
id|ctrl
op_assign
id|readl
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
id|ctrl
op_or_assign
id|S3C2410_NFCONF_INITECC
suffix:semicolon
id|writel
c_func
(paren
id|ctrl
comma
id|info-&gt;regs
op_plus
id|S3C2410_NFCONF
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_nand_calculate_ecc
r_static
r_int
id|s3c2410_nand_calculate_ecc
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
r_struct
id|s3c2410_nand_info
op_star
id|info
op_assign
id|s3c2410_nand_mtd_toinfo
c_func
(paren
id|mtd
)paren
suffix:semicolon
id|ecc_code
(braket
l_int|0
)braket
op_assign
id|readb
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFECC
op_plus
l_int|0
)paren
suffix:semicolon
id|ecc_code
(braket
l_int|1
)braket
op_assign
id|readb
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFECC
op_plus
l_int|1
)paren
suffix:semicolon
id|ecc_code
(braket
l_int|2
)braket
op_assign
id|readb
c_func
(paren
id|info-&gt;regs
op_plus
id|S3C2410_NFECC
op_plus
l_int|2
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;calculate_ecc: returning ecc %02x,%02x,%02x&bslash;n&quot;
comma
id|ecc_code
(braket
l_int|0
)braket
comma
id|ecc_code
(braket
l_int|1
)braket
comma
id|ecc_code
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* over-ride the standard functions for a little more speed? */
DECL|function|s3c2410_nand_read_buf
r_static
r_void
id|s3c2410_nand_read_buf
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
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|readsb
c_func
(paren
id|this-&gt;IO_ADDR_R
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_nand_write_buf
r_static
r_void
id|s3c2410_nand_write_buf
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
r_struct
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|writesb
c_func
(paren
id|this-&gt;IO_ADDR_W
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* device management functions */
DECL|function|s3c2410_nand_remove
r_static
r_int
id|s3c2410_nand_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|s3c2410_nand_info
op_star
id|info
op_assign
id|to_nand_info
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* first thing we need to do is release all our mtds&n;&t; * and their partitions, then go through freeing the&n;&t; * resources used &n;&t; */
r_if
c_cond
(paren
id|info-&gt;mtds
op_ne
l_int|NULL
)paren
(brace
r_struct
id|s3c2410_nand_mtd
op_star
id|ptr
op_assign
id|info-&gt;mtds
suffix:semicolon
r_int
id|mtdno
suffix:semicolon
r_for
c_loop
(paren
id|mtdno
op_assign
l_int|0
suffix:semicolon
id|mtdno
OL
id|info-&gt;mtd_count
suffix:semicolon
id|mtdno
op_increment
comma
id|ptr
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;releasing mtd %d (%p)&bslash;n&quot;
comma
id|mtdno
comma
id|ptr
)paren
suffix:semicolon
id|nand_release
c_func
(paren
op_amp
id|ptr-&gt;mtd
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|info-&gt;mtds
)paren
suffix:semicolon
)brace
multiline_comment|/* free the common resources */
r_if
c_cond
(paren
id|info-&gt;clk
op_ne
l_int|NULL
op_logical_and
op_logical_neg
id|IS_ERR
c_func
(paren
id|info-&gt;clk
)paren
)paren
(brace
id|clk_disable
c_func
(paren
id|info-&gt;clk
)paren
suffix:semicolon
id|clk_unuse
c_func
(paren
id|info-&gt;clk
)paren
suffix:semicolon
id|clk_put
c_func
(paren
id|info-&gt;clk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;regs
op_ne
l_int|NULL
)paren
(brace
id|iounmap
c_func
(paren
id|info-&gt;regs
)paren
suffix:semicolon
id|info-&gt;regs
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;area
op_ne
l_int|NULL
)paren
(brace
id|release_resource
c_func
(paren
id|info-&gt;area
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info-&gt;area
)paren
suffix:semicolon
id|info-&gt;area
op_assign
l_int|NULL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_PARTITIONS
DECL|function|s3c2410_nand_add_partition
r_static
r_int
id|s3c2410_nand_add_partition
c_func
(paren
r_struct
id|s3c2410_nand_info
op_star
id|info
comma
r_struct
id|s3c2410_nand_mtd
op_star
id|mtd
comma
r_struct
id|s3c2410_nand_set
op_star
id|set
)paren
(brace
r_if
c_cond
(paren
id|set
op_eq
l_int|NULL
)paren
r_return
id|add_mtd_device
c_func
(paren
op_amp
id|mtd-&gt;mtd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set-&gt;nr_partitions
OG
l_int|0
op_logical_and
id|set-&gt;partitions
op_ne
l_int|NULL
)paren
(brace
r_return
id|add_mtd_partitions
c_func
(paren
op_amp
id|mtd-&gt;mtd
comma
id|set-&gt;partitions
comma
id|set-&gt;nr_partitions
)paren
suffix:semicolon
)brace
r_return
id|add_mtd_device
c_func
(paren
op_amp
id|mtd-&gt;mtd
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|s3c2410_nand_add_partition
r_static
r_int
id|s3c2410_nand_add_partition
c_func
(paren
r_struct
id|s3c2410_nand_info
op_star
id|info
comma
r_struct
id|s3c2410_nand_mtd
op_star
id|mtd
comma
r_struct
id|s3c2410_nand_set
op_star
id|set
)paren
(brace
r_return
id|add_mtd_device
c_func
(paren
op_amp
id|mtd-&gt;mtd
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* s3c2410_nand_init_chip&n; *&n; * init a single instance of an chip &n;*/
DECL|function|s3c2410_nand_init_chip
r_static
r_void
id|s3c2410_nand_init_chip
c_func
(paren
r_struct
id|s3c2410_nand_info
op_star
id|info
comma
r_struct
id|s3c2410_nand_mtd
op_star
id|nmtd
comma
r_struct
id|s3c2410_nand_set
op_star
id|set
)paren
(brace
r_struct
id|nand_chip
op_star
id|chip
op_assign
op_amp
id|nmtd-&gt;chip
suffix:semicolon
id|chip-&gt;IO_ADDR_R
op_assign
(paren
r_char
op_star
)paren
id|info-&gt;regs
op_plus
id|S3C2410_NFDATA
suffix:semicolon
id|chip-&gt;IO_ADDR_W
op_assign
(paren
r_char
op_star
)paren
id|info-&gt;regs
op_plus
id|S3C2410_NFDATA
suffix:semicolon
id|chip-&gt;hwcontrol
op_assign
id|s3c2410_nand_hwcontrol
suffix:semicolon
id|chip-&gt;dev_ready
op_assign
id|s3c2410_nand_devready
suffix:semicolon
id|chip-&gt;cmdfunc
op_assign
id|s3c2410_nand_command
suffix:semicolon
id|chip-&gt;write_buf
op_assign
id|s3c2410_nand_write_buf
suffix:semicolon
id|chip-&gt;read_buf
op_assign
id|s3c2410_nand_read_buf
suffix:semicolon
id|chip-&gt;select_chip
op_assign
id|s3c2410_nand_select_chip
suffix:semicolon
id|chip-&gt;chip_delay
op_assign
l_int|50
suffix:semicolon
id|chip-&gt;priv
op_assign
id|nmtd
suffix:semicolon
id|chip-&gt;options
op_assign
l_int|0
suffix:semicolon
id|chip-&gt;controller
op_assign
op_amp
id|info-&gt;controller
suffix:semicolon
id|nmtd-&gt;info
op_assign
id|info
suffix:semicolon
id|nmtd-&gt;mtd.priv
op_assign
id|chip
suffix:semicolon
id|nmtd-&gt;set
op_assign
id|set
suffix:semicolon
r_if
c_cond
(paren
id|hardware_ecc
)paren
(brace
id|chip-&gt;correct_data
op_assign
id|s3c2410_nand_correct_data
suffix:semicolon
id|chip-&gt;enable_hwecc
op_assign
id|s3c2410_nand_enable_hwecc
suffix:semicolon
id|chip-&gt;calculate_ecc
op_assign
id|s3c2410_nand_calculate_ecc
suffix:semicolon
id|chip-&gt;eccmode
op_assign
id|NAND_ECC_HW3_512
suffix:semicolon
id|chip-&gt;autooob
op_assign
op_amp
id|nand_hw_eccoob
suffix:semicolon
)brace
r_else
(brace
id|chip-&gt;eccmode
op_assign
id|NAND_ECC_SOFT
suffix:semicolon
)brace
)brace
multiline_comment|/* s3c2410_nand_probe&n; *&n; * called by device layer when it finds a device matching&n; * one our driver can handled. This code checks to see if&n; * it can allocate all necessary resources then calls the&n; * nand layer to look for devices&n;*/
DECL|function|s3c2410_nand_probe
r_static
r_int
id|s3c2410_nand_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|s3c2410_platform_nand
op_star
id|plat
op_assign
id|to_nand_plat
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|s3c2410_nand_info
op_star
id|info
suffix:semicolon
r_struct
id|s3c2410_nand_mtd
op_star
id|nmtd
suffix:semicolon
r_struct
id|s3c2410_nand_set
op_star
id|sets
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|nr_sets
suffix:semicolon
r_int
id|setno
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_nand_probe(%p)&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;no memory for flash info&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|exit_error
suffix:semicolon
)brace
id|memzero
c_func
(paren
id|info
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|info
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|info-&gt;controller.lock
)paren
suffix:semicolon
multiline_comment|/* get the clock source and enable it */
id|info-&gt;clk
op_assign
id|clk_get
c_func
(paren
id|dev
comma
l_string|&quot;nand&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|info-&gt;clk
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;failed to get clock&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|exit_error
suffix:semicolon
)brace
id|clk_use
c_func
(paren
id|info-&gt;clk
)paren
suffix:semicolon
id|clk_enable
c_func
(paren
id|info-&gt;clk
)paren
suffix:semicolon
multiline_comment|/* allocate and map the resource */
id|res
op_assign
id|pdev-&gt;resource
suffix:semicolon
multiline_comment|/* assume that the flash has one resource */
id|size
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
suffix:semicolon
id|info-&gt;area
op_assign
id|request_mem_region
c_func
(paren
id|res-&gt;start
comma
id|size
comma
id|pdev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;area
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot reserve register region&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|exit_error
suffix:semicolon
)brace
id|info-&gt;device
op_assign
id|dev
suffix:semicolon
id|info-&gt;platform
op_assign
id|plat
suffix:semicolon
id|info-&gt;regs
op_assign
id|ioremap
c_func
(paren
id|res-&gt;start
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;regs
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot reserve register region&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|exit_error
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;mapped registers at %p&bslash;n&quot;
comma
id|info-&gt;regs
)paren
suffix:semicolon
multiline_comment|/* initialise the hardware */
id|err
op_assign
id|s3c2410_nand_inithw
c_func
(paren
id|info
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
r_goto
id|exit_error
suffix:semicolon
id|sets
op_assign
(paren
id|plat
op_ne
l_int|NULL
)paren
ques
c_cond
id|plat-&gt;sets
suffix:colon
l_int|NULL
suffix:semicolon
id|nr_sets
op_assign
(paren
id|plat
op_ne
l_int|NULL
)paren
ques
c_cond
id|plat-&gt;nr_sets
suffix:colon
l_int|1
suffix:semicolon
id|info-&gt;mtd_count
op_assign
id|nr_sets
suffix:semicolon
multiline_comment|/* allocate our information */
id|size
op_assign
id|nr_sets
op_star
r_sizeof
(paren
op_star
id|info-&gt;mtds
)paren
suffix:semicolon
id|info-&gt;mtds
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;mtds
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;failed to allocate mtd storage&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|exit_error
suffix:semicolon
)brace
id|memzero
c_func
(paren
id|info-&gt;mtds
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* initialise all possible chips */
id|nmtd
op_assign
id|info-&gt;mtds
suffix:semicolon
r_for
c_loop
(paren
id|setno
op_assign
l_int|0
suffix:semicolon
id|setno
OL
id|nr_sets
suffix:semicolon
id|setno
op_increment
comma
id|nmtd
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;initialising set %d (%p, info %p)&bslash;n&quot;
comma
id|setno
comma
id|nmtd
comma
id|info
)paren
suffix:semicolon
id|s3c2410_nand_init_chip
c_func
(paren
id|info
comma
id|nmtd
comma
id|sets
)paren
suffix:semicolon
id|nmtd-&gt;scan_res
op_assign
id|nand_scan
c_func
(paren
op_amp
id|nmtd-&gt;mtd
comma
(paren
id|sets
)paren
ques
c_cond
id|sets-&gt;nr_chips
suffix:colon
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nmtd-&gt;scan_res
op_eq
l_int|0
)paren
(brace
id|s3c2410_nand_add_partition
c_func
(paren
id|info
comma
id|nmtd
comma
id|sets
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sets
op_ne
l_int|NULL
)paren
id|sets
op_increment
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;initialised ok&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|exit_error
suffix:colon
id|s3c2410_nand_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|s3c2410_nand_driver
r_static
r_struct
id|device_driver
id|s3c2410_nand_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-nand&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|s3c2410_nand_probe
comma
dot
id|remove
op_assign
id|s3c2410_nand_remove
comma
)brace
suffix:semicolon
DECL|function|s3c2410_nand_init
r_static
r_int
id|__init
id|s3c2410_nand_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;S3C2410 NAND Driver, (c) 2004 Simtec Electronics&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|driver_register
c_func
(paren
op_amp
id|s3c2410_nand_driver
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_nand_exit
r_static
r_void
id|__exit
id|s3c2410_nand_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|s3c2410_nand_driver
)paren
suffix:semicolon
)brace
DECL|variable|s3c2410_nand_init
id|module_init
c_func
(paren
id|s3c2410_nand_init
)paren
suffix:semicolon
DECL|variable|s3c2410_nand_exit
id|module_exit
c_func
(paren
id|s3c2410_nand_exit
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
l_string|&quot;Ben Dooks &lt;ben@simtec.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;S3C2410 MTD NAND driver&quot;
)paren
suffix:semicolon
eof
