multiline_comment|/* $Id: b1pcmcia.c,v 1.12.6.5 2001/09/23 22:24:33 kai Exp $&n; * &n; * Module for AVM B1/M1/M2 PCMCIA-card.&n; * &n; * Copyright 1999 by Carsten Paeth &lt;calle@calle.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
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
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.12.6.5 $&quot;
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
DECL|variable|di
r_static
r_struct
id|capi_driver_interface
op_star
id|di
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
id|b1_free_card
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pcmcia_add_card
r_static
r_int
id|b1pcmcia_add_card
c_func
(paren
r_struct
id|capi_driver
op_star
id|driver
comma
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
id|MOD_INC_USE_COUNT
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
l_string|&quot;%s: no memory.&bslash;n&quot;
comma
id|driver-&gt;name
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
l_string|&quot;%s: AVM %s at i/o %#x, irq %d, revision %d&bslash;n&quot;
comma
id|driver-&gt;name
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
r_return
id|cinfo-&gt;capi_ctrl-&gt;cnr
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
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
DECL|variable|b1pcmcia_driver
r_static
r_struct
id|capi_driver
id|b1pcmcia_driver
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;b1pcmcia&quot;
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
id|b1pcmcia_remove_ctr
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
id|b1pcmcia_procinfo
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
)brace
suffix:semicolon
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
op_amp
id|b1pcmcia_driver
comma
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
op_amp
id|b1pcmcia_driver
comma
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
op_amp
id|b1pcmcia_driver
comma
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
r_struct
id|capi_ctr
op_star
id|ctrl
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
id|b1pcmcia_driver.contr_head
)paren
(brace
id|ctrl
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|capi_ctr
comma
id|driver_list
)paren
suffix:semicolon
id|card
op_assign
(paren
(paren
id|avmctrl_info
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
)paren
op_member_access_from_pointer
id|card
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
id|ctrl
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
multiline_comment|/* ------------------------------------------------------------- */
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
r_struct
id|capi_driver
op_star
id|driver
op_assign
op_amp
id|b1pcmcia_driver
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
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
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
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
id|detach_capi_driver
c_func
(paren
op_amp
id|b1pcmcia_driver
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
