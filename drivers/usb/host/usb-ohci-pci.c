macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;  /* for in_interrupt() */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;../core/hcd.h&quot;
macro_line|#include &quot;usb-ohci.h&quot;
macro_line|#ifdef CONFIG_PMAC_PBOOK
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#ifndef CONFIG_PM
DECL|macro|CONFIG_PM
mdefine_line|#define CONFIG_PM
macro_line|#endif
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* Increment the module usage count, start the control thread and&n; * return success. */
DECL|variable|ohci_pci_driver
r_static
r_struct
id|pci_driver
id|ohci_pci_driver
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|hc_found_ohci
id|hc_found_ohci
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
comma
r_void
op_star
id|mem_base
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
id|u8
id|latency
comma
id|limit
suffix:semicolon
id|ohci_t
op_star
id|ohci
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|__FILE__
l_string|&quot;: usb-%s, %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* bad pci latencies can contribute to overruns */
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|latency
)paren
suffix:semicolon
r_if
c_cond
(paren
id|latency
)paren
(brace
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_MAX_LAT
comma
op_amp
id|limit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|limit
op_logical_and
id|limit
OL
id|latency
)paren
(brace
id|dbg
(paren
l_string|&quot;PCI latency reduced to max %d&quot;
comma
id|limit
)paren
suffix:semicolon
id|pci_write_config_byte
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
id|limit
)paren
suffix:semicolon
id|latency
op_assign
id|limit
suffix:semicolon
)brace
)brace
id|ret
op_assign
id|hc_add_ohci
c_func
(paren
id|dev
comma
id|irq
comma
id|mem_base
comma
id|id-&gt;driver_data
comma
op_amp
id|ohci
comma
id|ohci_pci_driver.name
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|ohci-&gt;pci_latency
op_assign
id|latency
suffix:semicolon
r_if
c_cond
(paren
id|hc_start
(paren
id|ohci
comma
op_amp
id|ohci-&gt;ohci_dev-&gt;dev
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t start usb-%s&quot;
comma
id|ohci-&gt;slot_name
)paren
suffix:semicolon
id|hc_remove_ohci
c_func
(paren
id|ohci
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
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef&t;CONFIG_PM
multiline_comment|/* controller died; cleanup debris, then restart */
multiline_comment|/* must not be called from interrupt context */
DECL|function|hc_restart
r_static
r_void
id|hc_restart
(paren
id|ohci_t
op_star
id|ohci
)paren
(brace
r_int
id|temp
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;pci_latency
)paren
id|pci_write_config_byte
(paren
id|ohci-&gt;ohci_dev
comma
id|PCI_LATENCY_TIMER
comma
id|ohci-&gt;pci_latency
)paren
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
id|ohci-&gt;sleeping
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ohci-&gt;bus-&gt;root_hub
)paren
id|usb_disconnect
(paren
op_amp
id|ohci-&gt;bus-&gt;root_hub
)paren
suffix:semicolon
multiline_comment|/* empty the interrupt branches */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_INTS
suffix:semicolon
id|i
op_increment
)paren
id|ohci-&gt;ohci_int_load
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_INTS
suffix:semicolon
id|i
op_increment
)paren
id|ohci-&gt;hcca-&gt;int_table
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no EDs to remove */
id|ohci-&gt;ed_rm_list
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ohci-&gt;ed_rm_list
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* empty control and bulk lists */
id|ohci-&gt;ed_isotail
op_assign
l_int|NULL
suffix:semicolon
id|ohci-&gt;ed_controltail
op_assign
l_int|NULL
suffix:semicolon
id|ohci-&gt;ed_bulktail
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|hc_reset
(paren
id|ohci
)paren
)paren
OL
l_int|0
op_logical_or
(paren
id|temp
op_assign
id|hc_start
(paren
id|ohci
)paren
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t restart usb-%s, %d&quot;
comma
id|ohci-&gt;ohci_dev-&gt;slot_name
comma
id|temp
)paren
suffix:semicolon
)brace
r_else
id|dbg
(paren
l_string|&quot;restart usb-%s completed&quot;
comma
id|ohci-&gt;ohci_dev-&gt;slot_name
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_PM */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* configured so that an OHCI device is always provided */
multiline_comment|/* always called with process context; sleeping is OK */
r_static
r_int
id|__devinit
DECL|function|ohci_pci_probe
id|ohci_pci_probe
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
r_int
id|mem_resource
comma
id|mem_len
suffix:semicolon
r_void
op_star
id|mem_base
suffix:semicolon
r_int
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
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
id|err
c_func
(paren
l_string|&quot;found OHCI device with no IRQ assigned. check BIOS settings!&quot;
)paren
suffix:semicolon
id|pci_disable_device
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* we read its hardware registers as memory */
id|mem_resource
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|mem_len
op_assign
id|pci_resource_len
c_func
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
id|mem_resource
comma
id|mem_len
comma
id|ohci_pci_driver.name
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;controller already in use&quot;
)paren
suffix:semicolon
id|pci_disable_device
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|mem_base
op_assign
id|ioremap_nocache
(paren
id|mem_resource
comma
id|mem_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_base
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Error mapping OHCI memory&quot;
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|mem_resource
comma
id|mem_len
)paren
suffix:semicolon
id|pci_disable_device
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* controller writes into our memory */
id|pci_set_master
(paren
id|dev
)paren
suffix:semicolon
id|status
op_assign
id|hc_found_ohci
(paren
id|dev
comma
id|dev-&gt;irq
comma
id|mem_base
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
(brace
id|iounmap
(paren
id|mem_base
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|mem_resource
comma
id|mem_len
)paren
suffix:semicolon
id|pci_disable_device
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* may be called from interrupt context [interface spec] */
multiline_comment|/* may be called without controller present */
multiline_comment|/* may be called with controller, bus, and devices active */
r_static
r_void
id|__devexit
DECL|function|ohci_pci_remove
id|ohci_pci_remove
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|ohci_t
op_star
id|ohci
op_assign
(paren
id|ohci_t
op_star
)paren
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;remove %s controller usb-%s%s%s&quot;
comma
id|hcfs2string
(paren
id|ohci-&gt;hc_control
op_amp
id|OHCI_CTRL_HCFS
)paren
comma
id|dev-&gt;slot_name
comma
id|ohci-&gt;disabled
ques
c_cond
l_string|&quot; (disabled)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|in_interrupt
(paren
)paren
ques
c_cond
l_string|&quot; in interrupt&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|hc_remove_ohci
c_func
(paren
id|ohci
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
macro_line|#ifdef&t;CONFIG_PM
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|ohci_pci_suspend
id|ohci_pci_suspend
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
id|ohci_t
op_star
id|ohci
op_assign
(paren
id|ohci_t
op_star
)paren
id|pci_get_drvdata
c_func
(paren
id|dev
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
l_string|&quot;can&squot;t suspend usb-%s (state is %s)&quot;
comma
id|dev-&gt;slot_name
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
id|info
(paren
l_string|&quot;USB suspend: usb-%s&quot;
comma
id|dev-&gt;slot_name
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
id|usb_ed_lock
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
id|usb_ed_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Wait a frame or two */
id|mdelay
c_func
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
id|ohci-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* else, 2.4 assumes shared irqs -- don&squot;t disable */
macro_line|#endif
multiline_comment|/* Enable remote wakeup */
id|writel
(paren
id|readl
c_func
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
c_func
(paren
l_string|&quot;Bus in reset phase ???&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_RESUME
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Bus in resume phase ???&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_OPER
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Bus in operational phase ???&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OHCI_USB_SUSPEND
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Bus suspended&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* In some rare situations, Apple&squot;s OHCI have happily trashed&n;&t; * memory during sleep. We disable it&squot;s bus master bit during&n;&t; * suspend&n;&t; */
id|pci_read_config_word
(paren
id|dev
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
id|dev
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
id|ohci-&gt;ohci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|of_node
op_logical_and
id|_machine
op_eq
id|_MACH_Pmac
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
multiline_comment|/*-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|ohci_pci_resume
id|ohci_pci_resume
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|ohci_t
op_star
id|ohci
op_assign
(paren
id|ohci_t
op_star
)paren
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|temp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* guard against multiple resumes */
id|atomic_inc
(paren
op_amp
id|ohci-&gt;resume_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
id|ohci-&gt;resume_count
)paren
op_ne
l_int|1
)paren
(brace
id|err
(paren
l_string|&quot;concurrent PCI resumes for usb-%s&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|atomic_dec
(paren
op_amp
id|ohci-&gt;resume_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|ohci-&gt;ohci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|of_node
op_logical_and
id|_machine
op_eq
id|_MACH_Pmac
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
c_func
(paren
id|ohci-&gt;ohci_dev
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
l_string|&quot;USB restart: usb-%s&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
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
l_string|&quot;USB continue: usb-%s from %s wakeup&quot;
comma
id|dev-&gt;slot_name
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
l_string|&quot;controller usb-%s won&squot;t resume&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|ohci-&gt;disabled
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
id|EIO
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
id|usb_ed_lock
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
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|ohci-&gt;ed_rm_list
(braket
l_int|1
)braket
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
id|usb_ed_lock
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
id|ohci-&gt;irq
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
id|writel
(paren
id|OHCI_BLF
comma
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
suffix:semicolon
multiline_comment|/* start bulk list */
id|writel
(paren
id|OHCI_CLF
comma
op_amp
id|ohci-&gt;regs-&gt;cmdstatus
)paren
suffix:semicolon
multiline_comment|/* start Control list */
r_break
suffix:semicolon
r_default
suffix:colon
id|warn
(paren
l_string|&quot;odd PCI resume for usb-%s&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
)brace
multiline_comment|/* controller is operational, extra resumes are harmless */
id|atomic_dec
(paren
op_amp
id|ohci-&gt;resume_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_PM */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|variable|ohci_pci_ids
r_static
r_const
r_struct
id|pci_device_id
id|__devinitdata
id|ohci_pci_ids
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/*&n;&t; * AMD-756 [Viper] USB has a serious erratum when used with&n;&t; * lowspeed devices like mice.&n;&t; */
id|vendor
suffix:colon
l_int|0x1022
comma
id|device
suffix:colon
l_int|0x740c
comma
id|subvendor
suffix:colon
id|PCI_ANY_ID
comma
id|subdevice
suffix:colon
id|PCI_ANY_ID
comma
id|driver_data
suffix:colon
id|OHCI_QUIRK_AMD756
comma
)brace
comma
(brace
multiline_comment|/* handle any USB OHCI controller */
r_class
suffix:colon
(paren
(paren
id|PCI_CLASS_SERIAL_USB
op_lshift
l_int|8
)paren
op_or
l_int|0x10
)paren
comma
id|class_mask
suffix:colon
op_complement
l_int|0
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
id|ohci_pci_ids
)paren
suffix:semicolon
DECL|variable|ohci_pci_driver
r_static
r_struct
id|pci_driver
id|ohci_pci_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;usb-ohci&quot;
comma
id|id_table
suffix:colon
op_amp
id|ohci_pci_ids
(braket
l_int|0
)braket
comma
id|probe
suffix:colon
id|ohci_pci_probe
comma
id|remove
suffix:colon
id|__devexit_p
c_func
(paren
id|ohci_pci_remove
)paren
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
macro_line|#endif&t;/* PM */
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_init
r_static
r_int
id|__init
id|ohci_hcd_init
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
(paren
op_amp
id|ohci_pci_driver
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|ohci_hcd_cleanup
r_static
r_void
id|__exit
id|ohci_hcd_cleanup
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
DECL|variable|ohci_hcd_init
id|module_init
(paren
id|ohci_hcd_init
)paren
suffix:semicolon
DECL|variable|ohci_hcd_cleanup
id|module_exit
(paren
id|ohci_hcd_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof