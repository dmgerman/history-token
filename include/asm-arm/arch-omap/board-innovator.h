multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/board-innovator.h&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_INNOVATOR_H
DECL|macro|__ASM_ARCH_OMAP_INNOVATOR_H
mdefine_line|#define __ASM_ARCH_OMAP_INNOVATOR_H
macro_line|#if defined (CONFIG_ARCH_OMAP1510)
macro_line|#ifndef OMAP_SDRAM_DEVICE
DECL|macro|OMAP_SDRAM_DEVICE
mdefine_line|#define OMAP_SDRAM_DEVICE&t;&t;&t;D256M_1X16_4B
macro_line|#endif
DECL|macro|OMAP1510P1_IMIF_PRI_VALUE
mdefine_line|#define OMAP1510P1_IMIF_PRI_VALUE&t;&t;0x00
DECL|macro|OMAP1510P1_EMIFS_PRI_VALUE
mdefine_line|#define OMAP1510P1_EMIFS_PRI_VALUE&t;&t;0x00
DECL|macro|OMAP1510P1_EMIFF_PRI_VALUE
mdefine_line|#define OMAP1510P1_EMIFF_PRI_VALUE&t;&t;0x00
multiline_comment|/*&n; * These definitions define an area of FLASH set aside&n; * for the use of MTD/JFFS2. This is the area of flash&n; * that a JFFS2 filesystem will reside which is mounted&n; * at boot with the &quot;root=/dev/mtdblock/0 rw&quot;&n; * command line option. The flash address used here must&n; * fall within the legal range defined by rrload for storing&n; * the filesystem component. This address will be sufficiently&n; * deep into the overall flash range to avoid the other&n; * components also stored in flash such as the bootloader,&n; * the bootloader params, and the kernel.&n; * The SW2 settings for the map below are:&n; * 1 off, 2 off, 3 on, 4 off.&n; */
multiline_comment|/* Intel flash_0, partitioned as expected by rrload */
DECL|macro|OMAP_FLASH_0_BASE
mdefine_line|#define OMAP_FLASH_0_BASE&t;0xD8000000
DECL|macro|OMAP_FLASH_0_START
mdefine_line|#define OMAP_FLASH_0_START&t;0x00000000
DECL|macro|OMAP_FLASH_0_SIZE
mdefine_line|#define OMAP_FLASH_0_SIZE&t;SZ_16M
multiline_comment|/* Intel flash_1, used for cramfs or other flash file systems */
DECL|macro|OMAP_FLASH_1_BASE
mdefine_line|#define OMAP_FLASH_1_BASE&t;0xD9000000
DECL|macro|OMAP_FLASH_1_START
mdefine_line|#define OMAP_FLASH_1_START&t;0x01000000
DECL|macro|OMAP_FLASH_1_SIZE
mdefine_line|#define OMAP_FLASH_1_SIZE&t;SZ_16M
DECL|macro|NR_FPGA_IRQS
mdefine_line|#define NR_FPGA_IRQS&t;&t;24
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                 IH_BOARD_BASE + NR_FPGA_IRQS
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
macro_line|#endif /* CONFIG_ARCH_OMAP1510 */
macro_line|#if defined (CONFIG_ARCH_OMAP16XX)
multiline_comment|/* At OMAP1610 Innovator the Ethernet is directly connected to CS1 */
DECL|macro|INNOVATOR1610_ETHR_START
mdefine_line|#define INNOVATOR1610_ETHR_START&t;0x04000000
DECL|macro|INNOVATOR1610_ETHR_SIZE
mdefine_line|#define INNOVATOR1610_ETHR_SIZE&t;&t;SZ_4K
macro_line|#endif /* CONFIG_ARCH_OMAP1610 */
macro_line|#endif /* __ASM_ARCH_OMAP_INNOVATOR_H */
eof
