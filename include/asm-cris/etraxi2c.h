multiline_comment|/* $Id: etraxi2c.h,v 1.1 2001/01/18 15:49:57 bjornw Exp $ */
macro_line|#ifndef _LINUX_ETRAXI2C_H
DECL|macro|_LINUX_ETRAXI2C_H
mdefine_line|#define _LINUX_ETRAXI2C_H
multiline_comment|/* etraxi2c _IOC_TYPE, bits 8 to 15 in ioctl cmd */
DECL|macro|ETRAXI2C_IOCTYPE
mdefine_line|#define ETRAXI2C_IOCTYPE 44
multiline_comment|/* supported ioctl _IOC_NR&squot;s */
multiline_comment|/* in write operations, the argument contains both i2c&n; * slave, register and value.&n; */
DECL|macro|I2C_WRITEARG
mdefine_line|#define I2C_WRITEARG(slave, reg, value) (((slave) &lt;&lt; 16) | ((reg) &lt;&lt; 8) | (value))
DECL|macro|I2C_READARG
mdefine_line|#define I2C_READARG(slave, reg) (((slave) &lt;&lt; 16) | ((reg) &lt;&lt; 8))
DECL|macro|I2C_ARGSLAVE
mdefine_line|#define I2C_ARGSLAVE(arg) ((arg) &gt;&gt; 16)
DECL|macro|I2C_ARGREG
mdefine_line|#define I2C_ARGREG(arg) (((arg) &gt;&gt; 8) &amp; 0xff)
DECL|macro|I2C_ARGVALUE
mdefine_line|#define I2C_ARGVALUE(arg) ((arg) &amp; 0xff)
DECL|macro|I2C_WRITEREG
mdefine_line|#define I2C_WRITEREG 0x1   /* write to an i2c register */
DECL|macro|I2C_READREG
mdefine_line|#define I2C_READREG  0x2   /* read from an i2c register */
multiline_comment|/*&n;EXAMPLE usage:&n;&n;    i2c_arg = I2C_WRITEARG(STA013_WRITE_ADDR, reg, val);&n;    ioctl(fd, _IO(ETRAXI2C_IOCTYPE, I2C_WRITEREG), i2c_arg);&n;&n;    i2c_arg = I2C_READARG(STA013_READ_ADDR, reg);&n;    val = ioctl(fd, _IO(ETRAXI2C_IOCTYPE, I2C_READREG), i2c_arg);&n;&n;*/
macro_line|#endif
eof
