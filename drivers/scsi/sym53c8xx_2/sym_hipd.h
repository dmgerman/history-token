multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM_HIPD_H
DECL|macro|SYM_HIPD_H
mdefine_line|#define SYM_HIPD_H
multiline_comment|/*&n; *  Generic driver options.&n; *&n; *  They may be defined in platform specific headers, if they &n; *  are useful.&n; *&n; *    SYM_OPT_NO_BUS_MEMORY_MAPPING&n; *        When this option is set, the driver will not load the &n; *        on-chip RAM using MMIO, but let the SCRIPTS processor &n; *        do the work using MOVE MEMORY instructions.&n; *        (set for Linux/PPC)&n; *&n; *    SYM_OPT_HANDLE_DIR_UNKNOWN&n; *        When this option is set, the SCRIPTS used by the driver &n; *        are able to handle SCSI transfers with direction not &n; *        supplied by user.&n; *        (set for Linux-2.0.X)&n; *&n; *    SYM_OPT_HANDLE_DEVICE_QUEUEING&n; *        When this option is set, the driver will use a queue per &n; *        device and handle QUEUE FULL status requeuing internally.&n; *&n; *    SYM_OPT_BUS_DMA_ABSTRACTION&n; *        When this option is set, the driver allocator is responsible &n; *        of maintaining bus physical addresses and so provides virtual &n; *        to bus physical address translation of driver data structures.&n; *        (set for FreeBSD-4 and Linux 2.3)&n; *&n; *    SYM_OPT_SNIFF_INQUIRY&n; *        When this option is set, the driver sniff out successful &n; *        INQUIRY response and performs negotiations accordingly.&n; *        (set for Linux)&n; *&n; *    SYM_OPT_LIMIT_COMMAND_REORDERING&n; *        When this option is set, the driver tries to limit tagged &n; *        command reordering to some reasonnable value.&n; *        (set for Linux)&n; */
macro_line|#if 0
mdefine_line|#define SYM_OPT_NO_BUS_MEMORY_MAPPING
mdefine_line|#define SYM_OPT_HANDLE_DIR_UNKNOWN
mdefine_line|#define SYM_OPT_HANDLE_DEVICE_QUEUEING
mdefine_line|#define SYM_OPT_BUS_DMA_ABSTRACTION
mdefine_line|#define SYM_OPT_SNIFF_INQUIRY
mdefine_line|#define SYM_OPT_LIMIT_COMMAND_REORDERING
macro_line|#endif
multiline_comment|/*&n; *  Active debugging tags and verbosity.&n; *  Both DEBUG_FLAGS and sym_verbose can be redefined &n; *  by the platform specific code to something else.&n; */
DECL|macro|DEBUG_ALLOC
mdefine_line|#define DEBUG_ALLOC&t;(0x0001)
DECL|macro|DEBUG_PHASE
mdefine_line|#define DEBUG_PHASE&t;(0x0002)
DECL|macro|DEBUG_POLL
mdefine_line|#define DEBUG_POLL&t;(0x0004)
DECL|macro|DEBUG_QUEUE
mdefine_line|#define DEBUG_QUEUE&t;(0x0008)
DECL|macro|DEBUG_RESULT
mdefine_line|#define DEBUG_RESULT&t;(0x0010)
DECL|macro|DEBUG_SCATTER
mdefine_line|#define DEBUG_SCATTER&t;(0x0020)
DECL|macro|DEBUG_SCRIPT
mdefine_line|#define DEBUG_SCRIPT&t;(0x0040)
DECL|macro|DEBUG_TINY
mdefine_line|#define DEBUG_TINY&t;(0x0080)
DECL|macro|DEBUG_TIMING
mdefine_line|#define DEBUG_TIMING&t;(0x0100)
DECL|macro|DEBUG_NEGO
mdefine_line|#define DEBUG_NEGO&t;(0x0200)
DECL|macro|DEBUG_TAGS
mdefine_line|#define DEBUG_TAGS&t;(0x0400)
DECL|macro|DEBUG_POINTER
mdefine_line|#define DEBUG_POINTER&t;(0x0800)
macro_line|#ifndef DEBUG_FLAGS
DECL|macro|DEBUG_FLAGS
mdefine_line|#define DEBUG_FLAGS&t;(0x0000)
macro_line|#endif
macro_line|#ifndef sym_verbose
DECL|macro|sym_verbose
mdefine_line|#define sym_verbose&t;(np-&gt;verbose)
macro_line|#endif
multiline_comment|/*&n; *  These ones should have been already defined.&n; */
macro_line|#ifndef offsetof
DECL|macro|offsetof
mdefine_line|#define offsetof(t, m)&t;((size_t) (&amp;((t *)0)-&gt;m))
macro_line|#endif
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a, b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef assert
DECL|macro|assert
mdefine_line|#define&t;assert(expression) { &bslash;&n;&t;if (!(expression)) { &bslash;&n;&t;&t;(void)panic( &bslash;&n;&t;&t;&t;&quot;assertion &bslash;&quot;%s&bslash;&quot; failed: file &bslash;&quot;%s&bslash;&quot;, line %d&bslash;n&quot;, &bslash;&n;&t;&t;&t;#expression, &bslash;&n;&t;&t;&t;__FILE__, __LINE__); &bslash;&n;&t;} &bslash;&n;}
macro_line|#endif
multiline_comment|/*&n; *  Number of tasks per device we want to handle.&n; */
macro_line|#if&t;SYM_CONF_MAX_TAG_ORDER &gt; 8
macro_line|#error&t;&quot;more than 256 tags per logical unit not allowed.&quot;
macro_line|#endif
DECL|macro|SYM_CONF_MAX_TASK
mdefine_line|#define&t;SYM_CONF_MAX_TASK&t;(1&lt;&lt;SYM_CONF_MAX_TAG_ORDER)
multiline_comment|/*&n; *  Donnot use more tasks that we can handle.&n; */
macro_line|#ifndef&t;SYM_CONF_MAX_TAG
DECL|macro|SYM_CONF_MAX_TAG
mdefine_line|#define&t;SYM_CONF_MAX_TAG&t;SYM_CONF_MAX_TASK
macro_line|#endif
macro_line|#if&t;SYM_CONF_MAX_TAG &gt; SYM_CONF_MAX_TASK
DECL|macro|SYM_CONF_MAX_TAG
macro_line|#undef&t;SYM_CONF_MAX_TAG
DECL|macro|SYM_CONF_MAX_TAG
mdefine_line|#define&t;SYM_CONF_MAX_TAG&t;SYM_CONF_MAX_TASK
macro_line|#endif
multiline_comment|/*&n; *    This one means &squot;NO TAG for this job&squot;&n; */
DECL|macro|NO_TAG
mdefine_line|#define NO_TAG&t;(256)
multiline_comment|/*&n; *  Number of SCSI targets.&n; */
macro_line|#if&t;SYM_CONF_MAX_TARGET &gt; 16
macro_line|#error&t;&quot;more than 16 targets not allowed.&quot;
macro_line|#endif
multiline_comment|/*&n; *  Number of logical units per target.&n; */
macro_line|#if&t;SYM_CONF_MAX_LUN &gt; 64
macro_line|#error&t;&quot;more than 64 logical units per target not allowed.&quot;
macro_line|#endif
multiline_comment|/*&n; *    Asynchronous pre-scaler (ns). Shall be 40 for &n; *    the SCSI timings to be compliant.&n; */
DECL|macro|SYM_CONF_MIN_ASYNC
mdefine_line|#define&t;SYM_CONF_MIN_ASYNC (40)
multiline_comment|/*&n; *  Number of entries in the START and DONE queues.&n; *&n; *  We limit to 1 PAGE in order to succeed allocation of &n; *  these queues. Each entry is 8 bytes long (2 DWORDS).&n; */
macro_line|#ifdef&t;SYM_CONF_MAX_START
DECL|macro|SYM_CONF_MAX_QUEUE
mdefine_line|#define&t;SYM_CONF_MAX_QUEUE (SYM_CONF_MAX_START+2)
macro_line|#else
DECL|macro|SYM_CONF_MAX_QUEUE
mdefine_line|#define&t;SYM_CONF_MAX_QUEUE (7*SYM_CONF_MAX_TASK+2)
DECL|macro|SYM_CONF_MAX_START
mdefine_line|#define&t;SYM_CONF_MAX_START (SYM_CONF_MAX_QUEUE-2)
macro_line|#endif
macro_line|#if&t;SYM_CONF_MAX_QUEUE &gt; SYM_MEM_CLUSTER_SIZE/8
DECL|macro|SYM_CONF_MAX_QUEUE
macro_line|#undef&t;SYM_CONF_MAX_QUEUE
DECL|macro|SYM_CONF_MAX_QUEUE
mdefine_line|#define&t;SYM_CONF_MAX_QUEUE (SYM_MEM_CLUSTER_SIZE/8)
DECL|macro|SYM_CONF_MAX_START
macro_line|#undef&t;SYM_CONF_MAX_START
DECL|macro|SYM_CONF_MAX_START
mdefine_line|#define&t;SYM_CONF_MAX_START (SYM_CONF_MAX_QUEUE-2)
macro_line|#endif
multiline_comment|/*&n; *  For this one, we want a short name :-)&n; */
DECL|macro|MAX_QUEUE
mdefine_line|#define MAX_QUEUE&t;SYM_CONF_MAX_QUEUE
multiline_comment|/*&n; *  Union of supported NVRAM formats.&n; */
DECL|struct|sym_nvram
r_struct
id|sym_nvram
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|macro|SYM_SYMBIOS_NVRAM
mdefine_line|#define&t;SYM_SYMBIOS_NVRAM&t;(1)
DECL|macro|SYM_TEKRAM_NVRAM
mdefine_line|#define&t;SYM_TEKRAM_NVRAM&t;(2)
macro_line|#if SYM_CONF_NVRAM_SUPPORT
r_union
(brace
DECL|member|Symbios
id|Symbios_nvram
id|Symbios
suffix:semicolon
DECL|member|Tekram
id|Tekram_nvram
id|Tekram
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *  Common definitions for both bus space based and legacy IO methods.&n; */
DECL|macro|INB
mdefine_line|#define INB(r)&t;&t;INB_OFF(offsetof(struct sym_reg,r))
DECL|macro|INW
mdefine_line|#define INW(r)&t;&t;INW_OFF(offsetof(struct sym_reg,r))
DECL|macro|INL
mdefine_line|#define INL(r)&t;&t;INL_OFF(offsetof(struct sym_reg,r))
DECL|macro|OUTB
mdefine_line|#define OUTB(r, v)&t;OUTB_OFF(offsetof(struct sym_reg,r), (v))
DECL|macro|OUTW
mdefine_line|#define OUTW(r, v)&t;OUTW_OFF(offsetof(struct sym_reg,r), (v))
DECL|macro|OUTL
mdefine_line|#define OUTL(r, v)&t;OUTL_OFF(offsetof(struct sym_reg,r), (v))
DECL|macro|OUTONB
mdefine_line|#define OUTONB(r, m)&t;OUTB(r, INB(r) | (m))
DECL|macro|OUTOFFB
mdefine_line|#define OUTOFFB(r, m)&t;OUTB(r, INB(r) &amp; ~(m))
DECL|macro|OUTONW
mdefine_line|#define OUTONW(r, m)&t;OUTW(r, INW(r) | (m))
DECL|macro|OUTOFFW
mdefine_line|#define OUTOFFW(r, m)&t;OUTW(r, INW(r) &amp; ~(m))
DECL|macro|OUTONL
mdefine_line|#define OUTONL(r, m)&t;OUTL(r, INL(r) | (m))
DECL|macro|OUTOFFL
mdefine_line|#define OUTOFFL(r, m)&t;OUTL(r, INL(r) &amp; ~(m))
multiline_comment|/*&n; *  We normally want the chip to have a consistent view&n; *  of driver internal data structures when we restart it.&n; *  Thus these macros.&n; */
DECL|macro|OUTL_DSP
mdefine_line|#define OUTL_DSP(v)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;MEMORY_WRITE_BARRIER();&t;&t;&bslash;&n;&t;&t;OUTL (nc_dsp, (v));&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|OUTONB_STD
mdefine_line|#define OUTONB_STD()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;MEMORY_WRITE_BARRIER();&t;&t;&bslash;&n;&t;&t;OUTONB (nc_dcntl, (STD|NOCOM));&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; *  Command control block states.&n; */
DECL|macro|HS_IDLE
mdefine_line|#define HS_IDLE&t;&t;(0)
DECL|macro|HS_BUSY
mdefine_line|#define HS_BUSY&t;&t;(1)
DECL|macro|HS_NEGOTIATE
mdefine_line|#define HS_NEGOTIATE&t;(2)&t;/* sync/wide data transfer*/
DECL|macro|HS_DISCONNECT
mdefine_line|#define HS_DISCONNECT&t;(3)&t;/* Disconnected by target */
DECL|macro|HS_WAIT
mdefine_line|#define HS_WAIT&t;&t;(4)&t;/* waiting for resource&t;  */
DECL|macro|HS_DONEMASK
mdefine_line|#define HS_DONEMASK&t;(0x80)
DECL|macro|HS_COMPLETE
mdefine_line|#define HS_COMPLETE&t;(4|HS_DONEMASK)
DECL|macro|HS_SEL_TIMEOUT
mdefine_line|#define HS_SEL_TIMEOUT&t;(5|HS_DONEMASK)&t;/* Selection timeout      */
DECL|macro|HS_UNEXPECTED
mdefine_line|#define HS_UNEXPECTED&t;(6|HS_DONEMASK)&t;/* Unexpected disconnect  */
DECL|macro|HS_COMP_ERR
mdefine_line|#define HS_COMP_ERR&t;(7|HS_DONEMASK)&t;/* Completed with error&t;  */
multiline_comment|/*&n; *  Software Interrupt Codes&n; */
DECL|macro|SIR_BAD_SCSI_STATUS
mdefine_line|#define&t;SIR_BAD_SCSI_STATUS&t;(1)
DECL|macro|SIR_SEL_ATN_NO_MSG_OUT
mdefine_line|#define&t;SIR_SEL_ATN_NO_MSG_OUT&t;(2)
DECL|macro|SIR_MSG_RECEIVED
mdefine_line|#define&t;SIR_MSG_RECEIVED&t;(3)
DECL|macro|SIR_MSG_WEIRD
mdefine_line|#define&t;SIR_MSG_WEIRD&t;&t;(4)
DECL|macro|SIR_NEGO_FAILED
mdefine_line|#define&t;SIR_NEGO_FAILED&t;&t;(5)
DECL|macro|SIR_NEGO_PROTO
mdefine_line|#define&t;SIR_NEGO_PROTO&t;&t;(6)
DECL|macro|SIR_SCRIPT_STOPPED
mdefine_line|#define&t;SIR_SCRIPT_STOPPED&t;(7)
DECL|macro|SIR_REJECT_TO_SEND
mdefine_line|#define&t;SIR_REJECT_TO_SEND&t;(8)
DECL|macro|SIR_SWIDE_OVERRUN
mdefine_line|#define&t;SIR_SWIDE_OVERRUN&t;(9)
DECL|macro|SIR_SODL_UNDERRUN
mdefine_line|#define&t;SIR_SODL_UNDERRUN&t;(10)
DECL|macro|SIR_RESEL_NO_MSG_IN
mdefine_line|#define&t;SIR_RESEL_NO_MSG_IN&t;(11)
DECL|macro|SIR_RESEL_NO_IDENTIFY
mdefine_line|#define&t;SIR_RESEL_NO_IDENTIFY&t;(12)
DECL|macro|SIR_RESEL_BAD_LUN
mdefine_line|#define&t;SIR_RESEL_BAD_LUN&t;(13)
DECL|macro|SIR_TARGET_SELECTED
mdefine_line|#define&t;SIR_TARGET_SELECTED&t;(14)
DECL|macro|SIR_RESEL_BAD_I_T_L
mdefine_line|#define&t;SIR_RESEL_BAD_I_T_L&t;(15)
DECL|macro|SIR_RESEL_BAD_I_T_L_Q
mdefine_line|#define&t;SIR_RESEL_BAD_I_T_L_Q&t;(16)
DECL|macro|SIR_ABORT_SENT
mdefine_line|#define&t;SIR_ABORT_SENT&t;&t;(17)
DECL|macro|SIR_RESEL_ABORTED
mdefine_line|#define&t;SIR_RESEL_ABORTED&t;(18)
DECL|macro|SIR_MSG_OUT_DONE
mdefine_line|#define&t;SIR_MSG_OUT_DONE&t;(19)
DECL|macro|SIR_COMPLETE_ERROR
mdefine_line|#define&t;SIR_COMPLETE_ERROR&t;(20)
DECL|macro|SIR_DATA_OVERRUN
mdefine_line|#define&t;SIR_DATA_OVERRUN&t;(21)
DECL|macro|SIR_BAD_PHASE
mdefine_line|#define&t;SIR_BAD_PHASE&t;&t;(22)
macro_line|#if&t;SYM_CONF_DMA_ADDRESSING_MODE == 2
DECL|macro|SIR_DMAP_DIRTY
mdefine_line|#define&t;SIR_DMAP_DIRTY&t;&t;(23)
DECL|macro|SIR_MAX
mdefine_line|#define&t;SIR_MAX&t;&t;&t;(23)
macro_line|#else
DECL|macro|SIR_MAX
mdefine_line|#define&t;SIR_MAX&t;&t;&t;(22)
macro_line|#endif
multiline_comment|/*&n; *  Extended error bit codes.&n; *  xerr_status field of struct sym_ccb.&n; */
DECL|macro|XE_EXTRA_DATA
mdefine_line|#define&t;XE_EXTRA_DATA&t;(1)&t;/* unexpected data phase&t; */
DECL|macro|XE_BAD_PHASE
mdefine_line|#define&t;XE_BAD_PHASE&t;(1&lt;&lt;1)&t;/* illegal phase (4/5)&t;&t; */
DECL|macro|XE_PARITY_ERR
mdefine_line|#define&t;XE_PARITY_ERR&t;(1&lt;&lt;2)&t;/* unrecovered SCSI parity error */
DECL|macro|XE_SODL_UNRUN
mdefine_line|#define&t;XE_SODL_UNRUN&t;(1&lt;&lt;3)&t;/* ODD transfer in DATA OUT phase */
DECL|macro|XE_SWIDE_OVRUN
mdefine_line|#define&t;XE_SWIDE_OVRUN&t;(1&lt;&lt;4)&t;/* ODD transfer in DATA IN phase */
multiline_comment|/*&n; *  Negotiation status.&n; *  nego_status field of struct sym_ccb.&n; */
DECL|macro|NS_SYNC
mdefine_line|#define NS_SYNC&t;&t;(1)
DECL|macro|NS_WIDE
mdefine_line|#define NS_WIDE&t;&t;(2)
DECL|macro|NS_PPR
mdefine_line|#define NS_PPR&t;&t;(3)
multiline_comment|/*&n; *  A CCB hashed table is used to retrieve CCB address &n; *  from DSA value.&n; */
DECL|macro|CCB_HASH_SHIFT
mdefine_line|#define CCB_HASH_SHIFT&t;&t;8
DECL|macro|CCB_HASH_SIZE
mdefine_line|#define CCB_HASH_SIZE&t;&t;(1UL &lt;&lt; CCB_HASH_SHIFT)
DECL|macro|CCB_HASH_MASK
mdefine_line|#define CCB_HASH_MASK&t;&t;(CCB_HASH_SIZE-1)
macro_line|#if 1
DECL|macro|CCB_HASH_CODE
mdefine_line|#define CCB_HASH_CODE(dsa)&t;&bslash;&n;&t;(((dsa) &gt;&gt; (_LGRU16_(sizeof(struct sym_ccb)))) &amp; CCB_HASH_MASK)
macro_line|#else
DECL|macro|CCB_HASH_CODE
mdefine_line|#define CCB_HASH_CODE(dsa)&t;(((dsa) &gt;&gt; 9) &amp; CCB_HASH_MASK)
macro_line|#endif
macro_line|#if&t;SYM_CONF_DMA_ADDRESSING_MODE == 2
multiline_comment|/*&n; *  We may want to use segment registers for 64 bit DMA.&n; *  16 segments registers -&gt; up to 64 GB addressable.&n; */
DECL|macro|SYM_DMAP_SHIFT
mdefine_line|#define SYM_DMAP_SHIFT&t;(4)
DECL|macro|SYM_DMAP_SIZE
mdefine_line|#define SYM_DMAP_SIZE&t;(1u&lt;&lt;SYM_DMAP_SHIFT)
DECL|macro|SYM_DMAP_MASK
mdefine_line|#define SYM_DMAP_MASK&t;(SYM_DMAP_SIZE-1)
macro_line|#endif
multiline_comment|/*&n; *  Device flags.&n; */
DECL|macro|SYM_DISC_ENABLED
mdefine_line|#define SYM_DISC_ENABLED&t;(1)
DECL|macro|SYM_TAGS_ENABLED
mdefine_line|#define SYM_TAGS_ENABLED&t;(1&lt;&lt;1)
DECL|macro|SYM_SCAN_BOOT_DISABLED
mdefine_line|#define SYM_SCAN_BOOT_DISABLED&t;(1&lt;&lt;2)
DECL|macro|SYM_SCAN_LUNS_DISABLED
mdefine_line|#define SYM_SCAN_LUNS_DISABLED&t;(1&lt;&lt;3)
multiline_comment|/*&n; *  Host adapter miscellaneous flags.&n; */
DECL|macro|SYM_AVOID_BUS_RESET
mdefine_line|#define SYM_AVOID_BUS_RESET&t;(1)
DECL|macro|SYM_SCAN_TARGETS_HILO
mdefine_line|#define SYM_SCAN_TARGETS_HILO&t;(1&lt;&lt;1)
multiline_comment|/*&n; *  Misc.&n; */
DECL|macro|SYM_SNOOP_TIMEOUT
mdefine_line|#define SYM_SNOOP_TIMEOUT (10000000)
DECL|macro|BUS_8_BIT
mdefine_line|#define BUS_8_BIT&t;0
DECL|macro|BUS_16_BIT
mdefine_line|#define BUS_16_BIT&t;1
multiline_comment|/*&n; *  Gather negotiable parameters value&n; */
DECL|struct|sym_trans
r_struct
id|sym_trans
(brace
DECL|member|scsi_version
id|u8
id|scsi_version
suffix:semicolon
DECL|member|spi_version
id|u8
id|spi_version
suffix:semicolon
DECL|member|period
id|u8
id|period
suffix:semicolon
DECL|member|offset
id|u8
id|offset
suffix:semicolon
DECL|member|width
id|u8
id|width
suffix:semicolon
DECL|member|options
id|u8
id|options
suffix:semicolon
multiline_comment|/* PPR options */
)brace
suffix:semicolon
DECL|struct|sym_tinfo
r_struct
id|sym_tinfo
(brace
DECL|member|curr
r_struct
id|sym_trans
id|curr
suffix:semicolon
DECL|member|goal
r_struct
id|sym_trans
id|goal
suffix:semicolon
DECL|member|user
r_struct
id|sym_trans
id|user
suffix:semicolon
macro_line|#ifdef&t;SYM_OPT_ANNOUNCE_TRANSFER_RATE
DECL|member|prev
r_struct
id|sym_trans
id|prev
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *  Global TCB HEADER.&n; *&n; *  Due to lack of indirect addressing on earlier NCR chips,&n; *  this substructure is copied from the TCB to a global &n; *  address after selection.&n; *  For SYMBIOS chips that support LOAD/STORE this copy is &n; *  not needed and thus not performed.&n; */
DECL|struct|sym_tcbh
r_struct
id|sym_tcbh
(brace
multiline_comment|/*&n;&t; *  Scripts bus addresses of LUN table accessed from scripts.&n;&t; *  LUN #0 is a special case, since multi-lun devices are rare, &n;&t; *  and we we want to speed-up the general case and not waste &n;&t; *  resources.&n;&t; */
DECL|member|luntbl_sa
id|u32
id|luntbl_sa
suffix:semicolon
multiline_comment|/* bus address of this table&t;*/
DECL|member|lun0_sa
id|u32
id|lun0_sa
suffix:semicolon
multiline_comment|/* bus address of LCB #0&t;*/
multiline_comment|/*&n;&t; *  Actual SYNC/WIDE IO registers value for this target.&n;&t; *  &squot;sval&squot;, &squot;wval&squot; and &squot;uval&squot; are read from SCRIPTS and &n;&t; *  so have alignment constraints.&n;&t; */
DECL|member|uval
multiline_comment|/*0*/
id|u_char
id|uval
suffix:semicolon
multiline_comment|/* -&gt; SCNTL4 register&t;&t;*/
DECL|member|sval
multiline_comment|/*1*/
id|u_char
id|sval
suffix:semicolon
multiline_comment|/* -&gt; SXFER  io register&t;*/
DECL|member|filler1
multiline_comment|/*2*/
id|u_char
id|filler1
suffix:semicolon
DECL|member|wval
multiline_comment|/*3*/
id|u_char
id|wval
suffix:semicolon
multiline_comment|/* -&gt; SCNTL3 io register&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; *  Target Control Block&n; */
DECL|struct|sym_tcb
r_struct
id|sym_tcb
(brace
multiline_comment|/*&n;&t; *  TCB header.&n;&t; *  Assumed at offset 0.&n;&t; */
DECL|member|head
multiline_comment|/*0*/
r_struct
id|sym_tcbh
id|head
suffix:semicolon
multiline_comment|/*&n;&t; *  LUN table used by the SCRIPTS processor.&n;&t; *  An array of bus addresses is used on reselection.&n;&t; */
DECL|member|luntbl
id|u32
op_star
id|luntbl
suffix:semicolon
multiline_comment|/* LCBs bus address table&t;*/
multiline_comment|/*&n;&t; *  LUN table used by the C code.&n;&t; */
DECL|member|lun0p
id|lcb_p
id|lun0p
suffix:semicolon
multiline_comment|/* LCB of LUN #0 (usual case)&t;*/
macro_line|#if SYM_CONF_MAX_LUN &gt; 1
DECL|member|lunmp
id|lcb_p
op_star
id|lunmp
suffix:semicolon
multiline_comment|/* Other LCBs [1..MAX_LUN]&t;*/
macro_line|#endif
multiline_comment|/*&n;&t; *  Bitmap that tells about LUNs that succeeded at least &n;&t; *  1 IO and therefore assumed to be a real device.&n;&t; *  Avoid useless allocation of the LCB structure.&n;&t; */
DECL|member|lun_map
id|u32
id|lun_map
(braket
(paren
id|SYM_CONF_MAX_LUN
op_plus
l_int|31
)paren
op_div
l_int|32
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *  Bitmap that tells about LUNs that haven&squot;t yet an LCB &n;&t; *  allocated (not discovered or LCB allocation failed).&n;&t; */
DECL|member|busy0_map
id|u32
id|busy0_map
(braket
(paren
id|SYM_CONF_MAX_LUN
op_plus
l_int|31
)paren
op_div
l_int|32
)braket
suffix:semicolon
macro_line|#ifdef&t;SYM_HAVE_STCB
multiline_comment|/*&n;&t; *  O/S specific data structure.&n;&t; */
DECL|member|s
r_struct
id|sym_stcb
id|s
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Transfer capabilities (SIP)&n;&t; */
DECL|member|tinfo
r_struct
id|sym_tinfo
id|tinfo
suffix:semicolon
multiline_comment|/*&n;&t; * Keep track of the CCB used for the negotiation in order&n;&t; * to ensure that only 1 negotiation is queued at a time.&n;&t; */
DECL|member|nego_cp
id|ccb_p
id|nego_cp
suffix:semicolon
multiline_comment|/* CCB used for the nego&t;&t;*/
multiline_comment|/*&n;&t; *  Set when we want to reset the device.&n;&t; */
DECL|member|to_reset
id|u_char
id|to_reset
suffix:semicolon
multiline_comment|/*&n;&t; *  Other user settable limits and options.&n;&t; *  These limits are read from the NVRAM if present.&n;&t; */
DECL|member|usrflags
id|u_char
id|usrflags
suffix:semicolon
DECL|member|usrtags
id|u_short
id|usrtags
suffix:semicolon
macro_line|#ifdef&t;SYM_OPT_SNIFF_INQUIRY
multiline_comment|/*&n;&t; *  Some minimal information from INQUIRY response.&n;&t; */
DECL|member|cmdq_map
id|u32
id|cmdq_map
(braket
(paren
id|SYM_CONF_MAX_LUN
op_plus
l_int|31
)paren
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|inq_version
id|u_char
id|inq_version
suffix:semicolon
DECL|member|inq_byte7
id|u_char
id|inq_byte7
suffix:semicolon
DECL|member|inq_byte56
id|u_char
id|inq_byte56
suffix:semicolon
DECL|member|inq_byte7_valid
id|u_char
id|inq_byte7_valid
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *  Global LCB HEADER.&n; *&n; *  Due to lack of indirect addressing on earlier NCR chips,&n; *  this substructure is copied from the LCB to a global &n; *  address after selection.&n; *  For SYMBIOS chips that support LOAD/STORE this copy is &n; *  not needed and thus not performed.&n; */
DECL|struct|sym_lcbh
r_struct
id|sym_lcbh
(brace
multiline_comment|/*&n;&t; *  SCRIPTS address jumped by SCRIPTS on reselection.&n;&t; *  For not probed logical units, this address points to &n;&t; *  SCRIPTS that deal with bad LU handling (must be at &n;&t; *  offset zero of the LCB for that reason).&n;&t; */
DECL|member|resel_sa
multiline_comment|/*0*/
id|u32
id|resel_sa
suffix:semicolon
multiline_comment|/*&n;&t; *  Task (bus address of a CCB) read from SCRIPTS that points &n;&t; *  to the unique ITL nexus allowed to be disconnected.&n;&t; */
DECL|member|itl_task_sa
id|u32
id|itl_task_sa
suffix:semicolon
multiline_comment|/*&n;&t; *  Task table bus address (read from SCRIPTS).&n;&t; */
DECL|member|itlq_tbl_sa
id|u32
id|itlq_tbl_sa
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Logical Unit Control Block&n; */
DECL|struct|sym_lcb
r_struct
id|sym_lcb
(brace
multiline_comment|/*&n;&t; *  TCB header.&n;&t; *  Assumed at offset 0.&n;&t; */
DECL|member|head
multiline_comment|/*0*/
r_struct
id|sym_lcbh
id|head
suffix:semicolon
multiline_comment|/*&n;&t; *  Task table read from SCRIPTS that contains pointers to &n;&t; *  ITLQ nexuses. The bus address read from SCRIPTS is &n;&t; *  inside the header.&n;&t; */
DECL|member|itlq_tbl
id|u32
op_star
id|itlq_tbl
suffix:semicolon
multiline_comment|/* Kernel virtual address&t;*/
multiline_comment|/*&n;&t; *  Busy CCBs management.&n;&t; */
DECL|member|busy_itlq
id|u_short
id|busy_itlq
suffix:semicolon
multiline_comment|/* Number of busy tagged CCBs&t;*/
DECL|member|busy_itl
id|u_short
id|busy_itl
suffix:semicolon
multiline_comment|/* Number of busy untagged CCBs&t;*/
multiline_comment|/*&n;&t; *  Circular tag allocation buffer.&n;&t; */
DECL|member|ia_tag
id|u_short
id|ia_tag
suffix:semicolon
multiline_comment|/* Tag allocation index&t;&t;*/
DECL|member|if_tag
id|u_short
id|if_tag
suffix:semicolon
multiline_comment|/* Tag release index&t;&t;*/
DECL|member|cb_tags
id|u_char
op_star
id|cb_tags
suffix:semicolon
multiline_comment|/* Circular tags buffer&t;&t;*/
multiline_comment|/*&n;&t; *  O/S specific data structure.&n;&t; */
macro_line|#ifdef&t;SYM_HAVE_SLCB
DECL|member|s
r_struct
id|sym_slcb
id|s
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
multiline_comment|/*&n;&t; *  Optionnaly the driver can handle device queueing, &n;&t; *  and requeues internally command to redo.&n;&t; */
id|SYM_QUEHEAD
DECL|member|waiting_ccbq
id|waiting_ccbq
suffix:semicolon
id|SYM_QUEHEAD
DECL|member|started_ccbq
id|started_ccbq
suffix:semicolon
DECL|member|num_sgood
r_int
id|num_sgood
suffix:semicolon
DECL|member|started_tags
id|u_short
id|started_tags
suffix:semicolon
DECL|member|started_no_tag
id|u_short
id|started_no_tag
suffix:semicolon
DECL|member|started_max
id|u_short
id|started_max
suffix:semicolon
DECL|member|started_limit
id|u_short
id|started_limit
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SYM_OPT_LIMIT_COMMAND_REORDERING
multiline_comment|/*&n;&t; *  Optionnaly the driver can try to prevent SCSI &n;&t; *  IOs from being too much reordering.&n;&t; */
DECL|member|tags_si
id|u_char
id|tags_si
suffix:semicolon
multiline_comment|/* Current index to tags sum&t;*/
DECL|member|tags_sum
id|u_short
id|tags_sum
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Tags sum counters&t;&t;*/
DECL|member|tags_since
id|u_short
id|tags_since
suffix:semicolon
multiline_comment|/* # of tags since last switch&t;*/
macro_line|#endif
multiline_comment|/*&n;&t; *  Set when we want to clear all tasks.&n;&t; */
DECL|member|to_clear
id|u_char
id|to_clear
suffix:semicolon
multiline_comment|/*&n;&t; *  Capabilities.&n;&t; */
DECL|member|user_flags
id|u_char
id|user_flags
suffix:semicolon
DECL|member|curr_flags
id|u_char
id|curr_flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Action from SCRIPTS on a task.&n; *  Is part of the CCB, but is also used separately to plug &n; *  error handling action to perform from SCRIPTS.&n; */
DECL|struct|sym_actscr
r_struct
id|sym_actscr
(brace
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* Jumped by SCRIPTS after selection&t;*/
DECL|member|restart
id|u32
id|restart
suffix:semicolon
multiline_comment|/* Jumped by SCRIPTS on relection&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; *  Phase mismatch context.&n; *&n; *  It is part of the CCB and is used as parameters for the &n; *  DATA pointer. We need two contexts to handle correctly the &n; *  SAVED DATA POINTER.&n; */
DECL|struct|sym_pmc
r_struct
id|sym_pmc
(brace
DECL|member|sg
r_struct
id|sym_tblmove
id|sg
suffix:semicolon
multiline_comment|/* Updated interrupted SG block&t;*/
DECL|member|ret
id|u32
id|ret
suffix:semicolon
multiline_comment|/* SCRIPT return address&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; *  LUN control block lookup.&n; *  We use a direct pointer for LUN #0, and a table of &n; *  pointers which is only allocated for devices that support &n; *  LUN(s) &gt; 0.&n; */
macro_line|#if SYM_CONF_MAX_LUN &lt;= 1
DECL|macro|sym_lp
mdefine_line|#define sym_lp(np, tp, lun) (!lun) ? (tp)-&gt;lun0p : 0
macro_line|#else
DECL|macro|sym_lp
mdefine_line|#define sym_lp(np, tp, lun) &bslash;&n;&t;(!lun) ? (tp)-&gt;lun0p : (tp)-&gt;lunmp ? (tp)-&gt;lunmp[(lun)] : 0
macro_line|#endif
multiline_comment|/*&n; *  Status are used by the host and the script processor.&n; *&n; *  The last four bytes (status[4]) are copied to the &n; *  scratchb register (declared as scr0..scr3) just after the &n; *  select/reselect, and copied back just after disconnecting.&n; *  Inside the script the XX_REG are used.&n; */
multiline_comment|/*&n; *  Last four bytes (script)&n; */
DECL|macro|HX_REG
mdefine_line|#define  HX_REG&t;scr0
DECL|macro|HX_PRT
mdefine_line|#define  HX_PRT&t;nc_scr0
DECL|macro|HS_REG
mdefine_line|#define  HS_REG&t;scr1
DECL|macro|HS_PRT
mdefine_line|#define  HS_PRT&t;nc_scr1
DECL|macro|SS_REG
mdefine_line|#define  SS_REG&t;scr2
DECL|macro|SS_PRT
mdefine_line|#define  SS_PRT&t;nc_scr2
DECL|macro|HF_REG
mdefine_line|#define  HF_REG&t;scr3
DECL|macro|HF_PRT
mdefine_line|#define  HF_PRT&t;nc_scr3
multiline_comment|/*&n; *  Last four bytes (host)&n; */
DECL|macro|host_xflags
mdefine_line|#define  host_xflags   phys.head.status[0]
DECL|macro|host_status
mdefine_line|#define  host_status   phys.head.status[1]
DECL|macro|ssss_status
mdefine_line|#define  ssss_status   phys.head.status[2]
DECL|macro|host_flags
mdefine_line|#define  host_flags    phys.head.status[3]
multiline_comment|/*&n; *  Host flags&n; */
DECL|macro|HF_IN_PM0
mdefine_line|#define HF_IN_PM0&t;1u
DECL|macro|HF_IN_PM1
mdefine_line|#define HF_IN_PM1&t;(1u&lt;&lt;1)
DECL|macro|HF_ACT_PM
mdefine_line|#define HF_ACT_PM&t;(1u&lt;&lt;2)
DECL|macro|HF_DP_SAVED
mdefine_line|#define HF_DP_SAVED&t;(1u&lt;&lt;3)
DECL|macro|HF_SENSE
mdefine_line|#define HF_SENSE&t;(1u&lt;&lt;4)
DECL|macro|HF_EXT_ERR
mdefine_line|#define HF_EXT_ERR&t;(1u&lt;&lt;5)
DECL|macro|HF_DATA_IN
mdefine_line|#define HF_DATA_IN&t;(1u&lt;&lt;6)
macro_line|#ifdef SYM_CONF_IARB_SUPPORT
DECL|macro|HF_HINT_IARB
mdefine_line|#define HF_HINT_IARB&t;(1u&lt;&lt;7)
macro_line|#endif
multiline_comment|/*&n; *  More host flags&n; */
macro_line|#if&t;SYM_CONF_DMA_ADDRESSING_MODE == 2
DECL|macro|HX_DMAP_DIRTY
mdefine_line|#define&t;HX_DMAP_DIRTY&t;(1u&lt;&lt;7)
macro_line|#endif
multiline_comment|/*&n; *  Global CCB HEADER.&n; *&n; *  Due to lack of indirect addressing on earlier NCR chips,&n; *  this substructure is copied from the ccb to a global &n; *  address after selection (or reselection) and copied back &n; *  before disconnect.&n; *  For SYMBIOS chips that support LOAD/STORE this copy is &n; *  not needed and thus not performed.&n; */
DECL|struct|sym_ccbh
r_struct
id|sym_ccbh
(brace
multiline_comment|/*&n;&t; *  Start and restart SCRIPTS addresses (must be at 0).&n;&t; */
DECL|member|go
multiline_comment|/*0*/
r_struct
id|sym_actscr
id|go
suffix:semicolon
multiline_comment|/*&n;&t; *  SCRIPTS jump address that deal with data pointers.&n;&t; *  &squot;savep&squot; points to the position in the script responsible &n;&t; *  for the actual transfer of data.&n;&t; *  It&squot;s written on reception of a SAVE_DATA_POINTER message.&n;&t; */
DECL|member|savep
id|u32
id|savep
suffix:semicolon
multiline_comment|/* Jump address to saved data pointer&t;*/
DECL|member|lastp
id|u32
id|lastp
suffix:semicolon
multiline_comment|/* SCRIPTS address at end of data&t;*/
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
DECL|member|wlastp
id|u32
id|wlastp
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Status fields.&n;&t; */
DECL|member|status
id|u8
id|status
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  GET/SET the value of the data pointer used by SCRIPTS.&n; *&n; *  We must distinguish between the LOAD/STORE-based SCRIPTS &n; *  that use directly the header in the CCB, and the NCR-GENERIC &n; *  SCRIPTS that use the copy of the header in the HCB.&n; */
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
DECL|macro|sym_set_script_dp
mdefine_line|#define sym_set_script_dp(np, cp, dp)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (np-&gt;features &amp; FE_LDSTR)&t;&t;&t;&bslash;&n;&t;&t;&t;cp-&gt;phys.head.lastp = cpu_to_scr(dp);&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;np-&gt;ccb_head.lastp = cpu_to_scr(dp);&t;&bslash;&n;&t;} while (0)
DECL|macro|sym_get_script_dp
mdefine_line|#define sym_get_script_dp(np, cp) &t;&t;&t;&t;&bslash;&n;&t;scr_to_cpu((np-&gt;features &amp; FE_LDSTR) ?&t;&t;&t;&bslash;&n;&t;&t;cp-&gt;phys.head.lastp : np-&gt;ccb_head.lastp)
macro_line|#else
DECL|macro|sym_set_script_dp
mdefine_line|#define sym_set_script_dp(np, cp, dp)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cp-&gt;phys.head.lastp = cpu_to_scr(dp);&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|sym_get_script_dp
mdefine_line|#define sym_get_script_dp(np, cp) (cp-&gt;phys.head.lastp)
macro_line|#endif
multiline_comment|/*&n; *  Data Structure Block&n; *&n; *  During execution of a ccb by the script processor, the &n; *  DSA (data structure address) register points to this &n; *  substructure of the ccb.&n; */
DECL|struct|sym_dsb
r_struct
id|sym_dsb
(brace
multiline_comment|/*&n;&t; *  CCB header.&n;&t; *  Also assumed at offset 0 of the sym_ccb structure.&n;&t; */
DECL|member|head
multiline_comment|/*0*/
r_struct
id|sym_ccbh
id|head
suffix:semicolon
multiline_comment|/*&n;&t; *  Phase mismatch contexts.&n;&t; *  We need two to handle correctly the SAVED DATA POINTER.&n;&t; *  MUST BOTH BE AT OFFSET &lt; 256, due to using 8 bit arithmetic &n;&t; *  for address calculation from SCRIPTS.&n;&t; */
DECL|member|pm0
r_struct
id|sym_pmc
id|pm0
suffix:semicolon
DECL|member|pm1
r_struct
id|sym_pmc
id|pm1
suffix:semicolon
multiline_comment|/*&n;&t; *  Table data for Script&n;&t; */
DECL|member|select
r_struct
id|sym_tblsel
id|select
suffix:semicolon
DECL|member|smsg
r_struct
id|sym_tblmove
id|smsg
suffix:semicolon
DECL|member|smsg_ext
r_struct
id|sym_tblmove
id|smsg_ext
suffix:semicolon
DECL|member|cmd
r_struct
id|sym_tblmove
id|cmd
suffix:semicolon
DECL|member|sense
r_struct
id|sym_tblmove
id|sense
suffix:semicolon
DECL|member|wresid
r_struct
id|sym_tblmove
id|wresid
suffix:semicolon
DECL|member|data
r_struct
id|sym_tblmove
id|data
(braket
id|SYM_CONF_MAX_SG
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Our Command Control Block&n; */
DECL|struct|sym_ccb
r_struct
id|sym_ccb
(brace
multiline_comment|/*&n;&t; *  This is the data structure which is pointed by the DSA &n;&t; *  register when it is executed by the script processor.&n;&t; *  It must be the first entry.&n;&t; */
DECL|member|phys
r_struct
id|sym_dsb
id|phys
suffix:semicolon
multiline_comment|/*&n;&t; *  Pointer to CAM ccb and related stuff.&n;&t; */
DECL|member|cam_ccb
id|cam_ccb_p
id|cam_ccb
suffix:semicolon
multiline_comment|/* CAM scsiio ccb&t;&t;*/
DECL|member|cdb_buf
id|u8
id|cdb_buf
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Copy of CDB&t;&t;&t;*/
DECL|member|sns_bbuf
id|u8
op_star
id|sns_bbuf
suffix:semicolon
multiline_comment|/* Bounce buffer for sense data&t;*/
macro_line|#ifndef&t;SYM_SNS_BBUF_LEN
DECL|macro|SYM_SNS_BBUF_LEN
mdefine_line|#define&t;SYM_SNS_BBUF_LEN (32)
macro_line|#endif&t;
DECL|member|data_len
r_int
id|data_len
suffix:semicolon
multiline_comment|/* Total data length&t;&t;*/
DECL|member|segments
r_int
id|segments
suffix:semicolon
multiline_comment|/* Number of SG segments&t;*/
DECL|member|order
id|u8
id|order
suffix:semicolon
multiline_comment|/* Tag type (if tagged command)&t;*/
multiline_comment|/*&n;&t; *  Miscellaneous status&squot;.&n;&t; */
DECL|member|nego_status
id|u_char
id|nego_status
suffix:semicolon
multiline_comment|/* Negotiation status&t;&t;*/
DECL|member|xerr_status
id|u_char
id|xerr_status
suffix:semicolon
multiline_comment|/* Extended error flags&t;&t;*/
DECL|member|extra_bytes
id|u32
id|extra_bytes
suffix:semicolon
multiline_comment|/* Extraneous bytes transferred&t;*/
multiline_comment|/*&n;&t; *  Message areas.&n;&t; *  We prepare a message to be sent after selection.&n;&t; *  We may use a second one if the command is rescheduled &n;&t; *  due to CHECK_CONDITION or COMMAND TERMINATED.&n;&t; *  Contents are IDENTIFY and SIMPLE_TAG.&n;&t; *  While negotiating sync or wide transfer,&n;&t; *  a SDTR or WDTR message is appended.&n;&t; */
DECL|member|scsi_smsg
id|u_char
id|scsi_smsg
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|scsi_smsg2
id|u_char
id|scsi_smsg2
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *  Auto request sense related fields.&n;&t; */
DECL|member|sensecmd
id|u_char
id|sensecmd
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Request Sense command&t;*/
DECL|member|sv_scsi_status
id|u_char
id|sv_scsi_status
suffix:semicolon
multiline_comment|/* Saved SCSI status &t;&t;*/
DECL|member|sv_xerr_status
id|u_char
id|sv_xerr_status
suffix:semicolon
multiline_comment|/* Saved extended status&t;*/
DECL|member|sv_resid
r_int
id|sv_resid
suffix:semicolon
multiline_comment|/* Saved residual&t;&t;*/
multiline_comment|/*&n;&t; *  O/S specific data structure.&n;&t; */
macro_line|#ifdef&t;SYM_HAVE_SCCB
DECL|member|s
r_struct
id|sym_sccb
id|s
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Other fields.&n;&t; */
macro_line|#ifdef&t;SYM_OPT_HANDLE_IO_TIMEOUT
DECL|member|tmo_linkq
id|SYM_QUEHEAD
id|tmo_linkq
suffix:semicolon
multiline_comment|/* Optional timeout handling&t;*/
DECL|member|tmo_clock
id|u_int
id|tmo_clock
suffix:semicolon
multiline_comment|/* (link and dealine value)&t;*/
macro_line|#endif
DECL|member|ccb_ba
id|u32
id|ccb_ba
suffix:semicolon
multiline_comment|/* BUS address of this CCB&t;*/
DECL|member|tag
id|u_short
id|tag
suffix:semicolon
multiline_comment|/* Tag for this transfer&t;*/
multiline_comment|/*  NO_TAG means no tag&t;&t;*/
DECL|member|target
id|u_char
id|target
suffix:semicolon
DECL|member|lun
id|u_char
id|lun
suffix:semicolon
DECL|member|link_ccbh
id|ccb_p
id|link_ccbh
suffix:semicolon
multiline_comment|/* Host adapter CCB hash chain&t;*/
id|SYM_QUEHEAD
DECL|member|link_ccbq
id|link_ccbq
suffix:semicolon
multiline_comment|/* Link to free/busy CCB queue&t;*/
DECL|member|startp
id|u32
id|startp
suffix:semicolon
multiline_comment|/* Initial data pointer&t;&t;*/
DECL|member|goalp
id|u32
id|goalp
suffix:semicolon
multiline_comment|/* Expected last data pointer&t;*/
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
DECL|member|wgoalp
id|u32
id|wgoalp
suffix:semicolon
macro_line|#endif
DECL|member|ext_sg
r_int
id|ext_sg
suffix:semicolon
multiline_comment|/* Extreme data pointer, used&t;*/
DECL|member|ext_ofs
r_int
id|ext_ofs
suffix:semicolon
multiline_comment|/*  to calculate the residual.&t;*/
macro_line|#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
id|SYM_QUEHEAD
DECL|member|link2_ccbq
id|link2_ccbq
suffix:semicolon
multiline_comment|/* Link for device queueing&t;*/
DECL|member|started
id|u_char
id|started
suffix:semicolon
multiline_comment|/* CCB queued to the squeue&t;*/
macro_line|#endif
DECL|member|to_abort
id|u_char
id|to_abort
suffix:semicolon
multiline_comment|/* Want this IO to be aborted&t;*/
macro_line|#ifdef SYM_OPT_LIMIT_COMMAND_REORDERING
DECL|member|tags_si
id|u_char
id|tags_si
suffix:semicolon
multiline_comment|/* Lun tags sum index (0,1)&t;*/
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|CCB_BA
mdefine_line|#define CCB_BA(cp,lbl)&t;(cp-&gt;ccb_ba + offsetof(struct sym_ccb, lbl))
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
DECL|macro|sym_goalp
mdefine_line|#define&t;sym_goalp(cp) ((cp-&gt;host_flags &amp; HF_DATA_IN) ? cp-&gt;goalp : cp-&gt;wgoalp)
macro_line|#else
DECL|macro|sym_goalp
mdefine_line|#define&t;sym_goalp(cp) (cp-&gt;goalp)
macro_line|#endif
multiline_comment|/*&n; *  Host Control Block&n; */
DECL|struct|sym_hcb
r_struct
id|sym_hcb
(brace
multiline_comment|/*&n;&t; *  Global headers.&n;&t; *  Due to poorness of addressing capabilities, earlier &n;&t; *  chips (810, 815, 825) copy part of the data structures &n;&t; *  (CCB, TCB and LCB) in fixed areas.&n;&t; */
macro_line|#if&t;SYM_CONF_GENERIC_SUPPORT
DECL|member|ccb_head
r_struct
id|sym_ccbh
id|ccb_head
suffix:semicolon
DECL|member|tcb_head
r_struct
id|sym_tcbh
id|tcb_head
suffix:semicolon
DECL|member|lcb_head
r_struct
id|sym_lcbh
id|lcb_head
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Idle task and invalid task actions and &n;&t; *  their bus addresses.&n;&t; */
DECL|member|idletask
DECL|member|notask
DECL|member|bad_itl
DECL|member|bad_itlq
r_struct
id|sym_actscr
id|idletask
comma
id|notask
comma
id|bad_itl
comma
id|bad_itlq
suffix:semicolon
DECL|member|idletask_ba
DECL|member|notask_ba
DECL|member|bad_itl_ba
DECL|member|bad_itlq_ba
id|u32
id|idletask_ba
comma
id|notask_ba
comma
id|bad_itl_ba
comma
id|bad_itlq_ba
suffix:semicolon
multiline_comment|/*&n;&t; *  Dummy lun table to protect us against target &n;&t; *  returning bad lun number on reselection.&n;&t; */
DECL|member|badluntbl
id|u32
op_star
id|badluntbl
suffix:semicolon
multiline_comment|/* Table physical address&t;*/
DECL|member|badlun_sa
id|u32
id|badlun_sa
suffix:semicolon
multiline_comment|/* SCRIPT handler BUS address&t;*/
multiline_comment|/*&n;&t; *  Bus address of this host control block.&n;&t; */
DECL|member|hcb_ba
id|u32
id|hcb_ba
suffix:semicolon
multiline_comment|/*&n;&t; *  Bit 32-63 of the on-chip RAM bus address in LE format.&n;&t; *  The START_RAM64 script loads the MMRS and MMWS from this &n;&t; *  field.&n;&t; */
DECL|member|scr_ram_seg
id|u32
id|scr_ram_seg
suffix:semicolon
multiline_comment|/*&n;&t; *  Initial value of some IO register bits.&n;&t; *  These values are assumed to have been set by BIOS, and may &n;&t; *  be used to probe adapter implementation differences.&n;&t; */
DECL|member|sv_scntl0
DECL|member|sv_scntl3
DECL|member|sv_dmode
DECL|member|sv_dcntl
DECL|member|sv_ctest3
DECL|member|sv_ctest4
id|u_char
id|sv_scntl0
comma
id|sv_scntl3
comma
id|sv_dmode
comma
id|sv_dcntl
comma
id|sv_ctest3
comma
id|sv_ctest4
comma
DECL|member|sv_ctest5
DECL|member|sv_gpcntl
DECL|member|sv_stest2
DECL|member|sv_stest4
DECL|member|sv_scntl4
id|sv_ctest5
comma
id|sv_gpcntl
comma
id|sv_stest2
comma
id|sv_stest4
comma
id|sv_scntl4
comma
DECL|member|sv_stest1
id|sv_stest1
suffix:semicolon
multiline_comment|/*&n;&t; *  Actual initial value of IO register bits used by the &n;&t; *  driver. They are loaded at initialisation according to  &n;&t; *  features that are to be enabled/disabled.&n;&t; */
DECL|member|rv_scntl0
DECL|member|rv_scntl3
DECL|member|rv_dmode
DECL|member|rv_dcntl
DECL|member|rv_ctest3
DECL|member|rv_ctest4
id|u_char
id|rv_scntl0
comma
id|rv_scntl3
comma
id|rv_dmode
comma
id|rv_dcntl
comma
id|rv_ctest3
comma
id|rv_ctest4
comma
DECL|member|rv_ctest5
DECL|member|rv_stest2
DECL|member|rv_ccntl0
DECL|member|rv_ccntl1
DECL|member|rv_scntl4
id|rv_ctest5
comma
id|rv_stest2
comma
id|rv_ccntl0
comma
id|rv_ccntl1
comma
id|rv_scntl4
suffix:semicolon
multiline_comment|/*&n;&t; *  Target data.&n;&t; */
DECL|member|target
r_struct
id|sym_tcb
id|target
(braket
id|SYM_CONF_MAX_TARGET
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *  Target control block bus address array used by the SCRIPT &n;&t; *  on reselection.&n;&t; */
DECL|member|targtbl
id|u32
op_star
id|targtbl
suffix:semicolon
DECL|member|targtbl_ba
id|u32
id|targtbl_ba
suffix:semicolon
multiline_comment|/*&n;&t; *  DMA pool handle for this HBA.&n;&t; */
macro_line|#ifdef&t;SYM_OPT_BUS_DMA_ABSTRACTION
DECL|member|bus_dmat
id|m_pool_ident_t
id|bus_dmat
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  O/S specific data structure&n;&t; */
DECL|member|s
r_struct
id|sym_shcb
id|s
suffix:semicolon
multiline_comment|/*&n;&t; *  Physical bus addresses of the chip.&n;&t; */
DECL|member|mmio_ba
id|u32
id|mmio_ba
suffix:semicolon
multiline_comment|/* MMIO 32 bit BUS address&t;*/
DECL|member|mmio_ws
r_int
id|mmio_ws
suffix:semicolon
multiline_comment|/* MMIO Window size&t;&t;*/
DECL|member|ram_ba
id|u32
id|ram_ba
suffix:semicolon
multiline_comment|/* RAM 32 bit BUS address&t;*/
DECL|member|ram_ws
r_int
id|ram_ws
suffix:semicolon
multiline_comment|/* RAM window size&t;&t;*/
multiline_comment|/*&n;&t; *  SCRIPTS virtual and physical bus addresses.&n;&t; *  &squot;script&squot;  is loaded in the on-chip RAM if present.&n;&t; *  &squot;scripth&squot; stays in main memory for all chips except the &n;&t; *  53C895A, 53C896 and 53C1010 that provide 8K on-chip RAM.&n;&t; */
DECL|member|scripta0
id|u_char
op_star
id|scripta0
suffix:semicolon
multiline_comment|/* Copy of scripts A, B, Z&t;*/
DECL|member|scriptb0
id|u_char
op_star
id|scriptb0
suffix:semicolon
DECL|member|scriptz0
id|u_char
op_star
id|scriptz0
suffix:semicolon
DECL|member|scripta_ba
id|u32
id|scripta_ba
suffix:semicolon
multiline_comment|/* Actual scripts A, B, Z&t;*/
DECL|member|scriptb_ba
id|u32
id|scriptb_ba
suffix:semicolon
multiline_comment|/* 32 bit bus addresses.&t;*/
DECL|member|scriptz_ba
id|u32
id|scriptz_ba
suffix:semicolon
DECL|member|scripta_sz
id|u_short
id|scripta_sz
suffix:semicolon
multiline_comment|/* Actual size of script A, B, Z*/
DECL|member|scriptb_sz
id|u_short
id|scriptb_sz
suffix:semicolon
DECL|member|scriptz_sz
id|u_short
id|scriptz_sz
suffix:semicolon
multiline_comment|/*&n;&t; *  Bus addresses, setup and patch methods for &n;&t; *  the selected firmware.&n;&t; */
DECL|member|fwa_bas
r_struct
id|sym_fwa_ba
id|fwa_bas
suffix:semicolon
multiline_comment|/* Useful SCRIPTA bus addresses&t;*/
DECL|member|fwb_bas
r_struct
id|sym_fwb_ba
id|fwb_bas
suffix:semicolon
multiline_comment|/* Useful SCRIPTB bus addresses&t;*/
DECL|member|fwz_bas
r_struct
id|sym_fwz_ba
id|fwz_bas
suffix:semicolon
multiline_comment|/* Useful SCRIPTZ bus addresses&t;*/
DECL|member|fw_setup
r_void
(paren
op_star
id|fw_setup
)paren
(paren
id|hcb_p
id|np
comma
r_struct
id|sym_fw
op_star
id|fw
)paren
suffix:semicolon
DECL|member|fw_patch
r_void
(paren
op_star
id|fw_patch
)paren
(paren
id|hcb_p
id|np
)paren
suffix:semicolon
DECL|member|fw_name
r_char
op_star
id|fw_name
suffix:semicolon
multiline_comment|/*&n;&t; *  General controller parameters and configuration.&n;&t; */
DECL|member|device_id
id|u_short
id|device_id
suffix:semicolon
multiline_comment|/* PCI device id&t;&t;*/
DECL|member|revision_id
id|u_char
id|revision_id
suffix:semicolon
multiline_comment|/* PCI device revision id&t;*/
DECL|member|features
id|u_int
id|features
suffix:semicolon
multiline_comment|/* Chip features map&t;&t;*/
DECL|member|myaddr
id|u_char
id|myaddr
suffix:semicolon
multiline_comment|/* SCSI id of the adapter&t;*/
DECL|member|maxburst
id|u_char
id|maxburst
suffix:semicolon
multiline_comment|/* log base 2 of dwords burst&t;*/
DECL|member|maxwide
id|u_char
id|maxwide
suffix:semicolon
multiline_comment|/* Maximum transfer width&t;*/
DECL|member|minsync
id|u_char
id|minsync
suffix:semicolon
multiline_comment|/* Min sync period factor (ST)&t;*/
DECL|member|maxsync
id|u_char
id|maxsync
suffix:semicolon
multiline_comment|/* Max sync period factor (ST)&t;*/
DECL|member|maxoffs
id|u_char
id|maxoffs
suffix:semicolon
multiline_comment|/* Max scsi offset        (ST)&t;*/
DECL|member|minsync_dt
id|u_char
id|minsync_dt
suffix:semicolon
multiline_comment|/* Min sync period factor (DT)&t;*/
DECL|member|maxsync_dt
id|u_char
id|maxsync_dt
suffix:semicolon
multiline_comment|/* Max sync period factor (DT)&t;*/
DECL|member|maxoffs_dt
id|u_char
id|maxoffs_dt
suffix:semicolon
multiline_comment|/* Max scsi offset        (DT)&t;*/
DECL|member|multiplier
id|u_char
id|multiplier
suffix:semicolon
multiline_comment|/* Clock multiplier (1,2,4)&t;*/
DECL|member|clock_divn
id|u_char
id|clock_divn
suffix:semicolon
multiline_comment|/* Number of clock divisors&t;*/
DECL|member|clock_khz
id|u32
id|clock_khz
suffix:semicolon
multiline_comment|/* SCSI clock frequency in KHz&t;*/
DECL|member|pciclk_khz
id|u32
id|pciclk_khz
suffix:semicolon
multiline_comment|/* Estimated PCI clock  in KHz&t;*/
multiline_comment|/*&n;&t; *  Start queue management.&n;&t; *  It is filled up by the host processor and accessed by the &n;&t; *  SCRIPTS processor in order to start SCSI commands.&n;&t; */
r_volatile
multiline_comment|/* Prevent code optimizations&t;*/
DECL|member|squeue
id|u32
op_star
id|squeue
suffix:semicolon
multiline_comment|/* Start queue virtual address&t;*/
DECL|member|squeue_ba
id|u32
id|squeue_ba
suffix:semicolon
multiline_comment|/* Start queue BUS address&t;*/
DECL|member|squeueput
id|u_short
id|squeueput
suffix:semicolon
multiline_comment|/* Next free slot of the queue&t;*/
DECL|member|actccbs
id|u_short
id|actccbs
suffix:semicolon
multiline_comment|/* Number of allocated CCBs&t;*/
multiline_comment|/*&n;&t; *  Command completion queue.&n;&t; *  It is the same size as the start queue to avoid overflow.&n;&t; */
DECL|member|dqueueget
id|u_short
id|dqueueget
suffix:semicolon
multiline_comment|/* Next position to scan&t;*/
r_volatile
multiline_comment|/* Prevent code optimizations&t;*/
DECL|member|dqueue
id|u32
op_star
id|dqueue
suffix:semicolon
multiline_comment|/* Completion (done) queue&t;*/
DECL|member|dqueue_ba
id|u32
id|dqueue_ba
suffix:semicolon
multiline_comment|/* Done queue BUS address&t;*/
multiline_comment|/*&n;&t; *  Miscellaneous buffers accessed by the scripts-processor.&n;&t; *  They shall be DWORD aligned, because they may be read or &n;&t; *  written with a script command.&n;&t; */
DECL|member|msgout
id|u_char
id|msgout
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Buffer for MESSAGE OUT &t;*/
DECL|member|msgin
id|u_char
id|msgin
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Buffer for MESSAGE IN&t;*/
DECL|member|lastmsg
id|u32
id|lastmsg
suffix:semicolon
multiline_comment|/* Last SCSI message sent&t;*/
DECL|member|scratch
id|u32
id|scratch
suffix:semicolon
multiline_comment|/* Scratch for SCSI receive&t;*/
multiline_comment|/* Also used for cache test &t;*/
multiline_comment|/*&n;&t; *  Miscellaneous configuration and status parameters.&n;&t; */
DECL|member|usrflags
id|u_char
id|usrflags
suffix:semicolon
multiline_comment|/* Miscellaneous user flags&t;*/
DECL|member|scsi_mode
id|u_char
id|scsi_mode
suffix:semicolon
multiline_comment|/* Current SCSI BUS mode&t;*/
DECL|member|verbose
id|u_char
id|verbose
suffix:semicolon
multiline_comment|/* Verbosity for this controller*/
multiline_comment|/*&n;&t; *  CCB lists and queue.&n;&t; */
DECL|member|ccbh
id|ccb_p
op_star
id|ccbh
suffix:semicolon
multiline_comment|/* CCBs hashed by DSA value&t;*/
multiline_comment|/* CCB_HASH_SIZE lists of CCBs&t;*/
DECL|member|free_ccbq
id|SYM_QUEHEAD
id|free_ccbq
suffix:semicolon
multiline_comment|/* Queue of available CCBs&t;*/
DECL|member|busy_ccbq
id|SYM_QUEHEAD
id|busy_ccbq
suffix:semicolon
multiline_comment|/* Queue of busy CCBs&t;&t;*/
multiline_comment|/*&n;&t; *  During error handling and/or recovery,&n;&t; *  active CCBs that are to be completed with &n;&t; *  error or requeued are moved from the busy_ccbq&n;&t; *  to the comp_ccbq prior to completion.&n;&t; */
DECL|member|comp_ccbq
id|SYM_QUEHEAD
id|comp_ccbq
suffix:semicolon
macro_line|#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
DECL|member|dummy_ccbq
id|SYM_QUEHEAD
id|dummy_ccbq
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Optional handling of IO timeouts.&n;&t; */
macro_line|#ifdef&t;SYM_OPT_HANDLE_IO_TIMEOUT
DECL|member|tmo0_ccbq
id|SYM_QUEHEAD
id|tmo0_ccbq
suffix:semicolon
DECL|member|tmo_ccbq
id|SYM_QUEHEAD
op_star
id|tmo_ccbq
suffix:semicolon
multiline_comment|/* [2*SYM_TIMEOUT_ORDER_MAX] */
DECL|member|tmo_clock
id|u_int
id|tmo_clock
suffix:semicolon
DECL|member|tmo_actq
id|u_int
id|tmo_actq
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  IMMEDIATE ARBITRATION (IARB) control.&n;&t; *&n;&t; *  We keep track in &squot;last_cp&squot; of the last CCB that has been &n;&t; *  queued to the SCRIPTS processor and clear &squot;last_cp&squot; when &n;&t; *  this CCB completes. If last_cp is not zero at the moment &n;&t; *  we queue a new CCB, we set a flag in &squot;last_cp&squot; that is &n;&t; *  used by the SCRIPTS as a hint for setting IARB.&n;&t; *  We donnot set more than &squot;iarb_max&squot; consecutive hints for &n;&t; *  IARB in order to leave devices a chance to reselect.&n;&t; *  By the way, any non zero value of &squot;iarb_max&squot; is unfair. :)&n;&t; */
macro_line|#ifdef SYM_CONF_IARB_SUPPORT
DECL|member|iarb_max
id|u_short
id|iarb_max
suffix:semicolon
multiline_comment|/* Max. # consecutive IARB hints*/
DECL|member|iarb_count
id|u_short
id|iarb_count
suffix:semicolon
multiline_comment|/* Actual # of these hints&t;*/
DECL|member|last_cp
id|ccb_p
id|last_cp
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Command abort handling.&n;&t; *  We need to synchronize tightly with the SCRIPTS &n;&t; *  processor in order to handle things correctly.&n;&t; */
DECL|member|abrt_msg
id|u_char
id|abrt_msg
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Message to send buffer&t;*/
DECL|member|abrt_tbl
r_struct
id|sym_tblmove
id|abrt_tbl
suffix:semicolon
multiline_comment|/* Table for the MOV of it &t;*/
DECL|member|abrt_sel
r_struct
id|sym_tblsel
id|abrt_sel
suffix:semicolon
multiline_comment|/* Sync params for selection&t;*/
DECL|member|istat_sem
id|u_char
id|istat_sem
suffix:semicolon
multiline_comment|/* Tells the chip to stop (SEM)&t;*/
multiline_comment|/*&n;&t; *  64 bit DMA handling.&n;&t; */
macro_line|#if&t;SYM_CONF_DMA_ADDRESSING_MODE != 0
DECL|member|use_dac
id|u_char
id|use_dac
suffix:semicolon
multiline_comment|/* Use PCI DAC cycles&t;&t;*/
macro_line|#if&t;SYM_CONF_DMA_ADDRESSING_MODE == 2
DECL|member|dmap_dirty
id|u_char
id|dmap_dirty
suffix:semicolon
multiline_comment|/* Dma segments registers dirty&t;*/
DECL|member|dmap_bah
id|u32
id|dmap_bah
(braket
id|SYM_DMAP_SIZE
)braket
suffix:semicolon
multiline_comment|/* Segment registers map&t;*/
macro_line|#endif
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|HCB_BA
mdefine_line|#define HCB_BA(np, lbl)&t;(np-&gt;hcb_ba + offsetof(struct sym_hcb, lbl))
multiline_comment|/*&n; *  NVRAM reading (sym_nvram.c).&n; */
r_void
id|sym_nvram_setup_host
(paren
id|hcb_p
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvram
)paren
suffix:semicolon
r_void
id|sym_nvram_setup_target
(paren
id|hcb_p
id|np
comma
r_int
id|target
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
suffix:semicolon
r_int
id|sym_read_nvram
(paren
id|sdev_p
id|np
comma
r_struct
id|sym_nvram
op_star
id|nvp
)paren
suffix:semicolon
multiline_comment|/*&n; *  FIRMWARES (sym_fw.c)&n; */
r_struct
id|sym_fw
op_star
id|sym_find_firmware
c_func
(paren
r_struct
id|sym_pci_chip
op_star
id|chip
)paren
suffix:semicolon
r_void
id|sym_fw_bind_script
(paren
id|hcb_p
id|np
comma
id|u32
op_star
id|start
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; *  Driver methods called from O/S specific code.&n; */
r_char
op_star
id|sym_driver_name
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sym_print_xerr
c_func
(paren
id|ccb_p
id|cp
comma
r_int
id|x_status
)paren
suffix:semicolon
r_int
id|sym_reset_scsi_bus
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|enab_int
)paren
suffix:semicolon
r_struct
id|sym_pci_chip
op_star
id|sym_lookup_pci_chip_table
(paren
id|u_short
id|device_id
comma
id|u_char
id|revision
)paren
suffix:semicolon
r_void
id|sym_put_start_queue
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
)paren
suffix:semicolon
macro_line|#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
r_void
id|sym_start_next_ccbs
c_func
(paren
id|hcb_p
id|np
comma
id|lcb_p
id|lp
comma
r_int
id|maxn
)paren
suffix:semicolon
macro_line|#endif
r_void
id|sym_start_up
(paren
id|hcb_p
id|np
comma
r_int
id|reason
)paren
suffix:semicolon
r_void
id|sym_interrupt
(paren
id|hcb_p
id|np
)paren
suffix:semicolon
r_void
id|sym_flush_comp_queue
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|cam_status
)paren
suffix:semicolon
r_int
id|sym_clear_tasks
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|cam_status
comma
r_int
id|target
comma
r_int
id|lun
comma
r_int
id|task
)paren
suffix:semicolon
id|ccb_p
id|sym_get_ccb
(paren
id|hcb_p
id|np
comma
id|u_char
id|tn
comma
id|u_char
id|ln
comma
id|u_char
id|tag_order
)paren
suffix:semicolon
r_void
id|sym_free_ccb
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
)paren
suffix:semicolon
id|lcb_p
id|sym_alloc_lcb
(paren
id|hcb_p
id|np
comma
id|u_char
id|tn
comma
id|u_char
id|ln
)paren
suffix:semicolon
r_int
id|sym_queue_scsiio
c_func
(paren
id|hcb_p
id|np
comma
id|cam_scsiio_p
id|csio
comma
id|ccb_p
id|cp
)paren
suffix:semicolon
r_int
id|sym_abort_scsiio
c_func
(paren
id|hcb_p
id|np
comma
id|cam_ccb_p
id|ccb
comma
r_int
id|timed_out
)paren
suffix:semicolon
r_int
id|sym_abort_ccb
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
r_int
id|timed_out
)paren
suffix:semicolon
r_int
id|sym_reset_scsi_target
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
)paren
suffix:semicolon
r_void
id|sym_hcb_free
c_func
(paren
id|hcb_p
id|np
)paren
suffix:semicolon
macro_line|#ifdef SYM_OPT_NVRAM_PRE_READ
r_int
id|sym_hcb_attach
c_func
(paren
id|hcb_p
id|np
comma
r_struct
id|sym_fw
op_star
id|fw
comma
r_struct
id|sym_nvram
op_star
id|nvram
)paren
suffix:semicolon
macro_line|#else
r_int
id|sym_hcb_attach
c_func
(paren
id|hcb_p
id|np
comma
r_struct
id|sym_fw
op_star
id|fw
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Optionnaly, the driver may handle IO timeouts.&n; */
macro_line|#ifdef&t;SYM_OPT_HANDLE_IO_TIMEOUT
r_int
id|sym_abort_ccb
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
r_int
id|timed_out
)paren
suffix:semicolon
r_void
id|sym_timeout_ccb
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
id|u_int
id|ticks
)paren
suffix:semicolon
DECL|function|sym_untimeout_ccb
r_static
r_void
id|__inline
id|sym_untimeout_ccb
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
)paren
(brace
id|sym_remque
c_func
(paren
op_amp
id|cp-&gt;tmo_linkq
)paren
suffix:semicolon
id|sym_insque_head
c_func
(paren
op_amp
id|cp-&gt;tmo_linkq
comma
op_amp
id|np-&gt;tmo0_ccbq
)paren
suffix:semicolon
)brace
r_void
id|sym_clock
c_func
(paren
id|hcb_p
id|np
)paren
suffix:semicolon
macro_line|#endif&t;/* SYM_OPT_HANDLE_IO_TIMEOUT */
multiline_comment|/*&n; *  Optionnaly, the driver may provide a function&n; *  to announce transfer rate changes.&n; */
macro_line|#ifdef&t;SYM_OPT_ANNOUNCE_TRANSFER_RATE
r_void
id|sym_announce_transfer_rate
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Optionnaly, the driver may sniff inquiry data.&n; */
macro_line|#ifdef&t;SYM_OPT_SNIFF_INQUIRY
DECL|macro|INQ7_CMDQ
mdefine_line|#define&t;INQ7_CMDQ&t;(0x02)
DECL|macro|INQ7_SYNC
mdefine_line|#define&t;INQ7_SYNC&t;(0x10)
DECL|macro|INQ7_WIDE16
mdefine_line|#define&t;INQ7_WIDE16&t;(0x20)
DECL|macro|INQ56_CLOCKING
mdefine_line|#define INQ56_CLOCKING&t;(3&lt;&lt;2)
DECL|macro|INQ56_ST_ONLY
mdefine_line|#define INQ56_ST_ONLY&t;(0&lt;&lt;2)
DECL|macro|INQ56_DT_ONLY
mdefine_line|#define INQ56_DT_ONLY&t;(1&lt;&lt;2)
DECL|macro|INQ56_ST_DT
mdefine_line|#define INQ56_ST_DT&t;(3&lt;&lt;2)
r_void
id|sym_update_trans_settings
c_func
(paren
id|hcb_p
id|np
comma
id|tcb_p
id|tp
)paren
suffix:semicolon
r_int
id|__sym_sniff_inquiry
c_func
(paren
id|hcb_p
id|np
comma
id|u_char
id|tn
comma
id|u_char
id|ln
comma
id|u_char
op_star
id|inq_data
comma
r_int
id|inq_len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Build a scatter/gather entry.&n; *&n; *  For 64 bit systems, we use the 8 upper bits of the size field &n; *  to provide bus address bits 32-39 to the SCRIPTS processor.&n; *  This allows the 895A, 896, 1010 to address up to 1 TB of memory.&n; */
macro_line|#if   SYM_CONF_DMA_ADDRESSING_MODE == 0
DECL|macro|sym_build_sge
mdefine_line|#define sym_build_sge(np, data, badd, len)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(data)-&gt;addr = cpu_to_scr(badd);&t;&bslash;&n;&t;(data)-&gt;size = cpu_to_scr(len);&t;&t;&bslash;&n;} while (0)
macro_line|#elif SYM_CONF_DMA_ADDRESSING_MODE == 1
DECL|macro|sym_build_sge
mdefine_line|#define sym_build_sge(np, data, badd, len)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(data)-&gt;addr = cpu_to_scr(badd);&t;&t;&t;&t;&bslash;&n;&t;(data)-&gt;size = cpu_to_scr((((badd) &gt;&gt; 8) &amp; 0xff000000) + len);&t;&bslash;&n;} while (0)
macro_line|#elif SYM_CONF_DMA_ADDRESSING_MODE == 2
r_int
id|sym_lookup_dmap
c_func
(paren
id|hcb_p
id|np
comma
id|u32
id|h
comma
r_int
id|s
)paren
suffix:semicolon
r_static
id|__inline
r_void
DECL|function|sym_build_sge
id|sym_build_sge
c_func
(paren
id|hcb_p
id|np
comma
r_struct
id|sym_tblmove
op_star
id|data
comma
id|u64
id|badd
comma
r_int
id|len
)paren
(brace
id|u32
id|h
op_assign
(paren
id|badd
op_rshift
l_int|32
)paren
suffix:semicolon
r_int
id|s
op_assign
(paren
id|h
op_amp
id|SYM_DMAP_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h
op_ne
id|np-&gt;dmap_bah
(braket
id|s
)braket
)paren
r_goto
id|bad
suffix:semicolon
id|good
suffix:colon
(paren
id|data
)paren
op_member_access_from_pointer
id|addr
op_assign
id|cpu_to_scr
c_func
(paren
id|badd
)paren
suffix:semicolon
(paren
id|data
)paren
op_member_access_from_pointer
id|size
op_assign
id|cpu_to_scr
c_func
(paren
(paren
id|s
op_lshift
l_int|24
)paren
op_plus
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bad
suffix:colon
id|s
op_assign
id|sym_lookup_dmap
c_func
(paren
id|np
comma
id|h
comma
id|s
)paren
suffix:semicolon
r_goto
id|good
suffix:semicolon
)brace
macro_line|#else
macro_line|#error &quot;Unsupported DMA addressing mode&quot;
macro_line|#endif
multiline_comment|/*&n; *  Set up data pointers used by SCRIPTS.&n; *  Called from O/S specific code.&n; */
r_static
r_void
id|__inline
DECL|function|sym_setup_data_pointers
id|sym_setup_data_pointers
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
r_int
id|dir
)paren
(brace
id|u32
id|lastp
comma
id|goalp
suffix:semicolon
multiline_comment|/*&n;&t; *  No segments means no data.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cp-&gt;segments
)paren
id|dir
op_assign
id|CAM_DIR_NONE
suffix:semicolon
multiline_comment|/*&n;&t; *  Set the data pointer.&n;&t; */
r_switch
c_cond
(paren
id|dir
)paren
(brace
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
r_case
id|CAM_DIR_UNKNOWN
suffix:colon
macro_line|#endif
r_case
id|CAM_DIR_OUT
suffix:colon
id|goalp
op_assign
id|SCRIPTA_BA
(paren
id|np
comma
id|data_out2
)paren
op_plus
l_int|8
suffix:semicolon
id|lastp
op_assign
id|goalp
op_minus
l_int|8
op_minus
(paren
id|cp-&gt;segments
op_star
(paren
l_int|2
op_star
l_int|4
)paren
)paren
suffix:semicolon
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
id|cp-&gt;wgoalp
op_assign
id|cpu_to_scr
c_func
(paren
id|goalp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_ne
id|CAM_DIR_UNKNOWN
)paren
r_break
suffix:semicolon
id|cp-&gt;phys.head.wlastp
op_assign
id|cpu_to_scr
c_func
(paren
id|lastp
)paren
suffix:semicolon
multiline_comment|/* fall through */
macro_line|#else
r_break
suffix:semicolon
macro_line|#endif
r_case
id|CAM_DIR_IN
suffix:colon
id|cp-&gt;host_flags
op_or_assign
id|HF_DATA_IN
suffix:semicolon
id|goalp
op_assign
id|SCRIPTA_BA
(paren
id|np
comma
id|data_in2
)paren
op_plus
l_int|8
suffix:semicolon
id|lastp
op_assign
id|goalp
op_minus
l_int|8
op_minus
(paren
id|cp-&gt;segments
op_star
(paren
l_int|2
op_star
l_int|4
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CAM_DIR_NONE
suffix:colon
r_default
suffix:colon
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
id|cp-&gt;host_flags
op_or_assign
id|HF_DATA_IN
suffix:semicolon
macro_line|#endif
id|lastp
op_assign
id|goalp
op_assign
id|SCRIPTB_BA
(paren
id|np
comma
id|no_data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Set all pointers values needed by SCRIPTS.&n;&t; */
id|cp-&gt;phys.head.lastp
op_assign
id|cpu_to_scr
c_func
(paren
id|lastp
)paren
suffix:semicolon
id|cp-&gt;phys.head.savep
op_assign
id|cpu_to_scr
c_func
(paren
id|lastp
)paren
suffix:semicolon
id|cp-&gt;startp
op_assign
id|cp-&gt;phys.head.savep
suffix:semicolon
id|cp-&gt;goalp
op_assign
id|cpu_to_scr
c_func
(paren
id|goalp
)paren
suffix:semicolon
macro_line|#ifdef&t;SYM_OPT_HANDLE_DIR_UNKNOWN
multiline_comment|/*&n;&t; *  If direction is unknown, start at data_io.&n;&t; */
r_if
c_cond
(paren
id|dir
op_eq
id|CAM_DIR_UNKNOWN
)paren
id|cp-&gt;phys.head.savep
op_assign
id|cpu_to_scr
c_func
(paren
id|SCRIPTB_BA
(paren
id|np
comma
id|data_io
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *  MEMORY ALLOCATOR.&n; */
multiline_comment|/*&n; *  Shortest memory chunk is (1&lt;&lt;SYM_MEM_SHIFT), currently 16.&n; *  Actual allocations happen as SYM_MEM_CLUSTER_SIZE sized.&n; *  (1 PAGE at a time is just fine).&n; */
DECL|macro|SYM_MEM_SHIFT
mdefine_line|#define SYM_MEM_SHIFT&t;4
DECL|macro|SYM_MEM_CLUSTER_SIZE
mdefine_line|#define SYM_MEM_CLUSTER_SIZE&t;(1UL &lt;&lt; SYM_MEM_CLUSTER_SHIFT)
DECL|macro|SYM_MEM_CLUSTER_MASK
mdefine_line|#define SYM_MEM_CLUSTER_MASK&t;(SYM_MEM_CLUSTER_SIZE-1)
multiline_comment|/*&n; *  Link between free memory chunks of a given size.&n; */
DECL|struct|sym_m_link
r_typedef
r_struct
id|sym_m_link
(brace
DECL|member|next
r_struct
id|sym_m_link
op_star
id|next
suffix:semicolon
DECL|typedef|m_link_p
)brace
op_star
id|m_link_p
suffix:semicolon
multiline_comment|/*&n; *  Virtual to bus physical translation for a given cluster.&n; *  Such a structure is only useful with DMA abstraction.&n; */
macro_line|#ifdef&t;SYM_OPT_BUS_DMA_ABSTRACTION
DECL|struct|sym_m_vtob
r_typedef
r_struct
id|sym_m_vtob
(brace
multiline_comment|/* Virtual to Bus address translation */
DECL|member|next
r_struct
id|sym_m_vtob
op_star
id|next
suffix:semicolon
macro_line|#ifdef&t;SYM_HAVE_M_SVTOB
DECL|member|s
r_struct
id|sym_m_svtob
id|s
suffix:semicolon
multiline_comment|/* OS specific data structure */
macro_line|#endif
DECL|member|vaddr
id|m_addr_t
id|vaddr
suffix:semicolon
multiline_comment|/* Virtual address */
DECL|member|baddr
id|m_addr_t
id|baddr
suffix:semicolon
multiline_comment|/* Bus physical address */
DECL|typedef|m_vtob_p
)brace
op_star
id|m_vtob_p
suffix:semicolon
multiline_comment|/* Hash this stuff a bit to speed up translations */
DECL|macro|VTOB_HASH_SHIFT
mdefine_line|#define VTOB_HASH_SHIFT&t;&t;5
DECL|macro|VTOB_HASH_SIZE
mdefine_line|#define VTOB_HASH_SIZE&t;&t;(1UL &lt;&lt; VTOB_HASH_SHIFT)
DECL|macro|VTOB_HASH_MASK
mdefine_line|#define VTOB_HASH_MASK&t;&t;(VTOB_HASH_SIZE-1)
DECL|macro|VTOB_HASH_CODE
mdefine_line|#define VTOB_HASH_CODE(m)&t;&bslash;&n;&t;((((m_addr_t) (m)) &gt;&gt; SYM_MEM_CLUSTER_SHIFT) &amp; VTOB_HASH_MASK)
macro_line|#endif&t;/* SYM_OPT_BUS_DMA_ABSTRACTION */
multiline_comment|/*&n; *  Memory pool of a given kind.&n; *  Ideally, we want to use:&n; *  1) 1 pool for memory we donnot need to involve in DMA.&n; *  2) The same pool for controllers that require same DMA &n; *     constraints and features.&n; *     The OS specific m_pool_id_t thing and the sym_m_pool_match() &n; *     method are expected to tell the driver about.&n; */
DECL|struct|sym_m_pool
r_typedef
r_struct
id|sym_m_pool
(brace
macro_line|#ifdef&t;SYM_OPT_BUS_DMA_ABSTRACTION
DECL|member|dev_dmat
id|m_pool_ident_t
id|dev_dmat
suffix:semicolon
multiline_comment|/* Identifies the pool (see above) */
DECL|member|get_mem_cluster
id|m_addr_t
(paren
op_star
id|get_mem_cluster
)paren
(paren
r_struct
id|sym_m_pool
op_star
)paren
suffix:semicolon
macro_line|#ifdef&t;SYM_MEM_FREE_UNUSED
DECL|member|free_mem_cluster
r_void
(paren
op_star
id|free_mem_cluster
)paren
(paren
r_struct
id|sym_m_pool
op_star
comma
id|m_addr_t
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|M_GET_MEM_CLUSTER
mdefine_line|#define M_GET_MEM_CLUSTER()&t;&t;mp-&gt;get_mem_cluster(mp)
DECL|macro|M_FREE_MEM_CLUSTER
mdefine_line|#define M_FREE_MEM_CLUSTER(p)&t;&t;mp-&gt;free_mem_cluster(mp, p)
macro_line|#ifdef&t;SYM_HAVE_M_SPOOL
DECL|member|s
r_struct
id|sym_m_spool
id|s
suffix:semicolon
multiline_comment|/* OS specific data structure */
macro_line|#endif
DECL|member|nump
r_int
id|nump
suffix:semicolon
DECL|member|vtob
id|m_vtob_p
id|vtob
(braket
id|VTOB_HASH_SIZE
)braket
suffix:semicolon
DECL|member|next
r_struct
id|sym_m_pool
op_star
id|next
suffix:semicolon
macro_line|#else
mdefine_line|#define M_GET_MEM_CLUSTER()&t;&t;sym_get_mem_cluster()
mdefine_line|#define M_FREE_MEM_CLUSTER(p)&t;&t;sym_free_mem_cluster(p)
macro_line|#endif&t;/* SYM_OPT_BUS_DMA_ABSTRACTION */
DECL|member|h
r_struct
id|sym_m_link
id|h
(braket
id|SYM_MEM_CLUSTER_SHIFT
op_minus
id|SYM_MEM_SHIFT
op_plus
l_int|1
)braket
suffix:semicolon
DECL|typedef|m_pool_p
)brace
op_star
id|m_pool_p
suffix:semicolon
multiline_comment|/*&n; *  Alloc and free non DMAable memory.&n; */
r_void
id|sym_mfree_unlocked
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
op_star
id|sym_calloc_unlocked
c_func
(paren
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/*&n; *  Alloc, free and translate addresses to bus physical &n; *  for DMAable memory.&n; */
macro_line|#ifdef&t;SYM_OPT_BUS_DMA_ABSTRACTION
r_void
op_star
id|__sym_calloc_dma_unlocked
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|__sym_mfree_dma_unlocked
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_void
op_star
id|m
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
id|u32
id|__vtobus_unlocked
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_void
op_star
id|m
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Verbs used by the driver code for DMAable memory handling.&n; * The _uvptv_ macro avoids a nasty warning about pointer to volatile &n; * being discarded.&n; */
DECL|macro|_uvptv_
mdefine_line|#define _uvptv_(p) ((void *)((u_long)(p)))
DECL|macro|_sym_calloc_dma
mdefine_line|#define _sym_calloc_dma(np, l, n)&t;__sym_calloc_dma(np-&gt;bus_dmat, l, n)
DECL|macro|_sym_mfree_dma
mdefine_line|#define _sym_mfree_dma(np, p, l, n)&t;&bslash;&n;&t;&t;&t;__sym_mfree_dma(np-&gt;bus_dmat, _uvptv_(p), l, n)
DECL|macro|sym_calloc_dma
mdefine_line|#define sym_calloc_dma(l, n)&t;&t;_sym_calloc_dma(np, l, n)
DECL|macro|sym_mfree_dma
mdefine_line|#define sym_mfree_dma(p, l, n)&t;&t;_sym_mfree_dma(np, p, l, n)
DECL|macro|_vtobus
mdefine_line|#define _vtobus(np, p)&t;&t;&t;__vtobus(np-&gt;bus_dmat, _uvptv_(p))
DECL|macro|vtobus
mdefine_line|#define vtobus(p)&t;&t;&t;_vtobus(np, p)
multiline_comment|/*&n; *  Override some function names.&n; */
DECL|macro|PRINT_ADDR
mdefine_line|#define PRINT_ADDR&t;sym_print_addr
DECL|macro|PRINT_TARGET
mdefine_line|#define PRINT_TARGET&t;sym_print_target
DECL|macro|PRINT_LUN
mdefine_line|#define PRINT_LUN&t;sym_print_lun
DECL|macro|MDELAY
mdefine_line|#define MDELAY&t;&t;sym_mdelay
DECL|macro|UDELAY
mdefine_line|#define UDELAY&t;&t;sym_udelay
macro_line|#endif /* SYM_HIPD_H */
eof
