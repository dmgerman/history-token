macro_line|#ifndef _IDE_H
DECL|macro|_IDE_H
mdefine_line|#define _IDE_H
multiline_comment|/*&n; *  Copyright (C) 1994-2002  Linus Torvalds &amp; authors&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/hdsmart.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/hdreg.h&gt;
multiline_comment|/*&n; * This is the multiple IDE interface driver, as evolved from hd.c.&n; * It supports up to four IDE interfaces, on one or more IRQs (usually 14, 15).&n; * There can be up to two drives per interface, as per the ATA-2 spec.&n; *&n; * Primary i/f:    ide0: major=3;  (hda) minor=0; (hdb) minor=64&n; * Secondary i/f:  ide1: major=22; (hdc) minor=0; (hdd) minor=64&n; * Tertiary i/f:   ide2: major=33; (hde) minor=0; (hdf) minor=64&n; * Quaternary i/f: ide3: major=34; (hdg) minor=0; (hdh) minor=64&n; */
multiline_comment|/******************************************************************************&n; * IDE driver configuration options (play with these as desired):&n; */
DECL|macro|INITIAL_MULT_COUNT
mdefine_line|#define INITIAL_MULT_COUNT&t;0&t;/* off=0; on=2,4,8,16,32, etc.. */
macro_line|#ifndef SUPPORT_SLOW_DATA_PORTS&t;&t;&t;/* 1 to support slow data ports */
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|# define SUPPORT_SLOW_DATA_PORTS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef FANCY_STATUS_DUMPS&t;&t;/* 1 for human-readable drive errors */
DECL|macro|FANCY_STATUS_DUMPS
macro_line|# define FANCY_STATUS_DUMPS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef DISABLE_IRQ_NOSYNC
DECL|macro|DISABLE_IRQ_NOSYNC
macro_line|# define DISABLE_IRQ_NOSYNC&t;0
macro_line|#endif
multiline_comment|/*&n; *  &quot;No user-serviceable parts&quot; beyond this point&n; *****************************************************************************/
multiline_comment|/* ATA/ATAPI Commands pre T13 Spec */
DECL|macro|WIN_NOP
mdefine_line|#define WIN_NOP&t;&t;&t;&t;0x00
DECL|macro|CFA_REQ_EXT_ERROR_CODE
mdefine_line|#define CFA_REQ_EXT_ERROR_CODE&t;&t;0x03 /* CFA Request Extended Error Code */
DECL|macro|WIN_SRST
mdefine_line|#define WIN_SRST&t;&t;&t;0x08 /* ATAPI soft reset command */
DECL|macro|WIN_DEVICE_RESET
mdefine_line|#define WIN_DEVICE_RESET&t;&t;0x08
DECL|macro|WIN_RESTORE
mdefine_line|#define WIN_RESTORE&t;&t;&t;0x10
DECL|macro|WIN_READ
mdefine_line|#define WIN_READ&t;&t;&t;0x20 /* 28-Bit */
DECL|macro|WIN_READ_EXT
mdefine_line|#define WIN_READ_EXT&t;&t;&t;0x24 /* 48-Bit */
DECL|macro|WIN_READDMA_EXT
mdefine_line|#define WIN_READDMA_EXT&t;&t;&t;0x25 /* 48-Bit */
DECL|macro|WIN_READDMA_QUEUED_EXT
mdefine_line|#define WIN_READDMA_QUEUED_EXT&t;&t;0x26 /* 48-Bit */
DECL|macro|WIN_READ_NATIVE_MAX_EXT
mdefine_line|#define WIN_READ_NATIVE_MAX_EXT&t;&t;0x27 /* 48-Bit */
DECL|macro|WIN_MULTREAD_EXT
mdefine_line|#define WIN_MULTREAD_EXT&t;&t;0x29 /* 48-Bit */
DECL|macro|WIN_WRITE
mdefine_line|#define WIN_WRITE&t;&t;&t;0x30 /* 28-Bit */
DECL|macro|WIN_WRITE_EXT
mdefine_line|#define WIN_WRITE_EXT&t;&t;&t;0x34 /* 48-Bit */
DECL|macro|WIN_WRITEDMA_EXT
mdefine_line|#define WIN_WRITEDMA_EXT&t;&t;0x35 /* 48-Bit */
DECL|macro|WIN_WRITEDMA_QUEUED_EXT
mdefine_line|#define WIN_WRITEDMA_QUEUED_EXT&t;&t;0x36 /* 48-Bit */
DECL|macro|WIN_SET_MAX_EXT
mdefine_line|#define WIN_SET_MAX_EXT&t;&t;&t;0x37 /* 48-Bit */
DECL|macro|CFA_WRITE_SECT_WO_ERASE
mdefine_line|#define CFA_WRITE_SECT_WO_ERASE&t;&t;0x38 /* CFA Write Sectors without erase */
DECL|macro|WIN_MULTWRITE_EXT
mdefine_line|#define WIN_MULTWRITE_EXT&t;&t;0x39 /* 48-Bit */
DECL|macro|WIN_WRITE_VERIFY
mdefine_line|#define WIN_WRITE_VERIFY&t;&t;0x3C /* 28-Bit */
DECL|macro|WIN_VERIFY
mdefine_line|#define WIN_VERIFY&t;&t;&t;0x40 /* 28-Bit - Read Verify Sectors */
DECL|macro|WIN_VERIFY_EXT
mdefine_line|#define WIN_VERIFY_EXT&t;&t;&t;0x42 /* 48-Bit */
DECL|macro|WIN_FORMAT
mdefine_line|#define WIN_FORMAT&t;&t;&t;0x50
DECL|macro|WIN_INIT
mdefine_line|#define WIN_INIT&t;&t;&t;0x60
DECL|macro|WIN_SEEK
mdefine_line|#define WIN_SEEK&t;&t;&t;0x70
DECL|macro|CFA_TRANSLATE_SECTOR
mdefine_line|#define CFA_TRANSLATE_SECTOR&t;&t;0x87 /* CFA Translate Sector */
DECL|macro|WIN_DIAGNOSE
mdefine_line|#define WIN_DIAGNOSE&t;&t;&t;0x90
DECL|macro|WIN_SPECIFY
mdefine_line|#define WIN_SPECIFY&t;&t;&t;0x91 /* set drive geometry translation */
DECL|macro|WIN_DOWNLOAD_MICROCODE
mdefine_line|#define WIN_DOWNLOAD_MICROCODE&t;&t;0x92
DECL|macro|WIN_STANDBYNOW2
mdefine_line|#define WIN_STANDBYNOW2&t;&t;&t;0x94
DECL|macro|WIN_SETIDLE2
mdefine_line|#define WIN_SETIDLE2&t;&t;&t;0x97
DECL|macro|WIN_CHECKPOWERMODE2
mdefine_line|#define WIN_CHECKPOWERMODE2&t;&t;0x98
DECL|macro|WIN_SLEEPNOW2
mdefine_line|#define WIN_SLEEPNOW2&t;&t;&t;0x99
DECL|macro|WIN_PACKETCMD
mdefine_line|#define WIN_PACKETCMD&t;&t;&t;0xA0 /* Send a packet command. */
DECL|macro|WIN_PIDENTIFY
mdefine_line|#define WIN_PIDENTIFY&t;&t;&t;0xA1 /* identify ATAPI device&t;*/
DECL|macro|WIN_QUEUED_SERVICE
mdefine_line|#define WIN_QUEUED_SERVICE&t;&t;0xA2
DECL|macro|WIN_SMART
mdefine_line|#define WIN_SMART&t;&t;&t;0xB0 /* self-monitoring and reporting */
DECL|macro|CFA_ERASE_SECTORS
mdefine_line|#define CFA_ERASE_SECTORS&t;&t;0xC0
DECL|macro|WIN_MULTREAD
mdefine_line|#define WIN_MULTREAD&t;&t;&t;0xC4 /* read sectors using multiple mode*/
DECL|macro|WIN_MULTWRITE
mdefine_line|#define WIN_MULTWRITE&t;&t;&t;0xC5 /* write sectors using multiple mode */
DECL|macro|WIN_SETMULT
mdefine_line|#define WIN_SETMULT&t;&t;&t;0xC6 /* enable/disable multiple mode */
DECL|macro|WIN_READDMA_QUEUED
mdefine_line|#define WIN_READDMA_QUEUED&t;&t;0xC7 /* read sectors using Queued DMA transfers */
DECL|macro|WIN_READDMA
mdefine_line|#define WIN_READDMA&t;&t;&t;0xC8 /* read sectors using DMA transfers */
DECL|macro|WIN_WRITEDMA
mdefine_line|#define WIN_WRITEDMA&t;&t;&t;0xCA /* write sectors using DMA transfers */
DECL|macro|WIN_WRITEDMA_QUEUED
mdefine_line|#define WIN_WRITEDMA_QUEUED&t;&t;0xCC /* write sectors using Queued DMA transfers */
DECL|macro|CFA_WRITE_MULTI_WO_ERASE
mdefine_line|#define CFA_WRITE_MULTI_WO_ERASE&t;0xCD /* CFA Write multiple without erase */
DECL|macro|WIN_GETMEDIASTATUS
mdefine_line|#define WIN_GETMEDIASTATUS&t;&t;0xDA
DECL|macro|WIN_DOORLOCK
mdefine_line|#define WIN_DOORLOCK&t;&t;&t;0xDE /* lock door on removable drives */
DECL|macro|WIN_DOORUNLOCK
mdefine_line|#define WIN_DOORUNLOCK&t;&t;&t;0xDF /* unlock door on removable drives */
DECL|macro|WIN_STANDBYNOW1
mdefine_line|#define WIN_STANDBYNOW1&t;&t;&t;0xE0
DECL|macro|WIN_IDLEIMMEDIATE
mdefine_line|#define WIN_IDLEIMMEDIATE&t;&t;0xE1 /* force drive to become &quot;ready&quot; */
DECL|macro|WIN_STANDBY
mdefine_line|#define WIN_STANDBY&t;&t;&t;0xE2 /* Set device in Standby Mode */
DECL|macro|WIN_SETIDLE1
mdefine_line|#define WIN_SETIDLE1&t;&t;&t;0xE3
DECL|macro|WIN_READ_BUFFER
mdefine_line|#define WIN_READ_BUFFER&t;&t;&t;0xE4 /* force read only 1 sector */
DECL|macro|WIN_CHECKPOWERMODE1
mdefine_line|#define WIN_CHECKPOWERMODE1&t;&t;0xE5
DECL|macro|WIN_SLEEPNOW1
mdefine_line|#define WIN_SLEEPNOW1&t;&t;&t;0xE6
DECL|macro|WIN_FLUSH_CACHE
mdefine_line|#define WIN_FLUSH_CACHE&t;&t;&t;0xE7
DECL|macro|WIN_WRITE_BUFFER
mdefine_line|#define WIN_WRITE_BUFFER&t;&t;0xE8 /* force write only 1 sector */
DECL|macro|WIN_FLUSH_CACHE_EXT
mdefine_line|#define WIN_FLUSH_CACHE_EXT&t;&t;0xEA /* 48-Bit */
DECL|macro|WIN_IDENTIFY
mdefine_line|#define WIN_IDENTIFY&t;&t;&t;0xEC /* ask drive to identify itself&t;*/
DECL|macro|WIN_MEDIAEJECT
mdefine_line|#define WIN_MEDIAEJECT&t;&t;&t;0xED
DECL|macro|WIN_IDENTIFY_DMA
mdefine_line|#define WIN_IDENTIFY_DMA&t;&t;0xEE /* same as WIN_IDENTIFY, but DMA */
DECL|macro|WIN_SETFEATURES
mdefine_line|#define WIN_SETFEATURES&t;&t;&t;0xEF /* set special drive features */
DECL|macro|EXABYTE_ENABLE_NEST
mdefine_line|#define EXABYTE_ENABLE_NEST&t;&t;0xF0
DECL|macro|WIN_SECURITY_SET_PASS
mdefine_line|#define WIN_SECURITY_SET_PASS&t;&t;0xF1
DECL|macro|WIN_SECURITY_UNLOCK
mdefine_line|#define WIN_SECURITY_UNLOCK&t;&t;0xF2
DECL|macro|WIN_SECURITY_ERASE_PREPARE
mdefine_line|#define WIN_SECURITY_ERASE_PREPARE&t;0xF3
DECL|macro|WIN_SECURITY_ERASE_UNIT
mdefine_line|#define WIN_SECURITY_ERASE_UNIT&t;&t;0xF4
DECL|macro|WIN_SECURITY_FREEZE_LOCK
mdefine_line|#define WIN_SECURITY_FREEZE_LOCK&t;0xF5
DECL|macro|WIN_SECURITY_DISABLE
mdefine_line|#define WIN_SECURITY_DISABLE&t;&t;0xF6
DECL|macro|WIN_READ_NATIVE_MAX
mdefine_line|#define WIN_READ_NATIVE_MAX&t;&t;0xF8 /* return the native maximum address */
DECL|macro|WIN_SET_MAX
mdefine_line|#define WIN_SET_MAX&t;&t;&t;0xF9
DECL|macro|DISABLE_SEAGATE
mdefine_line|#define DISABLE_SEAGATE&t;&t;&t;0xFB
multiline_comment|/* WIN_SMART sub-commands */
DECL|macro|SMART_READ_VALUES
mdefine_line|#define SMART_READ_VALUES&t;&t;0xD0
DECL|macro|SMART_READ_THRESHOLDS
mdefine_line|#define SMART_READ_THRESHOLDS&t;&t;0xD1
DECL|macro|SMART_AUTOSAVE
mdefine_line|#define SMART_AUTOSAVE&t;&t;&t;0xD2
DECL|macro|SMART_SAVE
mdefine_line|#define SMART_SAVE&t;&t;&t;0xD3
DECL|macro|SMART_IMMEDIATE_OFFLINE
mdefine_line|#define SMART_IMMEDIATE_OFFLINE&t;&t;0xD4
DECL|macro|SMART_READ_LOG_SECTOR
mdefine_line|#define SMART_READ_LOG_SECTOR&t;&t;0xD5
DECL|macro|SMART_WRITE_LOG_SECTOR
mdefine_line|#define SMART_WRITE_LOG_SECTOR&t;&t;0xD6
DECL|macro|SMART_WRITE_THRESHOLDS
mdefine_line|#define SMART_WRITE_THRESHOLDS&t;&t;0xD7
DECL|macro|SMART_ENABLE
mdefine_line|#define SMART_ENABLE&t;&t;&t;0xD8
DECL|macro|SMART_DISABLE
mdefine_line|#define SMART_DISABLE&t;&t;&t;0xD9
DECL|macro|SMART_STATUS
mdefine_line|#define SMART_STATUS&t;&t;&t;0xDA
DECL|macro|SMART_AUTO_OFFLINE
mdefine_line|#define SMART_AUTO_OFFLINE&t;&t;0xDB
multiline_comment|/* Password used in TF4 &amp; TF5 executing SMART commands */
DECL|macro|SMART_LCYL_PASS
mdefine_line|#define SMART_LCYL_PASS&t;&t;&t;0x4F
DECL|macro|SMART_HCYL_PASS
mdefine_line|#define SMART_HCYL_PASS&t;&t;&t;0xC2
multiline_comment|/* WIN_SETFEATURES sub-commands */
DECL|macro|SETFEATURES_EN_WCACHE
mdefine_line|#define SETFEATURES_EN_WCACHE&t;0x02&t;/* Enable write cache */
DECL|macro|SETFEATURES_XFER
mdefine_line|#define SETFEATURES_XFER&t;0x03&t;/* Set transfer mode */
DECL|macro|XFER_UDMA_7
macro_line|#&t;define XFER_UDMA_7&t;0x47&t;/* 0100|0111 */
DECL|macro|XFER_UDMA_6
macro_line|#&t;define XFER_UDMA_6&t;0x46&t;/* 0100|0110 */
DECL|macro|XFER_UDMA_5
macro_line|#&t;define XFER_UDMA_5&t;0x45&t;/* 0100|0101 */
DECL|macro|XFER_UDMA_4
macro_line|#&t;define XFER_UDMA_4&t;0x44&t;/* 0100|0100 */
DECL|macro|XFER_UDMA_3
macro_line|#&t;define XFER_UDMA_3&t;0x43&t;/* 0100|0011 */
DECL|macro|XFER_UDMA_2
macro_line|#&t;define XFER_UDMA_2&t;0x42&t;/* 0100|0010 */
DECL|macro|XFER_UDMA_1
macro_line|#&t;define XFER_UDMA_1&t;0x41&t;/* 0100|0001 */
DECL|macro|XFER_UDMA_0
macro_line|#&t;define XFER_UDMA_0&t;0x40&t;/* 0100|0000 */
DECL|macro|XFER_MW_DMA_2
macro_line|#&t;define XFER_MW_DMA_2&t;0x22&t;/* 0010|0010 */
DECL|macro|XFER_MW_DMA_1
macro_line|#&t;define XFER_MW_DMA_1&t;0x21&t;/* 0010|0001 */
DECL|macro|XFER_MW_DMA_0
macro_line|#&t;define XFER_MW_DMA_0&t;0x20&t;/* 0010|0000 */
DECL|macro|XFER_SW_DMA_2
macro_line|#&t;define XFER_SW_DMA_2&t;0x12&t;/* 0001|0010 */
DECL|macro|XFER_SW_DMA_1
macro_line|#&t;define XFER_SW_DMA_1&t;0x11&t;/* 0001|0001 */
DECL|macro|XFER_SW_DMA_0
macro_line|#&t;define XFER_SW_DMA_0&t;0x10&t;/* 0001|0000 */
DECL|macro|XFER_PIO_4
macro_line|#&t;define XFER_PIO_4&t;0x0C&t;/* 0000|1100 */
DECL|macro|XFER_PIO_3
macro_line|#&t;define XFER_PIO_3&t;0x0B&t;/* 0000|1011 */
DECL|macro|XFER_PIO_2
macro_line|#&t;define XFER_PIO_2&t;0x0A&t;/* 0000|1010 */
DECL|macro|XFER_PIO_1
macro_line|#&t;define XFER_PIO_1&t;0x09&t;/* 0000|1001 */
DECL|macro|XFER_PIO_0
macro_line|#&t;define XFER_PIO_0&t;0x08&t;/* 0000|1000 */
DECL|macro|XFER_PIO_SLOW
macro_line|#&t;define XFER_PIO_SLOW&t;0x00&t;/* 0000|0000 */
DECL|macro|SETFEATURES_DIS_DEFECT
mdefine_line|#define SETFEATURES_DIS_DEFECT&t;0x04&t;/* Disable Defect Management */
DECL|macro|SETFEATURES_EN_APM
mdefine_line|#define SETFEATURES_EN_APM&t;0x05&t;/* Enable advanced power management */
DECL|macro|SETFEATURES_DIS_MSN
mdefine_line|#define SETFEATURES_DIS_MSN&t;0x31&t;/* Disable Media Status Notification */
DECL|macro|SETFEATURES_EN_AAM
mdefine_line|#define SETFEATURES_EN_AAM&t;0x42&t;/* Enable Automatic Acoustic Management */
DECL|macro|SETFEATURES_DIS_RLA
mdefine_line|#define SETFEATURES_DIS_RLA&t;0x55&t;/* Disable read look-ahead feature */
DECL|macro|SETFEATURES_EN_RI
mdefine_line|#define SETFEATURES_EN_RI&t;0x5D&t;/* Enable release interrupt */
DECL|macro|SETFEATURES_EN_SI
mdefine_line|#define SETFEATURES_EN_SI&t;0x5E&t;/* Enable SERVICE interrupt */
DECL|macro|SETFEATURES_DIS_RPOD
mdefine_line|#define SETFEATURES_DIS_RPOD&t;0x66&t;/* Disable reverting to power on defaults */
DECL|macro|SETFEATURES_DIS_WCACHE
mdefine_line|#define SETFEATURES_DIS_WCACHE&t;0x82&t;/* Disable write cache */
DECL|macro|SETFEATURES_EN_DEFECT
mdefine_line|#define SETFEATURES_EN_DEFECT&t;0x84&t;/* Enable Defect Management */
DECL|macro|SETFEATURES_DIS_APM
mdefine_line|#define SETFEATURES_DIS_APM&t;0x85&t;/* Disable advanced power management */
DECL|macro|SETFEATURES_EN_MSN
mdefine_line|#define SETFEATURES_EN_MSN&t;0x95&t;/* Enable Media Status Notification */
DECL|macro|SETFEATURES_EN_RLA
mdefine_line|#define SETFEATURES_EN_RLA&t;0xAA&t;/* Enable read look-ahead feature */
DECL|macro|SETFEATURES_PREFETCH
mdefine_line|#define SETFEATURES_PREFETCH&t;0xAB&t;/* Sets drive prefetch value */
DECL|macro|SETFEATURES_DIS_AAM
mdefine_line|#define SETFEATURES_DIS_AAM&t;0xC2&t;/* Disable Automatic Acoustic Management */
DECL|macro|SETFEATURES_EN_RPOD
mdefine_line|#define SETFEATURES_EN_RPOD&t;0xCC&t;/* Enable reverting to power on defaults */
DECL|macro|SETFEATURES_DIS_RI
mdefine_line|#define SETFEATURES_DIS_RI&t;0xDD&t;/* Disable release interrupt */
DECL|macro|SETFEATURES_DIS_SI
mdefine_line|#define SETFEATURES_DIS_SI&t;0xDE&t;/* Disable SERVICE interrupt */
multiline_comment|/* WIN_SECURITY sub-commands */
DECL|macro|SECURITY_SET_PASSWORD
mdefine_line|#define SECURITY_SET_PASSWORD&t;&t;0xBA
DECL|macro|SECURITY_UNLOCK
mdefine_line|#define SECURITY_UNLOCK&t;&t;&t;0xBB
DECL|macro|SECURITY_ERASE_PREPARE
mdefine_line|#define SECURITY_ERASE_PREPARE&t;&t;0xBC
DECL|macro|SECURITY_ERASE_UNIT
mdefine_line|#define SECURITY_ERASE_UNIT&t;&t;0xBD
DECL|macro|SECURITY_FREEZE_LOCK
mdefine_line|#define SECURITY_FREEZE_LOCK&t;&t;0xBE
DECL|macro|SECURITY_DISABLE_PASSWORD
mdefine_line|#define SECURITY_DISABLE_PASSWORD&t;0xBF
multiline_comment|/* Taskfile related constants.&n; */
DECL|macro|IDE_DRIVE_TASK_INVALID
mdefine_line|#define IDE_DRIVE_TASK_INVALID&t;&t;-1
DECL|macro|IDE_DRIVE_TASK_NO_DATA
mdefine_line|#define IDE_DRIVE_TASK_NO_DATA&t;&t;0
DECL|macro|IDE_DRIVE_TASK_SET_XFER
mdefine_line|#define IDE_DRIVE_TASK_SET_XFER&t;&t;1
DECL|macro|IDE_DRIVE_TASK_IN
mdefine_line|#define IDE_DRIVE_TASK_IN&t;&t;2
DECL|macro|IDE_DRIVE_TASK_OUT
mdefine_line|#define IDE_DRIVE_TASK_OUT&t;&t;3
DECL|macro|IDE_DRIVE_TASK_RAW_WRITE
mdefine_line|#define IDE_DRIVE_TASK_RAW_WRITE&t;4
DECL|struct|hd_drive_task_hdr
r_struct
id|hd_drive_task_hdr
(brace
DECL|member|feature
id|u8
id|feature
suffix:semicolon
DECL|member|sector_count
id|u8
id|sector_count
suffix:semicolon
DECL|member|sector_number
id|u8
id|sector_number
suffix:semicolon
DECL|member|low_cylinder
id|u8
id|low_cylinder
suffix:semicolon
DECL|member|high_cylinder
id|u8
id|high_cylinder
suffix:semicolon
DECL|member|device_head
id|u8
id|device_head
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Define standard taskfile in/out register&n; */
DECL|macro|IDE_TASKFILE_STD_OUT_FLAGS
mdefine_line|#define IDE_TASKFILE_STD_OUT_FLAGS&t;0xFE
DECL|macro|IDE_TASKFILE_STD_IN_FLAGS
mdefine_line|#define IDE_TASKFILE_STD_IN_FLAGS&t;0xFE
DECL|macro|IDE_HOB_STD_OUT_FLAGS
mdefine_line|#define IDE_HOB_STD_OUT_FLAGS&t;&t;0xC0
DECL|macro|IDE_HOB_STD_IN_FLAGS
mdefine_line|#define IDE_HOB_STD_IN_FLAGS&t;&t;0xC0
DECL|macro|TASKFILE_INVALID
mdefine_line|#define TASKFILE_INVALID&t;&t;0x7fff
DECL|macro|TASKFILE_48
mdefine_line|#define TASKFILE_48&t;&t;&t;0x8000
DECL|macro|TASKFILE_NO_DATA
mdefine_line|#define TASKFILE_NO_DATA&t;&t;0x0000
DECL|macro|TASKFILE_IN
mdefine_line|#define TASKFILE_IN&t;&t;&t;0x0001
DECL|macro|TASKFILE_MULTI_IN
mdefine_line|#define TASKFILE_MULTI_IN&t;&t;0x0002
DECL|macro|TASKFILE_OUT
mdefine_line|#define TASKFILE_OUT&t;&t;&t;0x0004
DECL|macro|TASKFILE_MULTI_OUT
mdefine_line|#define TASKFILE_MULTI_OUT&t;&t;0x0008
DECL|macro|TASKFILE_IN_OUT
mdefine_line|#define TASKFILE_IN_OUT&t;&t;&t;0x0010
DECL|macro|TASKFILE_IN_DMA
mdefine_line|#define TASKFILE_IN_DMA&t;&t;&t;0x0020
DECL|macro|TASKFILE_OUT_DMA
mdefine_line|#define TASKFILE_OUT_DMA&t;&t;0x0040
DECL|macro|TASKFILE_IN_DMAQ
mdefine_line|#define TASKFILE_IN_DMAQ&t;&t;0x0080
DECL|macro|TASKFILE_OUT_DMAQ
mdefine_line|#define TASKFILE_OUT_DMAQ&t;&t;0x0100
DECL|macro|TASKFILE_P_IN
mdefine_line|#define TASKFILE_P_IN&t;&t;&t;0x0200
DECL|macro|TASKFILE_P_OUT
mdefine_line|#define TASKFILE_P_OUT&t;&t;&t;0x0400
DECL|macro|TASKFILE_P_IN_DMA
mdefine_line|#define TASKFILE_P_IN_DMA&t;&t;0x0800
DECL|macro|TASKFILE_P_OUT_DMA
mdefine_line|#define TASKFILE_P_OUT_DMA&t;&t;0x1000
DECL|macro|TASKFILE_P_IN_DMAQ
mdefine_line|#define TASKFILE_P_IN_DMAQ&t;&t;0x2000
DECL|macro|TASKFILE_P_OUT_DMAQ
mdefine_line|#define TASKFILE_P_OUT_DMAQ&t;&t;0x4000
multiline_comment|/* bus states */
r_enum
(brace
DECL|enumerator|BUSSTATE_OFF
id|BUSSTATE_OFF
op_assign
l_int|0
comma
DECL|enumerator|BUSSTATE_ON
id|BUSSTATE_ON
comma
DECL|enumerator|BUSSTATE_TRISTATE
id|BUSSTATE_TRISTATE
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure returned by HDIO_GET_IDENTITY, as per ANSI NCITS ATA6 rev.1b spec.&n; *&n; * If you change something here, please remember to update fix_driveid() in&n; * ide/probe.c.&n; */
DECL|struct|hd_driveid
r_struct
id|hd_driveid
(brace
DECL|member|config
id|u16
id|config
suffix:semicolon
multiline_comment|/* lots of obsolete bit flags */
DECL|member|cyls
id|u16
id|cyls
suffix:semicolon
multiline_comment|/* Obsolete, &quot;physical&quot; cyls */
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
multiline_comment|/* reserved (word 2) */
DECL|member|heads
id|u16
id|heads
suffix:semicolon
multiline_comment|/* Obsolete, &quot;physical&quot; heads */
DECL|member|track_bytes
id|u16
id|track_bytes
suffix:semicolon
multiline_comment|/* unformatted bytes per track */
DECL|member|sector_bytes
id|u16
id|sector_bytes
suffix:semicolon
multiline_comment|/* unformatted bytes per sector */
DECL|member|sectors
id|u16
id|sectors
suffix:semicolon
multiline_comment|/* Obsolete, &quot;physical&quot; sectors per track */
DECL|member|vendor0
id|u16
id|vendor0
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|vendor1
id|u16
id|vendor1
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|vendor2
id|u16
id|vendor2
suffix:semicolon
multiline_comment|/* Retired vendor unique */
DECL|member|serial_no
id|u8
id|serial_no
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|buf_type
id|u16
id|buf_type
suffix:semicolon
multiline_comment|/* Retired */
DECL|member|buf_size
id|u16
id|buf_size
suffix:semicolon
multiline_comment|/* Retired, 512 byte increments&n;&t;&t;&t;&t; * 0 = not_specified&n;&t;&t;&t;&t; */
DECL|member|ecc_bytes
id|u16
id|ecc_bytes
suffix:semicolon
multiline_comment|/* for r/w long cmds; 0 = not_specified */
DECL|member|fw_rev
id|u8
id|fw_rev
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|model
r_char
id|model
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|max_multsect
id|u8
id|max_multsect
suffix:semicolon
multiline_comment|/* 0=not_implemented */
DECL|member|vendor3
id|u8
id|vendor3
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|dword_io
id|u16
id|dword_io
suffix:semicolon
multiline_comment|/* 0=not_implemented; 1=implemented */
DECL|member|vendor4
id|u8
id|vendor4
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|capability
id|u8
id|capability
suffix:semicolon
multiline_comment|/* (upper byte of word 49)&n;&t;&t;&t;&t; *  3:&t;IORDYsup&n;&t;&t;&t;&t; *  2:&t;IORDYsw&n;&t;&t;&t;&t; *  1:&t;LBA&n;&t;&t;&t;&t; *  0:&t;DMA&n;&t;&t;&t;&t; */
DECL|member|reserved50
id|u16
id|reserved50
suffix:semicolon
multiline_comment|/* reserved (word 50) */
DECL|member|vendor5
id|u8
id|vendor5
suffix:semicolon
multiline_comment|/* Obsolete, vendor unique */
DECL|member|tPIO
id|u8
id|tPIO
suffix:semicolon
multiline_comment|/* Obsolete, 0=slow, 1=medium, 2=fast */
DECL|member|vendor6
id|u8
id|vendor6
suffix:semicolon
multiline_comment|/* Obsolete, vendor unique */
DECL|member|tDMA
id|u8
id|tDMA
suffix:semicolon
multiline_comment|/* Obsolete, 0=slow, 1=medium, 2=fast */
DECL|member|field_valid
id|u16
id|field_valid
suffix:semicolon
multiline_comment|/* (word 53)&n;&t;&t;&t;&t; *  2:&t;ultra_ok&t;word  88&n;&t;&t;&t;&t; *  1:&t;eide_ok&t;&t;words 64-70&n;&t;&t;&t;&t; *  0:&t;cur_ok&t;&t;words 54-58&n;&t;&t;&t;&t; */
DECL|member|cur_cyls
id|u16
id|cur_cyls
suffix:semicolon
multiline_comment|/* Obsolete, logical cylinders */
DECL|member|cur_heads
id|u16
id|cur_heads
suffix:semicolon
multiline_comment|/* Obsolete, l heads */
DECL|member|cur_sectors
id|u16
id|cur_sectors
suffix:semicolon
multiline_comment|/* Obsolete, l sectors per track */
DECL|member|cur_capacity0
id|u16
id|cur_capacity0
suffix:semicolon
multiline_comment|/* Obsolete, l total sectors on drive */
DECL|member|cur_capacity1
id|u16
id|cur_capacity1
suffix:semicolon
multiline_comment|/* Obsolete, (2 words, misaligned int)     */
DECL|member|multsect
id|u8
id|multsect
suffix:semicolon
multiline_comment|/* current multiple sector count */
DECL|member|multsect_valid
id|u8
id|multsect_valid
suffix:semicolon
multiline_comment|/* when (bit0==1) multsect is ok */
DECL|member|lba_capacity
id|u32
id|lba_capacity
suffix:semicolon
multiline_comment|/* Obsolete, total number of sectors */
DECL|member|dma_1word
id|u16
id|dma_1word
suffix:semicolon
multiline_comment|/* Obsolete, single-word dma info */
DECL|member|dma_mword
id|u16
id|dma_mword
suffix:semicolon
multiline_comment|/* multiple-word dma info */
DECL|member|eide_pio_modes
id|u16
id|eide_pio_modes
suffix:semicolon
multiline_comment|/* bits 0:mode3 1:mode4 */
DECL|member|eide_dma_min
id|u16
id|eide_dma_min
suffix:semicolon
multiline_comment|/* min mword dma cycle time (ns) */
DECL|member|eide_dma_time
id|u16
id|eide_dma_time
suffix:semicolon
multiline_comment|/* recommended mword dma cycle time (ns) */
DECL|member|eide_pio
id|u16
id|eide_pio
suffix:semicolon
multiline_comment|/* min cycle time (ns), no IORDY  */
DECL|member|eide_pio_iordy
id|u16
id|eide_pio_iordy
suffix:semicolon
multiline_comment|/* min cycle time (ns), with IORDY */
DECL|member|words69_70
id|u16
id|words69_70
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* reserved words 69-70&n;&t;&t;&t;&t; * future command overlap and queuing&n;&t;&t;&t;&t; */
multiline_comment|/* HDIO_GET_IDENTITY currently returns only words 0 through 70 */
DECL|member|words71_74
id|u16
id|words71_74
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved words 71-74&n;&t;&t;&t;&t; * for IDENTIFY PACKET DEVICE command&n;&t;&t;&t;&t; */
DECL|member|queue_depth
id|u16
id|queue_depth
suffix:semicolon
multiline_comment|/* (word 75)&n;&t;&t;&t;&t; * 15:5&t;reserved&n;&t;&t;&t;&t; *  4:0&t;Maximum queue depth -1&n;&t;&t;&t;&t; */
DECL|member|words76_79
id|u16
id|words76_79
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved words 76-79 */
DECL|member|major_rev_num
id|u16
id|major_rev_num
suffix:semicolon
multiline_comment|/* (word 80) */
DECL|member|minor_rev_num
id|u16
id|minor_rev_num
suffix:semicolon
multiline_comment|/* (word 81) */
DECL|member|command_set_1
id|u16
id|command_set_1
suffix:semicolon
multiline_comment|/* (word 82) supported&n;&t;&t;&t;&t; * 15:&t;Obsolete&n;&t;&t;&t;&t; * 14:&t;NOP command&n;&t;&t;&t;&t; * 13:&t;READ_BUFFER&n;&t;&t;&t;&t; * 12:&t;WRITE_BUFFER&n;&t;&t;&t;&t; * 11:&t;Obsolete&n;&t;&t;&t;&t; * 10:&t;Host Protected Area&n;&t;&t;&t;&t; *  9:&t;DEVICE Reset&n;&t;&t;&t;&t; *  8:&t;SERVICE Interrupt&n;&t;&t;&t;&t; *  7:&t;Release Interrupt&n;&t;&t;&t;&t; *  6:&t;look-ahead&n;&t;&t;&t;&t; *  5:&t;write cache&n;&t;&t;&t;&t; *  4:&t;PACKET Command&n;&t;&t;&t;&t; *  3:&t;Power Management Feature Set&n;&t;&t;&t;&t; *  2:&t;Removable Feature Set&n;&t;&t;&t;&t; *  1:&t;Security Feature Set&n;&t;&t;&t;&t; *  0:&t;SMART Feature Set&n;&t;&t;&t;&t; */
DECL|member|command_set_2
id|u16
id|command_set_2
suffix:semicolon
multiline_comment|/* (word 83)&n;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t; * 13:&t;FLUSH CACHE EXT&n;&t;&t;&t;&t; * 12:&t;FLUSH CACHE&n;&t;&t;&t;&t; * 11:&t;Device Configuration Overlay&n;&t;&t;&t;&t; * 10:&t;48-bit Address Feature Set&n;&t;&t;&t;&t; *  9:&t;Automatic Acoustic Management&n;&t;&t;&t;&t; *  8:&t;SET MAX security&n;&t;&t;&t;&t; *  7:&t;reserved 1407DT PARTIES&n;&t;&t;&t;&t; *  6:&t;SetF sub-command Power-Up&n;&t;&t;&t;&t; *  5:&t;Power-Up in Standby Feature Set&n;&t;&t;&t;&t; *  4:&t;Removable Media Notification&n;&t;&t;&t;&t; *  3:&t;APM Feature Set&n;&t;&t;&t;&t; *  2:&t;CFA Feature Set&n;&t;&t;&t;&t; *  1:&t;READ/WRITE DMA QUEUED&n;&t;&t;&t;&t; *  0:&t;Download MicroCode&n;&t;&t;&t;&t; */
DECL|member|cfsse
id|u16
id|cfsse
suffix:semicolon
multiline_comment|/* (word 84)&n;&t;&t;&t;&t; * cmd set-feature supported extensions&n;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t; * 13:3&t;reserved&n;&t;&t;&t;&t; *  2:&t;Media Serial Number Valid&n;&t;&t;&t;&t; *  1:&t;SMART selt-test supported&n;&t;&t;&t;&t; *  0:&t;SMART error logging&n;&t;&t;&t;&t; */
DECL|member|cfs_enable_1
id|u16
id|cfs_enable_1
suffix:semicolon
multiline_comment|/* (word 85)&n;&t;&t;&t;&t; * command set-feature enabled&n;&t;&t;&t;&t; * 15:&t;Obsolete&n;&t;&t;&t;&t; * 14:&t;NOP command&n;&t;&t;&t;&t; * 13:&t;READ_BUFFER&n;&t;&t;&t;&t; * 12:&t;WRITE_BUFFER&n;&t;&t;&t;&t; * 11:&t;Obsolete&n;&t;&t;&t;&t; * 10:&t;Host Protected Area&n;&t;&t;&t;&t; *  9:&t;DEVICE Reset&n;&t;&t;&t;&t; *  8:&t;SERVICE Interrupt&n;&t;&t;&t;&t; *  7:&t;Release Interrupt&n;&t;&t;&t;&t; *  6:&t;look-ahead&n;&t;&t;&t;&t; *  5:&t;write cache&n;&t;&t;&t;&t; *  4:&t;PACKET Command&n;&t;&t;&t;&t; *  3:&t;Power Management Feature Set&n;&t;&t;&t;&t; *  2:&t;Removable Feature Set&n;&t;&t;&t;&t; *  1:&t;Security Feature Set&n;&t;&t;&t;&t; *  0:&t;SMART Feature Set&n;&t;&t;&t;&t; */
DECL|member|cfs_enable_2
id|u16
id|cfs_enable_2
suffix:semicolon
multiline_comment|/* (word 86)&n;&t;&t;&t;&t; * command set-feature enabled&n;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t; * 13:&t;FLUSH CACHE EXT&n;&t;&t;&t;&t; * 12:&t;FLUSH CACHE&n;&t;&t;&t;&t; * 11:&t;Device Configuration Overlay&n;&t;&t;&t;&t; * 10:&t;48-bit Address Feature Set&n;&t;&t;&t;&t; *  9:&t;Automatic Acoustic Management&n;&t;&t;&t;&t; *  8:&t;SET MAX security&n;&t;&t;&t;&t; *  7:&t;reserved 1407DT PARTIES&n;&t;&t;&t;&t; *  6:&t;SetF sub-command Power-Up&n;&t;&t;&t;&t; *  5:&t;Power-Up in Standby Feature Set&n;&t;&t;&t;&t; *  4:&t;Removable Media Notification&n;&t;&t;&t;&t; *  3:&t;APM Feature Set&n;&t;&t;&t;&t; *  2:&t;CFA Feature Set&n;&t;&t;&t;&t; *  1:&t;READ/WRITE DMA QUEUED&n;&t;&t;&t;&t; *  0:&t;Download MicroCode&n;&t;&t;&t;&t; */
DECL|member|csf_default
id|u16
id|csf_default
suffix:semicolon
multiline_comment|/* (word 87)&n;&t;&t;&t;&t; * command set-feature default&n;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t; * 13:3&t;reserved&n;&t;&t;&t;&t; *  2:&t;Media Serial Number Valid&n;&t;&t;&t;&t; *  1:&t;SMART selt-test supported&n;&t;&t;&t;&t; *  0:&t;SMART error logging&n;&t;&t;&t;&t; */
DECL|member|dma_ultra
id|u16
id|dma_ultra
suffix:semicolon
multiline_comment|/* (word 88) */
DECL|member|word89
id|u16
id|word89
suffix:semicolon
multiline_comment|/* reserved (word 89) */
DECL|member|word90
id|u16
id|word90
suffix:semicolon
multiline_comment|/* reserved (word 90) */
DECL|member|CurAPMvalues
id|u16
id|CurAPMvalues
suffix:semicolon
multiline_comment|/* current APM values */
DECL|member|word92
id|u16
id|word92
suffix:semicolon
multiline_comment|/* reserved (word 92) */
DECL|member|hw_config
id|u16
id|hw_config
suffix:semicolon
multiline_comment|/* hardware config (word 93)&n;&t;&t;&t;&t; * 15:&n;&t;&t;&t;&t; * 14:&n;&t;&t;&t;&t; * 13:&n;&t;&t;&t;&t; * 12:&n;&t;&t;&t;&t; * 11:&n;&t;&t;&t;&t; * 10:&n;&t;&t;&t;&t; *  9:&n;&t;&t;&t;&t; *  8:&n;&t;&t;&t;&t; *  7:&n;&t;&t;&t;&t; *  6:&n;&t;&t;&t;&t; *  5:&n;&t;&t;&t;&t; *  4:&n;&t;&t;&t;&t; *  3:&n;&t;&t;&t;&t; *  2:&n;&t;&t;&t;&t; *  1:&n;&t;&t;&t;&t; *  0:&n;&t;&t;&t;&t; */
DECL|member|acoustic
id|u16
id|acoustic
suffix:semicolon
multiline_comment|/* (word 94)&n;&t;&t;&t;&t; * 15:8&t;Vendor&squot;s recommended value&n;&t;&t;&t;&t; *  7:0&t;current value&n;&t;&t;&t;&t; */
DECL|member|words95_99
id|u16
id|words95_99
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved words 95-99 */
DECL|member|lba_capacity_2
id|u64
id|lba_capacity_2
suffix:semicolon
multiline_comment|/* 48-bit total number of sectors */
DECL|member|words104_125
id|u16
id|words104_125
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* reserved words 104-125 */
DECL|member|last_lun
id|u16
id|last_lun
suffix:semicolon
multiline_comment|/* (word 126) */
DECL|member|word127
id|u16
id|word127
suffix:semicolon
multiline_comment|/* (word 127) Feature Set&n;&t;&t;&t;&t; * Removable Media Notification&n;&t;&t;&t;&t; * 15:2&t;reserved&n;&t;&t;&t;&t; *  1:0&t;00 = not supported&n;&t;&t;&t;&t; *&t;01 = supported&n;&t;&t;&t;&t; *&t;10 = reserved&n;&t;&t;&t;&t; *&t;11 = reserved&n;&t;&t;&t;&t; */
DECL|member|dlf
id|u16
id|dlf
suffix:semicolon
multiline_comment|/* (word 128)&n;&t;&t;&t;&t; * device lock function&n;&t;&t;&t;&t; * 15:9&t;reserved&n;&t;&t;&t;&t; *  8&t;security level 1:max 0:high&n;&t;&t;&t;&t; *  7:6&t;reserved&n;&t;&t;&t;&t; *  5&t;enhanced erase&n;&t;&t;&t;&t; *  4&t;expire&n;&t;&t;&t;&t; *  3&t;frozen&n;&t;&t;&t;&t; *  2&t;locked&n;&t;&t;&t;&t; *  1&t;en/disabled&n;&t;&t;&t;&t; *  0&t;capability&n;&t;&t;&t;&t; */
DECL|member|csfo
id|u16
id|csfo
suffix:semicolon
multiline_comment|/* (word 129)&n;&t;&t;&t;&t; * current set features options&n;&t;&t;&t;&t; * 15:4&t;reserved&n;&t;&t;&t;&t; *  3:&t;auto reassign&n;&t;&t;&t;&t; *  2:&t;reverting&n;&t;&t;&t;&t; *  1:&t;read-look-ahead&n;&t;&t;&t;&t; *  0:&t;write cache&n;&t;&t;&t;&t; */
DECL|member|words130_155
id|u16
id|words130_155
(braket
l_int|26
)braket
suffix:semicolon
multiline_comment|/* reserved vendor words 130-155 */
DECL|member|word156
id|u16
id|word156
suffix:semicolon
multiline_comment|/* reserved vendor word 156 */
DECL|member|words157_159
id|u16
id|words157_159
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved vendor words 157-159 */
DECL|member|cfa_power
id|u16
id|cfa_power
suffix:semicolon
multiline_comment|/* (word 160) CFA Power Mode&n;&t;&t;&t;&t; * 15 word 160 supported&n;&t;&t;&t;&t; * 14 reserved&n;&t;&t;&t;&t; * 13&n;&t;&t;&t;&t; * 12&n;&t;&t;&t;&t; * 11:0&n;&t;&t;&t;&t; */
DECL|member|words161_175
id|u16
id|words161_175
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Reserved for CFA */
DECL|member|words176_205
id|u16
id|words176_205
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* Current Media Serial Number */
DECL|member|words206_254
id|u16
id|words206_254
(braket
l_int|48
)braket
suffix:semicolon
multiline_comment|/* reserved words 206-254 */
DECL|member|integrity_word
id|u16
id|integrity_word
suffix:semicolon
multiline_comment|/* (word 255)&n;&t;&t;&t;&t; * 15:8 Checksum&n;&t;&t;&t;&t; *  7:0 Signature&n;&t;&t;&t;&t; */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|IDE_NICE_DSC_OVERLAP
mdefine_line|#define IDE_NICE_DSC_OVERLAP&t;(0)&t;/* per the DSC overlap protocol */
multiline_comment|/*&n; * Probably not wise to fiddle with these&n; */
DECL|macro|ERROR_MAX
mdefine_line|#define ERROR_MAX&t;8&t;/* Max read/write errors per sector */
DECL|macro|ERROR_RESET
mdefine_line|#define ERROR_RESET&t;3&t;/* Reset controller every 4th retry */
multiline_comment|/*&n; * State flags.&n; */
DECL|macro|DMA_PIO_RETRY
mdefine_line|#define DMA_PIO_RETRY&t;1&t;/* retrying in PIO */
multiline_comment|/*&n; * Definitions for accessing IDE controller registers.&n; */
r_enum
(brace
DECL|enumerator|IDE_DATA_OFFSET
id|IDE_DATA_OFFSET
op_assign
l_int|0
comma
DECL|enumerator|IDE_ERROR_OFFSET
id|IDE_ERROR_OFFSET
op_assign
l_int|1
comma
DECL|enumerator|IDE_FEATURE_OFFSET
id|IDE_FEATURE_OFFSET
op_assign
l_int|1
comma
DECL|enumerator|IDE_NSECTOR_OFFSET
id|IDE_NSECTOR_OFFSET
op_assign
l_int|2
comma
DECL|enumerator|IDE_SECTOR_OFFSET
id|IDE_SECTOR_OFFSET
op_assign
l_int|3
comma
DECL|enumerator|IDE_LCYL_OFFSET
id|IDE_LCYL_OFFSET
op_assign
l_int|4
comma
DECL|enumerator|IDE_HCYL_OFFSET
id|IDE_HCYL_OFFSET
op_assign
l_int|5
comma
DECL|enumerator|IDE_SELECT_OFFSET
id|IDE_SELECT_OFFSET
op_assign
l_int|6
comma
DECL|enumerator|IDE_STATUS_OFFSET
id|IDE_STATUS_OFFSET
op_assign
l_int|7
comma
DECL|enumerator|IDE_COMMAND_OFFSET
id|IDE_COMMAND_OFFSET
op_assign
l_int|7
comma
DECL|enumerator|IDE_CONTROL_OFFSET
id|IDE_CONTROL_OFFSET
op_assign
l_int|8
comma
DECL|enumerator|IDE_ALTSTATUS_OFFSET
id|IDE_ALTSTATUS_OFFSET
op_assign
l_int|8
comma
DECL|enumerator|IDE_IRQ_OFFSET
id|IDE_IRQ_OFFSET
op_assign
l_int|9
comma
DECL|enumerator|IDE_NR_PORTS
id|IDE_NR_PORTS
op_assign
l_int|10
)brace
suffix:semicolon
DECL|macro|IDE_DATA_REG
mdefine_line|#define IDE_DATA_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_DATA_OFFSET])
DECL|macro|IDE_ERROR_REG
mdefine_line|#define IDE_ERROR_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_ERROR_OFFSET])
DECL|macro|IDE_NSECTOR_REG
mdefine_line|#define IDE_NSECTOR_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_NSECTOR_OFFSET])
DECL|macro|IDE_SECTOR_REG
mdefine_line|#define IDE_SECTOR_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_SECTOR_OFFSET])
DECL|macro|IDE_LCYL_REG
mdefine_line|#define IDE_LCYL_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_LCYL_OFFSET])
DECL|macro|IDE_HCYL_REG
mdefine_line|#define IDE_HCYL_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_HCYL_OFFSET])
DECL|macro|IDE_SELECT_REG
mdefine_line|#define IDE_SELECT_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_SELECT_OFFSET])
DECL|macro|IDE_COMMAND_REG
mdefine_line|#define IDE_COMMAND_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_STATUS_OFFSET])
DECL|macro|IDE_IRQ_REG
mdefine_line|#define IDE_IRQ_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_IRQ_OFFSET])
DECL|macro|IDE_FEATURE_REG
mdefine_line|#define IDE_FEATURE_REG&t;&t;IDE_ERROR_REG
DECL|macro|IDE_IREASON_REG
mdefine_line|#define IDE_IREASON_REG&t;&t;IDE_NSECTOR_REG
DECL|macro|IDE_BCOUNTL_REG
mdefine_line|#define IDE_BCOUNTL_REG&t;&t;IDE_LCYL_REG
DECL|macro|IDE_BCOUNTH_REG
mdefine_line|#define IDE_BCOUNTH_REG&t;&t;IDE_HCYL_REG
DECL|macro|GET_ERR
mdefine_line|#define GET_ERR()&t;&t;IN_BYTE(IDE_ERROR_REG)
DECL|macro|GET_ALTSTAT
mdefine_line|#define GET_ALTSTAT()&t;&t;IN_BYTE(drive-&gt;channel-&gt;io_ports[IDE_CONTROL_OFFSET])
DECL|macro|GET_FEAT
mdefine_line|#define GET_FEAT()&t;&t;IN_BYTE(IDE_NSECTOR_REG)
multiline_comment|/* Bits of HD_STATUS */
DECL|macro|ERR_STAT
mdefine_line|#define ERR_STAT&t;&t;0x01
DECL|macro|INDEX_STAT
mdefine_line|#define INDEX_STAT&t;&t;0x02
DECL|macro|ECC_STAT
mdefine_line|#define ECC_STAT&t;&t;0x04&t;/* Corrected error */
DECL|macro|DRQ_STAT
mdefine_line|#define DRQ_STAT&t;&t;0x08
DECL|macro|SEEK_STAT
mdefine_line|#define SEEK_STAT&t;&t;0x10
DECL|macro|SERVICE_STAT
mdefine_line|#define SERVICE_STAT&t;&t;SEEK_STAT
DECL|macro|WRERR_STAT
mdefine_line|#define WRERR_STAT&t;&t;0x20
DECL|macro|READY_STAT
mdefine_line|#define READY_STAT&t;&t;0x40
DECL|macro|BUSY_STAT
mdefine_line|#define BUSY_STAT&t;&t;0x80
multiline_comment|/* Bits for HD_ERROR */
DECL|macro|MARK_ERR
mdefine_line|#define MARK_ERR&t;&t;0x01&t;/* Bad address mark */
DECL|macro|TRK0_ERR
mdefine_line|#define TRK0_ERR&t;&t;0x02&t;/* couldn&squot;t find track 0 */
DECL|macro|ABRT_ERR
mdefine_line|#define ABRT_ERR&t;&t;0x04&t;/* Command aborted */
DECL|macro|MCR_ERR
mdefine_line|#define MCR_ERR&t;&t;&t;0x08&t;/* media change request */
DECL|macro|ID_ERR
mdefine_line|#define ID_ERR&t;&t;&t;0x10&t;/* ID field not found */
DECL|macro|MC_ERR
mdefine_line|#define MC_ERR&t;&t;&t;0x20&t;/* media changed */
DECL|macro|ECC_ERR
mdefine_line|#define ECC_ERR&t;&t;&t;0x40&t;/* Uncorrectable ECC error */
DECL|macro|BBD_ERR
mdefine_line|#define BBD_ERR&t;&t;&t;0x80&t;/* pre-EIDE meaning:  block marked bad */
DECL|macro|ICRC_ERR
mdefine_line|#define ICRC_ERR&t;&t;0x80&t;/* new meaning:  CRC error during transfer */
multiline_comment|/*&n; * sector count bits&n; */
DECL|macro|NSEC_CD
mdefine_line|#define NSEC_CD&t;&t;&t;0x01
DECL|macro|NSEC_IO
mdefine_line|#define NSEC_IO&t;&t;&t;0x02
DECL|macro|NSEC_REL
mdefine_line|#define NSEC_REL&t;&t;0x04
DECL|macro|BAD_R_STAT
mdefine_line|#define BAD_R_STAT&t;&t;(BUSY_STAT   | ERR_STAT)
DECL|macro|BAD_W_STAT
mdefine_line|#define BAD_W_STAT&t;&t;(BAD_R_STAT  | WRERR_STAT)
DECL|macro|BAD_STAT
mdefine_line|#define BAD_STAT&t;&t;(BAD_R_STAT  | DRQ_STAT)
DECL|macro|DRIVE_READY
mdefine_line|#define DRIVE_READY&t;&t;(READY_STAT  | SEEK_STAT)
DECL|macro|DATA_READY
mdefine_line|#define DATA_READY&t;&t;(DRQ_STAT)
multiline_comment|/*&n; * Our Physical Region Descriptor (PRD) table should be large enough&n; * to handle the biggest I/O request we are likely to see.  Since requests&n; * can have no more than 256 sectors, and since the typical blocksize is&n; * two or more sectors, we could get by with a limit of 128 entries here for&n; * the usual worst case.  Most requests seem to include some contiguous blocks,&n; * further reducing the number of table entries required.&n; *&n; * As it turns out though, we must allocate a full 4KB page for this,&n; * so the two PRD tables (ide0 &amp; ide1) will each get half of that,&n; * allowing each to have about 256 entries (8 bytes each) from this.&n; */
DECL|macro|PRD_BYTES
mdefine_line|#define PRD_BYTES&t;8
DECL|macro|PRD_ENTRIES
mdefine_line|#define PRD_ENTRIES&t;(PAGE_SIZE / (2 * PRD_BYTES))
multiline_comment|/*&n; * Some more useful definitions&n; */
DECL|macro|IDE_MAJOR_NAME
mdefine_line|#define IDE_MAJOR_NAME&t;&quot;hd&quot;&t;/* the same for all i/f; see also genhd.c */
DECL|macro|MAJOR_NAME
mdefine_line|#define MAJOR_NAME&t;IDE_MAJOR_NAME
DECL|macro|PARTN_BITS
mdefine_line|#define PARTN_BITS&t;6&t;/* number of minor dev bits for partitions */
DECL|macro|PARTN_MASK
mdefine_line|#define PARTN_MASK&t;((1&lt;&lt;PARTN_BITS)-1)&t;/* a useful bit mask */
DECL|macro|MAX_DRIVES
mdefine_line|#define MAX_DRIVES&t;2&t;/* per interface; 2 assumed by lots of code */
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE&t;512
DECL|macro|SECTOR_WORDS
mdefine_line|#define SECTOR_WORDS&t;(SECTOR_SIZE / 4)&t;/* number of 32bit words per sector */
multiline_comment|/*&n; * Timeouts for various operations:&n; */
DECL|macro|WAIT_DRQ
mdefine_line|#define WAIT_DRQ&t;(5*HZ/100)&t;/* 50msec - spec allows up to 20ms */
DECL|macro|WAIT_READY
mdefine_line|#define WAIT_READY&t;(5*HZ)&t;&t;/* 5sec   - some laptops are very slow */
DECL|macro|WAIT_PIDENTIFY
mdefine_line|#define WAIT_PIDENTIFY&t;(10*HZ)&t;&t;/* 10sec  - should be less than 3ms (?), if all ATAPI CD is closed at boot */
DECL|macro|WAIT_WORSTCASE
mdefine_line|#define WAIT_WORSTCASE&t;(30*HZ)&t;&t;/* 30sec  - worst case when spinning up */
DECL|macro|WAIT_CMD
mdefine_line|#define WAIT_CMD&t;(10*HZ)&t;&t;/* 10sec  - maximum wait for an IRQ to happen */
DECL|macro|WAIT_MIN_SLEEP
mdefine_line|#define WAIT_MIN_SLEEP&t;(2*HZ/100)&t;/* 20msec - minimum sleep time */
multiline_comment|/*&n; * Check for an interrupt and acknowledge the interrupt status&n; */
r_struct
id|ata_channel
suffix:semicolon
DECL|typedef|ide_ack_intr_t
r_typedef
r_int
(paren
id|ide_ack_intr_t
)paren
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
macro_line|#ifndef NO_DMA
DECL|macro|NO_DMA
macro_line|# define NO_DMA  255
macro_line|#endif
multiline_comment|/*&n; * This is used to keep track of the specific hardware chipset used by each IDE&n; * interface, if known. Please note that we don&squot;t discriminate between&n; * different PCI host chips here.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ide_unknown
id|ide_unknown
comma
DECL|enumerator|ide_generic
id|ide_generic
comma
DECL|enumerator|ide_pci
id|ide_pci
comma
DECL|enumerator|ide_cmd640
id|ide_cmd640
comma
DECL|enumerator|ide_dtc2278
id|ide_dtc2278
comma
DECL|enumerator|ide_ali14xx
id|ide_ali14xx
comma
DECL|enumerator|ide_qd65xx
id|ide_qd65xx
comma
DECL|enumerator|ide_umc8672
id|ide_umc8672
comma
DECL|enumerator|ide_ht6560b
id|ide_ht6560b
comma
DECL|enumerator|ide_pdc4030
id|ide_pdc4030
comma
DECL|enumerator|ide_rz1000
id|ide_rz1000
comma
DECL|enumerator|ide_trm290
id|ide_trm290
comma
DECL|enumerator|ide_cmd646
id|ide_cmd646
comma
DECL|enumerator|ide_cy82c693
id|ide_cy82c693
comma
DECL|enumerator|ide_pmac
id|ide_pmac
comma
DECL|enumerator|ide_etrax100
id|ide_etrax100
comma
DECL|enumerator|ide_acorn
id|ide_acorn
DECL|typedef|hwif_chipset_t
)brace
id|hwif_chipset_t
suffix:semicolon
DECL|macro|IDE_CHIPSET_PCI_MASK
mdefine_line|#define IDE_CHIPSET_PCI_MASK    &bslash;&n;    ((1&lt;&lt;ide_pci)|(1&lt;&lt;ide_cmd646)|(1&lt;&lt;ide_ali14xx))
DECL|macro|IDE_CHIPSET_IS_PCI
mdefine_line|#define IDE_CHIPSET_IS_PCI(c)   ((IDE_CHIPSET_PCI_MASK &gt;&gt; (c)) &amp; 1)
multiline_comment|/*&n; * Structure to hold all information about the location of this port&n; */
DECL|struct|hw_regs_s
r_typedef
r_struct
id|hw_regs_s
(brace
DECL|member|io_ports
id|ide_ioreg_t
id|io_ports
(braket
id|IDE_NR_PORTS
)braket
suffix:semicolon
multiline_comment|/* task file registers */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* our irq number */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* our dma entry */
DECL|member|ack_intr
r_int
(paren
op_star
id|ack_intr
)paren
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
multiline_comment|/* acknowledge interrupt */
DECL|member|chipset
id|hwif_chipset_t
id|chipset
suffix:semicolon
DECL|typedef|hw_regs_t
)brace
id|hw_regs_t
suffix:semicolon
multiline_comment|/*&n; * Set up hw_regs_t structure before calling ide_register_hw (optional)&n; */
r_extern
r_void
id|ide_setup_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|offsets
comma
id|ide_ioreg_t
id|ctrl
comma
id|ide_ioreg_t
id|intr
comma
r_int
(paren
op_star
id|ack_intr
)paren
(paren
r_struct
id|ata_channel
op_star
)paren
comma
r_int
id|irq
)paren
suffix:semicolon
macro_line|#include &lt;asm/ide.h&gt;
multiline_comment|/* Currently only m68k, apus and m8xx need it */
macro_line|#ifdef ATA_ARCH_ACK_INTR
r_extern
r_int
id|ide_irq_lock
suffix:semicolon
DECL|macro|ide_ack_intr
macro_line|# define ide_ack_intr(hwif) (hwif-&gt;hw.ack_intr ? hwif-&gt;hw.ack_intr(hwif) : 1)
macro_line|#else
DECL|macro|ide_ack_intr
macro_line|# define ide_ack_intr(hwif) (1)
macro_line|#endif
multiline_comment|/* Currently only Atari needs it */
macro_line|#ifndef ATA_ARCH_LOCK
DECL|macro|ide_release_lock
macro_line|# define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
macro_line|# define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
macro_line|#endif
multiline_comment|/*&n; * If the arch-dependant ide.h did not declare/define any OUT_BYTE or IN_BYTE&n; * functions, we make some defaults here. The only architecture currently&n; * needing this is Cris.&n; */
macro_line|#ifndef HAVE_ARCH_IN_OUT
DECL|macro|OUT_BYTE
macro_line|# define OUT_BYTE(b,p)&t;&t;outb((b),(p))
DECL|macro|OUT_WORD
macro_line|# define OUT_WORD(w,p)&t;&t;outw((w),(p))
DECL|macro|IN_BYTE
macro_line|# define IN_BYTE(p)&t;&t;(u8)inb(p)
DECL|macro|IN_WORD
macro_line|# define IN_WORD(p)&t;&t;(u16)inw(p)
macro_line|#endif
multiline_comment|/*&n; * Device types - the nomenclature is analogous to SCSI code.&n; */
DECL|macro|ATA_DISK
mdefine_line|#define ATA_DISK        0x20
DECL|macro|ATA_TAPE
mdefine_line|#define ATA_TAPE        0x01
DECL|macro|ATA_ROM
mdefine_line|#define ATA_ROM         0x05&t;/* CD-ROM */
DECL|macro|ATA_MOD
mdefine_line|#define ATA_MOD&t;&t;0x07    /* optical */
DECL|macro|ATA_FLOPPY
mdefine_line|#define ATA_FLOPPY&t;0x00
DECL|macro|ATA_SCSI
mdefine_line|#define ATA_SCSI&t;0x21
DECL|macro|ATA_NO_LUN
mdefine_line|#define ATA_NO_LUN      0x7f
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number: 0/1 */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
multiline_comment|/*&n; * ATA/ATAPI device structure :&n; */
DECL|struct|ata_device
r_struct
id|ata_device
(brace
DECL|member|channel
r_struct
id|ata_channel
op_star
id|channel
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* device name */
DECL|member|usage
r_int
r_int
id|usage
suffix:semicolon
multiline_comment|/* current &quot;open()&quot; count for drive */
DECL|member|type
r_char
id|type
suffix:semicolon
multiline_comment|/* distingiush different devices: disk, cdrom, tape, floppy, ... */
DECL|member|queue
id|request_queue_t
id|queue
suffix:semicolon
multiline_comment|/* per device request queue */
DECL|member|rq
r_struct
id|request
op_star
id|rq
suffix:semicolon
multiline_comment|/* current request */
DECL|member|retry_pio
id|u8
id|retry_pio
suffix:semicolon
multiline_comment|/* retrying dma capable host in pio */
DECL|member|state
id|u8
id|state
suffix:semicolon
multiline_comment|/* retry state */
DECL|member|using_dma
r_int
id|using_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disk is using dma for read/write */
DECL|member|using_tcq
r_int
id|using_tcq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disk is using queueing */
DECL|member|dsc_overlap
r_int
id|dsc_overlap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: DSC overlap */
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* currently doing revalidate_disk() */
DECL|member|blocked
r_int
id|blocked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1=powermanagment told us not to do anything, so sleep nicely */
DECL|member|present
r_int
id|present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive is physically present */
DECL|member|noprobe
r_int
id|noprobe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* from:  hdx=noprobe */
DECL|member|removable
r_int
id|removable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 if need to do check_media_change */
DECL|member|forced_geom
r_int
id|forced_geom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 if hdx=c,h,s was given at boot */
DECL|member|nobios
r_int
id|nobios
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: do not probe bios for drive */
DECL|member|revalidate
r_int
id|revalidate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* request revalidation */
DECL|member|atapi_overlap
r_int
id|atapi_overlap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: ATAPI overlap (not supported) */
DECL|member|doorlocking
r_int
id|doorlocking
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: for removable only: door lock/unlock works */
DECL|member|autotune
r_int
id|autotune
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 1=autotune, 2=noautotune, 0=default */
DECL|member|ata_flash
r_int
id|ata_flash
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1=present, 0=default */
DECL|member|addressing
r_int
id|addressing
suffix:semicolon
multiline_comment|/* : 2; 0=28-bit, 1=48-bit, 2=64-bit */
DECL|member|scsi
id|u8
id|scsi
suffix:semicolon
multiline_comment|/* 0=default, 1=skip current ide-subdriver for ide-scsi emulation */
DECL|member|select
id|select_t
id|select
suffix:semicolon
multiline_comment|/* basic drive/head select reg value */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* last retrived status value for device */
DECL|member|ready_stat
id|u8
id|ready_stat
suffix:semicolon
multiline_comment|/* min status value for drive ready */
DECL|member|mult_count
id|u8
id|mult_count
suffix:semicolon
multiline_comment|/* current multiple sector setting */
DECL|member|bad_wstat
id|u8
id|bad_wstat
suffix:semicolon
multiline_comment|/* used for ignoring WRERR_STAT */
DECL|member|nowerr
id|u8
id|nowerr
suffix:semicolon
multiline_comment|/* used for ignoring WRERR_STAT */
DECL|member|head
id|u8
id|head
suffix:semicolon
multiline_comment|/* &quot;real&quot; number of heads */
DECL|member|sect
id|u8
id|sect
suffix:semicolon
multiline_comment|/* &quot;real&quot; sectors per track */
DECL|member|bios_head
id|u8
id|bios_head
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO number of heads */
DECL|member|bios_sect
id|u8
id|bios_sect
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO sectors per track */
DECL|member|bios_cyl
r_int
r_int
id|bios_cyl
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO number of cyls */
DECL|member|cyl
r_int
r_int
id|cyl
suffix:semicolon
multiline_comment|/* &quot;real&quot; number of cyls */
DECL|member|capacity
id|u64
id|capacity
suffix:semicolon
multiline_comment|/* total number of sectors */
DECL|member|drive_data
r_int
r_int
id|drive_data
suffix:semicolon
multiline_comment|/* for use by tuneproc/selectproc as needed */
DECL|member|wqueue
id|wait_queue_head_t
id|wqueue
suffix:semicolon
multiline_comment|/* used to wait for drive in open() */
DECL|member|id
r_struct
id|hd_driveid
op_star
id|id
suffix:semicolon
multiline_comment|/* drive model identification info */
DECL|member|part
r_struct
id|hd_struct
op_star
id|part
suffix:semicolon
multiline_comment|/* drive partition table */
DECL|member|driver
r_struct
id|ata_operations
op_star
id|driver
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* extra driver data */
DECL|member|de
id|devfs_handle_t
id|de
suffix:semicolon
multiline_comment|/* directory for device */
DECL|member|driver_req
r_char
id|driver_req
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* requests specific driver */
DECL|member|last_lun
r_int
id|last_lun
suffix:semicolon
multiline_comment|/* last logical unit */
DECL|member|forced_lun
r_int
id|forced_lun
suffix:semicolon
multiline_comment|/* if hdxlun was given at boot */
DECL|member|lun
r_int
id|lun
suffix:semicolon
multiline_comment|/* logical unit */
DECL|member|crc_count
r_int
id|crc_count
suffix:semicolon
multiline_comment|/* crc counter to reduce drive speed */
DECL|member|quirk_list
r_int
id|quirk_list
suffix:semicolon
multiline_comment|/* drive is considered quirky if set for a specific host */
DECL|member|current_speed
id|u8
id|current_speed
suffix:semicolon
multiline_comment|/* current transfer rate set */
DECL|member|dn
id|u8
id|dn
suffix:semicolon
multiline_comment|/* now wide spread use */
DECL|member|wcache
id|u8
id|wcache
suffix:semicolon
multiline_comment|/* status of write cache */
DECL|member|acoustic
id|u8
id|acoustic
suffix:semicolon
multiline_comment|/* acoustic management */
DECL|member|queue_depth
r_int
r_int
id|queue_depth
suffix:semicolon
multiline_comment|/* max queue depth */
DECL|member|failures
r_int
r_int
id|failures
suffix:semicolon
multiline_comment|/* current failure count */
DECL|member|max_failures
r_int
r_int
id|max_failures
suffix:semicolon
multiline_comment|/* maximum allowed failure count */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* global device tree handle */
multiline_comment|/*&n;&t; * tcq statistics&n;&t; */
DECL|member|immed_rel
r_int
r_int
id|immed_rel
suffix:semicolon
DECL|member|immed_comp
r_int
r_int
id|immed_comp
suffix:semicolon
DECL|member|max_last_depth
r_int
id|max_last_depth
suffix:semicolon
DECL|member|max_depth
r_int
id|max_depth
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Status returned by various functions.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ATA_OP_FINISHED
id|ATA_OP_FINISHED
comma
multiline_comment|/* no drive operation was started */
DECL|enumerator|ATA_OP_CONTINUES
id|ATA_OP_CONTINUES
comma
multiline_comment|/* a drive operation was started, and a handler was set */
DECL|enumerator|ATA_OP_RELEASED
id|ATA_OP_RELEASED
comma
multiline_comment|/* started and released bus */
DECL|enumerator|ATA_OP_READY
id|ATA_OP_READY
multiline_comment|/* indicate status poll finished fine */
DECL|typedef|ide_startstop_t
)brace
id|ide_startstop_t
suffix:semicolon
multiline_comment|/*&n; *  Interrupt and timeout handler type.&n; */
DECL|typedef|ata_handler_t
r_typedef
id|ide_startstop_t
(paren
id|ata_handler_t
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|ata_expiry_t
r_typedef
id|ide_startstop_t
(paren
id|ata_expiry_t
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|ATA_PRIMARY
id|ATA_PRIMARY
op_assign
l_int|0
comma
DECL|enumerator|ATA_SECONDARY
id|ATA_SECONDARY
op_assign
l_int|1
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IDE_BUSY
id|IDE_BUSY
comma
multiline_comment|/* awaiting an interrupt */
DECL|enumerator|IDE_SLEEP
id|IDE_SLEEP
comma
DECL|enumerator|IDE_PIO
id|IDE_PIO
comma
multiline_comment|/* PIO in progress */
DECL|enumerator|IDE_DMA
id|IDE_DMA
multiline_comment|/* DMA in progress */
)brace
suffix:semicolon
DECL|struct|ata_channel
r_struct
id|ata_channel
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* device handle */
DECL|member|unit
r_int
id|unit
suffix:semicolon
multiline_comment|/* channel number */
multiline_comment|/* This lock is used to serialize requests on the same device queue or&n;&t; * between differen queues sharing the same irq line.&n;&t; */
DECL|member|lock
id|spinlock_t
op_star
id|lock
suffix:semicolon
DECL|member|active
r_int
r_int
op_star
id|active
suffix:semicolon
multiline_comment|/* active processing request */
DECL|member|handler
id|ide_startstop_t
(paren
op_star
id|handler
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
multiline_comment|/* irq handler, if active */
multiline_comment|/* FIXME: Only still used in PDC4030.  Localize this code there by&n;&t; * replacing with busy waits.&n;&t; */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* failsafe timer */
DECL|member|expiry
id|ide_startstop_t
(paren
op_star
id|expiry
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* irq handler, if active */
DECL|member|poll_timeout
r_int
r_int
id|poll_timeout
suffix:semicolon
multiline_comment|/* timeout value during polled operations */
DECL|member|drive
r_struct
id|ata_device
op_star
id|drive
suffix:semicolon
multiline_comment|/* last serviced drive */
DECL|member|io_ports
id|ide_ioreg_t
id|io_ports
(braket
id|IDE_NR_PORTS
)braket
suffix:semicolon
multiline_comment|/* task file registers */
DECL|member|hw
id|hw_regs_t
id|hw
suffix:semicolon
multiline_comment|/* hardware info */
macro_line|#ifdef CONFIG_PCI
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* for pci chipsets */
macro_line|#endif
DECL|member|drives
r_struct
id|ata_device
id|drives
(braket
id|MAX_DRIVES
)braket
suffix:semicolon
multiline_comment|/* drive info */
DECL|member|gd
r_struct
id|gendisk
op_star
id|gd
suffix:semicolon
multiline_comment|/* gendisk structure */
multiline_comment|/*&n;&t; * Routines to tune PIO and DMA mode for drives.&n;&t; *&n;&t; * A value of 255 indicates that the function should choose the optimal&n;&t; * mode itself.&n;&t; */
multiline_comment|/* setup disk on a channel for a particular PIO transfer mode */
DECL|member|tuneproc
r_void
(paren
op_star
id|tuneproc
)paren
(paren
r_struct
id|ata_device
op_star
comma
id|u8
id|pio
)paren
suffix:semicolon
multiline_comment|/* setup the chipset timing for a particular transfer mode */
DECL|member|speedproc
r_int
(paren
op_star
id|speedproc
)paren
(paren
r_struct
id|ata_device
op_star
comma
id|u8
id|pio
)paren
suffix:semicolon
multiline_comment|/* tweaks hardware to select drive */
DECL|member|selectproc
r_void
(paren
op_star
id|selectproc
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/* routine to reset controller after a disk reset */
DECL|member|resetproc
r_void
(paren
op_star
id|resetproc
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/* special interrupt handling for shared pci interrupts */
DECL|member|intrproc
r_void
(paren
op_star
id|intrproc
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/* special host masking for drive selection */
DECL|member|maskproc
r_void
(paren
op_star
id|maskproc
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/* check host&squot;s drive quirk list */
DECL|member|quirkproc
r_int
(paren
op_star
id|quirkproc
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/* driver soft-power interface */
DECL|member|busproc
r_int
(paren
op_star
id|busproc
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* CPU-polled transfer routines */
DECL|member|ata_read
r_void
(paren
op_star
id|ata_read
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|ata_write
r_void
(paren
op_star
id|ata_write
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|atapi_read
r_void
(paren
op_star
id|atapi_read
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|atapi_write
r_void
(paren
op_star
id|atapi_write
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|udma_setup
r_int
(paren
op_star
id|udma_setup
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|udma_enable
r_void
(paren
op_star
id|udma_enable
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|udma_start
r_void
(paren
op_star
id|udma_start
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|member|udma_stop
r_int
(paren
op_star
id|udma_stop
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|udma_init
r_int
(paren
op_star
id|udma_init
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|member|udma_irq_status
r_int
(paren
op_star
id|udma_irq_status
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|udma_timeout
r_void
(paren
op_star
id|udma_timeout
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|udma_irq_lost
r_void
(paren
op_star
id|udma_irq_lost
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|seg_boundary_mask
r_int
r_int
id|seg_boundary_mask
suffix:semicolon
DECL|member|max_segment_size
r_int
r_int
id|max_segment_size
suffix:semicolon
DECL|member|dmatable_cpu
r_int
r_int
op_star
id|dmatable_cpu
suffix:semicolon
multiline_comment|/* dma physical region descriptor table (cpu view) */
DECL|member|dmatable_dma
id|dma_addr_t
id|dmatable_dma
suffix:semicolon
multiline_comment|/* dma physical region descriptor table (dma view) */
DECL|member|sg_table
r_struct
id|scatterlist
op_star
id|sg_table
suffix:semicolon
multiline_comment|/* Scatter-gather list used to build the above */
DECL|member|sg_nents
r_int
id|sg_nents
suffix:semicolon
multiline_comment|/* Current number of entries in it */
DECL|member|sg_dma_direction
r_int
id|sg_dma_direction
suffix:semicolon
multiline_comment|/* dma transfer direction */
DECL|member|dma_base
r_int
r_int
id|dma_base
suffix:semicolon
multiline_comment|/* base addr for dma ports */
DECL|member|dma_extra
r_int
id|dma_extra
suffix:semicolon
multiline_comment|/* extra addr for dma ports */
DECL|member|config_data
r_int
r_int
id|config_data
suffix:semicolon
multiline_comment|/* for use by chipset-specific code */
DECL|member|select_data
r_int
r_int
id|select_data
suffix:semicolon
multiline_comment|/* for use by chipset-specific code */
DECL|member|proc
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
multiline_comment|/* /proc/ide/ directory entry */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* our irq number */
DECL|member|major
r_int
id|major
suffix:semicolon
multiline_comment|/* our major number */
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* name of interface */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* 0 for ide0; 1 for ide1; ... */
DECL|member|chipset
id|hwif_chipset_t
id|chipset
suffix:semicolon
multiline_comment|/* sub-module for tuning.. */
DECL|member|noprobe
r_int
id|noprobe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t probe for this interface */
DECL|member|present
r_int
id|present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* there is a device on this interface */
DECL|member|serialized
r_int
id|serialized
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* serialized operation between channels */
DECL|member|sharing_irq
r_int
id|sharing_irq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 = sharing irq with another hwif */
DECL|member|reset
r_int
id|reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reset after probe */
DECL|member|autodma
r_int
id|autodma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* automatically try to enable DMA at boot */
DECL|member|udma_four
r_int
id|udma_four
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1=ATA-66 capable, 0=default */
DECL|member|highmem
r_int
id|highmem
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* can do full 32-bit dma */
DECL|member|straight8
r_int
id|straight8
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Alan&squot;s straight 8 check */
DECL|member|no_io_32bit
r_int
id|no_io_32bit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disallow enabling 32bit I/O */
DECL|member|no_unmask
r_int
id|no_unmask
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disallow setting unmask bit */
DECL|member|auto_poll
r_int
id|auto_poll
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* supports nop auto-poll */
DECL|member|unmask
r_int
id|unmask
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: okay to unmask other irqs */
DECL|member|slow
r_int
id|slow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: slow data port */
DECL|member|io_32bit
r_int
id|io_32bit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0=16-bit, 1=32-bit */
DECL|member|no_atapi_autodma
r_int
id|no_atapi_autodma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: use auto DMA only for disks */
DECL|member|bus_state
r_int
r_char
id|bus_state
suffix:semicolon
multiline_comment|/* power state of the IDE bus */
DECL|member|modes_map
r_int
id|modes_map
suffix:semicolon
multiline_comment|/* map of supported transfer modes */
)brace
suffix:semicolon
multiline_comment|/*&n; * Register new hardware with ide&n; */
r_extern
r_int
id|ide_register_hw
c_func
(paren
id|hw_regs_t
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_void
id|ide_unregister
c_func
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
DECL|macro|IDE_MAX_TAG
mdefine_line|#define IDE_MAX_TAG&t;32
macro_line|#ifdef CONFIG_BLK_DEV_IDE_TCQ
DECL|function|ata_pending_commands
r_static
r_inline
r_int
id|ata_pending_commands
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;using_tcq
)paren
r_return
id|blk_queue_tag_depth
c_func
(paren
op_amp
id|drive-&gt;queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata_can_queue
r_static
r_inline
r_int
id|ata_can_queue
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;using_tcq
)paren
r_return
id|blk_queue_tag_queue
c_func
(paren
op_amp
id|drive-&gt;queue
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|macro|ata_pending_commands
macro_line|# define ata_pending_commands(drive)&t;(0)
DECL|macro|ata_can_queue
macro_line|# define ata_can_queue(drive)&t;&t;(1)
macro_line|#endif
multiline_comment|/* FIXME: kill this as soon as possible */
DECL|macro|PROC_IDE_READ_RETURN
mdefine_line|#define PROC_IDE_READ_RETURN(page,start,off,count,eof,len) return 0;
multiline_comment|/*&n; * This structure describes the operations possible on a particular device type&n; * (CD-ROM, tape, DISK and so on).&n; *&n; * This is the main hook for device type support submodules.&n; */
DECL|struct|ata_operations
r_struct
id|ata_operations
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|attach
r_void
(paren
op_star
id|attach
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|cleanup
r_int
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|standby
r_int
(paren
op_star
id|standby
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|do_request
id|ide_startstop_t
(paren
op_star
id|do_request
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
comma
id|sector_t
)paren
suffix:semicolon
DECL|member|end_request
r_int
(paren
op_star
id|end_request
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|check_media_change
r_int
(paren
op_star
id|check_media_change
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|revalidate
r_void
(paren
op_star
id|revalidate
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|capacity
id|sector_t
(paren
op_star
id|capacity
)paren
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/* linked list of rgistered device type drivers */
DECL|member|next
r_struct
id|ata_operations
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Alas, no aliases. Too much hassle with bringing module.h everywhere */
DECL|macro|ata_get
mdefine_line|#define ata_get(ata) &bslash;&n;&t;(((ata) &amp;&amp; (ata)-&gt;owner)&t;&bslash;&n;&t;&t;? ( try_inc_mod_count((ata)-&gt;owner) ? (ata) : NULL ) &bslash;&n;&t;&t;: (ata))
DECL|macro|ata_put
mdefine_line|#define ata_put(ata) &bslash;&n;do {&t;&bslash;&n;&t;if ((ata) &amp;&amp; (ata)-&gt;owner) &bslash;&n;&t;&t;__MOD_DEC_USE_COUNT((ata)-&gt;owner);&t;&bslash;&n;} while(0)
r_extern
id|sector_t
id|ata_capacity
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
r_extern
r_void
id|unregister_ata_driver
c_func
(paren
r_struct
id|ata_operations
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_int
id|register_ata_driver
c_func
(paren
r_struct
id|ata_operations
op_star
id|driver
)paren
suffix:semicolon
DECL|function|ata_driver_module
r_static
r_inline
r_int
id|ata_driver_module
c_func
(paren
r_struct
id|ata_operations
op_star
id|driver
)paren
(brace
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|register_ata_driver
c_func
(paren
id|driver
)paren
op_le
l_int|0
)paren
(brace
id|unregister_ata_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#else
id|register_ata_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|ata_ops
mdefine_line|#define ata_ops(drive)&t;&t;((drive)-&gt;driver)
r_extern
r_struct
id|ata_channel
id|ide_hwifs
(braket
)braket
suffix:semicolon
multiline_comment|/* master data repository */
r_extern
r_int
id|noautodma
suffix:semicolon
multiline_comment|/*&n; * We need blk.h, but we replace its end_request by our own version.&n; */
DECL|macro|IDE_DRIVER
mdefine_line|#define IDE_DRIVER&t;&t;/* Toggle some magic bits in blk.h */
DECL|macro|LOCAL_END_REQUEST
mdefine_line|#define LOCAL_END_REQUEST&t;/* Don&squot;t generate end_request in blk.h */
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device)&t;(minor(device) &gt;&gt; PARTN_BITS)
macro_line|#include &lt;linux/blk.h&gt;
r_extern
r_int
id|ata_end_request
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ata_set_handler
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|ata_handler_t
id|handler
comma
r_int
r_int
id|timeout
comma
id|ata_expiry_t
id|expiry
)paren
suffix:semicolon
r_extern
id|u8
id|ata_dump
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
id|ide_startstop_t
id|ata_error
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
id|rq
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ide_fixstring
c_func
(paren
r_char
op_star
id|s
comma
r_const
r_int
id|bytecount
comma
r_const
r_int
id|byteswap
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine is called from the partition-table code in genhd.c&n; * to &quot;convert&quot; a drive to a logical geometry with fewer than 1024 cyls.&n; */
r_int
id|ide_xlate_1024
c_func
(paren
id|kdev_t
comma
r_int
comma
r_int
comma
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Convert kdev_t structure into struct ata_device * one.&n; */
r_struct
id|ata_device
op_star
id|get_info_ptr
c_func
(paren
id|kdev_t
id|i_rdev
)paren
suffix:semicolon
multiline_comment|/*&n; * temporarily mapping a (possible) highmem bio for PIO transfer&n; */
DECL|macro|ide_rq_offset
mdefine_line|#define ide_rq_offset(rq) (((rq)-&gt;hard_cur_sectors - (rq)-&gt;current_nr_sectors) &lt;&lt; 9)
DECL|struct|ata_taskfile
r_struct
id|ata_taskfile
(brace
DECL|member|taskfile
r_struct
id|hd_drive_task_hdr
id|taskfile
suffix:semicolon
DECL|member|hobfile
r_struct
id|hd_drive_task_hdr
id|hobfile
suffix:semicolon
DECL|member|cmd
id|u8
id|cmd
suffix:semicolon
multiline_comment|/* actual ATA command */
DECL|member|command_type
r_int
id|command_type
suffix:semicolon
DECL|member|XXX_handler
id|ide_startstop_t
(paren
op_star
id|XXX_handler
)paren
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|ata_read
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ata_write
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ide_raw_taskfile
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|ata_taskfile
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ide_config_drive_speed
c_func
(paren
r_struct
id|ata_device
op_star
comma
id|u8
)paren
suffix:semicolon
r_extern
r_int
id|eighty_ninty_three
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|system_bus_speed
suffix:semicolon
multiline_comment|/*&n; * CompactFlash cards and their brethern pretend to be removable hard disks,&n; * but they never have a slave unit, and they don&squot;t have doorlock mechanisms.&n; * This test catches them, and is invoked elsewhere when setting appropriate&n; * config bits.&n; */
r_extern
r_int
id|drive_is_flashcard
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ide_spin_wait_hwgroup
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ide_timer_expiry
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_extern
r_void
id|ata_irq_request
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|do_ide_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_void
id|ide_init_subdrivers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|block_device_operations
id|ide_fops
(braket
)braket
suffix:semicolon
multiline_comment|/* Probe for devices attached to the systems host controllers.&n; */
r_extern
r_int
id|ideprobe_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDISK
r_extern
r_int
id|idedisk_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
r_extern
r_int
id|ide_cdrom_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDETAPE
r_extern
r_int
id|idetape_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDEFLOPPY
r_extern
r_int
id|idefloppy_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDESCSI
r_extern
r_int
id|idescsi_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|ata_register_device
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|ata_operations
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ata_unregister_device
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
r_extern
r_int
id|ata_revalidate
c_func
(paren
id|kdev_t
id|i_rdev
)paren
suffix:semicolon
r_extern
r_void
id|ide_driver_module
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|macro|ON_BOARD
macro_line|# define ON_BOARD&t;&t;0
DECL|macro|NEVER_BOARD
macro_line|# define NEVER_BOARD&t;&t;1
macro_line|# ifdef CONFIG_BLK_DEV_OFFBOARD
DECL|macro|OFF_BOARD
macro_line|#  define OFF_BOARD&t;&t;ON_BOARD
macro_line|# else
DECL|macro|OFF_BOARD
macro_line|#  define OFF_BOARD&t;&t;NEVER_BOARD
macro_line|# endif
r_void
id|__init
id|ide_scan_pcibus
c_func
(paren
r_int
id|scan_direction
)paren
suffix:semicolon
macro_line|#endif
DECL|function|udma_enable
r_static
r_inline
r_void
id|udma_enable
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|on
comma
r_int
id|verbose
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_enable
c_func
(paren
id|drive
comma
id|on
comma
id|verbose
)paren
suffix:semicolon
)brace
DECL|function|udma_start
r_static
r_inline
r_void
id|udma_start
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_start
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|udma_stop
r_static
r_inline
r_int
id|udma_stop
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_stop
c_func
(paren
id|drive
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|IDE_DMA
comma
id|drive-&gt;channel-&gt;active
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Initiate actual DMA data transfer. The direction is encoded in the request.&n; */
DECL|function|udma_init
r_static
r_inline
id|ide_startstop_t
id|udma_init
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_int
id|ret
suffix:semicolon
id|set_bit
c_func
(paren
id|IDE_DMA
comma
id|drive-&gt;channel-&gt;active
)paren
suffix:semicolon
id|ret
op_assign
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_init
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|ATA_OP_CONTINUES
)paren
id|clear_bit
c_func
(paren
id|IDE_DMA
comma
id|drive-&gt;channel-&gt;active
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|udma_irq_status
r_static
r_inline
r_int
id|udma_irq_status
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_return
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_irq_status
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|udma_timeout
r_static
r_inline
r_void
id|udma_timeout
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_timeout
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|udma_irq_lost
r_static
r_inline
r_void
id|udma_irq_lost
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_irq_lost
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_extern
r_void
id|udma_pci_enable
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|on
comma
r_int
id|verbose
)paren
suffix:semicolon
r_extern
r_void
id|udma_pci_start
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
r_extern
r_int
id|udma_pci_stop
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
r_extern
r_int
id|udma_pci_init
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
r_extern
r_int
id|udma_pci_irq_status
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
r_extern
r_void
id|udma_pci_timeout
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
r_extern
r_void
id|udma_pci_irq_lost
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|udma_pci_setup
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udma_generic_setup
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udma_new_table
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udma_destroy_table
c_func
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udma_print
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|udma_black_list
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|udma_white_list
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
id|ide_startstop_t
id|udma_tcq_init
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|udma_tcq_enable
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|ide_startstop_t
id|ide_dma_intr
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|check_drive_lists
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
id|good_bad
)paren
suffix:semicolon
r_extern
r_void
id|ide_release_dma
c_func
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ata_start_dma
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
r_extern
r_void
id|ata_init_dma
c_func
(paren
r_struct
id|ata_channel
op_star
comma
r_int
r_int
)paren
id|__init
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|ata_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|ide_lock
suffix:semicolon
DECL|macro|DRIVE_LOCK
mdefine_line|#define DRIVE_LOCK(drive)&t;((drive)-&gt;queue.queue_lock)
multiline_comment|/* Low level device access functions. */
r_extern
r_void
id|ata_select
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ata_mask
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ata_status
c_func
(paren
r_struct
id|ata_device
op_star
comma
id|u8
comma
id|u8
)paren
suffix:semicolon
r_extern
r_int
id|ata_status_irq
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
r_extern
r_int
id|ata_status_poll
c_func
(paren
r_struct
id|ata_device
op_star
comma
id|u8
comma
id|u8
comma
r_int
r_int
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
r_extern
r_int
id|ata_irq_enable
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ata_reset
c_func
(paren
r_struct
id|ata_channel
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ata_out_regfile
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|hd_drive_task_hdr
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ata_in_regfile
c_func
(paren
r_struct
id|ata_device
op_star
comma
r_struct
id|hd_drive_task_hdr
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
