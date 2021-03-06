multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/pci-integrator.c&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *&n; *  PCI functions for Integrator&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/* &n; * A small note about bridges and interrupts.  The DECchip 21050 (and&n; * later) adheres to the PCI-PCI bridge specification.  This says that&n; * the interrupts on the other side of a bridge are swizzled in the&n; * following manner:&n; *&n; * Dev    Interrupt   Interrupt &n; *        Pin on      Pin on &n; *        Device      Connector&n; *&n; *   4    A           A&n; *        B           B&n; *        C           C&n; *        D           D&n; * &n; *   5    A           B&n; *        B           C&n; *        C           D&n; *        D           A&n; *&n; *   6    A           C&n; *        B           D&n; *        C           A&n; *        D           B&n; *&n; *   7    A           D&n; *        B           A&n; *        C           B&n; *        D           C&n; *&n; * Where A = pin 1, B = pin 2 and so on and pin=0 = default = A.&n; * Thus, each swizzle is ((pin-1) + (device#-4)) % 4&n; *&n; * The following code swizzles for exactly one bridge.  &n; */
DECL|function|bridge_swizzle
r_static
r_inline
r_int
id|bridge_swizzle
c_func
(paren
r_int
id|pin
comma
r_int
r_int
id|slot
)paren
(brace
r_return
(paren
id|pin
op_plus
id|slot
)paren
op_amp
l_int|3
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine handles multiple bridges.&n; */
DECL|function|integrator_swizzle
r_static
id|u8
id|__init
id|integrator_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pinp
)paren
(brace
r_int
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_if
c_cond
(paren
id|pin
op_eq
l_int|0
)paren
id|pin
op_assign
l_int|1
suffix:semicolon
id|pin
op_sub_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
(brace
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * move up the chain of bridges, swizzling as we go.&n;&t;&t; */
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
)brace
op_star
id|pinp
op_assign
id|pin
op_plus
l_int|1
suffix:semicolon
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_int
id|irq_tab
(braket
l_int|4
)braket
id|__initdata
op_assign
(brace
id|IRQ_AP_PCIINT0
comma
id|IRQ_AP_PCIINT1
comma
id|IRQ_AP_PCIINT2
comma
id|IRQ_AP_PCIINT3
)brace
suffix:semicolon
multiline_comment|/*&n; * map the specified device/slot/pin to an IRQ.  This works out such&n; * that slot 9 pin 1 is INT0, pin 2 is INT1, and slot 10 pin 1 is INT1.&n; */
DECL|function|integrator_map_irq
r_static
r_int
id|__init
id|integrator_map_irq
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
id|intnr
op_assign
(paren
(paren
id|slot
op_minus
l_int|9
)paren
op_plus
(paren
id|pin
op_minus
l_int|1
)paren
)paren
op_amp
l_int|3
suffix:semicolon
r_return
id|irq_tab
(braket
id|intnr
)braket
suffix:semicolon
)brace
r_extern
r_void
id|pci_v3_init
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|hw_pci
id|integrator_pci
id|__initdata
op_assign
(brace
dot
id|swizzle
op_assign
id|integrator_swizzle
comma
dot
id|map_irq
op_assign
id|integrator_map_irq
comma
dot
id|setup
op_assign
id|pci_v3_setup
comma
dot
id|nr_controllers
op_assign
l_int|1
comma
dot
id|scan
op_assign
id|pci_v3_scan_bus
comma
dot
id|preinit
op_assign
id|pci_v3_preinit
comma
dot
id|postinit
op_assign
id|pci_v3_postinit
comma
)brace
suffix:semicolon
DECL|function|integrator_pci_init
r_static
r_int
id|__init
id|integrator_pci_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_integrator
c_func
(paren
)paren
)paren
id|pci_common_init
c_func
(paren
op_amp
id|integrator_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|integrator_pci_init
id|subsys_initcall
c_func
(paren
id|integrator_pci_init
)paren
suffix:semicolon
eof
