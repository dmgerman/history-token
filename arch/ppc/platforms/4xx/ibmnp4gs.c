multiline_comment|/*&n; *&n; *    Copyright 2000-2002 MontaVista Software Inc.&n; *      Completed implementation.&n; *&t;Current maintainer&n; *      Armin Kuster akuster@mvista.com&n; *&n; *    Module name: ibmnp4gs.c&n; *&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;ibmnp4gs.h&quot;
macro_line|#include &lt;asm/ocp.h&gt;
DECL|variable|core_ocp
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
op_assign
(brace
(brace
id|UART
comma
id|UART0_IO_BASE
comma
id|UART0_INT
comma
id|IBM_CPM_UART0
)brace
comma
(brace
id|PCI
comma
id|PCIL0_BASE
comma
id|OCP_IRQ_NA
comma
id|IBM_CPM_PCI
)brace
comma
(brace
id|OCP_NULL_TYPE
comma
l_int|0x0
comma
id|OCP_IRQ_NA
comma
id|OCP_CPM_NA
)brace
comma
)brace
suffix:semicolon
eof
