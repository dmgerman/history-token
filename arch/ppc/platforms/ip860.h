multiline_comment|/*&n; * MicroSys IP860 VMEBus board specific definitions&n; * &n; * Copyright (c) 2000, 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_IP860_H
DECL|macro|__MACH_IP860_H
mdefine_line|#define __MACH_IP860_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|IP860_IMMR_BASE
mdefine_line|#define&t;IP860_IMMR_BASE&t;0xF1000000&t;/* phys. addr of IMMR&t;&t;&t;*/
DECL|macro|IP860_IMAP_SIZE
mdefine_line|#define&t;IP860_IMAP_SIZE&t;(64 * 1024)&t;/* size of mapped area&t;&t;&t;*/
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR&t;IP860_IMMR_BASE&t;/* physical base address of IMMR area&t;*/
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;IP860_IMAP_SIZE&t;/* mapped size of IMMR area&t;&t;*/
multiline_comment|/*&n; * MPC8xx Chip Select Usage&n; */
DECL|macro|IP860_BOOT_CS
mdefine_line|#define&t;IP860_BOOT_CS&t;&t;0&t;/* Boot (VMEBus or Flash) Chip Select 0&t;*/
DECL|macro|IP860_FLASH_CS
mdefine_line|#define IP860_FLASH_CS&t;&t;1&t;/* Flash&t;    is on Chip Select 1&t;*/
DECL|macro|IP860_SDRAM_CS
mdefine_line|#define IP860_SDRAM_CS&t;&t;2&t;/* SDRAM&t;    is on Chip Select 2&t;*/
DECL|macro|IP860_SRAM_CS
mdefine_line|#define&t;IP860_SRAM_CS&t;&t;3&t;/* SRAM&t;&t;    is on Chip Select 3&t;*/
DECL|macro|IP860_BCSR_CS
mdefine_line|#define IP860_BCSR_CS&t;&t;4&t;/* BCSR&t;&t;    is on Chip Select 4&t;*/
DECL|macro|IP860_IP_CS
mdefine_line|#define IP860_IP_CS&t;&t;5&t;/* IP Slots&t;   are on Chip Select 5&t;*/
DECL|macro|IP860_VME_STD_CS
mdefine_line|#define IP860_VME_STD_CS&t;6&t;/* VME Standard I/O is on Chip Select 6&t;*/
DECL|macro|IP860_VME_SHORT_CS
mdefine_line|#define IP860_VME_SHORT_CS&t;7&t;/* VME Short    I/O is on Chip Select 7&t;*/
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif&t;/* __MACH_IP860_H */
eof
