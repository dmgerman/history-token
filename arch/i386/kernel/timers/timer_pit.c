multiline_comment|/* This function must be called with interrupts disabled &n; * It was inspired by Steve McCanne&squot;s microtime-i386 for BSD.  -- jrs&n; * &n; * However, the pc-audio speaker driver changes the divisor so that&n; * it gets interrupted rather more often - it loads 64 into the&n; * counter rather than 11932! This has an adverse impact on&n; * do_gettimeoffset() -- it stops working! What is also not&n; * good is that the interval that our timer function gets called&n; * is no longer 10.0002 ms, but 9.9767 ms. To get around this&n; * would require using a different timing source. Maybe someone&n; * could use the RTC - I know that this can interrupt at frequencies&n; * ranging from 8192Hz to 2Hz. If I had the energy, I&squot;d somehow fix&n; * it so that at startup, the timer code in sched.c would select&n; * using either the RTC or the 8253 timer. The decision would be&n; * based on whether there was any other device around that needed&n; * to trample on the 8253. I&squot;d set up the RTC to interrupt at 1024 Hz,&n; * and then do some jiggery to have a version of do_timer that &n; * advanced the clock by 1/1024 s. Every time that reached over 1/100&n; * of a second, then do all the old code. If the time was kept correct&n; * then do_gettimeoffset could just return 0 - there is no low order&n; * divider that can be accessed.&n; *&n; * Ideally, you would be able to use the RTC for the speaker driver,&n; * but it appears that the speaker driver really needs interrupt more&n; * often than every 120 us or so.&n; *&n; * Anyway, this needs more thought....&t;&t;pjsg (1993-08-28)&n; * &n; * If you are really that interested, you should be reading&n; * comp.protocols.time.ntp!&n; */
DECL|function|do_slow_gettimeoffset
r_static
r_int
r_int
id|do_slow_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
id|count
suffix:semicolon
r_static
r_int
id|count_p
op_assign
id|LATCH
suffix:semicolon
multiline_comment|/* for the first call after boot */
r_static
r_int
r_int
id|jiffies_p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * cache volatile jiffies temporarily; we have IRQs turned off. &n;&t; */
r_int
r_int
id|jiffies_t
suffix:semicolon
multiline_comment|/* gets recalled with irq locally disabled */
id|spin_lock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
multiline_comment|/*&n;&t; * We do this guaranteed double memory access instead of a _p &n;&t; * postfix in the previous port access. Wheee, hackady hack&n;&t; */
id|jiffies_t
op_assign
id|jiffies
suffix:semicolon
id|count
op_or_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* VIA686a test code... reset the latch if count &gt; max + 1 */
r_if
c_cond
(paren
id|count
OG
id|LATCH
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
id|count
op_assign
id|LATCH
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * avoiding timer inconsistencies (they are rare, but they happen)...&n;&t; * there are two kinds of problems that must be avoided here:&n;&t; *  1. the timer counter underflows&n;&t; *  2. hardware problem with the timer, not giving us continuous time,&n;&t; *     the counter does small &quot;jumps&quot; upwards on some Pentium systems,&n;&t; *     (see c&squot;t 95/10 page 335 for Neptun bug.)&n;&t; */
r_if
c_cond
(paren
id|jiffies_t
op_eq
id|jiffies_p
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|count_p
)paren
(brace
multiline_comment|/* the nutcase */
id|count
op_assign
id|do_timer_overflow
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
)brace
r_else
id|jiffies_p
op_assign
id|jiffies_t
suffix:semicolon
id|count_p
op_assign
id|count
suffix:semicolon
id|count
op_assign
(paren
(paren
id|LATCH
op_minus
l_int|1
)paren
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|do_gettimeoffset
r_static
r_int
r_int
(paren
op_star
id|do_gettimeoffset
)paren
(paren
r_void
)paren
op_assign
id|do_slow_gettimeoffset
suffix:semicolon
eof
