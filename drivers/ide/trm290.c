multiline_comment|/*&n; *  linux/drivers/ide/trm290.c&t;&t;Version 1.02&t;Mar. 18, 2000&n; *&n; *  Copyright (c) 1997-1998  Mark Lord&n; *  May be copied or modified under the terms of the GNU General Public License&n; */
multiline_comment|/*&n; * This module provides support for the bus-master IDE DMA function&n; * of the Tekram TRM290 chip, used on a variety of PCI IDE add-on boards,&n; * including a &quot;Precision Instruments&quot; board.  The TRM290 pre-dates&n; * the sff-8038 standard (ide-dma.c) by a few months, and differs&n; * significantly enough to warrant separate routines for some functions,&n; * while re-using others from ide-dma.c.&n; *&n; * EXPERIMENTAL!  It works for me (a sample of one).&n; *&n; * Works reliably for me in DMA mode (READs only),&n; * DMA WRITEs are disabled by default (see #define below);&n; *&n; * DMA is not enabled automatically for this chipset,&n; * but can be turned on manually (with &quot;hdparm -d1&quot;) at run time.&n; *&n; * I need volunteers with &quot;spare&quot; drives for further testing&n; * and development, and maybe to help figure out the peculiarities.&n; * Even knowing the registers (below), some things behave strangely.&n; */
DECL|macro|TRM290_NO_DMA_WRITES
mdefine_line|#define TRM290_NO_DMA_WRITES&t;/* DMA writes seem unreliable sometimes */
multiline_comment|/*&n; * TRM-290 PCI-IDE2 Bus Master Chip&n; * ================================&n; * The configuration registers are addressed in normal I/O port space&n; * and are used as follows:&n; *&n; * trm290_base depends on jumper settings, and is probed for by ide-dma.c&n; *&n; * trm290_base+2 when WRITTEN: chiptest register (byte, write-only)&n; *&t;bit7 must always be written as &quot;1&quot;&n; *&t;bits6-2 undefined&n; *&t;bit1 1=legacy_compatible_mode, 0=native_pci_mode&n; *&t;bit0 1=test_mode, 0=normal(default)&n; *&n; * trm290_base+2 when READ: status register (byte, read-only)&n; *&t;bits7-2 undefined&n; *&t;bit1 channel0 busmaster interrupt status 0=none, 1=asserted&n; *&t;bit0 channel0 interrupt status 0=none, 1=asserted&n; *&n; * trm290_base+3 Interrupt mask register&n; *&t;bits7-5 undefined&n; *&t;bit4 legacy_header: 1=present, 0=absent&n; *&t;bit3 channel1 busmaster interrupt status 0=none, 1=asserted (read only)&n; *&t;bit2 channel1 interrupt status 0=none, 1=asserted (read only)&n; *&t;bit1 channel1 interrupt mask: 1=masked, 0=unmasked(default)&n; *&t;bit0 channel0 interrupt mask: 1=masked, 0=unmasked(default)&n; *&n; * trm290_base+1 &quot;CPR&quot; Config Pointer Register (byte)&n; *&t;bit7 1=autoincrement CPR bits 2-0 after each access of CDR&n; *&t;bit6 1=min. 1 wait-state posted write cycle (default), 0=0 wait-state&n; *&t;bit5 0=enabled master burst access (default), 1=disable  (write only)&n; *&t;bit4 PCI DEVSEL# timing select: 1=medium(default), 0=fast&n; *&t;bit3 0=primary IDE channel, 1=secondary IDE channel&n; *&t;bits2-0 register index for accesses through CDR port&n; *&n; * trm290_base+0 &quot;CDR&quot; Config Data Register (word)&n; *&t;two sets of seven config registers,&n; *&t;selected by CPR bit 3 (channel) and CPR bits 2-0 (index 0 to 6),&n; *&t;each index defined below:&n; *&n; * Index-0 Base address register for command block (word)&n; *&t;defaults: 0x1f0 for primary, 0x170 for secondary&n; *&n; * Index-1 general config register (byte)&n; *&t;bit7 1=DMA enable, 0=DMA disable&n; *&t;bit6 1=activate IDE_RESET, 0=no action (default)&n; *&t;bit5 1=enable IORDY, 0=disable IORDY (default)&n; *&t;bit4 0=16-bit data port(default), 1=8-bit (XT) data port&n; *&t;bit3 interrupt polarity: 1=active_low, 0=active_high(default)&n; *&t;bit2 power-saving-mode(?): 1=enable, 0=disable(default) (write only)&n; *&t;bit1 bus_master_mode(?): 1=enable, 0=disable(default)&n; *&t;bit0 enable_io_ports: 1=enable(default), 0=disable&n; *&n; * Index-2 read-ahead counter preload bits 0-7 (byte, write only)&n; *&t;bits7-0 bits7-0 of readahead count&n; *&n; * Index-3 read-ahead config register (byte, write only)&n; *&t;bit7 1=enable_readahead, 0=disable_readahead(default)&n; *&t;bit6 1=clear_FIFO, 0=no_action&n; *&t;bit5 undefined&n; *&t;bit4 mode4 timing control: 1=enable, 0=disable(default)&n; *&t;bit3 undefined&n; *&t;bit2 undefined&n; *&t;bits1-0 bits9-8 of read-ahead count&n; *&n; * Index-4 base address register for control block (word)&n; *&t;defaults: 0x3f6 for primary, 0x376 for secondary&n; *&n; * Index-5 data port timings (shared by both drives) (byte)&n; *&t;standard PCI &quot;clk&quot; (clock) counts, default value = 0xf5&n; *&n; *&t;bits7-6 setup time:  00=1clk, 01=2clk, 10=3clk, 11=4clk&n; *&t;bits5-3 hold time:&t;000=1clk, 001=2clk, 010=3clk,&n; *&t;&t;&t;&t;011=4clk, 100=5clk, 101=6clk,&n; *&t;&t;&t;&t;110=8clk, 111=12clk&n; *&t;bits2-0 active time:&t;000=2clk, 001=3clk, 010=4clk,&n; *&t;&t;&t;&t;011=5clk, 100=6clk, 101=8clk,&n; *&t;&t;&t;&t;110=12clk, 111=16clk&n; *&n; * Index-6 command/control port timings (shared by both drives) (byte)&n; *&t;same layout as Index-5, default value = 0xde&n; *&n; * Suggested CDR programming for PIO mode0 (600ns):&n; *&t;0x01f0,0x21,0xff,0x80,0x03f6,0xf5,0xde&t;; primary&n; *&t;0x0170,0x21,0xff,0x80,0x0376,0xf5,0xde&t;; secondary&n; *&n; * Suggested CDR programming for PIO mode3 (180ns):&n; *&t;0x01f0,0x21,0xff,0x80,0x03f6,0x09,0xde&t;; primary&n; *&t;0x0170,0x21,0xff,0x80,0x0376,0x09,0xde&t;; secondary&n; *&n; * Suggested CDR programming for PIO mode4 (120ns):&n; *&t;0x01f0,0x21,0xff,0x80,0x03f6,0x00,0xde&t;; primary&n; *&t;0x0170,0x21,0xff,0x80,0x0376,0x00,0xde&t;; secondary&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|trm290_prepare_drive
r_static
r_void
id|trm290_prepare_drive
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
id|reg
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* select PIO or DMA */
id|reg
op_assign
id|use_dma
ques
c_cond
(paren
l_int|0x21
op_or
l_int|0x82
)paren
suffix:colon
(paren
l_int|0x21
op_amp
op_complement
l_int|0x82
)paren
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_if
c_cond
(paren
id|reg
op_ne
id|hwif-&gt;select_data
)paren
(brace
id|hwif-&gt;select_data
op_assign
id|reg
suffix:semicolon
id|outb
c_func
(paren
l_int|0x51
op_or
(paren
id|hwif-&gt;channel
op_lshift
l_int|3
)paren
comma
id|hwif-&gt;config_data
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* set PIO/DMA */
id|outw
c_func
(paren
id|reg
op_amp
l_int|0xff
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
)brace
multiline_comment|/* enable IRQ if not probing */
r_if
c_cond
(paren
id|drive-&gt;present
)paren
(brace
id|reg
op_assign
id|inw
c_func
(paren
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
op_amp
l_int|0x13
suffix:semicolon
id|reg
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|hwif-&gt;channel
)paren
suffix:semicolon
id|outw
c_func
(paren
id|reg
comma
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
suffix:semicolon
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
)brace
DECL|function|trm290_selectproc
r_static
r_void
id|trm290_selectproc
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|trm290_prepare_drive
c_func
(paren
id|drive
comma
id|drive-&gt;using_dma
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
DECL|function|trm290_dmaproc
r_static
r_int
id|trm290_dmaproc
(paren
id|ide_dma_action_t
id|func
comma
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
r_int
r_int
id|count
comma
id|reading
op_assign
l_int|2
comma
id|writing
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|ide_dma_write
suffix:colon
id|reading
op_assign
l_int|0
suffix:semicolon
id|writing
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef TRM290_NO_DMA_WRITES
r_break
suffix:semicolon
multiline_comment|/* always use PIO for writes */
macro_line|#endif
r_case
id|ide_dma_read
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|count
op_assign
id|ide_build_dmatable
c_func
(paren
id|drive
comma
id|func
)paren
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* try PIO instead of DMA */
id|trm290_prepare_drive
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* select DMA xfer */
id|outl
c_func
(paren
id|hwif-&gt;dmatable_dma
op_or
id|reading
op_or
id|writing
comma
id|hwif-&gt;dma_base
)paren
suffix:semicolon
id|drive-&gt;waiting_for_dma
op_assign
l_int|1
suffix:semicolon
id|outw
c_func
(paren
(paren
id|count
op_star
l_int|2
)paren
op_minus
l_int|1
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* start DMA */
r_if
c_cond
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
r_return
l_int|0
suffix:semicolon
id|ide_set_handler
c_func
(paren
id|drive
comma
op_amp
id|ide_dma_intr
comma
id|WAIT_CMD
comma
l_int|NULL
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|reading
ques
c_cond
id|WIN_READDMA
suffix:colon
id|WIN_WRITEDMA
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|ide_dma_begin
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|ide_dma_end
suffix:colon
id|drive-&gt;waiting_for_dma
op_assign
l_int|0
suffix:semicolon
id|ide_destroy_dmatable
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* purge DMA mappings */
r_return
(paren
id|inw
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_ne
l_int|0x00ff
)paren
suffix:semicolon
r_case
id|ide_dma_test_irq
suffix:colon
r_return
(paren
id|inw
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_eq
l_int|0x00ff
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|ide_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
suffix:semicolon
)brace
id|trm290_prepare_drive
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* select PIO xfer */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
multiline_comment|/*&n; * Invoked from ide-dma.c at boot time.&n; */
DECL|function|ide_init_trm290
r_void
id|__init
id|ide_init_trm290
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_int
id|cfgbase
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|byte
id|reg
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|hwif-&gt;chipset
op_assign
id|ide_trm290
suffix:semicolon
id|cfgbase
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_amp
l_int|5
)paren
op_logical_and
id|cfgbase
)paren
(brace
id|hwif-&gt;config_data
op_assign
id|cfgbase
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;TRM290: chip config base at 0x%04lx&bslash;n&quot;
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
)brace
r_else
(brace
id|hwif-&gt;config_data
op_assign
l_int|0x3df0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;TRM290: using default config base at 0x%04lx&bslash;n&quot;
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
)brace
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
multiline_comment|/* put config reg into first byte of hwif-&gt;select_data */
id|outb
c_func
(paren
l_int|0x51
op_or
(paren
id|hwif-&gt;channel
op_lshift
l_int|3
)paren
comma
id|hwif-&gt;config_data
op_plus
l_int|1
)paren
suffix:semicolon
id|hwif-&gt;select_data
op_assign
l_int|0x21
suffix:semicolon
multiline_comment|/* select PIO as default */
id|outb
c_func
(paren
id|hwif-&gt;select_data
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
id|reg
op_assign
id|inb
c_func
(paren
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* get IRQ info */
id|reg
op_assign
(paren
id|reg
op_amp
l_int|0x10
)paren
op_or
l_int|0x03
suffix:semicolon
multiline_comment|/* mask IRQs for both ports */
id|outb
c_func
(paren
id|reg
comma
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x10
)paren
)paren
id|hwif-&gt;irq
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* legacy mode */
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
multiline_comment|/* sharing IRQ with mate */
id|ide_setup_dma
c_func
(paren
id|hwif
comma
(paren
id|hwif-&gt;config_data
op_plus
l_int|4
)paren
op_xor
(paren
id|hwif-&gt;channel
ques
c_cond
l_int|0x0080
suffix:colon
l_int|0x0000
)paren
comma
l_int|3
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
id|hwif-&gt;dmaproc
op_assign
op_amp
id|trm290_dmaproc
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
id|hwif-&gt;selectproc
op_assign
op_amp
id|trm290_selectproc
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* play it safe for now */
macro_line|#if 1
(brace
multiline_comment|/*&n;&t;&t; * My trm290-based card doesn&squot;t seem to work with all possible values&n;&t;&t; * for the control basereg, so this kludge ensures that we use only&n;&t;&t; * values that are known to work.  Ugh.&t;&t;-ml&n;&t;&t; */
r_int
r_int
id|old
comma
id|compat
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x374
suffix:colon
l_int|0x3f4
suffix:semicolon
r_static
r_int
r_int
id|next_offset
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
l_int|0x54
op_or
(paren
id|hwif-&gt;channel
op_lshift
l_int|3
)paren
comma
id|hwif-&gt;config_data
op_plus
l_int|1
)paren
suffix:semicolon
id|old
op_assign
id|inw
c_func
(paren
id|hwif-&gt;config_data
)paren
op_amp
op_complement
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|old
op_ne
id|compat
op_logical_and
id|inb
c_func
(paren
id|old
op_plus
l_int|2
)paren
op_eq
l_int|0xff
)paren
(brace
id|compat
op_add_assign
(paren
id|next_offset
op_add_assign
l_int|0x400
)paren
suffix:semicolon
multiline_comment|/* leave lower 10 bits untouched */
macro_line|#if 1
r_if
c_cond
(paren
id|ide_check_region
c_func
(paren
id|compat
op_plus
l_int|2
comma
l_int|1
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Aieee %s: ide_check_region failure at 0x%04x&bslash;n&quot;
comma
id|hwif-&gt;name
comma
(paren
id|compat
op_plus
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The region check is not needed; however.........&n;&t;&t;&t; * Since this is the checked in ide-probe.c,&n;&t;&t;&t; * this is only an assignment.&n;&t;&t;&t; */
macro_line|#endif
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|compat
op_plus
l_int|2
suffix:semicolon
id|outw
c_func
(paren
id|compat
op_or
l_int|1
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: control basereg workaround: old=0x%04x, new=0x%04x&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|old
comma
id|inw
c_func
(paren
id|hwif-&gt;config_data
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
eof
