multiline_comment|/* $Id: b1pci.c,v 1.1.4.1.2.1 2001/12/21 15:00:17 kai Exp $&n; * &n; * Module for AVM B1 PCI-card.&n; * &n; * Copyright 1999 by Carsten Paeth &lt;calle@calle.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/isdn/capicmd.h&gt;
macro_line|#include &lt;linux/isdn/capiutil.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#include &quot;avmcard.h&quot;
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.1.4.1.2.1 $&quot;
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|b1pci_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AVM
comma
id|PCI_DEVICE_ID_AVM_B1
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|b1pci_pci_tbl
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CAPI4Linux: Driver for AVM B1 PCI card&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|di
r_static
r_struct
id|capi_driver_interface
op_star
id|di
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pci_interrupt
r_static
r_void
id|b1pci_interrupt
c_func
(paren
r_int
id|interrupt
comma
r_void
op_star
id|devptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|avmcard
op_star
id|card
op_assign
id|devptr
suffix:semicolon
id|b1_handle_interrupt
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pci_procinfo
r_static
r_char
op_star
id|b1pci_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|cinfo-&gt;infobuf
comma
l_string|&quot;%s %s 0x%x %d r%d&quot;
comma
id|cinfo-&gt;cardname
(braket
l_int|0
)braket
ques
c_cond
id|cinfo-&gt;cardname
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
ques
c_cond
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;port
suffix:colon
l_int|0x0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;irq
suffix:colon
l_int|0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;revision
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|cinfo-&gt;infobuf
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pci_add_card
r_static
r_int
id|b1pci_add_card
c_func
(paren
r_struct
id|capi_driver
op_star
id|driver
comma
r_struct
id|capicardparams
op_star
id|p
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|avmcard
op_star
id|card
suffix:semicolon
id|avmctrl_info
op_star
id|cinfo
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|card
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmcard
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|memset
c_func
(paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
id|avmcard
)paren
)paren
suffix:semicolon
id|cinfo
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmctrl_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_goto
id|err_kfree
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cinfo
comma
l_int|0
comma
r_sizeof
(paren
id|avmctrl_info
)paren
)paren
suffix:semicolon
id|card-&gt;ctrlinfo
op_assign
id|cinfo
suffix:semicolon
id|cinfo-&gt;card
op_assign
id|card
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;b1pci-%x&quot;
comma
id|p-&gt;port
)paren
suffix:semicolon
id|card-&gt;port
op_assign
id|p-&gt;port
suffix:semicolon
id|card-&gt;irq
op_assign
id|p-&gt;irq
suffix:semicolon
id|card-&gt;cardtype
op_assign
id|avm_b1pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
comma
id|card-&gt;name
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ports 0x%03x-0x%03x in use.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;port
op_plus
id|AVMB1_PORTLEN
)paren
suffix:semicolon
r_goto
id|err_kfree_ctrlinfo
suffix:semicolon
)brace
id|b1_reset
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|retval
op_assign
id|b1_detect
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;cardtype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_release_region
suffix:semicolon
)brace
id|b1_reset
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|b1_getrevision
c_func
(paren
id|card
)paren
suffix:semicolon
id|retval
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|b1pci_interrupt
comma
id|SA_SHIRQ
comma
id|card-&gt;name
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to get IRQ %d.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_release_region
suffix:semicolon
)brace
id|cinfo-&gt;capi_ctrl
op_assign
id|di
op_member_access_from_pointer
id|attach_ctr
c_func
(paren
id|driver
comma
id|card-&gt;name
comma
id|cinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo-&gt;capi_ctrl
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: attach controller failed.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_free_irq
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;revision
op_ge
l_int|4
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AVM B1 PCI V4 at i/o %#x, irq %d, revision %d (no dma)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;revision
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AVM B1 PCI at i/o %#x, irq %d, revision %d&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;revision
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|err_release_region
suffix:colon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|err_kfree_ctrlinfo
suffix:colon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|err_kfree
suffix:colon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|err
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|b1pci_remove_ctr
r_static
r_void
id|b1pci_remove_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
r_int
r_int
id|port
op_assign
id|card-&gt;port
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|di
op_member_access_from_pointer
id|detach_ctr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|ctrl-&gt;driverdata
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|b1pci_driver
r_static
r_struct
id|capi_driver
id|b1pci_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;b1pci&quot;
comma
id|revision
suffix:colon
l_string|&quot;0.0&quot;
comma
id|load_firmware
suffix:colon
id|b1_load_firmware
comma
id|reset_ctr
suffix:colon
id|b1_reset_ctr
comma
id|remove_ctr
suffix:colon
id|b1pci_remove_ctr
comma
id|register_appl
suffix:colon
id|b1_register_appl
comma
id|release_appl
suffix:colon
id|b1_release_appl
comma
id|send_message
suffix:colon
id|b1_send_message
comma
id|procinfo
suffix:colon
id|b1pci_procinfo
comma
id|ctr_read_proc
suffix:colon
id|b1ctl_read_proc
comma
id|driver_read_proc
suffix:colon
l_int|0
comma
multiline_comment|/* use standard driver_read_proc */
id|add_card
suffix:colon
l_int|0
comma
multiline_comment|/* no add_card function */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|div4
r_static
r_struct
id|capi_driver_interface
op_star
id|div4
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pciv4_procinfo
r_static
r_char
op_star
id|b1pciv4_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|cinfo-&gt;infobuf
comma
l_string|&quot;%s %s 0x%x %d 0x%lx r%d&quot;
comma
id|cinfo-&gt;cardname
(braket
l_int|0
)braket
ques
c_cond
id|cinfo-&gt;cardname
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
ques
c_cond
id|cinfo-&gt;version
(braket
id|VER_DRIVER
)braket
suffix:colon
l_string|&quot;-&quot;
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;port
suffix:colon
l_int|0x0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;irq
suffix:colon
l_int|0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;membase
suffix:colon
l_int|0
comma
id|cinfo-&gt;card
ques
c_cond
id|cinfo-&gt;card-&gt;revision
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|cinfo-&gt;infobuf
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pciv4_add_card
r_static
r_int
id|b1pciv4_add_card
c_func
(paren
r_struct
id|capi_driver
op_star
id|driver
comma
r_struct
id|capicardparams
op_star
id|p
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|avmcard
op_star
id|card
suffix:semicolon
id|avmctrl_info
op_star
id|cinfo
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|card
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmcard
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|memset
c_func
(paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
id|avmcard
)paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|card-&gt;lock
)paren
suffix:semicolon
id|card-&gt;dma
op_assign
id|avmcard_dma_alloc
c_func
(paren
id|driver-&gt;name
comma
id|dev
comma
l_int|2048
op_plus
l_int|128
comma
l_int|2048
op_plus
l_int|128
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;dma
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: dma alloc.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_goto
id|err_kfree
suffix:semicolon
)brace
id|cinfo
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmctrl_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_goto
id|err_dma_free
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cinfo
comma
l_int|0
comma
r_sizeof
(paren
id|avmctrl_info
)paren
)paren
suffix:semicolon
id|card-&gt;ctrlinfo
op_assign
id|cinfo
suffix:semicolon
id|cinfo-&gt;card
op_assign
id|card
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;b1pciv4-%x&quot;
comma
id|p-&gt;port
)paren
suffix:semicolon
id|card-&gt;port
op_assign
id|p-&gt;port
suffix:semicolon
id|card-&gt;irq
op_assign
id|p-&gt;irq
suffix:semicolon
id|card-&gt;membase
op_assign
id|p-&gt;membase
suffix:semicolon
id|card-&gt;cardtype
op_assign
id|avm_b1pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
comma
id|card-&gt;name
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ports 0x%03x-0x%03x in use.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;port
op_plus
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_kfree_ctrlinfo
suffix:semicolon
)brace
id|card-&gt;mbase
op_assign
id|ioremap_nocache
c_func
(paren
id|card-&gt;membase
comma
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;mbase
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: can&squot;t remap memory at 0x%lx&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;membase
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_release_region
suffix:semicolon
)brace
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|retval
op_assign
id|b1pciv4_detect
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_unmap
suffix:semicolon
)brace
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|b1_getrevision
c_func
(paren
id|card
)paren
suffix:semicolon
id|retval
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|b1dma_interrupt
comma
id|SA_SHIRQ
comma
id|card-&gt;name
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to get IRQ %d.&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_unmap
suffix:semicolon
)brace
id|cinfo-&gt;capi_ctrl
op_assign
id|div4
op_member_access_from_pointer
id|attach_ctr
c_func
(paren
id|driver
comma
id|card-&gt;name
comma
id|cinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cinfo-&gt;capi_ctrl
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: attach controller failed.&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_free_irq
suffix:semicolon
)brace
id|card-&gt;cardnr
op_assign
id|cinfo-&gt;capi_ctrl-&gt;cnr
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AVM B1 PCI V4 at i/o %#x, irq %d, mem %#lx, revision %d (dma)&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;membase
comma
id|card-&gt;revision
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|err_unmap
suffix:colon
id|iounmap
c_func
(paren
id|card-&gt;mbase
)paren
suffix:semicolon
id|err_release_region
suffix:colon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|err_kfree_ctrlinfo
suffix:colon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|err_dma_free
suffix:colon
id|avmcard_dma_free
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|err_kfree
suffix:colon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|err
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|b1pciv4_remove_ctr
r_static
r_void
id|b1pciv4_remove_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
op_assign
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
id|avmcard
op_star
id|card
op_assign
id|cinfo-&gt;card
suffix:semicolon
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|div4
op_member_access_from_pointer
id|detach_ctr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|card-&gt;mbase
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|AVMB1_PORTLEN
)paren
suffix:semicolon
id|ctrl-&gt;driverdata
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|card-&gt;ctrlinfo
)paren
suffix:semicolon
id|avmcard_dma_free
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|b1pciv4_driver
r_static
r_struct
id|capi_driver
id|b1pciv4_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;b1pciv4&quot;
comma
id|revision
suffix:colon
l_string|&quot;0.0&quot;
comma
id|load_firmware
suffix:colon
id|b1dma_load_firmware
comma
id|reset_ctr
suffix:colon
id|b1dma_reset_ctr
comma
id|remove_ctr
suffix:colon
id|b1pciv4_remove_ctr
comma
id|register_appl
suffix:colon
id|b1dma_register_appl
comma
id|release_appl
suffix:colon
id|b1dma_release_appl
comma
id|send_message
suffix:colon
id|b1dma_send_message
comma
id|procinfo
suffix:colon
id|b1pciv4_procinfo
comma
id|ctr_read_proc
suffix:colon
id|b1dmactl_read_proc
comma
id|driver_read_proc
suffix:colon
l_int|0
comma
multiline_comment|/* use standard driver_read_proc */
id|add_card
suffix:colon
l_int|0
comma
multiline_comment|/* no add_card function */
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_ISDN_DRV_AVMB1_B1PCIV4 */
DECL|function|b1pci_probe
r_static
r_int
id|__devinit
id|b1pci_probe
c_func
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
id|ent
)paren
(brace
r_struct
id|capi_driver
op_star
id|driver
op_assign
op_amp
id|b1pci_driver
suffix:semicolon
r_struct
id|capicardparams
id|param
suffix:semicolon
r_int
id|retval
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to enable AVM-B1&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|param.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|2
)paren
)paren
(brace
multiline_comment|/* B1 PCI V4 */
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
id|driver
op_assign
op_amp
id|b1pciv4_driver
suffix:semicolon
id|pci_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
id|param.membase
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|param.port
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: PCI BIOS reports AVM-B1 V4 at i/o %#x, irq %d, mem %#x&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
id|retval
op_assign
id|b1pciv4_add_card
c_func
(paren
id|driver
comma
op_amp
id|param
comma
id|dev
)paren
suffix:semicolon
macro_line|#else
id|retval
op_assign
id|b1pci_add_card
c_func
(paren
id|driver
comma
op_amp
id|param
comma
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no AVM-B1 V4 at i/o %#x, irq %d, mem %#x detected&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|param.membase
op_assign
l_int|0
suffix:semicolon
id|param.port
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: PCI BIOS reports AVM-B1 at i/o %#x, irq %d&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
)paren
suffix:semicolon
id|retval
op_assign
id|b1pci_add_card
c_func
(paren
id|driver
comma
op_amp
id|param
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no AVM-B1 at i/o %#x, irq %d detected&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|param.port
comma
id|param.irq
)paren
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|b1pci_pci_driver
r_static
r_struct
id|pci_driver
id|b1pci_pci_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;b1pci&quot;
comma
id|id_table
suffix:colon
id|b1pci_pci_tbl
comma
id|probe
suffix:colon
id|b1pci_probe
comma
)brace
suffix:semicolon
DECL|function|b1pci_init
r_static
r_int
id|__init
id|b1pci_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|capi_driver
op_star
id|driver
op_assign
op_amp
id|b1pci_driver
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
r_struct
id|capi_driver
op_star
id|driverv4
op_assign
op_amp
id|b1pciv4_driver
suffix:semicolon
macro_line|#endif
r_char
op_star
id|p
suffix:semicolon
r_int
id|ncards
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
(braket
l_int|1
)braket
)paren
(brace
id|strncpy
c_func
(paren
id|driver-&gt;revision
comma
id|p
op_plus
l_int|2
comma
r_sizeof
(paren
id|driver-&gt;revision
)paren
)paren
suffix:semicolon
id|driver-&gt;revision
(braket
r_sizeof
(paren
id|driver-&gt;revision
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|driver-&gt;revision
comma
l_char|&squot;$&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
OG
id|driver-&gt;revision
)paren
op_star
(paren
id|p
op_minus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
(braket
l_int|1
)braket
)paren
(brace
id|strncpy
c_func
(paren
id|driverv4-&gt;revision
comma
id|p
op_plus
l_int|2
comma
r_sizeof
(paren
id|driverv4-&gt;revision
)paren
)paren
suffix:semicolon
id|driverv4-&gt;revision
(braket
r_sizeof
(paren
id|driverv4-&gt;revision
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|driverv4-&gt;revision
comma
l_char|&squot;$&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
OG
id|driverv4-&gt;revision
)paren
op_star
(paren
id|p
op_minus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: revision %s&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|driver-&gt;revision
)paren
suffix:semicolon
id|di
op_assign
id|attach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|di
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to attach capi_driver&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: revision %s&bslash;n&quot;
comma
id|driverv4-&gt;name
comma
id|driverv4-&gt;revision
)paren
suffix:semicolon
id|div4
op_assign
id|attach_capi_driver
c_func
(paren
id|driverv4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|div4
)paren
(brace
id|detach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to attach capi_driver&bslash;n&quot;
comma
id|driverv4-&gt;name
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif
id|ncards
op_assign
id|pci_register_driver
c_func
(paren
op_amp
id|b1pci_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncards
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %d B1-PCI card(s) detected&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|ncards
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: NO B1-PCI card detected&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|b1pci_pci_driver
)paren
suffix:semicolon
id|detach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
id|detach_capi_driver
c_func
(paren
id|driverv4
)paren
suffix:semicolon
macro_line|#endif
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|b1pci_exit
r_static
r_void
id|__exit
id|b1pci_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|b1pci_pci_driver
)paren
suffix:semicolon
id|detach_capi_driver
c_func
(paren
op_amp
id|b1pci_driver
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1_B1PCIV4
id|detach_capi_driver
c_func
(paren
op_amp
id|b1pciv4_driver
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|b1pci_init
id|module_init
c_func
(paren
id|b1pci_init
)paren
suffix:semicolon
DECL|variable|b1pci_exit
id|module_exit
c_func
(paren
id|b1pci_exit
)paren
suffix:semicolon
eof
