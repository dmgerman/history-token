multiline_comment|/*&n; * (C) Copyright 2003-2004&n; * Humboldt Solutions Ltd, adrian@humboldt.co.uk.&n; &n; * This is a combined i2c adapter and algorithm driver for the&n; * MPC107/Tsi107 PowerPC northbridge and processors that include&n; * the same I2C unit (8240, 8245, 85xx). &n; *&n; * Release 0.7&n; *&n; * This file is licensed under the terms of the GNU General Public&n; * License version 2. This program is licensed &quot;as is&quot; without any&n; * warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|MPC_I2C_ADDR
mdefine_line|#define MPC_I2C_ADDR  0x00
DECL|macro|MPC_I2C_FDR
mdefine_line|#define MPC_I2C_FDR &t;0x04
DECL|macro|MPC_I2C_CR
mdefine_line|#define MPC_I2C_CR&t;0x08
DECL|macro|MPC_I2C_SR
mdefine_line|#define MPC_I2C_SR&t;0x0c
DECL|macro|MPC_I2C_DR
mdefine_line|#define MPC_I2C_DR&t;0x10
DECL|macro|MPC_I2C_DFSRR
mdefine_line|#define MPC_I2C_DFSRR 0x14
DECL|macro|MPC_I2C_REGION
mdefine_line|#define MPC_I2C_REGION 0x20
DECL|macro|CCR_MEN
mdefine_line|#define CCR_MEN  0x80
DECL|macro|CCR_MIEN
mdefine_line|#define CCR_MIEN 0x40
DECL|macro|CCR_MSTA
mdefine_line|#define CCR_MSTA 0x20
DECL|macro|CCR_MTX
mdefine_line|#define CCR_MTX  0x10
DECL|macro|CCR_TXAK
mdefine_line|#define CCR_TXAK 0x08
DECL|macro|CCR_RSTA
mdefine_line|#define CCR_RSTA 0x04
DECL|macro|CSR_MCF
mdefine_line|#define CSR_MCF  0x80
DECL|macro|CSR_MAAS
mdefine_line|#define CSR_MAAS 0x40
DECL|macro|CSR_MBB
mdefine_line|#define CSR_MBB  0x20
DECL|macro|CSR_MAL
mdefine_line|#define CSR_MAL  0x10
DECL|macro|CSR_SRW
mdefine_line|#define CSR_SRW  0x04
DECL|macro|CSR_MIF
mdefine_line|#define CSR_MIF  0x02
DECL|macro|CSR_RXAK
mdefine_line|#define CSR_RXAK 0x01
DECL|struct|mpc_i2c
r_struct
id|mpc_i2c
(brace
DECL|member|base
r_char
op_star
id|base
suffix:semicolon
DECL|member|ocpdef
r_struct
id|ocp_def
op_star
id|ocpdef
suffix:semicolon
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
DECL|member|queue
id|wait_queue_head_t
id|queue
suffix:semicolon
DECL|member|adap
r_struct
id|i2c_adapter
id|adap
suffix:semicolon
)brace
suffix:semicolon
DECL|function|writeccr
r_static
id|__inline__
r_void
id|writeccr
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
comma
id|u32
id|x
)paren
(brace
id|writeb
c_func
(paren
id|x
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_CR
)paren
suffix:semicolon
)brace
DECL|function|mpc_i2c_isr
r_static
id|irqreturn_t
id|mpc_i2c_isr
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
id|mpc_i2c
op_star
id|i2c
op_assign
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
op_amp
id|CSR_MIF
)paren
(brace
multiline_comment|/* Read again to allow register to stabilise */
id|i2c-&gt;interrupt
op_assign
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|i2c-&gt;queue
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|i2c_wait
r_static
r_int
id|i2c_wait
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
comma
r_int
id|timeout
comma
r_int
id|writing
)paren
(brace
r_int
r_int
id|orig_jiffies
op_assign
id|jiffies
suffix:semicolon
id|u32
id|x
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i2c-&gt;ocpdef-&gt;irq
op_eq
id|OCP_IRQ_NA
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
op_amp
id|CSR_MIF
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|orig_jiffies
op_plus
id|timeout
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: timeout&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|x
op_assign
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Interrupt mode */
id|result
op_assign
id|wait_event_interruptible_timeout
c_func
(paren
id|i2c-&gt;queue
comma
(paren
id|i2c-&gt;interrupt
op_amp
id|CSR_MIF
)paren
comma
id|timeout
op_star
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|result
OL
l_int|0
)paren
)paren
id|pr_debug
c_func
(paren
l_string|&quot;I2C: wait interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
(paren
id|i2c-&gt;interrupt
op_amp
id|CSR_MIF
)paren
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: wait timeout&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
id|x
op_assign
id|i2c-&gt;interrupt
suffix:semicolon
id|i2c-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
id|CSR_MCF
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: unfinished&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x
op_amp
id|CSR_MAL
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: MAL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|writing
op_logical_and
(paren
id|x
op_amp
id|CSR_RXAK
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: No RXAK&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* generate stop */
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MEN
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mpc_i2c_setclock
r_static
r_void
id|mpc_i2c_setclock
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
)paren
(brace
r_struct
id|ocp_fs_i2c_data
op_star
id|i2c_data
op_assign
id|i2c-&gt;ocpdef-&gt;additions
suffix:semicolon
multiline_comment|/* Set clock and filters */
r_if
c_cond
(paren
id|i2c_data
op_logical_and
(paren
id|i2c_data-&gt;flags
op_amp
id|FS_I2C_SEPARATE_DFSRR
)paren
)paren
(brace
id|writeb
c_func
(paren
l_int|0x31
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_FDR
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x10
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_DFSRR
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i2c_data
op_logical_and
(paren
id|i2c_data-&gt;flags
op_amp
id|FS_I2C_CLOCK_5200
)paren
)paren
id|writeb
c_func
(paren
l_int|0x3f
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_FDR
)paren
suffix:semicolon
r_else
id|writel
c_func
(paren
l_int|0x1031
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_FDR
)paren
suffix:semicolon
)brace
DECL|function|mpc_i2c_start
r_static
r_void
id|mpc_i2c_start
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
)paren
(brace
multiline_comment|/* Clear arbitration */
id|writeb
c_func
(paren
l_int|0
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
suffix:semicolon
multiline_comment|/* Start with MEN */
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MEN
)paren
suffix:semicolon
)brace
DECL|function|mpc_i2c_stop
r_static
r_void
id|mpc_i2c_stop
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
)paren
(brace
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MEN
)paren
suffix:semicolon
)brace
DECL|function|mpc_write
r_static
r_int
id|mpc_write
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
comma
r_int
id|target
comma
r_const
id|u8
op_star
id|data
comma
r_int
id|length
comma
r_int
id|restart
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|timeout
op_assign
id|i2c-&gt;adap.timeout
suffix:semicolon
id|u32
id|flags
op_assign
id|restart
ques
c_cond
id|CCR_RSTA
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Start with MEN */
r_if
c_cond
(paren
op_logical_neg
id|restart
)paren
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MEN
)paren
suffix:semicolon
multiline_comment|/* Start as master */
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MIEN
op_or
id|CCR_MEN
op_or
id|CCR_MSTA
op_or
id|CCR_MTX
op_or
id|flags
)paren
suffix:semicolon
multiline_comment|/* Write target byte */
id|writeb
c_func
(paren
(paren
id|target
op_lshift
l_int|1
)paren
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_DR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_wait
c_func
(paren
id|i2c
comma
id|timeout
comma
l_int|1
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
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
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Write data byte */
id|writeb
c_func
(paren
id|data
(braket
id|i
)braket
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_DR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_wait
c_func
(paren
id|i2c
comma
id|timeout
comma
l_int|1
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mpc_read
r_static
r_int
id|mpc_read
c_func
(paren
r_struct
id|mpc_i2c
op_star
id|i2c
comma
r_int
id|target
comma
id|u8
op_star
id|data
comma
r_int
id|length
comma
r_int
id|restart
)paren
(brace
r_int
id|timeout
op_assign
id|i2c-&gt;adap.timeout
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u32
id|flags
op_assign
id|restart
ques
c_cond
id|CCR_RSTA
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Start with MEN */
r_if
c_cond
(paren
op_logical_neg
id|restart
)paren
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MEN
)paren
suffix:semicolon
multiline_comment|/* Switch to read - restart */
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MIEN
op_or
id|CCR_MEN
op_or
id|CCR_MSTA
op_or
id|CCR_MTX
op_or
id|flags
)paren
suffix:semicolon
multiline_comment|/* Write target address byte - this time with the read flag set */
id|writeb
c_func
(paren
(paren
id|target
op_lshift
l_int|1
)paren
op_or
l_int|1
comma
id|i2c-&gt;base
op_plus
id|MPC_I2C_DR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_wait
c_func
(paren
id|i2c
comma
id|timeout
comma
l_int|1
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|length
)paren
(brace
r_if
c_cond
(paren
id|length
op_eq
l_int|1
)paren
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MIEN
op_or
id|CCR_MEN
op_or
id|CCR_MSTA
op_or
id|CCR_TXAK
)paren
suffix:semicolon
r_else
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MIEN
op_or
id|CCR_MEN
op_or
id|CCR_MSTA
)paren
suffix:semicolon
multiline_comment|/* Dummy read */
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_DR
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i2c_wait
c_func
(paren
id|i2c
comma
id|timeout
comma
l_int|0
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Generate txack on next to last byte */
r_if
c_cond
(paren
id|i
op_eq
id|length
op_minus
l_int|2
)paren
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MIEN
op_or
id|CCR_MEN
op_or
id|CCR_MSTA
op_or
id|CCR_TXAK
)paren
suffix:semicolon
multiline_comment|/* Generate stop on last byte */
r_if
c_cond
(paren
id|i
op_eq
id|length
op_minus
l_int|1
)paren
id|writeccr
c_func
(paren
id|i2c
comma
id|CCR_MIEN
op_or
id|CCR_MEN
op_or
id|CCR_TXAK
)paren
suffix:semicolon
id|data
(braket
id|i
)braket
op_assign
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_DR
)paren
suffix:semicolon
)brace
r_return
id|length
suffix:semicolon
)brace
DECL|function|mpc_xfer
r_static
r_int
id|mpc_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
)paren
(brace
r_struct
id|i2c_msg
op_star
id|pmsg
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|orig_jiffies
op_assign
id|jiffies
suffix:semicolon
r_struct
id|mpc_i2c
op_star
id|i2c
op_assign
id|i2c_get_adapdata
c_func
(paren
id|adap
)paren
suffix:semicolon
id|mpc_i2c_start
c_func
(paren
id|i2c
)paren
suffix:semicolon
multiline_comment|/* Allow bus up to 1s to become not busy */
r_while
c_loop
(paren
id|readb
c_func
(paren
id|i2c-&gt;base
op_plus
id|MPC_I2C_SR
)paren
op_amp
id|CSR_MBB
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: Interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|orig_jiffies
op_plus
id|HZ
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I2C: timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|ret
op_ge
l_int|0
op_logical_and
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pmsg
op_assign
op_amp
id|msgs
(braket
id|i
)braket
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Doing %s %d bytes to 0x%02x - %d of %d messages&bslash;n&quot;
comma
id|pmsg-&gt;flags
op_amp
id|I2C_M_RD
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|pmsg-&gt;len
comma
id|pmsg-&gt;addr
comma
id|i
op_plus
l_int|1
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmsg-&gt;flags
op_amp
id|I2C_M_RD
)paren
id|ret
op_assign
id|mpc_read
c_func
(paren
id|i2c
comma
id|pmsg-&gt;addr
comma
id|pmsg-&gt;buf
comma
id|pmsg-&gt;len
comma
id|i
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|mpc_write
c_func
(paren
id|i2c
comma
id|pmsg-&gt;addr
comma
id|pmsg-&gt;buf
comma
id|pmsg-&gt;len
comma
id|i
)paren
suffix:semicolon
)brace
id|mpc_i2c_stop
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
(paren
id|ret
OL
l_int|0
)paren
ques
c_cond
id|ret
suffix:colon
id|num
suffix:semicolon
)brace
DECL|function|mpc_functionality
r_static
id|u32
id|mpc_functionality
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|I2C_FUNC_I2C
op_or
id|I2C_FUNC_SMBUS_EMUL
suffix:semicolon
)brace
DECL|variable|mpc_algo
r_static
r_struct
id|i2c_algorithm
id|mpc_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MPC algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_MPC107
comma
dot
id|master_xfer
op_assign
id|mpc_xfer
comma
dot
id|functionality
op_assign
id|mpc_functionality
comma
)brace
suffix:semicolon
DECL|variable|mpc_ops
r_static
r_struct
id|i2c_adapter
id|mpc_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;MPC adapter&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_MPC107
op_or
id|I2C_HW_MPC107
comma
dot
id|algo
op_assign
op_amp
id|mpc_algo
comma
dot
r_class
op_assign
id|I2C_CLASS_HWMON
comma
dot
id|timeout
op_assign
l_int|1
comma
dot
id|retries
op_assign
l_int|1
)brace
suffix:semicolon
DECL|function|mpc_i2c_probe
r_static
r_int
id|__devinit
id|mpc_i2c_probe
c_func
(paren
r_struct
id|ocp_device
op_star
id|ocp
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|mpc_i2c
op_star
id|i2c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i2c
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|i2c
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|i2c
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|i2c
)paren
)paren
suffix:semicolon
id|i2c-&gt;ocpdef
op_assign
id|ocp-&gt;def
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|i2c-&gt;queue
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|ocp-&gt;def-&gt;paddr
comma
id|MPC_I2C_REGION
comma
l_string|&quot;i2c-mpc&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-mpc - resource unavailable&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|i2c-&gt;base
op_assign
id|ioremap
c_func
(paren
id|ocp-&gt;def-&gt;paddr
comma
id|MPC_I2C_REGION
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c-&gt;base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-mpc - failed to map controller&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|fail_map
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ocp-&gt;def-&gt;irq
op_ne
id|OCP_IRQ_NA
)paren
r_if
c_cond
(paren
(paren
id|result
op_assign
id|request_irq
c_func
(paren
id|ocp-&gt;def-&gt;irq
comma
id|mpc_i2c_isr
comma
l_int|0
comma
l_string|&quot;i2c-mpc&quot;
comma
id|i2c
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-mpc - failed to attach interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_irq
suffix:semicolon
)brace
id|i2c-&gt;adap
op_assign
id|mpc_ops
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|i2c-&gt;adap
comma
id|i2c
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|i2c-&gt;adap
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-mpc - failed to add adapter&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_add
suffix:semicolon
)brace
id|mpc_i2c_setclock
c_func
(paren
id|i2c
)paren
suffix:semicolon
id|ocp_set_drvdata
c_func
(paren
id|ocp
comma
id|i2c
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
id|fail_add
suffix:colon
r_if
c_cond
(paren
id|ocp-&gt;def-&gt;irq
op_ne
id|OCP_IRQ_NA
)paren
id|free_irq
c_func
(paren
id|ocp-&gt;def-&gt;irq
comma
l_int|0
)paren
suffix:semicolon
id|fail_irq
suffix:colon
id|iounmap
c_func
(paren
id|i2c-&gt;base
)paren
suffix:semicolon
id|fail_map
suffix:colon
id|release_mem_region
c_func
(paren
id|ocp-&gt;def-&gt;paddr
comma
id|MPC_I2C_REGION
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|mpc_i2c_remove
r_static
r_void
id|__devexit
id|mpc_i2c_remove
c_func
(paren
r_struct
id|ocp_device
op_star
id|ocp
)paren
(brace
r_struct
id|mpc_i2c
op_star
id|i2c
op_assign
id|ocp_get_drvdata
c_func
(paren
id|ocp
)paren
suffix:semicolon
id|ocp_set_drvdata
c_func
(paren
id|ocp
comma
l_int|NULL
)paren
suffix:semicolon
id|i2c_del_adapter
c_func
(paren
op_amp
id|i2c-&gt;adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ocp-&gt;def-&gt;irq
op_ne
id|OCP_IRQ_NA
)paren
id|free_irq
c_func
(paren
id|i2c-&gt;ocpdef-&gt;irq
comma
id|i2c
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|i2c-&gt;base
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|i2c-&gt;ocpdef-&gt;paddr
comma
id|MPC_I2C_REGION
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i2c
)paren
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|ocp_device_id
id|mpc_iic_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_FREESCALE
comma
dot
id|function
op_assign
id|OCP_FUNC_IIC
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|ocp
comma
id|mpc_iic_ids
)paren
suffix:semicolon
DECL|variable|mpc_iic_driver
r_static
r_struct
id|ocp_driver
id|mpc_iic_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;iic&quot;
comma
dot
id|id_table
op_assign
id|mpc_iic_ids
comma
dot
id|probe
op_assign
id|mpc_i2c_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|mpc_i2c_remove
)paren
)brace
suffix:semicolon
DECL|function|iic_init
r_static
r_int
id|__init
id|iic_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ocp_register_driver
c_func
(paren
op_amp
id|mpc_iic_driver
)paren
suffix:semicolon
)brace
DECL|function|iic_exit
r_static
r_void
id|__exit
id|iic_exit
c_func
(paren
r_void
)paren
(brace
id|ocp_unregister_driver
c_func
(paren
op_amp
id|mpc_iic_driver
)paren
suffix:semicolon
)brace
DECL|variable|iic_init
id|module_init
c_func
(paren
id|iic_init
)paren
suffix:semicolon
DECL|variable|iic_exit
id|module_exit
c_func
(paren
id|iic_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Adrian Cox &lt;adrian@humboldt.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;I2C-Bus adapter for MPC107 bridge and MPC824x/85xx/52xx processors&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
