multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * [ Initialisation is based on Linus&squot;  ]&n; * [ uhci code and gregs ohci fragments ]&n; * [ (C) Copyright 1999 Linus Torvalds  ]&n; * [ (C) Copyright 1999 Gregory P. Smith]&n; * &n; * PCI Bus Glue&n; *&n; * This file is licenced under the GPL.&n; */
macro_line|#ifdef CONFIG_PMAC_PBOOK
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
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
id|hcd-&gt;pdev
)paren
(brace
id|ohci-&gt;hcca
op_assign
id|pci_alloc_consistent
(paren
id|hcd-&gt;pdev
comma
r_sizeof
op_star
id|ohci-&gt;hcca
comma
op_amp
id|ohci-&gt;hcca_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;hcca
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* AMD 756, for most chips (early revs), corrupts register&n;&t;&t; * values on read ... so enable the vendor workaround.&n;&t;&t; */
r_if
c_cond
(paren
id|hcd-&gt;pdev-&gt;vendor
op_eq
l_int|0x1022
op_logical_and
id|hcd-&gt;pdev-&gt;device
op_eq
l_int|0x740c
)paren
(brace
id|ohci-&gt;flags
op_assign
id|OHCI_QUIRK_AMD756
suffix:semicolon
id|info
(paren
l_string|&quot;%s: AMD756 erratum 4 workaround&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
)brace
multiline_comment|/* Apple&squot;s OHCI driver has a lot of bizarre workarounds&n;&t;&t; * for this chip.  Evidently control and bulk lists&n;&t;&t; * can get confused.  (B&amp;W G3 models, and ...)&n;&t;&t; */
r_else
r_if
c_cond
(paren
id|hcd-&gt;pdev-&gt;vendor
op_eq
l_int|0x1045
op_logical_and
id|hcd-&gt;pdev-&gt;device
op_eq
l_int|0xc861
)paren
(brace
id|info
(paren
l_string|&quot;%s: WARNING: OPTi workarounds unavailable&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
)brace
)brace
id|memset
(paren
id|ohci-&gt;hcca
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ohci_hcca
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ohci_mem_init
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ohci-&gt;regs
op_assign
id|hcd-&gt;regs
suffix:semicolon
id|ohci-&gt;parent_dev
op_assign
op_amp
id|ohci-&gt;hcd.pdev-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|hc_reset
(paren
id|ohci
)paren
OL
l_int|0
)paren
(brace
id|ohci_stop
(paren
id|hcd
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
id|hc_start
(paren
id|ohci
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t start %s&quot;
comma
id|ohci-&gt;hcd.self.bus_name
)paren
suffix:semicolon
id|ohci_stop
(paren
id|hcd
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
macro_line|#ifdef&t;DEBUG
id|ohci_dump
(paren
id|ohci
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
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
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|cmd
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
op_ne
id|OHCI_USB_OPER
)paren
(brace
id|dbg
(paren
l_string|&quot;can&squot;t suspend %s (state is %s)&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|hcfs2string
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* act as if usb suspend can always be used */
id|dbg
(paren
l_string|&quot;%s: suspend to %d&quot;
comma
id|hcd-&gt;self.bus_name
comma
id|state
)paren
suffix:semicolon
id|ohci-&gt;sleeping
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* First stop processing */
id|spin_lock_irqsave
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_and_assign
op_complement
(paren
id|OHCI_CTRL_PLE
op_or
id|OHCI_CTRL_CLE
op_or
id|OHCI_CTRL_BLE
op_or
id|OHCI_CTRL_IE
)paren
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_INTR_SF
comma
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
(paren
r_void
)paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Wait a frame or two */
id|mdelay
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
op_amp
id|OHCI_INTR_SF
)paren
id|mdelay
(paren
l_int|1
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
id|hcd-&gt;pdev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* else, 2.4 assumes shared irqs -- don&squot;t disable */
macro_line|#endif
multiline_comment|/* Enable remote wakeup */
id|writel
(paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
op_or
id|OHCI_INTR_RD
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
multiline_comment|/* Suspend chip and let things settle down a bit */
id|ohci-&gt;hc_control
op_assign
id|OHCI_USB_SUSPEND
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|mdelay
(paren
l_int|500
)paren
suffix:semicolon
multiline_comment|/* No schedule here ! */
r_switch
c_cond
(paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
op_amp
id|OHCI_CTRL_HCFS
)paren
(brace
r_case
id|OHCI_USB_RESET
suffix:colon
id|dbg
(paren
l_string|&quot;%s suspend-&gt;reset ?&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_RESUME
suffix:colon
id|dbg
(paren
l_string|&quot;%s suspend-&gt;resume ?&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_OPER
suffix:colon
id|dbg
(paren
l_string|&quot;%s suspend-&gt;operational ?&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_SUSPEND
suffix:colon
id|dbg
(paren
l_string|&quot;%s suspended&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* In some rare situations, Apple&squot;s OHCI have happily trashed&n;&t; * memory during sleep. We disable its bus master bit during&n;&t; * suspend&n;&t; */
id|pci_read_config_word
(paren
id|hcd-&gt;pdev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|cmd
op_and_assign
op_complement
id|PCI_COMMAND_MASTER
suffix:semicolon
id|pci_write_config_word
(paren
id|hcd-&gt;pdev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
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
id|hcd-&gt;pdev
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
id|temp
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
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
id|hcd-&gt;pdev
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
multiline_comment|/* did we suspend, or were we powered off? */
id|ohci-&gt;hc_control
op_assign
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|temp
op_assign
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
suffix:semicolon
macro_line|#ifdef DEBUG
multiline_comment|/* the registers may look crazy here */
id|ohci_dump_status
(paren
id|ohci
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Re-enable bus mastering */
id|pci_set_master
(paren
id|ohci-&gt;hcd.pdev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|temp
)paren
(brace
r_case
id|OHCI_USB_RESET
suffix:colon
singleline_comment|// lost power
id|info
(paren
l_string|&quot;USB restart: %s&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|retval
op_assign
id|hc_restart
(paren
id|ohci
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_SUSPEND
suffix:colon
singleline_comment|// host wakeup
r_case
id|OHCI_USB_RESUME
suffix:colon
singleline_comment|// remote wakeup
id|info
(paren
l_string|&quot;USB continue: %s from %s wakeup&quot;
comma
id|hcd-&gt;self.bus_name
comma
(paren
id|temp
op_eq
id|OHCI_USB_SUSPEND
)paren
ques
c_cond
l_string|&quot;host&quot;
suffix:colon
l_string|&quot;remote&quot;
)paren
suffix:semicolon
id|ohci-&gt;hc_control
op_assign
id|OHCI_USB_RESUME
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|mdelay
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/* no schedule here ! */
multiline_comment|/* Some controllers (lucent) need a longer delay here */
id|mdelay
(paren
l_int|15
)paren
suffix:semicolon
id|temp
op_assign
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|temp
op_assign
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_ne
id|OHCI_USB_RESUME
)paren
(brace
id|err
(paren
l_string|&quot;controller %s won&squot;t resume&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Some chips likes being resumed first */
id|writel
(paren
id|OHCI_USB_OPER
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
(paren
r_void
)paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
id|mdelay
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Then re-enable operations */
id|spin_lock_irqsave
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|0
suffix:semicolon
id|ohci-&gt;sleeping
op_assign
l_int|0
suffix:semicolon
id|ohci-&gt;hc_control
op_assign
id|OHCI_CONTROL_INIT
op_or
id|OHCI_USB_OPER
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ohci-&gt;ed_rm_list
)paren
(brace
r_if
c_cond
(paren
id|ohci-&gt;ed_controltail
)paren
id|ohci-&gt;hc_control
op_or_assign
id|OHCI_CTRL_CLE
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;ed_bulktail
)paren
id|ohci-&gt;hc_control
op_or_assign
id|OHCI_CTRL_BLE
suffix:semicolon
)brace
id|hcd-&gt;state
op_assign
id|USB_STATE_READY
suffix:semicolon
id|writel
(paren
id|ohci-&gt;hc_control
comma
op_amp
id|ohci-&gt;regs-&gt;control
)paren
suffix:semicolon
multiline_comment|/* trigger a start-frame interrupt (why?) */
id|writel
(paren
id|OHCI_INTR_SF
comma
op_amp
id|ohci-&gt;regs-&gt;intrstatus
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_INTR_SF
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
multiline_comment|/* Check for a pending done list */
id|writel
(paren
id|OHCI_INTR_WDH
comma
op_amp
id|ohci-&gt;regs-&gt;intrdisable
)paren
suffix:semicolon
(paren
r_void
)paren
id|readl
(paren
op_amp
id|ohci-&gt;regs-&gt;intrdisable
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|ohci-&gt;lock
comma
id|flags
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
id|enable_irq
(paren
id|hcd-&gt;pdev-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ohci-&gt;hcca-&gt;done_head
)paren
id|dl_done_list
(paren
id|ohci
comma
id|dl_reverse_done_list
(paren
id|ohci
)paren
)paren
suffix:semicolon
id|writel
(paren
id|OHCI_INTR_WDH
comma
op_amp
id|ohci-&gt;regs-&gt;intrenable
)paren
suffix:semicolon
multiline_comment|/* assume there are TDs on the bulk and control lists */
id|writel
(paren
id|OHCI_BLF
op_or
id|OHCI_CLF
comma
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
suffix:semicolon
singleline_comment|// ohci_dump_status (ohci);
id|dbg
(paren
l_string|&quot;sleeping = %d, disabled = %d&quot;
comma
id|ohci-&gt;sleeping
comma
id|ohci-&gt;disabled
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|warn
(paren
l_string|&quot;odd PCI resume for %s&quot;
comma
id|hcd-&gt;self.bus_name
)paren
suffix:semicolon
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
id|description
suffix:colon
id|hcd_name
comma
multiline_comment|/*&n;&t; * generic hardware linkage&n;&t; */
id|irq
suffix:colon
id|ohci_irq
comma
id|flags
suffix:colon
id|HCD_MEMORY
op_or
id|HCD_USB11
comma
multiline_comment|/*&n;&t; * basic lifecycle operations&n;&t; */
id|start
suffix:colon
id|ohci_pci_start
comma
macro_line|#ifdef&t;CONFIG_PM
id|suspend
suffix:colon
id|ohci_pci_suspend
comma
id|resume
suffix:colon
id|ohci_pci_resume
comma
macro_line|#endif
id|stop
suffix:colon
id|ohci_stop
comma
multiline_comment|/*&n;&t; * memory lifecycle (except per-request)&n;&t; */
id|hcd_alloc
suffix:colon
id|ohci_hcd_alloc
comma
id|hcd_free
suffix:colon
id|ohci_hcd_free
comma
multiline_comment|/*&n;&t; * managing i/o requests and associated device resources&n;&t; */
id|urb_enqueue
suffix:colon
id|ohci_urb_enqueue
comma
id|urb_dequeue
suffix:colon
id|ohci_urb_dequeue
comma
id|free_config
suffix:colon
id|ohci_free_config
comma
multiline_comment|/*&n;&t; * scheduling support&n;&t; */
id|get_frame_number
suffix:colon
id|ohci_get_frame
comma
multiline_comment|/*&n;&t; * root hub support&n;&t; */
id|hub_status_data
suffix:colon
id|ohci_hub_status_data
comma
id|hub_control
suffix:colon
id|ohci_hub_control
comma
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|pci_ids
r_static
r_const
r_struct
id|pci_device_id
id|__devinitdata
id|pci_ids
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* handle any USB OHCI controller */
r_class
suffix:colon
(paren
id|PCI_CLASS_SERIAL_USB
op_lshift
l_int|8
)paren
op_or
l_int|0x10
comma
id|class_mask
suffix:colon
op_complement
l_int|0
comma
id|driver_data
suffix:colon
(paren
r_int
r_int
)paren
op_amp
id|ohci_pci_hc_driver
comma
multiline_comment|/* no matter who makes it */
id|vendor
suffix:colon
id|PCI_ANY_ID
comma
id|device
suffix:colon
id|PCI_ANY_ID
comma
id|subvendor
suffix:colon
id|PCI_ANY_ID
comma
id|subdevice
suffix:colon
id|PCI_ANY_ID
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
id|name
suffix:colon
(paren
r_char
op_star
)paren
id|hcd_name
comma
id|id_table
suffix:colon
id|pci_ids
comma
id|probe
suffix:colon
id|usb_hcd_pci_probe
comma
id|remove
suffix:colon
id|usb_hcd_pci_remove
comma
macro_line|#ifdef&t;CONFIG_PM
id|suspend
suffix:colon
id|usb_hcd_pci_suspend
comma
id|resume
suffix:colon
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
id|dbg
(paren
id|DRIVER_INFO
l_string|&quot; (PCI)&quot;
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;block sizes: ed %d td %d&quot;
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