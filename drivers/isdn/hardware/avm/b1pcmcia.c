multiline_comment|/* $Id: b1pcmcia.c,v 1.1.2.2 2004/01/16 21:09:27 keil Exp $&n; * &n; * Module for AVM B1/M1/M2 PCMCIA-card.&n; * &n; * Copyright 1999 by Carsten Paeth &lt;calle@calle.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/b1pcmcia.h&gt;
macro_line|#include &lt;linux/isdn/capicmd.h&gt;
macro_line|#include &lt;linux/isdn/capiutil.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#include &quot;avmcard.h&quot;
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.1.2.2 $&quot;
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CAPI4Linux: Driver for AVM PCMCIA cards&quot;
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
DECL|function|b1pcmcia_remove_ctr
r_static
r_void
id|b1pcmcia_remove_ctr
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
id|detach_capi_ctr
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
id|b1_free_card
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
r_static
id|LIST_HEAD
c_func
(paren
id|cards
)paren
suffix:semicolon
r_static
r_char
op_star
id|b1pcmcia_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
suffix:semicolon
DECL|function|b1pcmcia_add_card
r_static
r_int
id|b1pcmcia_add_card
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
comma
r_enum
id|avmcardtype
id|cardtype
)paren
(brace
id|avmctrl_info
op_star
id|cinfo
suffix:semicolon
id|avmcard
op_star
id|card
suffix:semicolon
r_char
op_star
id|cardname
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
l_string|&quot;b1pcmcia: no memory.&bslash;n&quot;
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
id|cinfo
op_assign
id|card-&gt;ctrlinfo
suffix:semicolon
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|avm_m1
suffix:colon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;m1-%x&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|avm_m2
suffix:colon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;m2-%x&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;b1pcmcia-%x&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|card-&gt;port
op_assign
id|port
suffix:semicolon
id|card-&gt;irq
op_assign
id|irq
suffix:semicolon
id|card-&gt;cardtype
op_assign
id|cardtype
suffix:semicolon
id|retval
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|b1_interrupt
comma
l_int|0
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
l_string|&quot;b1pcmcia: unable to get IRQ %d.&bslash;n&quot;
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
id|err_free
suffix:semicolon
)brace
id|b1_reset
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|b1_detect
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;cardtype
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;b1pcmcia: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_free_irq
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
id|cinfo-&gt;capi_ctrl.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|cinfo-&gt;capi_ctrl.driver_name
op_assign
l_string|&quot;b1pcmcia&quot;
suffix:semicolon
id|cinfo-&gt;capi_ctrl.driverdata
op_assign
id|cinfo
suffix:semicolon
id|cinfo-&gt;capi_ctrl.register_appl
op_assign
id|b1_register_appl
suffix:semicolon
id|cinfo-&gt;capi_ctrl.release_appl
op_assign
id|b1_release_appl
suffix:semicolon
id|cinfo-&gt;capi_ctrl.send_message
op_assign
id|b1_send_message
suffix:semicolon
id|cinfo-&gt;capi_ctrl.load_firmware
op_assign
id|b1_load_firmware
suffix:semicolon
id|cinfo-&gt;capi_ctrl.reset_ctr
op_assign
id|b1_reset_ctr
suffix:semicolon
id|cinfo-&gt;capi_ctrl.procinfo
op_assign
id|b1pcmcia_procinfo
suffix:semicolon
id|cinfo-&gt;capi_ctrl.ctr_read_proc
op_assign
id|b1ctl_read_proc
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
l_string|&quot;b1pcmcia: attach controller failed.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_free_irq
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|avm_m1
suffix:colon
id|cardname
op_assign
l_string|&quot;M1&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|avm_m2
suffix:colon
id|cardname
op_assign
l_string|&quot;M2&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cardname
op_assign
l_string|&quot;B1 PCMCIA&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;b1pcmcia: AVM %s at i/o %#x, irq %d, revision %d&bslash;n&quot;
comma
id|cardname
comma
id|card-&gt;port
comma
id|card-&gt;irq
comma
id|card-&gt;revision
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|card-&gt;list
comma
op_amp
id|cards
)paren
suffix:semicolon
r_return
id|cinfo-&gt;capi_ctrl.cnr
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
DECL|function|b1pcmcia_procinfo
r_static
r_char
op_star
id|b1pcmcia_procinfo
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
DECL|function|b1pcmcia_addcard_b1
r_int
id|b1pcmcia_addcard_b1
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_return
id|b1pcmcia_add_card
c_func
(paren
id|port
comma
id|irq
comma
id|avm_b1pcmcia
)paren
suffix:semicolon
)brace
DECL|function|b1pcmcia_addcard_m1
r_int
id|b1pcmcia_addcard_m1
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_return
id|b1pcmcia_add_card
c_func
(paren
id|port
comma
id|irq
comma
id|avm_m1
)paren
suffix:semicolon
)brace
DECL|function|b1pcmcia_addcard_m2
r_int
id|b1pcmcia_addcard_m2
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_return
id|b1pcmcia_add_card
c_func
(paren
id|port
comma
id|irq
comma
id|avm_m2
)paren
suffix:semicolon
)brace
DECL|function|b1pcmcia_delcard
r_int
id|b1pcmcia_delcard
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|avmcard
op_star
id|card
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|cards
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|avmcard
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;port
op_eq
id|port
op_logical_and
id|card-&gt;irq
op_eq
id|irq
)paren
(brace
id|b1pcmcia_remove_ctr
c_func
(paren
op_amp
id|card-&gt;ctrlinfo
(braket
l_int|0
)braket
dot
id|capi_ctrl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
DECL|variable|b1pcmcia_addcard_b1
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_addcard_b1
)paren
suffix:semicolon
DECL|variable|b1pcmcia_addcard_m1
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_addcard_m1
)paren
suffix:semicolon
DECL|variable|b1pcmcia_addcard_m2
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_addcard_m2
)paren
suffix:semicolon
DECL|variable|b1pcmcia_delcard
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_delcard
)paren
suffix:semicolon
DECL|variable|capi_driver_b1pcmcia
r_static
r_struct
id|capi_driver
id|capi_driver_b1pcmcia
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;b1pcmcia&quot;
comma
dot
id|revision
op_assign
l_string|&quot;1.0&quot;
comma
)brace
suffix:semicolon
DECL|function|b1pcmcia_init
r_static
r_int
id|__init
id|b1pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_char
id|rev
(braket
l_int|32
)braket
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
id|strlcpy
c_func
(paren
id|rev
comma
id|p
op_plus
l_int|2
comma
l_int|32
)paren
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
id|rev
comma
l_char|&squot;$&squot;
)paren
)paren
op_ne
l_int|0
op_logical_and
id|p
OG
id|rev
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
r_else
id|strcpy
c_func
(paren
id|rev
comma
l_string|&quot;1.0&quot;
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|capi_driver_b1pcmcia.revision
comma
id|rev
comma
l_int|32
)paren
suffix:semicolon
id|register_capi_driver
c_func
(paren
op_amp
id|capi_driver_b1pcmcia
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;b1pci: revision %s&bslash;n&quot;
comma
id|rev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|b1pcmcia_exit
r_static
r_void
id|__exit
id|b1pcmcia_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_capi_driver
c_func
(paren
op_amp
id|capi_driver_b1pcmcia
)paren
suffix:semicolon
)brace
DECL|variable|b1pcmcia_init
id|module_init
c_func
(paren
id|b1pcmcia_init
)paren
suffix:semicolon
DECL|variable|b1pcmcia_exit
id|module_exit
c_func
(paren
id|b1pcmcia_exit
)paren
suffix:semicolon
eof
