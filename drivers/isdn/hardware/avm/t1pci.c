multiline_comment|/* $Id: t1pci.c,v 1.1.4.1.2.1 2001/12/21 15:00:17 kai Exp $&n; * &n; * Module for AVM T1 PCI-card.&n; * &n; * Copyright 1999 by Carsten Paeth &lt;calle@calle.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/isdn/capicmd.h&gt;
macro_line|#include &lt;linux/isdn/capiutil.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#include &quot;avmcard.h&quot;
DECL|macro|CONFIG_T1PCI_DEBUG
macro_line|#undef CONFIG_T1PCI_DEBUG
DECL|macro|CONFIG_T1PCI_POLLDEBUG
macro_line|#undef CONFIG_T1PCI_POLLDEBUG
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|t1pci_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AVM
comma
id|PCI_DEVICE_ID_AVM_T1
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
id|t1pci_pci_tbl
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CAPI4Linux: Driver for AVM T1 PCI card&quot;
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
r_static
r_char
op_star
id|t1pci_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
suffix:semicolon
DECL|function|t1pci_add_card
r_static
r_int
id|t1pci_add_card
c_func
(paren
r_struct
id|capicardparams
op_star
id|p
comma
r_struct
id|pci_dev
op_star
id|pdev
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
id|card
op_assign
id|b1_alloc_card
c_func
(paren
l_int|1
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
l_string|&quot;t1pci: no memory.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|card-&gt;dma
op_assign
id|avmcard_dma_alloc
c_func
(paren
l_string|&quot;t1pci&quot;
comma
id|pdev
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
l_string|&quot;t1pci: no memory.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_free
suffix:semicolon
)brace
id|cinfo
op_assign
id|card-&gt;ctrlinfo
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;t1pci-%x&quot;
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
id|avm_t1pci
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
l_string|&quot;t1pci: ports 0x%03x-0x%03x in use.&bslash;n&quot;
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
id|err_free_dma
suffix:semicolon
)brace
id|card-&gt;mbase
op_assign
id|ioremap
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
l_string|&quot;t1pci: can&squot;t remap memory at 0x%lx&bslash;n&quot;
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
id|t1pci_detect
c_func
(paren
id|card
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
r_if
c_cond
(paren
id|retval
OL
l_int|6
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;t1pci: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;t1pci: card at 0x%x, but cable not connected or T1 has no power (%d)&bslash;n&quot;
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
l_string|&quot;t1pci: unable to get IRQ %d.&bslash;n&quot;
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
id|cinfo-&gt;capi_ctrl.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|cinfo-&gt;capi_ctrl.driver_name
op_assign
l_string|&quot;t1pci&quot;
suffix:semicolon
id|cinfo-&gt;capi_ctrl.driverdata
op_assign
id|cinfo
suffix:semicolon
id|cinfo-&gt;capi_ctrl.register_appl
op_assign
id|b1dma_register_appl
suffix:semicolon
id|cinfo-&gt;capi_ctrl.release_appl
op_assign
id|b1dma_release_appl
suffix:semicolon
id|cinfo-&gt;capi_ctrl.send_message
op_assign
id|b1dma_send_message
suffix:semicolon
id|cinfo-&gt;capi_ctrl.load_firmware
op_assign
id|b1dma_load_firmware
suffix:semicolon
id|cinfo-&gt;capi_ctrl.reset_ctr
op_assign
id|b1dma_reset_ctr
suffix:semicolon
id|cinfo-&gt;capi_ctrl.procinfo
op_assign
id|t1pci_procinfo
suffix:semicolon
id|cinfo-&gt;capi_ctrl.ctr_read_proc
op_assign
id|b1dmactl_read_proc
suffix:semicolon
id|strcpy
c_func
(paren
id|cinfo-&gt;capi_ctrl.name
comma
id|card-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
id|attach_capi_ctr
c_func
(paren
op_amp
id|cinfo-&gt;capi_ctrl
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
l_string|&quot;t1pci: attach controller failed.&bslash;n&quot;
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
id|cinfo-&gt;capi_ctrl.cnr
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;t1pci: AVM T1 PCI at i/o %#x, irq %d, mem %#lx&bslash;n&quot;
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;membase
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|card
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
id|err_free_dma
suffix:colon
id|avmcard_dma_free
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|err_free
suffix:colon
id|b1_free_card
c_func
(paren
id|card
)paren
suffix:semicolon
id|err
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1pci_remove
r_static
r_void
id|t1pci_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|avmcard
op_star
id|card
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|avmctrl_info
op_star
id|cinfo
op_assign
id|card-&gt;ctrlinfo
suffix:semicolon
id|b1dma_reset
c_func
(paren
id|card
)paren
suffix:semicolon
id|detach_capi_ctr
c_func
(paren
op_amp
id|cinfo-&gt;capi_ctrl
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
id|avmcard_dma_free
c_func
(paren
id|card-&gt;dma
)paren
suffix:semicolon
id|b1_free_card
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1pci_procinfo
r_static
r_char
op_star
id|t1pci_procinfo
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
l_string|&quot;%s %s 0x%x %d 0x%lx&quot;
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
)paren
suffix:semicolon
r_return
id|cinfo-&gt;infobuf
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|t1pci_probe
r_static
r_int
id|__devinit
id|t1pci_probe
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
l_string|&quot;t1pci: failed to enable AVM-T1-PCI&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pci_set_master
c_func
(paren
id|dev
)paren
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
id|param.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;t1pci: PCI BIOS reports AVM-T1-PCI at i/o %#x, irq %d, mem %#x&bslash;n&quot;
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
)paren
suffix:semicolon
id|retval
op_assign
id|t1pci_add_card
c_func
(paren
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
l_string|&quot;t1pci: no AVM-T1-PCI at i/o %#x, irq %d detected, mem %#x&bslash;n&quot;
comma
id|param.port
comma
id|param.irq
comma
id|param.membase
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|t1pci_pci_driver
r_static
r_struct
id|pci_driver
id|t1pci_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;t1pci&quot;
comma
dot
id|id_table
op_assign
id|t1pci_pci_tbl
comma
dot
id|probe
op_assign
id|t1pci_probe
comma
dot
id|remove
op_assign
id|t1pci_remove
comma
)brace
suffix:semicolon
DECL|function|t1pci_init
r_static
r_int
id|__init
id|t1pci_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|t1pci_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|t1pci_exit
r_static
r_void
id|__exit
id|t1pci_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|t1pci_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|t1pci_init
id|module_init
c_func
(paren
id|t1pci_init
)paren
suffix:semicolon
DECL|variable|t1pci_exit
id|module_exit
c_func
(paren
id|t1pci_exit
)paren
suffix:semicolon
eof
