multiline_comment|/*&n; * Copyright 2003 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * Board specific definititions for the PMC-Sierra Yosemite&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __TITAN_DEP_H__
DECL|macro|__TITAN_DEP_H__
mdefine_line|#define __TITAN_DEP_H__
macro_line|#include &lt;asm/addrspace.h&gt;              /* for KSEG1ADDR() */
macro_line|#include &lt;asm/byteorder.h&gt;              /* for cpu_to_le32() */
multiline_comment|/* Turn on serial */
DECL|macro|CONFIG_TITAN_SERIAL
mdefine_line|#define&t;CONFIG_TITAN_SERIAL
multiline_comment|/* PCI */
DECL|macro|TITAN_PCI_BASE
mdefine_line|#define&t;TITAN_PCI_BASE&t;&t;&t;0xbb000000
DECL|macro|TITAN_WRITE
mdefine_line|#define TITAN_WRITE(ofs, data)  &bslash;&n;        *(volatile u32 *)(TITAN_PCI_BASE+(ofs)) = cpu_to_le32(data)
DECL|macro|TITAN_READ
mdefine_line|#define TITAN_READ(ofs, data)   &bslash;&n;        *(data) = le32_to_cpu(*(volatile u32 *)(TITAN_PCI_BASE+(ofs)))
DECL|macro|TITAN_READ_DATA
mdefine_line|#define TITAN_READ_DATA(ofs)    &bslash;&n;        le32_to_cpu(*(volatile u32 *)(TITAN_PCI_BASE+(ofs)))
DECL|macro|TITAN_WRITE_16
mdefine_line|#define TITAN_WRITE_16(ofs, data)  &bslash;&n;        *(volatile u16 *)(TITAN_PCI_BASE+(ofs)) = cpu_to_le16(data)
DECL|macro|TITAN_READ_16
mdefine_line|#define TITAN_READ_16(ofs, data)   &bslash;&n;        *(data) = le16_to_cpu(*(volatile u16 *)(TITAN_PCI_BASE+(ofs)))
DECL|macro|TITAN_WRITE_8
mdefine_line|#define TITAN_WRITE_8(ofs, data)  &bslash;&n;        *(volatile u8 *)(TITAN_PCI_BASE+(ofs)) = data
DECL|macro|TITAN_READ_8
mdefine_line|#define TITAN_READ_8(ofs, data)   &bslash;&n;        *(data) = *(volatile u8 *)(TITAN_PCI_BASE+(ofs))
multiline_comment|/*&n; * PCI specific defines&n; */
DECL|macro|TITAN_PCI_0_CONFIG_ADDRESS
mdefine_line|#define&t;TITAN_PCI_0_CONFIG_ADDRESS&t;0x780
DECL|macro|TITAN_PCI_0_CONFIG_DATA
mdefine_line|#define&t;TITAN_PCI_0_CONFIG_DATA&t;&t;0x784
multiline_comment|/*&n; * HT specific defines&n; */
DECL|macro|RM9000x2_HTLINK_REG
mdefine_line|#define RM9000x2_HTLINK_REG     0xbb000644
DECL|macro|RM9000x2_BASE_ADDR
mdefine_line|#define RM9000x2_BASE_ADDR      0xbb000000
DECL|macro|RM9000x2_OCD_HTCFGA
mdefine_line|#define RM9000x2_OCD_HTCFGA     0x06f8
DECL|macro|RM9000x2_OCD_HTCFGD
mdefine_line|#define RM9000x2_OCD_HTCFGD     0x06fc
multiline_comment|/*&n; * Hypertransport specific macros&n; */
DECL|macro|RM9K_WRITE
mdefine_line|#define RM9K_WRITE(ofs, data)   *(volatile u_int32_t *)(RM9000x2_BASE_ADDR+ofs) = data
DECL|macro|RM9K_WRITE_8
mdefine_line|#define RM9K_WRITE_8(ofs, data) *(volatile u8 *)(RM9000x2_BASE_ADDR+ofs) = data
DECL|macro|RM9K_WRITE_16
mdefine_line|#define RM9K_WRITE_16(ofs, data) *(volatile u16 *)(RM9000x2_BASE_ADDR+ofs) = data
DECL|macro|RM9K_READ
mdefine_line|#define RM9K_READ(ofs, val)     *(val) = *(volatile u_int32_t *)(RM9000x2_BASE_ADDR+ofs)
DECL|macro|RM9K_READ_8
mdefine_line|#define RM9K_READ_8(ofs, val)   *(val) = *(volatile u8 *)(RM9000x2_BASE_ADDR+ofs)
DECL|macro|RM9K_READ_16
mdefine_line|#define RM9K_READ_16(ofs, val)  *(val) = *(volatile u16 *)(RM9000x2_BASE_ADDR+ofs)
macro_line|#endif 
eof
