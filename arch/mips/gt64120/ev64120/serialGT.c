multiline_comment|/*&n; * serialGT.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *  Low Level Serial Port control for use&n; *  with the Galileo EVB64120A MIPS eval board and&n; *  its on board two channel 16552 Uart.&n; *&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
singleline_comment|// Note:
singleline_comment|//   Serial CHANNELS - 0 is the bottom connector of evb64120A.
singleline_comment|//                       (The one that maps to the &quot;B&quot; channel of the
singleline_comment|//                       board&squot;s uart)
singleline_comment|//                     1 is the top connector of evb64120A.
singleline_comment|//                       (The one that maps to the &quot;A&quot; channel of the
singleline_comment|//                       board&squot;s uart)
DECL|variable|DEBUG_CHANNEL
r_int
id|DEBUG_CHANNEL
op_assign
l_int|0
suffix:semicolon
singleline_comment|// See Note Above
DECL|variable|CONSOLE_CHANNEL
r_int
id|CONSOLE_CHANNEL
op_assign
l_int|1
suffix:semicolon
singleline_comment|// See Note Above
DECL|macro|DUART
mdefine_line|#define DUART 0xBD000000&t;/* Base address of Uart. */
DECL|macro|CHANNELOFFSET
mdefine_line|#define CHANNELOFFSET 0x20&t;/* DUART+CHANNELOFFSET gets you to the ChanA&n;&t;&t;&t;&t;   register set of the 16552 Uart device.&n;&t;&t;&t;&t;   DUART+0 gets you to the ChanB register set.&n;&t;&t;&t;&t; */
DECL|macro|DUART_DELTA
mdefine_line|#define DUART_DELTA 0x4
DECL|macro|FIFO_ENABLE
mdefine_line|#define FIFO_ENABLE 0x07
DECL|macro|INT_ENABLE
mdefine_line|#define INT_ENABLE  0x04&t;/* default interrupt mask */
DECL|macro|RBR
mdefine_line|#define RBR 0x00
DECL|macro|THR
mdefine_line|#define THR 0x00
DECL|macro|DLL
mdefine_line|#define DLL 0x00
DECL|macro|IER
mdefine_line|#define IER 0x01
DECL|macro|DLM
mdefine_line|#define DLM 0x01
DECL|macro|IIR
mdefine_line|#define IIR 0x02
DECL|macro|FCR
mdefine_line|#define FCR 0x02
DECL|macro|LCR
mdefine_line|#define LCR 0x03
DECL|macro|MCR
mdefine_line|#define MCR 0x04
DECL|macro|LSR
mdefine_line|#define LSR 0x05
DECL|macro|MSR
mdefine_line|#define MSR 0x06
DECL|macro|SCR
mdefine_line|#define SCR 0x07
DECL|macro|LCR_DLAB
mdefine_line|#define LCR_DLAB 0x80
DECL|macro|XTAL
mdefine_line|#define XTAL 1843200
DECL|macro|LSR_THRE
mdefine_line|#define LSR_THRE 0x20
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI   0x10
DECL|macro|LSR_DR
mdefine_line|#define LSR_DR   0x01
DECL|macro|MCR_LOOP
mdefine_line|#define MCR_LOOP 0x10
DECL|macro|ACCESS_DELAY
mdefine_line|#define ACCESS_DELAY 0x10000
multiline_comment|/******************************&n; Routine:&n; Description:&n; ******************************/
DECL|function|inreg
r_int
id|inreg
c_func
(paren
r_int
id|channel
comma
r_int
id|reg
)paren
(brace
r_int
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|DUART
op_plus
(paren
id|channel
op_star
id|CHANNELOFFSET
)paren
op_plus
(paren
id|reg
op_star
id|DUART_DELTA
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n; ******************************/
DECL|function|outreg
r_void
id|outreg
c_func
(paren
r_int
id|channel
comma
r_int
id|reg
comma
r_int
r_char
id|val
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|DUART
op_plus
(paren
id|channel
op_star
id|CHANNELOFFSET
)paren
op_plus
(paren
id|reg
op_star
id|DUART_DELTA
)paren
)paren
op_assign
id|val
suffix:semicolon
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n;   Initialize the device driver.&n; ******************************/
DECL|function|serial_init
r_void
id|serial_init
c_func
(paren
r_int
id|channel
)paren
(brace
multiline_comment|/*&n;&t; * Configure active port, (CHANNELOFFSET already set.)&n;&t; *&n;&t; * Set 8 bits, 1 stop bit, no parity.&n;&t; *&n;&t; * LCR&lt;7&gt;       0       divisor latch access bit&n;&t; * LCR&lt;6&gt;       0       break control (1=send break)&n;&t; * LCR&lt;5&gt;       0       stick parity (0=space, 1=mark)&n;&t; * LCR&lt;4&gt;       0       parity even (0=odd, 1=even)&n;&t; * LCR&lt;3&gt;       0       parity enable (1=enabled)&n;&t; * LCR&lt;2&gt;       0       # stop bits (0=1, 1=1.5)&n;&t; * LCR&lt;1:0&gt;     11      bits per character(00=5, 01=6, 10=7, 11=8)&n;&t; */
id|outreg
c_func
(paren
id|channel
comma
id|LCR
comma
l_int|0x3
)paren
suffix:semicolon
id|outreg
c_func
(paren
id|channel
comma
id|FCR
comma
id|FIFO_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Enable the FIFO */
id|outreg
c_func
(paren
id|channel
comma
id|IER
comma
id|INT_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Enable appropriate interrupts */
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n;   Set the baud rate.&n; ******************************/
DECL|function|serial_set
r_void
id|serial_set
c_func
(paren
r_int
id|channel
comma
r_int
r_int
id|baud
)paren
(brace
r_int
r_char
id|sav_lcr
suffix:semicolon
multiline_comment|/*&n;&t; * Enable access to the divisor latches by setting DLAB in LCR.&n;&t; *&n;&t; */
id|sav_lcr
op_assign
id|inreg
c_func
(paren
id|channel
comma
id|LCR
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * Set baud rate&n;&t; */
id|outreg
c_func
(paren
id|channel
comma
id|LCR
comma
id|LCR_DLAB
op_or
id|sav_lcr
)paren
suffix:semicolon
singleline_comment|//  outreg(DLL,(XTAL/(16*2*(baud))-2));
id|outreg
c_func
(paren
id|channel
comma
id|DLL
comma
id|XTAL
op_div
(paren
l_int|16
op_star
id|baud
)paren
)paren
suffix:semicolon
singleline_comment|//  outreg(DLM,(XTAL/(16*2*(baud))-2)&gt;&gt;8);
id|outreg
c_func
(paren
id|channel
comma
id|DLM
comma
(paren
id|XTAL
op_div
(paren
l_int|16
op_star
id|baud
)paren
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * Note: Set baud rate, hardcoded here for rate of 115200&n;&t; * since became unsure of above &quot;buad rate&quot; algorithm (??).&n;&t; */
id|outreg
c_func
(paren
id|channel
comma
id|LCR
comma
l_int|0x83
)paren
suffix:semicolon
id|outreg
c_func
(paren
id|channel
comma
id|DLM
comma
l_int|0x00
)paren
suffix:semicolon
singleline_comment|// See note above
id|outreg
c_func
(paren
id|channel
comma
id|DLL
comma
l_int|0x02
)paren
suffix:semicolon
singleline_comment|// See note above.
id|outreg
c_func
(paren
id|channel
comma
id|LCR
comma
l_int|0x03
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Restore line control register&n;&t; */
id|outreg
c_func
(paren
id|channel
comma
id|LCR
comma
id|sav_lcr
)paren
suffix:semicolon
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n;   Transmit a character.&n; ******************************/
DECL|function|serial_putc
r_void
id|serial_putc
c_func
(paren
r_int
id|channel
comma
r_int
id|c
)paren
(brace
r_while
c_loop
(paren
(paren
id|inreg
c_func
(paren
id|channel
comma
id|LSR
)paren
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|outreg
c_func
(paren
id|channel
comma
id|THR
comma
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n;    Read a received character if one is&n;    available.  Return -1 otherwise.&n; ******************************/
DECL|function|serial_getc
r_int
id|serial_getc
c_func
(paren
r_int
id|channel
)paren
(brace
r_if
c_cond
(paren
id|inreg
c_func
(paren
id|channel
comma
id|LSR
)paren
op_amp
id|LSR_DR
)paren
(brace
r_return
id|inreg
c_func
(paren
id|channel
comma
id|RBR
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n;   Used by embedded gdb client. (example; gdb-stub.c)&n; ******************************/
DECL|function|getDebugChar
r_char
id|getDebugChar
c_func
(paren
)paren
(brace
r_int
id|val
suffix:semicolon
r_while
c_loop
(paren
(paren
id|val
op_assign
id|serial_getc
c_func
(paren
id|DEBUG_CHANNEL
)paren
)paren
op_eq
op_minus
l_int|1
)paren
suffix:semicolon
singleline_comment|// loop until we get a character in.
r_return
(paren
r_char
)paren
id|val
suffix:semicolon
)brace
multiline_comment|/******************************&n; Routine:&n; Description:&n;   Used by embedded gdb target. (example; gdb-stub.c)&n; ******************************/
DECL|function|putDebugChar
r_void
id|putDebugChar
c_func
(paren
r_char
id|c
)paren
(brace
id|serial_putc
c_func
(paren
id|DEBUG_CHANNEL
comma
(paren
r_int
)paren
id|c
)paren
suffix:semicolon
)brace
eof
