multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *      Board specific pci fixups for the Toshiba rbtx4927&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *              ppopov@mvista.com or source@mvista.com&n; *&n; * Copyright (C) 2000-2001 Toshiba Corporation &n; *&n; * Copyright (C) 2004 MontaVista Software Inc.&n; * Author: Manish Lachwani (mlachwani@mvista.com)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/tx4927/tx4927.h&gt;
macro_line|#include &lt;asm/tx4927/tx4927_pci.h&gt;
DECL|macro|DEBUG
macro_line|#undef  DEBUG
macro_line|#ifdef  DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...)       printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
multiline_comment|/* look up table for backplane pci irq for slots 17-20 by pin # */
DECL|variable|backplane_pci_irq
r_static
r_int
r_char
id|backplane_pci_irq
(braket
l_int|4
)braket
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/* PJ6 SLOT:  17, PIN: 1 */
(brace
id|TX4927_IRQ_IOC_PCIA
comma
multiline_comment|/* PJ6 SLOT:  17, PIN: 2 */
id|TX4927_IRQ_IOC_PCIB
comma
multiline_comment|/* PJ6 SLOT:  17, PIN: 3 */
id|TX4927_IRQ_IOC_PCIC
comma
multiline_comment|/* PJ6 SLOT:  17, PIN: 4 */
id|TX4927_IRQ_IOC_PCID
)brace
comma
multiline_comment|/* SB  SLOT:  18, PIN: 1 */
(brace
id|TX4927_IRQ_IOC_PCIB
comma
multiline_comment|/* SB  SLOT:  18, PIN: 2 */
id|TX4927_IRQ_IOC_PCIC
comma
multiline_comment|/* SB  SLOT:  18, PIN: 3 */
id|TX4927_IRQ_IOC_PCID
comma
multiline_comment|/* SB  SLOT:  18, PIN: 4 */
id|TX4927_IRQ_IOC_PCIA
)brace
comma
multiline_comment|/* PJ5 SLOT:  19, PIN: 1 */
(brace
id|TX4927_IRQ_IOC_PCIC
comma
multiline_comment|/* PJ5 SLOT:  19, PIN: 2 */
id|TX4927_IRQ_IOC_PCID
comma
multiline_comment|/* PJ5 SLOT:  19, PIN: 3 */
id|TX4927_IRQ_IOC_PCIA
comma
multiline_comment|/* PJ5 SLOT:  19, PIN: 4 */
id|TX4927_IRQ_IOC_PCIB
)brace
comma
multiline_comment|/* PJ4 SLOT:  20, PIN: 1 */
(brace
id|TX4927_IRQ_IOC_PCID
comma
multiline_comment|/* PJ4 SLOT:  20, PIN: 2 */
id|TX4927_IRQ_IOC_PCIA
comma
multiline_comment|/* PJ4 SLOT:  20, PIN: 3 */
id|TX4927_IRQ_IOC_PCIB
comma
multiline_comment|/* PJ4 SLOT:  20, PIN: 4 */
id|TX4927_IRQ_IOC_PCIC
)brace
)brace
suffix:semicolon
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
id|DBG
c_func
(paren
l_string|&quot;pci_get_irq: pin is %d&bslash;n&quot;
comma
id|pin
)paren
suffix:semicolon
multiline_comment|/* IRQ rotation */
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
id|TX4927_PCIC_IDSEL_AD_TO_SLOT
c_func
(paren
l_int|23
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Onboard PCI_SLOT(dev-&gt;devfn) is %d&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
multiline_comment|/* IDSEL=A23 is tx4927 onboard pci slot */
id|irq
op_assign
(paren
id|irq
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
id|irq
op_increment
suffix:semicolon
multiline_comment|/* 1-4 */
id|DBG
c_func
(paren
l_string|&quot;irq is now %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
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
id|TX4927_IRQ_IOC_PCIA
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|irq
op_assign
id|TX4927_IRQ_IOC_PCIB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irq
op_assign
id|TX4927_IRQ_IOC_PCIC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|irq
op_assign
id|TX4927_IRQ_IOC_PCID
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* PCI Backplane */
id|DBG
c_func
(paren
l_string|&quot;PCI Backplane PCI_SLOT(dev-&gt;devfn) is %d&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|irq
op_assign
id|backplane_pci_irq
(braket
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_minus
l_int|17
)braket
(braket
id|irq
)braket
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;assigned irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
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
r_int
r_char
id|irq
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI Setup for pin %d &bslash;n&quot;
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
l_int|0x9130
)paren
multiline_comment|/* IDE */
id|irq
op_assign
l_int|14
suffix:semicolon
r_else
id|irq
op_assign
id|pci_get_irq
c_func
(paren
id|dev
comma
id|pin
)paren
suffix:semicolon
r_return
id|irq
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
