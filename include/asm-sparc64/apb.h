multiline_comment|/* $Id: apb.h,v 1.2 1998/04/01 20:41:49 ecd Exp $&n; * apb.h: Advanced PCI Bridge Configuration Registers and Bits&n; *&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC64_APB_H
DECL|macro|_SPARC64_APB_H
mdefine_line|#define _SPARC64_APB_H
DECL|macro|APB_TICK_REGISTER
mdefine_line|#define APB_TICK_REGISTER&t;&t;&t;0xb0
DECL|macro|APB_INT_ACK
mdefine_line|#define APB_INT_ACK&t;&t;&t;&t;0xb8
DECL|macro|APB_PRIMARY_MASTER_RETRY_LIMIT
mdefine_line|#define APB_PRIMARY_MASTER_RETRY_LIMIT&t;&t;0xc0
DECL|macro|APB_DMA_ASFR
mdefine_line|#define APB_DMA_ASFR&t;&t;&t;&t;0xc8
DECL|macro|APB_DMA_AFAR
mdefine_line|#define APB_DMA_AFAR&t;&t;&t;&t;0xd0
DECL|macro|APB_PIO_TARGET_RETRY_LIMIT
mdefine_line|#define APB_PIO_TARGET_RETRY_LIMIT&t;&t;0xd8
DECL|macro|APB_PIO_TARGET_LATENCY_TIMER
mdefine_line|#define APB_PIO_TARGET_LATENCY_TIMER&t;&t;0xd9
DECL|macro|APB_DMA_TARGET_RETRY_LIMIT
mdefine_line|#define APB_DMA_TARGET_RETRY_LIMIT&t;&t;0xda
DECL|macro|APB_DMA_TARGET_LATENCY_TIMER
mdefine_line|#define APB_DMA_TARGET_LATENCY_TIMER&t;&t;0xdb
DECL|macro|APB_SECONDARY_MASTER_RETRY_LIMIT
mdefine_line|#define APB_SECONDARY_MASTER_RETRY_LIMIT&t;0xdc
DECL|macro|APB_SECONDARY_CONTROL
mdefine_line|#define APB_SECONDARY_CONTROL&t;&t;&t;0xdd
DECL|macro|APB_IO_ADDRESS_MAP
mdefine_line|#define APB_IO_ADDRESS_MAP&t;&t;&t;0xde
DECL|macro|APB_MEM_ADDRESS_MAP
mdefine_line|#define APB_MEM_ADDRESS_MAP&t;&t;&t;0xdf
DECL|macro|APB_PCI_CONTROL_LOW
mdefine_line|#define APB_PCI_CONTROL_LOW&t;&t;&t;0xe0
DECL|macro|APB_PCI_CTL_LOW_ARB_PARK
macro_line|#  define APB_PCI_CTL_LOW_ARB_PARK&t;&t;&t;(1 &lt;&lt; 21)
DECL|macro|APB_PCI_CTL_LOW_ERRINT_EN
macro_line|#  define APB_PCI_CTL_LOW_ERRINT_EN&t;&t;&t;(1 &lt;&lt; 8)
DECL|macro|APB_PCI_CONTROL_HIGH
mdefine_line|#define APB_PCI_CONTROL_HIGH&t;&t;&t;0xe4
DECL|macro|APB_PCI_CTL_HIGH_SERR
macro_line|#  define APB_PCI_CTL_HIGH_SERR&t;&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|APB_PCI_CTL_HIGH_ARBITER_EN
macro_line|#  define APB_PCI_CTL_HIGH_ARBITER_EN&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|APB_PIO_ASFR
mdefine_line|#define APB_PIO_ASFR&t;&t;&t;&t;0xe8
DECL|macro|APB_PIO_AFAR
mdefine_line|#define APB_PIO_AFAR&t;&t;&t;&t;0xf0
DECL|macro|APB_DIAG_REGISTER
mdefine_line|#define APB_DIAG_REGISTER&t;&t;&t;0xf8
macro_line|#endif /* !(_SPARC64_APB_H) */
eof
