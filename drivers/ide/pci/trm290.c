multiline_comment|/*&n; *  linux/drivers/ide/pci/trm290.c&t;&t;Version 1.02&t;Mar. 18, 2000&n; *&n; *  Copyright (c) 1997-1998  Mark Lord&n; *  May be copied or modified under the terms of the GNU General Public License&n; *&n; *  June 22, 2004 - get rid of check_region&n; *                  Jesper Juhl &lt;juhl-lkml@dif.dk&gt;&n; *&n; */
multiline_comment|/*&n; * This module provides support for the bus-master IDE DMA function&n; * of the Tekram TRM290 chip, used on a variety of PCI IDE add-on boards,&n; * including a &quot;Precision Instruments&quot; board.  The TRM290 pre-dates&n; * the sff-8038 standard (ide-dma.c) by a few months, and differs&n; * significantly enough to warrant separate routines for some functions,&n; * while re-using others from ide-dma.c.&n; *&n; * EXPERIMENTAL!  It works for me (a sample of one).&n; *&n; * Works reliably for me in DMA mode (READs only),&n; * DMA WRITEs are disabled by default (see #define below);&n; *&n; * DMA is not enabled automatically for this chipset,&n; * but can be turned on manually (with &quot;hdparm -d1&quot;) at run time.&n; *&n; * I need volunteers with &quot;spare&quot; drives for further testing&n; * and development, and maybe to help figure out the peculiarities.&n; * Even knowing the registers (below), some things behave strangely.&n; */
DECL|macro|TRM290_NO_DMA_WRITES
mdefine_line|#define TRM290_NO_DMA_WRITES&t;/* DMA writes seem unreliable sometimes */
multiline_comment|/*&n; * TRM-290 PCI-IDE2 Bus Master Chip&n; * ================================&n; * The configuration registers are addressed in normal I/O port space&n; * and are used as follows:&n; *&n; * trm290_base depends on jumper settings, and is probed for by ide-dma.c&n; *&n; * trm290_base+2 when WRITTEN: chiptest register (byte, write-only)&n; *&t;bit7 must always be written as &quot;1&quot;&n; *&t;bits6-2 undefined&n; *&t;bit1 1=legacy_compatible_mode, 0=native_pci_mode&n; *&t;bit0 1=test_mode, 0=normal(default)&n; *&n; * trm290_base+2 when READ: status register (byte, read-only)&n; *&t;bits7-2 undefined&n; *&t;bit1 channel0 busmaster interrupt status 0=none, 1=asserted&n; *&t;bit0 channel0 interrupt status 0=none, 1=asserted&n; *&n; * trm290_base+3 Interrupt mask register&n; *&t;bits7-5 undefined&n; *&t;bit4 legacy_header: 1=present, 0=absent&n; *&t;bit3 channel1 busmaster interrupt status 0=none, 1=asserted (read only)&n; *&t;bit2 channel1 interrupt status 0=none, 1=asserted (read only)&n; *&t;bit1 channel1 interrupt mask: 1=masked, 0=unmasked(default)&n; *&t;bit0 channel0 interrupt mask: 1=masked, 0=unmasked(default)&n; *&n; * trm290_base+1 &quot;CPR&quot; Config Pointer Register (byte)&n; *&t;bit7 1=autoincrement CPR bits 2-0 after each access of CDR&n; *&t;bit6 1=min. 1 wait-state posted write cycle (default), 0=0 wait-state&n; *&t;bit5 0=enabled master burst access (default), 1=disable  (write only)&n; *&t;bit4 PCI DEVSEL# timing select: 1=medium(default), 0=fast&n; *&t;bit3 0=primary IDE channel, 1=secondary IDE channel&n; *&t;bits2-0 register index for accesses through CDR port&n; *&n; * trm290_base+0 &quot;CDR&quot; Config Data Register (word)&n; *&t;two sets of seven config registers,&n; *&t;selected by CPR bit 3 (channel) and CPR bits 2-0 (index 0 to 6),&n; *&t;each index defined below:&n; *&n; * Index-0 Base address register for command block (word)&n; *&t;defaults: 0x1f0 for primary, 0x170 for secondary&n; *&n; * Index-1 general config register (byte)&n; *&t;bit7 1=DMA enable, 0=DMA disable&n; *&t;bit6 1=activate IDE_RESET, 0=no action (default)&n; *&t;bit5 1=enable IORDY, 0=disable IORDY (default)&n; *&t;bit4 0=16-bit data port(default), 1=8-bit (XT) data port&n; *&t;bit3 interrupt polarity: 1=active_low, 0=active_high(default)&n; *&t;bit2 power-saving-mode(?): 1=enable, 0=disable(default) (write only)&n; *&t;bit1 bus_master_mode(?): 1=enable, 0=disable(default)&n; *&t;bit0 enable_io_ports: 1=enable(default), 0=disable&n; *&n; * Index-2 read-ahead counter preload bits 0-7 (byte, write only)&n; *&t;bits7-0 bits7-0 of readahead count&n; *&n; * Index-3 read-ahead config register (byte, write only)&n; *&t;bit7 1=enable_readahead, 0=disable_readahead(default)&n; *&t;bit6 1=clear_FIFO, 0=no_action&n; *&t;bit5 undefined&n; *&t;bit4 mode4 timing control: 1=enable, 0=disable(default)&n; *&t;bit3 undefined&n; *&t;bit2 undefined&n; *&t;bits1-0 bits9-8 of read-ahead count&n; *&n; * Index-4 base address register for control block (word)&n; *&t;defaults: 0x3f6 for primary, 0x376 for secondary&n; *&n; * Index-5 data port timings (shared by both drives) (byte)&n; *&t;standard PCI &quot;clk&quot; (clock) counts, default value = 0xf5&n; *&n; *&t;bits7-6 setup time:  00=1clk, 01=2clk, 10=3clk, 11=4clk&n; *&t;bits5-3 hold time:&t;000=1clk, 001=2clk, 010=3clk,&n; *&t;&t;&t;&t;011=4clk, 100=5clk, 101=6clk,&n; *&t;&t;&t;&t;110=8clk, 111=12clk&n; *&t;bits2-0 active time:&t;000=2clk, 001=3clk, 010=4clk,&n; *&t;&t;&t;&t;011=5clk, 100=6clk, 101=8clk,&n; *&t;&t;&t;&t;110=12clk, 111=16clk&n; *&n; * Index-6 command/control port timings (shared by both drives) (byte)&n; *&t;same layout as Index-5, default value = 0xde&n; *&n; * Suggested CDR programming for PIO mode0 (600ns):&n; *&t;0x01f0,0x21,0xff,0x80,0x03f6,0xf5,0xde&t;; primary&n; *&t;0x0170,0x21,0xff,0x80,0x0376,0xf5,0xde&t;; secondary&n; *&n; * Suggested CDR programming for PIO mode3 (180ns):&n; *&t;0x01f0,0x21,0xff,0x80,0x03f6,0x09,0xde&t;; primary&n; *&t;0x0170,0x21,0xff,0x80,0x0376,0x09,0xde&t;; secondary&n; *&n; * Suggested CDR programming for PIO mode4 (120ns):&n; *&t;0x01f0,0x21,0xff,0x80,0x03f6,0x00,0xde&t;; primary&n; *&t;0x0170,0x21,0xff,0x80,0x0376,0x00,0xde&t;; secondary&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
id|u16
id|reg
op_assign
l_int|0
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
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
multiline_comment|/* set PIO/DMA */
id|hwif
op_member_access_from_pointer
id|OUTB
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
id|hwif
op_member_access_from_pointer
id|OUTW
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
id|hwif
op_member_access_from_pointer
id|INW
c_func
(paren
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
suffix:semicolon
id|reg
op_and_assign
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
id|hwif
op_member_access_from_pointer
id|OUTW
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
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
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
DECL|function|trm290_ide_dma_write
r_static
r_int
id|trm290_ide_dma_write
(paren
id|ide_drive_t
op_star
id|drive
multiline_comment|/*, struct request *rq */
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
id|request
op_star
id|rq
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
suffix:semicolon
singleline_comment|//&t;ide_task_t *args&t;= rq-&gt;special;
id|task_ioreg_t
id|command
op_assign
id|WIN_NOP
suffix:semicolon
r_if
c_cond
(paren
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|handler
op_ne
l_int|NULL
)paren
multiline_comment|/* paranoia check */
id|BUG
c_func
(paren
)paren
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
multiline_comment|/*&n;&t; * FIX ME to use only ACB ide_task_t args Struct&n;&t; */
macro_line|#if 0
(brace
id|ide_task_t
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|command
op_assign
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
suffix:semicolon
)brace
macro_line|#else
id|command
op_assign
multiline_comment|/* (lba48) ? WIN_READDMA_EXT : */
id|WIN_READDMA
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;flags
op_amp
id|REQ_DRIVE_TASKFILE
)paren
(brace
id|ide_task_t
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|command
op_assign
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* issue cmd to drive */
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|command
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_begin
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|trm290_ide_dma_read
r_static
r_int
id|trm290_ide_dma_read
(paren
id|ide_drive_t
op_star
id|drive
multiline_comment|/*, struct request *rq */
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
id|request
op_star
id|rq
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
suffix:semicolon
singleline_comment|//&t;ide_task_t *args&t;= rq-&gt;special;
id|task_ioreg_t
id|command
op_assign
id|WIN_NOP
suffix:semicolon
r_if
c_cond
(paren
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|handler
op_ne
l_int|NULL
)paren
multiline_comment|/* paranoia check */
id|BUG
c_func
(paren
)paren
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
multiline_comment|/*&n;&t; * FIX ME to use only ACB ide_task_t args Struct&n;&t; */
macro_line|#if 0
(brace
id|ide_task_t
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|command
op_assign
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
suffix:semicolon
)brace
macro_line|#else
id|command
op_assign
multiline_comment|/* (lba48) ? WIN_WRITEDMA_EXT : */
id|WIN_WRITEDMA
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;flags
op_amp
id|REQ_DRIVE_TASKFILE
)paren
(brace
id|ide_task_t
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|command
op_assign
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* issue cmd to drive */
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|command
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_begin
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|trm290_ide_dma_setup
r_static
r_int
id|trm290_ide_dma_setup
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
id|drive-&gt;hwif
suffix:semicolon
r_struct
id|request
op_star
id|rq
op_assign
id|hwif-&gt;hwgroup-&gt;rq
suffix:semicolon
r_int
r_int
id|count
comma
id|rw
suffix:semicolon
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|rq
)paren
)paren
(brace
macro_line|#ifdef TRM290_NO_DMA_WRITES
multiline_comment|/* always use PIO for writes */
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
macro_line|#endif
id|rw
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|rw
op_assign
l_int|2
suffix:semicolon
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
id|rq
)paren
)paren
)paren
(brace
multiline_comment|/* try PIO instead of DMA */
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
multiline_comment|/* select DMA xfer */
id|trm290_prepare_drive
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|hwif-&gt;dmatable_dma
op_or
id|rw
comma
id|hwif-&gt;dma_command
)paren
suffix:semicolon
id|drive-&gt;waiting_for_dma
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* start DMA */
id|hwif
op_member_access_from_pointer
id|OUTW
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
id|hwif-&gt;dma_status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|trm290_ide_dma_begin
r_static
r_int
id|trm290_ide_dma_begin
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|trm290_ide_dma_end
r_static
r_int
id|trm290_ide_dma_end
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
id|u16
id|status
op_assign
l_int|0
suffix:semicolon
id|drive-&gt;waiting_for_dma
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* purge DMA mappings */
id|ide_destroy_dmatable
c_func
(paren
id|drive
)paren
suffix:semicolon
id|status
op_assign
id|hwif
op_member_access_from_pointer
id|INW
c_func
(paren
id|hwif-&gt;dma_status
)paren
suffix:semicolon
r_return
(paren
id|status
op_ne
l_int|0x00ff
)paren
suffix:semicolon
)brace
DECL|function|trm290_ide_dma_test_irq
r_static
r_int
id|trm290_ide_dma_test_irq
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
id|u16
id|status
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|hwif
op_member_access_from_pointer
id|INW
c_func
(paren
id|hwif-&gt;dma_status
)paren
suffix:semicolon
r_return
(paren
id|status
op_eq
l_int|0x00ff
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
multiline_comment|/*&n; * Invoked from ide-dma.c at boot time.&n; */
DECL|function|init_hwif_trm290
r_void
id|__devinit
id|init_hwif_trm290
c_func
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
id|u8
id|reg
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|hwif-&gt;no_lba48
op_assign
l_int|1
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
id|KERN_INFO
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
id|KERN_INFO
l_string|&quot;TRM290: using default config base at 0x%04lx&bslash;n&quot;
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* put config reg into first byte of hwif-&gt;select_data */
id|hwif
op_member_access_from_pointer
id|OUTB
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
multiline_comment|/* select PIO as default */
id|hwif-&gt;select_data
op_assign
l_int|0x21
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|hwif-&gt;select_data
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
multiline_comment|/* get IRQ info */
id|reg
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* mask IRQs for both ports */
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
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|reg
comma
id|hwif-&gt;config_data
op_plus
l_int|3
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x10
)paren
)paren
multiline_comment|/* legacy mode */
id|hwif-&gt;irq
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
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
multiline_comment|/* sharing IRQ with mate */
id|hwif-&gt;irq
op_assign
id|hwif-&gt;mate-&gt;irq
suffix:semicolon
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
id|hwif-&gt;dma_setup
op_assign
op_amp
id|trm290_ide_dma_setup
suffix:semicolon
id|hwif-&gt;ide_dma_write
op_assign
op_amp
id|trm290_ide_dma_write
suffix:semicolon
id|hwif-&gt;ide_dma_read
op_assign
op_amp
id|trm290_ide_dma_read
suffix:semicolon
id|hwif-&gt;ide_dma_begin
op_assign
op_amp
id|trm290_ide_dma_begin
suffix:semicolon
id|hwif-&gt;ide_dma_end
op_assign
op_amp
id|trm290_ide_dma_end
suffix:semicolon
id|hwif-&gt;ide_dma_test_irq
op_assign
op_amp
id|trm290_ide_dma_test_irq
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
macro_line|#if 1
(brace
multiline_comment|/*&n;&t; * My trm290-based card doesn&squot;t seem to work with all possible values&n;&t; * for the control basereg, so this kludge ensures that we use only&n;&t; * values that are known to work.  Ugh.&t;&t;-ml&n;&t; */
id|u16
r_new
comma
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
id|u16
id|next_offset
op_assign
l_int|0
suffix:semicolon
id|u8
id|old_mask
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
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
id|hwif
op_member_access_from_pointer
id|INW
c_func
(paren
id|hwif-&gt;config_data
)paren
suffix:semicolon
id|old
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|old_mask
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|old
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_ne
id|compat
op_logical_and
id|old_mask
op_eq
l_int|0xff
)paren
(brace
multiline_comment|/* leave lower 10 bits untouched */
id|compat
op_add_assign
(paren
id|next_offset
op_add_assign
l_int|0x400
)paren
suffix:semicolon
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|compat
op_plus
l_int|2
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTW
c_func
(paren
id|compat
op_or
l_int|1
comma
id|hwif-&gt;config_data
)paren
suffix:semicolon
r_new
op_assign
id|hwif
op_member_access_from_pointer
id|INW
c_func
(paren
id|hwif-&gt;config_data
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: control basereg workaround: &quot;
l_string|&quot;old=0x%04x, new=0x%04x&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|old
comma
r_new
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|trm290_chipset
id|__devinitdata
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;TRM290&quot;
comma
dot
id|init_hwif
op_assign
id|init_hwif_trm290
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
id|bootable
op_assign
id|ON_BOARD
comma
)brace
suffix:semicolon
DECL|function|trm290_init_one
r_static
r_int
id|__devinit
id|trm290_init_one
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
id|trm290_chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|trm290_pci_tbl
r_static
r_struct
id|pci_device_id
id|trm290_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_TEKRAM
comma
id|PCI_DEVICE_ID_TEKRAM_DC290
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
id|trm290_pci_tbl
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
l_string|&quot;TRM290_IDE&quot;
comma
dot
id|id_table
op_assign
id|trm290_pci_tbl
comma
dot
id|probe
op_assign
id|trm290_init_one
comma
)brace
suffix:semicolon
DECL|function|trm290_ide_init
r_static
r_int
id|trm290_ide_init
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
DECL|variable|trm290_ide_init
id|module_init
c_func
(paren
id|trm290_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark Lord&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for Tekram TRM290 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
