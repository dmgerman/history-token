multiline_comment|/*&n; *  drivers/mtd/nand/edb7312.c&n; *&n; *  Copyright (C) 2002 Marius Gr&#xfffd;ger (mag@sysgo.de)&n; *&n; *  Derived from drivers/mtd/nand/autcpu12.c&n; *       Copyright (c) 2001 Thomas Gleixner (gleixner@autronix.de)&n; *&n; * $Id: edb7312.c,v 1.5 2003/04/20 07:24:40 gleixner Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Overview:&n; *   This is a device driver for the NAND flash device found on the&n; *   CLEP7312 board which utilizes the Toshiba TC58V64AFT part. This is&n; *   a 64Mibit (8MiB x 8 bits) NAND flash device.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt; /* for CLPS7111_VIRT_BASE */
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
multiline_comment|/*&n; * MTD structure for EDB7312 board&n; */
DECL|variable|ep7312_mtd
r_static
r_struct
id|mtd_info
op_star
id|ep7312_mtd
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Values specific to the EDB7312 board (used with EP7312 processor)&n; */
DECL|macro|EP7312_FIO_PBASE
mdefine_line|#define EP7312_FIO_PBASE 0x10000000&t;/* Phys address of flash */
DECL|macro|EP7312_PXDR
mdefine_line|#define EP7312_PXDR&t;0x0001&t;/*&n;&t;&t;&t;&t; * IO offset to Port B data register&n;&t;&t;&t;&t; * where the CLE, ALE and NCE pins&n;&t;&t;&t;&t; * are wired to.&n;&t;&t;&t;&t; */
DECL|macro|EP7312_PXDDR
mdefine_line|#define EP7312_PXDDR&t;0x0041&t;/*&n;&t;&t;&t;&t; * IO offset to Port B data direction&n;&t;&t;&t;&t; * register so we can control the IO&n;&t;&t;&t;&t; * lines.&n;&t;&t;&t;&t; */
multiline_comment|/*&n; * Module stuff&n; */
DECL|variable|ep7312_fio_pbase
r_static
r_int
id|ep7312_fio_pbase
op_assign
id|EP7312_FIO_PBASE
suffix:semicolon
DECL|variable|ep7312_pxdr
r_static
r_int
id|ep7312_pxdr
op_assign
id|EP7312_PXDR
suffix:semicolon
DECL|variable|ep7312_pxddr
r_static
r_int
id|ep7312_pxddr
op_assign
id|EP7312_PXDDR
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_PARM
c_func
(paren
id|ep7312_fio_pbase
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ep7312_pxdr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ep7312_pxddr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;ep7312_fio_pbase=&quot;
comma
id|ep7312_fio_pbase
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;ep7312_pxdr=&quot;
comma
id|ep7312_pxdr
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;ep7312_pxddr=&quot;
comma
id|ep7312_pxddr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_PARTITIONS
multiline_comment|/*&n; * Define static partitions for flash device&n; */
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;EP7312 Nand Flash&quot;
comma
id|offset
suffix:colon
l_int|0
comma
id|size
suffix:colon
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)brace
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS 1
macro_line|#endif
multiline_comment|/* &n; *&t;hardware specific access to control-lines&n; */
DECL|function|ep7312_hwcontrol
r_static
r_void
id|ep7312_hwcontrol
c_func
(paren
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
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|ep7312_pxdr
)paren
op_or
l_int|0x10
comma
id|ep7312_pxdr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRCLE
suffix:colon
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|ep7312_pxdr
)paren
op_amp
op_complement
l_int|0x10
comma
id|ep7312_pxdr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETALE
suffix:colon
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|ep7312_pxdr
)paren
op_or
l_int|0x20
comma
id|ep7312_pxdr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRALE
suffix:colon
id|clps_writeb
c_func
(paren
id|clps_readb
c_func
(paren
id|ep7312_pxdr
)paren
op_amp
op_complement
l_int|0x20
comma
id|ep7312_pxdr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETNCE
suffix:colon
id|clps_writeb
c_func
(paren
(paren
id|clps_readb
c_func
(paren
id|ep7312_pxdr
)paren
op_or
l_int|0x80
)paren
op_amp
op_complement
l_int|0x40
comma
id|ep7312_pxdr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRNCE
suffix:colon
id|clps_writeb
c_func
(paren
(paren
id|clps_readb
c_func
(paren
id|ep7312_pxdr
)paren
op_or
l_int|0x80
)paren
op_or
l_int|0x40
comma
id|ep7312_pxdr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;read device ready pin&n; */
DECL|function|ep7312_device_ready
r_static
r_int
id|ep7312_device_ready
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Main initialization routine&n; */
DECL|function|ep7312_init
r_static
r_int
id|__init
id|ep7312_init
(paren
r_void
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
suffix:semicolon
r_const
r_char
op_star
id|part_type
op_assign
l_int|0
suffix:semicolon
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
r_int
id|ep7312_fio_base
suffix:semicolon
multiline_comment|/* Allocate memory for MTD device structure and private data */
id|ep7312_mtd
op_assign
id|kmalloc
c_func
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
id|ep7312_mtd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to allocate EDB7312 NAND MTD device structure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* map physical adress */
id|ep7312_fio_base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|ep7312_fio_pbase
comma
id|SZ_1K
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ep7312_fio_base
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ioremap EDB7312 NAND flash failed&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ep7312_mtd
)paren
suffix:semicolon
r_return
op_minus
id|EIO
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
id|ep7312_mtd
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
id|ep7312_mtd
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
id|ep7312_mtd-&gt;priv
op_assign
id|this
suffix:semicolon
multiline_comment|/*&n;&t; * Set GPIO Port B control register so that the pins are configured&n;&t; * to be outputs for controlling the NAND flash.&n;&t; */
id|clps_writeb
c_func
(paren
l_int|0xf0
comma
id|ep7312_pxddr
)paren
suffix:semicolon
multiline_comment|/* insert callbacks */
id|this-&gt;IO_ADDR_R
op_assign
id|ep7312_fio_base
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
id|ep7312_fio_base
suffix:semicolon
id|this-&gt;hwcontrol
op_assign
id|ep7312_hwcontrol
suffix:semicolon
id|this-&gt;dev_ready
op_assign
id|ep7312_device_ready
suffix:semicolon
multiline_comment|/* 15 us command delay time */
id|this-&gt;chip_delay
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* Scan to find existence of the device */
r_if
c_cond
(paren
id|nand_scan
(paren
id|ep7312_mtd
)paren
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ep7312_fio_base
)paren
suffix:semicolon
id|kfree
(paren
id|ep7312_mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Allocate memory for internal data buffer */
id|this-&gt;data_buf
op_assign
id|kmalloc
(paren
r_sizeof
(paren
id|u_char
)paren
op_star
(paren
id|ep7312_mtd-&gt;oobblock
op_plus
id|ep7312_mtd-&gt;oobsize
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this-&gt;data_buf
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to allocate NAND data buffer for EDB7312.&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ep7312_fio_base
)paren
suffix:semicolon
id|kfree
(paren
id|ep7312_mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_CMDLINE_PARTS
id|mtd_parts_nb
op_assign
id|parse_cmdline_partitions
c_func
(paren
id|ep7312_mtd
comma
op_amp
id|mtd_parts
comma
l_string|&quot;edb7312-nand&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd_parts_nb
OG
l_int|0
)paren
id|part_type
op_assign
l_string|&quot;command line&quot;
suffix:semicolon
r_else
id|mtd_parts_nb
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|mtd_parts_nb
op_eq
l_int|0
)paren
(brace
id|mtd_parts
op_assign
id|partition_info
suffix:semicolon
id|mtd_parts_nb
op_assign
id|NUM_PARTITIONS
suffix:semicolon
id|part_type
op_assign
l_string|&quot;static&quot;
suffix:semicolon
)brace
multiline_comment|/* Register the partitions */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Using %s partition definition&bslash;n&quot;
comma
id|part_type
)paren
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|ep7312_mtd
comma
id|mtd_parts
comma
id|mtd_parts_nb
)paren
suffix:semicolon
multiline_comment|/* Return happy */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ep7312_init
id|module_init
c_func
(paren
id|ep7312_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up routine&n; */
DECL|function|ep7312_cleanup
r_static
r_void
id|__exit
id|ep7312_cleanup
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
id|ep7312_mtd
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Unregister the device */
id|del_mtd_device
(paren
id|ep7312_mtd
)paren
suffix:semicolon
multiline_comment|/* Free internal data buffer */
id|kfree
(paren
id|this-&gt;data_buf
)paren
suffix:semicolon
multiline_comment|/* Free the MTD device structure */
id|kfree
(paren
id|ep7312_mtd
)paren
suffix:semicolon
)brace
DECL|variable|ep7312_cleanup
id|module_exit
c_func
(paren
id|ep7312_cleanup
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
l_string|&quot;Marius Groeger &lt;mag@sysgo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for Cogent EDB7312 board&quot;
)paren
suffix:semicolon
eof
