multiline_comment|/*&n; * arch/ppc/platforms/pcore.h&n; * &n; * Definitions for Force PowerCore board support&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __PPC_PLATFORMS_PCORE_H
DECL|macro|__PPC_PLATFORMS_PCORE_H
mdefine_line|#define __PPC_PLATFORMS_PCORE_H
macro_line|#include &lt;asm/mpc10x.h&gt;
DECL|macro|PCORE_TYPE_6750
mdefine_line|#define PCORE_TYPE_6750&t;&t;&t;1
DECL|macro|PCORE_TYPE_680
mdefine_line|#define PCORE_TYPE_680&t;&t;&t;2
DECL|macro|PCORE_NVRAM_AS0
mdefine_line|#define PCORE_NVRAM_AS0&t;&t;&t;0x73
DECL|macro|PCORE_NVRAM_AS1
mdefine_line|#define PCORE_NVRAM_AS1&t;&t;&t;0x75
DECL|macro|PCORE_NVRAM_DATA
mdefine_line|#define PCORE_NVRAM_DATA&t;&t;0x77    
DECL|macro|PCORE_DCCR_REG
mdefine_line|#define PCORE_DCCR_REG&t;&t;&t;(MPC10X_MAPB_ISA_IO_BASE + 0x308)
DECL|macro|PCORE_DCCR_L2_MASK
mdefine_line|#define PCORE_DCCR_L2_MASK&t;&t;0xc0
DECL|macro|PCORE_DCCR_L2_0KB
mdefine_line|#define PCORE_DCCR_L2_0KB&t;&t;0x00
DECL|macro|PCORE_DCCR_L2_256KB
mdefine_line|#define PCORE_DCCR_L2_256KB&t;&t;0x40
DECL|macro|PCORE_DCCR_L2_512KB
mdefine_line|#define PCORE_DCCR_L2_512KB&t;&t;0xc0
DECL|macro|PCORE_DCCR_L2_1MB
mdefine_line|#define PCORE_DCCR_L2_1MB&t;&t;0x80
DECL|macro|PCORE_DCCR_L2_2MB
mdefine_line|#define PCORE_DCCR_L2_2MB&t;&t;0x00
DECL|macro|PCORE_WINBOND_IDE_INT
mdefine_line|#define PCORE_WINBOND_IDE_INT&t;&t;0x43
DECL|macro|PCORE_WINBOND_PCI_INT
mdefine_line|#define PCORE_WINBOND_PCI_INT&t;&t;0x44
DECL|macro|PCORE_WINBOND_PRI_EDG_LVL
mdefine_line|#define PCORE_WINBOND_PRI_EDG_LVL&t;0x4d0
DECL|macro|PCORE_WINBOND_SEC_EDG_LVL
mdefine_line|#define PCORE_WINBOND_SEC_EDG_LVL&t;0x4d1
macro_line|#endif /* __PPC_PLATFORMS_PCORE_H */
eof
