multiline_comment|/*&n; * File:&t;portdrv_pci.c&n; * Purpose:&t;PCI Express Port Bus Driver&n; *&n; * Copyright (C) 2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pcieport_if.h&gt;
macro_line|#include &quot;portdrv.h&quot;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v1.0&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;tom.l.nguyen@intel.com&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;PCIE Port Bus Driver&quot;
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* global data */
DECL|variable|device_name
r_static
r_const
r_char
id|device_name
(braket
)braket
op_assign
l_string|&quot;pcieport-driver&quot;
suffix:semicolon
multiline_comment|/*&n; * pcie_portdrv_probe - Probe PCI-Express port devices&n; * @dev: PCI-Express port device being probed&n; *&n; * If detected invokes the pcie_port_device_register() method for &n; * this port device.&n; *&n; */
DECL|function|pcie_portdrv_probe
r_static
r_int
id|__devinit
id|pcie_portdrv_probe
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
r_int
id|status
suffix:semicolon
id|status
op_assign
id|pcie_port_device_probe
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pci_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s-&gt;Dev[%04x:%04x] has invalid IRQ. Check vendor BIOS&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev-&gt;device
comma
id|dev-&gt;vendor
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pcie_port_device_register
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcie_portdrv_remove
r_static
r_void
id|pcie_portdrv_remove
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pcie_port_device_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
DECL|function|pcie_portdrv_suspend
r_static
r_int
id|pcie_portdrv_suspend
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
r_return
id|pcie_port_device_suspend
c_func
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|pcie_portdrv_resume
r_static
r_int
id|pcie_portdrv_resume
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
id|pcie_port_device_resume
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * LINUX Device Driver Model&n; */
DECL|variable|port_pci_ids
r_static
r_const
r_struct
id|pci_device_id
id|port_pci_ids
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* handle any PCI-Express port */
id|PCI_DEVICE_CLASS
c_func
(paren
(paren
(paren
id|PCI_CLASS_BRIDGE_PCI
op_lshift
l_int|8
)paren
op_or
l_int|0x00
)paren
comma
op_complement
l_int|0
)paren
comma
)brace
comma
(brace
multiline_comment|/* end: all zeroes */
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|port_pci_ids
)paren
suffix:semicolon
DECL|variable|pcie_portdrv
r_static
r_struct
id|pci_driver
id|pcie_portdrv
op_assign
(brace
dot
id|name
op_assign
(paren
r_char
op_star
)paren
id|device_name
comma
dot
id|id_table
op_assign
op_amp
id|port_pci_ids
(braket
l_int|0
)braket
comma
dot
id|probe
op_assign
id|pcie_portdrv_probe
comma
dot
id|remove
op_assign
id|pcie_portdrv_remove
comma
macro_line|#ifdef&t;CONFIG_PM
dot
id|suspend
op_assign
id|pcie_portdrv_suspend
comma
dot
id|resume
op_assign
id|pcie_portdrv_resume
comma
macro_line|#endif&t;/* PM */
)brace
suffix:semicolon
DECL|function|pcie_portdrv_init
r_static
r_int
id|__init
id|pcie_portdrv_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|pcie_port_bus_register
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
id|pci_register_driver
c_func
(paren
op_amp
id|pcie_portdrv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|pcie_port_bus_unregister
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|pcie_portdrv_exit
r_static
r_void
id|__exit
id|pcie_portdrv_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|pcie_portdrv
)paren
suffix:semicolon
id|pcie_port_bus_unregister
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|pcie_portdrv_init
id|module_init
c_func
(paren
id|pcie_portdrv_init
)paren
suffix:semicolon
DECL|variable|pcie_portdrv_exit
id|module_exit
c_func
(paren
id|pcie_portdrv_exit
)paren
suffix:semicolon
eof
