multiline_comment|/*&n; *  i8042 keyboard and mouse controller driver for Linux&n; *&n; *  Copyright (c) 1999-2002 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* request/free_irq */
macro_line|#include &quot;i8042.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;i8042 keyboard and mouse controller driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i8042_noaux
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i8042_unlock
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i8042_reset
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i8042_direct
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
DECL|variable|i8042_noaux
r_static
r_int
id|i8042_noaux
suffix:semicolon
DECL|variable|i8042_unlock
r_static
r_int
id|i8042_unlock
suffix:semicolon
DECL|variable|i8042_reset
r_static
r_int
id|i8042_reset
suffix:semicolon
DECL|variable|i8042_direct
r_static
r_int
id|i8042_direct
suffix:semicolon
DECL|variable|i8042_lock
id|spinlock_t
id|i8042_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|struct|i8042_values
r_struct
id|i8042_values
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|disable
r_int
r_char
id|disable
suffix:semicolon
DECL|member|irqen
r_int
r_char
id|irqen
suffix:semicolon
DECL|member|exists
r_int
r_char
id|exists
suffix:semicolon
DECL|member|name
r_int
r_char
op_star
id|name
suffix:semicolon
DECL|member|phys
r_int
r_char
op_star
id|phys
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|i8042_kbd_port
r_static
r_struct
id|serio
id|i8042_kbd_port
suffix:semicolon
DECL|variable|i8042_aux_port
r_static
r_struct
id|serio
id|i8042_aux_port
suffix:semicolon
DECL|variable|i8042_initial_ctr
r_static
r_int
r_char
id|i8042_initial_ctr
suffix:semicolon
DECL|variable|i8042_ctr
r_static
r_int
r_char
id|i8042_ctr
suffix:semicolon
DECL|variable|i8042_timer
r_struct
id|timer_list
id|i8042_timer
suffix:semicolon
macro_line|#ifdef I8042_DEBUG_IO
DECL|variable|i8042_start
r_static
r_int
r_int
id|i8042_start
suffix:semicolon
macro_line|#endif
DECL|variable|i8042_unxlate_seen
r_static
r_int
r_int
id|i8042_unxlate_seen
(braket
l_int|128
op_div
id|BITS_PER_LONG
)braket
suffix:semicolon
DECL|variable|i8042_unxlate_table
r_static
r_int
r_char
id|i8042_unxlate_table
(braket
l_int|128
)braket
op_assign
(brace
l_int|0
comma
l_int|118
comma
l_int|22
comma
l_int|30
comma
l_int|38
comma
l_int|37
comma
l_int|46
comma
l_int|54
comma
l_int|61
comma
l_int|62
comma
l_int|70
comma
l_int|69
comma
l_int|78
comma
l_int|85
comma
l_int|102
comma
l_int|13
comma
l_int|21
comma
l_int|29
comma
l_int|36
comma
l_int|45
comma
l_int|44
comma
l_int|53
comma
l_int|60
comma
l_int|67
comma
l_int|68
comma
l_int|77
comma
l_int|84
comma
l_int|91
comma
l_int|90
comma
l_int|20
comma
l_int|28
comma
l_int|27
comma
l_int|35
comma
l_int|43
comma
l_int|52
comma
l_int|51
comma
l_int|59
comma
l_int|66
comma
l_int|75
comma
l_int|76
comma
l_int|82
comma
l_int|14
comma
l_int|18
comma
l_int|93
comma
l_int|26
comma
l_int|34
comma
l_int|33
comma
l_int|42
comma
l_int|50
comma
l_int|49
comma
l_int|58
comma
l_int|65
comma
l_int|73
comma
l_int|74
comma
l_int|89
comma
l_int|124
comma
l_int|17
comma
l_int|41
comma
l_int|88
comma
l_int|5
comma
l_int|6
comma
l_int|4
comma
l_int|12
comma
l_int|3
comma
l_int|11
comma
l_int|2
comma
l_int|10
comma
l_int|1
comma
l_int|9
comma
l_int|119
comma
l_int|126
comma
l_int|108
comma
l_int|117
comma
l_int|125
comma
l_int|123
comma
l_int|107
comma
l_int|115
comma
l_int|116
comma
l_int|121
comma
l_int|105
comma
l_int|114
comma
l_int|122
comma
l_int|112
comma
l_int|113
comma
l_int|127
comma
l_int|96
comma
l_int|97
comma
l_int|120
comma
l_int|7
comma
l_int|15
comma
l_int|23
comma
l_int|31
comma
l_int|39
comma
l_int|47
comma
l_int|55
comma
l_int|63
comma
l_int|71
comma
l_int|79
comma
l_int|86
comma
l_int|94
comma
l_int|8
comma
l_int|16
comma
l_int|24
comma
l_int|32
comma
l_int|40
comma
l_int|48
comma
l_int|56
comma
l_int|64
comma
l_int|72
comma
l_int|80
comma
l_int|87
comma
l_int|111
comma
l_int|19
comma
l_int|25
comma
l_int|57
comma
l_int|81
comma
l_int|83
comma
l_int|92
comma
l_int|95
comma
l_int|98
comma
l_int|99
comma
l_int|100
comma
l_int|101
comma
l_int|103
comma
l_int|104
comma
l_int|106
comma
l_int|109
comma
l_int|110
)brace
suffix:semicolon
r_static
r_void
id|i8042_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * The i8042_wait_read() and i8042_wait_write functions wait for the i8042 to&n; * be ready for reading values from it / writing values to it.&n; */
DECL|function|i8042_wait_read
r_static
r_int
id|i8042_wait_read
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
op_complement
id|i8042_read_status
c_func
(paren
)paren
op_amp
id|I8042_STR_OBF
)paren
op_logical_and
(paren
id|i
OL
id|I8042_CTL_TIMEOUT
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_return
op_minus
(paren
id|i
op_eq
id|I8042_CTL_TIMEOUT
)paren
suffix:semicolon
)brace
DECL|function|i8042_wait_write
r_static
r_int
id|i8042_wait_write
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i8042_read_status
c_func
(paren
)paren
op_amp
id|I8042_STR_IBF
)paren
op_logical_and
(paren
id|i
OL
id|I8042_CTL_TIMEOUT
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_return
op_minus
(paren
id|i
op_eq
id|I8042_CTL_TIMEOUT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_flush() flushes all data that may be in the keyboard and mouse buffers&n; * of the i8042 down the toilet.&n; */
DECL|function|i8042_flush
r_static
r_int
id|i8042_flush
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i8042_read_status
c_func
(paren
)paren
op_amp
id|I8042_STR_OBF
)paren
op_logical_and
(paren
id|i
op_increment
OL
id|I8042_BUFFER_SIZE
)paren
)paren
macro_line|#ifdef I8042_DEBUG_IO
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c: %02x &lt;- i8042 (flush) [%d]&bslash;n&quot;
comma
id|i8042_read_data
c_func
(paren
)paren
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#else
id|i8042_read_data
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_command() executes a command on the i8042. It also sends the input parameter(s)&n; * of the commands to it, and receives the output value(s). The parameters are to be&n; * stored in the param array, and the output is placed into the same array. The number&n; * of the parameters and output values is encoded in bits 8-11 of the command&n; * number.&n; */
DECL|function|i8042_command
r_static
r_int
id|i8042_command
c_func
(paren
r_int
r_char
op_star
id|param
comma
r_int
id|command
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
id|retval
op_assign
id|i8042_wait_write
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
macro_line|#ifdef I8042_DEBUG_IO
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c: %02x -&gt; i8042 (command) [%d]&bslash;n&quot;
comma
id|command
op_amp
l_int|0xff
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#endif
id|i8042_write_command
c_func
(paren
id|command
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
(paren
id|command
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|i8042_wait_write
c_func
(paren
)paren
)paren
)paren
r_break
suffix:semicolon
macro_line|#ifdef I8042_DEBUG_IO
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c: %02x -&gt; i8042 (parameter) [%d]&bslash;n&quot;
comma
id|param
(braket
id|i
)braket
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#endif
id|i8042_write_data
c_func
(paren
id|param
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
(paren
id|command
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|i8042_wait_read
c_func
(paren
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i8042_read_status
c_func
(paren
)paren
op_amp
id|I8042_STR_AUXDATA
)paren
id|param
(braket
id|i
)braket
op_assign
op_complement
id|i8042_read_data
c_func
(paren
)paren
suffix:semicolon
r_else
id|param
(braket
id|i
)braket
op_assign
id|i8042_read_data
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef I8042_DEBUG_IO
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c: %02x &lt;- i8042 (return) [%d]&bslash;n&quot;
comma
id|param
(braket
id|i
)braket
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef I8042_DEBUG_IO
r_if
c_cond
(paren
id|retval
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c:      -- i8042 (timeout) [%d]&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_kbd_write() sends a byte out through the keyboard interface.&n; * It also automatically refreshes the CTR value, since some i8042&squot;s&n; * trash their CTR after attempting to send data to an nonexistent&n; * device.&n; */
DECL|function|i8042_kbd_write
r_static
r_int
id|i8042_kbd_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
r_int
r_char
id|c
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|retval
op_assign
id|i8042_wait_write
c_func
(paren
)paren
)paren
)paren
(brace
macro_line|#ifdef I8042_DEBUG_IO
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c: %02x -&gt; i8042 (kbd-data) [%d]&bslash;n&quot;
comma
id|c
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#endif
id|i8042_write_data
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_aux_write() sends a byte out through the aux interface.&n; */
DECL|function|i8042_aux_write
r_static
r_int
id|i8042_aux_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
r_int
r_char
id|c
)paren
(brace
r_int
id|retval
suffix:semicolon
multiline_comment|/*&n; * Send the byte out.&n; */
id|retval
op_assign
id|i8042_command
c_func
(paren
op_amp
id|c
comma
id|I8042_CMD_AUX_SEND
)paren
suffix:semicolon
multiline_comment|/*&n; * Here we restore the CTR value. I don&squot;t know why, but i8042&squot;s in half-AT&n; * mode tend to trash their CTR when doing the AUX_SEND command.&n; */
id|retval
op_or_assign
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
suffix:semicolon
multiline_comment|/*&n; * Make sure the interrupt happens and the character is received even&n; * in the case the IRQ isn&squot;t wired, so that we can receive further&n; * characters later.&n; */
id|i8042_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_open() is called when a port is open by the higher layer.&n; * It allocates an interrupt and enables the port.&n; */
DECL|function|i8042_open
r_static
r_int
id|i8042_open
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
r_struct
id|i8042_values
op_star
id|values
op_assign
id|port-&gt;driver
suffix:semicolon
multiline_comment|/*&n; * Allocate the interrupt&n; */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|values-&gt;irq
comma
id|i8042_interrupt
comma
l_int|0
comma
l_string|&quot;i8042&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: Can&squot;t get irq %d for %s, unregistering the port.&bslash;n&quot;
comma
id|values-&gt;irq
comma
id|values-&gt;name
)paren
suffix:semicolon
id|values-&gt;exists
op_assign
l_int|0
suffix:semicolon
id|serio_unregister_port
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable the interrupt.&n; */
id|i8042_ctr
op_or_assign
id|values-&gt;irqen
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: Can&squot;t write CTR while opening %s.&bslash;n&quot;
comma
id|values-&gt;name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_close() frees the interrupt, and disables the interface when the&n; * upper layer doesn&squot;t need it anymore.&n; */
DECL|function|i8042_close
r_static
r_void
id|i8042_close
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
r_struct
id|i8042_values
op_star
id|values
op_assign
id|port-&gt;driver
suffix:semicolon
multiline_comment|/*&n; * Disable the interrupt.&n; */
id|i8042_ctr
op_and_assign
op_complement
id|values-&gt;irqen
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: Can&squot;t write CTR while closing %s.&bslash;n&quot;
comma
id|values-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Free the interrupt&n; */
id|free_irq
c_func
(paren
id|values-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Structures for registering the devices in the serio.c module.&n; */
DECL|variable|i8042_kbd_values
r_static
r_struct
id|i8042_values
id|i8042_kbd_values
op_assign
(brace
id|irq
suffix:colon
id|I8042_KBD_IRQ
comma
id|irqen
suffix:colon
id|I8042_CTR_KBDINT
comma
id|disable
suffix:colon
id|I8042_CTR_KBDDIS
comma
id|name
suffix:colon
l_string|&quot;KBD&quot;
comma
id|exists
suffix:colon
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|i8042_kbd_port
r_static
r_struct
id|serio
id|i8042_kbd_port
op_assign
(brace
id|type
suffix:colon
id|SERIO_8042
comma
id|write
suffix:colon
id|i8042_kbd_write
comma
id|open
suffix:colon
id|i8042_open
comma
id|close
suffix:colon
id|i8042_close
comma
id|driver
suffix:colon
op_amp
id|i8042_kbd_values
comma
id|name
suffix:colon
l_string|&quot;i8042 Kbd Port&quot;
comma
id|phys
suffix:colon
id|I8042_KBD_PHYS_DESC
comma
)brace
suffix:semicolon
DECL|variable|i8042_aux_values
r_static
r_struct
id|i8042_values
id|i8042_aux_values
op_assign
(brace
id|irq
suffix:colon
id|I8042_AUX_IRQ
comma
id|irqen
suffix:colon
id|I8042_CTR_AUXINT
comma
id|disable
suffix:colon
id|I8042_CTR_AUXDIS
comma
id|name
suffix:colon
l_string|&quot;AUX&quot;
comma
id|exists
suffix:colon
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|i8042_aux_port
r_static
r_struct
id|serio
id|i8042_aux_port
op_assign
(brace
id|type
suffix:colon
id|SERIO_8042
comma
id|write
suffix:colon
id|i8042_aux_write
comma
id|open
suffix:colon
id|i8042_open
comma
id|close
suffix:colon
id|i8042_close
comma
id|driver
suffix:colon
op_amp
id|i8042_aux_values
comma
id|name
suffix:colon
l_string|&quot;i8042 Aux Port&quot;
comma
id|phys
suffix:colon
id|I8042_AUX_PHYS_DESC
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * i8042_interrupt() is the most important function in this driver -&n; * it handles the interrupts from the i8042, and sends incoming bytes&n; * to the upper layers.&n; */
DECL|function|i8042_interrupt
r_static
r_void
id|i8042_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|str
comma
id|data
suffix:semicolon
r_int
r_int
id|dfl
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|str
op_assign
id|i8042_read_status
c_func
(paren
)paren
)paren
op_amp
id|I8042_STR_OBF
)paren
(brace
id|data
op_assign
id|i8042_read_data
c_func
(paren
)paren
suffix:semicolon
id|dfl
op_assign
(paren
(paren
id|str
op_amp
id|I8042_STR_PARITY
)paren
ques
c_cond
id|SERIO_PARITY
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|str
op_amp
id|I8042_STR_TIMEOUT
)paren
ques
c_cond
id|SERIO_TIMEOUT
suffix:colon
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef I8042_DEBUG_IO
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i8042.c: %02x &lt;- i8042 (interrupt-%s, %d) [%d]&bslash;n&quot;
comma
id|data
comma
(paren
id|str
op_amp
id|I8042_STR_AUXDATA
)paren
ques
c_cond
l_string|&quot;aux&quot;
suffix:colon
l_string|&quot;kbd&quot;
comma
id|irq
comma
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|i8042_start
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|i8042_aux_values.exists
op_logical_and
(paren
id|str
op_amp
id|I8042_STR_AUXDATA
)paren
)paren
(brace
id|serio_interrupt
c_func
(paren
op_amp
id|i8042_aux_port
comma
id|data
comma
id|dfl
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|i8042_kbd_values.exists
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i8042_direct
)paren
(brace
r_if
c_cond
(paren
id|data
OG
l_int|0x7f
)paren
(brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|data
op_amp
l_int|0x7f
comma
id|i8042_unxlate_seen
)paren
)paren
(brace
id|serio_interrupt
c_func
(paren
op_amp
id|i8042_kbd_port
comma
l_int|0xf0
comma
id|dfl
)paren
suffix:semicolon
id|data
op_assign
id|i8042_unxlate_table
(braket
id|data
op_amp
l_int|0x7f
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
id|set_bit
c_func
(paren
id|data
comma
id|i8042_unxlate_seen
)paren
suffix:semicolon
id|data
op_assign
id|i8042_unxlate_table
(braket
id|data
)braket
suffix:semicolon
)brace
)brace
id|serio_interrupt
c_func
(paren
op_amp
id|i8042_kbd_port
comma
id|data
comma
id|dfl
)paren
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8042_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_controller init initializes the i8042 controller, and,&n; * most importantly, sets it into non-xlated mode.&n; */
DECL|function|i8042_controller_init
r_static
r_int
id|__init
id|i8042_controller_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; * Check the i/o region before we touch it.&n; */
macro_line|#if !defined(__i386__) &amp;&amp; !defined(__sh__) &amp;&amp; !defined(__alpha__) &t;
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|I8042_DATA_REG
comma
l_int|16
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: %#x port already in use!&bslash;n&quot;
comma
id|I8042_DATA_REG
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Test the i8042. We need to know if it thinks it&squot;s working correctly&n; * before doing anything else.&n; */
id|i8042_flush
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i8042_reset
)paren
(brace
r_int
r_char
id|param
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_CTL_TEST
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: i8042 controller self test timeout.&bslash;n&quot;
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
id|param
op_ne
id|I8042_RET_CTL_TEST
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: i8042 controller selftest failed. (%#x != %#x)&bslash;n&quot;
comma
id|param
comma
id|I8042_RET_CTL_TEST
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Read the CTR.&n; */
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_RCTR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: Can&squot;t read CTR while initializing i8042.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Save the CTR for restoral on unload / reboot.&n; */
id|i8042_initial_ctr
op_assign
id|i8042_ctr
suffix:semicolon
multiline_comment|/*&n; * Disable both interfaces and their interrupts.&n; */
id|i8042_ctr
op_or_assign
id|I8042_CTR_KBDDIS
suffix:semicolon
id|i8042_ctr
op_and_assign
op_complement
id|I8042_CTR_KBDINT
suffix:semicolon
multiline_comment|/*&n; * Handle keylock.&n; */
r_if
c_cond
(paren
op_complement
id|i8042_read_status
c_func
(paren
)paren
op_amp
id|I8042_STR_KEYLOCK
)paren
(brace
r_if
c_cond
(paren
id|i8042_unlock
)paren
(brace
id|i8042_ctr
op_or_assign
id|I8042_CTR_IGNKEYLOCK
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i8042.c: Warning: Keylock active.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * If the chip is configured into nontranslated mode by the BIOS, don&squot;t&n; * bother enabling translating and just use that happily.&n; */
r_if
c_cond
(paren
op_complement
id|i8042_ctr
op_amp
id|I8042_CTR_XLATE
)paren
id|i8042_direct
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Set nontranslated mode for the kbd interface if requested by an option.&n; * This is vital for a working scancode set 3 support. After this the kbd&n; * interface becomes a simple serial in/out, like the aux interface is. If&n; * the user doesn&squot;t wish this, the driver tries to untranslate the values&n; * after the i8042 translates them.&n; */
r_if
c_cond
(paren
id|i8042_direct
)paren
id|i8042_ctr
op_and_assign
op_complement
id|I8042_CTR_XLATE
suffix:semicolon
multiline_comment|/*&n; * Write CTR back.&n; */
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: Can&squot;t write CTR while initializing i8042.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Here we try to reset everything back to a state in which the BIOS will be&n; * able to talk to the hardware when rebooting.&n; */
DECL|function|i8042_controller_cleanup
r_void
id|i8042_controller_cleanup
c_func
(paren
r_void
)paren
(brace
id|i8042_flush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Reset the controller.&n; */
r_if
c_cond
(paren
id|i8042_reset
)paren
(brace
r_int
r_char
id|param
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_CTL_TEST
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i8042.c: i8042 controller reset timeout.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Restore the original control register setting.&n; */
id|i8042_ctr
op_assign
id|i8042_initial_ctr
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i8042.c: Can&squot;t restore CTR.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Reset anything that is connected to the ports if the ports&n; * are enabled in the original config.&n; */
r_if
c_cond
(paren
id|i8042_kbd_values.exists
)paren
id|i8042_kbd_write
c_func
(paren
op_amp
id|i8042_kbd_port
comma
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i8042_aux_values.exists
)paren
id|i8042_aux_write
c_func
(paren
op_amp
id|i8042_aux_port
comma
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_check_aux() applies as much paranoia as it can at detecting&n; * the presence of an AUX interface.&n; */
DECL|function|i8042_check_aux
r_static
r_int
id|__init
id|i8042_check_aux
c_func
(paren
r_struct
id|i8042_values
op_star
id|values
comma
r_struct
id|serio
op_star
id|port
)paren
(brace
r_int
r_char
id|param
suffix:semicolon
multiline_comment|/*&n; * Check if AUX irq is available. If it isn&squot;t, then there is no point&n; * in trying to detect AUX presence.&n; */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|values-&gt;irq
comma
id|i8042_interrupt
comma
l_int|0
comma
l_string|&quot;i8042&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|free_irq
c_func
(paren
id|values-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * Get rid of bytes in the queue.&n; */
id|i8042_flush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Internal loopback test - filters out AT-type i8042&squot;s&n; */
id|param
op_assign
l_int|0x5a
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_AUX_LOOP
)paren
op_logical_or
id|param
op_ne
l_int|0xa5
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * External connection test - filters out AT-soldered PS/2 i8042&squot;s&n; */
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_AUX_TEST
)paren
op_logical_or
id|param
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Bit assignment test - filters out PS/2 i8042&squot;s in AT mode&n; */
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_AUX_DISABLE
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_CTL_RCTR
)paren
op_logical_or
(paren
op_complement
id|param
op_amp
id|I8042_CTR_AUXDIS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_AUX_TEST
)paren
op_logical_or
id|param
)paren
(brace
multiline_comment|/*&n; * We&squot;ve got an old AMI i8042 with &squot;Bad Cache&squot; commands.&n; */
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_AUX_ENABLE
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
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_AUX_ENABLE
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|param
comma
id|I8042_CMD_CTL_RCTR
)paren
op_logical_or
(paren
id|param
op_amp
id|I8042_CTR_AUXDIS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Disable the interface.&n; */
id|i8042_ctr
op_or_assign
id|I8042_CTR_AUXDIS
suffix:semicolon
id|i8042_ctr
op_and_assign
op_complement
id|I8042_CTR_AUXINT
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * i8042_port_register() marks the device as existing,&n; * registers it, and reports to the user.&n; */
DECL|function|i8042_port_register
r_static
r_int
id|__init
id|i8042_port_register
c_func
(paren
r_struct
id|i8042_values
op_star
id|values
comma
r_struct
id|serio
op_star
id|port
)paren
(brace
id|values-&gt;exists
op_assign
l_int|1
suffix:semicolon
id|serio_register_port
c_func
(paren
id|port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: i8042 %s port at %#x,%#x irq %d&bslash;n&quot;
comma
id|values-&gt;name
comma
id|I8042_DATA_REG
comma
id|I8042_COMMAND_REG
comma
id|values-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8042_timer_func
r_static
r_void
id|i8042_timer_func
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|i8042_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|i8042_timer
comma
id|jiffies
op_plus
id|I8042_POLL_PERIOD
)paren
suffix:semicolon
)brace
DECL|function|i8042_start_polling
r_static
r_void
id|__init
id|i8042_start_polling
c_func
(paren
r_void
)paren
(brace
id|i8042_ctr
op_and_assign
op_complement
id|I8042_CTR_KBDDIS
suffix:semicolon
r_if
c_cond
(paren
id|i8042_aux_values.exists
)paren
id|i8042_ctr
op_and_assign
op_complement
id|I8042_CTR_AUXDIS
suffix:semicolon
r_if
c_cond
(paren
id|i8042_command
c_func
(paren
op_amp
id|i8042_ctr
comma
id|I8042_CMD_CTL_WCTR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i8042.c: Can&squot;t write CTR while starting polling.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|i8042_timer.function
op_assign
id|i8042_timer_func
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|i8042_timer
comma
id|jiffies
op_plus
id|I8042_POLL_PERIOD
)paren
suffix:semicolon
)brace
DECL|function|i8042_stop_polling
r_static
r_void
id|__exit
id|i8042_stop_polling
c_func
(paren
r_void
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|i8042_timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Module init and cleanup functions.&n; */
DECL|function|i8042_setup
r_void
id|__init
id|i8042_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;i8042_reset=1&quot;
)paren
)paren
id|i8042_reset
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;i8042_noaux=1&quot;
)paren
)paren
id|i8042_noaux
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;i8042_unlock=1&quot;
)paren
)paren
id|i8042_unlock
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;i8042_direct=1&quot;
)paren
)paren
id|i8042_direct
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Reset the 8042 back to original mode.&n; */
DECL|function|i8042_notify_sys
r_static
r_int
id|i8042_notify_sys
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|unused
)paren
(brace
r_if
c_cond
(paren
id|code
op_eq
id|SYS_DOWN
op_logical_or
id|code
op_eq
id|SYS_HALT
)paren
id|i8042_controller_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|i8042_notifier
r_static
r_struct
id|notifier_block
id|i8042_notifier
op_assign
(brace
id|i8042_notify_sys
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|function|i8042_init
r_int
id|__init
id|i8042_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef I8042_DEBUG_IO
id|i8042_start
op_assign
id|jiffies
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|i8042_platform_init
c_func
(paren
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|i8042_controller_init
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|i8042_port_register
c_func
(paren
op_amp
id|i8042_kbd_values
comma
op_amp
id|i8042_kbd_port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i8042_noaux
op_logical_and
op_logical_neg
id|i8042_check_aux
c_func
(paren
op_amp
id|i8042_aux_values
comma
op_amp
id|i8042_aux_port
)paren
)paren
id|i8042_port_register
c_func
(paren
op_amp
id|i8042_aux_values
comma
op_amp
id|i8042_aux_port
)paren
suffix:semicolon
id|i8042_start_polling
c_func
(paren
)paren
suffix:semicolon
id|register_reboot_notifier
c_func
(paren
op_amp
id|i8042_notifier
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8042_exit
r_void
id|__exit
id|i8042_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|i8042_notifier
)paren
suffix:semicolon
id|i8042_stop_polling
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i8042_kbd_values.exists
)paren
id|serio_unregister_port
c_func
(paren
op_amp
id|i8042_kbd_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i8042_aux_values.exists
)paren
id|serio_unregister_port
c_func
(paren
op_amp
id|i8042_aux_port
)paren
suffix:semicolon
id|i8042_controller_cleanup
c_func
(paren
)paren
suffix:semicolon
id|i8042_platform_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|i8042_init
id|module_init
c_func
(paren
id|i8042_init
)paren
suffix:semicolon
DECL|variable|i8042_exit
id|module_exit
c_func
(paren
id|i8042_exit
)paren
suffix:semicolon
eof