multiline_comment|/*&n; *&t;Low-Level PCI Support for MPC-1211&n; *&n; *      (c) 2002 Saito.K &amp; Jeanne&n; *&n; */
macro_line|#ifndef _PCI_MPC1211_H_
DECL|macro|_PCI_MPC1211_H_
mdefine_line|#define _PCI_MPC1211_H_
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* set debug level 4=verbose...1=terse */
singleline_comment|//#define DEBUG_PCI 3
DECL|macro|DEBUG_PCI
macro_line|#undef DEBUG_PCI
macro_line|#ifdef DEBUG_PCI
DECL|macro|PCIDBG
mdefine_line|#define PCIDBG(n, x...) { if(DEBUG_PCI&gt;=n) printk(x); }
macro_line|#else
DECL|macro|PCIDBG
mdefine_line|#define PCIDBG(n, x...)
macro_line|#endif
multiline_comment|/* startup values */
DECL|macro|PCI_PROBE_BIOS
mdefine_line|#define PCI_PROBE_BIOS    1
DECL|macro|PCI_PROBE_CONF1
mdefine_line|#define PCI_PROBE_CONF1   2
DECL|macro|PCI_PROBE_CONF2
mdefine_line|#define PCI_PROBE_CONF2   4
DECL|macro|PCI_NO_SORT
mdefine_line|#define PCI_NO_SORT       0x100
DECL|macro|PCI_BIOS_SORT
mdefine_line|#define PCI_BIOS_SORT     0x200
DECL|macro|PCI_NO_CHECKS
mdefine_line|#define PCI_NO_CHECKS     0x400
DECL|macro|PCI_ASSIGN_ROMS
mdefine_line|#define PCI_ASSIGN_ROMS   0x1000
DECL|macro|PCI_BIOS_IRQ_SCAN
mdefine_line|#define PCI_BIOS_IRQ_SCAN 0x2000
multiline_comment|/* MPC-1211 Specific Values */
DECL|macro|PCIPAR
mdefine_line|#define PCIPAR            (0xa4000cf8)    /* PCI Config address */
DECL|macro|PCIPDR
mdefine_line|#define PCIPDR            (0xa4000cfc)    /* PCI Config data    */
DECL|macro|PA_PCI_IO
mdefine_line|#define PA_PCI_IO         (0xa4000000)    /* PCI I/O space */
DECL|macro|PA_PCI_MEM
mdefine_line|#define PA_PCI_MEM        (0xb0000000)    /* PCI MEM space */
macro_line|#endif /* _PCI_MPC1211_H_ */
eof
