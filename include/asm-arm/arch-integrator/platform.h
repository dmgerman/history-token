multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/* DO NOT EDIT!! - this file automatically generated&n; *                 from .s file by awk -f s2h.awk&n; */
multiline_comment|/**************************************************************************&n; * * Copyright &#xfffd; ARM Limited 1998.  All rights reserved.&n; * ***********************************************************************/
multiline_comment|/* ************************************************************************&n; * &n; *   Integrator address map&n; * &n; * &t;NOTE: This is a multi-hosted header file for use with uHAL and&n; * &t;      supported debuggers.&n; * &n; * &t;$Id: platform.s,v 1.32 2000/02/18 10:51:39 asims Exp $&n; * &n; * ***********************************************************************/
macro_line|#ifndef __address_h
DECL|macro|__address_h
mdefine_line|#define __address_h                     1
multiline_comment|/* ========================================================================&n; *  Integrator definitions&n; * ========================================================================&n; * ------------------------------------------------------------------------&n; *  Memory definitions&n; * ------------------------------------------------------------------------&n; *  Integrator memory map&n; * &n; */
DECL|macro|INTEGRATOR_BOOT_ROM_LO
mdefine_line|#define INTEGRATOR_BOOT_ROM_LO          0x00000000
DECL|macro|INTEGRATOR_BOOT_ROM_HI
mdefine_line|#define INTEGRATOR_BOOT_ROM_HI          0x20000000
DECL|macro|INTEGRATOR_BOOT_ROM_BASE
mdefine_line|#define INTEGRATOR_BOOT_ROM_BASE        INTEGRATOR_BOOT_ROM_HI&t; /*  Normal position */
DECL|macro|INTEGRATOR_BOOT_ROM_SIZE
mdefine_line|#define INTEGRATOR_BOOT_ROM_SIZE        SZ_512K
multiline_comment|/* &n; *  New Core Modules have different amounts of SSRAM, the amount of SSRAM&n; *  fitted can be found in HDR_STAT.&n; * &n; *  The symbol INTEGRATOR_SSRAM_SIZE is kept, however this now refers to&n; *  the minimum amount of SSRAM fitted on any core module.&n; * &n; *  New Core Modules also alias the SSRAM.&n; * &n; */
DECL|macro|INTEGRATOR_SSRAM_BASE
mdefine_line|#define INTEGRATOR_SSRAM_BASE           0x00000000
DECL|macro|INTEGRATOR_SSRAM_ALIAS_BASE
mdefine_line|#define INTEGRATOR_SSRAM_ALIAS_BASE     0x10800000
DECL|macro|INTEGRATOR_SSRAM_SIZE
mdefine_line|#define INTEGRATOR_SSRAM_SIZE           SZ_256K
DECL|macro|INTEGRATOR_FLASH_BASE
mdefine_line|#define INTEGRATOR_FLASH_BASE           0x24000000
DECL|macro|INTEGRATOR_FLASH_SIZE
mdefine_line|#define INTEGRATOR_FLASH_SIZE           SZ_32M
DECL|macro|INTEGRATOR_MBRD_SSRAM_BASE
mdefine_line|#define INTEGRATOR_MBRD_SSRAM_BASE      0x28000000
DECL|macro|INTEGRATOR_MBRD_SSRAM_SIZE
mdefine_line|#define INTEGRATOR_MBRD_SSRAM_SIZE      SZ_512K
multiline_comment|/* &n; *  SDRAM is a SIMM therefore the size is not known.&n; * &n; */
DECL|macro|INTEGRATOR_SDRAM_BASE
mdefine_line|#define INTEGRATOR_SDRAM_BASE           0x00040000
DECL|macro|INTEGRATOR_SDRAM_ALIAS_BASE
mdefine_line|#define INTEGRATOR_SDRAM_ALIAS_BASE     0x80000000
DECL|macro|INTEGRATOR_HDR0_SDRAM_BASE
mdefine_line|#define INTEGRATOR_HDR0_SDRAM_BASE      0x80000000
DECL|macro|INTEGRATOR_HDR1_SDRAM_BASE
mdefine_line|#define INTEGRATOR_HDR1_SDRAM_BASE      0x90000000
DECL|macro|INTEGRATOR_HDR2_SDRAM_BASE
mdefine_line|#define INTEGRATOR_HDR2_SDRAM_BASE      0xA0000000
DECL|macro|INTEGRATOR_HDR3_SDRAM_BASE
mdefine_line|#define INTEGRATOR_HDR3_SDRAM_BASE      0xB0000000
multiline_comment|/* &n; *  Logic expansion modules&n; * &n; */
DECL|macro|INTEGRATOR_LOGIC_MODULES_BASE
mdefine_line|#define INTEGRATOR_LOGIC_MODULES_BASE   0xC0000000
DECL|macro|INTEGRATOR_LOGIC_MODULE0_BASE
mdefine_line|#define INTEGRATOR_LOGIC_MODULE0_BASE   0xC0000000
DECL|macro|INTEGRATOR_LOGIC_MODULE1_BASE
mdefine_line|#define INTEGRATOR_LOGIC_MODULE1_BASE   0xD0000000
DECL|macro|INTEGRATOR_LOGIC_MODULE2_BASE
mdefine_line|#define INTEGRATOR_LOGIC_MODULE2_BASE   0xE0000000
DECL|macro|INTEGRATOR_LOGIC_MODULE3_BASE
mdefine_line|#define INTEGRATOR_LOGIC_MODULE3_BASE   0xF0000000
multiline_comment|/* ------------------------------------------------------------------------&n; *  Integrator header card registers&n; * ------------------------------------------------------------------------&n; * &n; */
DECL|macro|INTEGRATOR_HDR_ID_OFFSET
mdefine_line|#define INTEGRATOR_HDR_ID_OFFSET        0x00
DECL|macro|INTEGRATOR_HDR_PROC_OFFSET
mdefine_line|#define INTEGRATOR_HDR_PROC_OFFSET      0x04
DECL|macro|INTEGRATOR_HDR_OSC_OFFSET
mdefine_line|#define INTEGRATOR_HDR_OSC_OFFSET       0x08
DECL|macro|INTEGRATOR_HDR_CTRL_OFFSET
mdefine_line|#define INTEGRATOR_HDR_CTRL_OFFSET      0x0C
DECL|macro|INTEGRATOR_HDR_STAT_OFFSET
mdefine_line|#define INTEGRATOR_HDR_STAT_OFFSET      0x10
DECL|macro|INTEGRATOR_HDR_LOCK_OFFSET
mdefine_line|#define INTEGRATOR_HDR_LOCK_OFFSET      0x14
DECL|macro|INTEGRATOR_HDR_SDRAM_OFFSET
mdefine_line|#define INTEGRATOR_HDR_SDRAM_OFFSET     0x20
DECL|macro|INTEGRATOR_HDR_INIT_OFFSET
mdefine_line|#define INTEGRATOR_HDR_INIT_OFFSET      0x24&t; /*  CM9x6 */
DECL|macro|INTEGRATOR_HDR_IC_OFFSET
mdefine_line|#define INTEGRATOR_HDR_IC_OFFSET        0x40
DECL|macro|INTEGRATOR_HDR_SPDBASE_OFFSET
mdefine_line|#define INTEGRATOR_HDR_SPDBASE_OFFSET   0x100
DECL|macro|INTEGRATOR_HDR_SPDTOP_OFFSET
mdefine_line|#define INTEGRATOR_HDR_SPDTOP_OFFSET    0x200
DECL|macro|INTEGRATOR_HDR_BASE
mdefine_line|#define INTEGRATOR_HDR_BASE             0x10000000
DECL|macro|INTEGRATOR_HDR_ID
mdefine_line|#define INTEGRATOR_HDR_ID               (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_ID_OFFSET)
DECL|macro|INTEGRATOR_HDR_PROC
mdefine_line|#define INTEGRATOR_HDR_PROC             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_PROC_OFFSET)
DECL|macro|INTEGRATOR_HDR_OSC
mdefine_line|#define INTEGRATOR_HDR_OSC              (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_OSC_OFFSET)
DECL|macro|INTEGRATOR_HDR_CTRL
mdefine_line|#define INTEGRATOR_HDR_CTRL             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_CTRL_OFFSET)
DECL|macro|INTEGRATOR_HDR_STAT
mdefine_line|#define INTEGRATOR_HDR_STAT             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_STAT_OFFSET)
DECL|macro|INTEGRATOR_HDR_LOCK
mdefine_line|#define INTEGRATOR_HDR_LOCK             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_LOCK_OFFSET)
DECL|macro|INTEGRATOR_HDR_SDRAM
mdefine_line|#define INTEGRATOR_HDR_SDRAM            (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_SDRAM_OFFSET)
DECL|macro|INTEGRATOR_HDR_INIT
mdefine_line|#define INTEGRATOR_HDR_INIT             (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_INIT_OFFSET)
DECL|macro|INTEGRATOR_HDR_IC
mdefine_line|#define INTEGRATOR_HDR_IC               (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_IC_OFFSET)
DECL|macro|INTEGRATOR_HDR_SPDBASE
mdefine_line|#define INTEGRATOR_HDR_SPDBASE          (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_SPDBASE_OFFSET)
DECL|macro|INTEGRATOR_HDR_SPDTOP
mdefine_line|#define INTEGRATOR_HDR_SPDTOP           (INTEGRATOR_HDR_BASE + INTEGRATOR_HDR_SPDTOP_OFFSET)
DECL|macro|INTEGRATOR_HDR_CTRL_LED
mdefine_line|#define INTEGRATOR_HDR_CTRL_LED         0x01
DECL|macro|INTEGRATOR_HDR_CTRL_MBRD_DETECH
mdefine_line|#define INTEGRATOR_HDR_CTRL_MBRD_DETECH 0x02
DECL|macro|INTEGRATOR_HDR_CTRL_REMAP
mdefine_line|#define INTEGRATOR_HDR_CTRL_REMAP       0x04
DECL|macro|INTEGRATOR_HDR_CTRL_RESET
mdefine_line|#define INTEGRATOR_HDR_CTRL_RESET       0x08
DECL|macro|INTEGRATOR_HDR_CTRL_HIGHVECTORS
mdefine_line|#define INTEGRATOR_HDR_CTRL_HIGHVECTORS 0x10
DECL|macro|INTEGRATOR_HDR_CTRL_BIG_ENDIAN
mdefine_line|#define INTEGRATOR_HDR_CTRL_BIG_ENDIAN  0x20
DECL|macro|INTEGRATOR_HDR_CTRL_FASTBUS
mdefine_line|#define INTEGRATOR_HDR_CTRL_FASTBUS     0x40
DECL|macro|INTEGRATOR_HDR_CTRL_SYNC
mdefine_line|#define INTEGRATOR_HDR_CTRL_SYNC        0x80
DECL|macro|INTEGRATOR_HDR_OSC_CORE_10MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_10MHz   0x102
DECL|macro|INTEGRATOR_HDR_OSC_CORE_15MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_15MHz   0x107
DECL|macro|INTEGRATOR_HDR_OSC_CORE_20MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_20MHz   0x10C
DECL|macro|INTEGRATOR_HDR_OSC_CORE_25MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_25MHz   0x111
DECL|macro|INTEGRATOR_HDR_OSC_CORE_30MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_30MHz   0x116
DECL|macro|INTEGRATOR_HDR_OSC_CORE_35MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_35MHz   0x11B
DECL|macro|INTEGRATOR_HDR_OSC_CORE_40MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_40MHz   0x120
DECL|macro|INTEGRATOR_HDR_OSC_CORE_45MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_45MHz   0x125
DECL|macro|INTEGRATOR_HDR_OSC_CORE_50MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_50MHz   0x12A
DECL|macro|INTEGRATOR_HDR_OSC_CORE_55MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_55MHz   0x12F
DECL|macro|INTEGRATOR_HDR_OSC_CORE_60MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_60MHz   0x134
DECL|macro|INTEGRATOR_HDR_OSC_CORE_65MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_65MHz   0x139
DECL|macro|INTEGRATOR_HDR_OSC_CORE_70MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_70MHz   0x13E
DECL|macro|INTEGRATOR_HDR_OSC_CORE_75MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_75MHz   0x143
DECL|macro|INTEGRATOR_HDR_OSC_CORE_80MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_80MHz   0x148
DECL|macro|INTEGRATOR_HDR_OSC_CORE_85MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_85MHz   0x14D
DECL|macro|INTEGRATOR_HDR_OSC_CORE_90MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_90MHz   0x152
DECL|macro|INTEGRATOR_HDR_OSC_CORE_95MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_95MHz   0x157
DECL|macro|INTEGRATOR_HDR_OSC_CORE_100MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_100MHz  0x15C
DECL|macro|INTEGRATOR_HDR_OSC_CORE_105MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_105MHz  0x161
DECL|macro|INTEGRATOR_HDR_OSC_CORE_110MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_110MHz  0x166
DECL|macro|INTEGRATOR_HDR_OSC_CORE_115MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_115MHz  0x16B
DECL|macro|INTEGRATOR_HDR_OSC_CORE_120MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_120MHz  0x170
DECL|macro|INTEGRATOR_HDR_OSC_CORE_125MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_125MHz  0x175
DECL|macro|INTEGRATOR_HDR_OSC_CORE_130MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_130MHz  0x17A
DECL|macro|INTEGRATOR_HDR_OSC_CORE_135MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_135MHz  0x17F
DECL|macro|INTEGRATOR_HDR_OSC_CORE_140MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_140MHz  0x184
DECL|macro|INTEGRATOR_HDR_OSC_CORE_145MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_145MHz  0x189
DECL|macro|INTEGRATOR_HDR_OSC_CORE_150MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_150MHz  0x18E
DECL|macro|INTEGRATOR_HDR_OSC_CORE_155MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_155MHz  0x193
DECL|macro|INTEGRATOR_HDR_OSC_CORE_160MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_160MHz  0x198
DECL|macro|INTEGRATOR_HDR_OSC_CORE_MASK
mdefine_line|#define INTEGRATOR_HDR_OSC_CORE_MASK    0x7FF
DECL|macro|INTEGRATOR_HDR_OSC_MEM_10MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_10MHz    0x10C000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_15MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_15MHz    0x116000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_20MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_20MHz    0x120000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_25MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_25MHz    0x12A000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_30MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_30MHz    0x134000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_33MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_33MHz    0x13A000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_40MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_40MHz    0x148000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_50MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_50MHz    0x15C000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_60MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_60MHz    0x170000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_66MHz
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_66MHz    0x17C000
DECL|macro|INTEGRATOR_HDR_OSC_MEM_MASK
mdefine_line|#define INTEGRATOR_HDR_OSC_MEM_MASK     0x7FF000
DECL|macro|INTEGRATOR_HDR_OSC_BUS_MODE_CM7x0
mdefine_line|#define INTEGRATOR_HDR_OSC_BUS_MODE_CM7x0  0x0
DECL|macro|INTEGRATOR_HDR_OSC_BUS_MODE_CM9x0
mdefine_line|#define INTEGRATOR_HDR_OSC_BUS_MODE_CM9x0  0x0800000
DECL|macro|INTEGRATOR_HDR_OSC_BUS_MODE_CM9x6
mdefine_line|#define INTEGRATOR_HDR_OSC_BUS_MODE_CM9x6  0x1000000
DECL|macro|INTEGRATOR_HDR_OSC_BUS_MODE_CM10x00
mdefine_line|#define INTEGRATOR_HDR_OSC_BUS_MODE_CM10x00  0x1800000
DECL|macro|INTEGRATOR_HDR_OSC_BUS_MODE_MASK
mdefine_line|#define INTEGRATOR_HDR_OSC_BUS_MODE_MASK  0x1800000
DECL|macro|INTEGRATOR_HDR_SDRAM_SPD_OK
mdefine_line|#define INTEGRATOR_HDR_SDRAM_SPD_OK     (1 &lt;&lt; 5)
multiline_comment|/* ------------------------------------------------------------------------&n; *  Integrator system registers&n; * ------------------------------------------------------------------------&n; * &n; */
multiline_comment|/* &n; *  System Controller&n; * &n; */
DECL|macro|INTEGRATOR_SC_ID_OFFSET
mdefine_line|#define INTEGRATOR_SC_ID_OFFSET         0x00
DECL|macro|INTEGRATOR_SC_OSC_OFFSET
mdefine_line|#define INTEGRATOR_SC_OSC_OFFSET        0x04
DECL|macro|INTEGRATOR_SC_CTRLS_OFFSET
mdefine_line|#define INTEGRATOR_SC_CTRLS_OFFSET      0x08
DECL|macro|INTEGRATOR_SC_CTRLC_OFFSET
mdefine_line|#define INTEGRATOR_SC_CTRLC_OFFSET      0x0C
DECL|macro|INTEGRATOR_SC_DEC_OFFSET
mdefine_line|#define INTEGRATOR_SC_DEC_OFFSET        0x10
DECL|macro|INTEGRATOR_SC_ARB_OFFSET
mdefine_line|#define INTEGRATOR_SC_ARB_OFFSET        0x14
DECL|macro|INTEGRATOR_SC_PCIENABLE_OFFSET
mdefine_line|#define INTEGRATOR_SC_PCIENABLE_OFFSET  0x18
DECL|macro|INTEGRATOR_SC_LOCK_OFFSET
mdefine_line|#define INTEGRATOR_SC_LOCK_OFFSET       0x1C
DECL|macro|INTEGRATOR_SC_BASE
mdefine_line|#define INTEGRATOR_SC_BASE              0x11000000
DECL|macro|INTEGRATOR_SC_ID
mdefine_line|#define INTEGRATOR_SC_ID                (INTEGRATOR_SC_BASE + INTEGRATOR_SC_ID_OFFSET)
DECL|macro|INTEGRATOR_SC_OSC
mdefine_line|#define INTEGRATOR_SC_OSC               (INTEGRATOR_SC_BASE + INTEGRATOR_SC_OSC_OFFSET)
DECL|macro|INTEGRATOR_SC_CTRLS
mdefine_line|#define INTEGRATOR_SC_CTRLS             (INTEGRATOR_SC_BASE + INTEGRATOR_SC_CTRLS_OFFSET)
DECL|macro|INTEGRATOR_SC_CTRLC
mdefine_line|#define INTEGRATOR_SC_CTRLC             (INTEGRATOR_SC_BASE + INTEGRATOR_SC_CTRLC_OFFSET)
DECL|macro|INTEGRATOR_SC_DEC
mdefine_line|#define INTEGRATOR_SC_DEC               (INTEGRATOR_SC_BASE + INTEGRATOR_SC_DEC_OFFSET)
DECL|macro|INTEGRATOR_SC_ARB
mdefine_line|#define INTEGRATOR_SC_ARB               (INTEGRATOR_SC_BASE + INTEGRATOR_SC_ARB_OFFSET)
DECL|macro|INTEGRATOR_SC_PCIENABLE
mdefine_line|#define INTEGRATOR_SC_PCIENABLE         (INTEGRATOR_SC_BASE + INTEGRATOR_SC_PCIENABLE_OFFSET)
DECL|macro|INTEGRATOR_SC_LOCK
mdefine_line|#define INTEGRATOR_SC_LOCK              (INTEGRATOR_SC_BASE + INTEGRATOR_SC_LOCK_OFFSET)
DECL|macro|INTEGRATOR_SC_OSC_SYS_10MHz
mdefine_line|#define INTEGRATOR_SC_OSC_SYS_10MHz     0x20
DECL|macro|INTEGRATOR_SC_OSC_SYS_15MHz
mdefine_line|#define INTEGRATOR_SC_OSC_SYS_15MHz     0x34
DECL|macro|INTEGRATOR_SC_OSC_SYS_20MHz
mdefine_line|#define INTEGRATOR_SC_OSC_SYS_20MHz     0x48
DECL|macro|INTEGRATOR_SC_OSC_SYS_25MHz
mdefine_line|#define INTEGRATOR_SC_OSC_SYS_25MHz     0x5C
DECL|macro|INTEGRATOR_SC_OSC_SYS_33MHz
mdefine_line|#define INTEGRATOR_SC_OSC_SYS_33MHz     0x7C
DECL|macro|INTEGRATOR_SC_OSC_SYS_MASK
mdefine_line|#define INTEGRATOR_SC_OSC_SYS_MASK      0xFF
DECL|macro|INTEGRATOR_SC_OSC_PCI_25MHz
mdefine_line|#define INTEGRATOR_SC_OSC_PCI_25MHz     0x100
DECL|macro|INTEGRATOR_SC_OSC_PCI_33MHz
mdefine_line|#define INTEGRATOR_SC_OSC_PCI_33MHz     0x0
DECL|macro|INTEGRATOR_SC_OSC_PCI_MASK
mdefine_line|#define INTEGRATOR_SC_OSC_PCI_MASK      0x100
DECL|macro|INTEGRATOR_SC_CTRL_SOFTRST
mdefine_line|#define INTEGRATOR_SC_CTRL_SOFTRST      (1 &lt;&lt; 0)
DECL|macro|INTEGRATOR_SC_CTRL_nFLVPPEN
mdefine_line|#define INTEGRATOR_SC_CTRL_nFLVPPEN     (1 &lt;&lt; 1)
DECL|macro|INTEGRATOR_SC_CTRL_nFLWP
mdefine_line|#define INTEGRATOR_SC_CTRL_nFLWP        (1 &lt;&lt; 2)
DECL|macro|INTEGRATOR_SC_CTRL_URTS0
mdefine_line|#define INTEGRATOR_SC_CTRL_URTS0        (1 &lt;&lt; 4)
DECL|macro|INTEGRATOR_SC_CTRL_UDTR0
mdefine_line|#define INTEGRATOR_SC_CTRL_UDTR0        (1 &lt;&lt; 5)
DECL|macro|INTEGRATOR_SC_CTRL_URTS1
mdefine_line|#define INTEGRATOR_SC_CTRL_URTS1        (1 &lt;&lt; 6)
DECL|macro|INTEGRATOR_SC_CTRL_UDTR1
mdefine_line|#define INTEGRATOR_SC_CTRL_UDTR1        (1 &lt;&lt; 7)
multiline_comment|/* &n; *  External Bus Interface&n; * &n; */
DECL|macro|INTEGRATOR_EBI_BASE
mdefine_line|#define INTEGRATOR_EBI_BASE             0x12000000 
DECL|macro|INTEGRATOR_EBI_CSR0_OFFSET
mdefine_line|#define INTEGRATOR_EBI_CSR0_OFFSET      0x00
DECL|macro|INTEGRATOR_EBI_CSR1_OFFSET
mdefine_line|#define INTEGRATOR_EBI_CSR1_OFFSET      0x04
DECL|macro|INTEGRATOR_EBI_CSR2_OFFSET
mdefine_line|#define INTEGRATOR_EBI_CSR2_OFFSET      0x08
DECL|macro|INTEGRATOR_EBI_CSR3_OFFSET
mdefine_line|#define INTEGRATOR_EBI_CSR3_OFFSET      0x0C
DECL|macro|INTEGRATOR_EBI_LOCK_OFFSET
mdefine_line|#define INTEGRATOR_EBI_LOCK_OFFSET      0x20
DECL|macro|INTEGRATOR_EBI_CSR0
mdefine_line|#define INTEGRATOR_EBI_CSR0             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR0_OFFSET)
DECL|macro|INTEGRATOR_EBI_CSR1
mdefine_line|#define INTEGRATOR_EBI_CSR1             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR1_OFFSET)
DECL|macro|INTEGRATOR_EBI_CSR2
mdefine_line|#define INTEGRATOR_EBI_CSR2             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR2_OFFSET)
DECL|macro|INTEGRATOR_EBI_CSR3
mdefine_line|#define INTEGRATOR_EBI_CSR3             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_CSR3_OFFSET)
DECL|macro|INTEGRATOR_EBI_LOCK
mdefine_line|#define INTEGRATOR_EBI_LOCK             (INTEGRATOR_EBI_BASE + INTEGRATOR_EBI_LOCK_OFFSET)
DECL|macro|INTEGRATOR_EBI_8_BIT
mdefine_line|#define INTEGRATOR_EBI_8_BIT            0x00
DECL|macro|INTEGRATOR_EBI_16_BIT
mdefine_line|#define INTEGRATOR_EBI_16_BIT           0x01
DECL|macro|INTEGRATOR_EBI_32_BIT
mdefine_line|#define INTEGRATOR_EBI_32_BIT           0x02
DECL|macro|INTEGRATOR_EBI_WRITE_ENABLE
mdefine_line|#define INTEGRATOR_EBI_WRITE_ENABLE     0x04
DECL|macro|INTEGRATOR_EBI_SYNC
mdefine_line|#define INTEGRATOR_EBI_SYNC             0x08
DECL|macro|INTEGRATOR_EBI_WS_2
mdefine_line|#define INTEGRATOR_EBI_WS_2             0x00
DECL|macro|INTEGRATOR_EBI_WS_3
mdefine_line|#define INTEGRATOR_EBI_WS_3             0x10
DECL|macro|INTEGRATOR_EBI_WS_4
mdefine_line|#define INTEGRATOR_EBI_WS_4             0x20
DECL|macro|INTEGRATOR_EBI_WS_5
mdefine_line|#define INTEGRATOR_EBI_WS_5             0x30
DECL|macro|INTEGRATOR_EBI_WS_6
mdefine_line|#define INTEGRATOR_EBI_WS_6             0x40
DECL|macro|INTEGRATOR_EBI_WS_7
mdefine_line|#define INTEGRATOR_EBI_WS_7             0x50
DECL|macro|INTEGRATOR_EBI_WS_8
mdefine_line|#define INTEGRATOR_EBI_WS_8             0x60
DECL|macro|INTEGRATOR_EBI_WS_9
mdefine_line|#define INTEGRATOR_EBI_WS_9             0x70
DECL|macro|INTEGRATOR_EBI_WS_10
mdefine_line|#define INTEGRATOR_EBI_WS_10            0x80
DECL|macro|INTEGRATOR_EBI_WS_11
mdefine_line|#define INTEGRATOR_EBI_WS_11            0x90
DECL|macro|INTEGRATOR_EBI_WS_12
mdefine_line|#define INTEGRATOR_EBI_WS_12            0xA0
DECL|macro|INTEGRATOR_EBI_WS_13
mdefine_line|#define INTEGRATOR_EBI_WS_13            0xB0
DECL|macro|INTEGRATOR_EBI_WS_14
mdefine_line|#define INTEGRATOR_EBI_WS_14            0xC0
DECL|macro|INTEGRATOR_EBI_WS_15
mdefine_line|#define INTEGRATOR_EBI_WS_15            0xD0
DECL|macro|INTEGRATOR_EBI_WS_16
mdefine_line|#define INTEGRATOR_EBI_WS_16            0xE0
DECL|macro|INTEGRATOR_EBI_WS_17
mdefine_line|#define INTEGRATOR_EBI_WS_17            0xF0
DECL|macro|INTEGRATOR_CT_BASE
mdefine_line|#define INTEGRATOR_CT_BASE              0x13000000&t; /*  Counter/Timers */
DECL|macro|INTEGRATOR_IC_BASE
mdefine_line|#define INTEGRATOR_IC_BASE              0x14000000&t; /*  Interrupt Controller */
DECL|macro|INTEGRATOR_RTC_BASE
mdefine_line|#define INTEGRATOR_RTC_BASE             0x15000000&t; /*  Real Time Clock */
DECL|macro|INTEGRATOR_UART0_BASE
mdefine_line|#define INTEGRATOR_UART0_BASE           0x16000000&t; /*  UART 0 */
DECL|macro|INTEGRATOR_UART1_BASE
mdefine_line|#define INTEGRATOR_UART1_BASE           0x17000000&t; /*  UART 1 */
DECL|macro|INTEGRATOR_KBD_BASE
mdefine_line|#define INTEGRATOR_KBD_BASE             0x18000000&t; /*  Keyboard */
DECL|macro|INTEGRATOR_MOUSE_BASE
mdefine_line|#define INTEGRATOR_MOUSE_BASE           0x19000000&t; /*  Mouse */
multiline_comment|/* &n; *  LED&squot;s &amp; Switches&n; * &n; */
DECL|macro|INTEGRATOR_DBG_ALPHA_OFFSET
mdefine_line|#define INTEGRATOR_DBG_ALPHA_OFFSET     0x00
DECL|macro|INTEGRATOR_DBG_LEDS_OFFSET
mdefine_line|#define INTEGRATOR_DBG_LEDS_OFFSET      0x04
DECL|macro|INTEGRATOR_DBG_SWITCH_OFFSET
mdefine_line|#define INTEGRATOR_DBG_SWITCH_OFFSET    0x08
DECL|macro|INTEGRATOR_DBG_BASE
mdefine_line|#define INTEGRATOR_DBG_BASE             0x1A000000
DECL|macro|INTEGRATOR_DBG_ALPHA
mdefine_line|#define INTEGRATOR_DBG_ALPHA            (INTEGRATOR_DBG_BASE + INTEGRATOR_DBG_ALPHA_OFFSET)
DECL|macro|INTEGRATOR_DBG_LEDS
mdefine_line|#define INTEGRATOR_DBG_LEDS             (INTEGRATOR_DBG_BASE + INTEGRATOR_DBG_LEDS_OFFSET)
DECL|macro|INTEGRATOR_DBG_SWITCH
mdefine_line|#define INTEGRATOR_DBG_SWITCH           (INTEGRATOR_DBG_BASE + INTEGRATOR_DBG_SWITCH_OFFSET)
DECL|macro|INTEGRATOR_GPIO_BASE
mdefine_line|#define INTEGRATOR_GPIO_BASE            0x1B000000&t; /*  GPIO */
multiline_comment|/* ------------------------------------------------------------------------&n; *  KMI keyboard/mouse definitions&n; * ------------------------------------------------------------------------&n; */
multiline_comment|/* PS2 Keyboard interface */
DECL|macro|KMI0_BASE
mdefine_line|#define KMI0_BASE                       INTEGRATOR_KBD_BASE&t;&t;
multiline_comment|/* PS2 Mouse interface */
DECL|macro|KMI1_BASE
mdefine_line|#define KMI1_BASE                       INTEGRATOR_MOUSE_BASE
multiline_comment|/* KMI definitions are now in include/asm-arm/hardware/amba_kmi.h -- rmk */
multiline_comment|/* ------------------------------------------------------------------------&n; *  Where in the memory map does PCI live?&n; * ------------------------------------------------------------------------&n; *  This represents a fairly liberal usage of address space.  Even though&n; *  the V3 only has two windows (therefore we need to map stuff on the fly),&n; *  we maintain the same addresses, even if they&squot;re not mapped.&n; * &n; */
DECL|macro|PHYS_PCI_MEM_BASE
mdefine_line|#define PHYS_PCI_MEM_BASE               0x40000000   /* 512M to xxx */
multiline_comment|/*  unused 256M from A0000000-AFFFFFFF might be used for I2O ???&n; */
DECL|macro|PHYS_PCI_IO_BASE
mdefine_line|#define PHYS_PCI_IO_BASE                0x60000000   /* 16M to xxx */
multiline_comment|/*  unused (128-16)M from B1000000-B7FFFFFF&n; */
DECL|macro|PHYS_PCI_CONFIG_BASE
mdefine_line|#define PHYS_PCI_CONFIG_BASE            0x61000000   /* 16M to xxx */
multiline_comment|/*  unused ((128-16)M - 64K) from XXX&n; */
DECL|macro|PHYS_PCI_V3_BASE
mdefine_line|#define PHYS_PCI_V3_BASE                0x62000000
DECL|macro|PCI_DRAMSIZE
mdefine_line|#define PCI_DRAMSIZE                    INTEGRATOR_SSRAM_SIZE&t;
multiline_comment|/* &squot;export&squot; these to UHAL */
DECL|macro|UHAL_PCI_IO
mdefine_line|#define UHAL_PCI_IO                     PCI_IO_BASE
DECL|macro|UHAL_PCI_MEM
mdefine_line|#define UHAL_PCI_MEM                    PCI_MEM_BASE
DECL|macro|UHAL_PCI_ALLOC_IO_BASE
mdefine_line|#define UHAL_PCI_ALLOC_IO_BASE          0x00004000
DECL|macro|UHAL_PCI_ALLOC_MEM_BASE
mdefine_line|#define UHAL_PCI_ALLOC_MEM_BASE         PCI_MEM_BASE
DECL|macro|UHAL_PCI_MAX_SLOT
mdefine_line|#define UHAL_PCI_MAX_SLOT               20
multiline_comment|/* ========================================================================&n; *  Start of uHAL definitions&n; * ========================================================================&n; */
multiline_comment|/* ------------------------------------------------------------------------&n; *  Integrator Interrupt Controllers&n; * ------------------------------------------------------------------------&n; * &n; *  Offsets from interrupt controller base &n; * &n; *  System Controller interrupt controller base is&n; * &n; * &t;INTEGRATOR_IC_BASE + (header_number &lt;&lt; 6)&n; * &n; *  Core Module interrupt controller base is&n; * &n; * &t;INTEGRATOR_HDR_IC &n; * &n; */
DECL|macro|IRQ_STATUS
mdefine_line|#define IRQ_STATUS                      0
DECL|macro|IRQ_RAW_STATUS
mdefine_line|#define IRQ_RAW_STATUS                  0x04
DECL|macro|IRQ_ENABLE
mdefine_line|#define IRQ_ENABLE                      0x08
DECL|macro|IRQ_ENABLE_SET
mdefine_line|#define IRQ_ENABLE_SET                  0x08
DECL|macro|IRQ_ENABLE_CLEAR
mdefine_line|#define IRQ_ENABLE_CLEAR                0x0C
DECL|macro|INT_SOFT_SET
mdefine_line|#define INT_SOFT_SET                    0x10
DECL|macro|INT_SOFT_CLEAR
mdefine_line|#define INT_SOFT_CLEAR                  0x14
DECL|macro|FIQ_STATUS
mdefine_line|#define FIQ_STATUS                      0x20
DECL|macro|FIQ_RAW_STATUS
mdefine_line|#define FIQ_RAW_STATUS                  0x24
DECL|macro|FIQ_ENABLE
mdefine_line|#define FIQ_ENABLE                      0x28
DECL|macro|FIQ_ENABLE_SET
mdefine_line|#define FIQ_ENABLE_SET                  0x28
DECL|macro|FIQ_ENABLE_CLEAR
mdefine_line|#define FIQ_ENABLE_CLEAR                0x2C
multiline_comment|/* ------------------------------------------------------------------------&n; *  Interrupts&n; * ------------------------------------------------------------------------&n; * &n; *  &n; *  Each Core Module has two interrupts controllers, one on the core module&n; *  itself and one in the system controller on the motherboard.  The&n; *  READ_INT macro in target.s reads both interrupt controllers and returns&n; *  a 32 bit bitmask, bits 0 to 23 are interrupts from the system controller&n; *  and bits 24 to 31 are from the core module.&n; *  &n; *  The following definitions relate to the bitmask returned by READ_INT.&n; * &n; */
multiline_comment|/* &n; *  As the interrupt bit definitions for FIQ/IRQ there is a common&n; *  set of definitions prefixed INT/INTMASK.  The FIQ/IRQ definitions&n; *  have been left to maintain backwards compatible.&n; * &n; */
multiline_comment|/* &n; *  Interrupt numbers&n; * &n; */
DECL|macro|INT_SOFTINT
mdefine_line|#define INT_SOFTINT                     0
DECL|macro|INT_UARTINT0
mdefine_line|#define INT_UARTINT0                    1
DECL|macro|INT_UARTINT1
mdefine_line|#define INT_UARTINT1                    2
DECL|macro|INT_KMIINT0
mdefine_line|#define INT_KMIINT0                     3
DECL|macro|INT_KMIINT1
mdefine_line|#define INT_KMIINT1                     4
DECL|macro|INT_TIMERINT0
mdefine_line|#define INT_TIMERINT0                   5
DECL|macro|INT_TIMERINT1
mdefine_line|#define INT_TIMERINT1                   6
DECL|macro|INT_TIMERINT2
mdefine_line|#define INT_TIMERINT2                   7
DECL|macro|INT_RTCINT
mdefine_line|#define INT_RTCINT                      8
DECL|macro|INT_EXPINT0
mdefine_line|#define INT_EXPINT0                     9
DECL|macro|INT_EXPINT1
mdefine_line|#define INT_EXPINT1                     10
DECL|macro|INT_EXPINT2
mdefine_line|#define INT_EXPINT2                     11
DECL|macro|INT_EXPINT3
mdefine_line|#define INT_EXPINT3                     12
DECL|macro|INT_PCIINT0
mdefine_line|#define INT_PCIINT0                     13
DECL|macro|INT_PCIINT1
mdefine_line|#define INT_PCIINT1                     14
DECL|macro|INT_PCIINT2
mdefine_line|#define INT_PCIINT2                     15
DECL|macro|INT_PCIINT3
mdefine_line|#define INT_PCIINT3                     16
DECL|macro|INT_V3INT
mdefine_line|#define INT_V3INT                       17
DECL|macro|INT_CPINT0
mdefine_line|#define INT_CPINT0                      18
DECL|macro|INT_CPINT1
mdefine_line|#define INT_CPINT1                      19
DECL|macro|INT_LBUSTIMEOUT
mdefine_line|#define INT_LBUSTIMEOUT                 20
DECL|macro|INT_APCINT
mdefine_line|#define INT_APCINT                      21
DECL|macro|INT_CM_SOFTINT
mdefine_line|#define INT_CM_SOFTINT                  24
DECL|macro|INT_CM_COMMRX
mdefine_line|#define INT_CM_COMMRX                   25
DECL|macro|INT_CM_COMMTX
mdefine_line|#define INT_CM_COMMTX                   26
multiline_comment|/* &n; *  Interrupt bit positions&n; * &n; */
DECL|macro|INTMASK_SOFTINT
mdefine_line|#define INTMASK_SOFTINT                 (1 &lt;&lt; INT_SOFTINT)
DECL|macro|INTMASK_UARTINT0
mdefine_line|#define INTMASK_UARTINT0                (1 &lt;&lt; INT_UARTINT0)
DECL|macro|INTMASK_UARTINT1
mdefine_line|#define INTMASK_UARTINT1                (1 &lt;&lt; INT_UARTINT1)
DECL|macro|INTMASK_KMIINT0
mdefine_line|#define INTMASK_KMIINT0                 (1 &lt;&lt; INT_KMIINT0)
DECL|macro|INTMASK_KMIINT1
mdefine_line|#define INTMASK_KMIINT1                 (1 &lt;&lt; INT_KMIINT1)
DECL|macro|INTMASK_TIMERINT0
mdefine_line|#define INTMASK_TIMERINT0               (1 &lt;&lt; INT_TIMERINT0)
DECL|macro|INTMASK_TIMERINT1
mdefine_line|#define INTMASK_TIMERINT1               (1 &lt;&lt; INT_TIMERINT1)
DECL|macro|INTMASK_TIMERINT2
mdefine_line|#define INTMASK_TIMERINT2               (1 &lt;&lt; INT_TIMERINT2)
DECL|macro|INTMASK_RTCINT
mdefine_line|#define INTMASK_RTCINT                  (1 &lt;&lt; INT_RTCINT)
DECL|macro|INTMASK_EXPINT0
mdefine_line|#define INTMASK_EXPINT0                 (1 &lt;&lt; INT_EXPINT0)
DECL|macro|INTMASK_EXPINT1
mdefine_line|#define INTMASK_EXPINT1                 (1 &lt;&lt; INT_EXPINT1)
DECL|macro|INTMASK_EXPINT2
mdefine_line|#define INTMASK_EXPINT2                 (1 &lt;&lt; INT_EXPINT2)
DECL|macro|INTMASK_EXPINT3
mdefine_line|#define INTMASK_EXPINT3                 (1 &lt;&lt; INT_EXPINT3)
DECL|macro|INTMASK_PCIINT0
mdefine_line|#define INTMASK_PCIINT0                 (1 &lt;&lt; INT_PCIINT0)
DECL|macro|INTMASK_PCIINT1
mdefine_line|#define INTMASK_PCIINT1                 (1 &lt;&lt; INT_PCIINT1)
DECL|macro|INTMASK_PCIINT2
mdefine_line|#define INTMASK_PCIINT2                 (1 &lt;&lt; INT_PCIINT2)
DECL|macro|INTMASK_PCIINT3
mdefine_line|#define INTMASK_PCIINT3                 (1 &lt;&lt; INT_PCIINT3)
DECL|macro|INTMASK_V3INT
mdefine_line|#define INTMASK_V3INT                   (1 &lt;&lt; INT_V3INT)
DECL|macro|INTMASK_CPINT0
mdefine_line|#define INTMASK_CPINT0                  (1 &lt;&lt; INT_CPINT0)
DECL|macro|INTMASK_CPINT1
mdefine_line|#define INTMASK_CPINT1                  (1 &lt;&lt; INT_CPINT1)
DECL|macro|INTMASK_LBUSTIMEOUT
mdefine_line|#define INTMASK_LBUSTIMEOUT             (1 &lt;&lt; INT_LBUSTIMEOUT)
DECL|macro|INTMASK_APCINT
mdefine_line|#define INTMASK_APCINT                  (1 &lt;&lt; INT_APCINT)
DECL|macro|INTMASK_CM_SOFTINT
mdefine_line|#define INTMASK_CM_SOFTINT              (1 &lt;&lt; INT_CM_SOFTINT)
DECL|macro|INTMASK_CM_COMMRX
mdefine_line|#define INTMASK_CM_COMMRX               (1 &lt;&lt; INT_CM_COMMRX)
DECL|macro|INTMASK_CM_COMMTX
mdefine_line|#define INTMASK_CM_COMMTX               (1 &lt;&lt; INT_CM_COMMTX)
multiline_comment|/* &n; *  INTEGRATOR_CM_INT0      - Interrupt number of first CM interrupt&n; *  INTEGRATOR_SC_VALID_INT - Mask of valid system controller interrupts&n; * &n; */
DECL|macro|INTEGRATOR_CM_INT0
mdefine_line|#define INTEGRATOR_CM_INT0              INT_CM_SOFTINT
DECL|macro|INTEGRATOR_SC_VALID_INT
mdefine_line|#define INTEGRATOR_SC_VALID_INT         0x003FFFFF
DECL|macro|MAXIRQNUM
mdefine_line|#define MAXIRQNUM                       31
DECL|macro|MAXFIQNUM
mdefine_line|#define MAXFIQNUM                       31
DECL|macro|MAXSWINUM
mdefine_line|#define MAXSWINUM                       31
multiline_comment|/* ------------------------------------------------------------------------&n; *  LED&squot;s - The header LED is not accessable via the uHAL API&n; * ------------------------------------------------------------------------&n; * &n; */
DECL|macro|GREEN_LED
mdefine_line|#define GREEN_LED                       0x01
DECL|macro|YELLOW_LED
mdefine_line|#define YELLOW_LED                      0x02
DECL|macro|RED_LED
mdefine_line|#define RED_LED                         0x04
DECL|macro|GREEN_LED_2
mdefine_line|#define GREEN_LED_2                     0x08
DECL|macro|ALL_LEDS
mdefine_line|#define ALL_LEDS                        0x0F
DECL|macro|LED_BANK
mdefine_line|#define LED_BANK                        INTEGRATOR_DBG_LEDS
multiline_comment|/* &n; *  Memory definitions - run uHAL out of SSRAM.&n; * &n; */
DECL|macro|uHAL_MEMORY_SIZE
mdefine_line|#define uHAL_MEMORY_SIZE                INTEGRATOR_SSRAM_SIZE
multiline_comment|/* &n; *  Application Flash&n; * &n; */
DECL|macro|FLASH_BASE
mdefine_line|#define FLASH_BASE                      INTEGRATOR_FLASH_BASE
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE                      INTEGRATOR_FLASH_SIZE
DECL|macro|FLASH_END
mdefine_line|#define FLASH_END                       (FLASH_BASE + FLASH_SIZE - 1)
DECL|macro|FLASH_BLOCK_SIZE
mdefine_line|#define FLASH_BLOCK_SIZE                SZ_128K
multiline_comment|/* &n; *  Boot Flash&n; * &n; */
DECL|macro|EPROM_BASE
mdefine_line|#define EPROM_BASE                      INTEGRATOR_BOOT_ROM_HI
DECL|macro|EPROM_SIZE
mdefine_line|#define EPROM_SIZE                      INTEGRATOR_BOOT_ROM_SIZE
DECL|macro|EPROM_END
mdefine_line|#define EPROM_END                       (EPROM_BASE + EPROM_SIZE - 1)
multiline_comment|/* &n; *  Clean base - dummy&n; * &n; */
DECL|macro|CLEAN_BASE
mdefine_line|#define CLEAN_BASE                      EPROM_BASE
multiline_comment|/* &n; *  Timer definitions&n; * &n; *  Only use timer 1 &amp; 2&n; *  (both run at 24MHz and will need the clock divider set to 16).&n; * &n; *  Timer 0 runs at bus frequency and therefore could vary and currently&n; *  uHAL can&squot;t handle that.&n; * &n; */
DECL|macro|INTEGRATOR_TIMER0_BASE
mdefine_line|#define INTEGRATOR_TIMER0_BASE          INTEGRATOR_CT_BASE
DECL|macro|INTEGRATOR_TIMER1_BASE
mdefine_line|#define INTEGRATOR_TIMER1_BASE          (INTEGRATOR_CT_BASE + 0x100)
DECL|macro|INTEGRATOR_TIMER2_BASE
mdefine_line|#define INTEGRATOR_TIMER2_BASE          (INTEGRATOR_CT_BASE + 0x200)
DECL|macro|MAX_TIMER
mdefine_line|#define MAX_TIMER                       2
DECL|macro|MAX_PERIOD
mdefine_line|#define MAX_PERIOD                      699050
DECL|macro|TICKS_PER_uSEC
mdefine_line|#define TICKS_PER_uSEC                  24
multiline_comment|/* &n; *  These are useconds NOT ticks.  &n; * &n; */
DECL|macro|mSEC_1
mdefine_line|#define mSEC_1                          1000
DECL|macro|mSEC_5
mdefine_line|#define mSEC_5                          (mSEC_1 * 5)
DECL|macro|mSEC_10
mdefine_line|#define mSEC_10                         (mSEC_1 * 10)
DECL|macro|mSEC_25
mdefine_line|#define mSEC_25                         (mSEC_1 * 25)
DECL|macro|SEC_1
mdefine_line|#define SEC_1                           (mSEC_1 * 1000)
DECL|macro|INTEGRATOR_CSR_BASE
mdefine_line|#define INTEGRATOR_CSR_BASE             0x10000000
DECL|macro|INTEGRATOR_CSR_SIZE
mdefine_line|#define INTEGRATOR_CSR_SIZE             0x10000000
macro_line|#endif
multiline_comment|/* &t;END */
eof
