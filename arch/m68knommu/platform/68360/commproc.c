multiline_comment|/*&n; * General Purpose functions for the global management of the&n; * Communication Processor Module.&n; *&n; * Copyright (c) 2000 Michael Leslie &lt;mleslie@lineo.com&gt;&n; * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)&n; *&n; * In addition to the individual control of the communication&n; * channels, there are a few functions that globally affect the&n; * communication processor.&n; *&n; * Buffer descriptors must be allocated from the dual ported memory&n; * space.  The allocator for that is here.  When the communication&n; * process is reset, we reclaim the memory available.  There is&n; * currently no deallocator for this memory.&n; * The amount of space available is platform dependent.  On the&n; * MBX, the EPPC software loads additional microcode into the&n; * communication processor, and uses some of the DP ram for this&n; * purpose.  Current, the first 512 bytes and the last 256 bytes of&n; * memory are used.  Right now I am conservative and only use the&n; * memory that can never be used for microcode.  If there are&n; * applications that require more DP ram, we can expand the boundaries&n; * but then we have to be careful of any downloaded microcode.&n; *&n; */
multiline_comment|/*&n; * Michael Leslie &lt;mleslie@lineo.com&gt;&n; * adapted Dan Malek&squot;s ppc8xx drivers to M68360&n; *&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/m68360.h&gt;
macro_line|#include &lt;asm/commproc.h&gt;
multiline_comment|/* #include &lt;asm/page.h&gt; */
multiline_comment|/* #include &lt;asm/pgtable.h&gt; */
r_extern
r_void
op_star
id|_quicc_base
suffix:semicolon
r_extern
r_int
r_int
id|system_clock
suffix:semicolon
DECL|variable|dp_alloc_base
r_static
id|uint
id|dp_alloc_base
suffix:semicolon
multiline_comment|/* Starting offset in DP ram */
DECL|variable|dp_alloc_top
r_static
id|uint
id|dp_alloc_top
suffix:semicolon
multiline_comment|/* Max offset + 1 */
macro_line|#if 0
r_static
r_void
op_star
id|host_buffer
suffix:semicolon
multiline_comment|/* One page of host buffer */
r_static
r_void
op_star
id|host_end
suffix:semicolon
multiline_comment|/* end + 1 */
macro_line|#endif
multiline_comment|/* struct  cpm360_t *cpmp; */
multiline_comment|/* Pointer to comm processor space */
DECL|variable|pquicc
id|QUICC
op_star
id|pquicc
suffix:semicolon
multiline_comment|/* QUICC  *quicc_dpram; */
multiline_comment|/* mleslie - temporary; use extern pquicc elsewhere instead */
multiline_comment|/* CPM interrupt vector functions. */
DECL|struct|cpm_action
r_struct
id|cpm_action
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
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
DECL|variable|cpm_vecs
r_static
r_struct
id|cpm_action
id|cpm_vecs
(braket
id|CPMVEC_NR
)braket
suffix:semicolon
r_static
r_void
id|cpm_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|cpm_error_interrupt
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* prototypes: */
r_void
id|cpm_install_handler
c_func
(paren
r_int
id|vec
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_void
id|m360_cpm_reset
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|m360_cpm_reset
r_void
id|m360_cpm_reset
c_func
(paren
)paren
(brace
multiline_comment|/* &t;pte_t&t;&t;   *pte; */
id|pquicc
op_assign
(paren
r_struct
id|quicc
op_star
)paren
(paren
id|_quicc_base
)paren
suffix:semicolon
multiline_comment|/* initialized in crt0_rXm.S */
multiline_comment|/* Perform a CPM reset. */
id|pquicc-&gt;cp_cr
op_assign
(paren
id|SOFTWARE_RESET
op_or
id|CMD_FLAG
)paren
suffix:semicolon
multiline_comment|/* Wait for CPM to become ready (should be 2 clocks). */
r_while
c_loop
(paren
id|pquicc-&gt;cp_cr
op_amp
id|CMD_FLAG
)paren
suffix:semicolon
multiline_comment|/* On the recommendation of the 68360 manual, p. 7-60&n;&t; * - Set sdma interupt service mask to 7&n;&t; * - Set sdma arbitration ID to 4&n;&t; */
id|pquicc-&gt;sdma_sdcr
op_assign
l_int|0x0740
suffix:semicolon
multiline_comment|/* Claim the DP memory for our use.&n;&t; */
id|dp_alloc_base
op_assign
id|CPM_DATAONLY_BASE
suffix:semicolon
id|dp_alloc_top
op_assign
id|dp_alloc_base
op_plus
id|CPM_DATAONLY_SIZE
suffix:semicolon
multiline_comment|/* Set the host page for allocation.&n;&t; */
multiline_comment|/* &t;host_buffer = host_page_addr; */
multiline_comment|/* &t;host_end = host_page_addr + PAGE_SIZE; */
multiline_comment|/* &t;pte = find_pte(&amp;init_mm, host_page_addr); */
multiline_comment|/* &t;pte_val(*pte) |= _PAGE_NO_CACHE; */
multiline_comment|/* &t;flush_tlb_page(current-&gt;mm-&gt;mmap, host_buffer); */
multiline_comment|/* Tell everyone where the comm processor resides.&n;&t;*/
multiline_comment|/* &t;cpmp = (cpm360_t *)commproc; */
)brace
multiline_comment|/* This is called during init_IRQ.  We used to do it above, but this&n; * was too early since init_IRQ was not yet called.&n; */
r_void
DECL|function|cpm_interrupt_init
id|cpm_interrupt_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Initialize the CPM interrupt controller.&n;&t; * NOTE THAT pquicc had better have been initialized!&n;&t; * reference: MC68360UM p. 7-377&n;&t; */
id|pquicc-&gt;intr_cicr
op_assign
(paren
id|CICR_SCD_SCC4
op_or
id|CICR_SCC_SCC3
op_or
id|CICR_SCB_SCC2
op_or
id|CICR_SCA_SCC1
)paren
op_or
(paren
id|CPM_INTERRUPT
op_lshift
l_int|13
)paren
op_or
id|CICR_HP_MASK
op_or
(paren
id|CPM_VECTOR_BASE
op_lshift
l_int|5
)paren
op_or
id|CICR_SPS
suffix:semicolon
multiline_comment|/* mask all CPM interrupts from reaching the cpu32 core: */
id|pquicc-&gt;intr_cimr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* mles - If I understand correctly, the 360 just pops over to the CPM&n;&t; * specific vector, obviating the necessity to vector through the IRQ&n;&t; * whose priority the CPM is set to. This needs a closer look, though.&n;&t; */
multiline_comment|/* Set our interrupt handler with the core CPU. */
multiline_comment|/* &t;if (request_irq(CPM_INTERRUPT, cpm_interrupt, 0, &quot;cpm&quot;, NULL) != 0) */
multiline_comment|/* &t;&t;panic(&quot;Could not allocate CPM IRQ!&quot;); */
multiline_comment|/* Install our own error handler.&n;&t; */
multiline_comment|/* I think we want to hold off on this one for the moment - mles */
multiline_comment|/* cpm_install_handler(CPMVEC_ERROR, cpm_error_interrupt, NULL); */
multiline_comment|/* master CPM interrupt enable */
multiline_comment|/* pquicc-&gt;intr_cicr |= CICR_IEN; */
multiline_comment|/* no such animal for 360 */
)brace
multiline_comment|/* CPM interrupt controller interrupt.&n;*/
r_static
r_void
DECL|function|cpm_interrupt
id|cpm_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* uint&t;vec; */
multiline_comment|/* mles: Note that this stuff is currently being performed by&n;&t; * M68360_do_irq(int vec, struct pt_regs *fp), in ../ints.c  */
multiline_comment|/* figure out the vector */
multiline_comment|/* call that vector&squot;s handler */
multiline_comment|/* clear the irq&squot;s bit in the service register */
macro_line|#if 0 /* old 860 stuff: */
multiline_comment|/* Get the vector by setting the ACK bit and then reading&n;&t; * the register.&n;&t; */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_civr
op_assign
l_int|1
suffix:semicolon
id|vec
op_assign
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_civr
suffix:semicolon
id|vec
op_rshift_assign
l_int|11
suffix:semicolon
r_if
c_cond
(paren
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
op_ne
l_int|0
)paren
(paren
op_star
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
)paren
(paren
id|cpm_vecs
(braket
id|vec
)braket
dot
id|dev_id
)paren
suffix:semicolon
r_else
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cimr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|vec
)paren
suffix:semicolon
multiline_comment|/* After servicing the interrupt, we have to remove the status&n;&t; * indicator.&n;&t; */
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cisr
op_or_assign
(paren
l_int|1
op_lshift
id|vec
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* The CPM can generate the error interrupt when there is a race condition&n; * between generating and masking interrupts.  All we have to do is ACK it&n; * and return.  This is a no-op function so we don&squot;t need any special&n; * tests in the interrupt handler.&n; */
r_static
r_void
DECL|function|cpm_error_interrupt
id|cpm_error_interrupt
c_func
(paren
r_void
op_star
id|dev
)paren
(brace
)brace
multiline_comment|/* Install a CPM interrupt handler.&n;*/
r_void
DECL|function|cpm_install_handler
id|cpm_install_handler
c_func
(paren
r_int
id|vec
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|dev_id
)paren
(brace
id|request_irq
c_func
(paren
id|vec
comma
id|handler
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;timer&quot;
comma
id|dev_id
)paren
suffix:semicolon
multiline_comment|/* &t;if (cpm_vecs[vec].handler != 0) */
multiline_comment|/* &t;&t;printk(&quot;CPM interrupt %x replacing %x&bslash;n&quot;, */
multiline_comment|/* &t;&t;&t;(uint)handler, (uint)cpm_vecs[vec].handler); */
multiline_comment|/* &t;cpm_vecs[vec].handler = handler; */
multiline_comment|/* &t;cpm_vecs[vec].dev_id = dev_id; */
multiline_comment|/*              ((immap_t *)IMAP_ADDR)-&gt;im_cpic.cpic_cimr |= (1 &lt;&lt; vec); */
multiline_comment|/* &t;pquicc-&gt;intr_cimr |= (1 &lt;&lt; vec); */
)brace
multiline_comment|/* Free a CPM interrupt handler.&n;*/
r_void
DECL|function|cpm_free_handler
id|cpm_free_handler
c_func
(paren
r_int
id|vec
)paren
(brace
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|cpm_vecs
(braket
id|vec
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ((immap_t *)IMAP_ADDR)-&gt;im_cpic.cpic_cimr &amp;= ~(1 &lt;&lt; vec); */
id|pquicc-&gt;intr_cimr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|vec
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate some memory from the dual ported ram.  We may want to&n; * enforce alignment restrictions, but right now everyone is a good&n; * citizen.&n; */
id|uint
DECL|function|m360_cpm_dpalloc
id|m360_cpm_dpalloc
c_func
(paren
id|uint
id|size
)paren
(brace
id|uint
id|retloc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp_alloc_base
op_plus
id|size
)paren
op_ge
id|dp_alloc_top
)paren
r_return
id|CPM_DP_NOSPACE
suffix:semicolon
id|retloc
op_assign
id|dp_alloc_base
suffix:semicolon
id|dp_alloc_base
op_add_assign
id|size
suffix:semicolon
r_return
id|retloc
suffix:semicolon
)brace
macro_line|#if 0 /* mleslie - for now these are simply kmalloc&squot;d */
multiline_comment|/* We also own one page of host buffer space for the allocation of&n; * UART &quot;fifos&quot; and the like.&n; */
id|uint
id|m360_cpm_hostalloc
c_func
(paren
id|uint
id|size
)paren
(brace
id|uint
id|retloc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|host_buffer
op_plus
id|size
)paren
op_ge
id|host_end
)paren
r_return
l_int|0
suffix:semicolon
id|retloc
op_assign
id|host_buffer
suffix:semicolon
id|host_buffer
op_add_assign
id|size
suffix:semicolon
r_return
id|retloc
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Set a baud rate generator.  This needs lots of work.  There are&n; * four BRGs, any of which can be wired to any channel.&n; * The internal baud rate clock is the system clock divided by 16.&n; * This assumes the baudrate is 16x oversampled by the uart.&n; */
multiline_comment|/* #define BRG_INT_CLK&t;(((bd_t *)__res)-&gt;bi_intfreq * 1000000) */
DECL|macro|BRG_INT_CLK
mdefine_line|#define BRG_INT_CLK&t;&t;system_clock
DECL|macro|BRG_UART_CLK
mdefine_line|#define BRG_UART_CLK&t;(BRG_INT_CLK/16)
r_void
DECL|function|m360_cpm_setbrg
id|m360_cpm_setbrg
c_func
(paren
id|uint
id|brg
comma
id|uint
id|rate
)paren
(brace
r_volatile
id|uint
op_star
id|bp
suffix:semicolon
multiline_comment|/* This is good enough to get SMCs running.....&n;&t; */
multiline_comment|/* bp = (uint *)&amp;cpmp-&gt;cp_brgc1; */
id|bp
op_assign
(paren
r_volatile
id|uint
op_star
)paren
(paren
op_amp
id|pquicc-&gt;brgc
(braket
l_int|0
)braket
dot
id|l
)paren
suffix:semicolon
id|bp
op_add_assign
id|brg
suffix:semicolon
op_star
id|bp
op_assign
(paren
(paren
id|BRG_UART_CLK
op_div
id|rate
op_minus
l_int|1
)paren
op_lshift
l_int|1
)paren
op_or
id|CPM_BRG_EN
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 4&n; *  c-basic-offset: 4&n; *  tab-width: 4&n; * End:&n; */
eof
