multiline_comment|/*&n; * (C) Copyright 2000, 2001&n; * Wolfgang Denk, DENX Software Engineering, wd@denx.de.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of&n; * the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&t; See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston,&n; * MA 02111-1307 USA&n; */
macro_line|#ifndef __ASM_PPCBOOT_H__
DECL|macro|__ASM_PPCBOOT_H__
mdefine_line|#define __ASM_PPCBOOT_H__
multiline_comment|/*&n; * Board information passed to kernel from PPCBoot&n; *&n; * include/asm-ppc/ppcboot.h&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|bd_info
r_typedef
r_struct
id|bd_info
(brace
DECL|member|bi_memstart
r_int
r_int
id|bi_memstart
suffix:semicolon
multiline_comment|/* start of DRAM memory */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* size&t; of DRAM memory in bytes */
DECL|member|bi_flashstart
r_int
r_int
id|bi_flashstart
suffix:semicolon
multiline_comment|/* start of FLASH memory */
DECL|member|bi_flashsize
r_int
r_int
id|bi_flashsize
suffix:semicolon
multiline_comment|/* size&t; of FLASH memory */
DECL|member|bi_flashoffset
r_int
r_int
id|bi_flashoffset
suffix:semicolon
multiline_comment|/* reserved area for startup monitor */
DECL|member|bi_sramstart
r_int
r_int
id|bi_sramstart
suffix:semicolon
multiline_comment|/* start of SRAM memory */
DECL|member|bi_sramsize
r_int
r_int
id|bi_sramsize
suffix:semicolon
multiline_comment|/* size&t; of SRAM memory */
macro_line|#if defined(CONFIG_8xx) || defined(CONFIG_CPM2) || defined(CONFIG_85xx) ||&bslash;&n;&t;defined(CONFIG_83xx)
DECL|member|bi_immr_base
r_int
r_int
id|bi_immr_base
suffix:semicolon
multiline_comment|/* base of IMMR register */
macro_line|#endif
macro_line|#if defined(CONFIG_PPC_MPC52xx)
DECL|member|bi_mbar_base
r_int
r_int
id|bi_mbar_base
suffix:semicolon
multiline_comment|/* base of internal registers */
macro_line|#endif
DECL|member|bi_bootflags
r_int
r_int
id|bi_bootflags
suffix:semicolon
multiline_comment|/* boot / reboot flag (for LynxOS) */
DECL|member|bi_ip_addr
r_int
r_int
id|bi_ip_addr
suffix:semicolon
multiline_comment|/* IP Address */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet address */
DECL|member|bi_ethspeed
r_int
r_int
id|bi_ethspeed
suffix:semicolon
multiline_comment|/* Ethernet speed in Mbps */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in MHz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in MHz */
macro_line|#if defined(CONFIG_CPM2)
DECL|member|bi_cpmfreq
r_int
r_int
id|bi_cpmfreq
suffix:semicolon
multiline_comment|/* CPM_CLK Freq, in MHz */
DECL|member|bi_brgfreq
r_int
r_int
id|bi_brgfreq
suffix:semicolon
multiline_comment|/* BRG_CLK Freq, in MHz */
DECL|member|bi_sccfreq
r_int
r_int
id|bi_sccfreq
suffix:semicolon
multiline_comment|/* SCC_CLK Freq, in MHz */
DECL|member|bi_vco
r_int
r_int
id|bi_vco
suffix:semicolon
multiline_comment|/* VCO Out from PLL, in MHz */
macro_line|#endif
macro_line|#if defined(CONFIG_PPC_MPC52xx)
DECL|member|bi_ipbfreq
r_int
r_int
id|bi_ipbfreq
suffix:semicolon
multiline_comment|/* IPB Bus Freq, in MHz */
DECL|member|bi_pcifreq
r_int
r_int
id|bi_pcifreq
suffix:semicolon
multiline_comment|/* PCI Bus Freq, in MHz */
macro_line|#endif
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
multiline_comment|/* Console Baudrate */
macro_line|#if defined(CONFIG_4xx)
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Version of the ROM (IBM) */
DECL|member|bi_procfreq
r_int
r_int
id|bi_procfreq
suffix:semicolon
multiline_comment|/* CPU (Internal) Freq, in Hz */
DECL|member|bi_plb_busfreq
r_int
r_int
id|bi_plb_busfreq
suffix:semicolon
multiline_comment|/* PLB Bus speed, in Hz */
DECL|member|bi_pci_busfreq
r_int
r_int
id|bi_pci_busfreq
suffix:semicolon
multiline_comment|/* PCI Bus speed, in Hz */
DECL|member|bi_pci_enetaddr
r_int
r_char
id|bi_pci_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* PCI Ethernet MAC address */
macro_line|#endif
macro_line|#if defined(CONFIG_HYMOD)
DECL|member|bi_hymod_conf
id|hymod_conf_t
id|bi_hymod_conf
suffix:semicolon
multiline_comment|/* hymod configuration information */
macro_line|#endif
macro_line|#if defined(CONFIG_EVB64260) || defined(CONFIG_44x) || defined(CONFIG_85xx) ||&bslash;&n;&t;defined(CONFIG_83xx)
multiline_comment|/* second onboard ethernet port */
DECL|member|bi_enet1addr
r_int
r_char
id|bi_enet1addr
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_EVB64260) || defined(CONFIG_440GX) || defined(CONFIG_85xx)
multiline_comment|/* third onboard ethernet ports */
DECL|member|bi_enet2addr
r_int
r_char
id|bi_enet2addr
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_440GX)
multiline_comment|/* fourth onboard ethernet ports */
DECL|member|bi_enet3addr
r_int
r_char
id|bi_enet3addr
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_4xx)
DECL|member|bi_opbfreq
r_int
r_int
id|bi_opbfreq
suffix:semicolon
multiline_comment|/* OB clock in Hz */
DECL|member|bi_iic_fast
r_int
id|bi_iic_fast
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Use fast i2c mode */
macro_line|#endif
macro_line|#if defined(CONFIG_440GX)
DECL|member|bi_phynum
r_int
id|bi_phynum
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* phy mapping */
DECL|member|bi_phymode
r_int
id|bi_phymode
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* phy mode */
macro_line|#endif
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif&t;/* __ASM_PPCBOOT_H__ */
eof
