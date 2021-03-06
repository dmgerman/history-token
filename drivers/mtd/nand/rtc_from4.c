multiline_comment|/*&n; *  drivers/mtd/nand/rtc_from4.c&n; *&n; *  Copyright (C) 2004  Red Hat, Inc.&n; * &n; *  Derived from drivers/mtd/nand/spia.c&n; *       Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)&n; *&n; * $Id: rtc_from4.c,v 1.7 2004/11/04 12:53:10 gleixner Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Overview:&n; *   This is a device driver for the AG-AND flash device found on the&n; *   Renesas Technology Corp. Flash ROM 4-slot interface board (FROM_BOARD4), &n; *   which utilizes the Renesas HN29V1G91T-30 part. &n; *   This chip is a 1 GBibit (128MiB x 8 bits) AG-AND flash device.&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/rslib.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nand.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * MTD structure for Renesas board&n; */
DECL|variable|rtc_from4_mtd
r_static
r_struct
id|mtd_info
op_star
id|rtc_from4_mtd
op_assign
l_int|NULL
suffix:semicolon
DECL|macro|RTC_FROM4_MAX_CHIPS
mdefine_line|#define RTC_FROM4_MAX_CHIPS&t;2
multiline_comment|/* HS77x9 processor register defines */
DECL|macro|SH77X9_BCR1
mdefine_line|#define SH77X9_BCR1&t;((volatile unsigned short *)(0xFFFFFF60))
DECL|macro|SH77X9_BCR2
mdefine_line|#define SH77X9_BCR2&t;((volatile unsigned short *)(0xFFFFFF62))
DECL|macro|SH77X9_WCR1
mdefine_line|#define SH77X9_WCR1&t;((volatile unsigned short *)(0xFFFFFF64))
DECL|macro|SH77X9_WCR2
mdefine_line|#define SH77X9_WCR2&t;((volatile unsigned short *)(0xFFFFFF66))
DECL|macro|SH77X9_MCR
mdefine_line|#define SH77X9_MCR&t;((volatile unsigned short *)(0xFFFFFF68))
DECL|macro|SH77X9_PCR
mdefine_line|#define SH77X9_PCR&t;((volatile unsigned short *)(0xFFFFFF6C))
DECL|macro|SH77X9_FRQCR
mdefine_line|#define SH77X9_FRQCR&t;((volatile unsigned short *)(0xFFFFFF80))
multiline_comment|/*&n; * Values specific to the Renesas Technology Corp. FROM_BOARD4 (used with HS77x9 processor)&n; */
multiline_comment|/* Address where flash is mapped */
DECL|macro|RTC_FROM4_FIO_BASE
mdefine_line|#define RTC_FROM4_FIO_BASE&t;0x14000000
multiline_comment|/* CLE and ALE are tied to address lines 5 &amp; 4, respectively */
DECL|macro|RTC_FROM4_CLE
mdefine_line|#define RTC_FROM4_CLE&t;&t;(1 &lt;&lt; 5)
DECL|macro|RTC_FROM4_ALE
mdefine_line|#define RTC_FROM4_ALE&t;&t;(1 &lt;&lt; 4)
multiline_comment|/* address lines A24-A22 used for chip selection */
DECL|macro|RTC_FROM4_NAND_ADDR_SLOT3
mdefine_line|#define RTC_FROM4_NAND_ADDR_SLOT3&t;(0x00800000)
DECL|macro|RTC_FROM4_NAND_ADDR_SLOT4
mdefine_line|#define RTC_FROM4_NAND_ADDR_SLOT4&t;(0x00C00000)
DECL|macro|RTC_FROM4_NAND_ADDR_FPGA
mdefine_line|#define RTC_FROM4_NAND_ADDR_FPGA&t;(0x01000000)
multiline_comment|/* mask address lines A24-A22 used for chip selection */
DECL|macro|RTC_FROM4_NAND_ADDR_MASK
mdefine_line|#define RTC_FROM4_NAND_ADDR_MASK&t;(RTC_FROM4_NAND_ADDR_SLOT3 | RTC_FROM4_NAND_ADDR_SLOT4 | RTC_FROM4_NAND_ADDR_FPGA)
multiline_comment|/* FPGA status register for checking device ready (bit zero) */
DECL|macro|RTC_FROM4_FPGA_SR
mdefine_line|#define RTC_FROM4_FPGA_SR&t;&t;(RTC_FROM4_NAND_ADDR_FPGA | 0x00000002)
DECL|macro|RTC_FROM4_DEVICE_READY
mdefine_line|#define RTC_FROM4_DEVICE_READY&t;&t;0x0001
multiline_comment|/* FPGA Reed-Solomon ECC Control register */
DECL|macro|RTC_FROM4_RS_ECC_CTL
mdefine_line|#define RTC_FROM4_RS_ECC_CTL&t;&t;(RTC_FROM4_NAND_ADDR_FPGA | 0x00000050)
DECL|macro|RTC_FROM4_RS_ECC_CTL_CLR
mdefine_line|#define RTC_FROM4_RS_ECC_CTL_CLR&t;(1 &lt;&lt; 7)
DECL|macro|RTC_FROM4_RS_ECC_CTL_GEN
mdefine_line|#define RTC_FROM4_RS_ECC_CTL_GEN&t;(1 &lt;&lt; 6)
DECL|macro|RTC_FROM4_RS_ECC_CTL_FD_E
mdefine_line|#define RTC_FROM4_RS_ECC_CTL_FD_E&t;(1 &lt;&lt; 5)
multiline_comment|/* FPGA Reed-Solomon ECC code base */
DECL|macro|RTC_FROM4_RS_ECC
mdefine_line|#define RTC_FROM4_RS_ECC&t;&t;(RTC_FROM4_NAND_ADDR_FPGA | 0x00000060)
DECL|macro|RTC_FROM4_RS_ECCN
mdefine_line|#define RTC_FROM4_RS_ECCN&t;&t;(RTC_FROM4_NAND_ADDR_FPGA | 0x00000080)
multiline_comment|/* FPGA Reed-Solomon ECC check register */
DECL|macro|RTC_FROM4_RS_ECC_CHK
mdefine_line|#define RTC_FROM4_RS_ECC_CHK&t;&t;(RTC_FROM4_NAND_ADDR_FPGA | 0x00000070)
DECL|macro|RTC_FROM4_RS_ECC_CHK_ERROR
mdefine_line|#define RTC_FROM4_RS_ECC_CHK_ERROR&t;(1 &lt;&lt; 7)
multiline_comment|/* Undefine for software ECC */
DECL|macro|RTC_FROM4_HWECC
mdefine_line|#define RTC_FROM4_HWECC&t;1
multiline_comment|/*&n; * Module stuff&n; */
DECL|variable|rtc_from4_fio_base
r_static
r_void
id|__iomem
op_star
id|rtc_from4_fio_base
op_assign
id|P2SEGADDR
c_func
(paren
id|RTC_FROM4_FIO_BASE
)paren
suffix:semicolon
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
(brace
dot
id|name
op_assign
l_string|&quot;Renesas flash partition 1&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
id|MTDPART_SIZ_FULL
)brace
comma
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS 1
multiline_comment|/* &n; *&t;hardware specific flash bbt decriptors&n; *&t;Note: this is to allow debugging by disabling &n; *&t;&t;NAND_BBT_CREATE and/or NAND_BBT_WRITE&n; *&n; */
DECL|variable|bbt_pattern
r_static
r_uint8
id|bbt_pattern
(braket
)braket
op_assign
(brace
l_char|&squot;B&squot;
comma
l_char|&squot;b&squot;
comma
l_char|&squot;t&squot;
comma
l_char|&squot;0&squot;
)brace
suffix:semicolon
DECL|variable|mirror_pattern
r_static
r_uint8
id|mirror_pattern
(braket
)braket
op_assign
(brace
l_char|&squot;1&squot;
comma
l_char|&squot;t&squot;
comma
l_char|&squot;b&squot;
comma
l_char|&squot;B&squot;
)brace
suffix:semicolon
DECL|variable|rtc_from4_bbt_main_descr
r_static
r_struct
id|nand_bbt_descr
id|rtc_from4_bbt_main_descr
op_assign
(brace
dot
id|options
op_assign
id|NAND_BBT_LASTBLOCK
op_or
id|NAND_BBT_CREATE
op_or
id|NAND_BBT_WRITE
op_or
id|NAND_BBT_2BIT
op_or
id|NAND_BBT_VERSION
op_or
id|NAND_BBT_PERCHIP
comma
dot
id|offs
op_assign
l_int|40
comma
dot
id|len
op_assign
l_int|4
comma
dot
id|veroffs
op_assign
l_int|44
comma
dot
id|maxblocks
op_assign
l_int|4
comma
dot
id|pattern
op_assign
id|bbt_pattern
)brace
suffix:semicolon
DECL|variable|rtc_from4_bbt_mirror_descr
r_static
r_struct
id|nand_bbt_descr
id|rtc_from4_bbt_mirror_descr
op_assign
(brace
dot
id|options
op_assign
id|NAND_BBT_LASTBLOCK
op_or
id|NAND_BBT_CREATE
op_or
id|NAND_BBT_WRITE
op_or
id|NAND_BBT_2BIT
op_or
id|NAND_BBT_VERSION
op_or
id|NAND_BBT_PERCHIP
comma
dot
id|offs
op_assign
l_int|40
comma
dot
id|len
op_assign
l_int|4
comma
dot
id|veroffs
op_assign
l_int|44
comma
dot
id|maxblocks
op_assign
l_int|4
comma
dot
id|pattern
op_assign
id|mirror_pattern
)brace
suffix:semicolon
macro_line|#ifdef RTC_FROM4_HWECC
multiline_comment|/* the Reed Solomon control structure */
DECL|variable|rs_decoder
r_static
r_struct
id|rs_control
op_star
id|rs_decoder
suffix:semicolon
multiline_comment|/* &n; *      hardware specific Out Of Band information&n; */
DECL|variable|rtc_from4_nand_oobinfo
r_static
r_struct
id|nand_oobinfo
id|rtc_from4_nand_oobinfo
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
l_int|32
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
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
comma
dot
id|oobfree
op_assign
(brace
(brace
l_int|32
comma
l_int|32
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/* Aargh. I missed the reversed bit order, when I&n; * was talking to Renesas about the FPGA.&n; *&n; * The table is used for bit reordering and inversion&n; * of the ecc byte which we get from the FPGA&n; */
DECL|variable|revbits
r_static
r_uint8
id|revbits
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x80
comma
l_int|0x40
comma
l_int|0xc0
comma
l_int|0x20
comma
l_int|0xa0
comma
l_int|0x60
comma
l_int|0xe0
comma
l_int|0x10
comma
l_int|0x90
comma
l_int|0x50
comma
l_int|0xd0
comma
l_int|0x30
comma
l_int|0xb0
comma
l_int|0x70
comma
l_int|0xf0
comma
l_int|0x08
comma
l_int|0x88
comma
l_int|0x48
comma
l_int|0xc8
comma
l_int|0x28
comma
l_int|0xa8
comma
l_int|0x68
comma
l_int|0xe8
comma
l_int|0x18
comma
l_int|0x98
comma
l_int|0x58
comma
l_int|0xd8
comma
l_int|0x38
comma
l_int|0xb8
comma
l_int|0x78
comma
l_int|0xf8
comma
l_int|0x04
comma
l_int|0x84
comma
l_int|0x44
comma
l_int|0xc4
comma
l_int|0x24
comma
l_int|0xa4
comma
l_int|0x64
comma
l_int|0xe4
comma
l_int|0x14
comma
l_int|0x94
comma
l_int|0x54
comma
l_int|0xd4
comma
l_int|0x34
comma
l_int|0xb4
comma
l_int|0x74
comma
l_int|0xf4
comma
l_int|0x0c
comma
l_int|0x8c
comma
l_int|0x4c
comma
l_int|0xcc
comma
l_int|0x2c
comma
l_int|0xac
comma
l_int|0x6c
comma
l_int|0xec
comma
l_int|0x1c
comma
l_int|0x9c
comma
l_int|0x5c
comma
l_int|0xdc
comma
l_int|0x3c
comma
l_int|0xbc
comma
l_int|0x7c
comma
l_int|0xfc
comma
l_int|0x02
comma
l_int|0x82
comma
l_int|0x42
comma
l_int|0xc2
comma
l_int|0x22
comma
l_int|0xa2
comma
l_int|0x62
comma
l_int|0xe2
comma
l_int|0x12
comma
l_int|0x92
comma
l_int|0x52
comma
l_int|0xd2
comma
l_int|0x32
comma
l_int|0xb2
comma
l_int|0x72
comma
l_int|0xf2
comma
l_int|0x0a
comma
l_int|0x8a
comma
l_int|0x4a
comma
l_int|0xca
comma
l_int|0x2a
comma
l_int|0xaa
comma
l_int|0x6a
comma
l_int|0xea
comma
l_int|0x1a
comma
l_int|0x9a
comma
l_int|0x5a
comma
l_int|0xda
comma
l_int|0x3a
comma
l_int|0xba
comma
l_int|0x7a
comma
l_int|0xfa
comma
l_int|0x06
comma
l_int|0x86
comma
l_int|0x46
comma
l_int|0xc6
comma
l_int|0x26
comma
l_int|0xa6
comma
l_int|0x66
comma
l_int|0xe6
comma
l_int|0x16
comma
l_int|0x96
comma
l_int|0x56
comma
l_int|0xd6
comma
l_int|0x36
comma
l_int|0xb6
comma
l_int|0x76
comma
l_int|0xf6
comma
l_int|0x0e
comma
l_int|0x8e
comma
l_int|0x4e
comma
l_int|0xce
comma
l_int|0x2e
comma
l_int|0xae
comma
l_int|0x6e
comma
l_int|0xee
comma
l_int|0x1e
comma
l_int|0x9e
comma
l_int|0x5e
comma
l_int|0xde
comma
l_int|0x3e
comma
l_int|0xbe
comma
l_int|0x7e
comma
l_int|0xfe
comma
l_int|0x01
comma
l_int|0x81
comma
l_int|0x41
comma
l_int|0xc1
comma
l_int|0x21
comma
l_int|0xa1
comma
l_int|0x61
comma
l_int|0xe1
comma
l_int|0x11
comma
l_int|0x91
comma
l_int|0x51
comma
l_int|0xd1
comma
l_int|0x31
comma
l_int|0xb1
comma
l_int|0x71
comma
l_int|0xf1
comma
l_int|0x09
comma
l_int|0x89
comma
l_int|0x49
comma
l_int|0xc9
comma
l_int|0x29
comma
l_int|0xa9
comma
l_int|0x69
comma
l_int|0xe9
comma
l_int|0x19
comma
l_int|0x99
comma
l_int|0x59
comma
l_int|0xd9
comma
l_int|0x39
comma
l_int|0xb9
comma
l_int|0x79
comma
l_int|0xf9
comma
l_int|0x05
comma
l_int|0x85
comma
l_int|0x45
comma
l_int|0xc5
comma
l_int|0x25
comma
l_int|0xa5
comma
l_int|0x65
comma
l_int|0xe5
comma
l_int|0x15
comma
l_int|0x95
comma
l_int|0x55
comma
l_int|0xd5
comma
l_int|0x35
comma
l_int|0xb5
comma
l_int|0x75
comma
l_int|0xf5
comma
l_int|0x0d
comma
l_int|0x8d
comma
l_int|0x4d
comma
l_int|0xcd
comma
l_int|0x2d
comma
l_int|0xad
comma
l_int|0x6d
comma
l_int|0xed
comma
l_int|0x1d
comma
l_int|0x9d
comma
l_int|0x5d
comma
l_int|0xdd
comma
l_int|0x3d
comma
l_int|0xbd
comma
l_int|0x7d
comma
l_int|0xfd
comma
l_int|0x03
comma
l_int|0x83
comma
l_int|0x43
comma
l_int|0xc3
comma
l_int|0x23
comma
l_int|0xa3
comma
l_int|0x63
comma
l_int|0xe3
comma
l_int|0x13
comma
l_int|0x93
comma
l_int|0x53
comma
l_int|0xd3
comma
l_int|0x33
comma
l_int|0xb3
comma
l_int|0x73
comma
l_int|0xf3
comma
l_int|0x0b
comma
l_int|0x8b
comma
l_int|0x4b
comma
l_int|0xcb
comma
l_int|0x2b
comma
l_int|0xab
comma
l_int|0x6b
comma
l_int|0xeb
comma
l_int|0x1b
comma
l_int|0x9b
comma
l_int|0x5b
comma
l_int|0xdb
comma
l_int|0x3b
comma
l_int|0xbb
comma
l_int|0x7b
comma
l_int|0xfb
comma
l_int|0x07
comma
l_int|0x87
comma
l_int|0x47
comma
l_int|0xc7
comma
l_int|0x27
comma
l_int|0xa7
comma
l_int|0x67
comma
l_int|0xe7
comma
l_int|0x17
comma
l_int|0x97
comma
l_int|0x57
comma
l_int|0xd7
comma
l_int|0x37
comma
l_int|0xb7
comma
l_int|0x77
comma
l_int|0xf7
comma
l_int|0x0f
comma
l_int|0x8f
comma
l_int|0x4f
comma
l_int|0xcf
comma
l_int|0x2f
comma
l_int|0xaf
comma
l_int|0x6f
comma
l_int|0xef
comma
l_int|0x1f
comma
l_int|0x9f
comma
l_int|0x5f
comma
l_int|0xdf
comma
l_int|0x3f
comma
l_int|0xbf
comma
l_int|0x7f
comma
l_int|0xff
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* &n; * rtc_from4_hwcontrol - hardware specific access to control-lines&n; * @mtd:&t;MTD device structure&n; * @cmd:&t;hardware control command&n; *&n; * Address lines (A5 and A4) are used to control Command and Address Latch &n; * Enable on this board, so set the read/write address appropriately.&n; *&n; * Chip Enable is also controlled by the Chip Select (CS5) and &n; * Address lines (A24-A22), so no action is required here.&n; *&n; */
DECL|function|rtc_from4_hwcontrol
r_static
r_void
id|rtc_from4_hwcontrol
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
id|nand_chip
op_star
id|this
op_assign
(paren
r_struct
id|nand_chip
op_star
)paren
(paren
id|mtd-&gt;priv
)paren
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
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_or
id|RTC_FROM4_CLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRCLE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_amp
op_complement
id|RTC_FROM4_CLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETALE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_or
id|RTC_FROM4_ALE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRALE
suffix:colon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_amp
op_complement
id|RTC_FROM4_ALE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_CTL_SETNCE
suffix:colon
r_break
suffix:semicolon
r_case
id|NAND_CTL_CLRNCE
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * rtc_from4_nand_select_chip - hardware specific chip select&n; * @mtd:&t;MTD device structure&n; * @chip:&t;Chip to select (0 == slot 3, 1 == slot 4)&n; *&n; * The chip select is based on address lines A24-A22.&n; * This driver uses flash slots 3 and 4 (A23-A22).&n; *&n; */
DECL|function|rtc_from4_nand_select_chip
r_static
r_void
id|rtc_from4_nand_select_chip
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
id|nand_chip
op_star
id|this
op_assign
id|mtd-&gt;priv
suffix:semicolon
id|this-&gt;IO_ADDR_R
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_R
op_amp
op_complement
id|RTC_FROM4_NAND_ADDR_MASK
)paren
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_amp
op_complement
id|RTC_FROM4_NAND_ADDR_MASK
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|chip
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* select slot 3 chip */
id|this-&gt;IO_ADDR_R
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_R
op_or
id|RTC_FROM4_NAND_ADDR_SLOT3
)paren
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_or
id|RTC_FROM4_NAND_ADDR_SLOT3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* select slot 4 chip */
id|this-&gt;IO_ADDR_R
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_R
op_or
id|RTC_FROM4_NAND_ADDR_SLOT4
)paren
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|this-&gt;IO_ADDR_W
op_or
id|RTC_FROM4_NAND_ADDR_SLOT4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * rtc_from4_nand_device_ready - hardware specific ready/busy check&n; * @mtd:&t;MTD device structure&n; *&n; * This board provides the Ready/Busy state in the status register&n; * of the FPGA.  Bit zero indicates the RDY(1)/BSY(0) signal.&n; *&n; */
DECL|function|rtc_from4_nand_device_ready
r_static
r_int
id|rtc_from4_nand_device_ready
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
id|status
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|rtc_from4_fio_base
op_plus
id|RTC_FROM4_FPGA_SR
)paren
)paren
suffix:semicolon
r_return
(paren
id|status
op_amp
id|RTC_FROM4_DEVICE_READY
)paren
suffix:semicolon
)brace
macro_line|#ifdef RTC_FROM4_HWECC
multiline_comment|/*&n; * rtc_from4_enable_hwecc - hardware specific hardware ECC enable function&n; * @mtd:&t;MTD device structure&n; * @mode:&t;I/O mode; read or write&n; *&n; * enable hardware ECC for data read or write &n; *&n; */
DECL|function|rtc_from4_enable_hwecc
r_static
r_void
id|rtc_from4_enable_hwecc
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
r_volatile
r_int
r_int
op_star
id|rs_ecc_ctl
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|rtc_from4_fio_base
op_plus
id|RTC_FROM4_RS_ECC_CTL
)paren
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|NAND_ECC_READ
suffix:colon
id|status
op_assign
id|RTC_FROM4_RS_ECC_CTL_CLR
op_or
id|RTC_FROM4_RS_ECC_CTL_FD_E
suffix:semicolon
op_star
id|rs_ecc_ctl
op_assign
id|status
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_ECC_READSYN
suffix:colon
id|status
op_assign
l_int|0x00
suffix:semicolon
op_star
id|rs_ecc_ctl
op_assign
id|status
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NAND_ECC_WRITE
suffix:colon
id|status
op_assign
id|RTC_FROM4_RS_ECC_CTL_CLR
op_or
id|RTC_FROM4_RS_ECC_CTL_GEN
op_or
id|RTC_FROM4_RS_ECC_CTL_FD_E
suffix:semicolon
op_star
id|rs_ecc_ctl
op_assign
id|status
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * rtc_from4_calculate_ecc - hardware specific code to read ECC code&n; * @mtd:&t;MTD device structure&n; * @dat:&t;buffer containing the data to generate ECC codes&n; * @ecc_code&t;ECC codes calculated&n; *&n; * The ECC code is calculated by the FPGA.  All we have to do is read the values&n; * from the FPGA registers.&n; *&n; * Note: We read from the inverted registers, since data is inverted before&n; * the code is calculated. So all 0xff data (blank page) results in all 0xff rs code&n; *&n; */
DECL|function|rtc_from4_calculate_ecc
r_static
r_void
id|rtc_from4_calculate_ecc
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
r_volatile
r_int
r_int
op_star
id|rs_eccn
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|rtc_from4_fio_base
op_plus
id|RTC_FROM4_RS_ECCN
)paren
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_int
id|i
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|value
op_assign
op_star
id|rs_eccn
suffix:semicolon
id|ecc_code
(braket
id|i
)braket
op_assign
(paren
r_int
r_char
)paren
id|value
suffix:semicolon
id|rs_eccn
op_increment
suffix:semicolon
)brace
id|ecc_code
(braket
l_int|7
)braket
op_or_assign
l_int|0x0f
suffix:semicolon
multiline_comment|/* set the last four bits (not used) */
)brace
multiline_comment|/*&n; * rtc_from4_correct_data - hardware specific code to correct data using ECC code&n; * @mtd:&t;MTD device structure&n; * @buf:&t;buffer containing the data to generate ECC codes&n; * @ecc1&t;ECC codes read&n; * @ecc2&t;ECC codes calculated&n; *&n; * The FPGA tells us fast, if there&squot;s an error or not. If no, we go back happy&n; * else we read the ecc results from the fpga and call the rs library to decode&n; * and hopefully correct the error&n; *&n; * For now I use the code, which we read from the FLASH to use the RS lib,&n; * as the syndrom conversion has a unresolved issue.&n; */
DECL|function|rtc_from4_correct_data
r_static
r_int
id|rtc_from4_correct_data
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
id|u_char
op_star
id|ecc1
comma
id|u_char
op_star
id|ecc2
)paren
(brace
r_int
id|i
comma
id|j
comma
id|res
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_uint16
id|par
(braket
l_int|6
)braket
comma
id|syn
(braket
l_int|6
)braket
comma
id|tmp
suffix:semicolon
r_uint8
id|ecc
(braket
l_int|8
)braket
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|rs_ecc
suffix:semicolon
id|status
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|rtc_from4_fio_base
op_plus
id|RTC_FROM4_RS_ECC_CHK
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|RTC_FROM4_RS_ECC_CHK_ERROR
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Read the syndrom pattern from the FPGA and correct the bitorder */
id|rs_ecc
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|rtc_from4_fio_base
op_plus
id|RTC_FROM4_RS_ECC
)paren
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ecc
(braket
id|i
)braket
op_assign
id|revbits
(braket
(paren
op_star
id|rs_ecc
)paren
op_amp
l_int|0xFF
)braket
suffix:semicolon
id|rs_ecc
op_increment
suffix:semicolon
)brace
multiline_comment|/* convert into 6 10bit syndrome fields */
id|par
(braket
l_int|5
)braket
op_assign
id|rs_decoder-&gt;index_of
(braket
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|0
)braket
op_rshift
l_int|0
)paren
op_amp
l_int|0x0ff
)paren
op_or
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_amp
l_int|0x300
)paren
)braket
suffix:semicolon
id|par
(braket
l_int|4
)braket
op_assign
id|rs_decoder-&gt;index_of
(braket
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|1
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x03f
)paren
op_or
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|2
)braket
op_lshift
l_int|6
)paren
op_amp
l_int|0x3c0
)paren
)braket
suffix:semicolon
id|par
(braket
l_int|3
)braket
op_assign
id|rs_decoder-&gt;index_of
(braket
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x00f
)paren
op_or
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|3
)braket
op_lshift
l_int|4
)paren
op_amp
l_int|0x3f0
)paren
)braket
suffix:semicolon
id|par
(braket
l_int|2
)braket
op_assign
id|rs_decoder-&gt;index_of
(braket
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|3
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|0x003
)paren
op_or
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|4
)braket
op_lshift
l_int|2
)paren
op_amp
l_int|0x3fc
)paren
)braket
suffix:semicolon
id|par
(braket
l_int|1
)braket
op_assign
id|rs_decoder-&gt;index_of
(braket
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|5
)braket
op_rshift
l_int|0
)paren
op_amp
l_int|0x0ff
)paren
op_or
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|6
)braket
op_lshift
l_int|8
)paren
op_amp
l_int|0x300
)paren
)braket
suffix:semicolon
id|par
(braket
l_int|0
)braket
op_assign
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|6
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x03f
)paren
op_or
(paren
(paren
(paren
r_uint16
)paren
id|ecc
(braket
l_int|7
)braket
op_lshift
l_int|6
)paren
op_amp
l_int|0x3c0
)paren
suffix:semicolon
multiline_comment|/* Convert to computable syndrome */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|syn
(braket
id|i
)braket
op_assign
id|par
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
l_int|6
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|par
(braket
id|j
)braket
op_ne
id|rs_decoder-&gt;nn
)paren
id|syn
(braket
id|i
)braket
op_xor_assign
id|rs_decoder-&gt;alpha_to
(braket
id|rs_modnn
c_func
(paren
id|rs_decoder
comma
id|par
(braket
id|j
)braket
op_plus
id|i
op_star
id|j
)paren
)braket
suffix:semicolon
multiline_comment|/* Convert to index form */
id|syn
(braket
id|i
)braket
op_assign
id|rs_decoder-&gt;index_of
(braket
id|syn
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
multiline_comment|/* Let the library code do its magic.*/
id|res
op_assign
id|decode_rs8
c_func
(paren
id|rs_decoder
comma
id|buf
comma
id|par
comma
l_int|512
comma
id|syn
comma
l_int|0
comma
l_int|NULL
comma
l_int|0xff
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OG
l_int|0
)paren
(brace
id|DEBUG
(paren
id|MTD_DEBUG_LEVEL0
comma
l_string|&quot;rtc_from4_correct_data: &quot;
l_string|&quot;ECC corrected %d errors on read&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Main initialization routine&n; */
DECL|function|rtc_from4_init
r_int
id|__init
id|rtc_from4_init
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
r_int
id|bcr1
comma
id|bcr2
comma
id|wcr2
suffix:semicolon
multiline_comment|/* Allocate memory for MTD device structure and private data */
id|rtc_from4_mtd
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
id|rtc_from4_mtd
)paren
(brace
id|printk
(paren
l_string|&quot;Unable to allocate Renesas NAND MTD device structure.&bslash;n&quot;
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
id|rtc_from4_mtd
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
id|rtc_from4_mtd
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
id|rtc_from4_mtd-&gt;priv
op_assign
id|this
suffix:semicolon
multiline_comment|/* set area 5 as PCMCIA mode to clear the spec of tDH(Data hold time;9ns min) */
id|bcr1
op_assign
op_star
id|SH77X9_BCR1
op_amp
op_complement
l_int|0x0002
suffix:semicolon
id|bcr1
op_or_assign
l_int|0x0002
suffix:semicolon
op_star
id|SH77X9_BCR1
op_assign
id|bcr1
suffix:semicolon
multiline_comment|/* set */
id|bcr2
op_assign
op_star
id|SH77X9_BCR2
op_amp
op_complement
l_int|0x0c00
suffix:semicolon
id|bcr2
op_or_assign
l_int|0x0800
suffix:semicolon
op_star
id|SH77X9_BCR2
op_assign
id|bcr2
suffix:semicolon
multiline_comment|/* set area 5 wait states */
id|wcr2
op_assign
op_star
id|SH77X9_WCR2
op_amp
op_complement
l_int|0x1c00
suffix:semicolon
id|wcr2
op_or_assign
l_int|0x1c00
suffix:semicolon
op_star
id|SH77X9_WCR2
op_assign
id|wcr2
suffix:semicolon
multiline_comment|/* Set address of NAND IO lines */
id|this-&gt;IO_ADDR_R
op_assign
id|rtc_from4_fio_base
suffix:semicolon
id|this-&gt;IO_ADDR_W
op_assign
id|rtc_from4_fio_base
suffix:semicolon
multiline_comment|/* Set address of hardware control function */
id|this-&gt;hwcontrol
op_assign
id|rtc_from4_hwcontrol
suffix:semicolon
multiline_comment|/* Set address of chip select function */
id|this-&gt;select_chip
op_assign
id|rtc_from4_nand_select_chip
suffix:semicolon
multiline_comment|/* command delay time (in us) */
id|this-&gt;chip_delay
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* return the status of the Ready/Busy line */
id|this-&gt;dev_ready
op_assign
id|rtc_from4_nand_device_ready
suffix:semicolon
macro_line|#ifdef RTC_FROM4_HWECC
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;rtc_from4_init: using hardware ECC detection.&bslash;n&quot;
)paren
suffix:semicolon
id|this-&gt;eccmode
op_assign
id|NAND_ECC_HW8_512
suffix:semicolon
id|this-&gt;options
op_or_assign
id|NAND_HWECC_SYNDROME
suffix:semicolon
multiline_comment|/* set the nand_oobinfo to support FPGA H/W error detection */
id|this-&gt;autooob
op_assign
op_amp
id|rtc_from4_nand_oobinfo
suffix:semicolon
id|this-&gt;enable_hwecc
op_assign
id|rtc_from4_enable_hwecc
suffix:semicolon
id|this-&gt;calculate_ecc
op_assign
id|rtc_from4_calculate_ecc
suffix:semicolon
id|this-&gt;correct_data
op_assign
id|rtc_from4_correct_data
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;rtc_from4_init: using software ECC detection.&bslash;n&quot;
)paren
suffix:semicolon
id|this-&gt;eccmode
op_assign
id|NAND_ECC_SOFT
suffix:semicolon
macro_line|#endif
multiline_comment|/* set the bad block tables to support debugging */
id|this-&gt;bbt_td
op_assign
op_amp
id|rtc_from4_bbt_main_descr
suffix:semicolon
id|this-&gt;bbt_md
op_assign
op_amp
id|rtc_from4_bbt_mirror_descr
suffix:semicolon
multiline_comment|/* Scan to find existence of the device */
r_if
c_cond
(paren
id|nand_scan
c_func
(paren
id|rtc_from4_mtd
comma
id|RTC_FROM4_MAX_CHIPS
)paren
)paren
(brace
id|kfree
c_func
(paren
id|rtc_from4_mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Register the partitions */
id|add_mtd_partitions
c_func
(paren
id|rtc_from4_mtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
macro_line|#ifdef RTC_FROM4_HWECC
multiline_comment|/* We could create the decoder on demand, if memory is a concern.&n;&t; * This way we have it handy, if an error happens &n;&t; *&n;&t; * Symbolsize is 10 (bits)&n;&t; * Primitve polynomial is x^10+x^3+1&n;&t; * first consecutive root is 0&n;&t; * primitve element to generate roots = 1&n;&t; * generator polinomial degree = 6&n;&t; */
id|rs_decoder
op_assign
id|init_rs
c_func
(paren
l_int|10
comma
l_int|0x409
comma
l_int|0
comma
l_int|1
comma
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs_decoder
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Could not create a RS decoder&bslash;n&quot;
)paren
suffix:semicolon
id|nand_release
c_func
(paren
id|rtc_from4_mtd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rtc_from4_mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Return happy */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rtc_from4_init
id|module_init
c_func
(paren
id|rtc_from4_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up routine&n; */
macro_line|#ifdef MODULE
DECL|function|rtc_from4_cleanup
r_static
r_void
id|__exit
id|rtc_from4_cleanup
(paren
r_void
)paren
(brace
multiline_comment|/* Release resource, unregister partitions */
id|nand_release
c_func
(paren
id|rtc_from4_mtd
)paren
suffix:semicolon
multiline_comment|/* Free the MTD device structure */
id|kfree
(paren
id|rtc_from4_mtd
)paren
suffix:semicolon
macro_line|#ifdef RTC_FROM4_HWECC
multiline_comment|/* Free the reed solomon resources */
r_if
c_cond
(paren
id|rs_decoder
)paren
(brace
id|free_rs
c_func
(paren
id|rs_decoder
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|variable|rtc_from4_cleanup
id|module_exit
c_func
(paren
id|rtc_from4_cleanup
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
l_string|&quot;d.marlin &lt;dmarlin@redhat.com&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Board-specific glue layer for AG-AND flash on Renesas FROM_BOARD4&quot;
)paren
suffix:semicolon
eof
