macro_line|#ifndef _I8042_SPARCIO_H
DECL|macro|_I8042_SPARCIO_H
mdefine_line|#define _I8042_SPARCIO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#endif
DECL|variable|i8042_kbd_irq
r_static
r_int
id|i8042_kbd_irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|i8042_aux_irq
r_static
r_int
id|i8042_aux_irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|I8042_KBD_IRQ
mdefine_line|#define I8042_KBD_IRQ i8042_kbd_irq
DECL|macro|I8042_AUX_IRQ
mdefine_line|#define I8042_AUX_IRQ i8042_aux_irq
DECL|macro|I8042_KBD_PHYS_DESC
mdefine_line|#define I8042_KBD_PHYS_DESC &quot;sparcps2/serio0&quot;
DECL|macro|I8042_AUX_PHYS_DESC
mdefine_line|#define I8042_AUX_PHYS_DESC &quot;sparcps2/serio1&quot;
DECL|macro|I8042_MUX_PHYS_DESC
mdefine_line|#define I8042_MUX_PHYS_DESC &quot;sparcps2/serio%d&quot;
DECL|variable|kbd_iobase
r_static
r_void
id|__iomem
op_star
id|kbd_iobase
suffix:semicolon
DECL|macro|I8042_COMMAND_REG
mdefine_line|#define I8042_COMMAND_REG&t;(kbd_iobase + 0x64UL)
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG&t;&t;(kbd_iobase + 0x60UL)
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
id|readb
c_func
(paren
id|kbd_iobase
op_plus
l_int|0x60UL
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
id|readb
c_func
(paren
id|kbd_iobase
op_plus
l_int|0x64UL
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
id|writeb
c_func
(paren
id|val
comma
id|kbd_iobase
op_plus
l_int|0x60UL
)paren
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
id|writeb
c_func
(paren
id|val
comma
id|kbd_iobase
op_plus
l_int|0x64UL
)paren
suffix:semicolon
)brace
DECL|macro|OBP_PS2KBD_NAME1
mdefine_line|#define OBP_PS2KBD_NAME1&t;&quot;kb_ps2&quot;
DECL|macro|OBP_PS2KBD_NAME2
mdefine_line|#define OBP_PS2KBD_NAME2&t;&quot;keyboard&quot;
DECL|macro|OBP_PS2MS_NAME1
mdefine_line|#define OBP_PS2MS_NAME1&t;&t;&quot;kdmouse&quot;
DECL|macro|OBP_PS2MS_NAME2
mdefine_line|#define OBP_PS2MS_NAME2&t;&t;&quot;mouse&quot;
DECL|function|i8042_platform_init
r_static
r_int
id|i8042_platform_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_PCI
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#else
r_char
id|prop
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|prom_root_node
comma
l_string|&quot;name&quot;
comma
id|prop
comma
r_sizeof
(paren
id|prop
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i8042: Cannot get name property of root OBP node.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|prop
comma
l_string|&quot;SUNW,JavaStation-1&quot;
comma
id|len
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Hardcoded values for MrCoffee.  */
id|i8042_kbd_irq
op_assign
id|i8042_aux_irq
op_assign
l_int|13
op_or
l_int|0x20
suffix:semicolon
id|kbd_iobase
op_assign
id|ioremap
c_func
(paren
l_int|0x71300060
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbd_iobase
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
suffix:semicolon
r_struct
id|linux_ebus_child
op_star
id|child
suffix:semicolon
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;8042&quot;
)paren
)paren
r_goto
id|edev_found
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
id|edev_found
suffix:colon
id|for_each_edevchild
c_func
(paren
id|edev
comma
id|child
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|child-&gt;prom_name
comma
id|OBP_PS2KBD_NAME1
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|child-&gt;prom_name
comma
id|OBP_PS2KBD_NAME2
)paren
)paren
(brace
id|i8042_kbd_irq
op_assign
id|child-&gt;irqs
(braket
l_int|0
)braket
suffix:semicolon
id|kbd_iobase
op_assign
id|ioremap
c_func
(paren
id|child-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
l_int|8
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|child-&gt;prom_name
comma
id|OBP_PS2MS_NAME1
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|child-&gt;prom_name
comma
id|OBP_PS2MS_NAME2
)paren
)paren
id|i8042_aux_irq
op_assign
id|child-&gt;irqs
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i8042_kbd_irq
op_eq
op_minus
l_int|1
op_logical_or
id|i8042_aux_irq
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i8042: Error, 8042 device lacks both kbd and &quot;
l_string|&quot;mouse nodes.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|i8042_reset
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
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
macro_line|#ifdef CONFIG_PCI
id|iounmap
c_func
(paren
id|kbd_iobase
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* _I8042_SPARCIO_H */
eof
