multiline_comment|/* auto_irq.c: Auto-configure IRQ lines for linux. */
multiline_comment|/*&n;    Written 1994 by Donald Becker.&n;&n;    The author may be reached as becker@scyld.com&n;&n;    This code is a general-purpose IRQ line detector for devices with&n;    jumpered IRQ lines.  If you can make the device raise an IRQ (and&n;    that IRQ line isn&squot;t already being used), these routines will tell&n;    you what IRQ line it&squot;s using -- perfect for those oh-so-cool boot-time&n;    device probes!&n;&n;    To use this, first call autoirq_setup(timeout). TIMEOUT is how many&n;    &squot;jiffies&squot; (1/100 sec.) to detect other devices that have active IRQ lines,&n;    and can usually be zero at boot.  &squot;autoirq_setup()&squot; returns the bit&n;    vector of nominally-available IRQ lines (lines may be physically in-use,&n;    but not yet registered to a device).&n;    Next, set up your device to trigger an interrupt.&n;    Finally call autoirq_report(TIMEOUT) to find out which IRQ line was&n;    most recently active.  The TIMEOUT should usually be zero, but may&n;    be set to the number of jiffies to wait for a slow device to raise an IRQ.&n;&n;    The idea of using the setup timeout to filter out bogus IRQs came from&n;    the serial driver.&n;*/
macro_line|#ifdef version
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;auto_irq.c:v1.11 Donald Becker (becker@scyld.com)&quot;
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
DECL|variable|irqs
r_static
r_int
r_int
id|irqs
suffix:semicolon
DECL|function|autoirq_setup
r_void
id|autoirq_setup
c_func
(paren
r_int
id|waittime
)paren
(brace
id|irqs
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|BUSY_LOOP_UNTIL
mdefine_line|#define BUSY_LOOP_UNTIL(j) while ((long)(jiffies-(j)) &lt; 0) ;
DECL|function|autoirq_report
r_int
id|autoirq_report
c_func
(paren
r_int
id|waittime
)paren
(brace
r_int
r_int
id|delay
op_assign
id|jiffies
op_plus
id|waittime
suffix:semicolon
id|BUSY_LOOP_UNTIL
c_func
(paren
id|delay
)paren
r_return
id|probe_irq_off
c_func
(paren
id|irqs
)paren
suffix:semicolon
)brace
DECL|variable|autoirq_setup
id|EXPORT_SYMBOL
c_func
(paren
id|autoirq_setup
)paren
suffix:semicolon
DECL|variable|autoirq_report
id|EXPORT_SYMBOL
c_func
(paren
id|autoirq_report
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DKERNEL -Wall -O6 -fomit-frame-pointer -I/usr/src/linux/net/tcp -c auto_irq.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 4&n; *  tab-width: 4&n; * End:&n; */
eof
