multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 &n; * USA&n;&n;Module Name:&n;&n;    amd8111e.h&n;&n;Abstract:&n;&t;&n; &t; AMD8111 based 10/100 Ethernet Controller driver definitions. &n;&n;Environment:&n;    &n;&t;Kernel Mode&n;&n;Revision History:&n;&n;*/
macro_line|#ifndef _AMD811E_H
DECL|macro|_AMD811E_H
mdefine_line|#define _AMD811E_H
multiline_comment|/* Hardware definitions */
DECL|macro|B31_MASK
mdefine_line|#define B31_MASK&t;0x80000000
DECL|macro|B30_MASK
mdefine_line|#define B30_MASK&t;0X40000000
DECL|macro|B29_MASK
mdefine_line|#define B29_MASK&t;0x20000000
DECL|macro|B28_MASK
mdefine_line|#define B28_MASK&t;0x10000000
DECL|macro|B27_MASK
mdefine_line|#define B27_MASK&t;0x08000000
DECL|macro|B26_MASK
mdefine_line|#define B26_MASK&t;0x04000000
DECL|macro|B25_MASK
mdefine_line|#define B25_MASK&t;0x02000000
DECL|macro|B24_MASK
mdefine_line|#define B24_MASK&t;0x01000000
DECL|macro|B23_MASK
mdefine_line|#define B23_MASK&t;0x00800000
DECL|macro|B22_MASK
mdefine_line|#define B22_MASK&t;0x00400000
DECL|macro|B21_MASK
mdefine_line|#define B21_MASK&t;0x00200000
DECL|macro|B20_MASK
mdefine_line|#define B20_MASK&t;0x00100000
DECL|macro|B19_MASK
mdefine_line|#define B19_MASK&t;0x00080000
DECL|macro|B18_MASK
mdefine_line|#define B18_MASK&t;0x00040000
DECL|macro|B17_MASK
mdefine_line|#define B17_MASK&t;0x00020000
DECL|macro|B16_MASK
mdefine_line|#define B16_MASK&t;0x00010000
DECL|macro|B15_MASK
mdefine_line|#define B15_MASK&t;0x8000
DECL|macro|B14_MASK
mdefine_line|#define B14_MASK&t;0x4000
DECL|macro|B13_MASK
mdefine_line|#define B13_MASK&t;0x2000
DECL|macro|B12_MASK
mdefine_line|#define B12_MASK&t;0x1000
DECL|macro|B11_MASK
mdefine_line|#define B11_MASK&t;0x0800
DECL|macro|B10_MASK
mdefine_line|#define B10_MASK&t;0x0400
DECL|macro|B9_MASK
mdefine_line|#define B9_MASK&t;&t;0x0200
DECL|macro|B8_MASK
mdefine_line|#define B8_MASK&t;&t;0x0100
DECL|macro|B7_MASK
mdefine_line|#define B7_MASK&t;&t;0x0080
DECL|macro|B6_MASK
mdefine_line|#define B6_MASK&t;&t;0x0040
DECL|macro|B5_MASK
mdefine_line|#define B5_MASK&t;&t;0x0020
DECL|macro|B4_MASK
mdefine_line|#define B4_MASK&t;&t;0x0010
DECL|macro|B3_MASK
mdefine_line|#define B3_MASK&t;&t;0x0008
DECL|macro|B2_MASK
mdefine_line|#define B2_MASK&t;&t;0x0004
DECL|macro|B1_MASK
mdefine_line|#define B1_MASK&t;&t;0x0002
DECL|macro|B0_MASK
mdefine_line|#define B0_MASK&t;&t;0x0001
multiline_comment|/* PCI register offset */
DECL|macro|PCI_ID_REG
mdefine_line|#define PCI_ID_REG&t;&t;0x00
DECL|macro|PCI_COMMAND_REG
mdefine_line|#define PCI_COMMAND_REG&t;&t;0x04
multiline_comment|/* #define MEMEN_BIT&t;&t;B1_MASK */
multiline_comment|/* #define IOEN_BIT&t;&t;B0_MASK */
DECL|macro|PCI_REV_ID_REG
mdefine_line|#define PCI_REV_ID_REG&t;&t;0x08
DECL|macro|PCI_MEM_BASE_REG
mdefine_line|#define PCI_MEM_BASE_REG&t;0x10
multiline_comment|/* #define MEMBASE_MASK&t;&t;0xFFFFF000 */
multiline_comment|/* #define MEMBASE_SIZE&t;&t;4096 */
DECL|macro|PCI_INTR_REG
mdefine_line|#define PCI_INTR_REG&t;&t;0x3C
DECL|macro|PCI_STATUS_REG
mdefine_line|#define PCI_STATUS_REG&t;&t;0x06
DECL|macro|PCI_CAP_ID_REG_OFFSET
mdefine_line|#define PCI_CAP_ID_REG_OFFSET&t;0x34
DECL|macro|PCI_PMC_REG_OFFSET
mdefine_line|#define PCI_PMC_REG_OFFSET&t;0x36
DECL|macro|PCI_PMCSR_REG_OFFSET
mdefine_line|#define PCI_PMCSR_REG_OFFSET&t;0x38
multiline_comment|/* #define NEW_CAP&t;&t;0x0010  */
DECL|macro|PME_EN
mdefine_line|#define PME_EN&t;&t;&t;0x0100
DECL|macro|PARTID_MASK
mdefine_line|#define PARTID_MASK&t;&t;0xFFFFF000
DECL|macro|PARTID_START_BIT
mdefine_line|#define PARTID_START_BIT&t;12
multiline_comment|/* #define LANCE_DWIO_RESET_PORT&t;0x18&n;#define LANCE_WIO_RESET_PORT&t;0x14 */
DECL|macro|MIB_OFFSET
mdefine_line|#define MIB_OFFSET&t;&t;0x28
multiline_comment|/* Command style register access&n;&n;Registers CMD0, CMD2, CMD3,CMD7 and INTEN0 uses a write access technique called command style access. It allows the write to selected bits of this register without altering the bits that are not selected. Command style registers are divided into 4 bytes that can be written independently. Higher order bit of each byte is the  value bit that specifies the value that will be written into the selected bits of register. &n;&n;eg., if the value 10011010b is written into the least significant byte of a command style register, bits 1,3 and 4 of the register will be set to 1, and the other bits will not be altered. If the value 00011010b is written into the same byte, bits 1,3 and 4 will be cleared to 0 and the other bits will not be altered.&n;&n;*/
multiline_comment|/*  Offset for Memory Mapped Registers. */
multiline_comment|/* 32 bit registers */
DECL|macro|ASF_STAT
mdefine_line|#define  ASF_STAT&t;&t;0x00&t;/* ASF status register */
DECL|macro|CHIPID
mdefine_line|#define CHIPID&t;&t;&t;0x04&t;/* Chip ID regsiter */
DECL|macro|MIB_DATA
mdefine_line|#define&t;MIB_DATA&t;&t;0x10&t;/* MIB data register */
DECL|macro|MIB_ADDR
mdefine_line|#define MIB_ADDR&t;&t;0x14&t;/* MIB address register */
DECL|macro|STAT0
mdefine_line|#define STAT0&t;&t;&t;0x30&t;/* Status0 register */
DECL|macro|INT0
mdefine_line|#define INT0&t;&t;&t;0x38&t;/* Interrupt0 register */
DECL|macro|INTEN0
mdefine_line|#define INTEN0&t;&t;&t;0x40&t;/* Interrupt0  enable register*/
DECL|macro|CMD0
mdefine_line|#define CMD0&t;&t;&t;0x48&t;/* Command0 register */
DECL|macro|CMD2
mdefine_line|#define CMD2&t;&t;&t;0x50&t;/* Command2 register */
DECL|macro|CMD3
mdefine_line|#define CMD3&t;&t;&t;0x54&t;/* Command3 resiter */
DECL|macro|CMD7
mdefine_line|#define CMD7&t;&t;&t;0x64&t;/* Command7 register */
DECL|macro|CTRL1
mdefine_line|#define CTRL1 &t;&t;&t;0x6C&t;/* Control1 register */
DECL|macro|CTRL2
mdefine_line|#define CTRL2 &t;&t;&t;0x70&t;/* Control2 register */
DECL|macro|XMT_RING_LIMIT
mdefine_line|#define XMT_RING_LIMIT&t;&t;0x7C&t;/* Transmit ring limit register */
DECL|macro|AUTOPOLL0
mdefine_line|#define AUTOPOLL0&t;&t;0x88&t;/* Auto-poll0 register */
DECL|macro|AUTOPOLL1
mdefine_line|#define AUTOPOLL1&t;&t;0x8A&t;/* Auto-poll1 register */
DECL|macro|AUTOPOLL2
mdefine_line|#define AUTOPOLL2&t;&t;0x8C&t;/* Auto-poll2 register */
DECL|macro|AUTOPOLL3
mdefine_line|#define AUTOPOLL3&t;&t;0x8E&t;/* Auto-poll3 register */
DECL|macro|AUTOPOLL4
mdefine_line|#define AUTOPOLL4&t;&t;0x90&t;/* Auto-poll4 register */
DECL|macro|AUTOPOLL5
mdefine_line|#define&t;AUTOPOLL5&t;&t;0x92&t;/* Auto-poll5 register */
DECL|macro|AP_VALUE
mdefine_line|#define AP_VALUE&t;&t;0x98&t;/* Auto-poll value register */
DECL|macro|DLY_INT_A
mdefine_line|#define DLY_INT_A&t;&t;0xA8&t;/* Group A delayed interrupt register */
DECL|macro|DLY_INT_B
mdefine_line|#define DLY_INT_B&t;&t;0xAC&t;/* Group B delayed interrupt register */
DECL|macro|FLOW_CONTROL
mdefine_line|#define FLOW_CONTROL&t;&t;0xC8&t;/* Flow control register */
DECL|macro|PHY_ACCESS
mdefine_line|#define PHY_ACCESS&t;&t;0xD0&t;/* PHY access register */
DECL|macro|STVAL
mdefine_line|#define STVAL&t;&t;&t;0xD8&t;/* Software timer value register */
DECL|macro|XMT_RING_BASE_ADDR0
mdefine_line|#define XMT_RING_BASE_ADDR0&t;0x100&t;/* Transmit ring0 base addr register */
DECL|macro|XMT_RING_BASE_ADDR1
mdefine_line|#define XMT_RING_BASE_ADDR1&t;0x108&t;/* Transmit ring1 base addr register */
DECL|macro|XMT_RING_BASE_ADDR2
mdefine_line|#define XMT_RING_BASE_ADDR2&t;0x110&t;/* Transmit ring2 base addr register */
DECL|macro|XMT_RING_BASE_ADDR3
mdefine_line|#define XMT_RING_BASE_ADDR3&t;0x118&t;/* Transmit ring2 base addr register */
DECL|macro|RCV_RING_BASE_ADDR0
mdefine_line|#define RCV_RING_BASE_ADDR0&t;0x120&t;/* Transmit ring0 base addr register */
DECL|macro|PMAT0
mdefine_line|#define PMAT0&t;&t;&t;0x190&t;/* OnNow pattern register0 */
DECL|macro|PMAT1
mdefine_line|#define PMAT1&t;&t;&t;0x194&t;/* OnNow pattern register1 */
multiline_comment|/* 16bit registers */
DECL|macro|XMT_RING_LEN0
mdefine_line|#define XMT_RING_LEN0&t;&t;0x140&t;/* Transmit Ring0 length register */
DECL|macro|XMT_RING_LEN1
mdefine_line|#define XMT_RING_LEN1&t;&t;0x144&t;/* Transmit Ring1 length register */
DECL|macro|XMT_RING_LEN2
mdefine_line|#define XMT_RING_LEN2&t;&t;0x148 &t;/* Transmit Ring2 length register */
DECL|macro|XMT_RING_LEN3
mdefine_line|#define XMT_RING_LEN3&t;&t;0x14C&t;/* Transmit Ring3 length register */
DECL|macro|RCV_RING_LEN0
mdefine_line|#define RCV_RING_LEN0&t;&t;0x150&t;/* Transmit Ring0 length register */
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;&t;0x178&t;/* SRAM size register */
DECL|macro|SRAM_BOUNDARY
mdefine_line|#define SRAM_BOUNDARY&t;&t;0x17A&t;/* SRAM boundary register */
multiline_comment|/* 48bit register */
DECL|macro|PADR
mdefine_line|#define PADR&t;&t;&t;0x160&t;/* Physical address register */
multiline_comment|/* 64bit register */
DECL|macro|LADRF
mdefine_line|#define LADRF&t;&t;&t;0x168&t;/* Logical address filter register */
multiline_comment|/* 8bit regsisters */
DECL|macro|IFS1
mdefine_line|#define IFS1&t;&t;&t;0x18C&t;/* Inter-frame spacing Part1 register */
DECL|macro|IFS
mdefine_line|#define IFS&t;&t;&t;0x18D&t;/* Inter-frame spacing register */
multiline_comment|/* Register Bit Definitions */
multiline_comment|/* STAT_ASF&t;&t;&t;0x00, 32bit register */
DECL|macro|ASF_INIT_DONE
mdefine_line|#define ASF_INIT_DONE&t;&t;B1_MASK
DECL|macro|ASF_INIT_PRESENT
mdefine_line|#define ASF_INIT_PRESENT&t;B0_MASK
multiline_comment|/* MIB_ADDR&t;&t;&t;0x14, 16bit register */
DECL|macro|MIB_CMD_ACTIVE
mdefine_line|#define&t;MIB_CMD_ACTIVE&t;&t;B15_MASK
DECL|macro|MIB_RD_CMD
mdefine_line|#define&t;MIB_RD_CMD&t;&t;B13_MASK
DECL|macro|MIB_CLEAR
mdefine_line|#define&t;MIB_CLEAR&t;&t;B12_MASK
DECL|macro|MIB_ADDRESS
mdefine_line|#define&t;MIB_ADDRESS&t;&t;0x0000003F&t;/* 5:0 */
multiline_comment|/* QOS_ADDR&t;&t;&t;0x1C, 16bit register */
DECL|macro|QOS_CMD_ACTIVE
mdefine_line|#define QOS_CMD_ACTIVE&t;&t;B15_MASK
DECL|macro|QOS_WR_CMD
mdefine_line|#define QOS_WR_CMD&t;&t;B14_MASK
DECL|macro|QOS_RD_CMD
mdefine_line|#define QOS_RD_CMD&t;&t;B13_MASK
DECL|macro|QOS_ADDRESS
mdefine_line|#define QOS_ADDRESS&t;&t;0x0000001F&t;/* 4:0 */
multiline_comment|/* STAT0&t;&t;&t;0x30, 32bit register */
DECL|macro|PAUSE_PEND
mdefine_line|#define PAUSE_PEND&t;&t;B14_MASK
DECL|macro|PAUSING
mdefine_line|#define PAUSING&t;&t;&t;B13_MASK
DECL|macro|PMAT_DET
mdefine_line|#define PMAT_DET&t;&t;B12_MASK
DECL|macro|MP_DET
mdefine_line|#define MP_DET&t;&t;&t;B11_MASK
DECL|macro|LC_DET
mdefine_line|#define LC_DET&t;&t;&t;B10_MASK
DECL|macro|SPEED_MASK
mdefine_line|#define SPEED_MASK&t;&t;0x0380&t;/* 9:7 */
DECL|macro|FULL_DPLX
mdefine_line|#define FULL_DPLX&t;&t;B6_MASK
DECL|macro|LINK_STATS
mdefine_line|#define LINK_STATS&t;&t;B5_MASK
DECL|macro|AUTONEG_COMPLETE
mdefine_line|#define AUTONEG_COMPLETE&t;B4_MASK
DECL|macro|MIIPD
mdefine_line|#define MIIPD&t;&t;&t;B3_MASK
DECL|macro|RX_SUSPENDED
mdefine_line|#define RX_SUSPENDED&t;&t;B2_MASK
DECL|macro|TX_SUSPENDED
mdefine_line|#define TX_SUSPENDED&t;&t;B1_MASK
DECL|macro|RUNNING
mdefine_line|#define RUNNING&t;&t;&t;B0_MASK
DECL|macro|PHY_SPEED_10
mdefine_line|#define PHY_SPEED_10&t;&t;0x2
DECL|macro|PHY_SPEED_100
mdefine_line|#define PHY_SPEED_100&t;&t;0x3
multiline_comment|/* INT0&t;&t;&t;&t;0x38, 32bit register */
DECL|macro|INTR
mdefine_line|#define INTR&t;&t;&t;B31_MASK
DECL|macro|PCSINT
mdefine_line|#define PCSINT&t;&t;&t;B28_MASK
DECL|macro|LCINT
mdefine_line|#define LCINT&t;&t;&t;B27_MASK
DECL|macro|APINT5
mdefine_line|#define APINT5&t;&t;&t;B26_MASK
DECL|macro|APINT4
mdefine_line|#define APINT4&t;&t;&t;B25_MASK
DECL|macro|APINT3
mdefine_line|#define APINT3&t;&t;&t;B24_MASK
DECL|macro|TINT_SUM
mdefine_line|#define TINT_SUM&t;&t;B23_MASK
DECL|macro|APINT2
mdefine_line|#define APINT2&t;&t;&t;B22_MASK
DECL|macro|APINT1
mdefine_line|#define APINT1&t;&t;&t;B21_MASK
DECL|macro|APINT0
mdefine_line|#define APINT0&t;&t;&t;B20_MASK
DECL|macro|MIIPDTINT
mdefine_line|#define MIIPDTINT&t;&t;B19_MASK
DECL|macro|MCCIINT
mdefine_line|#define MCCIINT&t;&t;&t;B18_MASK
DECL|macro|MCCINT
mdefine_line|#define MCCINT&t;&t;&t;B17_MASK
DECL|macro|MREINT
mdefine_line|#define MREINT&t;&t;&t;B16_MASK
DECL|macro|RINT_SUM
mdefine_line|#define RINT_SUM&t;&t;B15_MASK
DECL|macro|SPNDINT
mdefine_line|#define SPNDINT&t;&t;&t;B14_MASK
DECL|macro|MPINT
mdefine_line|#define MPINT&t;&t;&t;B13_MASK
DECL|macro|SINT
mdefine_line|#define SINT&t;&t;&t;B12_MASK
DECL|macro|TINT3
mdefine_line|#define TINT3&t;&t;&t;B11_MASK
DECL|macro|TINT2
mdefine_line|#define TINT2&t;&t;&t;B10_MASK
DECL|macro|TINT1
mdefine_line|#define TINT1&t;&t;&t;B9_MASK
DECL|macro|TINT0
mdefine_line|#define TINT0&t;&t;&t;B8_MASK
DECL|macro|UINT
mdefine_line|#define UINT&t;&t;&t;B7_MASK
DECL|macro|STINT
mdefine_line|#define STINT&t;&t;&t;B4_MASK
DECL|macro|RINT3
mdefine_line|#define RINT3&t;&t;&t;B3_MASK
DECL|macro|RINT2
mdefine_line|#define RINT2&t;&t;&t;B2_MASK
DECL|macro|RINT1
mdefine_line|#define RINT1&t;&t;&t;B1_MASK
DECL|macro|RINT0
mdefine_line|#define RINT0&t;&t;&t;B0_MASK
multiline_comment|/* INTEN0&t;&t;&t;0x40, 32bit register */
DECL|macro|VAL3
mdefine_line|#define VAL3&t;&t;&t;B31_MASK   /* VAL bit for byte 3 */
DECL|macro|VAL2
mdefine_line|#define VAL2&t;&t;&t;B23_MASK   /* VAL bit for byte 2 */
DECL|macro|VAL1
mdefine_line|#define VAL1&t;&t;&t;B15_MASK   /* VAL bit for byte 1 */
DECL|macro|VAL0
mdefine_line|#define VAL0&t;&t;&t;B7_MASK    /* VAL bit for byte 0 */
multiline_comment|/* VAL3 */
DECL|macro|PSCINTEN
mdefine_line|#define PSCINTEN&t;&t;B28_MASK
DECL|macro|LCINTEN
mdefine_line|#define LCINTEN&t;&t;&t;B27_MASK
DECL|macro|APINT5EN
mdefine_line|#define APINT5EN&t;&t;B26_MASK
DECL|macro|APINT4EN
mdefine_line|#define APINT4EN&t;&t;B25_MASK
DECL|macro|APINT3EN
mdefine_line|#define APINT3EN&t;&t;B24_MASK
multiline_comment|/* VAL2 */
DECL|macro|APINT2EN
mdefine_line|#define APINT2EN&t;&t;B22_MASK
DECL|macro|APINT1EN
mdefine_line|#define APINT1EN&t;&t;B21_MASK
DECL|macro|APINT0EN
mdefine_line|#define APINT0EN&t;&t;B20_MASK
DECL|macro|MIIPDTINTEN
mdefine_line|#define MIIPDTINTEN&t;&t;B19_MASK
DECL|macro|MCCIINTEN
mdefine_line|#define MCCIINTEN&t;&t;B18_MASK
DECL|macro|MCCINTEN
mdefine_line|#define MCCINTEN&t;&t;B17_MASK
DECL|macro|MREINTEN
mdefine_line|#define MREINTEN&t;&t;B16_MASK
multiline_comment|/* VAL1 */
DECL|macro|SPNDINTEN
mdefine_line|#define SPNDINTEN&t;&t;B14_MASK
DECL|macro|MPINTEN
mdefine_line|#define MPINTEN&t;&t;&t;B13_MASK
DECL|macro|SINTEN
mdefine_line|#define SINTEN&t;&t;&t;B12_MASK
DECL|macro|TINTEN3
mdefine_line|#define TINTEN3&t;&t;&t;B11_MASK
DECL|macro|TINTEN2
mdefine_line|#define TINTEN2&t;&t;&t;B10_MASK
DECL|macro|TINTEN1
mdefine_line|#define TINTEN1&t;&t;&t;B9_MASK
DECL|macro|TINTEN0
mdefine_line|#define TINTEN0&t;&t;&t;B8_MASK
multiline_comment|/* VAL0 */
DECL|macro|STINTEN
mdefine_line|#define STINTEN&t;&t;&t;B4_MASK
DECL|macro|RINTEN3
mdefine_line|#define RINTEN3&t;&t;&t;B3_MASK
DECL|macro|RINTEN2
mdefine_line|#define RINTEN2&t;&t;&t;B2_MASK
DECL|macro|RINTEN1
mdefine_line|#define RINTEN1&t;&t;&t;B1_MASK
DECL|macro|RINTEN0
mdefine_line|#define RINTEN0&t;&t;&t;B0_MASK
DECL|macro|INTEN0_CLEAR
mdefine_line|#define INTEN0_CLEAR &t;&t;0x1F7F7F1F /* Command style register */&t;&t;
multiline_comment|/* CMD0&t;&t;&t;&t;0x48, 32bit register */
multiline_comment|/* VAL2 */
DECL|macro|RDMD3
mdefine_line|#define RDMD3&t;&t;&t;B19_MASK
DECL|macro|RDMD2
mdefine_line|#define RDMD2&t;&t;&t;B18_MASK
DECL|macro|RDMD1
mdefine_line|#define RDMD1&t;&t;&t;B17_MASK
DECL|macro|RDMD0
mdefine_line|#define RDMD0&t;&t;&t;B16_MASK
multiline_comment|/* VAL1 */
DECL|macro|TDMD3
mdefine_line|#define TDMD3&t;&t;&t;B11_MASK
DECL|macro|TDMD2
mdefine_line|#define TDMD2&t;&t;&t;B10_MASK
DECL|macro|TDMD1
mdefine_line|#define TDMD1&t;&t;&t;B9_MASK
DECL|macro|TDMD0
mdefine_line|#define TDMD0&t;&t;&t;B8_MASK
multiline_comment|/* VAL0 */
DECL|macro|UINTCMD
mdefine_line|#define UINTCMD&t;&t;&t;B6_MASK
DECL|macro|RX_FAST_SPND
mdefine_line|#define RX_FAST_SPND&t;&t;B5_MASK
DECL|macro|TX_FAST_SPND
mdefine_line|#define TX_FAST_SPND&t;&t;B4_MASK
DECL|macro|RX_SPND
mdefine_line|#define RX_SPND&t;&t;&t;B3_MASK
DECL|macro|TX_SPND
mdefine_line|#define TX_SPND&t;&t;&t;B2_MASK
DECL|macro|INTREN
mdefine_line|#define INTREN&t;&t;&t;B1_MASK
DECL|macro|RUN
mdefine_line|#define RUN&t;&t;&t;B0_MASK
DECL|macro|CMD0_CLEAR
mdefine_line|#define CMD0_CLEAR &t;&t;0x000F0F7F   /* Command style register */&t;
multiline_comment|/* CMD2 &t;&t;&t;0x50, 32bit register */
multiline_comment|/* VAL3 */
DECL|macro|CONDUIT_MODE
mdefine_line|#define CONDUIT_MODE&t;&t;B29_MASK
multiline_comment|/* VAL2 */
DECL|macro|RPA
mdefine_line|#define RPA&t;&t;&t;B19_MASK
DECL|macro|DRCVPA
mdefine_line|#define DRCVPA&t;&t;&t;B18_MASK
DECL|macro|DRCVBC
mdefine_line|#define DRCVBC&t;&t;&t;B17_MASK
DECL|macro|PROM
mdefine_line|#define PROM&t;&t;&t;B16_MASK
multiline_comment|/* VAL1 */
DECL|macro|ASTRP_RCV
mdefine_line|#define ASTRP_RCV&t;&t;B13_MASK
DECL|macro|FCOLL
mdefine_line|#define FCOLL&t;&t;&t;B12_MASK
DECL|macro|EMBA
mdefine_line|#define EMBA&t;&t;&t;B11_MASK
DECL|macro|DXMT2PD
mdefine_line|#define DXMT2PD&t;&t;&t;B10_MASK
DECL|macro|LTINTEN
mdefine_line|#define LTINTEN&t;&t;&t;B9_MASK
DECL|macro|DXMTFCS
mdefine_line|#define DXMTFCS&t;&t;&t;B8_MASK
multiline_comment|/* VAL0 */
DECL|macro|APAD_XMT
mdefine_line|#define APAD_XMT&t;&t;B6_MASK
DECL|macro|DRTY
mdefine_line|#define DRTY&t;&t;&t;B5_MASK
DECL|macro|INLOOP
mdefine_line|#define INLOOP&t;&t;&t;B4_MASK
DECL|macro|EXLOOP
mdefine_line|#define EXLOOP&t;&t;&t;B3_MASK
DECL|macro|REX_RTRY
mdefine_line|#define REX_RTRY&t;&t;B2_MASK
DECL|macro|REX_UFLO
mdefine_line|#define REX_UFLO&t;&t;B1_MASK
DECL|macro|REX_LCOL
mdefine_line|#define REX_LCOL&t;&t;B0_MASK
DECL|macro|CMD2_CLEAR
mdefine_line|#define CMD2_CLEAR &t;&t;0x3F7F3F7F   /* Command style register */
multiline_comment|/* CMD3&t;&t;&t;&t;0x54, 32bit register */
multiline_comment|/* VAL3 */
DECL|macro|ASF_INIT_DONE_ALIAS
mdefine_line|#define ASF_INIT_DONE_ALIAS&t;B29_MASK
multiline_comment|/* VAL2 */
DECL|macro|JUMBO
mdefine_line|#define JUMBO&t;&t;&t;B21_MASK
DECL|macro|VSIZE
mdefine_line|#define VSIZE&t;&t;&t;B20_MASK
DECL|macro|VLONLY
mdefine_line|#define VLONLY&t;&t;&t;B19_MASK
DECL|macro|VL_TAG_DEL
mdefine_line|#define VL_TAG_DEL&t;&t;B18_MASK
multiline_comment|/* VAL1 */
DECL|macro|EN_PMGR
mdefine_line|#define EN_PMGR&t;&t;&t;B14_MASK
DECL|macro|INTLEVEL
mdefine_line|#define INTLEVEL&t;&t;B13_MASK
DECL|macro|FORCE_FULL_DUPLEX
mdefine_line|#define FORCE_FULL_DUPLEX&t;B12_MASK
DECL|macro|FORCE_LINK_STATUS
mdefine_line|#define FORCE_LINK_STATUS&t;B11_MASK
DECL|macro|APEP
mdefine_line|#define APEP&t;&t;&t;B10_MASK
DECL|macro|MPPLBA
mdefine_line|#define MPPLBA&t;&t;&t;B9_MASK
multiline_comment|/* VAL0 */
DECL|macro|RESET_PHY_PULSE
mdefine_line|#define RESET_PHY_PULSE&t;&t;B2_MASK
DECL|macro|RESET_PHY
mdefine_line|#define RESET_PHY&t;&t;B1_MASK
DECL|macro|PHY_RST_POL
mdefine_line|#define PHY_RST_POL&t;&t;B0_MASK
multiline_comment|/* CMD7&t;&t;&t;&t;0x64, 32bit register */
multiline_comment|/* VAL0 */
DECL|macro|PMAT_SAVE_MATCH
mdefine_line|#define PMAT_SAVE_MATCH&t;&t;B4_MASK
DECL|macro|PMAT_MODE
mdefine_line|#define PMAT_MODE&t;&t;B3_MASK
DECL|macro|MPEN_SW
mdefine_line|#define MPEN_SW&t;&t;&t;B1_MASK
DECL|macro|LCMODE_SW
mdefine_line|#define LCMODE_SW&t;&t;B0_MASK
DECL|macro|CMD7_CLEAR
mdefine_line|#define CMD7_CLEAR  &t;&t;0x0000001B&t;&t;/* Command style register */
multiline_comment|/* CTRL0&t;&t;&t;0x68, 32bit register */
DECL|macro|PHY_SEL
mdefine_line|#define PHY_SEL&t;&t;&t;0x03000000&t;/* 25:24 */
DECL|macro|RESET_PHY_WIDTH
mdefine_line|#define RESET_PHY_WIDTH&t;&t;0x00FF0000&t;/* 23:16 */
DECL|macro|BSWP_REGS
mdefine_line|#define BSWP_REGS&t;&t;B10_MASK
DECL|macro|BSWP_DESC
mdefine_line|#define BSWP_DESC&t;&t;B9_MASK
DECL|macro|BSWP_DATA
mdefine_line|#define BSWP_DATA&t;&t;B8_MASK
DECL|macro|CACHE_ALIGN
mdefine_line|#define CACHE_ALIGN&t;&t;B4_MASK
DECL|macro|BURST_LIMIT
mdefine_line|#define BURST_LIMIT&t;&t;0x0000000F&t;/* 3:0 */
multiline_comment|/* CTRL1&t;&t;&t;0x6C, 32bit register */
DECL|macro|SLOTMOD_MASK
mdefine_line|#define SLOTMOD_MASK&t;&t;0x03000000&t;/* 25:24 */
DECL|macro|XMTSP_MASK
mdefine_line|#define XMTSP_MASK&t;&t;0x300&t;/* 17:16 */
DECL|macro|XMTSP_128
mdefine_line|#define XMTSP_128&t;&t;0x200
DECL|macro|XMTSP_64
mdefine_line|#define XMTSP_64&t;&t;0x100
DECL|macro|CRTL1_DEFAULT
mdefine_line|#define CRTL1_DEFAULT&t;&t;0x00000017
multiline_comment|/* CTRL2&t;&t;&t;0x70, 32bit register */
DECL|macro|FS_MASK
mdefine_line|#define FS_MASK&t;&t;&t;0x00070000&t;/* 18:16 */
DECL|macro|FMDC_MASK
mdefine_line|#define FMDC_MASK&t;&t;0x00000300&t;/* 9:8 */
DECL|macro|XPHYRST
mdefine_line|#define XPHYRST&t;&t;&t;B7_MASK
DECL|macro|XPHYANE
mdefine_line|#define XPHYANE&t;&t;&t;B6_MASK
DECL|macro|XPHYFD
mdefine_line|#define XPHYFD&t;&t;&t;B5_MASK
DECL|macro|XPHYSP
mdefine_line|#define XPHYSP&t;&t;&t;B3_MASK&t;/* 4:3 */
DECL|macro|APDW_MASK
mdefine_line|#define APDW_MASK&t;&t;0x00000007&t;/* 2:0 */
multiline_comment|/* RCV_RING_CFG&t;&t;&t;0x78, 16bit register */
DECL|macro|RCV_DROP3
mdefine_line|#define RCV_DROP3&t;&t;B11_MASK
DECL|macro|RCV_DROP2
mdefine_line|#define RCV_DROP2&t;&t;B10_MASK
DECL|macro|RCV_DROP1
mdefine_line|#define RCV_DROP1&t;&t;B9_MASK
DECL|macro|RCV_DROP0
mdefine_line|#define RCV_DROP0&t;&t;B8_MASK
DECL|macro|RCV_RING_DEFAULT
mdefine_line|#define RCV_RING_DEFAULT&t;0x0030&t;/* 5:4 */
DECL|macro|RCV_RING3_EN
mdefine_line|#define RCV_RING3_EN&t;&t;B3_MASK
DECL|macro|RCV_RING2_EN
mdefine_line|#define RCV_RING2_EN&t;&t;B2_MASK
DECL|macro|RCV_RING1_EN
mdefine_line|#define RCV_RING1_EN&t;&t;B1_MASK
DECL|macro|RCV_RING0_EN
mdefine_line|#define RCV_RING0_EN&t;&t;B0_MASK
multiline_comment|/* XMT_RING_LIMIT&t;&t;0x7C, 32bit register */
DECL|macro|XMT_RING2_LIMIT
mdefine_line|#define XMT_RING2_LIMIT&t;&t;0x00FF0000&t;/* 23:16 */
DECL|macro|XMT_RING1_LIMIT
mdefine_line|#define XMT_RING1_LIMIT&t;&t;0x0000FF00&t;/* 15:8 */
DECL|macro|XMT_RING0_LIMIT
mdefine_line|#define XMT_RING0_LIMIT&t;&t;0x000000FF&t;/* 7:0 */
multiline_comment|/* AUTOPOLL0&t;&t;&t;0x88, 16bit register */
DECL|macro|AP_REG0_EN
mdefine_line|#define AP_REG0_EN&t;&t;B15_MASK
DECL|macro|AP_REG0_ADDR_MASK
mdefine_line|#define AP_REG0_ADDR_MASK&t;0x1F00&t;/* 12:8 */
DECL|macro|AP_PHY0_ADDR_MASK
mdefine_line|#define AP_PHY0_ADDR_MASK&t;0x001F&t;/* 4:0 */
multiline_comment|/* AUTOPOLL1&t;&t;&t;0x8A, 16bit register */
DECL|macro|AP_REG1_EN
mdefine_line|#define AP_REG1_EN&t;&t;B15_MASK
DECL|macro|AP_REG1_ADDR_MASK
mdefine_line|#define AP_REG1_ADDR_MASK&t;0x1F00&t;/* 12:8 */
DECL|macro|AP_PRE_SUP1
mdefine_line|#define AP_PRE_SUP1&t;&t;B6_MASK
DECL|macro|AP_PHY1_DFLT
mdefine_line|#define AP_PHY1_DFLT&t;&t;B5_MASK
DECL|macro|AP_PHY1_ADDR_MASK
mdefine_line|#define AP_PHY1_ADDR_MASK&t;0x001F&t;/* 4:0 */
multiline_comment|/* AUTOPOLL2&t;&t;&t;0x8C, 16bit register */
DECL|macro|AP_REG2_EN
mdefine_line|#define AP_REG2_EN&t;&t;B15_MASK
DECL|macro|AP_REG2_ADDR_MASK
mdefine_line|#define AP_REG2_ADDR_MASK&t;0x1F00&t;/* 12:8 */
DECL|macro|AP_PRE_SUP2
mdefine_line|#define AP_PRE_SUP2&t;&t;B6_MASK
DECL|macro|AP_PHY2_DFLT
mdefine_line|#define AP_PHY2_DFLT&t;&t;B5_MASK
DECL|macro|AP_PHY2_ADDR_MASK
mdefine_line|#define AP_PHY2_ADDR_MASK&t;0x001F&t;/* 4:0 */
multiline_comment|/* AUTOPOLL3&t;&t;&t;0x8E, 16bit register */
DECL|macro|AP_REG3_EN
mdefine_line|#define AP_REG3_EN&t;&t;B15_MASK
DECL|macro|AP_REG3_ADDR_MASK
mdefine_line|#define AP_REG3_ADDR_MASK&t;0x1F00&t;/* 12:8 */
DECL|macro|AP_PRE_SUP3
mdefine_line|#define AP_PRE_SUP3&t;&t;B6_MASK
DECL|macro|AP_PHY3_DFLT
mdefine_line|#define AP_PHY3_DFLT&t;&t;B5_MASK
DECL|macro|AP_PHY3_ADDR_MASK
mdefine_line|#define AP_PHY3_ADDR_MASK&t;0x001F&t;/* 4:0 */
multiline_comment|/* AUTOPOLL4&t;&t;&t;0x90, 16bit register */
DECL|macro|AP_REG4_EN
mdefine_line|#define AP_REG4_EN&t;&t;B15_MASK
DECL|macro|AP_REG4_ADDR_MASK
mdefine_line|#define AP_REG4_ADDR_MASK&t;0x1F00&t;/* 12:8 */
DECL|macro|AP_PRE_SUP4
mdefine_line|#define AP_PRE_SUP4&t;&t;B6_MASK
DECL|macro|AP_PHY4_DFLT
mdefine_line|#define AP_PHY4_DFLT&t;&t;B5_MASK
DECL|macro|AP_PHY4_ADDR_MASK
mdefine_line|#define AP_PHY4_ADDR_MASK&t;0x001F&t;/* 4:0 */
multiline_comment|/* AUTOPOLL5&t;&t;&t;0x92, 16bit register */
DECL|macro|AP_REG5_EN
mdefine_line|#define AP_REG5_EN&t;&t;B15_MASK
DECL|macro|AP_REG5_ADDR_MASK
mdefine_line|#define AP_REG5_ADDR_MASK&t;0x1F00&t;/* 12:8 */
DECL|macro|AP_PRE_SUP5
mdefine_line|#define AP_PRE_SUP5&t;&t;B6_MASK
DECL|macro|AP_PHY5_DFLT
mdefine_line|#define AP_PHY5_DFLT&t;&t;B5_MASK
DECL|macro|AP_PHY5_ADDR_MASK
mdefine_line|#define AP_PHY5_ADDR_MASK&t;0x001F&t;/* 4:0 */
multiline_comment|/* AP_VALUE &t;&t;&t;0x98, 32bit ragister */
DECL|macro|AP_VAL_ACTIVE
mdefine_line|#define AP_VAL_ACTIVE&t;&t;B31_MASK
DECL|macro|AP_VAL_RD_CMD
mdefine_line|#define AP_VAL_RD_CMD&t;&t;B29_MASK
DECL|macro|AP_ADDR
mdefine_line|#define AP_ADDR&t;&t;&t;0x00070000&t;/* 18:16 */
DECL|macro|AP_VAL
mdefine_line|#define AP_VAL&t;&t;&t;0x0000FFFF&t;/* 15:0 */
multiline_comment|/* PCS_ANEG&t;&t;&t;0x9C, 32bit register */
DECL|macro|SYNC_LOST
mdefine_line|#define SYNC_LOST&t;&t;B10_MASK
DECL|macro|IMATCH
mdefine_line|#define IMATCH&t;&t;&t;B9_MASK
DECL|macro|CMATCH
mdefine_line|#define CMATCH&t;&t;&t;B8_MASK
DECL|macro|PCS_AN_IDLE
mdefine_line|#define PCS_AN_IDLE&t;&t;B1_MASK
DECL|macro|PCS_AN_CFG
mdefine_line|#define PCS_AN_CFG&t;&t;B0_MASK
multiline_comment|/* DLY_INT_A&t;&t;&t;0xA8, 32bit register */
DECL|macro|DLY_INT_A_R3
mdefine_line|#define DLY_INT_A_R3&t;&t;B31_MASK
DECL|macro|DLY_INT_A_R2
mdefine_line|#define DLY_INT_A_R2&t;&t;B30_MASK
DECL|macro|DLY_INT_A_R1
mdefine_line|#define DLY_INT_A_R1&t;&t;B29_MASK
DECL|macro|DLY_INT_A_R0
mdefine_line|#define DLY_INT_A_R0&t;&t;B28_MASK
DECL|macro|DLY_INT_A_T3
mdefine_line|#define DLY_INT_A_T3&t;&t;B27_MASK
DECL|macro|DLY_INT_A_T2
mdefine_line|#define DLY_INT_A_T2&t;&t;B26_MASK
DECL|macro|DLY_INT_A_T1
mdefine_line|#define DLY_INT_A_T1&t;&t;B25_MASK
DECL|macro|DLY_INT_A_T0
mdefine_line|#define DLY_INT_A_T0&t;&t;B24_MASK
DECL|macro|EVENT_COUNT_A
mdefine_line|#define EVENT_COUNT_A&t;&t;0x00FF0000&t;/* 20:16 */
DECL|macro|MAX_DELAY_TIME_A
mdefine_line|#define MAX_DELAY_TIME_A&t;0x000007FF&t;/* 10:0 */
multiline_comment|/* DLY_INT_B&t;&t;&t;0xAC, 32bit register */
DECL|macro|DLY_INT_B_R3
mdefine_line|#define DLY_INT_B_R3&t;&t;B31_MASK
DECL|macro|DLY_INT_B_R2
mdefine_line|#define DLY_INT_B_R2&t;&t;B30_MASK
DECL|macro|DLY_INT_B_R1
mdefine_line|#define DLY_INT_B_R1&t;&t;B29_MASK
DECL|macro|DLY_INT_B_R0
mdefine_line|#define DLY_INT_B_R0&t;&t;B28_MASK
DECL|macro|DLY_INT_B_T3
mdefine_line|#define DLY_INT_B_T3&t;&t;B27_MASK
DECL|macro|DLY_INT_B_T2
mdefine_line|#define DLY_INT_B_T2&t;&t;B26_MASK
DECL|macro|DLY_INT_B_T1
mdefine_line|#define DLY_INT_B_T1&t;&t;B25_MASK
DECL|macro|DLY_INT_B_T0
mdefine_line|#define DLY_INT_B_T0&t;&t;B24_MASK
DECL|macro|EVENT_COUNT_B
mdefine_line|#define EVENT_COUNT_B&t;&t;0x00FF0000&t;/* 20:16 */
DECL|macro|MAX_DELAY_TIME_B
mdefine_line|#define MAX_DELAY_TIME_B&t;0x000007FF&t;/* 10:0 */
multiline_comment|/* DFC_THRESH2&t;&t;&t;0xC0, 16bit register */
DECL|macro|DFC_THRESH2_HIGH
mdefine_line|#define DFC_THRESH2_HIGH&t;0xFF00&t;/* 15:8 */
DECL|macro|DFC_THRESH2_LOW
mdefine_line|#define DFC_THRESH2_LOW&t;&t;0x00FF&t;/* 7:0 */
multiline_comment|/* DFC_THRESH3&t;&t;&t;0xC2, 16bit register */
DECL|macro|DFC_THRESH3_HIGH
mdefine_line|#define DFC_THRESH3_HIGH&t;0xFF00&t;/* 15:8 */
DECL|macro|DFC_THRESH3_LOW
mdefine_line|#define DFC_THRESH3_LOW&t;&t;0x00FF&t;/* 7:0 */
multiline_comment|/* DFC_THRESH0&t;&t;&t;0xC4, 16bit register */
DECL|macro|DFC_THRESH0_HIGH
mdefine_line|#define DFC_THRESH0_HIGH&t;0xFF00&t;/* 15:8 */
DECL|macro|DFC_THRESH0_LOW
mdefine_line|#define DFC_THRESH0_LOW&t;&t;0x00FF&t;/* 7:0 */
multiline_comment|/* DFC_THRESH1&t;&t;&t;0xC6, 16bit register */
DECL|macro|DFC_THRESH1_HIGH
mdefine_line|#define DFC_THRESH1_HIGH&t;0xFF00&t;/* 15:8 */
DECL|macro|DFC_THRESH1_LOW
mdefine_line|#define DFC_THRESH1_LOW&t;&t;0x00FF&t;/* 7:0 */
multiline_comment|/* FLOW_CONTROL &t;&t;0xC8, 32bit register */
DECL|macro|PAUSE_LEN_CHG
mdefine_line|#define PAUSE_LEN_CHG&t;&t;B30_MASK
DECL|macro|FFC_EN
mdefine_line|#define&t;FFC_EN&t;&t;&t;B28_MASK
DECL|macro|DFC_RING3_EN
mdefine_line|#define DFC_RING3_EN&t;&t;B27_MASK
DECL|macro|DFC_RING2_EN
mdefine_line|#define DFC_RING2_EN&t;&t;B26_MASK
DECL|macro|DFC_RING1_EN
mdefine_line|#define DFC_RING1_EN&t;&t;B25_MASK
DECL|macro|DFC_RING0_EN
mdefine_line|#define DFC_RING0_EN&t;&t;B24_MASK
DECL|macro|FIXP_CONGEST
mdefine_line|#define FIXP_CONGEST&t;&t;B21_MASK
DECL|macro|FPA
mdefine_line|#define FPA&t;&t;&t;B20_MASK
DECL|macro|NPA
mdefine_line|#define NPA&t;&t;&t;B19_MASK
DECL|macro|FIXP
mdefine_line|#define FIXP&t;&t;&t;B18_MASK
DECL|macro|FCPEN
mdefine_line|#define FCPEN&t;&t;&t;B17_MASK
DECL|macro|FCCMD
mdefine_line|#define FCCMD&t;&t;&t;B16_MASK
DECL|macro|PAUSE_LEN
mdefine_line|#define PAUSE_LEN&t;&t;0x0000FFFF&t;/* 15:0 */
multiline_comment|/* FFC THRESH&t;&t;&t;0xCC, 32bit register */
DECL|macro|FFC_HIGH
mdefine_line|#define FFC_HIGH&t;&t;0xFFFF0000&t;/* 31:16 */
DECL|macro|FFC_LOW
mdefine_line|#define FFC_LOW&t;&t;&t;0x0000FFFF&t;/* 15:0 */
multiline_comment|/* PHY_ ACCESS&t;&t;&t;0xD0, 32bit register */
DECL|macro|PHY_CMD_ACTIVE
mdefine_line|#define&t;PHY_CMD_ACTIVE&t;&t;B31_MASK
DECL|macro|PHY_WR_CMD
mdefine_line|#define PHY_WR_CMD&t;&t;B30_MASK
DECL|macro|PHY_RD_CMD
mdefine_line|#define PHY_RD_CMD&t;&t;B29_MASK
DECL|macro|PHY_RD_ERR
mdefine_line|#define PHY_RD_ERR&t;&t;B28_MASK
DECL|macro|PHY_PRE_SUP
mdefine_line|#define PHY_PRE_SUP&t;&t;B27_MASK
DECL|macro|PHY_ADDR
mdefine_line|#define PHY_ADDR&t;&t;0x03E00000&t;/* 25:21 */
DECL|macro|PHY_REG_ADDR
mdefine_line|#define PHY_REG_ADDR&t;&t;0x001F0000&t;/* 20:16 */
DECL|macro|PHY_DATA
mdefine_line|#define PHY_DATA&t;&t;0x0000FFFF&t;/* 15:0 */
multiline_comment|/* LED0..3&t;&t;&t;0xE0..0xE6, 16bit register */
DECL|macro|LEDOUT
mdefine_line|#define LEDOUT&t;&t;&t;B15_MASK
DECL|macro|LEDPOL
mdefine_line|#define LEDPOL&t;&t;&t;B14_MASK
DECL|macro|LEDDIS
mdefine_line|#define LEDDIS&t;&t;&t;B13_MASK
DECL|macro|LEDSTRETCH
mdefine_line|#define LEDSTRETCH&t;&t;B12_MASK
DECL|macro|LED1000
mdefine_line|#define LED1000&t;&t;&t;B8_MASK
DECL|macro|LED100
mdefine_line|#define LED100&t;&t;&t;B7_MASK
DECL|macro|LEDMP
mdefine_line|#define LEDMP&t;&t;&t;B6_MASK
DECL|macro|LEDFD
mdefine_line|#define LEDFD&t;&t;&t;B5_MASK
DECL|macro|LEDLINK
mdefine_line|#define LEDLINK&t;&t;&t;B4_MASK
DECL|macro|LEDRCVMAT
mdefine_line|#define LEDRCVMAT&t;&t;B3_MASK
DECL|macro|LEDXMT
mdefine_line|#define LEDXMT&t;&t;&t;B2_MASK
DECL|macro|LEDRCV
mdefine_line|#define LEDRCV&t;&t;&t;B1_MASK
DECL|macro|LEDCOLOUT
mdefine_line|#define LEDCOLOUT&t;&t;B0_MASK
multiline_comment|/* EEPROM_ACC&t;&t;&t;0x17C, 16bit register */
DECL|macro|PVALID
mdefine_line|#define PVALID&t;&t;&t;B15_MASK
DECL|macro|PREAD
mdefine_line|#define PREAD&t;&t;&t;B14_MASK
DECL|macro|EEDET
mdefine_line|#define EEDET&t;&t;&t;B13_MASK
DECL|macro|EEN
mdefine_line|#define&t;EEN&t;&t;&t;B4_MASK
DECL|macro|ECS
mdefine_line|#define ECS&t;&t;&t;B2_MASK
DECL|macro|EESK
mdefine_line|#define EESK&t;&t;&t;B1_MASK
DECL|macro|edi_edo
mdefine_line|#define edi_edo&t;&t;&t;b0_MASK
multiline_comment|/* PMAT0&t;&t;&t;0x190,&t; 32bit register */
DECL|macro|PMR_ACTIVE
mdefine_line|#define PMR_ACTIVE&t;&t;B31_MASK
DECL|macro|PMR_WR_CMD
mdefine_line|#define PMR_WR_CMD&t;&t;B30_MASK
DECL|macro|PMR_RD_CMD
mdefine_line|#define PMR_RD_CMD&t;&t;B29_MASK
DECL|macro|PMR_BANK
mdefine_line|#define PMR_BANK&t;&t;B28_MASK
DECL|macro|PMR_ADDR
mdefine_line|#define PMR_ADDR&t;&t;0x007F0000&t;/* 22:16 */
DECL|macro|PMR_B4
mdefine_line|#define PMR_B4&t;&t;&t;0x000000FF&t;/* 15:0 */
multiline_comment|/* PMAT1&t;&t;&t;0x194,&t; 32bit register */
DECL|macro|PMR_B3
mdefine_line|#define PMR_B3&t;&t;&t;0xFF000000&t;/* 31:24 */
DECL|macro|PMR_B2
mdefine_line|#define PMR_B2&t;&t;&t;0x00FF0000&t;/* 23:16 */
DECL|macro|PMR_B1
mdefine_line|#define PMR_B1&t;&t;&t;0x0000FF00&t;/* 15:8 */
DECL|macro|PMR_B0
mdefine_line|#define PMR_B0&t;&t;&t;0x000000FF&t;/* 7:0 */
multiline_comment|/************************************************************************/
multiline_comment|/*                                                                      */
multiline_comment|/*                      MIB counter definitions                         */
multiline_comment|/*                                                                      */
multiline_comment|/************************************************************************/
DECL|macro|rcv_miss_pkts
mdefine_line|#define rcv_miss_pkts&t;&t;&t;&t;0x00
DECL|macro|rcv_octets
mdefine_line|#define rcv_octets&t;&t;&t;&t;0x01
DECL|macro|rcv_broadcast_pkts
mdefine_line|#define rcv_broadcast_pkts&t;&t;&t;0x02
DECL|macro|rcv_multicast_pkts
mdefine_line|#define rcv_multicast_pkts&t;&t;&t;0x03
DECL|macro|rcv_undersize_pkts
mdefine_line|#define rcv_undersize_pkts&t;&t;&t;0x04
DECL|macro|rcv_oversize_pkts
mdefine_line|#define rcv_oversize_pkts&t;&t;&t;0x05
DECL|macro|rcv_fragments
mdefine_line|#define rcv_fragments&t;&t;&t;&t;0x06
DECL|macro|rcv_jabbers
mdefine_line|#define rcv_jabbers&t;&t;&t;&t;0x07
DECL|macro|rcv_unicast_pkts
mdefine_line|#define rcv_unicast_pkts&t;&t;&t;0x08
DECL|macro|rcv_alignment_errors
mdefine_line|#define rcv_alignment_errors&t;&t;&t;0x09
DECL|macro|rcv_fcs_errors
mdefine_line|#define rcv_fcs_errors&t;&t;&t;&t;0x0A
DECL|macro|rcv_good_octets
mdefine_line|#define rcv_good_octets&t;&t;&t;&t;0x0B
DECL|macro|rcv_mac_ctrl
mdefine_line|#define rcv_mac_ctrl&t;&t;&t;&t;0x0C
DECL|macro|rcv_flow_ctrl
mdefine_line|#define rcv_flow_ctrl&t;&t;&t;&t;0x0D
DECL|macro|rcv_pkts_64_octets
mdefine_line|#define rcv_pkts_64_octets&t;&t;&t;0x0E
DECL|macro|rcv_pkts_65to127_octets
mdefine_line|#define rcv_pkts_65to127_octets&t;&t;&t;0x0F
DECL|macro|rcv_pkts_128to255_octets
mdefine_line|#define rcv_pkts_128to255_octets&t;&t;0x10
DECL|macro|rcv_pkts_256to511_octets
mdefine_line|#define rcv_pkts_256to511_octets&t;&t;0x11
DECL|macro|rcv_pkts_512to1023_octets
mdefine_line|#define rcv_pkts_512to1023_octets&t;&t;0x12
DECL|macro|rcv_pkts_1024to1518_octets
mdefine_line|#define rcv_pkts_1024to1518_octets&t;&t;0x13
DECL|macro|rcv_unsupported_opcode
mdefine_line|#define rcv_unsupported_opcode&t;&t;&t;0x14
DECL|macro|rcv_symbol_errors
mdefine_line|#define rcv_symbol_errors&t;&t;&t;0x15
DECL|macro|rcv_drop_pkts_ring1
mdefine_line|#define rcv_drop_pkts_ring1&t;&t;&t;0x16
DECL|macro|rcv_drop_pkts_ring2
mdefine_line|#define rcv_drop_pkts_ring2&t;&t;&t;0x17
DECL|macro|rcv_drop_pkts_ring3
mdefine_line|#define rcv_drop_pkts_ring3&t;&t;&t;0x18
DECL|macro|rcv_drop_pkts_ring4
mdefine_line|#define rcv_drop_pkts_ring4&t;&t;&t;0x19
DECL|macro|rcv_jumbo_pkts
mdefine_line|#define rcv_jumbo_pkts&t;&t;&t;&t;0x1A
DECL|macro|xmt_underrun_pkts
mdefine_line|#define xmt_underrun_pkts&t;&t;&t;0x20
DECL|macro|xmt_octets
mdefine_line|#define xmt_octets&t;&t;&t;&t;0x21
DECL|macro|xmt_packets
mdefine_line|#define xmt_packets&t;&t;&t;&t;0x22
DECL|macro|xmt_broadcast_pkts
mdefine_line|#define xmt_broadcast_pkts&t;&t;&t;0x23
DECL|macro|xmt_multicast_pkts
mdefine_line|#define xmt_multicast_pkts&t;&t;&t;0x24
DECL|macro|xmt_collisions
mdefine_line|#define xmt_collisions&t;&t;&t;&t;0x25
DECL|macro|xmt_unicast_pkts
mdefine_line|#define xmt_unicast_pkts&t;&t;&t;0x26
DECL|macro|xmt_one_collision
mdefine_line|#define xmt_one_collision&t;&t;&t;0x27
DECL|macro|xmt_multiple_collision
mdefine_line|#define xmt_multiple_collision&t;&t;&t;0x28
DECL|macro|xmt_deferred_transmit
mdefine_line|#define xmt_deferred_transmit&t;&t;&t;0x29
DECL|macro|xmt_late_collision
mdefine_line|#define xmt_late_collision&t;&t;&t;0x2A
DECL|macro|xmt_excessive_defer
mdefine_line|#define xmt_excessive_defer&t;&t;&t;0x2B
DECL|macro|xmt_loss_carrier
mdefine_line|#define xmt_loss_carrier&t;&t;&t;0x2C
DECL|macro|xmt_excessive_collision
mdefine_line|#define xmt_excessive_collision&t;&t;&t;0x2D
DECL|macro|xmt_back_pressure
mdefine_line|#define xmt_back_pressure&t;&t;&t;0x2E
DECL|macro|xmt_flow_ctrl
mdefine_line|#define xmt_flow_ctrl&t;&t;&t;&t;0x2F
DECL|macro|xmt_pkts_64_octets
mdefine_line|#define xmt_pkts_64_octets&t;&t;&t;0x30
DECL|macro|xmt_pkts_65to127_octets
mdefine_line|#define xmt_pkts_65to127_octets&t;&t;&t;0x31
DECL|macro|xmt_pkts_128to255_octets
mdefine_line|#define xmt_pkts_128to255_octets&t;&t;0x32
DECL|macro|xmt_pkts_256to511_octets
mdefine_line|#define xmt_pkts_256to511_octets&t;&t;0x33
DECL|macro|xmt_pkts_512to1023_octets
mdefine_line|#define xmt_pkts_512to1023_octets&t;&t;0x34
DECL|macro|xmt_pkts_1024to1518_octet
mdefine_line|#define xmt_pkts_1024to1518_octet&t;&t;0x35
DECL|macro|xmt_oversize_pkts
mdefine_line|#define xmt_oversize_pkts&t;&t;&t;0x36
DECL|macro|xmt_jumbo_pkts
mdefine_line|#define xmt_jumbo_pkts&t;&t;&t;&t;0x37
multiline_comment|/* Driver definitions */
DECL|macro|PCI_VENDOR_ID_AMD
mdefine_line|#define&t; PCI_VENDOR_ID_AMD&t;&t;0x1022
DECL|macro|PCI_DEVICE_ID_AMD8111E_7462
mdefine_line|#define  PCI_DEVICE_ID_AMD8111E_7462&t;0x7462
DECL|macro|MAX_UNITS
mdefine_line|#define MAX_UNITS&t;&t;&t;16 /* Maximum number of devices possible */
DECL|macro|NUM_TX_BUFFERS
mdefine_line|#define NUM_TX_BUFFERS&t;&t;&t;32 /* Number of transmit buffers */
DECL|macro|NUM_RX_BUFFERS
mdefine_line|#define NUM_RX_BUFFERS&t;&t;&t;32 /* Number of receive buffers */&t;
DECL|macro|TX_BUFF_MOD_MASK
mdefine_line|#define TX_BUFF_MOD_MASK         &t;31 /* (NUM_TX_BUFFERS -1) */
DECL|macro|RX_BUFF_MOD_MASK
mdefine_line|#define RX_BUFF_MOD_MASK         &t;31 /* (NUM_RX_BUFFERS -1) */
DECL|macro|NUM_TX_RING_DR
mdefine_line|#define NUM_TX_RING_DR&t;&t;&t;32  
DECL|macro|NUM_RX_RING_DR
mdefine_line|#define NUM_RX_RING_DR&t;&t;&t;32 
DECL|macro|TX_RING_DR_MOD_MASK
mdefine_line|#define TX_RING_DR_MOD_MASK         &t;31 /* (NUM_TX_RING_DR -1) */
DECL|macro|RX_RING_DR_MOD_MASK
mdefine_line|#define RX_RING_DR_MOD_MASK         &t;31 /* (NUM_RX_RING_DR -1) */
DECL|macro|MAX_FILTER_SIZE
mdefine_line|#define MAX_FILTER_SIZE&t;&t;&t;64 /* Maximum multicast address */ 
DECL|macro|AMD8111E_MIN_MTU
mdefine_line|#define AMD8111E_MIN_MTU&t; &t;60 &t;
DECL|macro|AMD8111E_MAX_MTU
mdefine_line|#define AMD8111E_MAX_MTU&t;&t;9000&t;&t;&t;
DECL|macro|PKT_BUFF_SZ
mdefine_line|#define PKT_BUFF_SZ&t;&t;&t;1536
DECL|macro|MIN_PKT_LEN
mdefine_line|#define MIN_PKT_LEN&t;&t;&t;60
DECL|macro|ETH_ADDR_LEN
mdefine_line|#define ETH_ADDR_LEN&t;&t;&t;6
DECL|macro|OPTION_VLAN_ENABLE
mdefine_line|#define OPTION_VLAN_ENABLE&t;&t;0x0001
DECL|macro|OPTION_JUMBO_ENABLE
mdefine_line|#define OPTION_JUMBO_ENABLE&t;&t;0x0002
DECL|macro|OPTION_MULTICAST_ENABLE
mdefine_line|#define OPTION_MULTICAST_ENABLE&t;&t;0x0004
DECL|macro|OPTION_WOL_ENABLE
mdefine_line|#define OPTION_WOL_ENABLE&t;&t;0x0008
DECL|macro|OPTION_WAKE_MAGIC_ENABLE
mdefine_line|#define OPTION_WAKE_MAGIC_ENABLE&t;0x0010
DECL|macro|OPTION_WAKE_PHY_ENABLE
mdefine_line|#define OPTION_WAKE_PHY_ENABLE&t;&t;0x0020
DECL|macro|PHY_REG_ADDR_MASK
mdefine_line|#define PHY_REG_ADDR_MASK&t;&t;0x1f
multiline_comment|/* Assume contoller gets data 10 times the maximum processing time */
DECL|macro|REPEAT_CNT
mdefine_line|#define  REPEAT_CNT&t;&t;&t;10; 
multiline_comment|/* amd8111e decriptor flag definitions */
DECL|macro|OWN_BIT
mdefine_line|#define OWN_BIT&t;&t;&t;B15_MASK
DECL|macro|ADD_FCS_BIT
mdefine_line|#define ADD_FCS_BIT&t;&t;B13_MASK
DECL|macro|LTINT_BIT
mdefine_line|#define LTINT_BIT&t;&t;B12_MASK
DECL|macro|STP_BIT
mdefine_line|#define STP_BIT&t;&t;&t;B9_MASK
DECL|macro|ENP_BIT
mdefine_line|#define ENP_BIT&t;&t;&t;B8_MASK
DECL|macro|KILL_BIT
mdefine_line|#define KILL_BIT&t;&t;B6_MASK
DECL|macro|TCC_MASK
mdefine_line|#define TCC_MASK&t;&t;0x0003
DECL|macro|TCC_VLAN_INSERT
mdefine_line|#define TCC_VLAN_INSERT&t;&t;B1_MASK
DECL|macro|TCC_VLAN_REPLACE
mdefine_line|#define TCC_VLAN_REPLACE&t;0x0003
DECL|macro|RESET_RX_FLAGS
mdefine_line|#define RESET_RX_FLAGS&t;&t;0x0000
DECL|macro|ERR_BIT
mdefine_line|#define ERR_BIT &t;&t;B14_MASK
DECL|macro|FRAM_BIT
mdefine_line|#define FRAM_BIT&t;&t;B13_MASK
DECL|macro|OFLO_BIT
mdefine_line|#define OFLO_BIT&t;&t;B12_MASK
DECL|macro|CRC_BIT
mdefine_line|#define CRC_BIT&t;&t;&t;B11_MASK
DECL|macro|PAM_BIT
mdefine_line|#define PAM_BIT&t;&t;&t;B6_MASK
DECL|macro|LAFM_BIT
mdefine_line|#define LAFM_BIT&t;&t;B5_MASK
DECL|macro|BAM_BIT
mdefine_line|#define BAM_BIT&t;&t;&t;B4_MASK
DECL|macro|TT_MASK
mdefine_line|#define TT_MASK&t;&t;&t;0x000c
DECL|macro|TT_VLAN_TAGGED
mdefine_line|#define TT_VLAN_TAGGED&t;&t;0x000c
DECL|macro|TT_PRTY_TAGGED
mdefine_line|#define TT_PRTY_TAGGED&t;&t;0x0008
multiline_comment|/* driver ioctl parameters */
DECL|macro|PHY_ID
mdefine_line|#define PHY_ID &t;&t;&t;0x01&t;/* currently it is fixed */
DECL|macro|AMD8111E_REG_DUMP_LEN
mdefine_line|#define AMD8111E_REG_DUMP_LEN&t;4096&t;/* Memory mapped register length */
multiline_comment|/* amd8111e desriptor format */
DECL|struct|amd8111e_tx_dr
r_struct
id|amd8111e_tx_dr
(brace
DECL|member|buff_count
id|u16
id|buff_count
suffix:semicolon
multiline_comment|/* Size of the buffer pointed by this descriptor */
DECL|member|tx_dr_offset2
id|u16
id|tx_dr_offset2
suffix:semicolon
DECL|member|tag_ctrl_info
id|u16
id|tag_ctrl_info
suffix:semicolon
DECL|member|tag_ctrl_cmd
id|u16
id|tag_ctrl_cmd
suffix:semicolon
DECL|member|buff_phy_addr
id|u32
id|buff_phy_addr
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|amd8111e_rx_dr
r_struct
id|amd8111e_rx_dr
(brace
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|msg_count
id|u16
id|msg_count
suffix:semicolon
multiline_comment|/* Received message len */
DECL|member|tag_ctrl_info
id|u16
id|tag_ctrl_info
suffix:semicolon
DECL|member|buff_count
id|u16
id|buff_count
suffix:semicolon
multiline_comment|/* Len of the buffer pointed by descriptor. */
DECL|member|rx_dr_offset10
id|u16
id|rx_dr_offset10
suffix:semicolon
DECL|member|buff_phy_addr
id|u32
id|buff_phy_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|amd8111e_link_config
r_struct
id|amd8111e_link_config
(brace
DECL|macro|SPEED_INVALID
mdefine_line|#define SPEED_INVALID&t;&t;0xffff
DECL|macro|DUPLEX_INVALID
mdefine_line|#define DUPLEX_INVALID&t;&t;0xff
DECL|macro|AUTONEG_INVALID
mdefine_line|#define AUTONEG_INVALID&t;&t;0xff
DECL|member|orig_phy_option
r_int
r_int
id|orig_phy_option
suffix:semicolon
DECL|member|speed
id|u16
id|speed
suffix:semicolon
DECL|member|duplex
id|u8
id|duplex
suffix:semicolon
DECL|member|autoneg
id|u8
id|autoneg
suffix:semicolon
DECL|member|orig_speed
id|u16
id|orig_speed
suffix:semicolon
DECL|member|orig_duplex
id|u8
id|orig_duplex
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* 32bit alignment */
)brace
suffix:semicolon
DECL|struct|amd8111e_priv
r_struct
id|amd8111e_priv
(brace
DECL|member|tx_ring
r_struct
id|amd8111e_tx_dr
op_star
id|tx_ring
suffix:semicolon
DECL|member|rx_ring
r_struct
id|amd8111e_rx_dr
op_star
id|rx_ring
suffix:semicolon
DECL|member|tx_ring_dma_addr
id|dma_addr_t
id|tx_ring_dma_addr
suffix:semicolon
multiline_comment|/* tx descriptor ring base address */
DECL|member|rx_ring_dma_addr
id|dma_addr_t
id|rx_ring_dma_addr
suffix:semicolon
multiline_comment|/* rx descriptor ring base address */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* Ptr to the associated pci_dev */
DECL|member|amd8111e_net_dev
r_struct
id|net_device
op_star
id|amd8111e_net_dev
suffix:semicolon
multiline_comment|/* ptr to associated net_device */
multiline_comment|/* Transmit and recive skbs */
DECL|member|tx_skbuff
r_struct
id|sk_buff
op_star
id|tx_skbuff
(braket
id|NUM_TX_BUFFERS
)braket
suffix:semicolon
DECL|member|rx_skbuff
r_struct
id|sk_buff
op_star
id|rx_skbuff
(braket
id|NUM_RX_BUFFERS
)braket
suffix:semicolon
multiline_comment|/* Transmit and receive dma mapped addr */
DECL|member|tx_dma_addr
id|dma_addr_t
id|tx_dma_addr
(braket
id|NUM_TX_BUFFERS
)braket
suffix:semicolon
DECL|member|rx_dma_addr
id|dma_addr_t
id|rx_dma_addr
(braket
id|NUM_RX_BUFFERS
)braket
suffix:semicolon
multiline_comment|/* Reg memory mapped address */
DECL|member|mmio
r_void
op_star
id|mmio
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Guard lock */
DECL|member|rx_idx
DECL|member|tx_idx
r_int
r_int
id|rx_idx
comma
id|tx_idx
suffix:semicolon
multiline_comment|/* The next free ring entry */
DECL|member|tx_complete_idx
r_int
r_int
id|tx_complete_idx
suffix:semicolon
DECL|member|tx_ring_complete_idx
r_int
r_int
id|tx_ring_complete_idx
suffix:semicolon
DECL|member|tx_ring_idx
r_int
r_int
id|tx_ring_idx
suffix:semicolon
DECL|member|rx_buff_len
r_int
id|rx_buff_len
suffix:semicolon
multiline_comment|/* Buffer length of rx buffers */
DECL|member|options
r_int
id|options
suffix:semicolon
multiline_comment|/* Options enabled/disabled for the device */
DECL|member|ext_phy_option
r_int
r_int
id|ext_phy_option
suffix:semicolon
DECL|member|link_config
r_struct
id|amd8111e_link_config
id|link_config
suffix:semicolon
DECL|member|pm_cap
r_int
id|pm_cap
suffix:semicolon
DECL|member|next
r_struct
id|net_device
op_star
id|next
suffix:semicolon
macro_line|#if AMD8111E_VLAN_TAG_USED
DECL|member|vlgrp
r_struct
id|vlan_group
op_star
id|vlgrp
suffix:semicolon
macro_line|#endif&t;
DECL|member|opened
r_char
id|opened
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|prev_stats
r_struct
id|net_device_stats
id|prev_stats
suffix:semicolon
DECL|member|mc_list
r_struct
id|dev_mc_list
op_star
id|mc_list
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AMD8111E_READ_REG64
mdefine_line|#define AMD8111E_READ_REG64(_memMapBase, _offset, _pUlData)&t;&bslash;&n;&t;&t;&t;*(u32*)(_pUlData) = readl(_memMapBase + (_offset));&t;&bslash;&n;&t;&t;&t;*((u32*)(_pUlData))+1) = readl(_memMapBase + ((_offset)+4))
DECL|macro|AMD8111E_WRITE_REG64
mdefine_line|#define AMD8111E_WRITE_REG64(_memMapBase, _offset, _pUlData)&t;&bslash;&n;&t;&t;&t;writel(*(u32*)(_pUlData), _memMapBase + (_offset));&t;&bslash;&n;&t;&t;&t;writel(*(u32*)((u8*)(_pUlData)+4), _memMapBase + ((_offset)+4))&t;&bslash;&n;
multiline_comment|/* maps the external speed options to internal value */
DECL|variable|speed_duplex_mapping
r_static
r_int
r_char
id|speed_duplex_mapping
(braket
)braket
op_assign
(brace
id|XPHYANE
comma
multiline_comment|/* Auto-negotiation, speed_duplex option 0 */
l_int|0
comma
multiline_comment|/* 10M Half,  speed_duplex option 1 */
id|XPHYFD
comma
multiline_comment|/* 10M Full,  speed_duplex option 2 */
id|XPHYSP
comma
multiline_comment|/* 100M Half, speed_duplex option 3 */
id|XPHYFD
op_or
id|XPHYSP
multiline_comment|/* 100M Full, speed_duplex option 4 */
)brace
suffix:semicolon
DECL|variable|card_idx
r_static
r_int
id|card_idx
suffix:semicolon
DECL|variable|speed_duplex
r_static
r_int
id|speed_duplex
(braket
id|MAX_UNITS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
macro_line|#endif /* _AMD8111E_H */
eof
