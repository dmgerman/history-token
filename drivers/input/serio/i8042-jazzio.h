macro_line|#ifndef _I8042_JAZZ_H
DECL|macro|_I8042_JAZZ_H
mdefine_line|#define _I8042_JAZZ_H
macro_line|#include &lt;asm/jazz.h&gt;
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
multiline_comment|/*&n; * Names.&n; */
DECL|macro|I8042_KBD_PHYS_DESC
mdefine_line|#define I8042_KBD_PHYS_DESC &quot;R4030/serio0&quot;
DECL|macro|I8042_AUX_PHYS_DESC
mdefine_line|#define I8042_AUX_PHYS_DESC &quot;R4030/serio1&quot;
DECL|macro|I8042_MUX_PHYS_DESC
mdefine_line|#define I8042_MUX_PHYS_DESC &quot;R4030/serio%d&quot;
multiline_comment|/*&n; * IRQs.&n; */
DECL|macro|I8042_KBD_IRQ
mdefine_line|#define I8042_KBD_IRQ JAZZ_KEYBOARD_IRQ
DECL|macro|I8042_AUX_IRQ
mdefine_line|#define I8042_AUX_IRQ JAZZ_MOUSE_IRQ
DECL|macro|I8042_COMMAND_REG
mdefine_line|#define I8042_COMMAND_REG&t;((unsigned long)&amp;jazz_kh-&gt;command)
DECL|macro|I8042_STATUS_REG
mdefine_line|#define I8042_STATUS_REG&t;((unsigned long)&amp;jazz_kh-&gt;command)
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG&t;&t;((unsigned long)&amp;jazz_kh-&gt;data)
DECL|function|i8042_read_data
r_static
r_inline
r_int
id|i8042_read_data
c_func
(paren
r_void
)paren
(brace
r_return
id|jazz_kh-&gt;data
suffix:semicolon
)brace
DECL|function|i8042_read_status
r_static
r_inline
r_int
id|i8042_read_status
c_func
(paren
r_void
)paren
(brace
r_return
id|jazz_kh-&gt;command
suffix:semicolon
)brace
DECL|function|i8042_write_data
r_static
r_inline
r_void
id|i8042_write_data
c_func
(paren
r_int
id|val
)paren
(brace
id|jazz_kh-&gt;data
op_assign
id|val
suffix:semicolon
)brace
DECL|function|i8042_write_command
r_static
r_inline
r_void
id|i8042_write_command
c_func
(paren
r_int
id|val
)paren
(brace
id|jazz_kh-&gt;command
op_assign
id|val
suffix:semicolon
)brace
DECL|function|i8042_platform_init
r_static
r_inline
r_int
id|i8042_platform_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
multiline_comment|/* XXX JAZZ_KEYBOARD_ADDRESS is a virtual address */
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|JAZZ_KEYBOARD_ADDRESS
comma
l_int|2
comma
l_string|&quot;i8042&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8042_platform_exit
r_static
r_inline
r_void
id|i8042_platform_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
id|release_mem_region
c_func
(paren
id|JAZZ_KEYBOARD_ADDRESS
comma
l_int|2
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* _I8042_JAZZ_H */
eof
