multiline_comment|/* &n; * Q40 master Chip Control &n; * RTC stuff merged for compactnes..&n;*/
macro_line|#ifndef _Q40_MASTER_H
DECL|macro|_Q40_MASTER_H
mdefine_line|#define _Q40_MASTER_H
macro_line|#include &lt;asm/raw_io.h&gt;
DECL|macro|q40_master_addr
mdefine_line|#define q40_master_addr 0xff000000
DECL|macro|q40_rtc_addr
mdefine_line|#define q40_rtc_addr    0xff021ffc
DECL|macro|IIRQ_REG
mdefine_line|#define IIRQ_REG            0x0       /* internal IRQ reg */
DECL|macro|EIRQ_REG
mdefine_line|#define EIRQ_REG            0x4       /* external ... */
DECL|macro|KEYCODE_REG
mdefine_line|#define KEYCODE_REG         0x1c      /* value of received scancode  */
DECL|macro|DISPLAY_CONTROL_REG
mdefine_line|#define DISPLAY_CONTROL_REG 0x18
DECL|macro|FRAME_CLEAR_REG
mdefine_line|#define FRAME_CLEAR_REG     0x24
DECL|macro|LED_REG
mdefine_line|#define LED_REG             0x30
DECL|macro|Q40_LED_ON
mdefine_line|#define Q40_LED_ON()        master_outb(1,LED_REG)
DECL|macro|Q40_LED_OFF
mdefine_line|#define Q40_LED_OFF()       master_outb(0,LED_REG)
DECL|macro|INTERRUPT_REG
mdefine_line|#define INTERRUPT_REG       IIRQ_REG  /* &quot;native&quot; ints */
DECL|macro|KEY_IRQ_ENABLE_REG
mdefine_line|#define KEY_IRQ_ENABLE_REG  0x08      /**/
DECL|macro|KEYBOARD_UNLOCK_REG
mdefine_line|#define KEYBOARD_UNLOCK_REG 0x20      /* clear kb int */
DECL|macro|SAMPLE_ENABLE_REG
mdefine_line|#define SAMPLE_ENABLE_REG   0x14      /* generate SAMPLE ints */
DECL|macro|SAMPLE_RATE_REG
mdefine_line|#define SAMPLE_RATE_REG     0x2c
DECL|macro|SAMPLE_CLEAR_REG
mdefine_line|#define SAMPLE_CLEAR_REG    0x28
DECL|macro|SAMPLE_LOW
mdefine_line|#define SAMPLE_LOW          0x00
DECL|macro|SAMPLE_HIGH
mdefine_line|#define SAMPLE_HIGH         0x01
DECL|macro|FRAME_RATE_REG
mdefine_line|#define FRAME_RATE_REG       0x38      /* generate FRAME ints at 200 HZ rate */
macro_line|#if 0
mdefine_line|#define SER_ENABLE_REG      0x0c      /* allow serial ints to be generated */
macro_line|#endif
DECL|macro|EXT_ENABLE_REG
mdefine_line|#define EXT_ENABLE_REG      0x10      /* ... rest of the ISA ints ... */
DECL|macro|master_inb
mdefine_line|#define master_inb(_reg_)      in_8((unsigned char *)q40_master_addr+_reg_)
DECL|macro|master_outb
mdefine_line|#define master_outb(_b_,_reg_)  out_8((unsigned char *)q40_master_addr+_reg_,_b_)
multiline_comment|/* define some Q40 specific ints */
macro_line|#include &quot;q40ints.h&quot;
multiline_comment|/* RTC defines */
DECL|macro|Q40_RTC_BASE
mdefine_line|#define Q40_RTC_BASE (q40_rtc_addr)
DECL|macro|RTC_YEAR
mdefine_line|#define RTC_YEAR        (*(unsigned char *)(Q40_RTC_BASE+0))
DECL|macro|RTC_MNTH
mdefine_line|#define RTC_MNTH        (*(unsigned char *)(Q40_RTC_BASE-4))
DECL|macro|RTC_DATE
mdefine_line|#define RTC_DATE        (*(unsigned char *)(Q40_RTC_BASE-8))
DECL|macro|RTC_DOW
mdefine_line|#define RTC_DOW         (*(unsigned char *)(Q40_RTC_BASE-12))
DECL|macro|RTC_HOUR
mdefine_line|#define RTC_HOUR        (*(unsigned char *)(Q40_RTC_BASE-16))
DECL|macro|RTC_MINS
mdefine_line|#define RTC_MINS        (*(unsigned char *)(Q40_RTC_BASE-20))
DECL|macro|RTC_SECS
mdefine_line|#define RTC_SECS        (*(unsigned char *)(Q40_RTC_BASE-24))
DECL|macro|RTC_CTRL
mdefine_line|#define RTC_CTRL        (*(unsigned char *)(Q40_RTC_BASE-28))
multiline_comment|/* some control bits */
DECL|macro|RTC_READ
mdefine_line|#define RTC_READ   64  /* prepare for reading */
DECL|macro|RTC_WRITE
mdefine_line|#define RTC_WRITE  128
multiline_comment|/* misc defs */
DECL|macro|DAC_LEFT
mdefine_line|#define DAC_LEFT  ((unsigned char *)0xff008000)
DECL|macro|DAC_RIGHT
mdefine_line|#define DAC_RIGHT ((unsigned char *)0xff008004)
macro_line|#endif /* _Q40_MASTER_H */
eof
