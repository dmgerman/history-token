multiline_comment|/*&n; *  asm-ppc/raven.h -- Raven MPIC chip.&n; *&n; *  Copyright (C) 1998 Johnnie Peters&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASMPPC_RAVEN_H
DECL|macro|_ASMPPC_RAVEN_H
mdefine_line|#define _ASMPPC_RAVEN_H
DECL|macro|MVME2600_INT_SIO
mdefine_line|#define MVME2600_INT_SIO&t;&t;0
DECL|macro|MVME2600_INT_FALCN_ECC_ERR
mdefine_line|#define MVME2600_INT_FALCN_ECC_ERR&t;1
DECL|macro|MVME2600_INT_PCI_ETHERNET
mdefine_line|#define MVME2600_INT_PCI_ETHERNET&t;2
DECL|macro|MVME2600_INT_PCI_SCSI
mdefine_line|#define MVME2600_INT_PCI_SCSI&t;&t;3
DECL|macro|MVME2600_INT_PCI_GRAPHICS
mdefine_line|#define MVME2600_INT_PCI_GRAPHICS&t;4
DECL|macro|MVME2600_INT_PCI_VME0
mdefine_line|#define MVME2600_INT_PCI_VME0&t;&t;5
DECL|macro|MVME2600_INT_PCI_VME1
mdefine_line|#define MVME2600_INT_PCI_VME1&t;&t;6
DECL|macro|MVME2600_INT_PCI_VME2
mdefine_line|#define MVME2600_INT_PCI_VME2&t;&t;7
DECL|macro|MVME2600_INT_PCI_VME3
mdefine_line|#define MVME2600_INT_PCI_VME3&t;&t;8
DECL|macro|MVME2600_INT_PCI_INTA
mdefine_line|#define MVME2600_INT_PCI_INTA&t;&t;9
DECL|macro|MVME2600_INT_PCI_INTB
mdefine_line|#define MVME2600_INT_PCI_INTB&t;&t;10
DECL|macro|MVME2600_INT_PCI_INTC
mdefine_line|#define MVME2600_INT_PCI_INTC &t;&t;11
DECL|macro|MVME2600_INT_PCI_INTD
mdefine_line|#define MVME2600_INT_PCI_INTD &t;&t;12
DECL|macro|MVME2600_INT_LM_SIG0
mdefine_line|#define MVME2600_INT_LM_SIG0&t;&t;13
DECL|macro|MVME2600_INT_LM_SIG1
mdefine_line|#define MVME2600_INT_LM_SIG1&t;&t;14
r_extern
r_struct
id|hw_interrupt_type
id|raven_pic
suffix:semicolon
r_extern
r_int
id|raven_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASMPPC_RAVEN_H */
macro_line|#endif /* __KERNEL__ */
eof
