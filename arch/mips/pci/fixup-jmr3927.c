multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Board specific pci fixups.&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/jmr3927/jmr3927.h&gt;
DECL|macro|DEBUG
macro_line|#undef&t;DEBUG
macro_line|#ifdef &t;DEBUG
DECL|macro|DBG
mdefine_line|#define&t;DBG(x...)&t;printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define&t;DBG(x...)
macro_line|#endif
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
multiline_comment|/* will need to fixup IO resources */
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
multiline_comment|/* nothing to do here */
)brace
DECL|function|pci_get_irq
r_int
id|pci_get_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pin
)paren
(brace
r_int
r_char
id|irq
op_assign
id|pin
suffix:semicolon
multiline_comment|/* IRQ rotation (PICMG) */
id|irq
op_decrement
suffix:semicolon
multiline_comment|/* 0-3 */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;parent
op_eq
l_int|NULL
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
id|TX3927_PCIC_IDSEL_AD_TO_SLOT
c_func
(paren
l_int|23
)paren
)paren
(brace
multiline_comment|/* PCI CardSlot (IDSEL=A23, DevNu=12) */
multiline_comment|/* PCIA =&gt; PCIC (IDSEL=A23) */
multiline_comment|/* NOTE: JMR3927 JP1 must be set to OPEN */
id|irq
op_assign
(paren
id|irq
op_plus
l_int|2
)paren
op_mod
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;parent
op_eq
l_int|NULL
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
id|TX3927_PCIC_IDSEL_AD_TO_SLOT
c_func
(paren
l_int|22
)paren
)paren
(brace
multiline_comment|/* PCI CardSlot (IDSEL=A22, DevNu=11) */
multiline_comment|/* PCIA =&gt; PCIA (IDSEL=A22) */
multiline_comment|/* NOTE: JMR3927 JP1 must be set to OPEN */
id|irq
op_assign
(paren
id|irq
op_plus
l_int|0
)paren
op_mod
l_int|4
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* PCI Backplane */
id|irq
op_assign
(paren
id|irq
op_plus
l_int|3
op_plus
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
op_mod
l_int|4
suffix:semicolon
macro_line|#if 0&t;&t;&t;&t;/* ??? */
r_for
c_loop
(paren
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
id|bus-&gt;parent
op_ne
l_int|NULL
suffix:semicolon
id|bus
op_assign
id|bus-&gt;parent
)paren
(brace
id|irq
op_assign
(paren
id|irq
op_plus
l_int|3
op_plus
id|PCI_SLOT
c_func
(paren
id|bus-&gt;self-&gt;devfn
)paren
)paren
op_mod
l_int|4
suffix:semicolon
)brace
macro_line|#endif
)brace
id|irq
op_increment
suffix:semicolon
multiline_comment|/* 1-4 */
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|1
suffix:colon
id|irq
op_assign
id|JMR3927_IRQ_IOC_PCIA
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
singleline_comment|// wrong for backplane irq = JMR3927_IRQ_IOC_PCIB;
id|irq
op_assign
id|JMR3927_IRQ_IOC_PCID
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irq
op_assign
id|JMR3927_IRQ_IOC_PCIC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
singleline_comment|// wrong for backplane irq = JMR3927_IRQ_IOC_PCID;
id|irq
op_assign
id|JMR3927_IRQ_IOC_PCIB
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Check OnBoard Ethernet (IDSEL=A24, DevNu=13) */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;parent
op_eq
l_int|NULL
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
id|TX3927_PCIC_IDSEL_AD_TO_SLOT
c_func
(paren
l_int|24
)paren
)paren
(brace
r_extern
r_int
id|jmr3927_ether1_irq
suffix:semicolon
multiline_comment|/* check this irq line was reserved for ether1 */
r_if
c_cond
(paren
id|jmr3927_ether1_irq
op_ne
id|JMR3927_IRQ_ETHER0
)paren
id|irq
op_assign
id|JMR3927_IRQ_ETHER0
suffix:semicolon
r_else
id|irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable */
)brace
r_return
id|irq
suffix:semicolon
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
r_char
id|irq
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
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
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* SMSC SLC90E66 IDE uses irq 14, 15 (default) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_EFAR
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_EFAR_SLC90E66_1
)paren
)paren
(brace
id|irq
op_assign
id|pci_get_irq
c_func
(paren
id|dev
comma
id|irq
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: %02x:%02x IRQ %02x&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
)brace
eof
