multiline_comment|/*&n; *  arch/mips/pmc-sierra/yosemite/atmel_read_eeprom.c&n; *&n; *  Copyright (C) 2003 PMC-Sierra Inc.&n; *  Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *  Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * Header file for atmel_read_eeprom.c &n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/termios.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
DECL|macro|DEFAULT_PORT
mdefine_line|#define&t;DEFAULT_PORT &t;&quot;/dev/ttyS0&quot;&t;/* Port to open */
DECL|macro|TXX
mdefine_line|#define&t;TXX&t;&t;0 &t;&t;/* Dummy loop for spinning */
DECL|macro|BLOCK_SEL
mdefine_line|#define&t;BLOCK_SEL&t;0x00&t;&t;
DECL|macro|SLAVE_ADDR
mdefine_line|#define&t;SLAVE_ADDR&t;0xa0
DECL|macro|READ_BIT
mdefine_line|#define&t;READ_BIT&t;0x01
DECL|macro|WRITE_BIT
mdefine_line|#define&t;WRITE_BIT&t;0x00
DECL|macro|R_HEADER
mdefine_line|#define&t;R_HEADER&t;SLAVE_ADDR + BLOCK_SEL + READ_BIT
DECL|macro|W_HEADER
mdefine_line|#define&t;W_HEADER&t;SLAVE_ADDR + BLOCK_SEL + WRITE_BIT
multiline_comment|/*&n; * Clock, Voltages and Data&n; */
DECL|macro|vcc_off
mdefine_line|#define&t;vcc_off&t;&t;(ioctl(fd, TIOCSBRK, 0))
DECL|macro|vcc_on
mdefine_line|#define&t;vcc_on&t;&t;(ioctl(fd, TIOCCBRK, 0))
DECL|macro|sda_hi
mdefine_line|#define&t;sda_hi&t;&t;(ioctl(fd, TIOCMBIS, &amp;dtr))
DECL|macro|sda_lo
mdefine_line|#define&t;sda_lo&t;&t;(ioctl(fd, TIOCMBIC, &amp;dtr))
DECL|macro|scl_lo
mdefine_line|#define&t;scl_lo&t;&t;(ioctl(fd, TIOCMBIC, &amp;rts))
DECL|macro|scl_hi
mdefine_line|#define&t;scl_hi&t;&t;(ioctl(fd, TIOCMBIS, &amp;rts))
DECL|variable|rts
r_const
r_char
id|rts
op_assign
id|TIOCM_RTS
suffix:semicolon
DECL|variable|dtr
r_const
r_char
id|dtr
op_assign
id|TIOCM_DTR
suffix:semicolon
DECL|variable|fd
r_int
id|fd
suffix:semicolon
eof
