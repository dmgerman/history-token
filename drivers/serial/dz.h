multiline_comment|/*&n; * dz.h: Serial port driver for DECStations equiped &n; *       with the DZ chipset.&n; *&n; * Copyright (C) 1998 Olivier A. D. Lebaillif &n; *             &n; * Email: olivier.lebaillif@ifrsys.com&n; *&n; */
macro_line|#ifndef DZ_SERIAL_H
DECL|macro|DZ_SERIAL_H
mdefine_line|#define DZ_SERIAL_H
multiline_comment|/*&n; * Definitions for the Control and Status Received.&n; */
DECL|macro|DZ_TRDY
mdefine_line|#define DZ_TRDY        0x8000                 /* Transmitter empty */
DECL|macro|DZ_TIE
mdefine_line|#define DZ_TIE         0x4000                 /* Transmitter Interrupt Enable */
DECL|macro|DZ_RDONE
mdefine_line|#define DZ_RDONE       0x0080                 /* Receiver data ready */
DECL|macro|DZ_RIE
mdefine_line|#define DZ_RIE         0x0040                 /* Receive Interrupt Enable */
DECL|macro|DZ_MSE
mdefine_line|#define DZ_MSE         0x0020                 /* Master Scan Enable */
DECL|macro|DZ_CLR
mdefine_line|#define DZ_CLR         0x0010                 /* Master reset */
DECL|macro|DZ_MAINT
mdefine_line|#define DZ_MAINT       0x0008                 /* Loop Back Mode */
multiline_comment|/*&n; * Definitions for the Received buffer. &n; */
DECL|macro|DZ_RBUF_MASK
mdefine_line|#define DZ_RBUF_MASK   0x00FF                 /* Data Mask in the Receive Buffer */
DECL|macro|DZ_LINE_MASK
mdefine_line|#define DZ_LINE_MASK   0x0300                 /* Line Mask in the Receive Buffer */
DECL|macro|DZ_DVAL
mdefine_line|#define DZ_DVAL        0x8000                 /* Valid Data indicator */
DECL|macro|DZ_OERR
mdefine_line|#define DZ_OERR        0x4000                 /* Overrun error indicator */
DECL|macro|DZ_FERR
mdefine_line|#define DZ_FERR        0x2000                 /* Frame error indicator */
DECL|macro|DZ_PERR
mdefine_line|#define DZ_PERR        0x1000                 /* Parity error indicator */
DECL|macro|LINE
mdefine_line|#define LINE(x) (x &amp; DZ_LINE_MASK) &gt;&gt; 8       /* Get the line number from the input buffer */
DECL|macro|UCHAR
mdefine_line|#define UCHAR(x) (unsigned char)(x &amp; DZ_RBUF_MASK)
multiline_comment|/*&n; * Definitions for the Transmit Register.&n; */
DECL|macro|DZ_LINE_KEYBOARD
mdefine_line|#define DZ_LINE_KEYBOARD 0x0001
DECL|macro|DZ_LINE_MOUSE
mdefine_line|#define DZ_LINE_MOUSE    0x0002
DECL|macro|DZ_LINE_MODEM
mdefine_line|#define DZ_LINE_MODEM    0x0004
DECL|macro|DZ_LINE_PRINTER
mdefine_line|#define DZ_LINE_PRINTER  0x0008
DECL|macro|DZ_MODEM_DTR
mdefine_line|#define DZ_MODEM_DTR     0x0400               /* DTR for the modem line (2) */
multiline_comment|/*&n; * Definitions for the Modem Status Register.&n; */
DECL|macro|DZ_MODEM_DSR
mdefine_line|#define DZ_MODEM_DSR     0x0200               /* DSR for the modem line (2) */
multiline_comment|/*&n; * Definitions for the Transmit Data Register.&n; */
DECL|macro|DZ_BRK0
mdefine_line|#define DZ_BRK0          0x0100               /* Break assertion for line 0 */
DECL|macro|DZ_BRK1
mdefine_line|#define DZ_BRK1          0x0200               /* Break assertion for line 1 */
DECL|macro|DZ_BRK2
mdefine_line|#define DZ_BRK2          0x0400               /* Break assertion for line 2 */
DECL|macro|DZ_BRK3
mdefine_line|#define DZ_BRK3          0x0800               /* Break assertion for line 3 */
multiline_comment|/*&n; * Definitions for the Line Parameter Register.&n; */
DECL|macro|DZ_KEYBOARD
mdefine_line|#define DZ_KEYBOARD      0x0000               /* line 0 = keyboard */
DECL|macro|DZ_MOUSE
mdefine_line|#define DZ_MOUSE         0x0001               /* line 1 = mouse */
DECL|macro|DZ_MODEM
mdefine_line|#define DZ_MODEM         0x0002               /* line 2 = modem */
DECL|macro|DZ_PRINTER
mdefine_line|#define DZ_PRINTER       0x0003               /* line 3 = printer */
DECL|macro|DZ_CSIZE
mdefine_line|#define DZ_CSIZE         0x0018               /* Number of bits per byte (mask) */
DECL|macro|DZ_CS5
mdefine_line|#define DZ_CS5           0x0000               /* 5 bits per byte */
DECL|macro|DZ_CS6
mdefine_line|#define DZ_CS6           0x0008               /* 6 bits per byte */
DECL|macro|DZ_CS7
mdefine_line|#define DZ_CS7           0x0010               /* 7 bits per byte */
DECL|macro|DZ_CS8
mdefine_line|#define DZ_CS8           0x0018               /* 8 bits per byte */
DECL|macro|DZ_CSTOPB
mdefine_line|#define DZ_CSTOPB        0x0020               /* 2 stop bits instead of one */ 
DECL|macro|DZ_PARENB
mdefine_line|#define DZ_PARENB        0x0040               /* Parity enable */
DECL|macro|DZ_PARODD
mdefine_line|#define DZ_PARODD        0x0080               /* Odd parity instead of even */
DECL|macro|DZ_CBAUD
mdefine_line|#define DZ_CBAUD         0x0E00               /* Baud Rate (mask) */
DECL|macro|DZ_B50
mdefine_line|#define DZ_B50           0x0000
DECL|macro|DZ_B75
mdefine_line|#define DZ_B75           0x0100
DECL|macro|DZ_B110
mdefine_line|#define DZ_B110          0x0200
DECL|macro|DZ_B134
mdefine_line|#define DZ_B134          0x0300
DECL|macro|DZ_B150
mdefine_line|#define DZ_B150          0x0400
DECL|macro|DZ_B300
mdefine_line|#define DZ_B300          0x0500
DECL|macro|DZ_B600
mdefine_line|#define DZ_B600          0x0600
DECL|macro|DZ_B1200
mdefine_line|#define DZ_B1200         0x0700 
DECL|macro|DZ_B1800
mdefine_line|#define DZ_B1800         0x0800
DECL|macro|DZ_B2000
mdefine_line|#define DZ_B2000         0x0900
DECL|macro|DZ_B2400
mdefine_line|#define DZ_B2400         0x0A00
DECL|macro|DZ_B3600
mdefine_line|#define DZ_B3600         0x0B00
DECL|macro|DZ_B4800
mdefine_line|#define DZ_B4800         0x0C00
DECL|macro|DZ_B7200
mdefine_line|#define DZ_B7200         0x0D00
DECL|macro|DZ_B9600
mdefine_line|#define DZ_B9600         0x0E00
DECL|macro|DZ_CREAD
mdefine_line|#define DZ_CREAD         0x1000               /* Enable receiver */
DECL|macro|DZ_RXENAB
mdefine_line|#define DZ_RXENAB        0x1000               /* enable receive char */
multiline_comment|/*&n; * Addresses for the DZ registers&n; */
DECL|macro|DZ_CSR
mdefine_line|#define DZ_CSR       0x00            /* Control and Status Register */
DECL|macro|DZ_RBUF
mdefine_line|#define DZ_RBUF      0x08            /* Receive Buffer */
DECL|macro|DZ_LPR
mdefine_line|#define DZ_LPR       0x08            /* Line Parameters Register */
DECL|macro|DZ_TCR
mdefine_line|#define DZ_TCR       0x10            /* Transmitter Control Register */
DECL|macro|DZ_MSR
mdefine_line|#define DZ_MSR       0x18            /* Modem Status Register */
DECL|macro|DZ_TDR
mdefine_line|#define DZ_TDR       0x18            /* Transmit Data Register */
DECL|macro|DZ_NB_PORT
mdefine_line|#define DZ_NB_PORT 4
DECL|macro|DZ_XMIT_SIZE
mdefine_line|#define DZ_XMIT_SIZE   4096                 /* buffer size */
DECL|macro|DZ_WAKEUP_CHARS
mdefine_line|#define DZ_WAKEUP_CHARS   DZ_XMIT_SIZE/4
macro_line|#ifdef MODULE
r_int
id|init_module
(paren
r_void
)paren
r_void
id|cleanup_module
(paren
r_void
)paren
macro_line|#endif
macro_line|#endif /* DZ_SERIAL_H */
eof
