multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * include/asm-ppc/serial.h&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SERIAL_H__
DECL|macro|__ASM_SERIAL_H__
mdefine_line|#define __ASM_SERIAL_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_EV64260)
macro_line|#include &lt;platforms/ev64260.h&gt;
macro_line|#elif defined(CONFIG_GEMINI)
macro_line|#include &lt;platforms/gemini_serial.h&gt;
macro_line|#elif defined(CONFIG_POWERPMC250)
macro_line|#include &lt;platforms/powerpmc250_serial.h&gt;
macro_line|#elif defined(CONFIG_LOPEC)
macro_line|#include &lt;platforms/lopec_serial.h&gt;
macro_line|#elif defined(CONFIG_MCPN765)
macro_line|#include &lt;platforms/mcpn765_serial.h&gt;
macro_line|#elif defined(CONFIG_MVME5100)
macro_line|#include &lt;platforms/mvme5100_serial.h&gt;
macro_line|#elif defined(CONFIG_PRPMC750)
macro_line|#include &lt;platforms/prpmc750_serial.h&gt;
macro_line|#elif defined(CONFIG_PRPMC800)
macro_line|#include &lt;platforms/prpmc800_serial.h&gt;
macro_line|#elif defined(CONFIG_SANDPOINT)
macro_line|#include &lt;platforms/sandpoint_serial.h&gt;
macro_line|#elif defined(CONFIG_SPRUCE)
macro_line|#include &lt;platforms/spruce_serial.h&gt;
macro_line|#elif defined(CONFIG_ZX4500)
macro_line|#include &lt;platforms/zx4500_serial.h&gt;
macro_line|#elif defined(CONFIG_4xx)
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#else
multiline_comment|/*&n; * XXX Assume for now it has PC-style ISA serial ports.&n; * This is true for PReP and CHRP at least.&n; */
macro_line|#include &lt;asm/pc_serial.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#if defined(CONFIG_MAC_SERIAL)
DECL|macro|SERIAL_DEV_OFFSET
mdefine_line|#define SERIAL_DEV_OFFSET&t;((_machine == _MACH_prep || _machine == _MACH_chrp) ? 0 : 2)
macro_line|#endif
macro_line|#endif /* !CONFIG_GEMINI and others */
macro_line|#endif /* __ASM_SERIAL_H__ */
macro_line|#endif /* __KERNEL__ */
eof
