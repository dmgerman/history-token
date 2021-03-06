multiline_comment|/*&n; *  arch/mips/pmc-sierra/yosemite/atmel_read_eeprom.c&n; *&n; *  Copyright (C) 2003 PMC-Sierra Inc.&n; *  Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * Description:&n; *&n; * This code reads the ATMEL 24CXX EEPROM. The PMC-Sierra Yosemite board uses the ATMEL&n; * 24C32/24C64 which uses two byte addressing as compared to 24C16. Note that this program&n; * uses the serial port like /dev/ttyS0, to communicate with the EEPROM. Hence, you are &n; * expected to have a connectivity from the EEPROM to the serial port. This program does&n; * __not__ communicate using the I2C protocol&n; */
macro_line|#include &quot;atmel_read_eeprom.h&quot;
DECL|function|delay
r_static
r_void
id|delay
c_func
(paren
r_int
id|delay
)paren
(brace
r_while
c_loop
(paren
id|delay
op_decrement
)paren
suffix:semicolon
)brace
DECL|function|send_bit
r_static
r_void
id|send_bit
c_func
(paren
r_int
r_char
id|bit
)paren
(brace
id|scl_lo
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
id|sda_hi
suffix:semicolon
r_else
id|sda_lo
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|scl_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
)brace
DECL|function|send_ack
r_static
r_void
id|send_ack
c_func
(paren
r_void
)paren
(brace
id|send_bit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|send_byte
r_static
r_void
id|send_byte
c_func
(paren
r_int
r_char
id|byte
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|send_bit
c_func
(paren
(paren
id|byte
op_rshift
id|i
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
)brace
DECL|function|send_start
r_static
r_void
id|send_start
c_func
(paren
r_void
)paren
(brace
id|sda_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|scl_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|sda_lo
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
)brace
DECL|function|send_stop
r_static
r_void
id|send_stop
c_func
(paren
r_void
)paren
(brace
id|sda_lo
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|scl_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|sda_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
)brace
DECL|function|do_idle
r_static
r_void
id|do_idle
c_func
(paren
r_void
)paren
(brace
id|sda_hi
suffix:semicolon
id|scl_hi
suffix:semicolon
id|vcc_off
suffix:semicolon
)brace
DECL|function|recv_bit
r_static
r_int
id|recv_bit
c_func
(paren
r_void
)paren
(brace
r_int
id|status
suffix:semicolon
id|scl_lo
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|sda_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
id|scl_hi
suffix:semicolon
id|delay
c_func
(paren
id|TXX
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|recv_byte
r_static
r_int
r_char
id|recv_byte
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|byte
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|byte
op_or_assign
(paren
id|recv_bit
c_func
(paren
)paren
op_lshift
id|i
)paren
suffix:semicolon
r_return
id|byte
suffix:semicolon
)brace
DECL|function|recv_ack
r_static
r_int
id|recv_ack
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ack
suffix:semicolon
id|ack
op_assign
(paren
r_int
r_int
)paren
id|recv_bit
c_func
(paren
)paren
suffix:semicolon
id|scl_lo
suffix:semicolon
r_if
c_cond
(paren
id|ack
)paren
(brace
id|do_idle
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error reading the Atmel 24C32/24C64 EEPROM &bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|ack
suffix:semicolon
)brace
multiline_comment|/*&n; * This function does the actual read of the EEPROM. It needs the buffer into which the&n; * read data is copied, the size of the EEPROM being read and the buffer size&n; */
DECL|function|read_eeprom
r_int
id|read_eeprom
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|eeprom_size
comma
r_int
id|size
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|err
suffix:semicolon
id|send_start
c_func
(paren
)paren
suffix:semicolon
id|send_byte
c_func
(paren
id|W_HEADER
)paren
suffix:semicolon
id|recv_ack
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* EEPROM with size of more then 2K need two byte addressing */
r_if
c_cond
(paren
id|eeprom_size
OG
l_int|2048
)paren
(brace
id|send_byte
c_func
(paren
l_int|0x00
)paren
suffix:semicolon
id|recv_ack
c_func
(paren
)paren
suffix:semicolon
)brace
id|send_start
c_func
(paren
)paren
suffix:semicolon
id|send_byte
c_func
(paren
id|R_HEADER
)paren
suffix:semicolon
id|err
op_assign
id|recv_ack
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
l_int|1
)paren
r_return
id|err
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|buffer
op_increment
op_assign
id|recv_byte
c_func
(paren
)paren
suffix:semicolon
id|send_ack
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Note : We should do some check if the buffer contains correct information */
id|send_stop
c_func
(paren
)paren
suffix:semicolon
)brace
eof
