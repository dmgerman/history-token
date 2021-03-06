multiline_comment|/*&n; * linux/arch/arm/mach-footbridge/cats-pci.c&n; *&n; * PCI bios-type initialisation for PCI machines&n; *&n; * Bits taken from various places.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/* cats host-specific stuff */
DECL|variable|__initdata
r_static
r_int
id|irqmap_cats
(braket
)braket
id|__initdata
op_assign
(brace
id|IRQ_PCI
comma
id|IRQ_IN0
comma
id|IRQ_IN1
comma
id|IRQ_IN3
)brace
suffix:semicolon
DECL|function|cats_map_irq
r_static
r_int
id|__init
id|cats_map_irq
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
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|128
)paren
r_return
id|dev-&gt;irq
op_amp
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|1
op_logical_and
id|dev-&gt;irq
op_le
l_int|4
)paren
r_return
id|irqmap_cats
(braket
id|dev-&gt;irq
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: device %02x:%02x has unknown irq line %x&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * why not the standard PCI swizzle?  does this prevent 4-port tulip&n; * cards being used (ie, pci-pci bridge based cards)?&n; */
DECL|variable|__initdata
r_static
r_struct
id|hw_pci
id|cats_pci
id|__initdata
op_assign
(brace
dot
id|swizzle
op_assign
l_int|NULL
comma
dot
id|map_irq
op_assign
id|cats_map_irq
comma
dot
id|nr_controllers
op_assign
l_int|1
comma
dot
id|setup
op_assign
id|dc21285_setup
comma
dot
id|scan
op_assign
id|dc21285_scan_bus
comma
dot
id|preinit
op_assign
id|dc21285_preinit
comma
dot
id|postinit
op_assign
id|dc21285_postinit
comma
)brace
suffix:semicolon
DECL|function|cats_pci_init
r_static
r_int
id|cats_pci_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
id|pci_common_init
c_func
(paren
op_amp
id|cats_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cats_pci_init
id|subsys_initcall
c_func
(paren
id|cats_pci_init
)paren
suffix:semicolon
eof
