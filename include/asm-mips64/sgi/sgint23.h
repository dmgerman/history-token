multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * sgint23.h: Defines for the SGI INT2 and INT3 chipsets.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 98, 1999, 2000  Ralf Baechle&n; * Copyright (C) 1999 Andrew R. Baker (andrewb@uab.edu) - INT2 corrections&n; */
macro_line|#ifndef _ASM_SGI_SGINT23_H
DECL|macro|_ASM_SGI_SGINT23_H
mdefine_line|#define _ASM_SGI_SGINT23_H
multiline_comment|/* These are the virtual IRQ numbers, we divide all IRQ&squot;s into&n; * &squot;spaces&squot;, the &squot;space&squot; determines where and how to enable/disable&n; * that particular IRQ on an SGI machine.  Add new &squot;spaces&squot; as new&n; * IRQ hardware is supported.&n; */
DECL|macro|SGINT_LOCAL0
mdefine_line|#define SGINT_LOCAL0   0   /* INDY has 8 local0 irq levels */
DECL|macro|SGINT_LOCAL1
mdefine_line|#define SGINT_LOCAL1   8   /* INDY has 8 local1 irq levels */
DECL|macro|SGINT_LOCAL2
mdefine_line|#define SGINT_LOCAL2   16  /* INDY has 8 local2 vectored irq levels */
DECL|macro|SGINT_LOCAL3
mdefine_line|#define SGINT_LOCAL3   24  /* INDY has 8 local3 vectored irq levels */
DECL|macro|SGINT_GIO
mdefine_line|#define SGINT_GIO      32  /* INDY has 9 GIO irq levels */
DECL|macro|SGINT_HPCDMA
mdefine_line|#define SGINT_HPCDMA   41  /* INDY has 11 HPCDMA irq _sources_ */
DECL|macro|SGINT_END
mdefine_line|#define SGINT_END      52  /* End of &squot;spaces&squot; */
multiline_comment|/*&n; * Individual interrupt definitions for the INDY and Indigo2&n; */
DECL|macro|SGI_WD93_0_IRQ
mdefine_line|#define SGI_WD93_0_IRQ&t;SGINT_LOCAL0 + 1&t;/* 1st onboard WD93 */
DECL|macro|SGI_WD93_1_IRQ
mdefine_line|#define SGI_WD93_1_IRQ&t;SGINT_LOCAL0 + 2&t;/* 2nd onboard WD93 */
DECL|macro|SGI_ENET_IRQ
mdefine_line|#define SGI_ENET_IRQ&t;SGINT_LOCAL0 + 3&t;/* onboard ethernet */
DECL|macro|SGI_PANEL_IRQ
mdefine_line|#define SGI_PANEL_IRQ&t;SGINT_LOCAL1 + 1&t;/* front panel */
DECL|macro|SGI_EISA_IRQ
mdefine_line|#define SGI_EISA_IRQ&t;SGINT_LOCAL2 + 3&t;/* EISA interrupts */
DECL|macro|SGI_KEYBOARD_IRQ
mdefine_line|#define SGI_KEYBOARD_IRQ&t;SGINT_LOCAL2 + 4&t;/* keyboard */
DECL|macro|SGI_SERIAL_IRQ
mdefine_line|#define SGI_SERIAL_IRQ&t;SGINT_LOCAL2 + 5&t;/* onboard serial */
multiline_comment|/* INT2 occupies HPC PBUS slot 4, INT3 uses slot 6. */
DECL|macro|SGI_INT2_BASE
mdefine_line|#define SGI_INT2_BASE 0x1fbd9000 /* physical */
DECL|macro|SGI_INT3_BASE
mdefine_line|#define SGI_INT3_BASE 0x1fbd9880 /* physical */
DECL|struct|sgi_ioc_ints
r_struct
id|sgi_ioc_ints
(brace
macro_line|#ifdef __MIPSEB__
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|istat0
r_volatile
r_int
r_char
id|istat0
suffix:semicolon
multiline_comment|/* Interrupt status zero */
macro_line|#else
r_volatile
r_int
r_char
id|istat0
suffix:semicolon
multiline_comment|/* Interrupt status zero */
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|ISTAT0_FFULL
mdefine_line|#define ISTAT0_FFULL           0x01
DECL|macro|ISTAT0_SCSI0
mdefine_line|#define ISTAT0_SCSI0           0x02
DECL|macro|ISTAT0_SCSI1
mdefine_line|#define ISTAT0_SCSI1           0x04
DECL|macro|ISTAT0_ENET
mdefine_line|#define ISTAT0_ENET            0x08
DECL|macro|ISTAT0_GFXDMA
mdefine_line|#define ISTAT0_GFXDMA          0x10
DECL|macro|ISTAT0_LPR
mdefine_line|#define ISTAT0_LPR             0x20
DECL|macro|ISTAT0_HPC2
mdefine_line|#define ISTAT0_HPC2            0x40
DECL|macro|ISTAT0_LIO2
mdefine_line|#define ISTAT0_LIO2            0x80
macro_line|#ifdef __MIPSEB__
DECL|member|_unused1
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|imask0
r_volatile
r_int
r_char
id|imask0
suffix:semicolon
multiline_comment|/* Interrupt mask zero */
DECL|member|_unused2
r_int
r_char
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|istat1
r_volatile
r_int
r_char
id|istat1
suffix:semicolon
multiline_comment|/* Interrupt status one */
macro_line|#else
DECL|member|imask0
r_volatile
r_int
r_char
id|imask0
suffix:semicolon
multiline_comment|/* Interrupt mask zero */
DECL|member|_unused1
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|istat1
r_volatile
r_int
r_char
id|istat1
suffix:semicolon
multiline_comment|/* Interrupt status one */
DECL|member|_unused2
r_int
r_char
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|ISTAT1_ISDNI
mdefine_line|#define ISTAT1_ISDNI           0x01
DECL|macro|ISTAT1_PWR
mdefine_line|#define ISTAT1_PWR             0x02
DECL|macro|ISTAT1_ISDNH
mdefine_line|#define ISTAT1_ISDNH           0x04
DECL|macro|ISTAT1_LIO3
mdefine_line|#define ISTAT1_LIO3            0x08
DECL|macro|ISTAT1_HPC3
mdefine_line|#define ISTAT1_HPC3            0x10
DECL|macro|ISTAT1_AFAIL
mdefine_line|#define ISTAT1_AFAIL           0x20
DECL|macro|ISTAT1_VIDEO
mdefine_line|#define ISTAT1_VIDEO           0x40
DECL|macro|ISTAT1_GIO2
mdefine_line|#define ISTAT1_GIO2            0x80
macro_line|#ifdef __MIPSEB__
DECL|member|_unused3
r_int
r_char
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|imask1
r_volatile
r_int
r_char
id|imask1
suffix:semicolon
multiline_comment|/* Interrupt mask one */
DECL|member|_unused4
r_int
r_char
id|_unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|vmeistat
r_volatile
r_int
r_char
id|vmeistat
suffix:semicolon
multiline_comment|/* VME interrupt status */
DECL|member|_unused5
r_int
r_char
id|_unused5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmeimask0
r_volatile
r_int
r_char
id|cmeimask0
suffix:semicolon
multiline_comment|/* VME interrupt mask zero */
DECL|member|_unused6
r_int
r_char
id|_unused6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmeimask1
r_volatile
r_int
r_char
id|cmeimask1
suffix:semicolon
multiline_comment|/* VME interrupt mask one */
DECL|member|_unused7
r_int
r_char
id|_unused7
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmepol
r_volatile
r_int
r_char
id|cmepol
suffix:semicolon
multiline_comment|/* VME polarity */
macro_line|#else
DECL|member|imask1
r_volatile
r_int
r_char
id|imask1
suffix:semicolon
multiline_comment|/* Interrupt mask one */
DECL|member|_unused3
r_int
r_char
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|vmeistat
r_volatile
r_int
r_char
id|vmeistat
suffix:semicolon
multiline_comment|/* VME interrupt status */
DECL|member|_unused4
r_int
r_char
id|_unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmeimask0
r_volatile
r_int
r_char
id|cmeimask0
suffix:semicolon
multiline_comment|/* VME interrupt mask zero */
DECL|member|_unused5
r_int
r_char
id|_unused5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmeimask1
r_volatile
r_int
r_char
id|cmeimask1
suffix:semicolon
multiline_comment|/* VME interrupt mask one */
DECL|member|_unused6
r_int
r_char
id|_unused6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cmepol
r_volatile
r_int
r_char
id|cmepol
suffix:semicolon
multiline_comment|/* VME polarity */
DECL|member|_unused7
r_int
r_char
id|_unused7
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|sgi_ioc_timers
r_struct
id|sgi_ioc_timers
(brace
macro_line|#ifdef __MIPSEB__
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcnt0
r_volatile
r_int
r_char
id|tcnt0
suffix:semicolon
multiline_comment|/* counter 0 */
DECL|member|_unused1
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcnt1
r_volatile
r_int
r_char
id|tcnt1
suffix:semicolon
multiline_comment|/* counter 1 */
DECL|member|_unused2
r_int
r_char
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcnt2
r_volatile
r_int
r_char
id|tcnt2
suffix:semicolon
multiline_comment|/* counter 2 */
DECL|member|_unused3
r_int
r_char
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tcword
r_volatile
r_int
r_char
id|tcword
suffix:semicolon
multiline_comment|/* control word */
macro_line|#else
r_volatile
r_int
r_char
id|tcnt0
suffix:semicolon
multiline_comment|/* counter 0 */
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
r_volatile
r_int
r_char
id|tcnt1
suffix:semicolon
multiline_comment|/* counter 1 */
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
r_volatile
r_int
r_char
id|tcnt2
suffix:semicolon
multiline_comment|/* counter 2 */
r_int
r_char
id|_unused2
(braket
l_int|3
)braket
suffix:semicolon
r_volatile
r_int
r_char
id|tcword
suffix:semicolon
multiline_comment|/* control word */
r_int
r_char
id|_unused3
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Timer control word bits. */
DECL|macro|SGINT_TCWORD_BCD
mdefine_line|#define SGINT_TCWORD_BCD    0x01 /* Use BCD mode for counters */
DECL|macro|SGINT_TCWORD_MMASK
mdefine_line|#define SGINT_TCWORD_MMASK  0x0e /* Mode bitmask. */
DECL|macro|SGINT_TCWORD_MITC
mdefine_line|#define SGINT_TCWORD_MITC   0x00 /* IRQ on terminal count (doesn&squot;t work) */
DECL|macro|SGINT_TCWORD_MOS
mdefine_line|#define SGINT_TCWORD_MOS    0x02 /* One-shot IRQ mode. */
DECL|macro|SGINT_TCWORD_MRGEN
mdefine_line|#define SGINT_TCWORD_MRGEN  0x04 /* Normal rate generation */
DECL|macro|SGINT_TCWORD_MSWGEN
mdefine_line|#define SGINT_TCWORD_MSWGEN 0x06 /* Square wave generator mode */
DECL|macro|SGINT_TCWORD_MSWST
mdefine_line|#define SGINT_TCWORD_MSWST  0x08 /* Software strobe */
DECL|macro|SGINT_TCWORD_MHWST
mdefine_line|#define SGINT_TCWORD_MHWST  0x0a /* Hardware strobe */
DECL|macro|SGINT_TCWORD_CMASK
mdefine_line|#define SGINT_TCWORD_CMASK  0x30 /* Command mask */
DECL|macro|SGINT_TCWORD_CLAT
mdefine_line|#define SGINT_TCWORD_CLAT   0x00 /* Latch command */
DECL|macro|SGINT_TCWORD_CLSB
mdefine_line|#define SGINT_TCWORD_CLSB   0x10 /* LSB read/write */
DECL|macro|SGINT_TCWORD_CMSB
mdefine_line|#define SGINT_TCWORD_CMSB   0x20 /* MSB read/write */
DECL|macro|SGINT_TCWORD_CALL
mdefine_line|#define SGINT_TCWORD_CALL   0x30 /* Full counter read/write */
DECL|macro|SGINT_TCWORD_CNT0
mdefine_line|#define SGINT_TCWORD_CNT0   0x00 /* Select counter zero */
DECL|macro|SGINT_TCWORD_CNT1
mdefine_line|#define SGINT_TCWORD_CNT1   0x40 /* Select counter one */
DECL|macro|SGINT_TCWORD_CNT2
mdefine_line|#define SGINT_TCWORD_CNT2   0x80 /* Select counter two */
DECL|macro|SGINT_TCWORD_CRBCK
mdefine_line|#define SGINT_TCWORD_CRBCK  0xc0 /* Readback command */
DECL|macro|SGINT_TCSAMP_COUNTER
mdefine_line|#define SGINT_TCSAMP_COUNTER  10255
multiline_comment|/* FIXME: What does this really look like?  It was written to have&n; * 17 registers, but there are only 16 in my Indigo2.&n; * I guessed at which one to remove...  &t;- andrewb&n; */
DECL|struct|sgi_int2_regs
r_struct
id|sgi_int2_regs
(brace
DECL|member|ints
r_struct
id|sgi_ioc_ints
id|ints
suffix:semicolon
DECL|member|ledbits
r_volatile
id|u32
id|ledbits
suffix:semicolon
multiline_comment|/* LED control bits */
DECL|macro|INT2_LED_TXCLK
mdefine_line|#define INT2_LED_TXCLK         0x01       /* GPI to TXCLK enable */
DECL|macro|INT2_LED_SERSLCT0
mdefine_line|#define INT2_LED_SERSLCT0      0x02       /* serial port0: 0=apple 1=pc */
DECL|macro|INT2_LED_SERSLCT1
mdefine_line|#define INT2_LED_SERSLCT1      0x04       /* serial port1: 0=apple 1=pc */
DECL|macro|INT2_LED_CHEAPER
mdefine_line|#define INT2_LED_CHEAPER       0x08       /* 0=cheapernet 1=ethernet */
DECL|macro|INT2_LED_POWEROFF
mdefine_line|#define INT2_LED_POWEROFF      0x10       /* Power-off request, active high */
macro_line|#ifdef __MIPSEB__
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tclear
r_volatile
r_int
r_char
id|tclear
suffix:semicolon
multiline_comment|/* Timer clear strobe address */
macro_line|#else
DECL|member|tclear
r_volatile
r_int
r_char
id|tclear
suffix:semicolon
multiline_comment|/* Timer clear strobe address */
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|INT2_TCLEAR_T0CLR
mdefine_line|#define INT2_TCLEAR_T0CLR      0x1        /* Clear timer0 IRQ */
DECL|macro|INT2_TCLEAR_T1CLR
mdefine_line|#define INT2_TCLEAR_T1CLR      0x2        /* Clear timer1 IRQ */
multiline_comment|/* I am guessing there are only two unused registers here &n; * but I could be wrong...&t;&t;&t;- andrewb&n; */
multiline_comment|/*&t;u32 _unused[3]; */
DECL|member|_unused
id|u32
id|_unused
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|timers
r_struct
id|sgi_ioc_timers
id|timers
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sgi_int3_regs
r_struct
id|sgi_int3_regs
(brace
DECL|member|ints
r_struct
id|sgi_ioc_ints
id|ints
suffix:semicolon
macro_line|#ifdef __MIPSEB__
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tclear
r_volatile
r_int
r_char
id|tclear
suffix:semicolon
multiline_comment|/* Timer clear strobe address */
macro_line|#else
DECL|member|tclear
r_volatile
r_int
r_char
id|tclear
suffix:semicolon
multiline_comment|/* Timer clear strobe address */
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
DECL|member|estatus
r_volatile
id|u32
id|estatus
suffix:semicolon
multiline_comment|/* Error status reg */
DECL|member|_unused1
id|u32
id|_unused1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|timers
r_struct
id|sgi_ioc_timers
id|timers
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sgi_int2_regs
op_star
id|sgi_i2regs
suffix:semicolon
r_extern
r_struct
id|sgi_int3_regs
op_star
id|sgi_i3regs
suffix:semicolon
r_extern
r_struct
id|sgi_ioc_ints
op_star
id|ioc_icontrol
suffix:semicolon
r_extern
r_struct
id|sgi_ioc_timers
op_star
id|ioc_timers
suffix:semicolon
r_extern
r_volatile
r_int
r_char
op_star
id|ioc_tclear
suffix:semicolon
r_extern
r_void
id|indy_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SGI_SGINT23_H */
eof
