macro_line|#ifndef _LINUX_HDREG_H
DECL|macro|_LINUX_HDREG_H
mdefine_line|#define _LINUX_HDREG_H
multiline_comment|/*&n; * This file contains some defines for the AT-hd-controller.&n; * Various sources.&n; */
DECL|macro|HD_IRQ
mdefine_line|#define HD_IRQ 14&t;&t;&t;/* the standard disk interrupt */
multiline_comment|/* ide.c has its own port definitions in &quot;ide.h&quot; */
multiline_comment|/* Hd controller regs. Ref: IBM AT Bios-listing */
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA&t;&t;0x1f0&t;&t;/* _CTL when writing */
DECL|macro|HD_ERROR
mdefine_line|#define HD_ERROR&t;0x1f1&t;&t;/* see err-bits */
DECL|macro|HD_NSECTOR
mdefine_line|#define HD_NSECTOR&t;0x1f2&t;&t;/* nr of sectors to read/write */
DECL|macro|HD_SECTOR
mdefine_line|#define HD_SECTOR&t;0x1f3&t;&t;/* starting sector */
DECL|macro|HD_LCYL
mdefine_line|#define HD_LCYL&t;&t;0x1f4&t;&t;/* starting cylinder */
DECL|macro|HD_HCYL
mdefine_line|#define HD_HCYL&t;&t;0x1f5&t;&t;/* high byte of starting cyl */
DECL|macro|HD_CURRENT
mdefine_line|#define HD_CURRENT&t;0x1f6&t;&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|HD_STATUS
mdefine_line|#define HD_STATUS&t;0x1f7&t;&t;/* see status-bits */
DECL|macro|HD_FEATURE
mdefine_line|#define HD_FEATURE&t;HD_ERROR&t;/* same io address, read=error, write=feature */
DECL|macro|HD_PRECOMP
mdefine_line|#define HD_PRECOMP&t;HD_FEATURE&t;/* obsolete use of this port - predates IDE */
DECL|macro|HD_COMMAND
mdefine_line|#define HD_COMMAND&t;HD_STATUS&t;/* same io address, read=status, write=cmd */
DECL|macro|HD_CMD
mdefine_line|#define HD_CMD&t;&t;0x3f6&t;&t;/* used for resets */
DECL|macro|HD_ALTSTATUS
mdefine_line|#define HD_ALTSTATUS&t;0x3f6&t;&t;/* same as HD_STATUS but doesn&squot;t clear irq */
multiline_comment|/* remainder is shared between hd.c, ide.c, ide-cd.c, and the hdparm utility */
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
multiline_comment|/*&n; * Command Header sizes for IOCTL commands&n; */
DECL|macro|HDIO_DRIVE_CMD_HDR_SIZE
mdefine_line|#define HDIO_DRIVE_CMD_HDR_SIZE&t;&t;(4 * sizeof(u8))
DECL|macro|HDIO_DRIVE_HOB_HDR_SIZE
mdefine_line|#define HDIO_DRIVE_HOB_HDR_SIZE&t;&t;(8 * sizeof(u8))
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
DECL|member|data
id|u8
id|data
suffix:semicolon
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
DECL|member|command
id|u8
id|command
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
DECL|struct|hd_drive_hob_hdr
r_struct
id|hd_drive_hob_hdr
(brace
DECL|member|data
id|u8
id|data
suffix:semicolon
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
DECL|member|control
id|u8
id|control
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
DECL|struct|hd_geometry
r_struct
id|hd_geometry
(brace
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|sectors
r_int
r_char
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
r_int
id|cylinders
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* BIG GEOMETRY - dying, used only by HDIO_GETGEO_BIG_RAW */
DECL|struct|hd_big_geometry
r_struct
id|hd_big_geometry
(brace
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|sectors
r_int
r_char
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
r_int
id|cylinders
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) ptrs to user space are numbered 0x030n/0x031n */
DECL|macro|HDIO_GETGEO
mdefine_line|#define HDIO_GETGEO&t;&t;0x0301&t;/* get device geometry */
DECL|macro|HDIO_GET_UNMASKINTR
mdefine_line|#define HDIO_GET_UNMASKINTR&t;0x0302&t;/* get current unmask setting */
DECL|macro|HDIO_GET_MULTCOUNT
mdefine_line|#define HDIO_GET_MULTCOUNT&t;0x0304&t;/* get current IDE blockmode setting */
DECL|macro|HDIO_GET_QDMA
mdefine_line|#define HDIO_GET_QDMA&t;&t;0x0305&t;/* get use-qdma flag */
DECL|macro|HDIO_GET_32BIT
mdefine_line|#define HDIO_GET_32BIT&t;&t;0x0309&t;/* get current io_32bit setting */
DECL|macro|HDIO_GET_NOWERR
mdefine_line|#define HDIO_GET_NOWERR&t;&t;0x030a&t;/* get ignore-write-error flag */
DECL|macro|HDIO_GET_DMA
mdefine_line|#define HDIO_GET_DMA&t;&t;0x030b&t;/* get use-dma flag */
DECL|macro|HDIO_GET_NICE
mdefine_line|#define HDIO_GET_NICE&t;&t;0x030c&t;/* get nice flags */
DECL|macro|HDIO_GET_IDENTITY
mdefine_line|#define HDIO_GET_IDENTITY&t;0x030d&t;/* get IDE identification info */
DECL|macro|HDIO_GET_WCACHE
mdefine_line|#define HDIO_GET_WCACHE&t;&t;0x030e&t;/* get write cache mode on|off */
DECL|macro|HDIO_GET_ACOUSTIC
mdefine_line|#define HDIO_GET_ACOUSTIC&t;0x030f&t;/* get acoustic value */
DECL|macro|HDIO_GET_ADDRESS
mdefine_line|#define&t;HDIO_GET_ADDRESS&t;0x0310&t;/* */
DECL|macro|HDIO_GET_BUSSTATE
mdefine_line|#define HDIO_GET_BUSSTATE&t;0x031a&t;/* get the bus state of the hwif */
DECL|macro|HDIO_DRIVE_CMD
mdefine_line|#define HDIO_DRIVE_CMD&t;&t;0x031f&t;/* execute a special drive command */
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) non-ptr values are numbered 0x032n/0x033n */
DECL|macro|HDIO_SET_MULTCOUNT
mdefine_line|#define HDIO_SET_MULTCOUNT&t;0x0321&t;/* change IDE blockmode */
DECL|macro|HDIO_SET_UNMASKINTR
mdefine_line|#define HDIO_SET_UNMASKINTR&t;0x0322&t;/* permit other irqs during I/O */
DECL|macro|HDIO_SET_32BIT
mdefine_line|#define HDIO_SET_32BIT&t;&t;0x0324&t;/* change io_32bit flags */
DECL|macro|HDIO_SET_NOWERR
mdefine_line|#define HDIO_SET_NOWERR&t;&t;0x0325&t;/* change ignore-write-error flag */
DECL|macro|HDIO_SET_DMA
mdefine_line|#define HDIO_SET_DMA&t;&t;0x0326&t;/* change use-dma flag */
DECL|macro|HDIO_SET_PIO_MODE
mdefine_line|#define HDIO_SET_PIO_MODE&t;0x0327&t;/* reconfig interface to new speed */
DECL|macro|HDIO_SET_NICE
mdefine_line|#define HDIO_SET_NICE&t;&t;0x0329&t;/* set nice flags */
DECL|macro|HDIO_SET_WCACHE
mdefine_line|#define HDIO_SET_WCACHE&t;&t;0x032b&t;/* change write cache enable-disable */
DECL|macro|HDIO_SET_ACOUSTIC
mdefine_line|#define HDIO_SET_ACOUSTIC&t;0x032c&t;/* change acoustic behavior */
DECL|macro|HDIO_SET_BUSSTATE
mdefine_line|#define HDIO_SET_BUSSTATE&t;0x032d&t;/* set the bus state of the hwif */
DECL|macro|HDIO_SET_QDMA
mdefine_line|#define HDIO_SET_QDMA&t;&t;0x032e&t;/* change use-qdma flag */
DECL|macro|HDIO_SET_ADDRESS
mdefine_line|#define HDIO_SET_ADDRESS&t;0x032f&t;/* change lba addressing modes */
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
multiline_comment|/* hd/ide ctl&squot;s that pass (arg) ptrs to user space are numbered 0x033n/0x033n */
multiline_comment|/* 0x330 is reserved - used to be HDIO_GETGEO_BIG */
DECL|macro|HDIO_GETGEO_BIG_RAW
mdefine_line|#define HDIO_GETGEO_BIG_RAW&t;0x0331&t;/* */
DECL|macro|__NEW_HD_DRIVE_ID
mdefine_line|#define __NEW_HD_DRIVE_ID
multiline_comment|/*&n; * Structure returned by HDIO_GET_IDENTITY, as per ANSI NCITS ATA6 rev.1b spec.&n; *&n; * If you change something here, please remember to update fix_driveid() in&n; * ide/probe.c.&n; */
DECL|struct|hd_driveid
r_struct
id|hd_driveid
(brace
DECL|member|config
r_int
r_int
id|config
suffix:semicolon
multiline_comment|/* lots of obsolete bit flags */
DECL|member|cyls
r_int
r_int
id|cyls
suffix:semicolon
multiline_comment|/* Obsolete, &quot;physical&quot; cyls */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:semicolon
multiline_comment|/* reserved (word 2) */
DECL|member|heads
r_int
r_int
id|heads
suffix:semicolon
multiline_comment|/* Obsolete, &quot;physical&quot; heads */
DECL|member|track_bytes
r_int
r_int
id|track_bytes
suffix:semicolon
multiline_comment|/* unformatted bytes per track */
DECL|member|sector_bytes
r_int
r_int
id|sector_bytes
suffix:semicolon
multiline_comment|/* unformatted bytes per sector */
DECL|member|sectors
r_int
r_int
id|sectors
suffix:semicolon
multiline_comment|/* Obsolete, &quot;physical&quot; sectors per track */
DECL|member|vendor0
r_int
r_int
id|vendor0
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|vendor1
r_int
r_int
id|vendor1
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|vendor2
r_int
r_int
id|vendor2
suffix:semicolon
multiline_comment|/* Retired vendor unique */
DECL|member|serial_no
r_int
r_char
id|serial_no
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|buf_type
r_int
r_int
id|buf_type
suffix:semicolon
multiline_comment|/* Retired */
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* Retired, 512 byte increments&n;&t;&t;&t;&t;&t; * 0 = not_specified&n;&t;&t;&t;&t;&t; */
DECL|member|ecc_bytes
r_int
r_int
id|ecc_bytes
suffix:semicolon
multiline_comment|/* for r/w long cmds; 0 = not_specified */
DECL|member|fw_rev
r_int
r_char
id|fw_rev
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|model
r_int
r_char
id|model
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* 0 = not_specified */
DECL|member|max_multsect
r_int
r_char
id|max_multsect
suffix:semicolon
multiline_comment|/* 0=not_implemented */
DECL|member|vendor3
r_int
r_char
id|vendor3
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|dword_io
r_int
r_int
id|dword_io
suffix:semicolon
multiline_comment|/* 0=not_implemented; 1=implemented */
DECL|member|vendor4
r_int
r_char
id|vendor4
suffix:semicolon
multiline_comment|/* vendor unique */
DECL|member|capability
r_int
r_char
id|capability
suffix:semicolon
multiline_comment|/* (upper byte of word 49)&n;&t;&t;&t;&t;&t; *  3:&t;IORDYsup&n;&t;&t;&t;&t;&t; *  2:&t;IORDYsw&n;&t;&t;&t;&t;&t; *  1:&t;LBA&n;&t;&t;&t;&t;&t; *  0:&t;DMA&n;&t;&t;&t;&t;&t; */
DECL|member|reserved50
r_int
r_int
id|reserved50
suffix:semicolon
multiline_comment|/* reserved (word 50) */
DECL|member|vendor5
r_int
r_char
id|vendor5
suffix:semicolon
multiline_comment|/* Obsolete, vendor unique */
DECL|member|tPIO
r_int
r_char
id|tPIO
suffix:semicolon
multiline_comment|/* Obsolete, 0=slow, 1=medium, 2=fast */
DECL|member|vendor6
r_int
r_char
id|vendor6
suffix:semicolon
multiline_comment|/* Obsolete, vendor unique */
DECL|member|tDMA
r_int
r_char
id|tDMA
suffix:semicolon
multiline_comment|/* Obsolete, 0=slow, 1=medium, 2=fast */
DECL|member|field_valid
r_int
r_int
id|field_valid
suffix:semicolon
multiline_comment|/* (word 53)&n;&t;&t;&t;&t;&t; *  2:&t;ultra_ok&t;word  88&n;&t;&t;&t;&t;&t; *  1:&t;eide_ok&t;&t;words 64-70&n;&t;&t;&t;&t;&t; *  0:&t;cur_ok&t;&t;words 54-58&n;&t;&t;&t;&t;&t; */
DECL|member|cur_cyls
r_int
r_int
id|cur_cyls
suffix:semicolon
multiline_comment|/* Obsolete, logical cylinders */
DECL|member|cur_heads
r_int
r_int
id|cur_heads
suffix:semicolon
multiline_comment|/* Obsolete, l heads */
DECL|member|cur_sectors
r_int
r_int
id|cur_sectors
suffix:semicolon
multiline_comment|/* Obsolete, l sectors per track */
DECL|member|cur_capacity0
r_int
r_int
id|cur_capacity0
suffix:semicolon
multiline_comment|/* Obsolete, l total sectors on drive */
DECL|member|cur_capacity1
r_int
r_int
id|cur_capacity1
suffix:semicolon
multiline_comment|/* Obsolete, (2 words, misaligned int)     */
DECL|member|multsect
r_int
r_char
id|multsect
suffix:semicolon
multiline_comment|/* current multiple sector count */
DECL|member|multsect_valid
r_int
r_char
id|multsect_valid
suffix:semicolon
multiline_comment|/* when (bit0==1) multsect is ok */
DECL|member|lba_capacity
r_int
r_int
id|lba_capacity
suffix:semicolon
multiline_comment|/* Obsolete, total number of sectors */
DECL|member|dma_1word
r_int
r_int
id|dma_1word
suffix:semicolon
multiline_comment|/* Obsolete, single-word dma info */
DECL|member|dma_mword
r_int
r_int
id|dma_mword
suffix:semicolon
multiline_comment|/* multiple-word dma info */
DECL|member|eide_pio_modes
r_int
r_int
id|eide_pio_modes
suffix:semicolon
multiline_comment|/* bits 0:mode3 1:mode4 */
DECL|member|eide_dma_min
r_int
r_int
id|eide_dma_min
suffix:semicolon
multiline_comment|/* min mword dma cycle time (ns) */
DECL|member|eide_dma_time
r_int
r_int
id|eide_dma_time
suffix:semicolon
multiline_comment|/* recommended mword dma cycle time (ns) */
DECL|member|eide_pio
r_int
r_int
id|eide_pio
suffix:semicolon
multiline_comment|/* min cycle time (ns), no IORDY  */
DECL|member|eide_pio_iordy
r_int
r_int
id|eide_pio_iordy
suffix:semicolon
multiline_comment|/* min cycle time (ns), with IORDY */
DECL|member|words69_70
r_int
r_int
id|words69_70
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* reserved words 69-70&n;&t;&t;&t;&t;&t; * future command overlap and queuing&n;&t;&t;&t;&t;&t; */
multiline_comment|/* HDIO_GET_IDENTITY currently returns only words 0 through 70 */
DECL|member|words71_74
r_int
r_int
id|words71_74
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved words 71-74&n;&t;&t;&t;&t;&t; * for IDENTIFY PACKET DEVICE command&n;&t;&t;&t;&t;&t; */
DECL|member|queue_depth
r_int
r_int
id|queue_depth
suffix:semicolon
multiline_comment|/* (word 75)&n;&t;&t;&t;&t;&t; * 15:5&t;reserved&n;&t;&t;&t;&t;&t; *  4:0&t;Maximum queue depth -1&n;&t;&t;&t;&t;&t; */
DECL|member|words76_79
r_int
r_int
id|words76_79
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved words 76-79 */
DECL|member|major_rev_num
r_int
r_int
id|major_rev_num
suffix:semicolon
multiline_comment|/* (word 80) */
DECL|member|minor_rev_num
r_int
r_int
id|minor_rev_num
suffix:semicolon
multiline_comment|/* (word 81) */
DECL|member|command_set_1
r_int
r_int
id|command_set_1
suffix:semicolon
multiline_comment|/* (word 82) supported&n;&t;&t;&t;&t;&t; * 15:&t;Obsolete&n;&t;&t;&t;&t;&t; * 14:&t;NOP command&n;&t;&t;&t;&t;&t; * 13:&t;READ_BUFFER&n;&t;&t;&t;&t;&t; * 12:&t;WRITE_BUFFER&n;&t;&t;&t;&t;&t; * 11:&t;Obsolete&n;&t;&t;&t;&t;&t; * 10:&t;Host Protected Area&n;&t;&t;&t;&t;&t; *  9:&t;DEVICE Reset&n;&t;&t;&t;&t;&t; *  8:&t;SERVICE Interrupt&n;&t;&t;&t;&t;&t; *  7:&t;Release Interrupt&n;&t;&t;&t;&t;&t; *  6:&t;look-ahead&n;&t;&t;&t;&t;&t; *  5:&t;write cache&n;&t;&t;&t;&t;&t; *  4:&t;PACKET Command&n;&t;&t;&t;&t;&t; *  3:&t;Power Management Feature Set&n;&t;&t;&t;&t;&t; *  2:&t;Removable Feature Set&n;&t;&t;&t;&t;&t; *  1:&t;Security Feature Set&n;&t;&t;&t;&t;&t; *  0:&t;SMART Feature Set&n;&t;&t;&t;&t;&t; */
DECL|member|command_set_2
r_int
r_int
id|command_set_2
suffix:semicolon
multiline_comment|/* (word 83)&n;&t;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t;&t; * 13:&t;FLUSH CACHE EXT&n;&t;&t;&t;&t;&t; * 12:&t;FLUSH CACHE&n;&t;&t;&t;&t;&t; * 11:&t;Device Configuration Overlay&n;&t;&t;&t;&t;&t; * 10:&t;48-bit Address Feature Set&n;&t;&t;&t;&t;&t; *  9:&t;Automatic Acoustic Management&n;&t;&t;&t;&t;&t; *  8:&t;SET MAX security&n;&t;&t;&t;&t;&t; *  7:&t;reserved 1407DT PARTIES&n;&t;&t;&t;&t;&t; *  6:&t;SetF sub-command Power-Up&n;&t;&t;&t;&t;&t; *  5:&t;Power-Up in Standby Feature Set&n;&t;&t;&t;&t;&t; *  4:&t;Removable Media Notification&n;&t;&t;&t;&t;&t; *  3:&t;APM Feature Set&n;&t;&t;&t;&t;&t; *  2:&t;CFA Feature Set&n;&t;&t;&t;&t;&t; *  1:&t;READ/WRITE DMA QUEUED&n;&t;&t;&t;&t;&t; *  0:&t;Download MicroCode&n;&t;&t;&t;&t;&t; */
DECL|member|cfsse
r_int
r_int
id|cfsse
suffix:semicolon
multiline_comment|/* (word 84)&n;&t;&t;&t;&t;&t; * cmd set-feature supported extensions&n;&t;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t;&t; * 13:3&t;reserved&n;&t;&t;&t;&t;&t; *  2:&t;Media Serial Number Valid&n;&t;&t;&t;&t;&t; *  1:&t;SMART selt-test supported&n;&t;&t;&t;&t;&t; *  0:&t;SMART error logging&n;&t;&t;&t;&t;&t; */
DECL|member|cfs_enable_1
r_int
r_int
id|cfs_enable_1
suffix:semicolon
multiline_comment|/* (word 85)&n;&t;&t;&t;&t;&t; * command set-feature enabled&n;&t;&t;&t;&t;&t; * 15:&t;Obsolete&n;&t;&t;&t;&t;&t; * 14:&t;NOP command&n;&t;&t;&t;&t;&t; * 13:&t;READ_BUFFER&n;&t;&t;&t;&t;&t; * 12:&t;WRITE_BUFFER&n;&t;&t;&t;&t;&t; * 11:&t;Obsolete&n;&t;&t;&t;&t;&t; * 10:&t;Host Protected Area&n;&t;&t;&t;&t;&t; *  9:&t;DEVICE Reset&n;&t;&t;&t;&t;&t; *  8:&t;SERVICE Interrupt&n;&t;&t;&t;&t;&t; *  7:&t;Release Interrupt&n;&t;&t;&t;&t;&t; *  6:&t;look-ahead&n;&t;&t;&t;&t;&t; *  5:&t;write cache&n;&t;&t;&t;&t;&t; *  4:&t;PACKET Command&n;&t;&t;&t;&t;&t; *  3:&t;Power Management Feature Set&n;&t;&t;&t;&t;&t; *  2:&t;Removable Feature Set&n;&t;&t;&t;&t;&t; *  1:&t;Security Feature Set&n;&t;&t;&t;&t;&t; *  0:&t;SMART Feature Set&n;&t;&t;&t;&t;&t; */
DECL|member|cfs_enable_2
r_int
r_int
id|cfs_enable_2
suffix:semicolon
multiline_comment|/* (word 86)&n;&t;&t;&t;&t;&t; * command set-feature enabled&n;&t;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t;&t; * 13:&t;FLUSH CACHE EXT&n;&t;&t;&t;&t;&t; * 12:&t;FLUSH CACHE&n;&t;&t;&t;&t;&t; * 11:&t;Device Configuration Overlay&n;&t;&t;&t;&t;&t; * 10:&t;48-bit Address Feature Set&n;&t;&t;&t;&t;&t; *  9:&t;Automatic Acoustic Management&n;&t;&t;&t;&t;&t; *  8:&t;SET MAX security&n;&t;&t;&t;&t;&t; *  7:&t;reserved 1407DT PARTIES&n;&t;&t;&t;&t;&t; *  6:&t;SetF sub-command Power-Up&n;&t;&t;&t;&t;&t; *  5:&t;Power-Up in Standby Feature Set&n;&t;&t;&t;&t;&t; *  4:&t;Removable Media Notification&n;&t;&t;&t;&t;&t; *  3:&t;APM Feature Set&n;&t;&t;&t;&t;&t; *  2:&t;CFA Feature Set&n;&t;&t;&t;&t;&t; *  1:&t;READ/WRITE DMA QUEUED&n;&t;&t;&t;&t;&t; *  0:&t;Download MicroCode&n;&t;&t;&t;&t;&t; */
DECL|member|csf_default
r_int
r_int
id|csf_default
suffix:semicolon
multiline_comment|/* (word 87)&n;&t;&t;&t;&t;&t; * command set-feature default&n;&t;&t;&t;&t;&t; * 15:&t;Shall be ZERO&n;&t;&t;&t;&t;&t; * 14:&t;Shall be ONE&n;&t;&t;&t;&t;&t; * 13:3&t;reserved&n;&t;&t;&t;&t;&t; *  2:&t;Media Serial Number Valid&n;&t;&t;&t;&t;&t; *  1:&t;SMART selt-test supported&n;&t;&t;&t;&t;&t; *  0:&t;SMART error logging&n;&t;&t;&t;&t;&t; */
DECL|member|dma_ultra
r_int
r_int
id|dma_ultra
suffix:semicolon
multiline_comment|/* (word 88) */
DECL|member|word89
r_int
r_int
id|word89
suffix:semicolon
multiline_comment|/* reserved (word 89) */
DECL|member|word90
r_int
r_int
id|word90
suffix:semicolon
multiline_comment|/* reserved (word 90) */
DECL|member|CurAPMvalues
r_int
r_int
id|CurAPMvalues
suffix:semicolon
multiline_comment|/* current APM values */
DECL|member|word92
r_int
r_int
id|word92
suffix:semicolon
multiline_comment|/* reserved (word 92) */
DECL|member|hw_config
r_int
r_int
id|hw_config
suffix:semicolon
multiline_comment|/* hardware config (word 93)&n;&t;&t;&t;&t;&t; * 15:&n;&t;&t;&t;&t;&t; * 14:&n;&t;&t;&t;&t;&t; * 13:&n;&t;&t;&t;&t;&t; * 12:&n;&t;&t;&t;&t;&t; * 11:&n;&t;&t;&t;&t;&t; * 10:&n;&t;&t;&t;&t;&t; *  9:&n;&t;&t;&t;&t;&t; *  8:&n;&t;&t;&t;&t;&t; *  7:&n;&t;&t;&t;&t;&t; *  6:&n;&t;&t;&t;&t;&t; *  5:&n;&t;&t;&t;&t;&t; *  4:&n;&t;&t;&t;&t;&t; *  3:&n;&t;&t;&t;&t;&t; *  2:&n;&t;&t;&t;&t;&t; *  1:&n;&t;&t;&t;&t;&t; *  0:&n;&t;&t;&t;&t;&t; */
DECL|member|acoustic
r_int
r_int
id|acoustic
suffix:semicolon
multiline_comment|/* (word 94)&n;&t;&t;&t;&t;&t; * 15:8&t;Vendor&squot;s recommended value&n;&t;&t;&t;&t;&t; *  7:0&t;current value&n;&t;&t;&t;&t;&t; */
DECL|member|words95_99
r_int
r_int
id|words95_99
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved words 95-99 */
DECL|member|lba_capacity_2
r_int
r_int
r_int
id|lba_capacity_2
suffix:semicolon
multiline_comment|/* 48-bit total number of sectors */
DECL|member|words104_125
r_int
r_int
id|words104_125
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* reserved words 104-125 */
DECL|member|last_lun
r_int
r_int
id|last_lun
suffix:semicolon
multiline_comment|/* (word 126) */
DECL|member|word127
r_int
r_int
id|word127
suffix:semicolon
multiline_comment|/* (word 127) Feature Set&n;&t;&t;&t;&t;&t; * Removable Media Notification&n;&t;&t;&t;&t;&t; * 15:2&t;reserved&n;&t;&t;&t;&t;&t; *  1:0&t;00 = not supported&n;&t;&t;&t;&t;&t; *&t;01 = supported&n;&t;&t;&t;&t;&t; *&t;10 = reserved&n;&t;&t;&t;&t;&t; *&t;11 = reserved&n;&t;&t;&t;&t;&t; */
DECL|member|dlf
r_int
r_int
id|dlf
suffix:semicolon
multiline_comment|/* (word 128)&n;&t;&t;&t;&t;&t; * device lock function&n;&t;&t;&t;&t;&t; * 15:9&t;reserved&n;&t;&t;&t;&t;&t; *  8&t;security level 1:max 0:high&n;&t;&t;&t;&t;&t; *  7:6&t;reserved&n;&t;&t;&t;&t;&t; *  5&t;enhanced erase&n;&t;&t;&t;&t;&t; *  4&t;expire&n;&t;&t;&t;&t;&t; *  3&t;frozen&n;&t;&t;&t;&t;&t; *  2&t;locked&n;&t;&t;&t;&t;&t; *  1&t;en/disabled&n;&t;&t;&t;&t;&t; *  0&t;capability&n;&t;&t;&t;&t;&t; */
DECL|member|csfo
r_int
r_int
id|csfo
suffix:semicolon
multiline_comment|/*  (word 129)&n;&t;&t;&t;&t;&t; * current set features options&n;&t;&t;&t;&t;&t; * 15:4&t;reserved&n;&t;&t;&t;&t;&t; *  3:&t;auto reassign&n;&t;&t;&t;&t;&t; *  2:&t;reverting&n;&t;&t;&t;&t;&t; *  1:&t;read-look-ahead&n;&t;&t;&t;&t;&t; *  0:&t;write cache&n;&t;&t;&t;&t;&t; */
DECL|member|words130_155
r_int
r_int
id|words130_155
(braket
l_int|26
)braket
suffix:semicolon
multiline_comment|/* reserved vendor words 130-155 */
DECL|member|word156
r_int
r_int
id|word156
suffix:semicolon
multiline_comment|/* reserved vendor word 156 */
DECL|member|words157_159
r_int
r_int
id|words157_159
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved vendor words 157-159 */
DECL|member|cfa_power
r_int
r_int
id|cfa_power
suffix:semicolon
multiline_comment|/* (word 160) CFA Power Mode&n;&t;&t;&t;&t;&t; * 15 word 160 supported&n;&t;&t;&t;&t;&t; * 14 reserved&n;&t;&t;&t;&t;&t; * 13&n;&t;&t;&t;&t;&t; * 12&n;&t;&t;&t;&t;&t; * 11:0&n;&t;&t;&t;&t;&t; */
DECL|member|words161_175
r_int
r_int
id|words161_175
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Reserved for CFA */
DECL|member|words176_205
r_int
r_int
id|words176_205
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* Current Media Serial Number */
DECL|member|words206_254
r_int
r_int
id|words206_254
(braket
l_int|48
)braket
suffix:semicolon
multiline_comment|/* reserved words 206-254 */
DECL|member|integrity_word
r_int
r_int
id|integrity_word
suffix:semicolon
multiline_comment|/* (word 255)&n;&t;&t;&t;&t;&t; * 15:8 Checksum&n;&t;&t;&t;&t;&t; *  7:0 Signature&n;&t;&t;&t;&t;&t; */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * IDE &quot;nice&quot; flags. These are used on a per drive basis to determine&n; * when to be nice and give more bandwidth to the other devices which&n; * share the same IDE bus.&n; */
DECL|macro|IDE_NICE_DSC_OVERLAP
mdefine_line|#define IDE_NICE_DSC_OVERLAP&t;(0)&t;/* per the DSC overlap protocol */
DECL|macro|IDE_NICE_ATAPI_OVERLAP
mdefine_line|#define IDE_NICE_ATAPI_OVERLAP&t;(1)&t;/* not supported yet */
macro_line|#endif&t;/* _LINUX_HDREG_H */
eof
