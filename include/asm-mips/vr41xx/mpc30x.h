multiline_comment|/*&n; *  mpc30x.h, Include file for Victor MP-C303/304.&n; *&n; *  Copyright (C) 2002-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __VICTOR_MPC30X_H
DECL|macro|__VICTOR_MPC30X_H
mdefine_line|#define __VICTOR_MPC30X_H
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * General-Purpose I/O Pin Number&n; */
DECL|macro|VRC4173_PIN
mdefine_line|#define VRC4173_PIN&t;&t;&t;1
DECL|macro|MQ200_PIN
mdefine_line|#define MQ200_PIN&t;&t;&t;4
multiline_comment|/*&n; * Interrupt Number&n; */
DECL|macro|VRC4173_CASCADE_IRQ
mdefine_line|#define VRC4173_CASCADE_IRQ&t;&t;GIU_IRQ(VRC4173_PIN)
DECL|macro|MQ200_IRQ
mdefine_line|#define MQ200_IRQ&t;&t;&t;GIU_IRQ(MQ200_PIN)
macro_line|#endif /* __VICTOR_MPC30X_H */
eof
