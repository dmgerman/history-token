multiline_comment|/*&n; *  linux/include/linux/mtd/nand.h&n; *&n; *  Copyright (c) 2000 David Woodhouse &lt;dwmw2@mvhi.com&gt;&n; *                     Steven J. Hill &lt;sjhill@realitydiluted.com&gt;&n; *&t;&t;       Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *&n; * $Id: nand.h,v 1.25 2003/05/21 15:15:02 dwmw2 Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Info:&n; *   Contains standard defines and IDs for NAND flash devices&n; *&n; *  Changelog:&n; *   01-31-2000 DMW     Created&n; *   09-18-2000 SJH     Moved structure out of the Disk-On-Chip drivers&n; *&t;&t;&t;so it can be used by other NAND flash device&n; *&t;&t;&t;drivers. I also changed the copyright since none&n; *&t;&t;&t;of the original contents of this file are specific&n; *&t;&t;&t;to DoC devices. David can whack me with a baseball&n; *&t;&t;&t;bat later if I did something naughty.&n; *   10-11-2000 SJH     Added private NAND flash structure for driver&n; *   10-24-2000 SJH     Added prototype for &squot;nand_scan&squot; function&n; *   10-29-2001 TG&t;changed nand_chip structure to support &n; *&t;&t;&t;hardwarespecific function for accessing control lines&n; *   02-21-2002 TG&t;added support for different read/write adress and&n; *&t;&t;&t;ready/busy line access function&n; *   02-26-2002 TG&t;added chip_delay to nand_chip structure to optimize&n; *&t;&t;&t;command delay times for different chips&n; *   04-28-2002 TG&t;OOB config defines moved from nand.c to avoid duplicate&n; *&t;&t;&t;defines in jffs2/wbuf.c&n; *   08-07-2002 TG&t;forced bad block location to byte 5 of OOB, even if&n; *&t;&t;&t;CONFIG_MTD_NAND_ECC_JFFS2 is not set&n; *   08-10-2002 TG&t;extensions to nand_chip structure to support HW-ECC&n; *&n; *   08-29-2002 tglx &t;nand_chip structure: data_poi for selecting &n; *&t;&t;&t;internal / fs-driver buffer&n; *&t;&t;&t;support for 6byte/512byte hardware ECC&n; *&t;&t;&t;read_ecc, write_ecc extended for different oob-layout&n; *&t;&t;&t;oob layout selections: NAND_NONE_OOB, NAND_JFFS2_OOB,&n; *&t;&t;&t;NAND_YAFFS_OOB&n; *  11-25-2002 tglx&t;Added Manufacturer code FUJITSU, NATIONAL&n; *&t;&t;&t;Split manufacturer and device ID structures &n; */
macro_line|#ifndef __LINUX_MTD_NAND_H
DECL|macro|__LINUX_MTD_NAND_H
mdefine_line|#define __LINUX_MTD_NAND_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|mtd_info
suffix:semicolon
multiline_comment|/*&n; * Searches for a NAND device&n; */
r_extern
r_int
id|nand_scan
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
multiline_comment|/*&n; * Constants for hardware specific CLE/ALE/NCE function&n;*/
DECL|macro|NAND_CTL_SETNCE
mdefine_line|#define NAND_CTL_SETNCE &t;1
DECL|macro|NAND_CTL_CLRNCE
mdefine_line|#define NAND_CTL_CLRNCE&t;&t;2
DECL|macro|NAND_CTL_SETCLE
mdefine_line|#define NAND_CTL_SETCLE&t;&t;3
DECL|macro|NAND_CTL_CLRCLE
mdefine_line|#define NAND_CTL_CLRCLE&t;&t;4
DECL|macro|NAND_CTL_SETALE
mdefine_line|#define NAND_CTL_SETALE&t;&t;5
DECL|macro|NAND_CTL_CLRALE
mdefine_line|#define NAND_CTL_CLRALE&t;&t;6
multiline_comment|/*&n; * Standard NAND flash commands&n; */
DECL|macro|NAND_CMD_READ0
mdefine_line|#define NAND_CMD_READ0&t;&t;0
DECL|macro|NAND_CMD_READ1
mdefine_line|#define NAND_CMD_READ1&t;&t;1
DECL|macro|NAND_CMD_PAGEPROG
mdefine_line|#define NAND_CMD_PAGEPROG&t;0x10
DECL|macro|NAND_CMD_READOOB
mdefine_line|#define NAND_CMD_READOOB&t;0x50
DECL|macro|NAND_CMD_ERASE1
mdefine_line|#define NAND_CMD_ERASE1&t;&t;0x60
DECL|macro|NAND_CMD_STATUS
mdefine_line|#define NAND_CMD_STATUS&t;&t;0x70
DECL|macro|NAND_CMD_SEQIN
mdefine_line|#define NAND_CMD_SEQIN&t;&t;0x80
DECL|macro|NAND_CMD_READID
mdefine_line|#define NAND_CMD_READID&t;&t;0x90
DECL|macro|NAND_CMD_ERASE2
mdefine_line|#define NAND_CMD_ERASE2&t;&t;0xd0
DECL|macro|NAND_CMD_RESET
mdefine_line|#define NAND_CMD_RESET&t;&t;0xff
multiline_comment|/* &n; * Constants for ECC_MODES&n; *&n; * NONE:&t;No ECC&n; * SOFT:&t;Software ECC 3 byte ECC per 256 Byte data&n; * HW3_256:&t;Hardware ECC 3 byte ECC per 256 Byte data&n; * HW3_512:&t;Hardware ECC 3 byte ECC per 512 Byte data&n; *&n; *&n;*/
DECL|macro|NAND_ECC_NONE
mdefine_line|#define NAND_ECC_NONE&t;&t;0
DECL|macro|NAND_ECC_SOFT
mdefine_line|#define NAND_ECC_SOFT&t;&t;1
DECL|macro|NAND_ECC_HW3_256
mdefine_line|#define NAND_ECC_HW3_256&t;2
DECL|macro|NAND_ECC_HW3_512
mdefine_line|#define NAND_ECC_HW3_512&t;3
DECL|macro|NAND_ECC_HW6_512
mdefine_line|#define NAND_ECC_HW6_512&t;4
DECL|macro|NAND_ECC_DISKONCHIP
mdefine_line|#define NAND_ECC_DISKONCHIP&t;5
multiline_comment|/*&n; * Constants for Hardware ECC&n;*/
DECL|macro|NAND_ECC_READ
mdefine_line|#define NAND_ECC_READ&t;&t;0
DECL|macro|NAND_ECC_WRITE
mdefine_line|#define NAND_ECC_WRITE&t;&t;1
multiline_comment|/*&n; * Enumeration for NAND flash chip state&n; */
r_typedef
r_enum
(brace
DECL|enumerator|FL_READY
id|FL_READY
comma
DECL|enumerator|FL_READING
id|FL_READING
comma
DECL|enumerator|FL_WRITING
id|FL_WRITING
comma
DECL|enumerator|FL_ERASING
id|FL_ERASING
comma
DECL|enumerator|FL_SYNCING
id|FL_SYNCING
DECL|typedef|nand_state_t
)brace
id|nand_state_t
suffix:semicolon
multiline_comment|/*&n; * NAND Private Flash Chip Data&n; *&n; * Structure overview:&n; *&n; *  IO_ADDR_R - address to read the 8 I/O lines of the flash device &n; *&n; *  IO_ADDR_W - address to write the 8 I/O lines of the flash device &n; *&n; *  hwcontrol - hardwarespecific function for accesing control-lines&n; *&n; *  dev_ready - hardwarespecific function for accesing device ready/busy line&n; *&n; *  waitfunc - hardwarespecific function for wait on ready&n; *&n; *  calculate_ecc - function for ecc calculation or readback from ecc hardware&n; *&n; *  correct_data - function for ecc correction, matching to ecc generator (sw/hw)&n; *&n; *  enable_hwecc - function to enable (reset) hardware ecc generator&n; *&n; *  eccmod - mode of ecc: see constants&n; *&n; *  eccsize - databytes used per ecc-calculation&n; *&n; *  chip_delay - chip dependent delay for transfering data from array to read regs (tR)&n; *&n; *  chip_lock - spinlock used to protect access to this structure&n; *&n; *  wq - wait queue to sleep on if a NAND operation is in progress&n; *&n; *  state - give the current state of the NAND device&n; *&n; *  page_shift - number of address bits in a page (column address bits)&n; *&n; *  data_buf - data buffer passed to/from MTD user modules&n; *&n; *  data_cache - data cache for redundant page access and shadow for&n; *&t;&t; ECC failure&n; *&n; *  cache_page - number of last valid page in page_cache &n; */
DECL|struct|nand_chip
r_struct
id|nand_chip
(brace
DECL|member|IO_ADDR_R
r_int
r_int
id|IO_ADDR_R
suffix:semicolon
DECL|member|IO_ADDR_W
r_int
r_int
id|IO_ADDR_W
suffix:semicolon
DECL|member|hwcontrol
r_void
(paren
op_star
id|hwcontrol
)paren
(paren
r_int
id|cmd
)paren
suffix:semicolon
DECL|member|dev_ready
r_int
(paren
op_star
id|dev_ready
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|cmdfunc
r_void
(paren
op_star
id|cmdfunc
)paren
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
suffix:semicolon
DECL|member|waitfunc
r_int
(paren
op_star
id|waitfunc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|nand_chip
op_star
id|this
comma
r_int
id|state
)paren
suffix:semicolon
DECL|member|calculate_ecc
r_void
(paren
op_star
id|calculate_ecc
)paren
(paren
r_const
id|u_char
op_star
id|dat
comma
id|u_char
op_star
id|ecc_code
)paren
suffix:semicolon
DECL|member|correct_data
r_int
(paren
op_star
id|correct_data
)paren
(paren
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
suffix:semicolon
DECL|member|enable_hwecc
r_void
(paren
op_star
id|enable_hwecc
)paren
(paren
r_int
id|mode
)paren
suffix:semicolon
DECL|member|eccmode
r_int
id|eccmode
suffix:semicolon
DECL|member|eccsize
r_int
id|eccsize
suffix:semicolon
DECL|member|chip_delay
r_int
id|chip_delay
suffix:semicolon
DECL|member|chip_lock
id|spinlock_t
id|chip_lock
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|state
id|nand_state_t
id|state
suffix:semicolon
DECL|member|page_shift
r_int
id|page_shift
suffix:semicolon
DECL|member|data_buf
id|u_char
op_star
id|data_buf
suffix:semicolon
DECL|member|data_poi
id|u_char
op_star
id|data_poi
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * NAND Flash Manufacturer ID Codes&n; */
DECL|macro|NAND_MFR_TOSHIBA
mdefine_line|#define NAND_MFR_TOSHIBA&t;0x98
DECL|macro|NAND_MFR_SAMSUNG
mdefine_line|#define NAND_MFR_SAMSUNG&t;0xec
DECL|macro|NAND_MFR_FUJITSU
mdefine_line|#define NAND_MFR_FUJITSU&t;0x04
DECL|macro|NAND_MFR_NATIONAL
mdefine_line|#define NAND_MFR_NATIONAL&t;0x8f
multiline_comment|/*&n; * NAND Flash Device ID Structure&n; *&n; * Structure overview:&n; *&n; *  name - Identify the device type&n; *&n; *  id -  device ID code&n; *&n; *  chipshift - total number of address bits for the device which&n; *              is used to calculate address offsets and the total&n; *              number of bytes the device is capable of.&n; *&n; *  page256 - denotes if flash device has 256 byte pages or not.&n; *&n; *  pageadrlen - number of bytes minus one needed to hold the&n; *               complete address into the flash array. Keep in&n; *               mind that when a read or write is done to a&n; *               specific address, the address is input serially&n; *               8 bits at a time. This structure member is used&n; *               by the read/write routines as a loop index for&n; *               shifting the address out 8 bits at a time.&n; *&n; *  erasesize - size of an erase block in the flash device.&n; */
DECL|struct|nand_flash_dev
r_struct
id|nand_flash_dev
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|chipshift
r_int
id|chipshift
suffix:semicolon
DECL|member|erasesize
r_int
r_int
id|erasesize
suffix:semicolon
DECL|member|page256
r_char
id|page256
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * NAND Flash Manufacturer ID Structure&n; *&n; *  name - Manufacturer name&n; *&n; *  id - manufacturer ID code of device.&n;*/
DECL|struct|nand_manufacturers
r_struct
id|nand_manufacturers
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|nand_flash_dev
id|nand_flash_ids
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|nand_manufacturers
id|nand_manuf_ids
(braket
)braket
suffix:semicolon
multiline_comment|/*&n;* Constants for oob configuration&n;*/
DECL|macro|NAND_BADBLOCK_POS
mdefine_line|#define NAND_BADBLOCK_POS&t;&t;5
macro_line|#endif /* __LINUX_MTD_NAND_H */
eof
