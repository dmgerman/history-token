multiline_comment|/*&n; * arch/v850/kernel/mb_a_pci.c -- PCI support for Midas lab RTE-MOTHER-A board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* __nomods_init is like __devinit, but is a no-op when modules are enabled.&n;   This is used by some routines that can be called either during boot&n;   or by a module.  */
macro_line|#ifdef CONFIG_MODULES
DECL|macro|__nomods_init
mdefine_line|#define __nomods_init /*nothing*/
macro_line|#else
DECL|macro|__nomods_init
mdefine_line|#define __nomods_init __devinit
macro_line|#endif
multiline_comment|/* PCI devices on the Mother-A board can only do DMA to/from the MB SRAM&n;   (the RTE-V850E/MA1-CB cpu board doesn&squot;t support PCI access to&n;   CPU-board memory), and since linux DMA buffers are allocated in&n;   normal kernel memory, we basically have to copy DMA blocks around&n;   (this is like a `bounce buffer&squot;).  When a DMA block is `mapped&squot;, we&n;   allocate an identically sized block in MB SRAM, and if we&squot;re doing&n;   output to the device, copy the CPU-memory block to the MB-SRAM block.&n;   When an active block is `unmapped&squot;, we will copy the block back to&n;   CPU memory if necessary, and then deallocate the MB SRAM block.&n;   Ack.  */
multiline_comment|/* Where the motherboard SRAM is in the PCI-bus address space (the&n;   first 512K of it is also mapped at PCI address 0).  */
DECL|macro|PCI_MB_SRAM_ADDR
mdefine_line|#define PCI_MB_SRAM_ADDR 0x800000
multiline_comment|/* Convert CPU-view MB SRAM address to/from PCI-view addresses of the&n;   same memory.  */
DECL|macro|MB_SRAM_TO_PCI
mdefine_line|#define MB_SRAM_TO_PCI(mb_sram_addr) &bslash;&n;   ((dma_addr_t)mb_sram_addr - MB_A_SRAM_ADDR + PCI_MB_SRAM_ADDR)
DECL|macro|PCI_TO_MB_SRAM
mdefine_line|#define PCI_TO_MB_SRAM(pci_addr)     &bslash;&n;   (void *)(pci_addr - PCI_MB_SRAM_ADDR + MB_A_SRAM_ADDR)
r_static
r_void
id|pcibios_assign_resources
(paren
r_void
)paren
suffix:semicolon
DECL|struct|mb_pci_dev_irq
r_struct
id|mb_pci_dev_irq
(brace
DECL|member|dev
r_int
id|dev
suffix:semicolon
multiline_comment|/* PCI device number */
DECL|member|irq_base
r_int
id|irq_base
suffix:semicolon
multiline_comment|/* First IRQ  */
DECL|member|query_pin
r_int
id|query_pin
suffix:semicolon
multiline_comment|/* True if we should read the device&squot;s&n;&t;&t;&t;&t;   Interrupt Pin info, and allocate&n;&t;&t;&t;&t;   interrupt IRQ_BASE + PIN.  */
)brace
suffix:semicolon
multiline_comment|/* PCI interrupts are mapped statically to GBUS interrupts.  */
DECL|variable|mb_pci_dev_irqs
r_static
r_struct
id|mb_pci_dev_irq
id|mb_pci_dev_irqs
(braket
)braket
op_assign
(brace
multiline_comment|/* Motherboard SB82558 ethernet controller */
(brace
l_int|10
comma
id|IRQ_MB_A_LAN
comma
l_int|0
)brace
comma
multiline_comment|/* PCI slot 1 */
(brace
l_int|8
comma
id|IRQ_MB_A_PCI1
c_func
(paren
l_int|0
)paren
comma
l_int|1
)brace
comma
multiline_comment|/* PCI slot 2 */
(brace
l_int|9
comma
id|IRQ_MB_A_PCI2
c_func
(paren
l_int|0
)paren
comma
l_int|1
)brace
)brace
suffix:semicolon
DECL|macro|NUM_MB_PCI_DEV_IRQS
mdefine_line|#define NUM_MB_PCI_DEV_IRQS &bslash;&n;  (sizeof mb_pci_dev_irqs / sizeof mb_pci_dev_irqs[0])
"&f;"
multiline_comment|/* PCI configuration primitives.  */
DECL|macro|CONFIG_DMCFGA
mdefine_line|#define CONFIG_DMCFGA(bus, devfn, offs)&t;&t;&t;&t;&t;&bslash;&n;   (0x80000000&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    | ((offs) &amp; ~0x3)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    | ((devfn) &lt;&lt; 8)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    | ((bus)-&gt;number &lt;&lt; 16))
r_static
r_int
DECL|function|mb_pci_read
id|mb_pci_read
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
id|offs
comma
r_int
id|size
comma
id|u32
op_star
id|rval
)paren
(brace
id|u32
id|addr
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
id|MB_A_PCI_PCICR
op_assign
l_int|0x7
suffix:semicolon
id|MB_A_PCI_DMCFGA
op_assign
id|CONFIG_DMCFGA
(paren
id|bus
comma
id|devfn
comma
id|offs
)paren
suffix:semicolon
id|addr
op_assign
id|MB_A_PCI_IO_ADDR
op_plus
(paren
id|offs
op_amp
l_int|0x3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|rval
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|addr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|rval
op_assign
op_star
(paren
r_volatile
id|u16
op_star
)paren
id|addr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|rval
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|addr
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MB_A_PCI_PCISR
op_amp
l_int|0x2000
)paren
(brace
id|MB_A_PCI_PCISR
op_assign
l_int|0x2000
suffix:semicolon
op_star
id|rval
op_assign
op_complement
l_int|0
suffix:semicolon
)brace
id|MB_A_PCI_DMCFGA
op_assign
l_int|0
suffix:semicolon
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|mb_pci_write
id|mb_pci_write
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
id|offs
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
id|u32
id|addr
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
id|MB_A_PCI_PCICR
op_assign
l_int|0x7
suffix:semicolon
id|MB_A_PCI_DMCFGA
op_assign
id|CONFIG_DMCFGA
(paren
id|bus
comma
id|devfn
comma
id|offs
)paren
suffix:semicolon
id|addr
op_assign
id|MB_A_PCI_IO_ADDR
op_plus
(paren
id|offs
op_amp
l_int|0x3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
(paren
r_volatile
id|u16
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|MB_A_PCI_PCISR
op_amp
l_int|0x2000
)paren
id|MB_A_PCI_PCISR
op_assign
l_int|0x2000
suffix:semicolon
id|MB_A_PCI_DMCFGA
op_assign
l_int|0
suffix:semicolon
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|mb_pci_config_ops
r_static
r_struct
id|pci_ops
id|mb_pci_config_ops
op_assign
(brace
dot
id|read
op_assign
id|mb_pci_read
comma
dot
id|write
op_assign
id|mb_pci_write
comma
)brace
suffix:semicolon
"&f;"
multiline_comment|/* PCI Initialization.  */
DECL|variable|mb_pci_bus
r_static
r_struct
id|pci_bus
op_star
id|mb_pci_bus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do initial PCI setup.  */
DECL|function|pcibios_init
r_static
r_int
id|__devinit
id|pcibios_init
(paren
r_void
)paren
(brace
id|u32
id|id
op_assign
id|MB_A_PCI_PCIHIDR
suffix:semicolon
id|u16
id|vendor
op_assign
id|id
op_amp
l_int|0xFFFF
suffix:semicolon
id|u16
id|device
op_assign
(paren
id|id
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_eq
id|PCI_VENDOR_ID_PLX
op_logical_and
id|device
op_eq
id|PCI_DEVICE_ID_PLX_9080
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;PCI: PLX Technology PCI9080 HOST/PCI bridge&bslash;n&quot;
)paren
suffix:semicolon
id|MB_A_PCI_PCICR
op_assign
l_int|0x147
suffix:semicolon
id|MB_A_PCI_PCIBAR0
op_assign
l_int|0x007FFF00
suffix:semicolon
id|MB_A_PCI_PCIBAR1
op_assign
l_int|0x0000FF00
suffix:semicolon
id|MB_A_PCI_PCIBAR2
op_assign
l_int|0x00800000
suffix:semicolon
id|MB_A_PCI_PCILTR
op_assign
l_int|0x20
suffix:semicolon
id|MB_A_PCI_PCIPBAM
op_or_assign
l_int|0x3
suffix:semicolon
id|MB_A_PCI_PCISR
op_assign
op_complement
l_int|0
suffix:semicolon
multiline_comment|/* Clear errors.  */
multiline_comment|/* Reprogram the motherboard&squot;s IO/config address space,&n;&t;&t;   as we don&squot;t support the GCS7 address space that the&n;&t;&t;   default uses.  */
multiline_comment|/* Significant address bits used for decoding PCI GCS5 space&n;&t;&t;   accessess.  */
id|MB_A_PCI_DMRR
op_assign
op_complement
(paren
id|MB_A_PCI_MEM_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* I don&squot;t understand this, but the SolutionGear example code&n;&t;&t;   uses such an offset, and it doesn&squot;t work without it.  XXX */
macro_line|#if GCS5_SIZE == 0x00800000
DECL|macro|GCS5_CFG_OFFS
mdefine_line|#define GCS5_CFG_OFFS 0x00800000
macro_line|#else
mdefine_line|#define GCS5_CFG_OFFS 0
macro_line|#endif
multiline_comment|/* Address bit values for matching.  Note that we have to give&n;&t;&t;   the address from the motherboard&squot;s point of view, which is&n;&t;&t;   different than the CPU&squot;s.  */
multiline_comment|/* PCI memory space.  */
id|MB_A_PCI_DMLBAM
op_assign
id|GCS5_CFG_OFFS
op_plus
l_int|0x0
suffix:semicolon
multiline_comment|/* PCI I/O space.  */
id|MB_A_PCI_DMLBAI
op_assign
id|GCS5_CFG_OFFS
op_plus
(paren
id|MB_A_PCI_IO_ADDR
op_minus
id|GCS5_ADDR
)paren
suffix:semicolon
id|mb_pci_bus
op_assign
id|pci_scan_bus
(paren
l_int|0
comma
op_amp
id|mb_pci_config_ops
comma
l_int|0
)paren
suffix:semicolon
id|pcibios_assign_resources
(paren
)paren
suffix:semicolon
)brace
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;PCI: HOST/PCI bridge not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
(paren
id|pcibios_init
)paren
suffix:semicolon
DECL|function|pcibios_setup
r_char
id|__devinit
op_star
id|pcibios_setup
(paren
r_char
op_star
id|option
)paren
(brace
multiline_comment|/* Don&squot;t handle any options. */
r_return
id|option
suffix:semicolon
)brace
"&f;"
DECL|function|pcibios_enable_device
r_int
id|__nomods_init
id|pcibios_enable_device
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
id|u16
id|cmd
comma
id|old_cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|old_cmd
op_assign
id|cmd
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Device %s not available because &quot;
l_string|&quot;of resource collisions&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_ne
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|old_cmd
comma
id|cmd
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Resource allocation.  */
DECL|function|pcibios_assign_resources
r_static
r_void
id|__devinit
id|pcibios_assign_resources
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|di_num
suffix:semicolon
r_int
r_class
op_assign
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
r_class
op_logical_and
r_class
op_ne
id|PCI_CLASS_BRIDGE_HOST
)paren
(brace
r_int
id|r_num
suffix:semicolon
r_for
c_loop
(paren
id|r_num
op_assign
l_int|0
suffix:semicolon
id|r_num
OL
l_int|6
suffix:semicolon
id|r_num
op_increment
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|r_num
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
id|pci_assign_resource
(paren
id|dev
comma
id|r_num
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Assign interrupts.  */
r_for
c_loop
(paren
id|di_num
op_assign
l_int|0
suffix:semicolon
id|di_num
OL
id|NUM_MB_PCI_DEV_IRQS
suffix:semicolon
id|di_num
op_increment
)paren
(brace
r_struct
id|mb_pci_dev_irq
op_star
id|di
op_assign
op_amp
id|mb_pci_dev_irqs
(braket
id|di_num
)braket
suffix:semicolon
r_if
c_cond
(paren
id|di-&gt;dev
op_eq
id|PCI_SLOT
(paren
id|dev-&gt;devfn
)paren
)paren
(brace
r_int
id|irq
op_assign
id|di-&gt;irq_base
suffix:semicolon
r_if
c_cond
(paren
id|di-&gt;query_pin
)paren
(brace
multiline_comment|/* Find out which interrupt pin&n;&t;&t;&t;&t;&t;   this device uses (each PCI&n;&t;&t;&t;&t;&t;   slot has 4).  */
id|u8
id|irq_pin
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|irq_pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_pin
op_eq
l_int|0
)paren
multiline_comment|/* Doesn&squot;t use interrupts.  */
r_continue
suffix:semicolon
r_else
id|irq
op_add_assign
id|irq_pin
op_minus
l_int|1
suffix:semicolon
)brace
id|pcibios_update_irq
(paren
id|dev
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pcibios_update_irq
r_void
id|__devinit
id|pcibios_update_irq
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
)paren
(brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|pci_write_config_byte
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
)brace
r_void
id|__devinit
DECL|function|pcibios_resource_to_bus
id|pcibios_resource_to_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus_region
op_star
id|region
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|offset
op_assign
id|MB_A_PCI_IO_ADDR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
id|offset
op_assign
id|MB_A_PCI_MEM_ADDR
suffix:semicolon
)brace
id|region-&gt;start
op_assign
id|res-&gt;start
op_minus
id|offset
suffix:semicolon
id|region-&gt;end
op_assign
id|res-&gt;end
op_minus
id|offset
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Stubs for things we don&squot;t use.  */
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* Called after each bus is probed, but before its children are examined. */
DECL|function|pcibios_fixup_bus
r_void
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
)brace
r_void
DECL|function|pcibios_align_resource
id|pcibios_align_resource
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
)brace
DECL|function|pcibios_set_master
r_void
id|pcibios_set_master
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
"&f;"
multiline_comment|/* Mother-A SRAM memory allocation.  This is a simple first-fit allocator.  */
multiline_comment|/* A memory free-list node.  */
DECL|struct|mb_sram_free_area
r_struct
id|mb_sram_free_area
(brace
DECL|member|mem
r_void
op_star
id|mem
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|next
r_struct
id|mb_sram_free_area
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The tail of the free-list, which starts out containing all the SRAM.  */
DECL|variable|mb_sram_free_tail
r_static
r_struct
id|mb_sram_free_area
id|mb_sram_free_tail
op_assign
(brace
(paren
r_void
op_star
)paren
id|MB_A_SRAM_ADDR
comma
id|MB_A_SRAM_SIZE
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* The free-list.  */
DECL|variable|mb_sram_free_areas
r_static
r_struct
id|mb_sram_free_area
op_star
id|mb_sram_free_areas
op_assign
op_amp
id|mb_sram_free_tail
suffix:semicolon
multiline_comment|/* The free-list of free free-list nodes. (:-)  */
DECL|variable|mb_sram_free_free_areas
r_static
r_struct
id|mb_sram_free_area
op_star
id|mb_sram_free_free_areas
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Spinlock protecting the above globals.  */
DECL|variable|mb_sram_lock
r_static
id|spinlock_t
id|mb_sram_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Allocate a memory block at least SIZE bytes long in the Mother-A SRAM&n;   space.  */
DECL|function|alloc_mb_sram
r_static
r_void
op_star
id|alloc_mb_sram
(paren
r_int
id|size
)paren
(brace
r_struct
id|mb_sram_free_area
op_star
id|prev
comma
op_star
id|fa
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_void
op_star
id|mem
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
(paren
id|mb_sram_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Look for a free area that can contain SIZE bytes.  */
r_for
c_loop
(paren
id|prev
op_assign
l_int|0
comma
id|fa
op_assign
id|mb_sram_free_areas
suffix:semicolon
id|fa
suffix:semicolon
id|prev
op_assign
id|fa
comma
id|fa
op_assign
id|fa-&gt;next
)paren
r_if
c_cond
(paren
id|fa-&gt;size
op_ge
id|size
)paren
(brace
multiline_comment|/* Found one!  */
id|mem
op_assign
id|fa-&gt;mem
suffix:semicolon
r_if
c_cond
(paren
id|fa-&gt;size
op_eq
id|size
)paren
(brace
multiline_comment|/* In fact, it fits exactly, so remove&n;&t;&t;&t;&t;   this node from the free-list.  */
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|fa-&gt;next
suffix:semicolon
r_else
id|mb_sram_free_areas
op_assign
id|fa-&gt;next
suffix:semicolon
multiline_comment|/* Put it on the free-list-entry-free-list. */
id|fa-&gt;next
op_assign
id|mb_sram_free_free_areas
suffix:semicolon
id|mb_sram_free_free_areas
op_assign
id|fa
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* FA is bigger than SIZE, so just&n;&t;&t;&t;&t;   reduce its size to account for this&n;&t;&t;&t;&t;   allocation.  */
id|fa-&gt;mem
op_add_assign
id|size
suffix:semicolon
id|fa-&gt;size
op_sub_assign
id|size
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
id|mb_sram_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mem
suffix:semicolon
)brace
multiline_comment|/* Return the memory area MEM of size SIZE to the MB SRAM free pool.  */
DECL|function|free_mb_sram
r_static
r_void
id|free_mb_sram
(paren
r_void
op_star
id|mem
comma
r_int
id|size
)paren
(brace
r_struct
id|mb_sram_free_area
op_star
id|prev
comma
op_star
id|fa
comma
op_star
id|new_fa
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_void
op_star
id|end
op_assign
id|mem
op_plus
id|size
suffix:semicolon
id|spin_lock_irqsave
(paren
id|mb_sram_lock
comma
id|flags
)paren
suffix:semicolon
id|retry
suffix:colon
multiline_comment|/* Find an adjacent free-list entry.  */
r_for
c_loop
(paren
id|prev
op_assign
l_int|0
comma
id|fa
op_assign
id|mb_sram_free_areas
suffix:semicolon
id|fa
suffix:semicolon
id|prev
op_assign
id|fa
comma
id|fa
op_assign
id|fa-&gt;next
)paren
r_if
c_cond
(paren
id|fa-&gt;mem
op_eq
id|end
)paren
(brace
multiline_comment|/* FA is just after MEM, grow down to encompass it. */
id|fa-&gt;mem
op_assign
id|mem
suffix:semicolon
id|fa-&gt;size
op_add_assign
id|size
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fa-&gt;mem
op_plus
id|fa-&gt;size
op_eq
id|mem
)paren
(brace
r_struct
id|mb_sram_free_area
op_star
id|next_fa
op_assign
id|fa-&gt;next
suffix:semicolon
multiline_comment|/* FA is just before MEM, expand to encompass it. */
id|fa-&gt;size
op_add_assign
id|size
suffix:semicolon
multiline_comment|/* See if FA can now be merged with its successor. */
r_if
c_cond
(paren
id|next_fa
op_logical_and
id|fa-&gt;mem
op_plus
id|fa-&gt;size
op_eq
id|next_fa-&gt;mem
)paren
(brace
multiline_comment|/* Yup; merge NEXT_FA&squot;s info into FA.  */
id|fa-&gt;size
op_add_assign
id|next_fa-&gt;size
suffix:semicolon
id|fa-&gt;next
op_assign
id|next_fa-&gt;next
suffix:semicolon
multiline_comment|/* Free NEXT_FA.  */
id|next_fa-&gt;next
op_assign
id|mb_sram_free_free_areas
suffix:semicolon
id|mb_sram_free_free_areas
op_assign
id|next_fa
suffix:semicolon
)brace
r_goto
id|done
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fa-&gt;mem
OG
id|mem
)paren
multiline_comment|/* We&squot;ve reached the right spot in the free-list&n;&t;&t;&t;   without finding an adjacent free-area, so add&n;&t;&t;&t;   a new free area to hold mem. */
r_break
suffix:semicolon
multiline_comment|/* Make a new free-list entry.  */
multiline_comment|/* First, get a free-list entry.  */
r_if
c_cond
(paren
op_logical_neg
id|mb_sram_free_free_areas
)paren
(brace
multiline_comment|/* There are none, so make some.  */
r_void
op_star
id|block
suffix:semicolon
r_int
id|block_size
op_assign
r_sizeof
(paren
r_struct
id|mb_sram_free_area
)paren
op_star
l_int|8
suffix:semicolon
multiline_comment|/* Don&squot;t hold the lock while calling kmalloc (I&squot;m not&n;&t;&t;   sure whether it would be a problem, since we use&n;&t;&t;   GFP_ATOMIC, but it makes me nervous).  */
id|spin_unlock_irqrestore
(paren
id|mb_sram_lock
comma
id|flags
)paren
suffix:semicolon
id|block
op_assign
id|kmalloc
(paren
id|block_size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
id|panic
(paren
l_string|&quot;free_mb_sram: can&squot;t allocate free-list entry&quot;
)paren
suffix:semicolon
multiline_comment|/* Now get the lock back.  */
id|spin_lock_irqsave
(paren
id|mb_sram_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Add the new free free-list entries.  */
r_while
c_loop
(paren
id|block_size
OG
l_int|0
)paren
(brace
r_struct
id|mb_sram_free_area
op_star
id|nfa
op_assign
id|block
suffix:semicolon
id|nfa-&gt;next
op_assign
id|mb_sram_free_free_areas
suffix:semicolon
id|mb_sram_free_free_areas
op_assign
id|nfa
suffix:semicolon
id|block
op_add_assign
r_sizeof
op_star
id|nfa
suffix:semicolon
id|block_size
op_sub_assign
r_sizeof
op_star
id|nfa
suffix:semicolon
)brace
multiline_comment|/* Since we dropped the lock to call kmalloc, the&n;&t;&t;   free-list could have changed, so retry from the&n;&t;&t;   beginning.  */
r_goto
id|retry
suffix:semicolon
)brace
multiline_comment|/* Remove NEW_FA from the free-list of free-list entries.  */
id|new_fa
op_assign
id|mb_sram_free_free_areas
suffix:semicolon
id|mb_sram_free_free_areas
op_assign
id|new_fa-&gt;next
suffix:semicolon
multiline_comment|/* NEW_FA initially holds only MEM.  */
id|new_fa-&gt;mem
op_assign
id|mem
suffix:semicolon
id|new_fa-&gt;size
op_assign
id|size
suffix:semicolon
multiline_comment|/* Insert NEW_FA in the free-list between PREV and FA. */
id|new_fa-&gt;next
op_assign
id|fa
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|new_fa
suffix:semicolon
r_else
id|mb_sram_free_areas
op_assign
id|new_fa
suffix:semicolon
id|done
suffix:colon
id|spin_unlock_irqrestore
(paren
id|mb_sram_lock
comma
id|flags
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Maintainence of CPU -&gt; Mother-A DMA mappings.  */
DECL|struct|dma_mapping
r_struct
id|dma_mapping
(brace
DECL|member|cpu_addr
r_void
op_star
id|cpu_addr
suffix:semicolon
DECL|member|mb_sram_addr
r_void
op_star
id|mb_sram_addr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|next
r_struct
id|dma_mapping
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A list of mappings from CPU addresses to MB SRAM addresses for active&n;   DMA blocks (that have been `granted&squot; to the PCI device).  */
DECL|variable|active_dma_mappings
r_static
r_struct
id|dma_mapping
op_star
id|active_dma_mappings
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* A list of free mapping objects.  */
DECL|variable|free_dma_mappings
r_static
r_struct
id|dma_mapping
op_star
id|free_dma_mappings
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Spinlock protecting the above globals.  */
DECL|variable|dma_mappings_lock
r_static
id|spinlock_t
id|dma_mappings_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|new_dma_mapping
r_static
r_struct
id|dma_mapping
op_star
id|new_dma_mapping
(paren
r_int
id|size
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|dma_mapping
op_star
id|mapping
suffix:semicolon
r_void
op_star
id|mb_sram_block
op_assign
id|alloc_mb_sram
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mb_sram_block
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock_irqsave
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|free_dma_mappings
)paren
(brace
multiline_comment|/* We&squot;re out of mapping structures, make more.  */
r_void
op_star
id|mblock
suffix:semicolon
r_int
id|mblock_size
op_assign
r_sizeof
(paren
r_struct
id|dma_mapping
)paren
op_star
l_int|8
suffix:semicolon
multiline_comment|/* Don&squot;t hold the lock while calling kmalloc (I&squot;m not&n;&t;&t;   sure whether it would be a problem, since we use&n;&t;&t;   GFP_ATOMIC, but it makes me nervous).  */
id|spin_unlock_irqrestore
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
id|mblock
op_assign
id|kmalloc
(paren
id|mblock_size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mblock
)paren
(brace
id|free_mb_sram
(paren
id|mb_sram_block
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the lock back.  */
id|spin_lock_irqsave
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Add the new mapping structures to the free-list.  */
r_while
c_loop
(paren
id|mblock_size
OG
l_int|0
)paren
(brace
r_struct
id|dma_mapping
op_star
id|fm
op_assign
id|mblock
suffix:semicolon
id|fm-&gt;next
op_assign
id|free_dma_mappings
suffix:semicolon
id|free_dma_mappings
op_assign
id|fm
suffix:semicolon
id|mblock
op_add_assign
r_sizeof
op_star
id|fm
suffix:semicolon
id|mblock_size
op_sub_assign
r_sizeof
op_star
id|fm
suffix:semicolon
)brace
)brace
multiline_comment|/* Get a mapping struct from the freelist.  */
id|mapping
op_assign
id|free_dma_mappings
suffix:semicolon
id|free_dma_mappings
op_assign
id|mapping-&gt;next
suffix:semicolon
multiline_comment|/* Initialize the mapping.  Other fields should be filled in by&n;&t;   caller.  */
id|mapping-&gt;mb_sram_addr
op_assign
id|mb_sram_block
suffix:semicolon
id|mapping-&gt;size
op_assign
id|size
suffix:semicolon
multiline_comment|/* Add it to the list of active mappings.  */
id|mapping-&gt;next
op_assign
id|active_dma_mappings
suffix:semicolon
id|active_dma_mappings
op_assign
id|mapping
suffix:semicolon
id|spin_unlock_irqrestore
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mapping
suffix:semicolon
)brace
DECL|function|find_dma_mapping
r_static
r_struct
id|dma_mapping
op_star
id|find_dma_mapping
(paren
r_void
op_star
id|mb_sram_addr
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|dma_mapping
op_star
id|mapping
suffix:semicolon
id|spin_lock_irqsave
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|mapping
op_assign
id|active_dma_mappings
suffix:semicolon
id|mapping
suffix:semicolon
id|mapping
op_assign
id|mapping-&gt;next
)paren
r_if
c_cond
(paren
id|mapping-&gt;mb_sram_addr
op_eq
id|mb_sram_addr
)paren
(brace
id|spin_unlock_irqrestore
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mapping
suffix:semicolon
)brace
id|panic
(paren
l_string|&quot;find_dma_mapping: unmapped PCI DMA addr 0x%x&quot;
comma
id|MB_SRAM_TO_PCI
(paren
id|mb_sram_addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|deactivate_dma_mapping
r_static
r_struct
id|dma_mapping
op_star
id|deactivate_dma_mapping
(paren
r_void
op_star
id|mb_sram_addr
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|dma_mapping
op_star
id|mapping
comma
op_star
id|prev
suffix:semicolon
id|spin_lock_irqsave
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|prev
op_assign
l_int|0
comma
id|mapping
op_assign
id|active_dma_mappings
suffix:semicolon
id|mapping
suffix:semicolon
id|prev
op_assign
id|mapping
comma
id|mapping
op_assign
id|mapping-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|mapping-&gt;mb_sram_addr
op_eq
id|mb_sram_addr
)paren
(brace
multiline_comment|/* This is the MAPPING; deactivate it.  */
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|mapping-&gt;next
suffix:semicolon
r_else
id|active_dma_mappings
op_assign
id|mapping-&gt;next
suffix:semicolon
id|spin_unlock_irqrestore
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|mapping
suffix:semicolon
)brace
)brace
id|panic
(paren
l_string|&quot;deactivate_dma_mapping: unmapped PCI DMA addr 0x%x&quot;
comma
id|MB_SRAM_TO_PCI
(paren
id|mb_sram_addr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Return MAPPING to the freelist.  */
r_static
r_inline
r_void
DECL|function|free_dma_mapping
id|free_dma_mapping
(paren
r_struct
id|dma_mapping
op_star
id|mapping
)paren
(brace
r_int
id|flags
suffix:semicolon
id|free_mb_sram
(paren
id|mapping-&gt;mb_sram_addr
comma
id|mapping-&gt;size
)paren
suffix:semicolon
id|spin_lock_irqsave
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
id|mapping-&gt;next
op_assign
id|free_dma_mappings
suffix:semicolon
id|free_dma_mappings
op_assign
id|mapping
suffix:semicolon
id|spin_unlock_irqrestore
(paren
id|dma_mappings_lock
comma
id|flags
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Single PCI DMA mappings.  */
multiline_comment|/* `Grant&squot; to PDEV the memory block at CPU_ADDR, for doing DMA.  The&n;   32-bit PCI bus mastering address to use is returned.  the device owns&n;   this memory until either pci_unmap_single or pci_dma_sync_single is&n;   performed.  */
id|dma_addr_t
DECL|function|pci_map_single
id|pci_map_single
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_void
op_star
id|cpu_addr
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
r_struct
id|dma_mapping
op_star
id|mapping
op_assign
id|new_dma_mapping
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
r_return
l_int|0
suffix:semicolon
id|mapping-&gt;cpu_addr
op_assign
id|cpu_addr
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_eq
id|PCI_DMA_BIDIRECTIONAL
op_logical_or
id|dir
op_eq
id|PCI_DMA_TODEVICE
)paren
id|memcpy
(paren
id|mapping-&gt;mb_sram_addr
comma
id|cpu_addr
comma
id|size
)paren
suffix:semicolon
r_return
id|MB_SRAM_TO_PCI
(paren
id|mapping-&gt;mb_sram_addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Return to the CPU the PCI DMA memory block previously `granted&squot; to&n;   PDEV, at DMA_ADDR.  */
DECL|function|pci_unmap_single
r_void
id|pci_unmap_single
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
r_void
op_star
id|mb_sram_addr
op_assign
id|PCI_TO_MB_SRAM
(paren
id|dma_addr
)paren
suffix:semicolon
r_struct
id|dma_mapping
op_star
id|mapping
op_assign
id|deactivate_dma_mapping
(paren
id|mb_sram_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
id|mapping-&gt;size
)paren
id|panic
(paren
l_string|&quot;pci_unmap_single: size (%d) doesn&squot;t match&quot;
l_string|&quot; size of mapping at PCI DMA addr 0x%x (%d)&bslash;n&quot;
comma
id|size
comma
id|dma_addr
comma
id|mapping-&gt;size
)paren
suffix:semicolon
multiline_comment|/* Copy back the DMA&squot;d contents if necessary.  */
r_if
c_cond
(paren
id|dir
op_eq
id|PCI_DMA_BIDIRECTIONAL
op_logical_or
id|dir
op_eq
id|PCI_DMA_FROMDEVICE
)paren
id|memcpy
(paren
id|mapping-&gt;cpu_addr
comma
id|mb_sram_addr
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Return mapping to the freelist.  */
id|free_dma_mapping
(paren
id|mapping
)paren
suffix:semicolon
)brace
multiline_comment|/* Make physical memory consistent for a single streaming mode DMA&n;   translation after a transfer.&n;&n;   If you perform a pci_map_single() but wish to interrogate the&n;   buffer using the cpu, yet do not wish to teardown the PCI dma&n;   mapping, you must call this function before doing so.  At the next&n;   point you give the PCI dma address back to the card, the device&n;   again owns the buffer.  */
r_void
DECL|function|pci_dma_sync_single
id|pci_dma_sync_single
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
r_void
op_star
id|mb_sram_addr
op_assign
id|PCI_TO_MB_SRAM
(paren
id|dma_addr
)paren
suffix:semicolon
r_struct
id|dma_mapping
op_star
id|mapping
op_assign
id|find_dma_mapping
(paren
id|mb_sram_addr
)paren
suffix:semicolon
multiline_comment|/* Synchronize the DMA buffer with the CPU buffer if necessary.  */
r_if
c_cond
(paren
id|dir
op_eq
id|PCI_DMA_FROMDEVICE
)paren
id|memcpy
(paren
id|mapping-&gt;cpu_addr
comma
id|mb_sram_addr
comma
id|size
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dir
op_eq
id|PCI_DMA_TODEVICE
)paren
id|memcpy
(paren
id|mb_sram_addr
comma
id|mapping-&gt;cpu_addr
comma
id|size
)paren
suffix:semicolon
r_else
id|panic
c_func
(paren
l_string|&quot;pci_dma_sync_single: unsupported sync dir: %d&quot;
comma
id|dir
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Scatter-gather PCI DMA mappings.  */
multiline_comment|/* Do multiple DMA mappings at once.  */
r_int
DECL|function|pci_map_sg
id|pci_map_sg
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sg_len
comma
r_int
id|dir
)paren
(brace
id|BUG
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Unmap multiple DMA mappings at once.  */
r_void
DECL|function|pci_unmap_sg
id|pci_unmap_sg
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sg_len
comma
r_int
id|dir
)paren
(brace
id|BUG
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Make physical memory consistent for a set of streaming mode DMA&n;   translations after a transfer.  The same as pci_dma_sync_single but&n;   for a scatter-gather list, same rules and usage.  */
r_void
DECL|function|pci_dma_sync_sg
id|pci_dma_sync_sg
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sg_len
comma
r_int
id|dir
)paren
(brace
id|BUG
(paren
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* PCI mem mapping.  */
multiline_comment|/* Allocate and map kernel buffer using consistent mode DMA for PCI&n;   device.  Returns non-NULL cpu-view pointer to the buffer if&n;   successful and sets *DMA_ADDR to the pci side dma address as well,&n;   else DMA_ADDR is undefined.  */
r_void
op_star
DECL|function|pci_alloc_consistent
id|pci_alloc_consistent
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
(brace
r_void
op_star
id|mb_sram_mem
op_assign
id|alloc_mb_sram
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mb_sram_mem
)paren
op_star
id|dma_addr
op_assign
id|MB_SRAM_TO_PCI
(paren
id|mb_sram_mem
)paren
suffix:semicolon
r_return
id|mb_sram_mem
suffix:semicolon
)brace
multiline_comment|/* Free and unmap a consistent DMA buffer.  CPU_ADDR and DMA_ADDR must&n;   be values that were returned from pci_alloc_consistent.  SIZE must be&n;   the same as what as passed into pci_alloc_consistent.  References to&n;   the memory and mappings assosciated with CPU_ADDR or DMA_ADDR past&n;   this call are illegal.  */
r_void
DECL|function|pci_free_consistent
id|pci_free_consistent
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|size
comma
r_void
op_star
id|cpu_addr
comma
id|dma_addr_t
id|dma_addr
)paren
(brace
r_void
op_star
id|mb_sram_mem
op_assign
id|PCI_TO_MB_SRAM
(paren
id|dma_addr
)paren
suffix:semicolon
id|free_mb_sram
(paren
id|mb_sram_mem
comma
id|size
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* symbol exports (for modules) */
DECL|variable|pci_map_single
id|EXPORT_SYMBOL
(paren
id|pci_map_single
)paren
suffix:semicolon
DECL|variable|pci_unmap_single
id|EXPORT_SYMBOL
(paren
id|pci_unmap_single
)paren
suffix:semicolon
DECL|variable|pci_alloc_consistent
id|EXPORT_SYMBOL
(paren
id|pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|pci_free_consistent
id|EXPORT_SYMBOL
(paren
id|pci_free_consistent
)paren
suffix:semicolon
DECL|variable|pci_dma_sync_single
id|EXPORT_SYMBOL
(paren
id|pci_dma_sync_single
)paren
suffix:semicolon
eof
