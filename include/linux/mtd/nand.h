multiline_comment|/*&n; *  linux/include/linux/mtd/nand.h&n; *&n; *  Copyright (c) 2000 David Woodhouse &lt;dwmw2@mvhi.com&gt;&n; *                     Steven J. Hill &lt;sjhill@realitydiluted.com&gt;&n; *&t;&t;       Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *&n; * $Id: nand.h,v 1.68 2004/11/12 10:40:37 gleixner Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Info:&n; *   Contains standard defines and IDs for NAND flash devices&n; *&n; *  Changelog:&n; *   01-31-2000 DMW     Created&n; *   09-18-2000 SJH     Moved structure out of the Disk-On-Chip drivers&n; *&t;&t;&t;so it can be used by other NAND flash device&n; *&t;&t;&t;drivers. I also changed the copyright since none&n; *&t;&t;&t;of the original contents of this file are specific&n; *&t;&t;&t;to DoC devices. David can whack me with a baseball&n; *&t;&t;&t;bat later if I did something naughty.&n; *   10-11-2000 SJH     Added private NAND flash structure for driver&n; *   10-24-2000 SJH     Added prototype for &squot;nand_scan&squot; function&n; *   10-29-2001 TG&t;changed nand_chip structure to support &n; *&t;&t;&t;hardwarespecific function for accessing control lines&n; *   02-21-2002 TG&t;added support for different read/write adress and&n; *&t;&t;&t;ready/busy line access function&n; *   02-26-2002 TG&t;added chip_delay to nand_chip structure to optimize&n; *&t;&t;&t;command delay times for different chips&n; *   04-28-2002 TG&t;OOB config defines moved from nand.c to avoid duplicate&n; *&t;&t;&t;defines in jffs2/wbuf.c&n; *   08-07-2002 TG&t;forced bad block location to byte 5 of OOB, even if&n; *&t;&t;&t;CONFIG_MTD_NAND_ECC_JFFS2 is not set&n; *   08-10-2002 TG&t;extensions to nand_chip structure to support HW-ECC&n; *&n; *   08-29-2002 tglx &t;nand_chip structure: data_poi for selecting &n; *&t;&t;&t;internal / fs-driver buffer&n; *&t;&t;&t;support for 6byte/512byte hardware ECC&n; *&t;&t;&t;read_ecc, write_ecc extended for different oob-layout&n; *&t;&t;&t;oob layout selections: NAND_NONE_OOB, NAND_JFFS2_OOB,&n; *&t;&t;&t;NAND_YAFFS_OOB&n; *  11-25-2002 tglx&t;Added Manufacturer code FUJITSU, NATIONAL&n; *&t;&t;&t;Split manufacturer and device ID structures &n; *&n; *  02-08-2004 tglx &t;added option field to nand structure for chip anomalities&n; *  05-25-2004 tglx &t;added bad block table support, ST-MICRO manufacturer id&n; *&t;&t;&t;update of nand_chip structure description&n; */
macro_line|#ifndef __LINUX_MTD_NAND_H
DECL|macro|__LINUX_MTD_NAND_H
mdefine_line|#define __LINUX_MTD_NAND_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
r_struct
id|mtd_info
suffix:semicolon
multiline_comment|/* Scan and identify a NAND device */
r_extern
r_int
id|nand_scan
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|max_chips
)paren
suffix:semicolon
multiline_comment|/* Free resources held by the NAND device */
r_extern
r_void
id|nand_release
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
multiline_comment|/* Read raw data from the device without ECC */
r_extern
r_int
id|nand_read_raw
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_uint8
op_star
id|buf
comma
id|loff_t
id|from
comma
r_int
id|len
comma
r_int
id|ooblen
)paren
suffix:semicolon
multiline_comment|/* The maximum number of NAND chips in an array */
DECL|macro|NAND_MAX_CHIPS
mdefine_line|#define NAND_MAX_CHIPS&t;&t;8
multiline_comment|/* This constant declares the max. oobsize / page, which&n; * is supported now. If you add a chip with bigger oobsize/page&n; * adjust this accordingly.&n; */
DECL|macro|NAND_MAX_OOBSIZE
mdefine_line|#define NAND_MAX_OOBSIZE&t;64
multiline_comment|/*&n; * Constants for hardware specific CLE/ALE/NCE function&n;*/
multiline_comment|/* Select the chip by setting nCE to low */
DECL|macro|NAND_CTL_SETNCE
mdefine_line|#define NAND_CTL_SETNCE &t;1
multiline_comment|/* Deselect the chip by setting nCE to high */
DECL|macro|NAND_CTL_CLRNCE
mdefine_line|#define NAND_CTL_CLRNCE&t;&t;2
multiline_comment|/* Select the command latch by setting CLE to high */
DECL|macro|NAND_CTL_SETCLE
mdefine_line|#define NAND_CTL_SETCLE&t;&t;3
multiline_comment|/* Deselect the command latch by setting CLE to low */
DECL|macro|NAND_CTL_CLRCLE
mdefine_line|#define NAND_CTL_CLRCLE&t;&t;4
multiline_comment|/* Select the address latch by setting ALE to high */
DECL|macro|NAND_CTL_SETALE
mdefine_line|#define NAND_CTL_SETALE&t;&t;5
multiline_comment|/* Deselect the address latch by setting ALE to low */
DECL|macro|NAND_CTL_CLRALE
mdefine_line|#define NAND_CTL_CLRALE&t;&t;6
multiline_comment|/* Set write protection by setting WP to high. Not used! */
DECL|macro|NAND_CTL_SETWP
mdefine_line|#define NAND_CTL_SETWP&t;&t;7
multiline_comment|/* Clear write protection by setting WP to low. Not used! */
DECL|macro|NAND_CTL_CLRWP
mdefine_line|#define NAND_CTL_CLRWP&t;&t;8
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
DECL|macro|NAND_CMD_STATUS_MULTI
mdefine_line|#define NAND_CMD_STATUS_MULTI&t;0x71
DECL|macro|NAND_CMD_SEQIN
mdefine_line|#define NAND_CMD_SEQIN&t;&t;0x80
DECL|macro|NAND_CMD_READID
mdefine_line|#define NAND_CMD_READID&t;&t;0x90
DECL|macro|NAND_CMD_ERASE2
mdefine_line|#define NAND_CMD_ERASE2&t;&t;0xd0
DECL|macro|NAND_CMD_RESET
mdefine_line|#define NAND_CMD_RESET&t;&t;0xff
multiline_comment|/* Extended commands for large page devices */
DECL|macro|NAND_CMD_READSTART
mdefine_line|#define NAND_CMD_READSTART&t;0x30
DECL|macro|NAND_CMD_CACHEDPROG
mdefine_line|#define NAND_CMD_CACHEDPROG&t;0x15
multiline_comment|/* Status bits */
DECL|macro|NAND_STATUS_FAIL
mdefine_line|#define NAND_STATUS_FAIL&t;0x01
DECL|macro|NAND_STATUS_FAIL_N1
mdefine_line|#define NAND_STATUS_FAIL_N1&t;0x02
DECL|macro|NAND_STATUS_TRUE_READY
mdefine_line|#define NAND_STATUS_TRUE_READY&t;0x20
DECL|macro|NAND_STATUS_READY
mdefine_line|#define NAND_STATUS_READY&t;0x40
DECL|macro|NAND_STATUS_WP
mdefine_line|#define NAND_STATUS_WP&t;&t;0x80
multiline_comment|/* &n; * Constants for ECC_MODES&n; */
multiline_comment|/* No ECC. Usage is not recommended ! */
DECL|macro|NAND_ECC_NONE
mdefine_line|#define NAND_ECC_NONE&t;&t;0
multiline_comment|/* Software ECC 3 byte ECC per 256 Byte data */
DECL|macro|NAND_ECC_SOFT
mdefine_line|#define NAND_ECC_SOFT&t;&t;1
multiline_comment|/* Hardware ECC 3 byte ECC per 256 Byte data */
DECL|macro|NAND_ECC_HW3_256
mdefine_line|#define NAND_ECC_HW3_256&t;2
multiline_comment|/* Hardware ECC 3 byte ECC per 512 Byte data */
DECL|macro|NAND_ECC_HW3_512
mdefine_line|#define NAND_ECC_HW3_512&t;3
multiline_comment|/* Hardware ECC 3 byte ECC per 512 Byte data */
DECL|macro|NAND_ECC_HW6_512
mdefine_line|#define NAND_ECC_HW6_512&t;4
multiline_comment|/* Hardware ECC 8 byte ECC per 512 Byte data */
DECL|macro|NAND_ECC_HW8_512
mdefine_line|#define NAND_ECC_HW8_512&t;6
multiline_comment|/* Hardware ECC 12 byte ECC per 2048 Byte data */
DECL|macro|NAND_ECC_HW12_2048
mdefine_line|#define NAND_ECC_HW12_2048&t;7
multiline_comment|/*&n; * Constants for Hardware ECC&n;*/
multiline_comment|/* Reset Hardware ECC for read */
DECL|macro|NAND_ECC_READ
mdefine_line|#define NAND_ECC_READ&t;&t;0
multiline_comment|/* Reset Hardware ECC for write */
DECL|macro|NAND_ECC_WRITE
mdefine_line|#define NAND_ECC_WRITE&t;&t;1
multiline_comment|/* Enable Hardware ECC before syndrom is read back from flash */
DECL|macro|NAND_ECC_READSYN
mdefine_line|#define NAND_ECC_READSYN&t;2
multiline_comment|/* Option constants for bizarre disfunctionality and real&n;*  features&n;*/
multiline_comment|/* Chip can not auto increment pages */
DECL|macro|NAND_NO_AUTOINCR
mdefine_line|#define NAND_NO_AUTOINCR&t;0x00000001
multiline_comment|/* Buswitdh is 16 bit */
DECL|macro|NAND_BUSWIDTH_16
mdefine_line|#define NAND_BUSWIDTH_16&t;0x00000002
multiline_comment|/* Device supports partial programming without padding */
DECL|macro|NAND_NO_PADDING
mdefine_line|#define NAND_NO_PADDING&t;&t;0x00000004
multiline_comment|/* Chip has cache program function */
DECL|macro|NAND_CACHEPRG
mdefine_line|#define NAND_CACHEPRG&t;&t;0x00000008
multiline_comment|/* Chip has copy back function */
DECL|macro|NAND_COPYBACK
mdefine_line|#define NAND_COPYBACK&t;&t;0x00000010
multiline_comment|/* AND Chip which has 4 banks and a confusing page / block &n; * assignment. See Renesas datasheet for further information */
DECL|macro|NAND_IS_AND
mdefine_line|#define NAND_IS_AND&t;&t;0x00000020
multiline_comment|/* Chip has a array of 4 pages which can be read without&n; * additional ready /busy waits */
DECL|macro|NAND_4PAGE_ARRAY
mdefine_line|#define NAND_4PAGE_ARRAY&t;0x00000040 
multiline_comment|/* Options valid for Samsung large page devices */
DECL|macro|NAND_SAMSUNG_LP_OPTIONS
mdefine_line|#define NAND_SAMSUNG_LP_OPTIONS &bslash;&n;&t;(NAND_NO_PADDING | NAND_CACHEPRG | NAND_COPYBACK)
multiline_comment|/* Macros to identify the above */
DECL|macro|NAND_CANAUTOINCR
mdefine_line|#define NAND_CANAUTOINCR(chip) (!(chip-&gt;options &amp; NAND_NO_AUTOINCR))
DECL|macro|NAND_MUST_PAD
mdefine_line|#define NAND_MUST_PAD(chip) (!(chip-&gt;options &amp; NAND_NO_PADDING))
DECL|macro|NAND_HAS_CACHEPROG
mdefine_line|#define NAND_HAS_CACHEPROG(chip) ((chip-&gt;options &amp; NAND_CACHEPRG))
DECL|macro|NAND_HAS_COPYBACK
mdefine_line|#define NAND_HAS_COPYBACK(chip) ((chip-&gt;options &amp; NAND_COPYBACK))
multiline_comment|/* Mask to zero out the chip options, which come from the id table */
DECL|macro|NAND_CHIPOPTIONS_MSK
mdefine_line|#define NAND_CHIPOPTIONS_MSK&t;(0x0000ffff &amp; ~NAND_NO_AUTOINCR)
multiline_comment|/* Non chip related options */
multiline_comment|/* Use a flash based bad block table. This option is passed to the&n; * default bad block table function. */
DECL|macro|NAND_USE_FLASH_BBT
mdefine_line|#define NAND_USE_FLASH_BBT&t;0x00010000
multiline_comment|/* The hw ecc generator provides a syndrome instead a ecc value on read &n; * This can only work if we have the ecc bytes directly behind the &n; * data bytes. Applies for DOC and AG-AND Renesas HW Reed Solomon generators */
DECL|macro|NAND_HWECC_SYNDROME
mdefine_line|#define NAND_HWECC_SYNDROME&t;0x00020000
multiline_comment|/* Options set by nand scan */
multiline_comment|/* Nand scan has allocated oob_buf */
DECL|macro|NAND_OOBBUF_ALLOC
mdefine_line|#define NAND_OOBBUF_ALLOC&t;0x40000000
multiline_comment|/* Nand scan has allocated data_buf */
DECL|macro|NAND_DATABUF_ALLOC
mdefine_line|#define NAND_DATABUF_ALLOC&t;0x80000000
multiline_comment|/*&n; * nand_state_t - chip states&n; * Enumeration for NAND flash chip state&n; */
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
comma
DECL|enumerator|FL_CACHEDPRG
id|FL_CACHEDPRG
comma
DECL|typedef|nand_state_t
)brace
id|nand_state_t
suffix:semicolon
multiline_comment|/* Keep gcc happy */
r_struct
id|nand_chip
suffix:semicolon
multiline_comment|/**&n; * struct nand_hw_control - Control structure for hardware controller (e.g ECC generator) shared among independend devices&n; * @lock:               protection lock  &n; * @active:&t;&t;the mtd device which holds the controller currently&n; */
DECL|struct|nand_hw_control
r_struct
id|nand_hw_control
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|active
r_struct
id|nand_chip
op_star
id|active
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct nand_chip - NAND Private Flash Chip Data&n; * @IO_ADDR_R:&t;&t;[BOARDSPECIFIC] address to read the 8 I/O lines of the flash device &n; * @IO_ADDR_W:&t;&t;[BOARDSPECIFIC] address to write the 8 I/O lines of the flash device &n; * @read_byte:&t;&t;[REPLACEABLE] read one byte from the chip&n; * @write_byte:&t;&t;[REPLACEABLE] write one byte to the chip&n; * @read_word:&t;&t;[REPLACEABLE] read one word from the chip&n; * @write_word:&t;&t;[REPLACEABLE] write one word to the chip&n; * @write_buf:&t;&t;[REPLACEABLE] write data from the buffer to the chip&n; * @read_buf:&t;&t;[REPLACEABLE] read data from the chip into the buffer&n; * @verify_buf:&t;&t;[REPLACEABLE] verify buffer contents against the chip data&n; * @select_chip:&t;[REPLACEABLE] select chip nr&n; * @block_bad:&t;&t;[REPLACEABLE] check, if the block is bad&n; * @block_markbad:&t;[REPLACEABLE] mark the block bad&n; * @hwcontrol:&t;&t;[BOARDSPECIFIC] hardwarespecific function for accesing control-lines&n; * @dev_ready:&t;&t;[BOARDSPECIFIC] hardwarespecific function for accesing device ready/busy line&n; *&t;&t;&t;If set to NULL no access to ready/busy is available and the ready/busy information&n; *&t;&t;&t;is read from the chip status register&n; * @cmdfunc:&t;&t;[REPLACEABLE] hardwarespecific function for writing commands to the chip&n; * @waitfunc:&t;&t;[REPLACEABLE] hardwarespecific function for wait on ready&n; * @calculate_ecc: &t;[REPLACEABLE] function for ecc calculation or readback from ecc hardware&n; * @correct_data:&t;[REPLACEABLE] function for ecc correction, matching to ecc generator (sw/hw)&n; * @enable_hwecc:&t;[BOARDSPECIFIC] function to enable (reset) hardware ecc generator. Must only&n; *&t;&t;&t;be provided if a hardware ECC is available&n; * @erase_cmd:&t;&t;[INTERN] erase command write function, selectable due to AND support&n; * @scan_bbt:&t;&t;[REPLACEABLE] function to scan bad block table&n; * @eccmode:&t;&t;[BOARDSPECIFIC] mode of ecc, see defines &n; * @eccsize: &t;&t;[INTERN] databytes used per ecc-calculation&n; * @eccbytes: &t;&t;[INTERN] number of ecc bytes per ecc-calculation step&n; * @eccsteps:&t;&t;[INTERN] number of ecc calculation steps per page&n; * @chip_delay:&t;&t;[BOARDSPECIFIC] chip dependent delay for transfering data from array to read regs (tR)&n; * @chip_lock:&t;&t;[INTERN] spinlock used to protect access to this structure and the chip&n; * @wq:&t;&t;&t;[INTERN] wait queue to sleep on if a NAND operation is in progress&n; * @state: &t;&t;[INTERN] the current state of the NAND device&n; * @page_shift:&t;&t;[INTERN] number of address bits in a page (column address bits)&n; * @phys_erase_shift:&t;[INTERN] number of address bits in a physical eraseblock&n; * @bbt_erase_shift:&t;[INTERN] number of address bits in a bbt entry&n; * @chip_shift:&t;&t;[INTERN] number of address bits in one chip&n; * @data_buf:&t;&t;[INTERN] internal buffer for one page + oob &n; * @oob_buf:&t;&t;[INTERN] oob buffer for one eraseblock&n; * @oobdirty:&t;&t;[INTERN] indicates that oob_buf must be reinitialized&n; * @data_poi:&t;&t;[INTERN] pointer to a data buffer&n; * @options:&t;&t;[BOARDSPECIFIC] various chip options. They can partly be set to inform nand_scan about&n; *&t;&t;&t;special functionality. See the defines for further explanation&n; * @badblockpos:&t;[INTERN] position of the bad block marker in the oob area&n; * @numchips:&t;&t;[INTERN] number of physical chips&n; * @chipsize:&t;&t;[INTERN] the size of one chip for multichip arrays&n; * @pagemask:&t;&t;[INTERN] page number mask = number of (pages / chip) - 1&n; * @pagebuf:&t;&t;[INTERN] holds the pagenumber which is currently in data_buf&n; * @autooob:&t;&t;[REPLACEABLE] the default (auto)placement scheme&n; * @bbt:&t;&t;[INTERN] bad block table pointer&n; * @bbt_td:&t;&t;[REPLACEABLE] bad block table descriptor for flash lookup&n; * @bbt_md:&t;&t;[REPLACEABLE] bad block table mirror descriptor&n; * @badblock_pattern:&t;[REPLACEABLE] bad block scan pattern used for initial bad block scan &n; * @controller:&t;&t;[OPTIONAL] a pointer to a hardware controller structure which is shared among multiple independend devices&n; * @priv:&t;&t;[OPTIONAL] pointer to private chip date&n; */
DECL|struct|nand_chip
r_struct
id|nand_chip
(brace
DECL|member|IO_ADDR_R
r_void
id|__iomem
op_star
id|IO_ADDR_R
suffix:semicolon
DECL|member|IO_ADDR_W
r_void
id|__iomem
op_star
id|IO_ADDR_W
suffix:semicolon
DECL|member|read_byte
id|u_char
(paren
op_star
id|read_byte
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|write_byte
r_void
(paren
op_star
id|write_byte
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
id|byte
)paren
suffix:semicolon
DECL|member|read_word
id|u16
(paren
op_star
id|read_word
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|member|write_word
r_void
(paren
op_star
id|write_word
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u16
id|word
)paren
suffix:semicolon
DECL|member|write_buf
r_void
(paren
op_star
id|write_buf
)paren
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
suffix:semicolon
DECL|member|read_buf
r_void
(paren
op_star
id|read_buf
)paren
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
suffix:semicolon
DECL|member|verify_buf
r_int
(paren
op_star
id|verify_buf
)paren
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
suffix:semicolon
DECL|member|select_chip
r_void
(paren
op_star
id|select_chip
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|chip
)paren
suffix:semicolon
DECL|member|block_bad
r_int
(paren
op_star
id|block_bad
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
comma
r_int
id|getchip
)paren
suffix:semicolon
DECL|member|block_markbad
r_int
(paren
op_star
id|block_markbad
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|ofs
)paren
suffix:semicolon
DECL|member|hwcontrol
r_void
(paren
op_star
id|hwcontrol
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
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
r_struct
id|mtd_info
op_star
id|mtd
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
r_int
(paren
op_star
id|calculate_ecc
)paren
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
suffix:semicolon
DECL|member|correct_data
r_int
(paren
op_star
id|correct_data
)paren
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
suffix:semicolon
DECL|member|enable_hwecc
r_void
(paren
op_star
id|enable_hwecc
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|mode
)paren
suffix:semicolon
DECL|member|erase_cmd
r_void
(paren
op_star
id|erase_cmd
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|page
)paren
suffix:semicolon
DECL|member|scan_bbt
r_int
(paren
op_star
id|scan_bbt
)paren
(paren
r_struct
id|mtd_info
op_star
id|mtd
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
DECL|member|eccbytes
r_int
id|eccbytes
suffix:semicolon
DECL|member|eccsteps
r_int
id|eccsteps
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
DECL|member|phys_erase_shift
r_int
id|phys_erase_shift
suffix:semicolon
DECL|member|bbt_erase_shift
r_int
id|bbt_erase_shift
suffix:semicolon
DECL|member|chip_shift
r_int
id|chip_shift
suffix:semicolon
DECL|member|data_buf
id|u_char
op_star
id|data_buf
suffix:semicolon
DECL|member|oob_buf
id|u_char
op_star
id|oob_buf
suffix:semicolon
DECL|member|oobdirty
r_int
id|oobdirty
suffix:semicolon
DECL|member|data_poi
id|u_char
op_star
id|data_poi
suffix:semicolon
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
DECL|member|badblockpos
r_int
id|badblockpos
suffix:semicolon
DECL|member|numchips
r_int
id|numchips
suffix:semicolon
DECL|member|chipsize
r_int
r_int
id|chipsize
suffix:semicolon
DECL|member|pagemask
r_int
id|pagemask
suffix:semicolon
DECL|member|pagebuf
r_int
id|pagebuf
suffix:semicolon
DECL|member|autooob
r_struct
id|nand_oobinfo
op_star
id|autooob
suffix:semicolon
DECL|member|bbt
r_uint8
op_star
id|bbt
suffix:semicolon
DECL|member|bbt_td
r_struct
id|nand_bbt_descr
op_star
id|bbt_td
suffix:semicolon
DECL|member|bbt_md
r_struct
id|nand_bbt_descr
op_star
id|bbt_md
suffix:semicolon
DECL|member|badblock_pattern
r_struct
id|nand_bbt_descr
op_star
id|badblock_pattern
suffix:semicolon
DECL|member|controller
r_struct
id|nand_hw_control
op_star
id|controller
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
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
DECL|macro|NAND_MFR_RENESAS
mdefine_line|#define NAND_MFR_RENESAS&t;0x07
DECL|macro|NAND_MFR_STMICRO
mdefine_line|#define NAND_MFR_STMICRO&t;0x20
multiline_comment|/**&n; * struct nand_flash_dev - NAND Flash Device ID Structure&n; *&n; * @name:  &t;Identify the device type&n; * @id:   &t;device ID code&n; * @pagesize:  &t;Pagesize in bytes. Either 256 or 512 or 0&n; *&t;&t;If the pagesize is 0, then the real pagesize &n; *&t;&t;and the eraseize are determined from the&n; *&t;&t;extended id bytes in the chip&n; * @erasesize: &t;Size of an erase block in the flash device.&n; * @chipsize:  &t;Total chipsize in Mega Bytes&n; * @options:&t;Bitfield to store chip relevant options&n; */
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
DECL|member|pagesize
r_int
r_int
id|pagesize
suffix:semicolon
DECL|member|chipsize
r_int
r_int
id|chipsize
suffix:semicolon
DECL|member|erasesize
r_int
r_int
id|erasesize
suffix:semicolon
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct nand_manufacturers - NAND Flash Manufacturer ID Structure&n; * @name:&t;Manufacturer name&n; * @id: &t;manufacturer ID code of device.&n;*/
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
multiline_comment|/** &n; * struct nand_bbt_descr - bad block table descriptor&n; * @options:&t;options for this descriptor&n; * @pages:&t;the page(s) where we find the bbt, used with option BBT_ABSPAGE&n; *&t;&t;when bbt is searched, then we store the found bbts pages here.&n; *&t;&t;Its an array and supports up to 8 chips now&n; * @offs:&t;offset of the pattern in the oob area of the page&n; * @veroffs:&t;offset of the bbt version counter in the oob are of the page&n; * @version:&t;version read from the bbt page during scan&n; * @len:&t;length of the pattern, if 0 no pattern check is performed&n; * @maxblocks:&t;maximum number of blocks to search for a bbt. This number of&n; *&t;&t;blocks is reserved at the end of the device where the tables are &n; *&t;&t;written.&n; * @reserved_block_code: if non-0, this pattern denotes a reserved (rather than&n; *              bad) block in the stored bbt&n; * @pattern:&t;pattern to identify bad block table or factory marked good / &n; *&t;&t;bad blocks, can be NULL, if len = 0&n; *&n; * Descriptor for the bad block table marker and the descriptor for the &n; * pattern which identifies good and bad blocks. The assumption is made&n; * that the pattern and the version count are always located in the oob area&n; * of the first block.&n; */
DECL|struct|nand_bbt_descr
r_struct
id|nand_bbt_descr
(brace
DECL|member|options
r_int
id|options
suffix:semicolon
DECL|member|pages
r_int
id|pages
(braket
id|NAND_MAX_CHIPS
)braket
suffix:semicolon
DECL|member|offs
r_int
id|offs
suffix:semicolon
DECL|member|veroffs
r_int
id|veroffs
suffix:semicolon
DECL|member|version
r_uint8
id|version
(braket
id|NAND_MAX_CHIPS
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|maxblocks
r_int
id|maxblocks
suffix:semicolon
DECL|member|reserved_block_code
r_int
id|reserved_block_code
suffix:semicolon
DECL|member|pattern
r_uint8
op_star
id|pattern
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Options for the bad block table descriptors */
multiline_comment|/* The number of bits used per block in the bbt on the device */
DECL|macro|NAND_BBT_NRBITS_MSK
mdefine_line|#define NAND_BBT_NRBITS_MSK&t;0x0000000F
DECL|macro|NAND_BBT_1BIT
mdefine_line|#define NAND_BBT_1BIT&t;&t;0x00000001
DECL|macro|NAND_BBT_2BIT
mdefine_line|#define NAND_BBT_2BIT&t;&t;0x00000002
DECL|macro|NAND_BBT_4BIT
mdefine_line|#define NAND_BBT_4BIT&t;&t;0x00000004
DECL|macro|NAND_BBT_8BIT
mdefine_line|#define NAND_BBT_8BIT&t;&t;0x00000008
multiline_comment|/* The bad block table is in the last good block of the device */
DECL|macro|NAND_BBT_LASTBLOCK
mdefine_line|#define&t;NAND_BBT_LASTBLOCK&t;0x00000010
multiline_comment|/* The bbt is at the given page, else we must scan for the bbt */
DECL|macro|NAND_BBT_ABSPAGE
mdefine_line|#define NAND_BBT_ABSPAGE&t;0x00000020
multiline_comment|/* The bbt is at the given page, else we must scan for the bbt */
DECL|macro|NAND_BBT_SEARCH
mdefine_line|#define NAND_BBT_SEARCH&t;&t;0x00000040
multiline_comment|/* bbt is stored per chip on multichip devices */
DECL|macro|NAND_BBT_PERCHIP
mdefine_line|#define NAND_BBT_PERCHIP&t;0x00000080
multiline_comment|/* bbt has a version counter at offset veroffs */
DECL|macro|NAND_BBT_VERSION
mdefine_line|#define NAND_BBT_VERSION&t;0x00000100
multiline_comment|/* Create a bbt if none axists */
DECL|macro|NAND_BBT_CREATE
mdefine_line|#define NAND_BBT_CREATE&t;&t;0x00000200
multiline_comment|/* Search good / bad pattern through all pages of a block */
DECL|macro|NAND_BBT_SCANALLPAGES
mdefine_line|#define NAND_BBT_SCANALLPAGES&t;0x00000400
multiline_comment|/* Scan block empty during good / bad block scan */
DECL|macro|NAND_BBT_SCANEMPTY
mdefine_line|#define NAND_BBT_SCANEMPTY&t;0x00000800
multiline_comment|/* Write bbt if neccecary */
DECL|macro|NAND_BBT_WRITE
mdefine_line|#define NAND_BBT_WRITE&t;&t;0x00001000
multiline_comment|/* Read and write back block contents when writing bbt */
DECL|macro|NAND_BBT_SAVECONTENT
mdefine_line|#define NAND_BBT_SAVECONTENT&t;0x00002000
multiline_comment|/* Search good / bad pattern on the first and the second page */
DECL|macro|NAND_BBT_SCAN2NDPAGE
mdefine_line|#define NAND_BBT_SCAN2NDPAGE&t;0x00004000
multiline_comment|/* The maximum number of blocks to scan for a bbt */
DECL|macro|NAND_BBT_SCAN_MAXBLOCKS
mdefine_line|#define NAND_BBT_SCAN_MAXBLOCKS&t;4
r_extern
r_int
id|nand_scan_bbt
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|nand_bbt_descr
op_star
id|bd
)paren
suffix:semicolon
r_extern
r_int
id|nand_update_bbt
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|offs
)paren
suffix:semicolon
r_extern
r_int
id|nand_default_bbt
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_extern
r_int
id|nand_isbad_bbt
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|loff_t
id|offs
comma
r_int
id|allowbbt
)paren
suffix:semicolon
r_extern
r_int
id|nand_erase_nand
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
comma
r_int
id|allowbbt
)paren
suffix:semicolon
multiline_comment|/*&n;* Constants for oob configuration&n;*/
DECL|macro|NAND_SMALL_BADBLOCK_POS
mdefine_line|#define NAND_SMALL_BADBLOCK_POS&t;&t;5
DECL|macro|NAND_LARGE_BADBLOCK_POS
mdefine_line|#define NAND_LARGE_BADBLOCK_POS&t;&t;0
macro_line|#endif /* __LINUX_MTD_NAND_H */
eof
