macro_line|#ifndef _LINUX_VFC_I2C_H_
DECL|macro|_LINUX_VFC_I2C_H_
mdefine_line|#define _LINUX_VFC_I2C_H_
multiline_comment|/* control bits */
DECL|macro|PIN
mdefine_line|#define PIN  (0x80000000)
DECL|macro|ESO
mdefine_line|#define ESO  (0x40000000)
DECL|macro|ES1
mdefine_line|#define ES1  (0x20000000)
DECL|macro|ES2
mdefine_line|#define ES2  (0x10000000)
DECL|macro|ENI
mdefine_line|#define ENI  (0x08000000)
DECL|macro|STA
mdefine_line|#define STA  (0x04000000)
DECL|macro|STO
mdefine_line|#define STO  (0x02000000)
DECL|macro|ACK
mdefine_line|#define ACK  (0x01000000)
multiline_comment|/* status bits */
DECL|macro|STS
mdefine_line|#define STS  (0x20000000)
DECL|macro|BER
mdefine_line|#define BER  (0x10000000)
DECL|macro|LRB
mdefine_line|#define LRB  (0x08000000)
DECL|macro|AAS
mdefine_line|#define AAS  (0x04000000)
DECL|macro|LAB
mdefine_line|#define LAB  (0x02000000)
DECL|macro|BB
mdefine_line|#define BB   (0x01000000)
DECL|macro|SEND_I2C_START
mdefine_line|#define SEND_I2C_START (PIN | ESO | STA)
DECL|macro|SEND_I2C_STOP
mdefine_line|#define SEND_I2C_STOP (PIN | ESO | STO)
DECL|macro|CLEAR_I2C_BUS
mdefine_line|#define CLEAR_I2C_BUS (PIN | ESO | ACK)
DECL|macro|NEGATIVE_ACK
mdefine_line|#define NEGATIVE_ACK ((ESO) &amp; ~ACK)
DECL|macro|SELECT
mdefine_line|#define SELECT(a) (a)
DECL|macro|S0
mdefine_line|#define S0 (PIN | ESO | ES1)
DECL|macro|S0_OWN
mdefine_line|#define S0_OWN (PIN)
DECL|macro|S2
mdefine_line|#define S2 (PIN | ES1)
DECL|macro|S3
mdefine_line|#define S3 (PIN | ES2)
DECL|macro|ENABLE_SERIAL
mdefine_line|#define ENABLE_SERIAL (PIN | ESO)
DECL|macro|DISABLE_SERIAL
mdefine_line|#define DISABLE_SERIAL (PIN)
DECL|macro|RESET
mdefine_line|#define RESET (PIN)
DECL|macro|XMIT_LAST_BYTE
mdefine_line|#define XMIT_LAST_BYTE (1)
DECL|macro|VFC_I2C_ACK_CHECK
mdefine_line|#define VFC_I2C_ACK_CHECK (1)
DECL|macro|VFC_I2C_NO_ACK_CHECK
mdefine_line|#define VFC_I2C_NO_ACK_CHECK (0)
macro_line|#endif /* _LINUX_VFC_I2C_H_ */
eof
