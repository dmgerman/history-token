multiline_comment|/* &n;   * This header tries to allow you to write 2.3-compatible drivers, &n;   * but (using this header) still allows you to run them on 2.2 and &n;   * 2.0 kernels. &n;   *&n;   * Sometimes, a #define replaces a &quot;construct&quot; that older kernels&n;   * had. For example, &n;   *&n;   *       DECLARE_MUTEX(name);&n;   *&n;   * replaces the older &n;   *&n;   *       struct semaphore name = MUTEX;&n;   *&n;   * This file then declares the DECLARE_MUTEX macro to compile into the &n;   * older version. &n;   * &n;   * In some cases, a macro or function changes the number of arguments.&n;   * In that case, there is nothing we can do except define an access &n;   * macro that provides the same functionality on both versions of Linux. &n;   * &n;   * This is the case for example with the &quot;get_user&quot; macro 2.0 kernels use:&n;   *&n;   *          a = get_user (b);&n;   *  &n;   * while newer kernels use &n;   * &n;   *          get_user (a,b);&n;   *&n;   * This is unfortunate. We therefore define &quot;Get_user (a,b)&quot; which looks&n;   * almost the same as the 2.2+ construct, and translates into the &n;   * appropriate sequence for earlier constructs. &n;   * &n;   * Supported by this file are the 2.0 kernels, 2.2 kernels, and the &n;   * most recent 2.3 kernel. 2.3 support will be dropped as soon when 2.4&n;   * comes out. 2.0 support may someday be dropped. But then again, maybe &n;   * not. &n;   *&n;   * I&squot;ll try to maintain this, provided that Linus agrees with the setup. &n;   * Feel free to mail updates or suggestions. &n;   *&n;   * -- R.E.Wolff@BitWizard.nl&n;   *&n;   */
macro_line|#ifndef COMPATMAC_H
DECL|macro|COMPATMAC_H
mdefine_line|#define COMPATMAC_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; 0x020100    /* Less than 2.1.0 */
DECL|macro|TWO_ZERO
mdefine_line|#define TWO_ZERO
macro_line|#else
macro_line|#if LINUX_VERSION_CODE &lt; 0x020200   /* less than 2.2.x */
macro_line|#warning &quot;Please use a 2.2.x kernel. &quot;
macro_line|#else
macro_line|#if LINUX_VERSION_CODE &lt; 0x020300   /* less than 2.3.x */
DECL|macro|TWO_TWO
mdefine_line|#define TWO_TWO
macro_line|#else
DECL|macro|TWO_THREE
mdefine_line|#define TWO_THREE
macro_line|#endif
macro_line|#endif
macro_line|#endif
macro_line|#ifdef TWO_ZERO
multiline_comment|/* Here is the section that makes the 2.2 compatible driver source &n;   work for 2.0 too! We mostly try to adopt the &quot;new thingies&quot; from 2.2, &n;   and provide for compatibility stuff here if possible. */
multiline_comment|/* Some 200 days (on intel) */
DECL|macro|MAX_SCHEDULE_TIMEOUT
mdefine_line|#define MAX_SCHEDULE_TIMEOUT     ((long)(~0UL&gt;&gt;1))
macro_line|#include &lt;linux/bios32.h&gt;
DECL|macro|Get_user
mdefine_line|#define Get_user(a,b)                a = get_user(b)
DECL|macro|Put_user
mdefine_line|#define Put_user(a,b)                0,put_user(a,b)
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user(a,b,c)          memcpy_tofs(a,b,c)
DECL|function|copy_from_user
r_static
r_inline
r_int
id|copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|c
)paren
(brace
id|memcpy_fromfs
c_func
(paren
id|to
comma
id|from
comma
id|c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|pci_present
mdefine_line|#define pci_present                  pcibios_present
DECL|macro|pci_read_config_word
mdefine_line|#define pci_read_config_word         pcibios_read_config_word
DECL|macro|pci_read_config_dword
mdefine_line|#define pci_read_config_dword        pcibios_read_config_dword
DECL|function|get_irq
r_static
r_inline
r_int
r_char
id|get_irq
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|fn
)paren
(brace
r_int
r_char
id|t
suffix:semicolon
id|pcibios_read_config_byte
(paren
id|bus
comma
id|fn
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|t
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|function|ioremap
r_static
r_inline
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|length
)paren
(brace
r_if
c_cond
(paren
id|base
OL
l_int|0x100000
)paren
r_return
(paren
r_void
op_star
)paren
id|base
suffix:semicolon
r_return
id|vremap
(paren
id|base
comma
id|length
)paren
suffix:semicolon
)brace
DECL|macro|my_iounmap
mdefine_line|#define my_iounmap(x, b)             (((long)x&lt;0x100000)?0:vfree ((void*)x))
DECL|macro|capable
mdefine_line|#define capable(x)                   suser()
DECL|macro|tty_flip_buffer_push
mdefine_line|#define tty_flip_buffer_push(tty)    queue_task(&amp;tty-&gt;flip.tqueue, &amp;tq_timer)
DECL|macro|signal_pending
mdefine_line|#define signal_pending(current)      (current-&gt;signal &amp; ~current-&gt;blocked)
DECL|macro|schedule_timeout
mdefine_line|#define schedule_timeout(to)         do {current-&gt;timeout = jiffies + (to);schedule ();} while (0)
DECL|macro|time_after
mdefine_line|#define time_after(t1,t2)            (((long)t1-t2) &gt; 0)
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit(nr, addr)   set_bit(nr, addr)
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit(nr, addr) clear_bit(nr, addr)
multiline_comment|/* Not yet implemented on 2.0 */
DECL|macro|ASYNC_SPD_SHI
mdefine_line|#define ASYNC_SPD_SHI  -1
DECL|macro|ASYNC_SPD_WARP
mdefine_line|#define ASYNC_SPD_WARP -1
multiline_comment|/* Ugly hack: the driver_name doesn&squot;t exist in 2.0.x . So we define it&n;   to the &quot;name&quot; field that does exist. As long as the assignments are&n;   done in the right order, there is nothing to worry about. */
DECL|macro|driver_name
mdefine_line|#define driver_name           name 
multiline_comment|/* Should be in a header somewhere. They are in tty.h on 2.2 */
DECL|macro|TTY_HW_COOK_OUT
mdefine_line|#define TTY_HW_COOK_OUT       14 /* Flag to tell ntty what we can handle */
DECL|macro|TTY_HW_COOK_IN
mdefine_line|#define TTY_HW_COOK_IN        15 /* in hardware - output and input       */
multiline_comment|/* The return type of a &quot;close&quot; routine. */
DECL|macro|INT
mdefine_line|#define INT                   void
DECL|macro|NO_ERROR
mdefine_line|#define NO_ERROR              /* Nothing */
macro_line|#else
multiline_comment|/* The 2.2.x compatibility section. */
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|Get_user
mdefine_line|#define Get_user(a,b)         get_user(a,b)
DECL|macro|Put_user
mdefine_line|#define Put_user(a,b)         put_user(a,b)
DECL|macro|get_irq
mdefine_line|#define get_irq(pdev)         pdev-&gt;irq
DECL|macro|INT
mdefine_line|#define INT                   int
DECL|macro|NO_ERROR
mdefine_line|#define NO_ERROR              0
DECL|macro|my_iounmap
mdefine_line|#define my_iounmap(x,b)       (iounmap((char *)(b)))
macro_line|#endif
macro_line|#ifndef TWO_THREE
multiline_comment|/* These are new in 2.3. The source now uses 2.3 syntax, and here is &n;   the compatibility define... */
DECL|macro|wait_queue_head_t
mdefine_line|#define wait_queue_head_t     struct wait_queue *
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name)   struct semaphore name = MUTEX
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(wait, current) &bslash;&n;                              struct wait_queue wait = { current, NULL }
macro_line|#endif
macro_line|#endif
eof
