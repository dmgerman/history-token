macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * PCI Power management..&n; *&n; * This needs to be done centralized, so that we power manage PCI&n; * devices in the right order: we should not shut down PCI bridges&n; * before we&squot;ve shut down the devices behind them, and we should&n; * not wake up devices before we&squot;ve woken up the bridge to the&n; * device.. Eh?&n; *&n; * We do not touch devices that don&squot;t have a driver that exports&n; * a suspend/resume function. That is just too dangerous. If the default&n; * PCI suspend/resume functions work for a device, the driver can&n; * easily implement them (ie just have a suspend function that calls&n; * the pci_set_power_state() function).&n; */
DECL|function|pci_pm_save_state_device
r_static
r_int
id|pci_pm_save_state_device
c_func
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
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_struct
id|pci_driver
op_star
id|driver
op_assign
id|dev-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|driver
op_logical_and
id|driver-&gt;save_state
)paren
id|error
op_assign
id|driver
op_member_access_from_pointer
id|save_state
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pci_pm_suspend_device
r_static
r_int
id|pci_pm_suspend_device
c_func
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
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_struct
id|pci_driver
op_star
id|driver
op_assign
id|dev-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|driver
op_logical_and
id|driver-&gt;suspend
)paren
id|error
op_assign
id|driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pci_pm_resume_device
r_static
r_int
id|pci_pm_resume_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_struct
id|pci_driver
op_star
id|driver
op_assign
id|dev-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|driver
op_logical_and
id|driver-&gt;resume
)paren
id|error
op_assign
id|driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pci_pm_save_state_bus
r_static
r_int
id|pci_pm_save_state_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
id|u32
id|state
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|bus-&gt;children
)paren
(brace
id|error
op_assign
id|pci_pm_save_state_bus
c_func
(paren
id|pci_bus_b
c_func
(paren
id|list
)paren
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|bus-&gt;devices
)paren
(brace
id|error
op_assign
id|pci_pm_save_state_device
c_func
(paren
id|pci_dev_b
c_func
(paren
id|list
)paren
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_pm_suspend_bus
r_static
r_int
id|pci_pm_suspend_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
id|u32
id|state
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
multiline_comment|/* Walk the bus children list */
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|bus-&gt;children
)paren
id|pci_pm_suspend_bus
c_func
(paren
id|pci_bus_b
c_func
(paren
id|list
)paren
comma
id|state
)paren
suffix:semicolon
multiline_comment|/* Walk the device children list */
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|bus-&gt;devices
)paren
id|pci_pm_suspend_device
c_func
(paren
id|pci_dev_b
c_func
(paren
id|list
)paren
comma
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_pm_resume_bus
r_static
r_int
id|pci_pm_resume_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
multiline_comment|/* Walk the device children list */
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|bus-&gt;devices
)paren
id|pci_pm_resume_device
c_func
(paren
id|pci_dev_b
c_func
(paren
id|list
)paren
)paren
suffix:semicolon
multiline_comment|/* And then walk the bus children */
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|bus-&gt;children
)paren
id|pci_pm_resume_bus
c_func
(paren
id|pci_bus_b
c_func
(paren
id|list
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_pm_save_state
r_static
r_int
id|pci_pm_save_state
c_func
(paren
id|u32
id|state
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|pci_root_buses
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|list
)paren
suffix:semicolon
id|error
op_assign
id|pci_pm_save_state_bus
c_func
(paren
id|bus
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|pci_pm_save_state_device
c_func
(paren
id|bus-&gt;self
comma
id|state
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pci_pm_suspend
r_static
r_int
id|pci_pm_suspend
c_func
(paren
id|u32
id|state
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|pci_root_buses
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|list
)paren
suffix:semicolon
id|pci_pm_suspend_bus
c_func
(paren
id|bus
comma
id|state
)paren
suffix:semicolon
id|pci_pm_suspend_device
c_func
(paren
id|bus-&gt;self
comma
id|state
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_pm_resume
r_static
r_int
id|pci_pm_resume
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|pci_root_buses
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|list
)paren
suffix:semicolon
id|pci_pm_resume_device
c_func
(paren
id|bus-&gt;self
)paren
suffix:semicolon
id|pci_pm_resume_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pci_pm_callback
id|pci_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|pm_device
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|rqst
)paren
(brace
r_case
id|PM_SAVE_STATE
suffix:colon
id|error
op_assign
id|pci_pm_save_state
c_func
(paren
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_SUSPEND
suffix:colon
id|error
op_assign
id|pci_pm_suspend
c_func
(paren
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_RESUME
suffix:colon
id|error
op_assign
id|pci_pm_resume
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pci_pm_init
r_static
r_int
id|__init
id|pci_pm_init
c_func
(paren
r_void
)paren
(brace
id|pm_register
c_func
(paren
id|PM_PCI_DEV
comma
l_int|0
comma
id|pci_pm_callback
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_pm_init
id|subsys_initcall
c_func
(paren
id|pci_pm_init
)paren
suffix:semicolon
eof