multiline_comment|/*&n; * FILE NAME&n; *&t;drivers/char/vrc4173.c&n; * &n; * BRIEF MODULE DESCRIPTION&n; *&t;NEC VRC4173 driver for NEC VR4122/VR4131.&n; *&n; * Author: Yoichi Yuasa&n; *         yyuasa@mvista.com or source@mvista.com&n; *&n; * Copyright 2001,2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
macro_line|#include &lt;asm/vr41xx/vrc4173.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NEC VRC4173 driver for NEC VR4122/4131&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Yoichi Yuasa &lt;yyuasa@mvista.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|VRC4173_CMUCLKMSK
mdefine_line|#define VRC4173_CMUCLKMSK&t;0x040
DECL|macro|VRC4173_CMUSRST
mdefine_line|#define VRC4173_CMUSRST&t;&t;0x042
DECL|macro|VRC4173_SELECTREG
mdefine_line|#define VRC4173_SELECTREG&t;0x09e
DECL|macro|VRC4173_SYSINT1REG
mdefine_line|#define VRC4173_SYSINT1REG&t;0x060
DECL|macro|VRC4173_MSYSINT1REG
mdefine_line|#define VRC4173_MSYSINT1REG&t;0x06c
DECL|variable|vrc4173_table
r_static
r_struct
id|pci_device_id
id|vrc4173_table
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_NEC
comma
id|PCI_DEVICE_ID_NEC_VRC4173
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|vrc4173_io_offset
r_int
r_int
id|vrc4173_io_offset
op_assign
l_int|0
suffix:semicolon
DECL|variable|vrc4173_io_offset
id|EXPORT_SYMBOL
c_func
(paren
id|vrc4173_io_offset
)paren
suffix:semicolon
DECL|variable|vrc4173_cmuclkmsk
r_static
id|u16
id|vrc4173_cmuclkmsk
suffix:semicolon
DECL|variable|vrc4173_initialized
r_static
r_int
id|vrc4173_initialized
suffix:semicolon
DECL|function|vrc4173_clock_supply
r_void
id|vrc4173_clock_supply
c_func
(paren
id|u16
id|mask
)paren
(brace
r_if
c_cond
(paren
id|vrc4173_initialized
)paren
(brace
id|vrc4173_cmuclkmsk
op_or_assign
id|mask
suffix:semicolon
id|vrc4173_outw
c_func
(paren
id|vrc4173_cmuclkmsk
comma
id|VRC4173_CMUCLKMSK
)paren
suffix:semicolon
)brace
)brace
DECL|function|vrc4173_clock_mask
r_void
id|vrc4173_clock_mask
c_func
(paren
id|u16
id|mask
)paren
(brace
r_if
c_cond
(paren
id|vrc4173_initialized
)paren
(brace
id|vrc4173_cmuclkmsk
op_and_assign
op_complement
id|mask
suffix:semicolon
id|vrc4173_outw
c_func
(paren
id|vrc4173_cmuclkmsk
comma
id|VRC4173_CMUCLKMSK
)paren
suffix:semicolon
)brace
)brace
DECL|function|vrc4173_cmu_init
r_static
r_inline
r_void
id|vrc4173_cmu_init
c_func
(paren
r_void
)paren
(brace
id|vrc4173_cmuclkmsk
op_assign
id|vrc4173_inw
c_func
(paren
id|VRC4173_CMUCLKMSK
)paren
suffix:semicolon
)brace
DECL|variable|vrc4173_clock_supply
id|EXPORT_SYMBOL
c_func
(paren
id|vrc4173_clock_supply
)paren
suffix:semicolon
DECL|variable|vrc4173_clock_mask
id|EXPORT_SYMBOL
c_func
(paren
id|vrc4173_clock_mask
)paren
suffix:semicolon
DECL|function|vrc4173_select_function
r_void
id|vrc4173_select_function
c_func
(paren
r_int
id|func
)paren
(brace
id|u16
id|val
suffix:semicolon
r_if
c_cond
(paren
id|vrc4173_initialized
)paren
(brace
id|val
op_assign
id|vrc4173_inw
c_func
(paren
id|VRC4173_SELECTREG
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|PS2CH1_SELECT
suffix:colon
id|val
op_or_assign
l_int|0x0004
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PS2CH2_SELECT
suffix:colon
id|val
op_or_assign
l_int|0x0002
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TOUCHPANEL_SELECT
suffix:colon
id|val
op_and_assign
l_int|0x0007
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KIU8_SELECT
suffix:colon
id|val
op_and_assign
l_int|0x000e
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KIU10_SELECT
suffix:colon
id|val
op_and_assign
l_int|0x000c
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KIU12_SELECT
suffix:colon
id|val
op_and_assign
l_int|0x0008
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GPIO_SELECT
suffix:colon
id|val
op_or_assign
l_int|0x0008
suffix:semicolon
r_break
suffix:semicolon
)brace
id|vrc4173_outw
c_func
(paren
id|val
comma
id|VRC4173_SELECTREG
)paren
suffix:semicolon
)brace
)brace
DECL|variable|vrc4173_select_function
id|EXPORT_SYMBOL
c_func
(paren
id|vrc4173_select_function
)paren
suffix:semicolon
DECL|function|enable_vrc4173_irq
r_static
r_void
id|enable_vrc4173_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u16
id|val
suffix:semicolon
id|val
op_assign
id|vrc4173_inw
c_func
(paren
id|VRC4173_MSYSINT1REG
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|u16
)paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|VRC4173_IRQ_BASE
)paren
suffix:semicolon
id|vrc4173_outw
c_func
(paren
id|val
comma
id|VRC4173_MSYSINT1REG
)paren
suffix:semicolon
)brace
DECL|function|disable_vrc4173_irq
r_static
r_void
id|disable_vrc4173_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u16
id|val
suffix:semicolon
id|val
op_assign
id|vrc4173_inw
c_func
(paren
id|VRC4173_MSYSINT1REG
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
(paren
id|u16
)paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|VRC4173_IRQ_BASE
)paren
)paren
suffix:semicolon
id|vrc4173_outw
c_func
(paren
id|val
comma
id|VRC4173_MSYSINT1REG
)paren
suffix:semicolon
)brace
DECL|function|startup_vrc4173_irq
r_static
r_int
r_int
id|startup_vrc4173_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_vrc4173_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
DECL|macro|shutdown_vrc4173_irq
mdefine_line|#define shutdown_vrc4173_irq&t;disable_vrc4173_irq
DECL|macro|ack_vrc4173_irq
mdefine_line|#define ack_vrc4173_irq&t;&t;disable_vrc4173_irq
DECL|function|end_vrc4173_irq
r_static
r_void
id|end_vrc4173_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_vrc4173_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|vrc4173_irq_type
r_static
r_struct
id|hw_interrupt_type
id|vrc4173_irq_type
op_assign
(brace
l_string|&quot;VRC4173&quot;
comma
id|startup_vrc4173_irq
comma
id|shutdown_vrc4173_irq
comma
id|enable_vrc4173_irq
comma
id|disable_vrc4173_irq
comma
id|ack_vrc4173_irq
comma
id|end_vrc4173_irq
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|vrc4173_get_irq_number
r_static
r_int
id|vrc4173_get_irq_number
c_func
(paren
r_int
id|irq
)paren
(brace
id|u16
id|status
comma
id|mask
suffix:semicolon
r_int
id|i
suffix:semicolon
id|status
op_assign
id|vrc4173_inw
c_func
(paren
id|VRC4173_SYSINT1REG
)paren
suffix:semicolon
id|mask
op_assign
id|vrc4173_inw
c_func
(paren
id|VRC4173_MSYSINT1REG
)paren
suffix:semicolon
id|status
op_and_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|0x0001
op_lshift
id|i
)paren
)paren
r_return
id|VRC4173_IRQ_BASE
op_plus
id|i
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|vrc4173_icu_init
r_static
r_inline
r_void
id|vrc4173_icu_init
c_func
(paren
r_int
id|cascade_irq
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cascade_irq
template_param
id|GIU_IRQ
c_func
(paren
l_int|15
)paren
)paren
r_return
suffix:semicolon
id|vrc4173_outw
c_func
(paren
l_int|0
comma
id|VRC4173_MSYSINT1REG
)paren
suffix:semicolon
id|vr41xx_set_irq_trigger
c_func
(paren
id|cascade_irq
op_minus
id|GIU_IRQ
c_func
(paren
l_int|0
)paren
comma
id|TRIGGER_LEVEL
comma
id|SIGNAL_THROUGH
)paren
suffix:semicolon
id|vr41xx_set_irq_level
c_func
(paren
id|cascade_irq
op_minus
id|GIU_IRQ
c_func
(paren
l_int|0
)paren
comma
id|LEVEL_LOW
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|VRC4173_IRQ_BASE
suffix:semicolon
id|i
op_le
id|VRC4173_IRQ_LAST
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|vrc4173_irq_type
suffix:semicolon
)brace
DECL|function|vrc4173_probe
r_static
r_int
id|__devinit
id|vrc4173_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_int
r_int
id|start
comma
id|flags
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vrc4173: failed to enable device -- err=%d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|start
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vrc4173:No PCI I/O resources, aborting&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|start
op_logical_or
(paren
(paren
(paren
id|flags
op_assign
id|pci_resource_flags
c_func
(paren
id|pdev
comma
l_int|0
)paren
)paren
op_amp
id|IORESOURCE_IO
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vrc4173: No PCI I/O resources, aborting&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_request_regions
c_func
(paren
id|pdev
comma
l_string|&quot;NEC VRC4173&quot;
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vrc4173: PCI resources are busy, aborting&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|set_vrc4173_io_offset
c_func
(paren
id|start
)paren
suffix:semicolon
id|vrc4173_cmu_init
c_func
(paren
)paren
suffix:semicolon
id|vrc4173_icu_init
c_func
(paren
id|pdev-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|vr41xx_cascade_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|vrc4173_get_irq_number
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vrc4173: IRQ resource %d is busy, aborting&bslash;n&quot;
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NEC VRC4173 at 0x%#08lx, IRQ is cascaded to %d&bslash;n&quot;
comma
id|start
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vrc4173_driver
r_static
r_struct
id|pci_driver
id|vrc4173_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;NEC VRC4173&quot;
comma
id|probe
suffix:colon
id|vrc4173_probe
comma
id|remove
suffix:colon
l_int|NULL
comma
id|id_table
suffix:colon
id|vrc4173_table
comma
)brace
suffix:semicolon
DECL|function|vrc4173_init
r_static
r_int
id|__devinit
id|vrc4173_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|vrc4173_driver
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|vrc4173_initialized
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vrc4173_exit
r_static
r_void
id|__devexit
id|vrc4173_exit
c_func
(paren
r_void
)paren
(brace
id|vrc4173_initialized
op_assign
l_int|0
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|vrc4173_driver
)paren
suffix:semicolon
)brace
DECL|variable|vrc4173_init
id|module_init
c_func
(paren
id|vrc4173_init
)paren
suffix:semicolon
DECL|variable|vrc4173_exit
id|module_exit
c_func
(paren
id|vrc4173_exit
)paren
suffix:semicolon
eof
