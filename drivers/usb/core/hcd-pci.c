multiline_comment|/*&n; * (C) Copyright David Brownell 2000-2002&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;hcd.h&quot;
multiline_comment|/* PCI-based HCs are normal, but custom bus glue should be ok */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* configure so an HC device and id are always provided */
multiline_comment|/* always called with process context; sleeping is OK */
multiline_comment|/**&n; * usb_hcd_pci_probe - initialize PCI-based HCDs&n; * @dev: USB Host Controller being probed&n; * @id: pci hotplug id connecting controller to HCD framework&n; * Context: !in_interrupt()&n; *&n; * Allocates basic PCI resources for this USB host controller, and&n; * then invokes the start() method for the HCD associated with it&n; * through the hotplug entry&squot;s driver_data.&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as probe().&n; */
DECL|function|usb_hcd_pci_probe
r_int
id|usb_hcd_pci_probe
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
r_struct
id|hc_driver
op_star
id|driver
suffix:semicolon
r_struct
id|usb_hcd
op_star
id|hcd
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|usb_disabled
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|id
op_logical_or
op_logical_neg
(paren
id|driver
op_assign
(paren
r_struct
id|hc_driver
op_star
)paren
id|id-&gt;driver_data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
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
id|dev-&gt;current_state
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;dev.power.power_state
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
id|dev_err
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Found HC with no IRQ.  Check BIOS/PCI %s setup!&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
id|hcd
op_assign
id|usb_create_hcd
(paren
id|driver
comma
op_amp
id|dev-&gt;dev
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
op_logical_neg
id|hcd
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|driver-&gt;flags
op_amp
id|HCD_MEMORY
)paren
(brace
singleline_comment|// EHCI, OHCI
id|hcd-&gt;rsrc_start
op_assign
id|pci_resource_start
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|hcd-&gt;rsrc_len
op_assign
id|pci_resource_len
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
comma
id|driver-&gt;description
)paren
)paren
(brace
id|dev_dbg
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;controller already in use&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
id|hcd-&gt;regs
op_assign
id|ioremap_nocache
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcd-&gt;regs
op_eq
l_int|NULL
)paren
(brace
id|dev_dbg
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;error mapping memory&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err3
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// UHCI
r_int
id|region
suffix:semicolon
r_for
c_loop
(paren
id|region
op_assign
l_int|0
suffix:semicolon
id|region
OL
id|PCI_ROM_RESOURCE
suffix:semicolon
id|region
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pci_resource_flags
(paren
id|dev
comma
id|region
)paren
op_amp
id|IORESOURCE_IO
)paren
)paren
r_continue
suffix:semicolon
id|hcd-&gt;rsrc_start
op_assign
id|pci_resource_start
(paren
id|dev
comma
id|region
)paren
suffix:semicolon
id|hcd-&gt;rsrc_len
op_assign
id|pci_resource_len
(paren
id|dev
comma
id|region
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
comma
id|driver-&gt;description
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|region
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
id|dev_dbg
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;no i/o regions available&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PCI_NAMES
id|hcd-&gt;product_desc
op_assign
id|dev-&gt;pretty_name
suffix:semicolon
macro_line|#endif
id|pci_set_master
(paren
id|dev
)paren
suffix:semicolon
id|retval
op_assign
id|usb_add_hcd
(paren
id|hcd
comma
id|dev-&gt;irq
comma
id|SA_SHIRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_goto
id|err4
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|err4
suffix:colon
r_if
c_cond
(paren
id|driver-&gt;flags
op_amp
id|HCD_MEMORY
)paren
(brace
id|iounmap
(paren
id|hcd-&gt;regs
)paren
suffix:semicolon
id|err3
suffix:colon
id|release_mem_region
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
)brace
r_else
id|release_region
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
id|err2
suffix:colon
id|usb_put_hcd
(paren
id|hcd
)paren
suffix:semicolon
id|err1
suffix:colon
id|pci_disable_device
(paren
id|dev
)paren
suffix:semicolon
id|dev_err
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;init %s fail, %d&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|usb_hcd_pci_probe
id|EXPORT_SYMBOL
(paren
id|usb_hcd_pci_probe
)paren
suffix:semicolon
multiline_comment|/* may be called without controller electrically present */
multiline_comment|/* may be called with controller, bus, and devices active */
multiline_comment|/**&n; * usb_hcd_pci_remove - shutdown processing for PCI-based HCDs&n; * @dev: USB Host Controller being removed&n; * Context: !in_interrupt()&n; *&n; * Reverses the effect of usb_hcd_pci_probe(), first invoking&n; * the HCD&squot;s stop() method.  It is always called from a thread&n; * context, normally &quot;rmmod&quot;, &quot;apmd&quot;, or something similar.&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as remove().&n; */
DECL|function|usb_hcd_pci_remove
r_void
id|usb_hcd_pci_remove
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
suffix:semicolon
id|hcd
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hcd
)paren
r_return
suffix:semicolon
id|usb_remove_hcd
(paren
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcd-&gt;driver-&gt;flags
op_amp
id|HCD_MEMORY
)paren
(brace
id|iounmap
(paren
id|hcd-&gt;regs
)paren
suffix:semicolon
id|release_mem_region
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
)brace
r_else
(brace
id|release_region
(paren
id|hcd-&gt;rsrc_start
comma
id|hcd-&gt;rsrc_len
)paren
suffix:semicolon
)brace
id|usb_put_hcd
(paren
id|hcd
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|usb_hcd_pci_remove
id|EXPORT_SYMBOL
(paren
id|usb_hcd_pci_remove
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_PM
DECL|function|pci_state
r_static
r_char
id|__attribute_used__
op_star
id|pci_state
c_func
(paren
id|u32
id|state
)paren
(brace
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_string|&quot;D0&quot;
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_string|&quot;D1&quot;
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
l_string|&quot;D2&quot;
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_string|&quot;D3hot&quot;
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
l_string|&quot;D3cold&quot;
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_hcd_pci_suspend - power management suspend of a PCI-based HCD&n; * @dev: USB Host Controller being suspended&n; * @state: state that the controller is going into&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as suspend().&n; */
DECL|function|usb_hcd_pci_suspend
r_int
id|usb_hcd_pci_suspend
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
r_struct
id|usb_hcd
op_star
id|hcd
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|has_pci_pm
suffix:semicolon
id|hcd
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* even when the PCI layer rejects some of the PCI calls&n;&t; * below, HCs can try global suspend and reduce DMA traffic.&n;&t; * PM-sensitive HCDs may already have done this.&n;&t; */
id|has_pci_pm
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_PM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
OG
l_int|4
)paren
id|state
op_assign
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|hcd-&gt;state
)paren
(brace
multiline_comment|/* entry if root hub wasn&squot;t yet suspended ... from sysfs,&n;&t; * without autosuspend, or if USB_SUSPEND isn&squot;t configured.&n;&t; */
r_case
id|HC_STATE_RUNNING
suffix:colon
id|hcd-&gt;state
op_assign
id|HC_STATE_QUIESCING
suffix:semicolon
id|retval
op_assign
id|hcd-&gt;driver-&gt;suspend
(paren
id|hcd
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|dev_dbg
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;suspend fail, retval %d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hcd-&gt;state
op_assign
id|HC_STATE_SUSPENDED
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
multiline_comment|/* entry with CONFIG_USB_SUSPEND, or hcds that autosuspend: the&n;&t; * controller and/or root hub will already have been suspended,&n;&t; * but it won&squot;t be ready for a PCI resume call.&n;&t; *&n;&t; * FIXME only CONFIG_USB_SUSPEND guarantees hub_suspend() will&n;&t; * have been called, otherwise root hub timers still run ...&n;&t; */
r_case
id|HC_STATE_SUSPENDED
suffix:colon
r_if
c_cond
(paren
id|state
op_le
id|dev-&gt;current_state
)paren
r_break
suffix:semicolon
multiline_comment|/* no DMA or IRQs except in D0 */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;current_state
)paren
(brace
id|pci_save_state
(paren
id|dev
)paren
suffix:semicolon
id|pci_disable_device
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
(paren
id|hcd-&gt;irq
comma
id|hcd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|has_pci_pm
)paren
(brace
id|dev_dbg
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;--&gt; PCI D0/legacy&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* POLICY: ignore D1/D2/D3hot differences;&n;&t;&t; * we know D3hot will always work.&n;&t;&t; */
id|retval
op_assign
id|pci_set_power_state
(paren
id|dev
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
op_logical_and
id|state
OL
l_int|3
)paren
(brace
id|retval
op_assign
id|pci_set_power_state
(paren
id|dev
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|state
op_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
id|dev_dbg
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;--&gt; PCI %s&bslash;n&quot;
comma
id|pci_state
c_func
(paren
id|dev-&gt;current_state
)paren
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
id|pci_enable_wake
(paren
id|dev
comma
id|state
comma
id|hcd-&gt;remote_wakeup
)paren
suffix:semicolon
id|pci_enable_wake
(paren
id|dev
comma
l_int|4
comma
id|hcd-&gt;remote_wakeup
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|dev_dbg
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;PCI %s suspend fail, %d&bslash;n&quot;
comma
id|pci_state
c_func
(paren
id|state
)paren
comma
id|retval
)paren
suffix:semicolon
(paren
r_void
)paren
id|usb_hcd_pci_resume
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|dev_dbg
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;hcd state %d; not suspended&bslash;n&quot;
comma
id|hcd-&gt;state
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* update power_state **ONLY** to make sysfs happier */
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|dev-&gt;dev.power.power_state
op_assign
id|state
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|usb_hcd_pci_suspend
id|EXPORT_SYMBOL
(paren
id|usb_hcd_pci_suspend
)paren
suffix:semicolon
multiline_comment|/**&n; * usb_hcd_pci_resume - power management resume of a PCI-based HCD&n; * @dev: USB Host Controller being resumed&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as resume().&n; */
DECL|function|usb_hcd_pci_resume
r_int
id|usb_hcd_pci_resume
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|has_pci_pm
suffix:semicolon
id|hcd
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcd-&gt;state
op_ne
id|HC_STATE_SUSPENDED
)paren
(brace
id|dev_dbg
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;can&squot;t resume, not suspended!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|has_pci_pm
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_PM
)paren
suffix:semicolon
multiline_comment|/* D3cold resume isn&squot;t usually reported this way... */
id|dev_dbg
c_func
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;resume from PCI %s%s&bslash;n&quot;
comma
id|pci_state
c_func
(paren
id|dev-&gt;current_state
)paren
comma
id|has_pci_pm
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (legacy)&quot;
)paren
suffix:semicolon
id|hcd-&gt;state
op_assign
id|HC_STATE_RESUMING
suffix:semicolon
r_if
c_cond
(paren
id|has_pci_pm
)paren
id|pci_set_power_state
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;dev.power.power_state
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|request_irq
(paren
id|dev-&gt;irq
comma
id|usb_hcd_irq
comma
id|SA_SHIRQ
comma
id|hcd-&gt;driver-&gt;description
comma
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|dev_err
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;can&squot;t restore IRQ after resume!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|hcd-&gt;saw_irq
op_assign
l_int|0
suffix:semicolon
id|pci_restore_state
(paren
id|dev
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
id|pci_enable_wake
(paren
id|dev
comma
id|dev-&gt;current_state
comma
l_int|0
)paren
suffix:semicolon
id|pci_enable_wake
(paren
id|dev
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|retval
op_assign
id|hcd-&gt;driver-&gt;resume
(paren
id|hcd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HC_IS_RUNNING
(paren
id|hcd-&gt;state
)paren
)paren
(brace
id|dev_dbg
(paren
id|hcd-&gt;self.controller
comma
l_string|&quot;resume fail, retval %d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
id|usb_hc_died
(paren
id|hcd
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|usb_hcd_pci_resume
id|EXPORT_SYMBOL
(paren
id|usb_hcd_pci_resume
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_PM */
eof
