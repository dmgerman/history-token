multiline_comment|/*&n; * include/asm-ppc/platforms/beech.h   Platform definitions for the IBM Beech&n; *                                     board&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Copyright (C) 2002, International Business Machines Corporation&n; * All Rights Reserved.&n; *&n; * Bishop Brock&n; * IBM Research, Austin Center for Low-Power Computing&n; * bcbrock@us.ibm.com&n; * March, 2002&n; * &n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_BEECH_H__
DECL|macro|__ASM_BEECH_H__
mdefine_line|#define __ASM_BEECH_H__
macro_line|#include &lt;platforms/4xx/ibm405lp.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Data structure defining board information maintained by the standard boot&n; * ROM on the IBM Beech board. An effort has been made to&n; * keep the field names consistent with the 8xx &squot;bd_t&squot; board info&n; * structures.  &n; */
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|bi_tbfreq
r_int
r_int
id|bi_tbfreq
suffix:semicolon
multiline_comment|/* Frequency of SysTmrClk */
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* Version of the IBM ROM */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* DRAM installed, in bytes */
DECL|member|sysclock_period
r_int
r_int
id|sysclock_period
suffix:semicolon
multiline_comment|/* SysClk period in ns */
DECL|member|sys_speed
r_int
r_int
id|sys_speed
suffix:semicolon
multiline_comment|/* SysCLk frequency in Hz */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Processor speed, in Hz */
DECL|member|vco_speed
r_int
r_int
id|vco_speed
suffix:semicolon
multiline_comment|/* PLL VCO speed, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* PLB Bus speed, in Hz */
DECL|member|opb_speed
r_int
r_int
id|opb_speed
suffix:semicolon
multiline_comment|/* OPB Bus speed, in Hz */
DECL|member|ebc_speed
r_int
r_int
id|ebc_speed
suffix:semicolon
multiline_comment|/* EBC Bus speed, in Hz */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* See beech.c for a concise diagram of the Beech physical memory map. */
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR    ((uint)0xef600000)
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR    PPC4xx_ONB_IO_PADDR
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE     ((uint)4*1024)
multiline_comment|/* EBC Bank 0 controls the boot flash and SRAM */
DECL|macro|BEECH_BANK0_PADDR
mdefine_line|#define BEECH_BANK0_PADDR      ((uint)0xfff00000)
DECL|macro|BEECH_BANK0_EBC_SIZE
mdefine_line|#define BEECH_BANK0_EBC_SIZE   EBC0_BnCR_BS_1MB
DECL|macro|BEECH_SRAM_PADDR
mdefine_line|#define BEECH_SRAM_PADDR&t;&t;BEECH_BANK0_PADDR
DECL|macro|BEECH_SRAM_SIZE
mdefine_line|#define BEECH_SRAM_SIZE&t;&t;&t;((uint)(512 * 1024))
DECL|macro|BEECH_BOOTFLASH_PADDR
mdefine_line|#define BEECH_BOOTFLASH_PADDR&t;&t;(BEECH_BANK0_PADDR + (512 * 1024))
DECL|macro|BEECH_BOOTFLASH_SIZE
mdefine_line|#define BEECH_BOOTFLASH_SIZE&t;&t;((uint)(512 * 1024))
multiline_comment|/* EBC bank 1 controls the NVRAM, Ethernet and CPLD registers. The different&n;   areas are mapped in as small an area as possible to help catch any kernel&n;   addressing errors.&n;&n;   NVRAM is improperly connected on Beech Pass 1.  Only every other location is&n;   accessible.  This is a 32 KB NVRAM.&n;&n;   The Ethernet chip maps 13 address lines. We only map the &quot;I/O&quot; space used by&n;   the current driver.&n;&n;   The FPGA &quot;registers&quot; are decoded on 128 KB boundarys. Each is mapped in a&n;   separate page. */
DECL|macro|BEECH_BANK1_PADDR
mdefine_line|#define BEECH_BANK1_PADDR       ((uint)0xffe00000)
DECL|macro|BEECH_BANK1_EBC_SIZE
mdefine_line|#define BEECH_BANK1_EBC_SIZE    EBC0_BnCR_BS_1MB
DECL|macro|BEECH_NVRAM_PADDR
mdefine_line|#define BEECH_NVRAM_PADDR&t;&t;BEECH_BANK1_PADDR
DECL|macro|BEECH_NVRAM_SIZE
mdefine_line|#define BEECH_NVRAM_SIZE&t;&t;((uint) (32 * 1024))
DECL|macro|BEECH_ETHERNET_PADDR
mdefine_line|#define BEECH_ETHERNET_PADDR&t;&t;(BEECH_BANK1_PADDR + 0x00020000)
DECL|macro|BEECH_ETHERNET_SIZE
mdefine_line|#define BEECH_ETHERNET_SIZE&t;&t;((uint) (8 * 1024))
DECL|macro|BEECH_FPGA_REG_0_PADDR
mdefine_line|#define BEECH_FPGA_REG_0_PADDR&t;&t;(BEECH_BANK1_PADDR + 0x00080000)
DECL|macro|BEECH_FPGA_REG_0_SIZE
mdefine_line|#define BEECH_FPGA_REG_0_SIZE&t;&t;PAGE_SIZE
DECL|macro|BEECH_FPGA_REG_1_PADDR
mdefine_line|#define BEECH_FPGA_REG_1_PADDR&t;&t;(BEECH_BANK1_PADDR + 0x000A0000)
DECL|macro|BEECH_FPGA_REG_1_SIZE
mdefine_line|#define BEECH_FPGA_REG_1_SIZE&t;&t;PAGE_SIZE
DECL|macro|BEECH_FPGA_REG_2_PADDR
mdefine_line|#define BEECH_FPGA_REG_2_PADDR&t;&t;(BEECH_BANK1_PADDR + 0x000C0000)
DECL|macro|BEECH_FPGA_REG_2_SIZE
mdefine_line|#define BEECH_FPGA_REG_2_SIZE&t;&t;PAGE_SIZE
DECL|macro|BEECH_FPGA_REG_3_PADDR
mdefine_line|#define BEECH_FPGA_REG_3_PADDR&t;&t;(BEECH_BANK1_PADDR + 0x000E0000)
DECL|macro|BEECH_FPGA_REG_3_SIZE
mdefine_line|#define BEECH_FPGA_REG_3_SIZE&t;&t;PAGE_SIZE
DECL|macro|BEECH_FPGA_REG_4_PADDR
mdefine_line|#define BEECH_FPGA_REG_4_PADDR&t;&t;(BEECH_BANK1_PADDR + 0x00060000)
DECL|macro|BEECH_FPGA_REG_4_SIZE
mdefine_line|#define BEECH_FPGA_REG_4_SIZE&t;&t;PAGE_SIZE
multiline_comment|/* FPGA Register Bits (From IBM BIOS) [ May not be valid for Beech Pass 1 ]*/
DECL|macro|FPGA_REG_0_FLASH_N
mdefine_line|#define FPGA_REG_0_FLASH_N&t;&t;0x01
DECL|macro|FPGA_REG_0_FLASH_ONBD_N
mdefine_line|#define FPGA_REG_0_FLASH_ONBD_N&t;&t;0x02
DECL|macro|FPGA_REG_0_HITA_TOSH_N
mdefine_line|#define FPGA_REG_0_HITA_TOSH_N&t;&t;0x04&t;/* New in Pass 2 */
DECL|macro|FPGA_REG_0_STAT_OC
mdefine_line|#define FPGA_REG_0_STAT_OC&t;&t;0x20
DECL|macro|FPGA_REG_0_AC_SOURCE_SEL_N
mdefine_line|#define FPGA_REG_0_AC_SOURCE_SEL_N&t;0x40
DECL|macro|FPGA_REG_0_AC_ACTIVE_N
mdefine_line|#define FPGA_REG_0_AC_ACTIVE_N&t;&t;0x80
DECL|macro|FPGA_REG_1_USB_ACTIVE
mdefine_line|#define FPGA_REG_1_USB_ACTIVE&t;&t;0x01&t;/* New in Pass 2 */
DECL|macro|FPGA_REG_1_CLK_VARIABLE
mdefine_line|#define FPGA_REG_1_CLK_VARIABLE&t;&t;0x02
DECL|macro|FPGA_REG_1_CLK_TEST
mdefine_line|#define FPGA_REG_1_CLK_TEST&t;&t;0x04
DECL|macro|FPGA_REG_1_CLK_SS
mdefine_line|#define FPGA_REG_1_CLK_SS&t;&t;0x08
DECL|macro|FPGA_REG_1_EXT_IRQ_N
mdefine_line|#define FPGA_REG_1_EXT_IRQ_N&t;&t;0x10
DECL|macro|FPGA_REG_1_SMI_MODE_N
mdefine_line|#define FPGA_REG_1_SMI_MODE_N&t;&t;0x20
DECL|macro|FPGA_REG_1_BATT_LOW_N
mdefine_line|#define FPGA_REG_1_BATT_LOW_N&t;&t;0x40
DECL|macro|FPGA_REG_1_PCMCIA_PWR_FAULT_N
mdefine_line|#define FPGA_REG_1_PCMCIA_PWR_FAULT_N&t;0x80
DECL|macro|FPGA_REG_2_DEFAULT_UART1_N
mdefine_line|#define FPGA_REG_2_DEFAULT_UART1_N&t;0x01
DECL|macro|FPGA_REG_2_EN_1_8V_PLL_N
mdefine_line|#define FPGA_REG_2_EN_1_8V_PLL_N&t;0x02
DECL|macro|FPGA_REG_2_PC_BUF_EN_N
mdefine_line|#define FPGA_REG_2_PC_BUF_EN_N&t;&t;0x08
DECL|macro|FPGA_REG_2_CODEC_RESET_N
mdefine_line|#define FPGA_REG_2_CODEC_RESET_N&t;0x10&t;/* New in Pass 2 */
DECL|macro|FPGA_REG_2_TP_JSTICK_N
mdefine_line|#define FPGA_REG_2_TP_JSTICK_N&t;&t;0x20&t;/* New in Pass 2 */
DECL|macro|FPGA_REG_3_GAS_GAUGE_IO
mdefine_line|#define FPGA_REG_3_GAS_GAUGE_IO&t;&t;0x01
DECL|macro|FPGA_REG_4_SDRAM_CLK3_ENAB
mdefine_line|#define FPGA_REG_4_SDRAM_CLK3_ENAB&t;0x01
DECL|macro|FPGA_REG_4_SDRAM_CLK2_ENAB
mdefine_line|#define FPGA_REG_4_SDRAM_CLK2_ENAB&t;0x02
DECL|macro|FPGA_REG_4_SDRAM_CLK1_ENAB
mdefine_line|#define FPGA_REG_4_SDRAM_CLK1_ENAB&t;0x04
DECL|macro|FPGA_REG_4_SDRAM_CLK0_ENAB
mdefine_line|#define FPGA_REG_4_SDRAM_CLK0_ENAB&t;0x08
DECL|macro|FPGA_REG_4_PCMCIA_5V
mdefine_line|#define FPGA_REG_4_PCMCIA_5V&t;&t;0x10&t;/* New in Pass 2 */
DECL|macro|FPGA_REG_4_IRQ3
mdefine_line|#define FPGA_REG_4_IRQ3&t;&t;&t;0x20&t;/* New in Pass 2 */
multiline_comment|/* EBC Bank 2 contains the 16 MB &quot;Linux&quot; flash. The FPGA decodes a 32 MB&n;   bank. The lower 16 MB are available for expansion devices.  The upper 16 MB&n;   are used for the &quot;Linux&quot; flash.&n;&n;   Partitioning information is for the benefit of the MTD driver.  See &n;   drivers/mtd/maps/ibm4xx.c. We currently allocate the lower 1 MB for a&n;   kernel, and the other 15 MB for a filesystem.&n;&n;*/
multiline_comment|/* Bank 2 mappings changed between Beech Pass 1 and Pass 2 */
macro_line|#ifdef CONFIG_BEECH_PASS1
DECL|macro|BEECH_BIGFLASH_OFFSET
mdefine_line|#define BEECH_BIGFLASH_OFFSET 0
macro_line|#else
DECL|macro|BEECH_BIGFLASH_OFFSET
mdefine_line|#define BEECH_BIGFLASH_OFFSET (16 * 1024 * 1024)
macro_line|#endif
DECL|macro|BEECH_BANK2_PADDR
mdefine_line|#define BEECH_BANK2_PADDR      ((uint)0xf8000000)
DECL|macro|BEECH_BANK2_EBC_SIZE
mdefine_line|#define BEECH_BANK2_EBC_SIZE   EBC0_BnCR_BS_32MB
DECL|macro|BEECH_BIGFLASH_PADDR
mdefine_line|#define BEECH_BIGFLASH_PADDR&t;&t;(BEECH_BANK2_PADDR + BEECH_BIGFLASH_OFFSET)
DECL|macro|BEECH_BIGFLASH_SIZE
mdefine_line|#define BEECH_BIGFLASH_SIZE&t;&t;(16 * 1024 * 1024)
DECL|macro|BEECH_KERNEL_OFFSET
mdefine_line|#define BEECH_KERNEL_OFFSET    0
DECL|macro|BEECH_KERNEL_SIZE
mdefine_line|#define BEECH_KERNEL_SIZE      (1 * 1024 * 1024)
DECL|macro|BEECH_FREE_AREA_OFFSET
mdefine_line|#define BEECH_FREE_AREA_OFFSET BEECH_KERNEL_SIZE
DECL|macro|BEECH_FREE_AREA_SIZE
mdefine_line|#define BEECH_FREE_AREA_SIZE   (BEECH_BIGFLASH_SIZE - BEECH_KERNEL_SIZE)
multiline_comment|/* The PCMCIA controller driver 4xx_pccf.c is responsible for the EBC setup of&n;   PCMCIA.  Externally, EBC bank selects 3..7 take on PCMCIA functions when&n;   PCMCIA is enabled. */
DECL|macro|BEECH_PCMCIA_PADDR
mdefine_line|#define BEECH_PCMCIA_PADDR&t;&t;((uint)0xf0000000)
DECL|macro|BEECH_PCMCIA_SIZE
mdefine_line|#define BEECH_PCMCIA_SIZE&t;&t;((uint)(32 * 1024 * 1024))
multiline_comment|/* We do not currently support the internal clock mode for the UART.  This&n;   limits the minimum OPB frequency to just over 2X the UART oscillator&n;   frequency. At OPB frequencies less than this the serial port will not&n;   function due to the way that SerClk is sampled. */
DECL|macro|PPC4xx_SERCLK_FREQ
mdefine_line|#define PPC4xx_SERCLK_FREQ&t;&t;11059200
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;&t;(PPC4xx_SERCLK_FREQ / 16)
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&t;&quot;IBM 405LP Beech&quot;
multiline_comment|/****************************************************************************&n; * Non-standard board support follows&n; ****************************************************************************/
r_extern
r_int
id|beech_sram_free
c_func
(paren
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|ibm405lp_set_pixclk
c_func
(paren
r_int
id|pixclk_low
comma
r_int
id|pixclk_high
)paren
suffix:semicolon
r_extern
r_void
op_star
id|beech_sram_alloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* !__ASSEMBLY__ */
macro_line|#endif&t;&t;&t;&t;/* __ASM_BEECH_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
