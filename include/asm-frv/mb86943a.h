multiline_comment|/* mb86943a.h: MB86943 SPARClite &lt;-&gt; PCI bridge registers&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MB86943A_H
DECL|macro|_ASM_MB86943A_H
mdefine_line|#define _ASM_MB86943A_H
macro_line|#include &lt;asm/mb-regs.h&gt;
DECL|macro|__reg_MB86943_sl_ctl
mdefine_line|#define __reg_MB86943_sl_ctl&t;&t;*(volatile uint32_t *) (__region_CS1 + 0x00)
DECL|macro|MB86943_SL_CTL_BUS_WIDTH_64
mdefine_line|#define MB86943_SL_CTL_BUS_WIDTH_64&t;0x00000001
DECL|macro|MB86943_SL_CTL_AS_HOST
mdefine_line|#define MB86943_SL_CTL_AS_HOST&t;&t;0x00000002
DECL|macro|MB86943_SL_CTL_DRCT_MASTER_SWAP
mdefine_line|#define MB86943_SL_CTL_DRCT_MASTER_SWAP&t;0x00000004
DECL|macro|MB86943_SL_CTL_DRCT_SLAVE_SWAP
mdefine_line|#define MB86943_SL_CTL_DRCT_SLAVE_SWAP&t;0x00000008
DECL|macro|MB86943_SL_CTL_PCI_CONFIG_SWAP
mdefine_line|#define MB86943_SL_CTL_PCI_CONFIG_SWAP&t;0x00000010
DECL|macro|MB86943_SL_CTL_ECS0_ENABLE
mdefine_line|#define MB86943_SL_CTL_ECS0_ENABLE&t;0x00000020
DECL|macro|MB86943_SL_CTL_ECS1_ENABLE
mdefine_line|#define MB86943_SL_CTL_ECS1_ENABLE&t;0x00000040
DECL|macro|MB86943_SL_CTL_ECS2_ENABLE
mdefine_line|#define MB86943_SL_CTL_ECS2_ENABLE&t;0x00000080
DECL|macro|__reg_MB86943_ecs_ctl
mdefine_line|#define __reg_MB86943_ecs_ctl(N)&t;*(volatile uint32_t *) (__region_CS1 + 0x08 + (0x08*(N)))
DECL|macro|__reg_MB86943_ecs_range
mdefine_line|#define __reg_MB86943_ecs_range(N)&t;*(volatile uint32_t *) (__region_CS1 + 0x20 + (0x10*(N)))
DECL|macro|__reg_MB86943_ecs_base
mdefine_line|#define __reg_MB86943_ecs_base(N)&t;*(volatile uint32_t *) (__region_CS1 + 0x28 + (0x10*(N)))
DECL|macro|__reg_MB86943_sl_pci_io_range
mdefine_line|#define __reg_MB86943_sl_pci_io_range&t;*(volatile uint32_t *) (__region_CS1 + 0x50)
DECL|macro|__reg_MB86943_sl_pci_io_base
mdefine_line|#define __reg_MB86943_sl_pci_io_base&t;*(volatile uint32_t *) (__region_CS1 + 0x58)
DECL|macro|__reg_MB86943_sl_pci_mem_range
mdefine_line|#define __reg_MB86943_sl_pci_mem_range&t;*(volatile uint32_t *) (__region_CS1 + 0x60)
DECL|macro|__reg_MB86943_sl_pci_mem_base
mdefine_line|#define __reg_MB86943_sl_pci_mem_base&t;*(volatile uint32_t *) (__region_CS1 + 0x68)
DECL|macro|__reg_MB86943_pci_sl_io_base
mdefine_line|#define __reg_MB86943_pci_sl_io_base&t;*(volatile uint32_t *) (__region_CS1 + 0x70)
DECL|macro|__reg_MB86943_pci_sl_mem_base
mdefine_line|#define __reg_MB86943_pci_sl_mem_base&t;*(volatile uint32_t *) (__region_CS1 + 0x78)
macro_line|#endif /* _ASM_MB86943A_H */
eof
