multiline_comment|/*&n; * (C) Copyright David Brownell 2000-2002&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
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
r_int
r_int
id|resource
comma
id|len
suffix:semicolon
r_void
op_star
id|base
suffix:semicolon
r_struct
id|usb_hcd
op_star
id|hcd
suffix:semicolon
r_int
id|retval
comma
id|region
suffix:semicolon
r_char
id|buf
(braket
l_int|8
)braket
comma
op_star
id|bufp
op_assign
id|buf
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
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
id|err
(paren
l_string|&quot;Found HC with no IRQ.  Check BIOS/PCI %s setup!&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
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
id|region
op_assign
l_int|0
suffix:semicolon
id|resource
op_assign
id|pci_resource_start
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|len
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
id|resource
comma
id|len
comma
id|driver-&gt;description
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;controller already in use&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|base
op_assign
id|ioremap_nocache
(paren
id|resource
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|NULL
)paren
(brace
id|dbg
(paren
l_string|&quot;error mapping memory&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|clean_1
suffix:colon
id|release_mem_region
(paren
id|resource
comma
id|len
)paren
suffix:semicolon
id|err
(paren
l_string|&quot;init %s fail, %d&quot;
comma
id|dev-&gt;slot_name
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// UHCI
id|resource
op_assign
id|len
op_assign
l_int|0
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
id|resource
op_assign
id|pci_resource_start
(paren
id|dev
comma
id|region
)paren
suffix:semicolon
id|len
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
id|resource
comma
id|len
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
id|dbg
(paren
l_string|&quot;no i/o regions available&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|base
op_assign
(paren
r_void
op_star
)paren
id|resource
suffix:semicolon
)brace
singleline_comment|// driver-&gt;start(), later on, will transfer device from
singleline_comment|// control by SMM/BIOS to control by Linux (if needed)
id|pci_set_master
(paren
id|dev
)paren
suffix:semicolon
id|hcd
op_assign
id|driver-&gt;hcd_alloc
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcd
op_eq
l_int|NULL
)paren
(brace
id|dbg
(paren
l_string|&quot;hcd alloc fail&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|clean_2
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
id|base
)paren
suffix:semicolon
r_goto
id|clean_1
suffix:semicolon
)brace
r_else
(brace
id|release_region
(paren
id|resource
comma
id|len
)paren
suffix:semicolon
id|err
(paren
l_string|&quot;init %s fail, %d&quot;
comma
id|dev-&gt;slot_name
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
)brace
id|pci_set_drvdata
(paren
id|dev
comma
id|hcd
)paren
suffix:semicolon
id|hcd-&gt;driver
op_assign
id|driver
suffix:semicolon
id|hcd-&gt;description
op_assign
id|driver-&gt;description
suffix:semicolon
id|hcd-&gt;pdev
op_assign
id|dev
suffix:semicolon
id|hcd-&gt;self.bus_name
op_assign
id|dev-&gt;slot_name
suffix:semicolon
id|hcd-&gt;product_desc
op_assign
id|dev-&gt;dev.name
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|hcd_buffer_create
(paren
id|hcd
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|clean_3
suffix:colon
id|driver-&gt;hcd_free
(paren
id|hcd
)paren
suffix:semicolon
r_goto
id|clean_2
suffix:semicolon
)brace
id|info
(paren
l_string|&quot;%s @ %s, %s&quot;
comma
id|hcd-&gt;description
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;dev.name
)paren
suffix:semicolon
macro_line|#ifndef __sparc__
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#else
id|bufp
op_assign
id|__irq_itoa
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|request_irq
(paren
id|dev-&gt;irq
comma
id|usb_hcd_irq
comma
id|SA_SHIRQ
comma
id|hcd-&gt;description
comma
id|hcd
)paren
op_ne
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;request interrupt %s failed&quot;
comma
id|bufp
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|clean_3
suffix:semicolon
)brace
id|hcd-&gt;irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|hcd-&gt;regs
op_assign
id|base
suffix:semicolon
id|hcd-&gt;region
op_assign
id|region
suffix:semicolon
id|info
(paren
l_string|&quot;irq %s, %s %p&quot;
comma
id|bufp
comma
(paren
id|driver-&gt;flags
op_amp
id|HCD_MEMORY
)paren
ques
c_cond
l_string|&quot;pci mem&quot;
suffix:colon
l_string|&quot;io base&quot;
comma
id|base
)paren
suffix:semicolon
id|usb_bus_init
(paren
op_amp
id|hcd-&gt;self
)paren
suffix:semicolon
id|hcd-&gt;self.op
op_assign
op_amp
id|usb_hcd_operations
suffix:semicolon
id|hcd-&gt;self.hcpriv
op_assign
(paren
r_void
op_star
)paren
id|hcd
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|hcd-&gt;dev_list
)paren
suffix:semicolon
id|usb_register_bus
(paren
op_amp
id|hcd-&gt;self
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|driver-&gt;start
(paren
id|hcd
)paren
)paren
OL
l_int|0
)paren
id|usb_hcd_pci_remove
(paren
id|dev
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
r_struct
id|usb_device
op_star
id|hub
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
id|info
(paren
l_string|&quot;remove: %s, state %x&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|hcd-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
(paren
)paren
)paren
id|BUG
(paren
)paren
suffix:semicolon
id|hub
op_assign
id|hcd-&gt;self.root_hub
suffix:semicolon
id|hcd-&gt;state
op_assign
id|USB_STATE_QUIESCING
suffix:semicolon
id|dbg
(paren
l_string|&quot;%s: roothub graceful disconnect&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|usb_disconnect
(paren
op_amp
id|hub
)paren
suffix:semicolon
id|hcd-&gt;driver-&gt;stop
(paren
id|hcd
)paren
suffix:semicolon
id|hcd_buffer_destroy
(paren
id|hcd
)paren
suffix:semicolon
id|hcd-&gt;state
op_assign
id|USB_STATE_HALT
suffix:semicolon
id|free_irq
(paren
id|hcd-&gt;irq
comma
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
id|pci_resource_start
(paren
id|dev
comma
l_int|0
)paren
comma
id|pci_resource_len
(paren
id|dev
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|release_region
(paren
id|pci_resource_start
(paren
id|dev
comma
id|hcd-&gt;region
)paren
comma
id|pci_resource_len
(paren
id|dev
comma
id|hcd-&gt;region
)paren
)paren
suffix:semicolon
)brace
id|usb_deregister_bus
(paren
op_amp
id|hcd-&gt;self
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
id|hcd-&gt;self.refcnt
)paren
op_ne
l_int|1
)paren
id|err
(paren
l_string|&quot;usb_hcd_pci_remove %s, count != 1&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|hcd-&gt;driver-&gt;hcd_free
(paren
id|hcd
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
multiline_comment|/*&n; * Some &quot;sleep&quot; power levels imply updating struct usb_driver&n; * to include a callback asking hcds to do their bit by checking&n; * if all the drivers can suspend.  Gets involved with remote wakeup.&n; *&n; * If there are pending urbs, then HCs will need to access memory,&n; * causing extra power drain.  New sleep()/wakeup() PM calls might&n; * be needed, beyond PCI suspend()/resume().  The root hub timer&n; * still be accessing memory though ...&n; *&n; * FIXME:  USB should have some power budgeting support working with&n; * all kinds of hubs.&n; *&n; * FIXME:  This assumes only D0-&gt;D3 suspend and D3-&gt;D0 resume.&n; * D1 and D2 states should do something, yes?&n; *&n; * FIXME:  Should provide generic enable_wake(), calling pci_enable_wake()&n; * for all supported states, so that USB remote wakeup can work for any&n; * devices that support it (and are connected via powered hubs).&n; *&n; * FIXME:  resume doesn&squot;t seem to work right any more...&n; */
singleline_comment|// 2.4 kernels have issued concurrent resumes (w/APM)
singleline_comment|// we defend against that error; PCI doesn&squot;t yet.
multiline_comment|/**&n; * usb_hcd_pci_suspend - power management suspend of a PCI-based HCD&n; * @dev: USB Host Controller being suspended&n; *&n; * Store this function in the HCD&squot;s struct pci_driver as suspend().&n; */
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
suffix:semicolon
id|hcd
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|info
(paren
l_string|&quot;suspend %s to state %d&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|state
)paren
suffix:semicolon
id|pci_save_state
(paren
id|dev
comma
id|hcd-&gt;pci_state
)paren
suffix:semicolon
singleline_comment|// FIXME for all connected devices, leaf-to-root:
singleline_comment|// driver-&gt;suspend()
singleline_comment|// proposed &quot;new 2.5 driver model&quot; will automate that
multiline_comment|/* driver may want to disable DMA etc */
id|retval
op_assign
id|hcd-&gt;driver-&gt;suspend
(paren
id|hcd
comma
id|state
)paren
suffix:semicolon
id|hcd-&gt;state
op_assign
id|USB_STATE_SUSPENDED
suffix:semicolon
id|pci_set_power_state
(paren
id|dev
comma
id|state
)paren
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
id|hcd
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|info
(paren
l_string|&quot;resume %s&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
multiline_comment|/* guard against multiple resumes (APM bug?) */
id|atomic_inc
(paren
op_amp
id|hcd-&gt;resume_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
id|hcd-&gt;resume_count
)paren
op_ne
l_int|1
)paren
(brace
id|err
(paren
l_string|&quot;concurrent PCI resumes for %s&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|hcd-&gt;state
op_ne
id|USB_STATE_SUSPENDED
)paren
(brace
id|dbg
(paren
l_string|&quot;can&squot;t resume, not suspended!&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|hcd-&gt;state
op_assign
id|USB_STATE_RESUMING
suffix:semicolon
id|pci_set_power_state
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|pci_restore_state
(paren
id|dev
comma
id|hcd-&gt;pci_state
)paren
suffix:semicolon
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
id|HCD_IS_RUNNING
(paren
id|hcd-&gt;state
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;resume %s failure, retval %d&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|retval
)paren
suffix:semicolon
id|usb_hc_died
(paren
id|hcd
)paren
suffix:semicolon
singleline_comment|// FIXME:  recover, reset etc.
)brace
r_else
(brace
singleline_comment|// FIXME for all connected devices, root-to-leaf:
singleline_comment|// driver-&gt;resume ();
singleline_comment|// proposed &quot;new 2.5 driver model&quot; will automate that
)brace
id|done
suffix:colon
id|atomic_dec
(paren
op_amp
id|hcd-&gt;resume_count
)paren
suffix:semicolon
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
