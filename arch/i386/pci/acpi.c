macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|function|pci_acpi_scan_root
r_struct
id|pci_bus
op_star
id|__devinit
id|pci_acpi_scan_root
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|domain
comma
r_int
id|busnum
)paren
(brace
r_if
c_cond
(paren
id|domain
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Multiple domains not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|pcibios_scan_root
c_func
(paren
id|busnum
)paren
suffix:semicolon
)brace
DECL|function|pci_acpi_init
r_static
r_int
id|__init
id|pci_acpi_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pcibios_scanned
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_noirq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_pci_irq_init
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using ACPI for IRQ routing&bslash;n&quot;
)paren
suffix:semicolon
id|pcibios_scanned
op_increment
suffix:semicolon
id|pcibios_enable_irq
op_assign
id|acpi_pci_irq_enable
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Invalid ACPI-PCI IRQ routing table&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_acpi_init
id|subsys_initcall
c_func
(paren
id|pci_acpi_init
)paren
suffix:semicolon
eof
