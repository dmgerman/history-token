multiline_comment|/*&n; * drivers/mtd/nand/sharpsl.c&n; *&n; *  Copyright (C) 2004 Richard Purdie&n; *&n; *  $Id: sharpsl.c,v 1.2 2004/11/24 20:38:07 rpurdie Exp $&n; *&n; *  Based on Sharp&squot;s NAND driver sharp_sl.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/nand_ecc.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
DECL|variable|sharpsl_io_base
r_static
r_void
id|__iomem
op_star
id|sharpsl_io_base
suffix:semicolon
DECL|variable|sharpsl_phys_base
r_static
r_int
id|sharpsl_phys_base
op_assign
l_int|0x0C000000
suffix:semicolon
multiline_comment|/* register offset */
DECL|macro|ECCLPLB
mdefine_line|#define ECCLPLB&t; &t;sharpsl_io_base+0x00&t;/* line parity 7 - 0 bit */
DECL|macro|ECCLPUB
mdefine_line|#define ECCLPUB&t; &t;sharpsl_io_base+0x04&t;/* line parity 15 - 8 bit */
DECL|macro|ECCCP
mdefine_line|#define ECCCP&t;   &t;sharpsl_io_base+0x08&t;/* column parity 5 - 0 bit */
DECL|macro|ECCCNTR
mdefine_line|#define ECCCNTR&t; &t;sharpsl_io_base+0x0C&t;/* ECC byte counter */
DECL|macro|ECCCLRR
mdefine_line|#define ECCCLRR&t; &t;sharpsl_io_base+0x10&t;/* cleare ECC */
DECL|macro|FLASHIO
mdefine_line|#define FLASHIO&t; &t;sharpsl_io_base+0x14&t;/* Flash I/O */
DECL|macro|FLASHCTL
mdefine_line|#define FLASHCTL&t;sharpsl_io_base+0x18&t;/* Flash Control */
multiline_comment|/* Flash control bit */
DECL|macro|FLRYBY
mdefine_line|#define FLRYBY&t;&t;(1 &lt;&lt; 5)
DECL|macro|FLCE1
mdefine_line|#define FLCE1&t;&t;(1 &lt;&lt; 4)
DECL|macro|FLWP
mdefine_line|#define FLWP&t;&t;(1 &lt;&lt; 3)
DECL|macro|FLALE
mdefine_line|#define FLALE&t;&t;(1 &lt;&lt; 2)
DECL|macro|FLCLE
mdefine_line|#define FLCLE&t;&t;(1 &lt;&lt; 1)
DECL|macro|FLCE0
mdefine_line|#define FLCE0&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * MTD structure for SharpSL&n; */
DECL|variable|sharpsl_mtd
r_static
r_struct
id|mtd_info
op_star
id|sharpsl_mtd
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Define partitions for flash device&n; */
DECL|macro|DEFAULT_NUM_PARTITIONS
mdefine_line|#define DEFAULT_NUM_PARTITIONS 3
macro_line|#if defined CONFIG_MACH_POODLE
DECL|macro|SHARPSL_ROOTFS_SIZE
mdefine_line|#define SHARPSL_ROOTFS_SIZE 22
DECL|macro|SHARPSL_FLASH_SIZE
mdefine_line|#define SHARPSL_FLASH_SIZE 64
macro_line|#elif defined CONFIG_MACH_CORGI 
DECL|macro|SHARPSL_ROOTFS_SIZE
mdefine_line|#define SHARPSL_ROOTFS_SIZE 25
DECL|macro|SHARPSL_FLASH_SIZE
mdefine_line|#define SHARPSL_FLASH_SIZE 32
macro_line|#elif defined CONFIG_MACH_SHEPHERD
DECL|macro|SHARPSL_ROOTFS_SIZE
mdefine_line|#define SHARPSL_ROOTFS_SIZE 25
DECL|macro|SHARPSL_FLASH_SIZE
mdefine_line|#define SHARPSL_FLASH_SIZE 64
macro_line|#elif defined CONFIG_MACH_HUSKY
DECL|macro|SHARPSL_ROOTFS_SIZE
mdefine_line|#define SHARPSL_ROOTFS_SIZE 53
DECL|macro|SHARPSL_FLASH_SIZE
mdefine_line|#define SHARPSL_FLASH_SIZE 128
macro_line|#elif defined CONFIG_MACH_TOSA
DECL|macro|SHARPSL_ROOTFS_SIZE
mdefine_line|#define SHARPSL_ROOTFS_SIZE 28
DECL|macro|SHARPSL_FLASH_SIZE
mdefine_line|#define SHARPSL_FLASH_SIZE 64
macro_line|#else
DECL|macro|SHARPSL_ROOTFS_SIZE
mdefine_line|#define SHARPSL_ROOTFS_SIZE 30
DECL|macro|SHARPSL_FLASH_SIZE
mdefine_line|#define SHARPSL_FLASH_SIZE 64
macro_line|#endif
DECL|variable|nr_partitions
r_static
r_int
id|nr_partitions
suffix:semicolon
DECL|variable|sharpsl_nand_default_partition_info
r_static
r_struct
id|mtd_partition
id|sharpsl_nand_default_partition_info
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;NAND flash partition 0&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|7
op_star
l_int|1024
op_star
l_int|1024
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;NAND flash partition 1&quot;
comma
dot
id|offset
op_assign
l_int|7
op_star
l_int|1024
op_star
l_int|1024
comma
dot
id|size
op_assign
id|SHARPSL_ROOTFS_SIZE
op_star
l_int|1024
op_star
l_int|1024
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;NAND flash partition 2&quot;
comma
dot
id|offset
op_assign
(paren
id|SHARPSL_ROOTFS_SIZE
op_plus
l_int|7
)paren
op_star
l_int|1024
op_star
l_int|1024
comma
dot
id|size
op_assign
(paren
id|SHARPSL_FLASH_SIZE
op_minus
id|SHARPSL_ROOTFS_SIZE
op_minus
l_int|7
)paren
op_star
l_int|1024
op_star
l_int|1024
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* &n; *&t;hardware specific access to control-lines&n; */
r_static
r_void
DECL|function|sharpsl_nand_hwcontrol
id|sharpsl_nand_hwcontrol
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
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_or
id|FLCLE
comma
id|FLASHCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRCLE
suffix:colon
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_amp
op_complement
id|FLCLE
comma
id|FLASHCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETALE
suffix:colon
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_or
id|FLALE
comma
id|FLASHCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRALE
suffix:colon
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_amp
op_complement
id|FLALE
comma
id|FLASHCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETNCE
suffix:colon
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_amp
op_complement
(paren
id|FLCE0
op_or
id|FLCE1
)paren
comma
id|FLASHCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRNCE
suffix:colon
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_or
(paren
id|FLCE0
op_or
id|FLCE1
)paren
comma
id|FLASHCTL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|scan_ff_pattern
r_static
r_uint8
id|scan_ff_pattern
(braket
)braket
op_assign
(brace
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
DECL|variable|sharpsl_bbt
r_static
r_struct
id|nand_bbt_descr
id|sharpsl_bbt
op_assign
(brace
dot
id|options
op_assign
l_int|0
comma
dot
id|offs
op_assign
l_int|4
comma
dot
id|len
op_assign
l_int|2
comma
dot
id|pattern
op_assign
id|scan_ff_pattern
)brace
suffix:semicolon
r_static
r_int
DECL|function|sharpsl_nand_dev_ready
id|sharpsl_nand_dev_ready
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_amp
id|FLRYBY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sharpsl_nand_enable_hwecc
id|sharpsl_nand_enable_hwecc
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
id|writeb
c_func
(paren
l_int|0
comma
id|ECCCLRR
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|sharpsl_nand_calculate_ecc
id|sharpsl_nand_calculate_ecc
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
id|ecc_code
(braket
l_int|0
)braket
op_assign
op_complement
id|readb
c_func
(paren
id|ECCLPUB
)paren
suffix:semicolon
id|ecc_code
(braket
l_int|1
)braket
op_assign
op_complement
id|readb
c_func
(paren
id|ECCLPLB
)paren
suffix:semicolon
id|ecc_code
(braket
l_int|2
)braket
op_assign
(paren
op_complement
id|readb
c_func
(paren
id|ECCCP
)paren
op_lshift
l_int|2
)paren
op_or
l_int|0x03
suffix:semicolon
r_return
id|readb
c_func
(paren
id|ECCCNTR
)paren
op_ne
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MTD_PARTITIONS
DECL|variable|part_probes
r_const
r_char
op_star
id|part_probes
(braket
)braket
op_assign
(brace
l_string|&quot;cmdlinepart&quot;
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Main initialization routine&n; */
r_int
id|__init
DECL|function|sharpsl_nand_init
id|sharpsl_nand_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|nand_chip
op_star
id|this
suffix:semicolon
r_struct
id|mtd_partition
op_star
id|sharpsl_partition_info
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Allocate memory for MTD device structure and private data */
id|sharpsl_mtd
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
id|sharpsl_mtd
)paren
(brace
id|printk
(paren
l_string|&quot;Unable to allocate SharpSL NAND MTD device structure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* map physical adress */
id|sharpsl_io_base
op_assign
id|ioremap
c_func
(paren
id|sharpsl_phys_base
comma
l_int|0x1000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sharpsl_io_base
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ioremap to access Sharp SL NAND chip failed&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sharpsl_mtd
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
id|sharpsl_mtd
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
id|sharpsl_mtd
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
id|sharpsl_mtd-&gt;priv
op_assign
id|this
suffix:semicolon
multiline_comment|/*&n;&t; * PXA initialize&n;&t; */
id|writeb
c_func
(paren
id|readb
c_func
(paren
id|FLASHCTL
)paren
op_or
id|FLWP
comma
id|FLASHCTL
)paren
suffix:semicolon
multiline_comment|/* Set address of NAND IO lines */
id|this-&gt;IO_ADDR_R
op_assign
id|FLASHIO
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
id|FLASHIO
suffix:semicolon
multiline_comment|/* Set address of hardware control function */
id|this-&gt;hwcontrol
op_assign
id|sharpsl_nand_hwcontrol
suffix:semicolon
id|this-&gt;dev_ready
op_assign
id|sharpsl_nand_dev_ready
suffix:semicolon
multiline_comment|/* 15 us command delay time */
id|this-&gt;chip_delay
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* set eccmode using hardware ECC */
id|this-&gt;eccmode
op_assign
id|NAND_ECC_HW3_256
suffix:semicolon
id|this-&gt;enable_hwecc
op_assign
id|sharpsl_nand_enable_hwecc
suffix:semicolon
id|this-&gt;calculate_ecc
op_assign
id|sharpsl_nand_calculate_ecc
suffix:semicolon
id|this-&gt;correct_data
op_assign
id|nand_correct_data
suffix:semicolon
id|this-&gt;badblock_pattern
op_assign
op_amp
id|sharpsl_bbt
suffix:semicolon
multiline_comment|/* Scan to find existence of the device */
id|err
op_assign
id|nand_scan
c_func
(paren
id|sharpsl_mtd
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|iounmap
c_func
(paren
id|sharpsl_io_base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sharpsl_mtd
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Register the partitions */
id|sharpsl_mtd-&gt;name
op_assign
l_string|&quot;sharpsl-nand&quot;
suffix:semicolon
id|nr_partitions
op_assign
id|parse_mtd_partitions
c_func
(paren
id|sharpsl_mtd
comma
id|part_probes
comma
op_amp
id|sharpsl_partition_info
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_partitions
op_le
l_int|0
)paren
(brace
id|nr_partitions
op_assign
id|DEFAULT_NUM_PARTITIONS
suffix:semicolon
id|sharpsl_partition_info
op_assign
id|sharpsl_nand_default_partition_info
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MACH_HUSKY
multiline_comment|/* Need to use small eraseblock size for backward compatibility */
id|sharpsl_mtd-&gt;flags
op_or_assign
id|MTD_NO_VIRTBLOCKS
suffix:semicolon
macro_line|#endif
id|add_mtd_partitions
c_func
(paren
id|sharpsl_mtd
comma
id|sharpsl_partition_info
comma
id|nr_partitions
)paren
suffix:semicolon
multiline_comment|/* Return happy */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sharpsl_nand_init
id|module_init
c_func
(paren
id|sharpsl_nand_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up routine&n; */
macro_line|#ifdef MODULE
DECL|function|sharpsl_nand_cleanup
r_static
r_void
id|__exit
id|sharpsl_nand_cleanup
c_func
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
id|sharpsl_mtd
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Release resources, unregister device */
id|nand_release
c_func
(paren
id|sharpsl_mtd
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|sharpsl_io_base
)paren
suffix:semicolon
multiline_comment|/* Free the MTD device structure */
id|kfree
c_func
(paren
id|sharpsl_mtd
)paren
suffix:semicolon
)brace
DECL|variable|sharpsl_nand_cleanup
id|module_exit
c_func
(paren
id|sharpsl_nand_cleanup
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
l_string|&quot;Richard Purdie &lt;rpurdie@rpsys.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Device specific logic for NAND flash on Sharp SL-C7xx Series&quot;
)paren
suffix:semicolon
eof
