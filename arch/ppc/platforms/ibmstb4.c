multiline_comment|/*&n; *&n; *    Copyright 2000-2001 MontaVista Software Inc.&n; *      Completed implementation.&n; *&t;Current maintainer&n; *      Armin Kuster akuster@mvista.com&n; *&n; *    Module name: ibmstb4.c&n; *&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *      History: 12/26/2001 - armin&n; *&t;&t;initial release&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/ibmstb4.h&gt;
DECL|variable|COM_PORTS
r_const
r_struct
id|NS16550
op_star
id|COM_PORTS
(braket
)braket
op_assign
(brace
(paren
r_struct
id|NS16550
op_star
)paren
id|UART0_IO_BASE
comma
(paren
r_struct
id|NS16550
op_star
)paren
id|UART1_IO_BASE
comma
(paren
r_struct
id|NS16550
op_star
)paren
id|UART2_IO_BASE
comma
)brace
suffix:semicolon
DECL|variable|IIC_ADDR
r_const
r_struct
id|iic_regs
op_star
id|IIC_ADDR
(braket
)braket
op_assign
(brace
(paren
r_struct
id|iic_regs
op_star
)paren
id|IIC0_BASE
comma
)brace
suffix:semicolon
DECL|variable|GPIO_ADDR
r_const
r_struct
id|gpio_regs
op_star
id|GPIO_ADDR
(braket
)braket
op_assign
(brace
(paren
r_struct
id|gpio_regs
op_star
)paren
id|GPIO0_BASE
comma
)brace
suffix:semicolon
DECL|variable|IDE_ADDR
r_const
r_struct
id|ide_regs
op_star
id|IDE_ADDR
(braket
)braket
op_assign
(brace
(paren
r_struct
id|ide_regs
op_star
)paren
id|IDE0_IO_ADDR
comma
)brace
suffix:semicolon
eof