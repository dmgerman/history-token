multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Globespan IVR board-specific pci fixups.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_pci.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
DECL|function|pcibios_fixup_resources
r_void
id|__init
id|pcibios_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|pcibios_fixup
r_void
id|__init
id|pcibios_fixup
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|pcibios_fixup_irqs
r_void
id|__init
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|slot
comma
id|func
suffix:semicolon
r_int
r_char
id|pin
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_const
r_int
id|internal_func_irqs
(braket
l_int|7
)braket
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
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|func
op_assign
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|0x01
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Internal device 1 is actually 7 different&n;&t;&t;&t; * internal devices on the IT8172G (multi-function&n;&t;&t;&t; * device).&n;&t;&t;&t; */
r_if
c_cond
(paren
id|func
OL
l_int|7
)paren
id|dev-&gt;irq
op_assign
id|internal_func_irqs
(braket
id|func
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x11
suffix:colon
singleline_comment|// Realtek RTL-8139
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* pin A, hardware bug */
r_case
l_int|1
suffix:colon
multiline_comment|/* pin A */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTC_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* pin B */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTD_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* pin C */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTA_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* pin D */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTB_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev-&gt;irq
op_assign
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x12
suffix:colon
singleline_comment|// ivr slot
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* pin A, hardware bug */
r_case
l_int|1
suffix:colon
multiline_comment|/* pin A */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTB_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* pin B */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTB_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* pin C */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTC_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* pin D */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTD_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev-&gt;irq
op_assign
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x13
suffix:colon
singleline_comment|// expansion slot
r_switch
c_cond
(paren
id|pin
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* pin A, hardware bug */
r_case
l_int|1
suffix:colon
multiline_comment|/* pin A */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTA_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* pin B */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTB_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* pin C */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTC_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* pin D */
id|dev-&gt;irq
op_assign
id|IT8172_PCI_INTD_IRQ
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev-&gt;irq
op_assign
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;irq fixup: slot %d, int line %d, int number %d&bslash;n&quot;
comma
id|slot
comma
id|pin
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
eof
