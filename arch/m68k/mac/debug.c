multiline_comment|/*&n; * linux/arch/m68k/mac/debug.c&n; *&n; * Shamelessly stolen (SCC code and general framework) from:&n; *&n; * linux/arch/m68k/atari/debug.c&n; *&n; * Atari debugging and serial console stuff&n; *&n; * Assembled of parts of former atari/config.c 97-12-18 by Roman Hodek&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|BOOTINFO_COMPAT_1_0
mdefine_line|#define BOOTINFO_COMPAT_1_0
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/machw.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
r_extern
r_char
id|m68k_debug_device
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|compat_bootinfo
id|compat_boot_info
suffix:semicolon
r_extern
r_int
r_int
id|mac_videobase
suffix:semicolon
r_extern
r_int
r_int
id|mac_videodepth
suffix:semicolon
r_extern
r_int
r_int
id|mac_rowbytes
suffix:semicolon
r_extern
r_void
id|mac_serial_print
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|macro|DEBUG_HEADS
mdefine_line|#define DEBUG_HEADS
DECL|macro|DEBUG_SCREEN
macro_line|#undef DEBUG_SCREEN
DECL|macro|DEBUG_SERIAL
mdefine_line|#define DEBUG_SERIAL
multiline_comment|/*&n; * These two auxiliary debug functions should go away ASAP. Only usage:&n; * before the console output is up (after head.S come some other crucial&n; * setup routines :-) it permits writing &squot;data&squot; to the screen as bit patterns&n; * (good luck reading those). Helped to figure that the bootinfo contained&n; * garbage data on the amount and size of memory chunks ...&n; *&n; * The &squot;pos&squot; argument now simply means &squot;linefeed after print&squot; ...&n; */
macro_line|#ifdef DEBUG_SCREEN
DECL|variable|peng
DECL|variable|line
r_static
r_int
id|peng
op_assign
l_int|0
comma
id|line
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|function|mac_debugging_short
r_void
id|mac_debugging_short
c_func
(paren
r_int
id|pos
comma
r_int
id|num
)paren
(brace
macro_line|#ifdef DEBUG_SCREEN
r_int
r_char
op_star
id|pengoffset
suffix:semicolon
r_int
r_char
op_star
id|pptr
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEBUG_SERIAL
id|printk
c_func
(paren
l_string|&quot;debug: %d !&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEBUG_SCREEN
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
(brace
multiline_comment|/* printk(&quot;debug: %d !&bslash;n&quot;, num); */
r_return
suffix:semicolon
)brace
multiline_comment|/* calculate current offset */
id|pengoffset
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|mac_videobase
op_plus
(paren
l_int|150
op_plus
id|line
op_star
l_int|2
)paren
op_star
id|mac_rowbytes
)paren
op_plus
l_int|80
op_star
id|peng
suffix:semicolon
id|pptr
op_assign
id|pengoffset
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
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* # of bits */
(brace
multiline_comment|/*        value        mask for bit i, reverse order */
op_star
id|pptr
op_increment
op_assign
(paren
id|num
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
op_minus
id|i
op_minus
l_int|1
)paren
)paren
ques
c_cond
l_int|0xFF
suffix:colon
l_int|0x00
)paren
suffix:semicolon
)brace
id|peng
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pos
)paren
(brace
id|line
op_increment
suffix:semicolon
id|peng
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|mac_debugging_long
r_void
id|mac_debugging_long
c_func
(paren
r_int
id|pos
comma
r_int
id|addr
)paren
(brace
macro_line|#ifdef DEBUG_SCREEN
r_int
r_char
op_star
id|pengoffset
suffix:semicolon
r_int
r_char
op_star
id|pptr
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEBUG_SERIAL
id|printk
c_func
(paren
l_string|&quot;debug: #%ld !&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEBUG_SCREEN
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
(brace
multiline_comment|/* printk(&quot;debug: #%ld !&bslash;n&quot;, addr); */
r_return
suffix:semicolon
)brace
id|pengoffset
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|mac_videobase
op_plus
(paren
l_int|150
op_plus
id|line
op_star
l_int|2
)paren
op_star
id|mac_rowbytes
)paren
op_plus
l_int|80
op_star
id|peng
suffix:semicolon
id|pptr
op_assign
id|pengoffset
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
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* # of bits */
(brace
op_star
id|pptr
op_increment
op_assign
(paren
id|addr
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
op_minus
id|i
op_minus
l_int|1
)paren
)paren
ques
c_cond
l_int|0xFF
suffix:colon
l_int|0x00
)paren
suffix:semicolon
)brace
id|peng
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pos
)paren
(brace
id|line
op_increment
suffix:semicolon
id|peng
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#ifdef DEBUG_SERIAL
multiline_comment|/*&n; * TODO: serial debug code&n; */
DECL|struct|mac_SCC
r_struct
id|mac_SCC
(brace
DECL|member|cha_b_ctrl
id|u_char
id|cha_b_ctrl
suffix:semicolon
DECL|member|char_dummy1
id|u_char
id|char_dummy1
suffix:semicolon
DECL|member|cha_a_ctrl
id|u_char
id|cha_a_ctrl
suffix:semicolon
DECL|member|char_dummy2
id|u_char
id|char_dummy2
suffix:semicolon
DECL|member|cha_b_data
id|u_char
id|cha_b_data
suffix:semicolon
DECL|member|char_dummy3
id|u_char
id|char_dummy3
suffix:semicolon
DECL|member|cha_a_data
id|u_char
id|cha_a_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|scc
macro_line|# define scc (*((volatile struct mac_SCC*)mac_bi_data.sccbase))
multiline_comment|/* Flag that serial port is already initialized and used */
DECL|variable|mac_SCC_init_done
r_int
id|mac_SCC_init_done
suffix:semicolon
multiline_comment|/* Can be set somewhere, if a SCC master reset has already be done and should&n; * not be repeated; used by kgdb */
DECL|variable|mac_SCC_reset_done
r_int
id|mac_SCC_reset_done
suffix:semicolon
DECL|variable|scc_port
r_static
r_int
id|scc_port
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mac_console_driver
r_static
r_struct
id|console
id|mac_console_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;debug&quot;
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Crude hack to get console output to the screen before the framebuffer&n; * is initialized (happens a lot later in 2.1!).&n; * We just use the console routines declared in head.S, this will interfere&n; * with regular framebuffer console output and should be used exclusively&n; * to debug kernel problems manifesting before framebuffer init (aka WSOD)&n; *&n; * To keep this hack from interfering with the regular console driver, either&n; * deregister this driver before/on framebuffer console init, or silence this&n; * function after the fbcon driver is running (will lose console messages!?).&n; * To debug real early bugs, need to write a &squot;mac_register_console_hack()&squot;&n; * that is called from start_kernel() before setup_arch() and just registers&n; * this driver if Mac.&n; */
DECL|function|mac_debug_console_write
r_void
id|mac_debug_console_write
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|count
)paren
(brace
id|mac_serial_print
c_func
(paren
id|str
)paren
suffix:semicolon
)brace
multiline_comment|/* Mac: loops_per_jiffy min. 19000 ^= .5 us; MFPDELAY was 0.6 us*/
DECL|macro|uSEC
mdefine_line|#define uSEC 1
DECL|function|mac_sccb_out
r_static
r_inline
r_void
id|mac_sccb_out
(paren
r_char
id|c
)paren
(brace
r_int
id|i
suffix:semicolon
r_do
(brace
r_for
c_loop
(paren
id|i
op_assign
id|uSEC
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|scc.cha_b_ctrl
op_amp
l_int|0x04
)paren
)paren
suffix:semicolon
multiline_comment|/* wait for tx buf empty */
r_for
c_loop
(paren
id|i
op_assign
id|uSEC
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|scc.cha_b_data
op_assign
id|c
suffix:semicolon
)brace
DECL|function|mac_scca_out
r_static
r_inline
r_void
id|mac_scca_out
(paren
r_char
id|c
)paren
(brace
r_int
id|i
suffix:semicolon
r_do
(brace
r_for
c_loop
(paren
id|i
op_assign
id|uSEC
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|scc.cha_a_ctrl
op_amp
l_int|0x04
)paren
)paren
suffix:semicolon
multiline_comment|/* wait for tx buf empty */
r_for
c_loop
(paren
id|i
op_assign
id|uSEC
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|scc.cha_a_data
op_assign
id|c
suffix:semicolon
)brace
DECL|function|mac_sccb_console_write
r_void
id|mac_sccb_console_write
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|mac_sccb_out
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|mac_sccb_out
c_func
(paren
op_star
id|str
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|mac_scca_console_write
r_void
id|mac_scca_console_write
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|mac_scca_out
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|mac_scca_out
c_func
(paren
op_star
id|str
op_increment
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* The following two functions do a quick&squot;n&squot;dirty initialization of the MFP or&n; * SCC serial ports. They&squot;re used by the debugging interface, kgdb, and the&n; * serial console code. */
DECL|macro|SCCB_WRITE
mdefine_line|#define SCCB_WRITE(reg,val)&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;scc.cha_b_ctrl = (reg);&t;&t;&t;&t;&bslash;&n;&t;for( i = uSEC; i &gt; 0; --i )&t;&t;&t;&bslash;&n;&t;&t;barrier();&t;&t;&t;&t;&bslash;&n;&t;scc.cha_b_ctrl = (val);&t;&t;&t;&t;&bslash;&n;&t;for( i = uSEC; i &gt; 0; --i )&t;&t;&t;&bslash;&n;&t;&t;barrier();&t;&t;&t;&t;&bslash;&n;    } while(0)
DECL|macro|SCCA_WRITE
mdefine_line|#define SCCA_WRITE(reg,val)&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;scc.cha_a_ctrl = (reg);&t;&t;&t;&t;&bslash;&n;&t;for( i = uSEC; i &gt; 0; --i )&t;&t;&t;&bslash;&n;&t;&t;barrier();&t;&t;&t;&t;&bslash;&n;&t;scc.cha_a_ctrl = (val);&t;&t;&t;&t;&bslash;&n;&t;for( i = uSEC; i &gt; 0; --i )&t;&t;&t;&bslash;&n;&t;&t;barrier();&t;&t;&t;&t;&bslash;&n;    } while(0)
multiline_comment|/* loops_per_jiffy isn&squot;t initialized yet, so we can&squot;t use udelay(). This does a&n; * delay of ~ 60us. */
multiline_comment|/* Mac: loops_per_jiffy min. 19000 ^= .5 us; MFPDELAY was 0.6 us*/
DECL|macro|LONG_DELAY
mdefine_line|#define LONG_DELAY()&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&bslash;&n;&t;int i;&t;&t;&t;&t;&t;&bslash;&n;&t;for( i = 60*uSEC; i &gt; 0; --i )&t;&t;&bslash;&n;&t;    barrier();&t;&t;&t;&t;&bslash;&n;    } while(0)
macro_line|#ifndef CONFIG_SERIAL_CONSOLE
DECL|function|mac_init_scc_port
r_static
r_void
id|__init
id|mac_init_scc_port
c_func
(paren
r_int
id|cflag
comma
r_int
id|port
)paren
macro_line|#else
r_void
id|mac_init_scc_port
c_func
(paren
r_int
id|cflag
comma
r_int
id|port
)paren
macro_line|#endif
(brace
r_extern
r_int
id|mac_SCC_reset_done
suffix:semicolon
multiline_comment|/*&n;&t; * baud rates: 1200, 1800, 2400, 4800, 9600, 19.2k, 38.4k, 57.6k, 115.2k&n;&t; */
r_static
r_int
id|clksrc_table
(braket
l_int|9
)braket
op_assign
multiline_comment|/* reg 11: 0x50 = BRG, 0x00 = RTxC, 0x28 = TRxC */
(brace
l_int|0x50
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
r_static
r_int
id|clkmode_table
(braket
l_int|9
)braket
op_assign
multiline_comment|/* reg 4: 0x40 = x16, 0x80 = x32, 0xc0 = x64 */
(brace
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0xc0
comma
l_int|0x80
)brace
suffix:semicolon
r_static
r_int
id|div_table
(braket
l_int|9
)braket
op_assign
multiline_comment|/* reg12 (BRG low) */
(brace
l_int|94
comma
l_int|62
comma
l_int|46
comma
l_int|22
comma
l_int|10
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|baud
op_assign
id|cflag
op_amp
id|CBAUD
suffix:semicolon
r_int
id|clksrc
comma
id|clkmode
comma
id|div
comma
id|reg3
comma
id|reg5
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|CBAUDEX
)paren
id|baud
op_add_assign
id|B38400
suffix:semicolon
r_if
c_cond
(paren
id|baud
template_param
id|B38400
op_plus
l_int|2
)paren
id|baud
op_assign
id|B9600
suffix:semicolon
multiline_comment|/* use default 9600bps for non-implemented rates */
id|baud
op_sub_assign
id|B1200
suffix:semicolon
multiline_comment|/* tables starts at 1200bps */
id|clksrc
op_assign
id|clksrc_table
(braket
id|baud
)braket
suffix:semicolon
id|clkmode
op_assign
id|clkmode_table
(braket
id|baud
)braket
suffix:semicolon
id|div
op_assign
id|div_table
(braket
id|baud
)braket
suffix:semicolon
id|reg3
op_assign
(paren
(paren
(paren
id|cflag
op_amp
id|CSIZE
)paren
op_eq
id|CS8
)paren
ques
c_cond
l_int|0xc0
suffix:colon
l_int|0x40
)paren
suffix:semicolon
id|reg5
op_assign
(paren
(paren
(paren
id|cflag
op_amp
id|CSIZE
)paren
op_eq
id|CS8
)paren
ques
c_cond
l_int|0x60
suffix:colon
l_int|0x20
)paren
op_or
l_int|0x82
multiline_comment|/* assert DTR/RTS */
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|1
)paren
(brace
(paren
r_void
)paren
id|scc.cha_b_ctrl
suffix:semicolon
multiline_comment|/* reset reg pointer */
id|SCCB_WRITE
c_func
(paren
l_int|9
comma
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* reset */
id|LONG_DELAY
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* extra delay after WR9 access */
id|SCCB_WRITE
c_func
(paren
l_int|4
comma
(paren
id|cflag
op_amp
id|PARENB
)paren
ques
c_cond
(paren
(paren
id|cflag
op_amp
id|PARODD
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x03
)paren
suffix:colon
l_int|0
op_or
l_int|0x04
multiline_comment|/* 1 stopbit */
op_or
id|clkmode
)paren
suffix:semicolon
id|SCCB_WRITE
c_func
(paren
l_int|3
comma
id|reg3
)paren
suffix:semicolon
id|SCCB_WRITE
c_func
(paren
l_int|5
comma
id|reg5
)paren
suffix:semicolon
id|SCCB_WRITE
c_func
(paren
l_int|9
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* no interrupts */
id|LONG_DELAY
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* extra delay after WR9 access */
id|SCCB_WRITE
c_func
(paren
l_int|10
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* NRZ mode */
id|SCCB_WRITE
c_func
(paren
l_int|11
comma
id|clksrc
)paren
suffix:semicolon
multiline_comment|/* main clock source */
id|SCCB_WRITE
c_func
(paren
l_int|12
comma
id|div
)paren
suffix:semicolon
multiline_comment|/* BRG value */
id|SCCB_WRITE
c_func
(paren
l_int|13
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* BRG high byte */
id|SCCB_WRITE
c_func
(paren
l_int|14
comma
l_int|1
)paren
suffix:semicolon
id|SCCB_WRITE
c_func
(paren
l_int|3
comma
id|reg3
op_or
l_int|1
)paren
suffix:semicolon
id|SCCB_WRITE
c_func
(paren
l_int|5
comma
id|reg5
op_or
l_int|8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
(brace
(paren
r_void
)paren
id|scc.cha_a_ctrl
suffix:semicolon
multiline_comment|/* reset reg pointer */
id|SCCA_WRITE
c_func
(paren
l_int|9
comma
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* reset */
id|LONG_DELAY
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* extra delay after WR9 access */
id|SCCA_WRITE
c_func
(paren
l_int|4
comma
(paren
id|cflag
op_amp
id|PARENB
)paren
ques
c_cond
(paren
(paren
id|cflag
op_amp
id|PARODD
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x03
)paren
suffix:colon
l_int|0
op_or
l_int|0x04
multiline_comment|/* 1 stopbit */
op_or
id|clkmode
)paren
suffix:semicolon
id|SCCA_WRITE
c_func
(paren
l_int|3
comma
id|reg3
)paren
suffix:semicolon
id|SCCA_WRITE
c_func
(paren
l_int|5
comma
id|reg5
)paren
suffix:semicolon
id|SCCA_WRITE
c_func
(paren
l_int|9
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* no interrupts */
id|LONG_DELAY
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* extra delay after WR9 access */
id|SCCA_WRITE
c_func
(paren
l_int|10
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* NRZ mode */
id|SCCA_WRITE
c_func
(paren
l_int|11
comma
id|clksrc
)paren
suffix:semicolon
multiline_comment|/* main clock source */
id|SCCA_WRITE
c_func
(paren
l_int|12
comma
id|div
)paren
suffix:semicolon
multiline_comment|/* BRG value */
id|SCCA_WRITE
c_func
(paren
l_int|13
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* BRG high byte */
id|SCCA_WRITE
c_func
(paren
l_int|14
comma
l_int|1
)paren
suffix:semicolon
id|SCCA_WRITE
c_func
(paren
l_int|3
comma
id|reg3
op_or
l_int|1
)paren
suffix:semicolon
id|SCCA_WRITE
c_func
(paren
l_int|5
comma
id|reg5
op_or
l_int|8
)paren
suffix:semicolon
)brace
id|mac_SCC_reset_done
op_assign
l_int|1
suffix:semicolon
id|mac_SCC_init_done
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_SERIAL */
DECL|function|mac_init_scca_port
r_void
id|mac_init_scca_port
c_func
(paren
r_int
id|cflag
)paren
(brace
id|mac_init_scc_port
c_func
(paren
id|cflag
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mac_init_sccb_port
r_void
id|mac_init_sccb_port
c_func
(paren
r_int
id|cflag
)paren
(brace
id|mac_init_scc_port
c_func
(paren
id|cflag
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|mac_debug_init
r_void
id|__init
id|mac_debug_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef DEBUG_SERIAL
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;ser&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;ser1&quot;
)paren
)paren
(brace
multiline_comment|/* Mac modem port */
id|mac_init_scc_port
c_func
(paren
id|B9600
op_or
id|CS8
comma
l_int|0
)paren
suffix:semicolon
id|mac_console_driver.write
op_assign
id|mac_scca_console_write
suffix:semicolon
id|scc_port
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;ser2&quot;
)paren
)paren
(brace
multiline_comment|/* Mac printer port */
id|mac_init_scc_port
c_func
(paren
id|B9600
op_or
id|CS8
comma
l_int|1
)paren
suffix:semicolon
id|mac_console_driver.write
op_assign
id|mac_sccb_console_write
suffix:semicolon
id|scc_port
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef DEBUG_HEADS
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;scn&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;con&quot;
)paren
)paren
(brace
multiline_comment|/* display, using head.S console routines */
id|mac_console_driver.write
op_assign
id|mac_debug_console_write
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|mac_console_driver.write
)paren
id|register_console
c_func
(paren
op_amp
id|mac_console_driver
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 4&n; *  tab-width: 8&n; * End:&n; */
eof
