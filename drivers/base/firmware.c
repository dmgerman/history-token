multiline_comment|/*&n; * firmware.c - firmware subsystem hoohaw.&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; *&n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
r_static
id|decl_subsys
c_func
(paren
id|firmware
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|firmware_register
r_int
id|firmware_register
c_func
(paren
r_struct
id|subsystem
op_star
id|s
)paren
(brace
id|kset_set_kset_s
c_func
(paren
id|s
comma
id|firmware_subsys
)paren
suffix:semicolon
r_return
id|subsystem_register
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
DECL|function|firmware_unregister
r_void
id|firmware_unregister
c_func
(paren
r_struct
id|subsystem
op_star
id|s
)paren
(brace
id|subsystem_unregister
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
DECL|function|firmware_init
r_int
id|__init
id|firmware_init
c_func
(paren
r_void
)paren
(brace
r_return
id|subsystem_register
c_func
(paren
op_amp
id|firmware_subsys
)paren
suffix:semicolon
)brace
DECL|variable|firmware_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|firmware_register
)paren
suffix:semicolon
DECL|variable|firmware_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|firmware_unregister
)paren
suffix:semicolon
eof
