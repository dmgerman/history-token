multiline_comment|/*&n; * FILE NAME&n; *&t;include/asm-mips/vr41xx/mpc30x.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for Victor MP-C303/304.&n; *&n; * Copyright 2002,2003 Yoichi Yuasa&n; *                yuasa@hh.iij4u.or.jp&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; */
macro_line|#ifndef __VICTOR_MPC30X_H
DECL|macro|__VICTOR_MPC30X_H
mdefine_line|#define __VICTOR_MPC30X_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * Board specific address mapping&n; */
DECL|macro|VR41XX_PCI_MEM1_BASE
mdefine_line|#define VR41XX_PCI_MEM1_BASE&t;&t;0x10000000
DECL|macro|VR41XX_PCI_MEM1_SIZE
mdefine_line|#define VR41XX_PCI_MEM1_SIZE&t;&t;0x04000000
DECL|macro|VR41XX_PCI_MEM1_MASK
mdefine_line|#define VR41XX_PCI_MEM1_MASK&t;&t;0x7c000000
DECL|macro|VR41XX_PCI_MEM2_BASE
mdefine_line|#define VR41XX_PCI_MEM2_BASE&t;&t;0x14000000
DECL|macro|VR41XX_PCI_MEM2_SIZE
mdefine_line|#define VR41XX_PCI_MEM2_SIZE&t;&t;0x02000000
DECL|macro|VR41XX_PCI_MEM2_MASK
mdefine_line|#define VR41XX_PCI_MEM2_MASK&t;&t;0x7e000000
DECL|macro|VR41XX_PCI_IO_BASE
mdefine_line|#define VR41XX_PCI_IO_BASE&t;&t;0x16000000
DECL|macro|VR41XX_PCI_IO_SIZE
mdefine_line|#define VR41XX_PCI_IO_SIZE&t;&t;0x02000000
DECL|macro|VR41XX_PCI_IO_MASK
mdefine_line|#define VR41XX_PCI_IO_MASK&t;&t;0x7e000000
DECL|macro|VR41XX_PCI_IO_START
mdefine_line|#define VR41XX_PCI_IO_START&t;&t;0x01000000
DECL|macro|VR41XX_PCI_IO_END
mdefine_line|#define VR41XX_PCI_IO_END&t;&t;0x01ffffff
DECL|macro|VR41XX_PCI_MEM_START
mdefine_line|#define VR41XX_PCI_MEM_START&t;&t;0x12000000
DECL|macro|VR41XX_PCI_MEM_END
mdefine_line|#define VR41XX_PCI_MEM_END&t;&t;0x15ffffff
DECL|macro|IO_PORT_BASE
mdefine_line|#define IO_PORT_BASE&t;&t;&t;KSEG1ADDR(VR41XX_PCI_IO_BASE)
DECL|macro|IO_PORT_RESOURCE_START
mdefine_line|#define IO_PORT_RESOURCE_START&t;&t;0
DECL|macro|IO_PORT_RESOURCE_END
mdefine_line|#define IO_PORT_RESOURCE_END&t;&t;VR41XX_PCI_IO_SIZE
DECL|macro|IO_MEM1_RESOURCE_START
mdefine_line|#define IO_MEM1_RESOURCE_START&t;&t;VR41XX_PCI_MEM1_BASE
DECL|macro|IO_MEM1_RESOURCE_END
mdefine_line|#define IO_MEM1_RESOURCE_END&t;&t;(VR41XX_PCI_MEM1_BASE + VR41XX_PCI_MEM1_SIZE)
DECL|macro|IO_MEM2_RESOURCE_START
mdefine_line|#define IO_MEM2_RESOURCE_START&t;&t;VR41XX_PCI_MEM2_BASE
DECL|macro|IO_MEM2_RESOURCE_END
mdefine_line|#define IO_MEM2_RESOURCE_END&t;&t;(VR41XX_PCI_MEM2_BASE + VR41XX_PCI_MEM2_SIZE)
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
