multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_tsunami.c&n; *&n; * Based on code written by David A. Rusling (david.rusling@reo.mts.dec.com).&n; *&n; * Code common to all TSUNAMI core logic chips.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_tsunami.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
multiline_comment|/* Save Tsunami configuration data as the console had it set up.  */
r_struct
(brace
DECL|member|wsba
r_int
r_int
id|wsba
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|wsm
r_int
r_int
id|wsm
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|tba
r_int
r_int
id|tba
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|saved_config
)brace
id|saved_config
(braket
l_int|2
)braket
id|__attribute__
c_func
(paren
(paren
id|common
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * NOTE: Herein lie back-to-back mb instructions.  They are magic. &n; * One plausible explanation is that the I/O controller does not properly&n; * handle the system transaction.  Another involves timing.  Ho hum.&n; */
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_MCHECK
mdefine_line|#define DEBUG_MCHECK 0&t;&t;/* 0 = minimal, 1 = debug, 2 = debug+dump.  */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)&t;printk args
macro_line|#else
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)
macro_line|#endif
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address&n; * accordingly.  It is therefore not safe to have concurrent&n; * invocations to configuration space access routines, but there&n; * really shouldn&squot;t be any need for this.&n; *&n; * Note that all config space accesses use Type 1 address format.&n; *&n; * Note also that type 1 is determined by non-zero bus number.&n; *&n; * Type 1:&n; *&n; *  3 3|3 3 2 2|2 2 2 2|2 2 2 2|1 1 1 1|1 1 1 1|1 1 &n; *  3 2|1 0 9 8|7 6 5 4|3 2 1 0|9 8 7 6|5 4 3 2|1 0 9 8|7 6 5 4|3 2 1 0&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; * | | | | | | | | | | |B|B|B|B|B|B|B|B|D|D|D|D|D|F|F|F|R|R|R|R|R|R|0|1|&n; * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; *&t;31:24&t;reserved&n; *&t;23:16&t;bus number (8 bits = 128 possible buses)&n; *&t;15:11&t;Device number (5 bits)&n; *&t;10:8&t;function number&n; *&t; 7:2&t;register number&n; *  &n; * Notes:&n; *&t;The function number selects which function of a multi-function device &n; *&t;(e.g., SCSI and Ethernet).&n; * &n; *&t;The register selects a DWORD (32 bit) register offset.  Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
r_static
r_int
DECL|function|mk_conf_addr
id|mk_conf_addr
c_func
(paren
r_struct
id|pci_bus
op_star
id|pbus
comma
r_int
r_int
id|device_fn
comma
r_int
id|where
comma
r_int
r_int
op_star
id|pci_addr
comma
r_int
r_char
op_star
id|type1
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|pbus-&gt;sysdata
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|u8
id|bus
op_assign
id|pbus-&gt;number
suffix:semicolon
id|DBG_CFG
c_func
(paren
(paren
l_string|&quot;mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, &quot;
l_string|&quot;pci_addr=0x%p, type1=0x%p)&bslash;n&quot;
comma
id|bus
comma
id|device_fn
comma
id|where
comma
id|pci_addr
comma
id|type1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;bus
op_eq
id|pbus
)paren
id|bus
op_assign
l_int|0
suffix:semicolon
op_star
id|type1
op_assign
(paren
id|bus
op_ne
l_int|0
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|device_fn
op_lshift
l_int|8
)paren
op_or
id|where
suffix:semicolon
id|addr
op_or_assign
id|hose-&gt;config_space_base
suffix:semicolon
op_star
id|pci_addr
op_assign
id|addr
suffix:semicolon
id|DBG_CFG
c_func
(paren
(paren
l_string|&quot;mk_conf_addr: returning pci_addr 0x%lx&bslash;n&quot;
comma
id|addr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|tsunami_read_config
id|tsunami_read_config
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
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
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
id|value
op_assign
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|value
op_assign
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|value
op_assign
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|tsunami_write_config
id|tsunami_write_config
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
suffix:semicolon
r_int
r_char
id|type1
suffix:semicolon
r_if
c_cond
(paren
id|mk_conf_addr
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|addr
comma
op_amp
id|type1
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
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
id|__kernel_stb
c_func
(paren
id|value
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__kernel_stw
c_func
(paren
id|value
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|value
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|tsunami_pci_ops
r_struct
id|pci_ops
id|tsunami_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|tsunami_read_config
comma
dot
id|write
op_assign
id|tsunami_write_config
comma
)brace
suffix:semicolon
"&f;"
r_void
DECL|function|tsunami_pci_tbi
id|tsunami_pci_tbi
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|dma_addr_t
id|start
comma
id|dma_addr_t
id|end
)paren
(brace
id|tsunami_pchip
op_star
id|pchip
op_assign
id|hose-&gt;index
ques
c_cond
id|TSUNAMI_pchip1
suffix:colon
id|TSUNAMI_pchip0
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|csr
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* We can invalidate up to 8 tlb entries in a go.  The flush&n;&t;   matches against &lt;31:16&gt; in the pci address.  */
id|csr
op_assign
op_amp
id|pchip-&gt;tlbia.csr
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|start
op_xor
id|end
)paren
op_amp
l_int|0xffff0000
)paren
op_eq
l_int|0
)paren
id|csr
op_assign
op_amp
id|pchip-&gt;tlbiv.csr
suffix:semicolon
multiline_comment|/* For TBIA, it doesn&squot;t matter what value we write.  For TBI, &n;&t;   it&squot;s the shifted tag bits.  */
id|value
op_assign
(paren
id|start
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|12
suffix:semicolon
op_star
id|csr
op_assign
id|value
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|csr
suffix:semicolon
)brace
"&f;"
macro_line|#ifdef NXM_MACHINE_CHECKS_ON_TSUNAMI
r_static
r_int
id|__init
DECL|function|tsunami_probe_read
id|tsunami_probe_read
c_func
(paren
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_int
id|dont_care
comma
id|probe_result
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
id|s
op_assign
id|swpipl
c_func
(paren
id|IPL_MCHECK
op_minus
l_int|1
)paren
suffix:semicolon
id|mcheck_taken
c_func
(paren
id|cpu
)paren
op_assign
l_int|0
suffix:semicolon
id|mcheck_expected
c_func
(paren
id|cpu
)paren
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|dont_care
op_assign
op_star
id|vaddr
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
id|mcheck_expected
c_func
(paren
id|cpu
)paren
op_assign
l_int|0
suffix:semicolon
id|probe_result
op_assign
op_logical_neg
id|mcheck_taken
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|mcheck_taken
c_func
(paren
id|cpu
)paren
op_assign
l_int|0
suffix:semicolon
id|setipl
c_func
(paren
id|s
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dont_care == 0x%lx&bslash;n&quot;
comma
id|dont_care
)paren
suffix:semicolon
r_return
id|probe_result
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|tsunami_probe_write
id|tsunami_probe_write
c_func
(paren
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_int
id|true_contents
comma
id|probe_result
op_assign
l_int|1
suffix:semicolon
id|TSUNAMI_cchip-&gt;misc.csr
op_or_assign
(paren
l_int|1L
op_lshift
l_int|28
)paren
suffix:semicolon
multiline_comment|/* clear NXM... */
id|true_contents
op_assign
op_star
id|vaddr
suffix:semicolon
op_star
id|vaddr
op_assign
l_int|0
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TSUNAMI_cchip-&gt;misc.csr
op_amp
(paren
l_int|1L
op_lshift
l_int|28
)paren
)paren
(brace
r_int
id|source
op_assign
(paren
id|TSUNAMI_cchip-&gt;misc.csr
op_rshift
l_int|29
)paren
op_amp
l_int|7
suffix:semicolon
id|TSUNAMI_cchip-&gt;misc.csr
op_or_assign
(paren
l_int|1L
op_lshift
l_int|28
)paren
suffix:semicolon
multiline_comment|/* ...and unlock NXS. */
id|probe_result
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tsunami_probe_write: unit %d at 0x%016lx&bslash;n&quot;
comma
id|source
comma
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|probe_result
)paren
op_star
id|vaddr
op_assign
id|true_contents
suffix:semicolon
r_return
id|probe_result
suffix:semicolon
)brace
macro_line|#else
DECL|macro|tsunami_probe_read
mdefine_line|#define tsunami_probe_read(ADDR) 1
macro_line|#endif /* NXM_MACHINE_CHECKS_ON_TSUNAMI */
DECL|macro|FN
mdefine_line|#define FN __FUNCTION__
r_static
r_void
id|__init
DECL|function|tsunami_init_one_pchip
id|tsunami_init_one_pchip
c_func
(paren
id|tsunami_pchip
op_star
id|pchip
comma
r_int
id|index
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_if
c_cond
(paren
id|tsunami_probe_read
c_func
(paren
op_amp
id|pchip-&gt;pctl.csr
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|hose
op_assign
id|alloc_pci_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
l_int|0
)paren
id|pci_isa_hose
op_assign
id|hose
suffix:semicolon
id|hose-&gt;io_space
op_assign
id|alloc_resource
c_func
(paren
)paren
suffix:semicolon
id|hose-&gt;mem_space
op_assign
id|alloc_resource
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This is for userland consumption.  For some reason, the 40-bit&n;&t;   PIO bias that we use in the kernel through KSEG didn&squot;t work for&n;&t;   the page table based user mappings.  So make sure we get the&n;&t;   43-bit PIO bias.  */
id|hose-&gt;sparse_mem_base
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;sparse_io_base
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;dense_mem_base
op_assign
(paren
id|TSUNAMI_MEM
c_func
(paren
id|index
)paren
op_amp
l_int|0xffffffffff
)paren
op_or
l_int|0x80000000000
suffix:semicolon
id|hose-&gt;dense_io_base
op_assign
(paren
id|TSUNAMI_IO
c_func
(paren
id|index
)paren
op_amp
l_int|0xffffffffff
)paren
op_or
l_int|0x80000000000
suffix:semicolon
id|hose-&gt;config_space_base
op_assign
id|TSUNAMI_CONF
c_func
(paren
id|index
)paren
suffix:semicolon
id|hose-&gt;index
op_assign
id|index
suffix:semicolon
id|hose-&gt;io_space-&gt;start
op_assign
id|TSUNAMI_IO
c_func
(paren
id|index
)paren
op_minus
id|TSUNAMI_IO_BIAS
suffix:semicolon
id|hose-&gt;io_space-&gt;end
op_assign
id|hose-&gt;io_space-&gt;start
op_plus
id|TSUNAMI_IO_SPACE
op_minus
l_int|1
suffix:semicolon
id|hose-&gt;io_space-&gt;name
op_assign
id|pci_io_names
(braket
id|index
)braket
suffix:semicolon
id|hose-&gt;io_space-&gt;flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|hose-&gt;mem_space-&gt;start
op_assign
id|TSUNAMI_MEM
c_func
(paren
id|index
)paren
op_minus
id|TSUNAMI_MEM_BIAS
suffix:semicolon
id|hose-&gt;mem_space-&gt;end
op_assign
id|hose-&gt;mem_space-&gt;start
op_plus
l_int|0xffffffff
suffix:semicolon
id|hose-&gt;mem_space-&gt;name
op_assign
id|pci_mem_names
(braket
id|index
)braket
suffix:semicolon
id|hose-&gt;mem_space-&gt;flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
id|hose-&gt;io_space
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to request IO on hose %d&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|hose-&gt;mem_space
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to request MEM on hose %d&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Save the existing PCI window translations.  SRM will &n;&t; * need them when we go to reboot.&n;&t; */
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|0
)braket
op_assign
id|pchip-&gt;wsba
(braket
l_int|0
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|0
)braket
op_assign
id|pchip-&gt;wsm
(braket
l_int|0
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|0
)braket
op_assign
id|pchip-&gt;tba
(braket
l_int|0
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|1
)braket
op_assign
id|pchip-&gt;wsba
(braket
l_int|1
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|1
)braket
op_assign
id|pchip-&gt;wsm
(braket
l_int|1
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|1
)braket
op_assign
id|pchip-&gt;tba
(braket
l_int|1
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|2
)braket
op_assign
id|pchip-&gt;wsba
(braket
l_int|2
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|2
)braket
op_assign
id|pchip-&gt;wsm
(braket
l_int|2
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|2
)braket
op_assign
id|pchip-&gt;tba
(braket
l_int|2
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|3
)braket
op_assign
id|pchip-&gt;wsba
(braket
l_int|3
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|3
)braket
op_assign
id|pchip-&gt;wsm
(braket
l_int|3
)braket
dot
id|csr
suffix:semicolon
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|3
)braket
op_assign
id|pchip-&gt;tba
(braket
l_int|3
)braket
dot
id|csr
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the PCI to main memory translation windows.&n;&t; *&n;&t; * Note: Window 3 is scatter-gather only&n;&t; * &n;&t; * Window 0 is scatter-gather 8MB at 8MB (for isa)&n;&t; * Window 1 is scatter-gather (up to) 1GB at 1GB&n;&t; * Window 2 is direct access 2GB at 2GB&n;&t; *&n;&t; * NOTE: we need the align_entry settings for Acer devices on ES40,&n;&t; * specifically floppy and IDE when memory is larger than 2GB.&n;&t; */
id|hose-&gt;sg_isa
op_assign
id|iommu_arena_new
c_func
(paren
id|hose
comma
l_int|0x00800000
comma
l_int|0x00800000
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Initially set for 4 PTEs, but will be overridden to 64K for ISA. */
id|hose-&gt;sg_isa-&gt;align_entry
op_assign
l_int|4
suffix:semicolon
id|hose-&gt;sg_pci
op_assign
id|iommu_arena_new
c_func
(paren
id|hose
comma
l_int|0x40000000
comma
id|size_for_memory
c_func
(paren
l_int|0x40000000
)paren
comma
l_int|0
)paren
suffix:semicolon
id|hose-&gt;sg_pci-&gt;align_entry
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* Tsunami caches 4 PTEs at a time */
id|__direct_map_base
op_assign
l_int|0x80000000
suffix:semicolon
id|__direct_map_size
op_assign
l_int|0x80000000
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|0
)braket
dot
id|csr
op_assign
id|hose-&gt;sg_isa-&gt;dma_base
op_or
l_int|3
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|0
)braket
dot
id|csr
op_assign
(paren
id|hose-&gt;sg_isa-&gt;size
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|0
)braket
dot
id|csr
op_assign
id|virt_to_phys
c_func
(paren
id|hose-&gt;sg_isa-&gt;ptes
)paren
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|1
)braket
dot
id|csr
op_assign
id|hose-&gt;sg_pci-&gt;dma_base
op_or
l_int|3
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|1
)braket
dot
id|csr
op_assign
(paren
id|hose-&gt;sg_pci-&gt;size
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|1
)braket
dot
id|csr
op_assign
id|virt_to_phys
c_func
(paren
id|hose-&gt;sg_pci-&gt;ptes
)paren
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|2
)braket
dot
id|csr
op_assign
l_int|0x80000000
op_or
l_int|1
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|2
)braket
dot
id|csr
op_assign
(paren
l_int|0x80000000
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|2
)braket
dot
id|csr
op_assign
l_int|0
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|3
)braket
dot
id|csr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Enable the Monster Window to make DAC pci64 possible. */
id|pchip-&gt;pctl.csr
op_or_assign
id|pctl_m_mwin
suffix:semicolon
id|tsunami_pci_tbi
c_func
(paren
id|hose
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|tsunami_init_arch
id|tsunami_init_arch
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef NXM_MACHINE_CHECKS_ON_TSUNAMI
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* Ho hum.. init_arch is called before init_IRQ, but we need to be&n;&t;   able to handle machine checks.  So install the handler now.  */
id|wrent
c_func
(paren
id|entInt
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* NXMs just don&squot;t matter to Tsunami--unless they make it&n;&t;   choke completely. */
id|tmp
op_assign
(paren
r_int
r_int
)paren
(paren
id|TSUNAMI_cchip
op_minus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: probing bogus address:  0x%016lx&bslash;n&quot;
comma
id|FN
comma
id|bogus_addr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tprobe %s&bslash;n&quot;
comma
id|tsunami_probe_write
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|bogus_addr
)paren
ques
c_cond
l_string|&quot;succeeded&quot;
suffix:colon
l_string|&quot;failed&quot;
)paren
suffix:semicolon
macro_line|#endif /* NXM_MACHINE_CHECKS_ON_TSUNAMI */
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;%s: CChip registers:&bslash;n&quot;
comma
id|FN
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_CSC 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;csc.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_MTR 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip.mtr.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_MISC 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;misc.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DIM0 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;dim0.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DIM1 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;dim1.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DIR0 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;dir0.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DIR1 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;dir1.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DRIR 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_cchip-&gt;drir.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: DChip registers:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DSC 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_dchip-&gt;dsc.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_STR 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_dchip-&gt;str.csr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CSR_DREV 0x%lx&bslash;n&quot;
comma
id|FN
comma
id|TSUNAMI_dchip-&gt;drev.csr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* With multiple PCI busses, we play with I/O as physical addrs.  */
id|ioport_resource.end
op_assign
op_complement
l_int|0UL
suffix:semicolon
multiline_comment|/* Find how many hoses we have, and initialize them.  TSUNAMI&n;&t;   and TYPHOON can have 2, but might only have 1 (DS10).  */
id|tsunami_init_one_pchip
c_func
(paren
id|TSUNAMI_pchip0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TSUNAMI_cchip-&gt;csc.csr
op_amp
l_int|1L
op_lshift
l_int|14
)paren
id|tsunami_init_one_pchip
c_func
(paren
id|TSUNAMI_pchip1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|tsunami_kill_one_pchip
id|tsunami_kill_one_pchip
c_func
(paren
id|tsunami_pchip
op_star
id|pchip
comma
r_int
id|index
)paren
(brace
id|pchip-&gt;wsba
(braket
l_int|0
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|0
)braket
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|0
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|0
)braket
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|0
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|0
)braket
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|1
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|1
)braket
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|1
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|1
)braket
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|1
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|1
)braket
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|2
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|2
)braket
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|2
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|2
)braket
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|2
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|2
)braket
suffix:semicolon
id|pchip-&gt;wsba
(braket
l_int|3
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsba
(braket
l_int|3
)braket
suffix:semicolon
id|pchip-&gt;wsm
(braket
l_int|3
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|wsm
(braket
l_int|3
)braket
suffix:semicolon
id|pchip-&gt;tba
(braket
l_int|3
)braket
dot
id|csr
op_assign
id|saved_config
(braket
id|index
)braket
dot
id|tba
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_void
DECL|function|tsunami_kill_arch
id|tsunami_kill_arch
c_func
(paren
r_int
id|mode
)paren
(brace
id|tsunami_kill_one_pchip
c_func
(paren
id|TSUNAMI_pchip0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TSUNAMI_cchip-&gt;csc.csr
op_amp
l_int|1L
op_lshift
l_int|14
)paren
id|tsunami_kill_one_pchip
c_func
(paren
id|TSUNAMI_pchip1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tsunami_pci_clr_err_1
id|tsunami_pci_clr_err_1
c_func
(paren
id|tsunami_pchip
op_star
id|pchip
)paren
(brace
id|pchip-&gt;perror.csr
suffix:semicolon
id|pchip-&gt;perror.csr
op_assign
l_int|0x040
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|pchip-&gt;perror.csr
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tsunami_pci_clr_err
id|tsunami_pci_clr_err
c_func
(paren
r_void
)paren
(brace
id|tsunami_pci_clr_err_1
c_func
(paren
id|TSUNAMI_pchip0
)paren
suffix:semicolon
multiline_comment|/* TSUNAMI and TYPHOON can have 2, but might only have 1 (DS10) */
r_if
c_cond
(paren
id|TSUNAMI_cchip-&gt;csc.csr
op_amp
l_int|1L
op_lshift
l_int|14
)paren
id|tsunami_pci_clr_err_1
c_func
(paren
id|TSUNAMI_pchip1
)paren
suffix:semicolon
)brace
r_void
DECL|function|tsunami_machine_check
id|tsunami_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Clear error before any reporting.  */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* magic */
id|draina
c_func
(paren
)paren
suffix:semicolon
id|tsunami_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|process_mcheck_info
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
comma
l_string|&quot;TSUNAMI&quot;
comma
id|mcheck_expected
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
)brace
eof
