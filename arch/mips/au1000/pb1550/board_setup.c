multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Alchemy Pb1550 board setup.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
macro_line|#include &lt;asm/mach-pb1x00/pb1550.h&gt;
DECL|function|board_reset
r_void
id|board_reset
(paren
r_void
)paren
(brace
multiline_comment|/* Hit BCSR.SYSTEM_CONTROL[SW_RST] */
id|au_writew
c_func
(paren
id|au_readw
c_func
(paren
l_int|0xAF00001C
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
l_int|0xAF00001C
)paren
suffix:semicolon
)brace
DECL|function|board_setup
r_void
id|__init
id|board_setup
c_func
(paren
r_void
)paren
(brace
id|u32
id|pin_func
suffix:semicolon
multiline_comment|/* Enable PSC1 SYNC for AC97.  Normaly done in audio driver,&n;&t; * but it is board specific code, so put it here.&n;&t; */
id|pin_func
op_assign
id|au_readl
c_func
(paren
id|SYS_PINFUNC
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
id|pin_func
op_or_assign
id|SYS_PF_MUST_BE_SET
op_or
id|SYS_PF_PSC1_S1
suffix:semicolon
id|au_writel
c_func
(paren
id|pin_func
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0
comma
(paren
id|u32
)paren
id|bcsr
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* turn off pcmcia power */
id|au_sync
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;AMD Alchemy Pb1550 Board&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
