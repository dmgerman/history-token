macro_line|#ifndef _LINUX_TTY_H
DECL|macro|_LINUX_TTY_H
mdefine_line|#define _LINUX_TTY_H
multiline_comment|/*&n; * &squot;tty.h&squot; defines some structures used by tty_io.c and some defines.&n; */
multiline_comment|/*&n; * These constants are also useful for user-level apps (e.g., VC&n; * resizing).&n; */
DECL|macro|MIN_NR_CONSOLES
mdefine_line|#define MIN_NR_CONSOLES 1       /* must be at least 1 */
DECL|macro|MAX_NR_CONSOLES
mdefine_line|#define MAX_NR_CONSOLES&t;63&t;/* serial lines start at 64 */
DECL|macro|MAX_NR_USER_CONSOLES
mdefine_line|#define MAX_NR_USER_CONSOLES 63&t;/* must be root to allocate above this */
multiline_comment|/* Note: the ioctl VT_GETSTATE does not work for&n;&t;&t;   consoles 16 and higher (since it returns a short) */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_ldisc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Note: don&squot;t mess with NR_PTYS until you understand the tty minor &n; * number allocation game...&n; * (Note: the *_driver.minor_start values 1, 64, 128, 192 are&n; * hardcoded at present.)&n; */
DECL|macro|NR_PTYS
mdefine_line|#define NR_PTYS&t;&t;256&t;/* ptys/major */
DECL|macro|NR_LDISCS
mdefine_line|#define NR_LDISCS&t;16
multiline_comment|/*&n; * Unix98 PTY&squot;s can be defined as any multiple of NR_PTYS up to&n; * UNIX98_PTY_MAJOR_COUNT; this section defines what we need from the&n; * config options&n; */
macro_line|#ifdef CONFIG_UNIX98_PTYS
DECL|macro|UNIX98_NR_MAJORS
macro_line|# define UNIX98_NR_MAJORS ((CONFIG_UNIX98_PTY_COUNT+NR_PTYS-1)/NR_PTYS)
macro_line|# if UNIX98_NR_MAJORS &lt;= 0
DECL|macro|CONFIG_UNIX98_PTYS
macro_line|#  undef CONFIG_UNIX98_PTYS
macro_line|# elif UNIX98_NR_MAJORS &gt; UNIX98_PTY_MAJOR_COUNT
macro_line|#  error  Too many Unix98 ptys defined
DECL|macro|UNIX98_NR_MAJORS
macro_line|#  undef  UNIX98_NR_MAJORS
DECL|macro|UNIX98_NR_MAJORS
macro_line|#  define UNIX98_NR_MAJORS UNIX98_PTY_MAJOR_COUNT
macro_line|# endif
macro_line|#endif
multiline_comment|/*&n; * These are set up by the setup-routine at boot-time:&n; */
DECL|struct|screen_info
r_struct
id|screen_info
(brace
DECL|member|orig_x
r_int
r_char
id|orig_x
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|orig_y
r_int
r_char
id|orig_y
suffix:semicolon
multiline_comment|/* 0x01 */
DECL|member|dontuse1
r_int
r_int
id|dontuse1
suffix:semicolon
multiline_comment|/* 0x02 -- EXT_MEM_K sits here */
DECL|member|orig_video_page
r_int
r_int
id|orig_video_page
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|orig_video_mode
r_int
r_char
id|orig_video_mode
suffix:semicolon
multiline_comment|/* 0x06 */
DECL|member|orig_video_cols
r_int
r_char
id|orig_video_cols
suffix:semicolon
multiline_comment|/* 0x07 */
DECL|member|unused2
r_int
r_int
id|unused2
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|orig_video_ega_bx
r_int
r_int
id|orig_video_ega_bx
suffix:semicolon
multiline_comment|/* 0x0a */
DECL|member|unused3
r_int
r_int
id|unused3
suffix:semicolon
multiline_comment|/* 0x0c */
DECL|member|orig_video_lines
r_int
r_char
id|orig_video_lines
suffix:semicolon
multiline_comment|/* 0x0e */
DECL|member|orig_video_isVGA
r_int
r_char
id|orig_video_isVGA
suffix:semicolon
multiline_comment|/* 0x0f */
DECL|member|orig_video_points
r_int
r_int
id|orig_video_points
suffix:semicolon
multiline_comment|/* 0x10 */
multiline_comment|/* VESA graphic mode -- linear frame buffer */
DECL|member|lfb_width
r_int
r_int
id|lfb_width
suffix:semicolon
multiline_comment|/* 0x12 */
DECL|member|lfb_height
r_int
r_int
id|lfb_height
suffix:semicolon
multiline_comment|/* 0x14 */
DECL|member|lfb_depth
r_int
r_int
id|lfb_depth
suffix:semicolon
multiline_comment|/* 0x16 */
DECL|member|lfb_base
r_int
r_int
id|lfb_base
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|lfb_size
r_int
r_int
id|lfb_size
suffix:semicolon
multiline_comment|/* 0x1c */
DECL|member|dontuse2
DECL|member|dontuse3
r_int
r_int
id|dontuse2
comma
id|dontuse3
suffix:semicolon
multiline_comment|/* 0x20 -- CL_MAGIC and CL_OFFSET here */
DECL|member|lfb_linelength
r_int
r_int
id|lfb_linelength
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|red_size
r_int
r_char
id|red_size
suffix:semicolon
multiline_comment|/* 0x26 */
DECL|member|red_pos
r_int
r_char
id|red_pos
suffix:semicolon
multiline_comment|/* 0x27 */
DECL|member|green_size
r_int
r_char
id|green_size
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|green_pos
r_int
r_char
id|green_pos
suffix:semicolon
multiline_comment|/* 0x29 */
DECL|member|blue_size
r_int
r_char
id|blue_size
suffix:semicolon
multiline_comment|/* 0x2a */
DECL|member|blue_pos
r_int
r_char
id|blue_pos
suffix:semicolon
multiline_comment|/* 0x2b */
DECL|member|rsvd_size
r_int
r_char
id|rsvd_size
suffix:semicolon
multiline_comment|/* 0x2c */
DECL|member|rsvd_pos
r_int
r_char
id|rsvd_pos
suffix:semicolon
multiline_comment|/* 0x2d */
DECL|member|vesapm_seg
r_int
r_int
id|vesapm_seg
suffix:semicolon
multiline_comment|/* 0x2e */
DECL|member|vesapm_off
r_int
r_int
id|vesapm_off
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|pages
r_int
r_int
id|pages
suffix:semicolon
multiline_comment|/* 0x32 */
multiline_comment|/* 0x34 -- 0x3f reserved for future expansion */
)brace
suffix:semicolon
r_extern
r_struct
id|screen_info
id|screen_info
suffix:semicolon
DECL|macro|ORIG_X
mdefine_line|#define ORIG_X&t;&t;&t;(screen_info.orig_x)
DECL|macro|ORIG_Y
mdefine_line|#define ORIG_Y&t;&t;&t;(screen_info.orig_y)
DECL|macro|ORIG_VIDEO_MODE
mdefine_line|#define ORIG_VIDEO_MODE&t;&t;(screen_info.orig_video_mode)
DECL|macro|ORIG_VIDEO_COLS
mdefine_line|#define ORIG_VIDEO_COLS &t;(screen_info.orig_video_cols)
DECL|macro|ORIG_VIDEO_EGA_BX
mdefine_line|#define ORIG_VIDEO_EGA_BX&t;(screen_info.orig_video_ega_bx)
DECL|macro|ORIG_VIDEO_LINES
mdefine_line|#define ORIG_VIDEO_LINES&t;(screen_info.orig_video_lines)
DECL|macro|ORIG_VIDEO_ISVGA
mdefine_line|#define ORIG_VIDEO_ISVGA&t;(screen_info.orig_video_isVGA)
DECL|macro|ORIG_VIDEO_POINTS
mdefine_line|#define ORIG_VIDEO_POINTS       (screen_info.orig_video_points)
DECL|macro|VIDEO_TYPE_MDA
mdefine_line|#define VIDEO_TYPE_MDA&t;&t;0x10&t;/* Monochrome Text Display&t;*/
DECL|macro|VIDEO_TYPE_CGA
mdefine_line|#define VIDEO_TYPE_CGA&t;&t;0x11&t;/* CGA Display &t;&t;&t;*/
DECL|macro|VIDEO_TYPE_EGAM
mdefine_line|#define VIDEO_TYPE_EGAM&t;&t;0x20&t;/* EGA/VGA in Monochrome Mode&t;*/
DECL|macro|VIDEO_TYPE_EGAC
mdefine_line|#define VIDEO_TYPE_EGAC&t;&t;0x21&t;/* EGA in Color Mode&t;&t;*/
DECL|macro|VIDEO_TYPE_VGAC
mdefine_line|#define VIDEO_TYPE_VGAC&t;&t;0x22&t;/* VGA+ in Color Mode&t;&t;*/
DECL|macro|VIDEO_TYPE_VLFB
mdefine_line|#define VIDEO_TYPE_VLFB&t;&t;0x23&t;/* VESA VGA in graphic mode&t;*/
DECL|macro|VIDEO_TYPE_PICA_S3
mdefine_line|#define VIDEO_TYPE_PICA_S3&t;0x30&t;/* ACER PICA-61 local S3 video&t;*/
DECL|macro|VIDEO_TYPE_MIPS_G364
mdefine_line|#define VIDEO_TYPE_MIPS_G364&t;0x31    /* MIPS Magnum 4000 G364 video  */
DECL|macro|VIDEO_TYPE_SNI_RM
mdefine_line|#define VIDEO_TYPE_SNI_RM&t;0x32    /* SNI RM200 PCI video          */
DECL|macro|VIDEO_TYPE_SGI
mdefine_line|#define VIDEO_TYPE_SGI          0x33    /* Various SGI graphics hardware */
DECL|macro|VIDEO_TYPE_TGAC
mdefine_line|#define VIDEO_TYPE_TGAC&t;&t;0x40&t;/* DEC TGA */
DECL|macro|VIDEO_TYPE_SUN
mdefine_line|#define VIDEO_TYPE_SUN          0x50    /* Sun frame buffer. */
DECL|macro|VIDEO_TYPE_SUNPCI
mdefine_line|#define VIDEO_TYPE_SUNPCI       0x51    /* Sun PCI based frame buffer. */
DECL|macro|VIDEO_TYPE_PMAC
mdefine_line|#define VIDEO_TYPE_PMAC&t;&t;0x60&t;/* PowerMacintosh frame buffer. */
multiline_comment|/*&n; * This character is the same as _POSIX_VDISABLE: it cannot be used as&n; * a c_cc[] character, but indicates that a particular special character&n; * isn&squot;t in use (eg VINTR has no character etc)&n; */
DECL|macro|__DISABLED_CHAR
mdefine_line|#define __DISABLED_CHAR &squot;&bslash;0&squot;
multiline_comment|/*&n; * This is the flip buffer used for the tty driver.  The buffer is&n; * located in the tty structure, and is used as a high speed interface&n; * between the tty driver and the tty line discipline.&n; */
DECL|macro|TTY_FLIPBUF_SIZE
mdefine_line|#define TTY_FLIPBUF_SIZE 512
DECL|struct|tty_flip_buffer
r_struct
id|tty_flip_buffer
(brace
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|pty_sem
r_struct
id|semaphore
id|pty_sem
suffix:semicolon
DECL|member|char_buf_ptr
r_char
op_star
id|char_buf_ptr
suffix:semicolon
DECL|member|flag_buf_ptr
r_int
r_char
op_star
id|flag_buf_ptr
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|buf_num
r_int
id|buf_num
suffix:semicolon
DECL|member|char_buf
r_int
r_char
id|char_buf
(braket
l_int|2
op_star
id|TTY_FLIPBUF_SIZE
)braket
suffix:semicolon
DECL|member|flag_buf
r_char
id|flag_buf
(braket
l_int|2
op_star
id|TTY_FLIPBUF_SIZE
)braket
suffix:semicolon
DECL|member|slop
r_int
r_char
id|slop
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* N.B. bug overwrites buffer by 1 */
)brace
suffix:semicolon
multiline_comment|/*&n; * The pty uses char_buf and flag_buf as a contiguous buffer&n; */
DECL|macro|PTY_BUF_SIZE
mdefine_line|#define PTY_BUF_SIZE&t;4*TTY_FLIPBUF_SIZE
multiline_comment|/*&n; * When a break, frame error, or parity error happens, these codes are&n; * stuffed into the flags buffer.&n; */
DECL|macro|TTY_NORMAL
mdefine_line|#define TTY_NORMAL&t;0
DECL|macro|TTY_BREAK
mdefine_line|#define TTY_BREAK&t;1
DECL|macro|TTY_FRAME
mdefine_line|#define TTY_FRAME&t;2
DECL|macro|TTY_PARITY
mdefine_line|#define TTY_PARITY&t;3
DECL|macro|TTY_OVERRUN
mdefine_line|#define TTY_OVERRUN&t;4
DECL|macro|INTR_CHAR
mdefine_line|#define INTR_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VINTR])
DECL|macro|QUIT_CHAR
mdefine_line|#define QUIT_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VQUIT])
DECL|macro|ERASE_CHAR
mdefine_line|#define ERASE_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VERASE])
DECL|macro|KILL_CHAR
mdefine_line|#define KILL_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VKILL])
DECL|macro|EOF_CHAR
mdefine_line|#define EOF_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VEOF])
DECL|macro|TIME_CHAR
mdefine_line|#define TIME_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VTIME])
DECL|macro|MIN_CHAR
mdefine_line|#define MIN_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VMIN])
DECL|macro|SWTC_CHAR
mdefine_line|#define SWTC_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSWTC])
DECL|macro|START_CHAR
mdefine_line|#define START_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSTART])
DECL|macro|STOP_CHAR
mdefine_line|#define STOP_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSTOP])
DECL|macro|SUSP_CHAR
mdefine_line|#define SUSP_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSUSP])
DECL|macro|EOL_CHAR
mdefine_line|#define EOL_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VEOL])
DECL|macro|REPRINT_CHAR
mdefine_line|#define REPRINT_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VREPRINT])
DECL|macro|DISCARD_CHAR
mdefine_line|#define DISCARD_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VDISCARD])
DECL|macro|WERASE_CHAR
mdefine_line|#define WERASE_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VWERASE])
DECL|macro|LNEXT_CHAR
mdefine_line|#define LNEXT_CHAR(tty)&t;((tty)-&gt;termios-&gt;c_cc[VLNEXT])
DECL|macro|EOL2_CHAR
mdefine_line|#define EOL2_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VEOL2])
DECL|macro|_I_FLAG
mdefine_line|#define _I_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_iflag &amp; (f))
DECL|macro|_O_FLAG
mdefine_line|#define _O_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_oflag &amp; (f))
DECL|macro|_C_FLAG
mdefine_line|#define _C_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_cflag &amp; (f))
DECL|macro|_L_FLAG
mdefine_line|#define _L_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_lflag &amp; (f))
DECL|macro|I_IGNBRK
mdefine_line|#define I_IGNBRK(tty)&t;_I_FLAG((tty),IGNBRK)
DECL|macro|I_BRKINT
mdefine_line|#define I_BRKINT(tty)&t;_I_FLAG((tty),BRKINT)
DECL|macro|I_IGNPAR
mdefine_line|#define I_IGNPAR(tty)&t;_I_FLAG((tty),IGNPAR)
DECL|macro|I_PARMRK
mdefine_line|#define I_PARMRK(tty)&t;_I_FLAG((tty),PARMRK)
DECL|macro|I_INPCK
mdefine_line|#define I_INPCK(tty)&t;_I_FLAG((tty),INPCK)
DECL|macro|I_ISTRIP
mdefine_line|#define I_ISTRIP(tty)&t;_I_FLAG((tty),ISTRIP)
DECL|macro|I_INLCR
mdefine_line|#define I_INLCR(tty)&t;_I_FLAG((tty),INLCR)
DECL|macro|I_IGNCR
mdefine_line|#define I_IGNCR(tty)&t;_I_FLAG((tty),IGNCR)
DECL|macro|I_ICRNL
mdefine_line|#define I_ICRNL(tty)&t;_I_FLAG((tty),ICRNL)
DECL|macro|I_IUCLC
mdefine_line|#define I_IUCLC(tty)&t;_I_FLAG((tty),IUCLC)
DECL|macro|I_IXON
mdefine_line|#define I_IXON(tty)&t;_I_FLAG((tty),IXON)
DECL|macro|I_IXANY
mdefine_line|#define I_IXANY(tty)&t;_I_FLAG((tty),IXANY)
DECL|macro|I_IXOFF
mdefine_line|#define I_IXOFF(tty)&t;_I_FLAG((tty),IXOFF)
DECL|macro|I_IMAXBEL
mdefine_line|#define I_IMAXBEL(tty)&t;_I_FLAG((tty),IMAXBEL)
DECL|macro|O_OPOST
mdefine_line|#define O_OPOST(tty)&t;_O_FLAG((tty),OPOST)
DECL|macro|O_OLCUC
mdefine_line|#define O_OLCUC(tty)&t;_O_FLAG((tty),OLCUC)
DECL|macro|O_ONLCR
mdefine_line|#define O_ONLCR(tty)&t;_O_FLAG((tty),ONLCR)
DECL|macro|O_OCRNL
mdefine_line|#define O_OCRNL(tty)&t;_O_FLAG((tty),OCRNL)
DECL|macro|O_ONOCR
mdefine_line|#define O_ONOCR(tty)&t;_O_FLAG((tty),ONOCR)
DECL|macro|O_ONLRET
mdefine_line|#define O_ONLRET(tty)&t;_O_FLAG((tty),ONLRET)
DECL|macro|O_OFILL
mdefine_line|#define O_OFILL(tty)&t;_O_FLAG((tty),OFILL)
DECL|macro|O_OFDEL
mdefine_line|#define O_OFDEL(tty)&t;_O_FLAG((tty),OFDEL)
DECL|macro|O_NLDLY
mdefine_line|#define O_NLDLY(tty)&t;_O_FLAG((tty),NLDLY)
DECL|macro|O_CRDLY
mdefine_line|#define O_CRDLY(tty)&t;_O_FLAG((tty),CRDLY)
DECL|macro|O_TABDLY
mdefine_line|#define O_TABDLY(tty)&t;_O_FLAG((tty),TABDLY)
DECL|macro|O_BSDLY
mdefine_line|#define O_BSDLY(tty)&t;_O_FLAG((tty),BSDLY)
DECL|macro|O_VTDLY
mdefine_line|#define O_VTDLY(tty)&t;_O_FLAG((tty),VTDLY)
DECL|macro|O_FFDLY
mdefine_line|#define O_FFDLY(tty)&t;_O_FLAG((tty),FFDLY)
DECL|macro|C_BAUD
mdefine_line|#define C_BAUD(tty)&t;_C_FLAG((tty),CBAUD)
DECL|macro|C_CSIZE
mdefine_line|#define C_CSIZE(tty)&t;_C_FLAG((tty),CSIZE)
DECL|macro|C_CSTOPB
mdefine_line|#define C_CSTOPB(tty)&t;_C_FLAG((tty),CSTOPB)
DECL|macro|C_CREAD
mdefine_line|#define C_CREAD(tty)&t;_C_FLAG((tty),CREAD)
DECL|macro|C_PARENB
mdefine_line|#define C_PARENB(tty)&t;_C_FLAG((tty),PARENB)
DECL|macro|C_PARODD
mdefine_line|#define C_PARODD(tty)&t;_C_FLAG((tty),PARODD)
DECL|macro|C_HUPCL
mdefine_line|#define C_HUPCL(tty)&t;_C_FLAG((tty),HUPCL)
DECL|macro|C_CLOCAL
mdefine_line|#define C_CLOCAL(tty)&t;_C_FLAG((tty),CLOCAL)
DECL|macro|C_CIBAUD
mdefine_line|#define C_CIBAUD(tty)&t;_C_FLAG((tty),CIBAUD)
DECL|macro|C_CRTSCTS
mdefine_line|#define C_CRTSCTS(tty)&t;_C_FLAG((tty),CRTSCTS)
DECL|macro|L_ISIG
mdefine_line|#define L_ISIG(tty)&t;_L_FLAG((tty),ISIG)
DECL|macro|L_ICANON
mdefine_line|#define L_ICANON(tty)&t;_L_FLAG((tty),ICANON)
DECL|macro|L_XCASE
mdefine_line|#define L_XCASE(tty)&t;_L_FLAG((tty),XCASE)
DECL|macro|L_ECHO
mdefine_line|#define L_ECHO(tty)&t;_L_FLAG((tty),ECHO)
DECL|macro|L_ECHOE
mdefine_line|#define L_ECHOE(tty)&t;_L_FLAG((tty),ECHOE)
DECL|macro|L_ECHOK
mdefine_line|#define L_ECHOK(tty)&t;_L_FLAG((tty),ECHOK)
DECL|macro|L_ECHONL
mdefine_line|#define L_ECHONL(tty)&t;_L_FLAG((tty),ECHONL)
DECL|macro|L_NOFLSH
mdefine_line|#define L_NOFLSH(tty)&t;_L_FLAG((tty),NOFLSH)
DECL|macro|L_TOSTOP
mdefine_line|#define L_TOSTOP(tty)&t;_L_FLAG((tty),TOSTOP)
DECL|macro|L_ECHOCTL
mdefine_line|#define L_ECHOCTL(tty)&t;_L_FLAG((tty),ECHOCTL)
DECL|macro|L_ECHOPRT
mdefine_line|#define L_ECHOPRT(tty)&t;_L_FLAG((tty),ECHOPRT)
DECL|macro|L_ECHOKE
mdefine_line|#define L_ECHOKE(tty)&t;_L_FLAG((tty),ECHOKE)
DECL|macro|L_FLUSHO
mdefine_line|#define L_FLUSHO(tty)&t;_L_FLAG((tty),FLUSHO)
DECL|macro|L_PENDIN
mdefine_line|#define L_PENDIN(tty)&t;_L_FLAG((tty),PENDIN)
DECL|macro|L_IEXTEN
mdefine_line|#define L_IEXTEN(tty)&t;_L_FLAG((tty),IEXTEN)
multiline_comment|/*&n; * Where all of the state associated with a tty is kept while the tty&n; * is open.  Since the termios state should be kept even if the tty&n; * has been closed --- for things like the baud rate, etc --- it is&n; * not stored here, but rather a pointer to the real state is stored&n; * here.  Possible the winsize structure should have the same&n; * treatment, but (1) the default 80x24 is usually right and (2) it&squot;s&n; * most often used by a windowing system, which will set the correct&n; * size each time the window is created or resized anyway.&n; * IMPORTANT: since this structure is dynamically allocated, it must&n; * be no larger than 4096 bytes.  Changing TTY_FLIPBUF_SIZE will change&n; * the size of this structure, and it needs to be done with care.&n; * &t;&t;&t;&t;&t;&t;- TYT, 9/14/92&n; */
DECL|struct|tty_struct
r_struct
id|tty_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|driver
r_struct
id|tty_driver
id|driver
suffix:semicolon
DECL|member|ldisc
r_struct
id|tty_ldisc
id|ldisc
suffix:semicolon
DECL|member|termios
DECL|member|termios_locked
r_struct
id|termios
op_star
id|termios
comma
op_star
id|termios_locked
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|device
id|kdev_t
id|device
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|winsize
r_struct
id|winsize
id|winsize
suffix:semicolon
DECL|member|stopped
DECL|member|hw_stopped
DECL|member|flow_stopped
DECL|member|packet
r_int
r_char
id|stopped
suffix:colon
l_int|1
comma
id|hw_stopped
suffix:colon
l_int|1
comma
id|flow_stopped
suffix:colon
l_int|1
comma
id|packet
suffix:colon
l_int|1
suffix:semicolon
DECL|member|low_latency
DECL|member|warned
r_int
r_char
id|low_latency
suffix:colon
l_int|1
comma
id|warned
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ctrl_status
r_int
r_char
id|ctrl_status
suffix:semicolon
DECL|member|link
r_struct
id|tty_struct
op_star
id|link
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|flip
r_struct
id|tty_flip_buffer
id|flip
suffix:semicolon
DECL|member|max_flip_cnt
r_int
id|max_flip_cnt
suffix:semicolon
DECL|member|alt_speed
r_int
id|alt_speed
suffix:semicolon
multiline_comment|/* For magic substitution of 38400 bps */
DECL|member|write_wait
id|wait_queue_head_t
id|write_wait
suffix:semicolon
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
DECL|member|tq_hangup
r_struct
id|tq_struct
id|tq_hangup
suffix:semicolon
DECL|member|disc_data
r_void
op_star
id|disc_data
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
DECL|member|tty_files
r_struct
id|list_head
id|tty_files
suffix:semicolon
DECL|macro|N_TTY_BUF_SIZE
mdefine_line|#define N_TTY_BUF_SIZE 4096
multiline_comment|/*&n;&t; * The following is data for the N_TTY line discipline.  For&n;&t; * historical reasons, this is included in the tty structure.&n;&t; */
DECL|member|column
r_int
r_int
id|column
suffix:semicolon
DECL|member|lnext
DECL|member|erasing
DECL|member|raw
DECL|member|real_raw
DECL|member|icanon
r_int
r_char
id|lnext
suffix:colon
l_int|1
comma
id|erasing
suffix:colon
l_int|1
comma
id|raw
suffix:colon
l_int|1
comma
id|real_raw
suffix:colon
l_int|1
comma
id|icanon
suffix:colon
l_int|1
suffix:semicolon
DECL|member|closing
r_int
r_char
id|closing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|minimum_to_wake
r_int
r_int
id|minimum_to_wake
suffix:semicolon
DECL|member|overrun_time
r_int
id|overrun_time
suffix:semicolon
DECL|member|num_overrun
r_int
id|num_overrun
suffix:semicolon
DECL|member|process_char_map
r_int
r_int
id|process_char_map
(braket
l_int|256
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
DECL|member|read_buf
r_char
op_star
id|read_buf
suffix:semicolon
DECL|member|read_head
r_int
id|read_head
suffix:semicolon
DECL|member|read_tail
r_int
id|read_tail
suffix:semicolon
DECL|member|read_cnt
r_int
id|read_cnt
suffix:semicolon
DECL|member|read_flags
r_int
r_int
id|read_flags
(braket
id|N_TTY_BUF_SIZE
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
DECL|member|canon_data
r_int
id|canon_data
suffix:semicolon
DECL|member|canon_head
r_int
r_int
id|canon_head
suffix:semicolon
DECL|member|canon_column
r_int
r_int
id|canon_column
suffix:semicolon
DECL|member|atomic_read
r_struct
id|semaphore
id|atomic_read
suffix:semicolon
DECL|member|atomic_write
r_struct
id|semaphore
id|atomic_write
suffix:semicolon
DECL|member|read_lock
id|spinlock_t
id|read_lock
suffix:semicolon
multiline_comment|/* If the tty has a pending do_SAK, queue it here - akpm */
DECL|member|SAK_tq
r_struct
id|tq_struct
id|SAK_tq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* tty magic number */
DECL|macro|TTY_MAGIC
mdefine_line|#define TTY_MAGIC&t;&t;0x5401
multiline_comment|/*&n; * These bits are used in the flags field of the tty structure.&n; * &n; * So that interrupts won&squot;t be able to mess up the queues,&n; * copy_to_cooked must be atomic with respect to itself, as must&n; * tty-&gt;write.  Thus, you must use the inline functions set_bit() and&n; * clear_bit() to make things atomic.&n; */
DECL|macro|TTY_THROTTLED
mdefine_line|#define TTY_THROTTLED 0
DECL|macro|TTY_IO_ERROR
mdefine_line|#define TTY_IO_ERROR 1
DECL|macro|TTY_OTHER_CLOSED
mdefine_line|#define TTY_OTHER_CLOSED 2
DECL|macro|TTY_EXCLUSIVE
mdefine_line|#define TTY_EXCLUSIVE 3
DECL|macro|TTY_DEBUG
mdefine_line|#define TTY_DEBUG 4
DECL|macro|TTY_DO_WRITE_WAKEUP
mdefine_line|#define TTY_DO_WRITE_WAKEUP 5
DECL|macro|TTY_PUSH
mdefine_line|#define TTY_PUSH 6
DECL|macro|TTY_CLOSING
mdefine_line|#define TTY_CLOSING 7
DECL|macro|TTY_DONT_FLIP
mdefine_line|#define TTY_DONT_FLIP 8
DECL|macro|TTY_HW_COOK_OUT
mdefine_line|#define TTY_HW_COOK_OUT 14
DECL|macro|TTY_HW_COOK_IN
mdefine_line|#define TTY_HW_COOK_IN 15
DECL|macro|TTY_PTY_LOCK
mdefine_line|#define TTY_PTY_LOCK 16
DECL|macro|TTY_NO_WRITE_SPLIT
mdefine_line|#define TTY_NO_WRITE_SPLIT 17
DECL|macro|TTY_WRITE_FLUSH
mdefine_line|#define TTY_WRITE_FLUSH(tty) tty_write_flush((tty))
r_extern
r_void
id|tty_write_flush
c_func
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|termios
id|tty_std_termios
suffix:semicolon
r_extern
r_struct
id|tty_struct
op_star
id|redirect
suffix:semicolon
r_extern
r_struct
id|tty_ldisc
id|ldiscs
(braket
)braket
suffix:semicolon
r_extern
r_int
id|fg_console
comma
id|last_console
comma
id|want_console
suffix:semicolon
r_extern
r_int
id|kmsg_redirect
suffix:semicolon
r_extern
r_void
id|con_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|console_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|lp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mxser_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|moxa_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ip2_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pcxe_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|vcs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cy_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|stl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|stli_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|specialix_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|espserial_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|macserial_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tty_paranoia_check
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
id|kdev_t
id|device
comma
r_const
r_char
op_star
id|routine
)paren
suffix:semicolon
r_extern
r_char
op_star
id|tty_name
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
id|tty_wait_until_sent
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
id|tty_check_change
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|stop_tty
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|start_tty
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|tty_register_ldisc
c_func
(paren
r_int
id|disc
comma
r_struct
id|tty_ldisc
op_star
id|new_ldisc
)paren
suffix:semicolon
r_extern
r_int
id|tty_register_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_int
id|tty_unregister_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_void
id|tty_register_devfs
(paren
r_struct
id|tty_driver
op_star
id|driver
comma
r_int
r_int
id|flags
comma
r_int
id|minor
)paren
suffix:semicolon
r_extern
r_void
id|tty_unregister_devfs
(paren
r_struct
id|tty_driver
op_star
id|driver
comma
r_int
id|minor
)paren
suffix:semicolon
r_extern
r_int
id|tty_read_raw_data
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_char
op_star
id|bufp
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|tty_write_message
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
op_star
id|msg
)paren
suffix:semicolon
r_extern
r_int
id|is_orphaned_pgrp
c_func
(paren
r_int
id|pgrp
)paren
suffix:semicolon
r_extern
r_int
id|is_ignored
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_int
id|tty_signal
c_func
(paren
r_int
id|sig
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|tty_hangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|tty_vhangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|tty_unhangup
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_int
id|tty_hung_up_p
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_void
id|do_SAK
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|disassociate_ctty
c_func
(paren
r_int
id|priv
)paren
suffix:semicolon
r_extern
r_void
id|tty_flip_buffer_push
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|tty_get_baud_rate
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
multiline_comment|/* n_tty.c */
r_extern
r_struct
id|tty_ldisc
id|tty_ldisc_N_TTY
suffix:semicolon
multiline_comment|/* tty_ioctl.c */
r_extern
r_int
id|n_tty_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* serial.c */
r_extern
r_void
id|serial_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* pcxx.c */
r_extern
r_int
id|pcxe_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* printk.c */
r_extern
r_void
id|console_print
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* vt.c */
r_extern
r_int
id|vt_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
