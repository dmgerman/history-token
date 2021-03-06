multiline_comment|/*&n; * Copyright (C) 2000, 2004, 2005  MIPS Technologies, Inc.&n; *&t;All rights reserved.&n; *&t;Authors: Carsten Langgaard &lt;carstenl@mips.com&gt;&n; *&t;&t; Maciej W. Rozycki &lt;macro@mips.com&gt;&n; * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; */
macro_line|#ifndef _ASM_GT64120_H
DECL|macro|_ASM_GT64120_H
mdefine_line|#define _ASM_GT64120_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|MSK
mdefine_line|#define MSK(n)&t;&t;&t;((1 &lt;&lt; (n)) - 1)
multiline_comment|/*&n; *  Register offset addresses&n; */
multiline_comment|/* CPU Configuration.  */
DECL|macro|GT_CPU_OFS
mdefine_line|#define GT_CPU_OFS&t;&t;0x000
DECL|macro|GT_MULTI_OFS
mdefine_line|#define GT_MULTI_OFS&t;&t;0x120
multiline_comment|/* CPU Address Decode.  */
DECL|macro|GT_SCS10LD_OFS
mdefine_line|#define GT_SCS10LD_OFS&t;&t;0x008
DECL|macro|GT_SCS10HD_OFS
mdefine_line|#define GT_SCS10HD_OFS&t;&t;0x010
DECL|macro|GT_SCS32LD_OFS
mdefine_line|#define GT_SCS32LD_OFS&t;&t;0x018
DECL|macro|GT_SCS32HD_OFS
mdefine_line|#define GT_SCS32HD_OFS&t;&t;0x020
DECL|macro|GT_CS20LD_OFS
mdefine_line|#define GT_CS20LD_OFS&t;&t;0x028
DECL|macro|GT_CS20HD_OFS
mdefine_line|#define GT_CS20HD_OFS&t;&t;0x030
DECL|macro|GT_CS3BOOTLD_OFS
mdefine_line|#define GT_CS3BOOTLD_OFS&t;0x038
DECL|macro|GT_CS3BOOTHD_OFS
mdefine_line|#define GT_CS3BOOTHD_OFS&t;0x040
DECL|macro|GT_PCI0IOLD_OFS
mdefine_line|#define GT_PCI0IOLD_OFS&t;&t;0x048
DECL|macro|GT_PCI0IOHD_OFS
mdefine_line|#define GT_PCI0IOHD_OFS&t;&t;0x050
DECL|macro|GT_PCI0M0LD_OFS
mdefine_line|#define GT_PCI0M0LD_OFS&t;&t;0x058
DECL|macro|GT_PCI0M0HD_OFS
mdefine_line|#define GT_PCI0M0HD_OFS&t;&t;0x060
DECL|macro|GT_ISD_OFS
mdefine_line|#define GT_ISD_OFS&t;&t;0x068
DECL|macro|GT_PCI0M1LD_OFS
mdefine_line|#define GT_PCI0M1LD_OFS&t;&t;0x080
DECL|macro|GT_PCI0M1HD_OFS
mdefine_line|#define GT_PCI0M1HD_OFS&t;&t;0x088
DECL|macro|GT_PCI1IOLD_OFS
mdefine_line|#define GT_PCI1IOLD_OFS&t;&t;0x090
DECL|macro|GT_PCI1IOHD_OFS
mdefine_line|#define GT_PCI1IOHD_OFS&t;&t;0x098
DECL|macro|GT_PCI1M0LD_OFS
mdefine_line|#define GT_PCI1M0LD_OFS&t;&t;0x0a0
DECL|macro|GT_PCI1M0HD_OFS
mdefine_line|#define GT_PCI1M0HD_OFS&t;&t;0x0a8
DECL|macro|GT_PCI1M1LD_OFS
mdefine_line|#define GT_PCI1M1LD_OFS&t;&t;0x0b0
DECL|macro|GT_PCI1M1HD_OFS
mdefine_line|#define GT_PCI1M1HD_OFS&t;&t;0x0b8
DECL|macro|GT_PCI1M1LD_OFS
mdefine_line|#define GT_PCI1M1LD_OFS&t;&t;0x0b0
DECL|macro|GT_PCI1M1HD_OFS
mdefine_line|#define GT_PCI1M1HD_OFS&t;&t;0x0b8
DECL|macro|GT_SCS10AR_OFS
mdefine_line|#define GT_SCS10AR_OFS&t;&t;0x0d0
DECL|macro|GT_SCS32AR_OFS
mdefine_line|#define GT_SCS32AR_OFS&t;&t;0x0d8
DECL|macro|GT_CS20R_OFS
mdefine_line|#define GT_CS20R_OFS&t;&t;0x0e0
DECL|macro|GT_CS3BOOTR_OFS
mdefine_line|#define GT_CS3BOOTR_OFS&t;&t;0x0e8
DECL|macro|GT_PCI0IOREMAP_OFS
mdefine_line|#define GT_PCI0IOREMAP_OFS&t;0x0f0
DECL|macro|GT_PCI0M0REMAP_OFS
mdefine_line|#define GT_PCI0M0REMAP_OFS&t;0x0f8
DECL|macro|GT_PCI0M1REMAP_OFS
mdefine_line|#define GT_PCI0M1REMAP_OFS&t;0x100
DECL|macro|GT_PCI1IOREMAP_OFS
mdefine_line|#define GT_PCI1IOREMAP_OFS&t;0x108
DECL|macro|GT_PCI1M0REMAP_OFS
mdefine_line|#define GT_PCI1M0REMAP_OFS&t;0x110
DECL|macro|GT_PCI1M1REMAP_OFS
mdefine_line|#define GT_PCI1M1REMAP_OFS&t;0x118
multiline_comment|/* CPU Error Report.  */
DECL|macro|GT_CPUERR_ADDRLO_OFS
mdefine_line|#define GT_CPUERR_ADDRLO_OFS&t;0x070
DECL|macro|GT_CPUERR_ADDRHI_OFS
mdefine_line|#define GT_CPUERR_ADDRHI_OFS&t;0x078
DECL|macro|GT_CPUERR_DATALO_OFS
mdefine_line|#define GT_CPUERR_DATALO_OFS&t;0x128&t;&t;&t;/* GT-64120A only  */
DECL|macro|GT_CPUERR_DATAHI_OFS
mdefine_line|#define GT_CPUERR_DATAHI_OFS&t;0x130&t;&t;&t;/* GT-64120A only  */
DECL|macro|GT_CPUERR_PARITY_OFS
mdefine_line|#define GT_CPUERR_PARITY_OFS&t;0x138&t;&t;&t;/* GT-64120A only  */
multiline_comment|/* CPU Sync Barrier.  */
DECL|macro|GT_PCI0SYNC_OFS
mdefine_line|#define GT_PCI0SYNC_OFS&t;&t;0x0c0
DECL|macro|GT_PCI1SYNC_OFS
mdefine_line|#define GT_PCI1SYNC_OFS&t;&t;0x0c8
multiline_comment|/* SDRAM and Device Address Decode.  */
DECL|macro|GT_SCS0LD_OFS
mdefine_line|#define GT_SCS0LD_OFS&t;&t;0x400
DECL|macro|GT_SCS0HD_OFS
mdefine_line|#define GT_SCS0HD_OFS&t;&t;0x404
DECL|macro|GT_SCS1LD_OFS
mdefine_line|#define GT_SCS1LD_OFS&t;&t;0x408
DECL|macro|GT_SCS1HD_OFS
mdefine_line|#define GT_SCS1HD_OFS&t;&t;0x40c
DECL|macro|GT_SCS2LD_OFS
mdefine_line|#define GT_SCS2LD_OFS&t;&t;0x410
DECL|macro|GT_SCS2HD_OFS
mdefine_line|#define GT_SCS2HD_OFS&t;&t;0x414
DECL|macro|GT_SCS3LD_OFS
mdefine_line|#define GT_SCS3LD_OFS&t;&t;0x418
DECL|macro|GT_SCS3HD_OFS
mdefine_line|#define GT_SCS3HD_OFS&t;&t;0x41c
DECL|macro|GT_CS0LD_OFS
mdefine_line|#define GT_CS0LD_OFS&t;&t;0x420
DECL|macro|GT_CS0HD_OFS
mdefine_line|#define GT_CS0HD_OFS&t;&t;0x424
DECL|macro|GT_CS1LD_OFS
mdefine_line|#define GT_CS1LD_OFS&t;&t;0x428
DECL|macro|GT_CS1HD_OFS
mdefine_line|#define GT_CS1HD_OFS&t;&t;0x42c
DECL|macro|GT_CS2LD_OFS
mdefine_line|#define GT_CS2LD_OFS&t;&t;0x430
DECL|macro|GT_CS2HD_OFS
mdefine_line|#define GT_CS2HD_OFS&t;&t;0x434
DECL|macro|GT_CS3LD_OFS
mdefine_line|#define GT_CS3LD_OFS&t;&t;0x438
DECL|macro|GT_CS3HD_OFS
mdefine_line|#define GT_CS3HD_OFS&t;&t;0x43c
DECL|macro|GT_BOOTLD_OFS
mdefine_line|#define GT_BOOTLD_OFS&t;&t;0x440
DECL|macro|GT_BOOTHD_OFS
mdefine_line|#define GT_BOOTHD_OFS&t;&t;0x444
DECL|macro|GT_ADERR_OFS
mdefine_line|#define GT_ADERR_OFS&t;&t;0x470
multiline_comment|/* SDRAM Configuration.  */
DECL|macro|GT_SDRAM_CFG_OFS
mdefine_line|#define GT_SDRAM_CFG_OFS&t;0x448
DECL|macro|GT_SDRAM_OPMODE_OFS
mdefine_line|#define GT_SDRAM_OPMODE_OFS&t;0x474
DECL|macro|GT_SDRAM_BM_OFS
mdefine_line|#define GT_SDRAM_BM_OFS&t;&t;0x478
DECL|macro|GT_SDRAM_ADDRDECODE_OFS
mdefine_line|#define GT_SDRAM_ADDRDECODE_OFS&t;0x47c
multiline_comment|/* SDRAM Parameters.  */
DECL|macro|GT_SDRAM_B0_OFS
mdefine_line|#define GT_SDRAM_B0_OFS&t;&t;0x44c
DECL|macro|GT_SDRAM_B1_OFS
mdefine_line|#define GT_SDRAM_B1_OFS&t;&t;0x450
DECL|macro|GT_SDRAM_B2_OFS
mdefine_line|#define GT_SDRAM_B2_OFS&t;&t;0x454
DECL|macro|GT_SDRAM_B3_OFS
mdefine_line|#define GT_SDRAM_B3_OFS&t;&t;0x458
multiline_comment|/* Device Parameters.  */
DECL|macro|GT_DEV_B0_OFS
mdefine_line|#define GT_DEV_B0_OFS&t;&t;0x45c
DECL|macro|GT_DEV_B1_OFS
mdefine_line|#define GT_DEV_B1_OFS&t;&t;0x460
DECL|macro|GT_DEV_B2_OFS
mdefine_line|#define GT_DEV_B2_OFS&t;&t;0x464
DECL|macro|GT_DEV_B3_OFS
mdefine_line|#define GT_DEV_B3_OFS&t;&t;0x468
DECL|macro|GT_DEV_BOOT_OFS
mdefine_line|#define GT_DEV_BOOT_OFS&t;&t;0x46c
multiline_comment|/* ECC.  */
DECL|macro|GT_ECC_ERRDATALO
mdefine_line|#define GT_ECC_ERRDATALO&t;0x480&t;&t;&t;/* GT-64120A only  */
DECL|macro|GT_ECC_ERRDATAHI
mdefine_line|#define GT_ECC_ERRDATAHI&t;0x484&t;&t;&t;/* GT-64120A only  */
DECL|macro|GT_ECC_MEM
mdefine_line|#define GT_ECC_MEM&t;&t;0x488&t;&t;&t;/* GT-64120A only  */
DECL|macro|GT_ECC_CALC
mdefine_line|#define GT_ECC_CALC&t;&t;0x48c&t;&t;&t;/* GT-64120A only  */
DECL|macro|GT_ECC_ERRADDR
mdefine_line|#define GT_ECC_ERRADDR&t;&t;0x490&t;&t;&t;/* GT-64120A only  */
multiline_comment|/* DMA Record.  */
DECL|macro|GT_DMA0_CNT_OFS
mdefine_line|#define GT_DMA0_CNT_OFS&t;&t;0x800
DECL|macro|GT_DMA1_CNT_OFS
mdefine_line|#define GT_DMA1_CNT_OFS&t;&t;0x804
DECL|macro|GT_DMA2_CNT_OFS
mdefine_line|#define GT_DMA2_CNT_OFS&t;&t;0x808
DECL|macro|GT_DMA3_CNT_OFS
mdefine_line|#define GT_DMA3_CNT_OFS&t;&t;0x80c
DECL|macro|GT_DMA0_SA_OFS
mdefine_line|#define GT_DMA0_SA_OFS&t;&t;0x810
DECL|macro|GT_DMA1_SA_OFS
mdefine_line|#define GT_DMA1_SA_OFS&t;&t;0x814
DECL|macro|GT_DMA2_SA_OFS
mdefine_line|#define GT_DMA2_SA_OFS&t;&t;0x818
DECL|macro|GT_DMA3_SA_OFS
mdefine_line|#define GT_DMA3_SA_OFS&t;&t;0x81c
DECL|macro|GT_DMA0_DA_OFS
mdefine_line|#define GT_DMA0_DA_OFS&t;&t;0x820
DECL|macro|GT_DMA1_DA_OFS
mdefine_line|#define GT_DMA1_DA_OFS&t;&t;0x824
DECL|macro|GT_DMA2_DA_OFS
mdefine_line|#define GT_DMA2_DA_OFS&t;&t;0x828
DECL|macro|GT_DMA3_DA_OFS
mdefine_line|#define GT_DMA3_DA_OFS&t;&t;0x82c
DECL|macro|GT_DMA0_NEXT_OFS
mdefine_line|#define GT_DMA0_NEXT_OFS&t;0x830
DECL|macro|GT_DMA1_NEXT_OFS
mdefine_line|#define GT_DMA1_NEXT_OFS&t;0x834
DECL|macro|GT_DMA2_NEXT_OFS
mdefine_line|#define GT_DMA2_NEXT_OFS&t;0x838
DECL|macro|GT_DMA3_NEXT_OFS
mdefine_line|#define GT_DMA3_NEXT_OFS&t;0x83c
DECL|macro|GT_DMA0_CUR_OFS
mdefine_line|#define GT_DMA0_CUR_OFS&t;&t;0x870
DECL|macro|GT_DMA1_CUR_OFS
mdefine_line|#define GT_DMA1_CUR_OFS&t;&t;0x874
DECL|macro|GT_DMA2_CUR_OFS
mdefine_line|#define GT_DMA2_CUR_OFS&t;&t;0x878
DECL|macro|GT_DMA3_CUR_OFS
mdefine_line|#define GT_DMA3_CUR_OFS&t;&t;0x87c
multiline_comment|/* DMA Channel Control.  */
DECL|macro|GT_DMA0_CTRL_OFS
mdefine_line|#define GT_DMA0_CTRL_OFS&t;0x840
DECL|macro|GT_DMA1_CTRL_OFS
mdefine_line|#define GT_DMA1_CTRL_OFS&t;0x844
DECL|macro|GT_DMA2_CTRL_OFS
mdefine_line|#define GT_DMA2_CTRL_OFS&t;0x848
DECL|macro|GT_DMA3_CTRL_OFS
mdefine_line|#define GT_DMA3_CTRL_OFS&t;0x84c
multiline_comment|/* DMA Arbiter.  */
DECL|macro|GT_DMA_ARB_OFS
mdefine_line|#define GT_DMA_ARB_OFS&t;&t;0x860
multiline_comment|/* Timer/Counter.  */
DECL|macro|GT_TC0_OFS
mdefine_line|#define GT_TC0_OFS&t;&t;0x850
DECL|macro|GT_TC1_OFS
mdefine_line|#define GT_TC1_OFS&t;&t;0x854
DECL|macro|GT_TC2_OFS
mdefine_line|#define GT_TC2_OFS&t;&t;0x858
DECL|macro|GT_TC3_OFS
mdefine_line|#define GT_TC3_OFS&t;&t;0x85c
DECL|macro|GT_TC_CONTROL_OFS
mdefine_line|#define GT_TC_CONTROL_OFS&t;0x864
multiline_comment|/* PCI Internal.  */
DECL|macro|GT_PCI0_CMD_OFS
mdefine_line|#define GT_PCI0_CMD_OFS&t;&t;0xc00
DECL|macro|GT_PCI0_TOR_OFS
mdefine_line|#define GT_PCI0_TOR_OFS&t;&t;0xc04
DECL|macro|GT_PCI0_BS_SCS10_OFS
mdefine_line|#define GT_PCI0_BS_SCS10_OFS&t;0xc08
DECL|macro|GT_PCI0_BS_SCS32_OFS
mdefine_line|#define GT_PCI0_BS_SCS32_OFS&t;0xc0c
DECL|macro|GT_PCI0_BS_CS20_OFS
mdefine_line|#define GT_PCI0_BS_CS20_OFS&t;0xc10
DECL|macro|GT_PCI0_BS_CS3BT_OFS
mdefine_line|#define GT_PCI0_BS_CS3BT_OFS&t;0xc14
DECL|macro|GT_PCI1_IACK_OFS
mdefine_line|#define GT_PCI1_IACK_OFS&t;0xc30
DECL|macro|GT_PCI0_IACK_OFS
mdefine_line|#define GT_PCI0_IACK_OFS&t;0xc34
DECL|macro|GT_PCI0_BARE_OFS
mdefine_line|#define GT_PCI0_BARE_OFS&t;0xc3c
DECL|macro|GT_PCI0_PREFMBR_OFS
mdefine_line|#define GT_PCI0_PREFMBR_OFS&t;0xc40
DECL|macro|GT_PCI0_SCS10_BAR_OFS
mdefine_line|#define GT_PCI0_SCS10_BAR_OFS&t;0xc48
DECL|macro|GT_PCI0_SCS32_BAR_OFS
mdefine_line|#define GT_PCI0_SCS32_BAR_OFS&t;0xc4c
DECL|macro|GT_PCI0_CS20_BAR_OFS
mdefine_line|#define GT_PCI0_CS20_BAR_OFS&t;0xc50
DECL|macro|GT_PCI0_CS3BT_BAR_OFS
mdefine_line|#define GT_PCI0_CS3BT_BAR_OFS&t;0xc54
DECL|macro|GT_PCI0_SSCS10_BAR_OFS
mdefine_line|#define GT_PCI0_SSCS10_BAR_OFS&t;0xc58
DECL|macro|GT_PCI0_SSCS32_BAR_OFS
mdefine_line|#define GT_PCI0_SSCS32_BAR_OFS&t;0xc5c
DECL|macro|GT_PCI0_SCS3BT_BAR_OFS
mdefine_line|#define GT_PCI0_SCS3BT_BAR_OFS&t;0xc64
DECL|macro|GT_PCI1_CMD_OFS
mdefine_line|#define GT_PCI1_CMD_OFS&t;&t;0xc80
DECL|macro|GT_PCI1_TOR_OFS
mdefine_line|#define GT_PCI1_TOR_OFS&t;&t;0xc84
DECL|macro|GT_PCI1_BS_SCS10_OFS
mdefine_line|#define GT_PCI1_BS_SCS10_OFS&t;0xc88
DECL|macro|GT_PCI1_BS_SCS32_OFS
mdefine_line|#define GT_PCI1_BS_SCS32_OFS&t;0xc8c
DECL|macro|GT_PCI1_BS_CS20_OFS
mdefine_line|#define GT_PCI1_BS_CS20_OFS&t;0xc90
DECL|macro|GT_PCI1_BS_CS3BT_OFS
mdefine_line|#define GT_PCI1_BS_CS3BT_OFS&t;0xc94
DECL|macro|GT_PCI1_BARE_OFS
mdefine_line|#define GT_PCI1_BARE_OFS&t;0xcbc
DECL|macro|GT_PCI1_PREFMBR_OFS
mdefine_line|#define GT_PCI1_PREFMBR_OFS&t;0xcc0
DECL|macro|GT_PCI1_SCS10_BAR_OFS
mdefine_line|#define GT_PCI1_SCS10_BAR_OFS&t;0xcc8
DECL|macro|GT_PCI1_SCS32_BAR_OFS
mdefine_line|#define GT_PCI1_SCS32_BAR_OFS&t;0xccc
DECL|macro|GT_PCI1_CS20_BAR_OFS
mdefine_line|#define GT_PCI1_CS20_BAR_OFS&t;0xcd0
DECL|macro|GT_PCI1_CS3BT_BAR_OFS
mdefine_line|#define GT_PCI1_CS3BT_BAR_OFS&t;0xcd4
DECL|macro|GT_PCI1_SSCS10_BAR_OFS
mdefine_line|#define GT_PCI1_SSCS10_BAR_OFS&t;0xcd8
DECL|macro|GT_PCI1_SSCS32_BAR_OFS
mdefine_line|#define GT_PCI1_SSCS32_BAR_OFS&t;0xcdc
DECL|macro|GT_PCI1_SCS3BT_BAR_OFS
mdefine_line|#define GT_PCI1_SCS3BT_BAR_OFS&t;0xce4
DECL|macro|GT_PCI1_CFGADDR_OFS
mdefine_line|#define GT_PCI1_CFGADDR_OFS&t;0xcf0
DECL|macro|GT_PCI1_CFGDATA_OFS
mdefine_line|#define GT_PCI1_CFGDATA_OFS&t;0xcf4
DECL|macro|GT_PCI0_CFGADDR_OFS
mdefine_line|#define GT_PCI0_CFGADDR_OFS&t;0xcf8
DECL|macro|GT_PCI0_CFGDATA_OFS
mdefine_line|#define GT_PCI0_CFGDATA_OFS&t;0xcfc
multiline_comment|/* Interrupts.  */
DECL|macro|GT_INTRCAUSE_OFS
mdefine_line|#define GT_INTRCAUSE_OFS&t;0xc18
DECL|macro|GT_INTRMASK_OFS
mdefine_line|#define GT_INTRMASK_OFS&t;&t;0xc1c
DECL|macro|GT_PCI0_ICMASK_OFS
mdefine_line|#define GT_PCI0_ICMASK_OFS&t;0xc24
DECL|macro|GT_PCI0_SERR0MASK_OFS
mdefine_line|#define GT_PCI0_SERR0MASK_OFS&t;0xc28
DECL|macro|GT_CPU_INTSEL_OFS
mdefine_line|#define GT_CPU_INTSEL_OFS&t;0xc70
DECL|macro|GT_PCI0_INTSEL_OFS
mdefine_line|#define GT_PCI0_INTSEL_OFS&t;0xc74
DECL|macro|GT_HINTRCAUSE_OFS
mdefine_line|#define GT_HINTRCAUSE_OFS&t;0xc98
DECL|macro|GT_HINTRMASK_OFS
mdefine_line|#define GT_HINTRMASK_OFS&t;0xc9c
DECL|macro|GT_PCI0_HICMASK_OFS
mdefine_line|#define GT_PCI0_HICMASK_OFS&t;0xca4
DECL|macro|GT_PCI1_SERR1MASK_OFS
mdefine_line|#define GT_PCI1_SERR1MASK_OFS&t;0xca8
multiline_comment|/*&n; * I2O Support Registers&n; */
DECL|macro|INBOUND_MESSAGE_REGISTER0_PCI_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_PCI_SIDE&t;&t;0x010
DECL|macro|INBOUND_MESSAGE_REGISTER1_PCI_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_PCI_SIDE&t;&t;0x014
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_PCI_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_PCI_SIDE&t;&t;0x018
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_PCI_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_PCI_SIDE&t;&t;0x01c
DECL|macro|INBOUND_DOORBELL_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_PCI_SIDE&t;&t;0x020
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE&t;0x024
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE&t;0x028
DECL|macro|OUTBOUND_DOORBELL_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_PCI_SIDE&t;&t;0x02c
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE&t;0x030
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE&t;0x034
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE&t;0x040
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE&t;0x044
DECL|macro|QUEUE_CONTROL_REGISTER_PCI_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_PCI_SIDE&t;&t;&t;0x050
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_PCI_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_PCI_SIDE&t;&t;0x054
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x060
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x064
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x068
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x06c
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x070
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x074
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x078
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x07c
DECL|macro|INBOUND_MESSAGE_REGISTER0_CPU_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_CPU_SIDE&t;&t;0x1c10
DECL|macro|INBOUND_MESSAGE_REGISTER1_CPU_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_CPU_SIDE&t;&t;0x1c14
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_CPU_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_CPU_SIDE&t;&t;0x1c18
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_CPU_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_CPU_SIDE&t;&t;0x1c1c
DECL|macro|INBOUND_DOORBELL_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_CPU_SIDE&t;&t;0x1c20
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE&t;0x1c24
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE&t;0x1c28
DECL|macro|OUTBOUND_DOORBELL_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_CPU_SIDE&t;&t;0x1c2c
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE&t;0x1c30
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE&t;0x1c34
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE&t;0x1c40
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE&t;0x1c44
DECL|macro|QUEUE_CONTROL_REGISTER_CPU_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_CPU_SIDE&t;&t;&t;0x1c50
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_CPU_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_CPU_SIDE&t;&t;0x1c54
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c60
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c64
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c68
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c6c
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c70
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c74
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c78
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c7c
multiline_comment|/*&n; *  Register encodings&n; */
DECL|macro|GT_CPU_ENDIAN_SHF
mdefine_line|#define GT_CPU_ENDIAN_SHF&t;12
DECL|macro|GT_CPU_ENDIAN_MSK
mdefine_line|#define GT_CPU_ENDIAN_MSK&t;(MSK(1) &lt;&lt; GT_CPU_ENDIAN_SHF)
DECL|macro|GT_CPU_ENDIAN_BIT
mdefine_line|#define GT_CPU_ENDIAN_BIT&t;GT_CPU_ENDIAN_MSK
DECL|macro|GT_CPU_WR_SHF
mdefine_line|#define GT_CPU_WR_SHF&t;&t;16
DECL|macro|GT_CPU_WR_MSK
mdefine_line|#define GT_CPU_WR_MSK&t;&t;(MSK(1) &lt;&lt; GT_CPU_WR_SHF)
DECL|macro|GT_CPU_WR_BIT
mdefine_line|#define GT_CPU_WR_BIT&t;&t;GT_CPU_WR_MSK
DECL|macro|GT_CPU_WR_DXDXDXDX
mdefine_line|#define GT_CPU_WR_DXDXDXDX&t;0
DECL|macro|GT_CPU_WR_DDDD
mdefine_line|#define GT_CPU_WR_DDDD&t;&t;1
DECL|macro|GT_PCI_DCRM_SHF
mdefine_line|#define GT_PCI_DCRM_SHF&t;&t;21
DECL|macro|GT_PCI_LD_SHF
mdefine_line|#define GT_PCI_LD_SHF&t;&t;0
DECL|macro|GT_PCI_LD_MSK
mdefine_line|#define GT_PCI_LD_MSK&t;&t;(MSK(15) &lt;&lt; GT_PCI_LD_SHF)
DECL|macro|GT_PCI_HD_SHF
mdefine_line|#define GT_PCI_HD_SHF&t;&t;0
DECL|macro|GT_PCI_HD_MSK
mdefine_line|#define GT_PCI_HD_MSK&t;&t;(MSK(7) &lt;&lt; GT_PCI_HD_SHF)
DECL|macro|GT_PCI_REMAP_SHF
mdefine_line|#define GT_PCI_REMAP_SHF&t;0
DECL|macro|GT_PCI_REMAP_MSK
mdefine_line|#define GT_PCI_REMAP_MSK&t;(MSK(11) &lt;&lt; GT_PCI_REMAP_SHF)
DECL|macro|GT_CFGADDR_CFGEN_SHF
mdefine_line|#define GT_CFGADDR_CFGEN_SHF&t;31
DECL|macro|GT_CFGADDR_CFGEN_MSK
mdefine_line|#define GT_CFGADDR_CFGEN_MSK&t;(MSK(1) &lt;&lt; GT_CFGADDR_CFGEN_SHF)
DECL|macro|GT_CFGADDR_CFGEN_BIT
mdefine_line|#define GT_CFGADDR_CFGEN_BIT&t;GT_CFGADDR_CFGEN_MSK
DECL|macro|GT_CFGADDR_BUSNUM_SHF
mdefine_line|#define GT_CFGADDR_BUSNUM_SHF&t;16
DECL|macro|GT_CFGADDR_BUSNUM_MSK
mdefine_line|#define GT_CFGADDR_BUSNUM_MSK&t;(MSK(8) &lt;&lt; GT_CFGADDR_BUSNUM_SHF)
DECL|macro|GT_CFGADDR_DEVNUM_SHF
mdefine_line|#define GT_CFGADDR_DEVNUM_SHF&t;11
DECL|macro|GT_CFGADDR_DEVNUM_MSK
mdefine_line|#define GT_CFGADDR_DEVNUM_MSK&t;(MSK(5) &lt;&lt; GT_CFGADDR_DEVNUM_SHF)
DECL|macro|GT_CFGADDR_FUNCNUM_SHF
mdefine_line|#define GT_CFGADDR_FUNCNUM_SHF&t;8
DECL|macro|GT_CFGADDR_FUNCNUM_MSK
mdefine_line|#define GT_CFGADDR_FUNCNUM_MSK&t;(MSK(3) &lt;&lt; GT_CFGADDR_FUNCNUM_SHF)
DECL|macro|GT_CFGADDR_REGNUM_SHF
mdefine_line|#define GT_CFGADDR_REGNUM_SHF&t;2
DECL|macro|GT_CFGADDR_REGNUM_MSK
mdefine_line|#define GT_CFGADDR_REGNUM_MSK&t;(MSK(6) &lt;&lt; GT_CFGADDR_REGNUM_SHF)
DECL|macro|GT_SDRAM_BM_ORDER_SHF
mdefine_line|#define GT_SDRAM_BM_ORDER_SHF&t;2
DECL|macro|GT_SDRAM_BM_ORDER_MSK
mdefine_line|#define GT_SDRAM_BM_ORDER_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_BM_ORDER_SHF)
DECL|macro|GT_SDRAM_BM_ORDER_BIT
mdefine_line|#define GT_SDRAM_BM_ORDER_BIT&t;GT_SDRAM_BM_ORDER_MSK
DECL|macro|GT_SDRAM_BM_ORDER_SUB
mdefine_line|#define GT_SDRAM_BM_ORDER_SUB&t;1
DECL|macro|GT_SDRAM_BM_ORDER_LIN
mdefine_line|#define GT_SDRAM_BM_ORDER_LIN&t;0
DECL|macro|GT_SDRAM_BM_RSVD_ALL1
mdefine_line|#define GT_SDRAM_BM_RSVD_ALL1&t;0xffb
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_SHF
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_SHF&t;0
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_MSK
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_MSK&t;(MSK(3) &lt;&lt; GT_SDRAM_ADDRDECODE_ADDR_SHF)
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_0
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_0&t;0
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_1
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_1&t;1
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_2
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_2&t;2
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_3
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_3&t;3
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_4
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_4&t;4
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_5
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_5&t;5
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_6
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_6&t;6
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_7
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_7&t;7
DECL|macro|GT_SDRAM_B0_CASLAT_SHF
mdefine_line|#define GT_SDRAM_B0_CASLAT_SHF&t;&t;0
DECL|macro|GT_SDRAM_B0_CASLAT_MSK
mdefine_line|#define GT_SDRAM_B0_CASLAT_MSK&t;&t;(MSK(2) &lt;&lt; GT_SDRAM_B0__SHF)
DECL|macro|GT_SDRAM_B0_CASLAT_2
mdefine_line|#define GT_SDRAM_B0_CASLAT_2&t;&t;1
DECL|macro|GT_SDRAM_B0_CASLAT_3
mdefine_line|#define GT_SDRAM_B0_CASLAT_3&t;&t;2
DECL|macro|GT_SDRAM_B0_FTDIS_SHF
mdefine_line|#define GT_SDRAM_B0_FTDIS_SHF&t;&t;2
DECL|macro|GT_SDRAM_B0_FTDIS_MSK
mdefine_line|#define GT_SDRAM_B0_FTDIS_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_FTDIS_SHF)
DECL|macro|GT_SDRAM_B0_FTDIS_BIT
mdefine_line|#define GT_SDRAM_B0_FTDIS_BIT&t;&t;GT_SDRAM_B0_FTDIS_MSK
DECL|macro|GT_SDRAM_B0_SRASPRCHG_SHF
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_SHF&t;3
DECL|macro|GT_SDRAM_B0_SRASPRCHG_MSK
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_SRASPRCHG_SHF)
DECL|macro|GT_SDRAM_B0_SRASPRCHG_BIT
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_BIT&t;GT_SDRAM_B0_SRASPRCHG_MSK
DECL|macro|GT_SDRAM_B0_SRASPRCHG_2
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_2&t;&t;0
DECL|macro|GT_SDRAM_B0_SRASPRCHG_3
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_3&t;&t;1
DECL|macro|GT_SDRAM_B0_B0COMPAB_SHF
mdefine_line|#define GT_SDRAM_B0_B0COMPAB_SHF&t;4
DECL|macro|GT_SDRAM_B0_B0COMPAB_MSK
mdefine_line|#define GT_SDRAM_B0_B0COMPAB_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_B0COMPAB_SHF)
DECL|macro|GT_SDRAM_B0_B0COMPAB_BIT
mdefine_line|#define GT_SDRAM_B0_B0COMPAB_BIT&t;GT_SDRAM_B0_B0COMPAB_MSK
DECL|macro|GT_SDRAM_B0_64BITINT_SHF
mdefine_line|#define GT_SDRAM_B0_64BITINT_SHF&t;5
DECL|macro|GT_SDRAM_B0_64BITINT_MSK
mdefine_line|#define GT_SDRAM_B0_64BITINT_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_64BITINT_SHF)
DECL|macro|GT_SDRAM_B0_64BITINT_BIT
mdefine_line|#define GT_SDRAM_B0_64BITINT_BIT&t;GT_SDRAM_B0_64BITINT_MSK
DECL|macro|GT_SDRAM_B0_64BITINT_2
mdefine_line|#define GT_SDRAM_B0_64BITINT_2&t;&t;0
DECL|macro|GT_SDRAM_B0_64BITINT_4
mdefine_line|#define GT_SDRAM_B0_64BITINT_4&t;&t;1
DECL|macro|GT_SDRAM_B0_BW_SHF
mdefine_line|#define GT_SDRAM_B0_BW_SHF&t;&t;6
DECL|macro|GT_SDRAM_B0_BW_MSK
mdefine_line|#define GT_SDRAM_B0_BW_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BW_SHF)
DECL|macro|GT_SDRAM_B0_BW_BIT
mdefine_line|#define GT_SDRAM_B0_BW_BIT&t;&t;GT_SDRAM_B0_BW_MSK
DECL|macro|GT_SDRAM_B0_BW_32
mdefine_line|#define GT_SDRAM_B0_BW_32&t;&t;0
DECL|macro|GT_SDRAM_B0_BW_64
mdefine_line|#define GT_SDRAM_B0_BW_64&t;&t;1
DECL|macro|GT_SDRAM_B0_BLODD_SHF
mdefine_line|#define GT_SDRAM_B0_BLODD_SHF&t;&t;7
DECL|macro|GT_SDRAM_B0_BLODD_MSK
mdefine_line|#define GT_SDRAM_B0_BLODD_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BLODD_SHF)
DECL|macro|GT_SDRAM_B0_BLODD_BIT
mdefine_line|#define GT_SDRAM_B0_BLODD_BIT&t;&t;GT_SDRAM_B0_BLODD_MSK
DECL|macro|GT_SDRAM_B0_PAR_SHF
mdefine_line|#define GT_SDRAM_B0_PAR_SHF&t;&t;8
DECL|macro|GT_SDRAM_B0_PAR_MSK
mdefine_line|#define GT_SDRAM_B0_PAR_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_PAR_SHF)
DECL|macro|GT_SDRAM_B0_PAR_BIT
mdefine_line|#define GT_SDRAM_B0_PAR_BIT&t;&t;GT_SDRAM_B0_PAR_MSK
DECL|macro|GT_SDRAM_B0_BYPASS_SHF
mdefine_line|#define GT_SDRAM_B0_BYPASS_SHF&t;&t;9
DECL|macro|GT_SDRAM_B0_BYPASS_MSK
mdefine_line|#define GT_SDRAM_B0_BYPASS_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BYPASS_SHF)
DECL|macro|GT_SDRAM_B0_BYPASS_BIT
mdefine_line|#define GT_SDRAM_B0_BYPASS_BIT&t;&t;GT_SDRAM_B0_BYPASS_MSK
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_SHF
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_SHF&t;10
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_MSK
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_SRAS2SCAS_SHF)
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_BIT
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_BIT&t;GT_SDRAM_B0_SRAS2SCAS_MSK
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_2
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_2&t;&t;0
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_3
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_3&t;&t;1
DECL|macro|GT_SDRAM_B0_SIZE_SHF
mdefine_line|#define GT_SDRAM_B0_SIZE_SHF&t;&t;11
DECL|macro|GT_SDRAM_B0_SIZE_MSK
mdefine_line|#define GT_SDRAM_B0_SIZE_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_SIZE_SHF)
DECL|macro|GT_SDRAM_B0_SIZE_BIT
mdefine_line|#define GT_SDRAM_B0_SIZE_BIT&t;&t;GT_SDRAM_B0_SIZE_MSK
DECL|macro|GT_SDRAM_B0_SIZE_16M
mdefine_line|#define GT_SDRAM_B0_SIZE_16M&t;&t;0
DECL|macro|GT_SDRAM_B0_SIZE_64M
mdefine_line|#define GT_SDRAM_B0_SIZE_64M&t;&t;1
DECL|macro|GT_SDRAM_B0_EXTPAR_SHF
mdefine_line|#define GT_SDRAM_B0_EXTPAR_SHF&t;&t;12
DECL|macro|GT_SDRAM_B0_EXTPAR_MSK
mdefine_line|#define GT_SDRAM_B0_EXTPAR_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_EXTPAR_SHF)
DECL|macro|GT_SDRAM_B0_EXTPAR_BIT
mdefine_line|#define GT_SDRAM_B0_EXTPAR_BIT&t;&t;GT_SDRAM_B0_EXTPAR_MSK
DECL|macro|GT_SDRAM_B0_BLEN_SHF
mdefine_line|#define GT_SDRAM_B0_BLEN_SHF&t;&t;13
DECL|macro|GT_SDRAM_B0_BLEN_MSK
mdefine_line|#define GT_SDRAM_B0_BLEN_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BLEN_SHF)
DECL|macro|GT_SDRAM_B0_BLEN_BIT
mdefine_line|#define GT_SDRAM_B0_BLEN_BIT&t;&t;GT_SDRAM_B0_BLEN_MSK
DECL|macro|GT_SDRAM_B0_BLEN_8
mdefine_line|#define GT_SDRAM_B0_BLEN_8&t;&t;0
DECL|macro|GT_SDRAM_B0_BLEN_4
mdefine_line|#define GT_SDRAM_B0_BLEN_4&t;&t;1
DECL|macro|GT_SDRAM_CFG_REFINT_SHF
mdefine_line|#define GT_SDRAM_CFG_REFINT_SHF&t;&t;0
DECL|macro|GT_SDRAM_CFG_REFINT_MSK
mdefine_line|#define GT_SDRAM_CFG_REFINT_MSK&t;&t;(MSK(14) &lt;&lt; GT_SDRAM_CFG_REFINT_SHF)
DECL|macro|GT_SDRAM_CFG_NINTERLEAVE_SHF
mdefine_line|#define GT_SDRAM_CFG_NINTERLEAVE_SHF&t;14
DECL|macro|GT_SDRAM_CFG_NINTERLEAVE_MSK
mdefine_line|#define GT_SDRAM_CFG_NINTERLEAVE_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_NINTERLEAVE_SHF)
DECL|macro|GT_SDRAM_CFG_NINTERLEAVE_BIT
mdefine_line|#define GT_SDRAM_CFG_NINTERLEAVE_BIT&t;GT_SDRAM_CFG_NINTERLEAVE_MSK
DECL|macro|GT_SDRAM_CFG_RMW_SHF
mdefine_line|#define GT_SDRAM_CFG_RMW_SHF&t;&t;15
DECL|macro|GT_SDRAM_CFG_RMW_MSK
mdefine_line|#define GT_SDRAM_CFG_RMW_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_RMW_SHF)
DECL|macro|GT_SDRAM_CFG_RMW_BIT
mdefine_line|#define GT_SDRAM_CFG_RMW_BIT&t;&t;GT_SDRAM_CFG_RMW_MSK
DECL|macro|GT_SDRAM_CFG_NONSTAGREF_SHF
mdefine_line|#define GT_SDRAM_CFG_NONSTAGREF_SHF&t;16
DECL|macro|GT_SDRAM_CFG_NONSTAGREF_MSK
mdefine_line|#define GT_SDRAM_CFG_NONSTAGREF_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_NONSTAGREF_SHF)
DECL|macro|GT_SDRAM_CFG_NONSTAGREF_BIT
mdefine_line|#define GT_SDRAM_CFG_NONSTAGREF_BIT&t;GT_SDRAM_CFG_NONSTAGREF_MSK
DECL|macro|GT_SDRAM_CFG_DUPCNTL_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPCNTL_SHF&t;19
DECL|macro|GT_SDRAM_CFG_DUPCNTL_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPCNTL_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPCNTL_SHF)
DECL|macro|GT_SDRAM_CFG_DUPCNTL_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPCNTL_BIT&t;GT_SDRAM_CFG_DUPCNTL_MSK
DECL|macro|GT_SDRAM_CFG_DUPBA_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPBA_SHF&t;&t;20
DECL|macro|GT_SDRAM_CFG_DUPBA_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPBA_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPBA_SHF)
DECL|macro|GT_SDRAM_CFG_DUPBA_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPBA_BIT&t;&t;GT_SDRAM_CFG_DUPBA_MSK
DECL|macro|GT_SDRAM_CFG_DUPEOT0_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPEOT0_SHF&t;21
DECL|macro|GT_SDRAM_CFG_DUPEOT0_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPEOT0_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPEOT0_SHF)
DECL|macro|GT_SDRAM_CFG_DUPEOT0_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPEOT0_BIT&t;GT_SDRAM_CFG_DUPEOT0_MSK
DECL|macro|GT_SDRAM_CFG_DUPEOT1_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPEOT1_SHF&t;22
DECL|macro|GT_SDRAM_CFG_DUPEOT1_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPEOT1_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPEOT1_SHF)
DECL|macro|GT_SDRAM_CFG_DUPEOT1_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPEOT1_BIT&t;GT_SDRAM_CFG_DUPEOT1_MSK
DECL|macro|GT_SDRAM_OPMODE_OP_SHF
mdefine_line|#define GT_SDRAM_OPMODE_OP_SHF&t;&t;0
DECL|macro|GT_SDRAM_OPMODE_OP_MSK
mdefine_line|#define GT_SDRAM_OPMODE_OP_MSK&t;&t;(MSK(3) &lt;&lt; GT_SDRAM_OPMODE_OP_SHF)
DECL|macro|GT_SDRAM_OPMODE_OP_NORMAL
mdefine_line|#define GT_SDRAM_OPMODE_OP_NORMAL&t;0
DECL|macro|GT_SDRAM_OPMODE_OP_NOP
mdefine_line|#define GT_SDRAM_OPMODE_OP_NOP&t;&t;1
DECL|macro|GT_SDRAM_OPMODE_OP_PRCHG
mdefine_line|#define GT_SDRAM_OPMODE_OP_PRCHG&t;2
DECL|macro|GT_SDRAM_OPMODE_OP_MODE
mdefine_line|#define GT_SDRAM_OPMODE_OP_MODE&t;&t;3
DECL|macro|GT_SDRAM_OPMODE_OP_CBR
mdefine_line|#define GT_SDRAM_OPMODE_OP_CBR&t;&t;4
DECL|macro|GT_PCI0_BARE_SWSCS3BOOTDIS_SHF
mdefine_line|#define GT_PCI0_BARE_SWSCS3BOOTDIS_SHF&t;0
DECL|macro|GT_PCI0_BARE_SWSCS3BOOTDIS_MSK
mdefine_line|#define GT_PCI0_BARE_SWSCS3BOOTDIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SWSCS3BOOTDIS_SHF)
DECL|macro|GT_PCI0_BARE_SWSCS3BOOTDIS_BIT
mdefine_line|#define GT_PCI0_BARE_SWSCS3BOOTDIS_BIT&t;GT_PCI0_BARE_SWSCS3BOOTDIS_MSK
DECL|macro|GT_PCI0_BARE_SWSCS32DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SWSCS32DIS_SHF&t;1
DECL|macro|GT_PCI0_BARE_SWSCS32DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SWSCS32DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SWSCS32DIS_SHF)
DECL|macro|GT_PCI0_BARE_SWSCS32DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SWSCS32DIS_BIT&t;GT_PCI0_BARE_SWSCS32DIS_MSK
DECL|macro|GT_PCI0_BARE_SWSCS10DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SWSCS10DIS_SHF&t;2
DECL|macro|GT_PCI0_BARE_SWSCS10DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SWSCS10DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SWSCS10DIS_SHF)
DECL|macro|GT_PCI0_BARE_SWSCS10DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SWSCS10DIS_BIT&t;GT_PCI0_BARE_SWSCS10DIS_MSK
DECL|macro|GT_PCI0_BARE_INTIODIS_SHF
mdefine_line|#define GT_PCI0_BARE_INTIODIS_SHF&t;3
DECL|macro|GT_PCI0_BARE_INTIODIS_MSK
mdefine_line|#define GT_PCI0_BARE_INTIODIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_INTIODIS_SHF)
DECL|macro|GT_PCI0_BARE_INTIODIS_BIT
mdefine_line|#define GT_PCI0_BARE_INTIODIS_BIT&t;GT_PCI0_BARE_INTIODIS_MSK
DECL|macro|GT_PCI0_BARE_INTMEMDIS_SHF
mdefine_line|#define GT_PCI0_BARE_INTMEMDIS_SHF&t;4
DECL|macro|GT_PCI0_BARE_INTMEMDIS_MSK
mdefine_line|#define GT_PCI0_BARE_INTMEMDIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_INTMEMDIS_SHF)
DECL|macro|GT_PCI0_BARE_INTMEMDIS_BIT
mdefine_line|#define GT_PCI0_BARE_INTMEMDIS_BIT&t;GT_PCI0_BARE_INTMEMDIS_MSK
DECL|macro|GT_PCI0_BARE_CS3BOOTDIS_SHF
mdefine_line|#define GT_PCI0_BARE_CS3BOOTDIS_SHF&t;5
DECL|macro|GT_PCI0_BARE_CS3BOOTDIS_MSK
mdefine_line|#define GT_PCI0_BARE_CS3BOOTDIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_CS3BOOTDIS_SHF)
DECL|macro|GT_PCI0_BARE_CS3BOOTDIS_BIT
mdefine_line|#define GT_PCI0_BARE_CS3BOOTDIS_BIT&t;GT_PCI0_BARE_CS3BOOTDIS_MSK
DECL|macro|GT_PCI0_BARE_CS20DIS_SHF
mdefine_line|#define GT_PCI0_BARE_CS20DIS_SHF&t;6
DECL|macro|GT_PCI0_BARE_CS20DIS_MSK
mdefine_line|#define GT_PCI0_BARE_CS20DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_CS20DIS_SHF)
DECL|macro|GT_PCI0_BARE_CS20DIS_BIT
mdefine_line|#define GT_PCI0_BARE_CS20DIS_BIT&t;GT_PCI0_BARE_CS20DIS_MSK
DECL|macro|GT_PCI0_BARE_SCS32DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SCS32DIS_SHF&t;7
DECL|macro|GT_PCI0_BARE_SCS32DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SCS32DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SCS32DIS_SHF)
DECL|macro|GT_PCI0_BARE_SCS32DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SCS32DIS_BIT&t;GT_PCI0_BARE_SCS32DIS_MSK
DECL|macro|GT_PCI0_BARE_SCS10DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SCS10DIS_SHF&t;8
DECL|macro|GT_PCI0_BARE_SCS10DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SCS10DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SCS10DIS_SHF)
DECL|macro|GT_PCI0_BARE_SCS10DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SCS10DIS_BIT&t;GT_PCI0_BARE_SCS10DIS_MSK
DECL|macro|GT_INTRCAUSE_MASABORT0_SHF
mdefine_line|#define GT_INTRCAUSE_MASABORT0_SHF&t;18
DECL|macro|GT_INTRCAUSE_MASABORT0_MSK
mdefine_line|#define GT_INTRCAUSE_MASABORT0_MSK&t;(MSK(1) &lt;&lt; GT_INTRCAUSE_MASABORT0_SHF)
DECL|macro|GT_INTRCAUSE_MASABORT0_BIT
mdefine_line|#define GT_INTRCAUSE_MASABORT0_BIT&t;GT_INTRCAUSE_MASABORT0_MSK
DECL|macro|GT_INTRCAUSE_TARABORT0_SHF
mdefine_line|#define GT_INTRCAUSE_TARABORT0_SHF&t;19
DECL|macro|GT_INTRCAUSE_TARABORT0_MSK
mdefine_line|#define GT_INTRCAUSE_TARABORT0_MSK&t;(MSK(1) &lt;&lt; GT_INTRCAUSE_TARABORT0_SHF)
DECL|macro|GT_INTRCAUSE_TARABORT0_BIT
mdefine_line|#define GT_INTRCAUSE_TARABORT0_BIT&t;GT_INTRCAUSE_TARABORT0_MSK
DECL|macro|GT_PCI0_CFGADDR_REGNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_REGNUM_SHF&t;2
DECL|macro|GT_PCI0_CFGADDR_REGNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_REGNUM_MSK&t;(MSK(6) &lt;&lt; GT_PCI0_CFGADDR_REGNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_FUNCTNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_FUNCTNUM_SHF&t;8
DECL|macro|GT_PCI0_CFGADDR_FUNCTNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_FUNCTNUM_MSK&t;(MSK(3) &lt;&lt; GT_PCI0_CFGADDR_FUNCTNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_DEVNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_DEVNUM_SHF&t;11
DECL|macro|GT_PCI0_CFGADDR_DEVNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_DEVNUM_MSK&t;(MSK(5) &lt;&lt; GT_PCI0_CFGADDR_DEVNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_BUSNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_BUSNUM_SHF&t;16
DECL|macro|GT_PCI0_CFGADDR_BUSNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_BUSNUM_MSK&t;(MSK(8) &lt;&lt; GT_PCI0_CFGADDR_BUSNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_CONFIGEN_SHF
mdefine_line|#define GT_PCI0_CFGADDR_CONFIGEN_SHF&t;31
DECL|macro|GT_PCI0_CFGADDR_CONFIGEN_MSK
mdefine_line|#define GT_PCI0_CFGADDR_CONFIGEN_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_CFGADDR_CONFIGEN_SHF)
DECL|macro|GT_PCI0_CFGADDR_CONFIGEN_BIT
mdefine_line|#define GT_PCI0_CFGADDR_CONFIGEN_BIT&t;GT_PCI0_CFGADDR_CONFIGEN_MSK
DECL|macro|GT_PCI0_CMD_MBYTESWAP_SHF
mdefine_line|#define GT_PCI0_CMD_MBYTESWAP_SHF&t;0
DECL|macro|GT_PCI0_CMD_MBYTESWAP_MSK
mdefine_line|#define GT_PCI0_CMD_MBYTESWAP_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_CMD_MBYTESWAP_SHF)
DECL|macro|GT_PCI0_CMD_MBYTESWAP_BIT
mdefine_line|#define GT_PCI0_CMD_MBYTESWAP_BIT&t;GT_PCI0_CMD_MBYTESWAP_MSK
DECL|macro|GT_PCI0_CMD_MWORDSWAP_SHF
mdefine_line|#define GT_PCI0_CMD_MWORDSWAP_SHF&t;10
DECL|macro|GT_PCI0_CMD_MWORDSWAP_MSK
mdefine_line|#define GT_PCI0_CMD_MWORDSWAP_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_CMD_MWORDSWAP_SHF)
DECL|macro|GT_PCI0_CMD_MWORDSWAP_BIT
mdefine_line|#define GT_PCI0_CMD_MWORDSWAP_BIT&t;GT_PCI0_CMD_MWORDSWAP_MSK
DECL|macro|GT_PCI0_CMD_SBYTESWAP_SHF
mdefine_line|#define GT_PCI0_CMD_SBYTESWAP_SHF&t;16
DECL|macro|GT_PCI0_CMD_SBYTESWAP_MSK
mdefine_line|#define GT_PCI0_CMD_SBYTESWAP_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_CMD_SBYTESWAP_SHF)
DECL|macro|GT_PCI0_CMD_SBYTESWAP_BIT
mdefine_line|#define GT_PCI0_CMD_SBYTESWAP_BIT&t;GT_PCI0_CMD_SBYTESWAP_MSK
DECL|macro|GT_PCI0_CMD_SWORDSWAP_SHF
mdefine_line|#define GT_PCI0_CMD_SWORDSWAP_SHF&t;11
DECL|macro|GT_PCI0_CMD_SWORDSWAP_MSK
mdefine_line|#define GT_PCI0_CMD_SWORDSWAP_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_CMD_SWORDSWAP_SHF)
DECL|macro|GT_PCI0_CMD_SWORDSWAP_BIT
mdefine_line|#define GT_PCI0_CMD_SWORDSWAP_BIT&t;GT_PCI0_CMD_SWORDSWAP_MSK
multiline_comment|/*&n; *  Misc&n; */
DECL|macro|GT_DEF_PCI0_IO_BASE
mdefine_line|#define GT_DEF_PCI0_IO_BASE&t;0x10000000UL
DECL|macro|GT_DEF_PCI0_IO_SIZE
mdefine_line|#define GT_DEF_PCI0_IO_SIZE&t;0x02000000UL
DECL|macro|GT_DEF_PCI0_MEM0_BASE
mdefine_line|#define GT_DEF_PCI0_MEM0_BASE&t;0x12000000UL
DECL|macro|GT_DEF_PCI0_MEM0_SIZE
mdefine_line|#define GT_DEF_PCI0_MEM0_SIZE&t;0x02000000UL
DECL|macro|GT_DEF_BASE
mdefine_line|#define GT_DEF_BASE&t;&t;0x14000000UL
DECL|macro|GT_MAX_BANKSIZE
mdefine_line|#define GT_MAX_BANKSIZE&t;&t;(256 * 1024 * 1024)&t;/* Max 256MB bank  */
DECL|macro|GT_LATTIM_MIN
mdefine_line|#define GT_LATTIM_MIN&t;&t;6&t;&t;&t;/* Minimum lat  */
multiline_comment|/*&n; * The gt64120_dep.h file must define the following macros&n; *&n; *   GT_READ(ofs, data_pointer)&n; *   GT_WRITE(ofs, data)           - read/write GT64120 registers in 32bit&n; *&n; *   TIMER &t;- gt64120 timer irq, temporary solution until&n; *&t;&t;  full gt64120 cascade interrupt support is in place&n; */
macro_line|#include &lt;mach-gt64120.h&gt;
multiline_comment|/*&n; * Because of an error/peculiarity in the Galileo chip, we need to swap the&n; * bytes when running bigendian.  We also provide non-swapping versions.&n; */
DECL|macro|__GT_READ
mdefine_line|#define __GT_READ(ofs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile u32 *)(GT64120_BASE+(ofs)))
DECL|macro|__GT_WRITE
mdefine_line|#define __GT_WRITE(ofs, data)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do { *(volatile u32 *)(GT64120_BASE+(ofs)) = (data); } while (0)
DECL|macro|GT_READ
mdefine_line|#define GT_READ(ofs)&t;&t;le32_to_cpu(__GT_READ(ofs))
DECL|macro|GT_WRITE
mdefine_line|#define GT_WRITE(ofs, data)&t;__GT_WRITE(ofs, cpu_to_le32(data))
macro_line|#endif /* _ASM_GT64120_H */
eof
