multiline_comment|/*&n; *  capcella.h, Include file for ZAO Networks Capcella.&n; *&n; *  Copyright (C) 2002-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ZAO_CAPCELLA_H
DECL|macro|__ZAO_CAPCELLA_H
mdefine_line|#define __ZAO_CAPCELLA_H
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * General-Purpose I/O Pin Number&n; */
DECL|macro|PC104PLUS_INTA_PIN
mdefine_line|#define PC104PLUS_INTA_PIN&t;&t;2
DECL|macro|PC104PLUS_INTB_PIN
mdefine_line|#define PC104PLUS_INTB_PIN&t;&t;3
DECL|macro|PC104PLUS_INTC_PIN
mdefine_line|#define PC104PLUS_INTC_PIN&t;&t;4
DECL|macro|PC104PLUS_INTD_PIN
mdefine_line|#define PC104PLUS_INTD_PIN&t;&t;5
multiline_comment|/*&n; * Interrupt Number&n; */
DECL|macro|RTL8139_1_IRQ
mdefine_line|#define RTL8139_1_IRQ&t;&t;&t;GIU_IRQ(PC104PLUS_INTC_PIN)
DECL|macro|RTL8139_2_IRQ
mdefine_line|#define RTL8139_2_IRQ&t;&t;&t;GIU_IRQ(PC104PLUS_INTD_PIN)
DECL|macro|PC104PLUS_INTA_IRQ
mdefine_line|#define PC104PLUS_INTA_IRQ&t;&t;GIU_IRQ(PC104PLUS_INTA_PIN)
DECL|macro|PC104PLUS_INTB_IRQ
mdefine_line|#define PC104PLUS_INTB_IRQ&t;&t;GIU_IRQ(PC104PLUS_INTB_PIN)
DECL|macro|PC104PLUS_INTC_IRQ
mdefine_line|#define PC104PLUS_INTC_IRQ&t;&t;GIU_IRQ(PC104PLUS_INTC_PIN)
DECL|macro|PC104PLUS_INTD_IRQ
mdefine_line|#define PC104PLUS_INTD_IRQ&t;&t;GIU_IRQ(PC104PLUS_INTD_PIN)
macro_line|#endif /* __ZAO_CAPCELLA_H */
eof
