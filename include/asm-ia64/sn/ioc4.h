multiline_comment|/*&n; * Copyright (c) 2002-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; */
macro_line|#ifndef _ASM_IA64_SN_IOC4_H
DECL|macro|_ASM_IA64_SN_IOC4_H
mdefine_line|#define _ASM_IA64_SN_IOC4_H
macro_line|#if 0
multiline_comment|/*&n; * ioc4.h - IOC4 chip header file&n; */
multiline_comment|/* Notes:&n; * The IOC4 chip is a 32-bit PCI device that provides 4 serial ports,&n; * an IDE bus interface, a PC keyboard/mouse interface, and a real-time&n; * external interrupt interface.&n; *&n; * It includes an optimized DMA buffer management, and a store-and-forward&n; * buffer RAM.&n; *&n; * All IOC4 registers are 32 bits wide.&n; */
r_typedef
id|__uint32_t
id|ioc4reg_t
suffix:semicolon
multiline_comment|/*&n; * PCI Configuration Space Register Address Map, use offset from IOC4 PCI&n; * configuration base such that this can be used for multiple IOC4s&n; */
mdefine_line|#define IOC4_PCI_ID&t;&t;0x0&t;/* ID */
mdefine_line|#define IOC4_VENDOR_ID_NUM&t;0x10A9
mdefine_line|#define IOC4_DEVICE_ID_NUM&t;0x100A 
mdefine_line|#define IOC4_ADDRSPACE_MASK&t;0xfff00000ULL
mdefine_line|#define IOC4_PCI_SCR&t;&t;0x4 /* Status/Command */
mdefine_line|#define IOC4_PCI_REV&t;&t;0x8 /* Revision */
mdefine_line|#define IOC4_PCI_LAT&t;&t;0xC /* Latency Timer */
mdefine_line|#define IOC4_PCI_BAR0&t;&t;0x10 /* IOC4 base address 0 */
mdefine_line|#define IOC4_PCI_SIDV&t;&t;0x2c /* Subsys ID and vendor */
mdefine_line|#define IOC4_PCI_CAP &t;&t;0x34 /* Capability pointer */
mdefine_line|#define IOC4_PCI_LATGNTINT      0x3c /* Max_lat, min_gnt, int_pin, int_line */
multiline_comment|/*&n; * PCI Memory Space Map &n; */
mdefine_line|#define IOC4_PCI_ERR_ADDR_L     0x000&t;/* Low Error Address */
mdefine_line|#define IOC4_PCI_ERR_ADDR_VLD&t;     (0x1 &lt;&lt; 0)
mdefine_line|#define IOC4_PCI_ERR_ADDR_MST_ID_MSK (0xf &lt;&lt; 1)
mdefine_line|#define IOC4_PCI_ERR_ADDR_MUL_ERR    (0x1 &lt;&lt; 5)
mdefine_line|#define IOC4_PCI_ERR_ADDR_ADDR_MSK   (0x3ffffff &lt;&lt; 6)
multiline_comment|/* Master IDs contained in PCI_ERR_ADDR_MST_ID_MSK */
mdefine_line|#define IOC4_MST_ID_S0_TX&t;&t;0
mdefine_line|#define IOC4_MST_ID_S0_RX&t;&t;1
mdefine_line|#define IOC4_MST_ID_S1_TX&t;&t;2
mdefine_line|#define IOC4_MST_ID_S1_RX&t;&t;3
mdefine_line|#define IOC4_MST_ID_S2_TX&t;&t;4
mdefine_line|#define IOC4_MST_ID_S2_RX&t;&t;5
mdefine_line|#define IOC4_MST_ID_S3_TX&t;&t;6
mdefine_line|#define IOC4_MST_ID_S3_RX&t;&t;7
mdefine_line|#define IOC4_MST_ID_ATA &t;&t;8
mdefine_line|#define IOC4_PCI_ERR_ADDR_H&t;0x004&t;/* High Error Address */
mdefine_line|#define IOC4_SIO_IR&t;        0x008&t;/* SIO Interrupt Register */
mdefine_line|#define IOC4_OTHER_IR&t;        0x00C&t;/* Other Interrupt Register */
multiline_comment|/* These registers are read-only for general kernel code. To modify&n; * them use the functions in ioc4.c&n; */
mdefine_line|#define IOC4_SIO_IES_RO         0x010&t;/* SIO Interrupt Enable Set Reg */
mdefine_line|#define IOC4_OTHER_IES_RO       0x014&t;/* Other Interrupt Enable Set Reg */
mdefine_line|#define IOC4_SIO_IEC_RO         0x018&t;/* SIO Interrupt Enable Clear Reg */
mdefine_line|#define IOC4_OTHER_IEC_RO       0x01C&t;/* Other Interrupt Enable Clear Reg */
mdefine_line|#define IOC4_SIO_CR&t;        0x020&t;/* SIO Control Reg */
mdefine_line|#define IOC4_INT_OUT&t;        0x028&t;/* INT_OUT Reg (realtime interrupt) */
mdefine_line|#define IOC4_GPCR_S&t;        0x030&t;/* GenericPIO Cntrl Set Register */
mdefine_line|#define IOC4_GPCR_C&t;        0x034&t;/* GenericPIO Cntrl Clear Register */
mdefine_line|#define IOC4_GPDR&t;        0x038&t;/* GenericPIO Data Register */
mdefine_line|#define IOC4_GPPR_0&t;        0x040&t;/* GenericPIO Pin Registers */
mdefine_line|#define IOC4_GPPR_OFF&t;        0x4
mdefine_line|#define IOC4_GPPR(x)&t;        (IOC4_GPPR_0+(x)*IOC4_GPPR_OFF)
multiline_comment|/* ATAPI Registers */
mdefine_line|#define IOC4_ATA_0              0x100&t;/* Data w/timing */
mdefine_line|#define IOC4_ATA_1              0x104&t;/* Error/Features w/timing */
mdefine_line|#define IOC4_ATA_2              0x108&t;/* Sector Count w/timing */
mdefine_line|#define IOC4_ATA_3              0x10C&t;/* Sector Number w/timing */
mdefine_line|#define IOC4_ATA_4              0x110   /* Cyliner Low w/timing */
mdefine_line|#define IOC4_ATA_5              0x114&t;/* Cylinder High w/timing */
mdefine_line|#define IOC4_ATA_6              0x118&t;/* Device/Head w/timing */
mdefine_line|#define IOC4_ATA_7              0x11C&t;/* Status/Command w/timing */
mdefine_line|#define IOC4_ATA_0_AUX          0x120&t;/* Aux Status/Device Cntrl w/timing */
mdefine_line|#define IOC4_ATA_TIMING       &t;0x140&t;/* Timing value register 0 */
mdefine_line|#define IOC4_ATA_DMA_PTR_L      0x144   /* Low Memory Pointer to DMA List */
mdefine_line|#define IOC4_ATA_DMA_PTR_H      0x148   /* High Memory Pointer to DMA List */
mdefine_line|#define IOC4_ATA_DMA_ADDR_L     0x14C   /* Low Memory DMA Address */
mdefine_line|#define IOC4_ATA_DMA_ADDR_H     0x150   /* High Memory DMA Addresss */
mdefine_line|#define IOC4_ATA_BC_DEV         0x154&t;/* DMA Byte Count at Device */
mdefine_line|#define IOC4_ATA_BC_MEM         0x158&t;/* DMA Byte Count at Memory */
mdefine_line|#define IOC4_ATA_DMA_CTRL       0x15C&t;/* DMA Control/Status */
multiline_comment|/* Keyboard and Mouse Registers */
mdefine_line|#define IOC4_KM_CSR&t;        0x200&t;/* Kbd and Mouse Cntrl/Status Reg */
mdefine_line|#define IOC4_K_RD&t;        0x204&t;/* Kbd Read Data Register */
mdefine_line|#define IOC4_M_RD&t;        0x208&t;/* Mouse Read Data Register */
mdefine_line|#define IOC4_K_WD&t;        0x20C&t;/* Kbd Write Data Register */
mdefine_line|#define IOC4_M_WD&t;        0x210&t;/* Mouse Write Data Register */
multiline_comment|/* Serial Port Registers used for DMA mode serial I/O */
mdefine_line|#define IOC4_SBBR01_H&t;        0x300&t;/* Serial Port Ring Buffers &n;                                           Base Reg High for Channels 0 1*/
mdefine_line|#define IOC4_SBBR01_L&t;        0x304&t;/* Serial Port Ring Buffers &n;                                           Base Reg Low for Channels 0 1 */
mdefine_line|#define IOC4_SBBR23_H&t;        0x308&t;/* Serial Port Ring Buffers &n;                                           Base Reg High for Channels 2 3*/
mdefine_line|#define IOC4_SBBR23_L&t;        0x30C&t;/* Serial Port Ring Buffers &n;                                           Base Reg Low for Channels 2 3 */
mdefine_line|#define IOC4_SSCR_0&t;        0x310&t;/* Serial Port 0 Control */
mdefine_line|#define IOC4_STPIR_0&t;        0x314&t;/* Serial Port 0 TX Produce */
mdefine_line|#define IOC4_STCIR_0&t;        0x318&t;/* Serial Port 0 TX Consume */
mdefine_line|#define IOC4_SRPIR_0&t;        0x31C&t;/* Serial Port 0 RX Produce */
mdefine_line|#define IOC4_SRCIR_0&t;        0x320&t;/* Serial Port 0 RX Consume */
mdefine_line|#define IOC4_SRTR_0&t;        0x324&t;/* Serial Port 0 Receive Timer Reg */
mdefine_line|#define IOC4_SHADOW_0&t;&t;0x328&t;/* Serial Port 0 16550 Shadow Reg */
mdefine_line|#define IOC4_SSCR_1&t;        0x32C&t;/* Serial Port 1 Control */
mdefine_line|#define IOC4_STPIR_1&t;        0x330&t;/* Serial Port 1 TX Produce */
mdefine_line|#define IOC4_STCIR_1&t;        0x334&t;/* Serial Port 1 TX Consume */
mdefine_line|#define IOC4_SRPIR_1&t;        0x338   /* Serial Port 1 RX Produce */
mdefine_line|#define IOC4_SRCIR_1&t;        0x33C&t;/* Serial Port 1 RX Consume */
mdefine_line|#define IOC4_SRTR_1&t;        0x340&t;/* Serial Port 1 Receive Timer Reg */
mdefine_line|#define IOC4_SHADOW_1&t;&t;0x344&t;/* Serial Port 1 16550 Shadow Reg */
mdefine_line|#define IOC4_SSCR_2&t;        0x348&t;/* Serial Port 2 Control */
mdefine_line|#define IOC4_STPIR_2&t;        0x34C&t;/* Serial Port 2 TX Produce */
mdefine_line|#define IOC4_STCIR_2&t;        0x350&t;/* Serial Port 2 TX Consume */
mdefine_line|#define IOC4_SRPIR_2&t;        0x354&t;/* Serial Port 2 RX Produce */
mdefine_line|#define IOC4_SRCIR_2&t;        0x358&t;/* Serial Port 2 RX Consume */
mdefine_line|#define IOC4_SRTR_2&t;        0x35C&t;/* Serial Port 2 Receive Timer Reg */
mdefine_line|#define IOC4_SHADOW_2&t;&t;0x360&t;/* Serial Port 2 16550 Shadow Reg */
mdefine_line|#define IOC4_SSCR_3&t;        0x364&t;/* Serial Port 3 Control */
mdefine_line|#define IOC4_STPIR_3&t;        0x368&t;/* Serial Port 3 TX Produce */
mdefine_line|#define IOC4_STCIR_3&t;        0x36C&t;/* Serial Port 3 TX Consume */
mdefine_line|#define IOC4_SRPIR_3&t;        0x370&t;/* Serial Port 3 RX Produce */
mdefine_line|#define IOC4_SRCIR_3&t;        0x374&t;/* Serial Port 3 RX Consume */
mdefine_line|#define IOC4_SRTR_3&t;        0x378&t;/* Serial Port 3 Receive Timer Reg */
mdefine_line|#define IOC4_SHADOW_3&t;&t;0x37C&t;/* Serial Port 3 16550 Shadow Reg */
mdefine_line|#define IOC4_UART0_BASE         0x380   /* UART 0 */
mdefine_line|#define IOC4_UART1_BASE         0x388   /* UART 1 */
mdefine_line|#define IOC4_UART2_BASE         0x390   /* UART 2 */
mdefine_line|#define IOC4_UART3_BASE         0x398   /* UART 3 */
multiline_comment|/* Private page address aliases for usermode mapping */
mdefine_line|#define IOC4_INT_OUT_P&t;        0x04000&t;/* INT_OUT Reg */
mdefine_line|#define IOC4_SSCR_0_P&t;        0x08000 /* Serial Port 0 */
mdefine_line|#define IOC4_STPIR_0_P&t;        0x08004
mdefine_line|#define IOC4_STCIR_0_P&t;        0x08008&t;/* (read-only) */
mdefine_line|#define IOC4_SRPIR_0_P&t;        0x0800C&t;/* (read-only) */
mdefine_line|#define IOC4_SRCIR_0_P&t;        0x08010
mdefine_line|#define IOC4_SRTR_0_P&t;        0x08014
mdefine_line|#define IOC4_UART_LSMSMCR_0_P   0x08018&t;/* (read-only) */
mdefine_line|#define IOC4_SSCR_1_P&t;        0x0C000&t;/* Serial Port 1 */
mdefine_line|#define IOC4_STPIR_1_P&t;        0x0C004
mdefine_line|#define IOC4_STCIR_1_P&t;        0x0C008&t;/* (read-only) */
mdefine_line|#define IOC4_SRPIR_1_P&t;        0x0C00C&t;/* (read-only) */
mdefine_line|#define IOC4_SRCIR_1_P&t;        0x0C010
mdefine_line|#define IOC4_SRTR_1_P&t;        0x0C014
mdefine_line|#define IOC4_UART_LSMSMCR_1_P   0x0C018&t;/* (read-only) */
mdefine_line|#define IOC4_SSCR_2_P&t;        0x10000&t;/* Serial Port 2 */
mdefine_line|#define IOC4_STPIR_2_P&t;        0x10004
mdefine_line|#define IOC4_STCIR_2_P&t;        0x10008&t;/* (read-only) */
mdefine_line|#define IOC4_SRPIR_2_P&t;        0x1000C&t;/* (read-only) */
mdefine_line|#define IOC4_SRCIR_2_P&t;        0x10010
mdefine_line|#define IOC4_SRTR_2_P&t;        0x10014
mdefine_line|#define IOC4_UART_LSMSMCR_2_P   0x10018&t;/* (read-only) */
mdefine_line|#define IOC4_SSCR_3_P&t;        0x14000&t;/* Serial Port 3 */
mdefine_line|#define IOC4_STPIR_3_P&t;        0x14004
mdefine_line|#define IOC4_STCIR_3_P&t;        0x14008&t;/* (read-only) */
mdefine_line|#define IOC4_SRPIR_3_P&t;        0x1400C&t;/* (read-only) */
mdefine_line|#define IOC4_SRCIR_3_P&t;        0x14010
mdefine_line|#define IOC4_SRTR_3_P&t;        0x14014
mdefine_line|#define IOC4_UART_LSMSMCR_3_P   0x14018&t;/* (read-only) */
mdefine_line|#define IOC4_ALIAS_PAGE_SIZE&t;0x4000
multiline_comment|/* Interrupt types */
r_typedef
r_enum
id|ioc4_intr_type_e
(brace
id|ioc4_sio_intr_type
comma
id|ioc4_other_intr_type
comma
id|ioc4_num_intr_types
)brace
id|ioc4_intr_type_t
suffix:semicolon
mdefine_line|#define ioc4_first_intr_type    ioc4_sio_intr_type
multiline_comment|/* Bitmasks for IOC4_SIO_IR, IOC4_SIO_IEC, and IOC4_SIO_IES  */
mdefine_line|#define IOC4_SIO_IR_S0_TX_MT&t;&t;0x00000001 /* Serial port 0 TX empty */
mdefine_line|#define IOC4_SIO_IR_S0_RX_FULL&t;&t;0x00000002 /* Port 0 RX buf full */
mdefine_line|#define IOC4_SIO_IR_S0_RX_HIGH&t;&t;0x00000004 /* Port 0 RX hiwat */
mdefine_line|#define IOC4_SIO_IR_S0_RX_TIMER&t;&t;0x00000008 /* Port 0 RX timeout */
mdefine_line|#define IOC4_SIO_IR_S0_DELTA_DCD&t;0x00000010 /* Port 0 delta DCD */
mdefine_line|#define IOC4_SIO_IR_S0_DELTA_CTS&t;0x00000020 /* Port 0 delta CTS */
mdefine_line|#define IOC4_SIO_IR_S0_INT&t;        0x00000040 /* Port 0 pass-thru intr */
mdefine_line|#define IOC4_SIO_IR_S0_TX_EXPLICIT&t;0x00000080 /* Port 0 explicit TX thru */
mdefine_line|#define IOC4_SIO_IR_S1_TX_MT&t;&t;0x00000100 /* Serial port 1 */
mdefine_line|#define IOC4_SIO_IR_S1_RX_FULL&t;&t;0x00000200 /* */
mdefine_line|#define IOC4_SIO_IR_S1_RX_HIGH&t;&t;0x00000400 /* */
mdefine_line|#define IOC4_SIO_IR_S1_RX_TIMER&t;&t;0x00000800 /* */
mdefine_line|#define IOC4_SIO_IR_S1_DELTA_DCD&t;0x00001000 /* */
mdefine_line|#define IOC4_SIO_IR_S1_DELTA_CTS&t;0x00002000 /* */
mdefine_line|#define IOC4_SIO_IR_S1_INT&t;&t;0x00004000 /* */
mdefine_line|#define IOC4_SIO_IR_S1_TX_EXPLICIT&t;0x00008000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_TX_MT&t;&t;0x00010000 /* Serial port 2 */
mdefine_line|#define IOC4_SIO_IR_S2_RX_FULL&t;&t;0x00020000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_RX_HIGH&t;&t;0x00040000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_RX_TIMER&t;&t;0x00080000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_DELTA_DCD&t;0x00100000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_DELTA_CTS&t;0x00200000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_INT&t;&t;0x00400000 /* */
mdefine_line|#define IOC4_SIO_IR_S2_TX_EXPLICIT&t;0x00800000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_TX_MT&t;&t;0x01000000 /* Serial port 3 */
mdefine_line|#define IOC4_SIO_IR_S3_RX_FULL&t;&t;0x02000000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_RX_HIGH&t;&t;0x04000000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_RX_TIMER&t;&t;0x08000000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_DELTA_DCD&t;0x10000000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_DELTA_CTS&t;0x20000000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_INT&t;&t;0x40000000 /* */
mdefine_line|#define IOC4_SIO_IR_S3_TX_EXPLICIT&t;0x80000000 /* */
multiline_comment|/* Per device interrupt masks */
mdefine_line|#define IOC4_SIO_IR_S0&t;&t;(IOC4_SIO_IR_S0_TX_MT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_RX_FULL | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_RX_HIGH | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_RX_TIMER | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_DELTA_DCD | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_DELTA_CTS | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_INT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S0_TX_EXPLICIT)
mdefine_line|#define IOC4_SIO_IR_S1&t;&t;(IOC4_SIO_IR_S1_TX_MT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_RX_FULL | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_RX_HIGH | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_RX_TIMER | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_DELTA_DCD | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_DELTA_CTS | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_INT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S1_TX_EXPLICIT)
mdefine_line|#define IOC4_SIO_IR_S2&t;&t;(IOC4_SIO_IR_S2_TX_MT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_RX_FULL | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_RX_HIGH | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_RX_TIMER | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_DELTA_DCD | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_DELTA_CTS | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_INT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S2_TX_EXPLICIT)
mdefine_line|#define IOC4_SIO_IR_S3&t;&t;(IOC4_SIO_IR_S3_TX_MT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_RX_FULL | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_RX_HIGH | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_RX_TIMER | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_DELTA_DCD | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_DELTA_CTS | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_INT | &bslash;&n;&t;&t;&t;&t; IOC4_SIO_IR_S3_TX_EXPLICIT)
multiline_comment|/* Bitmasks for IOC4_OTHER_IR, IOC4_OTHER_IEC, and IOC4_OTHER_IES  */
mdefine_line|#define IOC4_OTHER_IR_ATA_INT           0x00000001 /* ATAPI intr pass-thru */
mdefine_line|#define IOC4_OTHER_IR_ATA_MEMERR        0x00000002 /* ATAPI DMA PCI error */
mdefine_line|#define IOC4_OTHER_IR_S0_MEMERR         0x00000004 /* Port 0 PCI error */
mdefine_line|#define IOC4_OTHER_IR_S1_MEMERR         0x00000008 /* Port 1 PCI error */
mdefine_line|#define IOC4_OTHER_IR_S2_MEMERR         0x00000010 /* Port 2 PCI error */
mdefine_line|#define IOC4_OTHER_IR_S3_MEMERR         0x00000020 /* Port 3 PCI error */
mdefine_line|#define IOC4_OTHER_IR_KBD_INT&t;&t;0x00000040 /* Kbd/mouse intr */
mdefine_line|#define IOC4_OTHER_IR_ATA_DMAINT        0x00000089 /* ATAPI DMA intr */
mdefine_line|#define IOC4_OTHER_IR_RT_INT&t;&t;0x00800000 /* RT output pulse */
mdefine_line|#define IOC4_OTHER_IR_GEN_INT1&t;&t;0x02000000 /* RT input pulse */
mdefine_line|#define IOC4_OTHER_IR_GEN_INT_SHIFT&t;        25
multiline_comment|/* Per device interrupt masks */
mdefine_line|#define IOC4_OTHER_IR_ATA       (IOC4_OTHER_IR_ATA_INT | &bslash;&n;&t;&t;&t;&t; IOC4_OTHER_IR_ATA_MEMERR | &bslash;&n;&t;&t;&t;&t; IOC4_OTHER_IR_ATA_DMAINT)
mdefine_line|#define IOC4_OTHER_IR_RT&t;(IOC4_OTHER_IR_RT_INT | IOC4_OTHER_IR_GEN_INT1)
multiline_comment|/* Macro to load pending interrupts */
mdefine_line|#define IOC4_PENDING_SIO_INTRS(mem)     (PCI_INW(&amp;((mem)-&gt;sio_ir)) &amp; &bslash;&n;&t;&t;&t;&t;         PCI_INW(&amp;((mem)-&gt;sio_ies_ro)))
mdefine_line|#define IOC4_PENDING_OTHER_INTRS(mem)   (PCI_INW(&amp;((mem)-&gt;other_ir)) &amp; &bslash;&n;&t;&t;&t;&t;         PCI_INW(&amp;((mem)-&gt;other_ies_ro)))
multiline_comment|/* Bitmasks for IOC4_SIO_CR */
mdefine_line|#define IOC4_SIO_SR_CMD_PULSE&t;&t;0x00000004 /* Byte bus strobe length */
mdefine_line|#define IOC4_SIO_CR_CMD_PULSE_SHIFT              0
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG&t;&t;0x00000070 /* Current non-ATA PCI bus&n;                                                      requester (ro) */
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_TX0&t;0x00000000
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_RX0&t;0x00000010
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_TX1&t;0x00000020
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_RX1&t;0x00000030
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_TX2&t;0x00000040
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_RX2&t;0x00000050
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_TX3&t;0x00000060
mdefine_line|#define IOC4_SIO_CR_ARB_DIAG_RX3&t;0x00000070
mdefine_line|#define IOC4_SIO_CR_SIO_DIAG_IDLE&t;0x00000080 /* 0 -&gt; active request among&n;                                                      serial ports (ro) */
mdefine_line|#define IOC4_SIO_CR_ATA_DIAG_IDLE&t;0x00000100 /* 0 -&gt; active request from&n;                                                      ATA port */
mdefine_line|#define IOC4_SIO_CR_ATA_DIAG_ACTIVE     0x00000200 /* 1 -&gt; ATA request is winner */ 
multiline_comment|/* Bitmasks for IOC4_INT_OUT */
mdefine_line|#define IOC4_INT_OUT_COUNT&t;        0x0000ffff /* Pulse interval timer */
mdefine_line|#define IOC4_INT_OUT_MODE&t;        0x00070000 /* Mode mask */
mdefine_line|#define IOC4_INT_OUT_MODE_0             0x00000000 /* Set output to 0 */
mdefine_line|#define IOC4_INT_OUT_MODE_1             0x00040000 /* Set output to 1 */
mdefine_line|#define IOC4_INT_OUT_MODE_1PULSE        0x00050000 /* Send 1 pulse */
mdefine_line|#define IOC4_INT_OUT_MODE_PULSES        0x00060000 /* Send 1 pulse every interval */
mdefine_line|#define IOC4_INT_OUT_MODE_SQW           0x00070000 /* Toggle output every interval */
mdefine_line|#define IOC4_INT_OUT_DIAG&t;        0x40000000 /* Diag mode */
mdefine_line|#define IOC4_INT_OUT_INT_OUT            0x80000000 /* Current state of INT_OUT */
multiline_comment|/* Time constants for IOC4_INT_OUT */
mdefine_line|#define IOC4_INT_OUT_NS_PER_TICK        (15 * 520) /* 15 ns PCI clock, multi=520 */
mdefine_line|#define IOC4_INT_OUT_TICKS_PER_PULSE             3 /* Outgoing pulse lasts 3&n;                                                      ticks */
mdefine_line|#define IOC4_INT_OUT_US_TO_COUNT(x)&t;           /* Convert uS to a count value */ &bslash;&n;&t;(((x) * 10 + IOC4_INT_OUT_NS_PER_TICK / 200) *&t;&bslash;&n;&t; 100 / IOC4_INT_OUT_NS_PER_TICK - 1)
mdefine_line|#define IOC4_INT_OUT_COUNT_TO_US(x)&t;           /* Convert count value to uS */ &bslash;&n;&t;(((x) + 1) * IOC4_INT_OUT_NS_PER_TICK / 1000)
mdefine_line|#define IOC4_INT_OUT_MIN_TICKS                   3 /* Min period is width of&n;                                                      pulse in &quot;ticks&quot; */
mdefine_line|#define IOC4_INT_OUT_MAX_TICKS  IOC4_INT_OUT_COUNT /* Largest possible count */
multiline_comment|/* Bitmasks for IOC4_GPCR */
mdefine_line|#define IOC4_GPCR_DIR&t;                0x000000ff /* Tristate pin in or out */
mdefine_line|#define IOC4_GPCR_DIR_PIN(x)              (1&lt;&lt;(x)) /* Access one of the DIR bits */
mdefine_line|#define IOC4_GPCR_EDGE&t;                0x0000ff00 /* Extint edge or level&n;                                                      sensitive */
mdefine_line|#define IOC4_GPCR_EDGE_PIN(x)        (1&lt;&lt;((x)+7 )) /* Access one of the EDGE bits */
multiline_comment|/* Values for IOC4_GPCR */
mdefine_line|#define IOC4_GPCR_INT_OUT_EN            0x00100000 /* Enable INT_OUT to pin 0 */
mdefine_line|#define IOC4_GPCR_DIR_SER0_XCVR         0x00000010 /* Port 0 Transceiver select&n;                                                      enable */
mdefine_line|#define IOC4_GPCR_DIR_SER1_XCVR         0x00000020 /* Port 1 Transceiver select&n;                                                      enable */
mdefine_line|#define IOC4_GPCR_DIR_SER2_XCVR         0x00000040 /* Port 2 Transceiver select&n;                                                      enable */
mdefine_line|#define IOC4_GPCR_DIR_SER3_XCVR         0x00000080 /* Port 3 Transceiver select&n;                                                      enable */
multiline_comment|/* Defs for some of the generic I/O pins */
mdefine_line|#define IOC4_GPCR_UART0_MODESEL&t;              0x10 /* Pin is output to port 0&n;                                                      mode sel */
mdefine_line|#define IOC4_GPCR_UART1_MODESEL&t;              0x20 /* Pin is output to port 1&n;                                                      mode sel */
mdefine_line|#define IOC4_GPCR_UART2_MODESEL&t;              0x40 /* Pin is output to port 2&n;                                                      mode sel */
mdefine_line|#define IOC4_GPCR_UART3_MODESEL&t;              0x80 /* Pin is output to port 3&n;                                                      mode sel */
mdefine_line|#define IOC4_GPPR_UART0_MODESEL_PIN&t;         4 /* GIO pin controlling&n;                                                      uart 0 mode select */
mdefine_line|#define IOC4_GPPR_UART1_MODESEL_PIN&t;         5 /* GIO pin controlling&n;                                                      uart 1 mode select */
mdefine_line|#define IOC4_GPPR_UART2_MODESEL_PIN&t;         6 /* GIO pin controlling&n;                                                      uart 2 mode select */
mdefine_line|#define IOC4_GPPR_UART3_MODESEL_PIN&t;         7 /* GIO pin controlling&n;                                                      uart 3 mode select */
multiline_comment|/* Bitmasks for IOC4_ATA_TIMING */
mdefine_line|#define IOC4_ATA_TIMING_ADR_SETUP&t;0x00000003 /* Clocks of addr set-up */
mdefine_line|#define IOC4_ATA_TIMING_PULSE_WIDTH&t;0x000001f8 /* Clocks of read or write&n;                                                      pulse width */
mdefine_line|#define IOC4_ATA_TIMING_RECOVERY&t;0x0000fe00 /* Clocks before next read&n;                                                      or write */
mdefine_line|#define IOC4_ATA_TIMING_USE_IORDY&t;0x00010000 /* PIO uses IORDY */
multiline_comment|/* Bitmasks for address list elements pointed to by IOC4_ATA_DMA_PTR_&lt;L|H&gt; */
mdefine_line|#define IOC4_ATA_ALE_DMA_ADDRESS        0xfffffffffffffffe
multiline_comment|/* Bitmasks for byte count list elements pointed to by IOC4_ATA_DMA_PTR_&lt;L|H&gt; */
mdefine_line|#define IOC4_ATA_BCLE_BYTE_COUNT        0x000000000000fffe
mdefine_line|#define IOC4_ATA_BCLE_LIST_END          0x0000000080000000
multiline_comment|/* Bitmasks for IOC4_ATA_BC_&lt;DEV|MEM&gt; */
mdefine_line|#define IOC4_ATA_BC_BYTE_CNT            0x0001fffe /* Byte count */
multiline_comment|/* Bitmasks for IOC4_ATA_DMA_CTRL */
mdefine_line|#define IOC4_ATA_DMA_CTRL_STRAT&t;&t;0x00000001 /* 1 -&gt; start DMA engine */
mdefine_line|#define IOC4_ATA_DMA_CTRL_STOP&t;&t;0x00000002 /* 1 -&gt; stop DMA engine */
mdefine_line|#define IOC4_ATA_DMA_CTRL_DIR&t;&t;0x00000004 /* 1 -&gt; ATA bus data copied&n;                                                      to memory */
mdefine_line|#define IOC4_ATA_DMA_CTRL_ACTIVE&t;0x00000008 /* DMA channel is active */
mdefine_line|#define IOC4_ATA_DMA_CTRL_MEM_ERROR&t;0x00000010 /* DMA engine encountered &n;&t;&t;&t;&t;&t;&t;      a PCI error */
multiline_comment|/* Bitmasks for IOC4_KM_CSR */
mdefine_line|#define IOC4_KM_CSR_K_WRT_PEND  0x00000001 /* Kbd port xmitting or resetting */
mdefine_line|#define IOC4_KM_CSR_M_WRT_PEND  0x00000002 /* Mouse port xmitting or resetting */
mdefine_line|#define IOC4_KM_CSR_K_LCB       0x00000004 /* Line Cntrl Bit for last KBD write */
mdefine_line|#define IOC4_KM_CSR_M_LCB       0x00000008 /* Same for mouse */
mdefine_line|#define IOC4_KM_CSR_K_DATA      0x00000010 /* State of kbd data line */
mdefine_line|#define IOC4_KM_CSR_K_CLK       0x00000020 /* State of kbd clock line */
mdefine_line|#define IOC4_KM_CSR_K_PULL_DATA 0x00000040 /* Pull kbd data line low */
mdefine_line|#define IOC4_KM_CSR_K_PULL_CLK  0x00000080 /* Pull kbd clock line low */
mdefine_line|#define IOC4_KM_CSR_M_DATA      0x00000100 /* State of mouse data line */
mdefine_line|#define IOC4_KM_CSR_M_CLK       0x00000200 /* State of mouse clock line */
mdefine_line|#define IOC4_KM_CSR_M_PULL_DATA 0x00000400 /* Pull mouse data line low */
mdefine_line|#define IOC4_KM_CSR_M_PULL_CLK  0x00000800 /* Pull mouse clock line low */
mdefine_line|#define IOC4_KM_CSR_EMM_MODE&t;0x00001000 /* Emulation mode */
mdefine_line|#define IOC4_KM_CSR_SIM_MODE&t;0x00002000 /* Clock X8 */
mdefine_line|#define IOC4_KM_CSR_K_SM_IDLE   0x00004000 /* Keyboard is idle */
mdefine_line|#define IOC4_KM_CSR_M_SM_IDLE   0x00008000 /* Mouse is idle */
mdefine_line|#define IOC4_KM_CSR_K_TO&t;0x00010000 /* Keyboard trying to send/receive */
mdefine_line|#define IOC4_KM_CSR_M_TO        0x00020000 /* Mouse trying to send/receive */
mdefine_line|#define IOC4_KM_CSR_K_TO_EN     0x00040000 /* KM_CSR_K_TO + KM_CSR_K_TO_EN =&n;                                              cause SIO_IR to assert */
mdefine_line|#define IOC4_KM_CSR_M_TO_EN&t;0x00080000 /* KM_CSR_M_TO + KM_CSR_M_TO_EN =&n;                                              cause SIO_IR to assert */
mdefine_line|#define IOC4_KM_CSR_K_CLAMP_ONE&t;0x00100000 /* Pull K_CLK low after rec. one char */
mdefine_line|#define IOC4_KM_CSR_M_CLAMP_ONE&t;0x00200000 /* Pull M_CLK low after rec. one char */
mdefine_line|#define IOC4_KM_CSR_K_CLAMP_THREE &bslash;&n;                           &t;0x00400000 /* Pull K_CLK low after rec. three chars */
mdefine_line|#define IOC4_KM_CSR_M_CLAMP_THREE &bslash;&n;                            &t;0x00800000 /* Pull M_CLK low after rec. three char */
multiline_comment|/* Bitmasks for IOC4_K_RD and IOC4_M_RD */
mdefine_line|#define IOC4_KM_RD_DATA_2       0x000000ff /* 3rd char recvd since last read */
mdefine_line|#define IOC4_KM_RD_DATA_2_SHIFT          0
mdefine_line|#define IOC4_KM_RD_DATA_1       0x0000ff00 /* 2nd char recvd since last read */
mdefine_line|#define IOC4_KM_RD_DATA_1_SHIFT          8
mdefine_line|#define IOC4_KM_RD_DATA_0&t;0x00ff0000 /* 1st char recvd since last read */
mdefine_line|#define IOC4_KM_RD_DATA_0_SHIFT         16
mdefine_line|#define IOC4_KM_RD_FRAME_ERR_2  0x01000000 /* Framing or parity error in byte 2 */
mdefine_line|#define IOC4_KM_RD_FRAME_ERR_1  0x02000000 /* Same for byte 1 */
mdefine_line|#define IOC4_KM_RD_FRAME_ERR_0  0x04000000 /* Same for byte 0 */
mdefine_line|#define IOC4_KM_RD_KBD_MSE      0x08000000 /* 0 if from kbd, 1 if from mouse */
mdefine_line|#define IOC4_KM_RD_OFLO&t;        0x10000000 /* 4th char recvd before this read */
mdefine_line|#define IOC4_KM_RD_VALID_2      0x20000000 /* DATA_2 valid */
mdefine_line|#define IOC4_KM_RD_VALID_1      0x40000000 /* DATA_1 valid */
mdefine_line|#define IOC4_KM_RD_VALID_0      0x80000000 /* DATA_0 valid */
mdefine_line|#define IOC4_KM_RD_VALID_ALL    (IOC4_KM_RD_VALID_0 | IOC4_KM_RD_VALID_1 | &bslash;&n;                                 IOC4_KM_RD_VALID_2)
multiline_comment|/* Bitmasks for IOC4_K_WD &amp; IOC4_M_WD */
mdefine_line|#define IOC4_KM_WD_WRT_DATA     0x000000ff /* Write to keyboard/mouse port */
mdefine_line|#define IOC4_KM_WD_WRT_DATA_SHIFT        0
multiline_comment|/* Bitmasks for serial RX status byte */
mdefine_line|#define IOC4_RXSB_OVERRUN       0x01       /* Char(s) lost */
mdefine_line|#define IOC4_RXSB_PAR_ERR&t;0x02&t;   /* Parity error */
mdefine_line|#define IOC4_RXSB_FRAME_ERR&t;0x04&t;   /* Framing error */
mdefine_line|#define IOC4_RXSB_BREAK&t;        0x08&t;   /* Break character */
mdefine_line|#define IOC4_RXSB_CTS&t;        0x10&t;   /* State of CTS */
mdefine_line|#define IOC4_RXSB_DCD&t;        0x20&t;   /* State of DCD */
mdefine_line|#define IOC4_RXSB_MODEM_VALID   0x40&t;   /* DCD, CTS, and OVERRUN are valid */
mdefine_line|#define IOC4_RXSB_DATA_VALID    0x80&t;   /* Data byte, FRAME_ERR PAR_ERR &amp; BREAK valid */
multiline_comment|/* Bitmasks for serial TX control byte */
mdefine_line|#define IOC4_TXCB_INT_WHEN_DONE 0x20       /* Interrupt after this byte is sent */
mdefine_line|#define IOC4_TXCB_INVALID&t;0x00&t;   /* Byte is invalid */
mdefine_line|#define IOC4_TXCB_VALID&t;        0x40&t;   /* Byte is valid */
mdefine_line|#define IOC4_TXCB_MCR&t;        0x80&t;   /* Data&lt;7:0&gt; to modem control register */
mdefine_line|#define IOC4_TXCB_DELAY&t;        0xc0&t;   /* Delay data&lt;7:0&gt; mSec */
multiline_comment|/* Bitmasks for IOC4_SBBR_L */
mdefine_line|#define IOC4_SBBR_L_SIZE&t;0x00000001 /* 0 == 1KB rings, 1 == 4KB rings */
mdefine_line|#define IOC4_SBBR_L_BASE&t;0xfffff000 /* Lower serial ring base addr */
multiline_comment|/* Bitmasks for IOC4_SSCR_&lt;3:0&gt; */
mdefine_line|#define IOC4_SSCR_RX_THRESHOLD  0x000001ff /* Hiwater mark */
mdefine_line|#define IOC4_SSCR_TX_TIMER_BUSY 0x00010000 /* TX timer in progress */
mdefine_line|#define IOC4_SSCR_HFC_EN&t;0x00020000 /* Hardware flow control enabled */
mdefine_line|#define IOC4_SSCR_RX_RING_DCD   0x00040000 /* Post RX record on delta-DCD */
mdefine_line|#define IOC4_SSCR_RX_RING_CTS   0x00080000 /* Post RX record on delta-CTS */
mdefine_line|#define IOC4_SSCR_DIAG&t;        0x00200000 /* Bypass clock divider for sim */
mdefine_line|#define IOC4_SSCR_RX_DRAIN&t;0x08000000 /* Drain RX buffer to memory */
mdefine_line|#define IOC4_SSCR_DMA_EN&t;0x10000000 /* Enable ring buffer DMA */
mdefine_line|#define IOC4_SSCR_DMA_PAUSE&t;0x20000000 /* Pause DMA */
mdefine_line|#define IOC4_SSCR_PAUSE_STATE   0x40000000 /* Sets when PAUSE takes effect */
mdefine_line|#define IOC4_SSCR_RESET&t;        0x80000000 /* Reset DMA channels */
multiline_comment|/* All producer/comsumer pointers are the same bitfield */
mdefine_line|#define IOC4_PROD_CONS_PTR_4K   0x00000ff8 /* For 4K buffers */
mdefine_line|#define IOC4_PROD_CONS_PTR_1K   0x000003f8 /* For 1K buffers */
mdefine_line|#define IOC4_PROD_CONS_PTR_OFF           3
multiline_comment|/* Bitmasks for IOC4_STPIR_&lt;3:0&gt; */
multiline_comment|/* Reserved for future register definitions */
multiline_comment|/* Bitmasks for IOC4_STCIR_&lt;3:0&gt; */
mdefine_line|#define IOC4_STCIR_BYTE_CNT     0x0f000000 /* Bytes in unpacker */
mdefine_line|#define IOC4_STCIR_BYTE_CNT_SHIFT       24
multiline_comment|/* Bitmasks for IOC4_SRPIR_&lt;3:0&gt; */
mdefine_line|#define IOC4_SRPIR_BYTE_CNT&t;0x0f000000 /* Bytes in packer */
mdefine_line|#define IOC4_SRPIR_BYTE_CNT_SHIFT       24
multiline_comment|/* Bitmasks for IOC4_SRCIR_&lt;3:0&gt; */
mdefine_line|#define IOC4_SRCIR_ARM&t;        0x80000000 /* Arm RX timer */
multiline_comment|/* Bitmasks for IOC4_SHADOW_&lt;3:0&gt; */
mdefine_line|#define IOC4_SHADOW_DR          0x00000001  /* Data ready */
mdefine_line|#define IOC4_SHADOW_OE          0x00000002  /* Overrun error */
mdefine_line|#define IOC4_SHADOW_PE          0x00000004  /* Parity error */
mdefine_line|#define IOC4_SHADOW_FE          0x00000008  /* Framing error */
mdefine_line|#define IOC4_SHADOW_BI          0x00000010  /* Break interrupt */
mdefine_line|#define IOC4_SHADOW_THRE        0x00000020  /* Xmit holding register empty */
mdefine_line|#define IOC4_SHADOW_TEMT        0x00000040  /* Xmit shift register empty */
mdefine_line|#define IOC4_SHADOW_RFCE        0x00000080  /* Char in RX fifo has an error */
mdefine_line|#define IOC4_SHADOW_DCTS        0x00010000  /* Delta clear to send */
mdefine_line|#define IOC4_SHADOW_DDCD        0x00080000  /* Delta data carrier detect */
mdefine_line|#define IOC4_SHADOW_CTS         0x00100000  /* Clear to send */
mdefine_line|#define IOC4_SHADOW_DCD         0x00800000  /* Data carrier detect */
mdefine_line|#define IOC4_SHADOW_DTR         0x01000000  /* Data terminal ready */
mdefine_line|#define IOC4_SHADOW_RTS         0x02000000  /* Request to send */
mdefine_line|#define IOC4_SHADOW_OUT1        0x04000000  /* 16550 OUT1 bit */
mdefine_line|#define IOC4_SHADOW_OUT2        0x08000000  /* 16550 OUT2 bit */
mdefine_line|#define IOC4_SHADOW_LOOP        0x10000000  /* Loopback enabled */
multiline_comment|/* Bitmasks for IOC4_SRTR_&lt;3:0&gt; */
mdefine_line|#define IOC4_SRTR_CNT&t;        0x00000fff /* Reload value for RX timer */
mdefine_line|#define IOC4_SRTR_CNT_VAL&t;0x0fff0000 /* Current value of RX timer */
mdefine_line|#define IOC4_SRTR_CNT_VAL_SHIFT         16
mdefine_line|#define IOC4_SRTR_HZ                 16000 /* SRTR clock frequency */
multiline_comment|/* Serial port register map used for DMA and PIO serial I/O */
r_typedef
r_volatile
r_struct
id|ioc4_serialregs
(brace
id|ioc4reg_t
id|sscr
suffix:semicolon
id|ioc4reg_t
id|stpir
suffix:semicolon
id|ioc4reg_t
id|stcir
suffix:semicolon
id|ioc4reg_t
id|srpir
suffix:semicolon
id|ioc4reg_t
id|srcir
suffix:semicolon
id|ioc4reg_t
id|srtr
suffix:semicolon
id|ioc4reg_t
id|shadow
suffix:semicolon
)brace
id|ioc4_sregs_t
suffix:semicolon
multiline_comment|/* IOC4 UART register map */
r_typedef
r_volatile
r_struct
id|ioc4_uartregs
(brace
r_union
(brace
r_char
id|rbr
suffix:semicolon
multiline_comment|/* read only, DLAB == 0 */
r_char
id|thr
suffix:semicolon
multiline_comment|/* write only, DLAB == 0 */
r_char
id|dll
suffix:semicolon
multiline_comment|/* DLAB == 1 */
)brace
id|u1
suffix:semicolon
r_union
(brace
r_char
id|ier
suffix:semicolon
multiline_comment|/* DLAB == 0 */
r_char
id|dlm
suffix:semicolon
multiline_comment|/* DLAB == 1 */
)brace
id|u2
suffix:semicolon
r_union
(brace
r_char
id|iir
suffix:semicolon
multiline_comment|/* read only */
r_char
id|fcr
suffix:semicolon
multiline_comment|/* write only */
)brace
id|u3
suffix:semicolon
r_char
id|i4u_lcr
suffix:semicolon
r_char
id|i4u_mcr
suffix:semicolon
r_char
id|i4u_lsr
suffix:semicolon
r_char
id|i4u_msr
suffix:semicolon
r_char
id|i4u_scr
suffix:semicolon
)brace
id|ioc4_uart_t
suffix:semicolon
mdefine_line|#define i4u_rbr u1.rbr
mdefine_line|#define i4u_thr u1.thr
mdefine_line|#define i4u_dll u1.dll
mdefine_line|#define i4u_ier u2.ier
mdefine_line|#define i4u_dlm u2.dlm
mdefine_line|#define i4u_iir u3.iir
mdefine_line|#define i4u_fcr u3.fcr
multiline_comment|/* PCI config space register map */
r_typedef
r_volatile
r_struct
id|ioc4_configregs
(brace
id|ioc4reg_t
id|pci_id
suffix:semicolon
id|ioc4reg_t
id|pci_scr
suffix:semicolon
id|ioc4reg_t
id|pci_rev
suffix:semicolon
id|ioc4reg_t
id|pci_lat
suffix:semicolon
id|ioc4reg_t
id|pci_bar0
suffix:semicolon
id|ioc4reg_t
id|pci_bar1
suffix:semicolon
id|ioc4reg_t
id|pci_bar2_not_implemented
suffix:semicolon
id|ioc4reg_t
id|pci_cis_ptr_not_implemented
suffix:semicolon
id|ioc4reg_t
id|pci_sidv
suffix:semicolon
id|ioc4reg_t
id|pci_rom_bar_not_implemented
suffix:semicolon
id|ioc4reg_t
id|pci_cap
suffix:semicolon
id|ioc4reg_t
id|pci_rsv
suffix:semicolon
id|ioc4reg_t
id|pci_latgntint
suffix:semicolon
r_char
id|pci_fill1
(braket
l_int|0x58
op_minus
l_int|0x3c
op_minus
l_int|4
)braket
suffix:semicolon
id|ioc4reg_t
id|pci_pcix
suffix:semicolon
id|ioc4reg_t
id|pci_pcixstatus
suffix:semicolon
)brace
id|ioc4_cfg_t
suffix:semicolon
multiline_comment|/* PCI memory space register map addressed using pci_bar0 */
r_typedef
r_volatile
r_struct
id|ioc4_memregs
(brace
multiline_comment|/* Miscellaneous IOC4  registers */
id|ioc4reg_t
id|pci_err_addr_l
suffix:semicolon
id|ioc4reg_t
id|pci_err_addr_h
suffix:semicolon
id|ioc4reg_t
id|sio_ir
suffix:semicolon
id|ioc4reg_t
id|other_ir
suffix:semicolon
multiline_comment|/* These registers are read-only for general kernel code.  To&n;     * modify them use the functions in ioc4.c.&n;     */
id|ioc4reg_t
id|sio_ies_ro
suffix:semicolon
id|ioc4reg_t
id|other_ies_ro
suffix:semicolon
id|ioc4reg_t
id|sio_iec_ro
suffix:semicolon
id|ioc4reg_t
id|other_iec_ro
suffix:semicolon
id|ioc4reg_t
id|sio_cr
suffix:semicolon
id|ioc4reg_t
id|misc_fill1
suffix:semicolon
id|ioc4reg_t
id|int_out
suffix:semicolon
id|ioc4reg_t
id|misc_fill2
suffix:semicolon
id|ioc4reg_t
id|gpcr_s
suffix:semicolon
id|ioc4reg_t
id|gpcr_c
suffix:semicolon
id|ioc4reg_t
id|gpdr
suffix:semicolon
id|ioc4reg_t
id|misc_fill3
suffix:semicolon
id|ioc4reg_t
id|gppr_0
suffix:semicolon
id|ioc4reg_t
id|gppr_1
suffix:semicolon
id|ioc4reg_t
id|gppr_2
suffix:semicolon
id|ioc4reg_t
id|gppr_3
suffix:semicolon
id|ioc4reg_t
id|gppr_4
suffix:semicolon
id|ioc4reg_t
id|gppr_5
suffix:semicolon
id|ioc4reg_t
id|gppr_6
suffix:semicolon
id|ioc4reg_t
id|gppr_7
suffix:semicolon
r_char
id|misc_fill4
(braket
l_int|0x100
op_minus
l_int|0x5C
op_minus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ATA/ATAP registers */
id|ioc4reg_t
id|ata_0
suffix:semicolon
id|ioc4reg_t
id|ata_1
suffix:semicolon
id|ioc4reg_t
id|ata_2
suffix:semicolon
id|ioc4reg_t
id|ata_3
suffix:semicolon
id|ioc4reg_t
id|ata_4
suffix:semicolon
id|ioc4reg_t
id|ata_5
suffix:semicolon
id|ioc4reg_t
id|ata_6
suffix:semicolon
id|ioc4reg_t
id|ata_7
suffix:semicolon
id|ioc4reg_t
id|ata_aux
suffix:semicolon
r_char
id|ata_fill1
(braket
l_int|0x140
op_minus
l_int|0x120
op_minus
l_int|4
)braket
suffix:semicolon
id|ioc4reg_t
id|ata_timing
suffix:semicolon
id|ioc4reg_t
id|ata_dma_ptr_l
suffix:semicolon
id|ioc4reg_t
id|ata_dma_ptr_h
suffix:semicolon
id|ioc4reg_t
id|ata_dma_addr_l
suffix:semicolon
id|ioc4reg_t
id|ata_dma_addr_h
suffix:semicolon
id|ioc4reg_t
id|ata_bc_dev
suffix:semicolon
id|ioc4reg_t
id|ata_bc_mem
suffix:semicolon
id|ioc4reg_t
id|ata_dma_ctrl
suffix:semicolon
r_char
id|ata_fill2
(braket
l_int|0x200
op_minus
l_int|0x15C
op_minus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Keyboard and mouse registers */
id|ioc4reg_t
id|km_csr
suffix:semicolon
id|ioc4reg_t
id|k_rd
suffix:semicolon
id|ioc4reg_t
id|m_rd
suffix:semicolon
id|ioc4reg_t
id|k_wd
suffix:semicolon
id|ioc4reg_t
id|m_wd
suffix:semicolon
r_char
id|km_fill1
(braket
l_int|0x300
op_minus
l_int|0x210
op_minus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Serial port registers used for DMA serial I/O */
id|ioc4reg_t
id|sbbr01_l
suffix:semicolon
id|ioc4reg_t
id|sbbr01_h
suffix:semicolon
id|ioc4reg_t
id|sbbr23_l
suffix:semicolon
id|ioc4reg_t
id|sbbr23_h
suffix:semicolon
id|ioc4_sregs_t
id|port_0
suffix:semicolon
id|ioc4_sregs_t
id|port_1
suffix:semicolon
id|ioc4_sregs_t
id|port_2
suffix:semicolon
id|ioc4_sregs_t
id|port_3
suffix:semicolon
id|ioc4_uart_t
id|uart_0
suffix:semicolon
id|ioc4_uart_t
id|uart_1
suffix:semicolon
id|ioc4_uart_t
id|uart_2
suffix:semicolon
id|ioc4_uart_t
id|uart_3
suffix:semicolon
)brace
id|ioc4_mem_t
suffix:semicolon
macro_line|#endif&t;/* 0 */
multiline_comment|/*&n; * Bytebus device space&n; */
DECL|macro|IOC4_BYTEBUS_DEV0
mdefine_line|#define IOC4_BYTEBUS_DEV0&t;0x80000L  /* Addressed using pci_bar0 */ 
DECL|macro|IOC4_BYTEBUS_DEV1
mdefine_line|#define IOC4_BYTEBUS_DEV1&t;0xA0000L  /* Addressed using pci_bar0 */
DECL|macro|IOC4_BYTEBUS_DEV2
mdefine_line|#define IOC4_BYTEBUS_DEV2&t;0xC0000L  /* Addressed using pci_bar0 */
DECL|macro|IOC4_BYTEBUS_DEV3
mdefine_line|#define IOC4_BYTEBUS_DEV3&t;0xE0000L  /* Addressed using pci_bar0 */
macro_line|#if 0
multiline_comment|/* UART clock speed */
mdefine_line|#define IOC4_SER_XIN_CLK        66000000
r_typedef
r_enum
id|ioc4_subdevs_e
(brace
id|ioc4_subdev_generic
comma
id|ioc4_subdev_kbms
comma
id|ioc4_subdev_tty0
comma
id|ioc4_subdev_tty1
comma
id|ioc4_subdev_tty2
comma
id|ioc4_subdev_tty3
comma
id|ioc4_subdev_rt
comma
id|ioc4_nsubdevs
)brace
id|ioc4_subdev_t
suffix:semicolon
multiline_comment|/* Subdevice disable bits,&n; * from the standard INFO_LBL_SUBDEVS&n; */
mdefine_line|#define IOC4_SDB_TTY0&t;&t;(1 &lt;&lt; ioc4_subdev_tty0)
mdefine_line|#define IOC4_SDB_TTY1&t;&t;(1 &lt;&lt; ioc4_subdev_tty1)
mdefine_line|#define IOC4_SDB_TTY2&t;&t;(1 &lt;&lt; ioc4_subdev_tty2)
mdefine_line|#define IOC4_SDB_TTY3&t;&t;(1 &lt;&lt; ioc4_subdev_tty3)
mdefine_line|#define IOC4_SDB_KBMS&t;&t;(1 &lt;&lt; ioc4_subdev_kbms)
mdefine_line|#define IOC4_SDB_RT&t;&t;(1 &lt;&lt; ioc4_subdev_rt)
mdefine_line|#define IOC4_SDB_GENERIC&t;(1 &lt;&lt; ioc4_subdev_generic)
mdefine_line|#define IOC4_ALL_SUBDEVS&t;((1 &lt;&lt; ioc4_nsubdevs) - 1)
mdefine_line|#define IOC4_SDB_SERIAL&t;&t;(IOC4_SDB_TTY0 | IOC4_SDB_TTY1 | IOC4_SDB_TTY2 | IOC4_SDB_TTY3)
mdefine_line|#define IOC4_STD_SUBDEVS&t;IOC4_ALL_SUBDEVS
mdefine_line|#define IOC4_INTA_SUBDEVS&t;(IOC4_SDB_SERIAL | IOC4_SDB_KBMS | IOC4_SDB_RT | IOC4_SDB_GENERIC)
r_extern
r_int
id|ioc4_subdev_enabled
c_func
(paren
id|vertex_hdl_t
comma
id|ioc4_subdev_t
)paren
suffix:semicolon
r_extern
r_void
id|ioc4_subdev_enables
c_func
(paren
id|vertex_hdl_t
comma
id|ulong_t
)paren
suffix:semicolon
r_extern
r_void
id|ioc4_subdev_enable
c_func
(paren
id|vertex_hdl_t
comma
id|ioc4_subdev_t
)paren
suffix:semicolon
r_extern
r_void
id|ioc4_subdev_disable
c_func
(paren
id|vertex_hdl_t
comma
id|ioc4_subdev_t
)paren
suffix:semicolon
multiline_comment|/* Macros to read and write the SIO_IEC and SIO_IES registers (see the&n; * comments in ioc4.c for details on why this is necessary&n; */
mdefine_line|#define IOC4_W_IES&t;0
mdefine_line|#define IOC4_W_IEC&t;1
r_extern
r_void
id|ioc4_write_ireg
c_func
(paren
r_void
op_star
comma
id|ioc4reg_t
comma
r_int
comma
id|ioc4_intr_type_t
)paren
suffix:semicolon
mdefine_line|#define IOC4_WRITE_IES(ioc4, val, type)&t;ioc4_write_ireg(ioc4, val, IOC4_W_IES, type)
mdefine_line|#define IOC4_WRITE_IEC(ioc4, val, type)&t;ioc4_write_ireg(ioc4, val, IOC4_W_IEC, type)
r_typedef
r_void
id|ioc4_intr_func_f
(paren
id|intr_arg_t
comma
id|ioc4reg_t
)paren
suffix:semicolon
r_typedef
r_void
id|ioc4_intr_connect_f
(paren
id|vertex_hdl_t
id|conn_vhdl
comma
id|ioc4_intr_type_t
comma
id|ioc4reg_t
comma
id|ioc4_intr_func_f
op_star
comma
id|intr_arg_t
id|info
comma
id|vertex_hdl_t
id|owner_vhdl
comma
id|vertex_hdl_t
id|intr_dev_vhdl
comma
r_int
(paren
op_star
)paren
(paren
id|intr_arg_t
)paren
)paren
suffix:semicolon
r_typedef
r_void
id|ioc4_intr_disconnect_f
(paren
id|vertex_hdl_t
id|conn_vhdl
comma
id|ioc4_intr_type_t
comma
id|ioc4reg_t
comma
id|ioc4_intr_func_f
op_star
comma
id|intr_arg_t
id|info
comma
id|vertex_hdl_t
id|owner_vhdl
)paren
suffix:semicolon
id|ioc4_intr_disconnect_f
id|ioc4_intr_disconnect
suffix:semicolon
id|ioc4_intr_connect_f
id|ioc4_intr_connect
suffix:semicolon
r_extern
r_int
id|ioc4_is_console
c_func
(paren
id|vertex_hdl_t
id|conn_vhdl
)paren
suffix:semicolon
r_extern
r_void
id|ioc4_mlreset
c_func
(paren
id|ioc4_cfg_t
op_star
comma
id|ioc4_mem_t
op_star
)paren
suffix:semicolon
r_extern
id|intr_func_f
id|ioc4_intr
suffix:semicolon
r_extern
id|ioc4_mem_t
op_star
id|ioc4_mem_ptr
c_func
(paren
r_void
op_star
id|ioc4_fastinfo
)paren
suffix:semicolon
r_typedef
id|ioc4_intr_func_f
op_star
id|ioc4_intr_func_t
suffix:semicolon
macro_line|#endif&t;/* 0 */
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_IOC4_H */
eof
