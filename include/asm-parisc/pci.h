macro_line|#ifndef __ASM_PARISC_PCI_H
DECL|macro|__ASM_PARISC_PCI_H
mdefine_line|#define __ASM_PARISC_PCI_H
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/*&n;** HP PCI platforms generally support multiple bus adapters.&n;**    (workstations 1-~4, servers 2-~32)&n;**&n;** Newer platforms number the busses across PCI bus adapters *sparsely*.&n;** E.g. 0, 8, 16, ...&n;**&n;** Under a PCI bus, most HP platforms support PPBs up to two or three&n;** levels deep. See &quot;Bit3&quot; product line. &n;*/
DECL|macro|PCI_MAX_BUSSES
mdefine_line|#define PCI_MAX_BUSSES&t;256
multiline_comment|/* [soapbox on]&n;** Who the hell can develop stuff without ASSERT or VASSERT?&n;** No one understands all the modules across all platforms.&n;** For linux add another dimension - processor architectures.&n;**&n;** This should be a standard/global macro used liberally&n;** in all code. Every respectable engineer I know in HP&n;** would support this argument. - grant&n;** [soapbox off]&n;*/
macro_line|#ifdef PCI_DEBUG
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr) &bslash;&n;&t;if(!(expr)) { &bslash;&n;&t;&t;printk( &quot;&bslash;n&quot; __FILE__ &quot;:%d: Assertion &quot; #expr &quot; failed!&bslash;n&quot;,__LINE__); &bslash;&n;&t;&t;panic(#expr); &bslash;&n;&t;}
macro_line|#else
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr)
macro_line|#endif
multiline_comment|/*&n;** pci_hba_data (aka H2P_OBJECT in HP/UX)&n;**&n;** This is the &quot;common&quot; or &quot;base&quot; data structure which HBA drivers&n;** (eg Dino or LBA) are required to place at the top of their own&n;** dev-&gt;sysdata structure.  I&squot;ve heard this called &quot;C inheritance&quot; too.&n;**&n;** Data needed by pcibios layer belongs here.&n;*/
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
multiline_comment|/*&n;** Convert between PCI (IO_VIEW) addresses and processor (PA_VIEW) addresses.&n;** Note that we currently support only LMMIO.&n;*/
DECL|macro|PCI_BUS_ADDR
mdefine_line|#define PCI_BUS_ADDR(hba,a)&t;((a) - hba-&gt;lmmio_space_offset)
DECL|macro|PCI_HOST_ADDR
mdefine_line|#define PCI_HOST_ADDR(hba,a)&t;((a) + hba-&gt;lmmio_space_offset)
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
multiline_comment|/*&n;** See Documentation/DMA-mapping.txt&n;*/
DECL|struct|pci_dma_ops
r_struct
id|pci_dma_ops
(brace
DECL|member|dma_supported
r_int
(paren
op_star
id|dma_supported
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
suffix:semicolon
DECL|member|alloc_consistent
r_void
op_star
(paren
op_star
id|alloc_consistent
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|iova
)paren
suffix:semicolon
DECL|member|free_consistent
r_void
(paren
op_star
id|free_consistent
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|iova
)paren
suffix:semicolon
DECL|member|map_single
id|dma_addr_t
(paren
op_star
id|map_single
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|unmap_single
r_void
(paren
op_star
id|unmap_single
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|dma_addr_t
id|iova
comma
r_int
id|size
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|map_sg
r_int
(paren
op_star
id|map_sg
)paren
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
id|nents
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|unmap_sg
r_void
(paren
op_star
id|unmap_sg
)paren
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
id|nhwents
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|dma_sync_single
r_void
(paren
op_star
id|dma_sync_single
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|dma_addr_t
id|iova
comma
r_int
id|size
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|dma_sync_sg
r_void
(paren
op_star
id|dma_sync_sg
)paren
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
id|nelems
comma
r_int
id|direction
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;** We could live without the hppa_dma_ops indirection if we didn&squot;t want&n;** to support 4 different coherent dma models with one binary (they will&n;** someday be loadable modules):&n;**     I/O MMU        consistent method           dma_sync behavior&n;**  =============   ======================       =======================&n;**  a) PA-7x00LC    uncachable host memory          flush/purge&n;**  b) U2/Uturn      cachable host memory              NOP&n;**  c) Ike/Astro     cachable host memory              NOP&n;**  d) EPIC/SAGA     memory on EPIC/SAGA         flush/reset DMA channel&n;**&n;** PA-7[13]00LC processors have a GSC bus interface and no I/O MMU.&n;**&n;** Systems (eg PCX-T workstations) that don&squot;t fall into the above&n;** categories will need to modify the needed drivers to perform&n;** flush/purge and allocate &quot;regular&quot; cacheable pages for everything.&n;*/
r_extern
r_struct
id|pci_dma_ops
op_star
id|hppa_dma_ops
suffix:semicolon
macro_line|#ifdef CONFIG_PA11
r_extern
r_struct
id|pci_dma_ops
id|pcxl_dma_ops
suffix:semicolon
r_extern
r_struct
id|pci_dma_ops
id|pcx_dma_ops
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** Oops hard if we haven&squot;t setup hppa_dma_ops by the time the first driver&n;** attempts to initialize.&n;** Since panic() is a (void)(), pci_dma_panic() is needed to satisfy&n;** the (int)() required by pci_dma_supported() interface.&n;*/
DECL|function|pci_dma_panic
r_static
r_inline
r_int
id|pci_dma_panic
c_func
(paren
r_char
op_star
id|msg
)paren
(brace
r_extern
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* linux/kernel.h */
id|panic
c_func
(paren
id|msg
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|macro|pci_dma_supported
mdefine_line|#define pci_dma_supported(p, m)&t;( &bslash;&n;&t;(NULL == hppa_dma_ops) &bslash;&n;&t;?  pci_dma_panic(&quot;Dynamic DMA support missing...OOPS!&bslash;n(Hint: was Astro/Ike/U2/Uturn not claimed?)&bslash;n&quot;) &bslash;&n;&t;: hppa_dma_ops-&gt;dma_supported(p,m) &bslash;&n;)
DECL|macro|pci_alloc_consistent
mdefine_line|#define pci_alloc_consistent(p, s, a)&t;hppa_dma_ops-&gt;alloc_consistent(p,s,a)
DECL|macro|pci_free_consistent
mdefine_line|#define pci_free_consistent(p, s, v, a)&t;hppa_dma_ops-&gt;free_consistent(p,s,v,a)
DECL|macro|pci_map_single
mdefine_line|#define pci_map_single(p, v, s, d)&t;hppa_dma_ops-&gt;map_single(p, v, s, d)
DECL|macro|pci_unmap_single
mdefine_line|#define pci_unmap_single(p, a, s, d)&t;hppa_dma_ops-&gt;unmap_single(p, a, s, d)
DECL|macro|pci_map_sg
mdefine_line|#define pci_map_sg(p, sg, n, d)&t;&t;hppa_dma_ops-&gt;map_sg(p, sg, n, d)
DECL|macro|pci_unmap_sg
mdefine_line|#define pci_unmap_sg(p, sg, n, d)&t;hppa_dma_ops-&gt;unmap_sg(p, sg, n, d)
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
multiline_comment|/* For U2/Astro/Ike based platforms (which are fully I/O coherent)&n;** dma_sync is a NOP. Let&squot;s keep the performance path short here.&n;*/
DECL|macro|pci_dma_sync_single
mdefine_line|#define pci_dma_sync_single(p, a, s, d)&t;{ if (hppa_dma_ops-&gt;dma_sync_single) &bslash;&n;&t;hppa_dma_ops-&gt;dma_sync_single(p, a, s, d); &bslash;&n;&t;}
DECL|macro|pci_dma_sync_sg
mdefine_line|#define pci_dma_sync_sg(p, sg, n, d)&t;{ if (hppa_dma_ops-&gt;dma_sync_sg) &bslash;&n;&t;hppa_dma_ops-&gt;dma_sync_sg(p, sg, n, d); &bslash;&n;&t;}
multiline_comment|/* No highmem on parisc, plus we have an IOMMU, so mapping pages is easy. */
DECL|macro|pci_map_page
mdefine_line|#define pci_map_page(dev, page, off, size, dir) &bslash;&n;&t;pci_map_single(dev, (page_address(page) + (off)), size, dir)
DECL|macro|pci_unmap_page
mdefine_line|#define pci_unmap_page(dev,addr,sz,dir) pci_unmap_single(dev,addr,sz,dir)
multiline_comment|/* Don&squot;t support DAC yet. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(0)
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
r_extern
r_void
id|pcibios_assign_unassigned_resources
c_func
(paren
r_struct
id|pci_bus
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
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO          0x10
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM         0x1000 /* NBPG - but pci/setup-res.c dies */
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
DECL|macro|pci_controller_num
mdefine_line|#define pci_controller_num(PDEV)&t;(0)
DECL|macro|GET_IOC
mdefine_line|#define GET_IOC(dev) ((struct ioc *)(HBA_DATA(dev-&gt;sysdata)-&gt;iommu))
macro_line|#ifdef CONFIG_IOMMU_CCIO
r_struct
id|parisc_device
suffix:semicolon
r_struct
id|ioc
suffix:semicolon
r_void
op_star
id|ccio_get_iommu
c_func
(paren
r_const
r_struct
id|parisc_device
op_star
id|dev
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|ccio_get_fake
c_func
(paren
r_const
r_struct
id|parisc_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|ccio_request_resource
c_func
(paren
r_const
r_struct
id|parisc_device
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
)paren
suffix:semicolon
r_int
id|ccio_allocate_resource
c_func
(paren
r_const
r_struct
id|parisc_device
op_star
id|dev
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
id|min
comma
r_int
r_int
id|max
comma
r_int
r_int
id|align
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_IOMMU_CCIO */
DECL|macro|ccio_get_iommu
mdefine_line|#define ccio_get_iommu(dev) NULL
DECL|macro|ccio_get_fake
mdefine_line|#define ccio_get_fake(dev) NULL
DECL|macro|ccio_request_resource
mdefine_line|#define ccio_request_resource(dev, res) request_resource(&amp;iomem_resource, res)
DECL|macro|ccio_allocate_resource
mdefine_line|#define ccio_allocate_resource(dev, res, size, min, max, align, alignf, data) &bslash;&n;&t;&t;allocate_resource(&amp;iomem_resource, res, size, min, max, &bslash;&n;&t;&t;&t;&t;align, alignf, data)
macro_line|#endif /* !CONFIG_IOMMU_CCIO */
macro_line|#ifdef CONFIG_IOMMU_SBA
r_struct
id|parisc_device
suffix:semicolon
r_void
op_star
id|sba_get_iommu
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_PARISC_PCI_H */
eof
