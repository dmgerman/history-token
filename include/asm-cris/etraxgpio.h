multiline_comment|/* $Id: etraxgpio.h,v 1.8 2002/06/17 15:53:07 johana Exp $ */
multiline_comment|/*&n; * The following devices are accessable using this driver using&n; * GPIO_MAJOR (120) and a couple of minor numbers:&n; * For ETRAX 100LX (ARCH_V10):&n; * /dev/gpioa  minor 0, 8 bit GPIO, each bit can change direction&n; * /dev/gpiob  minor 1, 8 bit GPIO, each bit can change direction&n; * /dev/leds   minor 2, Access to leds depending on kernelconfig&n; * /dev/gpiog  minor 3&n;         g0dir, g8_15dir, g16_23dir, g24 dir configurable in R_GEN_CONFIG&n;         g1-g7 and g25-g31 is both input and outputs but on different pins&n;         Also note that some bits change pins depending on what interfaces &n;         are enabled.&n; *&n; *&n; * For ETRAX 200 (ARCH_V32):&n; * /dev/gpioa  minor 0,  8 bit GPIO, each bit can change direction&n; * /dev/gpiob  minor 1, 18 bit GPIO, each bit can change direction&n; * /dev/gpioc  minor 2, 18 bit GPIO, each bit can change direction&n; * /dev/gpiod  minor 3, 18 bit GPIO, each bit can change direction&n; * /dev/gpioe  minor 4, 18 bit GPIO, each bit can change direction&n; * /dev/leds   minor 5, Access to leds depending on kernelconfig&n; *&n; */
macro_line|#ifndef _ASM_ETRAXGPIO_H
DECL|macro|_ASM_ETRAXGPIO_H
mdefine_line|#define _ASM_ETRAXGPIO_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* etraxgpio _IOC_TYPE, bits 8 to 15 in ioctl cmd */
macro_line|#ifdef CONFIG_ETRAX_ARCH_V10
DECL|macro|ETRAXGPIO_IOCTYPE
mdefine_line|#define ETRAXGPIO_IOCTYPE 43
DECL|macro|GPIO_MINOR_A
mdefine_line|#define GPIO_MINOR_A 0
DECL|macro|GPIO_MINOR_B
mdefine_line|#define GPIO_MINOR_B 1
DECL|macro|GPIO_MINOR_LEDS
mdefine_line|#define GPIO_MINOR_LEDS 2
DECL|macro|GPIO_MINOR_G
mdefine_line|#define GPIO_MINOR_G 3
DECL|macro|GPIO_MINOR_LAST
mdefine_line|#define GPIO_MINOR_LAST 3
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_ARCH_V32
DECL|macro|ETRAXGPIO_IOCTYPE
mdefine_line|#define ETRAXGPIO_IOCTYPE 43
DECL|macro|GPIO_MINOR_A
mdefine_line|#define GPIO_MINOR_A 0
DECL|macro|GPIO_MINOR_B
mdefine_line|#define GPIO_MINOR_B 1
DECL|macro|GPIO_MINOR_C
mdefine_line|#define GPIO_MINOR_C 2
DECL|macro|GPIO_MINOR_D
mdefine_line|#define GPIO_MINOR_D 3
DECL|macro|GPIO_MINOR_E
mdefine_line|#define GPIO_MINOR_E 4
DECL|macro|GPIO_MINOR_LEDS
mdefine_line|#define GPIO_MINOR_LEDS 5
DECL|macro|GPIO_MINOR_LAST
mdefine_line|#define GPIO_MINOR_LAST 5
macro_line|#endif
multiline_comment|/* supported ioctl _IOC_NR&squot;s */
DECL|macro|IO_READBITS
mdefine_line|#define IO_READBITS  0x1  /* read and return current port bits (obsolete) */
DECL|macro|IO_SETBITS
mdefine_line|#define IO_SETBITS   0x2  /* set the bits marked by 1 in the argument */
DECL|macro|IO_CLRBITS
mdefine_line|#define IO_CLRBITS   0x3  /* clear the bits marked by 1 in the argument */
multiline_comment|/* the alarm is waited for by select() */
DECL|macro|IO_HIGHALARM
mdefine_line|#define IO_HIGHALARM 0x4  /* set alarm on high for bits marked by 1 */
DECL|macro|IO_LOWALARM
mdefine_line|#define IO_LOWALARM  0x5  /* set alarm on low for bits marked by 1 */
DECL|macro|IO_CLRALARM
mdefine_line|#define IO_CLRALARM  0x6  /* clear alarm for bits marked by 1 */
multiline_comment|/* LED ioctl */
DECL|macro|IO_LEDACTIVE_SET
mdefine_line|#define IO_LEDACTIVE_SET 0x7 /* set active led&n;                              * 0=off, 1=green, 2=red, 3=yellow */
multiline_comment|/* GPIO direction ioctl&squot;s */
DECL|macro|IO_READDIR
mdefine_line|#define IO_READDIR    0x8  /* Read direction 0=input 1=output  (obsolete) */
DECL|macro|IO_SETINPUT
mdefine_line|#define IO_SETINPUT   0x9  /* Set direction for bits set, 0=unchanged 1=input, &n;                              returns mask with current inputs (obsolete) */
DECL|macro|IO_SETOUTPUT
mdefine_line|#define IO_SETOUTPUT  0xA  /* Set direction for bits set, 0=unchanged 1=output,&n;                              returns mask with current outputs (obsolete)*/
multiline_comment|/* LED ioctl extended */
DECL|macro|IO_LED_SETBIT
mdefine_line|#define IO_LED_SETBIT 0xB
DECL|macro|IO_LED_CLRBIT
mdefine_line|#define IO_LED_CLRBIT 0xC
multiline_comment|/* SHUTDOWN ioctl */
DECL|macro|IO_SHUTDOWN
mdefine_line|#define IO_SHUTDOWN   0xD
DECL|macro|IO_GET_PWR_BT
mdefine_line|#define IO_GET_PWR_BT 0xE
multiline_comment|/* Bit toggling in driver settings */
multiline_comment|/* bit set in low byte0 is CLK mask (0x00FF), &n;   bit set in byte1 is DATA mask    (0xFF00) &n;   msb, data_mask[7:0] , clk_mask[7:0]&n; */
DECL|macro|IO_CFG_WRITE_MODE
mdefine_line|#define IO_CFG_WRITE_MODE 0xF 
DECL|macro|IO_CFG_WRITE_MODE_VALUE
mdefine_line|#define IO_CFG_WRITE_MODE_VALUE(msb, data_mask, clk_mask) &bslash;&n;  ( (((msb)&amp;1) &lt;&lt; 16) | (((data_mask) &amp;0xFF) &lt;&lt; 8) | ((clk_mask) &amp; 0xFF) )
multiline_comment|/* The following 4 ioctl&squot;s take a pointer as argument and handles&n; * 32 bit ports (port G) properly.&n; * These replaces IO_READBITS,IO_SETINPUT AND IO_SETOUTPUT&n; */
DECL|macro|IO_READ_INBITS
mdefine_line|#define IO_READ_INBITS   0x10 /* *arg is result of reading the input pins */
DECL|macro|IO_READ_OUTBITS
mdefine_line|#define IO_READ_OUTBITS  0x11 /* *arg is result of reading the output shadow */
DECL|macro|IO_SETGET_INPUT
mdefine_line|#define IO_SETGET_INPUT  0x12 /* bits set in *arg is set to input,&n;                               * *arg updated with current input pins.&n;                               */
DECL|macro|IO_SETGET_OUTPUT
mdefine_line|#define IO_SETGET_OUTPUT 0x13 /* bits set in *arg is set to output,&n;                               * *arg updated with current output pins.&n;                               */
macro_line|#endif
eof
