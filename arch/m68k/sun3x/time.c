multiline_comment|/*&n; *  linux/arch/m68k/sun3x/time.c&n; *&n; *  Sun3x-specific time handling&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/sun3x.h&gt;
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
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) (((val)&amp;15) + ((val)&gt;&gt;4)*10)
multiline_comment|/* Read the Mostek */
DECL|function|sun3x_gettod
r_void
id|sun3x_gettod
(paren
r_int
op_star
id|yearp
comma
r_int
op_star
id|monp
comma
r_int
op_star
id|dayp
comma
r_int
op_star
id|hourp
comma
r_int
op_star
id|minp
comma
r_int
op_star
id|secp
)paren
(brace
r_volatile
r_int
r_char
op_star
id|eeprom
op_assign
(paren
r_int
r_char
op_star
)paren
id|SUN3X_EEPROM
suffix:semicolon
multiline_comment|/* Stop updates */
op_star
(paren
id|eeprom
op_plus
id|M_CONTROL
)paren
op_or_assign
id|C_READ
suffix:semicolon
multiline_comment|/* Read values */
op_star
id|yearp
op_assign
id|BCD_TO_BIN
c_func
(paren
op_star
(paren
id|eeprom
op_plus
id|M_YEAR
)paren
)paren
suffix:semicolon
op_star
id|monp
op_assign
id|BCD_TO_BIN
c_func
(paren
op_star
(paren
id|eeprom
op_plus
id|M_MONTH
)paren
)paren
suffix:semicolon
op_star
id|dayp
op_assign
id|BCD_TO_BIN
c_func
(paren
op_star
(paren
id|eeprom
op_plus
id|M_DATE
)paren
)paren
suffix:semicolon
op_star
id|hourp
op_assign
id|BCD_TO_BIN
c_func
(paren
op_star
(paren
id|eeprom
op_plus
id|M_HOUR
)paren
)paren
suffix:semicolon
op_star
id|minp
op_assign
id|BCD_TO_BIN
c_func
(paren
op_star
(paren
id|eeprom
op_plus
id|M_MIN
)paren
)paren
suffix:semicolon
op_star
id|secp
op_assign
id|BCD_TO_BIN
c_func
(paren
op_star
(paren
id|eeprom
op_plus
id|M_SEC
)paren
)paren
suffix:semicolon
multiline_comment|/* Restart updates */
op_star
(paren
id|eeprom
op_plus
id|M_CONTROL
)paren
op_and_assign
op_complement
id|C_READ
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
DECL|function|sun3x_timer_tick
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
DECL|function|sun3x_sched_init
r_void
id|__init
id|sun3x_sched_init
c_func
(paren
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
)paren
(brace
id|sys_request_irq
c_func
(paren
l_int|5
comma
id|sun3x_timer_tick
comma
id|IRQ_FLG_STD
comma
l_string|&quot;timer tick&quot;
comma
id|vector
)paren
suffix:semicolon
multiline_comment|/* Pulse enable low to get the clock started */
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
)brace
eof
