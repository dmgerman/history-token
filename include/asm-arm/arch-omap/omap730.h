multiline_comment|/* linux/include/asm-arm/arch-omap/omap730.h&n; *&n; * Hardware definitions for TI OMAP730 processor.&n; *&n; * Cleanup for Linux-2.6 by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP730_H
DECL|macro|__ASM_ARCH_OMAP730_H
mdefine_line|#define __ASM_ARCH_OMAP730_H
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Base addresses&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */
DECL|macro|OMAP730_SRAM_BASE
mdefine_line|#define OMAP730_SRAM_BASE&t;0xD0000000
DECL|macro|OMAP730_SRAM_SIZE
mdefine_line|#define OMAP730_SRAM_SIZE&t;(SZ_128K + SZ_64K + SZ_8K)
DECL|macro|OMAP730_SRAM_START
mdefine_line|#define OMAP730_SRAM_START&t;0x20000000
DECL|macro|OMAP730_MCBSP1_BASE
mdefine_line|#define OMAP730_MCBSP1_BASE&t;0xfffb1000
DECL|macro|OMAP730_MCBSP1_SIZE
mdefine_line|#define OMAP730_MCBSP1_SIZE&t;(SZ_1K * 2)
DECL|macro|OMAP730_MCBSP1_START
mdefine_line|#define OMAP730_MCBSP1_START&t;0xfffb1000
DECL|macro|OMAP730_MCBSP2_BASE
mdefine_line|#define OMAP730_MCBSP2_BASE&t;0xfffb1800
DECL|macro|OMAP730_DSP_BASE
mdefine_line|#define OMAP730_DSP_BASE&t;0xE0000000
DECL|macro|OMAP730_DSP_SIZE
mdefine_line|#define OMAP730_DSP_SIZE&t;0x50000
DECL|macro|OMAP730_DSP_START
mdefine_line|#define OMAP730_DSP_START&t;0xE0000000
DECL|macro|OMAP730_DSPREG_BASE
mdefine_line|#define OMAP730_DSPREG_BASE&t;0xE1000000
DECL|macro|OMAP730_DSPREG_SIZE
mdefine_line|#define OMAP730_DSPREG_SIZE&t;SZ_128K
DECL|macro|OMAP730_DSPREG_START
mdefine_line|#define OMAP730_DSPREG_START&t;0xE1000000
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * OMAP730 specific configuration registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP730_CONFIG_BASE
mdefine_line|#define OMAP730_CONFIG_BASE&t;0xfffe1000
DECL|macro|OMAP730_IO_CONF_0
mdefine_line|#define OMAP730_IO_CONF_0&t;0xfffe1070
DECL|macro|OMAP730_IO_CONF_1
mdefine_line|#define OMAP730_IO_CONF_1&t;0xfffe1074
DECL|macro|OMAP730_IO_CONF_2
mdefine_line|#define OMAP730_IO_CONF_2&t;0xfffe1078
DECL|macro|OMAP730_IO_CONF_3
mdefine_line|#define OMAP730_IO_CONF_3&t;0xfffe107c
DECL|macro|OMAP730_IO_CONF_4
mdefine_line|#define OMAP730_IO_CONF_4&t;0xfffe1080
DECL|macro|OMAP730_IO_CONF_5
mdefine_line|#define OMAP730_IO_CONF_5&t;0xfffe1084
DECL|macro|OMAP730_IO_CONF_6
mdefine_line|#define OMAP730_IO_CONF_6&t;0xfffe1088
DECL|macro|OMAP730_IO_CONF_7
mdefine_line|#define OMAP730_IO_CONF_7&t;0xfffe108c
DECL|macro|OMAP730_IO_CONF_8
mdefine_line|#define OMAP730_IO_CONF_8&t;0xfffe1090
DECL|macro|OMAP730_IO_CONF_9
mdefine_line|#define OMAP730_IO_CONF_9&t;0xfffe1094
DECL|macro|OMAP730_IO_CONF_10
mdefine_line|#define OMAP730_IO_CONF_10&t;0xfffe1098
DECL|macro|OMAP730_IO_CONF_11
mdefine_line|#define OMAP730_IO_CONF_11&t;0xfffe109c
DECL|macro|OMAP730_IO_CONF_12
mdefine_line|#define OMAP730_IO_CONF_12&t;0xfffe10a0
DECL|macro|OMAP730_IO_CONF_13
mdefine_line|#define OMAP730_IO_CONF_13&t;0xfffe10a4
DECL|macro|OMAP730_MODE_1
mdefine_line|#define OMAP730_MODE_1&t;&t;0xfffe1010
DECL|macro|OMAP730_MODE_2
mdefine_line|#define OMAP730_MODE_2&t;&t;0xfffe1014
multiline_comment|/* CSMI specials: in terms of base + offset */
DECL|macro|OMAP730_MODE2_OFFSET
mdefine_line|#define OMAP730_MODE2_OFFSET&t;0x14
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * OMAP730 traffic controller configuration registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP730_FLASH_CFG_0
mdefine_line|#define OMAP730_FLASH_CFG_0&t;0xfffecc10
DECL|macro|OMAP730_FLASH_ACFG_0
mdefine_line|#define OMAP730_FLASH_ACFG_0&t;0xfffecc50
DECL|macro|OMAP730_FLASH_CFG_1
mdefine_line|#define OMAP730_FLASH_CFG_1&t;0xfffecc14
DECL|macro|OMAP730_FLASH_ACFG_1
mdefine_line|#define OMAP730_FLASH_ACFG_1&t;0xfffecc54
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * OMAP730 DSP control registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP730_ICR_BASE
mdefine_line|#define OMAP730_ICR_BASE&t;0xfffbb800
DECL|macro|OMAP730_DSP_M_CTL
mdefine_line|#define OMAP730_DSP_M_CTL&t;0xfffbb804
DECL|macro|OMAP730_DSP_MMU_BASE
mdefine_line|#define OMAP730_DSP_MMU_BASE&t;0xfffed200
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * OMAP730 PCC_UPLD configuration registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP730_PCC_UPLD_CTRL_REG_BASE
mdefine_line|#define OMAP730_PCC_UPLD_CTRL_REG_BASE&t;(0xfffe0900)
DECL|macro|OMAP730_PCC_UPLD_CTRL_REG
mdefine_line|#define OMAP730_PCC_UPLD_CTRL_REG&t;(OMAP730_PCC_UPLD_CTRL_REG_BASE + 0x00)
macro_line|#endif /*  __ASM_ARCH_OMAP730_H */
eof
