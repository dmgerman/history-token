macro_line|#ifndef __ALPHA_LCA__H__
DECL|macro|__ALPHA_LCA__H__
mdefine_line|#define __ALPHA_LCA__H__
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * Low Cost Alpha (LCA) definitions (these apply to 21066 and 21068,&n; * for example).&n; *&n; * This file is based on:&n; *&n; *&t;DECchip 21066 and DECchip 21068 Alpha AXP Microprocessors&n; *&t;Hardware Reference Manual; Digital Equipment Corp.; May 1994;&n; *&t;Maynard, MA; Order Number: EC-N2681-71.&n; */
multiline_comment|/*&n; * NOTE: The LCA uses a Host Address Extension (HAE) register to access&n; *&t; PCI addresses that are beyond the first 27 bits of address&n; *&t; space.  Updating the HAE requires an external cycle (and&n; *&t; a memory barrier), which tends to be slow.  Instead of updating&n; *&t; it on each sparse memory access, we keep the current HAE value&n; *&t; cached in variable cache_hae.  Only if the cached HAE differs&n; *&t; from the desired HAE value do we actually updated HAE register.&n; *&t; The HAE register is preserved by the interrupt handler entry/exit&n; *&t; code, so this scheme works even in the presence of interrupts.&n; *&n; * Dense memory space doesn&squot;t require the HAE, but is restricted to&n; * aligned 32 and 64 bit accesses.  Special Cycle and Interrupt&n; * Acknowledge cycles may also require the use of the HAE.  The LCA&n; * limits I/O address space to the bottom 24 bits of address space,&n; * but this easily covers the 16 bit ISA I/O address space.&n; */
multiline_comment|/*&n; * NOTE 2! The memory operations do not set any memory barriers, as&n; * it&squot;s not needed for cases like a frame buffer that is essentially&n; * memory-like.  You need to do them by hand if the operations depend&n; * on ordering.&n; *&n; * Similarly, the port I/O operations do a &quot;mb&quot; only after a write&n; * operation: if an mb is needed before (as in the case of doing&n; * memory mapped I/O first, and then a port I/O operation to the same&n; * device), it needs to be done by hand.&n; *&n; * After the above has bitten me 100 times, I&squot;ll give up and just do&n; * the mb all the time, but right now I&squot;m hoping this will work out.&n; * Avoiding mb&squot;s may potentially be a noticeable speed improvement,&n; * but I can&squot;t honestly say I&squot;ve tested it.&n; *&n; * Handling interrupts that need to do mb&squot;s to synchronize to&n; * non-interrupts is another fun race area.  Don&squot;t do it (because if&n; * you do, I&squot;ll have to do *everything* with interrupts disabled,&n; * ugh).&n; */
multiline_comment|/*&n; * Memory Controller registers:&n; */
DECL|macro|LCA_MEM_BCR0
mdefine_line|#define LCA_MEM_BCR0&t;&t;(IDENT_ADDR + 0x120000000UL)
DECL|macro|LCA_MEM_BCR1
mdefine_line|#define LCA_MEM_BCR1&t;&t;(IDENT_ADDR + 0x120000008UL)
DECL|macro|LCA_MEM_BCR2
mdefine_line|#define LCA_MEM_BCR2&t;&t;(IDENT_ADDR + 0x120000010UL)
DECL|macro|LCA_MEM_BCR3
mdefine_line|#define LCA_MEM_BCR3&t;&t;(IDENT_ADDR + 0x120000018UL)
DECL|macro|LCA_MEM_BMR0
mdefine_line|#define LCA_MEM_BMR0&t;&t;(IDENT_ADDR + 0x120000020UL)
DECL|macro|LCA_MEM_BMR1
mdefine_line|#define LCA_MEM_BMR1&t;&t;(IDENT_ADDR + 0x120000028UL)
DECL|macro|LCA_MEM_BMR2
mdefine_line|#define LCA_MEM_BMR2&t;&t;(IDENT_ADDR + 0x120000030UL)
DECL|macro|LCA_MEM_BMR3
mdefine_line|#define LCA_MEM_BMR3&t;&t;(IDENT_ADDR + 0x120000038UL)
DECL|macro|LCA_MEM_BTR0
mdefine_line|#define LCA_MEM_BTR0&t;&t;(IDENT_ADDR + 0x120000040UL)
DECL|macro|LCA_MEM_BTR1
mdefine_line|#define LCA_MEM_BTR1&t;&t;(IDENT_ADDR + 0x120000048UL)
DECL|macro|LCA_MEM_BTR2
mdefine_line|#define LCA_MEM_BTR2&t;&t;(IDENT_ADDR + 0x120000050UL)
DECL|macro|LCA_MEM_BTR3
mdefine_line|#define LCA_MEM_BTR3&t;&t;(IDENT_ADDR + 0x120000058UL)
DECL|macro|LCA_MEM_GTR
mdefine_line|#define LCA_MEM_GTR&t;&t;(IDENT_ADDR + 0x120000060UL)
DECL|macro|LCA_MEM_ESR
mdefine_line|#define LCA_MEM_ESR&t;&t;(IDENT_ADDR + 0x120000068UL)
DECL|macro|LCA_MEM_EAR
mdefine_line|#define LCA_MEM_EAR&t;&t;(IDENT_ADDR + 0x120000070UL)
DECL|macro|LCA_MEM_CAR
mdefine_line|#define LCA_MEM_CAR&t;&t;(IDENT_ADDR + 0x120000078UL)
DECL|macro|LCA_MEM_VGR
mdefine_line|#define LCA_MEM_VGR&t;&t;(IDENT_ADDR + 0x120000080UL)
DECL|macro|LCA_MEM_PLM
mdefine_line|#define LCA_MEM_PLM&t;&t;(IDENT_ADDR + 0x120000088UL)
DECL|macro|LCA_MEM_FOR
mdefine_line|#define LCA_MEM_FOR&t;&t;(IDENT_ADDR + 0x120000090UL)
multiline_comment|/*&n; * I/O Controller registers:&n; */
DECL|macro|LCA_IOC_HAE
mdefine_line|#define LCA_IOC_HAE&t;&t;(IDENT_ADDR + 0x180000000UL)
DECL|macro|LCA_IOC_CONF
mdefine_line|#define LCA_IOC_CONF&t;&t;(IDENT_ADDR + 0x180000020UL)
DECL|macro|LCA_IOC_STAT0
mdefine_line|#define LCA_IOC_STAT0&t;&t;(IDENT_ADDR + 0x180000040UL)
DECL|macro|LCA_IOC_STAT1
mdefine_line|#define LCA_IOC_STAT1&t;&t;(IDENT_ADDR + 0x180000060UL)
DECL|macro|LCA_IOC_TBIA
mdefine_line|#define LCA_IOC_TBIA&t;&t;(IDENT_ADDR + 0x180000080UL)
DECL|macro|LCA_IOC_TB_ENA
mdefine_line|#define LCA_IOC_TB_ENA&t;&t;(IDENT_ADDR + 0x1800000a0UL)
DECL|macro|LCA_IOC_SFT_RST
mdefine_line|#define LCA_IOC_SFT_RST&t;&t;(IDENT_ADDR + 0x1800000c0UL)
DECL|macro|LCA_IOC_PAR_DIS
mdefine_line|#define LCA_IOC_PAR_DIS&t;&t;(IDENT_ADDR + 0x1800000e0UL)
DECL|macro|LCA_IOC_W_BASE0
mdefine_line|#define LCA_IOC_W_BASE0&t;&t;(IDENT_ADDR + 0x180000100UL)
DECL|macro|LCA_IOC_W_BASE1
mdefine_line|#define LCA_IOC_W_BASE1&t;&t;(IDENT_ADDR + 0x180000120UL)
DECL|macro|LCA_IOC_W_MASK0
mdefine_line|#define LCA_IOC_W_MASK0&t;&t;(IDENT_ADDR + 0x180000140UL)
DECL|macro|LCA_IOC_W_MASK1
mdefine_line|#define LCA_IOC_W_MASK1&t;&t;(IDENT_ADDR + 0x180000160UL)
DECL|macro|LCA_IOC_T_BASE0
mdefine_line|#define LCA_IOC_T_BASE0&t;&t;(IDENT_ADDR + 0x180000180UL)
DECL|macro|LCA_IOC_T_BASE1
mdefine_line|#define LCA_IOC_T_BASE1&t;&t;(IDENT_ADDR + 0x1800001a0UL)
DECL|macro|LCA_IOC_TB_TAG0
mdefine_line|#define LCA_IOC_TB_TAG0&t;&t;(IDENT_ADDR + 0x188000000UL)
DECL|macro|LCA_IOC_TB_TAG1
mdefine_line|#define LCA_IOC_TB_TAG1&t;&t;(IDENT_ADDR + 0x188000020UL)
DECL|macro|LCA_IOC_TB_TAG2
mdefine_line|#define LCA_IOC_TB_TAG2&t;&t;(IDENT_ADDR + 0x188000040UL)
DECL|macro|LCA_IOC_TB_TAG3
mdefine_line|#define LCA_IOC_TB_TAG3&t;&t;(IDENT_ADDR + 0x188000060UL)
DECL|macro|LCA_IOC_TB_TAG4
mdefine_line|#define LCA_IOC_TB_TAG4&t;&t;(IDENT_ADDR + 0x188000070UL)
DECL|macro|LCA_IOC_TB_TAG5
mdefine_line|#define LCA_IOC_TB_TAG5&t;&t;(IDENT_ADDR + 0x1880000a0UL)
DECL|macro|LCA_IOC_TB_TAG6
mdefine_line|#define LCA_IOC_TB_TAG6&t;&t;(IDENT_ADDR + 0x1880000c0UL)
DECL|macro|LCA_IOC_TB_TAG7
mdefine_line|#define LCA_IOC_TB_TAG7&t;&t;(IDENT_ADDR + 0x1880000e0UL)
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|LCA_IACK_SC
mdefine_line|#define LCA_IACK_SC&t;&t;(IDENT_ADDR + 0x1a0000000UL)
DECL|macro|LCA_CONF
mdefine_line|#define LCA_CONF&t;&t;(IDENT_ADDR + 0x1e0000000UL)
DECL|macro|LCA_IO
mdefine_line|#define LCA_IO&t;&t;&t;(IDENT_ADDR + 0x1c0000000UL)
DECL|macro|LCA_SPARSE_MEM
mdefine_line|#define LCA_SPARSE_MEM&t;&t;(IDENT_ADDR + 0x200000000UL)
DECL|macro|LCA_DENSE_MEM
mdefine_line|#define LCA_DENSE_MEM&t;&t;(IDENT_ADDR + 0x300000000UL)
multiline_comment|/*&n; * Bit definitions for I/O Controller status register 0:&n; */
DECL|macro|LCA_IOC_STAT0_CMD
mdefine_line|#define LCA_IOC_STAT0_CMD&t;&t;0xf
DECL|macro|LCA_IOC_STAT0_ERR
mdefine_line|#define LCA_IOC_STAT0_ERR&t;&t;(1&lt;&lt;4)
DECL|macro|LCA_IOC_STAT0_LOST
mdefine_line|#define LCA_IOC_STAT0_LOST&t;&t;(1&lt;&lt;5)
DECL|macro|LCA_IOC_STAT0_THIT
mdefine_line|#define LCA_IOC_STAT0_THIT&t;&t;(1&lt;&lt;6)
DECL|macro|LCA_IOC_STAT0_TREF
mdefine_line|#define LCA_IOC_STAT0_TREF&t;&t;(1&lt;&lt;7)
DECL|macro|LCA_IOC_STAT0_CODE_SHIFT
mdefine_line|#define LCA_IOC_STAT0_CODE_SHIFT&t;8
DECL|macro|LCA_IOC_STAT0_CODE_MASK
mdefine_line|#define LCA_IOC_STAT0_CODE_MASK&t;&t;0x7
DECL|macro|LCA_IOC_STAT0_P_NBR_SHIFT
mdefine_line|#define LCA_IOC_STAT0_P_NBR_SHIFT&t;13
DECL|macro|LCA_IOC_STAT0_P_NBR_MASK
mdefine_line|#define LCA_IOC_STAT0_P_NBR_MASK&t;0x7ffff
DECL|macro|LCA_HAE_ADDRESS
mdefine_line|#define LCA_HAE_ADDRESS&t;&t;LCA_IOC_HAE
multiline_comment|/* LCA PMR Power Management register defines */
DECL|macro|LCA_PMR_ADDR
mdefine_line|#define LCA_PMR_ADDR&t;(IDENT_ADDR + 0x120000098UL)
DECL|macro|LCA_PMR_PDIV
mdefine_line|#define LCA_PMR_PDIV    0x7                     /* Primary clock divisor */
DECL|macro|LCA_PMR_ODIV
mdefine_line|#define LCA_PMR_ODIV    0x38                    /* Override clock divisor */
DECL|macro|LCA_PMR_INTO
mdefine_line|#define LCA_PMR_INTO    0x40                    /* Interrupt override */
DECL|macro|LCA_PMR_DMAO
mdefine_line|#define LCA_PMR_DMAO    0x80                    /* DMA override */
DECL|macro|LCA_PMR_OCCEB
mdefine_line|#define LCA_PMR_OCCEB   0xffff0000L             /* Override cycle counter - even bits */
DECL|macro|LCA_PMR_OCCOB
mdefine_line|#define LCA_PMR_OCCOB   0xffff000000000000L     /* Override cycle counter - even bits */
DECL|macro|LCA_PMR_PRIMARY_MASK
mdefine_line|#define LCA_PMR_PRIMARY_MASK    0xfffffffffffffff8L
multiline_comment|/* LCA PMR Macros */
DECL|macro|LCA_READ_PMR
mdefine_line|#define LCA_READ_PMR        (*(volatile unsigned long *)LCA_PMR_ADDR)
DECL|macro|LCA_WRITE_PMR
mdefine_line|#define LCA_WRITE_PMR(d)    (*((volatile unsigned long *)LCA_PMR_ADDR) = (d))
DECL|macro|LCA_GET_PRIMARY
mdefine_line|#define LCA_GET_PRIMARY(r)  ((r) &amp; LCA_PMR_PDIV)
DECL|macro|LCA_GET_OVERRIDE
mdefine_line|#define LCA_GET_OVERRIDE(r) (((r) &gt;&gt; 3) &amp; LCA_PMR_PDIV)
DECL|macro|LCA_SET_PRIMARY_CLOCK
mdefine_line|#define LCA_SET_PRIMARY_CLOCK(r, c) ((r) = (((r) &amp; LCA_PMR_PRIMARY_MASK)|(c)))
multiline_comment|/* LCA PMR Divisor values */
DECL|macro|LCA_PMR_DIV_1
mdefine_line|#define LCA_PMR_DIV_1   0x0
DECL|macro|LCA_PMR_DIV_1_5
mdefine_line|#define LCA_PMR_DIV_1_5 0x1
DECL|macro|LCA_PMR_DIV_2
mdefine_line|#define LCA_PMR_DIV_2   0x2
DECL|macro|LCA_PMR_DIV_4
mdefine_line|#define LCA_PMR_DIV_4   0x3
DECL|macro|LCA_PMR_DIV_8
mdefine_line|#define LCA_PMR_DIV_8   0x4
DECL|macro|LCA_PMR_DIV_16
mdefine_line|#define LCA_PMR_DIV_16  0x5
DECL|macro|LCA_PMR_DIV_MIN
mdefine_line|#define LCA_PMR_DIV_MIN DIV_1
DECL|macro|LCA_PMR_DIV_MAX
mdefine_line|#define LCA_PMR_DIV_MAX DIV_16
multiline_comment|/*&n; * Data structure for handling LCA machine checks.  Correctable errors&n; * result in a short logout frame, uncorrectable ones in a long one.&n; */
DECL|struct|el_lca_mcheck_short
r_struct
id|el_lca_mcheck_short
(brace
DECL|member|h
r_struct
id|el_common
id|h
suffix:semicolon
multiline_comment|/* common logout header */
DECL|member|esr
r_int
r_int
id|esr
suffix:semicolon
multiline_comment|/* error-status register */
DECL|member|ear
r_int
r_int
id|ear
suffix:semicolon
multiline_comment|/* error-address register */
DECL|member|dc_stat
r_int
r_int
id|dc_stat
suffix:semicolon
multiline_comment|/* dcache status register */
DECL|member|ioc_stat0
r_int
r_int
id|ioc_stat0
suffix:semicolon
multiline_comment|/* I/O controller status register 0 */
DECL|member|ioc_stat1
r_int
r_int
id|ioc_stat1
suffix:semicolon
multiline_comment|/* I/O controller status register 1 */
)brace
suffix:semicolon
DECL|struct|el_lca_mcheck_long
r_struct
id|el_lca_mcheck_long
(brace
DECL|member|h
r_struct
id|el_common
id|h
suffix:semicolon
multiline_comment|/* common logout header */
DECL|member|pt
r_int
r_int
id|pt
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* PAL temps */
DECL|member|exc_addr
r_int
r_int
id|exc_addr
suffix:semicolon
multiline_comment|/* exception address */
DECL|member|pad1
r_int
r_int
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|pal_base
r_int
r_int
id|pal_base
suffix:semicolon
multiline_comment|/* PALcode base address */
DECL|member|hier
r_int
r_int
id|hier
suffix:semicolon
multiline_comment|/* hw interrupt enable */
DECL|member|hirr
r_int
r_int
id|hirr
suffix:semicolon
multiline_comment|/* hw interrupt request */
DECL|member|mm_csr
r_int
r_int
id|mm_csr
suffix:semicolon
multiline_comment|/* MMU control &amp; status */
DECL|member|dc_stat
r_int
r_int
id|dc_stat
suffix:semicolon
multiline_comment|/* data cache status */
DECL|member|dc_addr
r_int
r_int
id|dc_addr
suffix:semicolon
multiline_comment|/* data cache addr register */
DECL|member|abox_ctl
r_int
r_int
id|abox_ctl
suffix:semicolon
multiline_comment|/* address box control register */
DECL|member|esr
r_int
r_int
id|esr
suffix:semicolon
multiline_comment|/* error status register */
DECL|member|ear
r_int
r_int
id|ear
suffix:semicolon
multiline_comment|/* error address register */
DECL|member|car
r_int
r_int
id|car
suffix:semicolon
multiline_comment|/* cache control register */
DECL|member|ioc_stat0
r_int
r_int
id|ioc_stat0
suffix:semicolon
multiline_comment|/* I/O controller status register 0 */
DECL|member|ioc_stat1
r_int
r_int
id|ioc_stat1
suffix:semicolon
multiline_comment|/* I/O controller status register 1 */
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
multiline_comment|/* virtual address register */
)brace
suffix:semicolon
DECL|union|el_lca
r_union
id|el_lca
(brace
DECL|member|c
r_struct
id|el_common
op_star
id|c
suffix:semicolon
DECL|member|l
r_struct
id|el_lca_mcheck_long
op_star
id|l
suffix:semicolon
DECL|member|s
r_struct
id|el_lca_mcheck_short
op_star
id|s
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * Unlike Jensen, the Noname machines have no concept of local&n; * I/O---everything goes over the PCI bus.&n; *&n; * There is plenty room for optimization here.  In particular,&n; * the Alpha&squot;s insb/insw/extb/extw should be useful in moving&n; * data to/from the right byte-lanes.&n; */
DECL|macro|vip
mdefine_line|#define vip&t;volatile int __force *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int __force *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long __force *
DECL|macro|LCA_SET_HAE
mdefine_line|#define LCA_SET_HAE&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (addr &gt;= (1UL &lt;&lt; 24)) {&t;&t;&t;&bslash;&n;&t;&t;&t;unsigned long msb = addr &amp; 0xf8000000;&t;&bslash;&n;&t;&t;&t;addr -= msb;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;set_hae(msb);&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|function|lca_ioread8
id|__EXTERN_INLINE
r_int
r_int
id|lca_ioread8
c_func
(paren
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|result
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|LCA_DENSE_MEM
)paren
(brace
id|addr
op_sub_assign
id|LCA_DENSE_MEM
suffix:semicolon
id|LCA_SET_HAE
suffix:semicolon
id|base_and_type
op_assign
id|LCA_SPARSE_MEM
op_plus
l_int|0x00
suffix:semicolon
)brace
r_else
(brace
id|addr
op_sub_assign
id|LCA_IO
suffix:semicolon
id|base_and_type
op_assign
id|LCA_IO
op_plus
l_int|0x00
suffix:semicolon
)brace
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|lca_iowrite8
id|__EXTERN_INLINE
r_void
id|lca_iowrite8
c_func
(paren
id|u8
id|b
comma
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|w
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|LCA_DENSE_MEM
)paren
(brace
id|addr
op_sub_assign
id|LCA_DENSE_MEM
suffix:semicolon
id|LCA_SET_HAE
suffix:semicolon
id|base_and_type
op_assign
id|LCA_SPARSE_MEM
op_plus
l_int|0x00
suffix:semicolon
)brace
r_else
(brace
id|addr
op_sub_assign
id|LCA_IO
suffix:semicolon
id|base_and_type
op_assign
id|LCA_IO
op_plus
l_int|0x00
suffix:semicolon
)brace
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|lca_ioread16
id|__EXTERN_INLINE
r_int
r_int
id|lca_ioread16
c_func
(paren
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|result
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|LCA_DENSE_MEM
)paren
(brace
id|addr
op_sub_assign
id|LCA_DENSE_MEM
suffix:semicolon
id|LCA_SET_HAE
suffix:semicolon
id|base_and_type
op_assign
id|LCA_SPARSE_MEM
op_plus
l_int|0x08
suffix:semicolon
)brace
r_else
(brace
id|addr
op_sub_assign
id|LCA_IO
suffix:semicolon
id|base_and_type
op_assign
id|LCA_IO
op_plus
l_int|0x08
suffix:semicolon
)brace
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|lca_iowrite16
id|__EXTERN_INLINE
r_void
id|lca_iowrite16
c_func
(paren
id|u16
id|b
comma
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|w
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|LCA_DENSE_MEM
)paren
(brace
id|addr
op_sub_assign
id|LCA_DENSE_MEM
suffix:semicolon
id|LCA_SET_HAE
suffix:semicolon
id|base_and_type
op_assign
id|LCA_SPARSE_MEM
op_plus
l_int|0x08
suffix:semicolon
)brace
r_else
(brace
id|addr
op_sub_assign
id|LCA_IO
suffix:semicolon
id|base_and_type
op_assign
id|LCA_IO
op_plus
l_int|0x08
suffix:semicolon
)brace
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|lca_ioread32
id|__EXTERN_INLINE
r_int
r_int
id|lca_ioread32
c_func
(paren
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|LCA_DENSE_MEM
)paren
id|addr
op_assign
(paren
(paren
id|addr
op_minus
id|LCA_IO
)paren
op_lshift
l_int|5
)paren
op_plus
id|LCA_IO
op_plus
l_int|0x18
suffix:semicolon
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|lca_iowrite32
id|__EXTERN_INLINE
r_void
id|lca_iowrite32
c_func
(paren
id|u32
id|b
comma
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|LCA_DENSE_MEM
)paren
id|addr
op_assign
(paren
(paren
id|addr
op_minus
id|LCA_IO
)paren
op_lshift
l_int|5
)paren
op_plus
id|LCA_IO
op_plus
l_int|0x18
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|lca_ioportmap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|lca_ioportmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|LCA_IO
)paren
suffix:semicolon
)brace
DECL|function|lca_ioremap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|lca_ioremap
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
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|LCA_DENSE_MEM
)paren
suffix:semicolon
)brace
DECL|function|lca_is_ioaddr
id|__EXTERN_INLINE
r_int
id|lca_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|IDENT_ADDR
op_plus
l_int|0x120000000UL
suffix:semicolon
)brace
DECL|function|lca_is_mmio
id|__EXTERN_INLINE
r_int
id|lca_is_mmio
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|addr
op_ge
id|LCA_DENSE_MEM
suffix:semicolon
)brace
DECL|macro|vip
macro_line|#undef vip
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;lca
DECL|macro|lca_trivial_rw_bw
mdefine_line|#define lca_trivial_rw_bw&t;2
DECL|macro|lca_trivial_rw_lq
mdefine_line|#define lca_trivial_rw_lq&t;1
DECL|macro|lca_trivial_io_bw
mdefine_line|#define lca_trivial_io_bw&t;0
DECL|macro|lca_trivial_io_lq
mdefine_line|#define lca_trivial_io_lq&t;0
DECL|macro|lca_trivial_iounmap
mdefine_line|#define lca_trivial_iounmap&t;1
macro_line|#include &lt;asm/io_trivial.h&gt;
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_LCA__H__ */
eof
