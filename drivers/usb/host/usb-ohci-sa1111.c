multiline_comment|/*&n; *  linux/drivers/usb/usb-ohci-sa1111.c&n; *&n; *  The outline of this code was taken from Brad Parkers &lt;brad@heeltoe.com&gt;&n; *  original OHCI driver modifications, and reworked into a cleaner form&n; *  by Russell King &lt;rmk@arm.linux.org.uk&gt;.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/assabet.h&gt;
macro_line|#include &lt;asm/arch/badge4.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;usb-ohci.h&quot;
r_int
id|__devinit
id|hc_add_ohci
c_func
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
id|membase
comma
r_int
r_int
id|flags
comma
id|ohci_t
op_star
op_star
id|ohci
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|slot_name
)paren
suffix:semicolon
r_extern
r_void
id|hc_remove_ohci
c_func
(paren
id|ohci_t
op_star
id|ohci
)paren
suffix:semicolon
DECL|variable|sa1111_ohci
r_static
id|ohci_t
op_star
id|sa1111_ohci
suffix:semicolon
DECL|function|sa1111_ohci_configure
r_static
r_void
id|__init
id|sa1111_ohci_configure
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|usb_rst
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_xp860
c_func
(paren
)paren
op_logical_or
id|machine_has_neponset
c_func
(paren
)paren
op_logical_or
id|machine_is_pfs168
c_func
(paren
)paren
op_logical_or
id|machine_is_badge4
c_func
(paren
)paren
)paren
id|usb_rst
op_assign
id|USB_RESET_PWRSENSELOW
op_or
id|USB_RESET_PWRCTRLLOW
suffix:semicolon
multiline_comment|/*&n;&t; * Configure the power sense and control lines.  Place the USB&n;&t; * host controller in reset.&n;&t; */
id|USB_RESET
op_assign
id|usb_rst
op_or
id|USB_RESET_FORCEIFRESET
op_or
id|USB_RESET_FORCEHCRESET
suffix:semicolon
multiline_comment|/*&n;&t; * Now, carefully enable the USB clock, and take&n;&t; * the USB host controller out of reset.&n;&t; */
id|SKPCR
op_or_assign
id|SKPCR_UCLKEN
suffix:semicolon
id|udelay
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|USB_RESET
op_assign
id|usb_rst
suffix:semicolon
)brace
DECL|function|sa1111_ohci_init
r_static
r_int
id|__init
id|sa1111_ohci_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sa1111
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Request memory resources.&n;&t; */
singleline_comment|//&t;if (!request_mem_region(_USB_OHCI_OP_BASE, _USB_EXTENT, &quot;usb-ohci&quot;))
singleline_comment|//&t;&t;return -EBUSY;
id|sa1111_ohci_configure
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise the generic OHCI driver.&n;&t; */
id|ret
op_assign
id|hc_add_ohci
c_func
(paren
(paren
r_struct
id|pci_dev
op_star
)paren
l_int|1
comma
id|NIRQHCIM
comma
(paren
r_void
op_star
)paren
op_amp
id|USB_OHCI_OP_BASE
comma
l_int|0
comma
op_amp
id|sa1111_ohci
comma
l_string|&quot;usb-ohci&quot;
comma
l_string|&quot;sa1111&quot;
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
r_if
c_cond
(paren
id|hc_start
(paren
id|sa1111_ohci
comma
op_amp
id|sa1111-&gt;dev
)paren
OL
l_int|0
)paren
(brace
id|err
(paren
l_string|&quot;can&squot;t start usb-%s&quot;
comma
id|sa1111_ohci-&gt;slot_name
)paren
suffix:semicolon
id|hc_remove_ohci
(paren
id|sa1111_ohci
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
macro_line|#ifdef CONFIG_SA1100_BADGE4
r_if
c_cond
(paren
id|machine_is_badge4
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* found the controller, so now power the bus */
id|badge4_set_5V
c_func
(paren
id|BADGE4_5V_USB
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
singleline_comment|//&t;else
singleline_comment|//&t;&t;release_mem_region(_USB_OHCI_OP_BASE, _USB_EXTENT);
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sa1111_ohci_exit
r_static
r_void
id|__exit
id|sa1111_ohci_exit
c_func
(paren
r_void
)paren
(brace
id|hc_remove_ohci
c_func
(paren
id|sa1111_ohci
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Put the USB host controller into reset.&n;&t; */
id|USB_RESET
op_or_assign
id|USB_RESET_FORCEIFRESET
op_or
id|USB_RESET_FORCEHCRESET
suffix:semicolon
multiline_comment|/*&n;&t; * Stop the USB clock.&n;&t; */
id|SKPCR
op_and_assign
op_complement
id|SKPCR_UCLKEN
suffix:semicolon
multiline_comment|/*&n;&t; * Release memory resources.&n;&t; */
singleline_comment|//&t;release_mem_region(_USB_OHCI_OP_BASE, _USB_EXTENT);
macro_line|#ifdef CONFIG_SA1100_BADGE4
r_if
c_cond
(paren
id|machine_is_badge4
c_func
(paren
)paren
)paren
(brace
id|badge4_set_5V
c_func
(paren
id|BADGE4_5V_USB
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|variable|sa1111_ohci_init
id|module_init
c_func
(paren
id|sa1111_ohci_init
)paren
suffix:semicolon
DECL|variable|sa1111_ohci_exit
id|module_exit
c_func
(paren
id|sa1111_ohci_exit
)paren
suffix:semicolon
eof