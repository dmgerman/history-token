multiline_comment|/*&n; *    Copyright 2001 MontaVista Software Inc.&n; *        &lt;mlocke@mvista.com&gt;&n; *&n; * &t;Not much is needed for the Embedded Planet 405gp board&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;platforms/ibm_ocp.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|variable|ep405_bcsr
id|u8
op_star
id|ep405_bcsr
suffix:semicolon
DECL|variable|ep405_nvram
id|u8
op_star
id|ep405_nvram
suffix:semicolon
r_static
r_struct
(brace
DECL|member|cpld_xirq_select
id|u8
id|cpld_xirq_select
suffix:semicolon
DECL|member|pci_idsel
r_int
id|pci_idsel
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|variable|ep405_devtable
)brace
id|ep405_devtable
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_EP405PC
(brace
l_int|0x07
comma
l_int|0x0E
comma
l_int|25
)brace
comma
multiline_comment|/* EP405PC: USB */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|EP405_DEVTABLE_SIZE
mdefine_line|#define EP405_DEVTABLE_SIZE (sizeof(ep405_devtable)/sizeof(ep405_devtable[0]))
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
r_int
id|i
suffix:semicolon
multiline_comment|/* AFAICT this is only called a few times during PCI setup, so&n;&t;   performance is not critical */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EP405_DEVTABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|idsel
op_eq
id|ep405_devtable
(braket
id|i
)braket
dot
id|pci_idsel
)paren
r_return
id|ep405_devtable
(braket
id|i
)braket
dot
id|irq
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__init
DECL|function|board_setup_arch
id|board_setup_arch
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|bip
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_if
c_cond
(paren
id|bip-&gt;bi_nvramsize
op_eq
l_int|512
op_star
l_int|1024
)paren
(brace
multiline_comment|/* FIXME: we should properly handle NVRTCs of different sizes */
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_DS1557
comma
id|ep405_nvram
comma
id|ep405_nvram
comma
id|ep405_nvram
comma
l_int|8
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|bar_response
comma
id|bar
suffix:semicolon
multiline_comment|/*&n;&t; * Expected PCI mapping:&n;&t; *&n;&t; *  PLB addr             PCI memory addr&n;&t; *  ---------------------       ---------------------&n;&t; *  0000&squot;0000 - 7fff&squot;ffff &lt;---  0000&squot;0000 - 7fff&squot;ffff&n;&t; *  8000&squot;0000 - Bfff&squot;ffff ---&gt;  8000&squot;0000 - Bfff&squot;ffff&n;&t; *&n;&t; *  PLB addr             PCI io addr&n;&t; *  ---------------------       ---------------------&n;&t; *  e800&squot;0000 - e800&squot;ffff ---&gt;  0000&squot;0000 - 0001&squot;0000&n;&t; *&n;&t; */
multiline_comment|/* Disable region zero first */
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
multiline_comment|/* Disable region one */
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
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* Disable region two */
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
multiline_comment|/* Configure PTM (PCI-&gt;PLB) region 1 */
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;ptm1la
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* PLB base address */
multiline_comment|/* Disable PTM region 2 */
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
)brace
r_void
id|__init
DECL|function|board_io_mapping
id|board_io_mapping
c_func
(paren
r_void
)paren
(brace
id|bd_t
op_star
id|bip
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
id|ep405_bcsr
op_assign
id|ioremap
c_func
(paren
id|EP405_BCSR_PADDR
comma
id|EP405_BCSR_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bip-&gt;bi_nvramsize
OG
l_int|0
)paren
(brace
id|ep405_nvram
op_assign
id|ioremap
c_func
(paren
id|EP405_NVRAM_PADDR
comma
id|bip-&gt;bi_nvramsize
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|board_setup_irq
id|board_setup_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Workaround for a bug in the firmware it incorrectly sets&n;&t;   the IRQ polarities for XIRQ0 and XIRQ1 */
id|mtdcr
c_func
(paren
id|DCRN_UIC_PR
c_func
(paren
id|DCRN_UIC0_BASE
)paren
comma
l_int|0xffffff80
)paren
suffix:semicolon
multiline_comment|/* set the polarity */
id|mtdcr
c_func
(paren
id|DCRN_UIC_SR
c_func
(paren
id|DCRN_UIC0_BASE
)paren
comma
l_int|0x00000060
)paren
suffix:semicolon
multiline_comment|/* clear bogus interrupts */
multiline_comment|/* Activate the XIRQs from the CPLD */
id|writeb
c_func
(paren
l_int|0xf0
comma
id|ep405_bcsr
op_plus
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Set up IRQ routing */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EP405_DEVTABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|ep405_devtable
(braket
id|i
)braket
dot
id|irq
op_ge
l_int|25
)paren
op_logical_and
(paren
id|ep405_devtable
(braket
id|i
)braket
dot
id|irq
)paren
op_le
l_int|31
)paren
(brace
id|writeb
c_func
(paren
id|ep405_devtable
(braket
id|i
)braket
dot
id|cpld_xirq_select
comma
id|ep405_bcsr
op_plus
l_int|5
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|ep405_devtable
(braket
id|i
)braket
dot
id|irq
op_minus
l_int|25
comma
id|ep405_bcsr
op_plus
l_int|6
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
id|__init
DECL|function|board_init
id|board_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PPC_RTC
id|bd_t
op_star
id|bip
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
multiline_comment|/* FIXME: we should be able to access the NVRAM even if PPC_RTC is not configured */
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
r_if
c_cond
(paren
id|bip-&gt;bi_nvramsize
op_eq
l_int|512
op_star
l_int|1024
)paren
(brace
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
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;EP405: NVRTC size is not 512k (not a DS1557).  Not sure what to do with it&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
