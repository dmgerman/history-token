macro_line|#ifndef _IDE_H
DECL|macro|_IDE_H
mdefine_line|#define _IDE_H
multiline_comment|/*&n; *  Copyright (C) 1994-2002  Linus Torvalds &amp; authors&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/hdsmart.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
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
multiline_comment|/* Right now this is only needed by a promise controlled.&n; */
macro_line|#ifndef OK_TO_RESET_CONTROLLER&t;&t;/* 1 needed for good error recovery */
DECL|macro|OK_TO_RESET_CONTROLLER
macro_line|# define OK_TO_RESET_CONTROLLER&t;0&t;/* 0 for use with AH2372A/B interface */
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
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
multiline_comment|/* used everywhere */
multiline_comment|/*&n; * Probably not wise to fiddle with these&n; */
DECL|macro|ERROR_MAX
mdefine_line|#define ERROR_MAX&t;8&t;/* Max read/write errors per sector */
DECL|macro|ERROR_RESET
mdefine_line|#define ERROR_RESET&t;3&t;/* Reset controller every 4th retry */
DECL|macro|ERROR_RECAL
mdefine_line|#define ERROR_RECAL&t;1&t;/* Recalibrate every 2nd retry */
multiline_comment|/*&n; * state flags&n; */
DECL|macro|DMA_PIO_RETRY
mdefine_line|#define DMA_PIO_RETRY&t;1&t;/* retrying in PIO */
multiline_comment|/*&n; * Definitions for accessing IDE controller registers&n; */
DECL|macro|IDE_NR_PORTS
mdefine_line|#define IDE_NR_PORTS&t;&t;(10)
DECL|macro|IDE_DATA_OFFSET
mdefine_line|#define IDE_DATA_OFFSET&t;&t;(0)
DECL|macro|IDE_ERROR_OFFSET
mdefine_line|#define IDE_ERROR_OFFSET&t;(1)
DECL|macro|IDE_NSECTOR_OFFSET
mdefine_line|#define IDE_NSECTOR_OFFSET&t;(2)
DECL|macro|IDE_SECTOR_OFFSET
mdefine_line|#define IDE_SECTOR_OFFSET&t;(3)
DECL|macro|IDE_LCYL_OFFSET
mdefine_line|#define IDE_LCYL_OFFSET&t;&t;(4)
DECL|macro|IDE_HCYL_OFFSET
mdefine_line|#define IDE_HCYL_OFFSET&t;&t;(5)
DECL|macro|IDE_SELECT_OFFSET
mdefine_line|#define IDE_SELECT_OFFSET&t;(6)
DECL|macro|IDE_STATUS_OFFSET
mdefine_line|#define IDE_STATUS_OFFSET&t;(7)
DECL|macro|IDE_CONTROL_OFFSET
mdefine_line|#define IDE_CONTROL_OFFSET&t;(8)
DECL|macro|IDE_IRQ_OFFSET
mdefine_line|#define IDE_IRQ_OFFSET&t;&t;(9)
DECL|macro|IDE_FEATURE_OFFSET
mdefine_line|#define IDE_FEATURE_OFFSET&t;IDE_ERROR_OFFSET
DECL|macro|IDE_COMMAND_OFFSET
mdefine_line|#define IDE_COMMAND_OFFSET&t;IDE_STATUS_OFFSET
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
DECL|macro|IDE_STATUS_REG
mdefine_line|#define IDE_STATUS_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_STATUS_OFFSET])
DECL|macro|IDE_CONTROL_REG
mdefine_line|#define IDE_CONTROL_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_CONTROL_OFFSET])
DECL|macro|IDE_IRQ_REG
mdefine_line|#define IDE_IRQ_REG&t;&t;(drive-&gt;channel-&gt;io_ports[IDE_IRQ_OFFSET])
DECL|macro|IDE_FEATURE_REG
mdefine_line|#define IDE_FEATURE_REG&t;&t;IDE_ERROR_REG
DECL|macro|IDE_COMMAND_REG
mdefine_line|#define IDE_COMMAND_REG&t;&t;IDE_STATUS_REG
DECL|macro|IDE_ALTSTATUS_REG
mdefine_line|#define IDE_ALTSTATUS_REG&t;IDE_CONTROL_REG
DECL|macro|IDE_IREASON_REG
mdefine_line|#define IDE_IREASON_REG&t;&t;IDE_NSECTOR_REG
DECL|macro|IDE_BCOUNTL_REG
mdefine_line|#define IDE_BCOUNTL_REG&t;&t;IDE_LCYL_REG
DECL|macro|IDE_BCOUNTH_REG
mdefine_line|#define IDE_BCOUNTH_REG&t;&t;IDE_HCYL_REG
DECL|macro|GET_ERR
mdefine_line|#define GET_ERR()&t;&t;IN_BYTE(IDE_ERROR_REG)
DECL|macro|GET_STAT
mdefine_line|#define GET_STAT()&t;&t;IN_BYTE(IDE_STATUS_REG)
DECL|macro|GET_ALTSTAT
mdefine_line|#define GET_ALTSTAT()&t;&t;IN_BYTE(IDE_CONTROL_REG)
DECL|macro|GET_FEAT
mdefine_line|#define GET_FEAT()&t;&t;IN_BYTE(IDE_NSECTOR_REG)
DECL|macro|OK_STAT
mdefine_line|#define OK_STAT(stat,good,bad)&t;(((stat)&amp;((good)|(bad)))==(good))
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
DECL|macro|SELECT_DRIVE
mdefine_line|#define SELECT_DRIVE(channel, drive)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (channel-&gt;selectproc)&t;&t;&t;&t;&bslash;&n;&t;&t;channel-&gt;selectproc(drive);&t;&t;&t;&bslash;&n;&t;OUT_BYTE((drive)-&gt;select.all, channel-&gt;io_ports[IDE_SELECT_OFFSET]); &bslash;&n;}
DECL|macro|SELECT_MASK
mdefine_line|#define SELECT_MASK(channel, drive, mask)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (channel-&gt;maskproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;channel-&gt;maskproc(drive,mask);&t;&t;&t;&bslash;&n;}
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
id|ide_ack_intr_t
op_star
id|ack_intr
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
id|ide_ack_intr_t
op_star
id|ack_intr
comma
r_int
id|irq
)paren
suffix:semicolon
macro_line|#include &lt;asm/ide.h&gt;
multiline_comment|/* Currently only m68k, apus and m8xx need it */
macro_line|#ifdef ATA_ARCH_ACK_INTR
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
DECL|member|bit0
r_int
id|bit0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nIEN
r_int
id|nIEN
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device INTRQ to host */
DECL|member|SRST
r_int
id|SRST
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* host soft reset bit */
DECL|member|bit3
r_int
id|bit3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ATA-2 thingy */
DECL|member|reserved456
r_int
id|reserved456
suffix:colon
l_int|3
suffix:semicolon
DECL|member|HOB
r_int
id|HOB
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 48-bit address ordering */
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
r_int
id|HOB
suffix:colon
l_int|1
suffix:semicolon
r_int
id|reserved456
suffix:colon
l_int|3
suffix:semicolon
r_int
id|bit3
suffix:colon
l_int|1
suffix:semicolon
r_int
id|SRST
suffix:colon
l_int|1
suffix:semicolon
r_int
id|nIEN
suffix:colon
l_int|1
suffix:semicolon
r_int
id|bit0
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|control_t
)brace
id|control_t
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
multiline_comment|/* NOTE: If we had proper separation between channel and host chip, we&n;&t; * could move this to the channel and many sync problems would&n;&t; * magically just go away.&n;&t; */
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
DECL|member|sleep
r_int
r_int
id|sleep
suffix:semicolon
multiline_comment|/* sleep until this time */
DECL|member|retry_pio
id|byte
id|retry_pio
suffix:semicolon
multiline_comment|/* retrying dma capable host in pio */
DECL|member|state
id|byte
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
DECL|member|waiting_for_dma
r_int
id|waiting_for_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dma currently in progress */
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
DECL|member|remap_0_to_1
r_int
id|remap_0_to_1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 0=remap if ezdrive, 1=remap, 2=noremap */
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
id|byte
id|scsi
suffix:semicolon
multiline_comment|/* 0=default, 1=skip current ide-subdriver for ide-scsi emulation */
DECL|member|select
id|select_t
id|select
suffix:semicolon
multiline_comment|/* basic drive/head select reg value */
DECL|member|ctl
id|byte
id|ctl
suffix:semicolon
multiline_comment|/* &quot;normal&quot; value for IDE_CONTROL_REG */
DECL|member|ready_stat
id|byte
id|ready_stat
suffix:semicolon
multiline_comment|/* min status value for drive ready */
DECL|member|mult_count
id|byte
id|mult_count
suffix:semicolon
multiline_comment|/* current multiple sector setting */
DECL|member|bad_wstat
id|byte
id|bad_wstat
suffix:semicolon
multiline_comment|/* used for ignoring WRERR_STAT */
DECL|member|nowerr
id|byte
id|nowerr
suffix:semicolon
multiline_comment|/* used for ignoring WRERR_STAT */
DECL|member|sect0
id|byte
id|sect0
suffix:semicolon
multiline_comment|/* offset of first sector for DM6:DDO */
DECL|member|head
id|byte
id|head
suffix:semicolon
multiline_comment|/* &quot;real&quot; number of heads */
DECL|member|sect
id|byte
id|sect
suffix:semicolon
multiline_comment|/* &quot;real&quot; sectors per track */
DECL|member|bios_head
id|byte
id|bios_head
suffix:semicolon
multiline_comment|/* BIOS/fdisk/LILO number of heads */
DECL|member|bios_sect
id|byte
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
id|byte
id|quirk_list
suffix:semicolon
multiline_comment|/* drive is considered quirky if set for a specific host */
DECL|member|suspend_reset
id|byte
id|suspend_reset
suffix:semicolon
multiline_comment|/* drive suspend mode flag, soft-reset recovers */
DECL|member|init_speed
id|byte
id|init_speed
suffix:semicolon
multiline_comment|/* transfer rate set at boot */
DECL|member|current_speed
id|byte
id|current_speed
suffix:semicolon
multiline_comment|/* current transfer rate set */
DECL|member|dn
id|byte
id|dn
suffix:semicolon
multiline_comment|/* now wide spread use */
DECL|member|wcache
id|byte
id|wcache
suffix:semicolon
multiline_comment|/* status of write cache */
DECL|member|acoustic
id|byte
id|acoustic
suffix:semicolon
multiline_comment|/* acoustic management */
DECL|member|queue_depth
id|byte
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
DECL|member|device
r_struct
id|device
id|device
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
DECL|enumerator|ide_stopped
id|ide_stopped
comma
multiline_comment|/* no drive operation was started */
DECL|enumerator|ide_started
id|ide_started
comma
multiline_comment|/* a drive operation was started, and a handler was set */
DECL|enumerator|ide_released
id|ide_released
multiline_comment|/* started and released bus */
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
r_int
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
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* failsafe timer */
DECL|member|expiry
r_int
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
multiline_comment|/* setup disk on a channel for a particular transfer mode */
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
id|byte
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
id|byte
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
comma
r_int
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
DECL|member|XXX_udma
r_int
(paren
op_star
id|XXX_udma
)paren
(paren
r_struct
id|ata_device
op_star
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
r_int
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
id|rq
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
DECL|member|udma_read
r_int
(paren
op_star
id|udma_read
)paren
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
DECL|member|udma_write
r_int
(paren
op_star
id|udma_write
)paren
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
DECL|member|bus_state
r_int
r_char
id|bus_state
suffix:semicolon
multiline_comment|/* power state of the IDE bus */
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
comma
r_struct
id|ata_channel
op_star
op_star
id|hwifp
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
id|hwif
)paren
suffix:semicolon
r_struct
id|ata_taskfile
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
macro_line|#include &lt;linux/blk.h&gt;
r_extern
r_int
id|__ide_end_request
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
r_int
id|ide_end_request
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used on exit from the driver, to designate the next irq handler&n; * and also to start the safety timer.&n; */
r_extern
r_void
id|ide_set_handler
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
multiline_comment|/*&n; * Error reporting, in human readable form (luxurious, but a memory hog).&n; */
r_extern
id|u8
id|ide_dump_status
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
comma
id|u8
)paren
suffix:semicolon
r_extern
id|ide_startstop_t
id|ide_error
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
comma
id|byte
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_fixstring() cleans up and (optionally) byte-swaps a text string,&n; * removing leading/trailing blanks and compressing internal blanks.&n; * It is primarily used to tidy up the model name/number fields as&n; * returned by the WIN_[P]IDENTIFY commands.&n; */
r_void
id|ide_fixstring
c_func
(paren
id|byte
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
multiline_comment|/*&n; * This routine busy-waits for the drive status to be not &quot;busy&quot;.&n; * It then checks the status for all of the &quot;good&quot; bits and none&n; * of the &quot;bad&quot; bits, and if all is okay it returns 0.  All other&n; * cases return 1 after doing &quot;*startstop = ide_error()&quot;, and the&n; * caller should return the updated value of &quot;startstop&quot; in this case.&n; * &quot;startstop&quot; is unchanged when the function returns 0;&n; */
r_extern
r_int
id|ide_wait_stat
c_func
(paren
id|ide_startstop_t
op_star
comma
r_struct
id|ata_device
op_star
comma
r_struct
id|request
op_star
id|rq
comma
id|byte
comma
id|byte
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ide_wait_noerr
c_func
(paren
r_struct
id|ata_device
op_star
comma
id|byte
comma
id|byte
comma
r_int
r_int
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
multiline_comment|/*&n; * Re-Start an operation for an IDE interface.&n; * The caller should return immediately after invoking this.&n; */
id|ide_startstop_t
id|restart_request
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This function is intended to be used prior to invoking ide_do_drive_cmd().&n; */
r_extern
r_void
id|ide_init_drive_cmd
c_func
(paren
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n; * &quot;action&quot; parameter type for ide_do_drive_cmd() below.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ide_wait
id|ide_wait
comma
multiline_comment|/* insert rq at end of list, and wait for it */
DECL|enumerator|ide_preempt
id|ide_preempt
comma
multiline_comment|/* insert rq in front of current request */
DECL|enumerator|ide_end
id|ide_end
multiline_comment|/* insert rq at end of list, but don&squot;t wait for it */
DECL|typedef|ide_action_t
)brace
id|ide_action_t
suffix:semicolon
multiline_comment|/*&n; * temporarily mapping a (possible) highmem bio for PIO transfer&n; */
DECL|macro|ide_rq_offset
mdefine_line|#define ide_rq_offset(rq) (((rq)-&gt;hard_cur_sectors - (rq)-&gt;current_nr_sectors) &lt;&lt; 9)
r_extern
r_int
id|ide_do_drive_cmd
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
id|ide_action_t
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up after success/failure of an explicit drive cmd.&n; */
r_extern
r_void
id|ide_end_drive_cmd
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
id|u8
comma
id|u8
)paren
suffix:semicolon
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
id|hd_drive_hob_hdr
id|hobfile
suffix:semicolon
DECL|member|command_type
r_int
id|command_type
suffix:semicolon
DECL|member|prehandler
id|ide_startstop_t
(paren
op_star
id|prehandler
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
id|ide_startstop_t
id|ata_taskfile
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
r_struct
id|request
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Special Flagged Register Validation Caller&n; */
r_extern
id|ide_startstop_t
id|recal_intr
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
id|ide_startstop_t
id|task_no_data_intr
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
multiline_comment|/* This is setting up all fields in args, which depend upon the command type.&n; */
r_extern
r_void
id|ide_cmd_type_parser
c_func
(paren
r_struct
id|ata_taskfile
op_star
id|args
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
)paren
suffix:semicolon
r_extern
r_int
id|ide_cmd_ioctl
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_void
id|ide_delay_50ms
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
suffix:semicolon
r_extern
r_int
id|ide_driveid_update
c_func
(paren
r_struct
id|ata_device
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
id|byte
)paren
suffix:semicolon
r_extern
id|byte
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
r_extern
r_void
id|ide_stall_queue
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
r_int
id|ide_spin_wait_hwgroup
c_func
(paren
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
r_void
id|ide_timer_expiry
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
r_void
id|do_ide_request
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_void
id|ide_init_subdrivers
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
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
r_extern
r_int
id|ide_cdrom_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDETAPE
r_extern
r_int
id|idetape_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDEFLOPPY
r_extern
r_int
id|idefloppy_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDESCSI
r_extern
r_int
id|idescsi_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|ide_register_subdriver
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
id|ide_unregister_subdriver
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
r_int
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
r_return
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
r_return
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_stop
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|udma_read
r_static
r_inline
r_int
id|udma_read
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
r_return
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_read
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|udma_write
r_static
r_inline
r_int
id|udma_write
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
r_return
id|drive-&gt;channel
op_member_access_from_pointer
id|udma_write
c_func
(paren
id|drive
comma
id|rq
)paren
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
r_return
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
r_return
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
r_int
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
r_int
id|udma_pci_read
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
r_int
id|udma_pci_write
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
id|udma_new_table
c_func
(paren
r_struct
id|ata_channel
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
r_int
id|ata_do_udma
c_func
(paren
r_int
r_int
id|reading
comma
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
id|ide_startstop_t
id|udma_tcq_taskfile
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
r_int
id|XXX_ide_dmaproc
c_func
(paren
r_struct
id|ata_device
op_star
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
id|spinlock_t
id|ide_lock
suffix:semicolon
DECL|macro|DRIVE_LOCK
mdefine_line|#define DRIVE_LOCK(drive)&t;&t;((drive)-&gt;queue.queue_lock)
r_extern
r_int
id|drive_is_ready
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
macro_line|#endif
eof
