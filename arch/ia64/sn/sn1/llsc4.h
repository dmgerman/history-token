multiline_comment|/* &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Jack Steiner (steiner@sgi.com)&n; */
macro_line|#ifdef STANDALONE
macro_line|#include &quot;lock.h&quot;
macro_line|#endif
DECL|macro|DEF_NAPTICKS
mdefine_line|#define DEF_NAPTICKS&t;&t;0
DECL|macro|DEF_PASSES
mdefine_line|#define DEF_PASSES&t;&t;0
DECL|macro|DEF_AUTO_PASSES
mdefine_line|#define DEF_AUTO_PASSES&t;&t;1000000
DECL|macro|DEF_STOP_ON_ERROR
mdefine_line|#define DEF_STOP_ON_ERROR&t;1
DECL|macro|DEF_VERBOSE
mdefine_line|#define DEF_VERBOSE&t;&t;0
DECL|macro|DEF_LINECOUNT
mdefine_line|#define DEF_LINECOUNT&t;&t;2
DECL|macro|DEF_ITER_MSG
mdefine_line|#define DEF_ITER_MSG&t;&t;0
DECL|macro|DEF_VV
mdefine_line|#define DEF_VV&t;&t;&t;0xffffffff
DECL|macro|DEF_LINEPAD
mdefine_line|#define DEF_LINEPAD&t;&t;0x234
DECL|macro|MAXCPUS
mdefine_line|#define MAXCPUS&t;&t;&t;16
DECL|macro|CACHELINE
mdefine_line|#define CACHELINE&t;&t;64
DECL|macro|MAX_LINECOUNT
mdefine_line|#define MAX_LINECOUNT&t;&t;1024
DECL|macro|K
mdefine_line|#define K&t;&t;&t;1024
DECL|macro|MB
mdefine_line|#define&t;MB&t;&t;&t;(K*K)
DECL|macro|uint
mdefine_line|#define&t;uint &t;&t;unsigned int
DECL|macro|ushort
mdefine_line|#define&t;ushort&t;&t;unsigned short
DECL|macro|vint
mdefine_line|#define vint&t;&t;volatile int
DECL|macro|vlong
mdefine_line|#define vlong&t;&t;volatile long
DECL|macro|LOCKADDR
mdefine_line|#define LOCKADDR(i)&t;&amp;linep-&gt;lock[(i)]
DECL|macro|LOCK
mdefine_line|#define LOCK(i)&t;&t;set_lock(LOCKADDR(i), lockpat)
DECL|macro|UNLOCK
mdefine_line|#define UNLOCK(i)&t;clr_lock(LOCKADDR(i), lockpat)
DECL|macro|GETLOCK
mdefine_line|#define GETLOCK(i)&t;*LOCKADDR(i)
DECL|macro|ZEROLOCK
mdefine_line|#define ZEROLOCK(i)&t;zero_lock(LOCKADDR(i))
DECL|macro|CACHEALIGN
mdefine_line|#define CACHEALIGN(a)&t;((void*)((long)(a) &amp; ~127L))
DECL|typedef|lock_t
r_typedef
id|uint
id|lock_t
suffix:semicolon
DECL|typedef|share_t
r_typedef
id|uint
id|share_t
suffix:semicolon
DECL|typedef|private_t
r_typedef
id|uint
id|private_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lock
id|lock_t
id|lock
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|share
id|share_t
id|share
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|private
id|private_t
r_private
(braket
id|MAXCPUS
)braket
suffix:semicolon
DECL|member|share0
id|share_t
id|share0
suffix:semicolon
DECL|member|share1
id|share_t
id|share1
suffix:semicolon
DECL|typedef|dataline_t
)brace
id|dataline_t
suffix:semicolon
DECL|macro|LINEPAD
mdefine_line|#define LINEPAD&t;&t;&t;k_linepad
DECL|macro|LINESTRIDE
mdefine_line|#define LINESTRIDE&t;&t;(((sizeof(dataline_t)+CACHELINE-1)/CACHELINE)*CACHELINE + LINEPAD)
r_typedef
r_struct
(brace
DECL|member|threadstate
id|vint
id|threadstate
suffix:semicolon
DECL|member|threadpasses
id|uint
id|threadpasses
suffix:semicolon
DECL|member|private
id|private_t
r_private
(braket
id|MAX_LINECOUNT
)braket
suffix:semicolon
DECL|typedef|threadprivate_t
)brace
id|threadprivate_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|sk_go
id|vlong
id|sk_go
suffix:semicolon
multiline_comment|/* 0=idle, 1=init, 2=run */
DECL|member|sk_linecount
r_int
id|sk_linecount
suffix:semicolon
DECL|member|sk_passes
r_int
id|sk_passes
suffix:semicolon
DECL|member|sk_napticks
r_int
id|sk_napticks
suffix:semicolon
DECL|member|sk_stop_on_error
r_int
id|sk_stop_on_error
suffix:semicolon
DECL|member|sk_verbose
r_int
id|sk_verbose
suffix:semicolon
DECL|member|sk_iter_msg
r_int
id|sk_iter_msg
suffix:semicolon
DECL|member|sk_vv
r_int
id|sk_vv
suffix:semicolon
DECL|member|sk_linepad
r_int
id|sk_linepad
suffix:semicolon
DECL|member|sk_options
r_int
id|sk_options
suffix:semicolon
DECL|member|sk_testnumber
r_int
id|sk_testnumber
suffix:semicolon
DECL|member|sk_currentpass
id|vlong
id|sk_currentpass
suffix:semicolon
DECL|member|sk_blocks
r_void
op_star
id|sk_blocks
suffix:semicolon
DECL|member|sk_threadprivate
id|threadprivate_t
op_star
id|sk_threadprivate
(braket
id|MAXCPUS
)braket
suffix:semicolon
DECL|typedef|control_t
)brace
id|control_t
suffix:semicolon
multiline_comment|/* Run state (k_go) constants */
DECL|macro|ST_IDLE
mdefine_line|#define ST_IDLE&t;&t;0
DECL|macro|ST_INIT
mdefine_line|#define ST_INIT&t;&t;1
DECL|macro|ST_RUN
mdefine_line|#define ST_RUN&t;&t;2
DECL|macro|ST_STOP
mdefine_line|#define ST_STOP&t;&t;3
DECL|macro|ST_ERRSTOP
mdefine_line|#define ST_ERRSTOP&t;4
multiline_comment|/* Threadstate constants */
DECL|macro|TS_STOPPED
mdefine_line|#define TS_STOPPED&t;0
DECL|macro|TS_RUNNING
mdefine_line|#define&t;TS_RUNNING&t;1
DECL|macro|TS_KILLED
mdefine_line|#define TS_KILLED&t;2
r_int
id|llsc_main
(paren
r_int
id|cpuid
comma
r_int
id|mbasex
)paren
suffix:semicolon
eof
