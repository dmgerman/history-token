multiline_comment|/*&n; * PC Watchdog Driver&n; * by Ken Hollis (khollis@bitgate.com)&n; *&n; * Permission granted from Simon Machell (73244.1270@compuserve.com)&n; * Written for the Linux Kernel, and GPLed by Ken Hollis&n; *&n; * 960107&t;Added request_region routines, modulized the whole thing.&n; * 960108&t;Fixed end-of-file pointer (Thanks to Dan Hollis), added&n; *&t;&t;WD_TIMEOUT define.&n; * 960216&t;Added eof marker on the file, and changed verbose messages.&n; * 960716&t;Made functional and cosmetic changes to the source for&n; *&t;&t;inclusion in Linux 2.0.x kernels, thanks to Alan Cox.&n; * 960717&t;Removed read/seek routines, replaced with ioctl.  Also, added&n; *&t;&t;check_region command due to Alan&squot;s suggestion.&n; * 960821&t;Made changes to compile in newer 2.0.x kernels.  Added&n; *&t;&t;&quot;cold reboot sense&quot; entry.&n; * 960825&t;Made a few changes to code, deleted some defines and made&n; *&t;&t;typedefs to replace them.  Made heartbeat reset only available&n; *&t;&t;via ioctl, and removed the write routine.&n; * 960828&t;Added new items for PC Watchdog Rev.C card.&n; * 960829&t;Changed around all of the IOCTLs, added new features,&n; *&t;&t;added watchdog disable/re-enable routines.  Added firmware&n; *&t;&t;version reporting.  Added read routine for temperature.&n; *&t;&t;Removed some extra defines, added an autodetect Revision&n; *&t;&t;routine.&n; * 961006       Revised some documentation, fixed some cosmetic bugs.  Made&n; *              drivers to panic the system if it&squot;s overheating at bootup.&n; * 961118&t;Changed some verbiage on some of the output, tidied up&n; *&t;&t;code bits, and added compatibility to 2.1.x.&n; * 970912       Enabled board on open and disable on close.&n; * 971107&t;Took account of recent VFS changes (broke read).&n; * 971210       Disable board on initialisation in case board already ticking.&n; * 971222       Changed open/close for temperature handling&n; *              Michael Meskes &lt;meskes@debian.org&gt;.&n; * 980112       Used minor numbers from include/linux/miscdevice.h&n; * 990403       Clear reset status after reading control status register in &n; *              pcwd_showprevstate(). [Marc Boucher &lt;marc@mbsi.ca&gt;]&n; * 990605&t;Made changes to code to support Firmware 1.22a, added&n; *&t;&t;fairly useless proc entry.&n; * 990610&t;removed said useless proc code for the merge &lt;alan&gt;&n; * 000403&t;Removed last traces of proc code. &lt;davej&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * These are the auto-probe addresses available.&n; *&n; * Revision A only uses ports 0x270 and 0x370.  Revision C introduced 0x350.&n; * Revision A has an address range of 2 addresses, while Revision C has 3.&n; */
DECL|variable|pcwd_ioports
r_static
r_int
id|pcwd_ioports
(braket
)braket
op_assign
(brace
l_int|0x270
comma
l_int|0x350
comma
l_int|0x370
comma
l_int|0x000
)brace
suffix:semicolon
DECL|macro|WD_VER
mdefine_line|#define WD_VER                  &quot;1.10 (06/05/99)&quot;
multiline_comment|/*&n; * It should be noted that PCWD_REVISION_B was removed because A and B&n; * are essentially the same types of card, with the exception that B&n; * has temperature reporting.  Since I didn&squot;t receive a Rev.B card,&n; * the Rev.B card is not supported.  (It&squot;s a good thing too, as they&n; * are no longer in production.)&n; */
DECL|macro|PCWD_REVISION_A
mdefine_line|#define&t;PCWD_REVISION_A&t;&t;1
DECL|macro|PCWD_REVISION_C
mdefine_line|#define&t;PCWD_REVISION_C&t;&t;2
DECL|macro|WD_TIMEOUT
mdefine_line|#define&t;WD_TIMEOUT&t;&t;3&t;/* 1 1/2 seconds for a timeout */
multiline_comment|/*&n; * These are the defines for the PC Watchdog card, revision A.&n; */
DECL|macro|WD_WDRST
mdefine_line|#define WD_WDRST                0x01&t;/* Previously reset state */
DECL|macro|WD_T110
mdefine_line|#define WD_T110                 0x02&t;/* Temperature overheat sense */
DECL|macro|WD_HRTBT
mdefine_line|#define WD_HRTBT                0x04&t;/* Heartbeat sense */
DECL|macro|WD_RLY2
mdefine_line|#define WD_RLY2                 0x08&t;/* External relay triggered */
DECL|macro|WD_SRLY2
mdefine_line|#define WD_SRLY2                0x80&t;/* Software external relay triggered */
DECL|variable|current_readport
DECL|variable|revision
DECL|variable|temp_panic
r_static
r_int
id|current_readport
comma
id|revision
comma
id|temp_panic
suffix:semicolon
DECL|variable|is_open
DECL|variable|initial_status
DECL|variable|supports_temp
DECL|variable|mode_debug
r_static
r_int
id|is_open
comma
id|initial_status
comma
id|supports_temp
comma
id|mode_debug
suffix:semicolon
DECL|variable|io_lock
r_static
id|spinlock_t
id|io_lock
suffix:semicolon
multiline_comment|/*&n; * PCWD_CHECKCARD&n; *&n; * This routine checks the &quot;current_readport&quot; to see if the card lies there.&n; * If it does, it returns accordingly.&n; */
DECL|function|pcwd_checkcard
r_static
r_int
id|__init
id|pcwd_checkcard
c_func
(paren
r_void
)paren
(brace
r_int
id|card_dat
comma
id|prev_card_dat
comma
id|found
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
comma
id|done
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* As suggested by Alan Cox - this is a safety measure. */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|current_readport
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcwd: Port 0x%x unavailable.&bslash;n&quot;
comma
id|current_readport
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|card_dat
op_assign
l_int|0x00
suffix:semicolon
id|prev_card_dat
op_assign
l_int|0x00
suffix:semicolon
id|prev_card_dat
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev_card_dat
op_eq
l_int|0xFF
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OL
id|WD_TIMEOUT
)paren
(brace
multiline_comment|/* Read the raw card data from the port, and strip off the&n;&t;   first 4 bits */
id|card_dat
op_assign
id|inb_p
c_func
(paren
id|current_readport
)paren
suffix:semicolon
id|card_dat
op_and_assign
l_int|0x000F
suffix:semicolon
multiline_comment|/* Sleep 1/2 second (or 500000 microseconds :) */
id|mdelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
id|done
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If there&squot;s a heart beat in both instances, then this means we&n;&t;   found our card.  This also means that either the card was&n;&t;   previously reset, or the computer was power-cycled. */
r_if
c_cond
(paren
(paren
id|card_dat
op_amp
id|WD_HRTBT
)paren
op_logical_and
(paren
id|prev_card_dat
op_amp
id|WD_HRTBT
)paren
op_logical_and
(paren
op_logical_neg
id|done
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|done
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* If the card data is exactly the same as the previous card data,&n;&t;   it&squot;s safe to assume that we should check again.  The manual says&n;&t;   that the heart beat will change every second (or the bit will&n;&t;   toggle), and this can be used to see if the card is there.  If&n;&t;   the card was powered up with a cold boot, then the card will&n;&t;   not start blinking until 2.5 minutes after a reboot, so this&n;&t;   bit will stay at 1. */
r_if
c_cond
(paren
(paren
id|card_dat
op_eq
id|prev_card_dat
)paren
op_logical_and
(paren
op_logical_neg
id|done
)paren
)paren
(brace
id|count
op_increment
suffix:semicolon
id|done
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* If the card data is toggling any bits, this means that the heart&n;&t;   beat was detected, or something else about the card is set. */
r_if
c_cond
(paren
(paren
id|card_dat
op_ne
id|prev_card_dat
)paren
op_logical_and
(paren
op_logical_neg
id|done
)paren
)paren
(brace
id|done
op_assign
l_int|1
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Otherwise something else strange happened. */
r_if
c_cond
(paren
op_logical_neg
id|done
)paren
id|count
op_increment
suffix:semicolon
)brace
r_return
(paren
id|found
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|pcwd_showprevstate
r_void
id|pcwd_showprevstate
c_func
(paren
r_void
)paren
(brace
r_int
id|card_status
op_assign
l_int|0x0000
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
id|initial_status
op_assign
id|card_status
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
r_else
(brace
id|initial_status
op_assign
id|card_status
op_assign
id|inb
c_func
(paren
id|current_readport
op_plus
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|current_readport
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* clear reset status */
)brace
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
(brace
r_if
c_cond
(paren
id|card_status
op_amp
id|WD_WDRST
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: Previous reboot was caused by the card.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card_status
op_amp
id|WD_T110
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcwd: Card senses a CPU Overheat.  Panicking!&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;pcwd: CPU Overheat.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|card_status
op_amp
id|WD_WDRST
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|card_status
op_amp
id|WD_T110
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: Cold boot sense.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|card_status
op_amp
l_int|0x01
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: Previous reboot was caused by the card.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card_status
op_amp
l_int|0x04
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcwd: Card senses a CPU Overheat.  Panicking!&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;pcwd: CPU Overheat.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|card_status
op_amp
l_int|0x01
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|card_status
op_amp
l_int|0x04
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: Cold boot sense.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcwd_send_heartbeat
r_static
r_void
id|pcwd_send_heartbeat
c_func
(paren
r_void
)paren
(brace
r_int
id|wdrst_stat
suffix:semicolon
id|wdrst_stat
op_assign
id|inb_p
c_func
(paren
id|current_readport
)paren
suffix:semicolon
id|wdrst_stat
op_and_assign
l_int|0x0F
suffix:semicolon
id|wdrst_stat
op_or_assign
id|WD_WDRST
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
id|outb_p
c_func
(paren
id|wdrst_stat
comma
id|current_readport
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|outb_p
c_func
(paren
id|wdrst_stat
comma
id|current_readport
)paren
suffix:semicolon
)brace
DECL|function|pcwd_ioctl
r_static
r_int
id|pcwd_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
(brace
r_int
id|i
comma
id|cdat
comma
id|rv
suffix:semicolon
r_static
r_struct
id|watchdog_info
id|ident
op_assign
(brace
id|WDIOF_OVERHEAT
op_or
id|WDIOF_CARDRESET
comma
l_int|1
comma
l_string|&quot;PCWD&quot;
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_case
id|WDIOC_GETSUPPORT
suffix:colon
id|i
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|ident
comma
r_sizeof
(paren
id|ident
)paren
)paren
suffix:semicolon
r_return
id|i
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
id|cdat
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
r_else
id|cdat
op_assign
id|inb
c_func
(paren
id|current_readport
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|rv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
(brace
r_if
c_cond
(paren
id|cdat
op_amp
id|WD_WDRST
)paren
id|rv
op_or_assign
id|WDIOF_CARDRESET
suffix:semicolon
r_if
c_cond
(paren
id|cdat
op_amp
id|WD_T110
)paren
(brace
id|rv
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
r_if
c_cond
(paren
id|temp_panic
)paren
id|panic
c_func
(paren
l_string|&quot;pcwd: Temperature overheat trip!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|cdat
op_amp
l_int|0x01
)paren
id|rv
op_or_assign
id|WDIOF_CARDRESET
suffix:semicolon
r_if
c_cond
(paren
id|cdat
op_amp
l_int|0x04
)paren
(brace
id|rv
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
r_if
c_cond
(paren
id|temp_panic
)paren
id|panic
c_func
(paren
l_string|&quot;pcwd: Temperature overheat trip!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|rv
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
id|rv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
(brace
r_if
c_cond
(paren
id|initial_status
op_amp
id|WD_WDRST
)paren
id|rv
op_or_assign
id|WDIOF_CARDRESET
suffix:semicolon
r_if
c_cond
(paren
id|initial_status
op_amp
id|WD_T110
)paren
id|rv
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|initial_status
op_amp
l_int|0x01
)paren
id|rv
op_or_assign
id|WDIOF_CARDRESET
suffix:semicolon
r_if
c_cond
(paren
id|initial_status
op_amp
l_int|0x04
)paren
id|rv
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|rv
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETTEMP
suffix:colon
id|rv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|supports_temp
)paren
op_logical_and
(paren
id|mode_debug
op_eq
l_int|0
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|rv
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|rv
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|rv
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_SETOPTIONS
suffix:colon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_C
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rv
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rv
op_amp
id|WDIOS_DISABLECARD
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|cdat
op_assign
id|inb_p
c_func
(paren
id|current_readport
op_plus
l_int|2
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cdat
op_amp
l_int|0x10
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcwd: Could not disable card.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rv
op_amp
id|WDIOS_ENABLECARD
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|cdat
op_assign
id|inb_p
c_func
(paren
id|current_readport
op_plus
l_int|2
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdat
op_amp
l_int|0x10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcwd: Could not enable card.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rv
op_amp
id|WDIOS_TEMPPANIC
)paren
(brace
id|temp_panic
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|pcwd_send_heartbeat
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcwd_write
r_static
id|ssize_t
id|pcwd_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
multiline_comment|/*  Can&squot;t seek (pwrite) on this device  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
id|pcwd_send_heartbeat
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcwd_open
r_static
r_int
id|pcwd_open
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|ino-&gt;i_rdev
)paren
)paren
(brace
r_case
id|WATCHDOG_MINOR
suffix:colon
r_if
c_cond
(paren
id|is_open
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/*  Enable the port  */
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_C
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
)brace
id|is_open
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TEMP_MINOR
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcwd_read
r_static
id|ssize_t
id|pcwd_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
r_int
id|c
suffix:semicolon
r_int
r_char
id|cp
suffix:semicolon
multiline_comment|/*  Can&squot;t seek (pread) on this device  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|TEMP_MINOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Convert metric to Fahrenheit, since this was&n;&t;&t;&t; * the decided &squot;standard&squot; for this return value.&n;&t;&t;&t; */
id|c
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
id|cp
op_assign
(paren
id|c
op_star
l_int|9
op_div
l_int|5
)paren
op_plus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|cp
comma
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|pcwd_close
r_static
r_int
id|pcwd_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|ino-&gt;i_rdev
)paren
op_eq
id|WATCHDOG_MINOR
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|is_open
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT
multiline_comment|/*  Disable the board  */
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_C
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_support
r_static
r_inline
r_void
id|get_support
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|current_readport
)paren
op_ne
l_int|0xF0
)paren
id|supports_temp
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|get_revision
r_static
r_inline
r_int
id|get_revision
c_func
(paren
r_void
)paren
(brace
r_int
id|r
op_assign
id|PCWD_REVISION_C
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|current_readport
op_plus
l_int|2
)paren
op_eq
l_int|0xFF
)paren
op_logical_or
(paren
id|inb
c_func
(paren
id|current_readport
op_plus
l_int|3
)paren
op_eq
l_int|0xFF
)paren
)paren
id|r
op_assign
id|PCWD_REVISION_A
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|send_command
r_static
r_int
id|__init
id|send_command
c_func
(paren
r_int
id|cmd
)paren
(brace
r_int
id|i
suffix:semicolon
id|outb_p
c_func
(paren
id|cmd
comma
id|current_readport
op_plus
l_int|2
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
id|i
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|get_firmware
r_static
r_inline
r_char
op_star
id|get_firmware
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|found
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
comma
id|one
comma
id|ten
comma
id|hund
comma
id|minor
suffix:semicolon
r_char
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|kmalloc
c_func
(paren
l_int|6
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|count
OL
l_int|3
)paren
op_logical_and
(paren
op_logical_neg
id|found
)paren
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x80
comma
id|current_readport
op_plus
l_int|2
)paren
suffix:semicolon
id|i
op_assign
id|inb
c_func
(paren
id|current_readport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0x00
)paren
id|found
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
l_int|0xF3
)paren
id|outb_p
c_func
(paren
l_int|0x00
comma
id|current_readport
op_plus
l_int|2
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|400L
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
)paren
(brace
id|mode_debug
op_assign
l_int|1
suffix:semicolon
id|one
op_assign
id|send_command
c_func
(paren
l_int|0x81
)paren
suffix:semicolon
id|ten
op_assign
id|send_command
c_func
(paren
l_int|0x82
)paren
suffix:semicolon
id|hund
op_assign
id|send_command
c_func
(paren
l_int|0x83
)paren
suffix:semicolon
id|minor
op_assign
id|send_command
c_func
(paren
l_int|0x84
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
)paren
id|sprintf
c_func
(paren
id|ret
comma
l_string|&quot;%c.%c%c%c&quot;
comma
id|one
comma
id|ten
comma
id|hund
comma
id|minor
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|ret
comma
l_string|&quot;ERROR&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|debug_off
r_static
r_void
id|debug_off
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x00
comma
id|current_readport
op_plus
l_int|2
)paren
suffix:semicolon
id|mode_debug
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|pcwd_fops
r_static
r_struct
id|file_operations
id|pcwd_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|pcwd_read
comma
id|write
suffix:colon
id|pcwd_write
comma
id|ioctl
suffix:colon
id|pcwd_ioctl
comma
id|open
suffix:colon
id|pcwd_open
comma
id|release
suffix:colon
id|pcwd_close
comma
)brace
suffix:semicolon
DECL|variable|pcwd_miscdev
r_static
r_struct
id|miscdevice
id|pcwd_miscdev
op_assign
(brace
id|WATCHDOG_MINOR
comma
l_string|&quot;watchdog&quot;
comma
op_amp
id|pcwd_fops
)brace
suffix:semicolon
DECL|variable|temp_miscdev
r_static
r_struct
id|miscdevice
id|temp_miscdev
op_assign
(brace
id|TEMP_MINOR
comma
l_string|&quot;temperature&quot;
comma
op_amp
id|pcwd_fops
)brace
suffix:semicolon
DECL|function|pcwatchdog_init
r_static
r_int
id|__init
id|pcwatchdog_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|found
op_assign
l_int|0
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|io_lock
)paren
suffix:semicolon
id|revision
op_assign
id|PCWD_REVISION_A
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pcwd: v%s Ken Hollis (kenji@bitgate.com)&bslash;n&quot;
comma
id|WD_VER
)paren
suffix:semicolon
multiline_comment|/* Initial variables */
id|is_open
op_assign
l_int|0
suffix:semicolon
id|supports_temp
op_assign
l_int|0
suffix:semicolon
id|mode_debug
op_assign
l_int|0
suffix:semicolon
id|temp_panic
op_assign
l_int|0
suffix:semicolon
id|initial_status
op_assign
l_int|0x0000
suffix:semicolon
macro_line|#ifndef&t;PCWD_BLIND
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|pcwd_ioports
(braket
id|i
)braket
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|current_readport
op_assign
id|pcwd_ioports
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pcwd_checkcard
c_func
(paren
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcwd: No card detected, or port not available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef&t;PCWD_BLIND
id|current_readport
op_assign
id|PCWD_BLIND
suffix:semicolon
macro_line|#endif
id|get_support
c_func
(paren
)paren
suffix:semicolon
id|revision
op_assign
id|get_revision
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: PC Watchdog (REV.A) detected at port 0x%03x&bslash;n&quot;
comma
id|current_readport
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_C
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: PC Watchdog (REV.C) detected at port 0x%03x (Firmware version: %s)&bslash;n&quot;
comma
id|current_readport
comma
id|get_firmware
c_func
(paren
)paren
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Should NEVER happen, unless get_revision() fails. */
id|printk
c_func
(paren
l_string|&quot;pcwd: Unable to get revision.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|supports_temp
)paren
id|printk
c_func
(paren
l_string|&quot;pcwd: Temperature Option Detected.&bslash;n&quot;
)paren
suffix:semicolon
id|debug_off
c_func
(paren
)paren
suffix:semicolon
id|pcwd_showprevstate
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*  Disable the board  */
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_C
)paren
(brace
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
id|request_region
c_func
(paren
id|current_readport
comma
l_int|2
comma
l_string|&quot;PCWD Rev.A (Berkshire)&quot;
)paren
suffix:semicolon
r_else
id|request_region
c_func
(paren
id|current_readport
comma
l_int|4
comma
l_string|&quot;PCWD Rev.C (Berkshire)&quot;
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|pcwd_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|supports_temp
)paren
id|misc_register
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcwatchdog_exit
r_static
r_void
id|__exit
id|pcwatchdog_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*  Disable the board  */
r_if
c_cond
(paren
id|revision
op_eq
id|PCWD_REVISION_C
)paren
(brace
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA5
comma
id|current_readport
op_plus
l_int|3
)paren
suffix:semicolon
)brace
id|misc_deregister
c_func
(paren
op_amp
id|pcwd_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|supports_temp
)paren
id|misc_deregister
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|current_readport
comma
(paren
id|revision
op_eq
id|PCWD_REVISION_A
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
)paren
suffix:semicolon
)brace
DECL|variable|pcwatchdog_init
id|module_init
c_func
(paren
id|pcwatchdog_init
)paren
suffix:semicolon
DECL|variable|pcwatchdog_exit
id|module_exit
c_func
(paren
id|pcwatchdog_exit
)paren
suffix:semicolon
eof
