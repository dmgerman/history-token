multiline_comment|/*&n; *  e55.h, Include file for CASIO CASSIOPEIA E-10/15/55/65.&n; *&n; *  Copyright (C) 2002-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __CASIO_E55_H
DECL|macro|__CASIO_E55_H
mdefine_line|#define __CASIO_E55_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * Board specific address mapping&n; */
DECL|macro|VR41XX_ISA_MEM_BASE
mdefine_line|#define VR41XX_ISA_MEM_BASE&t;&t;0x10000000
DECL|macro|VR41XX_ISA_MEM_SIZE
mdefine_line|#define VR41XX_ISA_MEM_SIZE&t;&t;0x04000000
multiline_comment|/* VR41XX_ISA_IO_BASE includes offset from real base. */
DECL|macro|VR41XX_ISA_IO_BASE
mdefine_line|#define VR41XX_ISA_IO_BASE&t;&t;0x1400c000
DECL|macro|VR41XX_ISA_IO_SIZE
mdefine_line|#define VR41XX_ISA_IO_SIZE&t;&t;0x03ff4000
DECL|macro|ISA_BUS_IO_BASE
mdefine_line|#define ISA_BUS_IO_BASE&t;&t;&t;0
DECL|macro|ISA_BUS_IO_SIZE
mdefine_line|#define ISA_BUS_IO_SIZE&t;&t;&t;VR41XX_ISA_IO_SIZE
DECL|macro|IO_PORT_BASE
mdefine_line|#define IO_PORT_BASE&t;&t;&t;KSEG1ADDR(VR41XX_ISA_IO_BASE)
DECL|macro|IO_PORT_RESOURCE_START
mdefine_line|#define IO_PORT_RESOURCE_START&t;&t;ISA_BUS_IO_BASE
DECL|macro|IO_PORT_RESOURCE_END
mdefine_line|#define IO_PORT_RESOURCE_END&t;&t;(ISA_BUS_IO_BASE + ISA_BUS_IO_SIZE - 1)
macro_line|#endif /* __CASIO_E55_H */
eof
