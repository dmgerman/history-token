multiline_comment|/*&n; *  fixup-mpc30x.c, The Victor MP-C303/304 specific PCI fixups.&n; *&n; *  Copyright (C) 2002,2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/vr41xx/mpc30x.h&gt;
macro_line|#include &lt;asm/vr41xx/vrc4173.h&gt;
DECL|variable|__initdata
r_static
r_const
r_int
id|internal_func_irqs
(braket
)braket
id|__initdata
op_assign
(brace
id|VRC4173_CASCADE_IRQ
comma
id|VRC4173_AC97_IRQ
comma
id|VRC4173_USB_IRQ
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_const
r_int
id|irq_tab_mpc30x
(braket
)braket
id|__initdata
op_assign
(brace
(braket
l_int|12
)braket
op_assign
id|VRC4173_PCMCIA1_IRQ
comma
(braket
l_int|13
)braket
op_assign
id|VRC4173_PCMCIA2_IRQ
comma
(braket
l_int|29
)braket
op_assign
id|MQ200_IRQ
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
r_if
c_cond
(paren
id|slot
op_eq
l_int|30
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
id|irq_tab_mpc30x
(braket
id|slot
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
