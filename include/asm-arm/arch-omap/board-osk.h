multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/board-osk.h&n; *&n; * Hardware definitions for TI OMAP5912 OSK board.&n; *&n; * Written by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_OSK_H
DECL|macro|__ASM_ARCH_OMAP_OSK_H
mdefine_line|#define __ASM_ARCH_OMAP_OSK_H
multiline_comment|/* At OMAP5912 OSK the Ethernet is directly connected to CS1 */
DECL|macro|OMAP_OSK_ETHR_BASE
mdefine_line|#define OMAP_OSK_ETHR_BASE&t;&t;0xE8800000
DECL|macro|OMAP_OSK_ETHR_SIZE
mdefine_line|#define OMAP_OSK_ETHR_SIZE&t;&t;SZ_4K
DECL|macro|OMAP_OSK_ETHR_START
mdefine_line|#define OMAP_OSK_ETHR_START&t;&t;0x04800000
multiline_comment|/* Micron NOR flash at CS3 mapped to address 0x0 if BM bit is 1 */
DECL|macro|OMAP_OSK_NOR_FLASH_BASE
mdefine_line|#define OMAP_OSK_NOR_FLASH_BASE&t;&t;0xD8000000
DECL|macro|OMAP_OSK_NOR_FLASH_SIZE
mdefine_line|#define OMAP_OSK_NOR_FLASH_SIZE&t;&t;SZ_32M
DECL|macro|OMAP_OSK_NOR_FLASH_START
mdefine_line|#define OMAP_OSK_NOR_FLASH_START&t;0x00000000
macro_line|#endif /*  __ASM_ARCH_OMAP_OSK_H */
eof
