multiline_comment|/* $Id: capimain.c,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $&n; *&n; * ISDN interface module for Eicon active cards DIVA.&n; * CAPI Interface&n; * &n; * Copyright 2000-2002 by Armin Schindler (mac@melware.de) &n; * Copyright 2000-2002 Cytronics &amp; Melware (info@melware.de)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;os_capi.h&quot;
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;capi20.h&quot;
macro_line|#include &quot;divacapi.h&quot;
macro_line|#include &quot;cp_vers.h&quot;
macro_line|#include &quot;capifunc.h&quot;
DECL|variable|main_revision
r_static
r_char
op_star
id|main_revision
op_assign
l_string|&quot;$Revision: 1.1.2.11 $&quot;
suffix:semicolon
DECL|variable|DRIVERNAME
r_static
r_char
op_star
id|DRIVERNAME
op_assign
l_string|&quot;Eicon DIVA - CAPI Interface driver (http://www.melware.net)&quot;
suffix:semicolon
DECL|variable|DRIVERLNAME
r_static
r_char
op_star
id|DRIVERLNAME
op_assign
l_string|&quot;divacapi&quot;
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CAPI driver for Eicon DIVA cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Cytronics &amp; Melware, Eicon Networks&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;CAPI and DIVA card drivers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * get revision number from revision string&n; */
DECL|function|getrev
r_static
r_char
op_star
id|getrev
c_func
(paren
r_const
r_char
op_star
id|revision
)paren
(brace
r_char
op_star
id|rev
suffix:semicolon
r_char
op_star
id|p
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
)paren
(brace
id|rev
op_assign
id|p
op_plus
l_int|2
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|rev
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|rev
op_assign
l_string|&quot;1.0&quot;
suffix:semicolon
r_return
id|rev
suffix:semicolon
)brace
multiline_comment|/*&n; * sleep for some milliseconds&n; */
DECL|function|diva_os_sleep
r_void
id|diva_os_sleep
c_func
(paren
id|dword
id|mSec
)paren
(brace
r_int
r_int
id|timeout
op_assign
id|HZ
op_star
id|mSec
op_div
l_int|1000
op_plus
l_int|1
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * wait for some milliseconds&n; */
DECL|function|diva_os_wait
r_void
id|diva_os_wait
c_func
(paren
id|dword
id|mSec
)paren
(brace
id|mdelay
c_func
(paren
id|mSec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * alloc memory&n; */
DECL|function|diva_os_malloc
r_void
op_star
id|diva_os_malloc
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|ret
op_assign
(paren
r_void
op_star
)paren
id|vmalloc
c_func
(paren
(paren
r_int
r_int
)paren
id|size
)paren
suffix:semicolon
)brace
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * free memory&n; */
DECL|function|diva_os_free
r_void
id|diva_os_free
c_func
(paren
r_int
r_int
id|unused
comma
r_void
op_star
id|ptr
)paren
(brace
r_if
c_cond
(paren
id|ptr
)paren
(brace
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * alloc a message buffer&n; */
DECL|function|diva_os_alloc_message_buffer
id|diva_os_message_buffer_s
op_star
id|diva_os_alloc_message_buffer
c_func
(paren
r_int
r_int
id|size
comma
r_void
op_star
op_star
id|data_buf
)paren
(brace
id|diva_os_message_buffer_s
op_star
id|dmb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmb
)paren
(brace
op_star
id|data_buf
op_assign
id|skb_put
c_func
(paren
id|dmb
comma
id|size
)paren
suffix:semicolon
)brace
r_return
(paren
id|dmb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * free a message buffer&n; */
DECL|function|diva_os_free_message_buffer
r_void
id|diva_os_free_message_buffer
c_func
(paren
id|diva_os_message_buffer_s
op_star
id|dmb
)paren
(brace
id|kfree_skb
c_func
(paren
id|dmb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * proc function for controller info&n; */
DECL|function|diva_ctl_read_proc
r_static
r_int
id|diva_ctl_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|diva_card
op_star
id|card
op_assign
(paren
id|diva_card
op_star
)paren
id|ctrl-&gt;driverdata
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|ctrl-&gt;name
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Serial No. : %s&bslash;n&quot;
comma
id|ctrl-&gt;serial
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Id         : %d&bslash;n&quot;
comma
id|card-&gt;Id
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Channels   : %d&bslash;n&quot;
comma
id|card-&gt;d.channels
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
op_ge
id|len
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|off
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set additional os settings in capi_ctr struct&n; */
DECL|function|diva_os_set_controller_struct
r_void
id|diva_os_set_controller_struct
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|ctrl-&gt;driver_name
op_assign
id|DRIVERLNAME
suffix:semicolon
id|ctrl-&gt;load_firmware
op_assign
l_int|0
suffix:semicolon
id|ctrl-&gt;reset_ctr
op_assign
l_int|0
suffix:semicolon
id|ctrl-&gt;ctr_read_proc
op_assign
id|diva_ctl_read_proc
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|ctrl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * module init&n; */
DECL|function|divacapi_init
r_static
r_int
id|DIVA_INIT_FUNCTION
id|divacapi_init
c_func
(paren
r_void
)paren
(brace
r_char
id|tmprev
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|sprintf
c_func
(paren
id|DRIVERRELEASE
comma
l_string|&quot;%d.%d%s&quot;
comma
id|DRRELMAJOR
comma
id|DRRELMINOR
comma
id|DRRELEXTRA
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|DRIVERNAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Rel:%s  Rev:&quot;
comma
id|DRIVERLNAME
comma
id|DRIVERRELEASE
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tmprev
comma
id|main_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  Build: %s(%s)&bslash;n&quot;
comma
id|getrev
c_func
(paren
id|tmprev
)paren
comma
id|diva_capi_common_code_build
comma
id|DIVA_BUILD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|init_capifunc
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed init capi_driver.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * module exit&n; */
DECL|function|divacapi_exit
r_static
r_void
id|DIVA_EXIT_FUNCTION
id|divacapi_exit
c_func
(paren
r_void
)paren
(brace
id|finit_capifunc
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: module unloaded.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
)brace
DECL|variable|divacapi_init
id|module_init
c_func
(paren
id|divacapi_init
)paren
suffix:semicolon
DECL|variable|divacapi_exit
id|module_exit
c_func
(paren
id|divacapi_exit
)paren
suffix:semicolon
eof
