multiline_comment|/*&n; * linux/drivers/ide/sl82c105.c&n; *&n; * SL82C105/Winbond 553 IDE driver&n; *&n; * Maintainer unknown.&n; *&n; * Changelog:&n; *&n; * 15/11/1998&t;RMK&t;Drive tuning added from Rebel.com&squot;s kernel&n; *&t;&t;&t;sources&n; * 30/03/2002&t;RMK&t;Add fixes specified in W83C553F errata.&n; *&t;&t;&t;(with special thanks to Todd Inglett)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
macro_line|#include &quot;pcihost.h&quot;
r_extern
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
suffix:semicolon
multiline_comment|/*&n; * SL82C105 PCI config register 0x40 bits.&n; */
DECL|macro|CTRL_IDE_IRQB
mdefine_line|#define CTRL_IDE_IRQB&t;(1 &lt;&lt; 30)
DECL|macro|CTRL_IDE_IRQA
mdefine_line|#define CTRL_IDE_IRQA&t;(1 &lt;&lt; 28)
DECL|macro|CTRL_LEGIRQ
mdefine_line|#define CTRL_LEGIRQ&t;(1 &lt;&lt; 11)
DECL|macro|CTRL_P1F16
mdefine_line|#define CTRL_P1F16&t;(1 &lt;&lt; 5)
DECL|macro|CTRL_P1EN
mdefine_line|#define CTRL_P1EN&t;(1 &lt;&lt; 4)
DECL|macro|CTRL_P0F16
mdefine_line|#define CTRL_P0F16&t;(1 &lt;&lt; 1)
DECL|macro|CTRL_P0EN
mdefine_line|#define&t;CTRL_P0EN&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * Convert a PIO mode and cycle time to the required on/off&n; * times for the interface.  This has protection against run-away&n; * timings.&n; */
DECL|function|get_timing_sl82c105
r_static
r_int
r_int
id|get_timing_sl82c105
c_func
(paren
r_struct
id|ata_timing
op_star
id|t
)paren
(brace
r_int
r_int
id|cmd_on
suffix:semicolon
r_int
r_int
id|cmd_off
suffix:semicolon
id|cmd_on
op_assign
(paren
id|t-&gt;active
op_plus
l_int|29
)paren
op_div
l_int|30
suffix:semicolon
id|cmd_off
op_assign
(paren
id|t-&gt;cycle
op_minus
l_int|30
op_star
id|cmd_on
op_plus
l_int|29
)paren
op_div
l_int|30
suffix:semicolon
r_if
c_cond
(paren
id|cmd_on
OG
l_int|32
)paren
id|cmd_on
op_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|cmd_on
op_eq
l_int|0
)paren
id|cmd_on
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cmd_off
OG
l_int|32
)paren
id|cmd_off
op_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|cmd_off
op_eq
l_int|0
)paren
id|cmd_off
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|cmd_on
op_minus
l_int|1
)paren
op_lshift
l_int|8
op_or
(paren
id|cmd_off
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|t-&gt;mode
OG
id|XFER_PIO_2
)paren
ques
c_cond
l_int|0x40
suffix:colon
l_int|0x00
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure the drive and chipset for PIO&n; */
DECL|function|config_for_pio
r_static
r_void
id|config_for_pio
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|pio
comma
r_int
id|report
)paren
(brace
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_struct
id|ata_timing
op_star
id|t
suffix:semicolon
r_int
r_int
id|drv_ctrl
op_assign
l_int|0x909
suffix:semicolon
r_int
r_int
id|xfer_mode
comma
id|reg
suffix:semicolon
id|reg
op_assign
(paren
id|hwif-&gt;unit
ques
c_cond
l_int|0x4c
suffix:colon
l_int|0x44
)paren
op_plus
(paren
id|drive-&gt;select.b.unit
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_eq
l_int|255
)paren
id|xfer_mode
op_assign
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
)paren
suffix:semicolon
r_else
id|xfer_mode
op_assign
id|XFER_PIO_0
op_plus
id|min_t
c_func
(paren
id|byte
comma
id|pio
comma
l_int|4
)paren
suffix:semicolon
id|t
op_assign
id|ata_timing_data
c_func
(paren
id|xfer_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|drv_ctrl
op_assign
id|get_timing_sl82c105
c_func
(paren
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;using_dma
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we are actually using MW DMA, then we can not&n;&t;&t; * reprogram the interface drive control register.&n;&t;&t; */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|reg
comma
id|drv_ctrl
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|drv_ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|report
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: selected %s (%dns) (%04X)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|ide_xfer_verbose
c_func
(paren
id|xfer_mode
)paren
comma
id|t-&gt;cycle
comma
id|drv_ctrl
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Configure the drive and the chipset for DMA&n; */
DECL|function|config_for_dma
r_static
r_int
id|config_for_dma
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
id|hwif
op_assign
id|drive-&gt;channel
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
id|drv_ctrl
op_assign
l_int|0x909
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
id|reg
op_assign
(paren
id|hwif-&gt;unit
ques
c_cond
l_int|0x4c
suffix:colon
l_int|0x44
)paren
op_plus
(paren
id|drive-&gt;select.b.unit
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|XFER_MW_DMA_2
)paren
op_eq
l_int|0
)paren
id|drv_ctrl
op_assign
l_int|0x0240
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|reg
comma
id|drv_ctrl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check to see if the drive and&n; * chipset is capable of DMA mode&n; */
DECL|function|sl82c105_check_drive
r_static
r_int
id|sl82c105_check_drive
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|on
op_assign
l_int|0
suffix:semicolon
r_do
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
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;autodma
)paren
r_break
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
)paren
r_break
suffix:semicolon
multiline_comment|/* Consult the list of known &quot;bad&quot; drives */
r_if
c_cond
(paren
id|udma_black_list
c_func
(paren
id|drive
)paren
)paren
(brace
id|on
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
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
l_int|7
op_logical_or
id|id-&gt;dma_1word
op_amp
l_int|7
)paren
id|on
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|udma_white_list
c_func
(paren
id|drive
)paren
)paren
(brace
id|on
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|config_for_dma
c_func
(paren
id|drive
)paren
suffix:semicolon
r_else
id|config_for_pio
c_func
(paren
id|drive
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|udma_enable
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
multiline_comment|/*&n; * Our very own dmaproc.  We need to intercept various calls&n; * to fix up the SL82C105 specific behaviour.&n; */
DECL|function|sl82c105_dmaproc
r_static
r_int
id|sl82c105_dmaproc
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_return
id|sl82c105_check_drive
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The SL82C105 holds off all IDE interrupts while in DMA mode until&n; * all DMA activity is completed.  Sometimes this causes problems (eg,&n; * when the drive wants to report an error condition).&n; *&n; * 0x7e is a &quot;chip testing&quot; register.  Bit 2 resets the DMA controller&n; * state machine.  We need to kick this to work around various bugs.&n; */
DECL|function|sl82c105_reset_host
r_static
r_inline
r_void
id|sl82c105_reset_host
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|val
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x7e
comma
op_amp
id|val
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x7e
comma
id|val
op_or
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x7e
comma
id|val
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
)brace
DECL|function|sl82c105_dma_enable
r_static
r_void
id|sl82c105_dma_enable
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
op_logical_or
id|config_for_dma
c_func
(paren
id|drive
)paren
)paren
(brace
id|config_for_pio
c_func
(paren
id|drive
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|on
op_assign
l_int|0
suffix:semicolon
)brace
id|udma_pci_enable
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
multiline_comment|/*&n; * ATAPI devices can cause the SL82C105 DMA state machine to go gaga.&n; * Winbond recommend that the DMA state machine is reset prior to&n; * setting the bus master DMA enable bit.&n; *&n; * The generic IDE core will have disabled the BMEN bit before this&n; * function is called.&n; */
DECL|function|sl82c105_dma_read
r_static
r_int
id|sl82c105_dma_read
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
id|sl82c105_reset_host
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
)paren
suffix:semicolon
r_return
id|udma_pci_read
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|sl82c105_dma_write
r_static
r_int
id|sl82c105_dma_write
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
id|sl82c105_reset_host
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
)paren
suffix:semicolon
r_return
id|udma_pci_write
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|sl82c105_timeout
r_static
r_void
id|sl82c105_timeout
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
id|sl82c105_reset_host
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If we get an IRQ timeout, it might be that the DMA state machine&n; * got confused.  Fix from Todd Inglett.  Details from Winbond.&n; *&n; * This function is called when the IDE timer expires, the drive&n; * indicates that it is READY, and we were waiting for DMA to complete.&n; */
DECL|function|sl82c105_lostirq
r_static
r_void
id|sl82c105_lostirq
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
id|pci_dev
op_star
id|dev
op_assign
id|ch-&gt;pci_dev
suffix:semicolon
id|u32
id|val
comma
id|mask
op_assign
id|ch-&gt;unit
ques
c_cond
id|CTRL_IDE_IRQB
suffix:colon
id|CTRL_IDE_IRQA
suffix:semicolon
r_int
r_int
id|dma_base
op_assign
id|ch-&gt;dma_base
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sl82c105: lost IRQ: resetting host&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check the raw interrupt from the drive.&n;&t; */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|mask
)paren
id|printk
c_func
(paren
l_string|&quot;sl82c105: drive was requesting IRQ, but host lost it&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Was DMA enabled?  If so, disable it - we&squot;re resetting the&n;&t; * host.  The IDE layer will be handling the drive for us.&n;&t; */
id|val
op_assign
id|inb
c_func
(paren
id|dma_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
id|outb
c_func
(paren
id|val
op_amp
op_complement
l_int|1
comma
id|dma_base
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sl82c105: DMA was enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|sl82c105_reset_host
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We only deal with PIO mode here - DMA mode &squot;using_dma&squot; is not&n; * initialised at the point that this function is called.&n; */
DECL|function|tune_sl82c105
r_static
r_void
id|tune_sl82c105
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
id|config_for_pio
c_func
(paren
id|drive
comma
id|pio
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We support 32-bit I/O on this interface, and it&n;&t; * doesn&squot;t have problems with interrupts.&n;&t; */
id|drive-&gt;channel-&gt;io_32bit
op_assign
l_int|1
suffix:semicolon
id|drive-&gt;channel-&gt;unmask
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the revision of the Winbond bridge&n; * which this function is part of.&n; */
DECL|function|sl82c105_bridge_revision
r_static
id|__init
r_int
r_int
id|sl82c105_bridge_revision
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
suffix:semicolon
r_int
r_char
id|rev
suffix:semicolon
multiline_comment|/*&n;&t; * The bridge should be part of the same device, but function 0.&n;&t; */
id|bridge
op_assign
id|pci_find_slot
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|PCI_DEVFN
c_func
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure it is a Winbond 553 and is an ISA bridge.&n;&t; */
r_if
c_cond
(paren
id|bridge-&gt;vendor
op_ne
id|PCI_VENDOR_ID_WINBOND
op_logical_or
id|bridge-&gt;device
op_ne
id|PCI_DEVICE_ID_WINBOND_83C553
op_logical_or
id|bridge
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_ne
id|PCI_CLASS_BRIDGE_ISA
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * We need to find function 0&squot;s revision, not function 1&n;&t; */
id|pci_read_config_byte
c_func
(paren
id|bridge
comma
id|PCI_REVISION_ID
comma
op_amp
id|rev
)paren
suffix:semicolon
r_return
id|rev
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable the PCI device&n; */
DECL|function|sl82c105_init_chipset
r_static
r_int
r_int
id|__init
id|sl82c105_init_chipset
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|val
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|val
)paren
suffix:semicolon
id|val
op_or_assign
id|CTRL_P0EN
op_or
id|CTRL_P0F16
op_or
id|CTRL_P1EN
op_or
id|CTRL_P1F16
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|val
)paren
suffix:semicolon
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|sl82c105_init_dma
r_static
r_void
id|__init
id|sl82c105_init_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
comma
r_int
r_int
id|dma_base
)paren
(brace
r_int
r_int
id|bridge_rev
suffix:semicolon
id|byte
id|dma_state
suffix:semicolon
id|dma_state
op_assign
id|inb
c_func
(paren
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
id|bridge_rev
op_assign
id|sl82c105_bridge_revision
c_func
(paren
id|ch-&gt;pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge_rev
op_le
l_int|5
)paren
(brace
id|ch-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|ch-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|ch-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    %s: Winbond 553 bridge revision %d, BM-DMA disabled&bslash;n&quot;
comma
id|ch-&gt;name
comma
id|bridge_rev
)paren
suffix:semicolon
id|dma_state
op_and_assign
op_complement
l_int|0x60
suffix:semicolon
)brace
r_else
(brace
id|dma_state
op_or_assign
l_int|0x60
suffix:semicolon
id|ch-&gt;autodma
op_assign
l_int|1
suffix:semicolon
)brace
id|outb
c_func
(paren
id|dma_state
comma
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
id|ata_init_dma
c_func
(paren
id|ch
comma
id|dma_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge_rev
op_le
l_int|5
)paren
id|ch-&gt;XXX_udma
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|ch-&gt;XXX_udma
op_assign
id|sl82c105_dmaproc
suffix:semicolon
id|ch-&gt;udma_enable
op_assign
id|sl82c105_dma_enable
suffix:semicolon
id|ch-&gt;udma_read
op_assign
id|sl82c105_dma_read
suffix:semicolon
id|ch-&gt;udma_write
op_assign
id|sl82c105_dma_write
suffix:semicolon
id|ch-&gt;udma_timeout
op_assign
id|sl82c105_timeout
suffix:semicolon
id|ch-&gt;udma_irq_lost
op_assign
id|sl82c105_lostirq
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialise the chip&n; */
DECL|function|sl82c105_init_channel
r_static
r_void
id|__init
id|sl82c105_init_channel
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
id|ch-&gt;tuneproc
op_assign
id|tune_sl82c105
suffix:semicolon
)brace
multiline_comment|/* module data table */
DECL|variable|__initdata
r_static
r_struct
id|ata_pci_device
id|chipset
id|__initdata
op_assign
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_WINBOND
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_WINBOND_82C105
comma
id|init_chipset
suffix:colon
id|sl82c105_init_chipset
comma
id|init_channel
suffix:colon
id|sl82c105_init_channel
comma
id|init_dma
suffix:colon
id|sl82c105_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x40
comma
l_int|0x10
comma
l_int|0x10
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
suffix:semicolon
DECL|function|init_sl82c105
r_int
id|__init
id|init_sl82c105
c_func
(paren
r_void
)paren
(brace
id|ata_register_chipset
c_func
(paren
op_amp
id|chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
