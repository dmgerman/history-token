macro_line|#ifndef I2C_PCA9564_H
DECL|macro|I2C_PCA9564_H
mdefine_line|#define I2C_PCA9564_H 1
DECL|macro|I2C_PCA_STA
mdefine_line|#define I2C_PCA_STA&t;&t;0x00 /* STATUS  Read Only  */
DECL|macro|I2C_PCA_TO
mdefine_line|#define I2C_PCA_TO&t;&t;0x00 /* TIMEOUT Write Only */
DECL|macro|I2C_PCA_DAT
mdefine_line|#define I2C_PCA_DAT&t;&t;0x01 /* DATA    Read/Write */
DECL|macro|I2C_PCA_ADR
mdefine_line|#define I2C_PCA_ADR&t;&t;0x02 /* OWN ADR Read/Write */
DECL|macro|I2C_PCA_CON
mdefine_line|#define I2C_PCA_CON&t;&t;0x03 /* CONTROL Read/Write */
DECL|macro|I2C_PCA_CON_AA
mdefine_line|#define I2C_PCA_CON_AA&t;&t;0x80 /* Assert Acknowledge */
DECL|macro|I2C_PCA_CON_ENSIO
mdefine_line|#define I2C_PCA_CON_ENSIO&t;0x40 /* Enable */
DECL|macro|I2C_PCA_CON_STA
mdefine_line|#define I2C_PCA_CON_STA&t;&t;0x20 /* Start */
DECL|macro|I2C_PCA_CON_STO
mdefine_line|#define I2C_PCA_CON_STO&t;&t;0x10 /* Stop */
DECL|macro|I2C_PCA_CON_SI
mdefine_line|#define I2C_PCA_CON_SI&t;&t;0x08 /* Serial Interrupt */
DECL|macro|I2C_PCA_CON_CR
mdefine_line|#define I2C_PCA_CON_CR&t;&t;0x07 /* Clock Rate (MASK) */
DECL|macro|I2C_PCA_CON_330kHz
mdefine_line|#define I2C_PCA_CON_330kHz&t;0x00
DECL|macro|I2C_PCA_CON_288kHz
mdefine_line|#define I2C_PCA_CON_288kHz&t;0x01
DECL|macro|I2C_PCA_CON_217kHz
mdefine_line|#define I2C_PCA_CON_217kHz&t;0x02
DECL|macro|I2C_PCA_CON_146kHz
mdefine_line|#define I2C_PCA_CON_146kHz&t;0x03
DECL|macro|I2C_PCA_CON_88kHz
mdefine_line|#define I2C_PCA_CON_88kHz&t;0x04
DECL|macro|I2C_PCA_CON_59kHz
mdefine_line|#define I2C_PCA_CON_59kHz&t;0x05
DECL|macro|I2C_PCA_CON_44kHz
mdefine_line|#define I2C_PCA_CON_44kHz&t;0x06
DECL|macro|I2C_PCA_CON_36kHz
mdefine_line|#define I2C_PCA_CON_36kHz&t;0x07
macro_line|#endif /* I2C_PCA9564_H */
eof
