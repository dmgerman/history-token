macro_line|#ifndef __ALPHA_IRONGATE__H__
DECL|macro|__ALPHA_IRONGATE__H__
mdefine_line|#define __ALPHA_IRONGATE__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * IRONGATE is the internal name for the AMD-751 K7 core logic chipset&n; * which provides memory controller and PCI access for NAUTILUS-based&n; * EV6 (21264) systems.&n; *&n; * This file is based on:&n; *&n; * IronGate management library, (c) 1999 Alpha Processor, Inc.&n; * Copyright (C) 1999 Alpha Processor, Inc.,&n; *&t;(David Daniel, Stig Telfer, Soohoon Lee)&n; */
multiline_comment|/*&n; * The 21264 supports, and internally recognizes, a 44-bit physical&n; * address space that is divided equally between memory address space&n; * and I/O address space. Memory address space resides in the lower&n; * half of the physical address space (PA[43]=0) and I/O address space&n; * resides in the upper half of the physical address space (PA[43]=1).&n; */
multiline_comment|/*&n; * Irongate CSR map.  Some of the CSRs are 8 or 16 bits, but all access&n; * through the routines given is 32-bit.&n; *&n; * The first 0x40 bytes are standard as per the PCI spec.&n; */
DECL|typedef|igcsr32
r_typedef
r_volatile
id|__u32
id|igcsr32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev_vendor
id|igcsr32
id|dev_vendor
suffix:semicolon
multiline_comment|/* 0x00 - device ID, vendor ID */
DECL|member|stat_cmd
id|igcsr32
id|stat_cmd
suffix:semicolon
multiline_comment|/* 0x04 - status, command */
DECL|member|class
id|igcsr32
r_class
suffix:semicolon
multiline_comment|/* 0x08 - class code, rev ID */
DECL|member|latency
id|igcsr32
id|latency
suffix:semicolon
multiline_comment|/* 0x0C - header type, PCI latency */
DECL|member|bar0
id|igcsr32
id|bar0
suffix:semicolon
multiline_comment|/* 0x10 - BAR0 - AGP */
DECL|member|bar1
id|igcsr32
id|bar1
suffix:semicolon
multiline_comment|/* 0x14 - BAR1 - GART */
DECL|member|bar2
id|igcsr32
id|bar2
suffix:semicolon
multiline_comment|/* 0x18 - Power Management reg block */
DECL|member|rsrvd0
id|igcsr32
id|rsrvd0
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0x1C-0x33 reserved */
DECL|member|capptr
id|igcsr32
id|capptr
suffix:semicolon
multiline_comment|/* 0x34 - Capabilities pointer */
DECL|member|rsrvd1
id|igcsr32
id|rsrvd1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x38-0x3F reserved */
DECL|member|bacsr10
id|igcsr32
id|bacsr10
suffix:semicolon
multiline_comment|/* 0x40 - base address chip selects */
DECL|member|bacsr32
id|igcsr32
id|bacsr32
suffix:semicolon
multiline_comment|/* 0x44 - base address chip selects */
DECL|member|bacsr54
id|igcsr32
id|bacsr54
suffix:semicolon
multiline_comment|/* 0x48 - base address chip selects */
DECL|member|rsrvd2
id|igcsr32
id|rsrvd2
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0x4C-0x4F reserved */
DECL|member|drammap
id|igcsr32
id|drammap
suffix:semicolon
multiline_comment|/* 0x50 - address mapping control */
DECL|member|dramtm
id|igcsr32
id|dramtm
suffix:semicolon
multiline_comment|/* 0x54 - timing, driver strength */
DECL|member|dramms
id|igcsr32
id|dramms
suffix:semicolon
multiline_comment|/* 0x58 - ECC, mode/status */
DECL|member|rsrvd3
id|igcsr32
id|rsrvd3
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0x5C-0x5F reserved */
DECL|member|biu0
id|igcsr32
id|biu0
suffix:semicolon
multiline_comment|/* 0x60 - bus interface unit */
DECL|member|biusip
id|igcsr32
id|biusip
suffix:semicolon
multiline_comment|/* 0x64 - Serial initialisation pkt */
DECL|member|rsrvd4
id|igcsr32
id|rsrvd4
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x68-0x6F reserved */
DECL|member|mro
id|igcsr32
id|mro
suffix:semicolon
multiline_comment|/* 0x70 - memory request optimiser */
DECL|member|rsrvd5
id|igcsr32
id|rsrvd5
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0x74-0x7F reserved */
DECL|member|whami
id|igcsr32
id|whami
suffix:semicolon
multiline_comment|/* 0x80 - who am I */
DECL|member|pciarb
id|igcsr32
id|pciarb
suffix:semicolon
multiline_comment|/* 0x84 - PCI arbitration control */
DECL|member|pcicfg
id|igcsr32
id|pcicfg
suffix:semicolon
multiline_comment|/* 0x88 - PCI config status */
DECL|member|rsrvd6
id|igcsr32
id|rsrvd6
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* 0x8C-0x9F reserved */
multiline_comment|/* AGP (bus 1) control registers */
DECL|member|agpcap
id|igcsr32
id|agpcap
suffix:semicolon
multiline_comment|/* 0xA0 - AGP Capability Identifier */
DECL|member|agpstat
id|igcsr32
id|agpstat
suffix:semicolon
multiline_comment|/* 0xA4 - AGP status register */
DECL|member|agpcmd
id|igcsr32
id|agpcmd
suffix:semicolon
multiline_comment|/* 0xA8 - AGP control register */
DECL|member|agpva
id|igcsr32
id|agpva
suffix:semicolon
multiline_comment|/* 0xAC - AGP Virtual Address Space */
DECL|member|agpmode
id|igcsr32
id|agpmode
suffix:semicolon
multiline_comment|/* 0xB0 - AGP/GART mode control */
DECL|typedef|Irongate0
)brace
id|Irongate0
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev_vendor
id|igcsr32
id|dev_vendor
suffix:semicolon
multiline_comment|/* 0x00 - Device and Vendor IDs */
DECL|member|stat_cmd
id|igcsr32
id|stat_cmd
suffix:semicolon
multiline_comment|/* 0x04 - Status and Command regs */
DECL|member|class
id|igcsr32
r_class
suffix:semicolon
multiline_comment|/* 0x08 - subclass, baseclass etc */
DECL|member|htype
id|igcsr32
id|htype
suffix:semicolon
multiline_comment|/* 0x0C - header type (at 0x0E) */
DECL|member|rsrvd0
id|igcsr32
id|rsrvd0
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x10-0x17 reserved */
DECL|member|busnos
id|igcsr32
id|busnos
suffix:semicolon
multiline_comment|/* 0x18 - Primary, secondary bus nos */
DECL|member|io_baselim_regs
id|igcsr32
id|io_baselim_regs
suffix:semicolon
multiline_comment|/* 0x1C - IO base, IO lim, AGP status */
DECL|member|mem_baselim
id|igcsr32
id|mem_baselim
suffix:semicolon
multiline_comment|/* 0x20 - memory base, memory lim */
DECL|member|pfmem_baselim
id|igcsr32
id|pfmem_baselim
suffix:semicolon
multiline_comment|/* 0x24 - prefetchable base, lim */
DECL|member|rsrvd1
id|igcsr32
id|rsrvd1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x28-0x2F reserved */
DECL|member|io_baselim
id|igcsr32
id|io_baselim
suffix:semicolon
multiline_comment|/* 0x30 - IO base, IO limit */
DECL|member|rsrvd2
id|igcsr32
id|rsrvd2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x34-0x3B - reserved */
DECL|member|interrupt
id|igcsr32
id|interrupt
suffix:semicolon
multiline_comment|/* 0x3C - interrupt, PCI bridge ctrl */
DECL|typedef|Irongate1
)brace
id|Irongate1
suffix:semicolon
multiline_comment|/*&n; * Memory spaces:&n; */
multiline_comment|/* Irongate is consistent with a subset of the Tsunami memory map */
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|IRONGATE_BIAS
mdefine_line|#define IRONGATE_BIAS 0x80000000000UL
macro_line|#else
DECL|macro|IRONGATE_BIAS
mdefine_line|#define IRONGATE_BIAS 0x10000000000UL
macro_line|#endif
DECL|macro|IRONGATE_MEM
mdefine_line|#define IRONGATE_MEM&t;&t;(IDENT_ADDR | IRONGATE_BIAS | 0x000000000UL)
DECL|macro|IRONGATE_IACK_SC
mdefine_line|#define IRONGATE_IACK_SC&t;(IDENT_ADDR | IRONGATE_BIAS | 0x1F8000000UL)
DECL|macro|IRONGATE_IO
mdefine_line|#define IRONGATE_IO&t;&t;(IDENT_ADDR | IRONGATE_BIAS | 0x1FC000000UL)
DECL|macro|IRONGATE_CONF
mdefine_line|#define IRONGATE_CONF&t;&t;(IDENT_ADDR | IRONGATE_BIAS | 0x1FE000000UL)
multiline_comment|/*&n; * PCI Configuration space accesses are formed like so:&n; *&n; * 0x1FE &lt;&lt; 24 |  : 2 2 2 2 1 1 1 1 : 1 1 1 1 1 1 0 0 : 0 0 0 0 0 0 0 0 :&n; *                : 3 2 1 0 9 8 7 6 : 5 4 3 2 1 0 9 8 : 7 6 5 4 3 2 1 0 :&n; *                  ---bus numer---   -device-- -fun-   ---register----&n; */
DECL|macro|IGCSR
mdefine_line|#define IGCSR(dev,fun,reg)&t;( IRONGATE_CONF | &bslash;&n;&t;&t;&t;&t;((dev)&lt;&lt;11) | &bslash;&n;&t;&t;&t;&t;((fun)&lt;&lt;8) | &bslash;&n;&t;&t;&t;&t;(reg) )
DECL|macro|IRONGATE0
mdefine_line|#define IRONGATE0&t;&t;((Irongate0 *) IGCSR(0, 0, 0))
DECL|macro|IRONGATE1
mdefine_line|#define IRONGATE1&t;&t;((Irongate1 *) IGCSR(1, 0, 0))
multiline_comment|/*&n; * Data structure for handling IRONGATE machine checks:&n; * This is the standard OSF logout frame&n; */
DECL|macro|SCB_Q_SYSERR
mdefine_line|#define SCB_Q_SYSERR&t;0x620&t;&t;&t;/* OSF definitions */
DECL|macro|SCB_Q_PROCERR
mdefine_line|#define SCB_Q_PROCERR&t;0x630
DECL|macro|SCB_Q_SYSMCHK
mdefine_line|#define SCB_Q_SYSMCHK&t;0x660
DECL|macro|SCB_Q_PROCMCHK
mdefine_line|#define SCB_Q_PROCMCHK&t;0x670
DECL|struct|el_IRONGATE_sysdata_mcheck
r_struct
id|el_IRONGATE_sysdata_mcheck
(brace
DECL|member|FrameSize
id|__u32
id|FrameSize
suffix:semicolon
multiline_comment|/* Bytes, including this field */
DECL|member|FrameFlags
id|__u32
id|FrameFlags
suffix:semicolon
multiline_comment|/* &lt;31&gt; = Retry, &lt;30&gt; = Second Error */
DECL|member|CpuOffset
id|__u32
id|CpuOffset
suffix:semicolon
multiline_comment|/* Offset to CPU-specific into */
DECL|member|SystemOffset
id|__u32
id|SystemOffset
suffix:semicolon
multiline_comment|/* Offset to system-specific info */
DECL|member|MCHK_Code
id|__u32
id|MCHK_Code
suffix:semicolon
DECL|member|MCHK_Frame_Rev
id|__u32
id|MCHK_Frame_Rev
suffix:semicolon
DECL|member|I_STAT
id|__u64
id|I_STAT
suffix:semicolon
DECL|member|DC_STAT
id|__u64
id|DC_STAT
suffix:semicolon
DECL|member|C_ADDR
id|__u64
id|C_ADDR
suffix:semicolon
DECL|member|DC1_SYNDROME
id|__u64
id|DC1_SYNDROME
suffix:semicolon
DECL|member|DC0_SYNDROME
id|__u64
id|DC0_SYNDROME
suffix:semicolon
DECL|member|C_STAT
id|__u64
id|C_STAT
suffix:semicolon
DECL|member|C_STS
id|__u64
id|C_STS
suffix:semicolon
DECL|member|RESERVED0
id|__u64
id|RESERVED0
suffix:semicolon
DECL|member|EXC_ADDR
id|__u64
id|EXC_ADDR
suffix:semicolon
DECL|member|IER_CM
id|__u64
id|IER_CM
suffix:semicolon
DECL|member|ISUM
id|__u64
id|ISUM
suffix:semicolon
DECL|member|MM_STAT
id|__u64
id|MM_STAT
suffix:semicolon
DECL|member|PAL_BASE
id|__u64
id|PAL_BASE
suffix:semicolon
DECL|member|I_CTL
id|__u64
id|I_CTL
suffix:semicolon
DECL|member|PCTX
id|__u64
id|PCTX
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
multiline_comment|/*&n; * I/O functions:&n; *&n; * IRONGATE (AMD-751) PCI/memory support chip for the EV6 (21264) and&n; * K7 can only use linear accesses to get at PCI memory and I/O spaces.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|irongate_inb
id|__EXTERN_INLINE
r_int
r_int
id|irongate_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_outb
id|__EXTERN_INLINE
r_void
id|irongate_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_inw
id|__EXTERN_INLINE
r_int
r_int
id|irongate_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_outw
id|__EXTERN_INLINE
r_void
id|irongate_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_inl
id|__EXTERN_INLINE
r_int
r_int
id|irongate_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
suffix:semicolon
)brace
DECL|function|irongate_outl
id|__EXTERN_INLINE
r_void
id|irongate_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  All accesses are done through linear space.&n; */
DECL|function|irongate_readb
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
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
)brace
DECL|function|irongate_readw
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
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
)brace
DECL|function|irongate_readl
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|irongate_readq
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vulp
)paren
id|addr
suffix:semicolon
)brace
DECL|function|irongate_writeb
id|__EXTERN_INLINE
r_void
id|irongate_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|irongate_writew
id|__EXTERN_INLINE
r_void
id|irongate_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|irongate_writel
id|__EXTERN_INLINE
r_void
id|irongate_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|irongate_writeq
id|__EXTERN_INLINE
r_void
id|irongate_writeq
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vulp
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
r_extern
r_int
r_int
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
suffix:semicolon
r_extern
r_void
id|irongate_iounmap
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|function|irongate_is_ioaddr
id|__EXTERN_INLINE
r_int
id|irongate_is_ioaddr
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
id|IRONGATE_MEM
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
mdefine_line|#define __inb(p)&t;&t;irongate_inb((unsigned long)(p))
DECL|macro|__inw
mdefine_line|#define __inw(p)&t;&t;irongate_inw((unsigned long)(p))
DECL|macro|__inl
mdefine_line|#define __inl(p)&t;&t;irongate_inl((unsigned long)(p))
DECL|macro|__outb
mdefine_line|#define __outb(x,p)&t;&t;irongate_outb((x),(unsigned long)(p))
DECL|macro|__outw
mdefine_line|#define __outw(x,p)&t;&t;irongate_outw((x),(unsigned long)(p))
DECL|macro|__outl
mdefine_line|#define __outl(x,p)&t;&t;irongate_outl((x),(unsigned long)(p))
DECL|macro|__readb
mdefine_line|#define __readb(a)&t;&t;irongate_readb((unsigned long)(a))
DECL|macro|__readw
mdefine_line|#define __readw(a)&t;&t;irongate_readw((unsigned long)(a))
DECL|macro|__readl
mdefine_line|#define __readl(a)&t;&t;irongate_readl((unsigned long)(a))
DECL|macro|__readq
mdefine_line|#define __readq(a)&t;&t;irongate_readq((unsigned long)(a))
DECL|macro|__writeb
mdefine_line|#define __writeb(x,a)&t;&t;irongate_writeb((x),(unsigned long)(a))
DECL|macro|__writew
mdefine_line|#define __writew(x,a)&t;&t;irongate_writew((x),(unsigned long)(a))
DECL|macro|__writel
mdefine_line|#define __writel(x,a)&t;&t;irongate_writel((x),(unsigned long)(a))
DECL|macro|__writeq
mdefine_line|#define __writeq(x,a)&t;&t;irongate_writeq((x),(unsigned long)(a))
DECL|macro|__ioremap
mdefine_line|#define __ioremap(a,s)&t;&t;irongate_ioremap((unsigned long)(a),(s))
DECL|macro|__iounmap
mdefine_line|#define __iounmap(a)&t;&t;irongate_iounmap((unsigned long)(a))
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr(a)&t;&t;irongate_is_ioaddr((unsigned long)(a))
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;__inb(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;__inw(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;__inl(p)
DECL|macro|outb
mdefine_line|#define outb(x,p)&t;&t;__outb((x),(p))
DECL|macro|outw
mdefine_line|#define outw(x,p)&t;&t;__outw((x),(p))
DECL|macro|outl
mdefine_line|#define outl(x,p)&t;&t;__outl((x),(p))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;__readb(a)
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;__readw(a)
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl(a)
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq(a)
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)&t;__writeb((v),(a))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;__writew((v),(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_IRONGATE__H__ */
eof
