multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/io.h&n; *&n; * IO definitions for TI OMAP processors and boards&n; *&n; * Copied from linux/include/asm-arm/arch-sa1100/io.h&n; * Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Modifications:&n; *  06-12-1997&t;RMK&t;Created.&n; *  07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * We don&squot;t actually have real ISA nor PCI buses, but there is so many&n; * drivers out there that might just work if we fake them...&n; */
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;((void __iomem *)(PCIO_BASE + (a)))
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;(a)
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;(a)
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * I/O mapping&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|IO_PHYS
mdefine_line|#define IO_PHYS&t;&t;&t;0xFFFB0000
DECL|macro|IO_OFFSET
mdefine_line|#define IO_OFFSET&t;&t;0x01000000&t;/* Virtual IO = 0xfefb0000 */
DECL|macro|IO_VIRT
mdefine_line|#define IO_VIRT&t;&t;&t;(IO_PHYS - IO_OFFSET)
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x40000
DECL|macro|IO_ADDRESS
mdefine_line|#define IO_ADDRESS(x)&t;&t;((x) - IO_OFFSET)
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0
DECL|macro|io_p2v
mdefine_line|#define io_p2v(x)               ((x) - IO_OFFSET)
DECL|macro|io_v2p
mdefine_line|#define io_v2p(x)               ((x) + IO_OFFSET)
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/*&n; * Functions to access the OMAP IO region&n; *&n; * NOTE: - Use omap_read/write[bwl] for physical register addresses&n; *&t; - Use __raw_read/write[bwl]() for virtual register addresses&n; *&t; - Use IO_ADDRESS(phys_addr) to convert registers to virtual addresses&n; *&t; - DO NOT use hardcoded virtual addresses to allow changing the&n; *&t;   IO address space again if needed&n; */
DECL|macro|omap_readb
mdefine_line|#define omap_readb(a)&t;&t;(*(volatile unsigned char  *)IO_ADDRESS(a))
DECL|macro|omap_readw
mdefine_line|#define omap_readw(a)&t;&t;(*(volatile unsigned short *)IO_ADDRESS(a))
DECL|macro|omap_readl
mdefine_line|#define omap_readl(a)&t;&t;(*(volatile unsigned int   *)IO_ADDRESS(a))
DECL|macro|omap_writeb
mdefine_line|#define omap_writeb(v,a)&t;(*(volatile unsigned char  *)IO_ADDRESS(a) = (v))
DECL|macro|omap_writew
mdefine_line|#define omap_writew(v,a)&t;(*(volatile unsigned short *)IO_ADDRESS(a) = (v))
DECL|macro|omap_writel
mdefine_line|#define omap_writel(v,a)&t;(*(volatile unsigned int   *)IO_ADDRESS(a) = (v))
multiline_comment|/* 16 bit uses LDRH/STRH, base +/- offset_8 */
DECL|member|offset
DECL|typedef|__regbase16
r_typedef
r_struct
(brace
r_volatile
id|u16
id|offset
(braket
l_int|256
)braket
suffix:semicolon
)brace
id|__regbase16
suffix:semicolon
DECL|macro|__REGV16
mdefine_line|#define __REGV16(vaddr)&t;&t;((__regbase16 *)((vaddr)&amp;~0xff)) &bslash;&n;&t;&t;&t;&t;&t;-&gt;offset[((vaddr)&amp;0xff)&gt;&gt;1]
DECL|macro|__REG16
mdefine_line|#define __REG16(paddr)          __REGV16(io_p2v(paddr))
multiline_comment|/* 8/32 bit uses LDR/STR, base +/- offset_12 */
DECL|member|offset
DECL|typedef|__regbase8
r_typedef
r_struct
(brace
r_volatile
id|u8
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase8
suffix:semicolon
DECL|macro|__REGV8
mdefine_line|#define __REGV8(vaddr)&t;&t;((__regbase8  *)((vaddr)&amp;~4095)) &bslash;&n;&t;&t;&t;&t;&t;-&gt;offset[((vaddr)&amp;4095)&gt;&gt;0]
DECL|macro|__REG8
mdefine_line|#define __REG8(paddr)&t;&t;__REGV8(io_p2v(paddr))
DECL|member|offset
DECL|typedef|__regbase32
r_typedef
r_struct
(brace
r_volatile
id|u32
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase32
suffix:semicolon
DECL|macro|__REGV32
mdefine_line|#define __REGV32(vaddr)&t;&t;((__regbase32 *)((vaddr)&amp;~4095)) &bslash;&n;&t;&t;&t;&t;&t;-&gt;offset[((vaddr)&amp;4095)&gt;&gt;2]
DECL|macro|__REG32
mdefine_line|#define __REG32(paddr)&t;&t;__REGV32(io_p2v(paddr))
macro_line|#else
DECL|macro|__REG8
mdefine_line|#define __REG8(paddr)&t;&t;io_p2v(paddr)
DECL|macro|__REG16
mdefine_line|#define __REG16(paddr)&t;&t;io_p2v(paddr)
DECL|macro|__REG32
mdefine_line|#define __REG32(paddr)&t;&t;io_p2v(paddr)
macro_line|#endif
macro_line|#endif
eof
