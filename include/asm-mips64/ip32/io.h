macro_line|#ifndef __ASM_IP32_IO_H__
DECL|macro|__ASM_IP32_IO_H__
mdefine_line|#define __ASM_IP32_IO_H__
macro_line|#include &lt;asm/ip32/mace.h&gt;
multiline_comment|/*#ifdef CONFIG_MIPS_UNCACHED*/
DECL|macro|UNCACHEDADDR
mdefine_line|#define UNCACHEDADDR(x) (0x9000000000000000UL | (u64)(x))
multiline_comment|/*#else&n;#define UNCACHEDADDR(x) (x)&n;#endif*/
multiline_comment|/*#define UNCACHEDADDR(x) (KSEG1ADDR (x)) */
DECL|macro|IO_SPACE_BASE
mdefine_line|#define IO_SPACE_BASE UNCACHEDADDR (MACEPCI_HI_MEMORY)
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffffUL
macro_line|#endif
eof
