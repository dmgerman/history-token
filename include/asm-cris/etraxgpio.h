macro_line|#ifndef _ASM_ETRAXGPIO_H
DECL|macro|_ASM_ETRAXGPIO_H
mdefine_line|#define _ASM_ETRAXGPIO_H
multiline_comment|/* etraxgpio _IOC_TYPE, bits 8 to 15 in ioctl cmd */
DECL|macro|ETRAXGPIO_IOCTYPE
mdefine_line|#define ETRAXGPIO_IOCTYPE 43
multiline_comment|/* supported ioctl _IOC_NR&squot;s */
DECL|macro|IO_READBITS
mdefine_line|#define IO_READBITS  0x1  /* read and return current port bits */
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
mdefine_line|#define IO_READDIR    0x8  /* Read direction 0=input 1=output */
DECL|macro|IO_SETINPUT
mdefine_line|#define IO_SETINPUT   0x9  /* Set direction 0=unchanged 1=input, &n;                              returns current dir */
DECL|macro|IO_SETOUTPUT
mdefine_line|#define IO_SETOUTPUT  0xA  /* Set direction 0=unchanged 1=output,&n;                              returns current dir */
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
macro_line|#endif
eof
