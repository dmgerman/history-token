multiline_comment|/*&n; * include/asm-ppc/fsl_ocp.h&n; *&n; * Definitions for the on-chip peripherals on Freescale PPC processors&n; *&n; * Maintainer: Kumar Gala (kumar.gala@freescale.com)&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_FS_OCP_H__
DECL|macro|__ASM_FS_OCP_H__
mdefine_line|#define __ASM_FS_OCP_H__
multiline_comment|/* A table of information for supporting the Gianfar Ethernet Controller&n; * This helps identify which enet controller we are dealing with,&n; * and what type of enet controller it is&n; */
DECL|struct|ocp_gfar_data
r_struct
id|ocp_gfar_data
(brace
DECL|member|interruptTransmit
id|uint
id|interruptTransmit
suffix:semicolon
DECL|member|interruptError
id|uint
id|interruptError
suffix:semicolon
DECL|member|interruptReceive
id|uint
id|interruptReceive
suffix:semicolon
DECL|member|interruptPHY
id|uint
id|interruptPHY
suffix:semicolon
DECL|member|flags
id|uint
id|flags
suffix:semicolon
DECL|member|phyid
id|uint
id|phyid
suffix:semicolon
DECL|member|phyregidx
id|uint
id|phyregidx
suffix:semicolon
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags in the flags field */
DECL|macro|GFAR_HAS_COALESCE
mdefine_line|#define GFAR_HAS_COALESCE&t;&t;0x20
DECL|macro|GFAR_HAS_RMON
mdefine_line|#define GFAR_HAS_RMON&t;&t;&t;0x10
DECL|macro|GFAR_HAS_MULTI_INTR
mdefine_line|#define GFAR_HAS_MULTI_INTR&t;&t;0x08
DECL|macro|GFAR_FIRM_SET_MACADDR
mdefine_line|#define GFAR_FIRM_SET_MACADDR&t;&t;0x04
DECL|macro|GFAR_HAS_PHY_INTR
mdefine_line|#define GFAR_HAS_PHY_INTR&t;&t;0x02&t;/* if not set use a timer */
DECL|macro|GFAR_HAS_GIGABIT
mdefine_line|#define GFAR_HAS_GIGABIT&t;&t;0x01
multiline_comment|/* Data structure for I2C support.  Just contains a couple flags&n; * to distinguish various I2C implementations*/
DECL|struct|ocp_fs_i2c_data
r_struct
id|ocp_fs_i2c_data
(brace
DECL|member|flags
id|uint
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags for I2C */
DECL|macro|FS_I2C_SEPARATE_DFSRR
mdefine_line|#define FS_I2C_SEPARATE_DFSRR&t;0x02
DECL|macro|FS_I2C_32BIT
mdefine_line|#define FS_I2C_32BIT&t;&t;0x01
macro_line|#endif&t;/* __ASM_FS_OCP_H__ */
macro_line|#endif&t;/* __KERNEL__ */
eof
