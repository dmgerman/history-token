multiline_comment|/*&n; * linux/include/asm-arm/arch-adifcc/hardware.h&n; *&n; * Hardware definitions for ADI based systems&n; *&n; * Author: Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; *&n; * Copyright (C) 2000-2001 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;0
macro_line|#if defined(CONFIG_ARCH_ADI_EVB)
macro_line|#include &quot;adi_evb.h&quot;
macro_line|#endif
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
