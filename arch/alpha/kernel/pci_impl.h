multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/pci_impl.h&n; *&n; * This file contains declarations and inline functions for interfacing&n; * with the PCI initialization routines.&n; */
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|pci_controller
suffix:semicolon
r_struct
id|pci_iommu_arena
suffix:semicolon
multiline_comment|/*&n; * We can&squot;t just blindly use 64K for machines with EISA busses; they&n; * may also have PCI-PCI bridges present, and then we&squot;d configure the&n; * bridge incorrectly.&n; *&n; * Also, we start at 0x8000 or 0x9000, in hopes to get all devices&squot;&n; * IO space areas allocated *before* 0xC000; this is because certain&n; * BIOSes (Millennium for one) use PCI Config space &quot;mechanism #2&quot;&n; * accesses to probe the bus. If a device&squot;s registers appear at 0xC000,&n; * it may see an INx/OUTx at that address during BIOS emulation of the&n; * VGA BIOS, and some cards, notably Adaptec 2940UW, take mortal offense.&n; */
DECL|macro|EISA_DEFAULT_IO_BASE
mdefine_line|#define EISA_DEFAULT_IO_BASE&t;0x9000&t;/* start above 8th slot */
DECL|macro|DEFAULT_IO_BASE
mdefine_line|#define DEFAULT_IO_BASE&t;&t;0x8000&t;/* start at 8th slot */
multiline_comment|/*&n; * We try to make the DEFAULT_MEM_BASE addresses *always* have more than&n; * a single bit set. This is so that devices like the broken Myrinet card&n; * will always have a PCI memory address that will never match a IDSEL&n; * address in PCI Config space, which can cause problems with early rev cards.&n; */
multiline_comment|/*&n; * An XL is AVANTI (APECS) family, *but* it has only 27 bits of ISA address&n; * that get passed through the PCI&lt;-&gt;ISA bridge chip. Although this causes&n; * us to set the PCI-&gt;Mem window bases lower than normal, we still allocate&n; * PCI bus devices&squot; memory addresses *below* the low DMA mapping window,&n; * and hope they fit below 64Mb (to avoid conflicts), and so that they can&n; * be accessed via SPARSE space.&n; *&n; * We accept the risk that a broken Myrinet card will be put into a true XL&n; * and thus can more easily run into the problem described below.&n; */
DECL|macro|XL_DEFAULT_MEM_BASE
mdefine_line|#define XL_DEFAULT_MEM_BASE ((16+2)*1024*1024) /* 16M to 64M-1 is avail */
multiline_comment|/*&n; * APECS and LCA have only 34 bits for physical addresses, thus limiting PCI&n; * bus memory addresses for SPARSE access to be less than 128Mb.&n; */
DECL|macro|APECS_AND_LCA_DEFAULT_MEM_BASE
mdefine_line|#define APECS_AND_LCA_DEFAULT_MEM_BASE ((16+2)*1024*1024)
multiline_comment|/*&n; * Because MCPCIA and T2 core logic support more bits for&n; * physical addresses, they should allow an expanded range of SPARSE&n; * memory addresses.  However, we do not use them all, in order to&n; * avoid the HAE manipulation that would be needed.&n; */
DECL|macro|MCPCIA_DEFAULT_MEM_BASE
mdefine_line|#define MCPCIA_DEFAULT_MEM_BASE ((32+2)*1024*1024)
DECL|macro|T2_DEFAULT_MEM_BASE
mdefine_line|#define T2_DEFAULT_MEM_BASE ((16+1)*1024*1024)
multiline_comment|/*&n; * Because CIA and PYXIS have more bits for physical addresses,&n; * they support an expanded range of SPARSE memory addresses.&n; */
DECL|macro|DEFAULT_MEM_BASE
mdefine_line|#define DEFAULT_MEM_BASE ((128+16)*1024*1024)
multiline_comment|/* ??? Experimenting with no HAE for CIA.  */
DECL|macro|CIA_DEFAULT_MEM_BASE
mdefine_line|#define CIA_DEFAULT_MEM_BASE ((32+2)*1024*1024)
DECL|macro|IRONGATE_DEFAULT_MEM_BASE
mdefine_line|#define IRONGATE_DEFAULT_MEM_BASE ((256*8-16)*1024*1024)
DECL|macro|DEFAULT_AGP_APER_SIZE
mdefine_line|#define DEFAULT_AGP_APER_SIZE&t;(64*1024*1024)
multiline_comment|/* &n; * A small note about bridges and interrupts.  The DECchip 21050 (and&n; * later) adheres to the PCI-PCI bridge specification.  This says that&n; * the interrupts on the other side of a bridge are swizzled in the&n; * following manner:&n; *&n; * Dev    Interrupt   Interrupt &n; *        Pin on      Pin on &n; *        Device      Connector&n; *&n; *   4    A           A&n; *        B           B&n; *        C           C&n; *        D           D&n; * &n; *   5    A           B&n; *        B           C&n; *        C           D&n; *        D           A&n; *&n; *   6    A           C&n; *        B           D&n; *        C           A&n; *        D           B&n; *&n; *   7    A           D&n; *        B           A&n; *        C           B&n; *        D           C&n; *&n; *   Where A = pin 1, B = pin 2 and so on and pin=0 = default = A.&n; *   Thus, each swizzle is ((pin-1) + (device#-4)) % 4&n; *&n; *   The following code swizzles for exactly one bridge.  The routine&n; *   common_swizzle below handles multiple bridges.  But there are a&n; *   couple boards that do strange things, so we define this here.&n; */
DECL|function|bridge_swizzle
r_static
r_inline
id|u8
id|bridge_swizzle
c_func
(paren
id|u8
id|pin
comma
id|u8
id|slot
)paren
(brace
r_return
(paren
(paren
(paren
id|pin
op_minus
l_int|1
)paren
op_plus
id|slot
)paren
op_mod
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* The following macro is used to implement the table-based irq mapping&n;   function for all single-bus Alphas.  */
DECL|macro|COMMON_TABLE_LOOKUP
mdefine_line|#define COMMON_TABLE_LOOKUP&t;&t;&t;&t;&t;&t;&bslash;&n;({ long _ctl_ = -1; &t;&t;&t;&t;&t;&t;&t;&bslash;&n;   if (slot &gt;= min_idsel &amp;&amp; slot &lt;= max_idsel &amp;&amp; pin &lt; irqs_per_slot)&t;&bslash;&n;     _ctl_ = irq_tab[slot - min_idsel][pin];&t;&t;&t;&t;&bslash;&n;   _ctl_; })
multiline_comment|/* A PCI IOMMU allocation arena.  There are typically two of these&n;   regions per bus.  */
multiline_comment|/* ??? The 8400 has a 32-byte pte entry, and the entire table apparently&n;   lives directly on the host bridge (no tlb?).  We don&squot;t support this&n;   machine, but if we ever did, we&squot;d need to parameterize all this quite&n;   a bit further.  Probably with per-bus operation tables.  */
DECL|struct|pci_iommu_arena
r_struct
id|pci_iommu_arena
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|hose
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
DECL|macro|IOMMU_INVALID_PTE
mdefine_line|#define IOMMU_INVALID_PTE 0x2 /* 32:63 bits MBZ */
DECL|macro|IOMMU_RESERVED_PTE
mdefine_line|#define IOMMU_RESERVED_PTE 0xface
DECL|member|ptes
r_int
r_int
op_star
id|ptes
suffix:semicolon
DECL|member|dma_base
id|dma_addr_t
id|dma_base
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|next_entry
r_int
r_int
id|next_entry
suffix:semicolon
DECL|member|align_entry
r_int
r_int
id|align_entry
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_ALPHA_SRM) &amp;&amp; &bslash;&n;    (defined(CONFIG_ALPHA_CIA) || defined(CONFIG_ALPHA_LCA))
DECL|macro|NEED_SRM_SAVE_RESTORE
macro_line|# define NEED_SRM_SAVE_RESTORE
macro_line|#else
DECL|macro|NEED_SRM_SAVE_RESTORE
macro_line|# undef NEED_SRM_SAVE_RESTORE
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(NEED_SRM_SAVE_RESTORE)
DECL|macro|ALPHA_RESTORE_SRM_SETUP
macro_line|# define ALPHA_RESTORE_SRM_SETUP
macro_line|#else
DECL|macro|ALPHA_RESTORE_SRM_SETUP
macro_line|# undef ALPHA_RESTORE_SRM_SETUP
macro_line|#endif
macro_line|#ifdef ALPHA_RESTORE_SRM_SETUP
multiline_comment|/* Store PCI device configuration left by SRM here. */
DECL|struct|pdev_srm_saved_conf
r_struct
id|pdev_srm_saved_conf
(brace
DECL|member|next
r_struct
id|pdev_srm_saved_conf
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|pci_restore_srm_config
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|pdev_save_srm_config
mdefine_line|#define pdev_save_srm_config(dev)&t;do {} while (0)
DECL|macro|pci_restore_srm_config
mdefine_line|#define pci_restore_srm_config()&t;do {} while (0)
macro_line|#endif
multiline_comment|/* The hose list.  */
r_extern
r_struct
id|pci_controller
op_star
id|hose_head
comma
op_star
op_star
id|hose_tail
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|pci_isa_hose
suffix:semicolon
multiline_comment|/* Indicate that we trust the console to configure things properly.  */
r_extern
r_int
id|pci_probe_only
suffix:semicolon
r_extern
r_int
r_int
id|alpha_agpgart_size
suffix:semicolon
r_extern
r_void
id|common_init_pci
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u8
id|common_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|alloc_pci_controller
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|resource
op_star
id|alloc_resource
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|pci_iommu_arena
op_star
id|iommu_arena_new_node
c_func
(paren
r_int
comma
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|pci_iommu_arena
op_star
id|iommu_arena_new
c_func
(paren
r_struct
id|pci_controller
op_star
comma
id|dma_addr_t
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
r_const
id|pci_io_names
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
op_star
r_const
id|pci_mem_names
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|pci_hae0_name
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|size_for_memory
c_func
(paren
r_int
r_int
id|max
)paren
suffix:semicolon
r_extern
r_int
id|iommu_reserve
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|iommu_release
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|iommu_bind
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
comma
r_int
comma
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|iommu_unbind
c_func
(paren
r_struct
id|pci_iommu_arena
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
eof
