multiline_comment|/*&n; * PowerPC memory management structures&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_MMU_H_
DECL|macro|_PPC_MMU_H_
mdefine_line|#define _PPC_MMU_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Default &quot;unsigned long&quot; context */
DECL|typedef|mm_context_t
r_typedef
r_int
r_int
id|mm_context_t
suffix:semicolon
multiline_comment|/* Hardware Page Table Entry */
DECL|struct|_PTE
r_typedef
r_struct
id|_PTE
(brace
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|member|vsid
r_int
r_int
r_int
id|vsid
suffix:colon
l_int|52
suffix:semicolon
DECL|member|api
r_int
r_int
id|api
suffix:colon
l_int|5
suffix:semicolon
r_int
r_int
suffix:colon
l_int|5
suffix:semicolon
DECL|member|h
r_int
r_int
id|h
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rpn
r_int
r_int
r_int
id|rpn
suffix:colon
l_int|52
suffix:semicolon
macro_line|#else /* CONFIG_PPC64BRIDGE */
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Entry is valid */
r_int
r_int
id|vsid
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Virtual segment identifier */
r_int
r_int
id|h
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hash algorithm indicator */
r_int
r_int
id|api
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Abbreviated page index */
r_int
r_int
id|rpn
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* Real (physical) page number */
macro_line|#endif /* CONFIG_PPC64BRIDGE */
r_int
r_int
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Referenced */
DECL|member|c
r_int
r_int
id|c
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changed */
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write-thru cache mode */
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache inhibited */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Memory coherence */
DECL|member|g
r_int
r_int
id|g
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Guarded */
r_int
r_int
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|pp
r_int
r_int
id|pp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Page protection */
DECL|typedef|PTE
)brace
id|PTE
suffix:semicolon
multiline_comment|/* Values for PP (assumes Ks=0, Kp=1) */
DECL|macro|PP_RWXX
mdefine_line|#define PP_RWXX&t;0&t;/* Supervisor read/write, User none */
DECL|macro|PP_RWRX
mdefine_line|#define PP_RWRX 1&t;/* Supervisor read/write, User read */
DECL|macro|PP_RWRW
mdefine_line|#define PP_RWRW 2&t;/* Supervisor read/write, User read/write */
DECL|macro|PP_RXRX
mdefine_line|#define PP_RXRX 3&t;/* Supervisor read,       User read */
multiline_comment|/* Segment Register */
DECL|struct|_SEGREG
r_typedef
r_struct
id|_SEGREG
(brace
DECL|member|t
r_int
r_int
id|t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Normal or I/O  type */
DECL|member|ks
r_int
r_int
id|ks
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supervisor &squot;key&squot; (normally 0) */
DECL|member|kp
r_int
r_int
id|kp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* User &squot;key&squot; (normally 1) */
DECL|member|n
r_int
r_int
id|n
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* No-execute */
r_int
r_int
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|vsid
r_int
r_int
id|vsid
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Virtual Segment Identifier */
DECL|typedef|SEGREG
)brace
id|SEGREG
suffix:semicolon
multiline_comment|/* Block Address Translation (BAT) Registers */
DECL|struct|_P601_BATU
r_typedef
r_struct
id|_P601_BATU
(brace
multiline_comment|/* Upper part of BAT for 601 processor */
DECL|member|bepi
r_int
r_int
id|bepi
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Effective page index (virtual address) */
r_int
r_int
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* unused */
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache inhibit */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Memory coherence */
DECL|member|ks
r_int
r_int
id|ks
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supervisor key (normally 0) */
DECL|member|kp
r_int
r_int
id|kp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* User key (normally 1) */
DECL|member|pp
r_int
r_int
id|pp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Page access protections */
DECL|typedef|P601_BATU
)brace
id|P601_BATU
suffix:semicolon
DECL|struct|_BATU
r_typedef
r_struct
id|_BATU
(brace
multiline_comment|/* Upper part of BAT (all except 601) */
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|member|bepi
r_int
r_int
r_int
id|bepi
suffix:colon
l_int|47
suffix:semicolon
macro_line|#else /* CONFIG_PPC64BRIDGE */
r_int
r_int
id|bepi
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Effective page index (virtual address) */
macro_line|#endif /* CONFIG_PPC64BRIDGE */
r_int
r_int
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|bl
r_int
r_int
id|bl
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* Block size mask */
DECL|member|vs
r_int
r_int
id|vs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supervisor valid */
DECL|member|vp
r_int
r_int
id|vp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* User valid */
DECL|typedef|BATU
)brace
id|BATU
suffix:semicolon
DECL|struct|_P601_BATL
r_typedef
r_struct
id|_P601_BATL
(brace
multiline_comment|/* Lower part of BAT for 601 processor */
DECL|member|brpn
r_int
r_int
id|brpn
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Real page index (physical address) */
r_int
r_int
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Valid bit */
DECL|member|bl
r_int
r_int
id|bl
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Block size mask */
DECL|typedef|P601_BATL
)brace
id|P601_BATL
suffix:semicolon
DECL|struct|_BATL
r_typedef
r_struct
id|_BATL
(brace
multiline_comment|/* Lower part of BAT (all except 601) */
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|member|brpn
r_int
r_int
r_int
id|brpn
suffix:colon
l_int|47
suffix:semicolon
macro_line|#else /* CONFIG_PPC64BRIDGE */
r_int
r_int
id|brpn
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Real page index (physical address) */
macro_line|#endif /* CONFIG_PPC64BRIDGE */
r_int
r_int
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write-thru cache */
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache inhibit */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Memory coherence */
DECL|member|g
r_int
r_int
id|g
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Guarded (MBZ in IBAT) */
r_int
r_int
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|pp
r_int
r_int
id|pp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Page access protections */
DECL|typedef|BATL
)brace
id|BATL
suffix:semicolon
DECL|struct|_BAT
r_typedef
r_struct
id|_BAT
(brace
DECL|member|batu
id|BATU
id|batu
suffix:semicolon
multiline_comment|/* Upper register */
DECL|member|batl
id|BATL
id|batl
suffix:semicolon
multiline_comment|/* Lower register */
DECL|typedef|BAT
)brace
id|BAT
suffix:semicolon
DECL|struct|_P601_BAT
r_typedef
r_struct
id|_P601_BAT
(brace
DECL|member|batu
id|P601_BATU
id|batu
suffix:semicolon
multiline_comment|/* Upper register */
DECL|member|batl
id|P601_BATL
id|batl
suffix:semicolon
multiline_comment|/* Lower register */
DECL|typedef|P601_BAT
)brace
id|P601_BAT
suffix:semicolon
multiline_comment|/*&n; * Simulated two-level MMU.  This structure is used by the kernel&n; * to keep track of MMU mappings and is used to update/maintain&n; * the hardware HASH table which is really a cache of mappings.&n; *&n; * The simulated structures mimic the hardware available on other&n; * platforms, notably the 80x86 and 680x0.&n; */
DECL|struct|_pte
r_typedef
r_struct
id|_pte
(brace
DECL|member|page_num
r_int
r_int
id|page_num
suffix:colon
l_int|20
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Page flags (some unused bits) */
DECL|typedef|pte
)brace
id|pte
suffix:semicolon
DECL|macro|PD_SHIFT
mdefine_line|#define PD_SHIFT (10+12)&t;&t;/* Page directory */
DECL|macro|PD_MASK
mdefine_line|#define PD_MASK  0x02FF
DECL|macro|PT_SHIFT
mdefine_line|#define PT_SHIFT (12)&t;&t;&t;/* Page Table */
DECL|macro|PT_MASK
mdefine_line|#define PT_MASK  0x02FF
DECL|macro|PG_SHIFT
mdefine_line|#define PG_SHIFT (12)&t;&t;&t;/* Page Entry */
multiline_comment|/* MMU context */
DECL|struct|_MMU_context
r_typedef
r_struct
id|_MMU_context
(brace
DECL|member|segs
id|SEGREG
id|segs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Segment registers */
DECL|member|pmap
id|pte
op_star
op_star
id|pmap
suffix:semicolon
multiline_comment|/* Two-level page-map structure */
DECL|typedef|MMU_context
)brace
id|MMU_context
suffix:semicolon
r_extern
r_void
id|_tlbie
c_func
(paren
r_int
r_int
id|va
)paren
suffix:semicolon
multiline_comment|/* invalidate a TLB entry */
r_extern
r_void
id|_tlbia
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* invalidate all TLB entries */
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Block size masks */
DECL|macro|BL_128K
mdefine_line|#define BL_128K&t;0x000
DECL|macro|BL_256K
mdefine_line|#define BL_256K 0x001
DECL|macro|BL_512K
mdefine_line|#define BL_512K 0x003
DECL|macro|BL_1M
mdefine_line|#define BL_1M   0x007
DECL|macro|BL_2M
mdefine_line|#define BL_2M   0x00F
DECL|macro|BL_4M
mdefine_line|#define BL_4M   0x01F
DECL|macro|BL_8M
mdefine_line|#define BL_8M   0x03F
DECL|macro|BL_16M
mdefine_line|#define BL_16M  0x07F
DECL|macro|BL_32M
mdefine_line|#define BL_32M  0x0FF
DECL|macro|BL_64M
mdefine_line|#define BL_64M  0x1FF
DECL|macro|BL_128M
mdefine_line|#define BL_128M 0x3FF
DECL|macro|BL_256M
mdefine_line|#define BL_256M 0x7FF
multiline_comment|/* BAT Access Protection */
DECL|macro|BPP_XX
mdefine_line|#define BPP_XX&t;0x00&t;&t;/* No access */
DECL|macro|BPP_RX
mdefine_line|#define BPP_RX&t;0x01&t;&t;/* Read only */
DECL|macro|BPP_RW
mdefine_line|#define BPP_RW&t;0x02&t;&t;/* Read/write */
multiline_comment|/* Used to set up SDR1 register */
DECL|macro|HASH_TABLE_SIZE_64K
mdefine_line|#define HASH_TABLE_SIZE_64K&t;0x00010000
DECL|macro|HASH_TABLE_SIZE_128K
mdefine_line|#define HASH_TABLE_SIZE_128K&t;0x00020000
DECL|macro|HASH_TABLE_SIZE_256K
mdefine_line|#define HASH_TABLE_SIZE_256K&t;0x00040000
DECL|macro|HASH_TABLE_SIZE_512K
mdefine_line|#define HASH_TABLE_SIZE_512K&t;0x00080000
DECL|macro|HASH_TABLE_SIZE_1M
mdefine_line|#define HASH_TABLE_SIZE_1M&t;0x00100000
DECL|macro|HASH_TABLE_SIZE_2M
mdefine_line|#define HASH_TABLE_SIZE_2M&t;0x00200000
DECL|macro|HASH_TABLE_SIZE_4M
mdefine_line|#define HASH_TABLE_SIZE_4M&t;0x00400000
DECL|macro|HASH_TABLE_MASK_64K
mdefine_line|#define HASH_TABLE_MASK_64K&t;0x000   
DECL|macro|HASH_TABLE_MASK_128K
mdefine_line|#define HASH_TABLE_MASK_128K&t;0x001   
DECL|macro|HASH_TABLE_MASK_256K
mdefine_line|#define HASH_TABLE_MASK_256K&t;0x003   
DECL|macro|HASH_TABLE_MASK_512K
mdefine_line|#define HASH_TABLE_MASK_512K&t;0x007
DECL|macro|HASH_TABLE_MASK_1M
mdefine_line|#define HASH_TABLE_MASK_1M&t;0x00F   
DECL|macro|HASH_TABLE_MASK_2M
mdefine_line|#define HASH_TABLE_MASK_2M&t;0x01F   
DECL|macro|HASH_TABLE_MASK_4M
mdefine_line|#define HASH_TABLE_MASK_4M&t;0x03F   
multiline_comment|/* Control/status registers for the MPC8xx.&n; * A write operation to these registers causes serialized access.&n; * During software tablewalk, the registers used perform mask/shift-add&n; * operations when written/read.  A TLB entry is created when the Mx_RPN&n; * is written, and the contents of several registers are used to&n; * create the entry.&n; */
DECL|macro|MI_CTR
mdefine_line|#define MI_CTR&t;&t;784&t;/* Instruction TLB control register */
DECL|macro|MI_GPM
mdefine_line|#define MI_GPM&t;&t;0x80000000&t;/* Set domain manager mode */
DECL|macro|MI_PPM
mdefine_line|#define MI_PPM&t;&t;0x40000000&t;/* Set subpage protection */
DECL|macro|MI_CIDEF
mdefine_line|#define MI_CIDEF&t;0x20000000&t;/* Set cache inhibit when MMU dis */
DECL|macro|MI_RSV4I
mdefine_line|#define MI_RSV4I&t;0x08000000&t;/* Reserve 4 TLB entries */
DECL|macro|MI_PPCS
mdefine_line|#define MI_PPCS&t;&t;0x02000000&t;/* Use MI_RPN prob/priv state */
DECL|macro|MI_IDXMASK
mdefine_line|#define MI_IDXMASK&t;0x00001f00&t;/* TLB index to be loaded */
DECL|macro|MI_RESETVAL
mdefine_line|#define MI_RESETVAL&t;0x00000000&t;/* Value of register at reset */
multiline_comment|/* These are the Ks and Kp from the PowerPC books.  For proper operation,&n; * Ks = 0, Kp = 1.&n; */
DECL|macro|MI_AP
mdefine_line|#define MI_AP&t;&t;786
DECL|macro|MI_Ks
mdefine_line|#define MI_Ks&t;&t;0x80000000&t;/* Should not be set */
DECL|macro|MI_Kp
mdefine_line|#define MI_Kp&t;&t;0x40000000&t;/* Should always be set */
multiline_comment|/* The effective page number register.  When read, contains the information&n; * about the last instruction TLB miss.  When MI_RPN is written, bits in&n; * this register are used to create the TLB entry.&n; */
DECL|macro|MI_EPN
mdefine_line|#define MI_EPN&t;&t;787
DECL|macro|MI_EPNMASK
mdefine_line|#define MI_EPNMASK&t;0xfffff000&t;/* Effective page number for entry */
DECL|macro|MI_EVALID
mdefine_line|#define MI_EVALID&t;0x00000200&t;/* Entry is valid */
DECL|macro|MI_ASIDMASK
mdefine_line|#define MI_ASIDMASK&t;0x0000000f&t;/* ASID match value */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* A &quot;level 1&quot; or &quot;segment&quot; or whatever you want to call it register.&n; * For the instruction TLB, it contains bits that get loaded into the&n; * TLB entry when the MI_RPN is written.&n; */
DECL|macro|MI_TWC
mdefine_line|#define MI_TWC&t;&t;789
DECL|macro|MI_APG
mdefine_line|#define MI_APG&t;&t;0x000001e0&t;/* Access protection group (0) */
DECL|macro|MI_GUARDED
mdefine_line|#define MI_GUARDED&t;0x00000010&t;/* Guarded storage */
DECL|macro|MI_PSMASK
mdefine_line|#define MI_PSMASK&t;0x0000000c&t;/* Mask of page size bits */
DECL|macro|MI_PS8MEG
mdefine_line|#define MI_PS8MEG&t;0x0000000c&t;/* 8M page size */
DECL|macro|MI_PS512K
mdefine_line|#define MI_PS512K&t;0x00000004&t;/* 512K page size */
DECL|macro|MI_PS4K_16K
mdefine_line|#define MI_PS4K_16K&t;0x00000000&t;/* 4K or 16K page size */
DECL|macro|MI_SVALID
mdefine_line|#define MI_SVALID&t;0x00000001&t;/* Segment entry is valid */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* Real page number.  Defined by the pte.  Writing this register&n; * causes a TLB entry to be created for the instruction TLB, using&n; * additional information from the MI_EPN, and MI_TWC registers.&n; */
DECL|macro|MI_RPN
mdefine_line|#define MI_RPN&t;&t;790
multiline_comment|/* Define an RPN value for mapping kernel memory to large virtual&n; * pages for boot initialization.  This has real page number of 0,&n; * large page size, shared page, cache enabled, and valid.&n; * Also mark all subpages valid and write access.&n; */
DECL|macro|MI_BOOTINIT
mdefine_line|#define MI_BOOTINIT&t;0x000001fd
DECL|macro|MD_CTR
mdefine_line|#define MD_CTR&t;&t;792&t;/* Data TLB control register */
DECL|macro|MD_GPM
mdefine_line|#define MD_GPM&t;&t;0x80000000&t;/* Set domain manager mode */
DECL|macro|MD_PPM
mdefine_line|#define MD_PPM&t;&t;0x40000000&t;/* Set subpage protection */
DECL|macro|MD_CIDEF
mdefine_line|#define MD_CIDEF&t;0x20000000&t;/* Set cache inhibit when MMU dis */
DECL|macro|MD_WTDEF
mdefine_line|#define MD_WTDEF&t;0x10000000&t;/* Set writethrough when MMU dis */
DECL|macro|MD_RSV4I
mdefine_line|#define MD_RSV4I&t;0x08000000&t;/* Reserve 4 TLB entries */
DECL|macro|MD_TWAM
mdefine_line|#define MD_TWAM&t;&t;0x04000000&t;/* Use 4K page hardware assist */
DECL|macro|MD_PPCS
mdefine_line|#define MD_PPCS&t;&t;0x02000000&t;/* Use MI_RPN prob/priv state */
DECL|macro|MD_IDXMASK
mdefine_line|#define MD_IDXMASK&t;0x00001f00&t;/* TLB index to be loaded */
DECL|macro|MD_RESETVAL
mdefine_line|#define MD_RESETVAL&t;0x04000000&t;/* Value of register at reset */
DECL|macro|M_CASID
mdefine_line|#define M_CASID&t;&t;793&t;/* Address space ID (context) to match */
DECL|macro|MC_ASIDMASK
mdefine_line|#define MC_ASIDMASK&t;0x0000000f&t;/* Bits used for ASID value */
multiline_comment|/* These are the Ks and Kp from the PowerPC books.  For proper operation,&n; * Ks = 0, Kp = 1.&n; */
DECL|macro|MD_AP
mdefine_line|#define MD_AP&t;&t;794
DECL|macro|MD_Ks
mdefine_line|#define MD_Ks&t;&t;0x80000000&t;/* Should not be set */
DECL|macro|MD_Kp
mdefine_line|#define MD_Kp&t;&t;0x40000000&t;/* Should always be set */
multiline_comment|/* The effective page number register.  When read, contains the information&n; * about the last instruction TLB miss.  When MD_RPN is written, bits in&n; * this register are used to create the TLB entry.&n; */
DECL|macro|MD_EPN
mdefine_line|#define MD_EPN&t;&t;795
DECL|macro|MD_EPNMASK
mdefine_line|#define MD_EPNMASK&t;0xfffff000&t;/* Effective page number for entry */
DECL|macro|MD_EVALID
mdefine_line|#define MD_EVALID&t;0x00000200&t;/* Entry is valid */
DECL|macro|MD_ASIDMASK
mdefine_line|#define MD_ASIDMASK&t;0x0000000f&t;/* ASID match value */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* The pointer to the base address of the first level page table.&n; * During a software tablewalk, reading this register provides the address&n; * of the entry associated with MD_EPN.&n; */
DECL|macro|M_TWB
mdefine_line|#define M_TWB&t;&t;796
DECL|macro|M_L1TB
mdefine_line|#define&t;M_L1TB&t;&t;0xfffff000&t;/* Level 1 table base address */
DECL|macro|M_L1INDX
mdefine_line|#define M_L1INDX&t;0x00000ffc&t;/* Level 1 index, when read */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* A &quot;level 1&quot; or &quot;segment&quot; or whatever you want to call it register.&n; * For the data TLB, it contains bits that get loaded into the TLB entry&n; * when the MD_RPN is written.  It is also provides the hardware assist&n; * for finding the PTE address during software tablewalk.&n; */
DECL|macro|MD_TWC
mdefine_line|#define MD_TWC&t;&t;797
DECL|macro|MD_L2TB
mdefine_line|#define MD_L2TB&t;&t;0xfffff000&t;/* Level 2 table base address */
DECL|macro|MD_L2INDX
mdefine_line|#define MD_L2INDX&t;0xfffffe00&t;/* Level 2 index (*pte), when read */
DECL|macro|MD_APG
mdefine_line|#define MD_APG&t;&t;0x000001e0&t;/* Access protection group (0) */
DECL|macro|MD_GUARDED
mdefine_line|#define MD_GUARDED&t;0x00000010&t;/* Guarded storage */
DECL|macro|MD_PSMASK
mdefine_line|#define MD_PSMASK&t;0x0000000c&t;/* Mask of page size bits */
DECL|macro|MD_PS8MEG
mdefine_line|#define MD_PS8MEG&t;0x0000000c&t;/* 8M page size */
DECL|macro|MD_PS512K
mdefine_line|#define MD_PS512K&t;0x00000004&t;/* 512K page size */
DECL|macro|MD_PS4K_16K
mdefine_line|#define MD_PS4K_16K&t;0x00000000&t;/* 4K or 16K page size */
DECL|macro|MD_WT
mdefine_line|#define MD_WT&t;&t;0x00000002&t;/* Use writethrough page attribute */
DECL|macro|MD_SVALID
mdefine_line|#define MD_SVALID&t;0x00000001&t;/* Segment entry is valid */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* Real page number.  Defined by the pte.  Writing this register&n; * causes a TLB entry to be created for the data TLB, using&n; * additional information from the MD_EPN, and MD_TWC registers.&n; */
DECL|macro|MD_RPN
mdefine_line|#define MD_RPN&t;&t;798
multiline_comment|/* This is a temporary storage register that could be used to save&n; * a processor working register during a tablewalk.&n; */
DECL|macro|M_TW
mdefine_line|#define M_TW&t;&t;799
multiline_comment|/*&n; * At present, all PowerPC 400-class processors share a similar TLB&n; * architecture. The instruction and data sides share a unified,&n; * 64-entry, fully-associative TLB which is maintained totally under&n; * software control. In addition, the instruction side has a&n; * hardware-managed, 4-entry, fully- associative TLB which serves as a&n; * first level to the shared TLB. These two TLBs are known as the UTLB&n; * and ITLB, respectively.&n; */
DECL|macro|PPC4XX_TLB_SIZE
mdefine_line|#define        PPC4XX_TLB_SIZE 64
multiline_comment|/*&n; * TLB entries are defined by a &quot;high&quot; tag portion and a &quot;low&quot; data&n; * portion.  On all architectures, the data portion is 32-bits.&n; *&n; * TLB entries are managed entirely under software control by reading,&n; * writing, and searchoing using the 4xx-specific tlbre, tlbwr, and tlbsx&n; * instructions.&n; */
DECL|macro|TLB_LO
mdefine_line|#define&t;TLB_LO          1
DECL|macro|TLB_HI
mdefine_line|#define&t;TLB_HI          0
DECL|macro|TLB_DATA
mdefine_line|#define&t;TLB_DATA        TLB_LO
DECL|macro|TLB_TAG
mdefine_line|#define&t;TLB_TAG         TLB_HI
multiline_comment|/* Tag portion */
DECL|macro|TLB_EPN_MASK
mdefine_line|#define TLB_EPN_MASK    0xFFFFFC00      /* Effective Page Number */
DECL|macro|TLB_PAGESZ_MASK
mdefine_line|#define TLB_PAGESZ_MASK 0x00000380
DECL|macro|TLB_PAGESZ
mdefine_line|#define TLB_PAGESZ(x)   (((x) &amp; 0x7) &lt;&lt; 7)
DECL|macro|PAGESZ_1K
mdefine_line|#define   PAGESZ_1K&t;&t;0
DECL|macro|PAGESZ_4K
mdefine_line|#define   PAGESZ_4K             1
DECL|macro|PAGESZ_16K
mdefine_line|#define   PAGESZ_16K            2
DECL|macro|PAGESZ_64K
mdefine_line|#define   PAGESZ_64K            3
DECL|macro|PAGESZ_256K
mdefine_line|#define   PAGESZ_256K           4
DECL|macro|PAGESZ_1M
mdefine_line|#define   PAGESZ_1M             5
DECL|macro|PAGESZ_4M
mdefine_line|#define   PAGESZ_4M             6
DECL|macro|PAGESZ_16M
mdefine_line|#define   PAGESZ_16M            7
DECL|macro|TLB_VALID
mdefine_line|#define TLB_VALID       0x00000040      /* Entry is valid */
multiline_comment|/* Data portion */
DECL|macro|TLB_RPN_MASK
mdefine_line|#define TLB_RPN_MASK    0xFFFFFC00      /* Real Page Number */
DECL|macro|TLB_PERM_MASK
mdefine_line|#define TLB_PERM_MASK   0x00000300
DECL|macro|TLB_EX
mdefine_line|#define TLB_EX          0x00000200      /* Instruction execution allowed */
DECL|macro|TLB_WR
mdefine_line|#define TLB_WR          0x00000100      /* Writes permitted */
DECL|macro|TLB_ZSEL_MASK
mdefine_line|#define TLB_ZSEL_MASK   0x000000F0
DECL|macro|TLB_ZSEL
mdefine_line|#define TLB_ZSEL(x)     (((x) &amp; 0xF) &lt;&lt; 4)
DECL|macro|TLB_ATTR_MASK
mdefine_line|#define TLB_ATTR_MASK   0x0000000F
DECL|macro|TLB_W
mdefine_line|#define TLB_W           0x00000008      /* Caching is write-through */
DECL|macro|TLB_I
mdefine_line|#define TLB_I           0x00000004      /* Caching is inhibited */
DECL|macro|TLB_M
mdefine_line|#define TLB_M           0x00000002      /* Memory is coherent */
DECL|macro|TLB_G
mdefine_line|#define TLB_G           0x00000001      /* Memory is guarded from prefetch */
macro_line|#endif /* _PPC_MMU_H_ */
macro_line|#endif /* __KERNEL__ */
eof
