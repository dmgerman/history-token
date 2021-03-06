multiline_comment|/*********************************************************************&n; *&n; *&t;sir_core.c:&t;module core for irda-sir abstraction layer&n; *&n; *&t;Copyright (c) 2002 Martin Diehl&n; * &n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
multiline_comment|/***************************************************************************/
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Martin Diehl &lt;info@mdiehl.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IrDA SIR core&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/***************************************************************************/
DECL|variable|irda_register_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irda_register_dongle
)paren
suffix:semicolon
DECL|variable|irda_unregister_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|irda_unregister_dongle
)paren
suffix:semicolon
DECL|variable|sirdev_get_instance
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_get_instance
)paren
suffix:semicolon
DECL|variable|sirdev_put_instance
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_put_instance
)paren
suffix:semicolon
DECL|variable|sirdev_set_dongle
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_set_dongle
)paren
suffix:semicolon
DECL|variable|sirdev_write_complete
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_write_complete
)paren
suffix:semicolon
DECL|variable|sirdev_receive
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_receive
)paren
suffix:semicolon
DECL|variable|sirdev_raw_write
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_raw_write
)paren
suffix:semicolon
DECL|variable|sirdev_raw_read
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_raw_read
)paren
suffix:semicolon
DECL|variable|sirdev_set_dtr_rts
id|EXPORT_SYMBOL
c_func
(paren
id|sirdev_set_dtr_rts
)paren
suffix:semicolon
DECL|function|sir_core_init
r_static
r_int
id|__init
id|sir_core_init
c_func
(paren
r_void
)paren
(brace
r_return
id|irda_thread_create
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sir_core_exit
r_static
r_void
id|__exit
id|sir_core_exit
c_func
(paren
r_void
)paren
(brace
id|irda_thread_join
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sir_core_init
id|module_init
c_func
(paren
id|sir_core_init
)paren
suffix:semicolon
DECL|variable|sir_core_exit
id|module_exit
c_func
(paren
id|sir_core_exit
)paren
suffix:semicolon
eof
