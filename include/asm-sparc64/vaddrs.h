multiline_comment|/* $Id: vaddrs.h,v 1.10 1998/05/14 13:36:01 jj Exp $ */
macro_line|#ifndef _SPARC64_VADDRS_H
DECL|macro|_SPARC64_VADDRS_H
mdefine_line|#define _SPARC64_VADDRS_H
multiline_comment|/* asm-sparc64/vaddrs.h:  Here will be define the virtual addresses at&n; *                      which important I/O addresses will be mapped.&n; *                      For instance the timer register virtual address&n; *                      is defined here.&n; *&n; * Copyright (C) 1995,1998 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* Everything here must be in the first kernel PGD. */
DECL|macro|DVMA_VADDR
mdefine_line|#define  DVMA_VADDR     0x0000000100000000ULL  /* Base area of the DVMA on suns */
DECL|macro|DVMA_LEN
mdefine_line|#define  DVMA_LEN       0x0000000040000000ULL  /* Size of the DVMA address space */
DECL|macro|DVMA_END
mdefine_line|#define  DVMA_END       0x0000000140000000ULL
DECL|macro|MODULES_VADDR
mdefine_line|#define  MODULES_VADDR&t;0x0000000001000000ULL  /* Where to map modules */
DECL|macro|MODULES_LEN
mdefine_line|#define  MODULES_LEN&t;0x000000007f000000ULL
DECL|macro|MODULES_END
mdefine_line|#define  MODULES_END&t;0x0000000080000000ULL
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
