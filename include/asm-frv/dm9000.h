multiline_comment|/* dm9000.h: Davicom DM9000 adapter configuration&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_DM9000_H
DECL|macro|_ASM_DM9000_H
mdefine_line|#define _ASM_DM9000_H
macro_line|#include &lt;asm/mb-regs.h&gt;
DECL|macro|DM9000_ARCH_IOBASE
mdefine_line|#define DM9000_ARCH_IOBASE&t;(__region_CS6 + 0x300)
DECL|macro|DM9000_ARCH_IRQ
mdefine_line|#define DM9000_ARCH_IRQ&t;&t;IRQ_CPU_EXTERNAL3&t;/* XIRQ #3 (shared with FPGA) */
DECL|macro|DM9000_ARCH_IRQ_ACTLOW
macro_line|#undef DM9000_ARCH_IRQ_ACTLOW&t;&t;&t;&t;/* IRQ pin active high */
DECL|macro|DM9000_ARCH_BUS_INFO
mdefine_line|#define DM9000_ARCH_BUS_INFO&t;&quot;CS6#+0x300&quot;&t;&t;/* bus info for ethtool */
DECL|macro|__is_PCI_IO
macro_line|#undef __is_PCI_IO
DECL|macro|__is_PCI_IO
mdefine_line|#define __is_PCI_IO(addr)&t;0&t;/* not PCI */
DECL|macro|inl
macro_line|#undef inl
DECL|macro|inl
mdefine_line|#define inl(addr)&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __ioaddr = (unsigned long) addr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;uint32_t x = readl(__ioaddr);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((x &amp; 0xff) &lt;&lt; 24) | ((x &amp; 0xff00) &lt;&lt; 8) | ((x &gt;&gt; 8) &amp; 0xff00) | ((x &gt;&gt; 24) &amp; 0xff);&t;&bslash;&n;})
DECL|macro|insl
macro_line|#undef insl
DECL|macro|insl
mdefine_line|#define insl(a,b,l)&t;__insl(a,b,l,0) /* don&squot;t byte-swap */
macro_line|#endif /* _ASM_DM9000_H */
eof
