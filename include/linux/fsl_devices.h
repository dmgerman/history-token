multiline_comment|/*&n; * include/linux/fsl_devices.h&n; *&n; * Definitions for any platform device related flags or structures for&n; * Freescale processor devices&n; *&n; * Maintainer: Kumar Gala (kumar.gala@freescale.com)&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _FSL_DEVICE_H_
DECL|macro|_FSL_DEVICE_H_
mdefine_line|#define _FSL_DEVICE_H_
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Some conventions on how we handle peripherals on Freescale chips&n; *&n; * unique device: a platform_device entry in fsl_plat_devs[] plus&n; * associated device information in its platform_data structure.&n; *&n; * A chip is described by a set of unique devices.&n; *&n; * Each sub-arch has its own master list of unique devices and&n; * enumerates them by enum fsl_devices in a sub-arch specific header&n; *&n; * The platform data structure is broken into two parts.  The&n; * first is device specific information that help identify any&n; * unique features of a peripheral.  The second is any&n; * information that may be defined by the board or how the device&n; * is connected externally of the chip.&n; *&n; * naming conventions:&n; * - platform data structures: &lt;driver&gt;_platform_data&n; * - platform data device flags: FSL_&lt;driver&gt;_DEV_&lt;FLAG&gt;&n; * - platform data board flags: FSL_&lt;driver&gt;_BRD_&lt;FLAG&gt;&n; *&n; */
DECL|struct|gianfar_platform_data
r_struct
id|gianfar_platform_data
(brace
multiline_comment|/* device specific information */
DECL|member|device_flags
id|u32
id|device_flags
suffix:semicolon
DECL|member|phy_reg_addr
id|u32
id|phy_reg_addr
suffix:semicolon
multiline_comment|/* board specific information */
DECL|member|board_flags
id|u32
id|board_flags
suffix:semicolon
DECL|member|phyid
id|u32
id|phyid
suffix:semicolon
DECL|member|interruptPHY
id|u32
id|interruptPHY
suffix:semicolon
DECL|member|mac_addr
id|u8
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags related to gianfar device features */
DECL|macro|FSL_GIANFAR_DEV_HAS_GIGABIT
mdefine_line|#define FSL_GIANFAR_DEV_HAS_GIGABIT&t;&t;0x00000001
DECL|macro|FSL_GIANFAR_DEV_HAS_COALESCE
mdefine_line|#define FSL_GIANFAR_DEV_HAS_COALESCE&t;&t;0x00000002
DECL|macro|FSL_GIANFAR_DEV_HAS_RMON
mdefine_line|#define FSL_GIANFAR_DEV_HAS_RMON&t;&t;0x00000004
DECL|macro|FSL_GIANFAR_DEV_HAS_MULTI_INTR
mdefine_line|#define FSL_GIANFAR_DEV_HAS_MULTI_INTR&t;&t;0x00000008
multiline_comment|/* Flags in gianfar_platform_data */
DECL|macro|FSL_GIANFAR_BRD_HAS_PHY_INTR
mdefine_line|#define FSL_GIANFAR_BRD_HAS_PHY_INTR&t;0x00000001&t;/* if not set use a timer */
DECL|struct|fsl_i2c_platform_data
r_struct
id|fsl_i2c_platform_data
(brace
multiline_comment|/* device specific information */
DECL|member|device_flags
id|u32
id|device_flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags related to I2C device features */
DECL|macro|FSL_I2C_DEV_SEPARATE_DFSRR
mdefine_line|#define FSL_I2C_DEV_SEPARATE_DFSRR&t;0x00000001
DECL|macro|FSL_I2C_DEV_CLOCK_5200
mdefine_line|#define FSL_I2C_DEV_CLOCK_5200&t;&t;0x00000002
macro_line|#endif&t;&t;&t;&t;/* _FSL_DEVICE_H_ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
