multiline_comment|/*&n; * linux/include/asm-arm/arch-iop80310/hardware.h&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Note about PCI IO space mappings&n; *&n; * To make IO space accesses efficient, we store virtual addresses in&n; * the IO resources.&n; *&n; * The PCI IO space is located at virtual 0xfe000000 from physical&n; * 0x90000000.  The PCI BARs must be programmed with physical addresses,&n; * but when we read them, we convert them to virtual addresses.  See&n; * arch/arm/mach-iop310/iop310-pci.c&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses() 1
multiline_comment|/*&n; * these are the values for the secondary PCI bus on the 80312 chip.  I will&n; * have to do some fixup in the bus/dev fixup code&n; */
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO      0
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM     0x88000000
singleline_comment|// Generic chipset bits
macro_line|#include &quot;iop310.h&quot;
singleline_comment|// Board specific
macro_line|#if defined(CONFIG_ARCH_IQ80310)
macro_line|#include &quot;iq80310.h&quot;
macro_line|#endif
macro_line|#endif  /* _ASM_ARCH_HARDWARE_H */
eof
