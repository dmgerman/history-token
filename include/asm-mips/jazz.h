multiline_comment|/* $Id: jazz.h,v 1.9 1998/09/19 19:19:37 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 - 1998 by Andreas Busse and Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_JAZZ_H 
DECL|macro|__ASM_MIPS_JAZZ_H
mdefine_line|#define __ASM_MIPS_JAZZ_H 
multiline_comment|/*&n; * The addresses below are virtual address. The mappings are&n; * created on startup via wired entries in the tlb. The Mips&n; * Magnum R3000 and R4000 machines are similar in many aspects,&n; * but many hardware register are accessible at 0xb9000000 in&n; * instead of 0xe0000000.&n; */
DECL|macro|JAZZ_LOCAL_IO_SPACE
mdefine_line|#define JAZZ_LOCAL_IO_SPACE     0xe0000000
multiline_comment|/*&n; * Revision numbers in PICA_ASIC_REVISION&n; *&n; * 0xf0000000 - Rev1&n; * 0xf0000001 - Rev2&n; * 0xf0000002 - Rev3&n; */
DECL|macro|PICA_ASIC_REVISION
mdefine_line|#define PICA_ASIC_REVISION      0xe0000008
multiline_comment|/*&n; * The segments of the seven segment LED are mapped&n; * to the control bits as follows:&n; *&n; *         (7)&n; *      ---------&n; *      |       |&n; *  (2) |       | (6)&n; *      |  (1)  |&n; *      ---------&n; *      |       |&n; *  (3) |       | (5)&n; *      |  (4)  |&n; *      --------- . (0)&n; */
DECL|macro|PICA_LED
mdefine_line|#define PICA_LED                0xe000f000
multiline_comment|/*&n; * Some characters for the LED control registers&n; * The original Mips machines seem to have a LED display&n; * with integrated decoder while the Acer machines can&n; * control each of the seven segments and the dot independently.&n; * It&squot;s only a toy, anyway...&n; */
DECL|macro|LED_DOT
mdefine_line|#define LED_DOT                 0x01
DECL|macro|LED_SPACE
mdefine_line|#define LED_SPACE               0x00
DECL|macro|LED_0
mdefine_line|#define LED_0                   0xfc
DECL|macro|LED_1
mdefine_line|#define LED_1                   0x60
DECL|macro|LED_2
mdefine_line|#define LED_2                   0xda
DECL|macro|LED_3
mdefine_line|#define LED_3                   0xf2
DECL|macro|LED_4
mdefine_line|#define LED_4                   0x66
DECL|macro|LED_5
mdefine_line|#define LED_5                   0xb6
DECL|macro|LED_6
mdefine_line|#define LED_6                   0xbe
DECL|macro|LED_7
mdefine_line|#define LED_7                   0xe0
DECL|macro|LED_8
mdefine_line|#define LED_8                   0xfe
DECL|macro|LED_9
mdefine_line|#define LED_9                   0xf6
DECL|macro|LED_A
mdefine_line|#define LED_A                   0xee
DECL|macro|LED_b
mdefine_line|#define LED_b                   0x3e
DECL|macro|LED_C
mdefine_line|#define LED_C                   0x9c
DECL|macro|LED_d
mdefine_line|#define LED_d                   0x7a
DECL|macro|LED_E
mdefine_line|#define LED_E                   0x9e
DECL|macro|LED_F
mdefine_line|#define LED_F                   0x8e
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|function|pica_set_led
r_extern
id|__inline__
r_void
id|pica_set_led
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
r_volatile
r_int
r_int
op_star
id|led_register
op_assign
(paren
r_int
r_int
op_star
)paren
id|PICA_LED
suffix:semicolon
op_star
id|led_register
op_assign
id|bits
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Base address of the Sonic Ethernet adapter in Jazz machines.&n; */
DECL|macro|JAZZ_ETHERNET_BASE
mdefine_line|#define JAZZ_ETHERNET_BASE  0xe0001000
multiline_comment|/*&n; * Base address of the 53C94 SCSI hostadapter in Jazz machines.&n; */
DECL|macro|JAZZ_SCSI_BASE
mdefine_line|#define JAZZ_SCSI_BASE&t;&t;0xe0002000
multiline_comment|/*&n; * i8042 keyboard controller for JAZZ and PICA chipsets.&n; * This address is just a guess and seems to differ from&n; * other mips machines such as RC3xxx...&n; */
DECL|macro|JAZZ_KEYBOARD_ADDRESS
mdefine_line|#define JAZZ_KEYBOARD_ADDRESS   0xe0005000
DECL|macro|JAZZ_KEYBOARD_DATA
mdefine_line|#define JAZZ_KEYBOARD_DATA      0xe0005000
DECL|macro|JAZZ_KEYBOARD_COMMAND
mdefine_line|#define JAZZ_KEYBOARD_COMMAND   0xe0005001
macro_line|#ifndef _LANGUAGE_ASSEMBLY
r_typedef
r_struct
(brace
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|typedef|jazz_keyboard_hardware
)brace
id|jazz_keyboard_hardware
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pad0
r_int
r_char
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|typedef|mips_keyboard_hardware
)brace
id|mips_keyboard_hardware
suffix:semicolon
multiline_comment|/*&n; * For now. Needs to be changed for RC3xxx support. See below.&n; */
DECL|macro|keyboard_hardware
mdefine_line|#define keyboard_hardware       jazz_keyboard_hardware
macro_line|#endif
multiline_comment|/*&n; * i8042 keyboard controller for most other Mips machines.&n; */
DECL|macro|MIPS_KEYBOARD_ADDRESS
mdefine_line|#define MIPS_KEYBOARD_ADDRESS   0xb9005000
DECL|macro|MIPS_KEYBOARD_DATA
mdefine_line|#define MIPS_KEYBOARD_DATA      0xb9005003
DECL|macro|MIPS_KEYBOARD_COMMAND
mdefine_line|#define MIPS_KEYBOARD_COMMAND   0xb9005007
multiline_comment|/*&n; * Serial and parallel ports (WD 16C552) on the Mips JAZZ&n; */
DECL|macro|JAZZ_SERIAL1_BASE
mdefine_line|#define JAZZ_SERIAL1_BASE       (unsigned int)0xe0006000
DECL|macro|JAZZ_SERIAL2_BASE
mdefine_line|#define JAZZ_SERIAL2_BASE       (unsigned int)0xe0007000
DECL|macro|JAZZ_PARALLEL_BASE
mdefine_line|#define JAZZ_PARALLEL_BASE      (unsigned int)0xe0008000
multiline_comment|/*&n; * Dummy Device Address. Used in jazzdma.c&n; */
DECL|macro|JAZZ_DUMMY_DEVICE
mdefine_line|#define JAZZ_DUMMY_DEVICE       0xe000d000
multiline_comment|/*&n; * JAZZ timer registers and interrupt no.&n; * Note that the hardware timer interrupt is actually on&n; * cpu level 6, but to keep compatibility with PC stuff&n; * it is remapped to vector 0. See arch/mips/kernel/entry.S.&n; */
DECL|macro|JAZZ_TIMER_INTERVAL
mdefine_line|#define JAZZ_TIMER_INTERVAL     0xe0000228
DECL|macro|JAZZ_TIMER_REGISTER
mdefine_line|#define JAZZ_TIMER_REGISTER     0xe0000230
multiline_comment|/*&n; * DRAM configuration register&n; */
macro_line|#ifndef _LANGUAGE_ASSEMBLY
macro_line|#ifdef __MIPSEL__
r_typedef
r_struct
(brace
DECL|member|bank2
r_int
r_int
id|bank2
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bank1
r_int
r_int
id|bank1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|mem_bus_width
r_int
r_int
id|mem_bus_width
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_mode
r_int
r_int
id|page_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|23
suffix:semicolon
DECL|typedef|dram_configuration
)brace
id|dram_configuration
suffix:semicolon
macro_line|#else /* defined (__MIPSEB__) */
r_typedef
r_struct
(brace
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|23
suffix:semicolon
DECL|member|page_mode
r_int
r_int
id|page_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mem_bus_width
r_int
r_int
id|mem_bus_width
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bank1
r_int
r_int
id|bank1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bank2
r_int
r_int
id|bank2
suffix:colon
l_int|3
suffix:semicolon
DECL|typedef|dram_configuration
)brace
id|dram_configuration
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
DECL|macro|PICA_DRAM_CONFIG
mdefine_line|#define PICA_DRAM_CONFIG        0xe00fffe0
multiline_comment|/*&n; * JAZZ interrupt control registers&n; */
DECL|macro|JAZZ_IO_IRQ_SOURCE
mdefine_line|#define JAZZ_IO_IRQ_SOURCE      0xe0010000
DECL|macro|JAZZ_IO_IRQ_ENABLE
mdefine_line|#define JAZZ_IO_IRQ_ENABLE      0xe0010002
multiline_comment|/*&n; * JAZZ interrupt enable bits&n; */
DECL|macro|JAZZ_IE_PARALLEL
mdefine_line|#define JAZZ_IE_PARALLEL            (1 &lt;&lt; 0)
DECL|macro|JAZZ_IE_FLOPPY
mdefine_line|#define JAZZ_IE_FLOPPY              (1 &lt;&lt; 1)
DECL|macro|JAZZ_IE_SOUND
mdefine_line|#define JAZZ_IE_SOUND               (1 &lt;&lt; 2)
DECL|macro|JAZZ_IE_VIDEO
mdefine_line|#define JAZZ_IE_VIDEO               (1 &lt;&lt; 3)
DECL|macro|JAZZ_IE_ETHERNET
mdefine_line|#define JAZZ_IE_ETHERNET            (1 &lt;&lt; 4)
DECL|macro|JAZZ_IE_SCSI
mdefine_line|#define JAZZ_IE_SCSI                (1 &lt;&lt; 5)
DECL|macro|JAZZ_IE_KEYBOARD
mdefine_line|#define JAZZ_IE_KEYBOARD            (1 &lt;&lt; 6)
DECL|macro|JAZZ_IE_MOUSE
mdefine_line|#define JAZZ_IE_MOUSE               (1 &lt;&lt; 7)
DECL|macro|JAZZ_IE_SERIAL1
mdefine_line|#define JAZZ_IE_SERIAL1             (1 &lt;&lt; 8)
DECL|macro|JAZZ_IE_SERIAL2
mdefine_line|#define JAZZ_IE_SERIAL2             (1 &lt;&lt; 9)
multiline_comment|/*&n; * JAZZ Interrupt Level definitions&n; *&n; * This is somewhat broken.  For reasons which nobody can remember anymore&n; * we remap the Jazz interrupts to the usual ISA style interrupt numbers.&n; */
DECL|macro|JAZZ_PARALLEL_IRQ
mdefine_line|#define JAZZ_PARALLEL_IRQ       16
DECL|macro|JAZZ_FLOPPY_IRQ
mdefine_line|#define JAZZ_FLOPPY_IRQ          6 /* needs to be consistent with floppy driver! */
DECL|macro|JAZZ_SOUND_IRQ
mdefine_line|#define JAZZ_SOUND_IRQ          18
DECL|macro|JAZZ_VIDEO_IRQ
mdefine_line|#define JAZZ_VIDEO_IRQ          19
DECL|macro|JAZZ_ETHERNET_IRQ
mdefine_line|#define JAZZ_ETHERNET_IRQ       20
DECL|macro|JAZZ_SCSI_IRQ
mdefine_line|#define JAZZ_SCSI_IRQ           21
DECL|macro|JAZZ_KEYBOARD_IRQ
mdefine_line|#define JAZZ_KEYBOARD_IRQ       22
DECL|macro|JAZZ_MOUSE_IRQ
mdefine_line|#define JAZZ_MOUSE_IRQ          23
DECL|macro|JAZZ_SERIAL1_IRQ
mdefine_line|#define JAZZ_SERIAL1_IRQ        24
DECL|macro|JAZZ_SERIAL2_IRQ
mdefine_line|#define JAZZ_SERIAL2_IRQ        25
DECL|macro|JAZZ_TIMER_IRQ
mdefine_line|#define JAZZ_TIMER_IRQ          31
multiline_comment|/*&n; * JAZZ DMA Channels&n; * Note: Channels 4...7 are not used with respect to the Acer PICA-61&n; * chipset which does not provide these DMA channels.&n; */
DECL|macro|JAZZ_SCSI_DMA
mdefine_line|#define JAZZ_SCSI_DMA           0              /* SCSI */
DECL|macro|JAZZ_FLOPPY_DMA
mdefine_line|#define JAZZ_FLOPPY_DMA         1              /* FLOPPY */
DECL|macro|JAZZ_AUDIOL_DMA
mdefine_line|#define JAZZ_AUDIOL_DMA         2              /* AUDIO L */
DECL|macro|JAZZ_AUDIOR_DMA
mdefine_line|#define JAZZ_AUDIOR_DMA         3              /* AUDIO R */
multiline_comment|/*&n; * JAZZ R4030 MCT_ADR chip (DMA controller)&n; * Note: Virtual Addresses !&n; */
DECL|macro|JAZZ_R4030_CONFIG
mdefine_line|#define JAZZ_R4030_CONFIG&t;0xE0000000&t;/* R4030 config register */
DECL|macro|JAZZ_R4030_REVISION
mdefine_line|#define JAZZ_R4030_REVISION     0xE0000008&t;/* same as PICA_ASIC_REVISION */
DECL|macro|JAZZ_R4030_INV_ADDR
mdefine_line|#define JAZZ_R4030_INV_ADDR&t;0xE0000010&t;/* Invalid Address register */
DECL|macro|JAZZ_R4030_TRSTBL_BASE
mdefine_line|#define JAZZ_R4030_TRSTBL_BASE  0xE0000018&t;/* Translation Table Base */
DECL|macro|JAZZ_R4030_TRSTBL_LIM
mdefine_line|#define JAZZ_R4030_TRSTBL_LIM   0xE0000020&t;/* Translation Table Limit */
DECL|macro|JAZZ_R4030_TRSTBL_INV
mdefine_line|#define JAZZ_R4030_TRSTBL_INV   0xE0000028&t;/* Translation Table Invalidate */
DECL|macro|JAZZ_R4030_CACHE_MTNC
mdefine_line|#define JAZZ_R4030_CACHE_MTNC   0xE0000030&t;/* Cache Maintenance */
DECL|macro|JAZZ_R4030_R_FAIL_ADDR
mdefine_line|#define JAZZ_R4030_R_FAIL_ADDR  0xE0000038&t;/* Remote Failed Address */
DECL|macro|JAZZ_R4030_M_FAIL_ADDR
mdefine_line|#define JAZZ_R4030_M_FAIL_ADDR  0xE0000040&t;/* Memory Failed Address */
DECL|macro|JAZZ_R4030_CACHE_PTAG
mdefine_line|#define JAZZ_R4030_CACHE_PTAG   0xE0000048&t;/* I/O Cache Physical Tag */
DECL|macro|JAZZ_R4030_CACHE_LTAG
mdefine_line|#define JAZZ_R4030_CACHE_LTAG   0xE0000050&t;/* I/O Cache Logical Tag */
DECL|macro|JAZZ_R4030_CACHE_BMASK
mdefine_line|#define JAZZ_R4030_CACHE_BMASK  0xE0000058&t;/* I/O Cache Byte Mask */
DECL|macro|JAZZ_R4030_CACHE_BWIN
mdefine_line|#define JAZZ_R4030_CACHE_BWIN   0xE0000060&t;/* I/O Cache Buffer Window */
multiline_comment|/*&n; * Remote Speed Registers. &n; *&n; *  0: free,      1: Ethernet,  2: SCSI,      3: Floppy,&n; *  4: RTC,       5: Kb./Mouse  6: serial 1,  7: serial 2,&n; *  8: parallel,  9: NVRAM,    10: CPU,      11: PROM,&n; * 12: reserved, 13: free,     14: 7seg LED, 15: ???&n; */
DECL|macro|JAZZ_R4030_REM_SPEED
mdefine_line|#define JAZZ_R4030_REM_SPEED&t;0xE0000070&t;/* 16 Remote Speed Registers */
multiline_comment|/* 0xE0000070,78,80... 0xE00000E8 */
DECL|macro|JAZZ_R4030_IRQ_ENABLE
mdefine_line|#define JAZZ_R4030_IRQ_ENABLE   0xE00000E8&t;/* Internal Interrupt Enable */
DECL|macro|JAZZ_R4030_INVAL_ADDR
mdefine_line|#define JAZZ_R4030_INVAL_ADDR   0xE0000010&t;/* Invalid address Register */
DECL|macro|JAZZ_R4030_IRQ_SOURCE
mdefine_line|#define JAZZ_R4030_IRQ_SOURCE   0xE0000200&t;/* Interrupt Source Register */
DECL|macro|JAZZ_R4030_I386_ERROR
mdefine_line|#define JAZZ_R4030_I386_ERROR   0xE0000208&t;/* i386/EISA Bus Error */
multiline_comment|/*&n; * Virtual (E)ISA controller address&n; */
DECL|macro|JAZZ_EISA_IRQ_ACK
mdefine_line|#define JAZZ_EISA_IRQ_ACK&t;0xE0000238&t;/* EISA interrupt acknowledge */
multiline_comment|/*&n; * Access the R4030 DMA and I/O Controller&n; */
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|function|r4030_delay
r_extern
r_inline
r_void
id|r4030_delay
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
)paren
suffix:semicolon
)brace
DECL|function|r4030_read_reg16
r_extern
r_inline
r_int
r_int
id|r4030_read_reg16
c_func
(paren
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|r4030_delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|r4030_read_reg32
r_extern
r_inline
r_int
r_int
id|r4030_read_reg32
c_func
(paren
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|r4030_delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|r4030_write_reg16
r_extern
r_inline
r_void
id|r4030_write_reg16
c_func
(paren
r_int
id|addr
comma
r_int
id|val
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_assign
id|val
suffix:semicolon
id|r4030_delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|r4030_write_reg32
r_extern
r_inline
r_void
id|r4030_write_reg32
c_func
(paren
r_int
id|addr
comma
r_int
id|val
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_assign
id|val
suffix:semicolon
id|r4030_delay
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !LANGUAGE_ASSEMBLY__ */
DECL|macro|JAZZ_FDC_BASE
mdefine_line|#define JAZZ_FDC_BASE&t;0xe0003000
DECL|macro|JAZZ_RTC_BASE
mdefine_line|#define JAZZ_RTC_BASE&t;0xe0004000
DECL|macro|JAZZ_PORT_BASE
mdefine_line|#define JAZZ_PORT_BASE&t;0xe2000000
DECL|macro|JAZZ_EISA_BASE
mdefine_line|#define JAZZ_EISA_BASE&t;0xe3000000
macro_line|#endif /* __ASM_MIPS_JAZZ_H */
eof
