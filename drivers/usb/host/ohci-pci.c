multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * [ Initialisation is based on Linus&squot;  ]&n; * [ uhci code and gregs ohci fragments ]&n; * [ (C) Copyright 1999 Linus Torvalds  ]&n; * [ (C) Copyright 1999 Gregory P. Smith]&n; * &n; * PCI Bus Glue&n; *&n; * This file is licenced under the GPL.&n; */
macro_line|#ifdef CONFIG_PMAC_PBOOK
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#ifndef CONFIG_PM
DECL|macro|CONFIG_PM
macro_line|#&t;define CONFIG_PM
macro_line|#endif
macro_line|#endif
macro_line|#ifndef CONFIG_PCI
macro_line|#error &quot;This file is PCI bus glue.  CONFIG_PCI must be defined.&quot;
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|ohci_pci_reset
id|ohci_pci_reset
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|ohci_init
(paren
id|ohci
)paren
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|ohci_pci_start
id|ohci_pci_start
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|hcd-&gt;self.controller
op_logical_and
id|hcd-&gt;self.controller-&gt;bus
op_eq
op_amp
id|pci_bus_type
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|hcd-&gt;self.controller
)paren
suffix:semicolon
multiline_comment|/* AMD 756, for most chips (early revs), corrupts register&n;&t;&t; * values on read ... so enable the vendor workaround.&n;&t;&t; */
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AMD
op_logical_and
id|pdev-&gt;device
op_eq
l_int|0x740c
)paren
(brace
id|ohci-&gt;flags
op_assign
id|OHCI_QUIRK_AMD756
suffix:semicolon
id|ohci_info
(paren
id|ohci
comma
l_string|&quot;AMD756 erratum 4 workaround&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// also somewhat erratum 10 (suspend/resume issues)
)brace
multiline_comment|/* FIXME for some of the early AMD 760 southbridges, OHCI&n;&t;&t; * won&squot;t work at all.  blacklist them.&n;&t;&t; */
multiline_comment|/* Apple&squot;s OHCI driver has a lot of bizarre workarounds&n;&t;&t; * for this chip.  Evidently control and bulk lists&n;&t;&t; * can get confused.  (B&amp;W G3 models, and ...)&n;&t;&t; */
r_else
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_OPTI
op_logical_and
id|pdev-&gt;device
op_eq
l_int|0xc861
)paren
(brace
id|ohci_info
(paren
id|ohci
comma
l_string|&quot;WARNING: OPTi workarounds unavailable&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* OPTi sometimes acts wierd during init */
id|ohci-&gt;flags
op_assign
id|OHCI_QUIRK_INITRESET
suffix:semicolon
)brace
multiline_comment|/* Check for NSC87560. We have to look at the bridge (fn1) to&n;&t;&t; * identify the USB (fn2). This quirk might apply to more or&n;&t;&t; * even all NSC stuff.&n;&t;&t; */
r_else
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NS
)paren
(brace
r_struct
id|pci_dev
op_star
id|b
suffix:semicolon
id|b
op_assign
id|pci_find_slot
(paren
id|pdev-&gt;bus-&gt;number
comma
id|PCI_DEVFN
(paren
id|PCI_SLOT
(paren
id|pdev-&gt;devfn
)paren
comma
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_logical_and
id|b-&gt;device
op_eq
id|PCI_DEVICE_ID_NS_87560_LIO
op_logical_and
id|b-&gt;vendor
op_eq
id|PCI_VENDOR_ID_NS
)paren
(brace
id|ohci-&gt;flags
op_or_assign
id|OHCI_QUIRK_SUPERIO
suffix:semicolon
id|ohci_info
(paren
id|ohci
comma
l_string|&quot;Using NSC SuperIO setup&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* SiS sometimes acts wierd during init */
r_else
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_SI
)paren
(brace
id|ohci-&gt;flags
op_assign
id|OHCI_QUIRK_INITRESET
suffix:semicolon
id|ohci_info
c_func
(paren
id|ohci
comma
l_string|&quot;SiS init quirk&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* NOTE: there may have already been a first reset, to&n;&t; * keep bios/smm irqs from making trouble&n;&t; */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ohci_run
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|ohci_err
(paren
id|ohci
comma
l_string|&quot;can&squot;t start&bslash;n&quot;
)paren
suffix:semicolon
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef&t;CONFIG_PM
DECL|function|ohci_pci_suspend
r_static
r_int
id|ohci_pci_suspend
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
id|u32
id|state
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
multiline_comment|/* suspend root hub, hoping it keeps power during suspend */
r_while
c_loop
(paren
id|time_before
(paren
id|jiffies
comma
id|ohci-&gt;next_statechange
)paren
)paren
id|msleep
(paren
l_int|100
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
(paren
r_void
)paren
id|usb_suspend_device
(paren
id|hcd-&gt;self.root_hub
comma
id|state
)paren
suffix:semicolon
macro_line|#else
id|down
(paren
op_amp
id|hcd-&gt;self.root_hub-&gt;serialize
)paren
suffix:semicolon
(paren
r_void
)paren
id|ohci_hub_suspend
(paren
id|hcd
)paren
suffix:semicolon
id|up
(paren
op_amp
id|hcd-&gt;self.root_hub-&gt;serialize
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* let things settle down a bit */
id|msleep
(paren
l_int|100
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
id|disable_irq
(paren
(paren
id|to_pci_dev
c_func
(paren
id|hcd-&gt;self.controller
)paren
)paren
op_member_access_from_pointer
id|irq
)paren
suffix:semicolon
(brace
r_struct
id|device_node
op_star
id|of_node
suffix:semicolon
multiline_comment|/* Disable USB PAD &amp; cell clock */
id|of_node
op_assign
id|pci_device_to_OF_node
(paren
id|to_pci_dev
c_func
(paren
id|hcd-&gt;self.controller
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|of_node
)paren
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_USB_ENABLE
comma
id|of_node
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ohci_pci_resume
r_static
r_int
id|ohci_pci_resume
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_struct
id|ohci_hcd
op_star
id|ohci
op_assign
id|hcd_to_ohci
(paren
id|hcd
)paren
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
(brace
r_struct
id|device_node
op_star
id|of_node
suffix:semicolon
multiline_comment|/* Re-enable USB PAD &amp; cell clock */
id|of_node
op_assign
id|pci_device_to_OF_node
(paren
id|to_pci_dev
c_func
(paren
id|hcd-&gt;self.controller
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|of_node
)paren
id|pmac_call_feature
(paren
id|PMAC_FTR_USB_ENABLE
comma
id|of_node
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* resume root hub */
r_while
c_loop
(paren
id|time_before
(paren
id|jiffies
comma
id|ohci-&gt;next_statechange
)paren
)paren
id|msleep
(paren
l_int|100
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
multiline_comment|/* get extra cleanup even if remote wakeup isn&squot;t in use */
id|retval
op_assign
id|usb_resume_device
(paren
id|hcd-&gt;self.root_hub
)paren
suffix:semicolon
macro_line|#else
id|down
(paren
op_amp
id|hcd-&gt;self.root_hub-&gt;serialize
)paren
suffix:semicolon
id|retval
op_assign
id|ohci_hub_resume
(paren
id|hcd
)paren
suffix:semicolon
id|up
(paren
op_amp
id|hcd-&gt;self.root_hub-&gt;serialize
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
id|hcd-&gt;self.controller-&gt;power.power_state
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
id|enable_irq
(paren
id|to_pci_dev
c_func
(paren
id|hcd-&gt;self.controller
)paren
op_member_access_from_pointer
id|irq
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_PM */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|ohci_pci_hc_driver
r_static
r_const
r_struct
id|hc_driver
id|ohci_pci_hc_driver
op_assign
(brace
dot
id|description
op_assign
id|hcd_name
comma
multiline_comment|/*&n;&t; * generic hardware linkage&n;&t; */
dot
id|irq
op_assign
id|ohci_irq
comma
dot
id|flags
op_assign
id|HCD_MEMORY
op_or
id|HCD_USB11
comma
multiline_comment|/*&n;&t; * basic lifecycle operations&n;&t; */
dot
id|reset
op_assign
id|ohci_pci_reset
comma
dot
id|start
op_assign
id|ohci_pci_start
comma
macro_line|#ifdef&t;CONFIG_PM
dot
id|suspend
op_assign
id|ohci_pci_suspend
comma
dot
id|resume
op_assign
id|ohci_pci_resume
comma
macro_line|#endif
dot
id|stop
op_assign
id|ohci_stop
comma
multiline_comment|/*&n;&t; * memory lifecycle (except per-request)&n;&t; */
dot
id|hcd_alloc
op_assign
id|ohci_hcd_alloc
comma
dot
id|hcd_free
op_assign
id|ohci_hcd_free
comma
multiline_comment|/*&n;&t; * managing i/o requests and associated device resources&n;&t; */
dot
id|urb_enqueue
op_assign
id|ohci_urb_enqueue
comma
dot
id|urb_dequeue
op_assign
id|ohci_urb_dequeue
comma
dot
id|endpoint_disable
op_assign
id|ohci_endpoint_disable
comma
multiline_comment|/*&n;&t; * scheduling support&n;&t; */
dot
id|get_frame_number
op_assign
id|ohci_get_frame
comma
multiline_comment|/*&n;&t; * root hub support&n;&t; */
dot
id|hub_status_data
op_assign
id|ohci_hub_status_data
comma
dot
id|hub_control
op_assign
id|ohci_hub_control
comma
macro_line|#ifdef&t;CONFIG_USB_SUSPEND
dot
id|hub_suspend
op_assign
id|ohci_hub_suspend
comma
dot
id|hub_resume
op_assign
id|ohci_hub_resume
comma
macro_line|#endif
dot
id|start_port_reset
op_assign
id|ohci_start_port_reset
comma
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|pci_ids
r_static
r_const
r_struct
id|pci_device_id
id|pci_ids
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* handle any USB OHCI controller */
id|PCI_DEVICE_CLASS
c_func
(paren
(paren
id|PCI_CLASS_SERIAL_USB
op_lshift
l_int|8
)paren
op_or
l_int|0x10
comma
op_complement
l_int|0
)paren
comma
dot
id|driver_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ohci_pci_hc_driver
comma
)brace
comma
(brace
multiline_comment|/* end: all zeroes */
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|pci_ids
)paren
suffix:semicolon
multiline_comment|/* pci driver glue; this is a &quot;new style&quot; PCI driver module */
DECL|variable|ohci_pci_driver
r_static
r_struct
id|pci_driver
id|ohci_pci_driver
op_assign
(brace
dot
id|name
op_assign
(paren
r_char
op_star
)paren
id|hcd_name
comma
dot
id|id_table
op_assign
id|pci_ids
comma
dot
id|probe
op_assign
id|usb_hcd_pci_probe
comma
dot
id|remove
op_assign
id|usb_hcd_pci_remove
comma
macro_line|#ifdef&t;CONFIG_PM
dot
id|suspend
op_assign
id|usb_hcd_pci_suspend
comma
dot
id|resume
op_assign
id|usb_hcd_pci_resume
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|ohci_hcd_pci_init
r_static
r_int
id|__init
id|ohci_hcd_pci_init
(paren
r_void
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: &quot;
id|DRIVER_INFO
l_string|&quot; (PCI)&bslash;n&quot;
comma
id|hcd_name
)paren
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
id|pr_debug
(paren
l_string|&quot;%s: block sizes: ed %Zd td %Zd&bslash;n&quot;
comma
id|hcd_name
comma
r_sizeof
(paren
r_struct
id|ed
)paren
comma
r_sizeof
(paren
r_struct
id|td
)paren
)paren
suffix:semicolon
r_return
id|pci_module_init
(paren
op_amp
id|ohci_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|ohci_hcd_pci_init
id|module_init
(paren
id|ohci_hcd_pci_init
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_pci_cleanup
r_static
r_void
id|__exit
id|ohci_hcd_pci_cleanup
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|ohci_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|ohci_hcd_pci_cleanup
id|module_exit
(paren
id|ohci_hcd_pci_cleanup
)paren
suffix:semicolon
eof
