macro_line|#ifndef _I8042_IO_H
DECL|macro|_I8042_IO_H
mdefine_line|#define _I8042_IO_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by &n; * the Free Software Foundation.&n; */
multiline_comment|/*&n; * Names.&n; */
DECL|macro|I8042_KBD_PHYS_DESC
mdefine_line|#define I8042_KBD_PHYS_DESC &quot;isa0060/serio0&quot;
DECL|macro|I8042_AUX_PHYS_DESC
mdefine_line|#define I8042_AUX_PHYS_DESC &quot;isa0060/serio1&quot;
DECL|macro|I8042_MUX_PHYS_DESC
mdefine_line|#define I8042_MUX_PHYS_DESC &quot;isa0060/serio%d&quot;
multiline_comment|/*&n; * IRQs.&n; */
macro_line|#ifdef __alpha__
DECL|macro|I8042_KBD_IRQ
macro_line|# define I8042_KBD_IRQ&t;1
DECL|macro|I8042_AUX_IRQ
macro_line|# define I8042_AUX_IRQ&t;(RTC_PORT(0) == 0x170 ? 9 : 12)&t;/* Jensen is special */
macro_line|#elif defined(__ia64__)
DECL|macro|I8042_KBD_IRQ
macro_line|# define I8042_KBD_IRQ isa_irq_to_vector(1)
DECL|macro|I8042_AUX_IRQ
macro_line|# define I8042_AUX_IRQ isa_irq_to_vector(12)
macro_line|#else
DECL|macro|I8042_KBD_IRQ
macro_line|# define I8042_KBD_IRQ&t;1
DECL|macro|I8042_AUX_IRQ
macro_line|# define I8042_AUX_IRQ&t;12
macro_line|#endif
multiline_comment|/*&n; * Register numbers.&n; */
DECL|macro|I8042_COMMAND_REG
mdefine_line|#define I8042_COMMAND_REG&t;0x64&t;
DECL|macro|I8042_STATUS_REG
mdefine_line|#define I8042_STATUS_REG&t;0x64&t;
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG&t;&t;0x60
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
id|inb
c_func
(paren
id|I8042_DATA_REG
)paren
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
id|inb
c_func
(paren
id|I8042_STATUS_REG
)paren
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
id|outb
c_func
(paren
id|val
comma
id|I8042_DATA_REG
)paren
suffix:semicolon
r_return
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
id|outb
c_func
(paren
id|val
comma
id|I8042_COMMAND_REG
)paren
suffix:semicolon
r_return
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
multiline_comment|/*&n; * On ix86 platforms touching the i8042 data register region can do really&n; * bad things. Because of this the region is always reserved on ix86 boxes.&n; */
macro_line|#if !defined(__i386__) &amp;&amp; !defined(__sh__) &amp;&amp; !defined(__alpha__) &amp;&amp; !defined(__x86_64__)
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|I8042_DATA_REG
comma
l_int|16
comma
l_string|&quot;i8042&quot;
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#if !defined(__i386__) &amp;&amp; !defined(__x86_64__)
id|i8042_reset
op_assign
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
macro_line|#if !defined(__i386__) &amp;&amp; !defined(__sh__) &amp;&amp; !defined(__alpha__) &amp;&amp; !defined(__x86_64__)
id|release_region
c_func
(paren
id|I8042_DATA_REG
comma
l_int|16
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* _I8042_IO_H */
eof
