multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 Waldorf GmbH&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2004, 2005  MIPS Technologies, Inc.  All rights reserved.&n; *&t;Author:&t;Maciej W. Rozycki &lt;macro@mips.com&gt;&n; */
macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/cpu-features.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable-bits.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;mangle-port.h&gt;
multiline_comment|/*&n; * Slowdown I/O port space accesses for antique hardware.&n; */
DECL|macro|CONF_SLOWDOWN_IO
macro_line|#undef CONF_SLOWDOWN_IO
multiline_comment|/*&n; * Raw operations are never swapped in software.  Otoh values that raw&n; * operations are working on may or may not have been swapped by the bus&n; * hardware.  An example use would be for flash memory that&squot;s used for&n; * execute in place.&n; */
DECL|macro|__raw_ioswabb
macro_line|# define __raw_ioswabb(x)&t;(x)
DECL|macro|__raw_ioswabw
macro_line|# define __raw_ioswabw(x)&t;(x)
DECL|macro|__raw_ioswabl
macro_line|# define __raw_ioswabl(x)&t;(x)
DECL|macro|__raw_ioswabq
macro_line|# define __raw_ioswabq(x)&t;(x)
multiline_comment|/*&n; * Sane hardware offers swapping of PCI/ISA I/O space accesses in hardware;&n; * less sane hardware forces software to fiddle with this...&n; */
macro_line|#if defined(CONFIG_SWAP_IO_SPACE)
DECL|macro|ioswabb
macro_line|# define ioswabb(x)&t;&t;(x)
macro_line|# ifdef CONFIG_SGI_IP22
multiline_comment|/*&n; * IP22 seems braindead enough to swap 16bits values in hardware, but&n; * not 32bits.  Go figure... Can&squot;t tell without documentation.&n; */
DECL|macro|ioswabw
macro_line|#  define ioswabw(x)&t;&t;(x)
macro_line|# else
DECL|macro|ioswabw
macro_line|#  define ioswabw(x)&t;&t;le16_to_cpu(x)
macro_line|# endif
DECL|macro|ioswabl
macro_line|# define ioswabl(x)&t;&t;le32_to_cpu(x)
DECL|macro|ioswabq
macro_line|# define ioswabq(x)&t;&t;le64_to_cpu(x)
macro_line|#else
DECL|macro|ioswabb
macro_line|# define ioswabb(x)&t;&t;(x)
DECL|macro|ioswabw
macro_line|# define ioswabw(x)&t;&t;(x)
DECL|macro|ioswabl
macro_line|# define ioswabl(x)&t;&t;(x)
DECL|macro|ioswabq
macro_line|# define ioswabq(x)&t;&t;(x)
macro_line|#endif
multiline_comment|/*&n; * Native bus accesses never swapped.&n; */
DECL|macro|bus_ioswabb
mdefine_line|#define bus_ioswabb(x)&t;&t;(x)
DECL|macro|bus_ioswabw
mdefine_line|#define bus_ioswabw(x)&t;&t;(x)
DECL|macro|bus_ioswabl
mdefine_line|#define bus_ioswabl(x)&t;&t;(x)
DECL|macro|bus_ioswabq
mdefine_line|#define bus_ioswabq(x)&t;&t;(x)
DECL|macro|__bus_ioswabq
mdefine_line|#define __bus_ioswabq&t;&t;bus_ioswabq
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/*&n; * On MIPS I/O ports are memory mapped, so we access them using normal&n; * load/store instructions. mips_io_port_base is the virtual address to&n; * which all ports are being mapped.  For sake of efficiency some code&n; * assumes that this is an address that can be loaded with a single lui&n; * instruction, so the lower 16 bits must be zero.  Should be true on&n; * on any sane architecture; generic code does not use this assumption.&n; */
r_extern
r_const
r_int
r_int
id|mips_io_port_base
suffix:semicolon
DECL|macro|set_io_port_base
mdefine_line|#define set_io_port_base(base)&t;&bslash;&n;&t;do { * (unsigned long *) &amp;mips_io_port_base = (base); } while (0)
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; *&n; */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;sb&bslash;t$0,0x80(%0)&quot; &bslash;&n;&t;&t;: : &quot;r&quot; (mips_io_port_base));
macro_line|#ifdef CONF_SLOWDOWN_IO
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; *     virt_to_phys    -       map virtual addresses to physical&n; *     @address: address to remap&n; *&n; *     The returned physical address is the physical (CPU) mapping for&n; *     the memory address given. It is only valid to use this function on&n; *     addresses directly mapped or allocated via kmalloc.&n; *&n; *     This function does not give bus mappings for DMA transfers. In&n; *     almost all conceivable cases a device driver should not be using&n; *     this function&n; */
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|PAGE_OFFSET
suffix:semicolon
)brace
multiline_comment|/*&n; *     phys_to_virt    -       map physical address to virtual&n; *     @address: address to remap&n; *&n; *     The returned virtual address is a current CPU mapping for&n; *     the memory address given. It is only valid to use this function on&n; *     addresses that have a kernel mapping&n; *&n; *     This function does not handle bus mappings for DMA transfers. In&n; *     almost all conceivable cases a device driver should not be using&n; *     this function&n; */
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ISA I/O bus memory addresses are 1:1 with the physical address.&n; */
DECL|function|isa_virt_to_bus
r_static
r_inline
r_int
r_int
id|isa_virt_to_bus
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|PAGE_OFFSET
suffix:semicolon
)brace
DECL|function|isa_bus_to_virt
r_static
r_inline
r_void
op_star
id|isa_bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
DECL|macro|isa_page_to_bus
mdefine_line|#define isa_page_to_bus page_to_phys
multiline_comment|/*&n; * However PCI ones are not necessarily 1:1 and therefore these interfaces&n; * are forbidden in portable PCI drivers.&n; *&n; * Allow them for x86 for legacy drivers, though.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is mapped&n; * for the processor.  This implies the assumption that there is only&n; * one of these busses.&n; */
r_extern
r_int
r_int
id|isa_slot_offset
suffix:semicolon
multiline_comment|/*&n; * Change &quot;struct page&quot; to physical address.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;((dma_addr_t)page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
id|phys_t
id|offset
comma
id|phys_t
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|__iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
suffix:semicolon
DECL|function|__ioremap_mode
r_static
r_inline
r_void
op_star
id|__ioremap_mode
c_func
(paren
id|phys_t
id|offset
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_64bit_addresses
)paren
(brace
id|u64
id|base
op_assign
id|UNCAC_BASE
suffix:semicolon
multiline_comment|/*&n;&t;&t; * R10000 supports a 2 bit uncached attribute therefore&n;&t;&t; * UNCAC_BASE may not equal IO_BASE.&n;&t;&t; */
r_if
c_cond
(paren
id|flags
op_eq
id|_CACHE_UNCACHED
)paren
id|base
op_assign
(paren
id|u64
)paren
id|IO_BASE
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
(paren
id|base
op_plus
id|offset
)paren
suffix:semicolon
)brace
r_return
id|__ioremap
c_func
(paren
id|offset
comma
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ioremap     -   map bus memory into CPU space&n; * @offset:    bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address.&n; */
DECL|macro|ioremap
mdefine_line|#define ioremap(offset, size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ioremap_mode((offset), (size), _CACHE_UNCACHED)
multiline_comment|/*&n; * ioremap_nocache     -   map bus memory into CPU space&n; * @offset:    bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap_nocache performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address.&n; *&n; * This version of ioremap ensures that the memory is marked uncachable&n; * on the CPU as well as honouring existing caching rules from things like&n; * the PCI bus. Note that there are other caches and buffers on many&n; * busses. In paticular driver authors should read up on PCI writes&n; *&n; * It&squot;s useful if some control registers are in such an area and&n; * write combining or read caching is not desirable:&n; */
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(offset, size)&t;&t;&t;&t;&t;&bslash;&n;&t;__ioremap_mode((offset), (size), _CACHE_UNCACHED)
multiline_comment|/*&n; * These two are MIPS specific ioremap variant.  ioremap_cacheable_cow&n; * requests a cachable mapping, ioremap_uncached_accelerated requests a&n; * mapping using the uncached accelerated mode which isn&squot;t supported on&n; * all processors.&n; */
DECL|macro|ioremap_cacheable_cow
mdefine_line|#define ioremap_cacheable_cow(offset, size)&t;&t;&t;&t;&bslash;&n;&t;__ioremap_mode((offset), (size), _CACHE_CACHABLE_COW)
DECL|macro|ioremap_uncached_accelerated
mdefine_line|#define ioremap_uncached_accelerated(offset, size)&t;&t;&t;&bslash;&n;&t;__ioremap_mode((offset), (size), _CACHE_UNCACHED_ACCELERATED)
DECL|function|iounmap
r_static
r_inline
r_void
id|iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_64bit_addresses
)paren
r_return
suffix:semicolon
id|__iounmap
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|__BUILD_MEMORY_SINGLE
mdefine_line|#define __BUILD_MEMORY_SINGLE(pfx, bwlq, type, irq)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void pfx##write##bwlq(type val,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;    volatile void __iomem *mem)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__mem;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;type __val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__mem = (void *)__swizzle_addr_##bwlq((unsigned long)(mem));&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__val = pfx##ioswab##bwlq(val);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(type) != sizeof(u64) || sizeof(u64) == sizeof(long))&t;&bslash;&n;&t;&t;*__mem = __val;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else if (cpu_has_64bits) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __flags;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;type __tmp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (irq)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;local_irq_save(__flags);&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;mips3&quot;&t;&t;&quot;&bslash;t&bslash;t# __writeq&quot;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;dsll32&t;%L0, %L0, 0&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;dsrl32&t;%L0, %L0, 0&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;dsll32&t;%M0, %M0, 0&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;or&t;%L0, %L0, %M0&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;sd&t;%L0, %2&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;mips0&quot;&t;&t;&t;&t;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (__tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;0&quot; (__val), &quot;m&quot; (*__mem));&t;&t;&t;&bslash;&n;&t;&t;if (irq)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;local_irq_restore(__flags);&t;&t;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline type pfx##read##bwlq(volatile void __iomem *mem)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__mem;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;type __val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__mem = (void *)__swizzle_addr_##bwlq((unsigned long)(mem));&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(type) != sizeof(u64) || sizeof(u64) == sizeof(long))&t;&bslash;&n;&t;&t;__val = *__mem;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else if (cpu_has_64bits) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __flags;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_save(__flags);&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;mips3&quot;&t;&t;&quot;&bslash;t&bslash;t# __readq&quot;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;ld&t;%L0, %1&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;dsra32&t;%M0, %L0, 0&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;sll&t;%L0, %L0, 0&quot;&t;&t;&t;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;mips0&quot;&t;&t;&t;&t;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (__val)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;m&quot; (*__mem));&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_restore(__flags);&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return pfx##ioswab##bwlq(__val);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__BUILD_IOPORT_SINGLE
mdefine_line|#define __BUILD_IOPORT_SINGLE(pfx, bwlq, type, p, slow)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void pfx##out##bwlq##p(type val, unsigned long port)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__addr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;type __val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;port = __swizzle_addr_##bwlq(port);&t;&t;&t;&t;&bslash;&n;&t;__addr = (void *)(mips_io_port_base + port);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__val = pfx##ioswab##bwlq(val);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(type) != sizeof(u64)) {&t;&t;&t;&t;&bslash;&n;&t;&t;*__addr = __val;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;slow;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;BUILD_BUG();&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline type pfx##in##bwlq##p(unsigned long port)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__addr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;type __val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;port = __swizzle_addr_##bwlq(port);&t;&t;&t;&t;&bslash;&n;&t;__addr = (void *)(mips_io_port_base + port);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(type) != sizeof(u64)) {&t;&t;&t;&t;&bslash;&n;&t;&t;__val = *__addr;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;slow;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;BUILD_BUG();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return pfx##ioswab##bwlq(__val);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__BUILD_MEMORY_PFX
mdefine_line|#define __BUILD_MEMORY_PFX(bus, bwlq, type)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__BUILD_MEMORY_SINGLE(bus, bwlq, type, 1)
DECL|macro|__BUILD_IOPORT_PFX
mdefine_line|#define __BUILD_IOPORT_PFX(bus, bwlq, type)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__BUILD_IOPORT_SINGLE(bus, bwlq, type, ,)&t;&t;&t;&t;&bslash;&n;__BUILD_IOPORT_SINGLE(bus, bwlq, type, _p, SLOW_DOWN_IO)
DECL|macro|BUILDIO
mdefine_line|#define BUILDIO(bwlq, type)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__BUILD_MEMORY_PFX(, bwlq, type)&t;&t;&t;&t;&t;&bslash;&n;__BUILD_MEMORY_PFX(__raw_, bwlq, type)&t;&t;&t;&t;&t;&bslash;&n;__BUILD_MEMORY_PFX(bus_, bwlq, type)&t;&t;&t;&t;&t;&bslash;&n;__BUILD_IOPORT_PFX(, bwlq, type)&t;&t;&t;&t;&t;&bslash;&n;__BUILD_IOPORT_PFX(__raw_, bwlq, type)
DECL|macro|__BUILDIO
mdefine_line|#define __BUILDIO(bwlq, type)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__BUILD_MEMORY_SINGLE(__bus_, bwlq, type, 0)
id|BUILDIO
c_func
(paren
id|b
comma
id|u8
)paren
id|BUILDIO
c_func
(paren
id|w
comma
id|u16
)paren
id|BUILDIO
c_func
(paren
id|l
comma
id|u32
)paren
id|BUILDIO
c_func
(paren
id|q
comma
id|u64
)paren
id|__BUILDIO
c_func
(paren
id|q
comma
id|u64
)paren
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed&t;&t;&t;readb
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed&t;&t;&t;readw
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed&t;&t;&t;readl
DECL|macro|readq_relaxed
mdefine_line|#define readq_relaxed&t;&t;&t;readq
multiline_comment|/*&n; * Some code tests for these symbols&n; */
DECL|macro|readq
mdefine_line|#define readq&t;&t;&t;&t;readq
DECL|macro|writeq
mdefine_line|#define writeq&t;&t;&t;&t;writeq
DECL|macro|__BUILD_MEMORY_STRING
mdefine_line|#define __BUILD_MEMORY_STRING(bwlq, type)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void writes##bwlq(volatile void __iomem *mem, void *addr,&t;&bslash;&n;&t;&t;&t;&t;unsigned int count)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__addr = addr;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (count--) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__raw_write##bwlq(*__addr, mem);&t;&t;&t;&bslash;&n;&t;&t;__addr++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void reads##bwlq(volatile void __iomem *mem, void *addr,&t;&bslash;&n;&t;&t;&t;       unsigned int count)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__addr = addr;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (count--) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*__addr = __raw_read##bwlq(mem);&t;&t;&t;&bslash;&n;&t;&t;__addr++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__BUILD_IOPORT_STRING
mdefine_line|#define __BUILD_IOPORT_STRING(bwlq, type)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void outs##bwlq(unsigned long port, void *addr,&t;&t;&bslash;&n;&t;&t;&t;      unsigned int count)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__addr = addr;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (count--) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__raw_out##bwlq(*__addr, port);&t;&t;&t;&t;&bslash;&n;&t;&t;__addr++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void ins##bwlq(unsigned long port, void *addr,&t;&t;&bslash;&n;&t;&t;&t;     unsigned int count)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile type *__addr = addr;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (count--) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*__addr = __raw_in##bwlq(port);&t;&t;&t;&t;&bslash;&n;&t;&t;__addr++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|BUILDSTRING
mdefine_line|#define BUILDSTRING(bwlq, type)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__BUILD_MEMORY_STRING(bwlq, type)&t;&t;&t;&t;&t;&bslash;&n;__BUILD_IOPORT_STRING(bwlq, type)
id|BUILDSTRING
c_func
(paren
id|b
comma
id|u8
)paren
id|BUILDSTRING
c_func
(paren
id|w
comma
id|u16
)paren
id|BUILDSTRING
c_func
(paren
id|l
comma
id|u32
)paren
id|BUILDSTRING
c_func
(paren
id|q
comma
id|u64
)paren
multiline_comment|/* Depends on MIPS II instruction set */
DECL|macro|mmiowb
mdefine_line|#define mmiowb() asm volatile (&quot;sync&quot; ::: &quot;memory&quot;)
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
multiline_comment|/*&n; * Memory Mapped I/O&n; */
DECL|macro|ioread8
mdefine_line|#define ioread8(addr)&t;&t;readb(addr)
DECL|macro|ioread16
mdefine_line|#define ioread16(addr)&t;&t;readw(addr)
DECL|macro|ioread32
mdefine_line|#define ioread32(addr)&t;&t;readl(addr)
DECL|macro|iowrite8
mdefine_line|#define iowrite8(b,addr)&t;writeb(b,addr)
DECL|macro|iowrite16
mdefine_line|#define iowrite16(w,addr)&t;writew(w,addr)
DECL|macro|iowrite32
mdefine_line|#define iowrite32(l,addr)&t;writel(l,addr)
DECL|macro|ioread8_rep
mdefine_line|#define ioread8_rep(a,b,c)&t;readsb(a,b,c)
DECL|macro|ioread16_rep
mdefine_line|#define ioread16_rep(a,b,c)&t;readsw(a,b,c)
DECL|macro|ioread32_rep
mdefine_line|#define ioread32_rep(a,b,c)&t;readsl(a,b,c)
DECL|macro|iowrite8_rep
mdefine_line|#define iowrite8_rep(a,b,c)&t;writesb(a,b,c)
DECL|macro|iowrite16_rep
mdefine_line|#define iowrite16_rep(a,b,c)&t;writesw(a,b,c)
DECL|macro|iowrite32_rep
mdefine_line|#define iowrite32_rep(a,b,c)&t;writesl(a,b,c)
multiline_comment|/* Create a virtual mapping cookie for an IO port range */
r_extern
r_void
id|__iomem
op_star
id|ioport_map
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|ioport_unmap
c_func
(paren
r_void
id|__iomem
op_star
)paren
suffix:semicolon
multiline_comment|/* Create a virtual mapping cookie for a PCI BAR (memory or IO) */
r_struct
id|pci_dev
suffix:semicolon
r_extern
r_void
id|__iomem
op_star
id|pci_iomap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|bar
comma
r_int
r_int
id|max
)paren
suffix:semicolon
r_extern
r_void
id|pci_iounmap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_void
id|__iomem
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * ISA space is &squot;always mapped&squot; on currently supported MIPS systems, no need&n; * to explicitly ioremap() it. The fact that the ISA IO space is mapped&n; * to PAGE_OFFSET is pure coincidence - it does not mean ISA values&n; * are physical addresses. The following constant pointer can be&n; * used as the IO-area pointer (it can be iounmapped as well, so the&n; * analogy with PCI is quite large):&n; */
DECL|macro|__ISA_IO_base
mdefine_line|#define __ISA_IO_base ((char *)(isa_slot_offset))
DECL|macro|isa_readb
mdefine_line|#define isa_readb(a)&t;&t;readb(__ISA_IO_base + (a))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(a)&t;&t;readw(__ISA_IO_base + (a))
DECL|macro|isa_readl
mdefine_line|#define isa_readl(a)&t;&t;readl(__ISA_IO_base + (a))
DECL|macro|isa_readq
mdefine_line|#define isa_readq(a)&t;&t;readq(__ISA_IO_base + (a))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(b,a)&t;&t;writeb(b,__ISA_IO_base + (a))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(w,a)&t;&t;writew(w,__ISA_IO_base + (a))
DECL|macro|isa_writel
mdefine_line|#define isa_writel(l,a)&t;&t;writel(l,__ISA_IO_base + (a))
DECL|macro|isa_writeq
mdefine_line|#define isa_writeq(q,a)&t;&t;writeq(q,__ISA_IO_base + (a))
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c)&t;memset_io(__ISA_IO_base + (a),(b),(c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c) memcpy_fromio((a),__ISA_IO_base + (b),(c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c)&t;memcpy_toio(__ISA_IO_base + (a),(b),(c))
multiline_comment|/*&n; * We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and&n; * just copy it. The net code will then do the checksum later.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused) memcpy_fromio((skb)-&gt;data,(src),(len))
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(a,b,c,d) eth_copy_and_sum((a),(b),(c),(d))
multiline_comment|/*&n; *     check_signature         -       find BIOS signatures&n; *     @io_addr: mmio address to check&n; *     @signature:  signature block&n; *     @length: length of signature&n; *&n; *     Perform a signature comparison with the mmio address io_addr. This&n; *     address should have been obtained by ioremap.&n; *     Returns 1 on a match.&n; */
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_char
id|__iomem
op_star
id|io_addr
comma
r_const
r_int
r_char
op_star
id|signature
comma
r_int
id|length
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|io_addr
)paren
op_ne
op_star
id|signature
)paren
r_goto
id|out
suffix:semicolon
id|io_addr
op_increment
suffix:semicolon
id|signature
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * The caches on some architectures aren&squot;t dma-coherent and have need to&n; * handle this in software.  There are three types of operations that&n; * can be applied to dma buffers.&n; *&n; *  - dma_cache_wback_inv(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_wback(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_inv(start, size) invalidates the affected parts of the&n; *    caches.  Dirty lines of the caches may be written back or simply&n; *    be discarded.  This operation is necessary before dma operations&n; *    to the memory.&n; */
macro_line|#ifdef CONFIG_DMA_NONCOHERENT
r_extern
r_void
(paren
op_star
id|_dma_cache_wback_inv
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_dma_cache_wback
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_dma_cache_inv
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(start, size)&t;_dma_cache_wback_inv(start,size)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(start, size)&t;&t;_dma_cache_wback(start,size)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(start, size)&t;&t;_dma_cache_inv(start,size)
macro_line|#else /* Sane hardware */
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(start,size)&t;&bslash;&n;&t;do { (void) (start); (void) (size); } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(start,size)&t;&bslash;&n;&t;do { (void) (start); (void) (size); } while (0)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(start,size)&t;&bslash;&n;&t;do { (void) (start); (void) (size); } while (0)
macro_line|#endif /* CONFIG_DMA_NONCOHERENT */
multiline_comment|/*&n; * Read a 32-bit register that requires a 64-bit read cycle on the bus.&n; * Avoid interrupt mucking, just adjust the address for 4-byte access.&n; * Assume the addresses are 8-byte aligned.&n; */
macro_line|#ifdef __MIPSEB__
DECL|macro|__CSR_32_ADJUST
mdefine_line|#define __CSR_32_ADJUST 4
macro_line|#else
DECL|macro|__CSR_32_ADJUST
mdefine_line|#define __CSR_32_ADJUST 0
macro_line|#endif
DECL|macro|csr_out32
mdefine_line|#define csr_out32(v,a) (*(volatile u32 *)((unsigned long)(a) + __CSR_32_ADJUST) = (v))
DECL|macro|csr_in32
mdefine_line|#define csr_in32(a)    (*(volatile u32 *)((unsigned long)(a) + __CSR_32_ADJUST))
macro_line|#endif /* _ASM_IO_H */
eof
