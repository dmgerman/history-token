multiline_comment|/*&n; * IR port driver for the Cirrus Logic EP7211 processor.&n; *&n; * Copyright 2001, Blue Mug Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
DECL|macro|MIN_DELAY
mdefine_line|#define MIN_DELAY 25      /* 15 us, but wait a little more to be sure */
DECL|macro|MAX_DELAY
mdefine_line|#define MAX_DELAY 10000   /* 1 ms */
r_static
r_void
id|ep7211_ir_open
c_func
(paren
id|dongle_t
op_star
id|self
comma
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
r_static
r_void
id|ep7211_ir_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
suffix:semicolon
r_static
r_int
id|ep7211_ir_change_speed
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
r_static
r_int
id|ep7211_ir_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
DECL|variable|dongle
r_static
r_struct
id|dongle_reg
id|dongle
op_assign
(brace
id|Q_NULL
comma
id|IRDA_EP7211_IR
comma
id|ep7211_ir_open
comma
id|ep7211_ir_close
comma
id|ep7211_ir_reset
comma
id|ep7211_ir_change_speed
comma
)brace
suffix:semicolon
DECL|function|ep7211_ir_open
r_static
r_void
id|ep7211_ir_open
c_func
(paren
id|dongle_t
op_star
id|self
comma
r_struct
id|qos_info
op_star
id|qos
)paren
(brace
r_int
r_int
id|syscon1
comma
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn on the SIR encoder. */
id|syscon1
op_assign
id|clps_readl
c_func
(paren
id|SYSCON1
)paren
suffix:semicolon
id|syscon1
op_or_assign
id|SYSCON1_SIREN
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon1
comma
id|SYSCON1
)paren
suffix:semicolon
multiline_comment|/* XXX: We should disable modem status interrupts on the first&n;&t;&t;UART (interrupt #14). */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|ep7211_ir_close
r_static
r_void
id|ep7211_ir_close
c_func
(paren
id|dongle_t
op_star
id|self
)paren
(brace
r_int
r_int
id|syscon1
comma
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn off the SIR encoder. */
id|syscon1
op_assign
id|clps_readl
c_func
(paren
id|SYSCON1
)paren
suffix:semicolon
id|syscon1
op_and_assign
op_complement
id|SYSCON1_SIREN
suffix:semicolon
id|clps_writel
c_func
(paren
id|syscon1
comma
id|SYSCON1
)paren
suffix:semicolon
multiline_comment|/* XXX: If we&squot;ve disabled the modem status interrupts, we should&n;&t;&t;reset them back to their original state. */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ep7211_ir_change_speed (task)&n; *&n; *    Change speed of the EP7211 I/R port. We don&squot;t really have to do anything&n; *    for the EP7211 as long as the rate is being changed at the serial port&n; *    level.&n; */
DECL|function|ep7211_ir_change_speed
r_static
r_int
id|ep7211_ir_change_speed
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ep7211_ir_reset (task)&n; *&n; *      Reset the EP7211 I/R. We don&squot;t really have to do anything.&n; *&n; */
DECL|function|ep7211_ir_reset
r_static
r_int
id|ep7211_ir_reset
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
id|irda_task_next_state
c_func
(paren
id|task
comma
id|IRDA_TASK_DONE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ep7211_ir_init(void)&n; *&n; *    Initialize EP7211 I/R module&n; *&n; */
DECL|function|ep7211_ir_init
r_int
id|__init
id|ep7211_ir_init
c_func
(paren
r_void
)paren
(brace
r_return
id|irda_device_register_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ep7211_ir_cleanup(void)&n; *&n; *    Cleanup EP7211 I/R module&n; *&n; */
DECL|function|ep7211_ir_cleanup
r_static
r_void
id|__exit
id|ep7211_ir_cleanup
c_func
(paren
r_void
)paren
(brace
id|irda_device_unregister_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jon McClintock &lt;jonm@bluemug.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;EP7211 I/R driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ep7211_ir_init
id|module_init
c_func
(paren
id|ep7211_ir_init
)paren
suffix:semicolon
DECL|variable|ep7211_ir_cleanup
id|module_exit
c_func
(paren
id|ep7211_ir_cleanup
)paren
suffix:semicolon
eof
