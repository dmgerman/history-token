multiline_comment|/*&n; *  linux/include/linux/mtd/nand.h&n; *&n; *  Copyright (c) 2000 David Woodhouse &lt;dwmw2@mvhi.com&gt;&n; *                     Steven J. Hill &lt;sjhill@cotw.com&gt;&n; *&n; * $Id: nand.h,v 1.8 2000/10/30 17:16:17 sjhill Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Info:&n; *   Contains standard defines and IDs for NAND flash devices&n; *&n; *  Changelog:&n; *   01-31-2000 DMW     Created&n; *   09-18-2000 SJH     Moved structure out of the Disk-On-Chip drivers&n; *&t;&t;&t;so it can be used by other NAND flash device&n; *&t;&t;&t;drivers. I also changed the copyright since none&n; *&t;&t;&t;of the original contents of this file are specific&n; *&t;&t;&t;to DoC devices. David can whack me with a baseball&n; *&t;&t;&t;bat later if I did something naughty.&n; *   10-11-2000 SJH     Added private NAND flash structure for driver&n; *   10-24-2000 SJH     Added prototype for &squot;nand_scan&squot; function&n; */
macro_line|#ifndef __LINUX_MTD_NAND_H
DECL|macro|__LINUX_MTD_NAND_H
mdefine_line|#define __LINUX_MTD_NAND_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
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
multiline_comment|/*&n; * NAND Private Flash Chip Data&n; *&n; * Structure overview:&n; *&n; *  IO_ADDR - address to access the 8 I/O lines to the flash device&n; *&n; *  CTRL_ADDR - address where ALE, CLE and CE control bits are accessed&n; *&n; *  CLE - location in control word for Command Latch Enable bit&n; *&n; *  ALE - location in control word for Address Latch Enable bit&n; *&n; *  NCE - location in control word for nChip Enable bit&n; *&n; *  chip_lock - spinlock used to protect access to this structure&n; *&n; *  wq - wait queue to sleep on if a NAND operation is in progress&n; *&n; *  state - give the current state of the NAND device&n; *&n; *  page_shift - number of address bits in a page (column address bits)&n; *&n; *  data_buf - data buffer passed to/from MTD user modules&n; *&n; *  ecc_code_buf - used only for holding calculated or read ECCs for&n; *                 a page read or written when ECC is in use&n; *&n; *  reserved - padding to make structure fall on word boundary if&n; *             when ECC is in use&n; */
DECL|struct|nand_chip
r_struct
id|nand_chip
(brace
DECL|member|IO_ADDR
r_int
r_int
id|IO_ADDR
suffix:semicolon
DECL|member|CTRL_ADDR
r_int
r_int
id|CTRL_ADDR
suffix:semicolon
DECL|member|CLE
r_int
r_int
id|CLE
suffix:semicolon
DECL|member|ALE
r_int
r_int
id|ALE
suffix:semicolon
DECL|member|NCE
r_int
r_int
id|NCE
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
macro_line|#ifdef CONFIG_MTD_NAND_ECC
DECL|member|ecc_code_buf
id|u_char
id|ecc_code_buf
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved
id|u_char
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * NAND Flash Manufacturer ID Codes&n; */
DECL|macro|NAND_MFR_TOSHIBA
mdefine_line|#define NAND_MFR_TOSHIBA&t;0x98
DECL|macro|NAND_MFR_SAMSUNG
mdefine_line|#define NAND_MFR_SAMSUNG&t;0xec
multiline_comment|/*&n; * NAND Flash Device ID Structure&n; *&n; * Structure overview:&n; *&n; *  name - Complete name of device&n; *&n; *  manufacture_id - manufacturer ID code of device.&n; *&n; *  model_id - model ID code of device.&n; *&n; *  chipshift - total number of address bits for the device which&n; *              is used to calculate address offsets and the total&n; *              number of bytes the device is capable of.&n; *&n; *  page256 - denotes if flash device has 256 byte pages or not.&n; *&n; *  pageadrlen - number of bytes minus one needed to hold the&n; *               complete address into the flash array. Keep in&n; *               mind that when a read or write is done to a&n; *               specific address, the address is input serially&n; *               8 bits at a time. This structure member is used&n; *               by the read/write routines as a loop index for&n; *               shifting the address out 8 bits at a time.&n; *&n; *  erasesize - size of an erase block in the flash device.&n; */
DECL|struct|nand_flash_dev
r_struct
id|nand_flash_dev
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|manufacture_id
r_int
id|manufacture_id
suffix:semicolon
DECL|member|model_id
r_int
id|model_id
suffix:semicolon
DECL|member|chipshift
r_int
id|chipshift
suffix:semicolon
DECL|member|page256
r_char
id|page256
suffix:semicolon
DECL|member|pageadrlen
r_char
id|pageadrlen
suffix:semicolon
DECL|member|erasesize
r_int
r_int
id|erasesize
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_MTD_NAND_H */
eof
