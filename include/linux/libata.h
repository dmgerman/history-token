multiline_comment|/*&n;   Copyright 2003-2004 Red Hat, Inc.  All rights reserved.&n;   Copyright 2003-2004 Jeff Garzik&n;&n;   The contents of this file are subject to the Open&n;   Software License version 1.1 that can be found at&n;   http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n;   by reference.&n;&n;   Alternatively, the contents of this file may be used under the terms&n;   of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n;   in the kernel source COPYING file, in which case the provisions of&n;   the GPL are applicable instead of the above.  If you wish to allow&n;   the use of your version of this file only under the terms of the&n;   GPL and not to allow others to use your version of this file under&n;   the OSL, indicate your decision by deleting the provisions above and&n;   replace them with the notice and other provisions required by the GPL.&n;   If you do not delete the provisions above, a recipient may use your&n;   version of this file under either the OSL or the GPL.&n;&n; */
macro_line|#ifndef __LINUX_LIBATA_H__
DECL|macro|__LINUX_LIBATA_H__
mdefine_line|#define __LINUX_LIBATA_H__
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/ata.h&gt;
multiline_comment|/*&n; * compile-time options&n; */
DECL|macro|ATA_FORCE_PIO
macro_line|#undef ATA_FORCE_PIO&t;&t;/* do not configure or use DMA */
DECL|macro|ATA_DEBUG
macro_line|#undef ATA_DEBUG&t;&t;/* debugging output */
DECL|macro|ATA_VERBOSE_DEBUG
macro_line|#undef ATA_VERBOSE_DEBUG&t;/* yet more debugging output */
DECL|macro|ATA_IRQ_TRAP
macro_line|#undef ATA_IRQ_TRAP&t;&t;/* define to ack screaming irqs */
DECL|macro|ATA_NDEBUG
macro_line|#undef ATA_NDEBUG&t;&t;/* define to disable quick runtime checks */
DECL|macro|ATA_ENABLE_ATAPI
macro_line|#undef ATA_ENABLE_ATAPI&t;&t;/* define to enable ATAPI support */
DECL|macro|ATA_ENABLE_PATA
macro_line|#undef ATA_ENABLE_PATA&t;&t;/* define to enable PATA support in some&n;&t;&t;&t;&t; * low-level drivers */
multiline_comment|/* note: prints function name for you */
macro_line|#ifdef ATA_DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...) printk(KERN_ERR &quot;%s: &quot; fmt, __FUNCTION__, ## args)
macro_line|#ifdef ATA_VERBOSE_DEBUG
DECL|macro|VPRINTK
mdefine_line|#define VPRINTK(fmt, args...) printk(KERN_ERR &quot;%s: &quot; fmt, __FUNCTION__, ## args)
macro_line|#else
DECL|macro|VPRINTK
mdefine_line|#define VPRINTK(fmt, args...)
macro_line|#endif&t;/* ATA_VERBOSE_DEBUG */
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)
DECL|macro|VPRINTK
mdefine_line|#define VPRINTK(fmt, args...)
macro_line|#endif&t;/* ATA_DEBUG */
macro_line|#ifdef ATA_NDEBUG
DECL|macro|assert
mdefine_line|#define assert(expr)
macro_line|#else
DECL|macro|assert
mdefine_line|#define assert(expr) &bslash;&n;        if(unlikely(!(expr))) {                                   &bslash;&n;        printk(KERN_ERR &quot;Assertion failed! %s,%s,%s,line=%d&bslash;n&quot;, &bslash;&n;        #expr,__FILE__,__FUNCTION__,__LINE__);          &bslash;&n;        }
macro_line|#endif
multiline_comment|/* defines only for the constants which don&squot;t work well as enums */
DECL|macro|ATA_TAG_POISON
mdefine_line|#define ATA_TAG_POISON&t;&t;0xfafbfcfdU
r_enum
(brace
multiline_comment|/* various global constants */
DECL|enumerator|LIBATA_MAX_PRD
id|LIBATA_MAX_PRD
op_assign
id|ATA_MAX_PRD
op_div
l_int|2
comma
DECL|enumerator|ATA_MAX_PORTS
id|ATA_MAX_PORTS
op_assign
l_int|8
comma
DECL|enumerator|ATA_DEF_QUEUE
id|ATA_DEF_QUEUE
op_assign
l_int|1
comma
DECL|enumerator|ATA_MAX_QUEUE
id|ATA_MAX_QUEUE
op_assign
l_int|1
comma
DECL|enumerator|ATA_MAX_SECTORS
id|ATA_MAX_SECTORS
op_assign
l_int|200
comma
multiline_comment|/* FIXME */
DECL|enumerator|ATA_MAX_BUS
id|ATA_MAX_BUS
op_assign
l_int|2
comma
DECL|enumerator|ATA_DEF_BUSY_WAIT
id|ATA_DEF_BUSY_WAIT
op_assign
l_int|10000
comma
DECL|enumerator|ATA_SHORT_PAUSE
id|ATA_SHORT_PAUSE
op_assign
(paren
id|HZ
op_rshift
l_int|6
)paren
op_plus
l_int|1
comma
DECL|enumerator|ATA_SHT_EMULATED
id|ATA_SHT_EMULATED
op_assign
l_int|1
comma
DECL|enumerator|ATA_SHT_CMD_PER_LUN
id|ATA_SHT_CMD_PER_LUN
op_assign
l_int|1
comma
DECL|enumerator|ATA_SHT_THIS_ID
id|ATA_SHT_THIS_ID
op_assign
op_minus
l_int|1
comma
DECL|enumerator|ATA_SHT_USE_CLUSTERING
id|ATA_SHT_USE_CLUSTERING
op_assign
l_int|0
comma
multiline_comment|/* struct ata_device stuff */
DECL|enumerator|ATA_DFLAG_LBA48
id|ATA_DFLAG_LBA48
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* device supports LBA48 */
DECL|enumerator|ATA_DFLAG_PIO
id|ATA_DFLAG_PIO
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* device currently in PIO mode */
DECL|enumerator|ATA_DFLAG_MASTER
id|ATA_DFLAG_MASTER
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* is device 0? */
DECL|enumerator|ATA_DFLAG_WCACHE
id|ATA_DFLAG_WCACHE
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* has write cache we can&n;&t;&t;&t;&t;&t;     * (hopefully) flush? */
DECL|enumerator|ATA_DEV_UNKNOWN
id|ATA_DEV_UNKNOWN
op_assign
l_int|0
comma
multiline_comment|/* unknown device */
DECL|enumerator|ATA_DEV_ATA
id|ATA_DEV_ATA
op_assign
l_int|1
comma
multiline_comment|/* ATA device */
DECL|enumerator|ATA_DEV_ATA_UNSUP
id|ATA_DEV_ATA_UNSUP
op_assign
l_int|2
comma
multiline_comment|/* ATA device (unsupported) */
DECL|enumerator|ATA_DEV_ATAPI
id|ATA_DEV_ATAPI
op_assign
l_int|3
comma
multiline_comment|/* ATAPI device */
DECL|enumerator|ATA_DEV_ATAPI_UNSUP
id|ATA_DEV_ATAPI_UNSUP
op_assign
l_int|4
comma
multiline_comment|/* ATAPI device (unsupported) */
DECL|enumerator|ATA_DEV_NONE
id|ATA_DEV_NONE
op_assign
l_int|5
comma
multiline_comment|/* no device */
multiline_comment|/* struct ata_port flags */
DECL|enumerator|ATA_FLAG_SLAVE_POSS
id|ATA_FLAG_SLAVE_POSS
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* host supports slave dev */
multiline_comment|/* (doesn&squot;t imply presence) */
DECL|enumerator|ATA_FLAG_PORT_DISABLED
id|ATA_FLAG_PORT_DISABLED
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* port is disabled, ignore it */
DECL|enumerator|ATA_FLAG_SATA
id|ATA_FLAG_SATA
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
DECL|enumerator|ATA_FLAG_NO_LEGACY
id|ATA_FLAG_NO_LEGACY
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* no legacy mode check */
DECL|enumerator|ATA_FLAG_SRST
id|ATA_FLAG_SRST
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
multiline_comment|/* use ATA SRST, not E.D.D. */
DECL|enumerator|ATA_FLAG_MMIO
id|ATA_FLAG_MMIO
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
multiline_comment|/* use MMIO, not PIO */
DECL|enumerator|ATA_FLAG_SATA_RESET
id|ATA_FLAG_SATA_RESET
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
multiline_comment|/* use COMRESET */
multiline_comment|/* struct ata_taskfile flags */
DECL|enumerator|ATA_TFLAG_LBA48
id|ATA_TFLAG_LBA48
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|ATA_TFLAG_ISADDR
id|ATA_TFLAG_ISADDR
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* enable r/w to nsect/lba regs */
DECL|enumerator|ATA_TFLAG_DEVICE
id|ATA_TFLAG_DEVICE
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* enable r/w to device reg */
DECL|enumerator|ATA_QCFLAG_WRITE
id|ATA_QCFLAG_WRITE
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* read==0, write==1 */
DECL|enumerator|ATA_QCFLAG_ACTIVE
id|ATA_QCFLAG_ACTIVE
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* cmd not yet ack&squot;d to scsi lyer */
DECL|enumerator|ATA_QCFLAG_DMA
id|ATA_QCFLAG_DMA
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* data delivered via DMA */
DECL|enumerator|ATA_QCFLAG_ATAPI
id|ATA_QCFLAG_ATAPI
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* is ATAPI packet command? */
DECL|enumerator|ATA_QCFLAG_SG
id|ATA_QCFLAG_SG
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* have s/g table? */
DECL|enumerator|ATA_QCFLAG_POLL
id|ATA_QCFLAG_POLL
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
multiline_comment|/* polling, no interrupts */
multiline_comment|/* struct ata_engine atomic flags (use test_bit, etc.) */
DECL|enumerator|ATA_EFLG_ACTIVE
id|ATA_EFLG_ACTIVE
op_assign
l_int|0
comma
multiline_comment|/* engine is active */
multiline_comment|/* various lengths of time */
DECL|enumerator|ATA_TMOUT_EDD
id|ATA_TMOUT_EDD
op_assign
l_int|5
op_star
id|HZ
comma
multiline_comment|/* hueristic */
DECL|enumerator|ATA_TMOUT_PIO
id|ATA_TMOUT_PIO
op_assign
l_int|30
op_star
id|HZ
comma
DECL|enumerator|ATA_TMOUT_BOOT
id|ATA_TMOUT_BOOT
op_assign
l_int|30
op_star
id|HZ
comma
multiline_comment|/* hueristic */
DECL|enumerator|ATA_TMOUT_BOOT_QUICK
id|ATA_TMOUT_BOOT_QUICK
op_assign
l_int|7
op_star
id|HZ
comma
multiline_comment|/* hueristic */
DECL|enumerator|ATA_TMOUT_CDB
id|ATA_TMOUT_CDB
op_assign
l_int|30
op_star
id|HZ
comma
DECL|enumerator|ATA_TMOUT_CDB_QUICK
id|ATA_TMOUT_CDB_QUICK
op_assign
l_int|5
op_star
id|HZ
comma
multiline_comment|/* ATA bus states */
DECL|enumerator|BUS_UNKNOWN
id|BUS_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|BUS_DMA
id|BUS_DMA
op_assign
l_int|1
comma
DECL|enumerator|BUS_IDLE
id|BUS_IDLE
op_assign
l_int|2
comma
DECL|enumerator|BUS_NOINTR
id|BUS_NOINTR
op_assign
l_int|3
comma
DECL|enumerator|BUS_NODATA
id|BUS_NODATA
op_assign
l_int|4
comma
DECL|enumerator|BUS_TIMER
id|BUS_TIMER
op_assign
l_int|5
comma
DECL|enumerator|BUS_PIO
id|BUS_PIO
op_assign
l_int|6
comma
DECL|enumerator|BUS_EDD
id|BUS_EDD
op_assign
l_int|7
comma
DECL|enumerator|BUS_IDENTIFY
id|BUS_IDENTIFY
op_assign
l_int|8
comma
DECL|enumerator|BUS_PACKET
id|BUS_PACKET
op_assign
l_int|9
comma
multiline_comment|/* thread states */
DECL|enumerator|THR_UNKNOWN
id|THR_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|THR_PORT_RESET
id|THR_PORT_RESET
op_assign
(paren
id|THR_UNKNOWN
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_AWAIT_DEATH
id|THR_AWAIT_DEATH
op_assign
(paren
id|THR_PORT_RESET
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PROBE_FAILED
id|THR_PROBE_FAILED
op_assign
(paren
id|THR_AWAIT_DEATH
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_IDLE
id|THR_IDLE
op_assign
(paren
id|THR_PROBE_FAILED
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PROBE_SUCCESS
id|THR_PROBE_SUCCESS
op_assign
(paren
id|THR_IDLE
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PROBE_START
id|THR_PROBE_START
op_assign
(paren
id|THR_PROBE_SUCCESS
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PIO_POLL
id|THR_PIO_POLL
op_assign
(paren
id|THR_PROBE_START
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PIO_TMOUT
id|THR_PIO_TMOUT
op_assign
(paren
id|THR_PIO_POLL
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PIO
id|THR_PIO
op_assign
(paren
id|THR_PIO_TMOUT
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PIO_LAST
id|THR_PIO_LAST
op_assign
(paren
id|THR_PIO
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PIO_LAST_POLL
id|THR_PIO_LAST_POLL
op_assign
(paren
id|THR_PIO_LAST
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PIO_ERR
id|THR_PIO_ERR
op_assign
(paren
id|THR_PIO_LAST_POLL
op_plus
l_int|1
)paren
comma
DECL|enumerator|THR_PACKET
id|THR_PACKET
op_assign
(paren
id|THR_PIO_ERR
op_plus
l_int|1
)paren
comma
multiline_comment|/* SATA port states */
DECL|enumerator|PORT_UNKNOWN
id|PORT_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|PORT_ENABLED
id|PORT_ENABLED
op_assign
l_int|1
comma
DECL|enumerator|PORT_DISABLED
id|PORT_DISABLED
op_assign
l_int|2
comma
multiline_comment|/* ata_qc_cb_t flags - note uses above ATA_QCFLAG_xxx namespace,&n;&t; * but not numberspace&n;&t; */
DECL|enumerator|ATA_QCFLAG_TIMEOUT
id|ATA_QCFLAG_TIMEOUT
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* forward declarations */
r_struct
id|scsi_device
suffix:semicolon
r_struct
id|ata_port_operations
suffix:semicolon
r_struct
id|ata_port
suffix:semicolon
r_struct
id|ata_queued_cmd
suffix:semicolon
multiline_comment|/* typedefs */
DECL|typedef|ata_qc_cb_t
r_typedef
r_void
(paren
op_star
id|ata_qc_cb_t
)paren
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|struct|ata_ioports
r_struct
id|ata_ioports
(brace
DECL|member|cmd_addr
r_int
r_int
id|cmd_addr
suffix:semicolon
DECL|member|data_addr
r_int
r_int
id|data_addr
suffix:semicolon
DECL|member|error_addr
r_int
r_int
id|error_addr
suffix:semicolon
DECL|member|feature_addr
r_int
r_int
id|feature_addr
suffix:semicolon
DECL|member|nsect_addr
r_int
r_int
id|nsect_addr
suffix:semicolon
DECL|member|lbal_addr
r_int
r_int
id|lbal_addr
suffix:semicolon
DECL|member|lbam_addr
r_int
r_int
id|lbam_addr
suffix:semicolon
DECL|member|lbah_addr
r_int
r_int
id|lbah_addr
suffix:semicolon
DECL|member|device_addr
r_int
r_int
id|device_addr
suffix:semicolon
DECL|member|status_addr
r_int
r_int
id|status_addr
suffix:semicolon
DECL|member|command_addr
r_int
r_int
id|command_addr
suffix:semicolon
DECL|member|altstatus_addr
r_int
r_int
id|altstatus_addr
suffix:semicolon
DECL|member|ctl_addr
r_int
r_int
id|ctl_addr
suffix:semicolon
DECL|member|bmdma_addr
r_int
r_int
id|bmdma_addr
suffix:semicolon
DECL|member|scr_addr
r_int
r_int
id|scr_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_probe_ent
r_struct
id|ata_probe_ent
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|port_ops
r_struct
id|ata_port_operations
op_star
id|port_ops
suffix:semicolon
DECL|member|sht
id|Scsi_Host_Template
op_star
id|sht
suffix:semicolon
DECL|member|port
r_struct
id|ata_ioports
id|port
(braket
id|ATA_MAX_PORTS
)braket
suffix:semicolon
DECL|member|n_ports
r_int
r_int
id|n_ports
suffix:semicolon
DECL|member|pio_mask
r_int
r_int
id|pio_mask
suffix:semicolon
DECL|member|udma_mask
r_int
r_int
id|udma_mask
suffix:semicolon
DECL|member|legacy_mode
r_int
r_int
id|legacy_mode
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|irq_flags
r_int
r_int
id|irq_flags
suffix:semicolon
DECL|member|host_flags
r_int
r_int
id|host_flags
suffix:semicolon
DECL|member|mmio_base
r_void
op_star
id|mmio_base
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_host_set
r_struct
id|ata_host_set
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|mmio_base
r_void
op_star
id|mmio_base
suffix:semicolon
DECL|member|n_ports
r_int
r_int
id|n_ports
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|ports
r_struct
id|ata_port
op_star
id|ports
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_taskfile
r_struct
id|ata_taskfile
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* ATA_TFLAG_xxx */
DECL|member|protocol
id|u8
id|protocol
suffix:semicolon
multiline_comment|/* ATA_PROT_xxx */
DECL|member|ctl
id|u8
id|ctl
suffix:semicolon
multiline_comment|/* control reg */
DECL|member|hob_feature
id|u8
id|hob_feature
suffix:semicolon
multiline_comment|/* additional data */
DECL|member|hob_nsect
id|u8
id|hob_nsect
suffix:semicolon
multiline_comment|/* to support LBA48 */
DECL|member|hob_lbal
id|u8
id|hob_lbal
suffix:semicolon
DECL|member|hob_lbam
id|u8
id|hob_lbam
suffix:semicolon
DECL|member|hob_lbah
id|u8
id|hob_lbah
suffix:semicolon
DECL|member|feature
id|u8
id|feature
suffix:semicolon
DECL|member|nsect
id|u8
id|nsect
suffix:semicolon
DECL|member|lbal
id|u8
id|lbal
suffix:semicolon
DECL|member|lbam
id|u8
id|lbam
suffix:semicolon
DECL|member|lbah
id|u8
id|lbah
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|command
id|u8
id|command
suffix:semicolon
multiline_comment|/* IO operation */
)brace
suffix:semicolon
DECL|struct|ata_queued_cmd
r_struct
id|ata_queued_cmd
(brace
DECL|member|ap
r_struct
id|ata_port
op_star
id|ap
suffix:semicolon
DECL|member|dev
r_struct
id|ata_device
op_star
id|dev
suffix:semicolon
DECL|member|scsicmd
r_struct
id|scsi_cmnd
op_star
id|scsicmd
suffix:semicolon
DECL|member|scsidone
r_void
(paren
op_star
id|scsidone
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* ATA_QCFLAG_xxx */
DECL|member|tag
r_int
r_int
id|tag
suffix:semicolon
DECL|member|n_elem
r_int
r_int
id|n_elem
suffix:semicolon
DECL|member|nsect
r_int
r_int
id|nsect
suffix:semicolon
DECL|member|cursect
r_int
r_int
id|cursect
suffix:semicolon
DECL|member|cursg
r_int
r_int
id|cursg
suffix:semicolon
DECL|member|cursg_ofs
r_int
r_int
id|cursg_ofs
suffix:semicolon
DECL|member|tf
r_struct
id|ata_taskfile
id|tf
suffix:semicolon
DECL|member|sgent
r_struct
id|scatterlist
id|sgent
suffix:semicolon
DECL|member|sg
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
DECL|member|callback
id|ata_qc_cb_t
id|callback
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_host_stats
r_struct
id|ata_host_stats
(brace
DECL|member|unhandled_irq
r_int
r_int
id|unhandled_irq
suffix:semicolon
DECL|member|idle_irq
r_int
r_int
id|idle_irq
suffix:semicolon
DECL|member|rw_reqbuf
r_int
r_int
id|rw_reqbuf
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_device
r_struct
id|ata_device
(brace
DECL|member|n_sectors
id|u64
id|n_sectors
suffix:semicolon
multiline_comment|/* size of device, if ATA */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* ATA_DFLAG_xxx */
DECL|member|class
r_int
r_int
r_class
suffix:semicolon
multiline_comment|/* ATA_DEV_xxx */
DECL|member|devno
r_int
r_int
id|devno
suffix:semicolon
multiline_comment|/* 0 or 1 */
DECL|member|id
id|u16
id|id
(braket
id|ATA_ID_WORDS
)braket
suffix:semicolon
multiline_comment|/* IDENTIFY xxx DEVICE data */
DECL|member|pio_mode
r_int
r_int
id|pio_mode
suffix:semicolon
DECL|member|udma_mode
r_int
r_int
id|udma_mode
suffix:semicolon
DECL|member|vendor
r_int
r_char
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* space-padded, not ASCIIZ */
DECL|member|product
r_int
r_char
id|product
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* WARNING: shorter than&n;&t;&t;&t;&t;&t;&t; * ATAPI7 spec size, 40 ASCII&n;&t;&t;&t;&t;&t;&t; * characters&n;&t;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
DECL|struct|ata_engine
r_struct
id|ata_engine
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|q
r_struct
id|list_head
id|q
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_port
r_struct
id|ata_port
(brace
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* our co-allocated scsi host */
DECL|member|ops
r_struct
id|ata_port_operations
op_star
id|ops
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* ATA_FLAG_xxx */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* unique id req&squot;d by scsi midlyr */
DECL|member|port_no
r_int
r_int
id|port_no
suffix:semicolon
multiline_comment|/* unique port #; from zero */
DECL|member|prd
r_struct
id|ata_prd
op_star
id|prd
suffix:semicolon
multiline_comment|/* our SG list */
DECL|member|prd_dma
id|dma_addr_t
id|prd_dma
suffix:semicolon
multiline_comment|/* and its DMA mapping */
DECL|member|ioaddr
r_struct
id|ata_ioports
id|ioaddr
suffix:semicolon
multiline_comment|/* ATA cmd/ctl/dma register blocks */
DECL|member|ctl
id|u8
id|ctl
suffix:semicolon
multiline_comment|/* cache of ATA control register */
DECL|member|last_ctl
id|u8
id|last_ctl
suffix:semicolon
multiline_comment|/* Cache last written value */
DECL|member|bus_state
r_int
r_int
id|bus_state
suffix:semicolon
DECL|member|port_state
r_int
r_int
id|port_state
suffix:semicolon
DECL|member|pio_mask
r_int
r_int
id|pio_mask
suffix:semicolon
DECL|member|udma_mask
r_int
r_int
id|udma_mask
suffix:semicolon
DECL|member|cbl
r_int
r_int
id|cbl
suffix:semicolon
multiline_comment|/* cable type; ATA_CBL_xxx */
DECL|member|eng
r_struct
id|ata_engine
id|eng
suffix:semicolon
DECL|member|device
r_struct
id|ata_device
id|device
(braket
id|ATA_MAX_DEVICES
)braket
suffix:semicolon
DECL|member|qcmd
r_struct
id|ata_queued_cmd
id|qcmd
(braket
id|ATA_MAX_QUEUE
)braket
suffix:semicolon
DECL|member|qactive
r_int
r_int
id|qactive
suffix:semicolon
DECL|member|active_tag
r_int
r_int
id|active_tag
suffix:semicolon
DECL|member|stats
r_struct
id|ata_host_stats
id|stats
suffix:semicolon
DECL|member|host_set
r_struct
id|ata_host_set
op_star
id|host_set
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|probe_sem
r_struct
id|semaphore
id|probe_sem
suffix:semicolon
DECL|member|thr_state
r_int
r_int
id|thr_state
suffix:semicolon
DECL|member|time_to_die
r_int
id|time_to_die
suffix:semicolon
DECL|member|thr_pid
id|pid_t
id|thr_pid
suffix:semicolon
DECL|member|thr_exited
r_struct
id|completion
id|thr_exited
suffix:semicolon
DECL|member|thr_sem
r_struct
id|semaphore
id|thr_sem
suffix:semicolon
DECL|member|thr_timer
r_struct
id|timer_list
id|thr_timer
suffix:semicolon
DECL|member|thr_timeout
r_int
r_int
id|thr_timeout
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_port_operations
r_struct
id|ata_port_operations
(brace
DECL|member|port_disable
r_void
(paren
op_star
id|port_disable
)paren
(paren
r_struct
id|ata_port
op_star
)paren
suffix:semicolon
DECL|member|dev_config
r_void
(paren
op_star
id|dev_config
)paren
(paren
r_struct
id|ata_port
op_star
comma
r_struct
id|ata_device
op_star
)paren
suffix:semicolon
DECL|member|set_piomode
r_void
(paren
op_star
id|set_piomode
)paren
(paren
r_struct
id|ata_port
op_star
comma
r_struct
id|ata_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|set_udmamode
r_void
(paren
op_star
id|set_udmamode
)paren
(paren
r_struct
id|ata_port
op_star
comma
r_struct
id|ata_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|tf_load
r_void
(paren
op_star
id|tf_load
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
DECL|member|tf_read
r_void
(paren
op_star
id|tf_read
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
DECL|member|exec_command
r_void
(paren
op_star
id|exec_command
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
DECL|member|check_status
id|u8
(paren
op_star
id|check_status
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
DECL|member|phy_reset
r_void
(paren
op_star
id|phy_reset
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
DECL|member|bmdma_start
r_void
(paren
op_star
id|bmdma_start
)paren
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
DECL|member|fill_sg
r_void
(paren
op_star
id|fill_sg
)paren
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
DECL|member|eng_timeout
r_void
(paren
op_star
id|eng_timeout
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
DECL|member|irq_handler
id|irqreturn_t
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|scr_read
id|u32
(paren
op_star
id|scr_read
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|sc_reg
)paren
suffix:semicolon
DECL|member|scr_write
r_void
(paren
op_star
id|scr_write
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|sc_reg
comma
id|u32
id|val
)paren
suffix:semicolon
DECL|member|port_start
r_int
(paren
op_star
id|port_start
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
DECL|member|port_stop
r_void
(paren
op_star
id|port_stop
)paren
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
DECL|member|host_stop
r_void
(paren
op_star
id|host_stop
)paren
(paren
r_struct
id|ata_host_set
op_star
id|host_set
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ata_port_info
r_struct
id|ata_port_info
(brace
DECL|member|sht
id|Scsi_Host_Template
op_star
id|sht
suffix:semicolon
DECL|member|host_flags
r_int
r_int
id|host_flags
suffix:semicolon
DECL|member|pio_mask
r_int
r_int
id|pio_mask
suffix:semicolon
DECL|member|udma_mask
r_int
r_int
id|udma_mask
suffix:semicolon
DECL|member|port_ops
r_struct
id|ata_port_operations
op_star
id|port_ops
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_bits
r_struct
id|pci_bits
(brace
DECL|member|reg
r_int
r_int
id|reg
suffix:semicolon
multiline_comment|/* PCI config register to read */
DECL|member|width
r_int
r_int
id|width
suffix:semicolon
multiline_comment|/* 1 (8 bit), 2 (16 bit), 4 (32 bit) */
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|ata_port_probe
c_func
(paren
r_struct
id|ata_port
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sata_phy_reset
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
r_void
id|ata_bus_reset
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
r_void
id|ata_port_disable
c_func
(paren
r_struct
id|ata_port
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ata_std_ports
c_func
(paren
r_struct
id|ata_ioports
op_star
id|ioaddr
)paren
suffix:semicolon
r_extern
r_int
id|ata_pci_init_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|ata_port_info
op_star
op_star
id|port_info
comma
r_int
r_int
id|n_ports
)paren
suffix:semicolon
r_extern
r_void
id|ata_pci_remove_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
r_extern
r_int
id|ata_device_add
c_func
(paren
r_struct
id|ata_probe_ent
op_star
id|ent
)paren
suffix:semicolon
r_extern
r_int
id|ata_scsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|sht
)paren
suffix:semicolon
r_extern
r_int
id|ata_scsi_queuecmd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ata_scsi_error
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_extern
r_int
id|ata_scsi_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_extern
r_int
id|ata_scsi_slave_config
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_host_intr
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
multiline_comment|/*&n; * Default driver ops implementations&n; */
r_extern
r_void
id|ata_tf_load_pio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
r_void
id|ata_tf_load_mmio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
r_void
id|ata_tf_read_pio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
r_void
id|ata_tf_read_mmio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
id|u8
id|ata_check_status_pio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
id|u8
id|ata_check_status_mmio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
r_void
id|ata_exec_command_pio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
r_void
id|ata_exec_command_mmio
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
r_int
id|ata_port_start
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
r_void
id|ata_port_stop
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|ata_interrupt
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_instance
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|ata_fill_sg
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
r_extern
r_void
id|ata_bmdma_start_mmio
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
r_extern
r_void
id|ata_bmdma_start_pio
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
r_extern
r_int
id|pci_test_config_bits
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|pci_bits
op_star
id|bits
)paren
suffix:semicolon
r_extern
r_void
id|ata_qc_complete
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
comma
id|u8
id|drv_stat
comma
r_int
r_int
id|done_late
)paren
suffix:semicolon
r_extern
r_void
id|ata_eng_timeout
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
suffix:semicolon
r_extern
r_int
id|ata_std_bios_param
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|sector_t
id|capacity
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
DECL|function|msecs_to_jiffies
r_static
r_inline
r_int
r_int
id|msecs_to_jiffies
c_func
(paren
r_int
r_int
id|msecs
)paren
(brace
r_return
(paren
(paren
id|HZ
op_star
id|msecs
op_plus
l_int|999
)paren
op_div
l_int|1000
)paren
suffix:semicolon
)brace
DECL|function|ata_tag_valid
r_static
r_inline
r_int
r_int
id|ata_tag_valid
c_func
(paren
r_int
r_int
id|tag
)paren
(brace
r_return
(paren
id|tag
OL
id|ATA_MAX_QUEUE
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ata_dev_present
r_static
r_inline
r_int
r_int
id|ata_dev_present
c_func
(paren
r_struct
id|ata_device
op_star
id|dev
)paren
(brace
r_return
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_eq
id|ATA_DEV_ATA
)paren
op_logical_or
(paren
id|dev
op_member_access_from_pointer
r_class
op_eq
id|ATA_DEV_ATAPI
)paren
)paren
suffix:semicolon
)brace
DECL|function|ata_chk_err
r_static
r_inline
id|u8
id|ata_chk_err
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_MMIO
)paren
(brace
r_return
id|readb
c_func
(paren
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.error_addr
)paren
suffix:semicolon
)brace
r_return
id|inb
c_func
(paren
id|ap-&gt;ioaddr.error_addr
)paren
suffix:semicolon
)brace
DECL|function|ata_chk_status
r_static
r_inline
id|u8
id|ata_chk_status
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_return
id|ap-&gt;ops
op_member_access_from_pointer
id|check_status
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|ata_altstatus
r_static
r_inline
id|u8
id|ata_altstatus
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_MMIO
)paren
r_return
id|readb
c_func
(paren
id|ap-&gt;ioaddr.altstatus_addr
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|ap-&gt;ioaddr.altstatus_addr
)paren
suffix:semicolon
)brace
DECL|function|ata_pause
r_static
r_inline
r_void
id|ata_pause
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
id|ata_altstatus
c_func
(paren
id|ap
)paren
suffix:semicolon
id|ndelay
c_func
(paren
l_int|400
)paren
suffix:semicolon
)brace
DECL|function|ata_busy_wait
r_static
r_inline
id|u8
id|ata_busy_wait
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|bits
comma
r_int
r_int
id|max
)paren
(brace
id|u8
id|status
suffix:semicolon
r_do
(brace
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|status
op_assign
id|ata_chk_status
c_func
(paren
id|ap
)paren
suffix:semicolon
id|max
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|status
op_amp
id|bits
)paren
op_logical_and
(paren
id|max
OG
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|ata_wait_idle
r_static
r_inline
id|u8
id|ata_wait_idle
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
id|u8
id|status
op_assign
id|ata_busy_wait
c_func
(paren
id|ap
comma
id|ATA_BUSY
op_or
id|ATA_DRQ
comma
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|ATA_BUSY
op_or
id|ATA_DRQ
)paren
)paren
(brace
r_int
r_int
id|l
op_assign
id|ap-&gt;ioaddr.status_addr
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ATA: abnormal status 0x%X on port 0x%lX&bslash;n&quot;
comma
id|status
comma
id|l
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|ata_qc_from_tag
r_static
r_inline
r_struct
id|ata_queued_cmd
op_star
id|ata_qc_from_tag
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|tag
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|ata_tag_valid
c_func
(paren
id|tag
)paren
)paren
)paren
r_return
op_amp
id|ap-&gt;qcmd
(braket
id|tag
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ata_tf_init
r_static
r_inline
r_void
id|ata_tf_init
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
comma
r_int
r_int
id|device
)paren
(brace
id|memset
c_func
(paren
id|tf
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tf
)paren
)paren
suffix:semicolon
id|tf-&gt;ctl
op_assign
id|ap-&gt;ctl
suffix:semicolon
r_if
c_cond
(paren
id|device
op_eq
l_int|0
)paren
id|tf-&gt;device
op_assign
id|ATA_DEVICE_OBS
suffix:semicolon
r_else
id|tf-&gt;device
op_assign
id|ATA_DEVICE_OBS
op_or
id|ATA_DEV1
suffix:semicolon
)brace
DECL|function|ata_irq_on
r_static
r_inline
id|u8
id|ata_irq_on
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_struct
id|ata_ioports
op_star
id|ioaddr
op_assign
op_amp
id|ap-&gt;ioaddr
suffix:semicolon
id|ap-&gt;ctl
op_and_assign
op_complement
id|ATA_NIEN
suffix:semicolon
id|ap-&gt;last_ctl
op_assign
id|ap-&gt;ctl
suffix:semicolon
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_MMIO
)paren
id|writeb
c_func
(paren
id|ap-&gt;ctl
comma
id|ioaddr-&gt;ctl_addr
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|ap-&gt;ctl
comma
id|ioaddr-&gt;ctl_addr
)paren
suffix:semicolon
r_return
id|ata_wait_idle
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|ata_irq_ack
r_static
r_inline
id|u8
id|ata_irq_ack
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|chk_drq
)paren
(brace
r_int
r_int
id|bits
op_assign
id|chk_drq
ques
c_cond
id|ATA_BUSY
op_or
id|ATA_DRQ
suffix:colon
id|ATA_BUSY
suffix:semicolon
id|u8
id|host_stat
comma
id|post_stat
comma
id|status
suffix:semicolon
id|status
op_assign
id|ata_busy_wait
c_func
(paren
id|ap
comma
id|bits
comma
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|bits
)paren
id|DPRINTK
c_func
(paren
l_string|&quot;abnormal status 0x%X&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
multiline_comment|/* get controller status; clear intr, err bits */
r_if
c_cond
(paren
id|ap-&gt;flags
op_amp
id|ATA_FLAG_MMIO
)paren
(brace
r_void
op_star
id|mmio
op_assign
(paren
r_void
op_star
)paren
id|ap-&gt;ioaddr.bmdma_addr
suffix:semicolon
id|host_stat
op_assign
id|readb
c_func
(paren
id|mmio
op_plus
id|ATA_DMA_STATUS
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|host_stat
op_or
id|ATA_DMA_INTR
op_or
id|ATA_DMA_ERR
comma
id|mmio
op_plus
id|ATA_DMA_STATUS
)paren
suffix:semicolon
id|post_stat
op_assign
id|readb
c_func
(paren
id|mmio
op_plus
id|ATA_DMA_STATUS
)paren
suffix:semicolon
)brace
r_else
(brace
id|host_stat
op_assign
id|inb
c_func
(paren
id|ap-&gt;ioaddr.bmdma_addr
op_plus
id|ATA_DMA_STATUS
)paren
suffix:semicolon
id|outb
c_func
(paren
id|host_stat
op_or
id|ATA_DMA_INTR
op_or
id|ATA_DMA_ERR
comma
id|ap-&gt;ioaddr.bmdma_addr
op_plus
id|ATA_DMA_STATUS
)paren
suffix:semicolon
id|post_stat
op_assign
id|inb
c_func
(paren
id|ap-&gt;ioaddr.bmdma_addr
op_plus
id|ATA_DMA_STATUS
)paren
suffix:semicolon
)brace
id|VPRINTK
c_func
(paren
l_string|&quot;irq ack: host_stat 0x%X, new host_stat 0x%X, drv_stat 0x%X&bslash;n&quot;
comma
id|host_stat
comma
id|post_stat
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|scr_read
r_static
r_inline
id|u32
id|scr_read
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|reg
)paren
(brace
r_return
id|ap-&gt;ops
op_member_access_from_pointer
id|scr_read
c_func
(paren
id|ap
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|function|scr_write
r_static
r_inline
r_void
id|scr_write
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|reg
comma
id|u32
id|val
)paren
(brace
id|ap-&gt;ops
op_member_access_from_pointer
id|scr_write
c_func
(paren
id|ap
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|sata_dev_present
r_static
r_inline
r_int
r_int
id|sata_dev_present
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
)paren
(brace
r_return
(paren
(paren
id|scr_read
c_func
(paren
id|ap
comma
id|SCR_STATUS
)paren
op_amp
l_int|0xf
)paren
op_eq
l_int|0x3
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __LINUX_LIBATA_H__ */
eof
