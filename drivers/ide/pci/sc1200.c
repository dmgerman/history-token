multiline_comment|/*&n; * linux/drivers/ide/pci/sc1200.c&t;&t;Version 0.91&t;28-Jan-2003&n; *&n; * Copyright (C) 2000-2002&t;&t;Mark Lord &lt;mlord@pobox.com&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; * Development of this chipset driver was funded&n; * by the nice folks at National Semiconductor.&n; *&n; * Documentation:&n; *&t;Available from National Semiconductor&n; */
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
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sc1200.h&quot;
DECL|macro|SC1200_REV_A
mdefine_line|#define SC1200_REV_A&t;0x00
DECL|macro|SC1200_REV_B1
mdefine_line|#define SC1200_REV_B1&t;0x01
DECL|macro|SC1200_REV_B3
mdefine_line|#define SC1200_REV_B3&t;0x02
DECL|macro|SC1200_REV_C1
mdefine_line|#define SC1200_REV_C1&t;0x03
DECL|macro|SC1200_REV_D1
mdefine_line|#define SC1200_REV_D1&t;0x04
DECL|macro|PCI_CLK_33
mdefine_line|#define PCI_CLK_33&t;0x00
DECL|macro|PCI_CLK_48
mdefine_line|#define PCI_CLK_48&t;0x01
DECL|macro|PCI_CLK_66
mdefine_line|#define PCI_CLK_66&t;0x02
DECL|macro|PCI_CLK_33A
mdefine_line|#define PCI_CLK_33A&t;0x03
DECL|function|sc1200_get_pci_clock
r_static
r_int
r_int
id|sc1200_get_pci_clock
(paren
r_void
)paren
(brace
r_int
r_char
id|chip_id
comma
id|silicon_revision
suffix:semicolon
r_int
r_int
id|pci_clock
suffix:semicolon
multiline_comment|/*&n;&t; * Check the silicon revision, as not all versions of the chip&n;&t; * have the register with the fast PCI bus timings.&n;&t; */
id|chip_id
op_assign
id|inb
(paren
l_int|0x903c
)paren
suffix:semicolon
id|silicon_revision
op_assign
id|inb
(paren
l_int|0x903d
)paren
suffix:semicolon
singleline_comment|// Read the fast pci clock frequency
r_if
c_cond
(paren
id|chip_id
op_eq
l_int|0x04
op_logical_and
id|silicon_revision
OL
id|SC1200_REV_B1
)paren
(brace
id|pci_clock
op_assign
id|PCI_CLK_33
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// check clock generator configuration (cfcc)
singleline_comment|// the clock is in bits 8 and 9 of this word
id|pci_clock
op_assign
id|inw
(paren
l_int|0x901e
)paren
suffix:semicolon
id|pci_clock
op_rshift_assign
l_int|8
suffix:semicolon
id|pci_clock
op_and_assign
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
id|pci_clock
op_eq
id|PCI_CLK_33A
)paren
id|pci_clock
op_assign
id|PCI_CLK_33
suffix:semicolon
)brace
r_return
id|pci_clock
suffix:semicolon
)brace
DECL|macro|DISPLAY_SC1200_TIMINGS
mdefine_line|#define DISPLAY_SC1200_TIMINGS
macro_line|#if defined(DISPLAY_SC1200_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
r_static
r_int
id|sc1200_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|sc1200_display_info
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ide-proc.c */
r_extern
r_char
op_star
id|ide_media_verbose
c_func
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|variable|sc1200_proc
r_static
id|u8
id|sc1200_proc
op_assign
l_int|0
suffix:semicolon
DECL|variable|bmide_dev
r_static
r_struct
id|pci_dev
op_star
id|bmide_dev
suffix:semicolon
DECL|function|sc1200_get_info
r_static
r_int
id|sc1200_get_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|addr
comma
id|off_t
id|offset
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
r_int
r_int
id|bibma
op_assign
id|pci_resource_start
c_func
(paren
id|bmide_dev
comma
l_int|4
)paren
suffix:semicolon
r_int
id|len
suffix:semicolon
id|u8
id|c0
op_assign
l_int|0
comma
id|c1
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * at that point bibma+0x2 et bibma+0xa are byte registers&n;&t; * to investigate:&n;&t; */
id|c0
op_assign
id|inb_p
c_func
(paren
id|bibma
op_plus
l_int|0x02
)paren
suffix:semicolon
id|c1
op_assign
id|inb_p
c_func
(paren
id|bibma
op_plus
l_int|0x0a
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                               National SCx200 Chipset.&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- Primary Channel ---------------- Secondary Channel -------------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;                %sabled                         %sabled&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot; en&quot;
comma
(paren
id|c1
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot; en&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- drive0 --------- drive1 -------- drive0 ---------- drive1 ------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA enabled:    %s              %s             %s               %s&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c0
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c1
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c1
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;UDMA&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;PIO&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_assign
(paren
id|p
op_minus
id|buffer
)paren
op_minus
id|offset
suffix:semicolon
op_star
id|addr
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_return
id|len
OG
id|count
ques
c_cond
id|count
suffix:colon
id|len
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_SC1200_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_extern
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
suffix:semicolon
multiline_comment|/*&n; * Set a new transfer mode at the drive&n; */
DECL|function|sc1200_set_xfer_mode
r_int
id|sc1200_set_xfer_mode
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|mode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: sc1200_set_xfer_mode(%s)&bslash;n&quot;
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
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|mode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Here are the standard PIO mode 0-4 timings for each &quot;format&quot;.&n; * Format-0 uses fast data reg timings, with slower command reg timings.&n; * Format-1 uses fast timings for all registers, but won&squot;t work with all drives.&n; */
DECL|variable|sc1200_pio_timings
r_static
r_const
r_int
r_int
id|sc1200_pio_timings
(braket
l_int|4
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
singleline_comment|// format0  33Mhz
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
comma
singleline_comment|// format1, 33Mhz
(brace
l_int|0xfaa3f4f3
comma
l_int|0xc23232b2
comma
l_int|0x513101c1
comma
l_int|0x31213121
comma
l_int|0x10211021
)brace
comma
singleline_comment|// format1, 48Mhz
(brace
l_int|0xfff4fff4
comma
l_int|0xf35353d3
comma
l_int|0x814102f1
comma
l_int|0x42314231
comma
l_int|0x11311131
)brace
)brace
suffix:semicolon
singleline_comment|// format1, 66Mhz
multiline_comment|/*&n; * After chip reset, the PIO timings are set to 0x00009172, which is not valid.&n; */
singleline_comment|//#define SC1200_BAD_PIO(timings) (((timings)&amp;~0x80000000)==0x00009172)
DECL|function|sc1200_autoselect_dma_mode
r_static
r_int
id|sc1200_autoselect_dma_mode
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
multiline_comment|/*&n;&t; * The SC1200 specifies that two drives sharing a cable cannot&n;&t; * mix UDMA/MDMA.  It has to be one or the other, for the pair,&n;&t; * though different timings can still be chosen for each drive.&n;&t; * We could set the appropriate timing bits on the fly,&n;&t; * but that might be a bit confusing.  So, for now we statically&n;&t; * handle this requirement by looking at our mate drive to see&n;&t; * what it is capable of, before choosing a mode for our own drive.&n;&t; */
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
id|hwif
op_member_access_from_pointer
id|ide_dma_bad_drive
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
id|hwif-&gt;autodma
op_logical_and
op_logical_neg
id|hwif
op_member_access_from_pointer
id|ide_dma_bad_drive
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
r_return
id|mode
suffix:semicolon
)brace
multiline_comment|/*&n; * sc1200_config_dma2() handles selection/setting of DMA/UDMA modes&n; * for both the chipset and drive.&n; */
DECL|function|sc1200_config_dma2
r_static
r_int
id|sc1200_config_dma2
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|mode
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
id|unit
op_assign
id|drive-&gt;select.b.unit
suffix:semicolon
r_int
r_int
id|reg
comma
id|timings
suffix:semicolon
r_int
r_int
id|pci_clock
suffix:semicolon
r_int
r_int
id|basereg
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x50
suffix:colon
l_int|0x40
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
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_amp
op_complement
(paren
id|unit
ques
c_cond
l_int|0x40
suffix:colon
l_int|0x20
)paren
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* clear DMA_capable bit */
multiline_comment|/*&n;&t; * Tell the drive to switch to the new mode; abort on failure.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|mode
op_logical_or
id|sc1200_set_xfer_mode
c_func
(paren
id|drive
comma
id|mode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SC1200: set xfer mode failure&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* failure */
)brace
id|pci_clock
op_assign
id|sc1200_get_pci_clock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now tune the chipset to match the drive:&n;&t; *&n;&t; * Note that each DMA mode has several timings associated with it.&n;&t; * The correct timing depends on the fast PCI clock freq.&n;&t; */
id|timings
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|XFER_UDMA_0
suffix:colon
r_switch
c_cond
(paren
id|pci_clock
)paren
(brace
r_case
id|PCI_CLK_33
suffix:colon
id|timings
op_assign
l_int|0x00921250
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_48
suffix:colon
id|timings
op_assign
l_int|0x00932470
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_66
suffix:colon
id|timings
op_assign
l_int|0x009436a1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
r_switch
c_cond
(paren
id|pci_clock
)paren
(brace
r_case
id|PCI_CLK_33
suffix:colon
id|timings
op_assign
l_int|0x00911140
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_48
suffix:colon
id|timings
op_assign
l_int|0x00922260
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_66
suffix:colon
id|timings
op_assign
l_int|0x00933481
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
r_switch
c_cond
(paren
id|pci_clock
)paren
(brace
r_case
id|PCI_CLK_33
suffix:colon
id|timings
op_assign
l_int|0x00911030
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_48
suffix:colon
id|timings
op_assign
l_int|0x00922140
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_66
suffix:colon
id|timings
op_assign
l_int|0x00923261
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_switch
c_cond
(paren
id|pci_clock
)paren
(brace
r_case
id|PCI_CLK_33
suffix:colon
id|timings
op_assign
l_int|0x00077771
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_48
suffix:colon
id|timings
op_assign
l_int|0x000bbbb2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_66
suffix:colon
id|timings
op_assign
l_int|0x000ffff3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_switch
c_cond
(paren
id|pci_clock
)paren
(brace
r_case
id|PCI_CLK_33
suffix:colon
id|timings
op_assign
l_int|0x00012121
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_48
suffix:colon
id|timings
op_assign
l_int|0x00024241
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_66
suffix:colon
id|timings
op_assign
l_int|0x00035352
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_switch
c_cond
(paren
id|pci_clock
)paren
(brace
r_case
id|PCI_CLK_33
suffix:colon
id|timings
op_assign
l_int|0x00002020
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_48
suffix:colon
id|timings
op_assign
l_int|0x00013131
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLK_66
suffix:colon
id|timings
op_assign
l_int|0x00015151
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timings
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: sc1200_config_dma: huh? mode=%02x clk=%x &bslash;n&quot;
comma
id|drive-&gt;name
comma
id|mode
comma
id|pci_clock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* failure */
)brace
r_if
c_cond
(paren
id|unit
op_eq
l_int|0
)paren
(brace
multiline_comment|/* are we configuring drive0? */
id|pci_read_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
l_int|4
comma
op_amp
id|reg
)paren
suffix:semicolon
id|timings
op_or_assign
id|reg
op_amp
l_int|0x80000000
suffix:semicolon
multiline_comment|/* preserve PIO format bit */
id|pci_write_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
l_int|4
comma
id|timings
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_write_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
l_int|12
comma
id|timings
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_or
(paren
id|unit
ques
c_cond
l_int|0x40
suffix:colon
l_int|0x20
)paren
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
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
multiline_comment|/*&n; * sc1200_config_dma() handles selection/setting of DMA/UDMA modes&n; * for both the chipset and drive.&n; */
DECL|function|sc1200_config_dma
r_static
r_int
id|sc1200_config_dma
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_return
id|sc1200_config_dma2
c_func
(paren
id|drive
comma
id|sc1200_autoselect_dma_mode
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  Replacement for the standard ide_dma_end action in&n; *  dma_proc.&n; *&n; *  returns 1 on error, 0 otherwise&n; */
DECL|function|sc1200_ide_dma_end
r_int
id|sc1200_ide_dma_end
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
r_int
r_int
id|dma_base
op_assign
id|hwif-&gt;dma_base
suffix:semicolon
id|byte
id|dma_stat
suffix:semicolon
id|dma_stat
op_assign
id|inb
c_func
(paren
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* get DMA status */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dma_stat
op_amp
l_int|4
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; ide_dma_end dma_stat=%0x err=%x newerr=%x&bslash;n&quot;
comma
id|dma_stat
comma
(paren
(paren
id|dma_stat
op_amp
l_int|7
)paren
op_ne
l_int|4
)paren
comma
(paren
(paren
id|dma_stat
op_amp
l_int|2
)paren
op_eq
l_int|2
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|dma_stat
op_or
l_int|0x1b
comma
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* clear the INTR &amp; ERROR bits */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dma_base
)paren
op_amp
op_complement
l_int|1
comma
id|dma_base
)paren
suffix:semicolon
multiline_comment|/* !! DO THIS HERE !! stop DMA */
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
id|dma_stat
op_amp
l_int|7
)paren
op_ne
l_int|4
suffix:semicolon
multiline_comment|/* verify good DMA status */
)brace
multiline_comment|/*&n; * sc1200_tuneproc() handles selection/setting of PIO modes&n; * for both the chipset and drive.&n; *&n; * All existing BIOSs for this chipset guarantee that all drives&n; * will have valid default PIO timings set up before we get here.&n; */
DECL|function|sc1200_tuneproc
r_static
r_void
id|sc1200_tuneproc
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
multiline_comment|/* mode=255 means &quot;autotune&quot; */
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
r_static
id|byte
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
r_int
id|mode
op_assign
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|pio
)paren
(brace
r_case
l_int|200
suffix:colon
id|mode
op_assign
id|XFER_UDMA_0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|201
suffix:colon
id|mode
op_assign
id|XFER_UDMA_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|202
suffix:colon
id|mode
op_assign
id|XFER_UDMA_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|100
suffix:colon
id|mode
op_assign
id|XFER_MW_DMA_0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|101
suffix:colon
id|mode
op_assign
id|XFER_MW_DMA_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|102
suffix:colon
id|mode
op_assign
id|XFER_MW_DMA_2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mode
op_ne
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SC1200: %s: changing (U)DMA mode&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
(paren
r_void
)paren
id|sc1200_config_dma2
c_func
(paren
id|drive
comma
id|mode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|printk
c_func
(paren
l_string|&quot;SC1200: %s: setting PIO mode%d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sc1200_set_xfer_mode
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
r_int
r_int
id|basereg
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x50
suffix:colon
l_int|0x40
suffix:semicolon
id|pci_read_config_dword
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
l_int|4
comma
op_amp
id|format
)paren
suffix:semicolon
id|format
op_assign
(paren
id|format
op_rshift
l_int|31
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|format
)paren
id|format
op_add_assign
id|sc1200_get_pci_clock
c_func
(paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
(paren
id|drive-&gt;select.b.unit
op_lshift
l_int|3
)paren
comma
id|sc1200_pio_timings
(braket
id|format
)braket
(braket
id|pio
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|lookup_pci_dev
r_static
id|ide_hwif_t
op_star
id|lookup_pci_dev
(paren
id|ide_hwif_t
op_star
id|prev
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|h
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|MAX_HWIFS
suffix:semicolon
id|h
op_increment
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|h
)braket
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
(brace
r_if
c_cond
(paren
id|hwif
op_eq
id|prev
)paren
id|prev
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// found previous, now look for next match
)brace
r_else
(brace
r_if
c_cond
(paren
id|hwif
op_logical_and
id|hwif-&gt;pci_dev
op_eq
id|dev
)paren
r_return
id|hwif
suffix:semicolon
singleline_comment|// found next match
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
singleline_comment|// not found
)brace
DECL|struct|sc1200_saved_state_s
r_typedef
r_struct
id|sc1200_saved_state_s
(brace
DECL|member|regs
id|__u32
id|regs
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|sc1200_saved_state_t
)brace
id|sc1200_saved_state_t
suffix:semicolon
DECL|function|sc1200_suspend
r_static
r_int
id|sc1200_suspend
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SC1200: suspend(%u)&bslash;n&quot;
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|0
)paren
(brace
singleline_comment|// we only save state when going from full power to less
singleline_comment|//
singleline_comment|// Loop over all interfaces that are part of this PCI device:
singleline_comment|//
r_while
c_loop
(paren
(paren
id|hwif
op_assign
id|lookup_pci_dev
c_func
(paren
id|hwif
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|sc1200_saved_state_t
op_star
id|ss
suffix:semicolon
r_int
r_int
id|basereg
comma
id|r
suffix:semicolon
singleline_comment|//
singleline_comment|// allocate a permanent save area, if not already allocated
singleline_comment|//
id|ss
op_assign
(paren
id|sc1200_saved_state_t
op_star
)paren
id|hwif-&gt;config_data
suffix:semicolon
r_if
c_cond
(paren
id|ss
op_eq
l_int|NULL
)paren
(brace
id|ss
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|sc1200_saved_state_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ss
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
(paren
id|sc1200_saved_state_t
op_star
)paren
id|hwif-&gt;config_data
op_assign
id|ss
suffix:semicolon
)brace
id|ss
op_assign
(paren
id|sc1200_saved_state_t
op_star
)paren
id|hwif-&gt;config_data
suffix:semicolon
singleline_comment|//
singleline_comment|// Save timing registers:  this may be unnecessary if 
singleline_comment|// BIOS also does it
singleline_comment|//
id|basereg
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x50
suffix:colon
l_int|0x40
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
l_int|4
suffix:semicolon
op_increment
id|r
)paren
(brace
id|pci_read_config_dword
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
(paren
id|r
op_lshift
l_int|2
)paren
comma
op_amp
id|ss-&gt;regs
(braket
id|r
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* You don&squot;t need to iterate over disks -- sysfs should have done that for you already */
id|pci_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_set_power_state
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
id|dev-&gt;current_state
op_assign
id|state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sc1200_resume
r_static
r_int
id|sc1200_resume
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SC1200: resume&bslash;n&quot;
)paren
suffix:semicolon
id|pci_set_power_state
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// bring chip back from sleep state
id|dev-&gt;current_state
op_assign
l_int|0
suffix:semicolon
id|pci_enable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
singleline_comment|//
singleline_comment|// loop over all interfaces that are part of this pci device:
singleline_comment|//
r_while
c_loop
(paren
(paren
id|hwif
op_assign
id|lookup_pci_dev
c_func
(paren
id|hwif
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|basereg
comma
id|r
comma
id|d
comma
id|format
suffix:semicolon
id|sc1200_saved_state_t
op_star
id|ss
op_assign
(paren
id|sc1200_saved_state_t
op_star
)paren
id|hwif-&gt;config_data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: SC1200: resume&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
singleline_comment|//
singleline_comment|// Restore timing registers:  this may be unnecessary if BIOS also does it
singleline_comment|//
id|basereg
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x50
suffix:colon
l_int|0x40
suffix:semicolon
r_if
c_cond
(paren
id|ss
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
l_int|4
suffix:semicolon
op_increment
id|r
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
(paren
id|r
op_lshift
l_int|2
)paren
comma
id|ss-&gt;regs
(braket
id|r
)braket
)paren
suffix:semicolon
)brace
)brace
singleline_comment|//
singleline_comment|// Re-program drive PIO modes
singleline_comment|//
id|pci_read_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
l_int|4
comma
op_amp
id|format
)paren
suffix:semicolon
id|format
op_assign
(paren
id|format
op_rshift
l_int|31
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|format
)paren
id|format
op_add_assign
id|sc1200_get_pci_clock
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
l_int|2
suffix:semicolon
op_increment
id|d
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
op_amp
(paren
id|hwif-&gt;drives
(braket
id|d
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;present
)paren
(brace
r_int
r_int
id|pio
comma
id|timings
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|basereg
op_plus
(paren
id|drive-&gt;select.b.unit
op_lshift
l_int|3
)paren
comma
op_amp
id|timings
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pio
op_assign
l_int|0
suffix:semicolon
id|pio
op_le
l_int|4
suffix:semicolon
op_increment
id|pio
)paren
(brace
r_if
c_cond
(paren
id|sc1200_pio_timings
(braket
id|format
)braket
(braket
id|pio
)braket
op_eq
id|timings
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pio
OG
l_int|4
)paren
id|pio
op_assign
l_int|255
suffix:semicolon
multiline_comment|/* autotune */
(paren
r_void
)paren
id|sc1200_tuneproc
c_func
(paren
id|drive
comma
id|pio
)paren
suffix:semicolon
)brace
)brace
singleline_comment|//
singleline_comment|// Re-program drive DMA modes
singleline_comment|//
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
id|MAX_DRIVES
suffix:semicolon
op_increment
id|d
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
op_amp
(paren
id|hwif-&gt;drives
(braket
id|d
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;present
op_logical_and
op_logical_neg
id|hwif
op_member_access_from_pointer
id|ide_dma_bad_drive
c_func
(paren
id|drive
)paren
)paren
(brace
r_int
id|was_using_dma
op_assign
id|drive-&gt;using_dma
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
id|sc1200_config_dma
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|was_using_dma
op_logical_and
id|drive-&gt;using_dma
)paren
(brace
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the sc1200 bridge for reliable IDE DMA operation.&n; */
DECL|function|init_chipset_sc1200
r_static
r_int
r_int
id|__init
id|init_chipset_sc1200
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
macro_line|#if defined(DISPLAY_SC1200_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
r_if
c_cond
(paren
op_logical_neg
id|bmide_dev
)paren
(brace
id|sc1200_proc
op_assign
l_int|1
suffix:semicolon
id|bmide_dev
op_assign
id|dev
suffix:semicolon
id|ide_pci_register_host_proc
c_func
(paren
op_amp
id|sc1200_procs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_SC1200_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets invoked by the IDE driver once for each channel,&n; * and performs channel-specific pre-initialization before drive probing.&n; */
DECL|function|init_hwif_sc1200
r_static
r_void
id|__init
id|init_hwif_sc1200
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
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
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
(brace
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|sc1200_config_dma
suffix:semicolon
id|hwif-&gt;ide_dma_end
op_assign
op_amp
id|sc1200_ide_dma_end
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
id|hwif-&gt;tuneproc
op_assign
op_amp
id|sc1200_tuneproc
suffix:semicolon
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
DECL|function|init_dma_sc1200
r_static
r_void
id|__init
id|init_dma_sc1200
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
r_int
id|dmabase
)paren
(brace
id|ide_setup_dma
c_func
(paren
id|hwif
comma
id|dmabase
comma
l_int|8
)paren
suffix:semicolon
)brace
r_extern
r_void
id|ide_setup_pci_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
DECL|function|sc1200_init_one
r_static
r_int
id|__devinit
id|sc1200_init_one
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
id|ide_pci_device_t
op_star
id|d
op_assign
op_amp
id|sc1200_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_ne
id|d-&gt;device
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sc1200_pci_tbl
r_static
r_struct
id|pci_device_id
id|sc1200_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_SCx200_IDE
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
l_string|&quot;SC1200 IDE&quot;
comma
dot
id|id_table
op_assign
id|sc1200_pci_tbl
comma
dot
id|probe
op_assign
id|sc1200_init_one
comma
dot
id|suspend
op_assign
id|sc1200_suspend
comma
dot
id|resume
op_assign
id|sc1200_resume
comma
)brace
suffix:semicolon
DECL|function|sc1200_ide_init
r_static
r_int
id|sc1200_ide_init
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
DECL|function|sc1200_ide_exit
r_static
r_void
id|sc1200_ide_exit
c_func
(paren
r_void
)paren
(brace
id|ide_pci_unregister_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|sc1200_ide_init
id|module_init
c_func
(paren
id|sc1200_ide_init
)paren
suffix:semicolon
DECL|variable|sc1200_ide_exit
id|module_exit
c_func
(paren
id|sc1200_ide_exit
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
l_string|&quot;PCI driver module for NS SC1200 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
