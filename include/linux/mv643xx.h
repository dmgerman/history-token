multiline_comment|/*&n; * mv64340.h - MV-64340 Internal registers definition file.&n; *&n; * Copyright 2002 Momentum Computer, Inc.&n; * &t;Author: Matthew Dharm &lt;mdharm@momenco.com&gt;&n; * Copyright 2002 GALILEO TECHNOLOGY, LTD. &n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASM_MV64340_H
DECL|macro|__ASM_MV64340_H
mdefine_line|#define __ASM_MV64340_H
macro_line|#ifdef __MIPS__
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/marvell.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/****************************************/
multiline_comment|/* Processor Address Space              */
multiline_comment|/****************************************/
multiline_comment|/* DDR SDRAM BAR and size registers */
DECL|macro|MV64340_CS_0_BASE_ADDR
mdefine_line|#define MV64340_CS_0_BASE_ADDR                                      0x008
DECL|macro|MV64340_CS_0_SIZE
mdefine_line|#define MV64340_CS_0_SIZE                                           0x010
DECL|macro|MV64340_CS_1_BASE_ADDR
mdefine_line|#define MV64340_CS_1_BASE_ADDR                                      0x208
DECL|macro|MV64340_CS_1_SIZE
mdefine_line|#define MV64340_CS_1_SIZE                                           0x210
DECL|macro|MV64340_CS_2_BASE_ADDR
mdefine_line|#define MV64340_CS_2_BASE_ADDR                                      0x018
DECL|macro|MV64340_CS_2_SIZE
mdefine_line|#define MV64340_CS_2_SIZE                                           0x020
DECL|macro|MV64340_CS_3_BASE_ADDR
mdefine_line|#define MV64340_CS_3_BASE_ADDR                                      0x218
DECL|macro|MV64340_CS_3_SIZE
mdefine_line|#define MV64340_CS_3_SIZE                                           0x220
multiline_comment|/* Devices BAR and size registers */
DECL|macro|MV64340_DEV_CS0_BASE_ADDR
mdefine_line|#define MV64340_DEV_CS0_BASE_ADDR                                   0x028
DECL|macro|MV64340_DEV_CS0_SIZE
mdefine_line|#define MV64340_DEV_CS0_SIZE                                        0x030
DECL|macro|MV64340_DEV_CS1_BASE_ADDR
mdefine_line|#define MV64340_DEV_CS1_BASE_ADDR                                   0x228
DECL|macro|MV64340_DEV_CS1_SIZE
mdefine_line|#define MV64340_DEV_CS1_SIZE                                        0x230
DECL|macro|MV64340_DEV_CS2_BASE_ADDR
mdefine_line|#define MV64340_DEV_CS2_BASE_ADDR                                   0x248
DECL|macro|MV64340_DEV_CS2_SIZE
mdefine_line|#define MV64340_DEV_CS2_SIZE                                        0x250
DECL|macro|MV64340_DEV_CS3_BASE_ADDR
mdefine_line|#define MV64340_DEV_CS3_BASE_ADDR                                   0x038
DECL|macro|MV64340_DEV_CS3_SIZE
mdefine_line|#define MV64340_DEV_CS3_SIZE                                        0x040
DECL|macro|MV64340_BOOTCS_BASE_ADDR
mdefine_line|#define MV64340_BOOTCS_BASE_ADDR                                    0x238
DECL|macro|MV64340_BOOTCS_SIZE
mdefine_line|#define MV64340_BOOTCS_SIZE                                         0x240
multiline_comment|/* PCI 0 BAR and size registers */
DECL|macro|MV64340_PCI_0_IO_BASE_ADDR
mdefine_line|#define MV64340_PCI_0_IO_BASE_ADDR                                  0x048
DECL|macro|MV64340_PCI_0_IO_SIZE
mdefine_line|#define MV64340_PCI_0_IO_SIZE                                       0x050
DECL|macro|MV64340_PCI_0_MEMORY0_BASE_ADDR
mdefine_line|#define MV64340_PCI_0_MEMORY0_BASE_ADDR                             0x058
DECL|macro|MV64340_PCI_0_MEMORY0_SIZE
mdefine_line|#define MV64340_PCI_0_MEMORY0_SIZE                                  0x060
DECL|macro|MV64340_PCI_0_MEMORY1_BASE_ADDR
mdefine_line|#define MV64340_PCI_0_MEMORY1_BASE_ADDR                             0x080
DECL|macro|MV64340_PCI_0_MEMORY1_SIZE
mdefine_line|#define MV64340_PCI_0_MEMORY1_SIZE                                  0x088
DECL|macro|MV64340_PCI_0_MEMORY2_BASE_ADDR
mdefine_line|#define MV64340_PCI_0_MEMORY2_BASE_ADDR                             0x258
DECL|macro|MV64340_PCI_0_MEMORY2_SIZE
mdefine_line|#define MV64340_PCI_0_MEMORY2_SIZE                                  0x260
DECL|macro|MV64340_PCI_0_MEMORY3_BASE_ADDR
mdefine_line|#define MV64340_PCI_0_MEMORY3_BASE_ADDR                             0x280
DECL|macro|MV64340_PCI_0_MEMORY3_SIZE
mdefine_line|#define MV64340_PCI_0_MEMORY3_SIZE                                  0x288
multiline_comment|/* PCI 1 BAR and size registers */
DECL|macro|MV64340_PCI_1_IO_BASE_ADDR
mdefine_line|#define MV64340_PCI_1_IO_BASE_ADDR                                  0x090
DECL|macro|MV64340_PCI_1_IO_SIZE
mdefine_line|#define MV64340_PCI_1_IO_SIZE                                       0x098
DECL|macro|MV64340_PCI_1_MEMORY0_BASE_ADDR
mdefine_line|#define MV64340_PCI_1_MEMORY0_BASE_ADDR                             0x0a0
DECL|macro|MV64340_PCI_1_MEMORY0_SIZE
mdefine_line|#define MV64340_PCI_1_MEMORY0_SIZE                                  0x0a8
DECL|macro|MV64340_PCI_1_MEMORY1_BASE_ADDR
mdefine_line|#define MV64340_PCI_1_MEMORY1_BASE_ADDR                             0x0b0
DECL|macro|MV64340_PCI_1_MEMORY1_SIZE
mdefine_line|#define MV64340_PCI_1_MEMORY1_SIZE                                  0x0b8
DECL|macro|MV64340_PCI_1_MEMORY2_BASE_ADDR
mdefine_line|#define MV64340_PCI_1_MEMORY2_BASE_ADDR                             0x2a0
DECL|macro|MV64340_PCI_1_MEMORY2_SIZE
mdefine_line|#define MV64340_PCI_1_MEMORY2_SIZE                                  0x2a8
DECL|macro|MV64340_PCI_1_MEMORY3_BASE_ADDR
mdefine_line|#define MV64340_PCI_1_MEMORY3_BASE_ADDR                             0x2b0
DECL|macro|MV64340_PCI_1_MEMORY3_SIZE
mdefine_line|#define MV64340_PCI_1_MEMORY3_SIZE                                  0x2b8
multiline_comment|/* SRAM base address */
DECL|macro|MV64340_INTEGRATED_SRAM_BASE_ADDR
mdefine_line|#define MV64340_INTEGRATED_SRAM_BASE_ADDR                           0x268
multiline_comment|/* internal registers space base address */
DECL|macro|MV64340_INTERNAL_SPACE_BASE_ADDR
mdefine_line|#define MV64340_INTERNAL_SPACE_BASE_ADDR                            0x068
multiline_comment|/* Enables the CS , DEV_CS , PCI 0 and PCI 1 &n;   windows above */
DECL|macro|MV64340_BASE_ADDR_ENABLE
mdefine_line|#define MV64340_BASE_ADDR_ENABLE                                    0x278
multiline_comment|/****************************************/
multiline_comment|/* PCI remap registers                  */
multiline_comment|/****************************************/
multiline_comment|/* PCI 0 */
DECL|macro|MV64340_PCI_0_IO_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_IO_ADDR_REMAP                                 0x0f0
DECL|macro|MV64340_PCI_0_MEMORY0_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY0_LOW_ADDR_REMAP                        0x0f8
DECL|macro|MV64340_PCI_0_MEMORY0_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY0_HIGH_ADDR_REMAP                       0x320
DECL|macro|MV64340_PCI_0_MEMORY1_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY1_LOW_ADDR_REMAP                        0x100
DECL|macro|MV64340_PCI_0_MEMORY1_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY1_HIGH_ADDR_REMAP                       0x328
DECL|macro|MV64340_PCI_0_MEMORY2_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY2_LOW_ADDR_REMAP                        0x2f8
DECL|macro|MV64340_PCI_0_MEMORY2_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY2_HIGH_ADDR_REMAP                       0x330
DECL|macro|MV64340_PCI_0_MEMORY3_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY3_LOW_ADDR_REMAP                        0x300
DECL|macro|MV64340_PCI_0_MEMORY3_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_MEMORY3_HIGH_ADDR_REMAP                       0x338
multiline_comment|/* PCI 1 */
DECL|macro|MV64340_PCI_1_IO_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_IO_ADDR_REMAP                                 0x108
DECL|macro|MV64340_PCI_1_MEMORY0_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY0_LOW_ADDR_REMAP                        0x110
DECL|macro|MV64340_PCI_1_MEMORY0_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY0_HIGH_ADDR_REMAP                       0x340
DECL|macro|MV64340_PCI_1_MEMORY1_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY1_LOW_ADDR_REMAP                        0x118
DECL|macro|MV64340_PCI_1_MEMORY1_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY1_HIGH_ADDR_REMAP                       0x348
DECL|macro|MV64340_PCI_1_MEMORY2_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY2_LOW_ADDR_REMAP                        0x310
DECL|macro|MV64340_PCI_1_MEMORY2_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY2_HIGH_ADDR_REMAP                       0x350
DECL|macro|MV64340_PCI_1_MEMORY3_LOW_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY3_LOW_ADDR_REMAP                        0x318
DECL|macro|MV64340_PCI_1_MEMORY3_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_MEMORY3_HIGH_ADDR_REMAP                       0x358
DECL|macro|MV64340_CPU_PCI_0_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_CPU_PCI_0_HEADERS_RETARGET_CONTROL                  0x3b0
DECL|macro|MV64340_CPU_PCI_0_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_CPU_PCI_0_HEADERS_RETARGET_BASE                     0x3b8
DECL|macro|MV64340_CPU_PCI_1_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_CPU_PCI_1_HEADERS_RETARGET_CONTROL                  0x3c0
DECL|macro|MV64340_CPU_PCI_1_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_CPU_PCI_1_HEADERS_RETARGET_BASE                     0x3c8
DECL|macro|MV64340_CPU_GE_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_CPU_GE_HEADERS_RETARGET_CONTROL                     0x3d0
DECL|macro|MV64340_CPU_GE_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_CPU_GE_HEADERS_RETARGET_BASE                        0x3d8
DECL|macro|MV64340_CPU_IDMA_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_CPU_IDMA_HEADERS_RETARGET_CONTROL                   0x3e0
DECL|macro|MV64340_CPU_IDMA_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_CPU_IDMA_HEADERS_RETARGET_BASE                      0x3e8
multiline_comment|/****************************************/
multiline_comment|/*         CPU Control Registers        */
multiline_comment|/****************************************/
DECL|macro|MV64340_CPU_CONFIG
mdefine_line|#define MV64340_CPU_CONFIG                                          0x000
DECL|macro|MV64340_CPU_MODE
mdefine_line|#define MV64340_CPU_MODE                                            0x120
DECL|macro|MV64340_CPU_MASTER_CONTROL
mdefine_line|#define MV64340_CPU_MASTER_CONTROL                                  0x160
DECL|macro|MV64340_CPU_CROSS_BAR_CONTROL_LOW
mdefine_line|#define MV64340_CPU_CROSS_BAR_CONTROL_LOW                           0x150
DECL|macro|MV64340_CPU_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define MV64340_CPU_CROSS_BAR_CONTROL_HIGH                          0x158
DECL|macro|MV64340_CPU_CROSS_BAR_TIMEOUT
mdefine_line|#define MV64340_CPU_CROSS_BAR_TIMEOUT                               0x168
multiline_comment|/****************************************/
multiline_comment|/* SMP RegisterS                        */
multiline_comment|/****************************************/
DECL|macro|MV64340_SMP_WHO_AM_I
mdefine_line|#define MV64340_SMP_WHO_AM_I                                        0x200
DECL|macro|MV64340_SMP_CPU0_DOORBELL
mdefine_line|#define MV64340_SMP_CPU0_DOORBELL                                   0x214
DECL|macro|MV64340_SMP_CPU0_DOORBELL_CLEAR
mdefine_line|#define MV64340_SMP_CPU0_DOORBELL_CLEAR                             0x21C
DECL|macro|MV64340_SMP_CPU1_DOORBELL
mdefine_line|#define MV64340_SMP_CPU1_DOORBELL                                   0x224
DECL|macro|MV64340_SMP_CPU1_DOORBELL_CLEAR
mdefine_line|#define MV64340_SMP_CPU1_DOORBELL_CLEAR                             0x22C
DECL|macro|MV64340_SMP_CPU0_DOORBELL_MASK
mdefine_line|#define MV64340_SMP_CPU0_DOORBELL_MASK                              0x234
DECL|macro|MV64340_SMP_CPU1_DOORBELL_MASK
mdefine_line|#define MV64340_SMP_CPU1_DOORBELL_MASK                              0x23C
DECL|macro|MV64340_SMP_SEMAPHOR0
mdefine_line|#define MV64340_SMP_SEMAPHOR0                                       0x244
DECL|macro|MV64340_SMP_SEMAPHOR1
mdefine_line|#define MV64340_SMP_SEMAPHOR1                                       0x24c
DECL|macro|MV64340_SMP_SEMAPHOR2
mdefine_line|#define MV64340_SMP_SEMAPHOR2                                       0x254
DECL|macro|MV64340_SMP_SEMAPHOR3
mdefine_line|#define MV64340_SMP_SEMAPHOR3                                       0x25c
DECL|macro|MV64340_SMP_SEMAPHOR4
mdefine_line|#define MV64340_SMP_SEMAPHOR4                                       0x264
DECL|macro|MV64340_SMP_SEMAPHOR5
mdefine_line|#define MV64340_SMP_SEMAPHOR5                                       0x26c
DECL|macro|MV64340_SMP_SEMAPHOR6
mdefine_line|#define MV64340_SMP_SEMAPHOR6                                       0x274
DECL|macro|MV64340_SMP_SEMAPHOR7
mdefine_line|#define MV64340_SMP_SEMAPHOR7                                       0x27c
multiline_comment|/****************************************/
multiline_comment|/*  CPU Sync Barrier Register           */
multiline_comment|/****************************************/
DECL|macro|MV64340_CPU_0_SYNC_BARRIER_TRIGGER
mdefine_line|#define MV64340_CPU_0_SYNC_BARRIER_TRIGGER                          0x0c0
DECL|macro|MV64340_CPU_0_SYNC_BARRIER_VIRTUAL
mdefine_line|#define MV64340_CPU_0_SYNC_BARRIER_VIRTUAL                          0x0c8
DECL|macro|MV64340_CPU_1_SYNC_BARRIER_TRIGGER
mdefine_line|#define MV64340_CPU_1_SYNC_BARRIER_TRIGGER                          0x0d0
DECL|macro|MV64340_CPU_1_SYNC_BARRIER_VIRTUAL
mdefine_line|#define MV64340_CPU_1_SYNC_BARRIER_VIRTUAL                          0x0d8
multiline_comment|/****************************************/
multiline_comment|/* CPU Access Protect                   */
multiline_comment|/****************************************/
DECL|macro|MV64340_CPU_PROTECT_WINDOW_0_BASE_ADDR
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_0_BASE_ADDR                      0x180
DECL|macro|MV64340_CPU_PROTECT_WINDOW_0_SIZE
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_0_SIZE                           0x188
DECL|macro|MV64340_CPU_PROTECT_WINDOW_1_BASE_ADDR
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_1_BASE_ADDR                      0x190
DECL|macro|MV64340_CPU_PROTECT_WINDOW_1_SIZE
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_1_SIZE                           0x198
DECL|macro|MV64340_CPU_PROTECT_WINDOW_2_BASE_ADDR
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_2_BASE_ADDR                      0x1a0
DECL|macro|MV64340_CPU_PROTECT_WINDOW_2_SIZE
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_2_SIZE                           0x1a8
DECL|macro|MV64340_CPU_PROTECT_WINDOW_3_BASE_ADDR
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_3_BASE_ADDR                      0x1b0
DECL|macro|MV64340_CPU_PROTECT_WINDOW_3_SIZE
mdefine_line|#define MV64340_CPU_PROTECT_WINDOW_3_SIZE                           0x1b8
multiline_comment|/****************************************/
multiline_comment|/*          CPU Error Report            */
multiline_comment|/****************************************/
DECL|macro|MV64340_CPU_ERROR_ADDR_LOW
mdefine_line|#define MV64340_CPU_ERROR_ADDR_LOW                                  0x070
DECL|macro|MV64340_CPU_ERROR_ADDR_HIGH
mdefine_line|#define MV64340_CPU_ERROR_ADDR_HIGH                                 0x078
DECL|macro|MV64340_CPU_ERROR_DATA_LOW
mdefine_line|#define MV64340_CPU_ERROR_DATA_LOW                                  0x128
DECL|macro|MV64340_CPU_ERROR_DATA_HIGH
mdefine_line|#define MV64340_CPU_ERROR_DATA_HIGH                                 0x130
DECL|macro|MV64340_CPU_ERROR_PARITY
mdefine_line|#define MV64340_CPU_ERROR_PARITY                                    0x138
DECL|macro|MV64340_CPU_ERROR_CAUSE
mdefine_line|#define MV64340_CPU_ERROR_CAUSE                                     0x140
DECL|macro|MV64340_CPU_ERROR_MASK
mdefine_line|#define MV64340_CPU_ERROR_MASK                                      0x148
multiline_comment|/****************************************/
multiline_comment|/*      CPU Interface Debug Registers &t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_PUNIT_SLAVE_DEBUG_LOW
mdefine_line|#define MV64340_PUNIT_SLAVE_DEBUG_LOW                               0x360
DECL|macro|MV64340_PUNIT_SLAVE_DEBUG_HIGH
mdefine_line|#define MV64340_PUNIT_SLAVE_DEBUG_HIGH                              0x368
DECL|macro|MV64340_PUNIT_MASTER_DEBUG_LOW
mdefine_line|#define MV64340_PUNIT_MASTER_DEBUG_LOW                              0x370
DECL|macro|MV64340_PUNIT_MASTER_DEBUG_HIGH
mdefine_line|#define MV64340_PUNIT_MASTER_DEBUG_HIGH                             0x378
DECL|macro|MV64340_PUNIT_MMASK
mdefine_line|#define MV64340_PUNIT_MMASK                                         0x3e4
multiline_comment|/****************************************/
multiline_comment|/*  Integrated SRAM Registers           */
multiline_comment|/****************************************/
DECL|macro|MV64340_SRAM_CONFIG
mdefine_line|#define MV64340_SRAM_CONFIG                                         0x380
DECL|macro|MV64340_SRAM_TEST_MODE
mdefine_line|#define MV64340_SRAM_TEST_MODE                                      0X3F4
DECL|macro|MV64340_SRAM_ERROR_CAUSE
mdefine_line|#define MV64340_SRAM_ERROR_CAUSE                                    0x388
DECL|macro|MV64340_SRAM_ERROR_ADDR
mdefine_line|#define MV64340_SRAM_ERROR_ADDR                                     0x390
DECL|macro|MV64340_SRAM_ERROR_ADDR_HIGH
mdefine_line|#define MV64340_SRAM_ERROR_ADDR_HIGH                                0X3F8
DECL|macro|MV64340_SRAM_ERROR_DATA_LOW
mdefine_line|#define MV64340_SRAM_ERROR_DATA_LOW                                 0x398
DECL|macro|MV64340_SRAM_ERROR_DATA_HIGH
mdefine_line|#define MV64340_SRAM_ERROR_DATA_HIGH                                0x3a0
DECL|macro|MV64340_SRAM_ERROR_DATA_PARITY
mdefine_line|#define MV64340_SRAM_ERROR_DATA_PARITY                              0x3a8
multiline_comment|/****************************************/
multiline_comment|/* SDRAM Configuration                  */
multiline_comment|/****************************************/
DECL|macro|MV64340_SDRAM_CONFIG
mdefine_line|#define MV64340_SDRAM_CONFIG                                        0x1400
DECL|macro|MV64340_D_UNIT_CONTROL_LOW
mdefine_line|#define MV64340_D_UNIT_CONTROL_LOW                                  0x1404
DECL|macro|MV64340_D_UNIT_CONTROL_HIGH
mdefine_line|#define MV64340_D_UNIT_CONTROL_HIGH                                 0x1424
DECL|macro|MV64340_SDRAM_TIMING_CONTROL_LOW
mdefine_line|#define MV64340_SDRAM_TIMING_CONTROL_LOW                            0x1408
DECL|macro|MV64340_SDRAM_TIMING_CONTROL_HIGH
mdefine_line|#define MV64340_SDRAM_TIMING_CONTROL_HIGH                           0x140c
DECL|macro|MV64340_SDRAM_ADDR_CONTROL
mdefine_line|#define MV64340_SDRAM_ADDR_CONTROL                                  0x1410
DECL|macro|MV64340_SDRAM_OPEN_PAGES_CONTROL
mdefine_line|#define MV64340_SDRAM_OPEN_PAGES_CONTROL                            0x1414
DECL|macro|MV64340_SDRAM_OPERATION
mdefine_line|#define MV64340_SDRAM_OPERATION                                     0x1418
DECL|macro|MV64340_SDRAM_MODE
mdefine_line|#define MV64340_SDRAM_MODE                                          0x141c
DECL|macro|MV64340_EXTENDED_DRAM_MODE
mdefine_line|#define MV64340_EXTENDED_DRAM_MODE                                  0x1420
DECL|macro|MV64340_SDRAM_CROSS_BAR_CONTROL_LOW
mdefine_line|#define MV64340_SDRAM_CROSS_BAR_CONTROL_LOW                         0x1430
DECL|macro|MV64340_SDRAM_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define MV64340_SDRAM_CROSS_BAR_CONTROL_HIGH                        0x1434
DECL|macro|MV64340_SDRAM_CROSS_BAR_TIMEOUT
mdefine_line|#define MV64340_SDRAM_CROSS_BAR_TIMEOUT                             0x1438
DECL|macro|MV64340_SDRAM_ADDR_CTRL_PADS_CALIBRATION
mdefine_line|#define MV64340_SDRAM_ADDR_CTRL_PADS_CALIBRATION                    0x14c0
DECL|macro|MV64340_SDRAM_DATA_PADS_CALIBRATION
mdefine_line|#define MV64340_SDRAM_DATA_PADS_CALIBRATION                         0x14c4
multiline_comment|/****************************************/
multiline_comment|/* SDRAM Error Report                   */
multiline_comment|/****************************************/
DECL|macro|MV64340_SDRAM_ERROR_DATA_LOW
mdefine_line|#define MV64340_SDRAM_ERROR_DATA_LOW                                0x1444
DECL|macro|MV64340_SDRAM_ERROR_DATA_HIGH
mdefine_line|#define MV64340_SDRAM_ERROR_DATA_HIGH                               0x1440
DECL|macro|MV64340_SDRAM_ERROR_ADDR
mdefine_line|#define MV64340_SDRAM_ERROR_ADDR                                    0x1450
DECL|macro|MV64340_SDRAM_RECEIVED_ECC
mdefine_line|#define MV64340_SDRAM_RECEIVED_ECC                                  0x1448
DECL|macro|MV64340_SDRAM_CALCULATED_ECC
mdefine_line|#define MV64340_SDRAM_CALCULATED_ECC                                0x144c
DECL|macro|MV64340_SDRAM_ECC_CONTROL
mdefine_line|#define MV64340_SDRAM_ECC_CONTROL                                   0x1454
DECL|macro|MV64340_SDRAM_ECC_ERROR_COUNTER
mdefine_line|#define MV64340_SDRAM_ECC_ERROR_COUNTER                             0x1458
multiline_comment|/******************************************/
multiline_comment|/*  Controlled Delay Line (CDL) Registers */
multiline_comment|/******************************************/
DECL|macro|MV64340_DFCDL_CONFIG0
mdefine_line|#define MV64340_DFCDL_CONFIG0                                       0x1480
DECL|macro|MV64340_DFCDL_CONFIG1
mdefine_line|#define MV64340_DFCDL_CONFIG1                                       0x1484
DECL|macro|MV64340_DLL_WRITE
mdefine_line|#define MV64340_DLL_WRITE                                           0x1488
DECL|macro|MV64340_DLL_READ
mdefine_line|#define MV64340_DLL_READ                                            0x148c
DECL|macro|MV64340_SRAM_ADDR
mdefine_line|#define MV64340_SRAM_ADDR                                           0x1490
DECL|macro|MV64340_SRAM_DATA0
mdefine_line|#define MV64340_SRAM_DATA0                                          0x1494
DECL|macro|MV64340_SRAM_DATA1
mdefine_line|#define MV64340_SRAM_DATA1                                          0x1498
DECL|macro|MV64340_SRAM_DATA2
mdefine_line|#define MV64340_SRAM_DATA2                                          0x149c
DECL|macro|MV64340_DFCL_PROBE
mdefine_line|#define MV64340_DFCL_PROBE                                          0x14a0
multiline_comment|/******************************************/
multiline_comment|/*   Debug Registers                      */
multiline_comment|/******************************************/
DECL|macro|MV64340_DUNIT_DEBUG_LOW
mdefine_line|#define MV64340_DUNIT_DEBUG_LOW                                     0x1460
DECL|macro|MV64340_DUNIT_DEBUG_HIGH
mdefine_line|#define MV64340_DUNIT_DEBUG_HIGH                                    0x1464
DECL|macro|MV64340_DUNIT_MMASK
mdefine_line|#define MV64340_DUNIT_MMASK                                         0X1b40
multiline_comment|/****************************************/
multiline_comment|/* Device Parameters&t;&t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_DEVICE_BANK0_PARAMETERS
mdefine_line|#define MV64340_DEVICE_BANK0_PARAMETERS&t;&t;&t;&t;    0x45c
DECL|macro|MV64340_DEVICE_BANK1_PARAMETERS
mdefine_line|#define MV64340_DEVICE_BANK1_PARAMETERS&t;&t;&t;&t;    0x460
DECL|macro|MV64340_DEVICE_BANK2_PARAMETERS
mdefine_line|#define MV64340_DEVICE_BANK2_PARAMETERS&t;&t;&t;&t;    0x464
DECL|macro|MV64340_DEVICE_BANK3_PARAMETERS
mdefine_line|#define MV64340_DEVICE_BANK3_PARAMETERS&t;&t;&t;&t;    0x468
DECL|macro|MV64340_DEVICE_BOOT_BANK_PARAMETERS
mdefine_line|#define MV64340_DEVICE_BOOT_BANK_PARAMETERS&t;&t;&t;    0x46c
DECL|macro|MV64340_DEVICE_INTERFACE_CONTROL
mdefine_line|#define MV64340_DEVICE_INTERFACE_CONTROL                            0x4c0
DECL|macro|MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_LOW
mdefine_line|#define MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_LOW              0x4c8
DECL|macro|MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_HIGH             0x4cc
DECL|macro|MV64340_DEVICE_INTERFACE_CROSS_BAR_TIMEOUT
mdefine_line|#define MV64340_DEVICE_INTERFACE_CROSS_BAR_TIMEOUT                  0x4c4
multiline_comment|/****************************************/
multiline_comment|/* Device interrupt registers&t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_DEVICE_INTERRUPT_CAUSE
mdefine_line|#define MV64340_DEVICE_INTERRUPT_CAUSE&t;&t;&t;&t;    0x4d0
DECL|macro|MV64340_DEVICE_INTERRUPT_MASK
mdefine_line|#define MV64340_DEVICE_INTERRUPT_MASK&t;&t;&t;&t;    0x4d4
DECL|macro|MV64340_DEVICE_ERROR_ADDR
mdefine_line|#define MV64340_DEVICE_ERROR_ADDR&t;&t;&t;&t;    0x4d8
DECL|macro|MV64340_DEVICE_ERROR_DATA
mdefine_line|#define MV64340_DEVICE_ERROR_DATA   &t;&t;&t;&t;    0x4dc
DECL|macro|MV64340_DEVICE_ERROR_PARITY
mdefine_line|#define MV64340_DEVICE_ERROR_PARITY     &t;&t;&t;    0x4e0
multiline_comment|/****************************************/
multiline_comment|/* Device debug registers   &t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_DEVICE_DEBUG_LOW
mdefine_line|#define MV64340_DEVICE_DEBUG_LOW     &t;&t;&t;&t;    0x4e4
DECL|macro|MV64340_DEVICE_DEBUG_HIGH
mdefine_line|#define MV64340_DEVICE_DEBUG_HIGH     &t;&t;&t;&t;    0x4e8
DECL|macro|MV64340_RUNIT_MMASK
mdefine_line|#define MV64340_RUNIT_MMASK                                         0x4f0
multiline_comment|/****************************************/
multiline_comment|/* PCI Slave Address Decoding registers */
multiline_comment|/****************************************/
DECL|macro|MV64340_PCI_0_CS_0_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_CS_0_BANK_SIZE                                0xc08
DECL|macro|MV64340_PCI_1_CS_0_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_CS_0_BANK_SIZE                                0xc88
DECL|macro|MV64340_PCI_0_CS_1_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_CS_1_BANK_SIZE                                0xd08
DECL|macro|MV64340_PCI_1_CS_1_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_CS_1_BANK_SIZE                                0xd88
DECL|macro|MV64340_PCI_0_CS_2_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_CS_2_BANK_SIZE                                0xc0c
DECL|macro|MV64340_PCI_1_CS_2_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_CS_2_BANK_SIZE                                0xc8c
DECL|macro|MV64340_PCI_0_CS_3_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_CS_3_BANK_SIZE                                0xd0c
DECL|macro|MV64340_PCI_1_CS_3_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_CS_3_BANK_SIZE                                0xd8c
DECL|macro|MV64340_PCI_0_DEVCS_0_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_DEVCS_0_BANK_SIZE                             0xc10
DECL|macro|MV64340_PCI_1_DEVCS_0_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_DEVCS_0_BANK_SIZE                             0xc90
DECL|macro|MV64340_PCI_0_DEVCS_1_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_DEVCS_1_BANK_SIZE                             0xd10
DECL|macro|MV64340_PCI_1_DEVCS_1_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_DEVCS_1_BANK_SIZE                             0xd90
DECL|macro|MV64340_PCI_0_DEVCS_2_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_DEVCS_2_BANK_SIZE                             0xd18
DECL|macro|MV64340_PCI_1_DEVCS_2_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_DEVCS_2_BANK_SIZE                             0xd98
DECL|macro|MV64340_PCI_0_DEVCS_3_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_DEVCS_3_BANK_SIZE                             0xc14
DECL|macro|MV64340_PCI_1_DEVCS_3_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_DEVCS_3_BANK_SIZE                             0xc94
DECL|macro|MV64340_PCI_0_DEVCS_BOOT_BANK_SIZE
mdefine_line|#define MV64340_PCI_0_DEVCS_BOOT_BANK_SIZE                          0xd14
DECL|macro|MV64340_PCI_1_DEVCS_BOOT_BANK_SIZE
mdefine_line|#define MV64340_PCI_1_DEVCS_BOOT_BANK_SIZE                          0xd94
DECL|macro|MV64340_PCI_0_P2P_MEM0_BAR_SIZE
mdefine_line|#define MV64340_PCI_0_P2P_MEM0_BAR_SIZE                             0xd1c
DECL|macro|MV64340_PCI_1_P2P_MEM0_BAR_SIZE
mdefine_line|#define MV64340_PCI_1_P2P_MEM0_BAR_SIZE                             0xd9c
DECL|macro|MV64340_PCI_0_P2P_MEM1_BAR_SIZE
mdefine_line|#define MV64340_PCI_0_P2P_MEM1_BAR_SIZE                             0xd20
DECL|macro|MV64340_PCI_1_P2P_MEM1_BAR_SIZE
mdefine_line|#define MV64340_PCI_1_P2P_MEM1_BAR_SIZE                             0xda0
DECL|macro|MV64340_PCI_0_P2P_I_O_BAR_SIZE
mdefine_line|#define MV64340_PCI_0_P2P_I_O_BAR_SIZE                              0xd24
DECL|macro|MV64340_PCI_1_P2P_I_O_BAR_SIZE
mdefine_line|#define MV64340_PCI_1_P2P_I_O_BAR_SIZE                              0xda4
DECL|macro|MV64340_PCI_0_CPU_BAR_SIZE
mdefine_line|#define MV64340_PCI_0_CPU_BAR_SIZE                                  0xd28
DECL|macro|MV64340_PCI_1_CPU_BAR_SIZE
mdefine_line|#define MV64340_PCI_1_CPU_BAR_SIZE                                  0xda8
DECL|macro|MV64340_PCI_0_INTERNAL_SRAM_BAR_SIZE
mdefine_line|#define MV64340_PCI_0_INTERNAL_SRAM_BAR_SIZE                        0xe00
DECL|macro|MV64340_PCI_1_INTERNAL_SRAM_BAR_SIZE
mdefine_line|#define MV64340_PCI_1_INTERNAL_SRAM_BAR_SIZE                        0xe80
DECL|macro|MV64340_PCI_0_EXPANSION_ROM_BAR_SIZE
mdefine_line|#define MV64340_PCI_0_EXPANSION_ROM_BAR_SIZE                        0xd2c
DECL|macro|MV64340_PCI_1_EXPANSION_ROM_BAR_SIZE
mdefine_line|#define MV64340_PCI_1_EXPANSION_ROM_BAR_SIZE                        0xd9c
DECL|macro|MV64340_PCI_0_BASE_ADDR_REG_ENABLE
mdefine_line|#define MV64340_PCI_0_BASE_ADDR_REG_ENABLE                          0xc3c
DECL|macro|MV64340_PCI_1_BASE_ADDR_REG_ENABLE
mdefine_line|#define MV64340_PCI_1_BASE_ADDR_REG_ENABLE                          0xcbc
DECL|macro|MV64340_PCI_0_CS_0_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_0_BASE_ADDR_REMAP&t;&t;&t;    0xc48
DECL|macro|MV64340_PCI_1_CS_0_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_0_BASE_ADDR_REMAP&t;&t;&t;    0xcc8
DECL|macro|MV64340_PCI_0_CS_1_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_1_BASE_ADDR_REMAP&t;&t;&t;    0xd48
DECL|macro|MV64340_PCI_1_CS_1_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_1_BASE_ADDR_REMAP&t;&t;&t;    0xdc8
DECL|macro|MV64340_PCI_0_CS_2_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_2_BASE_ADDR_REMAP&t;&t;&t;    0xc4c
DECL|macro|MV64340_PCI_1_CS_2_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_2_BASE_ADDR_REMAP&t;&t;&t;    0xccc
DECL|macro|MV64340_PCI_0_CS_3_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_3_BASE_ADDR_REMAP&t;&t;&t;    0xd4c
DECL|macro|MV64340_PCI_1_CS_3_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_3_BASE_ADDR_REMAP&t;&t;&t;    0xdcc
DECL|macro|MV64340_PCI_0_CS_0_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_0_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF04
DECL|macro|MV64340_PCI_1_CS_0_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_0_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF84
DECL|macro|MV64340_PCI_0_CS_1_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_1_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF08
DECL|macro|MV64340_PCI_1_CS_1_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_1_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF88
DECL|macro|MV64340_PCI_0_CS_2_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_2_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF0C
DECL|macro|MV64340_PCI_1_CS_2_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_2_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF8C
DECL|macro|MV64340_PCI_0_CS_3_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_CS_3_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF10
DECL|macro|MV64340_PCI_1_CS_3_BASE_HIGH_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_CS_3_BASE_HIGH_ADDR_REMAP&t;&t;&t;    0xF90
DECL|macro|MV64340_PCI_0_DEVCS_0_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_DEVCS_0_BASE_ADDR_REMAP&t;&t;&t;    0xc50
DECL|macro|MV64340_PCI_1_DEVCS_0_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_DEVCS_0_BASE_ADDR_REMAP&t;&t;&t;    0xcd0
DECL|macro|MV64340_PCI_0_DEVCS_1_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_DEVCS_1_BASE_ADDR_REMAP&t;&t;&t;    0xd50
DECL|macro|MV64340_PCI_1_DEVCS_1_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_DEVCS_1_BASE_ADDR_REMAP&t;&t;&t;    0xdd0
DECL|macro|MV64340_PCI_0_DEVCS_2_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_DEVCS_2_BASE_ADDR_REMAP&t;&t;&t;    0xd58
DECL|macro|MV64340_PCI_1_DEVCS_2_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_DEVCS_2_BASE_ADDR_REMAP&t;&t;&t;    0xdd8
DECL|macro|MV64340_PCI_0_DEVCS_3_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_DEVCS_3_BASE_ADDR_REMAP           &t;    0xc54
DECL|macro|MV64340_PCI_1_DEVCS_3_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_DEVCS_3_BASE_ADDR_REMAP           &t;    0xcd4
DECL|macro|MV64340_PCI_0_DEVCS_BOOTCS_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_DEVCS_BOOTCS_BASE_ADDR_REMAP      &t;    0xd54
DECL|macro|MV64340_PCI_1_DEVCS_BOOTCS_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_DEVCS_BOOTCS_BASE_ADDR_REMAP      &t;    0xdd4
DECL|macro|MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_LOW
mdefine_line|#define MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_LOW                  0xd5c
DECL|macro|MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_LOW
mdefine_line|#define MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_LOW                  0xddc
DECL|macro|MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_HIGH
mdefine_line|#define MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_HIGH                 0xd60
DECL|macro|MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_HIGH
mdefine_line|#define MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_HIGH                 0xde0
DECL|macro|MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_LOW
mdefine_line|#define MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_LOW                  0xd64
DECL|macro|MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_LOW
mdefine_line|#define MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_LOW                  0xde4
DECL|macro|MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_HIGH
mdefine_line|#define MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_HIGH                 0xd68
DECL|macro|MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_HIGH
mdefine_line|#define MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_HIGH                 0xde8
DECL|macro|MV64340_PCI_0_P2P_I_O_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_P2P_I_O_BASE_ADDR_REMAP                       0xd6c
DECL|macro|MV64340_PCI_1_P2P_I_O_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_P2P_I_O_BASE_ADDR_REMAP                       0xdec 
DECL|macro|MV64340_PCI_0_CPU_BASE_ADDR_REMAP_LOW
mdefine_line|#define MV64340_PCI_0_CPU_BASE_ADDR_REMAP_LOW                       0xd70
DECL|macro|MV64340_PCI_1_CPU_BASE_ADDR_REMAP_LOW
mdefine_line|#define MV64340_PCI_1_CPU_BASE_ADDR_REMAP_LOW                       0xdf0
DECL|macro|MV64340_PCI_0_CPU_BASE_ADDR_REMAP_HIGH
mdefine_line|#define MV64340_PCI_0_CPU_BASE_ADDR_REMAP_HIGH                      0xd74
DECL|macro|MV64340_PCI_1_CPU_BASE_ADDR_REMAP_HIGH
mdefine_line|#define MV64340_PCI_1_CPU_BASE_ADDR_REMAP_HIGH                      0xdf4
DECL|macro|MV64340_PCI_0_INTEGRATED_SRAM_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_INTEGRATED_SRAM_BASE_ADDR_REMAP               0xf00
DECL|macro|MV64340_PCI_1_INTEGRATED_SRAM_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_INTEGRATED_SRAM_BASE_ADDR_REMAP               0xf80
DECL|macro|MV64340_PCI_0_EXPANSION_ROM_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_0_EXPANSION_ROM_BASE_ADDR_REMAP                 0xf38
DECL|macro|MV64340_PCI_1_EXPANSION_ROM_BASE_ADDR_REMAP
mdefine_line|#define MV64340_PCI_1_EXPANSION_ROM_BASE_ADDR_REMAP                 0xfb8
DECL|macro|MV64340_PCI_0_ADDR_DECODE_CONTROL
mdefine_line|#define MV64340_PCI_0_ADDR_DECODE_CONTROL                           0xd3c
DECL|macro|MV64340_PCI_1_ADDR_DECODE_CONTROL
mdefine_line|#define MV64340_PCI_1_ADDR_DECODE_CONTROL                           0xdbc
DECL|macro|MV64340_PCI_0_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_PCI_0_HEADERS_RETARGET_CONTROL                      0xF40
DECL|macro|MV64340_PCI_1_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_PCI_1_HEADERS_RETARGET_CONTROL                      0xFc0
DECL|macro|MV64340_PCI_0_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_PCI_0_HEADERS_RETARGET_BASE                         0xF44
DECL|macro|MV64340_PCI_1_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_PCI_1_HEADERS_RETARGET_BASE                         0xFc4
DECL|macro|MV64340_PCI_0_HEADERS_RETARGET_HIGH
mdefine_line|#define MV64340_PCI_0_HEADERS_RETARGET_HIGH                         0xF48
DECL|macro|MV64340_PCI_1_HEADERS_RETARGET_HIGH
mdefine_line|#define MV64340_PCI_1_HEADERS_RETARGET_HIGH                         0xFc8
multiline_comment|/***********************************/
multiline_comment|/*   PCI Control Register Map      */
multiline_comment|/***********************************/
DECL|macro|MV64340_PCI_0_DLL_STATUS_AND_COMMAND
mdefine_line|#define MV64340_PCI_0_DLL_STATUS_AND_COMMAND                        0x1d20
DECL|macro|MV64340_PCI_1_DLL_STATUS_AND_COMMAND
mdefine_line|#define MV64340_PCI_1_DLL_STATUS_AND_COMMAND                        0x1da0
DECL|macro|MV64340_PCI_0_MPP_PADS_DRIVE_CONTROL
mdefine_line|#define MV64340_PCI_0_MPP_PADS_DRIVE_CONTROL                        0x1d1C
DECL|macro|MV64340_PCI_1_MPP_PADS_DRIVE_CONTROL
mdefine_line|#define MV64340_PCI_1_MPP_PADS_DRIVE_CONTROL                        0x1d9C
DECL|macro|MV64340_PCI_0_COMMAND
mdefine_line|#define MV64340_PCI_0_COMMAND&t;&t;&t;         &t;    0xc00
DECL|macro|MV64340_PCI_1_COMMAND
mdefine_line|#define MV64340_PCI_1_COMMAND&t;&t;&t;&t;&t;    0xc80
DECL|macro|MV64340_PCI_0_MODE
mdefine_line|#define MV64340_PCI_0_MODE                                          0xd00
DECL|macro|MV64340_PCI_1_MODE
mdefine_line|#define MV64340_PCI_1_MODE                                          0xd80
DECL|macro|MV64340_PCI_0_RETRY
mdefine_line|#define MV64340_PCI_0_RETRY&t;        &t; &t;&t;    0xc04
DECL|macro|MV64340_PCI_1_RETRY
mdefine_line|#define MV64340_PCI_1_RETRY&t;&t;&t;&t;            0xc84
DECL|macro|MV64340_PCI_0_READ_BUFFER_DISCARD_TIMER
mdefine_line|#define MV64340_PCI_0_READ_BUFFER_DISCARD_TIMER                     0xd04
DECL|macro|MV64340_PCI_1_READ_BUFFER_DISCARD_TIMER
mdefine_line|#define MV64340_PCI_1_READ_BUFFER_DISCARD_TIMER                     0xd84
DECL|macro|MV64340_PCI_0_MSI_TRIGGER_TIMER
mdefine_line|#define MV64340_PCI_0_MSI_TRIGGER_TIMER                             0xc38
DECL|macro|MV64340_PCI_1_MSI_TRIGGER_TIMER
mdefine_line|#define MV64340_PCI_1_MSI_TRIGGER_TIMER                             0xcb8
DECL|macro|MV64340_PCI_0_ARBITER_CONTROL
mdefine_line|#define MV64340_PCI_0_ARBITER_CONTROL                               0x1d00
DECL|macro|MV64340_PCI_1_ARBITER_CONTROL
mdefine_line|#define MV64340_PCI_1_ARBITER_CONTROL                               0x1d80
DECL|macro|MV64340_PCI_0_CROSS_BAR_CONTROL_LOW
mdefine_line|#define MV64340_PCI_0_CROSS_BAR_CONTROL_LOW                         0x1d08
DECL|macro|MV64340_PCI_1_CROSS_BAR_CONTROL_LOW
mdefine_line|#define MV64340_PCI_1_CROSS_BAR_CONTROL_LOW                         0x1d88
DECL|macro|MV64340_PCI_0_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define MV64340_PCI_0_CROSS_BAR_CONTROL_HIGH                        0x1d0c
DECL|macro|MV64340_PCI_1_CROSS_BAR_CONTROL_HIGH
mdefine_line|#define MV64340_PCI_1_CROSS_BAR_CONTROL_HIGH                        0x1d8c
DECL|macro|MV64340_PCI_0_CROSS_BAR_TIMEOUT
mdefine_line|#define MV64340_PCI_0_CROSS_BAR_TIMEOUT                             0x1d04
DECL|macro|MV64340_PCI_1_CROSS_BAR_TIMEOUT
mdefine_line|#define MV64340_PCI_1_CROSS_BAR_TIMEOUT                             0x1d84
DECL|macro|MV64340_PCI_0_SYNC_BARRIER_TRIGGER_REG
mdefine_line|#define MV64340_PCI_0_SYNC_BARRIER_TRIGGER_REG                      0x1D18
DECL|macro|MV64340_PCI_1_SYNC_BARRIER_TRIGGER_REG
mdefine_line|#define MV64340_PCI_1_SYNC_BARRIER_TRIGGER_REG                      0x1D98
DECL|macro|MV64340_PCI_0_SYNC_BARRIER_VIRTUAL_REG
mdefine_line|#define MV64340_PCI_0_SYNC_BARRIER_VIRTUAL_REG                      0x1d10
DECL|macro|MV64340_PCI_1_SYNC_BARRIER_VIRTUAL_REG
mdefine_line|#define MV64340_PCI_1_SYNC_BARRIER_VIRTUAL_REG                      0x1d90
DECL|macro|MV64340_PCI_0_P2P_CONFIG
mdefine_line|#define MV64340_PCI_0_P2P_CONFIG                                    0x1d14
DECL|macro|MV64340_PCI_1_P2P_CONFIG
mdefine_line|#define MV64340_PCI_1_P2P_CONFIG                                    0x1d94
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_0_LOW
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_0_LOW                     0x1e00
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_0_HIGH
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_0_HIGH                    0x1e04
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_SIZE_0
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_0                         0x1e08
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_1_LOW
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_1_LOW                     0x1e10
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_1_HIGH
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_1_HIGH                    0x1e14
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_SIZE_1
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_1                         0x1e18
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_2_LOW
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_2_LOW                     0x1e20
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_2_HIGH
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_2_HIGH                    0x1e24
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_SIZE_2
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_2                         0x1e28
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_3_LOW
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_3_LOW                     0x1e30
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_3_HIGH
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_3_HIGH                    0x1e34
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_SIZE_3
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_3                         0x1e38
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_4_LOW
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_4_LOW                     0x1e40
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_4_HIGH
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_4_HIGH                    0x1e44
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_SIZE_4
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_4                         0x1e48
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_5_LOW
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_5_LOW                     0x1e50
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_BASE_5_HIGH
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_BASE_5_HIGH                    0x1e54
DECL|macro|MV64340_PCI_0_ACCESS_CONTROL_SIZE_5
mdefine_line|#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_5                         0x1e58
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_0_LOW
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_0_LOW                     0x1e80
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_0_HIGH
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_0_HIGH                    0x1e84
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_SIZE_0
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_0                         0x1e88
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_1_LOW
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_1_LOW                     0x1e90
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_1_HIGH
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_1_HIGH                    0x1e94
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_SIZE_1
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_1                         0x1e98
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_2_LOW
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_2_LOW                     0x1ea0
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_2_HIGH
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_2_HIGH                    0x1ea4
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_SIZE_2
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_2                         0x1ea8
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_3_LOW
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_3_LOW                     0x1eb0
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_3_HIGH
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_3_HIGH                    0x1eb4
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_SIZE_3
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_3                         0x1eb8
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_4_LOW
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_4_LOW                     0x1ec0
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_4_HIGH
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_4_HIGH                    0x1ec4
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_SIZE_4
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_4                         0x1ec8
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_5_LOW
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_5_LOW                     0x1ed0
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_BASE_5_HIGH
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_BASE_5_HIGH                    0x1ed4
DECL|macro|MV64340_PCI_1_ACCESS_CONTROL_SIZE_5
mdefine_line|#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_5                         0x1ed8
multiline_comment|/****************************************/
multiline_comment|/*   PCI Configuration Access Registers */
multiline_comment|/****************************************/
DECL|macro|MV64340_PCI_0_CONFIG_ADDR
mdefine_line|#define MV64340_PCI_0_CONFIG_ADDR &t;&t;&t;&t;    0xcf8
DECL|macro|MV64340_PCI_0_CONFIG_DATA_VIRTUAL_REG
mdefine_line|#define MV64340_PCI_0_CONFIG_DATA_VIRTUAL_REG                       0xcfc
DECL|macro|MV64340_PCI_1_CONFIG_ADDR
mdefine_line|#define MV64340_PCI_1_CONFIG_ADDR &t;&t;&t;&t;    0xc78
DECL|macro|MV64340_PCI_1_CONFIG_DATA_VIRTUAL_REG
mdefine_line|#define MV64340_PCI_1_CONFIG_DATA_VIRTUAL_REG                       0xc7c
DECL|macro|MV64340_PCI_0_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG
mdefine_line|#define MV64340_PCI_0_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG&t;            0xc34
DECL|macro|MV64340_PCI_1_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG
mdefine_line|#define MV64340_PCI_1_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG&t;            0xcb4
multiline_comment|/****************************************/
multiline_comment|/*   PCI Error Report Registers         */
multiline_comment|/****************************************/
DECL|macro|MV64340_PCI_0_SERR_MASK
mdefine_line|#define MV64340_PCI_0_SERR_MASK&t;&t;&t;&t;&t;    0xc28
DECL|macro|MV64340_PCI_1_SERR_MASK
mdefine_line|#define MV64340_PCI_1_SERR_MASK&t;&t;&t;&t;&t;    0xca8
DECL|macro|MV64340_PCI_0_ERROR_ADDR_LOW
mdefine_line|#define MV64340_PCI_0_ERROR_ADDR_LOW                                0x1d40
DECL|macro|MV64340_PCI_1_ERROR_ADDR_LOW
mdefine_line|#define MV64340_PCI_1_ERROR_ADDR_LOW                                0x1dc0
DECL|macro|MV64340_PCI_0_ERROR_ADDR_HIGH
mdefine_line|#define MV64340_PCI_0_ERROR_ADDR_HIGH                               0x1d44
DECL|macro|MV64340_PCI_1_ERROR_ADDR_HIGH
mdefine_line|#define MV64340_PCI_1_ERROR_ADDR_HIGH                               0x1dc4
DECL|macro|MV64340_PCI_0_ERROR_ATTRIBUTE
mdefine_line|#define MV64340_PCI_0_ERROR_ATTRIBUTE                               0x1d48
DECL|macro|MV64340_PCI_1_ERROR_ATTRIBUTE
mdefine_line|#define MV64340_PCI_1_ERROR_ATTRIBUTE                               0x1dc8
DECL|macro|MV64340_PCI_0_ERROR_COMMAND
mdefine_line|#define MV64340_PCI_0_ERROR_COMMAND                                 0x1d50
DECL|macro|MV64340_PCI_1_ERROR_COMMAND
mdefine_line|#define MV64340_PCI_1_ERROR_COMMAND                                 0x1dd0
DECL|macro|MV64340_PCI_0_ERROR_CAUSE
mdefine_line|#define MV64340_PCI_0_ERROR_CAUSE                                   0x1d58
DECL|macro|MV64340_PCI_1_ERROR_CAUSE
mdefine_line|#define MV64340_PCI_1_ERROR_CAUSE                                   0x1dd8
DECL|macro|MV64340_PCI_0_ERROR_MASK
mdefine_line|#define MV64340_PCI_0_ERROR_MASK                                    0x1d5c
DECL|macro|MV64340_PCI_1_ERROR_MASK
mdefine_line|#define MV64340_PCI_1_ERROR_MASK                                    0x1ddc
multiline_comment|/****************************************/
multiline_comment|/*   PCI Debug Registers                */
multiline_comment|/****************************************/
DECL|macro|MV64340_PCI_0_MMASK
mdefine_line|#define MV64340_PCI_0_MMASK                                         0X1D24
DECL|macro|MV64340_PCI_1_MMASK
mdefine_line|#define MV64340_PCI_1_MMASK                                         0X1DA4
multiline_comment|/*********************************************/
multiline_comment|/* PCI Configuration, Function 0, Registers  */
multiline_comment|/*********************************************/
DECL|macro|MV64340_PCI_DEVICE_AND_VENDOR_ID
mdefine_line|#define MV64340_PCI_DEVICE_AND_VENDOR_ID &t;&t;&t;    0x000
DECL|macro|MV64340_PCI_STATUS_AND_COMMAND
mdefine_line|#define MV64340_PCI_STATUS_AND_COMMAND&t;&t;&t;&t;    0x004
DECL|macro|MV64340_PCI_CLASS_CODE_AND_REVISION_ID
mdefine_line|#define MV64340_PCI_CLASS_CODE_AND_REVISION_ID&t;&t;&t;    0x008
DECL|macro|MV64340_PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE
mdefine_line|#define MV64340_PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE &t;    0x00C
DECL|macro|MV64340_PCI_SCS_0_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_SCS_0_BASE_ADDR_LOW   &t;      &t;&t;    0x010
DECL|macro|MV64340_PCI_SCS_0_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_SCS_0_BASE_ADDR_HIGH   &t;&t;            0x014
DECL|macro|MV64340_PCI_SCS_1_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_SCS_1_BASE_ADDR_LOW  &t;     &t;            0x018
DECL|macro|MV64340_PCI_SCS_1_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_SCS_1_BASE_ADDR_HIGH &t;&t;            0x01C
DECL|macro|MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_LOW      &t;    0x020
DECL|macro|MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_HIGH     &t;    0x024
DECL|macro|MV64340_PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID
mdefine_line|#define MV64340_PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID&t;    0x02c
DECL|macro|MV64340_PCI_EXPANSION_ROM_BASE_ADDR_REG
mdefine_line|#define MV64340_PCI_EXPANSION_ROM_BASE_ADDR_REG&t;                    0x030
DECL|macro|MV64340_PCI_CAPABILTY_LIST_POINTER
mdefine_line|#define MV64340_PCI_CAPABILTY_LIST_POINTER                          0x034
DECL|macro|MV64340_PCI_INTERRUPT_PIN_AND_LINE
mdefine_line|#define MV64340_PCI_INTERRUPT_PIN_AND_LINE &t;&t;&t;    0x03C
multiline_comment|/* capability list */
DECL|macro|MV64340_PCI_POWER_MANAGEMENT_CAPABILITY
mdefine_line|#define MV64340_PCI_POWER_MANAGEMENT_CAPABILITY                     0x040
DECL|macro|MV64340_PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL
mdefine_line|#define MV64340_PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL             0x044
DECL|macro|MV64340_PCI_VPD_ADDR
mdefine_line|#define MV64340_PCI_VPD_ADDR                                        0x048
DECL|macro|MV64340_PCI_VPD_DATA
mdefine_line|#define MV64340_PCI_VPD_DATA                                        0x04c
DECL|macro|MV64340_PCI_MSI_MESSAGE_CONTROL
mdefine_line|#define MV64340_PCI_MSI_MESSAGE_CONTROL                             0x050
DECL|macro|MV64340_PCI_MSI_MESSAGE_ADDR
mdefine_line|#define MV64340_PCI_MSI_MESSAGE_ADDR                                0x054
DECL|macro|MV64340_PCI_MSI_MESSAGE_UPPER_ADDR
mdefine_line|#define MV64340_PCI_MSI_MESSAGE_UPPER_ADDR                          0x058
DECL|macro|MV64340_PCI_MSI_MESSAGE_DATA
mdefine_line|#define MV64340_PCI_MSI_MESSAGE_DATA                                0x05c
DECL|macro|MV64340_PCI_X_COMMAND
mdefine_line|#define MV64340_PCI_X_COMMAND                                       0x060
DECL|macro|MV64340_PCI_X_STATUS
mdefine_line|#define MV64340_PCI_X_STATUS                                        0x064
DECL|macro|MV64340_PCI_COMPACT_PCI_HOT_SWAP
mdefine_line|#define MV64340_PCI_COMPACT_PCI_HOT_SWAP                            0x068
multiline_comment|/***********************************************/
multiline_comment|/*   PCI Configuration, Function 1, Registers  */
multiline_comment|/***********************************************/
DECL|macro|MV64340_PCI_SCS_2_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_SCS_2_BASE_ADDR_LOW   &t;&t;&t;    0x110
DECL|macro|MV64340_PCI_SCS_2_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_SCS_2_BASE_ADDR_HIGH&t;&t;&t;    0x114
DECL|macro|MV64340_PCI_SCS_3_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_SCS_3_BASE_ADDR_LOW &t;&t;&t;    0x118
DECL|macro|MV64340_PCI_SCS_3_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_SCS_3_BASE_ADDR_HIGH&t;&t;&t;    0x11c
DECL|macro|MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_LOW          &t;    0x120
DECL|macro|MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_HIGH         &t;    0x124
multiline_comment|/***********************************************/
multiline_comment|/*  PCI Configuration, Function 2, Registers   */
multiline_comment|/***********************************************/
DECL|macro|MV64340_PCI_DEVCS_0_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_DEVCS_0_BASE_ADDR_LOW&t;    &t;&t;    0x210
DECL|macro|MV64340_PCI_DEVCS_0_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_DEVCS_0_BASE_ADDR_HIGH &t;&t;&t;    0x214
DECL|macro|MV64340_PCI_DEVCS_1_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_DEVCS_1_BASE_ADDR_LOW &t;&t;&t;    0x218
DECL|macro|MV64340_PCI_DEVCS_1_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_DEVCS_1_BASE_ADDR_HIGH      &t;&t;    0x21c
DECL|macro|MV64340_PCI_DEVCS_2_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_DEVCS_2_BASE_ADDR_LOW &t;&t;&t;    0x220
DECL|macro|MV64340_PCI_DEVCS_2_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_DEVCS_2_BASE_ADDR_HIGH      &t;&t;    0x224
multiline_comment|/***********************************************/
multiline_comment|/*  PCI Configuration, Function 3, Registers   */
multiline_comment|/***********************************************/
DECL|macro|MV64340_PCI_DEVCS_3_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_DEVCS_3_BASE_ADDR_LOW&t;    &t;&t;    0x310
DECL|macro|MV64340_PCI_DEVCS_3_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_DEVCS_3_BASE_ADDR_HIGH &t;&t;&t;    0x314
DECL|macro|MV64340_PCI_BOOT_CS_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_BOOT_CS_BASE_ADDR_LOW&t;&t;&t;    0x318
DECL|macro|MV64340_PCI_BOOT_CS_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_BOOT_CS_BASE_ADDR_HIGH      &t;&t;    0x31c
DECL|macro|MV64340_PCI_CPU_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_CPU_BASE_ADDR_LOW &t;&t;&t;&t;    0x220
DECL|macro|MV64340_PCI_CPU_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_CPU_BASE_ADDR_HIGH      &t;&t;&t;    0x224
multiline_comment|/***********************************************/
multiline_comment|/*  PCI Configuration, Function 4, Registers   */
multiline_comment|/***********************************************/
DECL|macro|MV64340_PCI_P2P_MEM0_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_P2P_MEM0_BASE_ADDR_LOW  &t;&t;&t;    0x410
DECL|macro|MV64340_PCI_P2P_MEM0_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_P2P_MEM0_BASE_ADDR_HIGH &t;&t;&t;    0x414
DECL|macro|MV64340_PCI_P2P_MEM1_BASE_ADDR_LOW
mdefine_line|#define MV64340_PCI_P2P_MEM1_BASE_ADDR_LOW   &t;&t;&t;    0x418
DECL|macro|MV64340_PCI_P2P_MEM1_BASE_ADDR_HIGH
mdefine_line|#define MV64340_PCI_P2P_MEM1_BASE_ADDR_HIGH &t;&t;&t;    0x41c
DECL|macro|MV64340_PCI_P2P_I_O_BASE_ADDR
mdefine_line|#define MV64340_PCI_P2P_I_O_BASE_ADDR                 &t;            0x420
DECL|macro|MV64340_PCI_INTERNAL_REGS_I_O_MAPPED_BASE_ADDR
mdefine_line|#define MV64340_PCI_INTERNAL_REGS_I_O_MAPPED_BASE_ADDR              0x424
multiline_comment|/****************************************/
multiline_comment|/* Messaging Unit Registers (I20)   &t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_0_SIDE&t;&t;    0x010
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_0_SIDE  &t;&t;    0x014
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_0_SIDE &t;&t;    0x018
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_0_SIDE  &t;&t;    0x01C
DECL|macro|MV64340_I2O_INBOUND_DOORBELL_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_DOORBELL_REG_PCI_0_SIDE  &t;&t;    0x020
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE          0x024
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE&t;    0x028
DECL|macro|MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_0_SIDE &t;&t;    0x02C
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE         0x030
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE          0x034
DECL|macro|MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE       0x040
DECL|macro|MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE      0x044
DECL|macro|MV64340_I2O_QUEUE_CONTROL_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_CONTROL_REG_PCI_0_SIDE &t;&t;    0x050
DECL|macro|MV64340_I2O_QUEUE_BASE_ADDR_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_BASE_ADDR_REG_PCI_0_SIDE &t;&t;    0x054
DECL|macro|MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE        0x060
DECL|macro|MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE        0x064
DECL|macro|MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE        0x068
DECL|macro|MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE        0x06C
DECL|macro|MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE       0x070
DECL|macro|MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE       0x074
DECL|macro|MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE       0x0F8
DECL|macro|MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE       0x0FC
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_1_SIDE&t;&t;    0x090
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_1_SIDE  &t;&t;    0x094
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_1_SIDE &t;&t;    0x098
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_1_SIDE  &t;&t;    0x09C
DECL|macro|MV64340_I2O_INBOUND_DOORBELL_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_DOORBELL_REG_PCI_1_SIDE  &t;&t;    0x0A0
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE          0x0A4
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE&t;    0x0A8
DECL|macro|MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_1_SIDE &t;&t;    0x0AC
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE         0x0B0
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE          0x0B4
DECL|macro|MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE       0x0C0
DECL|macro|MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE      0x0C4
DECL|macro|MV64340_I2O_QUEUE_CONTROL_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_CONTROL_REG_PCI_1_SIDE &t;&t;    0x0D0
DECL|macro|MV64340_I2O_QUEUE_BASE_ADDR_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_BASE_ADDR_REG_PCI_1_SIDE &t;&t;    0x0D4
DECL|macro|MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE        0x0E0
DECL|macro|MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE        0x0E4
DECL|macro|MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE        0x0E8
DECL|macro|MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE        0x0EC
DECL|macro|MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE       0x0F0
DECL|macro|MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE       0x0F4
DECL|macro|MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE       0x078
DECL|macro|MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE       0x07C
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG0_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG0_CPU0_SIDE&t;&t;    0x1C10
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG1_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG1_CPU0_SIDE  &t;&t;    0x1C14
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG0_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG0_CPU0_SIDE &t;&t;    0x1C18
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG1_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG1_CPU0_SIDE  &t;&t;    0x1C1C
DECL|macro|MV64340_I2O_INBOUND_DOORBELL_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_DOORBELL_REG_CPU0_SIDE  &t;&t;    0x1C20
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE  &t;    0x1C24
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_CPU0_SIDE&t;    0x1C28
DECL|macro|MV64340_I2O_OUTBOUND_DOORBELL_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_DOORBELL_REG_CPU0_SIDE &t;&t;    0x1C2C
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE          0x1C30
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU0_SIDE           0x1C34
DECL|macro|MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE        0x1C40
DECL|macro|MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE       0x1C44
DECL|macro|MV64340_I2O_QUEUE_CONTROL_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_CONTROL_REG_CPU0_SIDE &t;&t;    0x1C50
DECL|macro|MV64340_I2O_QUEUE_BASE_ADDR_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_BASE_ADDR_REG_CPU0_SIDE &t;&t;    0x1C54
DECL|macro|MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE         0x1C60
DECL|macro|MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE         0x1C64
DECL|macro|MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE         0x1C68
DECL|macro|MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE         0x1C6C
DECL|macro|MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE        0x1C70
DECL|macro|MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE        0x1C74
DECL|macro|MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE        0x1CF8
DECL|macro|MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE        0x1CFC
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG0_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG0_CPU1_SIDE&t;&t;    0x1C90
DECL|macro|MV64340_I2O_INBOUND_MESSAGE_REG1_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_MESSAGE_REG1_CPU1_SIDE  &t;&t;    0x1C94
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG0_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG0_CPU1_SIDE &t;&t;    0x1C98
DECL|macro|MV64340_I2O_OUTBOUND_MESSAGE_REG1_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_MESSAGE_REG1_CPU1_SIDE  &t;&t;    0x1C9C
DECL|macro|MV64340_I2O_INBOUND_DOORBELL_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_DOORBELL_REG_CPU1_SIDE  &t;&t;    0x1CA0
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE  &t;    0x1CA4
DECL|macro|MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_CPU1_SIDE&t;    0x1CA8
DECL|macro|MV64340_I2O_OUTBOUND_DOORBELL_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_DOORBELL_REG_CPU1_SIDE &t;&t;    0x1CAC
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE          0x1CB0
DECL|macro|MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU1_SIDE           0x1CB4
DECL|macro|MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE        0x1CC0
DECL|macro|MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE       0x1CC4
DECL|macro|MV64340_I2O_QUEUE_CONTROL_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_CONTROL_REG_CPU1_SIDE &t;&t;    0x1CD0
DECL|macro|MV64340_I2O_QUEUE_BASE_ADDR_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_QUEUE_BASE_ADDR_REG_CPU1_SIDE &t;&t;    0x1CD4
DECL|macro|MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE         0x1CE0
DECL|macro|MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE         0x1CE4
DECL|macro|MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE         0x1CE8
DECL|macro|MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_INBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE         0x1CEC
DECL|macro|MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE        0x1CF0
DECL|macro|MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE        0x1CF4
DECL|macro|MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE        0x1C78
DECL|macro|MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE
mdefine_line|#define MV64340_I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE        0x1C7C
multiline_comment|/****************************************/
multiline_comment|/*        Ethernet Unit Registers  &t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_ETH_PHY_ADDR_REG
mdefine_line|#define MV64340_ETH_PHY_ADDR_REG                                    0x2000
DECL|macro|MV64340_ETH_SMI_REG
mdefine_line|#define MV64340_ETH_SMI_REG                                         0x2004
DECL|macro|MV64340_ETH_UNIT_DEFAULT_ADDR_REG
mdefine_line|#define MV64340_ETH_UNIT_DEFAULT_ADDR_REG                           0x2008
DECL|macro|MV64340_ETH_UNIT_DEFAULTID_REG
mdefine_line|#define MV64340_ETH_UNIT_DEFAULTID_REG                              0x200c
DECL|macro|MV64340_ETH_UNIT_INTERRUPT_CAUSE_REG
mdefine_line|#define MV64340_ETH_UNIT_INTERRUPT_CAUSE_REG                        0x2080
DECL|macro|MV64340_ETH_UNIT_INTERRUPT_MASK_REG
mdefine_line|#define MV64340_ETH_UNIT_INTERRUPT_MASK_REG                         0x2084
DECL|macro|MV64340_ETH_UNIT_INTERNAL_USE_REG
mdefine_line|#define MV64340_ETH_UNIT_INTERNAL_USE_REG                           0x24fc
DECL|macro|MV64340_ETH_UNIT_ERROR_ADDR_REG
mdefine_line|#define MV64340_ETH_UNIT_ERROR_ADDR_REG                             0x2094
DECL|macro|MV64340_ETH_BAR_0
mdefine_line|#define MV64340_ETH_BAR_0                                           0x2200
DECL|macro|MV64340_ETH_BAR_1
mdefine_line|#define MV64340_ETH_BAR_1                                           0x2208
DECL|macro|MV64340_ETH_BAR_2
mdefine_line|#define MV64340_ETH_BAR_2                                           0x2210
DECL|macro|MV64340_ETH_BAR_3
mdefine_line|#define MV64340_ETH_BAR_3                                           0x2218
DECL|macro|MV64340_ETH_BAR_4
mdefine_line|#define MV64340_ETH_BAR_4                                           0x2220
DECL|macro|MV64340_ETH_BAR_5
mdefine_line|#define MV64340_ETH_BAR_5                                           0x2228
DECL|macro|MV64340_ETH_SIZE_REG_0
mdefine_line|#define MV64340_ETH_SIZE_REG_0                                      0x2204
DECL|macro|MV64340_ETH_SIZE_REG_1
mdefine_line|#define MV64340_ETH_SIZE_REG_1                                      0x220c
DECL|macro|MV64340_ETH_SIZE_REG_2
mdefine_line|#define MV64340_ETH_SIZE_REG_2                                      0x2214
DECL|macro|MV64340_ETH_SIZE_REG_3
mdefine_line|#define MV64340_ETH_SIZE_REG_3                                      0x221c
DECL|macro|MV64340_ETH_SIZE_REG_4
mdefine_line|#define MV64340_ETH_SIZE_REG_4                                      0x2224
DECL|macro|MV64340_ETH_SIZE_REG_5
mdefine_line|#define MV64340_ETH_SIZE_REG_5                                      0x222c
DECL|macro|MV64340_ETH_HEADERS_RETARGET_BASE_REG
mdefine_line|#define MV64340_ETH_HEADERS_RETARGET_BASE_REG                       0x2230
DECL|macro|MV64340_ETH_HEADERS_RETARGET_CONTROL_REG
mdefine_line|#define MV64340_ETH_HEADERS_RETARGET_CONTROL_REG                    0x2234
DECL|macro|MV64340_ETH_HIGH_ADDR_REMAP_REG_0
mdefine_line|#define MV64340_ETH_HIGH_ADDR_REMAP_REG_0                           0x2280
DECL|macro|MV64340_ETH_HIGH_ADDR_REMAP_REG_1
mdefine_line|#define MV64340_ETH_HIGH_ADDR_REMAP_REG_1                           0x2284
DECL|macro|MV64340_ETH_HIGH_ADDR_REMAP_REG_2
mdefine_line|#define MV64340_ETH_HIGH_ADDR_REMAP_REG_2                           0x2288
DECL|macro|MV64340_ETH_HIGH_ADDR_REMAP_REG_3
mdefine_line|#define MV64340_ETH_HIGH_ADDR_REMAP_REG_3                           0x228c
DECL|macro|MV64340_ETH_BASE_ADDR_ENABLE_REG
mdefine_line|#define MV64340_ETH_BASE_ADDR_ENABLE_REG                            0x2290
DECL|macro|MV64340_ETH_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_ETH_ACCESS_PROTECTION_REG(port)                    (0x2294 + (port&lt;&lt;2))
DECL|macro|MV64340_ETH_MIB_COUNTERS_BASE
mdefine_line|#define MV64340_ETH_MIB_COUNTERS_BASE(port)                        (0x3000 + (port&lt;&lt;7))
DECL|macro|MV64340_ETH_PORT_CONFIG_REG
mdefine_line|#define MV64340_ETH_PORT_CONFIG_REG(port)                          (0x2400 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_CONFIG_EXTEND_REG
mdefine_line|#define MV64340_ETH_PORT_CONFIG_EXTEND_REG(port)                   (0x2404 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_MII_SERIAL_PARAMETRS_REG
mdefine_line|#define MV64340_ETH_MII_SERIAL_PARAMETRS_REG(port)                 (0x2408 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_GMII_SERIAL_PARAMETRS_REG
mdefine_line|#define MV64340_ETH_GMII_SERIAL_PARAMETRS_REG(port)                (0x240c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_VLAN_ETHERTYPE_REG
mdefine_line|#define MV64340_ETH_VLAN_ETHERTYPE_REG(port)                       (0x2410 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_MAC_ADDR_LOW
mdefine_line|#define MV64340_ETH_MAC_ADDR_LOW(port)                             (0x2414 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_MAC_ADDR_HIGH
mdefine_line|#define MV64340_ETH_MAC_ADDR_HIGH(port)                            (0x2418 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_SDMA_CONFIG_REG
mdefine_line|#define MV64340_ETH_SDMA_CONFIG_REG(port)                          (0x241c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_0
mdefine_line|#define MV64340_ETH_DSCP_0(port)                                   (0x2420 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_1
mdefine_line|#define MV64340_ETH_DSCP_1(port)                                   (0x2424 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_2
mdefine_line|#define MV64340_ETH_DSCP_2(port)                                   (0x2428 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_3
mdefine_line|#define MV64340_ETH_DSCP_3(port)                                   (0x242c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_4
mdefine_line|#define MV64340_ETH_DSCP_4(port)                                   (0x2430 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_5
mdefine_line|#define MV64340_ETH_DSCP_5(port)                                   (0x2434 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DSCP_6
mdefine_line|#define MV64340_ETH_DSCP_6(port)                                   (0x2438 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_SERIAL_CONTROL_REG
mdefine_line|#define MV64340_ETH_PORT_SERIAL_CONTROL_REG(port)                  (0x243c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_VLAN_PRIORITY_TAG_TO_PRIORITY
mdefine_line|#define MV64340_ETH_VLAN_PRIORITY_TAG_TO_PRIORITY(port)            (0x2440 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_STATUS_REG
mdefine_line|#define MV64340_ETH_PORT_STATUS_REG(port)                          (0x2444 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TRANSMIT_QUEUE_COMMAND_REG
mdefine_line|#define MV64340_ETH_TRANSMIT_QUEUE_COMMAND_REG(port)               (0x2448 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_FIXED_PRIORITY
mdefine_line|#define MV64340_ETH_TX_QUEUE_FIXED_PRIORITY(port)                  (0x244c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_TX_TOKEN_BUCKET_RATE_CONFIG
mdefine_line|#define MV64340_ETH_PORT_TX_TOKEN_BUCKET_RATE_CONFIG(port)         (0x2450 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_MAXIMUM_TRANSMIT_UNIT
mdefine_line|#define MV64340_ETH_MAXIMUM_TRANSMIT_UNIT(port)                    (0x2458 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_MAXIMUM_TOKEN_BUCKET_SIZE
mdefine_line|#define MV64340_ETH_PORT_MAXIMUM_TOKEN_BUCKET_SIZE(port)           (0x245c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_INTERRUPT_CAUSE_REG
mdefine_line|#define MV64340_ETH_INTERRUPT_CAUSE_REG(port)                      (0x2460 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_INTERRUPT_CAUSE_EXTEND_REG
mdefine_line|#define MV64340_ETH_INTERRUPT_CAUSE_EXTEND_REG(port)               (0x2464 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_INTERRUPT_MASK_REG
mdefine_line|#define MV64340_ETH_INTERRUPT_MASK_REG(port)                       (0x2468 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_INTERRUPT_EXTEND_MASK_REG
mdefine_line|#define MV64340_ETH_INTERRUPT_EXTEND_MASK_REG(port)                (0x246c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_RX_FIFO_URGENT_THRESHOLD_REG
mdefine_line|#define MV64340_ETH_RX_FIFO_URGENT_THRESHOLD_REG(port)             (0x2470 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_FIFO_URGENT_THRESHOLD_REG
mdefine_line|#define MV64340_ETH_TX_FIFO_URGENT_THRESHOLD_REG(port)             (0x2474 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_RX_MINIMAL_FRAME_SIZE_REG
mdefine_line|#define MV64340_ETH_RX_MINIMAL_FRAME_SIZE_REG(port)                (0x247c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_RX_DISCARDED_FRAMES_COUNTER
mdefine_line|#define MV64340_ETH_RX_DISCARDED_FRAMES_COUNTER(port)              (0x2484 + (port&lt;&lt;10)
DECL|macro|MV64340_ETH_PORT_DEBUG_0_REG
mdefine_line|#define MV64340_ETH_PORT_DEBUG_0_REG(port)                         (0x248c + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_DEBUG_1_REG
mdefine_line|#define MV64340_ETH_PORT_DEBUG_1_REG(port)                         (0x2490 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_INTERNAL_ADDR_ERROR_REG
mdefine_line|#define MV64340_ETH_PORT_INTERNAL_ADDR_ERROR_REG(port)             (0x2494 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_INTERNAL_USE_REG
mdefine_line|#define MV64340_ETH_INTERNAL_USE_REG(port)                         (0x24fc + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_RECEIVE_QUEUE_COMMAND_REG
mdefine_line|#define MV64340_ETH_RECEIVE_QUEUE_COMMAND_REG(port)                (0x2680 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_CURRENT_SERVED_TX_DESC_PTR
mdefine_line|#define MV64340_ETH_CURRENT_SERVED_TX_DESC_PTR(port)               (0x2684 + (port&lt;&lt;10))      
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_0
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_0(port)              (0x260c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_1
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_1(port)              (0x261c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_2
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_2(port)              (0x262c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_3
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_3(port)              (0x263c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_4
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_4(port)              (0x264c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_5
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_5(port)              (0x265c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_6
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_6(port)              (0x266c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_7
mdefine_line|#define MV64340_ETH_RX_CURRENT_QUEUE_DESC_PTR_7(port)              (0x267c + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_0
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_0(port)              (0x26c0 + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_1
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_1(port)              (0x26c4 + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_2
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_2(port)              (0x26c8 + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_3
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_3(port)              (0x26cc + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_4
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_4(port)              (0x26d0 + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_5
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_5(port)              (0x26d4 + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_6
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_6(port)              (0x26d8 + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_7
mdefine_line|#define MV64340_ETH_TX_CURRENT_QUEUE_DESC_PTR_7(port)              (0x26dc + (port&lt;&lt;10))     
DECL|macro|MV64340_ETH_TX_QUEUE_0_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_0_TOKEN_BUCKET_COUNT(port)            (0x2700 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_1_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_1_TOKEN_BUCKET_COUNT(port)            (0x2710 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_2_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_2_TOKEN_BUCKET_COUNT(port)            (0x2720 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_3_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_3_TOKEN_BUCKET_COUNT(port)            (0x2730 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_4_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_4_TOKEN_BUCKET_COUNT(port)            (0x2740 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_5_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_5_TOKEN_BUCKET_COUNT(port)            (0x2750 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_6_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_6_TOKEN_BUCKET_COUNT(port)            (0x2760 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_7_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_TX_QUEUE_7_TOKEN_BUCKET_COUNT(port)            (0x2770 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_0_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_0_TOKEN_BUCKET_CONFIG(port)           (0x2704 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_1_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_1_TOKEN_BUCKET_CONFIG(port)           (0x2714 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_2_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_2_TOKEN_BUCKET_CONFIG(port)           (0x2724 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_3_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_3_TOKEN_BUCKET_CONFIG(port)           (0x2734 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_4_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_4_TOKEN_BUCKET_CONFIG(port)           (0x2744 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_5_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_5_TOKEN_BUCKET_CONFIG(port)           (0x2754 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_6_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_6_TOKEN_BUCKET_CONFIG(port)           (0x2764 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_7_TOKEN_BUCKET_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_7_TOKEN_BUCKET_CONFIG(port)           (0x2774 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_0_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_0_ARBITER_CONFIG(port)                (0x2708 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_1_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_1_ARBITER_CONFIG(port)                (0x2718 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_2_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_2_ARBITER_CONFIG(port)                (0x2728 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_3_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_3_ARBITER_CONFIG(port)                (0x2738 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_4_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_4_ARBITER_CONFIG(port)                (0x2748 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_5_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_5_ARBITER_CONFIG(port)                (0x2758 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_6_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_6_ARBITER_CONFIG(port)                (0x2768 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_TX_QUEUE_7_ARBITER_CONFIG
mdefine_line|#define MV64340_ETH_TX_QUEUE_7_ARBITER_CONFIG(port)                (0x2778 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_PORT_TX_TOKEN_BUCKET_COUNT
mdefine_line|#define MV64340_ETH_PORT_TX_TOKEN_BUCKET_COUNT(port)               (0x2780 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DA_FILTER_SPECIAL_MULTICAST_TABLE_BASE
mdefine_line|#define MV64340_ETH_DA_FILTER_SPECIAL_MULTICAST_TABLE_BASE(port)   (0x3400 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DA_FILTER_OTHER_MULTICAST_TABLE_BASE
mdefine_line|#define MV64340_ETH_DA_FILTER_OTHER_MULTICAST_TABLE_BASE(port)     (0x3500 + (port&lt;&lt;10))
DECL|macro|MV64340_ETH_DA_FILTER_UNICAST_TABLE_BASE
mdefine_line|#define MV64340_ETH_DA_FILTER_UNICAST_TABLE_BASE(port)             (0x3600 + (port&lt;&lt;10))
multiline_comment|/*******************************************/
multiline_comment|/*          CUNIT  Registers               */
multiline_comment|/*******************************************/
multiline_comment|/* Address Decoding Register Map */
DECL|macro|MV64340_CUNIT_BASE_ADDR_REG0
mdefine_line|#define MV64340_CUNIT_BASE_ADDR_REG0                                0xf200
DECL|macro|MV64340_CUNIT_BASE_ADDR_REG1
mdefine_line|#define MV64340_CUNIT_BASE_ADDR_REG1                                0xf208
DECL|macro|MV64340_CUNIT_BASE_ADDR_REG2
mdefine_line|#define MV64340_CUNIT_BASE_ADDR_REG2                                0xf210
DECL|macro|MV64340_CUNIT_BASE_ADDR_REG3
mdefine_line|#define MV64340_CUNIT_BASE_ADDR_REG3                                0xf218
DECL|macro|MV64340_CUNIT_SIZE0
mdefine_line|#define MV64340_CUNIT_SIZE0                                         0xf204
DECL|macro|MV64340_CUNIT_SIZE1
mdefine_line|#define MV64340_CUNIT_SIZE1                                         0xf20c
DECL|macro|MV64340_CUNIT_SIZE2
mdefine_line|#define MV64340_CUNIT_SIZE2                                         0xf214
DECL|macro|MV64340_CUNIT_SIZE3
mdefine_line|#define MV64340_CUNIT_SIZE3                                         0xf21c
DECL|macro|MV64340_CUNIT_HIGH_ADDR_REMAP_REG0
mdefine_line|#define MV64340_CUNIT_HIGH_ADDR_REMAP_REG0                          0xf240
DECL|macro|MV64340_CUNIT_HIGH_ADDR_REMAP_REG1
mdefine_line|#define MV64340_CUNIT_HIGH_ADDR_REMAP_REG1                          0xf244
DECL|macro|MV64340_CUNIT_BASE_ADDR_ENABLE_REG
mdefine_line|#define MV64340_CUNIT_BASE_ADDR_ENABLE_REG                          0xf250
DECL|macro|MV64340_MPSC0_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_MPSC0_ACCESS_PROTECTION_REG                         0xf254
DECL|macro|MV64340_MPSC1_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_MPSC1_ACCESS_PROTECTION_REG                         0xf258
DECL|macro|MV64340_CUNIT_INTERNAL_SPACE_BASE_ADDR_REG
mdefine_line|#define MV64340_CUNIT_INTERNAL_SPACE_BASE_ADDR_REG                  0xf25C
multiline_comment|/*  Error Report Registers  */
DECL|macro|MV64340_CUNIT_INTERRUPT_CAUSE_REG
mdefine_line|#define MV64340_CUNIT_INTERRUPT_CAUSE_REG                           0xf310
DECL|macro|MV64340_CUNIT_INTERRUPT_MASK_REG
mdefine_line|#define MV64340_CUNIT_INTERRUPT_MASK_REG                            0xf314
DECL|macro|MV64340_CUNIT_ERROR_ADDR
mdefine_line|#define MV64340_CUNIT_ERROR_ADDR                                    0xf318
multiline_comment|/*  Cunit Control Registers */
DECL|macro|MV64340_CUNIT_ARBITER_CONTROL_REG
mdefine_line|#define MV64340_CUNIT_ARBITER_CONTROL_REG                           0xf300
DECL|macro|MV64340_CUNIT_CONFIG_REG
mdefine_line|#define MV64340_CUNIT_CONFIG_REG                                    0xb40c
DECL|macro|MV64340_CUNIT_CRROSBAR_TIMEOUT_REG
mdefine_line|#define MV64340_CUNIT_CRROSBAR_TIMEOUT_REG                          0xf304
multiline_comment|/*  Cunit Debug Registers   */
DECL|macro|MV64340_CUNIT_DEBUG_LOW
mdefine_line|#define MV64340_CUNIT_DEBUG_LOW                                     0xf340
DECL|macro|MV64340_CUNIT_DEBUG_HIGH
mdefine_line|#define MV64340_CUNIT_DEBUG_HIGH                                    0xf344
DECL|macro|MV64340_CUNIT_MMASK
mdefine_line|#define MV64340_CUNIT_MMASK                                         0xf380
multiline_comment|/*  MPSCs Clocks Routing Registers  */
DECL|macro|MV64340_MPSC_ROUTING_REG
mdefine_line|#define MV64340_MPSC_ROUTING_REG                                    0xb400
DECL|macro|MV64340_MPSC_RX_CLOCK_ROUTING_REG
mdefine_line|#define MV64340_MPSC_RX_CLOCK_ROUTING_REG                           0xb404
DECL|macro|MV64340_MPSC_TX_CLOCK_ROUTING_REG
mdefine_line|#define MV64340_MPSC_TX_CLOCK_ROUTING_REG                           0xb408
multiline_comment|/*  MPSCs Interrupts Registers    */
DECL|macro|MV64340_MPSC_CAUSE_REG
mdefine_line|#define MV64340_MPSC_CAUSE_REG(port)                               (0xb804 + (port&lt;&lt;3))
DECL|macro|MV64340_MPSC_MASK_REG
mdefine_line|#define MV64340_MPSC_MASK_REG(port)                                (0xb884 + (port&lt;&lt;3))
DECL|macro|MV64340_MPSC_MAIN_CONFIG_LOW
mdefine_line|#define MV64340_MPSC_MAIN_CONFIG_LOW(port)                         (0x8000 + (port&lt;&lt;12))
DECL|macro|MV64340_MPSC_MAIN_CONFIG_HIGH
mdefine_line|#define MV64340_MPSC_MAIN_CONFIG_HIGH(port)                        (0x8004 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_PROTOCOL_CONFIG
mdefine_line|#define MV64340_MPSC_PROTOCOL_CONFIG(port)                         (0x8008 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG1
mdefine_line|#define MV64340_MPSC_CHANNEL_REG1(port)                            (0x800c + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG2
mdefine_line|#define MV64340_MPSC_CHANNEL_REG2(port)                            (0x8010 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG3
mdefine_line|#define MV64340_MPSC_CHANNEL_REG3(port)                            (0x8014 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG4
mdefine_line|#define MV64340_MPSC_CHANNEL_REG4(port)                            (0x8018 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG5
mdefine_line|#define MV64340_MPSC_CHANNEL_REG5(port)                            (0x801c + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG6
mdefine_line|#define MV64340_MPSC_CHANNEL_REG6(port)                            (0x8020 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG7
mdefine_line|#define MV64340_MPSC_CHANNEL_REG7(port)                            (0x8024 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG8
mdefine_line|#define MV64340_MPSC_CHANNEL_REG8(port)                            (0x8028 + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG9
mdefine_line|#define MV64340_MPSC_CHANNEL_REG9(port)                            (0x802c + (port&lt;&lt;12))    
DECL|macro|MV64340_MPSC_CHANNEL_REG10
mdefine_line|#define MV64340_MPSC_CHANNEL_REG10(port)                           (0x8030 + (port&lt;&lt;12))    
multiline_comment|/*  MPSC0 Registers      */
multiline_comment|/***************************************/
multiline_comment|/*          SDMA Registers             */
multiline_comment|/***************************************/
DECL|macro|MV64340_SDMA_CONFIG_REG
mdefine_line|#define MV64340_SDMA_CONFIG_REG(channel)                        (0x4000 + (channel&lt;&lt;13))        
DECL|macro|MV64340_SDMA_COMMAND_REG
mdefine_line|#define MV64340_SDMA_COMMAND_REG(channel)                       (0x4008 + (channel&lt;&lt;13))        
DECL|macro|MV64340_SDMA_CURRENT_RX_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_SDMA_CURRENT_RX_DESCRIPTOR_POINTER(channel)     (0x4810 + (channel&lt;&lt;13))        
DECL|macro|MV64340_SDMA_CURRENT_TX_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_SDMA_CURRENT_TX_DESCRIPTOR_POINTER(channel)     (0x4c10 + (channel&lt;&lt;13))        
DECL|macro|MV64340_SDMA_FIRST_TX_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_SDMA_FIRST_TX_DESCRIPTOR_POINTER(channel)       (0x4c14 + (channel&lt;&lt;13)) 
DECL|macro|MV64340_SDMA_CAUSE_REG
mdefine_line|#define MV64340_SDMA_CAUSE_REG                                      0xb800
DECL|macro|MV64340_SDMA_MASK_REG
mdefine_line|#define MV64340_SDMA_MASK_REG                                       0xb880
multiline_comment|/* BRG Interrupts */
DECL|macro|MV64340_BRG_CONFIG_REG
mdefine_line|#define MV64340_BRG_CONFIG_REG(brg)                              (0xb200 + (brg&lt;&lt;3))
DECL|macro|MV64340_BRG_BAUDE_TUNING_REG
mdefine_line|#define MV64340_BRG_BAUDE_TUNING_REG(brg)                        (0xb208 + (brg&lt;&lt;3))
DECL|macro|MV64340_BRG_CAUSE_REG
mdefine_line|#define MV64340_BRG_CAUSE_REG                                       0xb834
DECL|macro|MV64340_BRG_MASK_REG
mdefine_line|#define MV64340_BRG_MASK_REG                                        0xb8b4
multiline_comment|/****************************************/
multiline_comment|/* DMA Channel Control&t;&t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_DMA_CHANNEL0_CONTROL
mdefine_line|#define MV64340_DMA_CHANNEL0_CONTROL &t;&t;&t;&t;    0x840
DECL|macro|MV64340_DMA_CHANNEL0_CONTROL_HIGH
mdefine_line|#define MV64340_DMA_CHANNEL0_CONTROL_HIGH&t;&t;&t;    0x880
DECL|macro|MV64340_DMA_CHANNEL1_CONTROL
mdefine_line|#define MV64340_DMA_CHANNEL1_CONTROL &t;&t;&t;&t;    0x844
DECL|macro|MV64340_DMA_CHANNEL1_CONTROL_HIGH
mdefine_line|#define MV64340_DMA_CHANNEL1_CONTROL_HIGH&t;&t;&t;    0x884
DECL|macro|MV64340_DMA_CHANNEL2_CONTROL
mdefine_line|#define MV64340_DMA_CHANNEL2_CONTROL &t;&t;&t;&t;    0x848
DECL|macro|MV64340_DMA_CHANNEL2_CONTROL_HIGH
mdefine_line|#define MV64340_DMA_CHANNEL2_CONTROL_HIGH&t;&t;&t;    0x888
DECL|macro|MV64340_DMA_CHANNEL3_CONTROL
mdefine_line|#define MV64340_DMA_CHANNEL3_CONTROL &t;&t;&t;&t;    0x84C
DECL|macro|MV64340_DMA_CHANNEL3_CONTROL_HIGH
mdefine_line|#define MV64340_DMA_CHANNEL3_CONTROL_HIGH&t;&t;&t;    0x88C
multiline_comment|/****************************************/
multiline_comment|/*           IDMA Registers             */
multiline_comment|/****************************************/
DECL|macro|MV64340_DMA_CHANNEL0_BYTE_COUNT
mdefine_line|#define MV64340_DMA_CHANNEL0_BYTE_COUNT                             0x800
DECL|macro|MV64340_DMA_CHANNEL1_BYTE_COUNT
mdefine_line|#define MV64340_DMA_CHANNEL1_BYTE_COUNT                             0x804
DECL|macro|MV64340_DMA_CHANNEL2_BYTE_COUNT
mdefine_line|#define MV64340_DMA_CHANNEL2_BYTE_COUNT                             0x808
DECL|macro|MV64340_DMA_CHANNEL3_BYTE_COUNT
mdefine_line|#define MV64340_DMA_CHANNEL3_BYTE_COUNT                             0x80C
DECL|macro|MV64340_DMA_CHANNEL0_SOURCE_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL0_SOURCE_ADDR                            0x810
DECL|macro|MV64340_DMA_CHANNEL1_SOURCE_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL1_SOURCE_ADDR                            0x814
DECL|macro|MV64340_DMA_CHANNEL2_SOURCE_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL2_SOURCE_ADDR                            0x818
DECL|macro|MV64340_DMA_CHANNEL3_SOURCE_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL3_SOURCE_ADDR                            0x81c
DECL|macro|MV64340_DMA_CHANNEL0_DESTINATION_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL0_DESTINATION_ADDR                       0x820
DECL|macro|MV64340_DMA_CHANNEL1_DESTINATION_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL1_DESTINATION_ADDR                       0x824
DECL|macro|MV64340_DMA_CHANNEL2_DESTINATION_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL2_DESTINATION_ADDR                       0x828
DECL|macro|MV64340_DMA_CHANNEL3_DESTINATION_ADDR
mdefine_line|#define MV64340_DMA_CHANNEL3_DESTINATION_ADDR                       0x82C
DECL|macro|MV64340_DMA_CHANNEL0_NEXT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL0_NEXT_DESCRIPTOR_POINTER                0x830
DECL|macro|MV64340_DMA_CHANNEL1_NEXT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL1_NEXT_DESCRIPTOR_POINTER                0x834
DECL|macro|MV64340_DMA_CHANNEL2_NEXT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL2_NEXT_DESCRIPTOR_POINTER                0x838
DECL|macro|MV64340_DMA_CHANNEL3_NEXT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL3_NEXT_DESCRIPTOR_POINTER                0x83C
DECL|macro|MV64340_DMA_CHANNEL0_CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL0_CURRENT_DESCRIPTOR_POINTER             0x870
DECL|macro|MV64340_DMA_CHANNEL1_CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL1_CURRENT_DESCRIPTOR_POINTER             0x874
DECL|macro|MV64340_DMA_CHANNEL2_CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL2_CURRENT_DESCRIPTOR_POINTER             0x878
DECL|macro|MV64340_DMA_CHANNEL3_CURRENT_DESCRIPTOR_POINTER
mdefine_line|#define MV64340_DMA_CHANNEL3_CURRENT_DESCRIPTOR_POINTER             0x87C
multiline_comment|/*  IDMA Address Decoding Base Address Registers  */
DECL|macro|MV64340_DMA_BASE_ADDR_REG0
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG0                                  0xa00
DECL|macro|MV64340_DMA_BASE_ADDR_REG1
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG1                                  0xa08
DECL|macro|MV64340_DMA_BASE_ADDR_REG2
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG2                                  0xa10
DECL|macro|MV64340_DMA_BASE_ADDR_REG3
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG3                                  0xa18
DECL|macro|MV64340_DMA_BASE_ADDR_REG4
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG4                                  0xa20
DECL|macro|MV64340_DMA_BASE_ADDR_REG5
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG5                                  0xa28
DECL|macro|MV64340_DMA_BASE_ADDR_REG6
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG6                                  0xa30
DECL|macro|MV64340_DMA_BASE_ADDR_REG7
mdefine_line|#define MV64340_DMA_BASE_ADDR_REG7                                  0xa38
multiline_comment|/*  IDMA Address Decoding Size Address Register   */
DECL|macro|MV64340_DMA_SIZE_REG0
mdefine_line|#define MV64340_DMA_SIZE_REG0                                       0xa04
DECL|macro|MV64340_DMA_SIZE_REG1
mdefine_line|#define MV64340_DMA_SIZE_REG1                                       0xa0c
DECL|macro|MV64340_DMA_SIZE_REG2
mdefine_line|#define MV64340_DMA_SIZE_REG2                                       0xa14
DECL|macro|MV64340_DMA_SIZE_REG3
mdefine_line|#define MV64340_DMA_SIZE_REG3                                       0xa1c
DECL|macro|MV64340_DMA_SIZE_REG4
mdefine_line|#define MV64340_DMA_SIZE_REG4                                       0xa24
DECL|macro|MV64340_DMA_SIZE_REG5
mdefine_line|#define MV64340_DMA_SIZE_REG5                                       0xa2c
DECL|macro|MV64340_DMA_SIZE_REG6
mdefine_line|#define MV64340_DMA_SIZE_REG6                                       0xa34
DECL|macro|MV64340_DMA_SIZE_REG7
mdefine_line|#define MV64340_DMA_SIZE_REG7                                       0xa3C
multiline_comment|/* IDMA Address Decoding High Address Remap and Access &n;                  Protection Registers                    */
DECL|macro|MV64340_DMA_HIGH_ADDR_REMAP_REG0
mdefine_line|#define MV64340_DMA_HIGH_ADDR_REMAP_REG0                            0xa60
DECL|macro|MV64340_DMA_HIGH_ADDR_REMAP_REG1
mdefine_line|#define MV64340_DMA_HIGH_ADDR_REMAP_REG1                            0xa64
DECL|macro|MV64340_DMA_HIGH_ADDR_REMAP_REG2
mdefine_line|#define MV64340_DMA_HIGH_ADDR_REMAP_REG2                            0xa68
DECL|macro|MV64340_DMA_HIGH_ADDR_REMAP_REG3
mdefine_line|#define MV64340_DMA_HIGH_ADDR_REMAP_REG3                            0xa6C
DECL|macro|MV64340_DMA_BASE_ADDR_ENABLE_REG
mdefine_line|#define MV64340_DMA_BASE_ADDR_ENABLE_REG                            0xa80
DECL|macro|MV64340_DMA_CHANNEL0_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_DMA_CHANNEL0_ACCESS_PROTECTION_REG                  0xa70
DECL|macro|MV64340_DMA_CHANNEL1_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_DMA_CHANNEL1_ACCESS_PROTECTION_REG                  0xa74
DECL|macro|MV64340_DMA_CHANNEL2_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_DMA_CHANNEL2_ACCESS_PROTECTION_REG                  0xa78
DECL|macro|MV64340_DMA_CHANNEL3_ACCESS_PROTECTION_REG
mdefine_line|#define MV64340_DMA_CHANNEL3_ACCESS_PROTECTION_REG                  0xa7c
DECL|macro|MV64340_DMA_ARBITER_CONTROL
mdefine_line|#define MV64340_DMA_ARBITER_CONTROL                                 0x860
DECL|macro|MV64340_DMA_CROSS_BAR_TIMEOUT
mdefine_line|#define MV64340_DMA_CROSS_BAR_TIMEOUT                               0x8d0
multiline_comment|/*  IDMA Headers Retarget Registers   */
DECL|macro|MV64340_DMA_HEADERS_RETARGET_CONTROL
mdefine_line|#define MV64340_DMA_HEADERS_RETARGET_CONTROL                        0xa84
DECL|macro|MV64340_DMA_HEADERS_RETARGET_BASE
mdefine_line|#define MV64340_DMA_HEADERS_RETARGET_BASE                           0xa88
multiline_comment|/*  IDMA Interrupt Register  */
DECL|macro|MV64340_DMA_INTERRUPT_CAUSE_REG
mdefine_line|#define MV64340_DMA_INTERRUPT_CAUSE_REG                             0x8c0
DECL|macro|MV64340_DMA_INTERRUPT_CAUSE_MASK
mdefine_line|#define MV64340_DMA_INTERRUPT_CAUSE_MASK                            0x8c4
DECL|macro|MV64340_DMA_ERROR_ADDR
mdefine_line|#define MV64340_DMA_ERROR_ADDR                                      0x8c8
DECL|macro|MV64340_DMA_ERROR_SELECT
mdefine_line|#define MV64340_DMA_ERROR_SELECT                                    0x8cc
multiline_comment|/*  IDMA Debug Register ( for internal use )    */
DECL|macro|MV64340_DMA_DEBUG_LOW
mdefine_line|#define MV64340_DMA_DEBUG_LOW                                       0x8e0
DECL|macro|MV64340_DMA_DEBUG_HIGH
mdefine_line|#define MV64340_DMA_DEBUG_HIGH                                      0x8e4
DECL|macro|MV64340_DMA_SPARE
mdefine_line|#define MV64340_DMA_SPARE                                           0xA8C
multiline_comment|/****************************************/
multiline_comment|/* Timer_Counter &t;&t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_TIMER_COUNTER0
mdefine_line|#define MV64340_TIMER_COUNTER0&t;&t;&t;&t;&t;    0x850
DECL|macro|MV64340_TIMER_COUNTER1
mdefine_line|#define MV64340_TIMER_COUNTER1&t;&t;&t;&t;&t;    0x854
DECL|macro|MV64340_TIMER_COUNTER2
mdefine_line|#define MV64340_TIMER_COUNTER2&t;&t;&t;&t;&t;    0x858
DECL|macro|MV64340_TIMER_COUNTER3
mdefine_line|#define MV64340_TIMER_COUNTER3&t;&t;&t;&t;&t;    0x85C
DECL|macro|MV64340_TIMER_COUNTER_0_3_CONTROL
mdefine_line|#define MV64340_TIMER_COUNTER_0_3_CONTROL&t;&t;&t;    0x864
DECL|macro|MV64340_TIMER_COUNTER_0_3_INTERRUPT_CAUSE
mdefine_line|#define MV64340_TIMER_COUNTER_0_3_INTERRUPT_CAUSE&t;&t;    0x868
DECL|macro|MV64340_TIMER_COUNTER_0_3_INTERRUPT_MASK
mdefine_line|#define MV64340_TIMER_COUNTER_0_3_INTERRUPT_MASK      &t;&t;    0x86c
multiline_comment|/****************************************/
multiline_comment|/*         Watchdog registers  &t;        */
multiline_comment|/****************************************/
DECL|macro|MV64340_WATCHDOG_CONFIG_REG
mdefine_line|#define MV64340_WATCHDOG_CONFIG_REG                                 0xb410
DECL|macro|MV64340_WATCHDOG_VALUE_REG
mdefine_line|#define MV64340_WATCHDOG_VALUE_REG                                  0xb414
multiline_comment|/****************************************/
multiline_comment|/* I2C Registers                        */
multiline_comment|/****************************************/
DECL|macro|MV64340_I2C_SLAVE_ADDR
mdefine_line|#define MV64340_I2C_SLAVE_ADDR                                      0xc000
DECL|macro|MV64340_I2C_EXTENDED_SLAVE_ADDR
mdefine_line|#define MV64340_I2C_EXTENDED_SLAVE_ADDR                             0xc010
DECL|macro|MV64340_I2C_DATA
mdefine_line|#define MV64340_I2C_DATA                                            0xc004
DECL|macro|MV64340_I2C_CONTROL
mdefine_line|#define MV64340_I2C_CONTROL                                         0xc008
DECL|macro|MV64340_I2C_STATUS_BAUDE_RATE
mdefine_line|#define MV64340_I2C_STATUS_BAUDE_RATE                               0xc00C
DECL|macro|MV64340_I2C_SOFT_RESET
mdefine_line|#define MV64340_I2C_SOFT_RESET                                      0xc01c
multiline_comment|/****************************************/
multiline_comment|/* GPP Interface Registers              */
multiline_comment|/****************************************/
DECL|macro|MV64340_GPP_IO_CONTROL
mdefine_line|#define MV64340_GPP_IO_CONTROL                                      0xf100
DECL|macro|MV64340_GPP_LEVEL_CONTROL
mdefine_line|#define MV64340_GPP_LEVEL_CONTROL                                   0xf110
DECL|macro|MV64340_GPP_VALUE
mdefine_line|#define MV64340_GPP_VALUE                                           0xf104
DECL|macro|MV64340_GPP_INTERRUPT_CAUSE
mdefine_line|#define MV64340_GPP_INTERRUPT_CAUSE                                 0xf108
DECL|macro|MV64340_GPP_INTERRUPT_MASK0
mdefine_line|#define MV64340_GPP_INTERRUPT_MASK0                                 0xf10c
DECL|macro|MV64340_GPP_INTERRUPT_MASK1
mdefine_line|#define MV64340_GPP_INTERRUPT_MASK1                                 0xf114
DECL|macro|MV64340_GPP_VALUE_SET
mdefine_line|#define MV64340_GPP_VALUE_SET                                       0xf118
DECL|macro|MV64340_GPP_VALUE_CLEAR
mdefine_line|#define MV64340_GPP_VALUE_CLEAR                                     0xf11c
multiline_comment|/****************************************/
multiline_comment|/* Interrupt Controller Registers       */
multiline_comment|/****************************************/
multiline_comment|/****************************************/
multiline_comment|/* Interrupts&t;  &t;&t;&t;*/
multiline_comment|/****************************************/
DECL|macro|MV64340_MAIN_INTERRUPT_CAUSE_LOW
mdefine_line|#define MV64340_MAIN_INTERRUPT_CAUSE_LOW                            0x004
DECL|macro|MV64340_MAIN_INTERRUPT_CAUSE_HIGH
mdefine_line|#define MV64340_MAIN_INTERRUPT_CAUSE_HIGH                           0x00c
DECL|macro|MV64340_CPU_INTERRUPT0_MASK_LOW
mdefine_line|#define MV64340_CPU_INTERRUPT0_MASK_LOW                             0x014
DECL|macro|MV64340_CPU_INTERRUPT0_MASK_HIGH
mdefine_line|#define MV64340_CPU_INTERRUPT0_MASK_HIGH                            0x01c
DECL|macro|MV64340_CPU_INTERRUPT0_SELECT_CAUSE
mdefine_line|#define MV64340_CPU_INTERRUPT0_SELECT_CAUSE                         0x024
DECL|macro|MV64340_CPU_INTERRUPT1_MASK_LOW
mdefine_line|#define MV64340_CPU_INTERRUPT1_MASK_LOW                             0x034
DECL|macro|MV64340_CPU_INTERRUPT1_MASK_HIGH
mdefine_line|#define MV64340_CPU_INTERRUPT1_MASK_HIGH                            0x03c
DECL|macro|MV64340_CPU_INTERRUPT1_SELECT_CAUSE
mdefine_line|#define MV64340_CPU_INTERRUPT1_SELECT_CAUSE                         0x044
DECL|macro|MV64340_INTERRUPT0_MASK_0_LOW
mdefine_line|#define MV64340_INTERRUPT0_MASK_0_LOW                               0x054
DECL|macro|MV64340_INTERRUPT0_MASK_0_HIGH
mdefine_line|#define MV64340_INTERRUPT0_MASK_0_HIGH                              0x05c
DECL|macro|MV64340_INTERRUPT0_SELECT_CAUSE
mdefine_line|#define MV64340_INTERRUPT0_SELECT_CAUSE                             0x064
DECL|macro|MV64340_INTERRUPT1_MASK_0_LOW
mdefine_line|#define MV64340_INTERRUPT1_MASK_0_LOW                               0x074
DECL|macro|MV64340_INTERRUPT1_MASK_0_HIGH
mdefine_line|#define MV64340_INTERRUPT1_MASK_0_HIGH                              0x07c
DECL|macro|MV64340_INTERRUPT1_SELECT_CAUSE
mdefine_line|#define MV64340_INTERRUPT1_SELECT_CAUSE                             0x084
multiline_comment|/****************************************/
multiline_comment|/*      MPP Interface Registers         */
multiline_comment|/****************************************/
DECL|macro|MV64340_MPP_CONTROL0
mdefine_line|#define MV64340_MPP_CONTROL0                                        0xf000
DECL|macro|MV64340_MPP_CONTROL1
mdefine_line|#define MV64340_MPP_CONTROL1                                        0xf004
DECL|macro|MV64340_MPP_CONTROL2
mdefine_line|#define MV64340_MPP_CONTROL2                                        0xf008
DECL|macro|MV64340_MPP_CONTROL3
mdefine_line|#define MV64340_MPP_CONTROL3                                        0xf00c
multiline_comment|/****************************************/
multiline_comment|/*    Serial Initialization registers   */
multiline_comment|/****************************************/
DECL|macro|MV64340_SERIAL_INIT_LAST_DATA
mdefine_line|#define MV64340_SERIAL_INIT_LAST_DATA                               0xf324
DECL|macro|MV64340_SERIAL_INIT_CONTROL
mdefine_line|#define MV64340_SERIAL_INIT_CONTROL                                 0xf328
DECL|macro|MV64340_SERIAL_INIT_STATUS
mdefine_line|#define MV64340_SERIAL_INIT_STATUS                                  0xf32c
r_extern
r_void
id|mv64340_irq_init
c_func
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
multiline_comment|/* MPSC Platform Device, Driver Data (Shared register regions) */
DECL|macro|MPSC_SHARED_NAME
mdefine_line|#define&t;MPSC_SHARED_NAME&t;&t;&quot;mpsc_shared&quot;
DECL|macro|MPSC_ROUTING_BASE_ORDER
mdefine_line|#define&t;MPSC_ROUTING_BASE_ORDER&t;&t;0
DECL|macro|MPSC_SDMA_INTR_BASE_ORDER
mdefine_line|#define&t;MPSC_SDMA_INTR_BASE_ORDER&t;1
DECL|macro|MPSC_ROUTING_REG_BLOCK_SIZE
mdefine_line|#define MPSC_ROUTING_REG_BLOCK_SIZE&t;0x000c
DECL|macro|MPSC_SDMA_INTR_REG_BLOCK_SIZE
mdefine_line|#define MPSC_SDMA_INTR_REG_BLOCK_SIZE&t;0x0084
DECL|struct|mpsc_shared_pd_dd
r_struct
id|mpsc_shared_pd_dd
(brace
DECL|member|mrr_val
id|u32
id|mrr_val
suffix:semicolon
DECL|member|rcrr_val
id|u32
id|rcrr_val
suffix:semicolon
DECL|member|tcrr_val
id|u32
id|tcrr_val
suffix:semicolon
DECL|member|intr_cause_val
id|u32
id|intr_cause_val
suffix:semicolon
DECL|member|intr_mask_val
id|u32
id|intr_mask_val
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* MPSC Platform Device, Driver Data */
DECL|macro|MPSC_CTLR_NAME
mdefine_line|#define&t;MPSC_CTLR_NAME&t;&t;&t;&quot;mpsc&quot;
DECL|macro|MPSC_BASE_ORDER
mdefine_line|#define&t;MPSC_BASE_ORDER&t;&t;&t;0
DECL|macro|MPSC_SDMA_BASE_ORDER
mdefine_line|#define&t;MPSC_SDMA_BASE_ORDER&t;&t;1
DECL|macro|MPSC_BRG_BASE_ORDER
mdefine_line|#define&t;MPSC_BRG_BASE_ORDER&t;&t;2
DECL|macro|MPSC_REG_BLOCK_SIZE
mdefine_line|#define MPSC_REG_BLOCK_SIZE&t;&t;0x0038
DECL|macro|MPSC_SDMA_REG_BLOCK_SIZE
mdefine_line|#define MPSC_SDMA_REG_BLOCK_SIZE&t;0x0c18
DECL|macro|MPSC_BRG_REG_BLOCK_SIZE
mdefine_line|#define MPSC_BRG_REG_BLOCK_SIZE&t;&t;0x0008
DECL|struct|mpsc_pd_dd
r_struct
id|mpsc_pd_dd
(brace
DECL|member|mirror_regs
id|u8
id|mirror_regs
suffix:semicolon
DECL|member|cache_mgmt
id|u8
id|cache_mgmt
suffix:semicolon
DECL|member|max_idle
id|u8
id|max_idle
suffix:semicolon
DECL|member|default_baud
r_int
id|default_baud
suffix:semicolon
DECL|member|default_bits
r_int
id|default_bits
suffix:semicolon
DECL|member|default_parity
r_int
id|default_parity
suffix:semicolon
DECL|member|default_flow
r_int
id|default_flow
suffix:semicolon
DECL|member|chr_1_val
id|u32
id|chr_1_val
suffix:semicolon
DECL|member|chr_2_val
id|u32
id|chr_2_val
suffix:semicolon
DECL|member|chr_10_val
id|u32
id|chr_10_val
suffix:semicolon
DECL|member|mpcr_val
id|u32
id|mpcr_val
suffix:semicolon
DECL|member|bcr_val
id|u32
id|bcr_val
suffix:semicolon
DECL|member|brg_can_tune
id|u8
id|brg_can_tune
suffix:semicolon
DECL|member|brg_clk_src
id|u8
id|brg_clk_src
suffix:semicolon
DECL|member|brg_clk_freq
id|u32
id|brg_clk_freq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASM_MV64340_H */
eof
