multiline_comment|/*&n; *  IBM/3270 Driver -- Copyright (C) 2000 UTS Global LLC&n; *&n; *  tubio.h -- All-Purpose header file&n; *&n; *&n; *&n; *&n; *&n; *  Author:  Richard Hitt&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#ifndef IBM_TTY3270_MAJOR
DECL|macro|IBM_TTY3270_MAJOR
macro_line|#  define IBM_TTY3270_MAJOR 212
macro_line|#endif /* IBM_TTY3270_MAJOR */
macro_line|#ifndef IBM_FS3270_MAJOR
DECL|macro|IBM_FS3270_MAJOR
macro_line|#  define IBM_FS3270_MAJOR 213
macro_line|#endif /* IBM_FS3270_MAJOR */
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|macro|TUB
mdefine_line|#define TUB(x) ((&squot;3&squot;&lt;&lt;8)|(x))
DECL|macro|TUBICMD
mdefine_line|#define TUBICMD TUB(3)
DECL|macro|TUBOCMD
mdefine_line|#define TUBOCMD TUB(4)
DECL|macro|TUBGETI
mdefine_line|#define TUBGETI TUB(7)
DECL|macro|TUBGETO
mdefine_line|#define TUBGETO TUB(8)
DECL|macro|TUBSETMOD
mdefine_line|#define TUBSETMOD TUB(12)
DECL|macro|TUBGETMOD
mdefine_line|#define TUBGETMOD TUB(13)
DECL|macro|TIOPOLL
mdefine_line|#define TIOPOLL TUB(32)
DECL|macro|TIOPOKE
mdefine_line|#define TIOPOKE TUB(33)
DECL|macro|TIONPOKE
mdefine_line|#define TIONPOKE TUB(34)
DECL|macro|TIOTNORM
mdefine_line|#define TIOTNORM TUB(35)
multiline_comment|/* Local Channel Commands */
DECL|macro|TC_WRITE
mdefine_line|#define TC_WRITE   0x01
DECL|macro|TC_EWRITE
mdefine_line|#define TC_EWRITE  0x05
DECL|macro|TC_READMOD
mdefine_line|#define TC_READMOD 0x06
DECL|macro|TC_EWRITEA
mdefine_line|#define TC_EWRITEA 0x0d
DECL|macro|TC_WRITESF
mdefine_line|#define TC_WRITESF 0x11
multiline_comment|/* Buffer Control Orders */
DECL|macro|TO_SF
mdefine_line|#define TO_SF 0x1d
DECL|macro|TO_SBA
mdefine_line|#define TO_SBA 0x11
DECL|macro|TO_IC
mdefine_line|#define TO_IC 0x13
DECL|macro|TO_PT
mdefine_line|#define TO_PT 0x05
DECL|macro|TO_RA
mdefine_line|#define TO_RA 0x3c
DECL|macro|TO_SFE
mdefine_line|#define TO_SFE 0x29
DECL|macro|TO_EUA
mdefine_line|#define TO_EUA 0x12
DECL|macro|TO_MF
mdefine_line|#define TO_MF 0x2c
DECL|macro|TO_SA
mdefine_line|#define TO_SA 0x28
multiline_comment|/* Field Attribute Bytes */
DECL|macro|TF_INPUT
mdefine_line|#define TF_INPUT 0x40           /* Visible input */
DECL|macro|TF_INPUTN
mdefine_line|#define TF_INPUTN 0x4c          /* Invisible input */
DECL|macro|TF_INMDT
mdefine_line|#define TF_INMDT 0xc1           /* Visible, Set-MDT */
DECL|macro|TF_LOG
mdefine_line|#define TF_LOG 0x60
DECL|macro|TF_STAT
mdefine_line|#define TF_STAT 0x60
multiline_comment|/* Character Attribute Bytes */
DECL|macro|TAT_RESET
mdefine_line|#define TAT_RESET 0x00
DECL|macro|TAT_FIELD
mdefine_line|#define TAT_FIELD 0xc0
DECL|macro|TAT_EXTHI
mdefine_line|#define TAT_EXTHI 0x41
DECL|macro|TAT_COLOR
mdefine_line|#define TAT_COLOR 0x42
DECL|macro|TAT_CHARS
mdefine_line|#define TAT_CHARS 0x43
DECL|macro|TAT_TRANS
mdefine_line|#define TAT_TRANS 0x46
multiline_comment|/* Reset value */
DECL|macro|TAR_RESET
mdefine_line|#define TAR_RESET 0x00
multiline_comment|/* Color values */
DECL|macro|TAC_BLUE
mdefine_line|#define TAC_BLUE 0xf1
DECL|macro|TAC_RED
mdefine_line|#define TAC_RED 0xf2
DECL|macro|TAC_PINK
mdefine_line|#define TAC_PINK 0xf3
DECL|macro|TAC_GREEN
mdefine_line|#define TAC_GREEN 0xf4
DECL|macro|TAC_TURQ
mdefine_line|#define TAC_TURQ 0xf5
DECL|macro|TAC_YELLOW
mdefine_line|#define TAC_YELLOW 0xf6
DECL|macro|TAC_WHITE
mdefine_line|#define TAC_WHITE 0xf7
DECL|macro|TAC_DEFAULT
mdefine_line|#define TAC_DEFAULT 0x00
multiline_comment|/* Write Control Characters */
DECL|macro|TW_NONE
mdefine_line|#define TW_NONE 0x40            /* No particular action */
DECL|macro|TW_KR
mdefine_line|#define TW_KR 0xc2              /* Keyboard restore */
DECL|macro|TW_PLUSALARM
mdefine_line|#define TW_PLUSALARM 0x04       /* Add this bit for alarm */
multiline_comment|/* Attention-ID (AID) Characters */
DECL|macro|TA_CLEAR
mdefine_line|#define TA_CLEAR 0x6d
DECL|macro|TA_PA2
mdefine_line|#define TA_PA2 0x6e
DECL|macro|TA_ENTER
mdefine_line|#define TA_ENTER 0x7d
multiline_comment|/* more to come */
DECL|macro|MIN
mdefine_line|#define MIN(a, b) ((a) &lt; (b)? (a): (b))
DECL|macro|TUB_BUFADR
mdefine_line|#define TUB_BUFADR(adr, cpp) &bslash;&n;&t;tty3270_tub_bufadr(tubp, adr, cpp)
DECL|macro|TUB_EBCASC
mdefine_line|#define TUB_EBCASC(addr, nr) codepage_convert(tub_ebcasc, addr, nr)
DECL|macro|TUB_ASCEBC
mdefine_line|#define TUB_ASCEBC(addr, nr) codepage_convert(tub_ascebc, addr, nr)
multiline_comment|/*&n; *&n; * General global values for the tube driver&n; *&n; */
DECL|enum|tubmode
r_enum
id|tubmode
(brace
DECL|enumerator|TBM_LN
id|TBM_LN
comma
multiline_comment|/* Line mode */
DECL|enumerator|TBM_FS
id|TBM_FS
comma
multiline_comment|/* Fullscreen mode */
DECL|enumerator|TBM_FSLN
id|TBM_FSLN
multiline_comment|/* Line mode shelled out of fullscreen */
)brace
suffix:semicolon
DECL|enum|tubstat
r_enum
id|tubstat
(brace
multiline_comment|/* normal-mode status */
DECL|enumerator|TBS_RUNNING
id|TBS_RUNNING
comma
multiline_comment|/* none of the following */
DECL|enumerator|TBS_MORE
id|TBS_MORE
comma
multiline_comment|/* timed &quot;MORE...&quot; in status */
DECL|enumerator|TBS_HOLD
id|TBS_HOLD
multiline_comment|/* untimed &quot;HOLDING&quot; in status */
)brace
suffix:semicolon
DECL|enum|tubcmd
r_enum
id|tubcmd
(brace
multiline_comment|/* normal-mode actions to do */
DECL|enumerator|TBC_CONOPEN
id|TBC_CONOPEN
comma
multiline_comment|/* Erase-write the console */
DECL|enumerator|TBC_OPEN
id|TBC_OPEN
comma
multiline_comment|/* Open the tty screen */
DECL|enumerator|TBC_UPDATE
id|TBC_UPDATE
comma
multiline_comment|/* Add lines to the log, clear cmdline */
DECL|enumerator|TBC_UPDLOG
id|TBC_UPDLOG
comma
multiline_comment|/* Add lines to log */
DECL|enumerator|TBC_KRUPDLOG
id|TBC_KRUPDLOG
comma
multiline_comment|/* Add lines to log, reset kbd */
DECL|enumerator|TBC_CLEAR
id|TBC_CLEAR
comma
multiline_comment|/* Build screen from scratch */
DECL|enumerator|TBC_CLRUPDLOG
id|TBC_CLRUPDLOG
comma
multiline_comment|/* Do log &amp; status, not cmdline */
DECL|enumerator|TBC_UPDSTAT
id|TBC_UPDSTAT
comma
multiline_comment|/* Do status update only */
DECL|enumerator|TBC_CLRINPUT
id|TBC_CLRINPUT
comma
multiline_comment|/* Clear input area only */
DECL|enumerator|TBC_UPDINPUT
id|TBC_UPDINPUT
multiline_comment|/* Update input area only */
)brace
suffix:semicolon
DECL|enum|tubwhat
r_enum
id|tubwhat
(brace
multiline_comment|/* echo what= proc actions */
DECL|enumerator|TW_BOGUS
id|TW_BOGUS
comma
multiline_comment|/* Nothing at all */
DECL|enumerator|TW_CONFIG
id|TW_CONFIG
multiline_comment|/* Output configuration info */
)brace
suffix:semicolon
DECL|macro|TUBMAXMINS
mdefine_line|#define TUBMAXMINS      256
DECL|macro|TUB_DEV
mdefine_line|#define TUB_DEV MKDEV(IBM_FS3270_MAJ, 0)        /* Generic /dev/3270/tub */
DECL|macro|_GEOM_ROWS
mdefine_line|#define _GEOM_ROWS 24
DECL|macro|_GEOM_COLS
mdefine_line|#define _GEOM_COLS 80
DECL|macro|GEOM_ROWS
mdefine_line|#define GEOM_ROWS (tubp-&gt;geom_rows)
DECL|macro|GEOM_COLS
mdefine_line|#define GEOM_COLS (tubp-&gt;geom_cols)
DECL|macro|GEOM_MAXROWS
mdefine_line|#define GEOM_MAXROWS 127
DECL|macro|GEOM_MAXCOLS
mdefine_line|#define GEOM_MAXCOLS 132
DECL|macro|GEOM_INPLEN
mdefine_line|#define GEOM_INPLEN (GEOM_COLS * 2 - 20)
DECL|macro|GEOM_MAXINPLEN
mdefine_line|#define GEOM_MAXINPLEN (GEOM_MAXCOLS * 2 - 20)
DECL|macro|GEOM_INPUT
mdefine_line|#define GEOM_INPUT (GEOM_COLS * (GEOM_ROWS - 2) - 1)  /* input atr posn */
DECL|macro|GEOM_STAT
mdefine_line|#define GEOM_STAT (GEOM_INPUT + 1 + GEOM_INPLEN)
DECL|macro|GEOM_LOG
mdefine_line|#define GEOM_LOG   (GEOM_COLS * GEOM_ROWS - 1)   /* log atr posn */
DECL|macro|TS_RUNNING
mdefine_line|#define TS_RUNNING &quot;Linux Running     &quot;
DECL|macro|TS_MORE
mdefine_line|#define TS_MORE    &quot;Linux More...     &quot;
DECL|macro|DEFAULT_SCROLLTIME
mdefine_line|#define DEFAULT_SCROLLTIME 5
DECL|macro|TS_HOLD
mdefine_line|#define TS_HOLD    &quot;Linux Holding     &quot;
multiline_comment|/* data length used by tty3270_set_status_area: SBA (3), SF (2), data */
DECL|macro|TS_LENGTH
mdefine_line|#define TS_LENGTH (sizeof TS_RUNNING + 3 + 2)
r_typedef
r_struct
(brace
DECL|member|aid
r_int
id|aid
suffix:semicolon
multiline_comment|/* What-to-do flags */
DECL|member|string
r_char
op_star
id|string
suffix:semicolon
multiline_comment|/* Optional input string */
DECL|typedef|aid_t
)brace
id|aid_t
suffix:semicolon
DECL|macro|AIDENTRY
mdefine_line|#define AIDENTRY(ch, tubp)  (&amp;((tubp)-&gt;tty_aid[(ch) &amp; 0x3f]))
multiline_comment|/* For TUBGETMOD and TUBSETMOD.  Should include. */
DECL|struct|tubiocb
r_typedef
r_struct
id|tubiocb
(brace
DECL|member|model
r_int
id|model
suffix:semicolon
DECL|member|line_cnt
r_int
id|line_cnt
suffix:semicolon
DECL|member|col_cnt
r_int
id|col_cnt
suffix:semicolon
DECL|member|pf_cnt
r_int
id|pf_cnt
suffix:semicolon
DECL|member|re_cnt
r_int
id|re_cnt
suffix:semicolon
DECL|member|map
r_int
id|map
suffix:semicolon
DECL|typedef|tubiocb_t
)brace
id|tubiocb_t
suffix:semicolon
multiline_comment|/* Flags that go in int aid, above */
DECL|macro|TA_CLEARKEY
mdefine_line|#define TA_CLEARKEY     0x01            /* Key does hardware CLEAR */
DECL|macro|TA_SHORTREAD
mdefine_line|#define TA_SHORTREAD    0x02            /* Key does hardware shortread */
multiline_comment|/* If both are off, key does hardware Read Modified. */
DECL|macro|TA_DOENTER
mdefine_line|#define TA_DOENTER      0x04            /* Treat key like ENTER */
DECL|macro|TA_DOSTRING
mdefine_line|#define TA_DOSTRING     0x08            /* Use string and ENTER */
DECL|macro|TA_DOSTRINGD
mdefine_line|#define TA_DOSTRINGD    0x10            /* Display string &amp; set MDT */
DECL|macro|TA_CLEARLOG
mdefine_line|#define TA_CLEARLOG     0x20            /* Make key cause clear of log */
multiline_comment|/*&n; * Tube driver buffer control block&n; */
DECL|struct|bcb_s
r_typedef
r_struct
id|bcb_s
(brace
DECL|member|bc_buf
r_char
op_star
id|bc_buf
suffix:semicolon
multiline_comment|/* Pointer to buffer */
DECL|member|bc_len
r_int
id|bc_len
suffix:semicolon
multiline_comment|/* Length of buffer */
DECL|member|bc_cnt
r_int
id|bc_cnt
suffix:semicolon
multiline_comment|/* Count of bytes buffered */
DECL|member|bc_wr
r_int
id|bc_wr
suffix:semicolon
multiline_comment|/* Posn to write next byte into */
DECL|member|bc_rd
r_int
id|bc_rd
suffix:semicolon
multiline_comment|/* Posn to read next byte from */
DECL|typedef|bcb_t
)brace
id|bcb_t
suffix:semicolon
DECL|struct|tub_s
r_typedef
r_struct
id|tub_s
(brace
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|irqrc
r_int
id|irqrc
suffix:semicolon
DECL|member|devno
r_int
id|devno
suffix:semicolon
DECL|member|geom_rows
r_int
id|geom_rows
suffix:semicolon
DECL|member|geom_cols
r_int
id|geom_cols
suffix:semicolon
DECL|member|tubiocb
id|tubiocb_t
id|tubiocb
suffix:semicolon
DECL|member|lnopen
r_int
id|lnopen
suffix:semicolon
DECL|member|fsopen
r_int
id|fsopen
suffix:semicolon
DECL|member|icmd
r_int
id|icmd
suffix:semicolon
DECL|member|ocmd
r_int
id|ocmd
suffix:semicolon
DECL|member|devstat
id|devstat_t
id|devstat
suffix:semicolon
DECL|member|rccw
id|ccw1_t
id|rccw
suffix:semicolon
DECL|member|wccw
id|ccw1_t
id|wccw
suffix:semicolon
DECL|member|wbuf
r_void
op_star
id|wbuf
suffix:semicolon
DECL|member|cswl
r_int
id|cswl
suffix:semicolon
DECL|member|intv
r_void
(paren
op_star
id|intv
)paren
(paren
r_struct
id|tub_s
op_star
comma
id|devstat_t
op_star
)paren
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
DECL|member|waitq
r_struct
id|wait_queue
op_star
id|waitq
suffix:semicolon
macro_line|#else
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
macro_line|#endif
DECL|member|dstat
r_int
id|dstat
suffix:semicolon
DECL|member|sense
id|sense_t
id|sense
suffix:semicolon
DECL|member|mode
r_enum
id|tubmode
id|mode
suffix:semicolon
DECL|member|stat
r_enum
id|tubstat
id|stat
suffix:semicolon
DECL|member|cmd
r_enum
id|tubcmd
id|cmd
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* See below for values */
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
multiline_comment|/* Stuff for fs-driver support */
DECL|member|fs_pid
id|pid_t
id|fs_pid
suffix:semicolon
multiline_comment|/* Pid if TBM_FS */
multiline_comment|/* Stuff for tty-driver support */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|tty_input
r_char
id|tty_input
(braket
id|GEOM_MAXINPLEN
)braket
suffix:semicolon
multiline_comment|/* tty input area */
DECL|member|tty_inattr
r_int
id|tty_inattr
suffix:semicolon
multiline_comment|/* input-area field attribute */
DECL|macro|TTY_OUTPUT_SIZE
mdefine_line|#define TTY_OUTPUT_SIZE 1024
DECL|member|tty_bcb
id|bcb_t
id|tty_bcb
suffix:semicolon
multiline_comment|/* Output buffer control info */
DECL|member|tty_oucol
r_int
id|tty_oucol
suffix:semicolon
multiline_comment|/* Kludge */
DECL|member|tty_nextlogx
r_int
id|tty_nextlogx
suffix:semicolon
multiline_comment|/* next screen-log position */
DECL|member|tty_scrolltime
r_int
id|tty_scrolltime
suffix:semicolon
multiline_comment|/* scrollforward wait time, sec */
DECL|member|tty_stimer
r_struct
id|timer_list
id|tty_stimer
suffix:semicolon
multiline_comment|/* timer for scrolltime */
DECL|member|tty_aid
id|aid_t
id|tty_aid
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Aid descriptors */
DECL|member|tty_aidinit
r_int
id|tty_aidinit
suffix:semicolon
multiline_comment|/* Boolean */
DECL|member|tty_showaidx
r_int
id|tty_showaidx
suffix:semicolon
multiline_comment|/* Last aid x to set_aid */
DECL|member|tty_14bitadr
r_int
id|tty_14bitadr
suffix:semicolon
multiline_comment|/* 14-bit bufadrs okay */
DECL|macro|MAX_TTY_ESCA
mdefine_line|#define MAX_TTY_ESCA 24&t;&t;&t;/* Set-Attribute-Order array */
DECL|member|tty_esca
r_char
id|tty_esca
(braket
id|MAX_TTY_ESCA
)braket
suffix:semicolon
multiline_comment|/* SA array */
DECL|member|tty_escx
r_int
id|tty_escx
suffix:semicolon
multiline_comment|/* Current index within it */
multiline_comment|/* For command recall --- */
DECL|member|tty_rclbufs
r_char
op_star
(paren
op_star
id|tty_rclbufs
)paren
(braket
)braket
suffix:semicolon
multiline_comment|/* Array of ptrs to recall bufs */
DECL|member|tty_rclk
r_int
id|tty_rclk
suffix:semicolon
multiline_comment|/* Size of array tty_rclbufs */
DECL|member|tty_rclp
r_int
id|tty_rclp
suffix:semicolon
multiline_comment|/* Index for most-recent cmd */
DECL|member|tty_rclb
r_int
id|tty_rclb
suffix:semicolon
multiline_comment|/* Index for backscrolling */
multiline_comment|/* Work area to contain the hardware write stream */
DECL|member|ttyscreen
r_char
(paren
op_star
id|ttyscreen
)paren
(braket
)braket
suffix:semicolon
multiline_comment|/* ptr to data stream area */
DECL|member|ttyscreenl
r_int
id|ttyscreenl
suffix:semicolon
multiline_comment|/* its length */
DECL|member|ttyccw
id|ccw1_t
id|ttyccw
suffix:semicolon
DECL|typedef|tub_t
)brace
id|tub_t
suffix:semicolon
multiline_comment|/* values for flags: */
DECL|macro|TUB_WORKING
mdefine_line|#define&t;TUB_WORKING&t;0x0001
DECL|macro|TUB_BHPENDING
mdefine_line|#define&t;TUB_BHPENDING&t;0x0002
DECL|macro|TUB_RDPENDING
mdefine_line|#define&t;TUB_RDPENDING&t;0x0004
DECL|macro|TUB_ALARM
mdefine_line|#define&t;TUB_ALARM&t;0x0008
DECL|macro|TUB_SCROLLTIMING
mdefine_line|#define&t;TUB_SCROLLTIMING  0x0010
DECL|macro|TUB_ATTN
mdefine_line|#define&t;TUB_ATTN&t;0x0020
DECL|macro|TUB_IACTIVE
mdefine_line|#define&t;TUB_IACTIVE&t;0x0040
DECL|macro|TUB_SIZED
mdefine_line|#define&t;TUB_SIZED&t;0x0080
DECL|macro|TUB_EXPECT_DE
mdefine_line|#define&t;TUB_EXPECT_DE&t;0x0100
DECL|macro|TUB_UNSOL_DE
mdefine_line|#define&t;TUB_UNSOL_DE&t;0x0200
DECL|macro|TUB_OPEN_STET
mdefine_line|#define&t;TUB_OPEN_STET&t;0x0400&t;&t;/* No screen clear on open */
DECL|macro|TUB_UE_BUSY
mdefine_line|#define&t;TUB_UE_BUSY&t;0x0800
macro_line|#ifdef CONFIG_3270_CONSOLE
multiline_comment|/*&n; * Extra stuff for 3270 console support&n; */
DECL|macro|S390_CONSOLE_DEV
mdefine_line|#define&t;S390_CONSOLE_DEV MKDEV(TTY_MAJOR, 64)
r_extern
r_int
id|tub3270_con_devno
suffix:semicolon
r_extern
r_char
(paren
op_star
id|tub3270_con_output
)paren
(braket
)braket
suffix:semicolon
r_extern
r_int
id|tub3270_con_outputl
suffix:semicolon
r_extern
r_int
id|tub3270_con_ouwr
suffix:semicolon
r_extern
r_int
id|tub3270_con_oucount
suffix:semicolon
r_extern
r_int
id|tub3270_con_irq
suffix:semicolon
r_extern
id|tub_t
op_star
id|tub3270_con_tubp
suffix:semicolon
r_extern
r_struct
id|tty_driver
id|tty3270_con_driver
suffix:semicolon
macro_line|#endif /* CONFIG_3270_CONSOLE */
r_extern
r_int
id|tubnummins
suffix:semicolon
r_extern
id|tub_t
op_star
(paren
op_star
id|tubminors
)paren
(braket
id|TUBMAXMINS
)braket
suffix:semicolon
r_extern
id|tub_t
op_star
(paren
op_star
(paren
op_star
id|tubirqs
)paren
(braket
l_int|256
)braket
)paren
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
r_char
id|tub_ascebc
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
r_char
id|tub_ebcasc
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
r_char
id|tub_ebcgraf
(braket
l_int|64
)braket
suffix:semicolon
r_extern
r_int
id|tubdebug
suffix:semicolon
r_extern
r_int
id|fs3270_major
suffix:semicolon
r_extern
r_int
id|tty3270_major
suffix:semicolon
r_extern
r_int
id|tty3270_proc_misc
suffix:semicolon
r_extern
r_enum
id|tubwhat
id|tty3270_proc_what
suffix:semicolon
macro_line|#ifndef spin_trylock_irqsave
DECL|macro|spin_trylock_irqsave
mdefine_line|#define spin_trylock_irqsave(lock, flags) &bslash;&n;({ &bslash;&n;&t;int success; &bslash;&n;&t;__save_flags(flags); &bslash;&n;&t;__cli(); &bslash;&n;&t;success = spin_trylock(lock); &bslash;&n;&t;if (success == 0) &bslash;&n;&t;&t;__restore_flags(flags); &bslash;&n;&t;success; &bslash;&n;})
macro_line|#endif /* if not spin_trylock_irqsave */
macro_line|#ifndef s390irq_spin_trylock_irqsave
DECL|macro|s390irq_spin_trylock_irqsave
mdefine_line|#define s390irq_spin_trylock_irqsave(irq, flags) &bslash;&n;&t;spin_trylock_irqsave(&amp;(ioinfo[irq]-&gt;irq_lock), flags)
macro_line|#endif /* if not s390irq_spin_trylock_irqsave */
DECL|macro|TUBLOCK
mdefine_line|#define TUBLOCK(irq, flags) &bslash;&n;&t;s390irq_spin_lock_irqsave(irq, flags)
DECL|macro|TUBTRYLOCK
mdefine_line|#define TUBTRYLOCK(irq, flags) &bslash;&n;&t;s390irq_spin_trylock_irqsave(irq, flags)
DECL|macro|TUBUNLOCK
mdefine_line|#define TUBUNLOCK(irq, flags) &bslash;&n;&t;s390irq_spin_unlock_irqrestore(irq, flags)
multiline_comment|/*&n; * Find tub_t * given fullscreen device&squot;s irq (subchannel number)&n; */
r_extern
id|tub_t
op_star
id|tubfindbyirq
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|IRQ2TUB
mdefine_line|#define IRQ2TUB(irq) tubfindbyirq(irq)
multiline_comment|/*&n; * Find tub_t * given fullscreen device&squot;s inode pointer&n; * This algorithm takes into account /dev/3270/tub.&n; */
macro_line|#ifdef CONFIG_3270_CONSOLE
DECL|macro|INODE2TUB
mdefine_line|#define INODE2TUB(ip) &bslash;&n;({ &bslash;&n;&t;unsigned int minor; &bslash;&n;&t;tub_t *tubp = NULL; &bslash;&n;&t;minor = MINOR((ip)-&gt;i_rdev); &bslash;&n;&t;if (minor == 0 &amp;&amp; current-&gt;tty != NULL) { &bslash;&n;&t;&t;if (tub3270_con_tubp != NULL &amp;&amp; &bslash;&n;&t;&t;    current-&gt;tty-&gt;device == S390_CONSOLE_DEV) &bslash;&n;&t;&t;&t;minor = tub3270_con_tubp-&gt;minor; &bslash;&n;&t;&t;else if (MAJOR(current-&gt;tty-&gt;device) == IBM_TTY3270_MAJOR) &bslash;&n;&t;&t;&t;minor = MINOR(current-&gt;tty-&gt;device); &bslash;&n;&t;} &bslash;&n;&t;if (minor &lt;= tubnummins &amp;&amp; minor &gt; 0) &bslash;&n;&t;&t;tubp = (*tubminors)[minor]; &bslash;&n;&t;tubp; &bslash;&n;})
macro_line|#else /* not CONFIG_3270_CONSOLE */
DECL|macro|INODE2TUB
mdefine_line|#define INODE2TUB(ip) &bslash;&n;({ &bslash;&n;&t;unsigned int minor; &bslash;&n;&t;tub_t *tubp = NULL; &bslash;&n;&t;minor = MINOR((ip)-&gt;i_rdev); &bslash;&n;&t;if (minor == 0 &amp;&amp; current-&gt;tty != NULL &amp;&amp; &bslash;&n;&t;    MAJOR(current-&gt;tty-&gt;device) == IBM_TTY3270_MAJOR) &bslash;&n;&t;&t;minor = MINOR(current-&gt;tty-&gt;device); &bslash;&n;&t;if (minor &lt;= tubnummins &amp;&amp; minor &gt; 0) &bslash;&n;&t;&t;tubp = (*tubminors)[minor]; &bslash;&n;&t;tubp; &bslash;&n;})
macro_line|#endif /* CONFIG_3270_CONSOLE or not */
multiline_comment|/*&n; * Find tub_t * given non-fullscreen (tty) device&squot;s tty_struct pointer&n; */
macro_line|#ifdef CONFIG_3270_CONSOLE
DECL|macro|TTY2TUB
mdefine_line|#define TTY2TUB(tty) &bslash;&n;({ &bslash;&n;&t;unsigned int minor; &bslash;&n;&t;tub_t *tubp = NULL; &bslash;&n;&t;minor = MINOR(tty-&gt;device); &bslash;&n;&t;if (tty-&gt;device == S390_CONSOLE_DEV) &bslash;&n;&t;&t;tubp = tub3270_con_tubp; &bslash;&n;&t;else if (minor &lt;= tubnummins &amp;&amp; minor &gt; 0) &bslash;&n;&t;&t;tubp = (*tubminors)[minor]; &bslash;&n;&t;tubp; &bslash;&n;})
macro_line|#else /* if not CONFIG_3270_CONSOLE */
DECL|macro|TTY2TUB
mdefine_line|#define TTY2TUB(tty) &bslash;&n;({ &bslash;&n;&t;unsigned int minor; &bslash;&n;&t;tub_t *tubp = NULL; &bslash;&n;&t;minor = MINOR(tty-&gt;device); &bslash;&n;&t;if (minor &lt;= tubnummins &amp;&amp; minor &gt; 0) &bslash;&n;&t;&t;tubp = (*tubminors)[minor]; &bslash;&n;&t;tubp; &bslash;&n;})
macro_line|#endif /* CONFIG_3270_CONSOLE or not */
r_extern
r_void
id|tub_inc_use_count
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tub_dec_use_count
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tub3270_movedata
c_func
(paren
id|bcb_t
op_star
comma
id|bcb_t
op_star
)paren
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
r_extern
r_int
id|tubmakemin
c_func
(paren
r_int
comma
id|dev_info_t
op_star
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
id|tubmakemin
c_func
(paren
r_int
comma
id|s390_dev_info_t
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|tub3270_con_copy
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_rcl_init
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_rcl_set
c_func
(paren
id|tub_t
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_rcl_fini
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_rcl_get
c_func
(paren
id|tub_t
op_star
comma
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_rcl_put
c_func
(paren
id|tub_t
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_rcl_sync
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_rcl_purge
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_rcl_resize
c_func
(paren
id|tub_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_size
c_func
(paren
id|tub_t
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_aid_init
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_aid_fini
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_aid_reinit
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_aid_get
c_func
(paren
id|tub_t
op_star
comma
r_int
comma
r_int
op_star
comma
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_aid_set
c_func
(paren
id|tub_t
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_build
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_scl_settimer
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_scl_resettimer
c_func
(paren
id|tub_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_scl_set
c_func
(paren
id|tub_t
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tty3270_scl_init
c_func
(paren
id|tub_t
op_star
id|tubp
)paren
suffix:semicolon
r_extern
r_void
id|tty3270_scl_fini
c_func
(paren
id|tub_t
op_star
id|tubp
)paren
suffix:semicolon
eof
