macro_line|#ifndef __ALPHA_MCPCIA__H__
DECL|macro|__ALPHA_MCPCIA__H__
mdefine_line|#define __ALPHA_MCPCIA__H__
multiline_comment|/* Define to experiment with fitting everything into one 128MB HAE window.&n;   One window per bus, that is.  */
DECL|macro|MCPCIA_ONE_HAE_WINDOW
mdefine_line|#define MCPCIA_ONE_HAE_WINDOW 1
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * MCPCIA is the internal name for a core logic chipset which provides&n; * PCI access for the RAWHIDE family of systems.&n; *&n; * This file is based on:&n; *&n; * RAWHIDE System Programmer&squot;s Manual&n; * 16-May-96&n; * Rev. 1.4&n; *&n; */
multiline_comment|/*------------------------------------------------------------------------**&n;**                                                                        **&n;**  I/O procedures                                                        **&n;**                                                                        **&n;**      inport[b|w|t|l], outport[b|w|t|l] 8:16:24:32 IO xfers             **&n;**&t;inportbxt: 8 bits only                                            **&n;**      inport:    alias of inportw                                       **&n;**      outport:   alias of outportw                                      **&n;**                                                                        **&n;**      inmem[b|w|t|l], outmem[b|w|t|l] 8:16:24:32 ISA memory xfers       **&n;**&t;inmembxt: 8 bits only                                             **&n;**      inmem:    alias of inmemw                                         **&n;**      outmem:   alias of outmemw                                        **&n;**                                                                        **&n;**------------------------------------------------------------------------*/
multiline_comment|/* MCPCIA ADDRESS BIT DEFINITIONS&n; *&n; *  3333 3333 3322 2222 2222 1111 1111 11&n; *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  1                                             000&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  |                                             |&bslash;|&n; *  |                               Byte Enable --+ |&n; *  |                             Transfer Length --+&n; *  +-- IO space, not cached&n; *&n; *   Byte      Transfer&n; *   Enable    Length    Transfer  Byte    Address&n; *   adr&lt;6:5&gt;  adr&lt;4:3&gt;  Length    Enable  Adder&n; *   ---------------------------------------------&n; *      00        00      Byte      1110   0x000&n; *      01        00      Byte      1101   0x020&n; *      10        00      Byte      1011   0x040&n; *      11        00      Byte      0111   0x060&n; *&n; *      00        01      Word      1100   0x008&n; *      01        01      Word      1001   0x028 &lt;= Not supported in this code.&n; *      10        01      Word      0011   0x048&n; *&n; *      00        10      Tribyte   1000   0x010&n; *      01        10      Tribyte   0001   0x030&n; *&n; *      10        11      Longword  0000   0x058&n; *&n; *      Note that byte enables are asserted low.&n; *&n; */
DECL|macro|MCPCIA_MID
mdefine_line|#define MCPCIA_MID(m)&t;&t;((unsigned long)(m) &lt;&lt; 33)
multiline_comment|/* Dodge has PCI0 and PCI1 at MID 4 and 5 respectively. &n;   Durango adds PCI2 and PCI3 at MID 6 and 7 respectively.  */
DECL|macro|MCPCIA_HOSE2MID
mdefine_line|#define MCPCIA_HOSE2MID(h)&t;((h) + 4)
DECL|macro|MCPCIA_MEM_MASK
mdefine_line|#define MCPCIA_MEM_MASK 0x07ffffff /* SPARSE Mem region mask is 27 bits */
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|MCPCIA_SPARSE
mdefine_line|#define MCPCIA_SPARSE(m)&t;(IDENT_ADDR + 0xf000000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_DENSE
mdefine_line|#define MCPCIA_DENSE(m)&t;&t;(IDENT_ADDR + 0xf100000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_IO
mdefine_line|#define MCPCIA_IO(m)&t;&t;(IDENT_ADDR + 0xf180000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_CONF
mdefine_line|#define MCPCIA_CONF(m)&t;&t;(IDENT_ADDR + 0xf1c0000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_CSR
mdefine_line|#define MCPCIA_CSR(m)&t;&t;(IDENT_ADDR + 0xf1e0000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_IO_IACK
mdefine_line|#define MCPCIA_IO_IACK(m)&t;(IDENT_ADDR + 0xf1f0000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_DENSE_IO
mdefine_line|#define MCPCIA_DENSE_IO(m)&t;(IDENT_ADDR + 0xe1fc000000UL + MCPCIA_MID(m))
DECL|macro|MCPCIA_DENSE_CONF
mdefine_line|#define MCPCIA_DENSE_CONF(m)&t;(IDENT_ADDR + 0xe1fe000000UL + MCPCIA_MID(m))
multiline_comment|/*&n; *  General Registers&n; */
DECL|macro|MCPCIA_REV
mdefine_line|#define MCPCIA_REV(m)&t;&t;(MCPCIA_CSR(m) + 0x000)
DECL|macro|MCPCIA_WHOAMI
mdefine_line|#define MCPCIA_WHOAMI(m)&t;(MCPCIA_CSR(m) + 0x040)
DECL|macro|MCPCIA_PCI_LAT
mdefine_line|#define MCPCIA_PCI_LAT(m)&t;(MCPCIA_CSR(m) + 0x080)
DECL|macro|MCPCIA_CAP_CTRL
mdefine_line|#define MCPCIA_CAP_CTRL(m)&t;(MCPCIA_CSR(m) + 0x100)
DECL|macro|MCPCIA_HAE_MEM
mdefine_line|#define MCPCIA_HAE_MEM(m)&t;(MCPCIA_CSR(m) + 0x400)
DECL|macro|MCPCIA_HAE_IO
mdefine_line|#define MCPCIA_HAE_IO(m)&t;(MCPCIA_CSR(m) + 0x440)
DECL|macro|_MCPCIA_IACK_SC
mdefine_line|#define _MCPCIA_IACK_SC(m)&t;(MCPCIA_CSR(m) + 0x480)
DECL|macro|MCPCIA_HAE_DENSE
mdefine_line|#define MCPCIA_HAE_DENSE(m)&t;(MCPCIA_CSR(m) + 0x4C0)
multiline_comment|/*&n; * Interrupt Control registers&n; */
DECL|macro|MCPCIA_INT_CTL
mdefine_line|#define MCPCIA_INT_CTL(m)&t;(MCPCIA_CSR(m) + 0x500)
DECL|macro|MCPCIA_INT_REQ
mdefine_line|#define MCPCIA_INT_REQ(m)&t;(MCPCIA_CSR(m) + 0x540)
DECL|macro|MCPCIA_INT_TARG
mdefine_line|#define MCPCIA_INT_TARG(m)&t;(MCPCIA_CSR(m) + 0x580)
DECL|macro|MCPCIA_INT_ADR
mdefine_line|#define MCPCIA_INT_ADR(m)&t;(MCPCIA_CSR(m) + 0x5C0)
DECL|macro|MCPCIA_INT_ADR_EXT
mdefine_line|#define MCPCIA_INT_ADR_EXT(m)&t;(MCPCIA_CSR(m) + 0x600)
DECL|macro|MCPCIA_INT_MASK0
mdefine_line|#define MCPCIA_INT_MASK0(m)&t;(MCPCIA_CSR(m) + 0x640)
DECL|macro|MCPCIA_INT_MASK1
mdefine_line|#define MCPCIA_INT_MASK1(m)&t;(MCPCIA_CSR(m) + 0x680)
DECL|macro|MCPCIA_INT_ACK0
mdefine_line|#define MCPCIA_INT_ACK0(m)&t;(MCPCIA_CSR(m) + 0x10003f00)
DECL|macro|MCPCIA_INT_ACK1
mdefine_line|#define MCPCIA_INT_ACK1(m)&t;(MCPCIA_CSR(m) + 0x10003f40)
multiline_comment|/*&n; * Performance Monitor registers&n; */
DECL|macro|MCPCIA_PERF_MON
mdefine_line|#define MCPCIA_PERF_MON(m)&t;(MCPCIA_CSR(m) + 0x300)
DECL|macro|MCPCIA_PERF_CONT
mdefine_line|#define MCPCIA_PERF_CONT(m)&t;(MCPCIA_CSR(m) + 0x340)
multiline_comment|/*&n; * Diagnostic Registers&n; */
DECL|macro|MCPCIA_CAP_DIAG
mdefine_line|#define MCPCIA_CAP_DIAG(m)&t;(MCPCIA_CSR(m) + 0x700)
DECL|macro|MCPCIA_TOP_OF_MEM
mdefine_line|#define MCPCIA_TOP_OF_MEM(m)&t;(MCPCIA_CSR(m) + 0x7C0)
multiline_comment|/*&n; * Error registers&n; */
DECL|macro|MCPCIA_MC_ERR0
mdefine_line|#define MCPCIA_MC_ERR0(m)&t;(MCPCIA_CSR(m) + 0x800)
DECL|macro|MCPCIA_MC_ERR1
mdefine_line|#define MCPCIA_MC_ERR1(m)&t;(MCPCIA_CSR(m) + 0x840)
DECL|macro|MCPCIA_CAP_ERR
mdefine_line|#define MCPCIA_CAP_ERR(m)&t;(MCPCIA_CSR(m) + 0x880)
DECL|macro|MCPCIA_PCI_ERR1
mdefine_line|#define MCPCIA_PCI_ERR1(m)&t;(MCPCIA_CSR(m) + 0x1040)
DECL|macro|MCPCIA_MDPA_STAT
mdefine_line|#define MCPCIA_MDPA_STAT(m)&t;(MCPCIA_CSR(m) + 0x4000)
DECL|macro|MCPCIA_MDPA_SYN
mdefine_line|#define MCPCIA_MDPA_SYN(m)&t;(MCPCIA_CSR(m) + 0x4040)
DECL|macro|MCPCIA_MDPA_DIAG
mdefine_line|#define MCPCIA_MDPA_DIAG(m)&t;(MCPCIA_CSR(m) + 0x4080)
DECL|macro|MCPCIA_MDPB_STAT
mdefine_line|#define MCPCIA_MDPB_STAT(m)&t;(MCPCIA_CSR(m) + 0x8000)
DECL|macro|MCPCIA_MDPB_SYN
mdefine_line|#define MCPCIA_MDPB_SYN(m)&t;(MCPCIA_CSR(m) + 0x8040)
DECL|macro|MCPCIA_MDPB_DIAG
mdefine_line|#define MCPCIA_MDPB_DIAG(m)&t;(MCPCIA_CSR(m) + 0x8080)
multiline_comment|/*&n; * PCI Address Translation Registers.&n; */
DECL|macro|MCPCIA_SG_TBIA
mdefine_line|#define MCPCIA_SG_TBIA(m)&t;(MCPCIA_CSR(m) + 0x1300)
DECL|macro|MCPCIA_HBASE
mdefine_line|#define MCPCIA_HBASE(m)&t;&t;(MCPCIA_CSR(m) + 0x1340)
DECL|macro|MCPCIA_W0_BASE
mdefine_line|#define MCPCIA_W0_BASE(m)&t;(MCPCIA_CSR(m) + 0x1400)
DECL|macro|MCPCIA_W0_MASK
mdefine_line|#define MCPCIA_W0_MASK(m)&t;(MCPCIA_CSR(m) + 0x1440)
DECL|macro|MCPCIA_T0_BASE
mdefine_line|#define MCPCIA_T0_BASE(m)&t;(MCPCIA_CSR(m) + 0x1480)
DECL|macro|MCPCIA_W1_BASE
mdefine_line|#define MCPCIA_W1_BASE(m)&t;(MCPCIA_CSR(m) + 0x1500)
DECL|macro|MCPCIA_W1_MASK
mdefine_line|#define MCPCIA_W1_MASK(m)&t;(MCPCIA_CSR(m) + 0x1540)
DECL|macro|MCPCIA_T1_BASE
mdefine_line|#define MCPCIA_T1_BASE(m)&t;(MCPCIA_CSR(m) + 0x1580)
DECL|macro|MCPCIA_W2_BASE
mdefine_line|#define MCPCIA_W2_BASE(m)&t;(MCPCIA_CSR(m) + 0x1600)
DECL|macro|MCPCIA_W2_MASK
mdefine_line|#define MCPCIA_W2_MASK(m)&t;(MCPCIA_CSR(m) + 0x1640)
DECL|macro|MCPCIA_T2_BASE
mdefine_line|#define MCPCIA_T2_BASE(m)&t;(MCPCIA_CSR(m) + 0x1680)
DECL|macro|MCPCIA_W3_BASE
mdefine_line|#define MCPCIA_W3_BASE(m)&t;(MCPCIA_CSR(m) + 0x1700)
DECL|macro|MCPCIA_W3_MASK
mdefine_line|#define MCPCIA_W3_MASK(m)&t;(MCPCIA_CSR(m) + 0x1740)
DECL|macro|MCPCIA_T3_BASE
mdefine_line|#define MCPCIA_T3_BASE(m)&t;(MCPCIA_CSR(m) + 0x1780)
multiline_comment|/* Hack!  Only words for bus 0.  */
macro_line|#ifndef MCPCIA_ONE_HAE_WINDOW
DECL|macro|MCPCIA_HAE_ADDRESS
mdefine_line|#define MCPCIA_HAE_ADDRESS&t;MCPCIA_HAE_MEM(4)
macro_line|#endif
DECL|macro|MCPCIA_IACK_SC
mdefine_line|#define MCPCIA_IACK_SC&t;&t;_MCPCIA_IACK_SC(4)
multiline_comment|/* &n; * The canonical non-remaped I/O and MEM addresses have these values&n; * subtracted out.  This is arranged so that folks manipulating ISA&n; * devices can use their familiar numbers and have them map to bus 0.&n; */
DECL|macro|MCPCIA_IO_BIAS
mdefine_line|#define MCPCIA_IO_BIAS&t;&t;MCPCIA_IO(4)
DECL|macro|MCPCIA_MEM_BIAS
mdefine_line|#define MCPCIA_MEM_BIAS&t;&t;MCPCIA_DENSE(4)
multiline_comment|/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
DECL|macro|MCPCIA_DAC_OFFSET
mdefine_line|#define MCPCIA_DAC_OFFSET&t;(1UL &lt;&lt; 40)
multiline_comment|/*&n; * Data structure for handling MCPCIA machine checks:&n; */
DECL|struct|el_MCPCIA_uncorrected_frame_mcheck
r_struct
id|el_MCPCIA_uncorrected_frame_mcheck
(brace
DECL|member|header
r_struct
id|el_common
id|header
suffix:semicolon
DECL|member|procdata
r_struct
id|el_common_EV5_uncorrectable_mcheck
id|procdata
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
multiline_comment|/*&n; * I/O functions:&n; *&n; * MCPCIA, the RAWHIDE family PCI/memory support chipset for the EV5 (21164)&n; * and EV56 (21164a) processors, can use either a sparse address mapping&n; * scheme, or the so-called byte-word PCI address space, to get at PCI memory&n; * and I/O.&n; *&n; * Unfortunately, we can&squot;t use BWIO with EV5, so for now, we always use SPARSE.&n; */
multiline_comment|/*&n; * Memory functions.  64-bit and 32-bit accesses are done through&n; * dense memory space, everything else through sparse space.&n; *&n; * For reading and writing 8 and 16 bit quantities we need to&n; * go through one of the three sparse address mapping regions&n; * and use the HAE_MEM CSR to provide some bits of the address.&n; * The following few routines use only sparse address region 1&n; * which gives 1Gbyte of accessible space which relates exactly&n; * to the amount of PCI memory mapping *into* system address space.&n; * See p 6-17 of the specification but it looks something like this:&n; *&n; * 21164 Address:&n; *&n; *          3         2         1&n; * 9876543210987654321098765432109876543210&n; * 1ZZZZ0.PCI.QW.Address............BBLL&n; *&n; * ZZ = SBZ&n; * BB = Byte offset&n; * LL = Transfer length&n; *&n; * PCI Address:&n; *&n; * 3         2         1&n; * 10987654321098765432109876543210&n; * HHH....PCI.QW.Address........ 00&n; *&n; * HHH = 31:29 HAE_MEM CSR&n; *&n; */
DECL|macro|vip
mdefine_line|#define vip&t;volatile int __force *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int __force *
macro_line|#ifdef MCPCIA_ONE_HAE_WINDOW
DECL|macro|MCPCIA_FROB_MMIO
mdefine_line|#define MCPCIA_FROB_MMIO&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__mcpcia_is_mmio(hose)) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_hae(hose &amp; 0xffffffff);&t;&t;&t;&t;&bslash;&n;&t;&t;hose = hose - MCPCIA_DENSE(4) + MCPCIA_SPARSE(4);&t;&bslash;&n;&t;}
macro_line|#else
DECL|macro|MCPCIA_FROB_MMIO
mdefine_line|#define MCPCIA_FROB_MMIO&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__mcpcia_is_mmio(hose)) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hose = hose - MCPCIA_DENSE(4) + MCPCIA_SPARSE(4);&t;&bslash;&n;&t;}
macro_line|#endif
DECL|function|__mcpcia_is_mmio
r_static
r_inline
r_int
id|__mcpcia_is_mmio
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
id|addr
op_amp
l_int|0x80000000UL
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|mcpcia_ioread8
id|__EXTERN_INLINE
r_int
r_int
id|mcpcia_ioread8
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
op_amp
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|hose
op_assign
(paren
r_int
r_int
)paren
id|xaddr
op_amp
op_complement
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
id|MCPCIA_FROB_MMIO
suffix:semicolon
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
id|hose
op_plus
l_int|0x00
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
DECL|function|mcpcia_iowrite8
id|__EXTERN_INLINE
r_void
id|mcpcia_iowrite8
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
op_amp
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|hose
op_assign
(paren
r_int
r_int
)paren
id|xaddr
op_amp
op_complement
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|w
suffix:semicolon
id|MCPCIA_FROB_MMIO
suffix:semicolon
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
id|hose
op_plus
l_int|0x00
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|mcpcia_ioread16
id|__EXTERN_INLINE
r_int
r_int
id|mcpcia_ioread16
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
op_amp
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|hose
op_assign
(paren
r_int
r_int
)paren
id|xaddr
op_amp
op_complement
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
id|MCPCIA_FROB_MMIO
suffix:semicolon
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
id|hose
op_plus
l_int|0x08
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
DECL|function|mcpcia_iowrite16
id|__EXTERN_INLINE
r_void
id|mcpcia_iowrite16
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
op_amp
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|hose
op_assign
(paren
r_int
r_int
)paren
id|xaddr
op_amp
op_complement
id|MCPCIA_MEM_MASK
suffix:semicolon
r_int
r_int
id|w
suffix:semicolon
id|MCPCIA_FROB_MMIO
suffix:semicolon
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
id|hose
op_plus
l_int|0x08
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|mcpcia_ioread32
id|__EXTERN_INLINE
r_int
r_int
id|mcpcia_ioread32
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
op_logical_neg
id|__mcpcia_is_mmio
c_func
(paren
id|addr
)paren
)paren
id|addr
op_assign
(paren
(paren
id|addr
op_amp
l_int|0xffff
)paren
op_lshift
l_int|5
)paren
op_plus
(paren
id|addr
op_amp
op_complement
l_int|0xfffful
)paren
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
DECL|function|mcpcia_iowrite32
id|__EXTERN_INLINE
r_void
id|mcpcia_iowrite32
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
op_logical_neg
id|__mcpcia_is_mmio
c_func
(paren
id|addr
)paren
)paren
id|addr
op_assign
(paren
(paren
id|addr
op_amp
l_int|0xffff
)paren
op_lshift
l_int|5
)paren
op_plus
(paren
id|addr
op_amp
op_complement
l_int|0xfffful
)paren
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
DECL|function|mcpcia_ioportmap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|mcpcia_ioportmap
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
id|MCPCIA_IO_BIAS
)paren
suffix:semicolon
)brace
DECL|function|mcpcia_ioremap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|mcpcia_ioremap
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
id|MCPCIA_MEM_BIAS
)paren
suffix:semicolon
)brace
DECL|function|mcpcia_is_ioaddr
id|__EXTERN_INLINE
r_int
id|mcpcia_is_ioaddr
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
id|MCPCIA_SPARSE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mcpcia_is_mmio
id|__EXTERN_INLINE
r_int
id|mcpcia_is_mmio
c_func
(paren
r_const
r_volatile
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
r_return
id|__mcpcia_is_mmio
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|MCPCIA_FROB_MMIO
macro_line|#undef MCPCIA_FROB_MMIO
DECL|macro|vip
macro_line|#undef vip
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;mcpcia
DECL|macro|mcpcia_trivial_rw_bw
mdefine_line|#define mcpcia_trivial_rw_bw&t;2
DECL|macro|mcpcia_trivial_rw_lq
mdefine_line|#define mcpcia_trivial_rw_lq&t;1
DECL|macro|mcpcia_trivial_io_bw
mdefine_line|#define mcpcia_trivial_io_bw&t;0
DECL|macro|mcpcia_trivial_io_lq
mdefine_line|#define mcpcia_trivial_io_lq&t;0
DECL|macro|mcpcia_trivial_iounmap
mdefine_line|#define mcpcia_trivial_iounmap&t;1
macro_line|#include &lt;asm/io_trivial.h&gt;
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_MCPCIA__H__ */
eof
