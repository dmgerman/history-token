multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Board specific pci fixups.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_pci.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
multiline_comment|/*&n; * Shortcuts&n; */
DECL|macro|INTA
mdefine_line|#define INTA&t;IT8172_PCI_INTA_IRQ
DECL|macro|INTB
mdefine_line|#define INTB&t;IT8172_PCI_INTB_IRQ
DECL|macro|INTC
mdefine_line|#define INTC&t;IT8172_PCI_INTC_IRQ
DECL|macro|INTD
mdefine_line|#define INTD&t;IT8172_PCI_INTD_IRQ
DECL|variable|__initdata
r_static
r_const
r_int
id|internal_func_irqs
(braket
l_int|7
)braket
id|__initdata
op_assign
(brace
id|IT8172_AC97_IRQ
comma
id|IT8172_DMA_IRQ
comma
id|IT8172_CDMA_IRQ
comma
id|IT8172_USB_IRQ
comma
id|IT8172_BRIDGE_MASTER_IRQ
comma
id|IT8172_IDE_IRQ
comma
id|IT8172_MC68K_IRQ
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|irq_tab_ite8172g
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
(braket
l_int|0x10
)braket
op_assign
(brace
l_int|0
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
(braket
l_int|0x11
)braket
op_assign
(brace
l_int|0
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
(braket
l_int|0x12
)braket
op_assign
(brace
l_int|0
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
(braket
l_int|0x13
)braket
op_assign
(brace
l_int|0
comma
id|INTC
comma
id|INTD
comma
id|INTA
comma
id|INTB
)brace
comma
(braket
l_int|0x14
)braket
op_assign
(brace
l_int|0
comma
id|INTD
comma
id|INTA
comma
id|INTB
comma
id|INTC
)brace
comma
)brace
suffix:semicolon
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
multiline_comment|/*&n;&t; * Internal device 1 is actually 7 different internal devices on the&n;&t; * IT8172G (a multifunction device).&n;&t; */
r_if
c_cond
(paren
id|slot
op_eq
l_int|1
)paren
r_return
id|internal_func_irqs
(braket
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)braket
suffix:semicolon
r_return
id|irq_tab_ite8172g
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
