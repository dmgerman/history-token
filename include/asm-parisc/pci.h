macro_line|#ifndef __ASM_PARISC_PCI_H
DECL|macro|__ASM_PARISC_PCI_H
mdefine_line|#define __ASM_PARISC_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/*&n;** HP PCI platforms generally support multiple bus adapters.&n;**    (workstations 1-~4, servers 2-~32)&n;**&n;** Newer platforms number the busses across PCI bus adapters *sparsely*.&n;** E.g. 0, 8, 16, ...&n;**&n;** Under a PCI bus, most HP platforms support PPBs up to two or three&n;** levels deep. See &quot;Bit3&quot; product line. &n;*/
DECL|macro|PCI_MAX_BUSSES
mdefine_line|#define PCI_MAX_BUSSES&t;256
multiline_comment|/*&n;** pci_hba_data (aka H2P_OBJECT in HP/UX)&n;**&n;** This is the &quot;common&quot; or &quot;base&quot; data structure which HBA drivers&n;** (eg Dino or LBA) are required to place at the top of their own&n;** platform_data structure.  I&squot;ve heard this called &quot;C inheritance&quot; too.&n;**&n;** Data needed by pcibios layer belongs here.&n;*/
DECL|struct|pci_hba_data
r_struct
id|pci_hba_data
(brace
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
multiline_comment|/* aka Host Physical Address */
DECL|member|dev
r_const
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* device from PA bus walk */
DECL|member|hba_bus
r_struct
id|pci_bus
op_star
id|hba_bus
suffix:semicolon
multiline_comment|/* primary PCI bus below HBA */
DECL|member|hba_num
r_int
id|hba_num
suffix:semicolon
multiline_comment|/* I/O port space access &quot;key&quot; */
DECL|member|bus_num
r_struct
id|resource
id|bus_num
suffix:semicolon
multiline_comment|/* PCI bus numbers */
DECL|member|io_space
r_struct
id|resource
id|io_space
suffix:semicolon
multiline_comment|/* PIOP */
DECL|member|lmmio_space
r_struct
id|resource
id|lmmio_space
suffix:semicolon
multiline_comment|/* bus addresses &lt; 4Gb */
DECL|member|elmmio_space
r_struct
id|resource
id|elmmio_space
suffix:semicolon
multiline_comment|/* additional bus addresses &lt; 4Gb */
DECL|member|gmmio_space
r_struct
id|resource
id|gmmio_space
suffix:semicolon
multiline_comment|/* bus addresses &gt; 4Gb */
multiline_comment|/* NOTE: Dino code assumes it can use *all* of the lmmio_space,&n;&t; * elmmio_space and gmmio_space as a contiguous array of&n;&t; * resources.  This #define represents the array size */
DECL|macro|DINO_MAX_LMMIO_RESOURCES
mdefine_line|#define DINO_MAX_LMMIO_RESOURCES&t;3
DECL|member|lmmio_space_offset
r_int
r_int
id|lmmio_space_offset
suffix:semicolon
multiline_comment|/* CPU view - PCI view */
DECL|member|iommu
r_void
op_star
id|iommu
suffix:semicolon
multiline_comment|/* IOMMU this device is under */
multiline_comment|/* REVISIT - spinlock to protect resources? */
DECL|macro|HBA_NAME_SIZE
mdefine_line|#define HBA_NAME_SIZE 16
DECL|member|io_name
r_char
id|io_name
(braket
id|HBA_NAME_SIZE
)braket
suffix:semicolon
DECL|member|lmmio_name
r_char
id|lmmio_name
(braket
id|HBA_NAME_SIZE
)braket
suffix:semicolon
DECL|member|elmmio_name
r_char
id|elmmio_name
(braket
id|HBA_NAME_SIZE
)braket
suffix:semicolon
DECL|member|gmmio_name
r_char
id|gmmio_name
(braket
id|HBA_NAME_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HBA_DATA
mdefine_line|#define HBA_DATA(d)&t;&t;((struct pci_hba_data *) (d))
multiline_comment|/* &n;** We support 2^16 I/O ports per HBA.  These are set up in the form&n;** 0xbbxxxx, where bb is the bus number and xxxx is the I/O port&n;** space address.&n;*/
DECL|macro|HBA_PORT_SPACE_BITS
mdefine_line|#define HBA_PORT_SPACE_BITS&t;16
DECL|macro|HBA_PORT_BASE
mdefine_line|#define HBA_PORT_BASE(h)&t;((h) &lt;&lt; HBA_PORT_SPACE_BITS)
DECL|macro|HBA_PORT_SPACE_SIZE
mdefine_line|#define HBA_PORT_SPACE_SIZE&t;(1UL &lt;&lt; HBA_PORT_SPACE_BITS)
DECL|macro|PCI_PORT_HBA
mdefine_line|#define PCI_PORT_HBA(a)&t;&t;((a) &gt;&gt; HBA_PORT_SPACE_BITS)
DECL|macro|PCI_PORT_ADDR
mdefine_line|#define PCI_PORT_ADDR(a)&t;((a) &amp; (HBA_PORT_SPACE_SIZE - 1))
macro_line|#if CONFIG_PARISC64
DECL|macro|PCI_F_EXTEND
mdefine_line|#define PCI_F_EXTEND&t;&t;0xffffffff00000000UL
DECL|macro|PCI_IS_LMMIO
mdefine_line|#define PCI_IS_LMMIO(hba,a)&t;pci_is_lmmio(hba,a)
multiline_comment|/* We need to know if an address is LMMMIO or GMMIO.&n; * LMMIO requires mangling and GMMIO we must use as-is.&n; */
DECL|function|pci_is_lmmio
r_static
id|__inline__
r_int
id|pci_is_lmmio
c_func
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
r_int
r_int
id|a
)paren
(brace
r_return
(paren
(paren
id|a
)paren
op_amp
id|PCI_F_EXTEND
)paren
op_eq
id|PCI_F_EXTEND
suffix:semicolon
)brace
multiline_comment|/*&n;** Convert between PCI (IO_VIEW) addresses and processor (PA_VIEW) addresses.&n;** See pcibios.c for more conversions used by Generic PCI code.&n;*/
DECL|macro|PCI_BUS_ADDR
mdefine_line|#define PCI_BUS_ADDR(hba,a)&t;(PCI_IS_LMMIO(hba,a)&t;&bslash;&n;&t;&t;?  ((a) - hba-&gt;lmmio_space_offset)&t;/* mangle LMMIO */ &bslash;&n;&t;&t;: (a))&t;&t;&t;&t;&t;/* GMMIO */
DECL|macro|PCI_HOST_ADDR
mdefine_line|#define PCI_HOST_ADDR(hba,a)&t;((a) + hba-&gt;lmmio_space_offset)
macro_line|#else&t;/* !CONFIG_PARISC64 */
DECL|macro|PCI_BUS_ADDR
mdefine_line|#define PCI_BUS_ADDR(hba,a)&t;(a)
DECL|macro|PCI_HOST_ADDR
mdefine_line|#define PCI_HOST_ADDR(hba,a)&t;(a)
DECL|macro|PCI_F_EXTEND
mdefine_line|#define PCI_F_EXTEND&t;&t;0UL
DECL|macro|PCI_IS_LMMIO
mdefine_line|#define PCI_IS_LMMIO(hba,a)&t;(1)&t;/* 32-bit doesn&squot;t support GMMIO */
macro_line|#endif /* !CONFIG_PARISC64 */
multiline_comment|/*&n;** KLUGE: linux/pci.h include asm/pci.h BEFORE declaring struct pci_bus&n;** (This eliminates some of the warnings).&n;*/
r_struct
id|pci_bus
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS     (1)
multiline_comment|/*&n;** Most PCI devices (eg Tulip, NCR720) also export the same registers&n;** to both MMIO and I/O port space.  Due to poor performance of I/O Port&n;** access under HP PCI bus adapters, strongly reccomend use of MMIO&n;** address space.&n;**&n;** While I&squot;m at it more PA programming notes:&n;**&n;** 1) MMIO stores (writes) are posted operations. This means the processor&n;**    gets an &quot;ACK&quot; before the write actually gets to the device. A read&n;**    to the same device (or typically the bus adapter above it) will&n;**    force in-flight write transaction(s) out to the targeted device&n;**    before the read can complete.&n;**&n;** 2) The Programmed I/O (PIO) data may not always be strongly ordered with&n;**    respect to DMA on all platforms. Ie PIO data can reach the processor&n;**    before in-flight DMA reaches memory. Since most SMP PA platforms&n;**    are I/O coherent, it generally doesn&squot;t matter...but sometimes&n;**    it does.&n;**&n;** I&squot;ve helped device driver writers debug both types of problems.&n;*/
DECL|struct|pci_port_ops
r_struct
id|pci_port_ops
(brace
DECL|member|inb
id|u8
(paren
op_star
id|inb
)paren
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
id|u16
id|port
)paren
suffix:semicolon
DECL|member|inw
id|u16
(paren
op_star
id|inw
)paren
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
id|u16
id|port
)paren
suffix:semicolon
DECL|member|inl
id|u32
(paren
op_star
id|inl
)paren
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
id|u16
id|port
)paren
suffix:semicolon
DECL|member|outb
r_void
(paren
op_star
id|outb
)paren
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
id|u16
id|port
comma
id|u8
id|data
)paren
suffix:semicolon
DECL|member|outw
r_void
(paren
op_star
id|outw
)paren
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
id|u16
id|port
comma
id|u16
id|data
)paren
suffix:semicolon
DECL|member|outl
r_void
(paren
op_star
id|outl
)paren
(paren
r_struct
id|pci_hba_data
op_star
id|hba
comma
id|u16
id|port
comma
id|u32
id|data
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_bios_ops
r_struct
id|pci_bios_ops
(brace
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|fixup_bus
r_void
(paren
op_star
id|fixup_bus
)paren
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* pci_unmap_{single,page} is not a nop, thus... */
DECL|macro|DECLARE_PCI_UNMAP_ADDR
mdefine_line|#define DECLARE_PCI_UNMAP_ADDR(ADDR_NAME)&t;&bslash;&n;&t;dma_addr_t ADDR_NAME;
DECL|macro|DECLARE_PCI_UNMAP_LEN
mdefine_line|#define DECLARE_PCI_UNMAP_LEN(LEN_NAME)&t;&t;&bslash;&n;&t;__u32 LEN_NAME;
DECL|macro|pci_unmap_addr
mdefine_line|#define pci_unmap_addr(PTR, ADDR_NAME)&t;&t;&t;&bslash;&n;&t;((PTR)-&gt;ADDR_NAME)
DECL|macro|pci_unmap_addr_set
mdefine_line|#define pci_unmap_addr_set(PTR, ADDR_NAME, VAL)&t;&t;&bslash;&n;&t;(((PTR)-&gt;ADDR_NAME) = (VAL))
DECL|macro|pci_unmap_len
mdefine_line|#define pci_unmap_len(PTR, LEN_NAME)&t;&t;&t;&bslash;&n;&t;((PTR)-&gt;LEN_NAME)
DECL|macro|pci_unmap_len_set
mdefine_line|#define pci_unmap_len_set(PTR, LEN_NAME, VAL)&t;&t;&bslash;&n;&t;(((PTR)-&gt;LEN_NAME) = (VAL))
multiline_comment|/*&n;** Stuff declared in arch/parisc/kernel/pci.c&n;*/
r_extern
r_struct
id|pci_port_ops
op_star
id|pci_port
suffix:semicolon
r_extern
r_struct
id|pci_bios_ops
op_star
id|pci_bios
suffix:semicolon
r_extern
r_int
id|pci_post_reset_delay
suffix:semicolon
multiline_comment|/* delay after de-asserting #RESET */
r_extern
r_int
id|pci_hba_count
suffix:semicolon
r_extern
r_struct
id|pci_hba_data
op_star
id|parisc_pci_hba
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_void
id|pcibios_register_hba
c_func
(paren
r_struct
id|pci_hba_data
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|function|pcibios_register_hba
r_extern
r_inline
r_void
id|pcibios_register_hba
c_func
(paren
r_struct
id|pci_hba_data
op_star
id|x
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*&n;** used by drivers/pci/pci.c:pci_do_scan_bus()&n;**   0 == check if bridge is numbered before re-numbering.&n;**   1 == pci_do_scan_bus() should automatically number all PCI-PCI bridges.&n;**&n;** REVISIT:&n;**   To date, only alpha sets this to one. We&squot;ll need to set this&n;**   to zero for legacy platforms and one for PAT platforms.&n;*/
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()     (pdc_type == PDC_TYPE_PAT)
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO          0x10
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM         0x1000 /* NBPG - but pci/setup-res.c dies */
multiline_comment|/* Don&squot;t support DAC yet. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)   (0)
multiline_comment|/* export the pci_ DMA API in terms of the dma_ one */
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
r_extern
r_void
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
suffix:semicolon
DECL|function|pcibios_add_platform_entries
r_static
r_inline
r_void
id|pcibios_add_platform_entries
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* __ASM_PARISC_PCI_H */
eof
