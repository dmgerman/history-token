multiline_comment|/*&n; *&t;file: ppc4xx_pm.c&n; *&n; *&t;This an attempt to get Power Management going for the IBM 4xx processor.&n; *&t;This was derived from the ppc4xx._setup.c file&n; *&n; *      Armin Kuster akuster@mvista.com&n; *      Jan  2002&n; *&n; *&n; * Copyright 2002 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&t;Version 1.0 (02/14/01) - A. Kuster&n; *&t;Initial version&t; - moved pm code from ppc4xx_setup.c&n; *&n; *&t;1.1 02/21/01 - A. Kuster&n; *&t;&t;minor fixes, init value to 0 &amp; += to &amp;=&n; *&t;&t;added stb03 ifdef for 2nd i2c device&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
r_void
id|__init
DECL|function|ppc4xx_pm_init
id|ppc4xx_pm_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off unused hardware to save power */
macro_line|#ifdef CONFIG_405GP
id|value
op_or_assign
id|CPM_DCP
suffix:semicolon
multiline_comment|/* CodePack */
macro_line|#endif
macro_line|#if !defined(CONFIG_IBM_OCP_GPIO)
id|value
op_or_assign
id|CPM_GPIO0
suffix:semicolon
macro_line|#endif
macro_line|#if !defined(CONFIG_PPC405_I2C_ADAP)
id|value
op_or_assign
id|CPM_IIC0
suffix:semicolon
macro_line|#ifdef CONFIG_STB03xxx
id|value
op_or_assign
id|CPM_IIC1
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#if !defined(CONFIG_405_DMA)
id|value
op_or_assign
id|CPM_DMA
suffix:semicolon
macro_line|#endif
id|mtdcr
c_func
(paren
id|DCRN_CPMFR
comma
id|value
)paren
suffix:semicolon
)brace
eof
