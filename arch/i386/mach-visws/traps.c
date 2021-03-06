multiline_comment|/* VISWS traps */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &quot;cobalt.h&quot;
macro_line|#include &quot;lithium.h&quot;
DECL|macro|A01234
mdefine_line|#define A01234 (LI_INTA_0 | LI_INTA_1 | LI_INTA_2 | LI_INTA_3 | LI_INTA_4)
DECL|macro|BCD
mdefine_line|#define BCD (LI_INTB | LI_INTC | LI_INTD)
DECL|macro|ALLDEVS
mdefine_line|#define ALLDEVS (A01234 | BCD)
DECL|function|lithium_init
r_static
id|__init
r_void
id|lithium_init
c_func
(paren
r_void
)paren
(brace
id|set_fixmap
c_func
(paren
id|FIX_LI_PCIA
comma
id|LI_PCI_A_PHYS
)paren
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_LI_PCIB
comma
id|LI_PCI_B_PHYS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|li_pcia_read16
c_func
(paren
id|PCI_VENDOR_ID
)paren
op_ne
id|PCI_VENDOR_ID_SGI
)paren
op_logical_or
(paren
id|li_pcia_read16
c_func
(paren
id|PCI_DEVICE_ID
)paren
op_ne
id|PCI_VENDOR_ID_SGI_LITHIUM
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Lithium hostbridge %c not found&bslash;n&quot;
comma
l_char|&squot;A&squot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;This machine is not SGI Visual Workstation 320/540&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|li_pcib_read16
c_func
(paren
id|PCI_VENDOR_ID
)paren
op_ne
id|PCI_VENDOR_ID_SGI
)paren
op_logical_or
(paren
id|li_pcib_read16
c_func
(paren
id|PCI_DEVICE_ID
)paren
op_ne
id|PCI_VENDOR_ID_SGI_LITHIUM
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Lithium hostbridge %c not found&bslash;n&quot;
comma
l_char|&squot;B&squot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;This machine is not SGI Visual Workstation 320/540&quot;
)paren
suffix:semicolon
)brace
id|li_pcia_write16
c_func
(paren
id|LI_PCI_INTEN
comma
id|ALLDEVS
)paren
suffix:semicolon
id|li_pcib_write16
c_func
(paren
id|LI_PCI_INTEN
comma
id|ALLDEVS
)paren
suffix:semicolon
)brace
DECL|function|cobalt_init
r_static
id|__init
r_void
id|cobalt_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * On normal SMP PC this is used only with SMP, but we have to&n;&t; * use it and set it up here to start the Cobalt clock&n;&t; */
id|set_fixmap
c_func
(paren
id|FIX_APIC_BASE
comma
id|APIC_DEFAULT_PHYS_BASE
)paren
suffix:semicolon
id|setup_local_APIC
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Local APIC Version %#lx, ID %#lx&bslash;n&quot;
comma
id|apic_read
c_func
(paren
id|APIC_LVR
)paren
comma
id|apic_read
c_func
(paren
id|APIC_ID
)paren
)paren
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_CO_CPU
comma
id|CO_CPU_PHYS
)paren
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_CO_APIC
comma
id|CO_APIC_PHYS
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Cobalt Revision %#lx, APIC ID %#lx&bslash;n&quot;
comma
id|co_cpu_read
c_func
(paren
id|CO_CPU_REV
)paren
comma
id|co_apic_read
c_func
(paren
id|CO_APIC_ID
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable Cobalt APIC being careful to NOT change the ID! */
id|co_apic_write
c_func
(paren
id|CO_APIC_ID
comma
id|co_apic_read
c_func
(paren
id|CO_APIC_ID
)paren
op_or
id|CO_APIC_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Cobalt APIC enabled: ID reg %#lx&bslash;n&quot;
comma
id|co_apic_read
c_func
(paren
id|CO_APIC_ID
)paren
)paren
suffix:semicolon
)brace
DECL|function|trap_init_hook
r_void
id|__init
id|trap_init_hook
c_func
(paren
r_void
)paren
(brace
id|lithium_init
c_func
(paren
)paren
suffix:semicolon
id|cobalt_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
