multiline_comment|/*&n; * linux/drivers/ide/icside.c&n; *&n; * Copyright (c) 1996-2002 Russell King.&n; *&n; * Changelog:&n; *  08-Jun-1996&t;RMK&t;Created&n; *  12-Sep-1997&t;RMK&t;Added interrupt enable/disable&n; *  17-Apr-1999&t;RMK&t;Added support for V6 EASI&n; *  22-May-1999&t;RMK&t;Added support for V6 DMA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Maximum number of interfaces per card&n; */
DECL|macro|MAX_IFS
mdefine_line|#define MAX_IFS&t;2
DECL|macro|ICS_IDENT_OFFSET
mdefine_line|#define ICS_IDENT_OFFSET&t;&t;0x8a0
DECL|macro|ICS_ARCIN_V5_INTRSTAT
mdefine_line|#define ICS_ARCIN_V5_INTRSTAT&t;&t;0x000
DECL|macro|ICS_ARCIN_V5_INTROFFSET
mdefine_line|#define ICS_ARCIN_V5_INTROFFSET&t;&t;0x001
DECL|macro|ICS_ARCIN_V5_IDEOFFSET
mdefine_line|#define ICS_ARCIN_V5_IDEOFFSET&t;&t;0xa00
DECL|macro|ICS_ARCIN_V5_IDEALTOFFSET
mdefine_line|#define ICS_ARCIN_V5_IDEALTOFFSET&t;0xae0
DECL|macro|ICS_ARCIN_V5_IDESTEPPING
mdefine_line|#define ICS_ARCIN_V5_IDESTEPPING&t;4
DECL|macro|ICS_ARCIN_V6_IDEOFFSET_1
mdefine_line|#define ICS_ARCIN_V6_IDEOFFSET_1&t;0x800
DECL|macro|ICS_ARCIN_V6_INTROFFSET_1
mdefine_line|#define ICS_ARCIN_V6_INTROFFSET_1&t;0x880
DECL|macro|ICS_ARCIN_V6_INTRSTAT_1
mdefine_line|#define ICS_ARCIN_V6_INTRSTAT_1&t;&t;0x8a4
DECL|macro|ICS_ARCIN_V6_IDEALTOFFSET_1
mdefine_line|#define ICS_ARCIN_V6_IDEALTOFFSET_1&t;0x8e0
DECL|macro|ICS_ARCIN_V6_IDEOFFSET_2
mdefine_line|#define ICS_ARCIN_V6_IDEOFFSET_2&t;0xc00
DECL|macro|ICS_ARCIN_V6_INTROFFSET_2
mdefine_line|#define ICS_ARCIN_V6_INTROFFSET_2&t;0xc80
DECL|macro|ICS_ARCIN_V6_INTRSTAT_2
mdefine_line|#define ICS_ARCIN_V6_INTRSTAT_2&t;&t;0xca4
DECL|macro|ICS_ARCIN_V6_IDEALTOFFSET_2
mdefine_line|#define ICS_ARCIN_V6_IDEALTOFFSET_2&t;0xce0
DECL|macro|ICS_ARCIN_V6_IDESTEPPING
mdefine_line|#define ICS_ARCIN_V6_IDESTEPPING&t;4
DECL|struct|cardinfo
r_struct
id|cardinfo
(brace
DECL|member|dataoffset
r_int
r_int
id|dataoffset
suffix:semicolon
DECL|member|ctrloffset
r_int
r_int
id|ctrloffset
suffix:semicolon
DECL|member|stepping
r_int
r_int
id|stepping
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|icside_cardinfo_v5
r_static
r_struct
id|cardinfo
id|icside_cardinfo_v5
op_assign
(brace
id|ICS_ARCIN_V5_IDEOFFSET
comma
id|ICS_ARCIN_V5_IDEALTOFFSET
comma
id|ICS_ARCIN_V5_IDESTEPPING
)brace
suffix:semicolon
DECL|variable|icside_cardinfo_v6_1
r_static
r_struct
id|cardinfo
id|icside_cardinfo_v6_1
op_assign
(brace
id|ICS_ARCIN_V6_IDEOFFSET_1
comma
id|ICS_ARCIN_V6_IDEALTOFFSET_1
comma
id|ICS_ARCIN_V6_IDESTEPPING
)brace
suffix:semicolon
DECL|variable|icside_cardinfo_v6_2
r_static
r_struct
id|cardinfo
id|icside_cardinfo_v6_2
op_assign
(brace
id|ICS_ARCIN_V6_IDEOFFSET_2
comma
id|ICS_ARCIN_V6_IDEALTOFFSET_2
comma
id|ICS_ARCIN_V6_IDESTEPPING
)brace
suffix:semicolon
DECL|struct|icside_state
r_struct
id|icside_state
(brace
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|enabled
r_int
r_int
id|enabled
suffix:semicolon
DECL|member|irq_port
r_int
r_int
id|irq_port
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|icside_cids
r_static
r_const
id|card_ids
id|icside_cids
(braket
)braket
op_assign
(brace
(brace
id|MANU_ICS
comma
id|PROD_ICS_IDE
)brace
comma
(brace
id|MANU_ICS2
comma
id|PROD_ICS2_IDE
)brace
comma
(brace
l_int|0xffff
comma
l_int|0xffff
)brace
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|ics_if_unknown
id|ics_if_unknown
comma
DECL|enumerator|ics_if_arcin_v5
id|ics_if_arcin_v5
comma
DECL|enumerator|ics_if_arcin_v6
id|ics_if_arcin_v6
DECL|typedef|iftype_t
)brace
id|iftype_t
suffix:semicolon
multiline_comment|/* ---------------- Version 5 PCB Support Functions --------------------- */
multiline_comment|/* Prototype: icside_irqenable_arcin_v5 (struct expansion_card *ec, int irqnr)&n; * Purpose  : enable interrupts from card&n; */
DECL|function|icside_irqenable_arcin_v5
r_static
r_void
id|icside_irqenable_arcin_v5
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_int
r_int
id|memc_port
op_assign
(paren
r_int
r_int
)paren
id|ec-&gt;irq_data
suffix:semicolon
id|outb
(paren
l_int|0
comma
id|memc_port
op_plus
id|ICS_ARCIN_V5_INTROFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: icside_irqdisable_arcin_v5 (struct expansion_card *ec, int irqnr)&n; * Purpose  : disable interrupts from card&n; */
DECL|function|icside_irqdisable_arcin_v5
r_static
r_void
id|icside_irqdisable_arcin_v5
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_int
r_int
id|memc_port
op_assign
(paren
r_int
r_int
)paren
id|ec-&gt;irq_data
suffix:semicolon
id|inb
(paren
id|memc_port
op_plus
id|ICS_ARCIN_V5_INTROFFSET
)paren
suffix:semicolon
)brace
DECL|variable|icside_ops_arcin_v5
r_static
r_const
id|expansioncard_ops_t
id|icside_ops_arcin_v5
op_assign
(brace
id|icside_irqenable_arcin_v5
comma
id|icside_irqdisable_arcin_v5
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* ---------------- Version 6 PCB Support Functions --------------------- */
multiline_comment|/* Prototype: icside_irqenable_arcin_v6 (struct expansion_card *ec, int irqnr)&n; * Purpose  : enable interrupts from card&n; */
DECL|function|icside_irqenable_arcin_v6
r_static
r_void
id|icside_irqenable_arcin_v6
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_struct
id|icside_state
op_star
id|state
op_assign
id|ec-&gt;irq_data
suffix:semicolon
r_int
r_int
id|base
op_assign
id|state-&gt;irq_port
suffix:semicolon
id|state-&gt;enabled
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|state-&gt;channel
)paren
(brace
r_case
l_int|0
suffix:colon
id|outb
c_func
(paren
l_int|0
comma
id|base
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
id|inb
c_func
(paren
id|base
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|outb
c_func
(paren
l_int|0
comma
id|base
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
id|inb
c_func
(paren
id|base
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Prototype: icside_irqdisable_arcin_v6 (struct expansion_card *ec, int irqnr)&n; * Purpose  : disable interrupts from card&n; */
DECL|function|icside_irqdisable_arcin_v6
r_static
r_void
id|icside_irqdisable_arcin_v6
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_struct
id|icside_state
op_star
id|state
op_assign
id|ec-&gt;irq_data
suffix:semicolon
id|state-&gt;enabled
op_assign
l_int|0
suffix:semicolon
id|inb
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
id|inb
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: icside_irqprobe(struct expansion_card *ec)&n; * Purpose  : detect an active interrupt from card&n; */
DECL|function|icside_irqpending_arcin_v6
r_static
r_int
id|icside_irqpending_arcin_v6
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_struct
id|icside_state
op_star
id|state
op_assign
id|ec-&gt;irq_data
suffix:semicolon
r_return
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTRSTAT_1
)paren
op_amp
l_int|1
op_logical_or
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTRSTAT_2
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|variable|icside_ops_arcin_v6
r_static
r_const
id|expansioncard_ops_t
id|icside_ops_arcin_v6
op_assign
(brace
id|icside_irqenable_arcin_v6
comma
id|icside_irqdisable_arcin_v6
comma
id|icside_irqpending_arcin_v6
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* Prototype: icside_identifyif (struct expansion_card *ec)&n; * Purpose  : identify IDE interface type&n; * Notes    : checks the description string&n; */
DECL|function|icside_identifyif
r_static
id|iftype_t
id|__init
id|icside_identifyif
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|iftype_t
id|iftype
suffix:semicolon
r_int
id|id
op_assign
l_int|0
suffix:semicolon
id|iftype
op_assign
id|ics_if_unknown
suffix:semicolon
id|addr
op_assign
id|ecard_address
(paren
id|ec
comma
id|ECARD_IOC
comma
id|ECARD_FAST
)paren
op_plus
id|ICS_IDENT_OFFSET
suffix:semicolon
id|id
op_assign
id|inb
(paren
id|addr
)paren
op_amp
l_int|1
suffix:semicolon
id|id
op_or_assign
(paren
id|inb
(paren
id|addr
op_plus
l_int|1
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|1
suffix:semicolon
id|id
op_or_assign
(paren
id|inb
(paren
id|addr
op_plus
l_int|2
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|2
suffix:semicolon
id|id
op_or_assign
(paren
id|inb
(paren
id|addr
op_plus
l_int|3
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|3
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* A3IN */
id|printk
c_func
(paren
l_string|&quot;icside: A3IN unsupported&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* A3USER */
id|printk
c_func
(paren
l_string|&quot;icside: A3USER unsupported&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* ARCIN V6 */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;icside: detected ARCIN V6 in slot %d&bslash;n&quot;
comma
id|ec-&gt;slot_no
)paren
suffix:semicolon
id|iftype
op_assign
id|ics_if_arcin_v6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
multiline_comment|/* ARCIN V5 (no id) */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;icside: detected ARCIN V5 in slot %d&bslash;n&quot;
comma
id|ec-&gt;slot_no
)paren
suffix:semicolon
id|iftype
op_assign
id|ics_if_arcin_v5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* we don&squot;t know - complain very loudly */
id|printk
c_func
(paren
l_string|&quot;icside: ***********************************&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;icside: *** UNKNOWN ICS INTERFACE id=%d ***&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;icside: ***********************************&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;icside: please report this to linux@arm.linux.org.uk&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;icside: defaulting to ARCIN V5&bslash;n&quot;
)paren
suffix:semicolon
id|iftype
op_assign
id|ics_if_arcin_v5
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|iftype
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle routing of interrupts.  This is called before&n; * we write the command to the drive.&n; */
DECL|function|icside_maskproc
r_static
r_void
id|icside_maskproc
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_const
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|icside_state
op_star
id|state
op_assign
id|ch-&gt;hw.priv
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|state-&gt;channel
op_assign
id|ch-&gt;unit
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;enabled
op_logical_and
op_logical_neg
id|mask
)paren
(brace
r_switch
c_cond
(paren
id|ch-&gt;unit
)paren
(brace
r_case
l_int|0
suffix:colon
id|outb
c_func
(paren
l_int|0
comma
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|outb
c_func
(paren
l_int|0
comma
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA_ICS
multiline_comment|/*&n; * SG-DMA support.&n; *&n; * Similar to the BM-DMA, but we use the RiscPCs IOMD DMA controllers.&n; * There is only one DMA controller per card, which means that only&n; * one drive can be accessed at one time.  NOTE! We do not enforce that&n; * here, but we rely on the main IDE driver spotting that both&n; * interfaces use the same IRQ, which should guarantee this.&n; */
DECL|macro|NR_ENTRIES
mdefine_line|#define NR_ENTRIES 256
DECL|macro|TABLE_SIZE
mdefine_line|#define TABLE_SIZE (NR_ENTRIES * 8)
DECL|function|ide_build_sglist
r_static
r_int
id|ide_build_sglist
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
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|ch-&gt;sg_table
suffix:semicolon
r_int
id|nents
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;flags
op_amp
id|REQ_SPECIAL
)paren
op_logical_and
(paren
id|drive-&gt;type
op_eq
id|ATA_DISK
)paren
)paren
(brace
r_struct
id|ata_taskfile
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;command_type
op_eq
id|IDE_DRIVE_TASK_RAW_WRITE
)paren
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_TODEVICE
suffix:semicolon
r_else
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_FROMDEVICE
suffix:semicolon
id|memset
c_func
(paren
id|sg
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sg
)paren
)paren
suffix:semicolon
id|sg-&gt;page
op_assign
id|virt_to_page
c_func
(paren
id|rq-&gt;buffer
)paren
suffix:semicolon
id|sg-&gt;offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|rq-&gt;buffer
)paren
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|sg-&gt;length
op_assign
id|rq-&gt;nr_sectors
op_star
id|SECTOR_SIZE
suffix:semicolon
id|nents
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|nents
op_assign
id|blk_rq_map_sg
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|rq
comma
id|sg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;q
op_logical_and
id|nents
OG
id|rq-&gt;nr_phys_segments
)paren
id|printk
c_func
(paren
l_string|&quot;icside: received %d segments, build %d&bslash;n&quot;
comma
id|rq-&gt;nr_phys_segments
comma
id|nents
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|rq
)paren
op_eq
id|READ
)paren
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_FROMDEVICE
suffix:semicolon
r_else
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_TODEVICE
suffix:semicolon
)brace
r_return
id|pci_map_sg
c_func
(paren
l_int|NULL
comma
id|sg
comma
id|nents
comma
id|ch-&gt;sg_dma_direction
)paren
suffix:semicolon
)brace
multiline_comment|/* Teardown mappings after DMA has completed.  */
DECL|function|icside_destroy_dmatable
r_static
r_void
id|icside_destroy_dmatable
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|drive-&gt;channel-&gt;sg_table
suffix:semicolon
r_int
id|nents
op_assign
id|drive-&gt;channel-&gt;sg_nents
suffix:semicolon
id|pci_unmap_sg
c_func
(paren
l_int|NULL
comma
id|sg
comma
id|nents
comma
id|drive-&gt;channel-&gt;sg_dma_direction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure the IOMD to give the appropriate timings for the transfer&n; * mode being requested.  We take the advice of the ATA standards, and&n; * calculate the cycle time based on the transfer mode, and the EIDE&n; * MW DMA specs that the drive provides in the IDENTIFY command.&n; *&n; * We have the following IOMD DMA modes to choose from:&n; *&n; *&t;Type&t;Active&t;&t;Recovery&t;Cycle&n; *&t;A&t;250 (250)&t;312 (550)&t;562 (800)&n; *&t;B&t;187&t;&t;250&t;&t;437&n; *&t;C&t;125 (125)&t;125 (375)&t;250 (500)&n; *&t;D&t;62&t;&t;125&t;&t;187&n; *&n; * (figures in brackets are actual measured timings)&n; *&n; * However, we also need to take care of the read/write active and&n; * recovery timings:&n; *&n; *&t;&t;&t;Read&t;Write&n; *  &t;Mode&t;Active&t;-- Recovery --&t;Cycle&t;IOMD type&n; *&t;MW0&t;215&t;50&t;215&t;480&t;A&n; *&t;MW1&t;80&t;50&t;50&t;150&t;C&n; *&t;MW2&t;70&t;25&t;25&t;120&t;C&n; */
r_static
r_int
DECL|function|icside_config_if
id|icside_config_if
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|xfer_mode
)paren
(brace
r_int
id|on
op_assign
l_int|0
comma
id|cycle_time
op_assign
l_int|0
comma
id|use_dma_info
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|xfer_mode
)paren
(brace
r_case
id|XFER_MW_DMA_2
suffix:colon
id|cycle_time
op_assign
l_int|250
suffix:semicolon
id|use_dma_info
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
id|cycle_time
op_assign
l_int|250
suffix:semicolon
id|use_dma_info
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
id|cycle_time
op_assign
l_int|480
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we&squot;re going to be doing MW_DMA_1 or MW_DMA_2, we should&n;&t; * take care to note the values in the ID...&n;&t; */
r_if
c_cond
(paren
id|use_dma_info
op_logical_and
id|drive-&gt;id-&gt;eide_dma_time
OG
id|cycle_time
)paren
id|cycle_time
op_assign
id|drive-&gt;id-&gt;eide_dma_time
suffix:semicolon
id|drive-&gt;drive_data
op_assign
id|cycle_time
suffix:semicolon
r_if
c_cond
(paren
id|cycle_time
op_logical_and
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|xfer_mode
)paren
op_eq
l_int|0
)paren
id|on
op_assign
l_int|1
suffix:semicolon
r_else
id|drive-&gt;drive_data
op_assign
l_int|480
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %02x selected (peak %dMB/s)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|xfer_mode
comma
l_int|2000
op_div
id|drive-&gt;drive_data
)paren
suffix:semicolon
id|drive-&gt;current_speed
op_assign
id|xfer_mode
suffix:semicolon
r_return
id|on
suffix:semicolon
)brace
DECL|function|icside_set_speed
r_static
r_int
id|icside_set_speed
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|byte
id|speed
)paren
(brace
r_return
id|icside_config_if
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|icside_dma_enable
r_static
r_void
id|icside_dma_enable
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
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
l_string|&quot;%s: DMA disabled&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE_TCQ
id|udma_tcq_enable
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&t; * We don&squot;t need any bouncing.  Yes, this looks the&n;&t; * wrong way around, but it is correct.&n;&t; */
id|blk_queue_bounce_limit
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|BLK_BOUNCE_ANY
)paren
suffix:semicolon
id|drive-&gt;using_dma
op_assign
id|on
suffix:semicolon
macro_line|#ifdef CONFIG_CLK_DEV_IDE_TCQ_DEFAULT
r_if
c_cond
(paren
id|on
)paren
id|udma_tcq_enable
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|icside_dma_check
r_static
r_int
id|icside_dma_check
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|map
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
id|xfer_mode
op_assign
id|XFER_PIO_2
suffix:semicolon
r_int
id|on
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|id
op_logical_or
op_logical_neg
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_or
op_logical_neg
id|ch-&gt;autodma
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Enable DMA on any drive that has multiword DMA&n;&t; */
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|4
)paren
(brace
id|xfer_mode
op_assign
id|XFER_MW_DMA_2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|2
)paren
(brace
id|xfer_mode
op_assign
id|XFER_MW_DMA_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|1
)paren
(brace
id|xfer_mode
op_assign
id|XFER_MW_DMA_0
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|on
op_assign
id|icside_config_if
c_func
(paren
id|drive
comma
id|xfer_mode
)paren
suffix:semicolon
id|icside_dma_enable
c_func
(paren
id|drive
comma
id|on
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|icside_dma_stop
r_static
r_int
id|icside_dma_stop
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|disable_dma
c_func
(paren
id|ch-&gt;hw.dma
)paren
suffix:semicolon
id|icside_destroy_dmatable
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|get_dma_residue
c_func
(paren
id|ch-&gt;hw.dma
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|icside_dma_start
r_static
r_void
id|icside_dma_start
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
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
multiline_comment|/* We can not enable DMA on both channels simultaneously. */
id|BUG_ON
c_func
(paren
id|dma_channel_active
c_func
(paren
id|ch-&gt;hw.dma
)paren
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|ch-&gt;hw.dma
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * dma_intr() is the handler for disk read/write DMA interrupts&n; */
DECL|function|icside_dmaintr
r_static
id|ide_startstop_t
id|icside_dmaintr
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
id|dma_stat
suffix:semicolon
id|dma_stat
op_assign
id|icside_dma_stop
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ata_status
c_func
(paren
id|drive
comma
id|DRIVE_READY
comma
id|drive-&gt;bad_wstat
op_or
id|DRQ_STAT
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dma_stat
)paren
(brace
id|__ide_end_request
c_func
(paren
id|drive
comma
id|rq
comma
l_int|1
comma
id|rq-&gt;nr_sectors
)paren
suffix:semicolon
r_return
id|ATA_OP_FINISHED
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: dma_intr: bad DMA status (dma_stat=%x)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|dma_stat
)paren
suffix:semicolon
)brace
r_return
id|ata_error
c_func
(paren
id|drive
comma
id|rq
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|icside_dma_common
id|icside_dma_common
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
comma
r_int
r_int
id|dma_mode
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * We can not enable DMA on both channels.&n;&t; */
id|BUG_ON
c_func
(paren
id|dma_channel_active
c_func
(paren
id|ch-&gt;hw.dma
)paren
)paren
suffix:semicolon
id|count
op_assign
id|ch-&gt;sg_nents
op_assign
id|ide_build_sglist
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
op_logical_neg
id|count
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Route the DMA signals to to this channel.&n;&t; */
id|outb
c_func
(paren
id|ch-&gt;select_data
comma
id|ch-&gt;config_data
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Select the correct timing for this drive.&n;&t; */
id|set_dma_speed
c_func
(paren
id|ch-&gt;hw.dma
comma
id|drive-&gt;drive_data
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the DMA engine about the SG table and&n;&t; * data direction.&n;&t; */
id|set_dma_sg
c_func
(paren
id|ch-&gt;hw.dma
comma
id|ch-&gt;sg_table
comma
id|count
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|ch-&gt;hw.dma
comma
id|dma_mode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|icside_dma_init
r_static
r_int
id|icside_dma_init
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
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|u8
r_int
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|icside_dma_common
c_func
(paren
id|drive
comma
id|rq
comma
id|DMA_MODE_WRITE
)paren
)paren
r_return
id|ATA_OP_FINISHED
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
r_return
id|ATA_OP_CONTINUES
suffix:semicolon
id|ata_set_handler
c_func
(paren
id|drive
comma
id|icside_dmaintr
comma
id|WAIT_CMD
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;flags
op_amp
id|REQ_SPECIAL
)paren
op_logical_and
id|drive-&gt;addressing
op_eq
l_int|1
)paren
(brace
r_struct
id|ata_taskfile
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|cmd
op_assign
id|args-&gt;cmd
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|drive-&gt;addressing
)paren
(brace
id|cmd
op_assign
id|rq_data_dir
c_func
(paren
id|rq
)paren
op_eq
id|WRITE
ques
c_cond
id|WIN_WRITEDMA_EXT
suffix:colon
id|WIN_READDMA_EXT
suffix:semicolon
)brace
r_else
(brace
id|cmd
op_assign
id|rq_data_dir
c_func
(paren
id|rq
)paren
op_eq
id|WRITE
ques
c_cond
id|WIN_WRITEDMA
suffix:colon
id|WIN_READDMA
suffix:semicolon
)brace
id|OUT_BYTE
c_func
(paren
id|cmd
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|ch-&gt;hw.dma
)paren
suffix:semicolon
r_return
id|ATA_OP_CONTINUES
suffix:semicolon
)brace
DECL|function|icside_irq_status
r_static
r_int
id|icside_irq_status
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|icside_state
op_star
id|state
op_assign
id|ch-&gt;hw.priv
suffix:semicolon
r_return
id|inb
c_func
(paren
id|state-&gt;irq_port
op_plus
(paren
id|ch-&gt;unit
ques
c_cond
id|ICS_ARCIN_V6_INTRSTAT_2
suffix:colon
id|ICS_ARCIN_V6_INTRSTAT_1
)paren
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|icside_dma_timeout
r_static
r_void
id|icside_dma_timeout
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: %s: UDMA timeout occured:&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|ata_dump
c_func
(paren
id|drive
comma
l_int|NULL
comma
l_string|&quot;UDMA timeout&quot;
)paren
suffix:semicolon
)brace
DECL|function|icside_irq_lost
r_static
r_void
id|icside_irq_lost
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: %s: IRQ lost&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|icside_setup_dma
r_static
r_int
id|icside_setup_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_int
id|autodma
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_IDEDMA_ICS_AUTO
id|autodma
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;    %s: SG-DMA&quot;
comma
id|ch-&gt;name
)paren
suffix:semicolon
id|ch-&gt;sg_table
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|NR_ENTRIES
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;sg_table
)paren
r_goto
id|failed
suffix:semicolon
id|ch-&gt;dmatable_cpu
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;dmatable_dma
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;speedproc
op_assign
id|icside_set_speed
suffix:semicolon
id|ch-&gt;udma_setup
op_assign
id|icside_dma_check
suffix:semicolon
id|ch-&gt;udma_enable
op_assign
id|icside_dma_enable
suffix:semicolon
id|ch-&gt;udma_start
op_assign
id|icside_dma_start
suffix:semicolon
id|ch-&gt;udma_stop
op_assign
id|icside_dma_stop
suffix:semicolon
id|ch-&gt;udma_init
op_assign
id|icside_dma_init
suffix:semicolon
id|ch-&gt;udma_irq_status
op_assign
id|icside_irq_status
suffix:semicolon
id|ch-&gt;udma_timeout
op_assign
id|icside_dma_timeout
suffix:semicolon
id|ch-&gt;udma_irq_lost
op_assign
id|icside_irq_lost
suffix:semicolon
id|ch-&gt;autodma
op_assign
id|autodma
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; capable%s&bslash;n&quot;
comma
id|autodma
ques
c_cond
l_string|&quot;, auto-enable&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|failed
suffix:colon
id|printk
c_func
(paren
l_string|&quot; disabled, unable to allocate DMA table&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_release_dma
r_void
id|ide_release_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_if
c_cond
(paren
id|ch-&gt;sg_table
)paren
(brace
id|kfree
c_func
(paren
id|ch-&gt;sg_table
)paren
suffix:semicolon
id|ch-&gt;sg_table
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|icside_find_hwif
r_static
r_struct
id|ata_channel
op_star
id|icside_find_hwif
c_func
(paren
r_int
r_int
id|dataport
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
suffix:semicolon
r_int
id|index
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_HWIFS
suffix:semicolon
op_increment
id|index
)paren
(brace
id|ch
op_assign
op_amp
id|ide_hwifs
(braket
id|index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_eq
(paren
id|ide_ioreg_t
)paren
id|dataport
)paren
r_goto
id|found
suffix:semicolon
)brace
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_HWIFS
suffix:semicolon
op_increment
id|index
)paren
(brace
id|ch
op_assign
op_amp
id|ide_hwifs
(braket
id|index
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
)paren
r_goto
id|found
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
id|found
suffix:colon
r_return
id|ch
suffix:semicolon
)brace
r_static
r_struct
id|ata_channel
op_star
DECL|function|icside_setup
id|icside_setup
c_func
(paren
r_int
r_int
id|base
comma
r_struct
id|cardinfo
op_star
id|info
comma
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
op_assign
id|base
op_plus
id|info-&gt;dataoffset
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
suffix:semicolon
id|ch
op_assign
id|icside_find_hwif
c_func
(paren
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
)paren
(brace
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ch-&gt;hw
comma
l_int|0
comma
r_sizeof
(paren
id|hw_regs_t
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ch-&gt;hw.io_ports
(braket
id|i
)braket
op_assign
(paren
id|ide_ioreg_t
)paren
id|port
suffix:semicolon
id|ch-&gt;io_ports
(braket
id|i
)braket
op_assign
(paren
id|ide_ioreg_t
)paren
id|port
suffix:semicolon
id|port
op_add_assign
l_int|1
op_lshift
id|info-&gt;stepping
suffix:semicolon
)brace
id|ch-&gt;hw.io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|base
op_plus
id|info-&gt;ctrloffset
suffix:semicolon
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|base
op_plus
id|info-&gt;ctrloffset
suffix:semicolon
id|ch-&gt;hw.irq
op_assign
id|irq
suffix:semicolon
id|ch-&gt;irq
op_assign
id|irq
suffix:semicolon
id|ch-&gt;hw.dma
op_assign
id|NO_DMA
suffix:semicolon
id|ch-&gt;noprobe
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;chipset
op_assign
id|ide_acorn
suffix:semicolon
)brace
r_return
id|ch
suffix:semicolon
)brace
DECL|function|icside_register_v5
r_static
r_int
id|__init
id|icside_register_v5
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_int
r_int
id|slot_port
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
suffix:semicolon
id|slot_port
op_assign
id|ecard_address
c_func
(paren
id|ec
comma
id|ECARD_MEMC
comma
l_int|0
)paren
suffix:semicolon
id|ec-&gt;irqaddr
op_assign
(paren
r_int
r_char
op_star
)paren
id|ioaddr
c_func
(paren
id|slot_port
op_plus
id|ICS_ARCIN_V5_INTRSTAT
)paren
suffix:semicolon
id|ec-&gt;irqmask
op_assign
l_int|1
suffix:semicolon
id|ec-&gt;irq_data
op_assign
(paren
r_void
op_star
)paren
id|slot_port
suffix:semicolon
id|ec-&gt;ops
op_assign
(paren
id|expansioncard_ops_t
op_star
)paren
op_amp
id|icside_ops_arcin_v5
suffix:semicolon
multiline_comment|/*&n;&t; * Be on the safe side - disable interrupts&n;&t; */
id|inb
c_func
(paren
id|slot_port
op_plus
id|ICS_ARCIN_V5_INTROFFSET
)paren
suffix:semicolon
id|ch
op_assign
id|icside_setup
c_func
(paren
id|slot_port
comma
op_amp
id|icside_cardinfo_v5
comma
id|ec-&gt;irq
)paren
suffix:semicolon
r_return
id|ch
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|icside_register_v6
r_static
r_int
id|__init
id|icside_register_v6
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_int
r_int
id|slot_port
comma
id|port
suffix:semicolon
r_struct
id|icside_state
op_star
id|state
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch0
comma
op_star
id|ch1
suffix:semicolon
r_int
r_int
id|sel
op_assign
l_int|0
suffix:semicolon
id|slot_port
op_assign
id|ecard_address
c_func
(paren
id|ec
comma
id|ECARD_IOC
comma
id|ECARD_FAST
)paren
suffix:semicolon
id|port
op_assign
id|ecard_address
c_func
(paren
id|ec
comma
id|ECARD_EASI
comma
id|ECARD_FAST
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
id|port
op_assign
id|slot_port
suffix:semicolon
r_else
id|sel
op_assign
l_int|1
op_lshift
l_int|5
suffix:semicolon
id|outb
c_func
(paren
id|sel
comma
id|slot_port
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Be on the safe side - disable interrupts&n;&t; */
id|inb
c_func
(paren
id|port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_1
)paren
suffix:semicolon
id|inb
c_func
(paren
id|port
op_plus
id|ICS_ARCIN_V6_INTROFFSET_2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find and register the interfaces.&n;&t; */
id|ch0
op_assign
id|icside_setup
c_func
(paren
id|port
comma
op_amp
id|icside_cardinfo_v6_1
comma
id|ec-&gt;irq
)paren
suffix:semicolon
id|ch1
op_assign
id|icside_setup
c_func
(paren
id|port
comma
op_amp
id|icside_cardinfo_v6_2
comma
id|ec-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch0
op_logical_or
op_logical_neg
id|ch1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|icside_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|state-&gt;channel
op_assign
l_int|0
suffix:semicolon
id|state-&gt;enabled
op_assign
l_int|0
suffix:semicolon
id|state-&gt;irq_port
op_assign
id|port
suffix:semicolon
id|ec-&gt;irq_data
op_assign
id|state
suffix:semicolon
id|ec-&gt;ops
op_assign
(paren
id|expansioncard_ops_t
op_star
)paren
op_amp
id|icside_ops_arcin_v6
suffix:semicolon
id|ch0-&gt;maskproc
op_assign
id|icside_maskproc
suffix:semicolon
id|ch0-&gt;unit
op_assign
l_int|0
suffix:semicolon
id|ch0-&gt;hw.priv
op_assign
id|state
suffix:semicolon
id|ch0-&gt;config_data
op_assign
id|slot_port
suffix:semicolon
id|ch0-&gt;select_data
op_assign
id|sel
suffix:semicolon
id|ch0-&gt;hw.dma
op_assign
id|ec-&gt;dma
suffix:semicolon
id|ch1-&gt;maskproc
op_assign
id|icside_maskproc
suffix:semicolon
id|ch1-&gt;unit
op_assign
l_int|1
suffix:semicolon
id|ch1-&gt;hw.priv
op_assign
id|state
suffix:semicolon
id|ch1-&gt;config_data
op_assign
id|slot_port
suffix:semicolon
id|ch1-&gt;select_data
op_assign
id|sel
op_or
l_int|1
suffix:semicolon
id|ch1-&gt;hw.dma
op_assign
id|ec-&gt;dma
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA_ICS
r_if
c_cond
(paren
id|ec-&gt;dma
op_ne
id|NO_DMA
op_logical_and
op_logical_neg
id|request_dma
c_func
(paren
id|ec-&gt;dma
comma
id|ch0-&gt;name
)paren
)paren
(brace
id|icside_setup_dma
c_func
(paren
id|ch0
)paren
suffix:semicolon
id|icside_setup_dma
c_func
(paren
id|ch1
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|icside_init
r_int
id|__init
id|icside_init
c_func
(paren
r_void
)paren
(brace
id|ecard_startfind
(paren
)paren
suffix:semicolon
r_do
(brace
r_struct
id|expansion_card
op_star
id|ec
suffix:semicolon
r_int
id|result
suffix:semicolon
id|ec
op_assign
id|ecard_find
c_func
(paren
l_int|0
comma
id|icside_cids
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|ecard_claim
c_func
(paren
id|ec
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|icside_identifyif
c_func
(paren
id|ec
)paren
)paren
(brace
r_case
id|ics_if_arcin_v5
suffix:colon
id|result
op_assign
id|icside_register_v5
c_func
(paren
id|ec
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ics_if_arcin_v6
suffix:colon
id|result
op_assign
id|icside_register_v6
c_func
(paren
id|ec
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
)paren
id|ecard_release
c_func
(paren
id|ec
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
