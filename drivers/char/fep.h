DECL|macro|CSTART
mdefine_line|#define CSTART       0x400L
DECL|macro|CMAX
mdefine_line|#define CMAX         0x800L
DECL|macro|ISTART
mdefine_line|#define ISTART       0x800L
DECL|macro|IMAX
mdefine_line|#define IMAX         0xC00L
DECL|macro|CIN
mdefine_line|#define CIN          0xD10L
DECL|macro|GLOBAL
mdefine_line|#define GLOBAL       0xD10L
DECL|macro|EIN
mdefine_line|#define EIN          0xD18L
DECL|macro|FEPSTAT
mdefine_line|#define FEPSTAT      0xD20L
DECL|macro|CHANSTRUCT
mdefine_line|#define CHANSTRUCT   0x1000L
DECL|macro|RXTXBUF
mdefine_line|#define RXTXBUF      0x4000L
DECL|struct|global_data
r_struct
id|global_data
(brace
DECL|member|cin
r_volatile
id|ushort
id|cin
suffix:semicolon
DECL|member|cout
r_volatile
id|ushort
id|cout
suffix:semicolon
DECL|member|cstart
r_volatile
id|ushort
id|cstart
suffix:semicolon
DECL|member|cmax
r_volatile
id|ushort
id|cmax
suffix:semicolon
DECL|member|ein
r_volatile
id|ushort
id|ein
suffix:semicolon
DECL|member|eout
r_volatile
id|ushort
id|eout
suffix:semicolon
DECL|member|istart
r_volatile
id|ushort
id|istart
suffix:semicolon
DECL|member|imax
r_volatile
id|ushort
id|imax
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|board_chan
r_struct
id|board_chan
(brace
DECL|member|filler1
r_int
id|filler1
suffix:semicolon
DECL|member|filler2
r_int
id|filler2
suffix:semicolon
DECL|member|tseg
r_volatile
id|ushort
id|tseg
suffix:semicolon
DECL|member|tin
r_volatile
id|ushort
id|tin
suffix:semicolon
DECL|member|tout
r_volatile
id|ushort
id|tout
suffix:semicolon
DECL|member|tmax
r_volatile
id|ushort
id|tmax
suffix:semicolon
DECL|member|rseg
r_volatile
id|ushort
id|rseg
suffix:semicolon
DECL|member|rin
r_volatile
id|ushort
id|rin
suffix:semicolon
DECL|member|rout
r_volatile
id|ushort
id|rout
suffix:semicolon
DECL|member|rmax
r_volatile
id|ushort
id|rmax
suffix:semicolon
DECL|member|tlow
r_volatile
id|ushort
id|tlow
suffix:semicolon
DECL|member|rlow
r_volatile
id|ushort
id|rlow
suffix:semicolon
DECL|member|rhigh
r_volatile
id|ushort
id|rhigh
suffix:semicolon
DECL|member|incr
r_volatile
id|ushort
id|incr
suffix:semicolon
DECL|member|etime
r_volatile
id|ushort
id|etime
suffix:semicolon
DECL|member|edelay
r_volatile
id|ushort
id|edelay
suffix:semicolon
DECL|member|dev
r_volatile
id|unchar
op_star
id|dev
suffix:semicolon
DECL|member|iflag
r_volatile
id|ushort
id|iflag
suffix:semicolon
DECL|member|oflag
r_volatile
id|ushort
id|oflag
suffix:semicolon
DECL|member|cflag
r_volatile
id|ushort
id|cflag
suffix:semicolon
DECL|member|gmask
r_volatile
id|ushort
id|gmask
suffix:semicolon
DECL|member|col
r_volatile
id|ushort
id|col
suffix:semicolon
DECL|member|delay
r_volatile
id|ushort
id|delay
suffix:semicolon
DECL|member|imask
r_volatile
id|ushort
id|imask
suffix:semicolon
DECL|member|tflush
r_volatile
id|ushort
id|tflush
suffix:semicolon
DECL|member|filler3
r_int
id|filler3
suffix:semicolon
DECL|member|filler4
r_int
id|filler4
suffix:semicolon
DECL|member|filler5
r_int
id|filler5
suffix:semicolon
DECL|member|filler6
r_int
id|filler6
suffix:semicolon
DECL|member|num
r_volatile
id|unchar
id|num
suffix:semicolon
DECL|member|ract
r_volatile
id|unchar
id|ract
suffix:semicolon
DECL|member|bstat
r_volatile
id|unchar
id|bstat
suffix:semicolon
DECL|member|tbusy
r_volatile
id|unchar
id|tbusy
suffix:semicolon
DECL|member|iempty
r_volatile
id|unchar
id|iempty
suffix:semicolon
DECL|member|ilow
r_volatile
id|unchar
id|ilow
suffix:semicolon
DECL|member|idata
r_volatile
id|unchar
id|idata
suffix:semicolon
DECL|member|eflag
r_volatile
id|unchar
id|eflag
suffix:semicolon
DECL|member|tflag
r_volatile
id|unchar
id|tflag
suffix:semicolon
DECL|member|rflag
r_volatile
id|unchar
id|rflag
suffix:semicolon
DECL|member|xmask
r_volatile
id|unchar
id|xmask
suffix:semicolon
DECL|member|xval
r_volatile
id|unchar
id|xval
suffix:semicolon
DECL|member|mstat
r_volatile
id|unchar
id|mstat
suffix:semicolon
DECL|member|mchange
r_volatile
id|unchar
id|mchange
suffix:semicolon
DECL|member|mint
r_volatile
id|unchar
id|mint
suffix:semicolon
DECL|member|lstat
r_volatile
id|unchar
id|lstat
suffix:semicolon
DECL|member|mtran
r_volatile
id|unchar
id|mtran
suffix:semicolon
DECL|member|orun
r_volatile
id|unchar
id|orun
suffix:semicolon
DECL|member|startca
r_volatile
id|unchar
id|startca
suffix:semicolon
DECL|member|stopca
r_volatile
id|unchar
id|stopca
suffix:semicolon
DECL|member|startc
r_volatile
id|unchar
id|startc
suffix:semicolon
DECL|member|stopc
r_volatile
id|unchar
id|stopc
suffix:semicolon
DECL|member|vnext
r_volatile
id|unchar
id|vnext
suffix:semicolon
DECL|member|hflow
r_volatile
id|unchar
id|hflow
suffix:semicolon
DECL|member|fillc
r_volatile
id|unchar
id|fillc
suffix:semicolon
DECL|member|ochar
r_volatile
id|unchar
id|ochar
suffix:semicolon
DECL|member|omask
r_volatile
id|unchar
id|omask
suffix:semicolon
DECL|member|filler7
id|unchar
id|filler7
suffix:semicolon
DECL|member|filler8
id|unchar
id|filler8
(braket
l_int|28
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SRXLWATER
mdefine_line|#define SRXLWATER      0xE0
DECL|macro|SRXHWATER
mdefine_line|#define SRXHWATER      0xE1
DECL|macro|STOUT
mdefine_line|#define STOUT          0xE2
DECL|macro|PAUSETX
mdefine_line|#define PAUSETX        0xE3
DECL|macro|RESUMETX
mdefine_line|#define RESUMETX       0xE4
DECL|macro|SAUXONOFFC
mdefine_line|#define SAUXONOFFC     0xE6
DECL|macro|SENDBREAK
mdefine_line|#define SENDBREAK      0xE8
DECL|macro|SETMODEM
mdefine_line|#define SETMODEM       0xE9
DECL|macro|SETIFLAGS
mdefine_line|#define SETIFLAGS      0xEA
DECL|macro|SONOFFC
mdefine_line|#define SONOFFC        0xEB
DECL|macro|STXLWATER
mdefine_line|#define STXLWATER      0xEC
DECL|macro|PAUSERX
mdefine_line|#define PAUSERX        0xEE
DECL|macro|RESUMERX
mdefine_line|#define RESUMERX       0xEF
DECL|macro|SETBUFFER
mdefine_line|#define SETBUFFER      0xF2
DECL|macro|SETCOOKED
mdefine_line|#define SETCOOKED      0xF3
DECL|macro|SETHFLOW
mdefine_line|#define SETHFLOW       0xF4
DECL|macro|SETCTRLFLAGS
mdefine_line|#define SETCTRLFLAGS   0xF5
DECL|macro|SETVNEXT
mdefine_line|#define SETVNEXT       0xF6
DECL|macro|BREAK_IND
mdefine_line|#define BREAK_IND        0x01
DECL|macro|LOWTX_IND
mdefine_line|#define LOWTX_IND        0x02
DECL|macro|EMPTYTX_IND
mdefine_line|#define EMPTYTX_IND      0x04
DECL|macro|DATA_IND
mdefine_line|#define DATA_IND         0x08
DECL|macro|MODEMCHG_IND
mdefine_line|#define MODEMCHG_IND     0x20
DECL|macro|RTS
mdefine_line|#define RTS   0x02
DECL|macro|CD
mdefine_line|#define CD    0x08
DECL|macro|DSR
mdefine_line|#define DSR   0x10
DECL|macro|CTS
mdefine_line|#define CTS   0x20
DECL|macro|RI
mdefine_line|#define RI    0x40
DECL|macro|DTR
mdefine_line|#define DTR   0x80
multiline_comment|/* These are termios bits as the FEP understands them */
multiline_comment|/* c_cflag bit meaning */
DECL|macro|FEP_CBAUD
mdefine_line|#define FEP_CBAUD&t;0000017
DECL|macro|FEP_B0
mdefine_line|#define  FEP_B0&t;&t;0000000&t;&t;/* hang up */
DECL|macro|FEP_B50
mdefine_line|#define  FEP_B50&t;0000001
DECL|macro|FEP_B75
mdefine_line|#define  FEP_B75&t;0000002
DECL|macro|FEP_B110
mdefine_line|#define  FEP_B110&t;0000003
DECL|macro|FEP_B134
mdefine_line|#define  FEP_B134&t;0000004
DECL|macro|FEP_B150
mdefine_line|#define  FEP_B150&t;0000005
DECL|macro|FEP_B200
mdefine_line|#define  FEP_B200&t;0000006
DECL|macro|FEP_B300
mdefine_line|#define  FEP_B300&t;0000007
DECL|macro|FEP_B600
mdefine_line|#define  FEP_B600&t;0000010
DECL|macro|FEP_B1200
mdefine_line|#define  FEP_B1200&t;0000011
DECL|macro|FEP_B1800
mdefine_line|#define  FEP_B1800&t;0000012
DECL|macro|FEP_B2400
mdefine_line|#define  FEP_B2400&t;0000013
DECL|macro|FEP_B4800
mdefine_line|#define  FEP_B4800&t;0000014
DECL|macro|FEP_B9600
mdefine_line|#define  FEP_B9600&t;0000015
DECL|macro|FEP_B19200
mdefine_line|#define  FEP_B19200&t;0000016
DECL|macro|FEP_B38400
mdefine_line|#define  FEP_B38400&t;0000017
DECL|macro|FEP_EXTA
mdefine_line|#define FEP_EXTA FEP_B19200
DECL|macro|FEP_EXTB
mdefine_line|#define FEP_EXTB FEP_B38400
DECL|macro|FEP_CSIZE
mdefine_line|#define FEP_CSIZE&t;0000060
DECL|macro|FEP_CS5
mdefine_line|#define   FEP_CS5&t;0000000
DECL|macro|FEP_CS6
mdefine_line|#define   FEP_CS6&t;0000020
DECL|macro|FEP_CS7
mdefine_line|#define   FEP_CS7&t;0000040
DECL|macro|FEP_CS8
mdefine_line|#define   FEP_CS8&t;0000060
DECL|macro|FEP_CSTOPB
mdefine_line|#define FEP_CSTOPB&t;0000100
DECL|macro|FEP_CREAD
mdefine_line|#define FEP_CREAD&t;0000200
DECL|macro|FEP_PARENB
mdefine_line|#define FEP_PARENB&t;0000400
DECL|macro|FEP_PARODD
mdefine_line|#define FEP_PARODD&t;0001000
DECL|macro|FEP_HUPCL
mdefine_line|#define FEP_HUPCL&t;0002000
DECL|macro|FEP_CLOCAL
mdefine_line|#define FEP_CLOCAL&t;0004000
DECL|macro|FEP_CIBAUD
mdefine_line|#define FEP_CIBAUD&t;03600000&t;&t;/* input baud rate (not used) */
DECL|macro|FEP_CRTSCTS
mdefine_line|#define FEP_CRTSCTS&t;  020000000000&t;&t;/* flow control */
eof
