multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/core_irongate.c&n; *&n; * Based on code written by David A. Rusling (david.rusling@reo.mts.dec.com).&n; *&n; *&t;Copyright (C) 1999 Alpha Processor, Inc.,&n; *&t;&t;(David Daniel, Stig Telfer, Soohoon Lee)&n; *&n; * Code common to all IRONGATE core logic chips.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/core_irongate.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
multiline_comment|/*&n; * BIOS32-style PCI interface:&n; */
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)&t;printk args
macro_line|#else
DECL|macro|DBG_CFG
macro_line|# define DBG_CFG(args)
macro_line|#endif
DECL|variable|IronECC
id|igcsr32
op_star
id|IronECC
suffix:semicolon
multiline_comment|/*&n; * Given a bus, device, and function number, compute resulting&n; * configuration space address accordingly.  It is therefore not safe&n; * to have concurrent invocations to configuration space access&n; * routines, but there really shouldn&squot;t be any need for this.&n; *&n; *&t;addr[31:24]&t;&t;reserved&n; *&t;addr[23:16]&t;&t;bus number (8 bits = 128 possible buses)&n; *&t;addr[15:11]&t;&t;Device number (5 bits)&n; *&t;addr[10: 8]&t;&t;function number&n; *&t;addr[ 7: 2]&t;&t;register number&n; *&n; * For IRONGATE:&n; *    if (bus = addr[23:16]) == 0&n; *    then&n; *&t;  type 0 config cycle:&n; *&t;      addr_on_pci[31:11] = id selection for device = addr[15:11]&n; *&t;      addr_on_pci[10: 2] = addr[10: 2] ???&n; *&t;      addr_on_pci[ 1: 0] = 00&n; *    else&n; *&t;  type 1 config cycle (pass on with no decoding):&n; *&t;      addr_on_pci[31:24] = 0&n; *&t;      addr_on_pci[23: 2] = addr[23: 2]&n; *&t;      addr_on_pci[ 1: 0] = 01&n; *    fi&n; *&n; * Notes:&n; *&t;The function number selects which function of a multi-function device&n; *&t;(e.g., SCSI and Ethernet).&n; *&n; *&t;The register selects a DWORD (32 bit) register offset.&t;Hence it&n; *&t;doesn&squot;t get shifted by 2 bits as we want to &quot;drop&quot; the bottom two&n; *&t;bits.&n; */
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
id|IRONGATE_CONF
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
DECL|function|irongate_read_config
id|irongate_read_config
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
DECL|function|irongate_write_config
id|irongate_write_config
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
DECL|variable|irongate_pci_ops
r_struct
id|pci_ops
id|irongate_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|irongate_read_config
comma
dot
id|write
op_assign
id|irongate_write_config
comma
)brace
suffix:semicolon
"&f;"
r_int
DECL|function|irongate_pci_clr_err
id|irongate_pci_clr_err
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|nmi_ctl
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|IRONGATE_jd
suffix:semicolon
id|again
suffix:colon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Iron stat_cmd %x&bslash;n&quot;
comma
id|IRONGATE_jd
)paren
suffix:semicolon
id|IRONGATE0-&gt;stat_cmd
op_assign
id|IRONGATE_jd
suffix:semicolon
multiline_comment|/* write again clears error bits */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
multiline_comment|/* re-read to force write */
id|IRONGATE_jd
op_assign
op_star
id|IronECC
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Iron ECC %x&bslash;n&quot;
comma
id|IRONGATE_jd
)paren
suffix:semicolon
op_star
id|IronECC
op_assign
id|IRONGATE_jd
suffix:semicolon
multiline_comment|/* write again clears error bits */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
op_star
id|IronECC
suffix:semicolon
multiline_comment|/* re-read to force write */
multiline_comment|/* Clear ALI NMI */
id|nmi_ctl
op_assign
id|inb
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_or_assign
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|IRONGATE_jd
op_assign
op_star
id|IronECC
suffix:semicolon
r_if
c_cond
(paren
id|IRONGATE_jd
op_amp
l_int|0x300
)paren
r_goto
id|again
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|IRONGATE_3GB
mdefine_line|#define IRONGATE_3GB 0xc0000000UL
multiline_comment|/* On Albacore (aka UP1500) with 4Gb of RAM we have to reserve some&n;   memory for PCI. At this point we just reserve memory above 3Gb. Most&n;   of this memory will be freed after PCI setup is done. */
r_static
r_void
id|__init
DECL|function|albacore_init_arch
id|albacore_init_arch
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|memtop
op_assign
id|max_low_pfn
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|pci_mem
op_assign
(paren
id|memtop
op_plus
l_int|0x1000000UL
)paren
op_amp
op_complement
l_int|0xffffffUL
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|cpu
suffix:semicolon
r_int
id|pal_rev
comma
id|pal_var
suffix:semicolon
id|cpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
)paren
suffix:semicolon
id|pal_rev
op_assign
id|cpu-&gt;pal_revision
op_amp
l_int|0xffff
suffix:semicolon
id|pal_var
op_assign
(paren
id|cpu-&gt;pal_revision
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* Consoles earlier than A5.6-18 (OSF PALcode v1.62-2) set up&n;&t;   the CPU incorrectly (leave speculative stores enabled),&n;&t;   which causes memory corruption under certain conditions.&n;&t;   Issue a warning for such consoles. */
r_if
c_cond
(paren
id|alpha_using_srm
op_logical_and
(paren
id|pal_rev
OL
l_int|0x13e
op_logical_or
(paren
id|pal_rev
op_eq
l_int|0x13e
op_logical_and
id|pal_var
OL
l_int|2
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;WARNING! Upgrade to SRM A5.6-19 &quot;
l_string|&quot;or later&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_mem
OG
id|IRONGATE_3GB
)paren
id|pci_mem
op_assign
id|IRONGATE_3GB
suffix:semicolon
id|IRONGATE0-&gt;pci_mem
op_assign
id|pci_mem
suffix:semicolon
id|alpha_mv.min_mem_address
op_assign
id|pci_mem
suffix:semicolon
r_if
c_cond
(paren
id|memtop
OG
id|pci_mem
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_void
op_star
id|move_initrd
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Move the initrd out of the way. */
r_if
c_cond
(paren
id|initrd_end
op_logical_and
id|__pa
c_func
(paren
id|initrd_end
)paren
OG
id|pci_mem
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
id|initrd_end
op_minus
id|initrd_start
suffix:semicolon
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|__pa
c_func
(paren
id|initrd_start
)paren
comma
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|move_initrd
c_func
(paren
id|pci_mem
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;irongate_init_arch: initrd too big &quot;
l_string|&quot;(%ldK)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|size
op_div
l_int|1024
)paren
suffix:semicolon
)brace
macro_line|#endif
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|pci_mem
comma
id|memtop
op_minus
id|pci_mem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_init_arch: temporarily reserving &quot;
l_string|&quot;region %08lx-%08lx for PCI&bslash;n&quot;
comma
id|pci_mem
comma
id|memtop
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|irongate_setup_agp
id|irongate_setup_agp
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Disable the GART window. AGPGART doesn&squot;t work due to yet&n;&t;   unresolved memory coherency issues... */
id|IRONGATE0-&gt;agpva
op_assign
id|IRONGATE0-&gt;agpva
op_amp
op_complement
l_int|0xf
suffix:semicolon
id|alpha_agpgart_size
op_assign
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|irongate_init_arch
id|irongate_init_arch
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
id|amd761
op_assign
(paren
id|IRONGATE0-&gt;dev_vendor
op_rshift
l_int|16
)paren
OG
l_int|0x7006
suffix:semicolon
multiline_comment|/* Albacore? */
id|IronECC
op_assign
id|amd761
ques
c_cond
op_amp
id|IRONGATE0-&gt;bacsr54_eccms761
suffix:colon
op_amp
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|irongate_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amd761
)paren
id|albacore_init_arch
c_func
(paren
)paren
suffix:semicolon
id|irongate_setup_agp
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create our single hose.&n;&t; */
id|pci_isa_hose
op_assign
id|hose
op_assign
id|alloc_pci_controller
c_func
(paren
)paren
suffix:semicolon
id|hose-&gt;io_space
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|hose-&gt;mem_space
op_assign
op_amp
id|iomem_resource
suffix:semicolon
id|hose-&gt;index
op_assign
l_int|0
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
id|IRONGATE_MEM
op_amp
l_int|0xffffffffff
)paren
op_or
l_int|0x80000000000
suffix:semicolon
id|hose-&gt;dense_io_base
op_assign
(paren
id|IRONGATE_IO
op_amp
l_int|0xffffffffff
)paren
op_or
l_int|0x80000000000
suffix:semicolon
id|hose-&gt;sg_isa
op_assign
id|hose-&gt;sg_pci
op_assign
l_int|NULL
suffix:semicolon
id|__direct_map_base
op_assign
l_int|0
suffix:semicolon
id|__direct_map_size
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
multiline_comment|/*&n; * IO map and AGP support&n; */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/agpgart.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|macro|GET_PAGE_DIR_OFF
mdefine_line|#define GET_PAGE_DIR_OFF(addr) (addr &gt;&gt; 22)
DECL|macro|GET_PAGE_DIR_IDX
mdefine_line|#define GET_PAGE_DIR_IDX(addr) (GET_PAGE_DIR_OFF(addr))
DECL|macro|GET_GATT_OFF
mdefine_line|#define GET_GATT_OFF(addr) ((addr &amp; 0x003ff000) &gt;&gt; 12) 
DECL|macro|GET_GATT
mdefine_line|#define GET_GATT(addr) (gatt_pages[GET_PAGE_DIR_IDX(addr)])
r_int
r_int
DECL|function|irongate_ioremap
id|irongate_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
r_int
r_int
id|baddr
comma
id|last
suffix:semicolon
id|u32
op_star
id|mmio_regs
comma
op_star
id|gatt_pages
comma
op_star
id|cur_gatt
comma
id|pte
suffix:semicolon
r_int
r_int
id|gart_bus_addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alpha_agpgart_size
)paren
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
id|gart_bus_addr
op_assign
(paren
r_int
r_int
)paren
id|IRONGATE0-&gt;bar0
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
multiline_comment|/* &n;&t; * Check for within the AGP aperture...&n;&t; */
r_do
(brace
multiline_comment|/*&n;&t;&t; * Check the AGP area&n;&t;&t; */
r_if
c_cond
(paren
id|addr
op_ge
id|gart_bus_addr
op_logical_and
id|addr
op_plus
id|size
op_minus
l_int|1
OL
id|gart_bus_addr
op_plus
id|alpha_agpgart_size
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Not found - assume legacy ioremap&n;&t;&t; */
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|mmio_regs
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|IRONGATE0-&gt;bar1
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
op_plus
id|IRONGATE_MEM
)paren
suffix:semicolon
id|gatt_pages
op_assign
(paren
id|u32
op_star
)paren
(paren
id|phys_to_virt
c_func
(paren
id|mmio_regs
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME */
multiline_comment|/*&n;&t; * Adjust the limits (mappings must be page aligned)&n;&t; */
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AGP ioremap failed... addr not page aligned (0x%lx)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
)brace
id|last
op_assign
id|addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last
)paren
op_minus
id|addr
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|addr
comma
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  gart_bus_addr  0x%lx&bslash;n&quot;
comma
id|gart_bus_addr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  gart_aper_size 0x%lx&bslash;n&quot;
comma
id|gart_aper_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  mmio_regs      %p&bslash;n&quot;
comma
id|mmio_regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  gatt_pages     %p&bslash;n&quot;
comma
id|gatt_pages
)paren
suffix:semicolon
r_for
c_loop
(paren
id|baddr
op_assign
id|addr
suffix:semicolon
id|baddr
op_le
id|last
suffix:semicolon
id|baddr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|cur_gatt
op_assign
id|phys_to_virt
c_func
(paren
id|GET_GATT
c_func
(paren
id|baddr
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|pte
op_assign
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|baddr
)paren
)braket
op_amp
op_complement
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap:  cur_gatt %p pte 0x%x&bslash;n&quot;
comma
id|cur_gatt
comma
id|pte
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Map it&n;&t; */
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
(paren
r_int
r_int
)paren
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|baddr
op_assign
id|addr
comma
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
suffix:semicolon
id|baddr
op_le
id|last
suffix:semicolon
id|baddr
op_add_assign
id|PAGE_SIZE
comma
id|vaddr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|cur_gatt
op_assign
id|phys_to_virt
c_func
(paren
id|GET_GATT
c_func
(paren
id|baddr
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|pte
op_assign
id|cur_gatt
(braket
id|GET_GATT_OFF
c_func
(paren
id|baddr
)paren
)braket
op_amp
op_complement
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|__alpha_remap_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|vaddr
)paren
comma
id|pte
comma
id|PAGE_SIZE
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AGP ioremap: FAILED to map...&bslash;n&quot;
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
l_int|NULL
suffix:semicolon
)brace
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;irongate_ioremap(0x%lx, 0x%lx) returning 0x%lx&bslash;n&quot;
comma
id|addr
comma
id|size
comma
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
r_return
id|vaddr
suffix:semicolon
)brace
r_void
DECL|function|irongate_iounmap
id|irongate_iounmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|addr
op_rshift
l_int|41
)paren
op_eq
op_minus
l_int|2
)paren
r_return
suffix:semicolon
multiline_comment|/* kseg map, nothing to do */
r_if
c_cond
(paren
id|addr
)paren
r_return
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|PAGE_MASK
op_amp
id|addr
)paren
)paren
suffix:semicolon
)brace
eof
