multiline_comment|/*&n; *  fixup-cappcela.c, The ZAO Networks Capcella specific PCI fixups.&n; *&n; *  Copyright (C) 2002,2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/vr41xx/capcella.h&gt;
multiline_comment|/*&n; * Shortcuts&n; */
DECL|macro|INT1
mdefine_line|#define INT1&t;RTL8139_1_IRQ
DECL|macro|INT2
mdefine_line|#define INT2&t;RTL8139_2_IRQ
DECL|macro|INTA
mdefine_line|#define INTA&t;PC104PLUS_INTA_IRQ
DECL|macro|INTB
mdefine_line|#define INTB&t;PC104PLUS_INTB_IRQ
DECL|macro|INTC
mdefine_line|#define INTC&t;PC104PLUS_INTC_IRQ
DECL|macro|INTD
mdefine_line|#define INTD&t;PC104PLUS_INTD_IRQ
DECL|variable|__initdata
r_static
r_char
id|irq_tab_capcella
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
id|INT1
comma
id|INT1
comma
id|INT1
comma
id|INT1
)brace
comma
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
id|INT2
comma
id|INT2
comma
id|INT2
comma
id|INT2
)brace
comma
(braket
l_int|14
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
r_return
id|irq_tab_capcella
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
