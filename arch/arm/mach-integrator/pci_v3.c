multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/pci_v3.c&n; *&n; *  PCI functions for V3 host PCI bridge&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000-2001 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/hardware/pci_v3.h&gt;
multiline_comment|/*&n; * The V3 PCI interface chip in Integrator provides several windows from&n; * local bus memory into the PCI memory areas.   Unfortunately, there&n; * are not really enough windows for our usage, therefore we reuse &n; * one of the windows for access to PCI configuration space.  The&n; * memory map is as follows:&n; * &n; * Local Bus Memory         Usage&n; * &n; * 40000000 - 4FFFFFFF      PCI memory.  256M non-prefetchable&n; * 50000000 - 5FFFFFFF      PCI memory.  256M prefetchable&n; * 60000000 - 60FFFFFF      PCI IO.  16M&n; * 61000000 - 61FFFFFF      PCI Configuration. 16M&n; * &n; * There are three V3 windows, each described by a pair of V3 registers.&n; * These are LB_BASE0/LB_MAP0, LB_BASE1/LB_MAP1 and LB_BASE2/LB_MAP2.&n; * Base0 and Base1 can be used for any type of PCI memory access.   Base2&n; * can be used either for PCI I/O or for I20 accesses.  By default, uHAL&n; * uses this only for PCI IO space.&n; * &n; * Normally these spaces are mapped using the following base registers:&n; * &n; * Usage Local Bus Memory         Base/Map registers used&n; * &n; * Mem   40000000 - 4FFFFFFF      LB_BASE0/LB_MAP0&n; * Mem   50000000 - 5FFFFFFF      LB_BASE1/LB_MAP1&n; * IO    60000000 - 60FFFFFF      LB_BASE2/LB_MAP2&n; * Cfg   61000000 - 61FFFFFF&n; * &n; * This means that I20 and PCI configuration space accesses will fail.&n; * When PCI configuration accesses are needed (via the uHAL PCI &n; * configuration space primitives) we must remap the spaces as follows:&n; * &n; * Usage Local Bus Memory         Base/Map registers used&n; * &n; * Mem   40000000 - 4FFFFFFF      LB_BASE0/LB_MAP0&n; * Mem   50000000 - 5FFFFFFF      LB_BASE0/LB_MAP0&n; * IO    60000000 - 60FFFFFF      LB_BASE2/LB_MAP2&n; * Cfg   61000000 - 61FFFFFF      LB_BASE1/LB_MAP1&n; * &n; * To make this work, the code depends on overlapping windows working.&n; * The V3 chip translates an address by checking its range within &n; * each of the BASE/MAP pairs in turn (in ascending register number&n; * order).  It will use the first matching pair.   So, for example,&n; * if the same address is mapped by both LB_BASE0/LB_MAP0 and&n; * LB_BASE1/LB_MAP1, the V3 will use the translation from &n; * LB_BASE0/LB_MAP0.&n; * &n; * To allow PCI Configuration space access, the code enlarges the&n; * window mapped by LB_BASE0/LB_MAP0 from 256M to 512M.  This occludes&n; * the windows currently mapped by LB_BASE1/LB_MAP1 so that it can&n; * be remapped for use by configuration cycles.&n; * &n; * At the end of the PCI Configuration space accesses, &n; * LB_BASE1/LB_MAP1 is reset to map PCI Memory.  Finally the window&n; * mapped by LB_BASE0/LB_MAP0 is reduced in size from 512M to 256M to&n; * reveal the now restored LB_BASE1/LB_MAP1 window.&n; * &n; * NOTE: We do not set up I2O mapping.  I suspect that this is only&n; * for an intelligent (target) device.  Using I2O disables most of&n; * the mappings into PCI memory.&n; */
singleline_comment|// V3 access routines
DECL|macro|v3_writeb
mdefine_line|#define v3_writeb(o,v) __raw_writeb(v, PCI_V3_VADDR + (unsigned int)(o))
DECL|macro|v3_readb
mdefine_line|#define v3_readb(o)    (__raw_readb(PCI_V3_VADDR + (unsigned int)(o)))
DECL|macro|v3_writew
mdefine_line|#define v3_writew(o,v) __raw_writew(v, PCI_V3_VADDR + (unsigned int)(o))
DECL|macro|v3_readw
mdefine_line|#define v3_readw(o)    (__raw_readw(PCI_V3_VADDR + (unsigned int)(o)))
DECL|macro|v3_writel
mdefine_line|#define v3_writel(o,v) __raw_writel(v, PCI_V3_VADDR + (unsigned int)(o))
DECL|macro|v3_readl
mdefine_line|#define v3_readl(o)    (__raw_readl(PCI_V3_VADDR + (unsigned int)(o)))
multiline_comment|/*============================================================================&n; *&n; * routine:&t;uHALir_PCIMakeConfigAddress()&n; *&n; * parameters:&t;bus = which bus&n; *              device = which device&n; *              function = which function&n; *&t;&t;offset = configuration space register we are interested in&n; *&n; * description:&t;this routine will generate a platform dependant config&n; *&t;&t;address.&n; *&n; * calls:&t;none&n; *&n; * returns:&t;configuration address to play on the PCI bus&n; *&n; * To generate the appropriate PCI configuration cycles in the PCI &n; * configuration address space, you present the V3 with the following pattern &n; * (which is very nearly a type 1 (except that the lower two bits are 00 and&n; * not 01).   In order for this mapping to work you need to set up one of&n; * the local to PCI aperatures to 16Mbytes in length translating to&n; * PCI configuration space starting at 0x0000.0000.&n; *&n; * PCI configuration cycles look like this:&n; *&n; * Type 0:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | |D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|0|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:11&t;Device select bit.&n; * &t;10:8&t;Function number&n; * &t; 7:2&t;Register number&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; */
DECL|variable|v3_lock
r_static
id|spinlock_t
id|v3_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|PCI_BUS_NONMEM_START
mdefine_line|#define PCI_BUS_NONMEM_START&t;0x00000000
DECL|macro|PCI_BUS_NONMEM_SIZE
mdefine_line|#define PCI_BUS_NONMEM_SIZE&t;SZ_256M
DECL|macro|PCI_BUS_PREMEM_START
mdefine_line|#define PCI_BUS_PREMEM_START&t;PCI_BUS_NONMEM_START + PCI_BUS_NONMEM_SIZE
DECL|macro|PCI_BUS_PREMEM_SIZE
mdefine_line|#define PCI_BUS_PREMEM_SIZE&t;SZ_256M
macro_line|#if PCI_BUS_NONMEM_START &amp; 0x000fffff
macro_line|#error PCI_BUS_NONMEM_START must be megabyte aligned
macro_line|#endif
macro_line|#if PCI_BUS_PREMEM_START &amp; 0x000fffff
macro_line|#error PCI_BUS_PREMEM_START must be megabyte aligned
macro_line|#endif
DECL|macro|V3_LB_BASE_PREFETCH
macro_line|#undef V3_LB_BASE_PREFETCH
DECL|macro|V3_LB_BASE_PREFETCH
mdefine_line|#define V3_LB_BASE_PREFETCH 0
DECL|function|v3_open_config_window
r_static
r_int
r_int
id|v3_open_config_window
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|offset
)paren
(brace
r_int
r_int
id|address
comma
id|mapaddress
comma
id|busnr
suffix:semicolon
id|busnr
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
multiline_comment|/*&n;&t; * Trap out illegal values&n;&t; */
r_if
c_cond
(paren
id|offset
OG
l_int|255
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busnr
OG
l_int|255
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;devfn
OG
l_int|255
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busnr
op_eq
l_int|0
)paren
(brace
r_int
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * local bus segment so need a type 0 config cycle&n;&t;&t; *&n;&t;&t; * build the PCI configuration &quot;address&quot; with one-hot in&n;&t;&t; * A31-A11&n;&t;&t; *&n;&t;&t; * mapaddress:&n;&t;&t; *  3:1 = config cycle (101)&n;&t;&t; *  0   = PCI A1 &amp; A0 are 0 (0)&n;&t;&t; */
id|address
op_assign
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_lshift
l_int|8
suffix:semicolon
id|mapaddress
op_assign
id|V3_LB_MAP_TYPE_CONFIG
suffix:semicolon
r_if
c_cond
(paren
id|slot
OG
l_int|12
)paren
multiline_comment|/*&n;&t;&t;&t; * high order bits are handled by the MAP register&n;&t;&t;&t; */
id|mapaddress
op_or_assign
l_int|1
op_lshift
(paren
id|slot
op_minus
l_int|5
)paren
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t;&t; * low order bits handled directly in the address&n;&t;&t;&t; */
id|address
op_or_assign
l_int|1
op_lshift
(paren
id|slot
op_plus
l_int|11
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * not the local bus segment so need a type 1 config cycle&n;&t;&t; *&n;&t;&t; * address:&n;&t;&t; *  23:16 = bus number&n;&t;&t; *  15:11 = slot number (7:3 of devfn)&n;&t;&t; *  10:8  = func number (2:0 of devfn)&n;&t;&t; *&n;&t;&t; * mapaddress:&n;&t;&t; *  3:1 = config cycle (101)&n;&t;&t; *  0   = PCI A1 &amp; A0 from host bus (1)&n;&t;&t; */
id|mapaddress
op_assign
id|V3_LB_MAP_TYPE_CONFIG
op_or
id|V3_LB_MAP_AD_LOW_EN
suffix:semicolon
id|address
op_assign
(paren
id|busnr
op_lshift
l_int|16
)paren
op_or
(paren
id|dev-&gt;devfn
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set up base0 to see all 512Mbytes of memory space (not&n;&t; * prefetchable), this frees up base1 for re-use by&n;&t; * configuration memory&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE0
comma
id|v3_addr_to_lb_base
c_func
(paren
id|PHYS_PCI_MEM_BASE
)paren
op_or
id|V3_LB_BASE_ADR_SIZE_512MB
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up base1/map1 to point into configuration space.&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE1
comma
id|v3_addr_to_lb_base
c_func
(paren
id|PHYS_PCI_CONFIG_BASE
)paren
op_or
id|V3_LB_BASE_ADR_SIZE_16MB
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_LB_MAP1
comma
id|mapaddress
)paren
suffix:semicolon
r_return
id|PCI_CONFIG_VADDR
op_plus
id|address
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|v3_close_config_window
r_static
r_void
id|v3_close_config_window
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Reassign base1 for use by prefetchable PCI memory&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE1
comma
id|v3_addr_to_lb_base
c_func
(paren
id|PHYS_PCI_MEM_BASE
op_plus
id|SZ_256M
)paren
op_or
id|V3_LB_BASE_ADR_SIZE_256MB
op_or
id|V3_LB_BASE_PREFETCH
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_LB_MAP1
comma
id|v3_addr_to_lb_map
c_func
(paren
id|PCI_BUS_PREMEM_START
)paren
op_or
id|V3_LB_MAP_TYPE_MEM_MULTIPLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * And shrink base0 back to a 256M window (NOTE: MAP0 already correct)&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE0
comma
id|v3_addr_to_lb_base
c_func
(paren
id|PHYS_PCI_MEM_BASE
)paren
op_or
id|V3_LB_BASE_ADR_SIZE_256MB
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
)brace
DECL|function|v3_read_config_byte
r_static
r_int
id|v3_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|val
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|v
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
id|addr
op_assign
id|v3_open_config_window
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|v
op_assign
id|__raw_readb
c_func
(paren
id|addr
)paren
suffix:semicolon
id|v3_close_config_window
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|val
op_assign
id|v
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|v3_read_config_word
r_static
r_int
id|v3_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|val
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|v
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
id|addr
op_assign
id|v3_open_config_window
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|v
op_assign
id|__raw_readw
c_func
(paren
id|addr
)paren
suffix:semicolon
id|v3_close_config_window
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|val
op_assign
id|v
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|v3_read_config_dword
r_static
r_int
id|v3_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|val
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|v
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
id|addr
op_assign
id|v3_open_config_window
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|v
op_assign
id|__raw_readl
c_func
(paren
id|addr
)paren
suffix:semicolon
id|v3_close_config_window
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|val
op_assign
id|v
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|v3_write_config_byte
r_static
r_int
id|v3_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|val
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
id|addr
op_assign
id|v3_open_config_window
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|__raw_readb
c_func
(paren
id|addr
)paren
suffix:semicolon
id|v3_close_config_window
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|v3_write_config_word
r_static
r_int
id|v3_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|val
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
id|addr
op_assign
id|v3_open_config_window
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|__raw_writew
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|__raw_readw
c_func
(paren
id|addr
)paren
suffix:semicolon
id|v3_close_config_window
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|v3_write_config_dword
r_static
r_int
id|v3_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|val
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
id|addr
op_assign
id|v3_open_config_window
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|__raw_readl
c_func
(paren
id|addr
)paren
suffix:semicolon
id|v3_close_config_window
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|pci_v3_ops
r_static
r_struct
id|pci_ops
id|pci_v3_ops
op_assign
(brace
id|read_byte
suffix:colon
id|v3_read_config_byte
comma
id|read_word
suffix:colon
id|v3_read_config_word
comma
id|read_dword
suffix:colon
id|v3_read_config_dword
comma
id|write_byte
suffix:colon
id|v3_write_config_byte
comma
id|write_word
suffix:colon
id|v3_write_config_word
comma
id|write_dword
suffix:colon
id|v3_write_config_dword
comma
)brace
suffix:semicolon
DECL|variable|non_mem
r_static
r_struct
id|resource
id|non_mem
op_assign
(brace
id|name
suffix:colon
l_string|&quot;PCI non-prefetchable&quot;
comma
id|start
suffix:colon
id|PHYS_PCI_MEM_BASE
op_plus
id|PCI_BUS_NONMEM_START
comma
id|end
suffix:colon
id|PHYS_PCI_MEM_BASE
op_plus
id|PCI_BUS_NONMEM_START
op_plus
id|PCI_BUS_NONMEM_SIZE
op_minus
l_int|1
comma
id|flags
suffix:colon
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|pre_mem
r_static
r_struct
id|resource
id|pre_mem
op_assign
(brace
id|name
suffix:colon
l_string|&quot;PCI prefetchable&quot;
comma
id|start
suffix:colon
id|PHYS_PCI_MEM_BASE
op_plus
id|PCI_BUS_PREMEM_START
comma
id|end
suffix:colon
id|PHYS_PCI_MEM_BASE
op_plus
id|PCI_BUS_PREMEM_START
op_plus
id|PCI_BUS_PREMEM_SIZE
op_minus
l_int|1
comma
id|flags
suffix:colon
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
comma
)brace
suffix:semicolon
DECL|function|pci_v3_setup_resources
r_static
r_int
id|__init
id|pci_v3_setup_resources
c_func
(paren
r_struct
id|resource
op_star
op_star
id|resource
)paren
(brace
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|non_mem
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: unable to allocate non-prefetchable &quot;
l_string|&quot;memory region&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|pre_mem
)paren
)paren
(brace
id|release_resource
c_func
(paren
op_amp
id|non_mem
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: unable to allocate prefetchable &quot;
l_string|&quot;memory region&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * bus-&gt;resource[0] is the IO resource for this bus&n;&t; * bus-&gt;resource[1] is the mem resource for this bus&n;&t; * bus-&gt;resource[2] is the prefetch mem resource for this bus&n;&t; */
id|resource
(braket
l_int|0
)braket
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|resource
(braket
l_int|1
)braket
op_assign
op_amp
id|non_mem
suffix:semicolon
singleline_comment|//&t;resource[2] = &amp;pre_mem;
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * These don&squot;t seem to be implemented on the Integrator I have, which&n; * means I can&squot;t get additional information on the reason for the pm2fb&n; * problems.  I suppose I&squot;ll just have to mind-meld with the machine. ;)&n; */
DECL|macro|SC_PCI
mdefine_line|#define SC_PCI     (IO_ADDRESS(INTEGRATOR_SC_BASE) + INTEGRATOR_SC_PCIENABLE_OFFSET)
DECL|macro|SC_LBFADDR
mdefine_line|#define SC_LBFADDR (IO_ADDRESS(INTEGRATOR_SC_BASE) + 0x20)
DECL|macro|SC_LBFCODE
mdefine_line|#define SC_LBFCODE (IO_ADDRESS(INTEGRATOR_SC_BASE) + 0x24)
r_static
r_int
DECL|function|v3_pci_fault
id|v3_pci_fault
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pc
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_int
r_int
id|instr
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|pc
suffix:semicolon
macro_line|#if 0
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;V3 fault: addr 0x%08lx, FSR 0x%03x, PC 0x%08lx [%08lx] LBFADDR=%08x LBFCODE=%02x ISTAT=%02x&bslash;n&quot;
comma
id|addr
comma
id|fsr
comma
id|pc
comma
id|instr
comma
id|__raw_readl
c_func
(paren
id|SC_LBFADDR
)paren
comma
id|__raw_readl
c_func
(paren
id|SC_LBFCODE
)paren
op_amp
l_int|255
comma
id|v3_readb
c_func
(paren
id|V3_LB_ISTAT
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
id|printascii
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#endif
id|v3_writeb
c_func
(paren
id|V3_LB_ISTAT
comma
l_int|0
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|3
comma
id|SC_PCI
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the instruction being executed was a read,&n;&t; * make it look like it read all-ones.&n;&t; */
r_if
c_cond
(paren
(paren
id|instr
op_amp
l_int|0x0c100000
)paren
op_eq
l_int|0x04100000
)paren
(brace
r_int
id|reg
op_assign
(paren
id|instr
op_rshift
l_int|12
)paren
op_amp
l_int|15
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|instr
op_amp
l_int|0x00400000
)paren
id|val
op_assign
l_int|255
suffix:semicolon
r_else
id|val
op_assign
op_minus
l_int|1
suffix:semicolon
id|regs-&gt;uregs
(braket
id|reg
)braket
op_assign
id|val
suffix:semicolon
id|regs-&gt;ARM_pc
op_add_assign
l_int|4
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|instr
op_amp
l_int|0x0e100090
)paren
op_eq
l_int|0x00100090
)paren
(brace
r_int
id|reg
op_assign
(paren
id|instr
op_rshift
l_int|12
)paren
op_amp
l_int|15
suffix:semicolon
id|regs-&gt;uregs
(braket
id|reg
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|regs-&gt;ARM_pc
op_add_assign
l_int|4
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|v3_irq
r_static
r_void
id|v3_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|devid
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef CONFIG_DEBUG_LL
r_int
r_int
id|pc
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_int
r_int
id|instr
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|pc
suffix:semicolon
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;V3 int %d: pc=0x%08lx [%08lx] LBFADDR=%08x LBFCODE=%02x ISTAT=%02x&bslash;n&quot;
comma
id|irq
comma
id|pc
comma
id|instr
comma
id|__raw_readl
c_func
(paren
id|SC_LBFADDR
)paren
comma
id|__raw_readl
c_func
(paren
id|SC_LBFCODE
)paren
op_amp
l_int|255
comma
id|v3_readb
c_func
(paren
id|V3_LB_ISTAT
)paren
)paren
suffix:semicolon
id|printascii
c_func
(paren
id|buf
)paren
suffix:semicolon
macro_line|#endif
id|v3_writew
c_func
(paren
id|V3_PCI_STAT
comma
l_int|0xf000
)paren
suffix:semicolon
id|v3_writeb
c_func
(paren
id|V3_LB_ISTAT
comma
l_int|0
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|3
comma
id|SC_PCI
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_LL
multiline_comment|/*&n;&t; * If the instruction being executed was a read,&n;&t; * make it look like it read all-ones.&n;&t; */
r_if
c_cond
(paren
(paren
id|instr
op_amp
l_int|0x0c100000
)paren
op_eq
l_int|0x04100000
)paren
(brace
r_int
id|reg
op_assign
(paren
id|instr
op_rshift
l_int|16
)paren
op_amp
l_int|15
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;   reg%d = %08lx&bslash;n&quot;
comma
id|reg
comma
id|regs-&gt;uregs
(braket
id|reg
)braket
)paren
suffix:semicolon
id|printascii
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|pci_v3_setup
r_int
id|__init
id|pci_v3_setup
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_eq
l_int|0
)paren
(brace
id|sys-&gt;mem_offset
op_assign
id|PHYS_PCI_MEM_BASE
suffix:semicolon
id|ret
op_assign
id|pci_v3_setup_resources
c_func
(paren
id|sys-&gt;resource
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pci_v3_scan_bus
r_struct
id|pci_bus
op_star
id|pci_v3_scan_bus
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
(brace
r_return
id|pci_scan_bus
c_func
(paren
id|sys-&gt;busnr
comma
op_amp
id|pci_v3_ops
comma
id|sys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * V3_LB_BASE? - local bus address&n; * V3_LB_MAP?  - pci bus address&n; */
DECL|function|pci_v3_preinit
r_void
id|__init
id|pci_v3_preinit
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Hook in our fault handler for PCI errors&n;&t; */
id|hook_fault_code
c_func
(paren
l_int|4
comma
id|v3_pci_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on linefetch&quot;
)paren
suffix:semicolon
id|hook_fault_code
c_func
(paren
l_int|6
comma
id|v3_pci_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on linefetch&quot;
)paren
suffix:semicolon
id|hook_fault_code
c_func
(paren
l_int|8
comma
id|v3_pci_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on non-linefetch&quot;
)paren
suffix:semicolon
id|hook_fault_code
c_func
(paren
l_int|10
comma
id|v3_pci_fault
comma
id|SIGBUS
comma
l_string|&quot;external abort on non-linefetch&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unlock V3 registers, but only if they were previously locked.&n;&t; */
r_if
c_cond
(paren
id|v3_readw
c_func
(paren
id|V3_SYSTEM
)paren
op_amp
id|V3_SYSTEM_M_LOCK
)paren
id|v3_writew
c_func
(paren
id|V3_SYSTEM
comma
l_int|0xa05f
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup window 0 - PCI non-prefetchable memory&n;&t; *  Local: 0x40000000 Bus: 0x00000000 Size: 256MB&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE0
comma
id|v3_addr_to_lb_base
c_func
(paren
id|PHYS_PCI_MEM_BASE
)paren
op_or
id|V3_LB_BASE_ADR_SIZE_256MB
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_LB_MAP0
comma
id|v3_addr_to_lb_map
c_func
(paren
id|PCI_BUS_NONMEM_START
)paren
op_or
id|V3_LB_MAP_TYPE_MEM
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup window 1 - PCI prefetchable memory&n;&t; *  Local: 0x50000000 Bus: 0x10000000 Size: 256MB&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE1
comma
id|v3_addr_to_lb_base
c_func
(paren
id|PHYS_PCI_MEM_BASE
op_plus
id|SZ_256M
)paren
op_or
id|V3_LB_BASE_ADR_SIZE_256MB
op_or
id|V3_LB_BASE_PREFETCH
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_LB_MAP1
comma
id|v3_addr_to_lb_map
c_func
(paren
id|PCI_BUS_PREMEM_START
)paren
op_or
id|V3_LB_MAP_TYPE_MEM_MULTIPLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup window 2 - PCI IO&n;&t; */
id|v3_writel
c_func
(paren
id|V3_LB_BASE2
comma
id|v3_addr_to_lb_base2
c_func
(paren
id|PHYS_PCI_IO_BASE
)paren
op_or
id|V3_LB_BASE_ENABLE
)paren
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_LB_MAP2
comma
id|v3_addr_to_lb_map2
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable PCI to host IO cycles&n;&t; */
id|temp
op_assign
id|v3_readw
c_func
(paren
id|V3_PCI_CFG
)paren
op_amp
op_complement
id|V3_PCI_CFG_M_I2O_EN
suffix:semicolon
id|temp
op_or_assign
id|V3_PCI_CFG_M_IO_REG_DIS
op_or
id|V3_PCI_CFG_M_IO_DIS
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_PCI_CFG
comma
id|temp
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;FIFO_CFG: %04x  FIFO_PRIO: %04x&bslash;n&quot;
comma
id|v3_readw
c_func
(paren
id|V3_FIFO_CFG
)paren
comma
id|v3_readw
c_func
(paren
id|V3_FIFO_PRIORITY
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the V3 FIFO such that writes have higher priority than&n;&t; * reads, and local bus write causes local bus read fifo flush.&n;&t; * Same for PCI.&n;&t; */
id|v3_writew
c_func
(paren
id|V3_FIFO_PRIORITY
comma
l_int|0x0a0a
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Re-lock the system register.&n;&t; */
id|temp
op_assign
id|v3_readw
c_func
(paren
id|V3_SYSTEM
)paren
op_or
id|V3_SYSTEM_M_LOCK
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_SYSTEM
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear any error conditions, and enable write errors.&n;&t; */
id|v3_writeb
c_func
(paren
id|V3_LB_ISTAT
comma
l_int|0
)paren
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_LB_CFG
comma
id|v3_readw
c_func
(paren
id|V3_LB_CFG
)paren
op_or
(paren
l_int|1
op_lshift
l_int|10
)paren
)paren
suffix:semicolon
id|v3_writeb
c_func
(paren
id|V3_LB_IMASK
comma
l_int|0x28
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|3
comma
id|SC_PCI
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Grab the PCI error interrupt.&n;&t; */
id|ret
op_assign
id|request_irq
c_func
(paren
id|IRQ_V3INT
comma
id|v3_irq
comma
l_int|0
comma
l_string|&quot;V3&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: unable to grab PCI error &quot;
l_string|&quot;interrupt: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|v3_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pci_v3_postinit
r_void
id|__init
id|pci_v3_postinit
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pci_cmd
suffix:semicolon
id|pci_cmd
op_assign
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_INVALIDATE
suffix:semicolon
id|v3_writew
c_func
(paren
id|V3_PCI_CMD
comma
id|pci_cmd
)paren
suffix:semicolon
id|v3_writeb
c_func
(paren
id|V3_LB_ISTAT
comma
op_complement
l_int|0x40
)paren
suffix:semicolon
id|v3_writeb
c_func
(paren
id|V3_LB_IMASK
comma
l_int|0x68
)paren
suffix:semicolon
macro_line|#if 0
id|ret
op_assign
id|request_irq
c_func
(paren
id|IRQ_LBUSTIMEOUT
comma
id|lb_timeout
comma
l_int|0
comma
l_string|&quot;bus timeout&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: unable to grab local bus timeout &quot;
l_string|&quot;interrupt: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
