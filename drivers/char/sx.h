multiline_comment|/*&n; *  sx.h&n; *&n; *  Copyright (C) 1998/1999 R.E.Wolff@BitWizard.nl&n; *&n; *  SX serial driver.&n; *  -- Supports SI, XIO and SX host cards. &n; *  -- Supports TAs, MTAs and SXDCs.&n; *&n; *  Version 1.3 -- March, 1999. &n; * &n; */
DECL|macro|SX_NBOARDS
mdefine_line|#define SX_NBOARDS        4
DECL|macro|SX_PORTSPERBOARD
mdefine_line|#define SX_PORTSPERBOARD 32
DECL|macro|SX_NPORTS
mdefine_line|#define SX_NPORTS        (SX_NBOARDS * SX_PORTSPERBOARD)
macro_line|#ifdef __KERNEL__
DECL|macro|SX_MAGIC
mdefine_line|#define SX_MAGIC 0x12345678
DECL|struct|sx_port
r_struct
id|sx_port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
multiline_comment|/*&n;  struct tq_struct        tqueue;&n;  struct tq_struct        tqueue_hangup;&n;  */
DECL|member|shutdown_wait
r_struct
id|wait_queue
op_star
id|shutdown_wait
suffix:semicolon
DECL|member|ch_base
r_int
id|ch_base
suffix:semicolon
DECL|member|c_dcd
r_int
id|c_dcd
suffix:semicolon
DECL|member|board
r_struct
id|sx_board
op_star
id|board
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|locks
r_int
id|locks
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sx_board
r_struct
id|sx_board
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|base2
r_int
r_int
id|base2
suffix:semicolon
DECL|member|hw_base
r_int
r_int
id|hw_base
suffix:semicolon
DECL|member|eisa_base
r_int
id|eisa_base
suffix:semicolon
DECL|member|port_base
r_int
id|port_base
suffix:semicolon
multiline_comment|/* Number of the first port */
DECL|member|ports
r_struct
id|sx_port
op_star
id|ports
suffix:semicolon
DECL|member|nports
r_int
id|nports
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|poll
r_int
id|poll
suffix:semicolon
DECL|member|ta_type
r_int
id|ta_type
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|locks
r_int
id|locks
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vpd_prom
r_struct
id|vpd_prom
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|hwrev
r_char
id|hwrev
suffix:semicolon
DECL|member|hwass
r_char
id|hwass
suffix:semicolon
DECL|member|uniqid
r_int
id|uniqid
suffix:semicolon
DECL|member|myear
r_char
id|myear
suffix:semicolon
DECL|member|mweek
r_char
id|mweek
suffix:semicolon
DECL|member|hw_feature
r_char
id|hw_feature
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|oem_id
r_char
id|oem_id
suffix:semicolon
DECL|member|identifier
r_char
id|identifier
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef MOD_RS232DB25MALE
DECL|macro|MOD_RS232DB25MALE
mdefine_line|#define MOD_RS232DB25MALE 0x0a
macro_line|#endif
DECL|macro|SI_ISA_BOARD
mdefine_line|#define SI_ISA_BOARD         0x00000001
DECL|macro|SX_ISA_BOARD
mdefine_line|#define SX_ISA_BOARD         0x00000002
DECL|macro|SX_PCI_BOARD
mdefine_line|#define SX_PCI_BOARD         0x00000004
DECL|macro|SX_CFPCI_BOARD
mdefine_line|#define SX_CFPCI_BOARD       0x00000008
DECL|macro|SX_CFISA_BOARD
mdefine_line|#define SX_CFISA_BOARD       0x00000010
DECL|macro|SI_EISA_BOARD
mdefine_line|#define SI_EISA_BOARD        0x00000020
DECL|macro|SX_BOARD_PRESENT
mdefine_line|#define SX_BOARD_PRESENT     0x00001000
DECL|macro|SX_BOARD_INITIALIZED
mdefine_line|#define SX_BOARD_INITIALIZED 0x00002000
DECL|macro|SX_IRQ_ALLOCATED
mdefine_line|#define SX_IRQ_ALLOCATED     0x00004000
DECL|macro|SX_BOARD_TYPE
mdefine_line|#define SX_BOARD_TYPE        0x000000ff
DECL|macro|IS_SX_BOARD
mdefine_line|#define IS_SX_BOARD(board) (board-&gt;flags &amp; (SX_PCI_BOARD | SX_CFPCI_BOARD | &bslash;&n;                                            SX_ISA_BOARD | SX_CFISA_BOARD))
DECL|macro|IS_SI_BOARD
mdefine_line|#define IS_SI_BOARD(board) (board-&gt;flags &amp; SI_ISA_BOARD)
DECL|macro|IS_EISA_BOARD
mdefine_line|#define IS_EISA_BOARD(board) (board-&gt;flags &amp; SI_EISA_BOARD)
DECL|macro|IS_CF_BOARD
mdefine_line|#define IS_CF_BOARD(board) (board-&gt;flags &amp; (SX_CFISA_BOARD | SX_CFPCI_BOARD))
DECL|macro|SERIAL_TYPE_NORMAL
mdefine_line|#define SERIAL_TYPE_NORMAL 1
multiline_comment|/* The SI processor clock is required to calculate the cc_int_count register&n;   value for the SI cards. */
DECL|macro|SI_PROCESSOR_CLOCK
mdefine_line|#define SI_PROCESSOR_CLOCK 25000000
multiline_comment|/* port flags */
multiline_comment|/* Make sure these don&squot;t clash with gs flags or async flags */
DECL|macro|SX_RX_THROTTLE
mdefine_line|#define SX_RX_THROTTLE        0x0000001
DECL|macro|SX_PORT_TRANSMIT_LOCK
mdefine_line|#define SX_PORT_TRANSMIT_LOCK  0
DECL|macro|SX_BOARD_INTR_LOCK
mdefine_line|#define SX_BOARD_INTR_LOCK     0
multiline_comment|/* Debug flags. Add these together to get more debug info. */
DECL|macro|SX_DEBUG_OPEN
mdefine_line|#define SX_DEBUG_OPEN          0x00000001
DECL|macro|SX_DEBUG_SETTING
mdefine_line|#define SX_DEBUG_SETTING       0x00000002
DECL|macro|SX_DEBUG_FLOW
mdefine_line|#define SX_DEBUG_FLOW          0x00000004
DECL|macro|SX_DEBUG_MODEMSIGNALS
mdefine_line|#define SX_DEBUG_MODEMSIGNALS  0x00000008
DECL|macro|SX_DEBUG_TERMIOS
mdefine_line|#define SX_DEBUG_TERMIOS       0x00000010
DECL|macro|SX_DEBUG_TRANSMIT
mdefine_line|#define SX_DEBUG_TRANSMIT      0x00000020
DECL|macro|SX_DEBUG_RECEIVE
mdefine_line|#define SX_DEBUG_RECEIVE       0x00000040
DECL|macro|SX_DEBUG_INTERRUPTS
mdefine_line|#define SX_DEBUG_INTERRUPTS    0x00000080
DECL|macro|SX_DEBUG_PROBE
mdefine_line|#define SX_DEBUG_PROBE         0x00000100
DECL|macro|SX_DEBUG_INIT
mdefine_line|#define SX_DEBUG_INIT          0x00000200
DECL|macro|SX_DEBUG_CLEANUP
mdefine_line|#define SX_DEBUG_CLEANUP       0x00000400
DECL|macro|SX_DEBUG_CLOSE
mdefine_line|#define SX_DEBUG_CLOSE         0x00000800
DECL|macro|SX_DEBUG_FIRMWARE
mdefine_line|#define SX_DEBUG_FIRMWARE      0x00001000
DECL|macro|SX_DEBUG_MEMTEST
mdefine_line|#define SX_DEBUG_MEMTEST       0x00002000
DECL|macro|SX_DEBUG_ALL
mdefine_line|#define SX_DEBUG_ALL           0xffffffff
DECL|macro|O_OTHER
mdefine_line|#define O_OTHER(tty)    &bslash;&n;      ((O_OLCUC(tty))  ||&bslash;&n;      (O_ONLCR(tty))   ||&bslash;&n;      (O_OCRNL(tty))   ||&bslash;&n;      (O_ONOCR(tty))   ||&bslash;&n;      (O_ONLRET(tty))  ||&bslash;&n;      (O_OFILL(tty))   ||&bslash;&n;      (O_OFDEL(tty))   ||&bslash;&n;      (O_NLDLY(tty))   ||&bslash;&n;      (O_CRDLY(tty))   ||&bslash;&n;      (O_TABDLY(tty))  ||&bslash;&n;      (O_BSDLY(tty))   ||&bslash;&n;      (O_VTDLY(tty))   ||&bslash;&n;      (O_FFDLY(tty)))
multiline_comment|/* Same for input. */
DECL|macro|I_OTHER
mdefine_line|#define I_OTHER(tty)    &bslash;&n;      ((I_INLCR(tty))  ||&bslash;&n;      (I_IGNCR(tty))   ||&bslash;&n;      (I_ICRNL(tty))   ||&bslash;&n;      (I_IUCLC(tty))   ||&bslash;&n;      (L_ISIG(tty)))
DECL|macro|MOD_TA
mdefine_line|#define MOD_TA   (        TA&gt;&gt;4)
DECL|macro|MOD_MTA
mdefine_line|#define MOD_MTA  (MTA_CD1400&gt;&gt;4)
DECL|macro|MOD_SXDC
mdefine_line|#define MOD_SXDC (      SXDC&gt;&gt;4)
multiline_comment|/* We copy the download code over to the card in chunks of ... bytes */
DECL|macro|SX_CHUNK_SIZE
mdefine_line|#define SX_CHUNK_SIZE 128
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* Specialix document 6210046-11 page 3 */
DECL|macro|SPX
mdefine_line|#define SPX(X) ((&squot;S&squot;&lt;&lt;24) | (&squot;P&squot; &lt;&lt; 16) | (X))
multiline_comment|/* Specialix-Linux specific IOCTLS. */
DECL|macro|SPXL
mdefine_line|#define SPXL(X) (SPX((&squot;L&squot; &lt;&lt; 8) | (X)))
DECL|macro|SXIO_SET_BOARD
mdefine_line|#define SXIO_SET_BOARD      SPXL(0x01)
DECL|macro|SXIO_GET_TYPE
mdefine_line|#define SXIO_GET_TYPE       SPXL(0x02)
DECL|macro|SXIO_DOWNLOAD
mdefine_line|#define SXIO_DOWNLOAD       SPXL(0x03)
DECL|macro|SXIO_INIT
mdefine_line|#define SXIO_INIT           SPXL(0x04)
DECL|macro|SXIO_SETDEBUG
mdefine_line|#define SXIO_SETDEBUG       SPXL(0x05)
DECL|macro|SXIO_GETDEBUG
mdefine_line|#define SXIO_GETDEBUG       SPXL(0x06)
DECL|macro|SXIO_DO_RAMTEST
mdefine_line|#define SXIO_DO_RAMTEST     SPXL(0x07)
DECL|macro|SXIO_SETGSDEBUG
mdefine_line|#define SXIO_SETGSDEBUG     SPXL(0x08)
DECL|macro|SXIO_GETGSDEBUG
mdefine_line|#define SXIO_GETGSDEBUG     SPXL(0x09)
DECL|macro|SXIO_GETNPORTS
mdefine_line|#define SXIO_GETNPORTS      SPXL(0x0a)
macro_line|#ifndef SXCTL_MISC_MINOR 
multiline_comment|/* Allow others to gather this into &quot;major.h&quot; or something like that */
DECL|macro|SXCTL_MISC_MINOR
mdefine_line|#define SXCTL_MISC_MINOR    167
macro_line|#endif
macro_line|#ifndef SX_NORMAL_MAJOR
multiline_comment|/* This allows overriding on the compiler commandline, or in a &quot;major.h&quot; &n;   include or something like that */
DECL|macro|SX_NORMAL_MAJOR
mdefine_line|#define SX_NORMAL_MAJOR  32
DECL|macro|SX_CALLOUT_MAJOR
mdefine_line|#define SX_CALLOUT_MAJOR 33
macro_line|#endif
DECL|macro|SX_TYPE_SX
mdefine_line|#define SX_TYPE_SX          0x01
DECL|macro|SX_TYPE_SI
mdefine_line|#define SX_TYPE_SI          0x02
DECL|macro|SX_TYPE_CF
mdefine_line|#define SX_TYPE_CF          0x03
DECL|macro|WINDOW_LEN
mdefine_line|#define WINDOW_LEN(board) (IS_CF_BOARD(board)?0x20000:SX_WINDOW_LEN)
multiline_comment|/*                         Need a #define for ^^^^^^^ !!! */
eof
