multiline_comment|/*&n; * arch/ppc/boot/simple/mpc52xx_tty.c&n; *&n; * Minimal serial functions needed to send messages out a MPC52xx&n; * Programmable Serial Controller (PSC).&n; *&n; * Author: Dale Farnsworth &lt;dfarnsworth@mvista.com&gt;&n; *&n; * 2003-2004 (c) MontaVista, Software, Inc.  This file is licensed under the&n; * terms of the GNU General Public License version 2.  This program is licensed&n; * &quot;as is&quot; without any warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mpc52xx.h&gt;
macro_line|#include &lt;asm/mpc52xx_psc.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#if MPC52xx_PF_CONSOLE_PORT == 0
DECL|macro|MPC52xx_CONSOLE
mdefine_line|#define MPC52xx_CONSOLE&t;&t;MPC52xx_PSC1
DECL|macro|MPC52xx_PSC_CONFIG_SHIFT
mdefine_line|#define MPC52xx_PSC_CONFIG_SHIFT&t;0
macro_line|#elif MPC52xx_PF_CONSOLE_PORT == 1
DECL|macro|MPC52xx_CONSOLE
mdefine_line|#define MPC52xx_CONSOLE&t;&t;MPC52xx_PSC2
DECL|macro|MPC52xx_PSC_CONFIG_SHIFT
mdefine_line|#define MPC52xx_PSC_CONFIG_SHIFT&t;4
macro_line|#elif MPC52xx_PF_CONSOLE_PORT == 2
DECL|macro|MPC52xx_CONSOLE
mdefine_line|#define MPC52xx_CONSOLE&t;&t;MPC52xx_PSC3
DECL|macro|MPC52xx_PSC_CONFIG_SHIFT
mdefine_line|#define MPC52xx_PSC_CONFIG_SHIFT&t;8
macro_line|#else
macro_line|#error &quot;MPC52xx_PF_CONSOLE_PORT not defined&quot;
macro_line|#endif
DECL|variable|psc
r_static
r_struct
id|mpc52xx_psc
id|__iomem
op_star
id|psc
op_assign
(paren
r_struct
id|mpc52xx_psc
id|__iomem
op_star
)paren
id|MPC52xx_CONSOLE
suffix:semicolon
multiline_comment|/* The decrementer counts at the system bus clock frequency&n; * divided by four.  The most accurate time base is connected to the&n; * rtc.  We read the decrementer change during one rtc tick (one second)&n; * and multiply by 4 to get the system bus clock frequency.&n; */
r_static
r_int
DECL|function|mpc52xx_ipbfreq
id|mpc52xx_ipbfreq
c_func
(paren
r_void
)paren
(brace
r_struct
id|mpc52xx_rtc
id|__iomem
op_star
id|rtc
op_assign
(paren
r_struct
id|mpc52xx_rtc
id|__iomem
op_star
)paren
id|MPC52xx_RTC
suffix:semicolon
r_struct
id|mpc52xx_cdm
id|__iomem
op_star
id|cdm
op_assign
(paren
r_struct
id|mpc52xx_cdm
id|__iomem
op_star
)paren
id|MPC52xx_CDM
suffix:semicolon
r_int
id|current_time
comma
id|previous_time
suffix:semicolon
r_int
id|tbl_start
comma
id|tbl_end
suffix:semicolon
r_int
id|xlbfreq
comma
id|ipbfreq
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|rtc-&gt;dividers
comma
l_int|0x8f1f0000
)paren
suffix:semicolon
multiline_comment|/* Set RTC 64x faster */
id|previous_time
op_assign
id|in_be32
c_func
(paren
op_amp
id|rtc-&gt;time
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|current_time
op_assign
id|in_be32
c_func
(paren
op_amp
id|rtc-&gt;time
)paren
)paren
op_eq
id|previous_time
)paren
suffix:semicolon
id|tbl_start
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
id|previous_time
op_assign
id|current_time
suffix:semicolon
r_while
c_loop
(paren
(paren
id|current_time
op_assign
id|in_be32
c_func
(paren
op_amp
id|rtc-&gt;time
)paren
)paren
op_eq
id|previous_time
)paren
suffix:semicolon
id|tbl_end
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|rtc-&gt;dividers
comma
l_int|0xffff0000
)paren
suffix:semicolon
multiline_comment|/* Restore RTC */
id|xlbfreq
op_assign
(paren
id|tbl_end
op_minus
id|tbl_start
)paren
op_lshift
l_int|8
suffix:semicolon
id|ipbfreq
op_assign
(paren
id|in_8
c_func
(paren
op_amp
id|cdm-&gt;ipb_clk_sel
)paren
op_amp
l_int|1
)paren
ques
c_cond
id|xlbfreq
op_div
l_int|2
suffix:colon
id|xlbfreq
suffix:semicolon
r_return
id|ipbfreq
suffix:semicolon
)brace
r_int
r_int
DECL|function|serial_init
id|serial_init
c_func
(paren
r_int
id|ignored
comma
r_void
op_star
id|ignored2
)paren
(brace
r_struct
id|mpc52xx_gpio
id|__iomem
op_star
id|gpio
op_assign
(paren
r_struct
id|mpc52xx_gpio
id|__iomem
op_star
)paren
id|MPC52xx_GPIO
suffix:semicolon
r_int
id|divisor
suffix:semicolon
r_int
id|mode1
suffix:semicolon
r_int
id|mode2
suffix:semicolon
id|u32
id|val32
suffix:semicolon
r_static
r_int
id|been_here
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|been_here
)paren
r_return
l_int|0
suffix:semicolon
id|been_here
op_assign
l_int|1
suffix:semicolon
id|val32
op_assign
id|in_be32
c_func
(paren
op_amp
id|gpio-&gt;port_config
)paren
suffix:semicolon
id|val32
op_and_assign
op_complement
(paren
l_int|0x7
op_lshift
id|MPC52xx_PSC_CONFIG_SHIFT
)paren
suffix:semicolon
id|val32
op_or_assign
id|MPC52xx_GPIO_PSC_CONFIG_UART_WITHOUT_CD
op_lshift
id|MPC52xx_PSC_CONFIG_SHIFT
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|gpio-&gt;port_config
comma
id|val32
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;command
comma
id|MPC52xx_PSC_RST_TX
op_or
id|MPC52xx_PSC_RX_DISABLE
op_or
id|MPC52xx_PSC_TX_ENABLE
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;command
comma
id|MPC52xx_PSC_RST_RX
)paren
suffix:semicolon
id|out_be32
c_func
(paren
op_amp
id|psc-&gt;sicr
comma
l_int|0x0
)paren
suffix:semicolon
id|out_be16
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_clock_select
comma
l_int|0xdd00
)paren
suffix:semicolon
id|out_be16
c_func
(paren
op_amp
id|psc-&gt;tfalarm
comma
l_int|0xf8
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;command
comma
id|MPC52xx_PSC_SEL_MODE_REG_1
op_or
id|MPC52xx_PSC_RX_ENABLE
op_or
id|MPC52xx_PSC_TX_ENABLE
)paren
suffix:semicolon
id|divisor
op_assign
(paren
(paren
id|mpc52xx_ipbfreq
c_func
(paren
)paren
op_div
(paren
id|CONFIG_SERIAL_MPC52xx_CONSOLE_BAUD
op_star
l_int|16
)paren
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
id|mode1
op_assign
id|MPC52xx_PSC_MODE_8_BITS
op_or
id|MPC52xx_PSC_MODE_PARNONE
op_or
id|MPC52xx_PSC_MODE_ERR
suffix:semicolon
id|mode2
op_assign
id|MPC52xx_PSC_MODE_ONE_STOP
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;ctur
comma
id|divisor
op_rshift
l_int|8
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;ctlr
comma
id|divisor
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;command
comma
id|MPC52xx_PSC_SEL_MODE_REG_1
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;mode
comma
id|mode1
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;mode
comma
id|mode2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ignored */
)brace
r_void
DECL|function|serial_putc
id|serial_putc
c_func
(paren
r_void
op_star
id|ignored
comma
r_const
r_char
id|c
)paren
(brace
id|serial_init
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|in_be16
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_status
)paren
op_amp
id|MPC52xx_PSC_SR_TXEMP
)paren
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_buffer_8
comma
id|c
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|in_be16
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_status
)paren
op_amp
id|MPC52xx_PSC_SR_TXEMP
)paren
)paren
suffix:semicolon
)brace
r_char
DECL|function|serial_getc
id|serial_getc
c_func
(paren
r_void
op_star
id|ignored
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|in_be16
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_status
)paren
op_amp
id|MPC52xx_PSC_SR_RXRDY
)paren
)paren
suffix:semicolon
r_return
id|in_8
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_buffer_8
)paren
suffix:semicolon
)brace
r_int
DECL|function|serial_tstc
id|serial_tstc
c_func
(paren
r_void
op_star
id|ignored
)paren
(brace
r_return
(paren
id|in_be16
c_func
(paren
op_amp
id|psc-&gt;mpc52xx_psc_status
)paren
op_amp
id|MPC52xx_PSC_SR_RXRDY
)paren
op_ne
l_int|0
suffix:semicolon
)brace
eof
