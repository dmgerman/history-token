multiline_comment|/*&n; * FILE NAME&n; *&t;include/asm-mips/vr41xx/e55.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for CASIO CASSIOPEIA E-10/15/55/65.&n; *&n; * Copyright 2002 Yoichi Yuasa&n; *                yuasa@hh.iij4u.or.jp&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; */
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
DECL|macro|VR41XX_ISA_IO_BASE
mdefine_line|#define VR41XX_ISA_IO_BASE&t;&t;0x14000000
DECL|macro|VR41XX_ISA_IO_SIZE
mdefine_line|#define VR41XX_ISA_IO_SIZE&t;&t;0x04000000
DECL|macro|IO_PORT_BASE
mdefine_line|#define IO_PORT_BASE&t;&t;&t;KSEG1ADDR(VR41XX_ISA_IO_BASE)
DECL|macro|IO_PORT_RESOURCE_START
mdefine_line|#define IO_PORT_RESOURCE_START&t;&t;0
DECL|macro|IO_PORT_RESOURCE_END
mdefine_line|#define IO_PORT_RESOURCE_END&t;&t;VR41XX_ISA_IO_SIZE
DECL|macro|IO_MEM_RESOURCE_START
mdefine_line|#define IO_MEM_RESOURCE_START&t;&t;VR41XX_ISA_MEM_BASE
DECL|macro|IO_MEM_RESOURCE_END
mdefine_line|#define IO_MEM_RESOURCE_END&t;&t;(VR41XX_ISA_MEM_BASE + VR41XX_ISA_MEM_SIZE)
macro_line|#endif /* __CASIO_E55_H */
eof
