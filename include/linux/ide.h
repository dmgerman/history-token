macro_line|#ifndef _IDE_H
DECL|macro|_IDE_H
mdefine_line|#define _IDE_H
multiline_comment|/*&n; *  linux/include/linux/ide.h&n; *&n; *  Copyright (C) 1994-1998  Linus Torvalds &amp; authors&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/hdsmart.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/hdreg.h&gt;
multiline_comment|/*&n; * This is the multiple IDE interface driver, as evolved from hd.c.&n; * It supports up to four IDE interfaces, on one or more IRQs (usually 14 &amp; 15).&n; * There can be up to two drives per interface, as per the ATA-2 spec.&n; *&n; * Primary i/f:    ide0: major=3;  (hda)         minor=0; (hdb)         minor=64&n; * Secondary i/f:  ide1: major=22; (hdc or hd1a) minor=0; (hdd or hd1b) minor=64&n; * Tertiary i/f:   ide2: major=33; (hde)         minor=0; (hdf)         minor=64&n; * Quaternary i/f: ide3: major=34; (hdg)         minor=0; (hdh)         minor=64&n; */
multiline_comment|/******************************************************************************&n; * IDE driver configuration options (play with these as desired):&n; *&n; * REALLY_SLOW_IO can be defined in ide.c and ide-cd.c, if necessary&n; */
DECL|macro|REALLY_FAST_IO
macro_line|#undef REALLY_FAST_IO&t;&t;&t;/* define if ide ports are perfect */
DECL|macro|INITIAL_MULT_COUNT
mdefine_line|#define INITIAL_MULT_COUNT&t;0&t;/* off=0; on=2,4,8,16,32, etc.. */
macro_line|#ifndef SUPPORT_SLOW_DATA_PORTS&t;&t;/* 1 to support slow data ports */
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef SUPPORT_VLB_SYNC&t;&t;/* 1 to support weird 32-bit chips */
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifndef DISK_RECOVERY_TIME&t;&t;/* off=0; on=access_delay_time */
DECL|macro|DISK_RECOVERY_TIME
mdefine_line|#define DISK_RECOVERY_TIME&t;0&t;/*  for hardware that needs it */
macro_line|#endif
macro_line|#ifndef OK_TO_RESET_CONTROLLER&t;&t;/* 1 needed for good error recovery */
DECL|macro|OK_TO_RESET_CONTROLLER
mdefine_line|#define OK_TO_RESET_CONTROLLER&t;1&t;/* 0 for use with AH2372A/B interface */
macro_line|#endif
macro_line|#ifndef FANCY_STATUS_DUMPS&t;&t;/* 1 for human-readable drive errors */
DECL|macro|FANCY_STATUS_DUMPS
mdefine_line|#define FANCY_STATUS_DUMPS&t;1&t;/* 0 to reduce kernel size */
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_CMD640
macro_line|#if 0&t;/* change to 1 when debugging cmd640 problems */
r_void
id|cmd640_dump_regs
(paren
r_void
)paren
suffix:semicolon
mdefine_line|#define CMD640_DUMP_REGS cmd640_dump_regs() /* for debugging cmd640 chipset */
macro_line|#endif
macro_line|#endif  /* CONFIG_BLK_DEV_CMD640 */
macro_line|#ifndef DISABLE_IRQ_NOSYNC
DECL|macro|DISABLE_IRQ_NOSYNC
mdefine_line|#define DISABLE_IRQ_NOSYNC&t;0
macro_line|#endif
multiline_comment|/*&n; * IDE_DRIVE_CMD is used to implement many features of the hdparm utility&n; */
DECL|macro|IDE_DRIVE_CMD
mdefine_line|#define IDE_DRIVE_CMD&t;&t;99&t;/* (magic) undef to reduce kernel size*/
multiline_comment|/*&n; * IDE_DRIVE_TASK is used to implement many features needed for raw tasks&n; */
DECL|macro|IDE_DRIVE_TASK
mdefine_line|#define IDE_DRIVE_TASK&t;&t;98
DECL|macro|IDE_DRIVE_CMD_AEB
mdefine_line|#define IDE_DRIVE_CMD_AEB&t;98
multiline_comment|/*&n; *  &quot;No user-serviceable parts&quot; beyond this point  :)&n; *****************************************************************************/
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
multiline_comment|/*&n; * Ensure that various configuration flags have compatible settings&n; */
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|REALLY_FAST_IO
macro_line|#undef REALLY_FAST_IO
macro_line|#endif
DECL|macro|HWIF
mdefine_line|#define HWIF(drive)&t;&t;((ide_hwif_t *)((drive)-&gt;hwif))
DECL|macro|HWGROUP
mdefine_line|#define HWGROUP(drive)&t;&t;((ide_hwgroup_t *)(HWIF(drive)-&gt;hwgroup))
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
mdefine_line|#define IDE_DATA_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_DATA_OFFSET])
DECL|macro|IDE_ERROR_REG
mdefine_line|#define IDE_ERROR_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_ERROR_OFFSET])
DECL|macro|IDE_NSECTOR_REG
mdefine_line|#define IDE_NSECTOR_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_NSECTOR_OFFSET])
DECL|macro|IDE_SECTOR_REG
mdefine_line|#define IDE_SECTOR_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_SECTOR_OFFSET])
DECL|macro|IDE_LCYL_REG
mdefine_line|#define IDE_LCYL_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_LCYL_OFFSET])
DECL|macro|IDE_HCYL_REG
mdefine_line|#define IDE_HCYL_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_HCYL_OFFSET])
DECL|macro|IDE_SELECT_REG
mdefine_line|#define IDE_SELECT_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_SELECT_OFFSET])
DECL|macro|IDE_STATUS_REG
mdefine_line|#define IDE_STATUS_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_STATUS_OFFSET])
DECL|macro|IDE_CONTROL_REG
mdefine_line|#define IDE_CONTROL_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_CONTROL_OFFSET])
DECL|macro|IDE_IRQ_REG
mdefine_line|#define IDE_IRQ_REG&t;&t;(HWIF(drive)-&gt;io_ports[IDE_IRQ_OFFSET])
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
DECL|macro|SECTOR_WORDS
mdefine_line|#define SECTOR_WORDS&t;(512 / 4)&t;/* number of 32bit words per sector */
DECL|macro|IDE_LARGE_SEEK
mdefine_line|#define IDE_LARGE_SEEK(b1,b2,t)&t;(((b1) &gt; (b2) + (t)) || ((b2) &gt; (b1) + (t)))
DECL|macro|IDE_MIN
mdefine_line|#define IDE_MIN(a,b)&t;((a)&lt;(b) ? (a):(b))
DECL|macro|IDE_MAX
mdefine_line|#define IDE_MAX(a,b)&t;((a)&gt;(b) ? (a):(b))
multiline_comment|/*&n; * Timeouts for various operations:&n; */
DECL|macro|WAIT_DRQ
mdefine_line|#define WAIT_DRQ&t;(5*HZ/100)&t;/* 50msec - spec allows up to 20ms */
macro_line|#if defined(CONFIG_APM) || defined(CONFIG_APM_MODULE)
DECL|macro|WAIT_READY
mdefine_line|#define WAIT_READY&t;(5*HZ)&t;&t;/* 5sec - some laptops are very slow */
macro_line|#else
DECL|macro|WAIT_READY
mdefine_line|#define WAIT_READY&t;(3*HZ/100)&t;/* 30msec - should be instantaneous */
macro_line|#endif /* CONFIG_APM || CONFIG_APM_MODULE */
DECL|macro|WAIT_PIDENTIFY
mdefine_line|#define WAIT_PIDENTIFY&t;(10*HZ)&t;/* 10sec  - should be less than 3ms (?)&n;&t;&t;&t;&t;            if all ATAPI CD is closed at boot */
DECL|macro|WAIT_WORSTCASE
mdefine_line|#define WAIT_WORSTCASE&t;(30*HZ)&t;/* 30sec  - worst case when spinning up */
DECL|macro|WAIT_CMD
mdefine_line|#define WAIT_CMD&t;(10*HZ)&t;/* 10sec  - maximum wait for an IRQ to happen */
DECL|macro|WAIT_MIN_SLEEP
mdefine_line|#define WAIT_MIN_SLEEP&t;(2*HZ/100)&t;/* 20msec - minimum sleep time */
DECL|macro|SELECT_DRIVE
mdefine_line|#define SELECT_DRIVE(hwif,drive)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;selectproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hwif-&gt;selectproc(drive);&t;&t;&t;&bslash;&n;&t;OUT_BYTE((drive)-&gt;select.all, hwif-&gt;io_ports[IDE_SELECT_OFFSET]); &bslash;&n;}
DECL|macro|SELECT_INTERRUPT
mdefine_line|#define SELECT_INTERRUPT(hwif,drive)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;intrproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hwif-&gt;intrproc(drive);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;OUT_BYTE((drive)-&gt;ctl|2, hwif-&gt;io_ports[IDE_CONTROL_OFFSET]);&t;&bslash;&n;}
DECL|macro|SELECT_MASK
mdefine_line|#define SELECT_MASK(hwif,drive,mask)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;maskproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hwif-&gt;maskproc(drive,mask);&t;&t;&t;&bslash;&n;}
DECL|macro|SELECT_READ_WRITE
mdefine_line|#define SELECT_READ_WRITE(hwif,drive,func)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;rwproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hwif-&gt;rwproc(drive,func);&t;&t;&t;&bslash;&n;}
DECL|macro|QUIRK_LIST
mdefine_line|#define QUIRK_LIST(hwif,drive)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;quirkproc)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(drive)-&gt;quirk_list = hwif-&gt;quirkproc(drive);&t;&bslash;&n;}
DECL|macro|IDE_DEBUG
mdefine_line|#define IDE_DEBUG(lineno) &bslash;&n;&t;printk(&quot;%s,%s,line=%d&bslash;n&quot;, __FILE__, __FUNCTION__, (lineno))
multiline_comment|/*&n; * Check for an interrupt and acknowledge the interrupt status&n; */
r_struct
id|hwif_s
suffix:semicolon
DECL|typedef|ide_ack_intr_t
r_typedef
r_int
(paren
id|ide_ack_intr_t
)paren
(paren
r_struct
id|hwif_s
op_star
)paren
suffix:semicolon
macro_line|#ifndef NO_DMA
DECL|macro|NO_DMA
mdefine_line|#define NO_DMA  255
macro_line|#endif
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
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* interface specific data */
DECL|typedef|hw_regs_t
)brace
id|hw_regs_t
suffix:semicolon
multiline_comment|/*&n; * Register new hardware with ide&n; */
r_int
id|ide_register_hw
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_struct
id|hwif_s
op_star
op_star
id|hwifp
)paren
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
multiline_comment|/*&n; * If the arch-dependant ide.h did not declare/define any OUT_BYTE&n; * or IN_BYTE functions, we make some defaults here.&n; */
macro_line|#ifndef HAVE_ARCH_OUT_BYTE
macro_line|#ifdef REALLY_FAST_IO
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)          outb((b),(p))
macro_line|#else
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)          outb_p((b),(p))
macro_line|#endif
macro_line|#endif
macro_line|#ifndef HAVE_ARCH_IN_BYTE
macro_line|#ifdef REALLY_FAST_IO
DECL|macro|IN_BYTE
mdefine_line|#define IN_BYTE(p)             (byte)inb_p(p)
macro_line|#else
DECL|macro|IN_BYTE
mdefine_line|#define IN_BYTE(p)             (byte)inb(p)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Now for the data we need to maintain per-drive:  ide_drive_t&n; */
DECL|macro|ide_scsi
mdefine_line|#define ide_scsi&t;0x21
DECL|macro|ide_disk
mdefine_line|#define ide_disk&t;0x20
DECL|macro|ide_optical
mdefine_line|#define ide_optical&t;0x7
DECL|macro|ide_cdrom
mdefine_line|#define ide_cdrom&t;0x5
DECL|macro|ide_tape
mdefine_line|#define ide_tape&t;0x1
DECL|macro|ide_floppy
mdefine_line|#define ide_floppy&t;0x0
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
DECL|member|set_geometry
r_int
id|set_geometry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* respecify drive geometry */
DECL|member|recalibrate
r_int
id|recalibrate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* seek to cyl 0      */
DECL|member|set_multmode
r_int
id|set_multmode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set multmode count */
DECL|member|set_tune
r_int
id|set_tune
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tune interface for drive */
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* unused */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|special_t
)brace
id|special_t
suffix:semicolon
DECL|struct|ide_drive_s
r_typedef
r_struct
id|ide_drive_s
(brace
DECL|member|queue
id|request_queue_t
id|queue
suffix:semicolon
multiline_comment|/* request queue */
DECL|member|next
r_struct
id|ide_drive_s
op_star
id|next
suffix:semicolon
multiline_comment|/* circular list of hwgroup drives */
DECL|member|sleep
r_int
r_int
id|sleep
suffix:semicolon
multiline_comment|/* sleep until this time */
DECL|member|service_start
r_int
r_int
id|service_start
suffix:semicolon
multiline_comment|/* time we started last request */
DECL|member|service_time
r_int
r_int
id|service_time
suffix:semicolon
multiline_comment|/* service time of last request */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* max time to wait for irq */
DECL|member|special
id|special_t
id|special
suffix:semicolon
multiline_comment|/* special action flags */
DECL|member|keep_settings
id|byte
id|keep_settings
suffix:semicolon
multiline_comment|/* restore settings after drive reset */
DECL|member|using_dma
id|byte
id|using_dma
suffix:semicolon
multiline_comment|/* disk is using dma for read/write */
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
DECL|member|waiting_for_dma
id|byte
id|waiting_for_dma
suffix:semicolon
multiline_comment|/* dma currently in progress */
DECL|member|unmask
id|byte
id|unmask
suffix:semicolon
multiline_comment|/* flag: okay to unmask other irqs */
DECL|member|slow
id|byte
id|slow
suffix:semicolon
multiline_comment|/* flag: slow data port */
DECL|member|bswap
id|byte
id|bswap
suffix:semicolon
multiline_comment|/* flag: byte swap data */
DECL|member|dsc_overlap
id|byte
id|dsc_overlap
suffix:semicolon
multiline_comment|/* flag: DSC overlap */
DECL|member|nice1
id|byte
id|nice1
suffix:semicolon
multiline_comment|/* flag: give potential excess bandwidth */
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
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* currently doing revalidate_disk() */
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
DECL|member|no_unmask
r_int
id|no_unmask
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disallow setting unmask bit */
DECL|member|no_io_32bit
r_int
id|no_io_32bit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disallow enabling 32bit I/O */
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
DECL|member|nice0
r_int
id|nice0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: give obvious excess bandwidth */
DECL|member|nice2
r_int
id|nice2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: give a share in our own bandwidth */
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
DECL|member|scsi
id|byte
id|scsi
suffix:semicolon
multiline_comment|/* 0=default, 1=skip current ide-subdriver for ide-scsi emulation */
DECL|member|media
id|byte
id|media
suffix:semicolon
multiline_comment|/* disk, cdrom, tape, floppy, ... */
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
DECL|member|mult_req
id|byte
id|mult_req
suffix:semicolon
multiline_comment|/* requested multiple sector setting */
DECL|member|tune_req
id|byte
id|tune_req
suffix:semicolon
multiline_comment|/* requested drive tuning setting */
DECL|member|io_32bit
id|byte
id|io_32bit
suffix:semicolon
multiline_comment|/* 0=16-bit, 1=32-bit, 2/3=32bit+sync */
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
DECL|member|usage
id|byte
id|usage
suffix:semicolon
multiline_comment|/* current &quot;open()&quot; count for drive */
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
r_int
r_int
id|capacity
suffix:semicolon
multiline_comment|/* total number of sectors */
DECL|member|drive_data
r_int
r_int
id|drive_data
suffix:semicolon
multiline_comment|/* for use by tuneproc/selectproc as needed */
DECL|member|hwif
r_void
op_star
id|hwif
suffix:semicolon
multiline_comment|/* actually (ide_hwif_t *) */
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
DECL|member|name
r_char
id|name
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* drive name, such as &quot;hda&quot; */
DECL|member|driver
r_void
op_star
id|driver
suffix:semicolon
multiline_comment|/* (ide_driver_t *) */
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
DECL|member|proc
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
multiline_comment|/* /proc/ide/ directory entry */
DECL|member|settings
r_void
op_star
id|settings
suffix:semicolon
multiline_comment|/* /proc/ide/ drive settings */
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
DECL|typedef|ide_drive_t
)brace
id|ide_drive_t
suffix:semicolon
multiline_comment|/*&n; * An ide_dmaproc_t() initiates/aborts DMA read/write operations on a drive.&n; *&n; * The caller is assumed to have selected the drive and programmed the drive&squot;s&n; * sector address using CHS or LBA.  All that remains is to prepare for DMA&n; * and then issue the actual read/write DMA/PIO command to the drive.&n; *&n; * Returns 0 if all went well.&n; * Returns 1 if DMA read/write could not be started, in which case the caller&n; * should either try again later, or revert to PIO for the current request.&n; */
DECL|enumerator|ide_dma_read
DECL|enumerator|ide_dma_write
DECL|enumerator|ide_dma_begin
r_typedef
r_enum
(brace
id|ide_dma_read
comma
id|ide_dma_write
comma
id|ide_dma_begin
comma
DECL|enumerator|ide_dma_end
DECL|enumerator|ide_dma_check
DECL|enumerator|ide_dma_on
id|ide_dma_end
comma
id|ide_dma_check
comma
id|ide_dma_on
comma
DECL|enumerator|ide_dma_off
DECL|enumerator|ide_dma_off_quietly
DECL|enumerator|ide_dma_test_irq
id|ide_dma_off
comma
id|ide_dma_off_quietly
comma
id|ide_dma_test_irq
comma
DECL|enumerator|ide_dma_bad_drive
DECL|enumerator|ide_dma_good_drive
id|ide_dma_bad_drive
comma
id|ide_dma_good_drive
comma
DECL|enumerator|ide_dma_verbose
DECL|enumerator|ide_dma_retune
id|ide_dma_verbose
comma
id|ide_dma_retune
comma
DECL|enumerator|ide_dma_lostirq
DECL|enumerator|ide_dma_timeout
id|ide_dma_lostirq
comma
id|ide_dma_timeout
DECL|typedef|ide_dma_action_t
)brace
id|ide_dma_action_t
suffix:semicolon
DECL|typedef|ide_dmaproc_t
r_typedef
r_int
(paren
id|ide_dmaproc_t
)paren
(paren
id|ide_dma_action_t
comma
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * An ide_ideproc_t() performs CPU-polled transfers to/from a drive.&n; * Arguments are: the drive, the buffer pointer, and the length (in bytes or&n; * words depending on if it&squot;s an IDE or ATAPI call).&n; *&n; * If it is not defined for a controller, standard-code is used from ide.c.&n; *&n; * Controllers which are not memory-mapped in the standard way need to &n; * override that mechanism using this function to work.&n; *&n; */
DECL|enumerator|ideproc_ide_input_data
DECL|enumerator|ideproc_ide_output_data
r_typedef
r_enum
(brace
id|ideproc_ide_input_data
comma
id|ideproc_ide_output_data
comma
DECL|enumerator|ideproc_atapi_input_bytes
DECL|enumerator|ideproc_atapi_output_bytes
id|ideproc_atapi_input_bytes
comma
id|ideproc_atapi_output_bytes
DECL|typedef|ide_ide_action_t
)brace
id|ide_ide_action_t
suffix:semicolon
DECL|typedef|ide_ideproc_t
r_typedef
r_void
(paren
id|ide_ideproc_t
)paren
(paren
id|ide_ide_action_t
comma
id|ide_drive_t
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * An ide_tuneproc_t() is used to set the speed of an IDE interface&n; * to a particular PIO mode.  The &quot;byte&quot; parameter is used&n; * to select the PIO mode by number (0,1,2,3,4,5), and a value of 255&n; * indicates that the interface driver should &quot;auto-tune&quot; the PIO mode&n; * according to the drive capabilities in drive-&gt;id;&n; *&n; * Not all interface types support tuning, and not all of those&n; * support all possible PIO settings.  They may silently ignore&n; * or round values as they see fit.&n; */
DECL|typedef|ide_tuneproc_t
r_typedef
r_void
(paren
id|ide_tuneproc_t
)paren
(paren
id|ide_drive_t
op_star
comma
id|byte
)paren
suffix:semicolon
DECL|typedef|ide_speedproc_t
r_typedef
r_int
(paren
id|ide_speedproc_t
)paren
(paren
id|ide_drive_t
op_star
comma
id|byte
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used to provide support for strange interfaces&n; */
DECL|typedef|ide_selectproc_t
r_typedef
r_void
(paren
id|ide_selectproc_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_resetproc_t
r_typedef
r_void
(paren
id|ide_resetproc_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_quirkproc_t
r_typedef
r_int
(paren
id|ide_quirkproc_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_intrproc_t
r_typedef
r_void
(paren
id|ide_intrproc_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_maskproc_t
r_typedef
r_void
(paren
id|ide_maskproc_t
)paren
(paren
id|ide_drive_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|ide_rw_proc_t
r_typedef
r_void
(paren
id|ide_rw_proc_t
)paren
(paren
id|ide_drive_t
op_star
comma
id|ide_dma_action_t
)paren
suffix:semicolon
multiline_comment|/*&n; * ide soft-power support&n; */
DECL|typedef|ide_busproc_t
r_typedef
r_int
(paren
id|ide_busproc_t
)paren
(paren
r_struct
id|hwif_s
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * hwif_chipset_t is used to keep track of the specific hardware&n; * chipset used by each IDE interface, if known.&n; */
DECL|enumerator|ide_unknown
DECL|enumerator|ide_generic
DECL|enumerator|ide_pci
r_typedef
r_enum
(brace
id|ide_unknown
comma
id|ide_generic
comma
id|ide_pci
comma
DECL|enumerator|ide_cmd640
DECL|enumerator|ide_dtc2278
DECL|enumerator|ide_ali14xx
id|ide_cmd640
comma
id|ide_dtc2278
comma
id|ide_ali14xx
comma
DECL|enumerator|ide_qd6580
DECL|enumerator|ide_umc8672
DECL|enumerator|ide_ht6560b
id|ide_qd6580
comma
id|ide_umc8672
comma
id|ide_ht6560b
comma
DECL|enumerator|ide_pdc4030
DECL|enumerator|ide_rz1000
DECL|enumerator|ide_trm290
id|ide_pdc4030
comma
id|ide_rz1000
comma
id|ide_trm290
comma
DECL|enumerator|ide_cmd646
DECL|enumerator|ide_cy82c693
DECL|enumerator|ide_4drives
id|ide_cmd646
comma
id|ide_cy82c693
comma
id|ide_4drives
comma
DECL|enumerator|ide_pmac
DECL|enumerator|ide_etrax100
id|ide_pmac
comma
id|ide_etrax100
DECL|typedef|hwif_chipset_t
)brace
id|hwif_chipset_t
suffix:semicolon
DECL|macro|IDE_CHIPSET_PCI_MASK
mdefine_line|#define IDE_CHIPSET_PCI_MASK&t;&bslash;&n;    ((1&lt;&lt;ide_pci)|(1&lt;&lt;ide_cmd646)|(1&lt;&lt;ide_ali14xx))
DECL|macro|IDE_CHIPSET_IS_PCI
mdefine_line|#define IDE_CHIPSET_IS_PCI(c)&t;((IDE_CHIPSET_PCI_MASK &gt;&gt; (c)) &amp; 1)
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|struct|ide_pci_devid_s
r_typedef
r_struct
id|ide_pci_devid_s
(brace
DECL|member|vid
r_int
r_int
id|vid
suffix:semicolon
DECL|member|did
r_int
r_int
id|did
suffix:semicolon
DECL|typedef|ide_pci_devid_t
)brace
id|ide_pci_devid_t
suffix:semicolon
DECL|macro|IDE_PCI_DEVID_NULL
mdefine_line|#define IDE_PCI_DEVID_NULL&t;((ide_pci_devid_t){0,0})
DECL|macro|IDE_PCI_DEVID_EQ
mdefine_line|#define IDE_PCI_DEVID_EQ(a,b)&t;(a.vid == b.vid &amp;&amp; a.did == b.did)
macro_line|#endif /* CONFIG_BLK_DEV_IDEPCI */
DECL|struct|hwif_s
r_typedef
r_struct
id|hwif_s
(brace
DECL|member|next
r_struct
id|hwif_s
op_star
id|next
suffix:semicolon
multiline_comment|/* for linked-list in ide_hwgroup_t */
DECL|member|hwgroup
r_void
op_star
id|hwgroup
suffix:semicolon
multiline_comment|/* actually (ide_hwgroup_t *) */
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
multiline_comment|/* Hardware info */
DECL|member|drives
id|ide_drive_t
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
DECL|member|tuneproc
id|ide_tuneproc_t
op_star
id|tuneproc
suffix:semicolon
multiline_comment|/* routine to tune PIO mode for drives */
DECL|member|speedproc
id|ide_speedproc_t
op_star
id|speedproc
suffix:semicolon
multiline_comment|/* routine to retune DMA modes for drives */
DECL|member|selectproc
id|ide_selectproc_t
op_star
id|selectproc
suffix:semicolon
multiline_comment|/* tweaks hardware to select drive */
DECL|member|resetproc
id|ide_resetproc_t
op_star
id|resetproc
suffix:semicolon
multiline_comment|/* routine to reset controller after a disk reset */
DECL|member|intrproc
id|ide_intrproc_t
op_star
id|intrproc
suffix:semicolon
multiline_comment|/* special interrupt handling for shared pci interrupts */
DECL|member|maskproc
id|ide_maskproc_t
op_star
id|maskproc
suffix:semicolon
multiline_comment|/* special host masking for drive selection */
DECL|member|quirkproc
id|ide_quirkproc_t
op_star
id|quirkproc
suffix:semicolon
multiline_comment|/* check host&squot;s drive quirk list */
DECL|member|rwproc
id|ide_rw_proc_t
op_star
id|rwproc
suffix:semicolon
multiline_comment|/* adjust timing based upon rq-&gt;cmd direction */
DECL|member|ideproc
id|ide_ideproc_t
op_star
id|ideproc
suffix:semicolon
multiline_comment|/* CPU-polled transfer routine */
DECL|member|dmaproc
id|ide_dmaproc_t
op_star
id|dmaproc
suffix:semicolon
multiline_comment|/* dma read/write/abort routine */
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
DECL|member|sg_dma_active
r_int
id|sg_dma_active
suffix:semicolon
multiline_comment|/* is it in use */
DECL|member|mate
r_struct
id|hwif_s
op_star
id|mate
suffix:semicolon
multiline_comment|/* other hwif from same PCI chip */
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
id|byte
id|major
suffix:semicolon
multiline_comment|/* our major number */
DECL|member|name
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* name of interface, eg. &quot;ide0&quot; */
DECL|member|index
id|byte
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
multiline_comment|/* this interface exists */
DECL|member|serialized
r_int
id|serialized
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* serialized operation with mate hwif */
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
DECL|member|channel
id|byte
id|channel
suffix:semicolon
multiline_comment|/* for dual-port chips: 0=primary, 1=secondary */
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* for pci chipsets */
DECL|member|pci_devid
id|ide_pci_devid_t
id|pci_devid
suffix:semicolon
multiline_comment|/* for pci chipsets: {VID,DID} */
macro_line|#endif /* CONFIG_BLK_DEV_IDEPCI */
macro_line|#if (DISK_RECOVERY_TIME &gt; 0)
DECL|member|last_time
r_int
r_int
id|last_time
suffix:semicolon
multiline_comment|/* time when previous rq was done */
macro_line|#endif
DECL|member|straight8
id|byte
id|straight8
suffix:semicolon
multiline_comment|/* Alan&squot;s straight 8 check */
DECL|member|hwif_data
r_void
op_star
id|hwif_data
suffix:semicolon
multiline_comment|/* extra hwif data */
DECL|member|busproc
id|ide_busproc_t
op_star
id|busproc
suffix:semicolon
multiline_comment|/* driver soft-power interface */
DECL|member|bus_state
id|byte
id|bus_state
suffix:semicolon
multiline_comment|/* power state of the IDE bus */
DECL|typedef|ide_hwif_t
)brace
id|ide_hwif_t
suffix:semicolon
multiline_comment|/*&n; * Status returned from various ide_ functions&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ide_stopped
id|ide_stopped
comma
multiline_comment|/* no drive operation was started */
DECL|enumerator|ide_started
id|ide_started
multiline_comment|/* a drive operation was started, and a handler was set */
DECL|typedef|ide_startstop_t
)brace
id|ide_startstop_t
suffix:semicolon
multiline_comment|/*&n; *  internal ide interrupt handler type&n; */
DECL|typedef|ide_handler_t
r_typedef
id|ide_startstop_t
(paren
id|ide_handler_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * when ide_timer_expiry fires, invoke a handler of this type&n; * to decide what to do.&n; */
DECL|typedef|ide_expiry_t
r_typedef
r_int
(paren
id|ide_expiry_t
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|struct|hwgroup_s
r_typedef
r_struct
id|hwgroup_s
(brace
DECL|member|handler
id|ide_handler_t
op_star
id|handler
suffix:semicolon
multiline_comment|/* irq handler, if active */
DECL|member|busy
r_volatile
r_int
id|busy
suffix:semicolon
multiline_comment|/* BOOL: protects all fields below */
DECL|member|sleeping
r_int
id|sleeping
suffix:semicolon
multiline_comment|/* BOOL: wake us up on timer expiry */
DECL|member|drive
id|ide_drive_t
op_star
id|drive
suffix:semicolon
multiline_comment|/* current drive */
DECL|member|hwif
id|ide_hwif_t
op_star
id|hwif
suffix:semicolon
multiline_comment|/* ptr to current hwif in linked-list */
DECL|member|rq
r_struct
id|request
op_star
id|rq
suffix:semicolon
multiline_comment|/* current request */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* failsafe timer */
DECL|member|wrq
r_struct
id|request
id|wrq
suffix:semicolon
multiline_comment|/* local copy of current write rq */
DECL|member|poll_timeout
r_int
r_int
id|poll_timeout
suffix:semicolon
multiline_comment|/* timeout value during long polls */
DECL|member|expiry
id|ide_expiry_t
op_star
id|expiry
suffix:semicolon
multiline_comment|/* queried upon timeouts */
DECL|typedef|ide_hwgroup_t
)brace
id|ide_hwgroup_t
suffix:semicolon
multiline_comment|/*&n; * configurable drive settings&n; */
DECL|macro|TYPE_INT
mdefine_line|#define TYPE_INT&t;0
DECL|macro|TYPE_INTA
mdefine_line|#define TYPE_INTA&t;1
DECL|macro|TYPE_BYTE
mdefine_line|#define TYPE_BYTE&t;2
DECL|macro|TYPE_SHORT
mdefine_line|#define TYPE_SHORT&t;3
DECL|macro|SETTING_READ
mdefine_line|#define SETTING_READ&t;(1 &lt;&lt; 0)
DECL|macro|SETTING_WRITE
mdefine_line|#define SETTING_WRITE&t;(1 &lt;&lt; 1)
DECL|macro|SETTING_RW
mdefine_line|#define SETTING_RW&t;(SETTING_READ | SETTING_WRITE)
DECL|typedef|ide_procset_t
r_typedef
r_int
(paren
id|ide_procset_t
)paren
(paren
id|ide_drive_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|struct|ide_settings_s
r_typedef
r_struct
id|ide_settings_s
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|rw
r_int
id|rw
suffix:semicolon
DECL|member|read_ioctl
r_int
id|read_ioctl
suffix:semicolon
DECL|member|write_ioctl
r_int
id|write_ioctl
suffix:semicolon
DECL|member|data_type
r_int
id|data_type
suffix:semicolon
DECL|member|min
r_int
id|min
suffix:semicolon
DECL|member|max
r_int
id|max
suffix:semicolon
DECL|member|mul_factor
r_int
id|mul_factor
suffix:semicolon
DECL|member|div_factor
r_int
id|div_factor
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|set
id|ide_procset_t
op_star
id|set
suffix:semicolon
DECL|member|auto_remove
r_int
id|auto_remove
suffix:semicolon
DECL|member|next
r_struct
id|ide_settings_s
op_star
id|next
suffix:semicolon
DECL|typedef|ide_settings_t
)brace
id|ide_settings_t
suffix:semicolon
r_void
id|ide_add_setting
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
id|name
comma
r_int
id|rw
comma
r_int
id|read_ioctl
comma
r_int
id|write_ioctl
comma
r_int
id|data_type
comma
r_int
id|min
comma
r_int
id|max
comma
r_int
id|mul_factor
comma
r_int
id|div_factor
comma
r_void
op_star
id|data
comma
id|ide_procset_t
op_star
id|set
)paren
suffix:semicolon
r_void
id|ide_remove_setting
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_char
op_star
id|name
)paren
suffix:semicolon
id|ide_settings_t
op_star
id|ide_find_setting_by_name
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|ide_read_setting
c_func
(paren
id|ide_drive_t
op_star
id|t
comma
id|ide_settings_t
op_star
id|setting
)paren
suffix:semicolon
r_int
id|ide_write_setting
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|ide_settings_t
op_star
id|setting
comma
r_int
id|val
)paren
suffix:semicolon
r_void
id|ide_add_generic_settings
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n; * /proc/ide interface&n; */
r_typedef
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|read_proc
id|read_proc_t
op_star
id|read_proc
suffix:semicolon
DECL|member|write_proc
id|write_proc_t
op_star
id|write_proc
suffix:semicolon
DECL|typedef|ide_proc_entry_t
)brace
id|ide_proc_entry_t
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_void
id|proc_ide_create
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|proc_ide_destroy
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|destroy_proc_ide_drives
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_void
id|create_proc_ide_interfaces
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ide_add_proc_entries
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
id|ide_proc_entry_t
op_star
id|p
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_void
id|ide_remove_proc_entries
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
id|ide_proc_entry_t
op_star
id|p
)paren
suffix:semicolon
DECL|variable|proc_ide_read_capacity
id|read_proc_t
id|proc_ide_read_capacity
suffix:semicolon
DECL|variable|proc_ide_read_geometry
id|read_proc_t
id|proc_ide_read_geometry
suffix:semicolon
multiline_comment|/*&n; * Standard exit stuff:&n; */
DECL|macro|PROC_IDE_READ_RETURN
mdefine_line|#define PROC_IDE_READ_RETURN(page,start,off,count,eof,len) &bslash;&n;{&t;&t;&t;&t;&t;&bslash;&n;&t;len -= off;&t;&t;&t;&bslash;&n;&t;if (len &lt; count) {&t;&t;&bslash;&n;&t;&t;*eof = 1;&t;&t;&bslash;&n;&t;&t;if (len &lt;= 0)&t;&t;&bslash;&n;&t;&t;&t;return 0;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&bslash;&n;&t;&t;len = count;&t;&t;&bslash;&n;&t;*start = page + off;&t;&t;&bslash;&n;&t;return len;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|PROC_IDE_READ_RETURN
mdefine_line|#define PROC_IDE_READ_RETURN(page,start,off,count,eof,len) return 0;
macro_line|#endif
multiline_comment|/*&n; * Subdrivers support.&n; */
DECL|macro|IDE_SUBDRIVER_VERSION
mdefine_line|#define IDE_SUBDRIVER_VERSION&t;1
DECL|typedef|ide_cleanup_proc
r_typedef
r_int
(paren
id|ide_cleanup_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_do_request_proc
r_typedef
id|ide_startstop_t
(paren
id|ide_do_request_proc
)paren
(paren
id|ide_drive_t
op_star
comma
r_struct
id|request
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ide_end_request_proc
r_typedef
r_void
(paren
id|ide_end_request_proc
)paren
(paren
id|byte
comma
id|ide_hwgroup_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_ioctl_proc
r_typedef
r_int
(paren
id|ide_ioctl_proc
)paren
(paren
id|ide_drive_t
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
DECL|typedef|ide_open_proc
r_typedef
r_int
(paren
id|ide_open_proc
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
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_release_proc
r_typedef
r_void
(paren
id|ide_release_proc
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
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_check_media_change_proc
r_typedef
r_int
(paren
id|ide_check_media_change_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_revalidate_proc
r_typedef
r_void
(paren
id|ide_revalidate_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_pre_reset_proc
r_typedef
r_void
(paren
id|ide_pre_reset_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_capacity_proc
r_typedef
r_int
r_int
(paren
id|ide_capacity_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_special_proc
r_typedef
id|ide_startstop_t
(paren
id|ide_special_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_setting_proc
r_typedef
r_void
(paren
id|ide_setting_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|typedef|ide_driver_reinit_proc
r_typedef
r_int
(paren
id|ide_driver_reinit_proc
)paren
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|struct|ide_driver_s
r_typedef
r_struct
id|ide_driver_s
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|version
r_const
r_char
op_star
id|version
suffix:semicolon
DECL|member|media
id|byte
id|media
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|supports_dma
r_int
id|supports_dma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|supports_dsc_overlap
r_int
id|supports_dsc_overlap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cleanup
id|ide_cleanup_proc
op_star
id|cleanup
suffix:semicolon
DECL|member|do_request
id|ide_do_request_proc
op_star
id|do_request
suffix:semicolon
DECL|member|end_request
id|ide_end_request_proc
op_star
id|end_request
suffix:semicolon
DECL|member|ioctl
id|ide_ioctl_proc
op_star
id|ioctl
suffix:semicolon
DECL|member|open
id|ide_open_proc
op_star
id|open
suffix:semicolon
DECL|member|release
id|ide_release_proc
op_star
id|release
suffix:semicolon
DECL|member|media_change
id|ide_check_media_change_proc
op_star
id|media_change
suffix:semicolon
DECL|member|revalidate
id|ide_revalidate_proc
op_star
id|revalidate
suffix:semicolon
DECL|member|pre_reset
id|ide_pre_reset_proc
op_star
id|pre_reset
suffix:semicolon
DECL|member|capacity
id|ide_capacity_proc
op_star
id|capacity
suffix:semicolon
DECL|member|special
id|ide_special_proc
op_star
id|special
suffix:semicolon
DECL|member|proc
id|ide_proc_entry_t
op_star
id|proc
suffix:semicolon
DECL|member|driver_reinit
id|ide_driver_reinit_proc
op_star
id|driver_reinit
suffix:semicolon
DECL|typedef|ide_driver_t
)brace
id|ide_driver_t
suffix:semicolon
DECL|macro|DRIVER
mdefine_line|#define DRIVER(drive)&t;&t;((ide_driver_t *)((drive)-&gt;driver))
multiline_comment|/*&n; * IDE modules.&n; */
DECL|macro|IDE_CHIPSET_MODULE
mdefine_line|#define IDE_CHIPSET_MODULE&t;&t;0&t;/* not supported yet */
DECL|macro|IDE_PROBE_MODULE
mdefine_line|#define IDE_PROBE_MODULE&t;&t;1
DECL|macro|IDE_DRIVER_MODULE
mdefine_line|#define IDE_DRIVER_MODULE&t;&t;2
DECL|typedef|ide_module_init_proc
r_typedef
r_int
(paren
id|ide_module_init_proc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|struct|ide_module_s
r_typedef
r_struct
id|ide_module_s
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|init
id|ide_module_init_proc
op_star
id|init
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|next
r_struct
id|ide_module_s
op_star
id|next
suffix:semicolon
DECL|typedef|ide_module_t
)brace
id|ide_module_t
suffix:semicolon
multiline_comment|/*&n; * ide_hwifs[] is the master data structure used to keep track&n; * of just about everything in ide.c.  Whenever possible, routines&n; * should be using pointers to a drive (ide_drive_t *) or&n; * pointers to a hwif (ide_hwif_t *), rather than indexing this&n; * structure directly (the allocation/layout may change!).&n; *&n; */
macro_line|#ifndef _IDE_C
r_extern
id|ide_hwif_t
id|ide_hwifs
(braket
)braket
suffix:semicolon
multiline_comment|/* master data repository */
r_extern
id|ide_module_t
op_star
id|ide_modules
suffix:semicolon
r_extern
id|ide_module_t
op_star
id|ide_probe
suffix:semicolon
macro_line|#endif
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
r_void
id|ide_end_request
c_func
(paren
id|byte
id|uptodate
comma
id|ide_hwgroup_t
op_star
id|hwgroup
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used for (nearly) all data transfers from/to the IDE interface&n; * FIXME for 2.5, to a pointer pass verses memcpy........&n; */
r_void
id|ide_input_data
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
suffix:semicolon
r_void
id|ide_output_data
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used for (nearly) all ATAPI data transfers from/to the IDE interface&n; * FIXME for 2.5, to a pointer pass verses memcpy........&n; */
r_void
id|atapi_input_bytes
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|bytecount
)paren
suffix:semicolon
r_void
id|atapi_output_bytes
(paren
id|ide_drive_t
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|bytecount
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used on exit from the driver, to designate the next irq handler&n; * and also to start the safety timer.&n; */
r_void
id|ide_set_handler
(paren
id|ide_drive_t
op_star
id|drive
comma
id|ide_handler_t
op_star
id|handler
comma
r_int
r_int
id|timeout
comma
id|ide_expiry_t
op_star
id|expiry
)paren
suffix:semicolon
multiline_comment|/*&n; * Error reporting, in human readable form (luxurious, but a memory hog).&n; */
id|byte
id|ide_dump_status
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
id|msg
comma
id|byte
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_error() takes action based on the error returned by the controller.&n; * The caller should return immediately after invoking this.&n; */
id|ide_startstop_t
id|ide_error
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
id|msg
comma
id|byte
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n; * Issue a simple drive command&n; * The drive must be selected beforehand.&n; */
r_void
id|ide_cmd
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|cmd
comma
id|byte
id|nsect
comma
id|ide_handler_t
op_star
id|handler
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_fixstring() cleans up and (optionally) byte-swaps a text string,&n; * removing leading/trailing blanks and compressing internal blanks.&n; * It is primarily used to tidy up the model name/number fields as&n; * returned by the WIN_[P]IDENTIFY commands.&n; */
r_void
id|ide_fixstring
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
r_int
id|ide_wait_stat
(paren
id|ide_startstop_t
op_star
id|startstop
comma
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|good
comma
id|byte
id|bad
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
r_int
id|ide_wait_noerr
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|good
comma
id|byte
id|bad
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine is called from the partition-table code in genhd.c&n; * to &quot;convert&quot; a drive to a logical geometry with fewer than 1024 cyls.&n; */
r_int
id|ide_xlate_1024
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
multiline_comment|/*&n; * Convert kdev_t structure into ide_drive_t * one.&n; */
id|ide_drive_t
op_star
id|get_info_ptr
(paren
id|kdev_t
id|i_rdev
)paren
suffix:semicolon
multiline_comment|/*&n; * Return the current idea about the total capacity of this drive.&n; */
r_int
r_int
id|current_capacity
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n; * Start a reset operation for an IDE interface.&n; * The caller should return immediately after invoking this.&n; */
id|ide_startstop_t
id|ide_do_reset
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Re-Start an operation for an IDE interface.&n; * The caller should return immediately after invoking this.&n; */
id|ide_startstop_t
id|restart_request
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This function is intended to be used prior to invoking ide_do_drive_cmd().&n; */
r_void
id|ide_init_drive_cmd
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
DECL|enumerator|ide_next
id|ide_next
comma
multiline_comment|/* insert rq immediately after current request */
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
multiline_comment|/*&n; * This function issues a special IDE device request&n; * onto the request queue.&n; *&n; * If action is ide_wait, then the rq is queued at the end of the&n; * request queue, and the function sleeps until it has been processed.&n; * This is for use when invoked from an ioctl handler.&n; *&n; * If action is ide_preempt, then the rq is queued at the head of&n; * the request queue, displacing the currently-being-processed&n; * request and this function returns immediately without waiting&n; * for the new rq to be completed.  This is VERY DANGEROUS, and is&n; * intended for careful use by the ATAPI tape/cdrom driver code.&n; *&n; * If action is ide_next, then the rq is queued immediately after&n; * the currently-being-processed-request (if any), and the function&n; * returns without waiting for the new rq to be completed.  As above,&n; * This is VERY DANGEROUS, and is intended for careful use by the&n; * ATAPI tape/cdrom driver code.&n; *&n; * If action is ide_end, then the rq is queued at the end of the&n; * request queue, and the function returns immediately without waiting&n; * for the new rq to be completed. This is again intended for careful&n; * use by the ATAPI tape/cdrom driver code.&n; */
r_int
id|ide_do_drive_cmd
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
comma
id|ide_action_t
id|action
)paren
suffix:semicolon
multiline_comment|/*&n; * Clean up after success/failure of an explicit drive cmd.&n; * stat/err are used only when (HWGROUP(drive)-&gt;rq-&gt;cmd == IDE_DRIVE_CMD).&n; */
r_void
id|ide_end_drive_cmd
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|stat
comma
id|byte
id|err
)paren
suffix:semicolon
multiline_comment|/*&n; * Issue ATA command and wait for completion.&n; */
r_int
id|ide_wait_cmd
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|cmd
comma
r_int
id|nsect
comma
r_int
id|feature
comma
r_int
id|sectors
comma
id|byte
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ide_wait_cmd_task
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
op_star
id|buf
)paren
suffix:semicolon
r_void
id|ide_delay_50ms
(paren
r_void
)paren
suffix:semicolon
r_int
id|system_bus_clock
c_func
(paren
r_void
)paren
suffix:semicolon
id|byte
id|ide_auto_reduce_xfer
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|ide_driveid_update
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|ide_ata66_check
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|cmd
comma
id|byte
id|nsect
comma
id|byte
id|feature
)paren
suffix:semicolon
r_int
id|ide_config_drive_speed
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|speed
)paren
suffix:semicolon
id|byte
id|eighty_ninty_three
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|set_transfer
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|cmd
comma
id|byte
id|nsect
comma
id|byte
id|feature
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_system_bus_speed() returns what we think is the system VESA/PCI&n; * bus speed (in MHz).  This is used for calculating interface PIO timings.&n; * The default is 40 for known PCI systems, 50 otherwise.&n; * The &quot;idebus=xx&quot; parameter can be used to override this value.&n; */
r_int
id|ide_system_bus_speed
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_multwrite() transfers a block of up to mcount sectors of data&n; * to a drive as part of a disk multwrite operation.&n; */
r_int
id|ide_multwrite
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|mcount
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_stall_queue() can be used by a drive to give excess bandwidth back&n; * to the hwgroup by sleeping for timeout jiffies.&n; */
r_void
id|ide_stall_queue
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
multiline_comment|/*&n; * ide_get_queue() returns the queue which corresponds to a given device.&n; */
id|request_queue_t
op_star
id|ide_get_queue
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * CompactFlash cards and their brethern pretend to be removable hard disks,&n; * but they never have a slave unit, and they don&squot;t have doorlock mechanisms.&n; * This test catches them, and is invoked elsewhere when setting appropriate config bits.&n; */
r_int
id|drive_is_flashcard
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|ide_spin_wait_hwgroup
(paren
id|ide_drive_t
op_star
id|drive
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
r_void
id|ide_intr
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
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
macro_line|#ifndef _IDE_C
r_extern
r_struct
id|block_device_operations
id|ide_fops
(braket
)braket
suffix:semicolon
r_extern
id|ide_proc_entry_t
id|generic_subdriver_entries
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef _IDE_C
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_int
id|ideprobe_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDE */
macro_line|#ifdef CONFIG_BLK_DEV_IDEDISK
r_int
id|idedisk_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDISK */
macro_line|#ifdef CONFIG_BLK_DEV_IDECD
r_int
id|ide_cdrom_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDECD */
macro_line|#ifdef CONFIG_BLK_DEV_IDETAPE
r_int
id|idetape_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDETAPE */
macro_line|#ifdef CONFIG_BLK_DEV_IDEFLOPPY
r_int
id|idefloppy_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEFLOPPY */
macro_line|#ifdef CONFIG_BLK_DEV_IDESCSI
r_int
id|idescsi_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDESCSI */
macro_line|#endif /* _IDE_C */
r_int
id|ide_register_module
(paren
id|ide_module_t
op_star
id|module
)paren
suffix:semicolon
r_void
id|ide_unregister_module
(paren
id|ide_module_t
op_star
id|module
)paren
suffix:semicolon
id|ide_drive_t
op_star
id|ide_scan_devices
(paren
id|byte
id|media
comma
r_const
r_char
op_star
id|name
comma
id|ide_driver_t
op_star
id|driver
comma
r_int
id|n
)paren
suffix:semicolon
r_int
id|ide_register_subdriver
(paren
id|ide_drive_t
op_star
id|drive
comma
id|ide_driver_t
op_star
id|driver
comma
r_int
id|version
)paren
suffix:semicolon
r_int
id|ide_unregister_subdriver
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|ide_replace_subdriver
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
id|driver
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|macro|ON_BOARD
mdefine_line|#define ON_BOARD&t;&t;1
DECL|macro|NEVER_BOARD
mdefine_line|#define NEVER_BOARD&t;&t;0
macro_line|#ifdef CONFIG_BLK_DEV_OFFBOARD
DECL|macro|OFF_BOARD
macro_line|#  define OFF_BOARD&t;&t;ON_BOARD
macro_line|#else /* CONFIG_BLK_DEV_OFFBOARD */
DECL|macro|OFF_BOARD
macro_line|#  define OFF_BOARD&t;&t;NEVER_BOARD
macro_line|#endif /* CONFIG_BLK_DEV_OFFBOARD */
r_int
r_int
id|ide_find_free_region
(paren
r_int
r_int
id|size
)paren
id|__init
suffix:semicolon
r_void
id|ide_scan_pcibus
(paren
r_int
id|scan_direction
)paren
id|__init
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
DECL|macro|BAD_DMA_DRIVE
mdefine_line|#define BAD_DMA_DRIVE&t;&t;0
DECL|macro|GOOD_DMA_DRIVE
mdefine_line|#define GOOD_DMA_DRIVE&t;&t;1
r_int
id|ide_build_dmatable
(paren
id|ide_drive_t
op_star
id|drive
comma
id|ide_dma_action_t
id|func
)paren
suffix:semicolon
r_void
id|ide_destroy_dmatable
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
id|ide_startstop_t
id|ide_dma_intr
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|check_drive_lists
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|good_bad
)paren
suffix:semicolon
r_int
id|report_drive_dmaing
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|ide_dmaproc
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
id|ide_release_dma
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
suffix:semicolon
r_void
id|ide_setup_dma
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
r_int
id|dmabase
comma
r_int
r_int
id|num_ports
)paren
id|__init
suffix:semicolon
r_int
r_int
id|ide_get_or_set_dma_base
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
id|extra
comma
r_const
r_char
op_star
id|name
)paren
id|__init
suffix:semicolon
macro_line|#endif
r_void
id|hwif_unregister
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
suffix:semicolon
macro_line|#endif /* _IDE_H */
eof
