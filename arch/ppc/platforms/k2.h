multiline_comment|/*&n; * arch/ppc/platforms/k2.h&n; * &n; * Definitions for SBS K2 board support&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __PPC_PLATFORMS_K2_H
DECL|macro|__PPC_PLATFORMS_K2_H
mdefine_line|#define __PPC_PLATFORMS_K2_H
multiline_comment|/*&n; * SBS K2 definitions&n; */
DECL|macro|K2_PCI64_BAR
mdefine_line|#define&t;K2_PCI64_BAR&t;&t;0xff400000
DECL|macro|K2_PCI32_BAR
mdefine_line|#define&t;K2_PCI32_BAR&t;&t;0xff500000
DECL|macro|K2_PCI64_CONFIG_ADDR
mdefine_line|#define K2_PCI64_CONFIG_ADDR&t;(K2_PCI64_BAR + 0x000f8000)
DECL|macro|K2_PCI64_CONFIG_DATA
mdefine_line|#define K2_PCI64_CONFIG_DATA&t;(K2_PCI64_BAR + 0x000f8010)
DECL|macro|K2_PCI32_CONFIG_ADDR
mdefine_line|#define K2_PCI32_CONFIG_ADDR&t;(K2_PCI32_BAR + 0x000f8000)
DECL|macro|K2_PCI32_CONFIG_DATA
mdefine_line|#define K2_PCI32_CONFIG_DATA&t;(K2_PCI32_BAR + 0x000f8010)
DECL|macro|K2_PCI64_MEM_BASE
mdefine_line|#define K2_PCI64_MEM_BASE&t;0xd0000000
DECL|macro|K2_PCI64_IO_BASE
mdefine_line|#define K2_PCI64_IO_BASE&t;0x80100000
DECL|macro|K2_PCI32_MEM_BASE
mdefine_line|#define K2_PCI32_MEM_BASE&t;0xc0000000
DECL|macro|K2_PCI32_IO_BASE
mdefine_line|#define K2_PCI32_IO_BASE&t;0x80000000
DECL|macro|K2_PCI32_SYS_MEM_BASE
mdefine_line|#define K2_PCI32_SYS_MEM_BASE&t;0x80000000
DECL|macro|K2_PCI64_SYS_MEM_BASE
mdefine_line|#define K2_PCI64_SYS_MEM_BASE&t;K2_PCI32_SYS_MEM_BASE
DECL|macro|K2_PCI32_LOWER_MEM
mdefine_line|#define K2_PCI32_LOWER_MEM&t;0x00000000
DECL|macro|K2_PCI32_UPPER_MEM
mdefine_line|#define K2_PCI32_UPPER_MEM&t;0x0fffffff
DECL|macro|K2_PCI32_LOWER_IO
mdefine_line|#define K2_PCI32_LOWER_IO&t;0x00000000
DECL|macro|K2_PCI32_UPPER_IO
mdefine_line|#define K2_PCI32_UPPER_IO&t;0x000fffff
DECL|macro|K2_PCI64_LOWER_MEM
mdefine_line|#define K2_PCI64_LOWER_MEM&t;0x10000000
DECL|macro|K2_PCI64_UPPER_MEM
mdefine_line|#define K2_PCI64_UPPER_MEM&t;0x1fffffff
DECL|macro|K2_PCI64_LOWER_IO
mdefine_line|#define K2_PCI64_LOWER_IO&t;0x00100000
DECL|macro|K2_PCI64_UPPER_IO
mdefine_line|#define&t;K2_PCI64_UPPER_IO&t;0x001fffff
DECL|macro|K2_ISA_IO_BASE
mdefine_line|#define K2_ISA_IO_BASE&t;&t;K2_PCI32_IO_BASE
DECL|macro|K2_ISA_MEM_BASE
mdefine_line|#define K2_ISA_MEM_BASE&t;&t;K2_PCI32_MEM_BASE
DECL|macro|K2_BOARD_ID_REG
mdefine_line|#define K2_BOARD_ID_REG&t;&t;(K2_ISA_IO_BASE + 0x800)
DECL|macro|K2_MISC_REG
mdefine_line|#define K2_MISC_REG&t;&t;(K2_ISA_IO_BASE + 0x804)
DECL|macro|K2_MSIZ_GEO_REG
mdefine_line|#define K2_MSIZ_GEO_REG&t;&t;(K2_ISA_IO_BASE + 0x808)
DECL|macro|K2_HOT_SWAP_REG
mdefine_line|#define K2_HOT_SWAP_REG&t;&t;(K2_ISA_IO_BASE + 0x80c)
DECL|macro|K2_PLD2_REG
mdefine_line|#define K2_PLD2_REG&t;&t;(K2_ISA_IO_BASE + 0x80e)
DECL|macro|K2_PLD3_REG
mdefine_line|#define K2_PLD3_REG&t;&t;(K2_ISA_IO_BASE + 0x80f)
DECL|macro|K2_BUS_SPD
mdefine_line|#define K2_BUS_SPD(board_id)&t;(board_id &gt;&gt; 2) &amp; 3
DECL|macro|K2_RTC_BASE_OFFSET
mdefine_line|#define K2_RTC_BASE_OFFSET&t;0x90000
DECL|macro|K2_RTC_BASE_ADDRESS
mdefine_line|#define K2_RTC_BASE_ADDRESS&t;(K2_PCI32_MEM_BASE + K2_RTC_BASE_OFFSET)
DECL|macro|K2_RTC_SIZE
mdefine_line|#define K2_RTC_SIZE&t;&t;0x8000
DECL|macro|K2_MEM_SIZE_MASK
mdefine_line|#define K2_MEM_SIZE_MASK&t;0xe0
DECL|macro|K2_MEM_SIZE
mdefine_line|#define K2_MEM_SIZE(size_reg)&t;(size_reg &amp; K2_MEM_SIZE_MASK) &gt;&gt; 5
DECL|macro|K2_MEM_SIZE_1GB
mdefine_line|#define&t;K2_MEM_SIZE_1GB&t;&t;0x40000000
DECL|macro|K2_MEM_SIZE_512MB
mdefine_line|#define K2_MEM_SIZE_512MB&t;0x20000000
DECL|macro|K2_MEM_SIZE_256MB
mdefine_line|#define K2_MEM_SIZE_256MB&t;0x10000000
DECL|macro|K2_MEM_SIZE_128MB
mdefine_line|#define K2_MEM_SIZE_128MB&t;0x08000000
DECL|macro|K2_L2CACHE_MASK
mdefine_line|#define K2_L2CACHE_MASK&t;&t;0x03&t;/* Mask for 2 L2 Cache bits */
DECL|macro|K2_L2CACHE_512KB
mdefine_line|#define K2_L2CACHE_512KB&t;0x00&t;/* 512KB */
DECL|macro|K2_L2CACHE_256KB
mdefine_line|#define K2_L2CACHE_256KB&t;0x01&t;/* 256KB */
DECL|macro|K2_L2CACHE_1MB
mdefine_line|#define K2_L2CACHE_1MB&t;&t;0x02&t;/* 1MB */
DECL|macro|K2_L2CACHE_NONE
mdefine_line|#define K2_L2CACHE_NONE&t;&t;0x03&t;/* None */
DECL|macro|K2_GEO_ADR_MASK
mdefine_line|#define K2_GEO_ADR_MASK&t;&t;0x1f
DECL|macro|K2_SYS_SLOT_MASK
mdefine_line|#define K2_SYS_SLOT_MASK&t;0x08
macro_line|#endif /* __PPC_PLATFORMS_K2_H */
eof
