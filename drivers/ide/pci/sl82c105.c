multiline_comment|/*&n; * linux/drivers/ide/pci/sl82c105.c&n; *&n; * SL82C105/Winbond 553 IDE driver&n; *&n; * Maintainer unknown.&n; *&n; * Drive tuning added from Rebel.com&squot;s kernel sources&n; *  -- Russell King (15/11/98) linux@arm.linux.org.uk&n; * &n; * Merge in Russell&squot;s HW workarounds, fix various problems&n; * with the timing registers setup.&n; *  -- Benjamin Herrenschmidt (01/11/03) benh@kernel.crashing.org&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(arg) printk arg
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt,...)
macro_line|#endif
multiline_comment|/*&n; * SL82C105 PCI config register 0x40 bits.&n; */
DECL|macro|CTRL_IDE_IRQB
mdefine_line|#define CTRL_IDE_IRQB   (1 &lt;&lt; 30)
DECL|macro|CTRL_IDE_IRQA
mdefine_line|#define CTRL_IDE_IRQA   (1 &lt;&lt; 28)
DECL|macro|CTRL_LEGIRQ
mdefine_line|#define CTRL_LEGIRQ     (1 &lt;&lt; 11)
DECL|macro|CTRL_P1F16
mdefine_line|#define CTRL_P1F16      (1 &lt;&lt; 5)
DECL|macro|CTRL_P1EN
mdefine_line|#define CTRL_P1EN       (1 &lt;&lt; 4)
DECL|macro|CTRL_P0F16
mdefine_line|#define CTRL_P0F16      (1 &lt;&lt; 1)
DECL|macro|CTRL_P0EN
mdefine_line|#define CTRL_P0EN       (1 &lt;&lt; 0)
multiline_comment|/*&n; * Convert a PIO mode and cycle time to the required on/off&n; * times for the interface.  This has protection against run-away&n; * timings.&n; */
DECL|function|get_timing_sl82c105
r_static
r_int
r_int
id|get_timing_sl82c105
c_func
(paren
id|ide_pio_data_t
op_star
id|p
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
id|ide_pio_timings
(braket
id|p-&gt;pio_mode
)braket
dot
id|active_time
op_plus
l_int|29
)paren
op_div
l_int|30
suffix:semicolon
id|cmd_off
op_assign
(paren
id|p-&gt;cycle_time
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
id|p-&gt;use_iordy
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
id|ide_drive_t
op_star
id|drive
comma
r_int
id|pio
comma
r_int
id|report
comma
r_int
id|chipset_only
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|ide_pio_data_t
id|p
suffix:semicolon
id|u16
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
id|DBG
c_func
(paren
(paren
l_string|&quot;config_for_pio(drive:%s, pio:%d, report:%d, chipset_only:%d)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
comma
id|report
comma
id|chipset_only
)paren
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|hwif-&gt;channel
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
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|5
comma
op_amp
id|p
)paren
suffix:semicolon
id|xfer_mode
op_assign
id|XFER_PIO_0
op_plus
id|pio
suffix:semicolon
r_if
c_cond
(paren
id|chipset_only
op_logical_or
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
(brace
id|drv_ctrl
op_assign
id|get_timing_sl82c105
c_func
(paren
op_amp
id|p
)paren
suffix:semicolon
id|drive-&gt;pio_speed
op_assign
id|xfer_mode
suffix:semicolon
)brace
r_else
id|drive-&gt;pio_speed
op_assign
id|XFER_PIO_0
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;using_dma
op_eq
l_int|0
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
id|p.cycle_time
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;config_for_dma(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|hwif-&gt;channel
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
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|reg
comma
l_int|0x0240
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
id|DBG
c_func
(paren
(paren
l_string|&quot;sl82c105_check_drive(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;autodma
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
id|__ide_dma_bad_drive
c_func
(paren
id|drive
)paren
)paren
r_break
suffix:semicolon
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
(paren
id|id-&gt;dma_mword
op_amp
id|hwif-&gt;mwdma_mask
)paren
op_logical_or
(paren
id|id-&gt;dma_1word
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__ide_dma_good_drive
c_func
(paren
id|drive
)paren
)paren
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
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
multiline_comment|/*&n; * If we get an IRQ timeout, it might be that the DMA state machine&n; * got confused.  Fix from Todd Inglett.  Details from Winbond.&n; *&n; * This function is called when the IDE timer expires, the drive&n; * indicates that it is READY, and we were waiting for DMA to complete.&n; */
DECL|function|sl82c105_ide_dma_lost_irq
r_static
r_int
id|sl82c105_ide_dma_lost_irq
c_func
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u32
id|val
comma
id|mask
op_assign
id|hwif-&gt;channel
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
id|hwif-&gt;dma_base
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
id|hwif
op_member_access_from_pointer
id|INB
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
multiline_comment|/* ide_dmaproc would return 1, so we do as well */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * ATAPI devices can cause the SL82C105 DMA state machine to go gaga.&n; * Winbond recommend that the DMA state machine is reset prior to&n; * setting the bus master DMA enable bit.&n; *&n; * The generic IDE core will have disabled the BMEN bit before this&n; * function is called.&n; */
DECL|function|sl82c105_ide_dma_begin
r_static
r_int
id|sl82c105_ide_dma_begin
c_func
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
singleline_comment|//&t;DBG((&quot;sl82c105_ide_dma_begin(drive:%s)&bslash;n&quot;, drive-&gt;name));
id|sl82c105_reset_host
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|__ide_dma_begin
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|sl82c105_ide_dma_timeout
r_static
r_int
id|sl82c105_ide_dma_timeout
c_func
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sl82c105_ide_dma_timeout(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
suffix:semicolon
id|sl82c105_reset_host
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|__ide_dma_timeout
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|sl82c105_ide_dma_on
r_static
r_int
id|sl82c105_ide_dma_on
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|DBG
c_func
(paren
(paren
l_string|&quot;sl82c105_ide_dma_on(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
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
comma
l_int|0
)paren
suffix:semicolon
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
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: DMA enabled&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
id|__ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|sl82c105_ide_dma_off_quietly
r_static
r_int
id|sl82c105_ide_dma_off_quietly
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|speed
op_assign
id|XFER_PIO_0
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sl82c105_ide_dma_off_quietly(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|__ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;pio_speed
)paren
id|speed
op_assign
id|drive-&gt;pio_speed
op_minus
id|XFER_PIO_0
suffix:semicolon
id|config_for_pio
c_func
(paren
id|drive
comma
id|speed
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|drive-&gt;current_speed
op_assign
id|drive-&gt;pio_speed
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, that is nasty, but we must make sure the DMA timings&n; * won&squot;t be used for a PIO access. The solution here is&n; * to make sure the 16 bits mode is diabled on the channel&n; * when DMA is enabled, thus causing the chip to use PIO0&n; * timings for those operations.&n; */
DECL|function|sl82c105_selectproc
r_static
r_void
id|sl82c105_selectproc
c_func
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u32
id|val
comma
id|old
comma
id|mask
suffix:semicolon
singleline_comment|//DBG((&quot;sl82c105_selectproc(drive:%s)&bslash;n&quot;, drive-&gt;name));
id|mask
op_assign
id|hwif-&gt;channel
ques
c_cond
id|CTRL_P1F16
suffix:colon
id|CTRL_P0F16
suffix:semicolon
id|old
op_assign
id|val
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
op_amp
id|hwif-&gt;hwif_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;using_dma
)paren
id|val
op_and_assign
op_complement
id|mask
suffix:semicolon
r_else
id|val
op_or_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|old
op_ne
id|val
)paren
(brace
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
op_star
(paren
(paren
id|u32
op_star
)paren
op_amp
id|hwif-&gt;hwif_data
)paren
op_assign
id|val
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * ATA reset will clear the 16 bits mode in the control&n; * register, we need to update our cache&n; */
DECL|function|sl82c105_resetproc
r_static
r_void
id|sl82c105_resetproc
c_func
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sl82c105_resetproc(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
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
op_star
(paren
(paren
id|u32
op_star
)paren
op_amp
id|hwif-&gt;hwif_data
)paren
op_assign
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * We only deal with PIO mode here - DMA mode &squot;using_dma&squot; is not&n; * initialised at the point that this function is called.&n; */
DECL|function|tune_sl82c105
r_static
r_void
id|tune_sl82c105
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
id|DBG
c_func
(paren
(paren
l_string|&quot;tune_sl82c105(drive:%s)&bslash;n&quot;
comma
id|drive-&gt;name
)paren
)paren
suffix:semicolon
id|config_for_pio
c_func
(paren
id|drive
comma
id|pio
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We support 32-bit I/O on this interface, and it&n;&t; * doesn&squot;t have problems with interrupts.&n;&t; */
id|drive-&gt;io_32bit
op_assign
l_int|1
suffix:semicolon
id|drive-&gt;unmask
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the revision of the Winbond bridge&n; * which this function is part of.&n; */
DECL|function|sl82c105_bridge_revision
r_static
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
id|u8
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
multiline_comment|/*&n; * Enable the PCI device&n; * &n; * --BenH: It&squot;s arch fixup code that should enable channels that&n; * have not been enabled by firmware. I decided we can still enable&n; * channel 0 here at least, but channel 1 has to be enabled by&n; * firmware or arch code. We still set both to 16 bits mode.&n; */
DECL|function|init_chipset_sl82c105
r_static
r_int
r_int
id|__init
id|init_chipset_sl82c105
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|msg
)paren
(brace
id|u32
id|val
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;init_chipset_sl82c105()&bslash;n&quot;
)paren
)paren
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
DECL|function|init_dma_sl82c105
r_static
r_void
id|__init
id|init_dma_sl82c105
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
r_int
id|dma_base
)paren
(brace
r_int
r_int
id|rev
suffix:semicolon
id|u8
id|dma_state
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;init_dma_sl82c105(hwif: ide%d, dma_base: 0x%08x)&bslash;n&quot;
comma
id|hwif-&gt;index
comma
id|dma_base
)paren
)paren
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_base
)paren
r_return
suffix:semicolon
id|dma_state
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
id|rev
op_assign
id|sl82c105_bridge_revision
c_func
(paren
id|hwif-&gt;pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev
op_le
l_int|5
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    %s: Winbond 553 bridge revision %d, BM-DMA disabled&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|rev
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
)brace
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|dma_state
comma
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
id|ide_setup_dma
c_func
(paren
id|hwif
comma
id|dma_base
comma
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise the chip&n; */
DECL|function|init_hwif_sl82c105
r_static
r_void
id|__init
id|init_hwif_sl82c105
c_func
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
id|u32
id|val
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;init_hwif_sl82c105(hwif: ide%d)&bslash;n&quot;
comma
id|hwif-&gt;index
)paren
)paren
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
id|tune_sl82c105
suffix:semicolon
id|hwif-&gt;selectproc
op_assign
id|sl82c105_selectproc
suffix:semicolon
id|hwif-&gt;resetproc
op_assign
id|sl82c105_resetproc
suffix:semicolon
multiline_comment|/* Default to PIO 0 for fallback unless tuned otherwise,&n;&t; * we always autotune PIO, this is done before DMA is&n;&t; * checked, so there is no risk of accidentally disabling&n;&t; * DMA&n;&t;  */
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|pio_speed
op_assign
id|XFER_PIO_0
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|pio_speed
op_assign
id|XFER_PIO_1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
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
op_star
(paren
(paren
id|u32
op_star
)paren
op_amp
id|hwif-&gt;hwif_data
)paren
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;dma_base
)paren
r_return
suffix:semicolon
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x07
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|sl82c105_check_drive
suffix:semicolon
id|hwif-&gt;ide_dma_on
op_assign
op_amp
id|sl82c105_ide_dma_on
suffix:semicolon
id|hwif-&gt;ide_dma_off_quietly
op_assign
op_amp
id|sl82c105_ide_dma_off_quietly
suffix:semicolon
id|hwif-&gt;ide_dma_lostirq
op_assign
op_amp
id|sl82c105_ide_dma_lost_irq
suffix:semicolon
id|hwif-&gt;ide_dma_begin
op_assign
op_amp
id|sl82c105_ide_dma_begin
suffix:semicolon
id|hwif-&gt;ide_dma_timeout
op_assign
op_amp
id|sl82c105_ide_dma_timeout
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
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
)brace
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|sl82c105_chipset
id|__devinitdata
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;W82C105&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_sl82c105
comma
dot
id|init_hwif
op_assign
id|init_hwif_sl82c105
comma
dot
id|init_dma
op_assign
id|init_dma_sl82c105
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|NOAUTODMA
comma
dot
id|enablebits
op_assign
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
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
suffix:semicolon
DECL|function|sl82c105_init_one
r_static
r_int
id|__devinit
id|sl82c105_init_one
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
id|sl82c105_chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sl82c105_pci_tbl
r_static
r_struct
id|pci_device_id
id|sl82c105_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
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
id|sl82c105_pci_tbl
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
l_string|&quot;W82C105 IDE&quot;
comma
dot
id|id_table
op_assign
id|sl82c105_pci_tbl
comma
dot
id|probe
op_assign
id|sl82c105_init_one
comma
)brace
suffix:semicolon
DECL|function|sl82c105_ide_init
r_static
r_int
id|sl82c105_ide_init
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
DECL|variable|sl82c105_ide_init
id|module_init
c_func
(paren
id|sl82c105_ide_init
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for W82C105 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
