multiline_comment|/*&n; * arch/ppc/platforms/beech.c  Platform setup for the IBM Beech board&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Copyright (C) 2002, International Business Machines Corporation&n; * All Rights Reserved&n; *&n; * Bishop Brock&n; * IBM Research, Austin Center for Low-Power Computing&n; * bcbrock@us.ibm.com&n; * March, 2002&n; *&n; */
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
r_static
r_void
id|beech_ebc_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|beech_fpga_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* &n;   Beech board physical memory map:&n;&n;   Main Memory (Initialized by the BIOS)&n;   =======================================================================&n;&n;   SDRAM (64 MB)     0x00000000 - 0x04000000&n;&n;   OPB Space: (Mapped virtual = physical in ppc4xx_setup.c)&n;   =======================================================================&n;&n;   UART0               &t;      0xEF600300&n;   UART1               &t;      0xEF600400&n;   IIC                 &t;      0xEF600500&n;   OPB Arbiter         &t;      0xEF600600&n;   GPIO Controller     &t;      0xEF600700&n;   CODEC Interface            0xEF600900&n;   Touch Panel Controller     0xEF600A00&n;   DES Controller             0xEF600B00&n;&n;   &n;   EBC Space: (Mapped virtual = physical in ppc4xx_map_io(); EBC setup&n;               for PCMCIA left to 4xx_pccf)&n;   Space             EBC Bank    Physical Addresses  EBC Base Address&n;   =========================================================================&n;&n;   PCMCIA (32 MB)        x       F0000000 - F1FFFFFF  F0000000 &n;&n;   Expansion             2       F8000000 - F8FFFFFF  F8000000&n;   Linux Flash (16 MB)           F9000000 - F9FFFFFF&n;&n;   NVRAM (32 KB)         1       FFE00000 - FFE07FFF  FFE00000&n;   &n;&n;   Ethernet(I/O)&t; 1&t; FFE20300 - FFE2030F  FFE00000&n;           (MEM)&t; &t; FFE40000 - FFE40FFF&n;&n;   FPGA_REG_4            1       FFE60000 - FFE60000  FFE00000&n;   FPGA_REG_0            1       FFE80000 - FFE80000  FFE00000&n;   FPGA_REG_1            1       FFEA0000 - FFEA0000  FFE00000&n;   FPGA_REG_2            1       FFEC0000 - FFEC0000  FFE00000&n;   FPGA_REG_3            1       FFEE0000 - FFEE0000  FFE00000&n;&n;   SRAM (512 KB)         0       FFF00000 - FFF7FFFF  FFF00000&n;&n;   Boot Flash  (512 KB)  0       FFF80000 - FFFFFFFF  FFF00000&n;&n;   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++&n;&n;   NB: On Beech 1, address ranges for Bank 2 were reversed&n;&n;*/
r_void
id|__init
DECL|function|beech_setup_arch
id|beech_setup_arch
c_func
(paren
r_void
)paren
(brace
id|ppc4xx_setup_arch
c_func
(paren
)paren
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_DCR146818
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Set up Beech FPGA. */
id|beech_fpga_setup
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|ppc4xx_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|beech_setup_arch
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_RTC
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_dcr146818_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_dcr146818_write_val
suffix:semicolon
macro_line|#endif
multiline_comment|/* Disable the LCD controller, which may have been left on by the&n;&t;   BIOS.  Then do initialization of the EBC. */
id|mtdcri
c_func
(paren
id|DCRN_LCD0
comma
id|DER
comma
l_int|0
)paren
suffix:semicolon
id|beech_ebc_setup
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++&n; + Non-standard board support follows&n; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
multiline_comment|/****************************************************************************&n; * EBC Setup&n; ****************************************************************************/
multiline_comment|/* The EBC is set up for Beech.  This may simply replicate the setup already&n;   done by the IBM BIOS for Beech (possibly with some address map changes), or&n;   may be the first initialization if the board is booting from another BIOS.&n;   Virtually all that is required to boot Linux on Beech is that the BIOS&n;   enable the memory controller, load a Linux image from flash, and run it.&n;&n;   For optimal dynamic frequency scaling the EBC settings will also vary as the&n;   frequency varies.&n;*/
r_static
r_void
id|__init
DECL|function|beech_ebc_setup
id|beech_ebc_setup
c_func
(paren
r_void
)paren
(brace
id|ebc0_bnap_t
id|ap
suffix:semicolon
id|ebc0_bncr_t
id|cr
suffix:semicolon
multiline_comment|/* Set EBC bank 0 for the SRAM and boot flash.&n;&n;&t;   Access parameters assume 120ns AMD flash @ 66.66 MHz maximum bus&n;&t;   speed = 8 cycle access with 2 turnaround cycles (30 ns).&n;&n;&t;   These parameters will work for the SRAM as well, which is a 70 ns&n;&t;   part. &n;&n;&t;   NB: IBM BIOS sets this bank to burst, however bursting will never&n;&t;   happen in Linux because this region is mapped non-cacheable and&n;&t;   guarded, so it is set non-burst here. */
id|cr.reg
op_assign
(paren
id|BEECH_BANK0_PADDR
op_amp
l_int|0xfff00000
)paren
op_or
(paren
id|mfdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnCR
c_func
(paren
l_int|0
)paren
)paren
op_amp
id|EBC0_BnCR_MASK
)paren
suffix:semicolon
id|cr.fields.bs
op_assign
id|BEECH_BANK0_EBC_SIZE
suffix:semicolon
id|cr.fields.bu
op_assign
id|EBC0_BnCR_BU_RW
suffix:semicolon
id|cr.fields.bw
op_assign
id|EBC0_BnCR_BW_16
suffix:semicolon
id|mtdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnCR
c_func
(paren
l_int|0
)paren
comma
id|cr.reg
)paren
suffix:semicolon
id|ap.reg
op_assign
id|mfdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnAP
c_func
(paren
l_int|0
)paren
)paren
op_amp
id|EBC0_BnAP_MASK
suffix:semicolon
id|ap.fields.twt
op_assign
l_int|8
suffix:semicolon
id|ap.fields.th
op_assign
l_int|2
suffix:semicolon
id|mtdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnAP
c_func
(paren
l_int|0
)paren
comma
id|ap.reg
)paren
suffix:semicolon
multiline_comment|/*  EBC bank 1 is used for many purposes: NVRAM, Ethernet, and FPGA&n;&t;   registers. This is a 1 MB, 16-bit bank. The access parameters must&n;&t;   handle the worst case of all of the devices. &n;&n;&t;   The Ethernet chip needs 20 ns setup of the addresses to the I/O&n;&t;   write signal (generated from the chip select), a minimum 150 ns&n;&t;   cycle, and 30 ns of turnaround.  These settings will work for the&n;&t;   other devices as well.&n;&t; */
id|cr.reg
op_assign
(paren
id|BEECH_BANK1_PADDR
op_amp
l_int|0xfff00000
)paren
op_or
(paren
id|mfdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnCR
c_func
(paren
l_int|1
)paren
)paren
op_amp
id|EBC0_BnCR_MASK
)paren
suffix:semicolon
id|cr.fields.bs
op_assign
id|BEECH_BANK1_EBC_SIZE
suffix:semicolon
id|cr.fields.bu
op_assign
id|EBC0_BnCR_BU_RW
suffix:semicolon
id|cr.fields.bw
op_assign
id|EBC0_BnCR_BW_16
suffix:semicolon
id|mtdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnCR
c_func
(paren
l_int|1
)paren
comma
id|cr.reg
)paren
suffix:semicolon
id|ap.reg
op_assign
id|mfdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnAP
c_func
(paren
l_int|1
)paren
)paren
op_amp
id|EBC0_BnAP_MASK
suffix:semicolon
id|ap.fields.twt
op_assign
l_int|10
suffix:semicolon
id|ap.fields.csn
op_assign
l_int|2
suffix:semicolon
id|ap.fields.th
op_assign
l_int|2
suffix:semicolon
id|mtdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnAP
c_func
(paren
l_int|1
)paren
comma
id|ap.reg
)paren
suffix:semicolon
multiline_comment|/* Set EBC bank 2 for the big (Linux) flash.  There is 16 MB of flash,&n;&t;   but the CPLD decodes a 32 MB region.&n;&n;&t;   Access parameters assume 90ns AMD flash @ 66.66 MHz maximum bus&n;&t;   speed = 6 cycle access with 2 turnaround cycles (30 ns).&n;&n;&t;   NB: IBM BIOS sets this bank to burst, however bursting will never&n;&t;   happen in Linux because this region is mapped non-cacheable and&n;&t;   guarded, so it is set non-burst here. */
id|cr.reg
op_assign
(paren
id|BEECH_BANK2_PADDR
op_amp
l_int|0xfff00000
)paren
op_or
(paren
id|mfdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnCR
c_func
(paren
l_int|2
)paren
)paren
op_amp
id|EBC0_BnCR_MASK
)paren
suffix:semicolon
id|cr.fields.bs
op_assign
id|BEECH_BANK2_EBC_SIZE
suffix:semicolon
id|cr.fields.bu
op_assign
id|EBC0_BnCR_BU_RW
suffix:semicolon
id|cr.fields.bw
op_assign
id|EBC0_BnCR_BW_8
suffix:semicolon
id|mtdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnCR
c_func
(paren
l_int|2
)paren
comma
id|cr.reg
)paren
suffix:semicolon
id|ap.reg
op_assign
id|mfdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnAP
c_func
(paren
l_int|2
)paren
)paren
op_amp
id|EBC0_BnAP_MASK
suffix:semicolon
id|ap.fields.twt
op_assign
l_int|6
suffix:semicolon
id|ap.fields.th
op_assign
l_int|2
suffix:semicolon
id|mtdcri
c_func
(paren
id|DCRN_EBC0
comma
id|BnAP
c_func
(paren
l_int|2
)paren
comma
id|ap.reg
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; * FPGA Setup&n; ****************************************************************************/
multiline_comment|/* The Beech FPGA is set up for Linux. */
r_static
r_void
id|__init
DECL|function|beech_fpga_setup
id|beech_fpga_setup
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u8
op_star
id|fpga_reg_2
suffix:semicolon
id|fpga_reg_2
op_assign
(paren
r_volatile
id|u8
op_star
)paren
id|ioremap
c_func
(paren
id|BEECH_FPGA_REG_2_PADDR
comma
id|BEECH_FPGA_REG_2_SIZE
)paren
suffix:semicolon
multiline_comment|/* Set RTS/CTS mode for UART 1 */
op_star
id|fpga_reg_2
op_or_assign
id|FPGA_REG_2_DEFAULT_UART1_N
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
