multiline_comment|/*&n; * BK Id: SCCS/s.ivms8.h 1.5 05/17/01 18:14:24 cort&n; */
multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * Speech Design Integrated Voicemail Systems (IVMS8) boards.&n; *&n; * Copyright (c) 2000 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_IVMS8_DEFS
DECL|macro|__MACH_IVMS8_DEFS
mdefine_line|#define __MACH_IVMS8_DEFS
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|interrupt_handler_t
r_typedef
r_void
(paren
id|interrupt_handler_t
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|struct|serial_io
r_typedef
r_struct
id|serial_io
(brace
DECL|member|getc
r_int
(paren
op_star
id|getc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|tstc
r_int
(paren
op_star
id|tstc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|putc
r_void
(paren
op_star
id|putc
)paren
(paren
r_const
r_char
id|c
)paren
suffix:semicolon
DECL|member|printf
r_void
(paren
op_star
id|printf
)paren
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|typedef|serial_io_t
)brace
id|serial_io_t
suffix:semicolon
DECL|struct|intr_util
r_typedef
r_struct
id|intr_util
(brace
DECL|member|install_hdlr
r_void
(paren
op_star
id|install_hdlr
)paren
(paren
r_int
comma
id|interrupt_handler_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|free_hdlr
r_void
(paren
op_star
id|free_hdlr
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|typedef|intr_util_t
)brace
id|intr_util_t
suffix:semicolon
multiline_comment|/* A Board Information structure that is given to a program when&n; * ppcboot starts it up.&n; */
DECL|struct|bd_info
r_typedef
r_struct
id|bd_info
(brace
DECL|member|bi_memstart
r_int
r_int
id|bi_memstart
suffix:semicolon
multiline_comment|/* start of  DRAM memory&t;&t;*/
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* size&t; of  DRAM memory in bytes&t;*/
DECL|member|bi_flashstart
r_int
r_int
id|bi_flashstart
suffix:semicolon
multiline_comment|/* start of FLASH memory&t;&t;*/
DECL|member|bi_flashsize
r_int
r_int
id|bi_flashsize
suffix:semicolon
multiline_comment|/* size&t; of FLASH memory&t;&t;*/
DECL|member|bi_flashoffset
r_int
r_int
id|bi_flashoffset
suffix:semicolon
multiline_comment|/* reserved area for startup monitor&t;*/
DECL|member|bi_sramstart
r_int
r_int
id|bi_sramstart
suffix:semicolon
multiline_comment|/* start of  SRAM memory&t;&t;*/
DECL|member|bi_sramsize
r_int
r_int
id|bi_sramsize
suffix:semicolon
multiline_comment|/* size&t; of  SRAM memory&t;&t;*/
DECL|member|bi_immr_base
r_int
r_int
id|bi_immr_base
suffix:semicolon
multiline_comment|/* base of IMMR register&t;&t;*/
DECL|member|bi_bootflags
r_int
r_int
id|bi_bootflags
suffix:semicolon
multiline_comment|/* boot / reboot flag (for LynxOS)&t;*/
DECL|member|bi_ip_addr
r_int
r_int
id|bi_ip_addr
suffix:semicolon
multiline_comment|/* IP Address&t;&t;&t;&t;*/
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet adress&t;&t;&t;*/
DECL|member|bi_reserved
r_int
r_char
id|bi_reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* -- just for alignment --&t;&t;*/
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in MHz&t;&t;*/
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in MHz&t;&t;&t;*/
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
multiline_comment|/* Console Baudrate&t;&t;&t;*/
DECL|member|bi_serial_io
id|serial_io_t
id|bi_serial_io
suffix:semicolon
multiline_comment|/* Addr of monitor fnc for Console I/O&t;*/
DECL|member|bi_interrupt
id|intr_util_t
id|bi_interrupt
suffix:semicolon
multiline_comment|/* Addr of monitor fnc for Interrupts&t;*/
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|IVMS_IMMR_BASE
mdefine_line|#define&t;IVMS_IMMR_BASE&t;0xFFF00000&t;/* phys. addr of IMMR&t;&t;&t;*/
DECL|macro|IVMS_IMAP_SIZE
mdefine_line|#define&t;IVMS_IMAP_SIZE&t;(64 * 1024)&t;/* size of mapped area&t;&t;&t;*/
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR&t;IVMS_IMMR_BASE&t;/* physical base address of IMMR area&t;*/
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;IVMS_IMAP_SIZE&t;/* mapped size of IMMR area&t;&t;*/
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;((uint)0xFE100000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;((uint)(64 * 1024))
DECL|macro|FEC_INTERRUPT
mdefine_line|#define&t;FEC_INTERRUPT&t; 9&t;&t;/* = SIU_LEVEL4&t;&t;&t;&t;*/
DECL|macro|IDE0_INTERRUPT
mdefine_line|#define IDE0_INTERRUPT&t;10&t;&t;/* = IRQ5&t;&t;&t;&t;*/
DECL|macro|CPM_INTERRUPT
mdefine_line|#define&t;CPM_INTERRUPT&t;11&t;&t;/* = SIU_LEVEL5 (was: SIU_LEVEL2)&t;*/
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;12&t;&t;/* = IRQ6&t;&t;&t;&t;*/
DECL|macro|MAX_HWIFS
mdefine_line|#define&t;MAX_HWIFS&t;1&t;/* overwrite default in include/asm-ppc/ide.h&t;*/
multiline_comment|/*&n; * Definitions for IDE0 Interface&n; */
DECL|macro|IDE0_BASE_OFFSET
mdefine_line|#define IDE0_BASE_OFFSET&t;&t;0x0000&t;/* Offset in PCMCIA memory&t;*/
DECL|macro|IDE0_DATA_REG_OFFSET
mdefine_line|#define IDE0_DATA_REG_OFFSET&t;&t;0x0000
DECL|macro|IDE0_ERROR_REG_OFFSET
mdefine_line|#define IDE0_ERROR_REG_OFFSET&t;&t;0x0081
DECL|macro|IDE0_NSECTOR_REG_OFFSET
mdefine_line|#define IDE0_NSECTOR_REG_OFFSET&t;&t;0x0082
DECL|macro|IDE0_SECTOR_REG_OFFSET
mdefine_line|#define IDE0_SECTOR_REG_OFFSET&t;&t;0x0083
DECL|macro|IDE0_LCYL_REG_OFFSET
mdefine_line|#define IDE0_LCYL_REG_OFFSET&t;&t;0x0084
DECL|macro|IDE0_HCYL_REG_OFFSET
mdefine_line|#define IDE0_HCYL_REG_OFFSET&t;&t;0x0085
DECL|macro|IDE0_SELECT_REG_OFFSET
mdefine_line|#define IDE0_SELECT_REG_OFFSET&t;&t;0x0086
DECL|macro|IDE0_STATUS_REG_OFFSET
mdefine_line|#define IDE0_STATUS_REG_OFFSET&t;&t;0x0087
DECL|macro|IDE0_CONTROL_REG_OFFSET
mdefine_line|#define IDE0_CONTROL_REG_OFFSET&t;&t;0x0106
DECL|macro|IDE0_IRQ_REG_OFFSET
mdefine_line|#define IDE0_IRQ_REG_OFFSET&t;&t;0x000A&t;/* not used&t;&t;&t;*/
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
multiline_comment|/* Generic 8xx type&n;*/
DECL|macro|_MACH_8xx
mdefine_line|#define _MACH_8xx (_MACH_ivms8)
macro_line|#endif&t;/* __MACH_IVMS8_DEFS */
eof
