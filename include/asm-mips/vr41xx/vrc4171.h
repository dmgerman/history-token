multiline_comment|/*&n; *  vrc4171.h, Include file for NEC VRC4171.&n; *&n; *  Copyright (C) 2003  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __NEC_VRC4171_H 
DECL|macro|__NEC_VRC4171_H
mdefine_line|#define __NEC_VRC4171_H 
multiline_comment|/*&n; * Configuration 1&n; */
r_enum
(brace
DECL|enumerator|SLOTB_IS_NONE
id|SLOTB_IS_NONE
comma
DECL|enumerator|SLOTB_IS_PCCARD
id|SLOTB_IS_PCCARD
comma
DECL|enumerator|SLOTB_IS_CF
id|SLOTB_IS_CF
comma
DECL|enumerator|SLOTB_IS_FLASHROM
id|SLOTB_IS_FLASHROM
)brace
suffix:semicolon
r_extern
r_void
id|vrc4171_set_multifunction_pin
c_func
(paren
r_int
id|config
)paren
suffix:semicolon
multiline_comment|/*&n; * Interrupt Status Mask&n; */
DECL|macro|IRQ_A
mdefine_line|#define IRQ_A&t;0x02
DECL|macro|IRQ_B
mdefine_line|#define IRQ_B&t;0x04
r_extern
r_uint16
id|vrc4171_get_irq_status
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __NEC_VRC4171_H */
eof
