macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|function|pci_hotplug
r_int
id|pci_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
op_star
id|envp
comma
r_int
id|num_envp
comma
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_char
op_star
id|scratch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|scratch
op_assign
id|buffer
suffix:semicolon
multiline_comment|/* stuff we want to pass to /sbin/hotplug */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|scnprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_CLASS=%04X&quot;
comma
id|pdev
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|scratch
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|scnprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_ID=%04X:%04X&quot;
comma
id|pdev-&gt;vendor
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|scratch
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|scnprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_SUBSYS_ID=%04X:%04X&quot;
comma
id|pdev-&gt;subsystem_vendor
comma
id|pdev-&gt;subsystem_device
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|scratch
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|scnprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_SLOT_NAME=%s&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|envp
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_visit_bus
r_static
r_int
id|pci_visit_bus
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_bus
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pci_dev_wrapped
id|wrapped_dev
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Scanning bus %04x:%02x&bslash;n&quot;
comma
id|pci_domain_nr
c_func
(paren
id|wrapped_bus-&gt;bus
)paren
comma
id|wrapped_bus-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;pre_visit_pci_bus
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|pre_visit_pci_bus
c_func
(paren
id|wrapped_bus
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
id|ln
op_assign
id|wrapped_bus-&gt;bus-&gt;devices.next
suffix:semicolon
r_while
c_loop
(paren
id|ln
op_ne
op_amp
id|wrapped_bus-&gt;bus-&gt;devices
)paren
(brace
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|wrapped_dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_dev_wrapped
)paren
)paren
suffix:semicolon
id|wrapped_dev.dev
op_assign
id|dev
suffix:semicolon
id|result
op_assign
id|pci_visit_dev
c_func
(paren
id|fn
comma
op_amp
id|wrapped_dev
comma
id|wrapped_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fn-&gt;post_visit_pci_bus
)paren
id|result
op_assign
id|fn
op_member_access_from_pointer
id|post_visit_pci_bus
c_func
(paren
id|wrapped_bus
comma
id|wrapped_parent
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_visit_bridge
r_static
r_int
id|pci_visit_bridge
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|pci_bus_wrapped
id|wrapped_bus
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Scanning bridge %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|wrapped_dev-&gt;dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
id|bus
op_assign
id|wrapped_dev-&gt;dev-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
id|bus
)paren
(brace
id|memset
c_func
(paren
op_amp
id|wrapped_bus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_bus_wrapped
)paren
)paren
suffix:semicolon
id|wrapped_bus.bus
op_assign
id|bus
suffix:semicolon
id|result
op_assign
id|pci_visit_bus
c_func
(paren
id|fn
comma
op_amp
id|wrapped_bus
comma
id|wrapped_dev
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_visit_dev - scans the pci buses.&n; * Every bus and every function is presented to a custom&n; * function that can act upon it.&n; */
DECL|function|pci_visit_dev
r_int
id|pci_visit_dev
c_func
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|wrapped_dev
ques
c_cond
id|wrapped_dev-&gt;dev
suffix:colon
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;pre_visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|pre_visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
(brace
r_case
id|PCI_CLASS_BRIDGE_PCI
suffix:colon
id|result
op_assign
id|pci_visit_bridge
c_func
(paren
id|fn
comma
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DBG
c_func
(paren
l_string|&quot;PCI: Scanning device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn-&gt;visit_pci_dev
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fn-&gt;post_visit_pci_dev
)paren
id|result
op_assign
id|fn
op_member_access_from_pointer
id|post_visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|pci_visit_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pci_visit_dev
)paren
suffix:semicolon
eof
