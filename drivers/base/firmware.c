multiline_comment|/*&n; * firmware.c - firmware subsystem hoohaw.&n; */
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
r_static
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
DECL|variable|firmware_init
id|core_initcall
c_func
(paren
id|firmware_init
)paren
suffix:semicolon
DECL|variable|firmware_register
id|EXPORT_SYMBOL
c_func
(paren
id|firmware_register
)paren
suffix:semicolon
DECL|variable|firmware_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|firmware_unregister
)paren
suffix:semicolon
eof
