multiline_comment|/*&n; * arch/ppc/platforms/4xx/sycamore.c&n; *&n; * Architecture- / platform-specific boot-time initialization code for&n; * IBM PowerPC 4xx based boards.&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2000-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/ppc4xx_pic.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ibm_ocp_pci.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|variable|kb_cs
r_void
op_star
id|kb_cs
suffix:semicolon
DECL|variable|kb_data
r_void
op_star
id|kb_data
suffix:semicolon
DECL|variable|sycamore_rtc_base
r_void
op_star
id|sycamore_rtc_base
suffix:semicolon
multiline_comment|/*&n; * Define external IRQ senses and polarities.&n; */
DECL|variable|__initdata
r_int
r_char
id|ppc4xx_uic_ext_irq_cfg
(braket
)braket
id|__initdata
op_assign
(brace
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 7 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 8 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 9 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 10 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 11 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 12 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 0 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 1 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 2 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 3 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 4 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 5 */
(paren
id|IRQ_SENSE_LEVEL
op_or
id|IRQ_POLARITY_NEGATIVE
)paren
comma
multiline_comment|/* Ext Int 6 */
)brace
suffix:semicolon
multiline_comment|/* Some IRQs unique to Sycamore.&n; * Used by the generic 405 PCI setup functions in ppc4xx_pci.c&n; */
r_int
id|__init
DECL|function|ppc405_map_irq
id|ppc405_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;     *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;     *      A       B       C       D&n;&t;     */
(brace
(brace
l_int|28
comma
l_int|28
comma
l_int|28
comma
l_int|28
)brace
comma
multiline_comment|/* IDSEL 1 - PCI slot 1 */
(brace
l_int|29
comma
l_int|29
comma
l_int|29
comma
l_int|29
)brace
comma
multiline_comment|/* IDSEL 2 - PCI slot 2 */
(brace
l_int|30
comma
l_int|30
comma
l_int|30
comma
l_int|30
)brace
comma
multiline_comment|/* IDSEL 3 - PCI slot 3 */
(brace
l_int|31
comma
l_int|31
comma
l_int|31
comma
l_int|31
)brace
comma
multiline_comment|/* IDSEL 4 - PCI slot 4 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|1
comma
id|max_idsel
op_assign
l_int|4
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__init
DECL|function|sycamore_setup_arch
id|sycamore_setup_arch
c_func
(paren
r_void
)paren
(brace
DECL|macro|SYCAMORE_PS2_BASE
mdefine_line|#define SYCAMORE_PS2_BASE&t;0xF0100000
DECL|macro|SYCAMORE_FPGA_BASE
mdefine_line|#define SYCAMORE_FPGA_BASE&t;0xF0300000
r_void
op_star
id|fpga_brdc
suffix:semicolon
r_int
r_char
id|fpga_brdc_data
suffix:semicolon
r_void
op_star
id|fpga_enable
suffix:semicolon
r_void
op_star
id|fpga_polarity
suffix:semicolon
r_void
op_star
id|fpga_status
suffix:semicolon
r_void
op_star
id|fpga_trigger
suffix:semicolon
id|ppc4xx_setup_arch
c_func
(paren
)paren
suffix:semicolon
id|ibm_ocp_set_emac
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|kb_data
op_assign
id|ioremap
c_func
(paren
id|SYCAMORE_PS2_BASE
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kb_data
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;sycamore_setup_arch() kb_data ioremap failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kb_cs
op_assign
id|kb_data
op_plus
l_int|1
suffix:semicolon
id|fpga_status
op_assign
id|ioremap
c_func
(paren
id|SYCAMORE_FPGA_BASE
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpga_status
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;sycamore_setup_arch() fpga_status ioremap failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fpga_enable
op_assign
id|fpga_status
op_plus
l_int|1
suffix:semicolon
id|fpga_polarity
op_assign
id|fpga_status
op_plus
l_int|2
suffix:semicolon
id|fpga_trigger
op_assign
id|fpga_status
op_plus
l_int|3
suffix:semicolon
id|fpga_brdc
op_assign
id|fpga_status
op_plus
l_int|4
suffix:semicolon
multiline_comment|/* split the keyboard and mouse interrupts */
id|fpga_brdc_data
op_assign
id|readb
c_func
(paren
id|fpga_brdc
)paren
suffix:semicolon
id|fpga_brdc_data
op_or_assign
l_int|0x80
suffix:semicolon
id|writeb
c_func
(paren
id|fpga_brdc_data
comma
id|fpga_brdc
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x3
comma
id|fpga_enable
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x3
comma
id|fpga_polarity
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x3
comma
id|fpga_trigger
)paren
suffix:semicolon
multiline_comment|/* RTC step for the sycamore */
id|sycamore_rtc_base
op_assign
(paren
r_void
op_star
)paren
id|SYCAMORE_RTC_VADDR
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_DS1743
comma
id|sycamore_rtc_base
comma
id|sycamore_rtc_base
comma
id|sycamore_rtc_base
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IBM Sycamore (IBM405GPr) Platform&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Port by MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|bios_fixup
id|bios_fixup
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_struct
id|pcil0_regs
op_star
id|pcip
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_int
r_int
id|bar_response
comma
id|bar
suffix:semicolon
multiline_comment|/*&n;&t; * Expected PCI mapping:&n;&t; *&n;&t; *  PLB addr             PCI memory addr&n;&t; *  ---------------------       ---------------------&n;&t; *  0000&squot;0000 - 7fff&squot;ffff &lt;---  0000&squot;0000 - 7fff&squot;ffff&n;&t; *  8000&squot;0000 - Bfff&squot;ffff ---&gt;  8000&squot;0000 - Bfff&squot;ffff&n;&t; *&n;&t; *  PLB addr             PCI io addr&n;&t; *  ---------------------       ---------------------&n;&t; *  e800&squot;0000 - e800&squot;ffff ---&gt;  0000&squot;0000 - 0001&squot;0000&n;&t; *&n;&t; * The following code is simplified by assuming that the bootrom&n;&t; * has been well behaved in following this mapping.&n;&t; */
macro_line|#ifdef DEBUG
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ioremap PCLIO_BASE = 0x%x&bslash;n&quot;
comma
id|pcip
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI bridge regs before fixup &bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|ma
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|la
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|pcila
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|pciha
)paren
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; ptm1ms&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm1ms
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ptm1la&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm1la
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ptm2ms&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm2ms
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ptm2la&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm2la
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* added for IBM boot rom version 1.15 bios bar changes  -AK */
multiline_comment|/* Disable region first */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|0
)braket
dot
id|ma
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* PLB starting addr, PCI: 0x80000000 */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|0
)braket
dot
id|la
)paren
comma
l_int|0x80000000
)paren
suffix:semicolon
multiline_comment|/* PCI start addr, 0x80000000 */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|0
)braket
dot
id|pcila
)paren
comma
id|PPC405_PCI_MEM_BASE
)paren
suffix:semicolon
multiline_comment|/* 512MB range of PLB to PCI */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|0
)braket
dot
id|pciha
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* Enable no pre-fetch, enable region */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|0
)braket
dot
id|ma
)paren
comma
(paren
(paren
l_int|0xffffffff
op_minus
(paren
id|PPC405_PCI_UPPER_MEM
op_minus
id|PPC405_PCI_MEM_BASE
)paren
)paren
op_or
l_int|0x01
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable inbound region one - 1GB size */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;ptm1ms
)paren
comma
l_int|0xc0000001
)paren
suffix:semicolon
multiline_comment|/* Disable outbound region one */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|1
)braket
dot
id|ma
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|1
)braket
dot
id|la
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|1
)braket
dot
id|pcila
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|1
)braket
dot
id|pciha
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|1
)braket
dot
id|ma
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* Disable inbound region two */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;ptm2ms
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* Disable outbound region two */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|2
)braket
dot
id|ma
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|2
)braket
dot
id|la
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|2
)braket
dot
id|pcila
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|2
)braket
dot
id|pciha
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
l_int|2
)braket
dot
id|ma
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* Zero config bars */
r_for
c_loop
(paren
id|bar
op_assign
id|PCI_BASE_ADDRESS_1
suffix:semicolon
id|bar
op_le
id|PCI_BASE_ADDRESS_2
suffix:semicolon
id|bar
op_add_assign
l_int|4
)paren
(brace
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
comma
id|PCI_FUNC
c_func
(paren
id|hose-&gt;first_busno
)paren
comma
id|bar
comma
l_int|0x00000000
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
comma
id|PCI_FUNC
c_func
(paren
id|hose-&gt;first_busno
)paren
comma
id|bar
comma
op_amp
id|bar_response
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;BUS %d, device %d, Function %d bar 0x%8.8x is 0x%8.8x&bslash;n&quot;
comma
id|hose-&gt;first_busno
comma
id|PCI_SLOT
c_func
(paren
id|hose-&gt;first_busno
)paren
comma
id|PCI_FUNC
c_func
(paren
id|hose-&gt;first_busno
)paren
comma
id|bar
comma
id|bar_response
)paren
suffix:semicolon
)brace
multiline_comment|/* end work arround */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;PCI bridge regs after fixup &bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|ma
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|la
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|pcila
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmm%dma&bslash;t0x%x&bslash;n&quot;
comma
id|i
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|i
)braket
dot
id|pciha
)paren
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; ptm1ms&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm1ms
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ptm1la&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm1la
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ptm2ms&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm2ms
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ptm2la&bslash;t0x%x&bslash;n&quot;
comma
id|in_le32
c_func
(paren
op_amp
(paren
id|pcip-&gt;ptm2la
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
r_void
id|__init
DECL|function|sycamore_map_io
id|sycamore_map_io
c_func
(paren
r_void
)paren
(brace
id|ppc4xx_map_io
c_func
(paren
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|SYCAMORE_RTC_VADDR
comma
id|SYCAMORE_RTC_PADDR
comma
id|SYCAMORE_RTC_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|ppc4xx_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|sycamore_setup_arch
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|sycamore_map_io
suffix:semicolon
macro_line|#ifdef CONFIG_GEN_RTC
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
macro_line|#endif
)brace
eof
