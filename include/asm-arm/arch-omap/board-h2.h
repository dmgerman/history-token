multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/board-h2.h&n; *&n; * Hardware definitions for TI OMAP1610 H2 board.&n; *&n; * Cleanup for Linux-2.6 by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_H2_H
DECL|macro|__ASM_ARCH_OMAP_H2_H
mdefine_line|#define __ASM_ARCH_OMAP_H2_H
multiline_comment|/* Placeholder for H2 specific defines */
multiline_comment|/* At OMAP1610 Innovator the Ethernet is directly connected to CS1 */
DECL|macro|OMAP1610_ETHR_BASE
mdefine_line|#define OMAP1610_ETHR_BASE&t;&t;0xE8000000
DECL|macro|OMAP1610_ETHR_SIZE
mdefine_line|#define OMAP1610_ETHR_SIZE&t;&t;SZ_4K
DECL|macro|OMAP1610_ETHR_START
mdefine_line|#define OMAP1610_ETHR_START&t;&t;0x04000000
multiline_comment|/* Intel STRATA NOR flash at CS3 or CS2B(NAND Boot) */
DECL|macro|OMAP_NOR_FLASH_SIZE
mdefine_line|#define OMAP_NOR_FLASH_SIZE             SZ_32M
DECL|macro|OMAP_NOR_FLASH_START1
mdefine_line|#define OMAP_NOR_FLASH_START1           0x0C000000 /* CS3 */
DECL|macro|OMAP_NOR_FLASH_START2
mdefine_line|#define OMAP_NOR_FLASH_START2           0x0A000000 /* CS2B */
multiline_comment|/* Samsung NAND flash at CS2B or CS3(NAND Boot) */
DECL|macro|OMAP_NAND_FLASH_START1
mdefine_line|#define OMAP_NAND_FLASH_START1           0x0A000000 /* CS2B */
DECL|macro|OMAP_NAND_FLASH_START2
mdefine_line|#define OMAP_NAND_FLASH_START2           0x0C000000 /* CS3 */
macro_line|#endif /*  __ASM_ARCH_OMAP_H2_H */
eof
