multiline_comment|/*&n; * CPCI-405 board specific definitions&n; *&n; * Copyright (c) 2001 Stefan Roese (stefan.roese@esd-electronics.com)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_CPCI405_H__
DECL|macro|__ASM_CPCI405_H__
mdefine_line|#define __ASM_CPCI405_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* We have a 405GP core */
macro_line|#include &lt;platforms/4xx/ibm405gp.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Some 4xx parts use a different timebase frequency from the internal clock.&n;*/
DECL|macro|bi_tbfreq
mdefine_line|#define bi_tbfreq bi_intfreq
multiline_comment|/* Map for the NVRAM space */
DECL|macro|CPCI405_NVRAM_PADDR
mdefine_line|#define CPCI405_NVRAM_PADDR&t;((uint)0xf0200000)
DECL|macro|CPCI405_NVRAM_SIZE
mdefine_line|#define CPCI405_NVRAM_SIZE&t;((uint)32*1024)
macro_line|#ifdef CONFIG_PPC405GP_INTERNAL_CLOCK
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;201600
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;691200
macro_line|#endif
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME &quot;esd CPCI-405&quot;
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif&t;/* __ASM_CPCI405_H__ */
macro_line|#endif /* __KERNEL__ */
eof
