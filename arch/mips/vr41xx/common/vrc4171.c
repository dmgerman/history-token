multiline_comment|/*&n; *  vrc4171.c, NEC VRC4171 base driver.&n; *&n; *  Copyright (C) 2003  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/vrc4171.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NEC VRC4171 base driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|vrc4171_get_irq_status
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|vrc4171_get_irq_status
)paren
suffix:semicolon
DECL|variable|vrc4171_set_multifunction_pin
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|vrc4171_set_multifunction_pin
)paren
suffix:semicolon
DECL|macro|CONFIGURATION1
mdefine_line|#define CONFIGURATION1&t;&t;0x05fe
DECL|macro|SLOTB_CONFIG
mdefine_line|#define SLOTB_CONFIG&t;&t;0xc000
DECL|macro|SLOTB_NONE
mdefine_line|#define SLOTB_NONE&t;&t;0x0000
DECL|macro|SLOTB_PCCARD
mdefine_line|#define SLOTB_PCCARD&t;&t;0x4000
DECL|macro|SLOTB_CF
mdefine_line|#define SLOTB_CF&t;&t;0x8000
DECL|macro|SLOTB_FLASHROM
mdefine_line|#define SLOTB_FLASHROM&t;&t;0xc000
DECL|macro|CONFIGURATION2
mdefine_line|#define CONFIGURATION2&t;&t;0x05fc
DECL|macro|INTERRUPT_STATUS
mdefine_line|#define INTERRUPT_STATUS&t;0x05fa
DECL|macro|PCS_CONTROL
mdefine_line|#define PCS_CONTROL&t;&t;0x05ee
DECL|macro|GPIO_DATA
mdefine_line|#define GPIO_DATA&t;&t;PCS_CONTROL
DECL|macro|PCS0_UPPER_START
mdefine_line|#define PCS0_UPPER_START&t;0x05ec
DECL|macro|PCS0_LOWER_START
mdefine_line|#define PCS0_LOWER_START&t;0x05ea
DECL|macro|PCS0_UPPER_STOP
mdefine_line|#define PCS0_UPPER_STOP&t;&t;0x05e8
DECL|macro|PCS0_LOWER_STOP
mdefine_line|#define PCS0_LOWER_STOP&t;&t;0x05e6
DECL|macro|PCS1_UPPER_START
mdefine_line|#define PCS1_UPPER_START&t;0x05e4
DECL|macro|PCS1_LOWER_START
mdefine_line|#define PCS1_LOWER_START&t;0x05e2
DECL|macro|PCS1_UPPER_STOP
mdefine_line|#define PCS1_UPPER_STOP&t;&t;0x05de
DECL|macro|PCS1_LOWER_STOP
mdefine_line|#define PCS1_LOWER_STOP&t;&t;0x05dc
DECL|macro|VRC4171_REGS_BASE
mdefine_line|#define VRC4171_REGS_BASE&t;PCS1_LOWER_STOP
DECL|macro|VRC4171_REGS_SIZE
mdefine_line|#define VRC4171_REGS_SIZE&t;0x24
DECL|function|vrc4171_get_irq_status
r_uint16
id|vrc4171_get_irq_status
c_func
(paren
r_void
)paren
(brace
r_return
id|inw
c_func
(paren
id|INTERRUPT_STATUS
)paren
suffix:semicolon
)brace
DECL|function|vrc4171_set_multifunction_pin
r_void
id|vrc4171_set_multifunction_pin
c_func
(paren
r_int
id|config
)paren
(brace
r_uint16
id|config1
suffix:semicolon
id|config1
op_assign
id|inw
c_func
(paren
id|CONFIGURATION1
)paren
suffix:semicolon
id|config1
op_and_assign
op_complement
id|SLOTB_CONFIG
suffix:semicolon
r_switch
c_cond
(paren
id|config
)paren
(brace
r_case
id|SLOTB_IS_NONE
suffix:colon
id|config1
op_or_assign
id|SLOTB_NONE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SLOTB_IS_PCCARD
suffix:colon
id|config1
op_or_assign
id|SLOTB_PCCARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SLOTB_IS_CF
suffix:colon
id|config1
op_or_assign
id|SLOTB_CF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SLOTB_IS_FLASHROM
suffix:colon
id|config1
op_or_assign
id|SLOTB_FLASHROM
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|outw
c_func
(paren
id|config1
comma
id|CONFIGURATION1
)paren
suffix:semicolon
)brace
DECL|function|vrc4171_init
r_static
r_int
id|__devinit
id|vrc4171_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|VRC4171_REGS_BASE
comma
id|VRC4171_REGS_SIZE
comma
l_string|&quot;NEC VRC4171&quot;
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NEC VRC4171 base driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vrc4171_exit
r_static
r_void
id|__devexit
id|vrc4171_exit
c_func
(paren
r_void
)paren
(brace
id|release_region
c_func
(paren
id|VRC4171_REGS_BASE
comma
id|VRC4171_REGS_SIZE
)paren
suffix:semicolon
)brace
DECL|variable|vrc4171_init
id|module_init
c_func
(paren
id|vrc4171_init
)paren
suffix:semicolon
DECL|variable|vrc4171_exit
id|module_exit
c_func
(paren
id|vrc4171_exit
)paren
suffix:semicolon
eof
