macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/*&n; *&t;IDE library routines. These are plug in code that most &n; *&t;drivers can use but occasionally may be weird enough&n; *&t;to want to do their own thing with&n; *&n; *&t;Add common non I/O op stuff here. Make sure it has proper&n; *&t;kernel-doc function headers or your patch will be rejected&n; */
multiline_comment|/**&n; *&t;ide_xfer_verbose&t;-&t;return IDE mode names&n; *&t;@xfer_rate: rate to name&n; *&n; *&t;Returns a constant string giving the name of the mode&n; *&t;requested.&n; */
DECL|function|ide_xfer_verbose
r_char
op_star
id|ide_xfer_verbose
(paren
id|u8
id|xfer_rate
)paren
(brace
r_switch
c_cond
(paren
id|xfer_rate
)paren
(brace
r_case
id|XFER_UDMA_7
suffix:colon
r_return
l_string|&quot;UDMA 7&quot;
suffix:semicolon
r_case
id|XFER_UDMA_6
suffix:colon
r_return
l_string|&quot;UDMA 6&quot;
suffix:semicolon
r_case
id|XFER_UDMA_5
suffix:colon
r_return
l_string|&quot;UDMA 5&quot;
suffix:semicolon
r_case
id|XFER_UDMA_4
suffix:colon
r_return
l_string|&quot;UDMA 4&quot;
suffix:semicolon
r_case
id|XFER_UDMA_3
suffix:colon
r_return
l_string|&quot;UDMA 3&quot;
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
r_return
l_string|&quot;UDMA 2&quot;
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
r_return
l_string|&quot;UDMA 1&quot;
suffix:semicolon
r_case
id|XFER_UDMA_0
suffix:colon
r_return
l_string|&quot;UDMA 0&quot;
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_return
l_string|&quot;MW DMA 2&quot;
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_return
l_string|&quot;MW DMA 1&quot;
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_return
l_string|&quot;MW DMA 0&quot;
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_return
l_string|&quot;SW DMA 2&quot;
suffix:semicolon
r_case
id|XFER_SW_DMA_1
suffix:colon
r_return
l_string|&quot;SW DMA 1&quot;
suffix:semicolon
r_case
id|XFER_SW_DMA_0
suffix:colon
r_return
l_string|&quot;SW DMA 0&quot;
suffix:semicolon
r_case
id|XFER_PIO_4
suffix:colon
r_return
l_string|&quot;PIO 4&quot;
suffix:semicolon
r_case
id|XFER_PIO_3
suffix:colon
r_return
l_string|&quot;PIO 3&quot;
suffix:semicolon
r_case
id|XFER_PIO_2
suffix:colon
r_return
l_string|&quot;PIO 2&quot;
suffix:semicolon
r_case
id|XFER_PIO_1
suffix:colon
r_return
l_string|&quot;PIO 1&quot;
suffix:semicolon
r_case
id|XFER_PIO_0
suffix:colon
r_return
l_string|&quot;PIO 0&quot;
suffix:semicolon
r_case
id|XFER_PIO_SLOW
suffix:colon
r_return
l_string|&quot;PIO SLOW&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;XFER ERROR&quot;
suffix:semicolon
)brace
)brace
DECL|variable|ide_xfer_verbose
id|EXPORT_SYMBOL
c_func
(paren
id|ide_xfer_verbose
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;ide_dma_speed&t;-&t;compute DMA speed&n; *&t;@drive: drive&n; *&t;@mode; intended mode&n; *&n; *&t;Checks the drive capabilities and returns the speed to use&n; *&t;for the transfer. Returns -1 if the requested mode is unknown&n; *&t;(eg PIO)&n; */
DECL|function|ide_dma_speed
id|u8
id|ide_dma_speed
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|mode
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
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
id|u8
id|speed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;media
op_ne
id|ide_disk
op_logical_and
id|hwif-&gt;atapi_dma
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
l_int|0x04
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0040
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_6
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0x03
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0020
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_5
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0x02
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0010
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0008
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0x01
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0004
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0002
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0001
)paren
op_logical_and
(paren
id|id-&gt;dma_ultra
op_amp
id|hwif-&gt;ultra_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0x00
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0004
)paren
op_logical_and
(paren
id|id-&gt;dma_mword
op_amp
id|hwif-&gt;mwdma_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_MW_DMA_2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0002
)paren
op_logical_and
(paren
id|id-&gt;dma_mword
op_amp
id|hwif-&gt;mwdma_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_MW_DMA_1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0001
)paren
op_logical_and
(paren
id|id-&gt;dma_mword
op_amp
id|hwif-&gt;mwdma_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_MW_DMA_0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0004
)paren
op_logical_and
(paren
id|id-&gt;dma_1word
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_SW_DMA_2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0002
)paren
op_logical_and
(paren
id|id-&gt;dma_1word
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_SW_DMA_1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0001
)paren
op_logical_and
(paren
id|id-&gt;dma_1word
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
(brace
id|speed
op_assign
id|XFER_SW_DMA_0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
singleline_comment|//&t;printk(&quot;%s: %s: mode 0x%02x, speed 0x%02x&bslash;n&quot;,
singleline_comment|//&t;&t;__FUNCTION__, drive-&gt;name, mode, speed);
r_return
id|speed
suffix:semicolon
)brace
DECL|variable|ide_dma_speed
id|EXPORT_SYMBOL
c_func
(paren
id|ide_dma_speed
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;ide_rate_filter&t;&t;-&t;return best speed for mode&n; *&t;@mode: modes available&n; *&t;@speed: desired speed&n; *&n; *&t;Given the available DMA/UDMA mode this function returns&n; *&t;the best available speed at or below the speed requested.&n; */
DECL|function|ide_rate_filter
id|u8
id|ide_rate_filter
(paren
id|u8
id|mode
comma
id|u8
id|speed
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_static
id|u8
id|speed_max
(braket
)braket
op_assign
(brace
id|XFER_MW_DMA_2
comma
id|XFER_UDMA_2
comma
id|XFER_UDMA_4
comma
id|XFER_UDMA_5
comma
id|XFER_UDMA_6
)brace
suffix:semicolon
singleline_comment|//&t;printk(&quot;%s: mode 0x%02x, speed 0x%02x&bslash;n&quot;, __FUNCTION__, mode, speed);
multiline_comment|/* So that we remember to update this if new modes appear */
r_if
c_cond
(paren
id|mode
OG
l_int|4
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|min
c_func
(paren
id|speed
comma
id|speed_max
(braket
id|mode
)braket
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_BLK_DEV_IDEDMA */
r_return
id|min
c_func
(paren
id|speed
comma
(paren
id|u8
)paren
id|XFER_PIO_4
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
)brace
DECL|variable|ide_rate_filter
id|EXPORT_SYMBOL
c_func
(paren
id|ide_rate_filter
)paren
suffix:semicolon
DECL|function|ide_dma_enable
r_int
id|ide_dma_enable
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
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_return
(paren
(paren
r_int
)paren
(paren
(paren
(paren
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|8
)paren
op_amp
id|hwif-&gt;ultra_mask
)paren
op_logical_or
(paren
(paren
id|id-&gt;dma_mword
op_rshift
l_int|8
)paren
op_amp
id|hwif-&gt;mwdma_mask
)paren
op_logical_or
(paren
(paren
id|id-&gt;dma_1word
op_rshift
l_int|8
)paren
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ide_dma_enable
id|EXPORT_SYMBOL
c_func
(paren
id|ide_dma_enable
)paren
suffix:semicolon
multiline_comment|/*&n; * Standard (generic) timings for PIO modes, from ATA2 specification.&n; * These timings are for access to the IDE data port register *only*.&n; * Some drives may specify a mode, while also specifying a different&n; * value for cycle_time (from drive identification data).&n; */
DECL|variable|ide_pio_timings
r_const
id|ide_pio_timings_t
id|ide_pio_timings
(braket
l_int|6
)braket
op_assign
(brace
(brace
l_int|70
comma
l_int|165
comma
l_int|600
)brace
comma
multiline_comment|/* PIO Mode 0 */
(brace
l_int|50
comma
l_int|125
comma
l_int|383
)brace
comma
multiline_comment|/* PIO Mode 1 */
(brace
l_int|30
comma
l_int|100
comma
l_int|240
)brace
comma
multiline_comment|/* PIO Mode 2 */
(brace
l_int|30
comma
l_int|80
comma
l_int|180
)brace
comma
multiline_comment|/* PIO Mode 3 with IORDY */
(brace
l_int|25
comma
l_int|70
comma
l_int|120
)brace
comma
multiline_comment|/* PIO Mode 4 with IORDY */
(brace
l_int|20
comma
l_int|50
comma
l_int|100
)brace
multiline_comment|/* PIO Mode 5 with IORDY (nonstandard) */
)brace
suffix:semicolon
DECL|variable|ide_pio_timings
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ide_pio_timings
)paren
suffix:semicolon
multiline_comment|/*&n; * Shared data/functions for determining best PIO mode for an IDE drive.&n; * Most of this stuff originally lived in cmd640.c, and changes to the&n; * ide_pio_blacklist[] table should be made with EXTREME CAUTION to avoid&n; * breaking the fragile cmd640.c support.&n; */
multiline_comment|/*&n; * Black list. Some drives incorrectly report their maximal PIO mode,&n; * at least in respect to CMD640. Here we keep info on some known drives.&n; */
DECL|struct|ide_pio_info
r_static
r_struct
id|ide_pio_info
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|pio
r_int
id|pio
suffix:semicolon
DECL|variable|ide_pio_blacklist
)brace
id|ide_pio_blacklist
(braket
)braket
op_assign
(brace
multiline_comment|/*&t;{ &quot;Conner Peripherals 1275MB - CFS1275A&quot;, 4 }, */
(brace
l_string|&quot;Conner Peripherals 540MB - CFS540A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2700&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2540&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2420&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2340&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2250&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;WDC AC2200&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;WDC AC21200&quot;
comma
l_int|4
)brace
comma
(brace
l_string|&quot;WDC AC2120&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;WDC AC2850&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC1270&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC1170&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;WDC AC1210&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;WDC AC280&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*&t;{ &quot;WDC AC21000&quot;, 4 }, */
(brace
l_string|&quot;WDC AC31000&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC31200&quot;
comma
l_int|3
)brace
comma
multiline_comment|/*&t;{ &quot;WDC AC31600&quot;, 4 }, */
(brace
l_string|&quot;Maxtor 7131 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7171 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7213 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7245 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7345 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7546 AT&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;Maxtor 7540 AV&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3121A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3122A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3172A&quot;
comma
l_int|1
)brace
comma
multiline_comment|/*&t;{ &quot;ST51080A&quot;, 4 },&n; *&t;{ &quot;ST51270A&quot;, 4 },&n; *&t;{ &quot;ST31220A&quot;, 4 },&n; *&t;{ &quot;ST31640A&quot;, 4 },&n; *&t;{ &quot;ST32140A&quot;, 4 },&n; *&t;{ &quot;ST3780A&quot;,  4 },&n; */
(brace
l_string|&quot;ST5660A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3660A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3630A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3655A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3391A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3390A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;ST3600A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;ST3290A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ST3144A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ST3491A&quot;
comma
l_int|1
)brace
comma
multiline_comment|/* reports 3, should be 1 or 2 (depending on */
multiline_comment|/* drive) according to Seagates FIND-ATA program */
(brace
l_string|&quot;QUANTUM ELS127A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM ELS170A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM LPS240A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM LPS210A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS270A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS365A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS540A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LIGHTNING 540A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LIGHTNING 730A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM FIREBALL_540&quot;
comma
l_int|3
)brace
comma
multiline_comment|/* Older Quantum Fireballs don&squot;t work */
(brace
l_string|&quot;QUANTUM FIREBALL_640&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM FIREBALL_1080&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM FIREBALL_1280&quot;
comma
l_int|3
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;ide_scan_pio_blacklist &t;-&t;check for a blacklisted drive&n; *&t;@model: Drive model string&n; *&n; *&t;This routine searches the ide_pio_blacklist for an entry&n; *&t;matching the start/whole of the supplied model name.&n; *&n; *&t;Returns -1 if no match found.&n; *&t;Otherwise returns the recommended PIO mode from ide_pio_blacklist[].&n; */
DECL|function|ide_scan_pio_blacklist
r_static
r_int
id|ide_scan_pio_blacklist
(paren
r_char
op_star
id|model
)paren
(brace
r_struct
id|ide_pio_info
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|ide_pio_blacklist
suffix:semicolon
id|p-&gt;name
op_ne
l_int|NULL
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|p-&gt;name
comma
id|model
comma
id|strlen
c_func
(paren
id|p-&gt;name
)paren
)paren
op_eq
l_int|0
)paren
r_return
id|p-&gt;pio
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ide_get_best_pio_mode&t;-&t;get PIO mode from drive&n; *&t;@driver: drive to consider&n; *&t;@mode_wanted: preferred mode&n; *&t;@max_mode: highest allowed&n; *&t;@d: pio data&n; *&n; *&t;This routine returns the recommended PIO settings for a given drive,&n; *&t;based on the drive-&gt;id information and the ide_pio_blacklist[].&n; *&t;This is used by most chipset support modules when &quot;auto-tuning&quot;.&n; *&n; *&t;Drive PIO mode auto selection&n; */
DECL|function|ide_get_best_pio_mode
id|u8
id|ide_get_best_pio_mode
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|mode_wanted
comma
id|u8
id|max_mode
comma
id|ide_pio_data_t
op_star
id|d
)paren
(brace
r_int
id|pio_mode
suffix:semicolon
r_int
id|cycle_time
op_assign
l_int|0
suffix:semicolon
r_int
id|use_iordy
op_assign
l_int|0
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
id|overridden
op_assign
l_int|0
suffix:semicolon
r_int
id|blacklisted
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mode_wanted
op_ne
l_int|255
)paren
(brace
id|pio_mode
op_assign
id|mode_wanted
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;id
)paren
(brace
id|pio_mode
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pio_mode
op_assign
id|ide_scan_pio_blacklist
c_func
(paren
id|id-&gt;model
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|overridden
op_assign
l_int|1
suffix:semicolon
id|blacklisted
op_assign
l_int|1
suffix:semicolon
id|use_iordy
op_assign
(paren
id|pio_mode
OG
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|pio_mode
op_assign
id|id-&gt;tPIO
suffix:semicolon
r_if
c_cond
(paren
id|pio_mode
OG
l_int|2
)paren
(brace
multiline_comment|/* 2 is maximum allowed tPIO value */
id|pio_mode
op_assign
l_int|2
suffix:semicolon
id|overridden
op_assign
l_int|1
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
multiline_comment|/* drive implements ATA2? */
r_if
c_cond
(paren
id|id-&gt;capability
op_amp
l_int|8
)paren
(brace
multiline_comment|/* drive supports use_iordy? */
id|use_iordy
op_assign
l_int|1
suffix:semicolon
id|cycle_time
op_assign
id|id-&gt;eide_pio_iordy
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|7
)paren
(brace
id|overridden
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|4
)paren
id|pio_mode
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|2
)paren
id|pio_mode
op_assign
l_int|4
suffix:semicolon
r_else
id|pio_mode
op_assign
l_int|3
suffix:semicolon
)brace
)brace
r_else
(brace
id|cycle_time
op_assign
id|id-&gt;eide_pio
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|drive-&gt;id-&gt;major_rev_num
op_amp
l_int|0x0004
)paren
id|printk
c_func
(paren
l_string|&quot;ATA-2 &quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Conservative &quot;downgrade&quot; for all pre-ATA2 drives&n;&t;&t; */
r_if
c_cond
(paren
id|pio_mode
op_logical_and
id|pio_mode
OL
l_int|4
)paren
(brace
id|pio_mode
op_decrement
suffix:semicolon
id|overridden
op_assign
l_int|1
suffix:semicolon
macro_line|#if 0
id|use_iordy
op_assign
(paren
id|pio_mode
OG
l_int|2
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|cycle_time
op_logical_and
id|cycle_time
OL
id|ide_pio_timings
(braket
id|pio_mode
)braket
dot
id|cycle_time
)paren
id|cycle_time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* use standard timing */
)brace
)brace
r_if
c_cond
(paren
id|pio_mode
OG
id|max_mode
)paren
(brace
id|pio_mode
op_assign
id|max_mode
suffix:semicolon
id|cycle_time
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
)paren
(brace
id|d-&gt;pio_mode
op_assign
id|pio_mode
suffix:semicolon
id|d-&gt;cycle_time
op_assign
id|cycle_time
ques
c_cond
id|cycle_time
suffix:colon
id|ide_pio_timings
(braket
id|pio_mode
)braket
dot
id|cycle_time
suffix:semicolon
id|d-&gt;use_iordy
op_assign
id|use_iordy
suffix:semicolon
id|d-&gt;overridden
op_assign
id|overridden
suffix:semicolon
id|d-&gt;blacklisted
op_assign
id|blacklisted
suffix:semicolon
)brace
r_return
id|pio_mode
suffix:semicolon
)brace
DECL|variable|ide_get_best_pio_mode
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ide_get_best_pio_mode
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;ide_toggle_bounce&t;-&t;handle bounce buffering&n; *&t;@drive: drive to update&n; *&t;@on: on/off boolean&n; *&n; *&t;Enable or disable bounce buffering for the device. Drives move&n; *&t;between PIO and DMA and that changes the rules we need.&n; */
DECL|function|ide_toggle_bounce
r_void
id|ide_toggle_bounce
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|on
)paren
(brace
id|u64
id|addr
op_assign
id|BLK_BOUNCE_HIGH
suffix:semicolon
multiline_comment|/* dma64_addr_t */
r_if
c_cond
(paren
id|on
op_logical_and
id|drive-&gt;media
op_eq
id|ide_disk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PCI_DMA_BUS_IS_PHYS
)paren
id|addr
op_assign
id|BLK_BOUNCE_ANY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
)paren
id|addr
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev-&gt;dma_mask
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drive-&gt;queue
)paren
id|blk_queue_bounce_limit
c_func
(paren
id|drive-&gt;queue
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|variable|ide_toggle_bounce
id|EXPORT_SYMBOL
c_func
(paren
id|ide_toggle_bounce
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;ide_set_xfer_rate&t;-&t;set transfer rate&n; *&t;@drive: drive to set&n; *&t;@speed: speed to attempt to set&n; *&t;&n; *&t;General helper for setting the speed of an IDE device. This&n; *&t;function knows about user enforced limits from the configuration&n; *&t;which speedproc() does not.  High level drivers should never&n; *&t;invoke speedproc() directly.&n; */
DECL|function|ide_set_xfer_rate
r_int
id|ide_set_xfer_rate
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|rate
)paren
(brace
macro_line|#ifndef CONFIG_BLK_DEV_IDEDMA
id|rate
op_assign
id|min
c_func
(paren
id|rate
comma
(paren
id|u8
)paren
id|XFER_PIO_4
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|speedproc
)paren
(brace
r_return
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|speedproc
c_func
(paren
id|drive
comma
id|rate
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|ide_set_xfer_rate
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ide_set_xfer_rate
)paren
suffix:semicolon
eof
