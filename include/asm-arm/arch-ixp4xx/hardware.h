multiline_comment|/*&n; * include/asm-arm/arch-ixp4xx/hardware.h &n; *&n; * Copyright (C) 2002 Intel Corporation.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
multiline_comment|/*&n; * Hardware definitions for IXP4xx based systems&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
DECL|macro|__ASM_ARCH_HARDWARE_H__
mdefine_line|#define __ASM_ARCH_HARDWARE_H__
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;&t;0x00001000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;&t;0x48000000
multiline_comment|/*&n; * We override the standard dma-mask routines for bouncing.&n; */
DECL|macro|HAVE_ARCH_PCI_SET_DMA_MASK
mdefine_line|#define&t;HAVE_ARCH_PCI_SET_DMA_MASK
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;1
macro_line|#if defined(CONFIG_CPU_IXP465) &amp;&amp; !defined(__ASSEMBLY__)
r_extern
r_int
r_int
id|processor_id
suffix:semicolon
DECL|macro|cpu_is_ixp465
mdefine_line|#define cpu_is_ixp465() ((processor_id &amp; 0xffffffc0) == 0x69054200)
macro_line|#else
DECL|macro|cpu_is_ixp465
mdefine_line|#define&t;cpu_is_ixp465()&t;(0)
macro_line|#endif
multiline_comment|/* Register locations and bits */
macro_line|#include &quot;ixp4xx-regs.h&quot;
multiline_comment|/* Platform helper functions and definitions */
macro_line|#include &quot;platform.h&quot;
multiline_comment|/* Platform specific details */
macro_line|#include &quot;ixdp425.h&quot;
macro_line|#include &quot;coyote.h&quot;
macro_line|#include &quot;prpmc1100.h&quot;
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
