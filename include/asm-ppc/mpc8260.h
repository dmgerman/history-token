multiline_comment|/* This is the single file included by all MPC8260 build options.&n; * Since there are many different boards and no standard configuration,&n; * we have a unique include file for each.  Rather than change every&n; * file that has to include MPC8260 configuration, they all include&n; * this one and the configuration switching is done here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __CONFIG_8260_DEFS
DECL|macro|__CONFIG_8260_DEFS
mdefine_line|#define __CONFIG_8260_DEFS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/mpc82xx.h&gt;
multiline_comment|/* Make sure the memory translation stuff is there if PCI not used.&n; */
macro_line|#ifndef _IO_BASE
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE        0
macro_line|#endif
macro_line|#ifndef _ISA_MEM_BASE
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE   0
macro_line|#endif
macro_line|#ifndef PCI_DRAM_OFFSET
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#endif
multiline_comment|/* Map 256MB I/O region&n; */
macro_line|#ifndef IO_PHYS_ADDR
DECL|macro|IO_PHYS_ADDR
mdefine_line|#define IO_PHYS_ADDR&t;0xe0000000
macro_line|#endif
macro_line|#ifndef IO_VIRT_ADDR
DECL|macro|IO_VIRT_ADDR
mdefine_line|#define IO_VIRT_ADDR&t;IO_PHYS_ADDR
macro_line|#endif
multiline_comment|/* The &quot;residual&quot; data board information structure the boot loader&n; * hands to us.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
macro_line|#endif /* !__CONFIG_8260_DEFS */
macro_line|#endif /* __KERNEL__ */
eof
