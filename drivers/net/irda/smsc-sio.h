macro_line|#ifndef SMSC_SIO_H
DECL|macro|SMSC_SIO_H
mdefine_line|#define SMSC_SIO_H
multiline_comment|/******************************************&n; Keys. They should work with every SMsC SIO&n; ******************************************/
DECL|macro|SMSCSIO_CFGACCESSKEY
mdefine_line|#define SMSCSIO_CFGACCESSKEY&t;&t;0x55
DECL|macro|SMSCSIO_CFGEXITKEY
mdefine_line|#define SMSCSIO_CFGEXITKEY&t;&t;&t;0xaa
multiline_comment|/*****************************&n; * Generic SIO Flat (!?)     *&n; *****************************/
multiline_comment|/* Register 0x0d */
DECL|macro|SMSCSIOFLAT_DEVICEID_REG
mdefine_line|#define SMSCSIOFLAT_DEVICEID_REG&t;&t;&t;&t;0x0d
multiline_comment|/* Register 0x0c */
DECL|macro|SMSCSIOFLAT_UARTMODE0C_REG
mdefine_line|#define SMSCSIOFLAT_UARTMODE0C_REG&t;&t;&t;&t;0x0c
DECL|macro|SMSCSIOFLAT_UART2MODE_MASK
mdefine_line|#define &t;SMSCSIOFLAT_UART2MODE_MASK&t;&t;&t;0x38
DECL|macro|SMSCSIOFLAT_UART2MODE_VAL_COM
mdefine_line|#define &t;SMSCSIOFLAT_UART2MODE_VAL_COM&t;&t;0x00
DECL|macro|SMSCSIOFLAT_UART2MODE_VAL_IRDA
mdefine_line|#define &t;SMSCSIOFLAT_UART2MODE_VAL_IRDA&t;&t;0x08
DECL|macro|SMSCSIOFLAT_UART2MODE_VAL_ASKIR
mdefine_line|#define &t;SMSCSIOFLAT_UART2MODE_VAL_ASKIR&t;&t;0x10
multiline_comment|/* Register 0x25 */
DECL|macro|SMSCSIOFLAT_UART2BASEADDR_REG
mdefine_line|#define SMSCSIOFLAT_UART2BASEADDR_REG&t;&t;&t;0x25
multiline_comment|/* Register 0x2b */
DECL|macro|SMSCSIOFLAT_FIRBASEADDR_REG
mdefine_line|#define SMSCSIOFLAT_FIRBASEADDR_REG&t;&t;&t;&t;0x2b
multiline_comment|/* Register 0x2c */
DECL|macro|SMSCSIOFLAT_FIRDMASELECT_REG
mdefine_line|#define SMSCSIOFLAT_FIRDMASELECT_REG&t;&t;&t;0x2c
DECL|macro|SMSCSIOFLAT_FIRDMASELECT_MASK
mdefine_line|#define &t;SMSCSIOFLAT_FIRDMASELECT_MASK&t;&t;0x0f
multiline_comment|/* Register 0x28 */
DECL|macro|SMSCSIOFLAT_UARTIRQSELECT_REG
mdefine_line|#define SMSCSIOFLAT_UARTIRQSELECT_REG&t;&t;&t;0x28
DECL|macro|SMSCSIOFLAT_UART2IRQSELECT_MASK
mdefine_line|#define &t;SMSCSIOFLAT_UART2IRQSELECT_MASK&t;&t;0x0f
DECL|macro|SMSCSIOFLAT_UART1IRQSELECT_MASK
mdefine_line|#define &t;SMSCSIOFLAT_UART1IRQSELECT_MASK&t;&t;0xf0
DECL|macro|SMSCSIOFLAT_UARTIRQSELECT_VAL_NONE
mdefine_line|#define &t;SMSCSIOFLAT_UARTIRQSELECT_VAL_NONE&t;0x00
multiline_comment|/*********************&n; * LPC47N227         *&n; *********************/
DECL|macro|LPC47N227_CFGACCESSKEY
mdefine_line|#define LPC47N227_CFGACCESSKEY&t;&t;0x55
DECL|macro|LPC47N227_CFGEXITKEY
mdefine_line|#define LPC47N227_CFGEXITKEY&t;&t;0xaa
multiline_comment|/* Register 0x00 */
DECL|macro|LPC47N227_FDCPOWERVALIDCONF_REG
mdefine_line|#define LPC47N227_FDCPOWERVALIDCONF_REG&t;&t;0x00
DECL|macro|LPC47N227_FDCPOWER_MASK
mdefine_line|#define &t;LPC47N227_FDCPOWER_MASK&t;&t;&t;0x08
DECL|macro|LPC47N227_VALID_MASK
mdefine_line|#define &t;LPC47N227_VALID_MASK&t;&t;&t;&t;0x80
multiline_comment|/* Register 0x02 */
DECL|macro|LPC47N227_UART12POWER_REG
mdefine_line|#define LPC47N227_UART12POWER_REG&t;&t;&t;&t;0x02
DECL|macro|LPC47N227_UART1POWERDOWN_MASK
mdefine_line|#define &t;LPC47N227_UART1POWERDOWN_MASK&t;&t;0x08
DECL|macro|LPC47N227_UART2POWERDOWN_MASK
mdefine_line|#define &t;LPC47N227_UART2POWERDOWN_MASK&t;&t;0x80
multiline_comment|/* Register 0x07 */
DECL|macro|LPC47N227_APMBOOTDRIVE_REG
mdefine_line|#define LPC47N227_APMBOOTDRIVE_REG&t;&t;&t;&t;0x07
DECL|macro|LPC47N227_PARPORT2AUTOPWRDOWN_MASK
mdefine_line|#define &t;LPC47N227_PARPORT2AUTOPWRDOWN_MASK&t;0x10 /* auto power down on if set */
DECL|macro|LPC47N227_UART2AUTOPWRDOWN_MASK
mdefine_line|#define &t;LPC47N227_UART2AUTOPWRDOWN_MASK&t;0x20 /* auto power down on if set */
DECL|macro|LPC47N227_UART1AUTOPWRDOWN_MASK
mdefine_line|#define &t;LPC47N227_UART1AUTOPWRDOWN_MASK&t;0x40 /* auto power down on if set */
multiline_comment|/* Register 0x0c */
DECL|macro|LPC47N227_UARTMODE0C_REG
mdefine_line|#define LPC47N227_UARTMODE0C_REG&t;&t;&t;&t;0x0c
DECL|macro|LPC47N227_UART2MODE_MASK
mdefine_line|#define &t;LPC47N227_UART2MODE_MASK&t;&t;&t;0x38
DECL|macro|LPC47N227_UART2MODE_VAL_COM
mdefine_line|#define &t;LPC47N227_UART2MODE_VAL_COM&t;&t;0x00
DECL|macro|LPC47N227_UART2MODE_VAL_IRDA
mdefine_line|#define &t;LPC47N227_UART2MODE_VAL_IRDA&t;&t;0x08
DECL|macro|LPC47N227_UART2MODE_VAL_ASKIR
mdefine_line|#define &t;LPC47N227_UART2MODE_VAL_ASKIR&t;&t;0x10
multiline_comment|/* Register 0x0d */
DECL|macro|LPC47N227_DEVICEID_REG
mdefine_line|#define LPC47N227_DEVICEID_REG&t;&t;&t;&t;&t;0x0d
DECL|macro|LPC47N227_DEVICEID_DEFVAL
mdefine_line|#define &t;LPC47N227_DEVICEID_DEFVAL&t;&t;&t;0x5a
multiline_comment|/* Register 0x0e */
DECL|macro|LPC47N227_REVISIONID_REG
mdefine_line|#define LPC47N227_REVISIONID_REG&t;&t;&t;&t;0x0e
multiline_comment|/* Register 0x25 */
DECL|macro|LPC47N227_UART2BASEADDR_REG
mdefine_line|#define LPC47N227_UART2BASEADDR_REG&t;&t;&t;0x25
multiline_comment|/* Register 0x28 */
DECL|macro|LPC47N227_UARTIRQSELECT_REG
mdefine_line|#define LPC47N227_UARTIRQSELECT_REG&t;&t;&t;0x28
DECL|macro|LPC47N227_UART2IRQSELECT_MASK
mdefine_line|#define &t;LPC47N227_UART2IRQSELECT_MASK&t;&t;0x0f
DECL|macro|LPC47N227_UART1IRQSELECT_MASK
mdefine_line|#define &t;LPC47N227_UART1IRQSELECT_MASK&t;&t;0xf0
DECL|macro|LPC47N227_UARTIRQSELECT_VAL_NONE
mdefine_line|#define &t;LPC47N227_UARTIRQSELECT_VAL_NONE&t;0x00
multiline_comment|/* Register 0x2b */
DECL|macro|LPC47N227_FIRBASEADDR_REG
mdefine_line|#define LPC47N227_FIRBASEADDR_REG&t;&t;&t;&t;0x2b
multiline_comment|/* Register 0x2c */
DECL|macro|LPC47N227_FIRDMASELECT_REG
mdefine_line|#define LPC47N227_FIRDMASELECT_REG&t;&t;&t;&t;0x2c
DECL|macro|LPC47N227_FIRDMASELECT_MASK
mdefine_line|#define &t;LPC47N227_FIRDMASELECT_MASK&t;&t;0x0f
DECL|macro|LPC47N227_FIRDMASELECT_VAL_DMA1
mdefine_line|#define &t;LPC47N227_FIRDMASELECT_VAL_DMA1&t;0x01 /* 47n227 has three dma channels */
DECL|macro|LPC47N227_FIRDMASELECT_VAL_DMA2
mdefine_line|#define &t;LPC47N227_FIRDMASELECT_VAL_DMA2&t;0x02
DECL|macro|LPC47N227_FIRDMASELECT_VAL_DMA3
mdefine_line|#define &t;LPC47N227_FIRDMASELECT_VAL_DMA3&t;0x03
DECL|macro|LPC47N227_FIRDMASELECT_VAL_NONE
mdefine_line|#define &t;LPC47N227_FIRDMASELECT_VAL_NONE&t;0x0f
macro_line|#endif
eof
