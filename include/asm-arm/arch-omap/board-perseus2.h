multiline_comment|/*&n; *  linux/include/asm-arm/arch-omap/board-perseus2.h&n; *&n; *  Copyright 2003 by Texas Instruments Incorporated&n; *    OMAP730 / P2-sample additions&n; *    Author: Jean Pihet&n; *&n; * Copyright (C) 2001 RidgeRun, Inc. (http://www.ridgerun.com)&n; * Author: RidgeRun, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_P2SAMPLE_H
DECL|macro|__ASM_ARCH_OMAP_P2SAMPLE_H
mdefine_line|#define __ASM_ARCH_OMAP_P2SAMPLE_H
macro_line|#if defined(CONFIG_ARCH_OMAP730) &amp;&amp; defined (CONFIG_MACH_OMAP_PERSEUS2)
multiline_comment|/*&n; * NOTE:  ALL DEFINITIONS IN THIS FILE NEED TO BE PREFIXED BY IDENTIFIER&n; *&t;  P2SAMPLE_ since they are specific to the EVM and not the chip.&n; */
multiline_comment|/* ---------------------------------------------------------------------------&n; *  OMAP730 Debug Board FPGA&n; * ---------------------------------------------------------------------------&n; */
multiline_comment|/* maps in the FPGA registers and the ETHR registers */
DECL|macro|OMAP730_FPGA_BASE
mdefine_line|#define OMAP730_FPGA_BASE&t;&t;0xE8000000&t;/* VA */
DECL|macro|OMAP730_FPGA_SIZE
mdefine_line|#define OMAP730_FPGA_SIZE&t;&t;SZ_4K&t;&t;/* SIZE */
DECL|macro|OMAP730_FPGA_START
mdefine_line|#define OMAP730_FPGA_START&t;&t;0x04000000&t;/* PA */
DECL|macro|OMAP730_FPGA_ETHR_START
mdefine_line|#define OMAP730_FPGA_ETHR_START&t;&t;OMAP730_FPGA_START
DECL|macro|OMAP730_FPGA_ETHR_BASE
mdefine_line|#define OMAP730_FPGA_ETHR_BASE&t;&t;OMAP730_FPGA_BASE
DECL|macro|OMAP730_FPGA_FPGA_REV
mdefine_line|#define OMAP730_FPGA_FPGA_REV&t;&t;(OMAP730_FPGA_BASE + 0x10)&t;/* FPGA Revision */
DECL|macro|OMAP730_FPGA_BOARD_REV
mdefine_line|#define OMAP730_FPGA_BOARD_REV&t;&t;(OMAP730_FPGA_BASE + 0x12)&t;/* Board Revision */
DECL|macro|OMAP730_FPGA_GPIO
mdefine_line|#define OMAP730_FPGA_GPIO&t;&t;(OMAP730_FPGA_BASE + 0x14)&t;/* GPIO outputs */
DECL|macro|OMAP730_FPGA_LEDS
mdefine_line|#define OMAP730_FPGA_LEDS&t;&t;(OMAP730_FPGA_BASE + 0x16)&t;/* LEDs outputs */
DECL|macro|OMAP730_FPGA_MISC_INPUTS
mdefine_line|#define OMAP730_FPGA_MISC_INPUTS&t;(OMAP730_FPGA_BASE + 0x18)&t;/* Misc inputs */
DECL|macro|OMAP730_FPGA_LAN_STATUS
mdefine_line|#define OMAP730_FPGA_LAN_STATUS&t;&t;(OMAP730_FPGA_BASE + 0x1A)&t;/* LAN Status line */
DECL|macro|OMAP730_FPGA_LAN_RESET
mdefine_line|#define OMAP730_FPGA_LAN_RESET&t;&t;(OMAP730_FPGA_BASE + 0x1C)&t;/* LAN Reset line */
singleline_comment|// LEDs definition on debug board (16 LEDs)
DECL|macro|OMAP730_FPGA_LED_CLAIMRELEASE
mdefine_line|#define OMAP730_FPGA_LED_CLAIMRELEASE&t;(1 &lt;&lt; 15)
DECL|macro|OMAP730_FPGA_LED_STARTSTOP
mdefine_line|#define OMAP730_FPGA_LED_STARTSTOP&t;(1 &lt;&lt; 14)
DECL|macro|OMAP730_FPGA_LED_HALTED
mdefine_line|#define OMAP730_FPGA_LED_HALTED&t;&t;(1 &lt;&lt; 13)
DECL|macro|OMAP730_FPGA_LED_IDLE
mdefine_line|#define OMAP730_FPGA_LED_IDLE&t;&t;(1 &lt;&lt; 12)
DECL|macro|OMAP730_FPGA_LED_TIMER
mdefine_line|#define OMAP730_FPGA_LED_TIMER&t;&t;(1 &lt;&lt; 11)
singleline_comment|// cpu0 load-meter LEDs
DECL|macro|OMAP730_FPGA_LOAD_METER
mdefine_line|#define OMAP730_FPGA_LOAD_METER&t;&t;(1 &lt;&lt; 0)&t;
singleline_comment|// A bit of fun on our board ...
DECL|macro|OMAP730_FPGA_LOAD_METER_SIZE
mdefine_line|#define OMAP730_FPGA_LOAD_METER_SIZE&t;11
DECL|macro|OMAP730_FPGA_LOAD_METER_MASK
mdefine_line|#define OMAP730_FPGA_LOAD_METER_MASK&t;((1 &lt;&lt; OMAP730_FPGA_LOAD_METER_SIZE) - 1)
macro_line|#ifndef OMAP_SDRAM_DEVICE
DECL|macro|OMAP_SDRAM_DEVICE
mdefine_line|#define OMAP_SDRAM_DEVICE&t;&t;D256M_1X16_4B
macro_line|#endif
multiline_comment|/*&n; * These definitions define an area of FLASH set aside&n; * for the use of MTD/JFFS2. This is the area of flash&n; * that a JFFS2 filesystem will reside which is mounted&n; * at boot with the &quot;root=/dev/mtdblock/0 rw&quot;&n; * command line option.&n; */
multiline_comment|/* Intel flash_0, partitioned as expected by rrload */
DECL|macro|OMAP_FLASH_0_BASE
mdefine_line|#define OMAP_FLASH_0_BASE&t;0xD8000000&t;/* VA */
DECL|macro|OMAP_FLASH_0_START
mdefine_line|#define OMAP_FLASH_0_START&t;0x00000000&t;/* PA */
DECL|macro|OMAP_FLASH_0_SIZE
mdefine_line|#define OMAP_FLASH_0_SIZE&t;SZ_32M
multiline_comment|/* The Ethernet Controller IRQ is cascaded to MPU_EXT_nIRQ througb the FPGA */
DECL|macro|INT_ETHER
mdefine_line|#define INT_ETHER&t;&t;INT_730_MPU_EXT_NIRQ
DECL|macro|MAXIRQNUM
mdefine_line|#define MAXIRQNUM&t;&t;IH_BOARD_BASE
DECL|macro|MAXFIQNUM
mdefine_line|#define MAXFIQNUM&t;&t;MAXIRQNUM
DECL|macro|MAXSWINUM
mdefine_line|#define MAXSWINUM&t;&t;MAXIRQNUM
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(MAXIRQNUM + 1)
macro_line|#ifndef __ASSEMBLY__
r_void
id|fpga_write
c_func
(paren
r_int
r_char
id|val
comma
r_int
id|reg
)paren
suffix:semicolon
r_int
r_char
id|fpga_read
c_func
(paren
r_int
id|reg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
macro_line|#error &quot;Only OMAP730 Perseus2 supported!&quot;
macro_line|#endif
macro_line|#endif
eof
