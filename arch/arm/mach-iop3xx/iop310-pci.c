multiline_comment|/*&n; * arch/arm/mach-iop3xx/iop310-pci.c&n; *&n; * PCI support for the Intel IOP310 chipset&n; *&n; * Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright (C) 2001 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/arch/iop310.h&gt;
multiline_comment|/*&n; *    *** Special note - why the IOP310 should NOT be used ***&n; *&n; * The PCI ATU is a brain dead implementation, only allowing 32-bit&n; * accesses to PCI configuration space.  This is especially brain&n; * dead for writes to this space.  A simple for-instance:&n; *&n; *  You want to modify the command register *without* corrupting the&n; *  status register.&n; *&n; *  To perform this, you need to read *32* bits of data from offset 4,&n; *  mask off the low 16, replace them with the new data, and write *32*&n; *  bits back.&n; *&n; *  Writing the status register at offset 6 with status bits set *clears*&n; *  the status.&n; *&n; * Hello?  Could we have a *SANE* implementation of a PCI ATU some day&n; * *PLEASE*?&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define  DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define  DBG(x...) do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * Calculate the address, etc from the bus, devfn and register&n; * offset.  Note that we have two root buses, so we need some&n; * method to determine whether we need config type 0 or 1 cycles.&n; * We use a root bus number in our bus-&gt;sysdata structure for this.&n; */
DECL|function|iop310_cfg_address
r_static
id|u32
id|iop310_cfg_address
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
comma
r_int
id|where
)paren
(brace
r_struct
id|pci_sys_data
op_star
id|sys
op_assign
id|bus-&gt;sysdata
suffix:semicolon
id|u32
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|sys-&gt;busnr
op_eq
id|bus-&gt;number
)paren
id|addr
op_assign
l_int|1
op_lshift
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_plus
l_int|16
)paren
suffix:semicolon
r_else
id|addr
op_assign
id|bus-&gt;number
op_lshift
l_int|16
op_or
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_lshift
l_int|11
op_or
l_int|1
suffix:semicolon
id|addr
op_or_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
op_lshift
l_int|8
op_or
(paren
id|where
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Primary PCI interface support.&n; */
DECL|function|iop310_pri_pci_status
r_static
r_int
id|iop310_pri_pci_status
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
op_star
id|IOP310_PATUSR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0xf900
)paren
(brace
op_star
id|IOP310_PATUSR
op_assign
id|status
op_amp
l_int|0xf900
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|status
op_assign
op_star
id|IOP310_PATUISR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0000018f
)paren
(brace
op_star
id|IOP310_PATUISR
op_assign
id|status
op_amp
l_int|0x0000018f
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|status
op_assign
op_star
id|IOP310_PSR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0xf900
)paren
(brace
op_star
id|IOP310_PSR
op_assign
id|status
op_amp
l_int|0xf900
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|status
op_assign
op_star
id|IOP310_PBISR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x003f
)paren
(brace
op_star
id|IOP310_PBISR
op_assign
id|status
op_amp
l_int|0x003f
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Simply write the address register and read the configuration&n; * data.  Note that the 4 nop&squot;s ensure that we are able to handle&n; * a delayed abort (in theory.)&n; */
DECL|function|iop310_pri_read
r_static
r_inline
id|u32
id|iop310_pri_read
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;str&t;%1, [%2]&bslash;n&bslash;t&quot;
l_string|&quot;ldr&t;%0, [%3]&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_POCCAR
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_POCCDR
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_int
DECL|function|iop310_pri_read_config
id|iop310_pri_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|iop310_cfg_address
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|u32
id|val
op_assign
id|iop310_pri_read
c_func
(paren
id|addr
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iop310_pri_pci_status
c_func
(paren
)paren
)paren
id|val
op_assign
l_int|0xffffffff
suffix:semicolon
op_star
id|value
op_assign
id|val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|iop310_pri_write_config
id|iop310_pri_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|iop310_cfg_address
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
l_int|4
)paren
(brace
id|val
op_assign
id|iop310_pri_read
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iop310_pri_pci_status
c_func
(paren
)paren
op_eq
l_int|0
)paren
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
id|where
op_assign
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
id|val
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|where
)paren
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
(paren
l_int|0xffff
op_lshift
id|where
)paren
suffix:semicolon
op_star
id|IOP310_POCCDR
op_assign
id|val
op_or
id|value
op_lshift
id|where
suffix:semicolon
)brace
r_else
(brace
id|asm
r_volatile
(paren
l_string|&quot;str&t;%1, [%2]&bslash;n&bslash;t&quot;
l_string|&quot;str&t;%0, [%3]&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_POCCAR
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_POCCDR
)paren
)paren
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|iop310_primary_ops
r_static
r_struct
id|pci_ops
id|iop310_primary_ops
op_assign
(brace
dot
id|read
op_assign
id|iop310_pri_read_config
comma
dot
id|write
op_assign
id|iop310_pri_write_config
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Secondary PCI interface support.&n; */
DECL|function|iop310_sec_pci_status
r_static
r_int
id|iop310_sec_pci_status
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|usr
comma
id|uisr
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|usr
op_assign
op_star
id|IOP310_SATUSR
suffix:semicolon
id|uisr
op_assign
op_star
id|IOP310_SATUISR
suffix:semicolon
r_if
c_cond
(paren
id|usr
op_amp
l_int|0xf900
)paren
(brace
op_star
id|IOP310_SATUSR
op_assign
id|usr
op_amp
l_int|0xf900
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uisr
op_amp
l_int|0x0000069f
)paren
(brace
op_star
id|IOP310_SATUISR
op_assign
id|uisr
op_amp
l_int|0x0000069f
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
id|DBG
c_func
(paren
l_string|&quot;ERROR (%08x %08x)&quot;
comma
id|usr
comma
id|uisr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Simply write the address register and read the configuration&n; * data.  Note that the 4 nop&squot;s ensure that we are able to handle&n; * a delayed abort (in theory.)&n; */
DECL|function|iop310_sec_read
r_static
r_inline
id|u32
id|iop310_sec_read
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;str&t;%1, [%2]&bslash;n&bslash;t&quot;
l_string|&quot;ldr&t;%0, [%3]&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_SOCCAR
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_SOCCDR
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_int
DECL|function|iop310_sec_read_config
id|iop310_sec_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|iop310_cfg_address
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|u32
id|val
op_assign
id|iop310_sec_read
c_func
(paren
id|addr
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iop310_sec_pci_status
c_func
(paren
)paren
)paren
id|val
op_assign
l_int|0xffffffff
suffix:semicolon
op_star
id|value
op_assign
id|val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|iop310_sec_write_config
id|iop310_sec_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|addr
op_assign
id|iop310_cfg_address
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
l_int|4
)paren
(brace
id|val
op_assign
id|iop310_sec_read
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iop310_sec_pci_status
c_func
(paren
)paren
op_eq
l_int|0
)paren
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
id|where
op_assign
(paren
id|where
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
id|val
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|where
)paren
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
(paren
l_int|0xffff
op_lshift
id|where
)paren
suffix:semicolon
op_star
id|IOP310_SOCCDR
op_assign
id|val
op_or
id|value
op_lshift
id|where
suffix:semicolon
)brace
r_else
(brace
id|asm
r_volatile
(paren
l_string|&quot;str&t;%1, [%2]&bslash;n&bslash;t&quot;
l_string|&quot;str&t;%0, [%3]&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_SOCCAR
)paren
comma
l_string|&quot;r&quot;
(paren
id|IOP310_SOCCDR
)paren
)paren
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|iop310_secondary_ops
r_static
r_struct
id|pci_ops
id|iop310_secondary_ops
op_assign
(brace
dot
id|read
op_assign
id|iop310_sec_read_config
comma
dot
id|write
op_assign
id|iop310_sec_write_config
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * When a PCI device does not exist during config cycles, the 80200 gets&n; * an external abort instead of returning 0xffffffff.  If it was an&n; * imprecise abort, we need to correct the return address to point after&n; * the instruction.  Also note that the Xscale manual says:&n; *&n; *  &quot;if a stall-until-complete LD or ST instruction triggers an&n; *  imprecise fault, then that fault will be seen by the program&n; *  within 3 instructions.&quot;&n; *&n; * This does not appear to be the case.  With 8 NOPs after the load, we&n; * see the imprecise abort occurring on the STM of iop310_sec_pci_status()&n; * which is about 10 instructions away.&n; *&n; * Always trust reality!&n; */
r_static
r_int
DECL|function|iop310_pci_abort
id|iop310_pci_abort
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
id|DBG
c_func
(paren
l_string|&quot;PCI abort: address = 0x%08lx fsr = 0x%03x PC = 0x%08lx LR = 0x%08lx&bslash;n&quot;
comma
id|addr
comma
id|fsr
comma
id|regs-&gt;ARM_pc
comma
id|regs-&gt;ARM_lr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If it was an imprecise abort, then we need to correct the&n;&t; * return address to be _after_ the instruction.&n;&t; */
r_if
c_cond
(paren
id|fsr
op_amp
(paren
l_int|1
op_lshift
l_int|10
)paren
)paren
id|regs-&gt;ARM_pc
op_add_assign
l_int|4
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Scan an IOP310 PCI bus.  sys-&gt;bus defines which bus we scan.&n; */
DECL|function|iop310_scan_bus
r_struct
id|pci_bus
op_star
id|iop310_scan_bus
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
r_struct
id|pci_ops
op_star
id|ops
suffix:semicolon
r_if
c_cond
(paren
id|nr
)paren
id|ops
op_assign
op_amp
id|iop310_secondary_ops
suffix:semicolon
r_else
id|ops
op_assign
op_amp
id|iop310_primary_ops
suffix:semicolon
r_return
id|pci_scan_bus
c_func
(paren
id|sys-&gt;busnr
comma
id|ops
comma
id|sys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup the system data for controller &squot;nr&squot;.   Return 0 if none found,&n; * 1 if found, or negative error.&n; *&n; * We can alter:&n; *  io_offset   - offset between IO resources and PCI bus BARs&n; *  mem_offset  - offset between mem resources and PCI bus BARs&n; *  resource[0] - parent IO resource&n; *  resource[1] - parent non-prefetchable memory resource&n; *  resource[2] - parent prefetchable memory resource&n; *  swizzle     - bridge swizzling function&n; *  map_irq     - irq mapping function&n; *&n; * Note that &squot;io_offset&squot; and &squot;mem_offset&squot; are left as zero since&n; * the IOP310 doesn&squot;t attempt to perform any address translation&n; * on accesses from the host to the bus.&n; */
DECL|function|iop310_setup
r_int
id|iop310_setup
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
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
l_int|2
)paren
r_return
l_int|0
suffix:semicolon
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
op_star
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|panic
c_func
(paren
l_string|&quot;PCI: unable to alloc resources&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|resource
)paren
op_star
l_int|2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr
)paren
(brace
r_case
l_int|0
suffix:colon
id|res
(braket
l_int|0
)braket
dot
id|start
op_assign
id|IOP310_PCIPRI_LOWER_IO
op_plus
l_int|0x6e000000
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|end
op_assign
id|IOP310_PCIPRI_LOWER_IO
op_plus
l_int|0x6e00ffff
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;PCI IO Primary&quot;
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|start
op_assign
id|IOP310_PCIPRI_LOWER_MEM
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|end
op_assign
id|IOP310_PCIPRI_LOWER_MEM
op_plus
id|IOP310_PCI_WINDOW_SIZE
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|name
op_assign
l_string|&quot;PCI Memory Primary&quot;
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|res
(braket
l_int|0
)braket
dot
id|start
op_assign
id|IOP310_PCISEC_LOWER_IO
op_plus
l_int|0x6e000000
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|end
op_assign
id|IOP310_PCISEC_LOWER_IO
op_plus
l_int|0x6e00ffff
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;PCI IO Secondary&quot;
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|start
op_assign
id|IOP310_PCISEC_LOWER_MEM
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|end
op_assign
id|IOP310_PCISEC_LOWER_MEM
op_plus
id|IOP310_PCI_WINDOW_SIZE
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|name
op_assign
l_string|&quot;PCI Memory Secondary&quot;
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|res
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|res
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|0
)braket
op_assign
op_amp
id|res
(braket
l_int|0
)braket
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|res
(braket
l_int|1
)braket
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|sys-&gt;io_offset
op_assign
l_int|0x6e000000
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|iop310_init
r_void
id|iop310_init
c_func
(paren
r_void
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI:  Intel 80312 PCI-to-PCI init code.&bslash;n&quot;
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  ATU secondary: ATUCR =0x%08x&bslash;n&quot;
comma
op_star
id|IOP310_ATUCR
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  ATU secondary: SOMWVR=0x%08x  SOIOWVR=0x%08x&bslash;n&quot;
comma
op_star
id|IOP310_SOMWVR
comma
op_star
id|IOP310_SOIOWVR
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  ATU secondary: SIABAR=0x%08x  SIALR  =0x%08x SIATVR=%08x&bslash;n&quot;
comma
op_star
id|IOP310_SIABAR
comma
op_star
id|IOP310_SIALR
comma
op_star
id|IOP310_SIATVR
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  ATU primary:   POMWVR=0x%08x  POIOWVR=0x%08x&bslash;n&quot;
comma
op_star
id|IOP310_POMWVR
comma
op_star
id|IOP310_POIOWVR
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  ATU primary:   PIABAR=0x%08x  PIALR  =0x%08x PIATVR=%08x&bslash;n&quot;
comma
op_star
id|IOP310_PIABAR
comma
op_star
id|IOP310_PIALR
comma
op_star
id|IOP310_PIATVR
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  P2P: PCR=0x%04x BCR=0x%04x EBCR=0x%04x&bslash;n&quot;
comma
op_star
id|IOP310_PCR
comma
op_star
id|IOP310_BCR
comma
op_star
id|IOP310_EBCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Windows have to be carefully opened via a nice set of calls&n;&t; * here or just some direct register fiddling in the board&n;&t; * specific init when we want transactions to occur between the&n;&t; * two PCI hoses.&n;&t; *&n;&t; * To do this, we will have manage RETRY assertion between the&n;&t; * firmware and the kernel.  This will ensure that the host&n;&t; * system&squot;s enumeration code is held off until we have tweaked&n;&t; * the interrupt routing and public/private IDSELs.&n;&t; *&n;&t; * For now we will simply default to disabling the integrated type&n;&t; * 81 P2P bridge.&n;&t; */
op_star
id|IOP310_PCR
op_and_assign
l_int|0xfff8
suffix:semicolon
id|hook_fault_code
c_func
(paren
l_int|16
op_plus
l_int|6
comma
id|iop310_pci_abort
comma
id|SIGBUS
comma
l_string|&quot;imprecise external abort&quot;
)paren
suffix:semicolon
)brace
eof
