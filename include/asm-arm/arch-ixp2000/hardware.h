multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp2000/hardware.h&n; *&n; * Hardware definitions for IXP2400/2800 based systems&n; *&n; * Original Author: Naeem M Afzal &lt;naeem.m.afzal@intel.com&gt;&n; *&n; * Maintainer: Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; *&n; * Copyright (C) 2001-2002 Intel Corp.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H__
DECL|macro|__ASM_ARCH_HARDWARE_H__
mdefine_line|#define __ASM_ARCH_HARDWARE_H__
multiline_comment|/*&n; * This needs to be platform-specific?&n; */
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO          0x00000000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM         0x00000000
macro_line|#include &quot;ixp2000-regs.h&quot;&t;/* Chipset Registers */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses() 0
multiline_comment|/*&n; * Platform helper functions&n; */
macro_line|#include &quot;platform.h&quot;
multiline_comment|/*&n; * Platform-specific bits&n; */
macro_line|#include &quot;ixdp2x00.h&quot;&t;&t;/* IXDP2400/2800 */
macro_line|#include &quot;ixdp2x01.h&quot;&t;&t;/* IXDP2401/2801 */
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H__ */
eof
