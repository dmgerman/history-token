multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/memory.h&n; *&n; * Memory map for OMAP-1510 and 1610&n; *&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * This file was derived from linux/include/asm-arm/arch-intergrator/memory.h&n; * Copyright (C) 1999 ARM Limited&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;&t;(0x10000000UL)
multiline_comment|/*&n; * OMAP-1510 Local Bus address offset&n; */
DECL|macro|OMAP1510_LB_OFFSET
mdefine_line|#define OMAP1510_LB_OFFSET&t;(0x30000000UL)
multiline_comment|/*&n; * Conversion between SDRAM and fake PCI bus, used by USB&n; * NOTE: Physical address must be converted to Local Bus address&n; *&t; on OMAP-1510 only&n; */
multiline_comment|/*&n; * Bus address is physical address, except for OMAP-1510 Local Bus.&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;__virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;__phys_to_virt(x)
multiline_comment|/*&n; * OMAP-1510 bus address is translated into a Local Bus address if the&n; * OMAP bus type is lbus. We do the address translation based on the&n; * device overriding the defaults used in the dma-mapping API.&n; * Note that the is_lbus_device() test is not very efficient on 1510&n; * because of the strncmp().&n; */
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|macro|virt_to_lbus
mdefine_line|#define virt_to_lbus(x)&t;&t;((x) - PAGE_OFFSET + OMAP1510_LB_OFFSET)
DECL|macro|lbus_to_virt
mdefine_line|#define lbus_to_virt(x)&t;&t;((x) - OMAP1510_LB_OFFSET + PAGE_OFFSET)
DECL|macro|is_lbus_device
mdefine_line|#define is_lbus_device(dev)&t;(cpu_is_omap1510() &amp;&amp; dev &amp;&amp; (strncmp(dev-&gt;bus_id, &quot;ohci&quot;, 4) == 0))
DECL|macro|__arch_page_to_dma
mdefine_line|#define __arch_page_to_dma(dev, page)&t;({is_lbus_device(dev) ? &bslash;&n;&t;&t;&t;&t;&t;(dma_addr_t)virt_to_lbus(page_address(page)) : &bslash;&n;&t;&t;&t;&t;&t;(dma_addr_t)__virt_to_bus(page_address(page));})
DECL|macro|__arch_dma_to_virt
mdefine_line|#define __arch_dma_to_virt(dev, addr)&t;({is_lbus_device(dev) ? &bslash;&n;&t;&t;&t;&t;&t;lbus_to_virt(addr) : &bslash;&n;&t;&t;&t;&t;&t;__bus_to_virt(addr);})
DECL|macro|__arch_virt_to_dma
mdefine_line|#define __arch_virt_to_dma(dev, addr)&t;({is_lbus_device(dev) ? &bslash;&n;&t;&t;&t;&t;&t;virt_to_lbus(addr) : &bslash;&n;&t;&t;&t;&t;&t;__virt_to_bus(addr);})
macro_line|#endif&t;/* CONFIG_ARCH_OMAP1510 */
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr) (0)
macro_line|#endif
eof
