multiline_comment|/*&n; * arch/m68k/atari/ataints.c -- Atari Linux interrupt handling code&n; *&n; * 5/2/94 Roman Hodek:&n; *  Added support for TT interrupts; setup for TT SCU (may someone has&n; *  twiddled there and we won&squot;t get the right interrupts :-()&n; *&n; *  Major change: The device-independent code in m68k/ints.c didn&squot;t know&n; *  about non-autovec ints yet. It hardcoded the number of possible ints to&n; *  7 (IRQ1...IRQ7). But the Atari has lots of non-autovec ints! I made the&n; *  number of possible ints a constant defined in interrupt.h, which is&n; *  47 for the Atari. So we can call request_irq() for all Atari interrupts&n; *  just the normal way. Additionally, all vectors &gt;= 48 are initialized to&n; *  call trap() instead of inthandler(). This must be changed here, too.&n; *&n; * 1995-07-16 Lars Brinkhoff &lt;f93labr@dd.chalmers.se&gt;:&n; *  Corrected a bug in atari_add_isr() which rejected all SCC&n; *  interrupt sources if there were no TT MFP!&n; *&n; * 12/13/95: New interface functions atari_level_triggered_int() and&n; *  atari_register_vme_int() as support for level triggered VME interrupts.&n; *&n; * 02/12/96: (Roman)&n; *  Total rewrite of Atari interrupt handling, for new scheme see comments&n; *  below.&n; *&n; * 1996-09-03 lars brinkhoff &lt;f93labr@dd.chalmers.se&gt;:&n; *  Added new function atari_unregister_vme_int(), and&n; *  modified atari_register_vme_int() as well as IS_VALID_INTNO()&n; *  to work with it.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/entry.h&gt;
multiline_comment|/*&n; * Atari interrupt handling scheme:&n; * --------------------------------&n; * &n; * All interrupt source have an internal number (defined in&n; * &lt;asm/atariints.h&gt;): Autovector interrupts are 1..7, then follow ST-MFP,&n; * TT-MFP, SCC, and finally VME interrupts. Vector numbers for the latter can&n; * be allocated by atari_register_vme_int().&n; *&n; * Each interrupt can be of three types:&n; * &n; *  - SLOW: The handler runs with all interrupts enabled, except the one it&n; *    was called by (to avoid reentering). This should be the usual method.&n; *    But it is currently possible only for MFP ints, since only the MFP&n; *    offers an easy way to mask interrupts.&n; *&n; *  - FAST: The handler runs with all interrupts disabled. This should be used&n; *    only for really fast handlers, that just do actions immediately&n; *    necessary, and let the rest do a bottom half or task queue.&n; *&n; *  - PRIORITIZED: The handler can be interrupted by higher-level ints&n; *    (greater IPL, no MFP priorities!). This is the method of choice for ints&n; *    which should be slow, but are not from a MFP.&n; *&n; * The feature of more than one handler for one int source is still there, but&n; * only applicable if all handers are of the same type. To not slow down&n; * processing of ints with only one handler by the chaining feature, the list&n; * calling function atari_call_irq_list() is only plugged in at the time the&n; * second handler is registered.&n; *&n; * Implementation notes: For fast-as-possible int handling, there are separate&n; * entry points for each type (slow/fast/prio). The assembler handler calls&n; * the irq directly in the usual case, no C wrapper is involved. In case of&n; * multiple handlers, atari_call_irq_list() is registered as handler and calls&n; * in turn the real irq&squot;s. To ease access from assembler level to the irq&n; * function pointer and accompanying data, these two are stored in a separate&n; * array, irq_handler[]. The rest of data (type, name) are put into a second&n; * array, irq_param, that is accessed from C only. For each slow interrupt (32&n; * in all) there are separate handler functions, which makes it possible to&n; * hard-code the MFP register address and value, are necessary to mask the&n; * int. If there&squot;d be only one generic function, lots of calculations would be&n; * needed to determine MFP register and int mask from the vector number :-(&n; *&n; * Furthermore, slow ints may not lower the IPL below its previous value&n; * (before the int happened). This is needed so that an int of class PRIO, on&n; * that this int may be stacked, cannot be reentered. This feature is&n; * implemented as follows: If the stack frame format is 1 (throwaway), the int&n; * is not stacked, and the IPL is anded with 0xfbff, resulting in a new level&n; * 2, which still blocks the HSYNC, but no interrupts of interest. If the&n; * frame format is 0, the int is nested, and the old IPL value can be found in&n; * the sr copy in the frame.&n; */
DECL|macro|NUM_INT_SOURCES
mdefine_line|#define&t;NUM_INT_SOURCES&t;(8 + NUM_ATARI_SOURCES)
DECL|typedef|asm_irq_handler
r_typedef
r_void
(paren
op_star
id|asm_irq_handler
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|struct|irqhandler
r_struct
id|irqhandler
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irqparam
r_struct
id|irqparam
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|devname
r_const
r_char
op_star
id|devname
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Array with irq&squot;s and their parameter data. This array is accessed from low&n; * level assembler code, so an element size of 8 allows usage of index scaling&n; * addressing mode.&n; */
DECL|variable|irq_handler
r_static
r_struct
id|irqhandler
id|irq_handler
(braket
id|NUM_INT_SOURCES
)braket
suffix:semicolon
multiline_comment|/*&n; * This array hold the rest of parameters of int handlers: type&n; * (slow,fast,prio) and the name of the handler. These values are only&n; * accessed from C&n; */
DECL|variable|irq_param
r_static
r_struct
id|irqparam
id|irq_param
(braket
id|NUM_INT_SOURCES
)braket
suffix:semicolon
multiline_comment|/*&n; * Bitmap for free interrupt vector numbers&n; * (new vectors starting from 0x70 can be allocated by&n; * atari_register_vme_int())&n; */
DECL|variable|free_vme_vec_bitmap
r_static
r_int
id|free_vme_vec_bitmap
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* check for valid int number (complex, sigh...) */
DECL|macro|IS_VALID_INTNO
mdefine_line|#define&t;IS_VALID_INTNO(n)&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((n) &gt; 0 &amp;&amp;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; /* autovec and ST-MFP ok anyway */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; (((n) &lt; TTMFP_SOURCE_BASE) ||&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  /* TT-MFP ok if present */&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  ((n) &gt;= TTMFP_SOURCE_BASE &amp;&amp; (n) &lt; SCC_SOURCE_BASE &amp;&amp;&t;&t;&t;&bslash;&n;&t;   ATARIHW_PRESENT(TT_MFP)) ||&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  /* SCC ok if present and number even */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  ((n) &gt;= SCC_SOURCE_BASE &amp;&amp; (n) &lt; VME_SOURCE_BASE &amp;&amp;&t;&t;&t;&bslash;&n;&t;   !((n) &amp; 1) &amp;&amp; ATARIHW_PRESENT(SCC)) ||&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  /* greater numbers ok if they are registered VME vectors */&t;&t;&bslash;&n;&t;  ((n) &gt;= VME_SOURCE_BASE &amp;&amp; (n) &lt; VME_SOURCE_BASE + VME_MAX_SOURCES &amp;&amp; &bslash;&n;&t;&t;  free_vme_vec_bitmap &amp; (1 &lt;&lt; ((n) - VME_SOURCE_BASE)))))
multiline_comment|/*&n; * Here start the assembler entry points for interrupts&n; */
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) atari_slow_irq_##nr##_handler(void)
DECL|macro|BUILD_SLOW_IRQ
mdefine_line|#define&t;BUILD_SLOW_IRQ(n)&t;&t;&t;&t;&t;&t;   &bslash;&n;asmlinkage void IRQ_NAME(n);&t;&t;&t;&t;&t;&t;   &bslash;&n;/* Dummy function to allow asm with operands.  */&t;&t;&t;   &bslash;&n;void atari_slow_irq_##n##_dummy (void) {&t;&t;&t;&t;   &bslash;&n;__asm__ (__ALIGN_STR &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;atari_slow_irq_&quot; #n &quot;_handler:&bslash;t&quot;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;addql&t;#1,%5&bslash;n&quot;&t;&t;/* local_irq_count++ */&t;&t;   &bslash;&n;&t;SAVE_ALL_INT &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;GET_CURRENT(%%d0) &quot;&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;andb&t;#~(1&lt;&lt;(%c3&amp;7)),%a4:w&bslash;n&quot;&t;/* mask this interrupt */&t;   &bslash;&n;&t;/* get old IPL from stack frame */&t;&t;&t;&t;   &bslash;&n;&quot;&t;bfextu&t;%%sp@(%c2){#5,#3},%%d0&bslash;n&quot;&t;&t;&t;&t;   &bslash;&n;&quot;&t;movew&t;%%sr,%%d1&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;bfins&t;%%d0,%%d1{#21,#3}&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;movew&t;%%d1,%%sr&bslash;n&quot;&t;&t;/* set IPL = previous value */&t;   &bslash;&n;&quot;&t;addql&t;#1,%a0&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;lea&t;%a1,%%a0&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;pea &t;%%sp@&bslash;n&quot;&t;&t;/* push addr of frame */&t;   &bslash;&n;&quot;&t;movel&t;%%a0@(4),%%sp@-&bslash;n&quot;&t;/* push handler data */&t;&t;   &bslash;&n;&quot;&t;pea &t;(%c3+8)&bslash;n&quot;&t;&t;/* push int number */&t;&t;   &bslash;&n;&quot;&t;movel&t;%%a0@,%%a0&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;jbsr&t;%%a0@&bslash;n&quot;&t;&t;/* call the handler */&t;&t;   &bslash;&n;&quot;&t;addql&t;#8,%%sp&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;addql&t;#4,%%sp&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;orw&t;#0x0600,%%sr&bslash;n&quot;&t;&t;&t;&t;&t;&t;   &bslash;&n;&quot;&t;andw&t;#0xfeff,%%sr&bslash;n&quot;&t;&t;/* set IPL = 6 again */&t;&t;   &bslash;&n;&quot;&t;orb &t;#(1&lt;&lt;(%c3&amp;7)),%a4:w&bslash;n&quot;&t;/* now unmask the int again */&t;   &bslash;&n;&quot;&t;jbra&t;ret_from_interrupt&bslash;n&quot;&t;&t;&t;&t;&t;   &bslash;&n;&t; : : &quot;i&quot; (&amp;kstat_cpu(0).irqs[n+8]), &quot;i&quot; (&amp;irq_handler[n+8]),&t;   &bslash;&n;&t;     &quot;n&quot; (PT_OFF_SR), &quot;n&quot; (n),&t;&t;&t;&t;&t;   &bslash;&n;&t;     &quot;i&quot; (n &amp; 8 ? (n &amp; 16 ? &amp;tt_mfp.int_mk_a : &amp;mfp.int_mk_a)&t;   &bslash;&n;&t;&t;        : (n &amp; 16 ? &amp;tt_mfp.int_mk_b : &amp;mfp.int_mk_b)),&t;   &bslash;&n;&t;     &quot;m&quot; (local_irq_count(0))&t;&t;&t;&t;&t;   &bslash;&n;);&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;for (;;);&t;&t;&t;/* fake noreturn */&t;&t;   &bslash;&n;}
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|12
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|13
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|15
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|17
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|18
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|19
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|21
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|22
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|23
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|24
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|25
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|26
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|27
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|28
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|29
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|30
)paren
suffix:semicolon
id|BUILD_SLOW_IRQ
c_func
(paren
l_int|31
)paren
suffix:semicolon
DECL|variable|slow_handlers
id|asm_irq_handler
id|slow_handlers
(braket
l_int|32
)braket
op_assign
(brace
id|atari_slow_irq_0_handler
comma
id|atari_slow_irq_1_handler
comma
id|atari_slow_irq_2_handler
comma
id|atari_slow_irq_3_handler
comma
id|atari_slow_irq_4_handler
comma
id|atari_slow_irq_5_handler
comma
id|atari_slow_irq_6_handler
comma
id|atari_slow_irq_7_handler
comma
id|atari_slow_irq_8_handler
comma
id|atari_slow_irq_9_handler
comma
id|atari_slow_irq_10_handler
comma
id|atari_slow_irq_11_handler
comma
id|atari_slow_irq_12_handler
comma
id|atari_slow_irq_13_handler
comma
id|atari_slow_irq_14_handler
comma
id|atari_slow_irq_15_handler
comma
id|atari_slow_irq_16_handler
comma
id|atari_slow_irq_17_handler
comma
id|atari_slow_irq_18_handler
comma
id|atari_slow_irq_19_handler
comma
id|atari_slow_irq_20_handler
comma
id|atari_slow_irq_21_handler
comma
id|atari_slow_irq_22_handler
comma
id|atari_slow_irq_23_handler
comma
id|atari_slow_irq_24_handler
comma
id|atari_slow_irq_25_handler
comma
id|atari_slow_irq_26_handler
comma
id|atari_slow_irq_27_handler
comma
id|atari_slow_irq_28_handler
comma
id|atari_slow_irq_29_handler
comma
id|atari_slow_irq_30_handler
comma
id|atari_slow_irq_31_handler
)brace
suffix:semicolon
id|asmlinkage
r_void
id|atari_fast_irq_handler
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|atari_prio_irq_handler
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Dummy function to allow asm with operands.  */
DECL|function|atari_fast_prio_irq_dummy
r_void
id|atari_fast_prio_irq_dummy
(paren
r_void
)paren
(brace
id|__asm__
(paren
id|__ALIGN_STR
l_string|&quot;&bslash;n&quot;
"&quot;"
id|atari_fast_irq_handler
suffix:colon
id|orw
macro_line|#0x700,%%sr&t;&t;/* disable all interrupts */
id|atari_prio_irq_handler
suffix:colon
"&bslash;"
id|t
id|addql
macro_line|#1,%2&bslash;n&quot;&t;&t;/* local_irq_count++ */
id|SAVE_ALL_INT
l_string|&quot;&bslash;n&quot;
id|GET_CURRENT
c_func
(paren
op_mod
op_mod
id|d0
)paren
"&quot;"
multiline_comment|/* get vector number from stack frame and convert to source */
id|bfextu
op_mod
op_mod
id|sp
"@"
(paren
op_mod
id|c1
)paren
(brace
macro_line|#4,#10},%%d0
id|subw
macro_line|#(0x40-8),%%d0
id|jpl
l_float|1f
id|addw
macro_line|#(0x40-8-0x18),%%d0
l_int|1
suffix:colon
id|lea
op_mod
id|a0
comma
op_mod
op_mod
id|a0
id|addql
macro_line|#1,%%a0@(%%d0:l:4)
id|lea
id|irq_handler
comma
op_mod
op_mod
id|a0
id|lea
op_mod
op_mod
id|a0
"@"
(paren
op_mod
op_mod
id|d0
suffix:colon
id|l
suffix:colon
l_int|8
)paren
comma
op_mod
op_mod
id|a0
id|pea
op_mod
op_mod
id|sp
"@"
multiline_comment|/* push frame address */
id|movel
op_mod
op_mod
id|a0
"@"
(paren
l_int|4
)paren
comma
op_mod
op_mod
id|sp
"@"
op_minus
multiline_comment|/* push handler data */
id|movel
op_mod
op_mod
id|d0
comma
op_mod
op_mod
id|sp
"@"
op_minus
multiline_comment|/* push int number */
id|movel
op_mod
op_mod
id|a0
"@"
comma
op_mod
op_mod
id|a0
id|jsr
op_mod
op_mod
id|a0
"@"
multiline_comment|/* and call the handler */
id|addql
macro_line|#8,%%sp
id|addql
macro_line|#4,%%sp
id|jbra
id|ret_from_interrupt
"&quot;"
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
op_amp
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
)paren
comma
l_string|&quot;n&quot;
(paren
id|PT_OFF_FORMATVEC
)paren
comma
l_string|&quot;m&quot;
(paren
id|local_irq_count
c_func
(paren
l_int|0
)paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
multiline_comment|/* GK:&n; * HBL IRQ handler for Falcon. Nobody needs it :-)&n; * ++andreas: raise ipl to disable further HBLANK interrupts.&n; */
id|asmlinkage
r_void
id|falcon_hblhandler
c_func
(paren
r_void
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.text&bslash;n&quot;
id|__ALIGN_STR
l_string|&quot;&bslash;n&quot;
"&quot;"
id|falcon_hblhandler
suffix:colon
id|orw
macro_line|#0x200,%sp@&t;/* set saved ipl to 2 */
id|rte
"&quot;"
)paren
suffix:semicolon
multiline_comment|/* Defined in entry.S; only increments &squot;num_spurious&squot; */
id|asmlinkage
r_void
id|bad_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|atari_microwire_cmd
c_func
(paren
r_int
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|atari_SCC_reset_done
suffix:semicolon
multiline_comment|/*&n; * void atari_init_IRQ (void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function should be called during kernel startup to initialize&n; * the atari IRQ handling routines.&n; */
DECL|function|atari_init_IRQ
r_void
id|__init
id|atari_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* initialize the vector table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_INT_SOURCES
suffix:semicolon
op_increment
id|i
)paren
(brace
id|vectors
(braket
id|IRQ_SOURCE_TO_VECTOR
c_func
(paren
id|i
)paren
)braket
op_assign
id|bad_interrupt
suffix:semicolon
)brace
multiline_comment|/* Initialize the MFP(s) */
macro_line|#ifdef ATARI_USE_SOFTWARE_EOI
id|mfp.vec_adr
op_assign
l_int|0x48
suffix:semicolon
multiline_comment|/* Software EOI-Mode */
macro_line|#else
id|mfp.vec_adr
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* Automatic EOI-Mode */
macro_line|#endif
id|mfp.int_en_a
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* turn off MFP-Ints */
id|mfp.int_en_b
op_assign
l_int|0x00
suffix:semicolon
id|mfp.int_mk_a
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* no Masking */
id|mfp.int_mk_b
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ATARIHW_PRESENT
c_func
(paren
id|TT_MFP
)paren
)paren
(brace
macro_line|#ifdef ATARI_USE_SOFTWARE_EOI
id|tt_mfp.vec_adr
op_assign
l_int|0x58
suffix:semicolon
multiline_comment|/* Software EOI-Mode */
macro_line|#else
id|tt_mfp.vec_adr
op_assign
l_int|0x50
suffix:semicolon
multiline_comment|/* Automatic EOI-Mode */
macro_line|#endif
id|tt_mfp.int_en_a
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* turn off MFP-Ints */
id|tt_mfp.int_en_b
op_assign
l_int|0x00
suffix:semicolon
id|tt_mfp.int_mk_a
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* no Masking */
id|tt_mfp.int_mk_b
op_assign
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ATARIHW_PRESENT
c_func
(paren
id|SCC
)paren
op_logical_and
op_logical_neg
id|atari_SCC_reset_done
)paren
(brace
id|scc.cha_a_ctrl
op_assign
l_int|9
suffix:semicolon
id|MFPDELAY
c_func
(paren
)paren
suffix:semicolon
id|scc.cha_a_ctrl
op_assign
(paren
r_char
)paren
l_int|0xc0
suffix:semicolon
multiline_comment|/* hardware reset */
)brace
r_if
c_cond
(paren
id|ATARIHW_PRESENT
c_func
(paren
id|SCU
)paren
)paren
(brace
multiline_comment|/* init the SCU if present */
id|tt_scu.sys_mask
op_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* enable VBL (for the cursor) and&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * disable HSYNC interrupts (who&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * needs them?)  MFP and SCC are&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * enabled in VME mask&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
id|tt_scu.vme_mask
op_assign
l_int|0x60
suffix:semicolon
multiline_comment|/* enable MFP and SCC ints */
)brace
r_else
(brace
multiline_comment|/* If no SCU and no Hades, the HSYNC interrupt needs to be&n;&t;&t; * disabled this way. (Else _inthandler in kernel/sys_call.S&n;&t;&t; * gets overruns)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_HADES
)paren
id|vectors
(braket
id|VEC_INT2
)braket
op_assign
id|falcon_hblhandler
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ATARIHW_PRESENT
c_func
(paren
id|PCM_8BIT
)paren
op_logical_and
id|ATARIHW_PRESENT
c_func
(paren
id|MICROWIRE
)paren
)paren
(brace
multiline_comment|/* Initialize the LM1992 Sound Controller to enable&n;&t;&t;   the PSG sound.  This is misplaced here, it should&n;&t;&t;   be in an atasound_init(), that doesn&squot;t exist yet. */
id|atari_microwire_cmd
c_func
(paren
id|MW_LM1992_PSG_HIGH
)paren
suffix:semicolon
)brace
id|stdma_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize the PSG: all sounds off, both ports output */
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|sound_ym.wd_data
op_assign
l_int|0xff
suffix:semicolon
)brace
DECL|function|atari_call_irq_list
r_static
r_void
id|atari_call_irq_list
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|irq_node_t
op_star
id|node
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
(paren
id|irq_node_t
op_star
)paren
id|dev_id
suffix:semicolon
id|node
suffix:semicolon
id|node
op_assign
id|node-&gt;next
)paren
id|node
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|node-&gt;dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atari_request_irq : add an interrupt service routine for a particular&n; *                     machine specific interrupt source.&n; *                     If the addition was successful, it returns 0.&n; */
DECL|function|atari_request_irq
r_int
id|atari_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
id|vector
suffix:semicolon
r_int
r_int
id|oflags
op_assign
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * The following is a hack to make some PCI card drivers work,&n;&t; * which set the SA_SHIRQ flag.&n;&t; */
id|flags
op_and_assign
op_complement
id|SA_SHIRQ
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_eq
id|SA_INTERRUPT
)paren
(brace
id|printk
(paren
l_string|&quot;%s: SA_INTERRUPT changed to IRQ_TYPE_SLOW for %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|devname
)paren
suffix:semicolon
id|flags
op_assign
id|IRQ_TYPE_SLOW
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
template_param
id|IRQ_TYPE_PRIO
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Bad irq type 0x%lx &lt;0x%lx&gt; requested from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|flags
comma
id|oflags
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_INTNO
c_func
(paren
id|irq
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Unknown irq %d requested from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|vector
op_assign
id|IRQ_SOURCE_TO_VECTOR
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check type/source combination: slow ints are (currently)&n;&t; * only possible for MFP-interrupts.&n;&t; */
r_if
c_cond
(paren
id|flags
op_eq
id|IRQ_TYPE_SLOW
op_logical_and
(paren
id|irq
OL
id|STMFP_SOURCE_BASE
op_logical_or
id|irq
op_ge
id|SCC_SOURCE_BASE
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Slow irq requested for non-MFP source %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vectors
(braket
id|vector
)braket
op_eq
id|bad_interrupt
)paren
(brace
multiline_comment|/* int has no handler yet */
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|irq_param
(braket
id|irq
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
id|irq_param
(braket
id|irq
)braket
dot
id|devname
op_assign
id|devname
suffix:semicolon
id|vectors
(braket
id|vector
)braket
op_assign
(paren
id|flags
op_eq
id|IRQ_TYPE_SLOW
)paren
ques
c_cond
id|slow_handlers
(braket
id|irq
op_minus
id|STMFP_SOURCE_BASE
)braket
suffix:colon
(paren
id|flags
op_eq
id|IRQ_TYPE_FAST
)paren
ques
c_cond
id|atari_fast_irq_handler
suffix:colon
id|atari_prio_irq_handler
suffix:semicolon
multiline_comment|/* If MFP int, also enable and umask it */
id|atari_turnon_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|atari_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|irq_param
(braket
id|irq
)braket
dot
id|flags
op_eq
id|flags
)paren
(brace
multiline_comment|/* old handler is of same type -&gt; handlers can be chained */
id|irq_node_t
op_star
id|node
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
op_ne
id|atari_call_irq_list
)paren
(brace
multiline_comment|/* Only one handler yet, make a node for this first one */
r_if
c_cond
(paren
op_logical_neg
(paren
id|node
op_assign
id|new_irq_node
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|node-&gt;handler
op_assign
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
suffix:semicolon
id|node-&gt;dev_id
op_assign
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
suffix:semicolon
id|node-&gt;devname
op_assign
id|irq_param
(braket
id|irq
)braket
dot
id|devname
suffix:semicolon
id|node-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
op_assign
id|atari_call_irq_list
suffix:semicolon
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|node
suffix:semicolon
id|irq_param
(braket
id|irq
)braket
dot
id|devname
op_assign
l_string|&quot;chained&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|node
op_assign
id|new_irq_node
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|node-&gt;handler
op_assign
id|handler
suffix:semicolon
id|node-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|node-&gt;devname
op_assign
id|devname
suffix:semicolon
multiline_comment|/* new handlers are put in front of the queue */
id|node-&gt;next
op_assign
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
suffix:semicolon
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|node
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
l_string|&quot;%s: Irq %d allocated by other type int (call from %s)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
DECL|function|atari_free_irq
r_void
id|atari_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|vector
suffix:semicolon
id|irq_node_t
op_star
op_star
id|list
comma
op_star
id|node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_VALID_INTNO
c_func
(paren
id|irq
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Unknown irq %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|vector
op_assign
id|IRQ_SOURCE_TO_VECTOR
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vectors
(braket
id|vector
)braket
op_eq
id|bad_interrupt
)paren
r_goto
id|not_found
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
op_ne
id|atari_call_irq_list
)paren
(brace
multiline_comment|/* It&squot;s the only handler for the interrupt */
r_if
c_cond
(paren
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
op_ne
id|dev_id
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
)brace
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_param
(braket
id|irq
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
id|vectors
(braket
id|vector
)braket
op_assign
id|bad_interrupt
suffix:semicolon
multiline_comment|/* If MFP int, also disable it */
id|atari_disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|atari_turnoff_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The interrupt is chained, find the irq on the list */
r_for
c_loop
(paren
id|list
op_assign
(paren
id|irq_node_t
op_star
op_star
)paren
op_amp
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
suffix:semicolon
op_star
id|list
suffix:semicolon
id|list
op_assign
op_amp
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|dev_id
op_eq
id|dev_id
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|list
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
)brace
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|handler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Mark it as free for reallocation */
op_star
id|list
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
multiline_comment|/* If there&squot;s now only one handler, unchain the interrupt, i.e. plug in&n;&t; * the handler directly again and omit atari_call_irq_list */
id|node
op_assign
(paren
id|irq_node_t
op_star
)paren
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|node
op_logical_and
op_logical_neg
id|node-&gt;next
)paren
(brace
id|irq_handler
(braket
id|irq
)braket
dot
id|handler
op_assign
id|node-&gt;handler
suffix:semicolon
id|irq_handler
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|node-&gt;dev_id
suffix:semicolon
id|irq_param
(braket
id|irq
)braket
dot
id|devname
op_assign
id|node-&gt;devname
suffix:semicolon
id|node-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Mark it as free for reallocation */
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
id|not_found
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: tried to remove invalid irq&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * atari_register_vme_int() returns the number of a free interrupt vector for&n; * hardware with a programmable int vector (probably a VME board).&n; */
DECL|function|atari_register_vme_int
r_int
r_int
id|atari_register_vme_int
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|free_vme_vec_bitmap
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|16
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|free_vme_vec_bitmap
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
r_return
(paren
id|VME_SOURCE_BASE
op_plus
id|i
)paren
suffix:semicolon
)brace
DECL|function|atari_unregister_vme_int
r_void
id|atari_unregister_vme_int
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_ge
id|VME_SOURCE_BASE
op_logical_and
id|irq
OL
id|VME_SOURCE_BASE
op_plus
id|VME_MAX_SOURCES
)paren
(brace
id|irq
op_sub_assign
id|VME_SOURCE_BASE
suffix:semicolon
id|free_vme_vec_bitmap
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_atari_interrupts
r_int
id|show_atari_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_INT_SOURCES
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|vectors
(braket
id|IRQ_SOURCE_TO_VECTOR
c_func
(paren
id|i
)paren
)braket
op_eq
id|bad_interrupt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|STMFP_SOURCE_BASE
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;auto %2d: %10u &quot;
comma
id|i
comma
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;vec $%02x: %10u &quot;
comma
id|IRQ_SOURCE_TO_VECTOR
c_func
(paren
id|i
)paren
comma
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_handler
(braket
id|i
)braket
dot
id|handler
op_ne
id|atari_call_irq_list
)paren
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|irq_param
(braket
id|i
)braket
dot
id|devname
)paren
suffix:semicolon
)brace
r_else
(brace
id|irq_node_t
op_star
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
(paren
id|irq_node_t
op_star
)paren
id|irq_handler
(braket
id|i
)braket
dot
id|dev_id
suffix:semicolon
id|n
suffix:semicolon
id|n
op_assign
id|n-&gt;next
)paren
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|n-&gt;devname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;next
)paren
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;                    &quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|num_spurious
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;spurio.: %10u&bslash;n&quot;
comma
id|num_spurious
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
