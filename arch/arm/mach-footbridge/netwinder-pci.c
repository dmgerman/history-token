multiline_comment|/*&n; * linux/arch/arm/mach-footbridge/netwinder-pci.c&n; *&n; * PCI bios-type initialisation for PCI machines&n; *&n; * Bits taken from various places.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
multiline_comment|/*&n; * We now use the slot ID instead of the device identifiers to select&n; * which interrupt is routed where.&n; */
DECL|function|netwinder_map_irq
r_static
r_int
id|__init
id|netwinder_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* host bridge */
r_return
l_int|0
suffix:semicolon
r_case
l_int|9
suffix:colon
multiline_comment|/* CyberPro */
r_return
id|IRQ_NETWINDER_VGA
suffix:semicolon
r_case
l_int|10
suffix:colon
multiline_comment|/* DC21143 */
r_return
id|IRQ_NETWINDER_ETHER100
suffix:semicolon
r_case
l_int|12
suffix:colon
multiline_comment|/* Winbond 553 */
r_return
id|IRQ_ISA_HARDDISK1
suffix:semicolon
r_case
l_int|13
suffix:colon
multiline_comment|/* Winbond 89C940F */
r_return
id|IRQ_NETWINDER_ETHER10
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: unknown device in slot %s: %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_struct
id|hw_pci
id|netwinder_pci
id|__initdata
op_assign
(brace
id|swizzle
suffix:colon
id|pci_std_swizzle
comma
id|map_irq
suffix:colon
id|netwinder_map_irq
comma
id|nr_controllers
suffix:colon
l_int|1
comma
id|setup
suffix:colon
id|dc21285_setup
comma
id|scan
suffix:colon
id|dc21285_scan_bus
comma
id|preinit
suffix:colon
id|dc21285_preinit
comma
id|postinit
suffix:colon
id|dc21285_postinit
comma
)brace
suffix:semicolon
eof
