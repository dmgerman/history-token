multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * heathrow.h: definitions for using the &quot;Heathrow&quot; I/O controller chip.&n; *&n; * Grabbed from Open Firmware definitions on a PowerBook G3 Series&n; *&n; * Copyright (C) 1997 Paul Mackerras.&n; */
multiline_comment|/* Front light color on Yikes/B&amp;W G3. 32 bits */
DECL|macro|HEATHROW_FRONT_LIGHT
mdefine_line|#define HEATHROW_FRONT_LIGHT&t;&t;0x32 /* (set to 0 or 0xffffffff) */
multiline_comment|/* Brightness/contrast (gossamer iMac ?). 8 bits */
DECL|macro|HEATHROW_BRIGHTNESS_CNTL
mdefine_line|#define HEATHROW_BRIGHTNESS_CNTL&t;0x32
DECL|macro|HEATHROW_CONTRAST_CNTL
mdefine_line|#define HEATHROW_CONTRAST_CNTL&t;&t;0x33
multiline_comment|/* offset from ohare base for feature control register */
DECL|macro|HEATHROW_MBCR
mdefine_line|#define HEATHROW_MBCR&t;&t;&t;0x34&t;/* Media bay control */
DECL|macro|HEATHROW_FCR
mdefine_line|#define HEATHROW_FCR&t;&t;&t;0x38&t;/* Feature control */
DECL|macro|HEATHROW_AUX_CNTL_REG
mdefine_line|#define HEATHROW_AUX_CNTL_REG&t;&t;0x3c&t;/* Aux control */
multiline_comment|/*&n; * Bits in feature control register.&n; * Bits postfixed with a _N are in inverse logic&n; */
DECL|macro|HRW_SCC_TRANS_EN_N
mdefine_line|#define HRW_SCC_TRANS_EN_N&t;0x00000001&t;/* Also controls modem power */
DECL|macro|HRW_BAY_POWER_N
mdefine_line|#define HRW_BAY_POWER_N&t;&t;0x00000002
DECL|macro|HRW_BAY_PCI_ENABLE
mdefine_line|#define HRW_BAY_PCI_ENABLE&t;0x00000004
DECL|macro|HRW_BAY_IDE_ENABLE
mdefine_line|#define HRW_BAY_IDE_ENABLE&t;0x00000008
DECL|macro|HRW_BAY_FLOPPY_ENABLE
mdefine_line|#define HRW_BAY_FLOPPY_ENABLE&t;0x00000010
DECL|macro|HRW_IDE0_ENABLE
mdefine_line|#define HRW_IDE0_ENABLE&t;&t;0x00000020
DECL|macro|HRW_IDE0_RESET_N
mdefine_line|#define HRW_IDE0_RESET_N&t;0x00000040
DECL|macro|HRW_BAY_DEV_MASK
mdefine_line|#define HRW_BAY_DEV_MASK&t;0x0000001c
DECL|macro|HRW_BAY_RESET_N
mdefine_line|#define HRW_BAY_RESET_N&t;&t;0x00000080
DECL|macro|HRW_IOBUS_ENABLE
mdefine_line|#define HRW_IOBUS_ENABLE&t;0x00000100&t;/* Internal IDE ? */
DECL|macro|HRW_SCC_ENABLE
mdefine_line|#define HRW_SCC_ENABLE&t;&t;0x00000200
DECL|macro|HRW_MESH_ENABLE
mdefine_line|#define HRW_MESH_ENABLE&t;&t;0x00000400
DECL|macro|HRW_SWIM_ENABLE
mdefine_line|#define HRW_SWIM_ENABLE&t;&t;0x00000800
DECL|macro|HRW_SOUND_POWER_N
mdefine_line|#define HRW_SOUND_POWER_N&t;0x00001000
DECL|macro|HRW_SOUND_CLK_ENABLE
mdefine_line|#define HRW_SOUND_CLK_ENABLE&t;0x00002000
DECL|macro|HRW_SCCA_IO
mdefine_line|#define HRW_SCCA_IO&t;&t;0x00004000
DECL|macro|HRW_SCCB_IO
mdefine_line|#define HRW_SCCB_IO&t;&t;0x00008000
DECL|macro|HRW_PORT_OR_DESK_VIA_N
mdefine_line|#define HRW_PORT_OR_DESK_VIA_N&t;0x00010000&t;/* This one is 0 on PowerBook */
DECL|macro|HRW_PWM_MON_ID_N
mdefine_line|#define HRW_PWM_MON_ID_N&t;0x00020000&t;/* ??? (0) */
DECL|macro|HRW_HOOK_MB_CNT_N
mdefine_line|#define HRW_HOOK_MB_CNT_N&t;0x00040000&t;/* ??? (0) */
DECL|macro|HRW_SWIM_CLONE_FLOPPY
mdefine_line|#define HRW_SWIM_CLONE_FLOPPY&t;0x00080000&t;/* ??? (0) */
DECL|macro|HRW_AUD_RUN22
mdefine_line|#define HRW_AUD_RUN22&t;&t;0x00100000&t;/* ??? (1) */
DECL|macro|HRW_SCSI_LINK_MODE
mdefine_line|#define HRW_SCSI_LINK_MODE&t;0x00200000&t;/* Read ??? (1) */
DECL|macro|HRW_ARB_BYPASS
mdefine_line|#define HRW_ARB_BYPASS&t;&t;0x00400000&t;/* Disable internal PCI arbitrer */
DECL|macro|HRW_IDE1_RESET_N
mdefine_line|#define HRW_IDE1_RESET_N&t;0x00800000&t;/* Media bay */
DECL|macro|HRW_SLOW_SCC_PCLK
mdefine_line|#define HRW_SLOW_SCC_PCLK&t;0x01000000&t;/* ??? (0) */
DECL|macro|HRW_RESET_SCC
mdefine_line|#define HRW_RESET_SCC&t;&t;0x02000000
DECL|macro|HRW_MFDC_CELL_ENABLE
mdefine_line|#define HRW_MFDC_CELL_ENABLE&t;0x04000000&t;/* ??? (0) */
DECL|macro|HRW_USE_MFDC
mdefine_line|#define HRW_USE_MFDC&t;&t;0x08000000&t;/* ??? (0) */
DECL|macro|HRW_BMAC_IO_ENABLE
mdefine_line|#define HRW_BMAC_IO_ENABLE&t;0x60000000&t;/* two bits, not documented in OF */
DECL|macro|HRW_BMAC_RESET
mdefine_line|#define HRW_BMAC_RESET&t;&t;0x80000000&t;/* not documented in OF */
multiline_comment|/* We OR those features at boot on desktop G3s */
DECL|macro|HRW_DEFAULTS
mdefine_line|#define HRW_DEFAULTS&t;&t;(HRW_SCCA_IO | HRW_SCCB_IO | HRW_SCC_ENABLE)
multiline_comment|/* Looks like Heathrow has some sort of GPIOs as well... */
DECL|macro|HRW_GPIO_MODEM_RESET
mdefine_line|#define HRW_GPIO_MODEM_RESET&t;0x6d
eof
