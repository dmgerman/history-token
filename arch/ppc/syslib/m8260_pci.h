macro_line|#ifndef _PPC_KERNEL_M8260_PCI_H
DECL|macro|_PPC_KERNEL_M8260_PCI_H
mdefine_line|#define _PPC_KERNEL_M8260_PCI_H
macro_line|#include &lt;asm/m8260_pci.h&gt;
multiline_comment|/*&n; *   Local-&gt;PCI map (from CPU)                             controlled by&n; *   MPC826x master window&n; *&n; *   0x80000000 - 0xBFFFFFFF    Total CPU2PCI space        PCIBR0&n; *                       &n; *   0x80000000 - 0x9FFFFFFF    PCI Mem with prefetch      (Outbound ATU #1)&n; *   0xA0000000 - 0xAFFFFFFF    PCI Mem w/o  prefetch      (Outbound ATU #2)&n; *   0xB0000000 - 0xB0FFFFFF    32-bit PCI IO              (Outbound ATU #3)&n; *                      &n; *   PCI-&gt;Local map (from PCI)&n; *   MPC826x slave window                                  controlled by&n; *&n; *   0x00000000 - 0x07FFFFFF    MPC826x local memory       (Inbound ATU #1)&n; */
multiline_comment|/* &n; * Slave window that allows PCI masters to access MPC826x local memory. &n; * This window is set up using the first set of Inbound ATU registers&n; */
macro_line|#ifndef MPC826x_PCI_SLAVE_MEM_LOCAL
DECL|macro|MPC826x_PCI_SLAVE_MEM_LOCAL
mdefine_line|#define MPC826x_PCI_SLAVE_MEM_LOCAL&t;(((struct bd_info *)__res)-&gt;bi_memstart)
DECL|macro|MPC826x_PCI_SLAVE_MEM_BUS
mdefine_line|#define MPC826x_PCI_SLAVE_MEM_BUS&t;(((struct bd_info *)__res)-&gt;bi_memstart)
DECL|macro|MPC826x_PCI_SLAVE_MEM_SIZE
mdefine_line|#define MPC826x_PCI_SLAVE_MEM_SIZE&t;(((struct bd_info *)__res)-&gt;bi_memsize)
macro_line|#endif
multiline_comment|/* &n; * This is the window that allows the CPU to access PCI address space.&n; * It will be setup with the SIU PCIBR0 register. All three PCI master&n; * windows, which allow the CPU to access PCI prefetch, non prefetch,&n; * and IO space (see below), must all fit within this window. &n; */
macro_line|#ifndef MPC826x_PCI_BASE
DECL|macro|MPC826x_PCI_BASE
mdefine_line|#define MPC826x_PCI_BASE&t;0x80000000
DECL|macro|MPC826x_PCI_MASK
mdefine_line|#define MPC826x_PCI_MASK&t;0xc0000000
macro_line|#endif
macro_line|#ifndef MPC826x_PCI_LOWER_MEM
DECL|macro|MPC826x_PCI_LOWER_MEM
mdefine_line|#define MPC826x_PCI_LOWER_MEM  0x80000000
DECL|macro|MPC826x_PCI_UPPER_MEM
mdefine_line|#define MPC826x_PCI_UPPER_MEM  0x9fffffff
DECL|macro|MPC826x_PCI_MEM_OFFSET
mdefine_line|#define MPC826x_PCI_MEM_OFFSET 0x00000000
macro_line|#endif
macro_line|#ifndef MPC826x_PCI_LOWER_MMIO
DECL|macro|MPC826x_PCI_LOWER_MMIO
mdefine_line|#define MPC826x_PCI_LOWER_MMIO  0xa0000000
DECL|macro|MPC826x_PCI_UPPER_MMIO
mdefine_line|#define MPC826x_PCI_UPPER_MMIO  0xafffffff
DECL|macro|MPC826x_PCI_MMIO_OFFSET
mdefine_line|#define MPC826x_PCI_MMIO_OFFSET 0x00000000
macro_line|#endif
macro_line|#ifndef MPC826x_PCI_LOWER_IO
DECL|macro|MPC826x_PCI_LOWER_IO
mdefine_line|#define MPC826x_PCI_LOWER_IO   0x00000000
DECL|macro|MPC826x_PCI_UPPER_IO
mdefine_line|#define MPC826x_PCI_UPPER_IO   0x00ffffff
DECL|macro|MPC826x_PCI_IO_BASE
mdefine_line|#define MPC826x_PCI_IO_BASE    0xb0000000
DECL|macro|MPC826x_PCI_IO_SIZE
mdefine_line|#define MPC826x_PCI_IO_SIZE    0x01000000
macro_line|#endif
macro_line|#ifndef _IO_BASE
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE isa_io_base
macro_line|#endif
macro_line|#ifdef CONFIG_8260_PCI9
r_extern
r_void
id|setup_m8260_indirect_pci
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|u32
id|cfg_addr
comma
id|u32
id|cfg_data
)paren
suffix:semicolon
macro_line|#else
DECL|macro|setup_m8260_indirect_pci
mdefine_line|#define setup_m8260_indirect_pci setup_indirect_pci
macro_line|#endif
macro_line|#endif /* _PPC_KERNEL_M8260_PCI_H */
eof
