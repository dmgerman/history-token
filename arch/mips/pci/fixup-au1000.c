multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Board specific pci fixups.&n; *&n; * Copyright 2001-2003 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
multiline_comment|/*&n; * Shortcut&n; */
macro_line|#ifdef CONFIG_SOC_AU1500
DECL|macro|INTA
mdefine_line|#define INTA AU1000_PCI_INTA
DECL|macro|INTB
mdefine_line|#define INTB AU1000_PCI_INTB
DECL|macro|INTC
mdefine_line|#define INTC AU1000_PCI_INTC
DECL|macro|INTD
mdefine_line|#define INTD AU1000_PCI_INTD
macro_line|#endif
macro_line|#ifdef CONFIG_SOC_AU1550
DECL|macro|INTA
mdefine_line|#define INTA AU1550_PCI_INTA
DECL|macro|INTB
mdefine_line|#define INTB AU1550_PCI_INTB
DECL|macro|INTC
mdefine_line|#define INTC AU1550_PCI_INTC
DECL|macro|INTD
mdefine_line|#define INTD AU1550_PCI_INTD
macro_line|#endif
DECL|macro|INTX
mdefine_line|#define INTX    0xFF /* not valid */
macro_line|#ifdef CONFIG_MIPS_DB1500
DECL|variable|__initdata
r_static
r_char
id|irq_tab_alchemy
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTX
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 12 - HPT371   */
(braket
l_int|13
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTC
comma
id|INTD
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_BOSPORUS
DECL|variable|__initdata
r_static
r_char
id|irq_tab_alchemy
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|11
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 11 - miniPCI  */
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTX
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 12 - SN1741   */
(braket
l_int|13
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTC
comma
id|INTD
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_MIRAGE
DECL|variable|__initdata
r_static
r_char
id|irq_tab_alchemy
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|11
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTD
comma
id|INTX
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 11 - SMI VGX */
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTX
comma
id|INTX
comma
id|INTC
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 12 - PNX1300 */
(braket
l_int|13
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 13 - miniPCI */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1550
DECL|variable|__initdata
r_static
r_char
id|irq_tab_alchemy
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|11
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTC
comma
id|INTX
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 11 - on-board HPT371    */
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTB
comma
id|INTC
comma
id|INTD
comma
id|INTA
)brace
comma
multiline_comment|/* IDSEL 12 - PCI slot 2 (left)  */
(braket
l_int|13
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTC
comma
id|INTD
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot 1 (right) */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_PB1500
DECL|variable|__initdata
r_static
r_char
id|irq_tab_alchemy
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTX
comma
id|INTX
comma
id|INTX
)brace
comma
multiline_comment|/* IDSEL 12 - HPT370   */
(braket
l_int|13
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTC
comma
id|INTD
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_PB1550
DECL|variable|__initdata
r_static
r_char
id|irq_tab_alchemy
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTB
comma
id|INTC
comma
id|INTD
comma
id|INTA
)brace
comma
multiline_comment|/* IDSEL 12 - PCI slot 2 (left)  */
(braket
l_int|13
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INTA
comma
id|INTB
comma
id|INTC
comma
id|INTD
)brace
comma
multiline_comment|/* IDSEL 13 - PCI slot 1 (right) */
)brace
suffix:semicolon
macro_line|#endif
DECL|function|pcibios_map_irq
r_int
id|__init
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_return
id|irq_tab_alchemy
(braket
id|slot
)braket
(braket
id|pin
)braket
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
