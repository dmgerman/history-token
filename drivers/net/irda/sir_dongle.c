multiline_comment|/*********************************************************************&n; *&n; *&t;sir_dongle.c:&t;manager for serial dongle protocol drivers&n; *&n; *&t;Copyright (c) 2002 Martin Diehl&n; *&n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
multiline_comment|/**************************************************************************&n; *&n; * dongle registration and attachment&n; *&n; */
r_static
id|LIST_HEAD
c_func
(paren
id|dongle_list
)paren
suffix:semicolon
multiline_comment|/* list of registered dongle drivers */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|dongle_list_lock
)paren
suffix:semicolon
multiline_comment|/* protects the list */
DECL|function|irda_register_dongle
r_int
id|irda_register_dongle
c_func
(paren
r_struct
id|dongle_driver
op_star
r_new
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|dongle_driver
op_star
id|drv
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s : registering dongle &bslash;&quot;%s&bslash;&quot; (%d).&bslash;n&quot;
comma
id|__FUNCTION__
comma
r_new
op_member_access_from_pointer
id|driver_name
comma
r_new
op_member_access_from_pointer
id|type
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|dongle_list
)paren
(brace
id|drv
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|dongle_driver
comma
id|dongle_list
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|type
op_eq
id|drv-&gt;type
)paren
(brace
id|up
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
)brace
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|dongle_list
comma
op_amp
id|dongle_list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_unregister_dongle
r_int
id|irda_unregister_dongle
c_func
(paren
r_struct
id|dongle_driver
op_star
id|drv
)paren
(brace
id|down
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|drv-&gt;dongle_list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sirdev_get_dongle
r_int
id|sirdev_get_dongle
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
id|IRDA_DONGLE
id|type
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_const
r_struct
id|dongle_driver
op_star
id|drv
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
id|request_module
c_func
(paren
l_string|&quot;irda-dongle-%d&quot;
comma
id|type
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dev-&gt;dongle_drv
op_ne
l_int|NULL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* serialize access to the list of registered dongles */
id|down
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|dongle_list
)paren
(brace
id|drv
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|dongle_driver
comma
id|dongle_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;type
op_eq
id|type
)paren
r_break
suffix:semicolon
r_else
id|drv
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|drv
)paren
(brace
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/* no such dongle */
)brace
multiline_comment|/* handling of SMP races with dongle module removal - three cases:&n;&t; * 1) dongle driver was already unregistered - then we haven&squot;t found the&n;&t; *&t;requested dongle above and are already out here&n;&t; * 2) the module is already marked deleted but the driver is still&n;&t; *&t;registered - then the try_module_get() below will fail&n;&t; * 3) the try_module_get() below succeeds before the module is marked&n;&t; *&t;deleted - then sys_delete_module() fails and prevents the removal&n;&t; *&t;because the module is in use.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|drv-&gt;owner
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ESTALE
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/* rmmod already pending */
)brace
id|dev-&gt;dongle_drv
op_assign
id|drv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv-&gt;open
op_logical_or
(paren
id|err
op_assign
id|drv
op_member_access_from_pointer
id|open
c_func
(paren
id|dev
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|out_reject
suffix:semicolon
multiline_comment|/* failed to open driver */
id|up
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_reject
suffix:colon
id|dev-&gt;dongle_drv
op_assign
l_int|NULL
suffix:semicolon
id|module_put
c_func
(paren
id|drv-&gt;owner
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|dongle_list_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sirdev_put_dongle
r_int
id|sirdev_put_dongle
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_const
r_struct
id|dongle_driver
op_star
id|drv
op_assign
id|dev-&gt;dongle_drv
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;close
)paren
id|drv
op_member_access_from_pointer
id|close
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* close this dongle instance */
id|dev-&gt;dongle_drv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* unlink the dongle driver */
id|module_put
c_func
(paren
id|drv-&gt;owner
)paren
suffix:semicolon
multiline_comment|/* decrement driver&squot;s module refcount */
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
