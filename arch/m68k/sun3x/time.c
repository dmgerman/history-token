multiline_comment|/*&n; *  linux/arch/m68k/sun3x/time.c&n; *&n; *  Sun3x-specific time handling&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/sun3x.h&gt;
macro_line|#include &lt;asm/sun3ints.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &quot;time.h&quot;
DECL|macro|M_CONTROL
mdefine_line|#define M_CONTROL 0xf8
DECL|macro|M_SEC
mdefine_line|#define M_SEC     0xf9
DECL|macro|M_MIN
mdefine_line|#define M_MIN     0xfa
DECL|macro|M_HOUR
mdefine_line|#define M_HOUR    0xfb
DECL|macro|M_DAY
mdefine_line|#define M_DAY     0xfc
DECL|macro|M_DATE
mdefine_line|#define M_DATE    0xfd
DECL|macro|M_MONTH
mdefine_line|#define M_MONTH   0xfe
DECL|macro|M_YEAR
mdefine_line|#define M_YEAR    0xff
DECL|macro|C_WRITE
mdefine_line|#define C_WRITE   0x80
DECL|macro|C_READ
mdefine_line|#define C_READ    0x40
DECL|macro|C_SIGN
mdefine_line|#define C_SIGN    0x20
DECL|macro|C_CALIB
mdefine_line|#define C_CALIB   0x1f
DECL|function|sun3x_hwclk
r_int
id|sun3x_hwclk
c_func
(paren
r_int
id|set
comma
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
r_volatile
r_struct
id|mostek_dt
op_star
id|h
op_assign
(paren
r_struct
id|mostek_dt
op_star
)paren
(paren
id|SUN3X_EEPROM
op_plus
id|M_CONTROL
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
)paren
(brace
id|h-&gt;csr
op_or_assign
id|C_WRITE
suffix:semicolon
id|h-&gt;sec
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_sec
)paren
suffix:semicolon
id|h-&gt;min
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_min
)paren
suffix:semicolon
id|h-&gt;hour
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_hour
)paren
suffix:semicolon
id|h-&gt;wday
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_wday
)paren
suffix:semicolon
id|h-&gt;mday
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_mday
)paren
suffix:semicolon
id|h-&gt;month
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_mon
)paren
suffix:semicolon
id|h-&gt;year
op_assign
id|BIN2BCD
c_func
(paren
id|t-&gt;tm_year
)paren
suffix:semicolon
id|h-&gt;csr
op_and_assign
op_complement
id|C_WRITE
suffix:semicolon
)brace
r_else
(brace
id|h-&gt;csr
op_or_assign
id|C_READ
suffix:semicolon
id|t-&gt;tm_sec
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;sec
)paren
suffix:semicolon
id|t-&gt;tm_min
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;min
)paren
suffix:semicolon
id|t-&gt;tm_hour
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;hour
)paren
suffix:semicolon
id|t-&gt;tm_wday
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;wday
)paren
suffix:semicolon
id|t-&gt;tm_mday
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;mday
)paren
suffix:semicolon
id|t-&gt;tm_mon
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;month
)paren
suffix:semicolon
id|t-&gt;tm_year
op_assign
id|BCD2BIN
c_func
(paren
id|h-&gt;year
)paren
suffix:semicolon
id|h-&gt;csr
op_and_assign
op_complement
id|C_READ
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Not much we can do here */
DECL|function|sun3x_gettimeoffset
r_int
r_int
id|sun3x_gettimeoffset
(paren
r_void
)paren
(brace
r_return
l_int|0L
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|sun3x_timer_tick
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
r_void
(paren
op_star
id|vector
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
id|dev_id
suffix:semicolon
multiline_comment|/* Clear the pending interrupt - pulse the enable line low */
id|disable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|vector
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sun3x_sched_init
r_void
id|__init
id|sun3x_sched_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|vector
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
id|sun3_disable_interrupts
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Pulse enable low to get the clock started */
id|sun3_disable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|sun3_enable_irq
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|sun3_enable_interrupts
c_func
(paren
)paren
suffix:semicolon
)brace
eof
