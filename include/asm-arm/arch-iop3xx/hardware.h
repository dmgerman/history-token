multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/hardware.h&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * Note about PCI IO space mappings&n; *&n; * To make IO space accesses efficient, we store virtual addresses in&n; * the IO resources.&n; *&n; * The PCI IO space is located at virtual 0xfe000000 from physical&n; * 0x90000000.  The PCI BARs must be programmed with physical addresses,&n; * but when we read them, we convert them to virtual addresses.  See&n; * arch/arm/mach-iop3xx/iop3xx-pci.c&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses() 1
multiline_comment|/*&n; * The min PCI I/O and MEM space are dependent on what specific&n; * chipset/platform we are running on, so instead of hardcoding with&n; * #ifdefs, we just fill these in the platform level PCI init code.&n; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|iop3xx_pcibios_min_io
suffix:semicolon
r_extern
r_int
r_int
id|iop3xx_pcibios_min_mem
suffix:semicolon
r_extern
r_int
r_int
id|processor_id
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * We just set these to zero since they are really bogus anyways&n; */
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO      (iop3xx_pcibios_min_io)
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM     (iop3xx_pcibios_min_mem)
multiline_comment|/*&n; * Generic chipset bits&n; *&n; */
macro_line|#include &quot;iop321.h&quot;
macro_line|#include &quot;iop331.h&quot;
multiline_comment|/*&n; * Board specific bits&n; */
macro_line|#include &quot;iq80321.h&quot;
macro_line|#include &quot;iq31244.h&quot;
macro_line|#include &quot;iq80331.h&quot;
macro_line|#include &quot;iq80332.h&quot;
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
