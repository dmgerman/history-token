multiline_comment|/* $Id: bbc_i2c.c,v 1.2 2001/04/02 09:59:08 davem Exp $&n; * bbc_i2c.c: I2C low-level driver for BBC device on UltraSPARC-III&n; *            platforms.&n; *&n; * Copyright (C) 2001 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/bbc.h&gt;
macro_line|#include &quot;bbc_i2c.h&quot;
multiline_comment|/* Convert this driver to use i2c bus layer someday... */
DECL|macro|I2C_PCF_PIN
mdefine_line|#define I2C_PCF_PIN&t;0x80
DECL|macro|I2C_PCF_ESO
mdefine_line|#define I2C_PCF_ESO&t;0x40
DECL|macro|I2C_PCF_ES1
mdefine_line|#define I2C_PCF_ES1&t;0x20
DECL|macro|I2C_PCF_ES2
mdefine_line|#define I2C_PCF_ES2&t;0x10
DECL|macro|I2C_PCF_ENI
mdefine_line|#define I2C_PCF_ENI&t;0x08
DECL|macro|I2C_PCF_STA
mdefine_line|#define I2C_PCF_STA&t;0x04
DECL|macro|I2C_PCF_STO
mdefine_line|#define I2C_PCF_STO&t;0x02
DECL|macro|I2C_PCF_ACK
mdefine_line|#define I2C_PCF_ACK&t;0x01
DECL|macro|I2C_PCF_START
mdefine_line|#define I2C_PCF_START    (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_ENI | I2C_PCF_STA | I2C_PCF_ACK)
DECL|macro|I2C_PCF_STOP
mdefine_line|#define I2C_PCF_STOP     (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STO | I2C_PCF_ACK)
DECL|macro|I2C_PCF_REPSTART
mdefine_line|#define I2C_PCF_REPSTART (              I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
DECL|macro|I2C_PCF_IDLE
mdefine_line|#define I2C_PCF_IDLE     (I2C_PCF_PIN | I2C_PCF_ESO               | I2C_PCF_ACK)
DECL|macro|I2C_PCF_INI
mdefine_line|#define I2C_PCF_INI 0x40   /* 1 if not initialized */
DECL|macro|I2C_PCF_STS
mdefine_line|#define I2C_PCF_STS 0x20
DECL|macro|I2C_PCF_BER
mdefine_line|#define I2C_PCF_BER 0x10
DECL|macro|I2C_PCF_AD0
mdefine_line|#define I2C_PCF_AD0 0x08
DECL|macro|I2C_PCF_LRB
mdefine_line|#define I2C_PCF_LRB 0x08
DECL|macro|I2C_PCF_AAS
mdefine_line|#define I2C_PCF_AAS 0x04
DECL|macro|I2C_PCF_LAB
mdefine_line|#define I2C_PCF_LAB 0x02
DECL|macro|I2C_PCF_BB
mdefine_line|#define I2C_PCF_BB  0x01
multiline_comment|/* The BBC devices have two I2C controllers.  The first I2C controller&n; * connects mainly to configuration proms (NVRAM, cpu configuration,&n; * dimm types, etc.).  Whereas the second I2C controller connects to&n; * environmental control devices such as fans and temperature sensors.&n; * The second controller also connects to the smartcard reader, if present.&n; */
DECL|macro|NUM_CHILDREN
mdefine_line|#define NUM_CHILDREN&t;8
DECL|struct|bbc_i2c_bus
r_struct
id|bbc_i2c_bus
(brace
DECL|member|next
r_struct
id|bbc_i2c_bus
op_star
id|next
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|i2c_bussel_reg
r_void
op_star
id|i2c_bussel_reg
suffix:semicolon
DECL|member|i2c_control_regs
r_void
op_star
id|i2c_control_regs
suffix:semicolon
DECL|member|own
DECL|member|clock
r_int
r_char
id|own
comma
id|clock
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|waiting
r_volatile
r_int
id|waiting
suffix:semicolon
DECL|member|bus_edev
r_struct
id|linux_ebus_device
op_star
id|bus_edev
suffix:semicolon
r_struct
(brace
DECL|member|device
r_struct
id|linux_ebus_child
op_star
id|device
suffix:semicolon
DECL|member|client_claimed
r_int
id|client_claimed
suffix:semicolon
DECL|member|devs
)brace
id|devs
(braket
id|NUM_CHILDREN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|all_bbc_i2c
r_static
r_struct
id|bbc_i2c_bus
op_star
id|all_bbc_i2c
suffix:semicolon
DECL|struct|bbc_i2c_client
r_struct
id|bbc_i2c_client
(brace
DECL|member|bp
r_struct
id|bbc_i2c_bus
op_star
id|bp
suffix:semicolon
DECL|member|echild
r_struct
id|linux_ebus_child
op_star
id|echild
suffix:semicolon
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|address
r_int
id|address
suffix:semicolon
)brace
suffix:semicolon
DECL|function|find_device
r_static
r_int
id|find_device
c_func
(paren
r_struct
id|bbc_i2c_bus
op_star
id|bp
comma
r_struct
id|linux_ebus_child
op_star
id|echild
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_CHILDREN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bp-&gt;devs
(braket
id|i
)braket
dot
id|device
op_eq
id|echild
)paren
(brace
r_if
c_cond
(paren
id|bp-&gt;devs
(braket
id|i
)braket
dot
id|client_claimed
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_device_claimage
r_static
r_void
id|set_device_claimage
c_func
(paren
r_struct
id|bbc_i2c_bus
op_star
id|bp
comma
r_struct
id|linux_ebus_child
op_star
id|echild
comma
r_int
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_CHILDREN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bp-&gt;devs
(braket
id|i
)braket
dot
id|device
op_eq
id|echild
)paren
(brace
id|bp-&gt;devs
(braket
id|i
)braket
dot
id|client_claimed
op_assign
id|val
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
DECL|macro|claim_device
mdefine_line|#define claim_device(BP,ECHILD)&t;&t;set_device_claimage(BP,ECHILD,1)
DECL|macro|release_device
mdefine_line|#define release_device(BP,ECHILD)&t;set_device_claimage(BP,ECHILD,0)
DECL|function|find_bus_for_device
r_static
r_struct
id|bbc_i2c_bus
op_star
id|find_bus_for_device
c_func
(paren
r_struct
id|linux_ebus_child
op_star
id|echild
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|all_bbc_i2c
suffix:semicolon
r_while
c_loop
(paren
id|bp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|find_device
c_func
(paren
id|bp
comma
id|echild
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|bp
op_assign
id|bp-&gt;next
suffix:semicolon
)brace
r_return
id|bp
suffix:semicolon
)brace
DECL|function|bbc_i2c_getdev
r_struct
id|linux_ebus_child
op_star
id|bbc_i2c_getdev
c_func
(paren
r_int
id|index
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|all_bbc_i2c
suffix:semicolon
r_struct
id|linux_ebus_child
op_star
id|echild
op_assign
l_int|NULL
suffix:semicolon
r_int
id|curidx
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|bp
op_ne
l_int|NULL
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|next
op_assign
id|bp-&gt;next
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_CHILDREN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|echild
op_assign
id|bp-&gt;devs
(braket
id|i
)braket
dot
id|device
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|curidx
op_eq
id|index
)paren
r_goto
id|out
suffix:semicolon
id|echild
op_assign
l_int|NULL
suffix:semicolon
id|curidx
op_increment
suffix:semicolon
)brace
id|bp
op_assign
id|next
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|curidx
op_eq
id|index
)paren
r_return
id|echild
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|bbc_i2c_attach
r_struct
id|bbc_i2c_client
op_star
id|bbc_i2c_attach
c_func
(paren
r_struct
id|linux_ebus_child
op_star
id|echild
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|find_bus_for_device
c_func
(paren
id|echild
)paren
suffix:semicolon
r_struct
id|bbc_i2c_client
op_star
id|client
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp
)paren
r_return
l_int|NULL
suffix:semicolon
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|client
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|client
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|client
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|client
)paren
)paren
suffix:semicolon
id|client-&gt;bp
op_assign
id|bp
suffix:semicolon
id|client-&gt;echild
op_assign
id|echild
suffix:semicolon
id|client-&gt;bus
op_assign
id|echild-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|client-&gt;address
op_assign
id|echild-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|claim_device
c_func
(paren
id|bp
comma
id|echild
)paren
suffix:semicolon
r_return
id|client
suffix:semicolon
)brace
DECL|function|bbc_i2c_detach
r_void
id|bbc_i2c_detach
c_func
(paren
r_struct
id|bbc_i2c_client
op_star
id|client
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|client-&gt;bp
suffix:semicolon
r_struct
id|linux_ebus_child
op_star
id|echild
op_assign
id|client-&gt;echild
suffix:semicolon
id|release_device
c_func
(paren
id|bp
comma
id|echild
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
DECL|function|wait_for_pin
r_static
r_int
id|wait_for_pin
c_func
(paren
r_struct
id|bbc_i2c_bus
op_star
id|bp
comma
id|u8
op_star
id|status
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|limit
op_assign
l_int|32
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
id|bp-&gt;waiting
op_assign
l_int|1
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|bp-&gt;wq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|limit
op_decrement
OG
l_int|0
)paren
(brace
id|u8
id|val
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
op_star
id|status
op_assign
id|val
op_assign
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
id|I2C_PCF_PIN
)paren
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|4
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|bp-&gt;wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|bp-&gt;waiting
op_assign
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|bbc_i2c_writeb
r_int
id|bbc_i2c_writeb
c_func
(paren
r_struct
id|bbc_i2c_client
op_star
id|client
comma
r_int
r_char
id|val
comma
r_int
id|off
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|client-&gt;bp
suffix:semicolon
r_int
id|address
op_assign
id|client-&gt;address
suffix:semicolon
id|u8
id|status
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;i2c_bussel_reg
op_ne
l_int|NULL
)paren
id|writeb
c_func
(paren
id|client-&gt;bus
comma
id|bp-&gt;i2c_bussel_reg
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|address
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_START
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
)paren
r_goto
id|out
suffix:semicolon
id|writeb
c_func
(paren
id|off
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
op_logical_or
(paren
id|status
op_amp
id|I2C_PCF_LRB
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|writeb
c_func
(paren
id|val
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|writeb
c_func
(paren
id|I2C_PCF_STOP
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|bbc_i2c_readb
r_int
id|bbc_i2c_readb
c_func
(paren
r_struct
id|bbc_i2c_client
op_star
id|client
comma
r_int
r_char
op_star
id|byte
comma
r_int
id|off
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|client-&gt;bp
suffix:semicolon
r_int
r_char
id|address
op_assign
id|client-&gt;address
comma
id|status
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;i2c_bussel_reg
op_ne
l_int|NULL
)paren
id|writeb
c_func
(paren
id|client-&gt;bus
comma
id|bp-&gt;i2c_bussel_reg
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|address
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_START
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
)paren
r_goto
id|out
suffix:semicolon
id|writeb
c_func
(paren
id|off
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
op_logical_or
(paren
id|status
op_amp
id|I2C_PCF_LRB
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_STOP
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
id|address
op_or_assign
l_int|0x1
suffix:semicolon
multiline_comment|/* READ */
id|writeb
c_func
(paren
id|address
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_START
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Set PIN back to one so the device sends the first&n;&t; * byte.&n;&t; */
(paren
r_void
)paren
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
)paren
r_goto
id|out
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_ESO
op_or
id|I2C_PCF_ENI
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
op_star
id|byte
op_assign
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_pin
c_func
(paren
id|bp
comma
op_amp
id|status
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|writeb
c_func
(paren
id|I2C_PCF_STOP
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
(paren
r_void
)paren
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|bbc_i2c_write_buf
r_int
id|bbc_i2c_write_buf
c_func
(paren
r_struct
id|bbc_i2c_client
op_star
id|client
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|off
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|err
op_assign
id|bbc_i2c_writeb
c_func
(paren
id|client
comma
op_star
id|buf
comma
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|err
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_decrement
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|off
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|bbc_i2c_read_buf
r_int
id|bbc_i2c_read_buf
c_func
(paren
r_struct
id|bbc_i2c_client
op_star
id|client
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|off
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|err
op_assign
id|bbc_i2c_readb
c_func
(paren
id|client
comma
id|buf
comma
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|err
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_decrement
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|off
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|bbc_i2c_getdev
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_getdev
)paren
suffix:semicolon
DECL|variable|bbc_i2c_attach
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_attach
)paren
suffix:semicolon
DECL|variable|bbc_i2c_detach
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_detach
)paren
suffix:semicolon
DECL|variable|bbc_i2c_writeb
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_writeb
)paren
suffix:semicolon
DECL|variable|bbc_i2c_readb
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_readb
)paren
suffix:semicolon
DECL|variable|bbc_i2c_write_buf
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_write_buf
)paren
suffix:semicolon
DECL|variable|bbc_i2c_read_buf
id|EXPORT_SYMBOL
c_func
(paren
id|bbc_i2c_read_buf
)paren
suffix:semicolon
DECL|function|bbc_i2c_interrupt
r_static
id|irqreturn_t
id|bbc_i2c_interrupt
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
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|dev_id
suffix:semicolon
multiline_comment|/* PIN going from set to clear is the only event which&n;&t; * makes the i2c assert an interrupt.&n;&t; */
r_if
c_cond
(paren
id|bp-&gt;waiting
op_logical_and
op_logical_neg
(paren
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
op_amp
id|I2C_PCF_PIN
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|bp-&gt;wq
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|reset_one_i2c
r_static
r_void
id|__init
id|reset_one_i2c
c_func
(paren
r_struct
id|bbc_i2c_bus
op_star
id|bp
)paren
(brace
id|writeb
c_func
(paren
id|I2C_PCF_PIN
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|bp-&gt;own
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_PIN
op_or
id|I2C_PCF_ES1
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|bp-&gt;clock
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x1
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_IDLE
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
)brace
DECL|function|attach_one_i2c
r_static
r_int
id|__init
id|attach_one_i2c
c_func
(paren
r_struct
id|linux_ebus_device
op_star
id|edev
comma
r_int
id|index
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|bp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|linux_ebus_child
op_star
id|echild
suffix:semicolon
r_int
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|bp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|bp
)paren
)paren
suffix:semicolon
id|bp-&gt;i2c_control_regs
op_assign
id|ioremap
c_func
(paren
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
l_int|0x2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp-&gt;i2c_control_regs
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|edev-&gt;num_addrs
op_eq
l_int|2
)paren
(brace
id|bp-&gt;i2c_bussel_reg
op_assign
id|ioremap
c_func
(paren
id|edev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
comma
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp-&gt;i2c_bussel_reg
)paren
r_goto
id|fail
suffix:semicolon
)brace
id|bp-&gt;waiting
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|bp-&gt;wq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|edev-&gt;irqs
(braket
l_int|0
)braket
comma
id|bbc_i2c_interrupt
comma
id|SA_SHIRQ
comma
l_string|&quot;bbc_i2c&quot;
comma
id|bp
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|bp-&gt;index
op_assign
id|index
suffix:semicolon
id|bp-&gt;bus_edev
op_assign
id|edev
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|bp-&gt;lock
)paren
suffix:semicolon
id|bp-&gt;next
op_assign
id|all_bbc_i2c
suffix:semicolon
id|all_bbc_i2c
op_assign
id|bp
suffix:semicolon
id|entry
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|echild
op_assign
id|edev-&gt;children
suffix:semicolon
id|echild
op_logical_and
id|entry
OL
l_int|8
suffix:semicolon
id|echild
op_assign
id|echild-&gt;next
comma
id|entry
op_increment
)paren
(brace
id|bp-&gt;devs
(braket
id|entry
)braket
dot
id|device
op_assign
id|echild
suffix:semicolon
id|bp-&gt;devs
(braket
id|entry
)braket
dot
id|client_claimed
op_assign
l_int|0
suffix:semicolon
)brace
id|writeb
c_func
(paren
id|I2C_PCF_PIN
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
id|bp-&gt;own
op_assign
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x01
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|I2C_PCF_PIN
op_or
id|I2C_PCF_ES1
comma
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x0
)paren
suffix:semicolon
id|bp-&gt;clock
op_assign
id|readb
c_func
(paren
id|bp-&gt;i2c_control_regs
op_plus
l_int|0x01
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-%d: Regs at %p, %d devices, own %02x, clock %02x.&bslash;n&quot;
comma
id|bp-&gt;index
comma
id|bp-&gt;i2c_control_regs
comma
id|entry
comma
id|bp-&gt;own
comma
id|bp-&gt;clock
)paren
suffix:semicolon
id|reset_one_i2c
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|bp-&gt;i2c_bussel_reg
)paren
id|iounmap
c_func
(paren
id|bp-&gt;i2c_bussel_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;i2c_control_regs
)paren
id|iounmap
c_func
(paren
id|bp-&gt;i2c_control_regs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|bbc_present
r_static
r_int
id|__init
id|bbc_present
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_ebus
op_star
id|ebus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|NULL
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
l_string|&quot;bbc&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|bbc_envctrl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|bbc_envctrl_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|bbc_i2c_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|bbc_i2c_init
r_static
r_int
id|__init
id|bbc_i2c_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_ebus
op_star
id|ebus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
comma
id|index
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tlb_type
op_ne
id|cheetah
op_logical_or
op_logical_neg
id|bbc_present
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
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
l_string|&quot;i2c&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|attach_one_i2c
c_func
(paren
id|edev
comma
id|index
)paren
)paren
id|index
op_increment
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|index
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|err
op_assign
id|bbc_envctrl_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|bbc_i2c_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bbc_i2c_cleanup
r_static
r_void
id|bbc_i2c_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|bp
op_assign
id|all_bbc_i2c
suffix:semicolon
id|bbc_envctrl_cleanup
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bp
op_ne
l_int|NULL
)paren
(brace
r_struct
id|bbc_i2c_bus
op_star
id|next
op_assign
id|bp-&gt;next
suffix:semicolon
id|free_irq
c_func
(paren
id|bp-&gt;bus_edev-&gt;irqs
(braket
l_int|0
)braket
comma
id|bp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;i2c_bussel_reg
)paren
id|iounmap
c_func
(paren
id|bp-&gt;i2c_bussel_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp-&gt;i2c_control_regs
)paren
id|iounmap
c_func
(paren
id|bp-&gt;i2c_control_regs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bp
)paren
suffix:semicolon
id|bp
op_assign
id|next
suffix:semicolon
)brace
id|all_bbc_i2c
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|bbc_i2c_init
id|module_init
c_func
(paren
id|bbc_i2c_init
)paren
suffix:semicolon
DECL|variable|bbc_i2c_cleanup
id|module_exit
c_func
(paren
id|bbc_i2c_cleanup
)paren
suffix:semicolon
eof
