multiline_comment|/*&n; * File created by Kanoj Sarcar 06/06/00.&n; * Copyright 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_SN_MAPPED_KERNEL_H
DECL|macro|__ASM_SN_MAPPED_KERNEL_H
mdefine_line|#define __ASM_SN_MAPPED_KERNEL_H
multiline_comment|/*&n; * Note on how mapped kernels work: the text and data section is &n; * compiled at cksseg segment (LOADADDR = 0xc001c000), and the &n; * init/setup/data section gets a 16M virtual address bump in the &n; * ld.script file (so that tlblo0 and tlblo1 maps the sections). &n; * The vmlinux.64 section addresses are put in the xkseg range &n; * using the change-addresses makefile option. Use elfdump -of &n; * on IRIX to see where the sections go. The Origin loader loads &n; * the two sections contiguously in physical memory. The loader &n; * sets the entry point into kernel_entry using a xkphys address, &n; * but instead of using 0xa800000001160000, it uses the address &n; * 0xa800000000160000, which is where it physically loaded that &n; * code. So no jumps can be done before we have switched to using &n; * cksseg addresses.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#ifdef CONFIG_MAPPED_KERNEL
DECL|macro|MAPPED_ADDR_RO_TO_PHYS
mdefine_line|#define MAPPED_ADDR_RO_TO_PHYS(x)&t;(x - CKSSEG)
DECL|macro|MAPPED_ADDR_RW_TO_PHYS
mdefine_line|#define MAPPED_ADDR_RW_TO_PHYS(x)&t;(x - CKSSEG - 16777216)
DECL|macro|MAPPED_KERN_RO_PHYSBASE
mdefine_line|#define MAPPED_KERN_RO_PHYSBASE(n) &bslash;&n;&t;&t;&t;(PLAT_NODE_DATA(n)-&gt;kern_vars.kv_ro_baseaddr)
DECL|macro|MAPPED_KERN_RW_PHYSBASE
mdefine_line|#define MAPPED_KERN_RW_PHYSBASE(n) &bslash;&n;&t;&t;&t;(PLAT_NODE_DATA(n)-&gt;kern_vars.kv_rw_baseaddr)
DECL|macro|MAPPED_KERN_RO_TO_PHYS
mdefine_line|#define MAPPED_KERN_RO_TO_PHYS(x) &bslash;&n;&t;&t;&t;&t;((unsigned long)MAPPED_ADDR_RO_TO_PHYS(x) | &bslash;&n;&t;&t;&t;&t;MAPPED_KERN_RO_PHYSBASE(get_compact_nodeid()))
DECL|macro|MAPPED_KERN_RW_TO_PHYS
mdefine_line|#define MAPPED_KERN_RW_TO_PHYS(x) &bslash;&n;&t;&t;&t;&t;((unsigned long)MAPPED_ADDR_RW_TO_PHYS(x) | &bslash;&n;&t;&t;&t;&t;MAPPED_KERN_RW_PHYSBASE(get_compact_nodeid()))
DECL|macro|MAPPED_OFFSET
mdefine_line|#define MAPPED_OFFSET&t;&t;&t;16777216
macro_line|#else /* CONFIG_MAPPED_KERNEL */
DECL|macro|MAPPED_KERN_RO_TO_PHYS
mdefine_line|#define MAPPED_KERN_RO_TO_PHYS(x)&t;(x - CKSEG0)
DECL|macro|MAPPED_KERN_RW_TO_PHYS
mdefine_line|#define MAPPED_KERN_RW_TO_PHYS(x)&t;(x - CKSEG0)
DECL|macro|MAPPED_OFFSET
mdefine_line|#define MAPPED_OFFSET&t;&t;&t;0
macro_line|#endif /* CONFIG_MAPPED_KERNEL */
DECL|macro|MAPPED_KERN_RO_TO_K0
mdefine_line|#define MAPPED_KERN_RO_TO_K0(x)&t;PHYS_TO_K0(MAPPED_KERN_RO_TO_PHYS(x))
DECL|macro|MAPPED_KERN_RW_TO_K0
mdefine_line|#define MAPPED_KERN_RW_TO_K0(x)&t;PHYS_TO_K0(MAPPED_KERN_RW_TO_PHYS(x))
macro_line|#endif __ASM_SN_MAPPED_KERNEL_H
eof
