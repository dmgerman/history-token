multiline_comment|/*&n; *  tb0226.h, Include file for TANBAC TB0226.&n; *&n; *  Copyright (C) 2002-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __TANBAC_TB0226_H
DECL|macro|__TANBAC_TB0226_H
mdefine_line|#define __TANBAC_TB0226_H
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * General-Purpose I/O Pin Number&n; */
DECL|macro|GD82559_1_PIN
mdefine_line|#define GD82559_1_PIN&t;&t;&t;2
DECL|macro|GD82559_2_PIN
mdefine_line|#define GD82559_2_PIN&t;&t;&t;3
DECL|macro|UPD720100_INTA_PIN
mdefine_line|#define UPD720100_INTA_PIN&t;&t;4
DECL|macro|UPD720100_INTB_PIN
mdefine_line|#define UPD720100_INTB_PIN&t;&t;8
DECL|macro|UPD720100_INTC_PIN
mdefine_line|#define UPD720100_INTC_PIN&t;&t;13
multiline_comment|/*&n; * Interrupt Number&n; */
DECL|macro|GD82559_1_IRQ
mdefine_line|#define GD82559_1_IRQ&t;&t;&t;GIU_IRQ(GD82559_1_PIN)
DECL|macro|GD82559_2_IRQ
mdefine_line|#define GD82559_2_IRQ&t;&t;&t;GIU_IRQ(GD82559_2_PIN)
DECL|macro|UPD720100_INTA_IRQ
mdefine_line|#define UPD720100_INTA_IRQ&t;&t;GIU_IRQ(UPD720100_INTA_PIN)
DECL|macro|UPD720100_INTB_IRQ
mdefine_line|#define UPD720100_INTB_IRQ&t;&t;GIU_IRQ(UPD720100_INTB_PIN)
DECL|macro|UPD720100_INTC_IRQ
mdefine_line|#define UPD720100_INTC_IRQ&t;&t;GIU_IRQ(UPD720100_INTC_PIN)
macro_line|#endif /* __TANBAC_TB0226_H */
eof
