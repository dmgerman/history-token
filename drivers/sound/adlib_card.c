multiline_comment|/*&n; * sound/adlib_card.c&n; *&n; * Detection routine for the AdLib card.&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;opl3.h&quot;
DECL|function|attach_adlib_card
r_static
r_void
id|__init
id|attach_adlib_card
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|hw_config-&gt;slots
(braket
l_int|0
)braket
op_assign
id|opl3_init
c_func
(paren
id|hw_config-&gt;io_base
comma
id|hw_config-&gt;osp
comma
id|THIS_MODULE
)paren
suffix:semicolon
)brace
DECL|function|probe_adlib
r_static
r_int
id|__init
id|probe_adlib
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_return
id|opl3_detect
c_func
(paren
id|hw_config-&gt;io_base
comma
id|hw_config-&gt;osp
)paren
suffix:semicolon
)brace
DECL|variable|cfg
r_static
r_struct
id|address_info
id|cfg
suffix:semicolon
DECL|variable|io
r_static
r_int
id|__initdata
id|io
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|init_adlib
r_static
r_int
id|__init
id|init_adlib
c_func
(paren
r_void
)paren
(brace
id|cfg.io_base
op_assign
id|io
suffix:semicolon
r_if
c_cond
(paren
id|cfg.io_base
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;adlib: must specify I/O address.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|probe_adlib
c_func
(paren
op_amp
id|cfg
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|attach_adlib_card
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_adlib
r_static
r_void
id|__exit
id|cleanup_adlib
c_func
(paren
r_void
)paren
(brace
id|sound_unload_synthdev
c_func
(paren
id|cfg.slots
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|variable|init_adlib
id|module_init
c_func
(paren
id|init_adlib
)paren
suffix:semicolon
DECL|variable|cleanup_adlib
id|module_exit
c_func
(paren
id|cleanup_adlib
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|setup_adlib
r_static
r_int
id|__init
id|setup_adlib
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* io */
r_int
id|ints
(braket
l_int|2
)braket
suffix:semicolon
id|str
op_assign
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
id|io
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;adlib=&quot;
comma
id|setup_adlib
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
