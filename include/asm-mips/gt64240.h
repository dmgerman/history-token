multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright - Galileo technology.&n; * Copyright (C) 2004 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_MV64240_H
DECL|macro|__ASM_MIPS_MV64240_H
mdefine_line|#define __ASM_MIPS_MV64240_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * CPU Control Registers&n; */
DECL|macro|CPU_CONFIGURATION
mdefine_line|#define CPU_CONFIGURATION&t;&t;&t;&t;&t;0x000
DECL|macro|CPU_MODE
mdefine_line|#define CPU_MODE&t;&t;&t;&t;&t;&t;0x120
DECL|macro|CPU_READ_RESPONSE_CROSSBAR_LOW
mdefine_line|#define CPU_READ_RESPONSE_CROSSBAR_LOW&t;&t;&t;&t;0x170
DECL|macro|CPU_READ_RESPONSE_CROSSBAR_HIGH
mdefine_line|#define CPU_READ_RESPONSE_CROSSBAR_HIGH&t;&t;&t;&t;0x178
multiline_comment|/*&n; * Processor Address Space&n; */
multiline_comment|/* Sdram&squot;s BAR&squot;S */
DECL|macro|SCS_0_LOW_DECODE_ADDRESS
mdefine_line|#define SCS_0_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x008
DECL|macro|SCS_0_HIGH_DECODE_ADDRESS
mdefine_line|#define SCS_0_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x010
DECL|macro|SCS_1_LOW_DECODE_ADDRESS
mdefine_line|#define SCS_1_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x208
DECL|macro|SCS_1_HIGH_DECODE_ADDRESS
mdefine_line|#define SCS_1_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x210
DECL|macro|SCS_2_LOW_DECODE_ADDRESS
mdefine_line|#define SCS_2_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x018
DECL|macro|SCS_2_HIGH_DECODE_ADDRESS
mdefine_line|#define SCS_2_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x020
DECL|macro|SCS_3_LOW_DECODE_ADDRESS
mdefine_line|#define SCS_3_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x218
DECL|macro|SCS_3_HIGH_DECODE_ADDRESS
mdefine_line|#define SCS_3_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x220
multiline_comment|/* Devices BAR&squot;S */
DECL|macro|CS_0_LOW_DECODE_ADDRESS
mdefine_line|#define CS_0_LOW_DECODE_ADDRESS&t;&t;&t;&t;&t;0x028
DECL|macro|CS_0_HIGH_DECODE_ADDRESS
mdefine_line|#define CS_0_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x030
DECL|macro|CS_1_LOW_DECODE_ADDRESS
mdefine_line|#define CS_1_LOW_DECODE_ADDRESS&t;&t;&t;&t;&t;0x228
DECL|macro|CS_1_HIGH_DECODE_ADDRESS
mdefine_line|#define CS_1_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x230
DECL|macro|CS_2_LOW_DECODE_ADDRESS
mdefine_line|#define CS_2_LOW_DECODE_ADDRESS&t;&t;&t;&t;&t;0x248
DECL|macro|CS_2_HIGH_DECODE_ADDRESS
mdefine_line|#define CS_2_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x250
DECL|macro|CS_3_LOW_DECODE_ADDRESS
mdefine_line|#define CS_3_LOW_DECODE_ADDRESS&t;&t;&t;&t;&t;0x038
DECL|macro|CS_3_HIGH_DECODE_ADDRESS
mdefine_line|#define CS_3_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x040
DECL|macro|BOOTCS_LOW_DECODE_ADDRESS
mdefine_line|#define BOOTCS_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x238
DECL|macro|BOOTCS_HIGH_DECODE_ADDRESS
mdefine_line|#define BOOTCS_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x240
DECL|macro|PCI_0I_O_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_0I_O_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x048
DECL|macro|PCI_0I_O_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_0I_O_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x050
DECL|macro|PCI_0MEMORY0_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY0_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x058
DECL|macro|PCI_0MEMORY0_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY0_HIGH_DECODE_ADDRESS&t;&t;&t;0x060
DECL|macro|PCI_0MEMORY1_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY1_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x080
DECL|macro|PCI_0MEMORY1_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY1_HIGH_DECODE_ADDRESS&t;&t;&t;0x088
DECL|macro|PCI_0MEMORY2_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY2_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x258
DECL|macro|PCI_0MEMORY2_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY2_HIGH_DECODE_ADDRESS&t;&t;&t;0x260
DECL|macro|PCI_0MEMORY3_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY3_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x280
DECL|macro|PCI_0MEMORY3_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_0MEMORY3_HIGH_DECODE_ADDRESS&t;&t;&t;0x288
DECL|macro|PCI_1I_O_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_1I_O_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x090
DECL|macro|PCI_1I_O_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_1I_O_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x098
DECL|macro|PCI_1MEMORY0_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY0_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x0a0
DECL|macro|PCI_1MEMORY0_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY0_HIGH_DECODE_ADDRESS&t;&t;&t;0x0a8
DECL|macro|PCI_1MEMORY1_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY1_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x0b0
DECL|macro|PCI_1MEMORY1_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY1_HIGH_DECODE_ADDRESS&t;&t;&t;0x0b8
DECL|macro|PCI_1MEMORY2_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY2_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x2a0
DECL|macro|PCI_1MEMORY2_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY2_HIGH_DECODE_ADDRESS&t;&t;&t;0x2a8
DECL|macro|PCI_1MEMORY3_LOW_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY3_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x2b0
DECL|macro|PCI_1MEMORY3_HIGH_DECODE_ADDRESS
mdefine_line|#define PCI_1MEMORY3_HIGH_DECODE_ADDRESS&t;&t;&t;0x2b8
DECL|macro|INTERNAL_SPACE_DECODE
mdefine_line|#define INTERNAL_SPACE_DECODE&t;&t;&t;&t;&t;0x068
DECL|macro|CPU_0_LOW_DECODE_ADDRESS
mdefine_line|#define CPU_0_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x290
DECL|macro|CPU_0_HIGH_DECODE_ADDRESS
mdefine_line|#define CPU_0_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x298
DECL|macro|CPU_1_LOW_DECODE_ADDRESS
mdefine_line|#define CPU_1_LOW_DECODE_ADDRESS&t;&t;&t;&t;0x2c0
DECL|macro|CPU_1_HIGH_DECODE_ADDRESS
mdefine_line|#define CPU_1_HIGH_DECODE_ADDRESS&t;&t;&t;&t;0x2c8
DECL|macro|PCI_0I_O_ADDRESS_REMAP
mdefine_line|#define PCI_0I_O_ADDRESS_REMAP&t;&t;&t;&t;&t;0x0f0
DECL|macro|PCI_0MEMORY0_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY0_ADDRESS_REMAP&t;&t;&t;&t;0x0f8
DECL|macro|PCI_0MEMORY0_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY0_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x320
DECL|macro|PCI_0MEMORY1_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY1_ADDRESS_REMAP&t;&t;&t;&t;0x100
DECL|macro|PCI_0MEMORY1_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY1_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x328
DECL|macro|PCI_0MEMORY2_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY2_ADDRESS_REMAP&t;&t;&t;&t;0x2f8
DECL|macro|PCI_0MEMORY2_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY2_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x330
DECL|macro|PCI_0MEMORY3_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY3_ADDRESS_REMAP&t;&t;&t;&t;0x300
DECL|macro|PCI_0MEMORY3_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_0MEMORY3_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x338
DECL|macro|PCI_1I_O_ADDRESS_REMAP
mdefine_line|#define PCI_1I_O_ADDRESS_REMAP&t;&t;&t;&t;&t;0x108
DECL|macro|PCI_1MEMORY0_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY0_ADDRESS_REMAP&t;&t;&t;&t;0x110
DECL|macro|PCI_1MEMORY0_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY0_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x340
DECL|macro|PCI_1MEMORY1_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY1_ADDRESS_REMAP&t;&t;&t;&t;0x118
DECL|macro|PCI_1MEMORY1_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY1_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x348
DECL|macro|PCI_1MEMORY2_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY2_ADDRESS_REMAP&t;&t;&t;&t;0x310
DECL|macro|PCI_1MEMORY2_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY2_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x350
DECL|macro|PCI_1MEMORY3_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY3_ADDRESS_REMAP&t;&t;&t;&t;0x318
DECL|macro|PCI_1MEMORY3_HIGH_ADDRESS_REMAP
mdefine_line|#define PCI_1MEMORY3_HIGH_ADDRESS_REMAP&t;&t;&t;&t;0x358
multiline_comment|/*&n; * CPU Sync Barrier&n; */
DECL|macro|PCI_0SYNC_BARIER_VIRTUAL_REGISTER
mdefine_line|#define PCI_0SYNC_BARIER_VIRTUAL_REGISTER&t;&t;&t;0x0c0
DECL|macro|PCI_1SYNC_BARIER_VIRTUAL_REGISTER
mdefine_line|#define PCI_1SYNC_BARIER_VIRTUAL_REGISTER&t;&t;&t;0x0c8
multiline_comment|/*&n; * CPU Access Protect&n; */
DECL|macro|CPU_LOW_PROTECT_ADDRESS_0
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_0&t;&t;&t;&t;0X180
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_0
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_0&t;&t;&t;&t;0X188
DECL|macro|CPU_LOW_PROTECT_ADDRESS_1
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_1&t;&t;&t;&t;0X190
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_1
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_1&t;&t;&t;&t;0X198
DECL|macro|CPU_LOW_PROTECT_ADDRESS_2
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_2&t;&t;&t;&t;0X1a0
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_2
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_2&t;&t;&t;&t;0X1a8
DECL|macro|CPU_LOW_PROTECT_ADDRESS_3
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_3&t;&t;&t;&t;0X1b0
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_3
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_3&t;&t;&t;&t;0X1b8
DECL|macro|CPU_LOW_PROTECT_ADDRESS_4
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_4&t;&t;&t;&t;0X1c0
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_4
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_4&t;&t;&t;&t;0X1c8
DECL|macro|CPU_LOW_PROTECT_ADDRESS_5
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_5&t;&t;&t;&t;0X1d0
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_5
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_5&t;&t;&t;&t;0X1d8
DECL|macro|CPU_LOW_PROTECT_ADDRESS_6
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_6&t;&t;&t;&t;0X1e0
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_6
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_6&t;&t;&t;&t;0X1e8
DECL|macro|CPU_LOW_PROTECT_ADDRESS_7
mdefine_line|#define CPU_LOW_PROTECT_ADDRESS_7&t;&t;&t;&t;0X1f0
DECL|macro|CPU_HIGH_PROTECT_ADDRESS_7
mdefine_line|#define CPU_HIGH_PROTECT_ADDRESS_7&t;&t;&t;&t;0X1f8
multiline_comment|/*&n; * Snoop Control&n; */
DECL|macro|SNOOP_BASE_ADDRESS_0
mdefine_line|#define SNOOP_BASE_ADDRESS_0&t;&t;&t;&t;&t;0x380
DECL|macro|SNOOP_TOP_ADDRESS_0
mdefine_line|#define SNOOP_TOP_ADDRESS_0&t;&t;&t;&t;&t;0x388
DECL|macro|SNOOP_BASE_ADDRESS_1
mdefine_line|#define SNOOP_BASE_ADDRESS_1&t;&t;&t;&t;&t;0x390
DECL|macro|SNOOP_TOP_ADDRESS_1
mdefine_line|#define SNOOP_TOP_ADDRESS_1&t;&t;&t;&t;&t;0x398
DECL|macro|SNOOP_BASE_ADDRESS_2
mdefine_line|#define SNOOP_BASE_ADDRESS_2&t;&t;&t;&t;&t;0x3a0
DECL|macro|SNOOP_TOP_ADDRESS_2
mdefine_line|#define SNOOP_TOP_ADDRESS_2&t;&t;&t;&t;&t;0x3a8
DECL|macro|SNOOP_BASE_ADDRESS_3
mdefine_line|#define SNOOP_BASE_ADDRESS_3&t;&t;&t;&t;&t;0x3b0
DECL|macro|SNOOP_TOP_ADDRESS_3
mdefine_line|#define SNOOP_TOP_ADDRESS_3&t;&t;&t;&t;&t;0x3b8
multiline_comment|/*&n; * CPU Error Report&n; */
DECL|macro|CPU_ERROR_ADDRESS_LOW
mdefine_line|#define CPU_ERROR_ADDRESS_LOW&t;&t;&t;&t;&t;0x070
DECL|macro|CPU_ERROR_ADDRESS_HIGH
mdefine_line|#define CPU_ERROR_ADDRESS_HIGH&t;&t;&t;&t;&t;0x078
DECL|macro|CPU_ERROR_DATA_LOW
mdefine_line|#define CPU_ERROR_DATA_LOW&t;&t;&t;&t;&t;0x128
DECL|macro|CPU_ERROR_DATA_HIGH
mdefine_line|#define CPU_ERROR_DATA_HIGH&t;&t;&t;&t;&t;0x130
DECL|macro|CPU_ERROR_PARITY
mdefine_line|#define CPU_ERROR_PARITY&t;&t;&t;&t;&t;0x138
DECL|macro|CPU_ERROR_CAUSE
mdefine_line|#define CPU_ERROR_CAUSE&t;&t;&t;&t;&t;&t;0x140
DECL|macro|CPU_ERROR_MASK
mdefine_line|#define CPU_ERROR_MASK&t;&t;&t;&t;&t;&t;0x148
multiline_comment|/*&n; * Pslave Debug&n; */
DECL|macro|X_0_ADDRESS
mdefine_line|#define X_0_ADDRESS&t;&t;&t;&t;&t;&t;0x360
DECL|macro|X_0_COMMAND_ID
mdefine_line|#define X_0_COMMAND_ID&t;&t;&t;&t;&t;&t;0x368
DECL|macro|X_1_ADDRESS
mdefine_line|#define X_1_ADDRESS&t;&t;&t;&t;&t;&t;0x370
DECL|macro|X_1_COMMAND_ID
mdefine_line|#define X_1_COMMAND_ID&t;&t;&t;&t;&t;&t;0x378
DECL|macro|WRITE_DATA_LOW
mdefine_line|#define WRITE_DATA_LOW&t;&t;&t;&t;&t;&t;0x3c0
DECL|macro|WRITE_DATA_HIGH
mdefine_line|#define WRITE_DATA_HIGH&t;&t;&t;&t;&t;&t;0x3c8
DECL|macro|WRITE_BYTE_ENABLE
mdefine_line|#define WRITE_BYTE_ENABLE&t;&t;&t;&t;&t;0X3e0
DECL|macro|READ_DATA_LOW
mdefine_line|#define READ_DATA_LOW&t;&t;&t;&t;&t;&t;0x3d0
DECL|macro|READ_DATA_HIGH
mdefine_line|#define READ_DATA_HIGH&t;&t;&t;&t;&t;&t;0x3d8
DECL|macro|READ_ID
mdefine_line|#define READ_ID&t;&t;&t;&t;&t;&t;&t;0x3e8
multiline_comment|/*&n; * SDRAM and Device Address Space&n; */
multiline_comment|/*&n; * SDRAM Configuration&n; */
DECL|macro|SDRAM_CONFIGURATION
mdefine_line|#define SDRAM_CONFIGURATION&t;&t;&t;&t;&t;0x448
DECL|macro|SDRAM_OPERATION_MODE
mdefine_line|#define SDRAM_OPERATION_MODE&t;&t;&t;&t;&t;0x474
DECL|macro|SDRAM_ADDRESS_DECODE
mdefine_line|#define SDRAM_ADDRESS_DECODE&t;&t;&t;&t;&t;0x47C
DECL|macro|SDRAM_TIMING_PARAMETERS
mdefine_line|#define SDRAM_TIMING_PARAMETERS&t;&t;&t;&t;&t;0x4b4
DECL|macro|SDRAM_UMA_CONTROL
mdefine_line|#define SDRAM_UMA_CONTROL&t;&t;&t;&t;&t;0x4a4
DECL|macro|SDRAM_CROSS_BAR_CONTROL_LOW
mdefine_line|#define SDRAM_CROSS_BAR_CONTROL_LOW&t;&t;&t;&t;0x4a8
DECL|macro|SDRAM_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define SDRAM_CROSS_BAR_CONTROL_HIGH&t;&t;&t;&t;0x4ac
DECL|macro|SDRAM_CROSS_BAR_TIMEOUT
mdefine_line|#define SDRAM_CROSS_BAR_TIMEOUT&t;&t;&t;&t;&t;0x4b0
multiline_comment|/*&n; * SDRAM Parameters&n; */
DECL|macro|SDRAM_BANK0PARAMETERS
mdefine_line|#define SDRAM_BANK0PARAMETERS&t;&t;&t;&t;&t;0x44C
DECL|macro|SDRAM_BANK1PARAMETERS
mdefine_line|#define SDRAM_BANK1PARAMETERS&t;&t;&t;&t;&t;0x450
DECL|macro|SDRAM_BANK2PARAMETERS
mdefine_line|#define SDRAM_BANK2PARAMETERS&t;&t;&t;&t;&t;0x454
DECL|macro|SDRAM_BANK3PARAMETERS
mdefine_line|#define SDRAM_BANK3PARAMETERS&t;&t;&t;&t;&t;0x458
multiline_comment|/*&n; * SDRAM Error Report&n; */
DECL|macro|SDRAM_ERROR_DATA_LOW
mdefine_line|#define SDRAM_ERROR_DATA_LOW&t;&t;&t;&t;&t;0x484
DECL|macro|SDRAM_ERROR_DATA_HIGH
mdefine_line|#define SDRAM_ERROR_DATA_HIGH&t;&t;&t;&t;&t;0x480
DECL|macro|SDRAM_AND_DEVICE_ERROR_ADDRESS
mdefine_line|#define SDRAM_AND_DEVICE_ERROR_ADDRESS&t;&t;&t;&t;0x490
DECL|macro|SDRAM_RECEIVED_ECC
mdefine_line|#define SDRAM_RECEIVED_ECC&t;&t;&t;&t;&t;0x488
DECL|macro|SDRAM_CALCULATED_ECC
mdefine_line|#define SDRAM_CALCULATED_ECC&t;&t;&t;&t;&t;0x48c
DECL|macro|SDRAM_ECC_CONTROL
mdefine_line|#define SDRAM_ECC_CONTROL&t;&t;&t;&t;&t;0x494
DECL|macro|SDRAM_ECC_ERROR_COUNTER
mdefine_line|#define SDRAM_ECC_ERROR_COUNTER&t;&t;&t;&t;&t;0x498
multiline_comment|/*&n; * SDunit Debug (for internal use)&n; */
DECL|macro|X0_ADDRESS
mdefine_line|#define X0_ADDRESS&t;&t;&t;&t;&t;&t;0x500
DECL|macro|X0_COMMAND_AND_ID
mdefine_line|#define X0_COMMAND_AND_ID&t;&t;&t;&t;&t;0x504
DECL|macro|X0_WRITE_DATA_LOW
mdefine_line|#define X0_WRITE_DATA_LOW&t;&t;&t;&t;&t;0x508
DECL|macro|X0_WRITE_DATA_HIGH
mdefine_line|#define X0_WRITE_DATA_HIGH&t;&t;&t;&t;&t;0x50c
DECL|macro|X0_WRITE_BYTE_ENABLE
mdefine_line|#define X0_WRITE_BYTE_ENABLE&t;&t;&t;&t;&t;0x518
DECL|macro|X0_READ_DATA_LOW
mdefine_line|#define X0_READ_DATA_LOW&t;&t;&t;&t;&t;0x510
DECL|macro|X0_READ_DATA_HIGH
mdefine_line|#define X0_READ_DATA_HIGH&t;&t;&t;&t;&t;0x514
DECL|macro|X0_READ_ID
mdefine_line|#define X0_READ_ID&t;&t;&t;&t;&t;&t;0x51c
DECL|macro|X1_ADDRESS
mdefine_line|#define X1_ADDRESS&t;&t;&t;&t;&t;&t;0x520
DECL|macro|X1_COMMAND_AND_ID
mdefine_line|#define X1_COMMAND_AND_ID&t;&t;&t;&t;&t;0x524
DECL|macro|X1_WRITE_DATA_LOW
mdefine_line|#define X1_WRITE_DATA_LOW&t;&t;&t;&t;&t;0x528
DECL|macro|X1_WRITE_DATA_HIGH
mdefine_line|#define X1_WRITE_DATA_HIGH&t;&t;&t;&t;&t;0x52c
DECL|macro|X1_WRITE_BYTE_ENABLE
mdefine_line|#define X1_WRITE_BYTE_ENABLE&t;&t;&t;&t;&t;0x538
DECL|macro|X1_READ_DATA_LOW
mdefine_line|#define X1_READ_DATA_LOW&t;&t;&t;&t;&t;0x530
DECL|macro|X1_READ_DATA_HIGH
mdefine_line|#define X1_READ_DATA_HIGH&t;&t;&t;&t;&t;0x534
DECL|macro|X1_READ_ID
mdefine_line|#define X1_READ_ID&t;&t;&t;&t;&t;&t;0x53c
DECL|macro|X0_SNOOP_ADDRESS
mdefine_line|#define X0_SNOOP_ADDRESS&t;&t;&t;&t;&t;0x540
DECL|macro|X0_SNOOP_COMMAND
mdefine_line|#define X0_SNOOP_COMMAND&t;&t;&t;&t;&t;0x544
DECL|macro|X1_SNOOP_ADDRESS
mdefine_line|#define X1_SNOOP_ADDRESS&t;&t;&t;&t;&t;0x548
DECL|macro|X1_SNOOP_COMMAND
mdefine_line|#define X1_SNOOP_COMMAND&t;&t;&t;&t;&t;0x54c
multiline_comment|/*&n; * Device Parameters&n; */
DECL|macro|DEVICE_BANK0PARAMETERS
mdefine_line|#define DEVICE_BANK0PARAMETERS&t;&t;&t;&t;&t;0x45c
DECL|macro|DEVICE_BANK1PARAMETERS
mdefine_line|#define DEVICE_BANK1PARAMETERS&t;&t;&t;&t;&t;0x460
DECL|macro|DEVICE_BANK2PARAMETERS
mdefine_line|#define DEVICE_BANK2PARAMETERS&t;&t;&t;&t;&t;0x464
DECL|macro|DEVICE_BANK3PARAMETERS
mdefine_line|#define DEVICE_BANK3PARAMETERS&t;&t;&t;&t;&t;0x468
DECL|macro|DEVICE_BOOT_BANK_PARAMETERS
mdefine_line|#define DEVICE_BOOT_BANK_PARAMETERS&t;&t;&t;&t;0x46c
DECL|macro|DEVICE_CONTROL
mdefine_line|#define DEVICE_CONTROL&t;&t;&t;&t;&t;&t;0x4c0
DECL|macro|DEVICE_CROSS_BAR_CONTROL_LOW
mdefine_line|#define DEVICE_CROSS_BAR_CONTROL_LOW&t;&t;&t;&t;0x4c8
DECL|macro|DEVICE_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define DEVICE_CROSS_BAR_CONTROL_HIGH&t;&t;&t;&t;0x4cc
DECL|macro|DEVICE_CROSS_BAR_TIMEOUT
mdefine_line|#define DEVICE_CROSS_BAR_TIMEOUT&t;&t;&t;&t;0x4c4
multiline_comment|/*&n; * Device Interrupt&n; */
DECL|macro|DEVICE_INTERRUPT_CAUSE
mdefine_line|#define DEVICE_INTERRUPT_CAUSE&t;&t;&t;&t;&t;0x4d0
DECL|macro|DEVICE_INTERRUPT_MASK
mdefine_line|#define DEVICE_INTERRUPT_MASK&t;&t;&t;&t;&t;0x4d4
DECL|macro|DEVICE_ERROR_ADDRESS
mdefine_line|#define DEVICE_ERROR_ADDRESS&t;&t;&t;&t;&t;0x4d8
multiline_comment|/*&n; * DMA Record&n; */
DECL|macro|CHANNEL0_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL0_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x800
DECL|macro|CHANNEL1_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL1_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x804
DECL|macro|CHANNEL2_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL2_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x808
DECL|macro|CHANNEL3_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL3_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x80C
DECL|macro|CHANNEL4_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL4_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x900
DECL|macro|CHANNEL5_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL5_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x904
DECL|macro|CHANNEL6_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL6_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x908
DECL|macro|CHANNEL7_DMA_BYTE_COUNT
mdefine_line|#define CHANNEL7_DMA_BYTE_COUNT&t;&t;&t;&t;&t;0x90C
DECL|macro|CHANNEL0_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL0_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x810
DECL|macro|CHANNEL1_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL1_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x814
DECL|macro|CHANNEL2_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL2_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x818
DECL|macro|CHANNEL3_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL3_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x81C
DECL|macro|CHANNEL4_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL4_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x910
DECL|macro|CHANNEL5_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL5_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x914
DECL|macro|CHANNEL6_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL6_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x918
DECL|macro|CHANNEL7_DMA_SOURCE_ADDRESS
mdefine_line|#define CHANNEL7_DMA_SOURCE_ADDRESS&t;&t;&t;&t;0x91C
DECL|macro|CHANNEL0_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL0_DMA_DESTINATION_ADDRESS&t;&t;&t;0x820
DECL|macro|CHANNEL1_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL1_DMA_DESTINATION_ADDRESS&t;&t;&t;0x824
DECL|macro|CHANNEL2_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL2_DMA_DESTINATION_ADDRESS&t;&t;&t;0x828
DECL|macro|CHANNEL3_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL3_DMA_DESTINATION_ADDRESS&t;&t;&t;0x82C
DECL|macro|CHANNEL4_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL4_DMA_DESTINATION_ADDRESS&t;&t;&t;0x920
DECL|macro|CHANNEL5_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL5_DMA_DESTINATION_ADDRESS&t;&t;&t;0x924
DECL|macro|CHANNEL6_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL6_DMA_DESTINATION_ADDRESS&t;&t;&t;0x928
DECL|macro|CHANNEL7_DMA_DESTINATION_ADDRESS
mdefine_line|#define CHANNEL7_DMA_DESTINATION_ADDRESS&t;&t;&t;0x92C
DECL|macro|CHANNEL0NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL0NEXT_RECORD_POINTER&t;&t;&t;&t;0x830
DECL|macro|CHANNEL1NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL1NEXT_RECORD_POINTER&t;&t;&t;&t;0x834
DECL|macro|CHANNEL2NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL2NEXT_RECORD_POINTER&t;&t;&t;&t;0x838
DECL|macro|CHANNEL3NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL3NEXT_RECORD_POINTER&t;&t;&t;&t;0x83C
DECL|macro|CHANNEL4NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL4NEXT_RECORD_POINTER&t;&t;&t;&t;0x930
DECL|macro|CHANNEL5NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL5NEXT_RECORD_POINTER&t;&t;&t;&t;0x934
DECL|macro|CHANNEL6NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL6NEXT_RECORD_POINTER&t;&t;&t;&t;0x938
DECL|macro|CHANNEL7NEXT_RECORD_POINTER
mdefine_line|#define CHANNEL7NEXT_RECORD_POINTER&t;&t;&t;&t;0x93C
DECL|macro|CHANNEL0CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL0CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x870
DECL|macro|CHANNEL1CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL1CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x874
DECL|macro|CHANNEL2CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL2CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x878
DECL|macro|CHANNEL3CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL3CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x87C
DECL|macro|CHANNEL4CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL4CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x970
DECL|macro|CHANNEL5CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL5CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x974
DECL|macro|CHANNEL6CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL6CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x978
DECL|macro|CHANNEL7CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL7CURRENT_DESCRIPTOR_POINTER&t;&t;&t;0x97C
DECL|macro|CHANNEL0_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL0_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x890
DECL|macro|CHANNEL1_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL1_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x894
DECL|macro|CHANNEL2_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL2_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x898
DECL|macro|CHANNEL3_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL3_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x89c
DECL|macro|CHANNEL4_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL4_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x990
DECL|macro|CHANNEL5_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL5_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x994
DECL|macro|CHANNEL6_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL6_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x998
DECL|macro|CHANNEL7_DMA_SOURCE_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL7_DMA_SOURCE_HIGH_PCI_ADDRESS&t;&t;&t;0x99c
DECL|macro|CHANNEL0_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL0_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x8a0
DECL|macro|CHANNEL1_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL1_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x8a4
DECL|macro|CHANNEL2_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL2_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x8a8
DECL|macro|CHANNEL3_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL3_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x8ac
DECL|macro|CHANNEL4_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL4_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x9a0
DECL|macro|CHANNEL5_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL5_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x9a4
DECL|macro|CHANNEL6_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL6_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x9a8
DECL|macro|CHANNEL7_DMA_DESTINATION_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL7_DMA_DESTINATION_HIGH_PCI_ADDRESS&t;&t;0x9ac
DECL|macro|CHANNEL0_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL0_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x8b0
DECL|macro|CHANNEL1_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL1_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x8b4
DECL|macro|CHANNEL2_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL2_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x8b8
DECL|macro|CHANNEL3_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL3_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x8bc
DECL|macro|CHANNEL4_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL4_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x9b0
DECL|macro|CHANNEL5_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL5_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x9b4
DECL|macro|CHANNEL6_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL6_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x9b8
DECL|macro|CHANNEL7_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS
mdefine_line|#define CHANNEL7_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS&t;0x9bc
multiline_comment|/*&n; * DMA Channel Control&n; */
DECL|macro|CHANNEL0CONTROL
mdefine_line|#define CHANNEL0CONTROL&t;&t;&t;&t;&t;&t;0x840
DECL|macro|CHANNEL0CONTROL_HIGH
mdefine_line|#define CHANNEL0CONTROL_HIGH&t;&t;&t;&t;&t;0x880
DECL|macro|CHANNEL1CONTROL
mdefine_line|#define CHANNEL1CONTROL&t;&t;&t;&t;&t;&t;0x844
DECL|macro|CHANNEL1CONTROL_HIGH
mdefine_line|#define CHANNEL1CONTROL_HIGH&t;&t;&t;&t;&t;0x884
DECL|macro|CHANNEL2CONTROL
mdefine_line|#define CHANNEL2CONTROL&t;&t;&t;&t;&t;&t;0x848
DECL|macro|CHANNEL2CONTROL_HIGH
mdefine_line|#define CHANNEL2CONTROL_HIGH&t;&t;&t;&t;&t;0x888
DECL|macro|CHANNEL3CONTROL
mdefine_line|#define CHANNEL3CONTROL&t;&t;&t;&t;&t;&t;0x84C
DECL|macro|CHANNEL3CONTROL_HIGH
mdefine_line|#define CHANNEL3CONTROL_HIGH&t;&t;&t;&t;&t;0x88C
DECL|macro|CHANNEL4CONTROL
mdefine_line|#define CHANNEL4CONTROL&t;&t;&t;&t;&t;&t;0x940
DECL|macro|CHANNEL4CONTROL_HIGH
mdefine_line|#define CHANNEL4CONTROL_HIGH&t;&t;&t;&t;&t;0x980
DECL|macro|CHANNEL5CONTROL
mdefine_line|#define CHANNEL5CONTROL&t;&t;&t;&t;&t;&t;0x944
DECL|macro|CHANNEL5CONTROL_HIGH
mdefine_line|#define CHANNEL5CONTROL_HIGH&t;&t;&t;&t;&t;0x984
DECL|macro|CHANNEL6CONTROL
mdefine_line|#define CHANNEL6CONTROL&t;&t;&t;&t;&t;&t;0x948
DECL|macro|CHANNEL6CONTROL_HIGH
mdefine_line|#define CHANNEL6CONTROL_HIGH&t;&t;&t;&t;&t;0x988
DECL|macro|CHANNEL7CONTROL
mdefine_line|#define CHANNEL7CONTROL&t;&t;&t;&t;&t;&t;0x94C
DECL|macro|CHANNEL7CONTROL_HIGH
mdefine_line|#define CHANNEL7CONTROL_HIGH&t;&t;&t;&t;&t;0x98C
multiline_comment|/*&n; * DMA Arbiter&n; */
DECL|macro|ARBITER_CONTROL_0_3
mdefine_line|#define ARBITER_CONTROL_0_3&t;&t;&t;&t;&t;0x860
DECL|macro|ARBITER_CONTROL_4_7
mdefine_line|#define ARBITER_CONTROL_4_7&t;&t;&t;&t;&t;0x960
multiline_comment|/*&n; * DMA Interrupt&n; */
DECL|macro|CHANELS0_3_INTERRUPT_CAUSE
mdefine_line|#define CHANELS0_3_INTERRUPT_CAUSE&t;&t;&t;&t;0x8c0
DECL|macro|CHANELS0_3_INTERRUPT_MASK
mdefine_line|#define CHANELS0_3_INTERRUPT_MASK&t;&t;&t;&t;0x8c4
DECL|macro|CHANELS0_3_ERROR_ADDRESS
mdefine_line|#define CHANELS0_3_ERROR_ADDRESS&t;&t;&t;&t;0x8c8
DECL|macro|CHANELS0_3_ERROR_SELECT
mdefine_line|#define CHANELS0_3_ERROR_SELECT&t;&t;&t;&t;&t;0x8cc
DECL|macro|CHANELS4_7_INTERRUPT_CAUSE
mdefine_line|#define CHANELS4_7_INTERRUPT_CAUSE&t;&t;&t;&t;0x9c0
DECL|macro|CHANELS4_7_INTERRUPT_MASK
mdefine_line|#define CHANELS4_7_INTERRUPT_MASK&t;&t;&t;&t;0x9c4
DECL|macro|CHANELS4_7_ERROR_ADDRESS
mdefine_line|#define CHANELS4_7_ERROR_ADDRESS&t;&t;&t;&t;0x9c8
DECL|macro|CHANELS4_7_ERROR_SELECT
mdefine_line|#define CHANELS4_7_ERROR_SELECT&t;&t;&t;&t;&t;0x9cc
multiline_comment|/*&n; * DMA Debug (for internal use)&n; */
DECL|macro|DMA_X0_ADDRESS
mdefine_line|#define DMA_X0_ADDRESS&t;&t;&t;&t;&t;&t;0x8e0
DECL|macro|DMA_X0_COMMAND_AND_ID
mdefine_line|#define DMA_X0_COMMAND_AND_ID&t;&t;&t;&t;&t;0x8e4
DECL|macro|DMA_X0_WRITE_DATA_LOW
mdefine_line|#define DMA_X0_WRITE_DATA_LOW&t;&t;&t;&t;&t;0x8e8
DECL|macro|DMA_X0_WRITE_DATA_HIGH
mdefine_line|#define DMA_X0_WRITE_DATA_HIGH&t;&t;&t;&t;&t;0x8ec
DECL|macro|DMA_X0_WRITE_BYTE_ENABLE
mdefine_line|#define DMA_X0_WRITE_BYTE_ENABLE&t;&t;&t;&t;0x8f8
DECL|macro|DMA_X0_READ_DATA_LOW
mdefine_line|#define DMA_X0_READ_DATA_LOW&t;&t;&t;&t;&t;0x8f0
DECL|macro|DMA_X0_READ_DATA_HIGH
mdefine_line|#define DMA_X0_READ_DATA_HIGH&t;&t;&t;&t;&t;0x8f4
DECL|macro|DMA_X0_READ_ID
mdefine_line|#define DMA_X0_READ_ID&t;&t;&t;&t;&t;&t;0x8fc
DECL|macro|DMA_X1_ADDRESS
mdefine_line|#define DMA_X1_ADDRESS&t;&t;&t;&t;&t;&t;0x9e0
DECL|macro|DMA_X1_COMMAND_AND_ID
mdefine_line|#define DMA_X1_COMMAND_AND_ID&t;&t;&t;&t;&t;0x9e4
DECL|macro|DMA_X1_WRITE_DATA_LOW
mdefine_line|#define DMA_X1_WRITE_DATA_LOW&t;&t;&t;&t;&t;0x9e8
DECL|macro|DMA_X1_WRITE_DATA_HIGH
mdefine_line|#define DMA_X1_WRITE_DATA_HIGH&t;&t;&t;&t;&t;0x9ec
DECL|macro|DMA_X1_WRITE_BYTE_ENABLE
mdefine_line|#define DMA_X1_WRITE_BYTE_ENABLE&t;&t;&t;&t;0x9f8
DECL|macro|DMA_X1_READ_DATA_LOW
mdefine_line|#define DMA_X1_READ_DATA_LOW&t;&t;&t;&t;&t;0x9f0
DECL|macro|DMA_X1_READ_DATA_HIGH
mdefine_line|#define DMA_X1_READ_DATA_HIGH&t;&t;&t;&t;&t;0x9f4
DECL|macro|DMA_X1_READ_ID
mdefine_line|#define DMA_X1_READ_ID&t;&t;&t;&t;&t;&t;0x9fc
multiline_comment|/*&n; * Timer_Counter&n; */
DECL|macro|TIMER_COUNTER0
mdefine_line|#define TIMER_COUNTER0&t;&t;&t;&t;&t;&t;0x850
DECL|macro|TIMER_COUNTER1
mdefine_line|#define TIMER_COUNTER1&t;&t;&t;&t;&t;&t;0x854
DECL|macro|TIMER_COUNTER2
mdefine_line|#define TIMER_COUNTER2&t;&t;&t;&t;&t;&t;0x858
DECL|macro|TIMER_COUNTER3
mdefine_line|#define TIMER_COUNTER3&t;&t;&t;&t;&t;&t;0x85C
DECL|macro|TIMER_COUNTER_0_3_CONTROL
mdefine_line|#define TIMER_COUNTER_0_3_CONTROL&t;&t;&t;&t;0x864
DECL|macro|TIMER_COUNTER_0_3_INTERRUPT_CAUSE
mdefine_line|#define TIMER_COUNTER_0_3_INTERRUPT_CAUSE&t;&t;&t;0x868
DECL|macro|TIMER_COUNTER_0_3_INTERRUPT_MASK
mdefine_line|#define TIMER_COUNTER_0_3_INTERRUPT_MASK&t;&t;&t;0x86c
DECL|macro|TIMER_COUNTER4
mdefine_line|#define TIMER_COUNTER4&t;&t;&t;&t;&t;&t;0x950
DECL|macro|TIMER_COUNTER5
mdefine_line|#define TIMER_COUNTER5&t;&t;&t;&t;&t;&t;0x954
DECL|macro|TIMER_COUNTER6
mdefine_line|#define TIMER_COUNTER6&t;&t;&t;&t;&t;&t;0x958
DECL|macro|TIMER_COUNTER7
mdefine_line|#define TIMER_COUNTER7&t;&t;&t;&t;&t;&t;0x95C
DECL|macro|TIMER_COUNTER_4_7_CONTROL
mdefine_line|#define TIMER_COUNTER_4_7_CONTROL&t;&t;&t;&t;0x964
DECL|macro|TIMER_COUNTER_4_7_INTERRUPT_CAUSE
mdefine_line|#define TIMER_COUNTER_4_7_INTERRUPT_CAUSE&t;&t;&t;0x968
DECL|macro|TIMER_COUNTER_4_7_INTERRUPT_MASK
mdefine_line|#define TIMER_COUNTER_4_7_INTERRUPT_MASK&t;&t;&t;0x96c
multiline_comment|/*&n; * PCI Slave Address Decoding&n; */
DECL|macro|PCI_0SCS_0_BANK_SIZE
mdefine_line|#define PCI_0SCS_0_BANK_SIZE&t;&t;&t;&t;&t;0xc08
DECL|macro|PCI_1SCS_0_BANK_SIZE
mdefine_line|#define PCI_1SCS_0_BANK_SIZE&t;&t;&t;&t;&t;0xc88
DECL|macro|PCI_0SCS_1_BANK_SIZE
mdefine_line|#define PCI_0SCS_1_BANK_SIZE&t;&t;&t;&t;&t;0xd08
DECL|macro|PCI_1SCS_1_BANK_SIZE
mdefine_line|#define PCI_1SCS_1_BANK_SIZE&t;&t;&t;&t;&t;0xd88
DECL|macro|PCI_0SCS_2_BANK_SIZE
mdefine_line|#define PCI_0SCS_2_BANK_SIZE&t;&t;&t;&t;&t;0xc0c
DECL|macro|PCI_1SCS_2_BANK_SIZE
mdefine_line|#define PCI_1SCS_2_BANK_SIZE&t;&t;&t;&t;&t;0xc8c
DECL|macro|PCI_0SCS_3_BANK_SIZE
mdefine_line|#define PCI_0SCS_3_BANK_SIZE&t;&t;&t;&t;&t;0xd0c
DECL|macro|PCI_1SCS_3_BANK_SIZE
mdefine_line|#define PCI_1SCS_3_BANK_SIZE&t;&t;&t;&t;&t;0xd8c
DECL|macro|PCI_0CS_0_BANK_SIZE
mdefine_line|#define PCI_0CS_0_BANK_SIZE&t;&t;&t;&t;&t;0xc10
DECL|macro|PCI_1CS_0_BANK_SIZE
mdefine_line|#define PCI_1CS_0_BANK_SIZE&t;&t;&t;&t;&t;0xc90
DECL|macro|PCI_0CS_1_BANK_SIZE
mdefine_line|#define PCI_0CS_1_BANK_SIZE&t;&t;&t;&t;&t;0xd10
DECL|macro|PCI_1CS_1_BANK_SIZE
mdefine_line|#define PCI_1CS_1_BANK_SIZE&t;&t;&t;&t;&t;0xd90
DECL|macro|PCI_0CS_2_BANK_SIZE
mdefine_line|#define PCI_0CS_2_BANK_SIZE&t;&t;&t;&t;&t;0xd18
DECL|macro|PCI_1CS_2_BANK_SIZE
mdefine_line|#define PCI_1CS_2_BANK_SIZE&t;&t;&t;&t;&t;0xd98
DECL|macro|PCI_0CS_3_BANK_SIZE
mdefine_line|#define PCI_0CS_3_BANK_SIZE&t;&t;&t;&t;&t;0xc14
DECL|macro|PCI_1CS_3_BANK_SIZE
mdefine_line|#define PCI_1CS_3_BANK_SIZE&t;&t;&t;&t;&t;0xc94
DECL|macro|PCI_0CS_BOOT_BANK_SIZE
mdefine_line|#define PCI_0CS_BOOT_BANK_SIZE&t;&t;&t;&t;&t;0xd14
DECL|macro|PCI_1CS_BOOT_BANK_SIZE
mdefine_line|#define PCI_1CS_BOOT_BANK_SIZE&t;&t;&t;&t;&t;0xd94
DECL|macro|PCI_0P2P_MEM0_BAR_SIZE
mdefine_line|#define PCI_0P2P_MEM0_BAR_SIZE&t;&t;&t;&t;&t;0xd1c
DECL|macro|PCI_1P2P_MEM0_BAR_SIZE
mdefine_line|#define PCI_1P2P_MEM0_BAR_SIZE&t;&t;&t;&t;&t;0xd9c
DECL|macro|PCI_0P2P_MEM1_BAR_SIZE
mdefine_line|#define PCI_0P2P_MEM1_BAR_SIZE&t;&t;&t;&t;&t;0xd20
DECL|macro|PCI_1P2P_MEM1_BAR_SIZE
mdefine_line|#define PCI_1P2P_MEM1_BAR_SIZE&t;&t;&t;&t;&t;0xda0
DECL|macro|PCI_0P2P_I_O_BAR_SIZE
mdefine_line|#define PCI_0P2P_I_O_BAR_SIZE&t;&t;&t;&t;&t;0xd24
DECL|macro|PCI_1P2P_I_O_BAR_SIZE
mdefine_line|#define PCI_1P2P_I_O_BAR_SIZE&t;&t;&t;&t;&t;0xda4
DECL|macro|PCI_0CPU_BAR_SIZE
mdefine_line|#define PCI_0CPU_BAR_SIZE&t;&t;&t;&t;&t;0xd28
DECL|macro|PCI_1CPU_BAR_SIZE
mdefine_line|#define PCI_1CPU_BAR_SIZE&t;&t;&t;&t;&t;0xda8
DECL|macro|PCI_0DAC_SCS_0_BANK_SIZE
mdefine_line|#define PCI_0DAC_SCS_0_BANK_SIZE&t;&t;&t;&t;0xe00
DECL|macro|PCI_1DAC_SCS_0_BANK_SIZE
mdefine_line|#define PCI_1DAC_SCS_0_BANK_SIZE&t;&t;&t;&t;0xe80
DECL|macro|PCI_0DAC_SCS_1_BANK_SIZE
mdefine_line|#define PCI_0DAC_SCS_1_BANK_SIZE&t;&t;&t;&t;0xe04
DECL|macro|PCI_1DAC_SCS_1_BANK_SIZE
mdefine_line|#define PCI_1DAC_SCS_1_BANK_SIZE&t;&t;&t;&t;0xe84
DECL|macro|PCI_0DAC_SCS_2_BANK_SIZE
mdefine_line|#define PCI_0DAC_SCS_2_BANK_SIZE&t;&t;&t;&t;0xe08
DECL|macro|PCI_1DAC_SCS_2_BANK_SIZE
mdefine_line|#define PCI_1DAC_SCS_2_BANK_SIZE&t;&t;&t;&t;0xe88
DECL|macro|PCI_0DAC_SCS_3_BANK_SIZE
mdefine_line|#define PCI_0DAC_SCS_3_BANK_SIZE&t;&t;&t;&t;0xe0c
DECL|macro|PCI_1DAC_SCS_3_BANK_SIZE
mdefine_line|#define PCI_1DAC_SCS_3_BANK_SIZE&t;&t;&t;&t;0xe8c
DECL|macro|PCI_0DAC_CS_0_BANK_SIZE
mdefine_line|#define PCI_0DAC_CS_0_BANK_SIZE&t;&t;&t;&t;&t;0xe10
DECL|macro|PCI_1DAC_CS_0_BANK_SIZE
mdefine_line|#define PCI_1DAC_CS_0_BANK_SIZE&t;&t;&t;&t;&t;0xe90
DECL|macro|PCI_0DAC_CS_1_BANK_SIZE
mdefine_line|#define PCI_0DAC_CS_1_BANK_SIZE&t;&t;&t;&t;&t;0xe14
DECL|macro|PCI_1DAC_CS_1_BANK_SIZE
mdefine_line|#define PCI_1DAC_CS_1_BANK_SIZE&t;&t;&t;&t;&t;0xe94
DECL|macro|PCI_0DAC_CS_2_BANK_SIZE
mdefine_line|#define PCI_0DAC_CS_2_BANK_SIZE&t;&t;&t;&t;&t;0xe18
DECL|macro|PCI_1DAC_CS_2_BANK_SIZE
mdefine_line|#define PCI_1DAC_CS_2_BANK_SIZE&t;&t;&t;&t;&t;0xe98
DECL|macro|PCI_0DAC_CS_3_BANK_SIZE
mdefine_line|#define PCI_0DAC_CS_3_BANK_SIZE&t;&t;&t;&t;&t;0xe1c
DECL|macro|PCI_1DAC_CS_3_BANK_SIZE
mdefine_line|#define PCI_1DAC_CS_3_BANK_SIZE&t;&t;&t;&t;&t;0xe9c
DECL|macro|PCI_0DAC_BOOTCS_BANK_SIZE
mdefine_line|#define PCI_0DAC_BOOTCS_BANK_SIZE&t;&t;&t;&t;0xe20
DECL|macro|PCI_1DAC_BOOTCS_BANK_SIZE
mdefine_line|#define PCI_1DAC_BOOTCS_BANK_SIZE&t;&t;&t;&t;0xea0
DECL|macro|PCI_0DAC_P2P_MEM0_BAR_SIZE
mdefine_line|#define PCI_0DAC_P2P_MEM0_BAR_SIZE&t;&t;&t;&t;0xe24
DECL|macro|PCI_1DAC_P2P_MEM0_BAR_SIZE
mdefine_line|#define PCI_1DAC_P2P_MEM0_BAR_SIZE&t;&t;&t;&t;0xea4
DECL|macro|PCI_0DAC_P2P_MEM1_BAR_SIZE
mdefine_line|#define PCI_0DAC_P2P_MEM1_BAR_SIZE&t;&t;&t;&t;0xe28
DECL|macro|PCI_1DAC_P2P_MEM1_BAR_SIZE
mdefine_line|#define PCI_1DAC_P2P_MEM1_BAR_SIZE&t;&t;&t;&t;0xea8
DECL|macro|PCI_0DAC_CPU_BAR_SIZE
mdefine_line|#define PCI_0DAC_CPU_BAR_SIZE&t;&t;&t;&t;&t;0xe2c
DECL|macro|PCI_1DAC_CPU_BAR_SIZE
mdefine_line|#define PCI_1DAC_CPU_BAR_SIZE&t;&t;&t;&t;&t;0xeac
DECL|macro|PCI_0EXPANSION_ROM_BAR_SIZE
mdefine_line|#define PCI_0EXPANSION_ROM_BAR_SIZE&t;&t;&t;&t;0xd2c
DECL|macro|PCI_1EXPANSION_ROM_BAR_SIZE
mdefine_line|#define PCI_1EXPANSION_ROM_BAR_SIZE&t;&t;&t;&t;0xdac
DECL|macro|PCI_0BASE_ADDRESS_REGISTERS_ENABLE
mdefine_line|#define PCI_0BASE_ADDRESS_REGISTERS_ENABLE&t;&t;&t;0xc3c
DECL|macro|PCI_1BASE_ADDRESS_REGISTERS_ENABLE
mdefine_line|#define PCI_1BASE_ADDRESS_REGISTERS_ENABLE&t;&t;&t;0xcbc
DECL|macro|PCI_0SCS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0SCS_0_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xc48
DECL|macro|PCI_1SCS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1SCS_0_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xcc8
DECL|macro|PCI_0SCS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0SCS_1_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xd48
DECL|macro|PCI_1SCS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1SCS_1_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xdc8
DECL|macro|PCI_0SCS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0SCS_2_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xc4c
DECL|macro|PCI_1SCS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1SCS_2_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xccc
DECL|macro|PCI_0SCS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0SCS_3_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xd4c
DECL|macro|PCI_1SCS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1SCS_3_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xdcc
DECL|macro|PCI_0CS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0CS_0_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xc50
DECL|macro|PCI_1CS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1CS_0_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xcd0
DECL|macro|PCI_0CS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0CS_1_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xd50
DECL|macro|PCI_1CS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1CS_1_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xdd0
DECL|macro|PCI_0CS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0CS_2_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xd58
DECL|macro|PCI_1CS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1CS_2_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xdd8
DECL|macro|PCI_0CS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0CS_3_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xc54
DECL|macro|PCI_1CS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1CS_3_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xcd4
DECL|macro|PCI_0CS_BOOTCS_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0CS_BOOTCS_BASE_ADDRESS_REMAP&t;&t;&t;0xd54
DECL|macro|PCI_1CS_BOOTCS_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1CS_BOOTCS_BASE_ADDRESS_REMAP&t;&t;&t;0xdd4
DECL|macro|PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_LOW&t;&t;&t;0xd5c
DECL|macro|PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_LOW&t;&t;&t;0xddc
DECL|macro|PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_HIGH&t;&t;&t;0xd60
DECL|macro|PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_HIGH&t;&t;&t;0xde0
DECL|macro|PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_LOW&t;&t;&t;0xd64
DECL|macro|PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_LOW&t;&t;&t;0xde4
DECL|macro|PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_HIGH&t;&t;&t;0xd68
DECL|macro|PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_HIGH&t;&t;&t;0xde8
DECL|macro|PCI_0P2P_I_O_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0P2P_I_O_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xd6c
DECL|macro|PCI_1P2P_I_O_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1P2P_I_O_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xdec
DECL|macro|PCI_0CPU_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0CPU_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xd70
DECL|macro|PCI_1CPU_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1CPU_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xdf0
DECL|macro|PCI_0DAC_SCS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_SCS_0_BASE_ADDRESS_REMAP&t;&t;&t;0xf00
DECL|macro|PCI_1DAC_SCS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_SCS_0_BASE_ADDRESS_REMAP&t;&t;&t;0xff0
DECL|macro|PCI_0DAC_SCS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_SCS_1_BASE_ADDRESS_REMAP&t;&t;&t;0xf04
DECL|macro|PCI_1DAC_SCS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_SCS_1_BASE_ADDRESS_REMAP&t;&t;&t;0xf84
DECL|macro|PCI_0DAC_SCS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_SCS_2_BASE_ADDRESS_REMAP&t;&t;&t;0xf08
DECL|macro|PCI_1DAC_SCS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_SCS_2_BASE_ADDRESS_REMAP&t;&t;&t;0xf88
DECL|macro|PCI_0DAC_SCS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_SCS_3_BASE_ADDRESS_REMAP&t;&t;&t;0xf0c
DECL|macro|PCI_1DAC_SCS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_SCS_3_BASE_ADDRESS_REMAP&t;&t;&t;0xf8c
DECL|macro|PCI_0DAC_CS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_CS_0_BASE_ADDRESS_REMAP&t;&t;&t;0xf10
DECL|macro|PCI_1DAC_CS_0_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_CS_0_BASE_ADDRESS_REMAP&t;&t;&t;0xf90
DECL|macro|PCI_0DAC_CS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_CS_1_BASE_ADDRESS_REMAP&t;&t;&t;0xf14
DECL|macro|PCI_1DAC_CS_1_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_CS_1_BASE_ADDRESS_REMAP&t;&t;&t;0xf94
DECL|macro|PCI_0DAC_CS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_CS_2_BASE_ADDRESS_REMAP&t;&t;&t;0xf18
DECL|macro|PCI_1DAC_CS_2_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_CS_2_BASE_ADDRESS_REMAP&t;&t;&t;0xf98
DECL|macro|PCI_0DAC_CS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_CS_3_BASE_ADDRESS_REMAP&t;&t;&t;0xf1c
DECL|macro|PCI_1DAC_CS_3_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_CS_3_BASE_ADDRESS_REMAP&t;&t;&t;0xf9c
DECL|macro|PCI_0DAC_BOOTCS_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_BOOTCS_BASE_ADDRESS_REMAP&t;&t;&t;0xf20
DECL|macro|PCI_1DAC_BOOTCS_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_BOOTCS_BASE_ADDRESS_REMAP&t;&t;&t;0xfa0
DECL|macro|PCI_0DAC_P2P_MEM0_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_0DAC_P2P_MEM0_BASE_ADDRESS_REMAP_LOW&t;&t;0xf24
DECL|macro|PCI_1DAC_P2P_MEM0_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_1DAC_P2P_MEM0_BASE_ADDRESS_REMAP_LOW&t;&t;0xfa4
DECL|macro|PCI_0DAC_P2P_MEM0_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_0DAC_P2P_MEM0_BASE_ADDRESS_REMAP_HIGH&t;&t;0xf28
DECL|macro|PCI_1DAC_P2P_MEM0_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_1DAC_P2P_MEM0_BASE_ADDRESS_REMAP_HIGH&t;&t;0xfa8
DECL|macro|PCI_0DAC_P2P_MEM1_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_0DAC_P2P_MEM1_BASE_ADDRESS_REMAP_LOW&t;&t;0xf2c
DECL|macro|PCI_1DAC_P2P_MEM1_BASE_ADDRESS_REMAP_LOW
mdefine_line|#define PCI_1DAC_P2P_MEM1_BASE_ADDRESS_REMAP_LOW&t;&t;0xfac
DECL|macro|PCI_0DAC_P2P_MEM1_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_0DAC_P2P_MEM1_BASE_ADDRESS_REMAP_HIGH&t;&t;0xf30
DECL|macro|PCI_1DAC_P2P_MEM1_BASE_ADDRESS_REMAP_HIGH
mdefine_line|#define PCI_1DAC_P2P_MEM1_BASE_ADDRESS_REMAP_HIGH&t;&t;0xfb0
DECL|macro|PCI_0DAC_CPU_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0DAC_CPU_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xf34
DECL|macro|PCI_1DAC_CPU_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1DAC_CPU_BASE_ADDRESS_REMAP&t;&t;&t;&t;0xfb4
DECL|macro|PCI_0EXPANSION_ROM_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_0EXPANSION_ROM_BASE_ADDRESS_REMAP&t;&t;&t;0xf38
DECL|macro|PCI_1EXPANSION_ROM_BASE_ADDRESS_REMAP
mdefine_line|#define PCI_1EXPANSION_ROM_BASE_ADDRESS_REMAP&t;&t;&t;0xfb8
DECL|macro|PCI_0ADDRESS_DECODE_CONTROL
mdefine_line|#define PCI_0ADDRESS_DECODE_CONTROL&t;&t;&t;&t;0xd3c
DECL|macro|PCI_1ADDRESS_DECODE_CONTROL
mdefine_line|#define PCI_1ADDRESS_DECODE_CONTROL&t;&t;&t;&t;0xdbc
multiline_comment|/*&n; * PCI Control&n; */
DECL|macro|PCI_0COMMAND
mdefine_line|#define PCI_0COMMAND&t;&t;&t;&t;&t;&t;0xc00
DECL|macro|PCI_1COMMAND
mdefine_line|#define PCI_1COMMAND&t;&t;&t;&t;&t;&t;0xc80
DECL|macro|PCI_0MODE
mdefine_line|#define PCI_0MODE&t;&t;&t;&t;&t;&t;0xd00
DECL|macro|PCI_1MODE
mdefine_line|#define PCI_1MODE&t;&t;&t;&t;&t;&t;0xd80
DECL|macro|PCI_0TIMEOUT_RETRY
mdefine_line|#define PCI_0TIMEOUT_RETRY&t;&t;&t;&t;&t;0xc04
DECL|macro|PCI_1TIMEOUT_RETRY
mdefine_line|#define PCI_1TIMEOUT_RETRY&t;&t;&t;&t;&t;0xc84
DECL|macro|PCI_0READ_BUFFER_DISCARD_TIMER
mdefine_line|#define PCI_0READ_BUFFER_DISCARD_TIMER&t;&t;&t;&t;0xd04
DECL|macro|PCI_1READ_BUFFER_DISCARD_TIMER
mdefine_line|#define PCI_1READ_BUFFER_DISCARD_TIMER&t;&t;&t;&t;0xd84
DECL|macro|MSI_0TRIGGER_TIMER
mdefine_line|#define MSI_0TRIGGER_TIMER&t;&t;&t;&t;&t;0xc38
DECL|macro|MSI_1TRIGGER_TIMER
mdefine_line|#define MSI_1TRIGGER_TIMER&t;&t;&t;&t;&t;0xcb8
DECL|macro|PCI_0ARBITER_CONTROL
mdefine_line|#define PCI_0ARBITER_CONTROL&t;&t;&t;&t;&t;0x1d00
DECL|macro|PCI_1ARBITER_CONTROL
mdefine_line|#define PCI_1ARBITER_CONTROL&t;&t;&t;&t;&t;0x1d80
multiline_comment|/* changing untill here */
DECL|macro|PCI_0CROSS_BAR_CONTROL_LOW
mdefine_line|#define PCI_0CROSS_BAR_CONTROL_LOW&t;&t;&t;&t; 0x1d08
DECL|macro|PCI_0CROSS_BAR_CONTROL_HIGH
mdefine_line|#define PCI_0CROSS_BAR_CONTROL_HIGH&t;&t;&t;&t; 0x1d0c
DECL|macro|PCI_0CROSS_BAR_TIMEOUT
mdefine_line|#define PCI_0CROSS_BAR_TIMEOUT&t;&t;&t;&t;&t; 0x1d04
DECL|macro|PCI_0READ_RESPONSE_CROSS_BAR_CONTROL_LOW
mdefine_line|#define PCI_0READ_RESPONSE_CROSS_BAR_CONTROL_LOW&t;&t; 0x1d18
DECL|macro|PCI_0READ_RESPONSE_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define PCI_0READ_RESPONSE_CROSS_BAR_CONTROL_HIGH&t;&t; 0x1d1c
DECL|macro|PCI_0SYNC_BARRIER_VIRTUAL_REGISTER
mdefine_line|#define PCI_0SYNC_BARRIER_VIRTUAL_REGISTER&t;&t;&t; 0x1d10
DECL|macro|PCI_0P2P_CONFIGURATION
mdefine_line|#define PCI_0P2P_CONFIGURATION&t;&t;&t;&t;&t; 0x1d14
DECL|macro|PCI_0ACCESS_CONTROL_BASE_0_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_0_LOW&t;&t;&t;&t; 0x1e00
DECL|macro|PCI_0ACCESS_CONTROL_BASE_0_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_0_HIGH&t;&t;&t;&t; 0x1e04
DECL|macro|PCI_0ACCESS_CONTROL_TOP_0
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_0&t;&t;&t;&t; 0x1e08
DECL|macro|PCI_0ACCESS_CONTROL_BASE_1_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_1_LOW&t;&t;&t;&t; 0c1e10
DECL|macro|PCI_0ACCESS_CONTROL_BASE_1_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_1_HIGH&t;&t;&t;&t; 0x1e14
DECL|macro|PCI_0ACCESS_CONTROL_TOP_1
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_1&t;&t;&t;&t; 0x1e18
DECL|macro|PCI_0ACCESS_CONTROL_BASE_2_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_2_LOW&t;&t;&t;&t; 0c1e20
DECL|macro|PCI_0ACCESS_CONTROL_BASE_2_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_2_HIGH&t;&t;&t;&t; 0x1e24
DECL|macro|PCI_0ACCESS_CONTROL_TOP_2
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_2&t;&t;&t;&t; 0x1e28
DECL|macro|PCI_0ACCESS_CONTROL_BASE_3_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_3_LOW&t;&t;&t;&t; 0c1e30
DECL|macro|PCI_0ACCESS_CONTROL_BASE_3_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_3_HIGH&t;&t;&t;&t; 0x1e34
DECL|macro|PCI_0ACCESS_CONTROL_TOP_3
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_3&t;&t;&t;&t; 0x1e38
DECL|macro|PCI_0ACCESS_CONTROL_BASE_4_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_4_LOW&t;&t;&t;&t; 0c1e40
DECL|macro|PCI_0ACCESS_CONTROL_BASE_4_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_4_HIGH&t;&t;&t;&t; 0x1e44
DECL|macro|PCI_0ACCESS_CONTROL_TOP_4
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_4&t;&t;&t;&t; 0x1e48
DECL|macro|PCI_0ACCESS_CONTROL_BASE_5_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_5_LOW&t;&t;&t;&t; 0c1e50
DECL|macro|PCI_0ACCESS_CONTROL_BASE_5_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_5_HIGH&t;&t;&t;&t; 0x1e54
DECL|macro|PCI_0ACCESS_CONTROL_TOP_5
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_5&t;&t;&t;&t; 0x1e58
DECL|macro|PCI_0ACCESS_CONTROL_BASE_6_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_6_LOW&t;&t;&t;&t; 0c1e60
DECL|macro|PCI_0ACCESS_CONTROL_BASE_6_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_6_HIGH&t;&t;&t;&t; 0x1e64
DECL|macro|PCI_0ACCESS_CONTROL_TOP_6
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_6&t;&t;&t;&t; 0x1e68
DECL|macro|PCI_0ACCESS_CONTROL_BASE_7_LOW
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_7_LOW&t;&t;&t;&t; 0c1e70
DECL|macro|PCI_0ACCESS_CONTROL_BASE_7_HIGH
mdefine_line|#define PCI_0ACCESS_CONTROL_BASE_7_HIGH&t;&t;&t;&t; 0x1e74
DECL|macro|PCI_0ACCESS_CONTROL_TOP_7
mdefine_line|#define PCI_0ACCESS_CONTROL_TOP_7&t;&t;&t;&t; 0x1e78
DECL|macro|PCI_1CROSS_BAR_CONTROL_LOW
mdefine_line|#define PCI_1CROSS_BAR_CONTROL_LOW&t;&t;&t;&t; 0x1d88
DECL|macro|PCI_1CROSS_BAR_CONTROL_HIGH
mdefine_line|#define PCI_1CROSS_BAR_CONTROL_HIGH&t;&t;&t;&t; 0x1d8c
DECL|macro|PCI_1CROSS_BAR_TIMEOUT
mdefine_line|#define PCI_1CROSS_BAR_TIMEOUT&t;&t;&t;&t;&t; 0x1d84
DECL|macro|PCI_1READ_RESPONSE_CROSS_BAR_CONTROL_LOW
mdefine_line|#define PCI_1READ_RESPONSE_CROSS_BAR_CONTROL_LOW&t;&t; 0x1d98
DECL|macro|PCI_1READ_RESPONSE_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define PCI_1READ_RESPONSE_CROSS_BAR_CONTROL_HIGH&t;&t; 0x1d9c
DECL|macro|PCI_1SYNC_BARRIER_VIRTUAL_REGISTER
mdefine_line|#define PCI_1SYNC_BARRIER_VIRTUAL_REGISTER&t;&t;&t; 0x1d90
DECL|macro|PCI_1P2P_CONFIGURATION
mdefine_line|#define PCI_1P2P_CONFIGURATION&t;&t;&t;&t;&t; 0x1d94
DECL|macro|PCI_1ACCESS_CONTROL_BASE_0_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_0_LOW&t;&t;&t;&t; 0x1e80
DECL|macro|PCI_1ACCESS_CONTROL_BASE_0_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_0_HIGH&t;&t;&t;&t; 0x1e84
DECL|macro|PCI_1ACCESS_CONTROL_TOP_0
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_0&t;&t;&t;&t; 0x1e88
DECL|macro|PCI_1ACCESS_CONTROL_BASE_1_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_1_LOW&t;&t;&t;&t; 0c1e90
DECL|macro|PCI_1ACCESS_CONTROL_BASE_1_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_1_HIGH&t;&t;&t;&t; 0x1e94
DECL|macro|PCI_1ACCESS_CONTROL_TOP_1
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_1&t;&t;&t;&t; 0x1e98
DECL|macro|PCI_1ACCESS_CONTROL_BASE_2_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_2_LOW&t;&t;&t;&t; 0c1ea0
DECL|macro|PCI_1ACCESS_CONTROL_BASE_2_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_2_HIGH&t;&t;&t;&t; 0x1ea4
DECL|macro|PCI_1ACCESS_CONTROL_TOP_2
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_2&t;&t;&t;&t; 0x1ea8
DECL|macro|PCI_1ACCESS_CONTROL_BASE_3_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_3_LOW&t;&t;&t;&t; 0c1eb0
DECL|macro|PCI_1ACCESS_CONTROL_BASE_3_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_3_HIGH&t;&t;&t;&t; 0x1eb4
DECL|macro|PCI_1ACCESS_CONTROL_TOP_3
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_3&t;&t;&t;&t; 0x1eb8
DECL|macro|PCI_1ACCESS_CONTROL_BASE_4_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_4_LOW&t;&t;&t;&t; 0c1ec0
DECL|macro|PCI_1ACCESS_CONTROL_BASE_4_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_4_HIGH&t;&t;&t;&t; 0x1ec4
DECL|macro|PCI_1ACCESS_CONTROL_TOP_4
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_4&t;&t;&t;&t; 0x1ec8
DECL|macro|PCI_1ACCESS_CONTROL_BASE_5_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_5_LOW&t;&t;&t;&t; 0c1ed0
DECL|macro|PCI_1ACCESS_CONTROL_BASE_5_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_5_HIGH&t;&t;&t;&t; 0x1ed4
DECL|macro|PCI_1ACCESS_CONTROL_TOP_5
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_5&t;&t;&t;&t; 0x1ed8
DECL|macro|PCI_1ACCESS_CONTROL_BASE_6_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_6_LOW&t;&t;&t;&t; 0c1ee0
DECL|macro|PCI_1ACCESS_CONTROL_BASE_6_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_6_HIGH&t;&t;&t;&t; 0x1ee4
DECL|macro|PCI_1ACCESS_CONTROL_TOP_6
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_6&t;&t;&t;&t; 0x1ee8
DECL|macro|PCI_1ACCESS_CONTROL_BASE_7_LOW
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_7_LOW&t;&t;&t;&t; 0c1ef0
DECL|macro|PCI_1ACCESS_CONTROL_BASE_7_HIGH
mdefine_line|#define PCI_1ACCESS_CONTROL_BASE_7_HIGH&t;&t;&t;&t; 0x1ef4
DECL|macro|PCI_1ACCESS_CONTROL_TOP_7
mdefine_line|#define PCI_1ACCESS_CONTROL_TOP_7&t;&t;&t;&t; 0x1ef8
multiline_comment|/*&n; * PCI Snoop Control&n; */
DECL|macro|PCI_0SNOOP_CONTROL_BASE_0_LOW
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_0_LOW&t;&t;&t;&t; 0x1f00
DECL|macro|PCI_0SNOOP_CONTROL_BASE_0_HIGH
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_0_HIGH&t;&t;&t;&t; 0x1f04
DECL|macro|PCI_0SNOOP_CONTROL_TOP_0
mdefine_line|#define PCI_0SNOOP_CONTROL_TOP_0&t;&t;&t;&t; 0x1f08
DECL|macro|PCI_0SNOOP_CONTROL_BASE_1_0_LOW
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_1_0_LOW&t;&t;&t;&t; 0x1f10
DECL|macro|PCI_0SNOOP_CONTROL_BASE_1_0_HIGH
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_1_0_HIGH&t;&t;&t; 0x1f14
DECL|macro|PCI_0SNOOP_CONTROL_TOP_1
mdefine_line|#define PCI_0SNOOP_CONTROL_TOP_1&t;&t;&t;&t; 0x1f18
DECL|macro|PCI_0SNOOP_CONTROL_BASE_2_0_LOW
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_2_0_LOW&t;&t;&t;&t; 0x1f20
DECL|macro|PCI_0SNOOP_CONTROL_BASE_2_0_HIGH
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_2_0_HIGH&t;&t;&t; 0x1f24
DECL|macro|PCI_0SNOOP_CONTROL_TOP_2
mdefine_line|#define PCI_0SNOOP_CONTROL_TOP_2&t;&t;&t;&t; 0x1f28
DECL|macro|PCI_0SNOOP_CONTROL_BASE_3_0_LOW
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_3_0_LOW&t;&t;&t;&t; 0x1f30
DECL|macro|PCI_0SNOOP_CONTROL_BASE_3_0_HIGH
mdefine_line|#define PCI_0SNOOP_CONTROL_BASE_3_0_HIGH&t;&t;&t; 0x1f34
DECL|macro|PCI_0SNOOP_CONTROL_TOP_3
mdefine_line|#define PCI_0SNOOP_CONTROL_TOP_3&t;&t;&t;&t; 0x1f38
DECL|macro|PCI_1SNOOP_CONTROL_BASE_0_LOW
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_0_LOW&t;&t;&t;&t; 0x1f80
DECL|macro|PCI_1SNOOP_CONTROL_BASE_0_HIGH
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_0_HIGH&t;&t;&t;&t; 0x1f84
DECL|macro|PCI_1SNOOP_CONTROL_TOP_0
mdefine_line|#define PCI_1SNOOP_CONTROL_TOP_0&t;&t;&t;&t; 0x1f88
DECL|macro|PCI_1SNOOP_CONTROL_BASE_1_0_LOW
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_1_0_LOW&t;&t;&t;&t; 0x1f90
DECL|macro|PCI_1SNOOP_CONTROL_BASE_1_0_HIGH
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_1_0_HIGH&t;&t;&t; 0x1f94
DECL|macro|PCI_1SNOOP_CONTROL_TOP_1
mdefine_line|#define PCI_1SNOOP_CONTROL_TOP_1&t;&t;&t;&t; 0x1f98
DECL|macro|PCI_1SNOOP_CONTROL_BASE_2_0_LOW
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_2_0_LOW&t;&t;&t;&t; 0x1fa0
DECL|macro|PCI_1SNOOP_CONTROL_BASE_2_0_HIGH
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_2_0_HIGH&t;&t;&t; 0x1fa4
DECL|macro|PCI_1SNOOP_CONTROL_TOP_2
mdefine_line|#define PCI_1SNOOP_CONTROL_TOP_2&t;&t;&t;&t; 0x1fa8
DECL|macro|PCI_1SNOOP_CONTROL_BASE_3_0_LOW
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_3_0_LOW&t;&t;&t;&t; 0x1fb0
DECL|macro|PCI_1SNOOP_CONTROL_BASE_3_0_HIGH
mdefine_line|#define PCI_1SNOOP_CONTROL_BASE_3_0_HIGH&t;&t;&t; 0x1fb4
DECL|macro|PCI_1SNOOP_CONTROL_TOP_3
mdefine_line|#define PCI_1SNOOP_CONTROL_TOP_3&t;&t;&t;&t; 0x1fb8
multiline_comment|/*&n; * PCI Configuration Address&n; */
DECL|macro|PCI_0CONFIGURATION_ADDRESS
mdefine_line|#define PCI_0CONFIGURATION_ADDRESS&t;&t;&t;&t;0xcf8
DECL|macro|PCI_0CONFIGURATION_DATA_VIRTUAL_REGISTER
mdefine_line|#define PCI_0CONFIGURATION_DATA_VIRTUAL_REGISTER&t;&t;0xcfc
DECL|macro|PCI_1CONFIGURATION_ADDRESS
mdefine_line|#define PCI_1CONFIGURATION_ADDRESS&t;&t;&t;&t;0xc78
DECL|macro|PCI_1CONFIGURATION_DATA_VIRTUAL_REGISTER
mdefine_line|#define PCI_1CONFIGURATION_DATA_VIRTUAL_REGISTER&t;&t;0xc7c
DECL|macro|PCI_0INTERRUPT_ACKNOWLEDGE_VIRTUAL_REGISTER
mdefine_line|#define PCI_0INTERRUPT_ACKNOWLEDGE_VIRTUAL_REGISTER&t;&t;0xc34
DECL|macro|PCI_1INTERRUPT_ACKNOWLEDGE_VIRTUAL_REGISTER
mdefine_line|#define PCI_1INTERRUPT_ACKNOWLEDGE_VIRTUAL_REGISTER&t;&t;0xcb4
multiline_comment|/*&n; * PCI Error Report&n; */
DECL|macro|PCI_0SERR_MASK
mdefine_line|#define PCI_0SERR_MASK&t;&t;&t;&t;&t;&t; 0xc28
DECL|macro|PCI_0ERROR_ADDRESS_LOW
mdefine_line|#define PCI_0ERROR_ADDRESS_LOW&t;&t;&t;&t;&t; 0x1d40
DECL|macro|PCI_0ERROR_ADDRESS_HIGH
mdefine_line|#define PCI_0ERROR_ADDRESS_HIGH&t;&t;&t;&t;&t; 0x1d44
DECL|macro|PCI_0ERROR_DATA_LOW
mdefine_line|#define PCI_0ERROR_DATA_LOW&t;&t;&t;&t;&t; 0x1d48
DECL|macro|PCI_0ERROR_DATA_HIGH
mdefine_line|#define PCI_0ERROR_DATA_HIGH&t;&t;&t;&t;&t; 0x1d4c
DECL|macro|PCI_0ERROR_COMMAND
mdefine_line|#define PCI_0ERROR_COMMAND&t;&t;&t;&t;&t; 0x1d50
DECL|macro|PCI_0ERROR_CAUSE
mdefine_line|#define PCI_0ERROR_CAUSE&t;&t;&t;&t;&t; 0x1d58
DECL|macro|PCI_0ERROR_MASK
mdefine_line|#define PCI_0ERROR_MASK&t;&t;&t;&t;&t;&t; 0x1d5c
DECL|macro|PCI_1SERR_MASK
mdefine_line|#define PCI_1SERR_MASK&t;&t;&t;&t;&t;&t; 0xca8
DECL|macro|PCI_1ERROR_ADDRESS_LOW
mdefine_line|#define PCI_1ERROR_ADDRESS_LOW&t;&t;&t;&t;&t; 0x1dc0
DECL|macro|PCI_1ERROR_ADDRESS_HIGH
mdefine_line|#define PCI_1ERROR_ADDRESS_HIGH&t;&t;&t;&t;&t; 0x1dc4
DECL|macro|PCI_1ERROR_DATA_LOW
mdefine_line|#define PCI_1ERROR_DATA_LOW&t;&t;&t;&t;&t; 0x1dc8
DECL|macro|PCI_1ERROR_DATA_HIGH
mdefine_line|#define PCI_1ERROR_DATA_HIGH&t;&t;&t;&t;&t; 0x1dcc
DECL|macro|PCI_1ERROR_COMMAND
mdefine_line|#define PCI_1ERROR_COMMAND&t;&t;&t;&t;&t; 0x1dd0
DECL|macro|PCI_1ERROR_CAUSE
mdefine_line|#define PCI_1ERROR_CAUSE&t;&t;&t;&t;&t; 0x1dd8
DECL|macro|PCI_1ERROR_MASK
mdefine_line|#define PCI_1ERROR_MASK&t;&t;&t;&t;&t;&t; 0x1ddc
multiline_comment|/*&n; * Lslave Debug&t; (for internal use)&n; */
DECL|macro|L_SLAVE_X0_ADDRESS
mdefine_line|#define L_SLAVE_X0_ADDRESS&t;&t;&t;&t;&t;0x1d20
DECL|macro|L_SLAVE_X0_COMMAND_AND_ID
mdefine_line|#define L_SLAVE_X0_COMMAND_AND_ID&t;&t;&t;&t;0x1d24
DECL|macro|L_SLAVE_X1_ADDRESS
mdefine_line|#define L_SLAVE_X1_ADDRESS&t;&t;&t;&t;&t;0x1d28
DECL|macro|L_SLAVE_X1_COMMAND_AND_ID
mdefine_line|#define L_SLAVE_X1_COMMAND_AND_ID&t;&t;&t;&t;0x1d2c
DECL|macro|L_SLAVE_WRITE_DATA_LOW
mdefine_line|#define L_SLAVE_WRITE_DATA_LOW&t;&t;&t;&t;&t;0x1d30
DECL|macro|L_SLAVE_WRITE_DATA_HIGH
mdefine_line|#define L_SLAVE_WRITE_DATA_HIGH&t;&t;&t;&t;&t;0x1d34
DECL|macro|L_SLAVE_WRITE_BYTE_ENABLE
mdefine_line|#define L_SLAVE_WRITE_BYTE_ENABLE&t;&t;&t;&t;0x1d60
DECL|macro|L_SLAVE_READ_DATA_LOW
mdefine_line|#define L_SLAVE_READ_DATA_LOW&t;&t;&t;&t;&t;0x1d38
DECL|macro|L_SLAVE_READ_DATA_HIGH
mdefine_line|#define L_SLAVE_READ_DATA_HIGH&t;&t;&t;&t;&t;0x1d3c
DECL|macro|L_SLAVE_READ_ID
mdefine_line|#define L_SLAVE_READ_ID&t;&t;&t;&t;&t;&t;0x1d64
macro_line|#if 0 /* Disabled because PCI_* namespace belongs to PCI subsystem ... */
multiline_comment|/*&n; * PCI Configuration Function 0&n; */
mdefine_line|#define PCI_DEVICE_AND_VENDOR_ID&t;&t;&t;&t;0x000
mdefine_line|#define PCI_STATUS_AND_COMMAND&t;&t;&t;&t;&t;0x004
mdefine_line|#define PCI_CLASS_CODE_AND_REVISION_ID&t;&t;&t;&t;0x008
mdefine_line|#define PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE&t;&t;0x00C
mdefine_line|#define PCI_SCS_0_BASE_ADDRESS&t;&t;&t;&t;&t;0x010
mdefine_line|#define PCI_SCS_1_BASE_ADDRESS&t;&t;&t;&t;&t;0x014
mdefine_line|#define PCI_SCS_2_BASE_ADDRESS&t;&t;&t;&t;&t;0x018
mdefine_line|#define PCI_SCS_3_BASE_ADDRESS&t;&t;&t;&t;&t;0x01C
mdefine_line|#define PCI_INTERNAL_REGISTERS_MEMORY_MAPPED_BASE_ADDRESS&t;0x020
mdefine_line|#define PCI_INTERNAL_REGISTERS_I_OMAPPED_BASE_ADDRESS&t;&t;0x024
mdefine_line|#define PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID&t;&t;0x02C
mdefine_line|#define PCI_EXPANSION_ROM_BASE_ADDRESS_REGISTER&t;&t;&t;0x030
mdefine_line|#define PCI_CAPABILTY_LIST_POINTER&t;&t;&t;&t;0x034
mdefine_line|#define PCI_INTERRUPT_PIN_AND_LINE&t;&t;&t;&t;0x03C
mdefine_line|#define PCI_POWER_MANAGEMENT_CAPABILITY&t;&t;&t;&t;0x040
mdefine_line|#define PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL&t;&t;&t;0x044
mdefine_line|#define PCI_VPD_ADDRESS&t;&t;&t;&t;&t;&t;0x048
mdefine_line|#define PCI_VPD_DATA&t;&t;&t;&t;&t;&t;0X04c
mdefine_line|#define PCI_MSI_MESSAGE_CONTROL&t;&t;&t;&t;&t;0x050
mdefine_line|#define PCI_MSI_MESSAGE_ADDRESS&t;&t;&t;&t;&t;0x054
mdefine_line|#define PCI_MSI_MESSAGE_UPPER_ADDRESS&t;&t;&t;&t;0x058
mdefine_line|#define PCI_MSI_MESSAGE_DATA&t;&t;&t;&t;&t;0x05c
mdefine_line|#define PCI_COMPACT_PCI_HOT_SWAP_CAPABILITY&t;&t;&t;0x058
multiline_comment|/*&n; * PCI Configuration Function 1&n; */
mdefine_line|#define PCI_CS_0_BASE_ADDRESS&t;&t;&t;&t;&t;0x110
mdefine_line|#define PCI_CS_1_BASE_ADDRESS&t;&t;&t;&t;&t;0x114
mdefine_line|#define PCI_CS_2_BASE_ADDRESS&t;&t;&t;&t;&t;0x118
mdefine_line|#define PCI_CS_3_BASE_ADDRESS&t;&t;&t;&t;&t;0x11c
mdefine_line|#define PCI_BOOTCS_BASE_ADDRESS&t;&t;&t;&t;&t;0x120
multiline_comment|/*&n; * PCI Configuration Function 2&n; */
mdefine_line|#define PCI_P2P_MEM0_BASE_ADDRESS&t;&t;&t;&t;0x210
mdefine_line|#define PCI_P2P_MEM1_BASE_ADDRESS&t;&t;&t;&t;0x214
mdefine_line|#define PCI_P2P_I_O_BASE_ADDRESS&t;&t;&t;&t;0x218
mdefine_line|#define PCI_CPU_BASE_ADDRESS&t;&t;&t;&t;&t;0x21c
multiline_comment|/*&n; * PCI Configuration Function 4&n; */
mdefine_line|#define PCI_DAC_SCS_0_BASE_ADDRESS_LOW&t;&t;&t;&t;0x410
mdefine_line|#define PCI_DAC_SCS_0_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x414
mdefine_line|#define PCI_DAC_SCS_1_BASE_ADDRESS_LOW&t;&t;&t;&t;0x418
mdefine_line|#define PCI_DAC_SCS_1_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x41c
mdefine_line|#define PCI_DAC_P2P_MEM0_BASE_ADDRESS_LOW&t;&t;&t;0x420
mdefine_line|#define PCI_DAC_P2P_MEM0_BASE_ADDRESS_HIGH&t;&t;&t;0x424
multiline_comment|/*&n; * PCI Configuration Function 5&n; */
mdefine_line|#define PCI_DAC_SCS_2_BASE_ADDRESS_LOW&t;&t;&t;&t;0x510
mdefine_line|#define PCI_DAC_SCS_2_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x514
mdefine_line|#define PCI_DAC_SCS_3_BASE_ADDRESS_LOW&t;&t;&t;&t;0x518
mdefine_line|#define PCI_DAC_SCS_3_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x51c
mdefine_line|#define PCI_DAC_P2P_MEM1_BASE_ADDRESS_LOW&t;&t;&t;0x520
mdefine_line|#define PCI_DAC_P2P_MEM1_BASE_ADDRESS_HIGH&t;&t;&t;0x524
multiline_comment|/*&n; * PCI Configuration Function 6&n; */
mdefine_line|#define PCI_DAC_CS_0_BASE_ADDRESS_LOW&t;&t;&t;&t;0x610
mdefine_line|#define PCI_DAC_CS_0_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x614
mdefine_line|#define PCI_DAC_CS_1_BASE_ADDRESS_LOW&t;&t;&t;&t;0x618
mdefine_line|#define PCI_DAC_CS_1_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x61c
mdefine_line|#define PCI_DAC_CS_2_BASE_ADDRESS_LOW&t;&t;&t;&t;0x620
mdefine_line|#define PCI_DAC_CS_2_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x624
multiline_comment|/*&n; * PCI Configuration Function 7&n; */
mdefine_line|#define PCI_DAC_CS_3_BASE_ADDRESS_LOW&t;&t;&t;&t;0x710
mdefine_line|#define PCI_DAC_CS_3_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x714
mdefine_line|#define PCI_DAC_BOOTCS_BASE_ADDRESS_LOW&t;&t;&t;&t;0x718
mdefine_line|#define PCI_DAC_BOOTCS_BASE_ADDRESS_HIGH&t;&t;&t;0x71c
mdefine_line|#define PCI_DAC_CPU_BASE_ADDRESS_LOW&t;&t;&t;&t;0x720
mdefine_line|#define PCI_DAC_CPU_BASE_ADDRESS_HIGH&t;&t;&t;&t;0x724
macro_line|#endif
multiline_comment|/*&n; * Interrupts&n; */
DECL|macro|LOW_INTERRUPT_CAUSE_REGISTER
mdefine_line|#define LOW_INTERRUPT_CAUSE_REGISTER&t;&t;&t;&t;0xc18
DECL|macro|HIGH_INTERRUPT_CAUSE_REGISTER
mdefine_line|#define HIGH_INTERRUPT_CAUSE_REGISTER&t;&t;&t;&t;0xc68
DECL|macro|CPU_INTERRUPT_MASK_REGISTER_LOW
mdefine_line|#define CPU_INTERRUPT_MASK_REGISTER_LOW&t;&t;&t;&t;0xc1c
DECL|macro|CPU_INTERRUPT_MASK_REGISTER_HIGH
mdefine_line|#define CPU_INTERRUPT_MASK_REGISTER_HIGH&t;&t;&t;0xc6c
DECL|macro|CPU_SELECT_CAUSE_REGISTER
mdefine_line|#define CPU_SELECT_CAUSE_REGISTER&t;&t;&t;&t;0xc70
DECL|macro|PCI_0INTERRUPT_CAUSE_MASK_REGISTER_LOW
mdefine_line|#define PCI_0INTERRUPT_CAUSE_MASK_REGISTER_LOW&t;&t;&t;0xc24
DECL|macro|PCI_0INTERRUPT_CAUSE_MASK_REGISTER_HIGH
mdefine_line|#define PCI_0INTERRUPT_CAUSE_MASK_REGISTER_HIGH&t;&t;&t;0xc64
DECL|macro|PCI_0SELECT_CAUSE
mdefine_line|#define PCI_0SELECT_CAUSE&t;&t;&t;&t;&t;0xc74
DECL|macro|PCI_1INTERRUPT_CAUSE_MASK_REGISTER_LOW
mdefine_line|#define PCI_1INTERRUPT_CAUSE_MASK_REGISTER_LOW&t;&t;&t;0xca4
DECL|macro|PCI_1INTERRUPT_CAUSE_MASK_REGISTER_HIGH
mdefine_line|#define PCI_1INTERRUPT_CAUSE_MASK_REGISTER_HIGH&t;&t;&t;0xce4
DECL|macro|PCI_1SELECT_CAUSE
mdefine_line|#define PCI_1SELECT_CAUSE&t;&t;&t;&t;&t;0xcf4
DECL|macro|CPU_INT_0_MASK
mdefine_line|#define CPU_INT_0_MASK&t;&t;&t;&t;&t;&t;0xe60
DECL|macro|CPU_INT_1_MASK
mdefine_line|#define CPU_INT_1_MASK&t;&t;&t;&t;&t;&t;0xe64
DECL|macro|CPU_INT_2_MASK
mdefine_line|#define CPU_INT_2_MASK&t;&t;&t;&t;&t;&t;0xe68
DECL|macro|CPU_INT_3_MASK
mdefine_line|#define CPU_INT_3_MASK&t;&t;&t;&t;&t;&t;0xe6c
multiline_comment|/*&n; * I20 Support registers&n; */
DECL|macro|INBOUND_MESSAGE_REGISTER0_PCI0_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_PCI0_SIDE&t;&t;&t;0x010
DECL|macro|INBOUND_MESSAGE_REGISTER1_PCI0_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_PCI0_SIDE&t;&t;&t;0x014
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_PCI0_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_PCI0_SIDE&t;&t;&t;0x018
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_PCI0_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_PCI0_SIDE&t;&t;&t;0x01C
DECL|macro|INBOUND_DOORBELL_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_PCI0_SIDE&t;&t;&t;0x020
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_PCI0_SIDE&t;&t;0x024
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_PCI0_SIDE&t;&t;0x028
DECL|macro|OUTBOUND_DOORBELL_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_PCI0_SIDE&t;&t;&t;0x02C
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI0_SIDE&t;&t;0x030
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_PCI0_SIDE&t;&t;0x034
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI0_SIDE&t;&t;0x040
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI0_SIDE&t;&t;0x044
DECL|macro|QUEUE_CONTROL_REGISTER_PCI0_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_PCI0_SIDE&t;&t;&t;0x050
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_PCI0_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_PCI0_SIDE&t;&t;&t;0x054
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_PCI0_SIDE&t;&t;0x060
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_PCI0_SIDE&t;&t;0x064
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_PCI0_SIDE&t;&t;0x068
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_PCI0_SIDE&t;&t;0x06C
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI0_SIDE&t;&t;0x070
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI0_SIDE&t;&t;0x074
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI0_SIDE&t;&t;0x0F8
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI0_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI0_SIDE&t;&t;0x0FC
DECL|macro|INBOUND_MESSAGE_REGISTER0_PCI1_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_PCI1_SIDE&t;&t;&t;0x090
DECL|macro|INBOUND_MESSAGE_REGISTER1_PCI1_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_PCI1_SIDE&t;&t;&t;0x094
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_PCI1_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_PCI1_SIDE&t;&t;&t;0x098
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_PCI1_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_PCI1_SIDE&t;&t;&t;0x09C
DECL|macro|INBOUND_DOORBELL_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_PCI1_SIDE&t;&t;&t;0x0A0
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_PCI1_SIDE&t;&t;0x0A4
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_PCI1_SIDE&t;&t;0x0A8
DECL|macro|OUTBOUND_DOORBELL_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_PCI1_SIDE&t;&t;&t;0x0AC
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI1_SIDE&t;&t;0x0B0
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_PCI1_SIDE&t;&t;0x0B4
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI1_SIDE&t;&t;0x0C0
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI1_SIDE&t;&t;0x0C4
DECL|macro|QUEUE_CONTROL_REGISTER_PCI1_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_PCI1_SIDE&t;&t;&t;0x0D0
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_PCI1_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_PCI1_SIDE&t;&t;&t;0x0D4
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_PCI1_SIDE&t;&t;0x0E0
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_PCI1_SIDE&t;&t;0x0E4
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_PCI1_SIDE&t;&t;0x0E8
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_PCI1_SIDE&t;&t;0x0EC
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI1_SIDE&t;&t;0x0F0
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI1_SIDE&t;&t;0x0F4
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI1_SIDE&t;&t;0x078
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI1_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI1_SIDE&t;&t;0x07C
DECL|macro|INBOUND_MESSAGE_REGISTER0_CPU0_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_CPU0_SIDE&t;&t;&t;0X1C10
DECL|macro|INBOUND_MESSAGE_REGISTER1_CPU0_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_CPU0_SIDE&t;&t;&t;0X1C14
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_CPU0_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_CPU0_SIDE&t;&t;&t;0X1C18
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_CPU0_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_CPU0_SIDE&t;&t;&t;0X1C1C
DECL|macro|INBOUND_DOORBELL_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_CPU0_SIDE&t;&t;&t;0X1C20
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_CPU0_SIDE&t;&t;0X1C24
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_CPU0_SIDE&t;&t;0X1C28
DECL|macro|OUTBOUND_DOORBELL_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_CPU0_SIDE&t;&t;&t;0X1C2C
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU0_SIDE&t;&t;0X1C30
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_CPU0_SIDE&t;&t;0X1C34
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU0_SIDE&t;&t;0X1C40
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU0_SIDE&t;&t;0X1C44
DECL|macro|QUEUE_CONTROL_REGISTER_CPU0_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_CPU0_SIDE&t;&t;&t;0X1C50
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_CPU0_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_CPU0_SIDE&t;&t;&t;0X1C54
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1C60
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1C64
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1C68
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1C6C
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1C70
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1C74
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1CF8
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU0_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU0_SIDE&t;&t;0X1CFC
DECL|macro|INBOUND_MESSAGE_REGISTER0_CPU1_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_CPU1_SIDE&t;&t;&t;0X1C90
DECL|macro|INBOUND_MESSAGE_REGISTER1_CPU1_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_CPU1_SIDE&t;&t;&t;0X1C94
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_CPU1_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_CPU1_SIDE&t;&t;&t;0X1C98
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_CPU1_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_CPU1_SIDE&t;&t;&t;0X1C9C
DECL|macro|INBOUND_DOORBELL_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_CPU1_SIDE&t;&t;&t;0X1CA0
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_CPU1_SIDE&t;&t;0X1CA4
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_CPU1_SIDE&t;&t;0X1CA8
DECL|macro|OUTBOUND_DOORBELL_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_CPU1_SIDE&t;&t;&t;0X1CAC
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU1_SIDE&t;&t;0X1CB0
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_CPU1_SIDE&t;&t;0X1CB4
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU1_SIDE&t;&t;0X1CC0
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU1_SIDE&t;&t;0X1CC4
DECL|macro|QUEUE_CONTROL_REGISTER_CPU1_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_CPU1_SIDE&t;&t;&t;0X1CD0
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_CPU1_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_CPU1_SIDE&t;&t;&t;0X1CD4
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1CE0
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1CE4
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1CE8
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1CEC
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1CF0
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1CF4
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1C78
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU1_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU1_SIDE&t;&t;0X1C7C
multiline_comment|/*&n; * Communication Unit Registers&n; */
DECL|macro|ETHERNET_0_ADDRESS_CONTROL_LOW
mdefine_line|#define ETHERNET_0_ADDRESS_CONTROL_LOW
DECL|macro|ETHERNET_0_ADDRESS_CONTROL_HIGH
mdefine_line|#define ETHERNET_0_ADDRESS_CONTROL_HIGH&t;&t;&t;&t;0xf204
DECL|macro|ETHERNET_0_RECEIVE_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_0_RECEIVE_BUFFER_PCI_HIGH_ADDRESS&t;&t;0xf208
DECL|macro|ETHERNET_0_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_0_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS&t;&t;0xf20c
DECL|macro|ETHERNET_0_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_0_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf210
DECL|macro|ETHERNET_0_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_0_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf214
DECL|macro|ETHERNET_0_HASH_TABLE_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_0_HASH_TABLE_PCI_HIGH_ADDRESS&t;&t;&t;0xf218
DECL|macro|ETHERNET_1_ADDRESS_CONTROL_LOW
mdefine_line|#define ETHERNET_1_ADDRESS_CONTROL_LOW&t;&t;&t;&t;0xf220
DECL|macro|ETHERNET_1_ADDRESS_CONTROL_HIGH
mdefine_line|#define ETHERNET_1_ADDRESS_CONTROL_HIGH&t;&t;&t;&t;0xf224
DECL|macro|ETHERNET_1_RECEIVE_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_1_RECEIVE_BUFFER_PCI_HIGH_ADDRESS&t;&t;0xf228
DECL|macro|ETHERNET_1_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_1_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS&t;&t;0xf22c
DECL|macro|ETHERNET_1_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_1_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf230
DECL|macro|ETHERNET_1_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_1_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf234
DECL|macro|ETHERNET_1_HASH_TABLE_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_1_HASH_TABLE_PCI_HIGH_ADDRESS&t;&t;&t;0xf238
DECL|macro|ETHERNET_2_ADDRESS_CONTROL_LOW
mdefine_line|#define ETHERNET_2_ADDRESS_CONTROL_LOW&t;&t;&t;&t;0xf240
DECL|macro|ETHERNET_2_ADDRESS_CONTROL_HIGH
mdefine_line|#define ETHERNET_2_ADDRESS_CONTROL_HIGH&t;&t;&t;&t;0xf244
DECL|macro|ETHERNET_2_RECEIVE_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_2_RECEIVE_BUFFER_PCI_HIGH_ADDRESS&t;&t;0xf248
DECL|macro|ETHERNET_2_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_2_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS&t;&t;0xf24c
DECL|macro|ETHERNET_2_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_2_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf250
DECL|macro|ETHERNET_2_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_2_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf254
DECL|macro|ETHERNET_2_HASH_TABLE_PCI_HIGH_ADDRESS
mdefine_line|#define ETHERNET_2_HASH_TABLE_PCI_HIGH_ADDRESS&t;&t;&t;0xf258
DECL|macro|MPSC_0_ADDRESS_CONTROL_LOW
mdefine_line|#define MPSC_0_ADDRESS_CONTROL_LOW&t;&t;&t;&t;0xf280
DECL|macro|MPSC_0_ADDRESS_CONTROL_HIGH
mdefine_line|#define MPSC_0_ADDRESS_CONTROL_HIGH&t;&t;&t;&t;0xf284
DECL|macro|MPSC_0_RECEIVE_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_0_RECEIVE_BUFFER_PCI_HIGH_ADDRESS&t;&t;&t;0xf288
DECL|macro|MPSC_0_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_0_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS&t;&t;&t;0xf28c
DECL|macro|MPSC_0_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_0_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf290
DECL|macro|MPSC_0_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_0_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf294
DECL|macro|MPSC_1_ADDRESS_CONTROL_LOW
mdefine_line|#define MPSC_1_ADDRESS_CONTROL_LOW&t;&t;&t;&t;0xf2a0
DECL|macro|MPSC_1_ADDRESS_CONTROL_HIGH
mdefine_line|#define MPSC_1_ADDRESS_CONTROL_HIGH&t;&t;&t;&t;0xf2a4
DECL|macro|MPSC_1_RECEIVE_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_1_RECEIVE_BUFFER_PCI_HIGH_ADDRESS&t;&t;&t;0xf2a8
DECL|macro|MPSC_1_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_1_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS&t;&t;&t;0xf2ac
DECL|macro|MPSC_1_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_1_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf2b0
DECL|macro|MPSC_1_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_1_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf2b4
DECL|macro|MPSC_2_ADDRESS_CONTROL_LOW
mdefine_line|#define MPSC_2_ADDRESS_CONTROL_LOW&t;&t;&t;&t;0xf2c0
DECL|macro|MPSC_2_ADDRESS_CONTROL_HIGH
mdefine_line|#define MPSC_2_ADDRESS_CONTROL_HIGH&t;&t;&t;&t;0xf2c4
DECL|macro|MPSC_2_RECEIVE_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_2_RECEIVE_BUFFER_PCI_HIGH_ADDRESS&t;&t;&t;0xf2c8
DECL|macro|MPSC_2_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_2_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS&t;&t;&t;0xf2cc
DECL|macro|MPSC_2_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_2_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf2d0
DECL|macro|MPSC_2_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS
mdefine_line|#define MPSC_2_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS&t;&t;0xf2d4
DECL|macro|SERIAL_INIT_PCI_HIGH_ADDRESS
mdefine_line|#define SERIAL_INIT_PCI_HIGH_ADDRESS&t;&t;&t;&t;0xf320
DECL|macro|SERIAL_INIT_LAST_DATA
mdefine_line|#define SERIAL_INIT_LAST_DATA&t;&t;&t;&t;&t;0xf324
DECL|macro|SERIAL_INIT_STATUS_AND_CONTROL
mdefine_line|#define SERIAL_INIT_STATUS_AND_CONTROL&t;&t;&t;&t;0xf328
DECL|macro|COMM_UNIT_ARBITER_CONTROL
mdefine_line|#define COMM_UNIT_ARBITER_CONTROL&t;&t;&t;&t;0xf300
DECL|macro|COMM_UNIT_CROSS_BAR_TIMEOUT
mdefine_line|#define COMM_UNIT_CROSS_BAR_TIMEOUT&t;&t;&t;&t;0xf304
DECL|macro|COMM_UNIT_INTERRUPT_CAUSE
mdefine_line|#define COMM_UNIT_INTERRUPT_CAUSE&t;&t;&t;&t;0xf310
DECL|macro|COMM_UNIT_INTERRUPT_MASK
mdefine_line|#define COMM_UNIT_INTERRUPT_MASK&t;&t;&t;&t;0xf314
DECL|macro|COMM_UNIT_ERROR_ADDRESS
mdefine_line|#define COMM_UNIT_ERROR_ADDRESS&t;&t;&t;&t;&t;0xf314
multiline_comment|/*&n; * Cunit Debug&t;(for internal use)&n; */
DECL|macro|CUNIT_ADDRESS
mdefine_line|#define CUNIT_ADDRESS&t;&t;&t;&t;&t;&t;0xf340
DECL|macro|CUNIT_COMMAND_AND_ID
mdefine_line|#define CUNIT_COMMAND_AND_ID&t;&t;&t;&t;&t;0xf344
DECL|macro|CUNIT_WRITE_DATA_LOW
mdefine_line|#define CUNIT_WRITE_DATA_LOW&t;&t;&t;&t;&t;0xf348
DECL|macro|CUNIT_WRITE_DATA_HIGH
mdefine_line|#define CUNIT_WRITE_DATA_HIGH&t;&t;&t;&t;&t;0xf34c
DECL|macro|CUNIT_WRITE_BYTE_ENABLE
mdefine_line|#define CUNIT_WRITE_BYTE_ENABLE&t;&t;&t;&t;&t;0xf358
DECL|macro|CUNIT_READ_DATA_LOW
mdefine_line|#define CUNIT_READ_DATA_LOW&t;&t;&t;&t;&t;0xf350
DECL|macro|CUNIT_READ_DATA_HIGH
mdefine_line|#define CUNIT_READ_DATA_HIGH&t;&t;&t;&t;&t;0xf354
DECL|macro|CUNIT_READ_ID
mdefine_line|#define CUNIT_READ_ID&t;&t;&t;&t;&t;&t;0xf35c
multiline_comment|/*&n; * Fast Ethernet Unit Registers&n; */
multiline_comment|/* Ethernet */
DECL|macro|ETHERNET_PHY_ADDRESS_REGISTER
mdefine_line|#define ETHERNET_PHY_ADDRESS_REGISTER&t;&t;&t;&t;0x2000
DECL|macro|ETHERNET_SMI_REGISTER
mdefine_line|#define ETHERNET_SMI_REGISTER&t;&t;&t;&t;&t;0x2010
multiline_comment|/* Ethernet 0 */
DECL|macro|ETHERNET0_PORT_CONFIGURATION_REGISTER
mdefine_line|#define ETHERNET0_PORT_CONFIGURATION_REGISTER&t;&t;&t;0x2400
DECL|macro|ETHERNET0_PORT_CONFIGURATION_EXTEND_REGISTER
mdefine_line|#define ETHERNET0_PORT_CONFIGURATION_EXTEND_REGISTER&t;&t;0x2408
DECL|macro|ETHERNET0_PORT_COMMAND_REGISTER
mdefine_line|#define ETHERNET0_PORT_COMMAND_REGISTER&t;&t;&t;&t;0x2410
DECL|macro|ETHERNET0_PORT_STATUS_REGISTER
mdefine_line|#define ETHERNET0_PORT_STATUS_REGISTER&t;&t;&t;&t;0x2418
DECL|macro|ETHERNET0_SERIAL_PARAMETRS_REGISTER
mdefine_line|#define ETHERNET0_SERIAL_PARAMETRS_REGISTER&t;&t;&t;0x2420
DECL|macro|ETHERNET0_HASH_TABLE_POINTER_REGISTER
mdefine_line|#define ETHERNET0_HASH_TABLE_POINTER_REGISTER&t;&t;&t;0x2428
DECL|macro|ETHERNET0_FLOW_CONTROL_SOURCE_ADDRESS_LOW
mdefine_line|#define ETHERNET0_FLOW_CONTROL_SOURCE_ADDRESS_LOW&t;&t;0x2430
DECL|macro|ETHERNET0_FLOW_CONTROL_SOURCE_ADDRESS_HIGH
mdefine_line|#define ETHERNET0_FLOW_CONTROL_SOURCE_ADDRESS_HIGH&t;&t;0x2438
DECL|macro|ETHERNET0_SDMA_CONFIGURATION_REGISTER
mdefine_line|#define ETHERNET0_SDMA_CONFIGURATION_REGISTER&t;&t;&t;0x2440
DECL|macro|ETHERNET0_SDMA_COMMAND_REGISTER
mdefine_line|#define ETHERNET0_SDMA_COMMAND_REGISTER&t;&t;&t;&t;0x2448
DECL|macro|ETHERNET0_INTERRUPT_CAUSE_REGISTER
mdefine_line|#define ETHERNET0_INTERRUPT_CAUSE_REGISTER&t;&t;&t;0x2450
DECL|macro|ETHERNET0_INTERRUPT_MASK_REGISTER
mdefine_line|#define ETHERNET0_INTERRUPT_MASK_REGISTER&t;&t;&t;0x2458
DECL|macro|ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER0&t;&t;&t;0x2480
DECL|macro|ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER1&t;&t;&t;0x2484
DECL|macro|ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER2
mdefine_line|#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER2&t;&t;&t;0x2488
DECL|macro|ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER3
mdefine_line|#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER3&t;&t;&t;0x248c
DECL|macro|ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER0&t;&t;0x24a0
DECL|macro|ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER1&t;&t;0x24a4
DECL|macro|ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER2
mdefine_line|#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER2&t;&t;0x24a8
DECL|macro|ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER3
mdefine_line|#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER3&t;&t;0x24ac
DECL|macro|ETHERNET0_CURRENT_TX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET0_CURRENT_TX_DESCRIPTOR_POINTER0&t;&t;0x24e0
DECL|macro|ETHERNET0_CURRENT_TX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET0_CURRENT_TX_DESCRIPTOR_POINTER1&t;&t;0x24e4
DECL|macro|ETHERNET0_MIB_COUNTER_BASE
mdefine_line|#define ETHERNET0_MIB_COUNTER_BASE&t;&t;&t;&t;0x2500
multiline_comment|/* Ethernet 1 */
DECL|macro|ETHERNET1_PORT_CONFIGURATION_REGISTER
mdefine_line|#define ETHERNET1_PORT_CONFIGURATION_REGISTER&t;&t;&t;0x2800
DECL|macro|ETHERNET1_PORT_CONFIGURATION_EXTEND_REGISTER
mdefine_line|#define ETHERNET1_PORT_CONFIGURATION_EXTEND_REGISTER&t;&t;0x2808
DECL|macro|ETHERNET1_PORT_COMMAND_REGISTER
mdefine_line|#define ETHERNET1_PORT_COMMAND_REGISTER&t;&t;&t;&t;0x2810
DECL|macro|ETHERNET1_PORT_STATUS_REGISTER
mdefine_line|#define ETHERNET1_PORT_STATUS_REGISTER&t;&t;&t;&t;0x2818
DECL|macro|ETHERNET1_SERIAL_PARAMETRS_REGISTER
mdefine_line|#define ETHERNET1_SERIAL_PARAMETRS_REGISTER&t;&t;&t;0x2820
DECL|macro|ETHERNET1_HASH_TABLE_POINTER_REGISTER
mdefine_line|#define ETHERNET1_HASH_TABLE_POINTER_REGISTER&t;&t;&t;0x2828
DECL|macro|ETHERNET1_FLOW_CONTROL_SOURCE_ADDRESS_LOW
mdefine_line|#define ETHERNET1_FLOW_CONTROL_SOURCE_ADDRESS_LOW&t;&t;0x2830
DECL|macro|ETHERNET1_FLOW_CONTROL_SOURCE_ADDRESS_HIGH
mdefine_line|#define ETHERNET1_FLOW_CONTROL_SOURCE_ADDRESS_HIGH&t;&t;0x2838
DECL|macro|ETHERNET1_SDMA_CONFIGURATION_REGISTER
mdefine_line|#define ETHERNET1_SDMA_CONFIGURATION_REGISTER&t;&t;&t;0x2840
DECL|macro|ETHERNET1_SDMA_COMMAND_REGISTER
mdefine_line|#define ETHERNET1_SDMA_COMMAND_REGISTER&t;&t;&t;&t;0x2848
DECL|macro|ETHERNET1_INTERRUPT_CAUSE_REGISTER
mdefine_line|#define ETHERNET1_INTERRUPT_CAUSE_REGISTER&t;&t;&t;0x2850
DECL|macro|ETHERNET1_INTERRUPT_MASK_REGISTER
mdefine_line|#define ETHERNET1_INTERRUPT_MASK_REGISTER&t;&t;&t;0x2858
DECL|macro|ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER0&t;&t;&t;0x2880
DECL|macro|ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER1&t;&t;&t;0x2884
DECL|macro|ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER2
mdefine_line|#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER2&t;&t;&t;0x2888
DECL|macro|ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER3
mdefine_line|#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER3&t;&t;&t;0x288c
DECL|macro|ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER0&t;&t;0x28a0
DECL|macro|ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER1&t;&t;0x28a4
DECL|macro|ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER2
mdefine_line|#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER2&t;&t;0x28a8
DECL|macro|ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER3
mdefine_line|#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER3&t;&t;0x28ac
DECL|macro|ETHERNET1_CURRENT_TX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET1_CURRENT_TX_DESCRIPTOR_POINTER0&t;&t;0x28e0
DECL|macro|ETHERNET1_CURRENT_TX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET1_CURRENT_TX_DESCRIPTOR_POINTER1&t;&t;0x28e4
DECL|macro|ETHERNET1_MIB_COUNTER_BASE
mdefine_line|#define ETHERNET1_MIB_COUNTER_BASE&t;&t;&t;&t;0x2900
multiline_comment|/* Ethernet 2 */
DECL|macro|ETHERNET2_PORT_CONFIGURATION_REGISTER
mdefine_line|#define ETHERNET2_PORT_CONFIGURATION_REGISTER&t;&t;&t;0x2c00
DECL|macro|ETHERNET2_PORT_CONFIGURATION_EXTEND_REGISTER
mdefine_line|#define ETHERNET2_PORT_CONFIGURATION_EXTEND_REGISTER&t;&t;0x2c08
DECL|macro|ETHERNET2_PORT_COMMAND_REGISTER
mdefine_line|#define ETHERNET2_PORT_COMMAND_REGISTER&t;&t;&t;&t;0x2c10
DECL|macro|ETHERNET2_PORT_STATUS_REGISTER
mdefine_line|#define ETHERNET2_PORT_STATUS_REGISTER&t;&t;&t;&t;0x2c18
DECL|macro|ETHERNET2_SERIAL_PARAMETRS_REGISTER
mdefine_line|#define ETHERNET2_SERIAL_PARAMETRS_REGISTER&t;&t;&t;0x2c20
DECL|macro|ETHERNET2_HASH_TABLE_POINTER_REGISTER
mdefine_line|#define ETHERNET2_HASH_TABLE_POINTER_REGISTER&t;&t;&t;0x2c28
DECL|macro|ETHERNET2_FLOW_CONTROL_SOURCE_ADDRESS_LOW
mdefine_line|#define ETHERNET2_FLOW_CONTROL_SOURCE_ADDRESS_LOW&t;&t;0x2c30
DECL|macro|ETHERNET2_FLOW_CONTROL_SOURCE_ADDRESS_HIGH
mdefine_line|#define ETHERNET2_FLOW_CONTROL_SOURCE_ADDRESS_HIGH&t;&t;0x2c38
DECL|macro|ETHERNET2_SDMA_CONFIGURATION_REGISTER
mdefine_line|#define ETHERNET2_SDMA_CONFIGURATION_REGISTER&t;&t;&t;0x2c40
DECL|macro|ETHERNET2_SDMA_COMMAND_REGISTER
mdefine_line|#define ETHERNET2_SDMA_COMMAND_REGISTER&t;&t;&t;&t;0x2c48
DECL|macro|ETHERNET2_INTERRUPT_CAUSE_REGISTER
mdefine_line|#define ETHERNET2_INTERRUPT_CAUSE_REGISTER&t;&t;&t;0x2c50
DECL|macro|ETHERNET2_INTERRUPT_MASK_REGISTER
mdefine_line|#define ETHERNET2_INTERRUPT_MASK_REGISTER&t;&t;&t;0x2c58
DECL|macro|ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER0&t;&t;&t;0x2c80
DECL|macro|ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER1&t;&t;&t;0x2c84
DECL|macro|ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER2
mdefine_line|#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER2&t;&t;&t;0x2c88
DECL|macro|ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER3
mdefine_line|#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER3&t;&t;&t;0x2c8c
DECL|macro|ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER0&t;&t;0x2ca0
DECL|macro|ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER1&t;&t;0x2ca4
DECL|macro|ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER2
mdefine_line|#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER2&t;&t;0x2ca8
DECL|macro|ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER3
mdefine_line|#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER3&t;&t;0x2cac
DECL|macro|ETHERNET2_CURRENT_TX_DESCRIPTOR_POINTER0
mdefine_line|#define ETHERNET2_CURRENT_TX_DESCRIPTOR_POINTER0&t;&t;0x2ce0
DECL|macro|ETHERNET2_CURRENT_TX_DESCRIPTOR_POINTER1
mdefine_line|#define ETHERNET2_CURRENT_TX_DESCRIPTOR_POINTER1&t;&t;0x2ce4
DECL|macro|ETHERNET2_MIB_COUNTER_BASE
mdefine_line|#define ETHERNET2_MIB_COUNTER_BASE&t;&t;&t;&t;0x2d00
multiline_comment|/*&n; * SDMA Registers&n; */
DECL|macro|SDMA_GROUP_CONFIGURATION_REGISTER
mdefine_line|#define SDMA_GROUP_CONFIGURATION_REGISTER&t;&t;&t;0xb1f0
DECL|macro|CHANNEL0_CONFIGURATION_REGISTER
mdefine_line|#define CHANNEL0_CONFIGURATION_REGISTER&t;&t;&t;&t;0x4000
DECL|macro|CHANNEL0_COMMAND_REGISTER
mdefine_line|#define CHANNEL0_COMMAND_REGISTER&t;&t;&t;&t;0x4008
DECL|macro|CHANNEL0_RX_CMD_STATUS
mdefine_line|#define CHANNEL0_RX_CMD_STATUS&t;&t;&t;&t;&t;0x4800
DECL|macro|CHANNEL0_RX_PACKET_AND_BUFFER_SIZES
mdefine_line|#define CHANNEL0_RX_PACKET_AND_BUFFER_SIZES&t;&t;&t;0x4804
DECL|macro|CHANNEL0_RX_BUFFER_POINTER
mdefine_line|#define CHANNEL0_RX_BUFFER_POINTER&t;&t;&t;&t;0x4808
DECL|macro|CHANNEL0_RX_NEXT_POINTER
mdefine_line|#define CHANNEL0_RX_NEXT_POINTER&t;&t;&t;&t;0x480c
DECL|macro|CHANNEL0_CURRENT_RX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL0_CURRENT_RX_DESCRIPTOR_POINTER&t;&t;&t;0x4810
DECL|macro|CHANNEL0_TX_CMD_STATUS
mdefine_line|#define CHANNEL0_TX_CMD_STATUS&t;&t;&t;&t;&t;0x4C00
DECL|macro|CHANNEL0_TX_PACKET_SIZE
mdefine_line|#define CHANNEL0_TX_PACKET_SIZE&t;&t;&t;&t;&t;0x4C04
DECL|macro|CHANNEL0_TX_BUFFER_POINTER
mdefine_line|#define CHANNEL0_TX_BUFFER_POINTER&t;&t;&t;&t;0x4C08
DECL|macro|CHANNEL0_TX_NEXT_POINTER
mdefine_line|#define CHANNEL0_TX_NEXT_POINTER&t;&t;&t;&t;0x4C0c
DECL|macro|CHANNEL0_CURRENT_TX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL0_CURRENT_TX_DESCRIPTOR_POINTER&t;&t;&t;0x4c10
DECL|macro|CHANNEL0_FIRST_TX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL0_FIRST_TX_DESCRIPTOR_POINTER&t;&t;&t;0x4c14
DECL|macro|CHANNEL1_CONFIGURATION_REGISTER
mdefine_line|#define CHANNEL1_CONFIGURATION_REGISTER&t;&t;&t;&t;0x6000
DECL|macro|CHANNEL1_COMMAND_REGISTER
mdefine_line|#define CHANNEL1_COMMAND_REGISTER&t;&t;&t;&t;0x6008
DECL|macro|CHANNEL1_RX_CMD_STATUS
mdefine_line|#define CHANNEL1_RX_CMD_STATUS&t;&t;&t;&t;&t;0x6800
DECL|macro|CHANNEL1_RX_PACKET_AND_BUFFER_SIZES
mdefine_line|#define CHANNEL1_RX_PACKET_AND_BUFFER_SIZES&t;&t;&t;0x6804
DECL|macro|CHANNEL1_RX_BUFFER_POINTER
mdefine_line|#define CHANNEL1_RX_BUFFER_POINTER&t;&t;&t;&t;0x6808
DECL|macro|CHANNEL1_RX_NEXT_POINTER
mdefine_line|#define CHANNEL1_RX_NEXT_POINTER&t;&t;&t;&t;0x680c
DECL|macro|CHANNEL1_CURRENT_RX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL1_CURRENT_RX_DESCRIPTOR_POINTER&t;&t;&t;0x6810
DECL|macro|CHANNEL1_TX_CMD_STATUS
mdefine_line|#define CHANNEL1_TX_CMD_STATUS&t;&t;&t;&t;&t;0x6C00
DECL|macro|CHANNEL1_TX_PACKET_SIZE
mdefine_line|#define CHANNEL1_TX_PACKET_SIZE&t;&t;&t;&t;&t;0x6C04
DECL|macro|CHANNEL1_TX_BUFFER_POINTER
mdefine_line|#define CHANNEL1_TX_BUFFER_POINTER&t;&t;&t;&t;0x6C08
DECL|macro|CHANNEL1_TX_NEXT_POINTER
mdefine_line|#define CHANNEL1_TX_NEXT_POINTER&t;&t;&t;&t;0x6C0c
DECL|macro|CHANNEL1_CURRENT_RX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL1_CURRENT_RX_DESCRIPTOR_POINTER&t;&t;&t;0x6810
DECL|macro|CHANNEL1_CURRENT_TX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL1_CURRENT_TX_DESCRIPTOR_POINTER&t;&t;&t;0x6c10
DECL|macro|CHANNEL1_FIRST_TX_DESCRIPTOR_POINTER
mdefine_line|#define CHANNEL1_FIRST_TX_DESCRIPTOR_POINTER&t;&t;&t;0x6c14
multiline_comment|/* SDMA Interrupt */
DECL|macro|SDMA_CAUSE
mdefine_line|#define SDMA_CAUSE&t;&t;&t;&t;&t;&t;0xb820
DECL|macro|SDMA_MASK
mdefine_line|#define SDMA_MASK&t;&t;&t;&t;&t;&t;0xb8a0
multiline_comment|/*&n; * Baude Rate Generators Registers&n; */
multiline_comment|/* BRG 0 */
DECL|macro|BRG0_CONFIGURATION_REGISTER
mdefine_line|#define BRG0_CONFIGURATION_REGISTER&t;&t;&t;&t;0xb200
DECL|macro|BRG0_BAUDE_TUNING_REGISTER
mdefine_line|#define BRG0_BAUDE_TUNING_REGISTER&t;&t;&t;&t;0xb204
multiline_comment|/* BRG 1 */
DECL|macro|BRG1_CONFIGURATION_REGISTER
mdefine_line|#define BRG1_CONFIGURATION_REGISTER&t;&t;&t;&t;0xb208
DECL|macro|BRG1_BAUDE_TUNING_REGISTER
mdefine_line|#define BRG1_BAUDE_TUNING_REGISTER&t;&t;&t;&t;0xb20c
multiline_comment|/* BRG 2 */
DECL|macro|BRG2_CONFIGURATION_REGISTER
mdefine_line|#define BRG2_CONFIGURATION_REGISTER&t;&t;&t;&t;0xb210
DECL|macro|BRG2_BAUDE_TUNING_REGISTER
mdefine_line|#define BRG2_BAUDE_TUNING_REGISTER&t;&t;&t;&t;0xb214
multiline_comment|/* BRG Interrupts */
DECL|macro|BRG_CAUSE_REGISTER
mdefine_line|#define BRG_CAUSE_REGISTER&t;&t;&t;&t;&t;0xb834
DECL|macro|BRG_MASK_REGISTER
mdefine_line|#define BRG_MASK_REGISTER&t;&t;&t;&t;&t;0xb8b4
multiline_comment|/* MISC */
DECL|macro|MAIN_ROUTING_REGISTER
mdefine_line|#define MAIN_ROUTING_REGISTER&t;&t;&t;&t;&t;0xb400
DECL|macro|RECEIVE_CLOCK_ROUTING_REGISTER
mdefine_line|#define RECEIVE_CLOCK_ROUTING_REGISTER&t;&t;&t;&t;0xb404
DECL|macro|TRANSMIT_CLOCK_ROUTING_REGISTER
mdefine_line|#define TRANSMIT_CLOCK_ROUTING_REGISTER&t;&t;&t;&t;0xb408
DECL|macro|COMM_UNIT_ARBITER_CONFIGURATION_REGISTER
mdefine_line|#define COMM_UNIT_ARBITER_CONFIGURATION_REGISTER&t;&t;0xb40c
DECL|macro|WATCHDOG_CONFIGURATION_REGISTER
mdefine_line|#define WATCHDOG_CONFIGURATION_REGISTER&t;&t;&t;&t;0xb410
DECL|macro|WATCHDOG_VALUE_REGISTER
mdefine_line|#define WATCHDOG_VALUE_REGISTER&t;&t;&t;&t;&t;0xb414
multiline_comment|/*&n; * Flex TDM Registers&n; */
multiline_comment|/* FTDM Port */
DECL|macro|FLEXTDM_TRANSMIT_READ_POINTER
mdefine_line|#define FLEXTDM_TRANSMIT_READ_POINTER&t;&t;&t;&t;0xa800
DECL|macro|FLEXTDM_RECEIVE_READ_POINTER
mdefine_line|#define FLEXTDM_RECEIVE_READ_POINTER&t;&t;&t;&t;0xa804
DECL|macro|FLEXTDM_CONFIGURATION_REGISTER
mdefine_line|#define FLEXTDM_CONFIGURATION_REGISTER&t;&t;&t;&t;0xa808
DECL|macro|FLEXTDM_AUX_CHANNELA_TX_REGISTER
mdefine_line|#define FLEXTDM_AUX_CHANNELA_TX_REGISTER&t;&t;&t;0xa80c
DECL|macro|FLEXTDM_AUX_CHANNELA_RX_REGISTER
mdefine_line|#define FLEXTDM_AUX_CHANNELA_RX_REGISTER&t;&t;&t;0xa810
DECL|macro|FLEXTDM_AUX_CHANNELB_TX_REGISTER
mdefine_line|#define FLEXTDM_AUX_CHANNELB_TX_REGISTER&t;&t;&t;0xa814
DECL|macro|FLEXTDM_AUX_CHANNELB_RX_REGISTER
mdefine_line|#define FLEXTDM_AUX_CHANNELB_RX_REGISTER&t;&t;&t;0xa818
multiline_comment|/* FTDM Interrupts */
DECL|macro|FTDM_CAUSE_REGISTER
mdefine_line|#define FTDM_CAUSE_REGISTER&t;&t;&t;&t;&t;0xb830
DECL|macro|FTDM_MASK_REGISTER
mdefine_line|#define FTDM_MASK_REGISTER&t;&t;&t;&t;&t;0xb8b0
multiline_comment|/*&n; * GPP Interface Registers&n; */
DECL|macro|GPP_IO_CONTROL
mdefine_line|#define GPP_IO_CONTROL&t;&t;&t;&t;&t;&t;0xf100
DECL|macro|GPP_LEVEL_CONTROL
mdefine_line|#define GPP_LEVEL_CONTROL&t;&t;&t;&t;&t;0xf110
DECL|macro|GPP_VALUE
mdefine_line|#define GPP_VALUE&t;&t;&t;&t;&t;&t;0xf104
DECL|macro|GPP_INTERRUPT_CAUSE
mdefine_line|#define GPP_INTERRUPT_CAUSE&t;&t;&t;&t;&t;0xf108
DECL|macro|GPP_INTERRUPT_MASK
mdefine_line|#define GPP_INTERRUPT_MASK&t;&t;&t;&t;&t;0xf10c
DECL|macro|MPP_CONTROL0
mdefine_line|#define MPP_CONTROL0&t;&t;&t;&t;&t;&t;0xf000
DECL|macro|MPP_CONTROL1
mdefine_line|#define MPP_CONTROL1&t;&t;&t;&t;&t;&t;0xf004
DECL|macro|MPP_CONTROL2
mdefine_line|#define MPP_CONTROL2&t;&t;&t;&t;&t;&t;0xf008
DECL|macro|MPP_CONTROL3
mdefine_line|#define MPP_CONTROL3&t;&t;&t;&t;&t;&t;0xf00c
DECL|macro|DEBUG_PORT_MULTIPLEX
mdefine_line|#define DEBUG_PORT_MULTIPLEX&t;&t;&t;&t;&t;0xf014
DECL|macro|SERIAL_PORT_MULTIPLEX
mdefine_line|#define SERIAL_PORT_MULTIPLEX&t;&t;&t;&t;&t;0xf010
multiline_comment|/*&n; * I2C Registers&n; */
DECL|macro|I2C_SLAVE_ADDRESS
mdefine_line|#define I2C_SLAVE_ADDRESS&t;&t;&t;&t;&t;0xc000
DECL|macro|I2C_EXTENDED_SLAVE_ADDRESS
mdefine_line|#define I2C_EXTENDED_SLAVE_ADDRESS&t;&t;&t;&t;0xc040
DECL|macro|I2C_DATA
mdefine_line|#define I2C_DATA&t;&t;&t;&t;&t;&t;0xc004
DECL|macro|I2C_CONTROL
mdefine_line|#define I2C_CONTROL&t;&t;&t;&t;&t;&t;0xc008
DECL|macro|I2C_STATUS_BAUDE_RATE
mdefine_line|#define I2C_STATUS_BAUDE_RATE&t;&t;&t;&t;&t;0xc00C
DECL|macro|I2C_SOFT_RESET
mdefine_line|#define I2C_SOFT_RESET&t;&t;&t;&t;&t;&t;0xc01c
multiline_comment|/*&n; * MPSC Registers&n; */
multiline_comment|/*&n; * MPSC0&n; */
DECL|macro|MPSC0_MAIN_CONFIGURATION_LOW
mdefine_line|#define MPSC0_MAIN_CONFIGURATION_LOW&t;&t;&t;&t;0x8000
DECL|macro|MPSC0_MAIN_CONFIGURATION_HIGH
mdefine_line|#define MPSC0_MAIN_CONFIGURATION_HIGH&t;&t;&t;&t;0x8004
DECL|macro|MPSC0_PROTOCOL_CONFIGURATION
mdefine_line|#define MPSC0_PROTOCOL_CONFIGURATION&t;&t;&t;&t;0x8008
DECL|macro|CHANNEL0_REGISTER1
mdefine_line|#define CHANNEL0_REGISTER1&t;&t;&t;&t;&t;0x800c
DECL|macro|CHANNEL0_REGISTER2
mdefine_line|#define CHANNEL0_REGISTER2&t;&t;&t;&t;&t;0x8010
DECL|macro|CHANNEL0_REGISTER3
mdefine_line|#define CHANNEL0_REGISTER3&t;&t;&t;&t;&t;0x8014
DECL|macro|CHANNEL0_REGISTER4
mdefine_line|#define CHANNEL0_REGISTER4&t;&t;&t;&t;&t;0x8018
DECL|macro|CHANNEL0_REGISTER5
mdefine_line|#define CHANNEL0_REGISTER5&t;&t;&t;&t;&t;0x801c
DECL|macro|CHANNEL0_REGISTER6
mdefine_line|#define CHANNEL0_REGISTER6&t;&t;&t;&t;&t;0x8020
DECL|macro|CHANNEL0_REGISTER7
mdefine_line|#define CHANNEL0_REGISTER7&t;&t;&t;&t;&t;0x8024
DECL|macro|CHANNEL0_REGISTER8
mdefine_line|#define CHANNEL0_REGISTER8&t;&t;&t;&t;&t;0x8028
DECL|macro|CHANNEL0_REGISTER9
mdefine_line|#define CHANNEL0_REGISTER9&t;&t;&t;&t;&t;0x802c
DECL|macro|CHANNEL0_REGISTER10
mdefine_line|#define CHANNEL0_REGISTER10&t;&t;&t;&t;&t;0x8030
DECL|macro|CHANNEL0_REGISTER11
mdefine_line|#define CHANNEL0_REGISTER11&t;&t;&t;&t;&t;0x8034
multiline_comment|/*&n; * MPSC1&n; */
DECL|macro|MPSC1_MAIN_CONFIGURATION_LOW
mdefine_line|#define MPSC1_MAIN_CONFIGURATION_LOW&t;&t;&t;&t;0x9000
DECL|macro|MPSC1_MAIN_CONFIGURATION_HIGH
mdefine_line|#define MPSC1_MAIN_CONFIGURATION_HIGH&t;&t;&t;&t;0x9004
DECL|macro|MPSC1_PROTOCOL_CONFIGURATION
mdefine_line|#define MPSC1_PROTOCOL_CONFIGURATION&t;&t;&t;&t;0x9008
DECL|macro|CHANNEL1_REGISTER1
mdefine_line|#define CHANNEL1_REGISTER1&t;&t;&t;&t;&t;0x900c
DECL|macro|CHANNEL1_REGISTER2
mdefine_line|#define CHANNEL1_REGISTER2&t;&t;&t;&t;&t;0x9010
DECL|macro|CHANNEL1_REGISTER3
mdefine_line|#define CHANNEL1_REGISTER3&t;&t;&t;&t;&t;0x9014
DECL|macro|CHANNEL1_REGISTER4
mdefine_line|#define CHANNEL1_REGISTER4&t;&t;&t;&t;&t;0x9018
DECL|macro|CHANNEL1_REGISTER5
mdefine_line|#define CHANNEL1_REGISTER5&t;&t;&t;&t;&t;0x901c
DECL|macro|CHANNEL1_REGISTER6
mdefine_line|#define CHANNEL1_REGISTER6&t;&t;&t;&t;&t;0x9020
DECL|macro|CHANNEL1_REGISTER7
mdefine_line|#define CHANNEL1_REGISTER7&t;&t;&t;&t;&t;0x9024
DECL|macro|CHANNEL1_REGISTER8
mdefine_line|#define CHANNEL1_REGISTER8&t;&t;&t;&t;&t;0x9028
DECL|macro|CHANNEL1_REGISTER9
mdefine_line|#define CHANNEL1_REGISTER9&t;&t;&t;&t;&t;0x902c
DECL|macro|CHANNEL1_REGISTER10
mdefine_line|#define CHANNEL1_REGISTER10&t;&t;&t;&t;&t;0x9030
DECL|macro|CHANNEL1_REGISTER11
mdefine_line|#define CHANNEL1_REGISTER11&t;&t;&t;&t;&t;0x9034
multiline_comment|/*&n; * MPSCs Interupts&n; */
DECL|macro|MPSC0_CAUSE
mdefine_line|#define MPSC0_CAUSE&t;&t;&t;&t;&t;&t;0xb804
DECL|macro|MPSC0_MASK
mdefine_line|#define MPSC0_MASK&t;&t;&t;&t;&t;&t;0xb884
DECL|macro|MPSC1_CAUSE
mdefine_line|#define MPSC1_CAUSE&t;&t;&t;&t;&t;&t;0xb80c
DECL|macro|MPSC1_MASK
mdefine_line|#define MPSC1_MASK&t;&t;&t;&t;&t;&t;0xb88c
r_extern
r_int
r_int
id|gt64240_base
suffix:semicolon
DECL|macro|GT64240_BASE
mdefine_line|#define GT64240_BASE&t;   (gt64240_base)
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the&n; * bytes when running bigendian.&n; */
DECL|macro|__GT_READ
mdefine_line|#define __GT_READ(ofs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile u32 *)(GT64240_BASE+(ofs)))
DECL|macro|__GT_WRITE
mdefine_line|#define __GT_WRITE(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile u32 *)(GT64240_BASE+(ofs)) = (data); } while (0)
DECL|macro|GT_READ
mdefine_line|#define GT_READ(ofs)&t;&t;le32_to_cpu(__GT_READ(ofs))
DECL|macro|GT_WRITE
mdefine_line|#define GT_WRITE(ofs, data)&t;__GT_WRITE(ofs, cpu_to_le32(data))
DECL|macro|GT_READ_16
mdefine_line|#define GT_READ_16(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;        le16_to_cpu(*(volatile u16 *)(GT64240_BASE+(ofs)))
DECL|macro|GT_WRITE_16
mdefine_line|#define GT_WRITE_16(ofs, data)  &bslash;&n;        *(volatile u16 *)(GT64240_BASE+(ofs)) = cpu_to_le16(data)
DECL|macro|GT_READ_8
mdefine_line|#define GT_READ_8(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;        *(data) = *(volatile u8 *)(GT64240_BASE+(ofs))
DECL|macro|GT_WRITE_8
mdefine_line|#define GT_WRITE_8(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;        *(volatile u8 *)(GT64240_BASE+(ofs)) = data
r_extern
r_struct
id|pci_ops
id|gt_bus0_pci_ops
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|gt_bus1_pci_ops
suffix:semicolon
macro_line|#endif&t;/* __ASM_MIPS_MV64240_H */
eof
