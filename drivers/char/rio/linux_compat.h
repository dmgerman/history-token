multiline_comment|/*&n; * (C) 2000 R.E.Wolff@BitWizard.nl&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|disable
mdefine_line|#define disable(oldspl) save_flags (oldspl)
DECL|macro|restore
mdefine_line|#define restore(oldspl) restore_flags (oldspl)
DECL|macro|sysbrk
mdefine_line|#define sysbrk(x) kmalloc ((x),in_interrupt()? GFP_ATOMIC : GFP_KERNEL)
DECL|macro|sysfree
mdefine_line|#define sysfree(p,size) kfree ((p))
DECL|macro|WBYTE
mdefine_line|#define WBYTE(p,v) writeb(v, &amp;p)
DECL|macro|RBYTE
mdefine_line|#define RBYTE(p)   readb (&amp;p)
DECL|macro|WWORD
mdefine_line|#define WWORD(p,v) writew(v, &amp;p)
DECL|macro|RWORD
mdefine_line|#define RWORD(p)   readw(&amp;p)
DECL|macro|WINDW
mdefine_line|#define WINDW(p,v) writew(v, p)
DECL|macro|RINDW
mdefine_line|#define RINDW(p)   readw(p)
DECL|macro|DEBUG_ALL
mdefine_line|#define DEBUG_ALL
DECL|macro|cprintf
mdefine_line|#define cprintf printk
macro_line|#ifdef __KERNEL__
DECL|macro|INKERNEL
mdefine_line|#define INKERNEL
macro_line|#endif
DECL|struct|ttystatics
r_struct
id|ttystatics
(brace
DECL|member|tm
r_struct
id|termios
id|tm
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bzero
mdefine_line|#define bzero(d, n)         memset((d), 0, (n))
DECL|macro|bcopy
mdefine_line|#define bcopy(src, dest, n) memcpy ((dest), (src), (n))
DECL|macro|SEM_SIGIGNORE
mdefine_line|#define SEM_SIGIGNORE 0x1234
macro_line|#ifdef DEBUG_SEM
DECL|macro|swait
mdefine_line|#define swait(a,b)      printk (&quot;waiting:    &quot; __FILE__ &quot; line %d&bslash;n&quot;, __LINE__)
DECL|macro|ssignal
mdefine_line|#define ssignal(sem)    printk (&quot;signalling: &quot; __FILE__ &quot; line %d&bslash;n&quot;, __LINE__)
DECL|macro|sreset
mdefine_line|#define sreset(sem)     printk (&quot;sreset:     &quot; __FILE__ &quot;&bslash;n&quot;)
DECL|macro|sem_init
mdefine_line|#define sem_init(sem,v) printk (&quot;sreset:     &quot; __FILE__ &quot;&bslash;n&quot;)
macro_line|#endif
DECL|macro|getpid
mdefine_line|#define getpid()    (current-&gt;pid)
DECL|macro|QSIZE
mdefine_line|#define QSIZE SERIAL_XMIT_SIZE
DECL|macro|pseterr
mdefine_line|#define pseterr(errno) return (- errno)
DECL|macro|V_CBAUD
mdefine_line|#define V_CBAUD CBAUD
multiline_comment|/* For one reason or another rioboot.c uses delay instead of RIODelay. */
DECL|macro|delay
mdefine_line|#define delay(x,y) RIODelay(NULL, y)
r_extern
r_int
id|rio_debug
suffix:semicolon
DECL|macro|RIO_DEBUG_INIT
mdefine_line|#define RIO_DEBUG_INIT         0x000001
DECL|macro|RIO_DEBUG_BOOT
mdefine_line|#define RIO_DEBUG_BOOT         0x000002
DECL|macro|RIO_DEBUG_CMD
mdefine_line|#define RIO_DEBUG_CMD          0x000004
DECL|macro|RIO_DEBUG_CTRL
mdefine_line|#define RIO_DEBUG_CTRL         0x000008
DECL|macro|RIO_DEBUG_INTR
mdefine_line|#define RIO_DEBUG_INTR         0x000010
DECL|macro|RIO_DEBUG_PARAM
mdefine_line|#define RIO_DEBUG_PARAM        0x000020
DECL|macro|RIO_DEBUG_ROUTE
mdefine_line|#define RIO_DEBUG_ROUTE        0x000040
DECL|macro|RIO_DEBUG_TABLE
mdefine_line|#define RIO_DEBUG_TABLE        0x000080
DECL|macro|RIO_DEBUG_TTY
mdefine_line|#define RIO_DEBUG_TTY          0x000100
DECL|macro|RIO_DEBUG_FLOW
mdefine_line|#define RIO_DEBUG_FLOW         0x000200
DECL|macro|RIO_DEBUG_MODEMSIGNALS
mdefine_line|#define RIO_DEBUG_MODEMSIGNALS 0x000400
DECL|macro|RIO_DEBUG_PROBE
mdefine_line|#define RIO_DEBUG_PROBE        0x000800
DECL|macro|RIO_DEBUG_CLEANUP
mdefine_line|#define RIO_DEBUG_CLEANUP      0x001000
DECL|macro|RIO_DEBUG_IFLOW
mdefine_line|#define RIO_DEBUG_IFLOW        0x002000
DECL|macro|RIO_DEBUG_PFE
mdefine_line|#define RIO_DEBUG_PFE          0x004000
DECL|macro|RIO_DEBUG_REC
mdefine_line|#define RIO_DEBUG_REC          0x008000
DECL|macro|RIO_DEBUG_SPINLOCK
mdefine_line|#define RIO_DEBUG_SPINLOCK     0x010000
DECL|macro|RIO_DEBUG_DELAY
mdefine_line|#define RIO_DEBUG_DELAY        0x020000
DECL|macro|RIO_DEBUG_MOD_COUNT
mdefine_line|#define RIO_DEBUG_MOD_COUNT    0x040000
multiline_comment|/* Copied over from riowinif.h . This is ugly. The winif file declares&n;also much other stuff which is incompatible with the headers from&n;the older driver. The older driver includes &quot;brates.h&quot; which shadows&n;the definitions from Linux, and is incompatible... */
multiline_comment|/* RxBaud and TxBaud definitions... */
DECL|macro|RIO_B0
mdefine_line|#define&t;RIO_B0&t;&t;&t;0x00&t;&t;&t;/* RTS / DTR signals dropped */
DECL|macro|RIO_B50
mdefine_line|#define&t;RIO_B50&t;&t;&t;0x01&t;&t;&t;/* 50 baud */
DECL|macro|RIO_B75
mdefine_line|#define&t;RIO_B75&t;&t;&t;0x02&t;&t;&t;/* 75 baud */
DECL|macro|RIO_B110
mdefine_line|#define&t;RIO_B110&t;&t;0x03&t;&t;&t;/* 110 baud */
DECL|macro|RIO_B134
mdefine_line|#define&t;RIO_B134&t;&t;0x04&t;&t;&t;/* 134.5 baud */
DECL|macro|RIO_B150
mdefine_line|#define&t;RIO_B150&t;&t;0x05&t;&t;&t;/* 150 baud */
DECL|macro|RIO_B200
mdefine_line|#define&t;RIO_B200&t;&t;0x06&t;&t;&t;/* 200 baud */
DECL|macro|RIO_B300
mdefine_line|#define&t;RIO_B300&t;&t;0x07&t;&t;&t;/* 300 baud */
DECL|macro|RIO_B600
mdefine_line|#define&t;RIO_B600&t;&t;0x08&t;&t;&t;/* 600 baud */
DECL|macro|RIO_B1200
mdefine_line|#define&t;RIO_B1200&t;&t;0x09&t;&t;&t;/* 1200 baud */
DECL|macro|RIO_B1800
mdefine_line|#define&t;RIO_B1800&t;&t;0x0A&t;&t;&t;/* 1800 baud */
DECL|macro|RIO_B2400
mdefine_line|#define&t;RIO_B2400&t;&t;0x0B&t;&t;&t;/* 2400 baud */
DECL|macro|RIO_B4800
mdefine_line|#define&t;RIO_B4800&t;&t;0x0C&t;&t;&t;/* 4800 baud */
DECL|macro|RIO_B9600
mdefine_line|#define&t;RIO_B9600&t;&t;0x0D&t;&t;&t;/* 9600 baud */
DECL|macro|RIO_B19200
mdefine_line|#define&t;RIO_B19200&t;&t;0x0E&t;&t;&t;/* 19200 baud */
DECL|macro|RIO_B38400
mdefine_line|#define&t;RIO_B38400&t;&t;0x0F&t;&t;&t;/* 38400 baud */
DECL|macro|RIO_B56000
mdefine_line|#define&t;RIO_B56000&t;&t;0x10&t;&t;&t;/* 56000 baud */
DECL|macro|RIO_B57600
mdefine_line|#define&t;RIO_B57600&t;&t;0x11&t;&t;&t;/* 57600 baud */
DECL|macro|RIO_B64000
mdefine_line|#define&t;RIO_B64000&t;&t;0x12&t;&t;&t;/* 64000 baud */
DECL|macro|RIO_B115200
mdefine_line|#define&t;RIO_B115200&t;&t;0x13&t;&t;&t;/* 115200 baud */
DECL|macro|RIO_B2000
mdefine_line|#define&t;RIO_B2000&t;&t;0x14&t;&t;&t;/* 2000 baud */
eof
