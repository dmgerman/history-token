multiline_comment|/*&n; * linux/drivers/ide/pci/ns87415.c&t;&t;Version 2.00  Sep. 10, 2002&n; *&n; * Copyright (C) 1997-1998&t;Mark Lord &lt;mlord@pobox.com&gt;&n; * Copyright (C) 1998&t;&t;Eddie C. Dost &lt;ecd@skynet.be&gt;&n; * Copyright (C) 1999-2000&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * Copyright (C) 2004&t;&t;Grant Grundler &lt;grundler at parisc-linux.org&gt;&n; *&n; * Inspired by an earlier effort from David S. Miller &lt;davem@redhat.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_SUPERIO
multiline_comment|/* SUPERIO 87560 is a PoS chip that NatSem denies exists.&n; * Unfortunately, it&squot;s built-in on all Astro-based PA-RISC workstations&n; * which use the integrated NS87514 cell for CD-ROM support.&n; * i.e we have to support for CD-ROM installs.&n; * See drivers/parisc/superio.c for more gory details.&n; */
macro_line|#include &lt;asm/superio.h&gt;
DECL|variable|superio_ide_status
r_static
r_int
r_int
id|superio_ide_status
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|superio_ide_select
r_static
r_int
r_int
id|superio_ide_select
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|superio_ide_dma_status
r_static
r_int
r_int
id|superio_ide_dma_status
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|SUPERIO_IDE_MAX_RETRIES
mdefine_line|#define SUPERIO_IDE_MAX_RETRIES 25
multiline_comment|/* Because of a defect in Super I/O, all reads of the PCI DMA status &n; * registers, IDE status register and the IDE select register need to be &n; * retried&n; */
DECL|function|superio_ide_inb
r_static
id|u8
id|superio_ide_inb
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_eq
id|superio_ide_status
(braket
l_int|0
)braket
op_logical_or
id|port
op_eq
id|superio_ide_status
(braket
l_int|1
)braket
op_logical_or
id|port
op_eq
id|superio_ide_select
(braket
l_int|0
)braket
op_logical_or
id|port
op_eq
id|superio_ide_select
(braket
l_int|1
)braket
op_logical_or
id|port
op_eq
id|superio_ide_dma_status
(braket
l_int|0
)braket
op_logical_or
id|port
op_eq
id|superio_ide_dma_status
(braket
l_int|1
)braket
)paren
(brace
id|u8
id|tmp
suffix:semicolon
r_int
id|retries
op_assign
id|SUPERIO_IDE_MAX_RETRIES
suffix:semicolon
multiline_comment|/* printk(&quot; [ reading port 0x%x with retry ] &quot;, port); */
r_do
(brace
id|tmp
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|0
)paren
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp
op_eq
l_int|0
op_logical_and
id|retries
op_decrement
OG
l_int|0
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
r_return
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|superio_ide_init_iops
r_static
r_void
id|__devinit
id|superio_ide_init_iops
(paren
r_struct
id|hwif_s
op_star
id|hwif
)paren
(brace
id|u32
id|base
comma
id|dmabase
suffix:semicolon
id|u8
id|tmp
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u8
id|port
op_assign
id|hwif-&gt;channel
suffix:semicolon
id|base
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
id|port
op_star
l_int|2
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
id|dmabase
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|4
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
id|superio_ide_status
(braket
id|port
)braket
op_assign
id|base
op_plus
id|IDE_STATUS_OFFSET
suffix:semicolon
id|superio_ide_select
(braket
id|port
)braket
op_assign
id|base
op_plus
id|IDE_SELECT_OFFSET
suffix:semicolon
id|superio_ide_dma_status
(braket
id|port
)braket
op_assign
id|dmabase
op_plus
(paren
op_logical_neg
id|port
ques
c_cond
l_int|2
suffix:colon
l_int|0xa
)paren
suffix:semicolon
multiline_comment|/* Clear error/interrupt, enable dma */
id|tmp
op_assign
id|superio_ide_inb
c_func
(paren
id|superio_ide_dma_status
(braket
id|port
)braket
)paren
suffix:semicolon
id|outb
c_func
(paren
id|tmp
op_or
l_int|0x66
comma
id|superio_ide_dma_status
(braket
id|port
)braket
)paren
suffix:semicolon
multiline_comment|/* We need to override inb to workaround a SuperIO errata */
id|hwif-&gt;INB
op_assign
id|superio_ide_inb
suffix:semicolon
)brace
DECL|function|init_iops_ns87415
r_static
r_void
id|__devinit
id|init_iops_ns87415
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|hwif-&gt;pci_dev-&gt;devfn
)paren
op_eq
l_int|0xE
)paren
(brace
multiline_comment|/* Built-in - assume it&squot;s under superio. */
id|superio_ide_init_iops
c_func
(paren
id|hwif
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|variable|ns87415_count
DECL|variable|ns87415_control
r_static
r_int
r_int
id|ns87415_count
op_assign
l_int|0
comma
id|ns87415_control
(braket
id|MAX_HWIFS
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * This routine either enables/disables (according to drive-&gt;present)&n; * the IRQ associated with the port (HWIF(drive)),&n; * and selects either PIO or DMA handshaking for the next I/O operation.&n; */
DECL|function|ns87415_prepare_drive
r_static
r_void
id|ns87415_prepare_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|use_dma
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
r_int
id|bit
comma
id|other
comma
r_new
comma
op_star
id|old
op_assign
(paren
r_int
r_int
op_star
)paren
id|hwif-&gt;select_data
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
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
r_new
op_assign
op_star
id|old
suffix:semicolon
multiline_comment|/* Adjust IRQ enable bit */
id|bit
op_assign
l_int|1
op_lshift
(paren
l_int|8
op_plus
id|hwif-&gt;channel
)paren
suffix:semicolon
r_new
op_assign
id|drive-&gt;present
ques
c_cond
(paren
r_new
op_amp
op_complement
id|bit
)paren
suffix:colon
(paren
r_new
op_or
id|bit
)paren
suffix:semicolon
multiline_comment|/* Select PIO or DMA, DMA may only be selected for one drive/channel. */
id|bit
op_assign
l_int|1
op_lshift
(paren
l_int|20
op_plus
id|drive-&gt;select.b.unit
op_plus
(paren
id|hwif-&gt;channel
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
id|other
op_assign
l_int|1
op_lshift
(paren
l_int|20
op_plus
(paren
l_int|1
op_minus
id|drive-&gt;select.b.unit
)paren
op_plus
(paren
id|hwif-&gt;channel
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_new
op_assign
id|use_dma
ques
c_cond
(paren
(paren
r_new
op_amp
op_complement
id|other
)paren
op_or
id|bit
)paren
suffix:colon
(paren
r_new
op_amp
op_complement
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ne
op_star
id|old
)paren
(brace
r_int
r_char
id|stat
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t change DMA engine settings while Write Buffers&n;&t;&t; * are busy.&n;&t;&t; */
(paren
r_void
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x43
comma
op_amp
id|stat
)paren
suffix:semicolon
r_while
c_loop
(paren
id|stat
op_amp
l_int|0x03
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
(paren
r_void
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x43
comma
op_amp
id|stat
)paren
suffix:semicolon
)brace
op_star
id|old
op_assign
r_new
suffix:semicolon
(paren
r_void
)paren
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
r_new
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * And let things settle...&n;&t;&t; */
id|udelay
c_func
(paren
l_int|10
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
DECL|function|ns87415_selectproc
r_static
r_void
id|ns87415_selectproc
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ns87415_prepare_drive
(paren
id|drive
comma
id|drive-&gt;using_dma
)paren
suffix:semicolon
)brace
DECL|function|ns87415_ide_dma_end
r_static
r_int
id|ns87415_ide_dma_end
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
id|u8
id|dma_stat
op_assign
l_int|0
comma
id|dma_cmd
op_assign
l_int|0
suffix:semicolon
id|drive-&gt;waiting_for_dma
op_assign
l_int|0
suffix:semicolon
id|dma_stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|hwif-&gt;dma_status
)paren
suffix:semicolon
multiline_comment|/* get dma command mode */
id|dma_cmd
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|hwif-&gt;dma_command
)paren
suffix:semicolon
multiline_comment|/* stop DMA */
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|dma_cmd
op_amp
op_complement
l_int|1
comma
id|hwif-&gt;dma_command
)paren
suffix:semicolon
multiline_comment|/* from ERRATA: clear the INTR &amp; ERROR bits */
id|dma_cmd
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|hwif-&gt;dma_command
)paren
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|dma_cmd
op_or
l_int|6
comma
id|hwif-&gt;dma_command
)paren
suffix:semicolon
multiline_comment|/* and free any DMA resources */
id|ide_destroy_dmatable
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* verify good DMA status */
r_return
(paren
id|dma_stat
op_amp
l_int|7
)paren
op_ne
l_int|4
suffix:semicolon
)brace
DECL|function|ns87415_ide_dma_setup
r_static
r_int
id|ns87415_ide_dma_setup
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
multiline_comment|/* select DMA xfer */
id|ns87415_prepare_drive
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ide_dma_setup
c_func
(paren
id|drive
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* DMA failed: select PIO xfer */
id|ns87415_prepare_drive
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ns87415_ide_dma_check
r_static
r_int
id|ns87415_ide_dma_check
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;media
op_ne
id|ide_disk
)paren
r_return
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|__ide_dma_check
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|init_hwif_ns87415
r_static
r_void
id|__init
id|init_hwif_ns87415
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|ctrl
comma
id|using_inta
suffix:semicolon
id|u8
id|progif
suffix:semicolon
macro_line|#ifdef __sparc_v9__
r_int
id|timeout
suffix:semicolon
id|u8
id|stat
suffix:semicolon
macro_line|#endif
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;selectproc
op_assign
op_amp
id|ns87415_selectproc
suffix:semicolon
multiline_comment|/*&n;&t; * We cannot probe for IRQ: both ports share common IRQ on INTA.&n;&t; * Also, leave IRQ masked during drive probing, to prevent infinite&n;&t; * interrupts from a potentially floating INTA..&n;&t; *&n;&t; * IRQs get unmasked in selectproc when drive is first used.&n;&t; */
(paren
r_void
)paren
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|ctrl
)paren
suffix:semicolon
(paren
r_void
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x09
comma
op_amp
id|progif
)paren
suffix:semicolon
multiline_comment|/* is irq in &quot;native&quot; mode? */
id|using_inta
op_assign
id|progif
op_amp
(paren
l_int|1
op_lshift
(paren
id|hwif-&gt;channel
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|using_inta
)paren
id|using_inta
op_assign
id|ctrl
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|4
op_plus
id|hwif-&gt;channel
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;mate
)paren
(brace
id|hwif-&gt;select_data
op_assign
id|hwif-&gt;mate-&gt;select_data
suffix:semicolon
)brace
r_else
(brace
id|hwif-&gt;select_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ns87415_control
(braket
id|ns87415_count
op_increment
)braket
suffix:semicolon
id|ctrl
op_or_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/* mask both IRQs */
r_if
c_cond
(paren
id|using_inta
)paren
id|ctrl
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|6
)paren
suffix:semicolon
multiline_comment|/* unmask INTA */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|hwif-&gt;select_data
)paren
op_assign
id|ctrl
suffix:semicolon
(paren
r_void
)paren
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|ctrl
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set prefetch size to 512 bytes for both ports,&n;&t;&t; * but don&squot;t turn on/off prefetching here.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x55
comma
l_int|0xee
)paren
suffix:semicolon
macro_line|#ifdef __sparc_v9__
multiline_comment|/*&n;&t;&t; * XXX: Reset the device, if we don&squot;t it will not respond&n;&t;&t; *      to SELECT_DRIVE() properly during first probe_hwif().&n;&t;&t; */
id|timeout
op_assign
l_int|10000
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
l_int|12
comma
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
l_int|8
comma
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
r_do
(brace
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_STATUS_OFFSET
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|stat
op_amp
id|BUSY_STAT
)paren
op_logical_and
op_decrement
id|timeout
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
op_logical_neg
id|using_inta
)paren
id|hwif-&gt;irq
op_assign
id|ide_default_irq
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;irq
op_logical_and
id|hwif-&gt;mate
op_logical_and
id|hwif-&gt;mate-&gt;irq
)paren
id|hwif-&gt;irq
op_assign
id|hwif-&gt;mate-&gt;irq
suffix:semicolon
multiline_comment|/* share IRQ with mate */
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;dma_base
)paren
r_return
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
l_int|0x60
comma
id|hwif-&gt;dma_status
)paren
suffix:semicolon
id|hwif-&gt;dma_setup
op_assign
op_amp
id|ns87415_ide_dma_setup
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|ns87415_ide_dma_check
suffix:semicolon
id|hwif-&gt;ide_dma_end
op_assign
op_amp
id|ns87415_ide_dma_end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|ns87415_chipset
id|__devinitdata
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;NS87415&quot;
comma
macro_line|#ifdef CONFIG_SUPERIO
dot
id|init_iops
op_assign
id|init_iops_ns87415
comma
macro_line|#endif
dot
id|init_hwif
op_assign
id|init_hwif_ns87415
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
suffix:semicolon
DECL|function|ns87415_init_one
r_static
r_int
id|__devinit
id|ns87415_init_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
op_amp
id|ns87415_chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ns87415_pci_tbl
r_static
r_struct
id|pci_device_id
id|ns87415_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_87415
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|ns87415_pci_tbl
)paren
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;NS87415_IDE&quot;
comma
dot
id|id_table
op_assign
id|ns87415_pci_tbl
comma
dot
id|probe
op_assign
id|ns87415_init_one
comma
)brace
suffix:semicolon
DECL|function|ns87415_ide_init
r_static
r_int
id|ns87415_ide_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ide_pci_register_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|ns87415_ide_init
id|module_init
c_func
(paren
id|ns87415_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark Lord, Eddie Dost, Andre Hedrick&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for NS87415 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
