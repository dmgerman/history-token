multiline_comment|/*&n; * linux/drivers/ide/pci/cs5530.c&t;&t;Version 0.7&t;Sept 10, 2002&n; *&n; * Copyright (C) 2000&t;&t;&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * Ditto of GNU General Public License.&n; *&n; * Copyright (C) 2000&t;&t;&t;Mark Lord &lt;mlord@pobox.com&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; * Development of this chipset driver was funded&n; * by the nice folks at National Semiconductor.&n; *&n; * Documentation:&n; *&t;CS5530 documentation available from National Semiconductor.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/**&n; *&t;cs5530_xfer_set_mode&t;-&t;set a new transfer mode at the drive&n; *&t;@drive: drive to tune&n; *&t;@mode: new mode&n; *&n; *&t;Logging wrapper to the IDE driver speed configuration. This can&n; *&t;probably go away now.&n; */
DECL|function|cs5530_set_xfer_mode
r_static
r_int
id|cs5530_set_xfer_mode
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|mode
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: cs5530_set_xfer_mode(%s)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|ide_xfer_verbose
c_func
(paren
id|mode
)paren
)paren
suffix:semicolon
r_return
(paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|mode
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Here are the standard PIO mode 0-4 timings for each &quot;format&quot;.&n; * Format-0 uses fast data reg timings, with slower command reg timings.&n; * Format-1 uses fast timings for all registers, but won&squot;t work with all drives.&n; */
DECL|variable|cs5530_pio_timings
r_static
r_int
r_int
id|cs5530_pio_timings
(braket
l_int|2
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|0x00009172
comma
l_int|0x00012171
comma
l_int|0x00020080
comma
l_int|0x00032010
comma
l_int|0x00040010
)brace
comma
(brace
l_int|0xd1329172
comma
l_int|0x71212171
comma
l_int|0x30200080
comma
l_int|0x20102010
comma
l_int|0x00100010
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * After chip reset, the PIO timings are set to 0x0000e132, which is not valid.&n; */
DECL|macro|CS5530_BAD_PIO
mdefine_line|#define CS5530_BAD_PIO(timings) (((timings)&amp;~0x80000000)==0x0000e132)
DECL|macro|CS5530_BASEREG
mdefine_line|#define CS5530_BASEREG(hwif)&t;(((hwif)-&gt;dma_base &amp; ~0xf) + ((hwif)-&gt;channel ? 0x30 : 0x20))
multiline_comment|/**&n; *&t;cs5530_tuneproc&t;&t;-&t;select/set PIO modes&n; *&n; *&t;cs5530_tuneproc() handles selection/setting of PIO modes&n; *&t;for both the chipset and drive.&n; *&n; *&t;The ide_init_cs5530() routine guarantees that all drives&n; *&t;will have valid default PIO timings set up before we get here.&n; */
DECL|function|cs5530_tuneproc
r_static
r_void
id|cs5530_tuneproc
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
multiline_comment|/* pio=255 means &quot;autotune&quot; */
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
id|format
suffix:semicolon
r_int
r_int
id|basereg
op_assign
id|CS5530_BASEREG
c_func
(paren
id|hwif
)paren
suffix:semicolon
r_static
id|u8
id|modes
(braket
l_int|5
)braket
op_assign
(brace
id|XFER_PIO_0
comma
id|XFER_PIO_1
comma
id|XFER_PIO_2
comma
id|XFER_PIO_3
comma
id|XFER_PIO_4
)brace
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
l_int|4
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs5530_set_xfer_mode
c_func
(paren
id|drive
comma
id|modes
(braket
id|pio
)braket
)paren
)paren
(brace
id|format
op_assign
(paren
id|hwif
op_member_access_from_pointer
id|INL
c_func
(paren
id|basereg
op_plus
l_int|4
)paren
op_rshift
l_int|31
)paren
op_amp
l_int|1
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|cs5530_pio_timings
(braket
id|format
)braket
(braket
id|pio
)braket
comma
id|basereg
op_plus
(paren
id|drive-&gt;select.b.unit
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;cs5530_config_dma&t;-&t;select/set DMA and UDMA modes&n; *&t;@drive: drive to tune&n; *&n; *&t;cs5530_config_dma() handles selection/setting of DMA/UDMA modes&n; *&t;for both the chipset and drive. The CS5530 has limitations about&n; *&t;mixing DMA/UDMA on the same cable.&n; */
DECL|function|cs5530_config_dma
r_static
r_int
id|cs5530_config_dma
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_int
id|udma_ok
op_assign
l_int|1
comma
id|mode
op_assign
l_int|0
suffix:semicolon
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
id|unit
op_assign
id|drive-&gt;select.b.unit
suffix:semicolon
id|ide_drive_t
op_star
id|mate
op_assign
op_amp
id|hwif-&gt;drives
(braket
id|unit
op_xor
l_int|1
)braket
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
r_int
id|reg
comma
id|timings
suffix:semicolon
r_int
r_int
id|basereg
suffix:semicolon
multiline_comment|/*&n;&t; * Default to DMA-off in case we run into trouble here.&n;&t; */
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* turn off DMA while we fiddle */
id|hwif
op_member_access_from_pointer
id|ide_dma_host_off
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* clear DMA_capable bit */
multiline_comment|/*&n;&t; * The CS5530 specifies that two drives sharing a cable cannot&n;&t; * mix UDMA/MDMA.  It has to be one or the other, for the pair,&n;&t; * though different timings can still be chosen for each drive.&n;&t; * We could set the appropriate timing bits on the fly,&n;&t; * but that might be a bit confusing.  So, for now we statically&n;&t; * handle this requirement by looking at our mate drive to see&n;&t; * what it is capable of, before choosing a mode for our own drive.&n;&t; *&n;&t; * Note: This relies on the fact we never fail from UDMA to MWDMA_2&n;&t; * but instead drop to PIO&n;&t; */
r_if
c_cond
(paren
id|mate-&gt;present
)paren
(brace
r_struct
id|hd_driveid
op_star
id|mateid
op_assign
id|mate-&gt;id
suffix:semicolon
r_if
c_cond
(paren
id|mateid
op_logical_and
(paren
id|mateid-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
op_logical_neg
id|__ide_dma_bad_drive
c_func
(paren
id|mate
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|mateid-&gt;field_valid
op_amp
l_int|4
)paren
op_logical_and
(paren
id|mateid-&gt;dma_ultra
op_amp
l_int|7
)paren
)paren
id|udma_ok
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|mateid-&gt;field_valid
op_amp
l_int|2
)paren
op_logical_and
(paren
id|mateid-&gt;dma_mword
op_amp
l_int|7
)paren
)paren
id|udma_ok
op_assign
l_int|0
suffix:semicolon
r_else
id|udma_ok
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Now see what the current drive is capable of,&n;&t; * selecting UDMA only if the mate said it was ok.&n;&t; */
r_if
c_cond
(paren
id|id
op_logical_and
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
id|drive-&gt;autodma
op_logical_and
op_logical_neg
id|__ide_dma_bad_drive
c_func
(paren
id|drive
)paren
)paren
(brace
r_if
c_cond
(paren
id|udma_ok
op_logical_and
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|4
)paren
id|mode
op_assign
id|XFER_UDMA_2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|2
)paren
id|mode
op_assign
id|XFER_UDMA_1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|1
)paren
id|mode
op_assign
id|XFER_UDMA_0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mode
op_logical_and
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
op_logical_and
(paren
id|id-&gt;dma_mword
op_amp
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|4
)paren
id|mode
op_assign
id|XFER_MW_DMA_2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|2
)paren
id|mode
op_assign
id|XFER_MW_DMA_1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|1
)paren
id|mode
op_assign
id|XFER_MW_DMA_0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Tell the drive to switch to the new mode; abort on failure.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|mode
op_logical_or
id|cs5530_set_xfer_mode
c_func
(paren
id|drive
comma
id|mode
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* failure */
multiline_comment|/*&n;&t; * Now tune the chipset to match the drive:&n;&t; */
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|XFER_UDMA_0
suffix:colon
id|timings
op_assign
l_int|0x00921250
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
id|timings
op_assign
l_int|0x00911140
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
id|timings
op_assign
l_int|0x00911030
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
id|timings
op_assign
l_int|0x00077771
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
id|timings
op_assign
l_int|0x00012121
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
id|timings
op_assign
l_int|0x00002020
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: cs5530_config_dma: huh? mode=%02x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|mode
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* failure */
)brace
id|basereg
op_assign
id|CS5530_BASEREG
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|reg
op_assign
id|hwif
op_member_access_from_pointer
id|INL
c_func
(paren
id|basereg
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* get drive0 config register */
id|timings
op_or_assign
id|reg
op_amp
l_int|0x80000000
suffix:semicolon
multiline_comment|/* preserve PIO format bit */
r_if
c_cond
(paren
id|unit
op_eq
l_int|0
)paren
(brace
multiline_comment|/* are we configuring drive0? */
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|timings
comma
id|basereg
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* write drive0 config register */
)brace
r_else
(brace
r_if
c_cond
(paren
id|timings
op_amp
l_int|0x00100000
)paren
id|reg
op_or_assign
l_int|0x00100000
suffix:semicolon
multiline_comment|/* enable UDMA timings for both drives */
r_else
id|reg
op_and_assign
op_complement
l_int|0x00100000
suffix:semicolon
multiline_comment|/* disable UDMA timings for both drives */
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|reg
comma
id|basereg
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* write drive0 config register */
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|timings
comma
id|basereg
op_plus
l_int|12
)paren
suffix:semicolon
multiline_comment|/* write drive1 config register */
)brace
(paren
r_void
)paren
id|hwif
op_member_access_from_pointer
id|ide_dma_host_on
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* set DMA_capable bit */
multiline_comment|/*&n;&t; * Finally, turn DMA on in software, and exit.&n;&t; */
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
multiline_comment|/**&n; *&t;init_chipset_5530&t;-&t;set up 5530 bridge&n; *&t;@dev: PCI device&n; *&t;@name: device name&n; *&n; *&t;Initialize the cs5530 bridge for reliable IDE DMA operation.&n; */
DECL|function|init_chipset_cs5530
r_static
r_int
r_int
id|__init
id|init_chipset_cs5530
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|pci_dev
op_star
id|master_0
op_assign
l_int|NULL
comma
op_star
id|cs5530_0
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_CYRIX_PCI_MASTER
suffix:colon
id|master_0
op_assign
id|dev
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_CYRIX_5530_LEGACY
suffix:colon
id|cs5530_0
op_assign
id|dev
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|master_0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to locate PCI MASTER function&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cs5530_0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to locate CS5530 LEGACY function&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs (there should only be one CPU with this chipset) */
multiline_comment|/*&n;&t; * Enable BusMaster and MemoryWriteAndInvalidate for the cs5530:&n;&t; * --&gt;  OR 0x14 into 16-bit PCI COMMAND reg of function 0 of the cs5530&n;&t; */
id|pci_set_master
c_func
(paren
id|cs5530_0
)paren
suffix:semicolon
id|pci_set_mwi
c_func
(paren
id|cs5530_0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set PCI CacheLineSize to 16-bytes:&n;&t; * --&gt; Write 0x04 into 8-bit PCI CACHELINESIZE reg of function 0 of the cs5530&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|cs5530_0
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable trapping of UDMA register accesses (Win98 hack):&n;&t; * --&gt; Write 0x5006 into 16-bit reg at offset 0xd0 of function 0 of the cs5530&n;&t; */
id|pci_write_config_word
c_func
(paren
id|cs5530_0
comma
l_int|0xd0
comma
l_int|0x5006
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Bit-1 at 0x40 enables MemoryWriteAndInvalidate on internal X-bus:&n;&t; * The other settings are what is necessary to get the register&n;&t; * into a sane state for IDE DMA operation.&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|master_0
comma
l_int|0x40
comma
l_int|0x1e
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Set max PCI burst size (16-bytes seems to work best):&n;&t; *&t;   16bytes: set bit-1 at 0x41 (reg value of 0x16)&n;&t; *&t;all others: clear bit-1 at 0x41, and do:&n;&t; *&t;  128bytes: OR 0x00 at 0x41&n;&t; *&t;  256bytes: OR 0x04 at 0x41&n;&t; *&t;  512bytes: OR 0x08 at 0x41&n;&t; *&t; 1024bytes: OR 0x0c at 0x41&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|master_0
comma
l_int|0x41
comma
l_int|0x14
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * These settings are necessary to get the chip&n;&t; * into a sane state for IDE DMA operation.&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|master_0
comma
l_int|0x42
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|master_0
comma
l_int|0x43
comma
l_int|0xc1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;init_hwif_cs5530&t;-&t;initialise an IDE channel&n; *&t;@hwif: IDE to initialize&n; *&n; *&t;This gets invoked by the IDE driver once for each channel. It&n; *&t;performs channel-specific pre-initialization before drive probing.&n; */
DECL|function|init_hwif_cs5530
r_static
r_void
id|__init
id|init_hwif_cs5530
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_int
id|basereg
suffix:semicolon
id|u32
id|d0_timings
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;mate
)paren
id|hwif-&gt;serialized
op_assign
id|hwif-&gt;mate-&gt;serialized
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|cs5530_tuneproc
suffix:semicolon
id|basereg
op_assign
id|CS5530_BASEREG
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|d0_timings
op_assign
id|hwif
op_member_access_from_pointer
id|INL
c_func
(paren
id|basereg
op_plus
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CS5530_BAD_PIO
c_func
(paren
id|d0_timings
)paren
)paren
(brace
multiline_comment|/* PIO timings not initialized? */
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|cs5530_pio_timings
(braket
(paren
id|d0_timings
op_rshift
l_int|31
)paren
op_amp
l_int|1
)braket
(braket
l_int|0
)braket
comma
id|basereg
op_plus
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
)paren
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* needs autotuning later */
)brace
r_if
c_cond
(paren
id|CS5530_BAD_PIO
c_func
(paren
id|hwif
op_member_access_from_pointer
id|INL
c_func
(paren
id|basereg
op_plus
l_int|8
)paren
)paren
)paren
(brace
multiline_comment|/* PIO timings not initialized? */
id|hwif
op_member_access_from_pointer
id|OUTL
c_func
(paren
id|cs5530_pio_timings
(braket
(paren
id|d0_timings
op_rshift
l_int|31
)paren
op_amp
l_int|1
)braket
(braket
l_int|0
)braket
comma
id|basereg
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
)paren
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* needs autotuning later */
)brace
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|cs5530_config_dma
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
id|cs5530_chipset
id|__devinitdata
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CS5530&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cs5530
comma
dot
id|init_hwif
op_assign
id|init_hwif_cs5530
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
DECL|function|cs5530_init_one
r_static
r_int
id|__devinit
id|cs5530_init_one
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
id|cs5530_chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cs5530_pci_tbl
r_static
r_struct
id|pci_device_id
id|cs5530_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5530_IDE
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
id|cs5530_pci_tbl
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
l_string|&quot;CS5530 IDE&quot;
comma
dot
id|id_table
op_assign
id|cs5530_pci_tbl
comma
dot
id|probe
op_assign
id|cs5530_init_one
comma
)brace
suffix:semicolon
DECL|function|cs5530_ide_init
r_static
r_int
id|cs5530_ide_init
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
DECL|variable|cs5530_ide_init
id|module_init
c_func
(paren
id|cs5530_ide_init
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
l_string|&quot;PCI driver module for Cyrix/NS 5530 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
