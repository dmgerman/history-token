multiline_comment|/* Random defines and structures for the HP Lance driver.&n; * Copyright (C) 05/1998 Peter Maydell &lt;pmaydell@chiark.greenend.org.uk&gt;&n; * Based on the Sun Lance driver and the NetBSD HP Lance driver&n; */
multiline_comment|/* Registers */
DECL|macro|HPLANCE_ID
mdefine_line|#define HPLANCE_ID&t;&t;0x01&t;&t;/* DIO register: ID byte */
DECL|macro|HPLANCE_STATUS
mdefine_line|#define HPLANCE_STATUS&t;&t;0x03&t;&t;/* DIO register: interrupt enable/status */
multiline_comment|/* Control and status bits for the status register */
DECL|macro|LE_IE
mdefine_line|#define LE_IE 0x80                                /* interrupt enable */
DECL|macro|LE_IR
mdefine_line|#define LE_IR 0x40                                /* interrupt requested */
DECL|macro|LE_LOCK
mdefine_line|#define LE_LOCK 0x08                              /* lock status register */
DECL|macro|LE_ACK
mdefine_line|#define LE_ACK 0x04                               /* ack of lock */
DECL|macro|LE_JAB
mdefine_line|#define LE_JAB 0x02                               /* loss of tx clock (???) */
multiline_comment|/* We can also extract the IPL from the status register with the standard&n; * DIO_IPL(hplance) macro, or using dio_scodetoipl()&n; */
multiline_comment|/* These are the offsets for the DIO regs (hplance_reg), lance_ioreg,&n; * memory and NVRAM:&n; */
DECL|macro|HPLANCE_IDOFF
mdefine_line|#define HPLANCE_IDOFF 0                           /* board baseaddr */
DECL|macro|HPLANCE_REGOFF
mdefine_line|#define HPLANCE_REGOFF 0x4000                     /* lance registers */
DECL|macro|HPLANCE_MEMOFF
mdefine_line|#define HPLANCE_MEMOFF 0x8000                     /* struct lance_init_block */
DECL|macro|HPLANCE_NVRAMOFF
mdefine_line|#define HPLANCE_NVRAMOFF 0xC008                   /* etheraddress as one *nibble* per byte */
eof
