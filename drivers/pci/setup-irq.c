multiline_comment|/*&n; *&t;drivers/pci/setup-irq.c&n; *&n; * Extruded from code written by&n; *      Dave Rusling (david.rusling@reo.mts.dec.com)&n; *      David Mosberger (davidm@cs.arizona.edu)&n; *&t;David Miller (davem@redhat.com)&n; *&n; * Support routines for initializing a PCI subsystem.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBGC
macro_line|# define DBGC(args)     printk args
macro_line|#else
DECL|macro|DBGC
macro_line|# define DBGC(args)
macro_line|#endif
r_static
r_void
id|__init
DECL|function|pdev_fixup_irq
id|pdev_fixup_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
(paren
op_star
id|swizzle
)paren
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
op_star
)paren
comma
r_int
(paren
op_star
id|map_irq
)paren
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
comma
id|u8
)paren
)paren
(brace
id|u8
id|pin
comma
id|slot
suffix:semicolon
r_int
id|irq
suffix:semicolon
multiline_comment|/* If this device is not on the primary bus, we need to figure out&n;&t;   which interrupt pin it will come in on.   We know which slot it&n;&t;   will come in on &squot;cos that slot is where the bridge is.   Each&n;&t;   time the interrupt line passes through a PCI-PCI bridge we must&n;&t;   apply the swizzle function.  */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
multiline_comment|/* Cope with 0 and illegal. */
r_if
c_cond
(paren
id|pin
op_eq
l_int|0
op_logical_or
id|pin
OG
l_int|4
)paren
id|pin
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Follow the chain of bridges, swizzling as we go.  */
id|slot
op_assign
(paren
op_star
id|swizzle
)paren
(paren
id|dev
comma
op_amp
id|pin
)paren
suffix:semicolon
id|irq
op_assign
(paren
op_star
id|map_irq
)paren
(paren
id|dev
comma
id|slot
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
op_minus
l_int|1
)paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_ERR
l_string|&quot;PCI fixup irq: (%s) got %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
)paren
)paren
suffix:semicolon
multiline_comment|/* Always tell the device, so the driver knows what is&n;&t;   the real IRQ to use; the device does not use it. */
id|pcibios_update_irq
c_func
(paren
id|dev
comma
id|irq
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pci_fixup_irqs
id|pci_fixup_irqs
c_func
(paren
id|u8
(paren
op_star
id|swizzle
)paren
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
op_star
)paren
comma
r_int
(paren
op_star
id|map_irq
)paren
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
comma
id|u8
)paren
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|pdev_fixup_irq
c_func
(paren
id|dev
comma
id|swizzle
comma
id|map_irq
)paren
suffix:semicolon
)brace
)brace
eof
