multiline_comment|/*&n; * include/asm-ppc/platforms/ibm405lp.h  405LP-specific definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Copyright (C) 2002, International Business Machines Corporation&n; * All Rights Reserved.&n; *&n; * Bishop Brock&n; * IBM Research, Austin Center for Low-Power Computing&n; * bcbrock@us.ibm.com&n; * March, 2002&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM405LP_H__
DECL|macro|__ASM_IBM405LP_H__
mdefine_line|#define __ASM_IBM405LP_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
multiline_comment|/* Machine-specific register naming for the 4xx processors is a mess. It seems&n;   that everyone had a different idea on how to prefix/abbreviate/configure the&n;   DCR numbers and MMIO addresses.  I&squot;m no different! For the 405LP we have&n;   defined all of the DCRs and MMIO address consistently with their names as&n;   documented in the official IBM hardware manual for the processor.&n;&n;   DCRs are all given a DCRN_ prefix, which seems to be the most&n;   common consistent naming scheme in old code (although the official IBM DCR&n;   names are so unique that there&squot;s really little need for the DCRN_).&n;&n;   At the end of the DCR defines several synonyms are defined for backwards&n;   compatibility, but all new code specific to the 405LP uses the consistent&n;   names. &n;&n;   Version 07/24/02 1.1 - Armin&n;        added default pm define&n;*/
multiline_comment|/*****************************************************************************&n; * Directly accessed DCRs&n; *****************************************************************************/
multiline_comment|/* DCRs used for Indirect Access */
DECL|macro|DCRN_SDRAM0_CFGADDR
mdefine_line|#define DCRN_SDRAM0_CFGADDR 0x010&t;/* Memory Ctlr. DCR Address Register */
DECL|macro|DCRN_SDRAM0_CFGDATA
mdefine_line|#define DCRN_SDRAM0_CFGDATA 0x011&t;/* Memory Ctlr. DCR Data Register */
DECL|macro|DCRN_EBC0_CFGADDR
mdefine_line|#define DCRN_EBC0_CFGADDR   0x012&t;/* Peripheral Ctlr. DCR Address Register */
DECL|macro|DCRN_EBC0_CFGDATA
mdefine_line|#define DCRN_EBC0_CFGDATA   0x013&t;/* Peripheral Ctlr. DCR Data Register */
DECL|macro|DCRN_SLA0_CFGADDR
mdefine_line|#define DCRN_SLA0_CFGADDR   0x0e0&t;/* Speech Label Accel. DCR Address Reg. */
DECL|macro|DCRN_SLA0_CFGDATA
mdefine_line|#define DCRN_SLA0_CFGDATA   0x0e1&t;/* Speech Label Accel. DCR Data Reg. */
DECL|macro|DCRN_LCD0_CFGADDR
mdefine_line|#define DCRN_LCD0_CFGADDR   0x3c8&t;/* LCD Ctlr. DCR Address Reg. */
DECL|macro|DCRN_LCD0_CFGDATA
mdefine_line|#define DCRN_LCD0_CFGDATA   0x3c9&t;/* LCD Ctlr. DCR Data Reg. */
multiline_comment|/* On-chip Buses */
DECL|macro|DCRN_PLB0_BESR
mdefine_line|#define DCRN_PLB0_BESR      0x084&t;/* PLB Bus Error Status Register */
DECL|macro|DCRN_PLB0_BEAR
mdefine_line|#define DCRN_PLB0_BEAR      0x086&t;/* PLB Bus Error Address Register */
DECL|macro|DCRN_PLB0_ACR
mdefine_line|#define DCRN_PLB0_ACR       0x087&t;/* PLB Arbiter Control Register */
DECL|macro|DCRN_POB0_BESR0
mdefine_line|#define DCRN_POB0_BESR0     0x0a0&t;/* PLB to OPB Bus Error Status Register 0 */
DECL|macro|DCRN_POB0_BEAR
mdefine_line|#define DCRN_POB0_BEAR      0x0a2&t;/* PLB to OPB Bus Error Address Register */
DECL|macro|DCRN_POB0_BESR1
mdefine_line|#define DCRN_POB0_BESR1     0x0a4&t;/* PLB to OPB Bus Error Status Register 1 */
multiline_comment|/* Clocking and Chip Control */
DECL|macro|DCRN_CPC0_PLLMR
mdefine_line|#define DCRN_CPC0_PLLMR     0x0b0&t;/* PLL Mode Register */
DECL|macro|DCRN_CPC0_CGCR0
mdefine_line|#define DCRN_CPC0_CGCR0     0x0b1&t;/* Clock Generation Control Register 0 */
DECL|macro|DCRN_CPC0_CGCR1
mdefine_line|#define DCRN_CPC0_CGCR1     0x0b2&t;/* Clock Generation Control Register 1 */
DECL|macro|DCRN_CPC0_CR0
mdefine_line|#define DCRN_CPC0_CR0       0x0b5&t;/* Chip Control Register 0 */
DECL|macro|DCRN_CHCR0
mdefine_line|#define DCRN_CHCR0 DCRN_CPC0_CR0
DECL|macro|DCRN_CPC0_CR1
mdefine_line|#define DCRN_CPC0_CR1       0x0b4&t;/* Chip Control Register 1 */
DECL|macro|DCRN_CPC0_PLBAPR
mdefine_line|#define DCRN_CPC0_PLBAPR    0x0b6&t;/* PLB Arbiter Priority Register */
DECL|macro|DCRN_CPC0_JTAGID
mdefine_line|#define DCRN_CPC0_JTAGID    0x0b7&t;/* JTAG ID Register */
multiline_comment|/* Clock and Power Management */
DECL|macro|DCRN_CPMSR_BASE
mdefine_line|#define DCRN_CPMSR_BASE     0x0b8&t;/* CPM Status Register */
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE     0x0ba&t;/* CPM Force Register */
multiline_comment|/* Universal Interrupt Controller */
DECL|macro|DCRN_UIC0_SR
mdefine_line|#define DCRN_UIC0_SR        0x0c0&t;/* UIC Status Register */
DECL|macro|DCRN_UIC0_ER
mdefine_line|#define DCRN_UIC0_ER        0x0c2&t;/* UIC Enable Register */
DECL|macro|DCRN_UIC0_CR
mdefine_line|#define DCRN_UIC0_CR        0x0c3&t;/* UIC Critical Register */
DECL|macro|DCRN_UIC0_PR
mdefine_line|#define DCRN_UIC0_PR        0x0c4&t;/* UIC Polarity Register */
DECL|macro|DCRN_UIC0_TR
mdefine_line|#define DCRN_UIC0_TR        0x0c5&t;/* UIC Triggering Register */
DECL|macro|DCRN_UIC0_MSR
mdefine_line|#define DCRN_UIC0_MSR       0x0c6&t;/* UIC Masked Status Register */
DECL|macro|DCRN_UIC0_VR
mdefine_line|#define DCRN_UIC0_VR        0x0c7&t;/* UIC Vector Register */
DECL|macro|DCRN_UIC0_VCR
mdefine_line|#define DCRN_UIC0_VCR       0x0c8&t;/* UIC Vector Configuration Register */
multiline_comment|/* Real-time Clock */
DECL|macro|DCRN_RTC0_SEC
mdefine_line|#define DCRN_RTC0_SEC       0x140&t;/* RTC Seconds Register */
DECL|macro|DCRN_RTC0_SECAL
mdefine_line|#define DCRN_RTC0_SECAL     0x141&t;/* RTC Seconds Alarm Register */
DECL|macro|DCRN_RTC0_MIN
mdefine_line|#define DCRN_RTC0_MIN       0x142&t;/* RTC Minutes Register */
DECL|macro|DCRN_RTC0_MINAL
mdefine_line|#define DCRN_RTC0_MINAL     0x143&t;/* RTC Minutes Alarm Register */
DECL|macro|DCRN_RTC0_HR
mdefine_line|#define DCRN_RTC0_HR        0x144&t;/* RTC Hours Register */
DECL|macro|DCRN_RTC0_HRAL
mdefine_line|#define DCRN_RTC0_HRAL      0x145&t;/* RTC Hours Alarm Register */
DECL|macro|DCRN_RTC0_DOW
mdefine_line|#define DCRN_RTC0_DOW       0x146&t;/* RTC Day of Week Register */
DECL|macro|DCRN_RTC0_DOM
mdefine_line|#define DCRN_RTC0_DOM       0x147&t;/* RTC Date of Month Register */
DECL|macro|DCRN_RTC0_MONTH
mdefine_line|#define DCRN_RTC0_MONTH     0x148&t;/* RTC Month Register */
DECL|macro|DCRN_RTC0_YEAR
mdefine_line|#define DCRN_RTC0_YEAR      0x149&t;/* RTC Year Register */
DECL|macro|DCRN_RTC0_CR0
mdefine_line|#define DCRN_RTC0_CR0       0x14a&t;/* RTC &quot;A&quot; Register */
DECL|macro|DCRN_RTC0_CR1
mdefine_line|#define DCRN_RTC0_CR1       0x14b&t;/* RTC &quot;B&quot; Register */
DECL|macro|DCRN_RTC0_CR2
mdefine_line|#define DCRN_RTC0_CR2       0x14c&t;/* RTC &quot;C&quot; Register */
DECL|macro|DCRN_RTC0_CR3
mdefine_line|#define DCRN_RTC0_CR3       0x14d&t;/* RTC &quot;D&quot; Register */
DECL|macro|DCRN_RTC0_CEN
mdefine_line|#define DCRN_RTC0_CEN       0x14e&t;/* RTC Century Register */
DECL|macro|DCRN_RTC0_WRAP
mdefine_line|#define DCRN_RTC0_WRAP      0x150&t;/* RTC Wrapper */
multiline_comment|/* Advanced Power Management Controller */
DECL|macro|DCRN_APM0_ISR
mdefine_line|#define DCRN_APM0_ISR &t;     0x160&t;/* APM Interrupt Status Register */
DECL|macro|DCRN_APM0_IER
mdefine_line|#define DCRN_APM0_IER &t;     0x162&t;/* APM Interrupt Enable Register */
DECL|macro|DCRN_APM0_IPR
mdefine_line|#define DCRN_APM0_IPR &t;     0x163&t;/* APM Interrupt Polarity Register */
DECL|macro|DCRN_APM0_ITR
mdefine_line|#define DCRN_APM0_ITR &t;     0x164&t;/* APM Interrupt Trigger Register */
DECL|macro|DCRN_APM0_CFG
mdefine_line|#define DCRN_APM0_CFG  &t;     0x165&t;/* APM Configuration Register */
DECL|macro|DCRN_APM0_SR
mdefine_line|#define DCRN_APM0_SR  &t;     0x166&t;/* APM Status Register */
DECL|macro|DCRN_APM0_ID
mdefine_line|#define DCRN_APM0_ID  &t;     0x167&t;/* APM Revision ID Register */
multiline_comment|/* Triple DES Controller */
DECL|macro|DCRN_TDES0_ADDR
mdefine_line|#define DCRN_TDES0_ADDR      0x180&t;/* TDES OPB Slave Base Address  */
DECL|macro|DCRN_TDES0_CFG
mdefine_line|#define DCRN_TDES0_CFG       0x181&t;/* TDES OPB Slave Configuration */
DECL|macro|DCRN_TDES0_STAT
mdefine_line|#define DCRN_TDES0_STAT      0x182&t;/* TDES Status  */
DECL|macro|DCRN_TDES0_ID
mdefine_line|#define DCRN_TDES0_ID        0x183&t;/* TDES Core ID */
multiline_comment|/* LCD Controller */
DECL|macro|DCRN_LCD0_CFG
mdefine_line|#define DCRN_LCD0_CFG        0x3c0&t;/* LCD Configuration Register */
DECL|macro|DCRN_LCD0_ICR
mdefine_line|#define DCRN_LCD0_ICR        0x3c1&t;/* LCD Interrupt Control Register */
DECL|macro|DCRN_LCD0_ISR
mdefine_line|#define DCRN_LCD0_ISR        0x3c2&t;/* LCD Interrupt Status Register */
DECL|macro|DCRN_LCD0_IMR
mdefine_line|#define DCRN_LCD0_IMR        0x3c3&t;/* LCD Interrupt Mask Register */
multiline_comment|/*****************************************************************************&n; * Indirectly accessed DCRs. Note that unlike direct-access DCRs whose numbers&n; * must be hard-coded into the instruction, indirect-access DCR numbers can be&n; * computed. &n; *****************************************************************************/
multiline_comment|/* Offsets for SDRAM Controler Registers */
DECL|macro|DCRN_SDRAM0_BESR0
mdefine_line|#define DCRN_SDRAM0_BESR0  0x00&t;/* Bus Error Syndrome Register 0 */
DECL|macro|DCRN_SDRAM0_BESR1
mdefine_line|#define DCRN_SDRAM0_BESR1  0x08&t;/* Bus Error Syndrome Register 1 */
DECL|macro|DCRN_SDRAM0_BEAR
mdefine_line|#define DCRN_SDRAM0_BEAR   0x10&t;/* Bus Error Address Register */
DECL|macro|DCRN_SDRAM0_CFG
mdefine_line|#define DCRN_SDRAM0_CFG    0x20&t;/* Memory Controller Options 1 */
DECL|macro|DCRN_SDRAM0_STATUS
mdefine_line|#define DCRN_SDRAM0_STATUS 0x24&t;/* SDRAM controller status */
DECL|macro|DCRN_SDRAM0_RTR
mdefine_line|#define DCRN_SDRAM0_RTR    0x30&t;/* Refresh Timer Register */
DECL|macro|DCRN_SDRAM0_PMIT
mdefine_line|#define DCRN_SDRAM0_PMIT   0x34&t;/* Power Management Idle Timer */
DECL|macro|DCRN_SDRAM0_B0CR
mdefine_line|#define DCRN_SDRAM0_B0CR   0x40&t;/* Memory Bank 0 Configuration */
DECL|macro|DCRN_SDRAM0_B1CR
mdefine_line|#define DCRN_SDRAM0_B1CR   0x44&t;/* Memory Bank 1 Configuration */
DECL|macro|DCRN_SDRAM0_B2CR
mdefine_line|#define DCRN_SDRAM0_B2CR   0x48&t;/* Memory Bank 2 Configuration */
DECL|macro|DCRN_SDRAM0_B3CR
mdefine_line|#define DCRN_SDRAM0_B3CR   0x4c&t;/* Memory Bank 3 Configuration */
DECL|macro|DCRN_SDRAM0_TR
mdefine_line|#define DCRN_SDRAM0_TR     0x80&t;/* Sdram Timing Register 1 */
DECL|macro|DCRN_SDRAM0_ECCCFG
mdefine_line|#define DCRN_SDRAM0_ECCCFG 0x94&t;/* ECC Configuration */
DECL|macro|DCRN_SDRAM0_ECCESR
mdefine_line|#define DCRN_SDRAM0_ECCESR 0x98&t;/* ECC Error Status Register */
DECL|macro|SDRAM0_BANKS
mdefine_line|#define SDRAM0_BANKS           4
DECL|macro|DCRN_SDRAM0_BnCR
mdefine_line|#define DCRN_SDRAM0_BnCR(bank) (0x40 + (4 * (bank)))
multiline_comment|/* Offsets for External Bus Controller Registers */
DECL|macro|DCRN_EBC0_B0CR
mdefine_line|#define DCRN_EBC0_B0CR  0x00&t;/* Peripheral Bank 0 Configuration Register */
DECL|macro|DCRN_EBC0_B1CR
mdefine_line|#define DCRN_EBC0_B1CR  0x01&t;/* Peripheral Bank 1 Configuration Register */
DECL|macro|DCRN_EBC0_B2CR
mdefine_line|#define DCRN_EBC0_B2CR  0x02&t;/* Peripheral Bank 2 Configuration Register */
DECL|macro|DCRN_EBC0_B3CR
mdefine_line|#define DCRN_EBC0_B3CR  0x03&t;/* Peripheral Bank 3 Configuration Register */
DECL|macro|DCRN_EBC0_B4CR
mdefine_line|#define DCRN_EBC0_B4CR  0x04&t;/* Peripheral Bank 4 Configuration Register */
DECL|macro|DCRN_EBC0_B5CR
mdefine_line|#define DCRN_EBC0_B5CR  0x05&t;/* Peripheral Bank 5 Configuration Register */
DECL|macro|DCRN_EBC0_B6CR
mdefine_line|#define DCRN_EBC0_B6CR  0x06&t;/* Peripheral Bank 6 Configuration Register */
DECL|macro|DCRN_EBC0_B7CR
mdefine_line|#define DCRN_EBC0_B7CR  0x07&t;/* Peripheral Bank 7 Configuration Register */
DECL|macro|DCRN_EBC0_B0AP
mdefine_line|#define DCRN_EBC0_B0AP  0x10&t;/* Peripheral Bank 0 Access Parameters */
DECL|macro|DCRN_EBC0_B1AP
mdefine_line|#define DCRN_EBC0_B1AP  0x11&t;/* Peripheral Bank 1 Access Parameters */
DECL|macro|DCRN_EBC0_B2AP
mdefine_line|#define DCRN_EBC0_B2AP  0x12&t;/* Peripheral Bank 2 Access Parameters */
DECL|macro|DCRN_EBC0_B3AP
mdefine_line|#define DCRN_EBC0_B3AP  0x13&t;/* Peripheral Bank 3 Access Parameters */
DECL|macro|DCRN_EBC0_B4AP
mdefine_line|#define DCRN_EBC0_B4AP  0x14&t;/* Peripheral Bank 4 Access Parameters */
DECL|macro|DCRN_EBC0_B5AP
mdefine_line|#define DCRN_EBC0_B5AP  0x15&t;/* Peripheral Bank 5 Access Parameters */
DECL|macro|DCRN_EBC0_B6AP
mdefine_line|#define DCRN_EBC0_B6AP  0x16&t;/* Peripheral Bank 6 Access Parameters */
DECL|macro|DCRN_EBC0_B7AP
mdefine_line|#define DCRN_EBC0_B7AP  0x17&t;/* Peripheral Bank 7 Access Parameters */
DECL|macro|DCRN_EBC0_BEAR
mdefine_line|#define DCRN_EBC0_BEAR  0x20&t;/* Periperal Bus Error Address Register */
DECL|macro|DCRN_EBC0_BESR0
mdefine_line|#define DCRN_EBC0_BESR0 0x21&t;/* Peripheral Bus Error Status Register 0 */
DECL|macro|DCRN_EBC0_BESR1
mdefine_line|#define DCRN_EBC0_BESR1 0x22&t;/* Peripheral Bus Error Status Register 0 */
DECL|macro|DCRN_EBC0_CFG
mdefine_line|#define DCRN_EBC0_CFG   0x23&t;/* External Peripheral Control Register */
DECL|macro|EBC0_BANKS
mdefine_line|#define EBC0_BANKS           8
DECL|macro|DCRN_EBC0_BnCR
mdefine_line|#define DCRN_EBC0_BnCR(bank) (bank)
DECL|macro|DCRN_EBC0_BnAP
mdefine_line|#define DCRN_EBC0_BnAP(bank) (0x10 + (bank))
multiline_comment|/* Offsets for LCD Controller DCRs */
DECL|macro|DCRN_LCD0_DER
mdefine_line|#define DCRN_LCD0_DER    0x80010000&t;/* Display Enable Regsiter */
DECL|macro|DCRN_LCD0_DCFG
mdefine_line|#define DCRN_LCD0_DCFG   0x80010010&t;/* Display Configuration Register */
DECL|macro|DCRN_LCD0_DSR
mdefine_line|#define DCRN_LCD0_DSR    0x80010040&t;/* Display Status Register */
DECL|macro|DCRN_LCD0_FRDR
mdefine_line|#define DCRN_LCD0_FRDR   0x80010080&t;/* Dither and Frame Rate Modulation Reg. */
DECL|macro|DCRN_LCD0_SDR
mdefine_line|#define DCRN_LCD0_SDR    0x800100c0&t;/* Signal Delay Register */
DECL|macro|DCRN_LCD0_ADSR
mdefine_line|#define DCRN_LCD0_ADSR   0x80010100&t;/* Active Display Size Register */
DECL|macro|DCRN_LCD0_TDSR
mdefine_line|#define DCRN_LCD0_TDSR   0x80010104&t;/* Total Display Size Register */
DECL|macro|DCRN_LCD0_FPLCR
mdefine_line|#define DCRN_LCD0_FPLCR  0x80010140&t;/* FPLINE Control Register */
DECL|macro|DCRN_LCD0_FPLOR
mdefine_line|#define DCRN_LCD0_FPLOR  0x80010144&t;/* FPLINE Offset Register */
DECL|macro|DCRN_LCD0_FPFCR
mdefine_line|#define DCRN_LCD0_FPFCR  0x80010148&t;/* FPFRAME Control Register */
DECL|macro|DCRN_LCD0_FPFOR
mdefine_line|#define DCRN_LCD0_FPFOR  0x8001014c&t;/* FPFRAME Control Register */
DECL|macro|DCRN_LCD0_FPSCR
mdefine_line|#define DCRN_LCD0_FPSCR  0x80010150&t;/* FPSHIFT Control Register */
DECL|macro|DCRN_LCD0_FPDRR
mdefine_line|#define DCRN_LCD0_FPDRR  0x80010158&t;/* FPDRDY Control Register */
DECL|macro|DCRN_LCD0_FPDCR
mdefine_line|#define DCRN_LCD0_FPDCR  0x80010160&t;/* FPDATA Control Register */
DECL|macro|DCRN_LCD0_PFBFR
mdefine_line|#define DCRN_LCD0_PFBFR  0x80010800&t;/* Pixel and Frame Buffer Format Reg. */
DECL|macro|DCRN_LCD0_PFR
mdefine_line|#define DCRN_LCD0_PFR    0x80011000&t;/* Pixel Format Register */
DECL|macro|DCRN_LCD0_FBBAR
mdefine_line|#define DCRN_LCD0_FBBAR  0x80011008&t;/* Frame Buffer Base Address Register */
DECL|macro|DCRN_LCD0_STRIDE
mdefine_line|#define DCRN_LCD0_STRIDE 0x8001100c&t;/* Stride Register */
DECL|macro|DCRN_LCD0_PAR
mdefine_line|#define DCRN_LCD0_PAR    0x80011800&t;/* Palette Access Registers Base */
DECL|macro|DCRN_LCD0_CER
mdefine_line|#define DCRN_LCD0_CER    0x80012000&t;/* Cursor Enable Register */
DECL|macro|DCRN_LCD0_CBAR
mdefine_line|#define DCRN_LCD0_CBAR   0x80012008&t;/* Cursor Base Address Register */
DECL|macro|DCRN_LCD0_CLR
mdefine_line|#define DCRN_LCD0_CLR    0x8001200c&t;/* Cursor Location Register */
DECL|macro|DCRN_LCD0_CC0R
mdefine_line|#define DCRN_LCD0_CC0R   0x80012010&t;/* Cursor Color 0 */
DECL|macro|DCRN_LCD0_CC1R
mdefine_line|#define DCRN_LCD0_CC1R   0x80012014&t;/* Cursor Color 1 */
DECL|macro|LCD0_PAR_REGS
mdefine_line|#define LCD0_PAR_REGS     256
DECL|macro|DCRN_LCD0_PARn
mdefine_line|#define DCRN_LCD0_PARn(n) (DCRN_LCD0_PAR + (4 * (n)))
multiline_comment|/* Offsets for Decompression Controller DCRs */
DECL|macro|DCRN_DCP0_ITOR0
mdefine_line|#define DCRN_DCP0_ITOR0   0x00&t;/* Index Table Origin Register 0 */
DECL|macro|DCRN_DCP0_ITOR1
mdefine_line|#define DCRN_DCP0_ITOR1   0x01&t;/* Index Table Origin Register 1 */
DECL|macro|DCRN_DCP0_ITOR2
mdefine_line|#define DCRN_DCP0_ITOR2   0x02&t;/* Index Table Origin Register 2 */
DECL|macro|DCRN_DCP0_ITOR3
mdefine_line|#define DCRN_DCP0_ITOR3   0x03&t;/* Index Table Origin Register 3 */
DECL|macro|DCRN_DCP0_ADDR0
mdefine_line|#define DCRN_DCP0_ADDR0   0x04&t;/* Address Decode Definition Register 0 */
DECL|macro|DCRN_DCP0_ADDR1
mdefine_line|#define DCRN_DCP0_ADDR1   0x05&t;/* Address Decode Definition Register 1 */
DECL|macro|DCRN_DCP0_CFG
mdefine_line|#define DCRN_DCP0_CFG     0x40&t;/* Decompression Controller Cfg. Register */
DECL|macro|DCRN_DCP0_ID
mdefine_line|#define DCRN_DCP0_ID      0x41&t;/* Decompression Controller ID Register */
DECL|macro|DCRN_DCP0_VER
mdefine_line|#define DCRN_DCP0_VER     0x42&t;/* Decompression Controller Version Register */
DECL|macro|DCRN_DCP0_PLBBEAR
mdefine_line|#define DCRN_DCP0_PLBBEAR 0x50&t;/* Bus Error Address Register (PLB) */
DECL|macro|DCRN_DCP0_MEMBEAR
mdefine_line|#define DCRN_DCP0_MEMBEAR 0x51&t;/* Bus Error Address Register (EBC/SDRAM) */
DECL|macro|DCRN_DCP0_ESR
mdefine_line|#define DCRN_DCP0_ESR     0x52&t;/* Bus Error Status Register 0 (Masters 0-3) */
DECL|macro|DCRN_DCP0_RAMn
mdefine_line|#define DCRN_DCP0_RAMn(n) (0x400 + (n))&t;/* Decompression Decode Table Entries&n;&t;&t;&t;&t;&t;   0x400-0x5FF Low 16-bit decode table&n;&t;&t;&t;&t;&t;   0x600-0x7FF High 16-bit decode table&n;&t;&t;&t;&t;&t; */
multiline_comment|/* Offsets for Speech Label Accelerator DCRs */
DECL|macro|DCRN_SLA0_CR
mdefine_line|#define DCRN_SLA0_CR    0x00&t;/* SLA Control Register */
DECL|macro|DCRN_SLA0_SR
mdefine_line|#define DCRN_SLA0_SR    0x01&t;/* SLA Status Register */
DECL|macro|DCRN_SLA0_BESR
mdefine_line|#define DCRN_SLA0_BESR  0x02&t;/* SLA Bus Error Status Register */
DECL|macro|DCRN_SLA0_BEAR
mdefine_line|#define DCRN_SLA0_BEAR  0x03&t;/* SLA Bus Error Address Register */
DECL|macro|DCRN_SLA0_UADDR
mdefine_line|#define DCRN_SLA0_UADDR 0x04&t;/* SLA PLB Upper Address Register */
DECL|macro|DCRN_SLA0_GMBA
mdefine_line|#define DCRN_SLA0_GMBA  0x05&t;/* SLA General Indirect Memory Base Address */
DECL|macro|DCRN_SLA0_GMLL
mdefine_line|#define DCRN_SLA0_GMLL  0x06&t;/* SLA General Indirect Memory Link List */
DECL|macro|DCRN_SLA0_AMBA
mdefine_line|#define DCRN_SLA0_AMBA  0x07&t;/* SLA Atom Memory Base Address Register */
DECL|macro|DCRN_SLA0_ACBA
mdefine_line|#define DCRN_SLA0_ACBA  0x08&t;/* SLA Accumulator Base Address Register */
DECL|macro|DCRN_SLA0_DIBA
mdefine_line|#define DCRN_SLA0_DIBA  0x09&t;/* SLA Done Indication Base Address Register */
DECL|macro|DCRN_SLA0_GPOFF
mdefine_line|#define DCRN_SLA0_GPOFF 0x0A&t;/* SLA General Indirect Pass Offset Register */
DECL|macro|DCRN_SLA0_SLPMD
mdefine_line|#define DCRN_SLA0_SLPMD 0x0B&t;/* SLA Sleep Mode Control Register */
DECL|macro|DCRN_SLA0_ID
mdefine_line|#define DCRN_SLA0_ID    0x0C&t;/* SLA ID Register */
DECL|macro|DCRN_SLA0_GMLLR
mdefine_line|#define DCRN_SLA0_GMLLR 0x0D&t;/* SLA General Indirect Memory Link List Reset */
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE&t;0x100
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE&t;0x108
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE&t;0x110
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE&t;0x118
DECL|macro|DCRNCAP_DMA_SG
mdefine_line|#define DCRNCAP_DMA_SG&t;1&t;/* have DMA scatter/gather capability */
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE&t;0x120
DECL|macro|DCRN_EBC_BASE
mdefine_line|#define DCRN_EBC_BASE&t;0x012
DECL|macro|DCRN_DCP0_BASE
mdefine_line|#define DCRN_DCP0_BASE&t;0x014
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE&t;0x0C0
DECL|macro|UIC0
mdefine_line|#define UIC0&t;DCRN_UIC0_BASE
DECL|macro|NR_UICS
macro_line|#undef NR_UICS
DECL|macro|NR_UICS
mdefine_line|#define NR_UICS&t;1
multiline_comment|/* More memory-mapped I/O bases, etc., esp. for OCP, that should be moved&n;   elsewhere. */
DECL|macro|IIC0_BASE
mdefine_line|#define IIC0_BASE&t;0xEF600500
DECL|macro|OPB0_BASE
mdefine_line|#define OPB0_BASE&t;0xEF600600
DECL|macro|GPIO0_BASE
mdefine_line|#define GPIO0_BASE&t;0xEF600700
DECL|macro|IIC0_IRQ
mdefine_line|#define IIC0_IRQ&t;2
multiline_comment|/****************************************************************************&n; * MMIO Addresses&n; ***************************************************************************/
multiline_comment|/* Touch Panel/PWM Controller */
DECL|macro|TPC0_IO_BASE
mdefine_line|#define TPC0_IO_BASE   0xef600a00
DECL|macro|TPC_CR
mdefine_line|#define TPC_CR   0x00&t;&t;/* TPC Command Register */
DECL|macro|TPC_PCRX
mdefine_line|#define TPC_PCRX 0x04&t;&t;/* TPC Precharge Count Register X1 */
DECL|macro|TPC_DCRX
mdefine_line|#define TPC_DCRX 0x08&t;&t;/* TPC Discharge Count Register X1 */
DECL|macro|TPC_PCRY
mdefine_line|#define TPC_PCRY 0x0c&t;&t;/* TPC Precharge Count Register Y1 */
DECL|macro|TPC_DCRY
mdefine_line|#define TPC_DCRY 0x10&t;&t;/* TPC Discharge Count Register Y1 */
DECL|macro|TPC_RRX
mdefine_line|#define TPC_RRX  0x14&t;&t;/* TPC Read Register X1 */
DECL|macro|TPC_RRY
mdefine_line|#define TPC_RRY  0x18&t;&t;/* TPC Read Register Y1 */
DECL|macro|TPC_SRX
mdefine_line|#define TPC_SRX  0x1c&t;&t;/* TPC Status Register X1 */
DECL|macro|TPC_SRY
mdefine_line|#define TPC_SRY  0x20&t;&t;/* TPC Status Register Y1 */
multiline_comment|/* Triple-DES Controller */
DECL|macro|TDES0_IO_BASE
mdefine_line|#define TDES0_IO_BASE  0xef600b00
multiline_comment|/*****************************************************************************&n; * CPM bits for the 405LP.  &n; *****************************************************************************/
DECL|macro|CPM_BITMASK
mdefine_line|#define CPM_BITMASK(i) (((unsigned)0x80000000) &gt;&gt; i)
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0   CPM_BITMASK(0)&t;/* IIC Interface */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU    CPM_BITMASK(1)&t;/* Processor Core */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA    CPM_BITMASK(3)&t;/* DMA Controller */
DECL|macro|IBM_CPM_OPB
mdefine_line|#define IBM_CPM_OPB    CPM_BITMASK(4)&t;/* PLB to OPB Bridge */
DECL|macro|IBM_CPM_DCP
mdefine_line|#define IBM_CPM_DCP    CPM_BITMASK(5)&t;/* CodePack */
DECL|macro|IBM_CPM_EBC
mdefine_line|#define IBM_CPM_EBC    CPM_BITMASK(6)&t;/* ROM/SRAM Peripheral Controller */
DECL|macro|IBM_CPM_SDRAM0
mdefine_line|#define IBM_CPM_SDRAM0 CPM_BITMASK(7)&t;/* SDRAM memory controller */
DECL|macro|IBM_CPM_PLB
mdefine_line|#define IBM_CPM_PLB    CPM_BITMASK(8)&t;/* PLB bus arbiter */
DECL|macro|IBM_CPM_GPIO0
mdefine_line|#define IBM_CPM_GPIO0  CPM_BITMASK(9)&t;/* General Purpose IO (??) */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0  CPM_BITMASK(10)&t;/* Serial Port 0 */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1  CPM_BITMASK(11)&t;/* Serial Port 1 */
DECL|macro|IBM_CPM_UIC
mdefine_line|#define IBM_CPM_UIC    CPM_BITMASK(12)&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK CPM_BITMASK(13)&t;/* CPU Timers */
DECL|macro|IBM_CPM_SLA
mdefine_line|#define IBM_CPM_SLA    CPM_BITMASK(14)&t;/* Speech Label Accelerator */
DECL|macro|IBM_CPM_CSI
mdefine_line|#define IBM_CPM_CSI    CPM_BITMASK(15)&t;/* CODEC Serial Interface */
DECL|macro|IBM_CPM_TPC
mdefine_line|#define IBM_CPM_TPC    CPM_BITMASK(16)&t;/* Touch Panel Controller */
DECL|macro|IBM_CPM_TDES
mdefine_line|#define IBM_CPM_TDES   CPM_BITMASK(18)&t;/* Triple DES */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM 0 /* for now until we get a better hable on this one - armin */
multiline_comment|/*****************************************************************************&n; * UIC IRQ ordinals for the 405LP.  IRQ bit names are as documented in the&n; * 405LP manual (except for reserved fields).  Backwards-compatible synonyms&n; * appear at the end.&n; *****************************************************************************/
DECL|macro|UIC_IRQ_U0
mdefine_line|#define UIC_IRQ_U0    0&t;&t;/* UART0 */
DECL|macro|UIC_IRQ_U1
mdefine_line|#define UIC_IRQ_U1    1&t;&t;/* UART1 */
DECL|macro|UIC_IRQ_IIC
mdefine_line|#define UIC_IRQ_IIC   2&t;&t;/* IIC */
DECL|macro|UIC_IRQ_EM
mdefine_line|#define UIC_IRQ_EM    3&t;&t;/* EBC ??? */
DECL|macro|UIC_IRQ_IRQ4
mdefine_line|#define UIC_IRQ_IRQ4  4&t;&t;/* Reserved */
DECL|macro|UIC_IRQ_D0
mdefine_line|#define UIC_IRQ_D0    5&t;&t;/* DMA Channel 0 */
DECL|macro|UIC_IRQ_D1
mdefine_line|#define UIC_IRQ_D1    6&t;&t;/* DMA Channel 1 */
DECL|macro|UIC_IRQ_D2
mdefine_line|#define UIC_IRQ_D2    7&t;&t;/* DMA Channel 2 */
DECL|macro|UIC_IRQ_D3
mdefine_line|#define UIC_IRQ_D3    8&t;&t;/* DMA Channel 3 */
DECL|macro|UIC_IRQ_IRQ9
mdefine_line|#define UIC_IRQ_IRQ9  9&t;&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ10
mdefine_line|#define UIC_IRQ_IRQ10 10&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ11
mdefine_line|#define UIC_IRQ_IRQ11 11&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ12
mdefine_line|#define UIC_IRQ_IRQ12 12&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ13
mdefine_line|#define UIC_IRQ_IRQ13 13&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ14
mdefine_line|#define UIC_IRQ_IRQ14 14&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ15
mdefine_line|#define UIC_IRQ_IRQ15 15&t;/* Reserved */
DECL|macro|UIC_IRQ_IRQ16
mdefine_line|#define UIC_IRQ_IRQ16 16&t;/* Reserved */
DECL|macro|UIC_IRQ_EC
mdefine_line|#define UIC_IRQ_EC    17&t;/* ECC Correctable Error ??? */
DECL|macro|UIC_IRQ_TPX
mdefine_line|#define UIC_IRQ_TPX   18&t;/* Touch Panel X */
DECL|macro|UIC_IRQ_TPY
mdefine_line|#define UIC_IRQ_TPY   19&t;/* Touch Panel Y */
DECL|macro|UIC_IRQ_SLA
mdefine_line|#define UIC_IRQ_SLA   20&t;/* SLA Interrupt */
DECL|macro|UIC_IRQ_CSI
mdefine_line|#define UIC_IRQ_CSI   21&t;/* CSI Interrupt */
DECL|macro|UIC_IRQ_LCD
mdefine_line|#define UIC_IRQ_LCD   22&t;/* LCD Interrupt */
DECL|macro|UIC_IRQ_RTC
mdefine_line|#define UIC_IRQ_RTC   23&t;/* RTC Interrupt */
DECL|macro|UIC_IRQ_APM
mdefine_line|#define UIC_IRQ_APM   24&t;/* APM Interrupt */
DECL|macro|UIC_IRQ_EIR0
mdefine_line|#define UIC_IRQ_EIR0  25&t;/* External IRQ 0 */
DECL|macro|UIC_IRQ_EIR1
mdefine_line|#define UIC_IRQ_EIR1  26&t;/* External IRQ 1 */
DECL|macro|UIC_IRQ_EIR2
mdefine_line|#define UIC_IRQ_EIR2  27&t;/* External IRQ 2 */
DECL|macro|UIC_IRQ_EIR3
mdefine_line|#define UIC_IRQ_EIR3  28&t;/* External IRQ 3 */
DECL|macro|UIC_IRQ_EIR4
mdefine_line|#define UIC_IRQ_EIR4  29&t;/* External IRQ 4 */
DECL|macro|UIC_IRQ_EIR5
mdefine_line|#define UIC_IRQ_EIR5  30&t;/* External IRQ 5 */
DECL|macro|UIC_IRQ_EIR6
mdefine_line|#define UIC_IRQ_EIR6  31&t;/* External IRQ 6 */
multiline_comment|/*****************************************************************************&n; * Serial port definitions&n; *****************************************************************************/
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;4
macro_line|#endif
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;UIC_IRQ_U0
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;UIC_IRQ_U1
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;0xEF600300
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;0xEF600400
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base:(u8 *) UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
macro_line|#if defined(CONFIG_UART0_TTYS0)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE    UART0_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS        &bslash;&n;        STD_UART_OP(0)          &bslash;&n;        STD_UART_OP(1)
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS1)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE    UART1_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS        &bslash;&n;        STD_UART_OP(1)          &bslash;&n;        STD_UART_OP(0)
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/****************************************************************************&n; * DCR type structures and field definitions for DCRs manipulated by the 405LP&n; * Linux port&n; ****************************************************************************/
multiline_comment|/* APM0_CFG - APM Configuration Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|17
suffix:semicolon
DECL|member|isp
r_int
r_int
id|isp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Initiate Sleep */
DECL|member|ewt
r_int
r_int
id|ewt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Enable Watchdog Timer */
DECL|member|sm
r_int
r_int
id|sm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Sleep Mode */
DECL|member|iica
r_int
r_int
id|iica
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* I2C Address (low-order 3 bits) */
DECL|member|psc
r_int
r_int
id|psc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Power Select Control */
DECL|member|cdiv
r_int
r_int
id|cdiv
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* IIC Clock Divider */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Valid bit */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|apm0_cfg_t
)brace
id|apm0_cfg_t
suffix:semicolon
DECL|macro|APM0_CFG_MASK
mdefine_line|#define APM0_CFG_MASK 0xffff8000&t;/* AND to clear all non-reserved fields */
multiline_comment|/* APM0_SR - APM Status Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|17
suffix:semicolon
DECL|member|cdet
r_int
r_int
id|cdet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Clock Detect */
DECL|member|en
r_int
r_int
id|en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* APM Enable Indicator */
DECL|member|rset
r_int
r_int
id|rset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Processor Reset by APM? */
DECL|member|pfr
r_int
r_int
id|pfr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Power Fail Reset? */
DECL|member|rsrt
r_int
r_int
id|rsrt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Restart Successful? */
DECL|member|sdwn
r_int
r_int
id|sdwn
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Shutdown Complete */
DECL|member|errc
r_int
r_int
id|errc
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Error Code */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Valid Bit */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|apm0_sr_t
)brace
id|apm0_sr_t
suffix:semicolon
DECL|macro|APM0_SR_MASK
mdefine_line|#define APM0_SR_MASK 0xffff8000&t;/* AND to clear all non-reserved fields */
multiline_comment|/* APM0_IER -- APM Interrupt Enable Register&n;   APM0_IPR -- APM Interrupt Polarity Register&n;   APM0_ISR -- APM Interrupt Status Register&n;   APM0_ITR -- APM Interrupt Trigger Register &n;&n;   The interrupts are also accessed via standard interrupt numbers:&n;&n;   59 : Wake-up Input 0&n;   60 : Wake-up Input 1&n;   61 : Wake-up Input 2&n;   62 : Real-Time Clock Interrupt&n;*/
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|27
suffix:semicolon
DECL|member|wi0e
r_int
r_int
id|wi0e
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi1e
r_int
r_int
id|wi1e
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi2e
r_int
r_int
id|wi2e
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cie
r_int
r_int
id|cie
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|apm0_ier_t
)brace
id|apm0_ier_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|27
suffix:semicolon
DECL|member|wi0p
r_int
r_int
id|wi0p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi1p
r_int
r_int
id|wi1p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi2p
r_int
r_int
id|wi2p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cip
r_int
r_int
id|cip
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|apm0_ipr_t
)brace
id|apm0_ipr_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|27
suffix:semicolon
DECL|member|wi0s
r_int
r_int
id|wi0s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi1s
r_int
r_int
id|wi1s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi2s
r_int
r_int
id|wi2s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cis
r_int
r_int
id|cis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|apm0_isr_t
)brace
id|apm0_isr_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|27
suffix:semicolon
DECL|member|wi0t
r_int
r_int
id|wi0t
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi1t
r_int
r_int
id|wi1t
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wi2t
r_int
r_int
id|wi2t
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cit
r_int
r_int
id|cit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|apm0_itr_t
)brace
id|apm0_itr_t
suffix:semicolon
DECL|macro|APM0_IER_MASK
mdefine_line|#define APM0_IER_MASK 0xffffffe0&t;/* AND to clear all non-reserved fields */
DECL|macro|APM0_IPR_MASK
mdefine_line|#define APM0_IPR_MASK 0xffffffe0&t;/* AND to clear all non-reserved fields */
DECL|macro|APM0_ISR_MASK
mdefine_line|#define APM0_ISR_MASK 0xffffffe0&t;/* AND to clear all non-reserved fields */
DECL|macro|APM0_ITR_MASK
mdefine_line|#define APM0_ITR_MASK 0xffffffe0&t;/* AND to clear all non-reserved fields */
multiline_comment|/* CPC0_PLLMR - PLL Mode Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|pmul
r_int
r_int
id|pmul
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* PLL Multiplier */
DECL|member|pdiv
r_int
r_int
id|pdiv
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* PLL Divider */
DECL|member|tun
r_int
r_int
id|tun
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* PLL Tuning Control */
DECL|member|db2
r_int
r_int
id|db2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Divide VCO by 2 Select */
DECL|member|csel
r_int
r_int
id|csel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* PLL Clock Output Select */
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Valid bit */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|cpc0_pllmr_t
)brace
id|cpc0_pllmr_t
suffix:semicolon
DECL|macro|CPC0_PLLMR_MASK
mdefine_line|#define CPC0_PLLMR_MASK 0x000001fe&t;/* AND to clear all non-reserved fields */
DECL|macro|CPC0_PLLMR_RTVFS_MASK
mdefine_line|#define CPC0_PLLMR_RTVFS_MASK CPC0_PLLMR_MASK&t;/* All bits controlled by RTVFS */
multiline_comment|/* The PLL multiplier/divider are always multiples of 4. */
DECL|macro|CPC0_PLLMR_MULDIV_ENCODE
mdefine_line|#define CPC0_PLLMR_MULDIV_ENCODE(n) ((((unsigned)(n)) / 4) - 1)
DECL|macro|CPC0_PLLMR_MULDIV_DECODE
mdefine_line|#define CPC0_PLLMR_MULDIV_DECODE(n) (((n) + 1) * 4)
DECL|macro|CPC0_PLLMR_MULDIV_MAX
mdefine_line|#define CPC0_PLLMR_MULDIV_MAX 128
DECL|macro|CPC0_PLLMR_TUN_HIGH
mdefine_line|#define CPC0_PLLMR_TUN_HIGH 0x200&t;/* High-band tuning */
DECL|macro|CPC0_PLLMR_TUN_LOW
mdefine_line|#define CPC0_PLLMR_TUN_LOW  0x000&t;/* Low-band tuning */
DECL|macro|CPC0_PLLMR_CSEL_REFCLK
mdefine_line|#define CPC0_PLLMR_CSEL_REFCLK  0&t;/* System Reference Clock */
DECL|macro|CPC0_PLLMR_CSEL_PLLVCO
mdefine_line|#define CPC0_PLLMR_CSEL_PLLVCO  1&t;/* PLL VCO */
DECL|macro|CPC0_PLLMR_CSEL_RTC
mdefine_line|#define CPC0_PLLMR_CSEL_RTC     2&t;/* RTC */
DECL|macro|CPC0_PLLMR_CSEL_EBCPLB5
mdefine_line|#define CPC0_PLLMR_CSEL_EBCPLB5 3&t;/* EBC-PLB divisor is 5 ??? */
multiline_comment|/* CPC0_CGCR0 - Clock Generation and Control Register 0 */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|pcp
r_int
r_int
id|pcp
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Proc. Core/PLB Clock Divisor */
DECL|member|pcsc
r_int
r_int
id|pcsc
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Proc. Core/SysClkOut Divisor */
DECL|member|pcu
r_int
r_int
id|pcu
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Proc. Core/UARTSerClk Clock Div. */
DECL|member|u0cs
r_int
r_int
id|u0cs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* UART0 Clock Select */
DECL|member|u1cs
r_int
r_int
id|u1cs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* UART1 Clock Select */
DECL|member|scsel
r_int
r_int
id|scsel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* SysClkOut Select */
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|13
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|cpc0_cgcr0_t
)brace
id|cpc0_cgcr0_t
suffix:semicolon
DECL|macro|CPC0_CGCR0_MASK
mdefine_line|#define CPC0_CGCR0_MASK 0x00001fff&t;/* AND to clear all non-reserved fields */
DECL|macro|CPC0_CGCR0_RTVFS_MASK
mdefine_line|#define CPC0_CGCR0_RTVFS_MASK 0x0001ffff&t;/* AND to clear all rtvfs-modified&n;&t;&t;&t;&t;&t;&t;   fields */
DECL|macro|CPC0_CGCR0_SCSEL_OFF
mdefine_line|#define CPC0_CGCR0_SCSEL_OFF  0&t;/* SysClkOut driven low (low power) */
DECL|macro|CPC0_CGCR0_SCSEL_CPU
mdefine_line|#define CPC0_CGCR0_SCSEL_CPU  1&t;/* Select CPU clock as SysClkOut */
DECL|macro|CPC0_CGCR0_SCSEL_PLB
mdefine_line|#define CPC0_CGCR0_SCSEL_PLB  2&t;/* SysClkOut is PLB Sample Cycle */
DECL|macro|CPC0_CGCR0_SCSEL_OPB
mdefine_line|#define CPC0_CGCR0_SCSEL_OPB  3&t;/* SysClkOut is OPB Sample Cycle */
multiline_comment|/* CPC0_CGCR1 - Clock Generation and Control Register 1 */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|po
r_int
r_int
id|po
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* PLB/OPB Clock Divisor */
DECL|member|pext
r_int
r_int
id|pext
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* PLB/External Clock Divisor */
DECL|member|ppxl
r_int
r_int
id|ppxl
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* PLB/LCD Pixel Clock Divisor */
DECL|member|csel
r_int
r_int
id|csel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* PerClk Select */
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|cpc0_cgcr1_t
)brace
id|cpc0_cgcr1_t
suffix:semicolon
DECL|macro|CPC0_CGCR1_MASK
mdefine_line|#define CPC0_CGCR1_MASK 0x00007fff&t;/* AND to clear all non-reserved fields */
DECL|macro|CPC0_CGCR1_RTVFS_MASK
mdefine_line|#define CPC0_CGCR1_RTVFS_MASK 0x0001ffff&t;/* AND to clear all rtvfs-modified&n;&t;&t;&t;&t;&t;&t;   fields */
multiline_comment|/* 5-bit clock dividers are directly encoded, except that an encoding of 0&n;   indicates divide-by-32. */
DECL|macro|CPC0_DIV_MAX
mdefine_line|#define CPC0_DIV_MAX      32
DECL|macro|CPC0_DIV_VALID
mdefine_line|#define CPC0_DIV_VALID(n) (((n) &gt; 0) &amp;&amp; ((n) &lt;= CPC0_DIV_MAX))
DECL|macro|CPC0_DIV_ENCODE
mdefine_line|#define CPC0_DIV_ENCODE(n) (((unsigned)(n) &gt;= CPC0_DIV_MAX) ? 0 : (unsigned)(n))
DECL|macro|CPC0_DIV_DECODE
mdefine_line|#define CPC0_DIV_DECODE(n) (((n) == 0) ? CPC0_DIV_MAX : (n))
DECL|macro|CPC0_CGCR1_CSEL_OFF
mdefine_line|#define CPC0_CGCR1_CSEL_OFF    0&t;/* PerClk driven low (low power) */
DECL|macro|CPC0_CGCR1_CSEL_PERCLK
mdefine_line|#define CPC0_CGCR1_CSEL_PERCLK 1&t;/* Select PerClk */
DECL|macro|CPC0_CGCR1_CSEL_PLBCLK
mdefine_line|#define CPC0_CGCR1_CSEL_PLBCLK 2&t;/* Select PLB clock */
DECL|macro|CPC0_CGCR1_CSEL_OPBCLK
mdefine_line|#define CPC0_CGCR1_CSEL_OPBCLK 3&t;/* Select OPB clock */
multiline_comment|/* CPC0_CR0 - Chip Control Register 0 */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd0
r_int
r_int
id|rsvd0
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ssr
r_int
r_int
id|ssr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SDRAM Self-Refresh on Sleep Req. */
DECL|member|gpms
r_int
r_int
id|gpms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* GPIO Pin Muxing Select */
DECL|member|u0pms
r_int
r_int
id|u0pms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* UART0 Pin Muxing Select */
DECL|member|u1pms
r_int
r_int
id|u1pms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* UART1 Pin Muxing Select */
DECL|member|ipms
r_int
r_int
id|ipms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* IIC Pin Muxing Select */
DECL|member|cpms
r_int
r_int
id|cpms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* CSI Pin Muxing Select */
DECL|member|tpms
r_int
r_int
id|tpms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* TPC Pin Muxing Select */
DECL|member|irpms
r_int
r_int
id|irpms
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* IRQ Pin Muxing Select */
DECL|member|pcmd
r_int
r_int
id|pcmd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PCMCIA Mode Disable */
DECL|member|u0dte
r_int
r_int
id|u0dte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* UART0 DMA Transmit Channel Enable */
DECL|member|u0rde
r_int
r_int
id|u0rde
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* UART0 DMA Receive Channel Enable */
DECL|member|u0dce
r_int
r_int
id|u0dce
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* UART0 DMA CLear on Enable */
DECL|member|rsvd1
r_int
r_int
id|rsvd1
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|cpc0_cr0_t
)brace
id|cpc0_cr0_t
suffix:semicolon
DECL|macro|CPC0_CR0_MASK
mdefine_line|#define CPC0_CR0_MASK 0xfe00003f&t;/* AND to clear all non-reserved fields */
multiline_comment|/* CPC0_CR1 - Chip Control Register 1 */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd0
r_int
r_int
id|rsvd0
suffix:colon
l_int|28
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|tbsed
r_int
r_int
id|tbsed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TB. Src. in Edge Detect Mode */
DECL|member|edmd
r_int
r_int
id|edmd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TB. Src. Edge Detect Mode Disable */
DECL|member|rsvd1
r_int
r_int
id|rsvd1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|cpc0_cr1_t
)brace
id|cpc0_cr1_t
suffix:semicolon
DECL|macro|CPC0_CR1_MASK
mdefine_line|#define CPC0_CR1_MASK 0xfffffff3&t;/* AND to clear all non-reserved fields */
multiline_comment|/* DCP0_CFG - DCP Configuration Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd0
r_int
r_int
id|rsvd0
suffix:colon
l_int|18
suffix:semicolon
DECL|member|sldy
r_int
r_int
id|sldy
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* Sleep Delay */
DECL|member|slen
r_int
r_int
id|slen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sleep Enable */
DECL|member|cdb
r_int
r_int
id|cdb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Clear Decompression Buffer */
DECL|member|rsvd1
r_int
r_int
id|rsvd1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ikb
r_int
r_int
id|ikb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Enable Decompression */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|dcp0_cfg_t
)brace
id|dcp0_cfg_t
suffix:semicolon
DECL|macro|DCP0_CFG_MASK
mdefine_line|#define DCP0_CFG_MASK 0xffffc002&t;/* AND to clear all non-reserved fields */
multiline_comment|/* DMA0_SLP - DMA Sleep Mode Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|idu
r_int
id|idu
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Idle Timer Upper */
DECL|member|rsvd0
r_int
id|rsvd0
suffix:colon
l_int|5
suffix:semicolon
DECL|member|sme
r_int
id|sme
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sleep Mode Enable */
DECL|member|rsvd1
r_int
id|rsvd1
suffix:colon
l_int|21
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|dma0_slp_t
)brace
id|dma0_slp_t
suffix:semicolon
DECL|macro|DMA0_SLP_MASK
mdefine_line|#define DMA0_SLP_MASK 0x07dfffff&t;/* AND to clear all non-reserved fields */
multiline_comment|/* EBC0_BnAP - EBC Bank Access Parameters */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|bme
r_int
id|bme
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Burst Mode Enable */
DECL|member|twt
r_int
id|twt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Transfer Wait (non-burst) */
DECL|member|rsvd0
r_int
id|rsvd0
suffix:colon
l_int|3
suffix:semicolon
DECL|member|csn
r_int
id|csn
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Chip Select On Timing */
DECL|member|oen
r_int
id|oen
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Output Enable On Timing */
DECL|member|wbn
r_int
id|wbn
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Write Byte Enable On Timing */
DECL|member|wbf
r_int
id|wbf
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Write Byte Enable Off Timing */
DECL|member|th
r_int
id|th
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Transfer Hold */
DECL|member|re
r_int
id|re
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Ready Enable */
DECL|member|sor
r_int
id|sor
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sample On Ready */
DECL|member|bem
r_int
id|bem
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte Enable Mode */
DECL|member|pen
r_int
id|pen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Parity Enable */
DECL|member|rsvd1
r_int
id|rsvd1
suffix:colon
l_int|5
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|ebc0_bnap_t
)brace
id|ebc0_bnap_t
suffix:semicolon
DECL|macro|EBC0_BnAP_MASK
mdefine_line|#define EBC0_BnAP_MASK 0x0070001f&t;/* AND to clear all non-reserved fields */
multiline_comment|/* EBC0_BnCR - EBC Bank Configuration Registers */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|bas
r_int
id|bas
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Base Address */
DECL|member|bs
r_int
id|bs
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Bank Size */
DECL|member|bu
r_int
id|bu
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Bank Usage */
DECL|member|bw
r_int
id|bw
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Bank Width */
DECL|member|rsvd
r_int
id|rsvd
suffix:colon
l_int|13
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|ebc0_bncr_t
)brace
id|ebc0_bncr_t
suffix:semicolon
DECL|macro|EBC0_BnCR_MASK
mdefine_line|#define EBC0_BnCR_MASK 0x00001fff&t;/* AND to clear all non-reserved fields */
DECL|macro|EBC0_BnCR_BS_1MB
mdefine_line|#define EBC0_BnCR_BS_1MB   0
DECL|macro|EBC0_BnCR_BS_2MB
mdefine_line|#define EBC0_BnCR_BS_2MB   1
DECL|macro|EBC0_BnCR_BS_4MB
mdefine_line|#define EBC0_BnCR_BS_4MB   2
DECL|macro|EBC0_BnCR_BS_8MB
mdefine_line|#define EBC0_BnCR_BS_8MB   3
DECL|macro|EBC0_BnCR_BS_16MB
mdefine_line|#define EBC0_BnCR_BS_16MB  4
DECL|macro|EBC0_BnCR_BS_32MB
mdefine_line|#define EBC0_BnCR_BS_32MB  5
DECL|macro|EBC0_BnCR_BS_64MB
mdefine_line|#define EBC0_BnCR_BS_64MB  6
DECL|macro|EBC0_BnCR_BS_128MB
mdefine_line|#define EBC0_BnCR_BS_128MB 7
DECL|macro|EBC0_BnCR_BU_R
mdefine_line|#define EBC0_BnCR_BU_R  1
DECL|macro|EBC0_BnCR_BU_W
mdefine_line|#define EBC0_BnCR_BU_W  2
DECL|macro|EBC0_BnCR_BU_RW
mdefine_line|#define EBC0_BnCR_BU_RW 3
DECL|macro|EBC0_BnCR_BW_8
mdefine_line|#define EBC0_BnCR_BW_8  0
DECL|macro|EBC0_BnCR_BW_16
mdefine_line|#define EBC0_BnCR_BW_16 1
DECL|macro|EBC0_BnCR_BW_32
mdefine_line|#define EBC0_BnCR_BW_32 2
multiline_comment|/* EBC0_CFG -EBC Configuration Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|ebtc
r_int
id|ebtc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* External Bus Three State Control */
DECL|member|ptd
r_int
id|ptd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device-paced Time-out Disable */
DECL|member|rtc
r_int
id|rtc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Ready Timeout Count */
DECL|member|rsvd0
r_int
id|rsvd0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cstc
r_int
id|cstc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Chip Select Three State Control */
DECL|member|bpf
r_int
id|bpf
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Burst Prefetch */
DECL|member|rsvd1
r_int
id|rsvd1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pme
r_int
id|pme
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Power Management Enable */
DECL|member|pmt
r_int
id|pmt
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Power Management Timer */
DECL|member|rsvd2
r_int
id|rsvd2
suffix:colon
l_int|12
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|ebc0_cfg_t
)brace
id|ebc0_cfg_t
suffix:semicolon
DECL|macro|EBC0_CFG_MASK
mdefine_line|#define EBC0_CFG_MASK 0x078c0fff&t;/* AND to clear all non-reserved fields */
DECL|macro|EBC0_CFG_RTC_16
mdefine_line|#define EBC0_CFG_RTC_16   0
DECL|macro|EBC0_CFG_RTC_32
mdefine_line|#define EBC0_CFG_RTC_32   1
DECL|macro|EBC0_CFG_RTC_64
mdefine_line|#define EBC0_CFG_RTC_64   2
DECL|macro|EBC0_CFG_RTC_128
mdefine_line|#define EBC0_CFG_RTC_128  3
DECL|macro|EBC0_CFG_RTC_256
mdefine_line|#define EBC0_CFG_RTC_256  4
DECL|macro|EBC0_CFG_RTC_512
mdefine_line|#define EBC0_CFG_RTC_512  5
DECL|macro|EBC0_CFG_RTC_1024
mdefine_line|#define EBC0_CFG_RTC_1024 6
DECL|macro|EBC0_CFG_RTC_2048
mdefine_line|#define EBC0_CFG_RTC_2048 7
multiline_comment|/* SDRAM0_CFG - SDRAM Controller Configuration Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|dce
r_int
r_int
id|dce
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SDRAM Controller Enable */
DECL|member|sre
r_int
r_int
id|sre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Self-Refresh Enable */
DECL|member|pme
r_int
r_int
id|pme
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Power Management Enable */
DECL|member|rsvd0
r_int
r_int
id|rsvd0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|regen
r_int
r_int
id|regen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Registered Memory Enable */
DECL|member|drw
r_int
r_int
id|drw
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* SDRAM Width */
DECL|member|brpf
r_int
r_int
id|brpf
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Burst Read Prefetch Granularity */
DECL|member|rsvd1
r_int
r_int
id|rsvd1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|emdulr
r_int
r_int
id|emdulr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Enable Memory Data Unless Read */
DECL|member|rsvd2
r_int
r_int
id|rsvd2
suffix:colon
l_int|21
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|sdram0_cfg_t
)brace
id|sdram0_cfg_t
suffix:semicolon
DECL|macro|SDRAM0_CFG_MASK
mdefine_line|#define SDRAM0_CFG_MASK 0x106fffff&t;/* AND to clear all non-reserved fields */
DECL|macro|SDRAM0_CFG_BRPF_16
mdefine_line|#define SDRAM0_CFG_BRPF_16 1
DECL|macro|SDRAM0_CFG_BRPF_32
mdefine_line|#define SDRAM0_CFG_BRPF_32 2
multiline_comment|/* SDRAM0_PMIT - SDRAM Power Management Idle Timer */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|cnt
r_int
r_int
id|cnt
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Cycle Count Before Sleep Request */
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|27
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|sdram0_pmit_t
)brace
id|sdram0_pmit_t
suffix:semicolon
DECL|macro|SDRAM0_PMIT_MASK
mdefine_line|#define SDRAM0_PMIT_MASK 0x07ffffff&t;/* AND to clear all non-reserved fields */
multiline_comment|/* SDRAM0_RTR - Refresh timer register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd0
r_int
id|rsvd0
suffix:colon
l_int|2
suffix:semicolon
DECL|member|iv
r_int
id|iv
suffix:colon
l_int|11
suffix:semicolon
DECL|member|rsvd1
r_int
id|rsvd1
suffix:colon
l_int|19
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|sdram0_rtr_t
)brace
id|sdram0_rtr_t
suffix:semicolon
DECL|macro|SDRAM0_RTR_MASK
mdefine_line|#define SDRAM0_RTR_MASK 0xc007ffff&t;/* AND to clear non-reserved fields */
DECL|macro|SDRAM0_RTR_RTVFS_MASK
mdefine_line|#define SDRAM0_RTR_RTVFS_MASK SDRAM0_RTR_MASK
DECL|macro|SDRAM0_RTR_IV
mdefine_line|#define SDRAM0_RTR_IV(n) (((n) &amp; 0x3ff8) &gt;&gt; 2)
multiline_comment|/* SDRAM0_TR - SDRAM Timing Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd0
r_int
r_int
id|rsvd0
suffix:colon
l_int|7
suffix:semicolon
DECL|member|casl
r_int
r_int
id|casl
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* CAS Latency */
DECL|member|rsvd1
r_int
r_int
id|rsvd1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|pta
r_int
r_int
id|pta
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Precharge-to-activate */
DECL|member|ctp
r_int
r_int
id|ctp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Read/Write to Precharge */
DECL|member|ldf
r_int
r_int
id|ldf
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Command Leadoff */
DECL|member|rsvd2
r_int
r_int
id|rsvd2
suffix:colon
l_int|9
suffix:semicolon
DECL|member|rfta
r_int
r_int
id|rfta
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Refresh-to-Activate */
DECL|member|rcd
r_int
r_int
id|rcd
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* RAS-CAS Delay */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|sdram0_tr_t
)brace
id|sdram0_tr_t
suffix:semicolon
DECL|macro|SDRAM0_TR_MASK
mdefine_line|#define SDRAM0_TR_MASK 0xfe703fe0&t;/* AND to clear non-reserved fields */
DECL|macro|SDRAM0_TR_RTVFS_MASK
mdefine_line|#define SDRAM0_TR_RTVFS_MASK SDRAM0_TR_MASK
DECL|macro|SDRAM0_TR_ENCODE
mdefine_line|#define SDRAM0_TR_ENCODE(n) ((n) - 1)
DECL|macro|SDRAM0_TR_ENCODE_RFTA
mdefine_line|#define SDRAM0_TR_ENCODE_RFTA(n) ((n) - 4)
multiline_comment|/* SLA0_SLPMD - SLA Sleep Mode Control Register */
r_typedef
r_union
(brace
DECL|member|reg
id|u32
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|slcr
r_int
id|slcr
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Sleep Counter */
DECL|member|rsvd0
r_int
id|rsvd0
suffix:colon
l_int|5
suffix:semicolon
DECL|member|slen
r_int
id|slen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sleep Mode Enable */
DECL|member|rsvd1
r_int
id|rsvd1
suffix:colon
l_int|21
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|typedef|sla0_slpmd_t
)brace
id|sla0_slpmd_t
suffix:semicolon
DECL|macro|SLA0_SLPMD_MASK
mdefine_line|#define SLA0_SLPMD_MASK 0x07dfffff&t;/* AND to clear all non-reserved fields */
multiline_comment|/* Several direct-write DCRs on the 405LP have an interlock requirement,&n;   implemented by a &quot;valid&quot; bit in the low-order bit.  This routine handles the&n;   handshaking for these registers, by&n;&n;   1) Rewriting the current value with the valid bit clear;&n;   2) Rewriting the new value with the valid bit clear;&n;   3) Rewriting the new value with the valid bit set.&n;&n;   The mask is a mask with 1s in every reserved bit position.&n;&n;   NB: This routine always writes the register with the valid bit set,&n;       regardless of the valid bit setting in the &squot;new&squot; parameter.  &n;&n;   Unfortunately this must be a macro to work (due to mtdcr()).&n;&n;   Note that for APM registers, it takes multiple RTC clock cycles for the DCR&n;   writes to take effect.  Any time delays after writes to APM are the&n;   resonsibility of the caller.&n;*/
DECL|macro|mtdcr_interlock
mdefine_line|#define mtdcr_interlock(dcrn, new, mask)                                    &bslash;&n;do {                                                                        &bslash;&n;&t;u32 __old, __new;                                                   &bslash;&n;&t;                                                                    &bslash;&n;&t;__old = mfdcr(dcrn);                                                &bslash;&n;&t;mtdcr(dcrn, __old &amp; 0xfffffffe);                                    &bslash;&n;&t;__new = ((__old &amp; (mask)) | ((new) &amp; ~(mask))) &amp; 0xfffffffe;        &bslash;&n;&t;mtdcr(dcrn, __new);                                                 &bslash;&n;&t;mtdcr(dcrn, __new | 1);                                             &bslash;&n;} while (0)
multiline_comment|/****************************************************************************&n; * Power Managament Routines&n; ****************************************************************************/
r_int
id|ibm405lp_set_pixclk
c_func
(paren
r_int
id|pixclk_min
comma
r_int
id|pixclk_max
)paren
suffix:semicolon
r_void
id|ibm405lp_reset_sdram
c_func
(paren
id|u32
id|new_rtr
comma
id|u32
id|new_tr
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|set_pixclk_hook
)paren
(paren
r_int
id|pixclk_min
comma
r_int
id|pixclk_max
)paren
suffix:semicolon
r_extern
r_int
id|last_pixclk_min
suffix:semicolon
r_extern
r_int
id|last_pixclk_max
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __ASSEMBLY__ */
macro_line|#include &lt;asm/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBM405LP_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
