multiline_comment|/*&n; * (C) Copyright 2000, 2001&n; * Wolfgang Denk, DENX Software Engineering, wd@denx.de.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of&n; * the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&t; See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston,&n; * MA 02111-1307 USA&n; */
macro_line|#ifndef _PPCBOOT_H_
DECL|macro|_PPCBOOT_H_
mdefine_line|#define _PPCBOOT_H_&t;1
multiline_comment|/*&n; * Board information passed to kernel from PPCBoot&n; *&n; * include/asm-ppc/ppcboot.h&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|interrupt_handler_t
r_typedef
r_void
(paren
id|interrupt_handler_t
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|struct|monitor_functions
r_typedef
r_struct
id|monitor_functions
(brace
DECL|member|getc
r_int
(paren
op_star
id|getc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|tstc
r_int
(paren
op_star
id|tstc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|putc
r_void
(paren
op_star
id|putc
)paren
(paren
r_const
r_char
id|c
)paren
suffix:semicolon
DECL|member|puts
r_void
(paren
op_star
id|puts
)paren
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
DECL|member|printf
r_void
(paren
op_star
id|printf
)paren
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|member|install_hdlr
r_void
(paren
op_star
id|install_hdlr
)paren
(paren
r_int
comma
id|interrupt_handler_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|free_hdlr
r_void
(paren
op_star
id|free_hdlr
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|malloc
r_void
op_star
(paren
op_star
id|malloc
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|typedef|mon_fnc_t
)brace
id|mon_fnc_t
suffix:semicolon
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
multiline_comment|/* start of  DRAM memory&t;&t;*/
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* size&t; of  DRAM memory in bytes&t;*/
DECL|member|bi_flashstart
r_int
r_int
id|bi_flashstart
suffix:semicolon
multiline_comment|/* start of FLASH memory&t;&t;*/
DECL|member|bi_flashsize
r_int
r_int
id|bi_flashsize
suffix:semicolon
multiline_comment|/* size&t; of FLASH memory&t;&t;*/
DECL|member|bi_flashoffset
r_int
r_int
id|bi_flashoffset
suffix:semicolon
multiline_comment|/* reserved area for startup monitor&t;*/
DECL|member|bi_sramstart
r_int
r_int
id|bi_sramstart
suffix:semicolon
multiline_comment|/* start of  SRAM memory&t;&t;*/
DECL|member|bi_sramsize
r_int
r_int
id|bi_sramsize
suffix:semicolon
multiline_comment|/* size&t; of  SRAM memory&t;&t;*/
macro_line|#if defined(CONFIG_8xx) || defined(CONFIG_8260)
DECL|member|bi_immr_base
r_int
r_int
id|bi_immr_base
suffix:semicolon
multiline_comment|/* base of IMMR register&t;&t;*/
macro_line|#endif
DECL|member|bi_bootflags
r_int
r_int
id|bi_bootflags
suffix:semicolon
multiline_comment|/* boot / reboot flag (for LynxOS)&t;*/
DECL|member|bi_ip_addr
r_int
r_int
id|bi_ip_addr
suffix:semicolon
multiline_comment|/* IP Address&t;&t;&t;&t;*/
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet adress&t;&t;&t;*/
DECL|member|bi_ethspeed
r_int
r_int
id|bi_ethspeed
suffix:semicolon
multiline_comment|/* Ethernet speed in Mbps&t;&t;*/
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in MHz&t;&t;*/
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in MHz&t;&t;&t;*/
macro_line|#if defined(CONFIG_8260)
DECL|member|bi_cpmfreq
r_int
r_int
id|bi_cpmfreq
suffix:semicolon
multiline_comment|/* CPM_CLK Freq, in MHz&t;&t;&t;*/
DECL|member|bi_brgfreq
r_int
r_int
id|bi_brgfreq
suffix:semicolon
multiline_comment|/* BRG_CLK Freq, in MHz&t;&t;&t;*/
DECL|member|bi_sccfreq
r_int
r_int
id|bi_sccfreq
suffix:semicolon
multiline_comment|/* SCC_CLK Freq, in MHz&t;&t;&t;*/
DECL|member|bi_vco
r_int
r_int
id|bi_vco
suffix:semicolon
multiline_comment|/* VCO Out from PLL, in MHz&t;&t;*/
macro_line|#endif
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
multiline_comment|/* Console Baudrate&t;&t;&t;*/
macro_line|#if defined(CONFIG_405GP)
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure&t;&t;*/
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Version of the ROM (IBM)&t;&t;*/
DECL|member|bi_procfreq
r_int
r_int
id|bi_procfreq
suffix:semicolon
multiline_comment|/* CPU (Internal) Freq, in Hz&t;&t;*/
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
multiline_comment|/* PCI Ethernet MAC address     */
macro_line|#endif
macro_line|#if defined(CONFIG_HYMOD)
DECL|member|bi_hymod_conf
id|hymod_conf_t
id|bi_hymod_conf
suffix:semicolon
multiline_comment|/* hymod configuration information&t;*/
macro_line|#endif
macro_line|#if defined(CONFIG_EVB64260)
multiline_comment|/* the board has three onboard ethernet ports */
DECL|member|bi_enet1addr
r_int
r_char
id|bi_enet1addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|bi_enet2addr
r_int
r_char
id|bi_enet2addr
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
DECL|member|bi_mon_fnc
id|mon_fnc_t
op_star
id|bi_mon_fnc
suffix:semicolon
multiline_comment|/* Pointer to monitor functions&t;&t;*/
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif&t;/* _PPCBOOT_H_ */
eof
