multiline_comment|/* linux/include/asm-arm/arch-omap/omap5912.h&n; *&n; * Hardware definitions for TI OMAP5912 processor.&n; *&n; * Written by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP5912_H
DECL|macro|__ASM_ARCH_OMAP5912_H
mdefine_line|#define __ASM_ARCH_OMAP5912_H
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Base addresses&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/* Syntax: XX_BASE = Virtual base address, XX_START = Physical base address */
multiline_comment|/* OMAP5912 internal SRAM size is 250kByte */
DECL|macro|OMAP5912_SRAM_BASE
mdefine_line|#define OMAP5912_SRAM_BASE&t;0xD0000000
DECL|macro|OMAP5912_SRAM_SIZE
mdefine_line|#define OMAP5912_SRAM_SIZE&t;0x3E800
DECL|macro|OMAP5912_SRAM_START
mdefine_line|#define OMAP5912_SRAM_START&t;0x20000000
DECL|macro|OMAP5912_DSP_BASE
mdefine_line|#define OMAP5912_DSP_BASE&t;0xE0000000
DECL|macro|OMAP5912_DSP_SIZE
mdefine_line|#define OMAP5912_DSP_SIZE&t;0x50000
DECL|macro|OMAP5912_DSP_START
mdefine_line|#define OMAP5912_DSP_START&t;0xE0000000
DECL|macro|OMAP5912_DSPREG_BASE
mdefine_line|#define OMAP5912_DSPREG_BASE&t;0xE1000000
DECL|macro|OMAP5912_DSPREG_SIZE
mdefine_line|#define OMAP5912_DSPREG_SIZE&t;SZ_128K
DECL|macro|OMAP5912_DSPREG_START
mdefine_line|#define OMAP5912_DSPREG_START&t;0xE1000000
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * System control registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|OMAP5912_ARM_IDLECT3
mdefine_line|#define OMAP5912_ARM_IDLECT3&t;&t;(CLKGEN_RESET_BASE + 0x24)
macro_line|#endif /*  __ASM_ARCH_OMAP5912_H */
eof
