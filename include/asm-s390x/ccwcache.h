multiline_comment|/* &n;   * File...........: linux/include/asm-s390/ccwcache.h&n;   * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n;   * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n;   * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 2000&n; */
macro_line|#ifndef CCWCACHE_H
DECL|macro|CCWCACHE_H
mdefine_line|#define CCWCACHE_H
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifndef __KERNEL__
DECL|macro|kmem_cache_t
mdefine_line|#define kmem_cache_t void
macro_line|#endif /* __KERNEL__ */
DECL|struct|ccw_req_t
r_typedef
r_struct
id|ccw_req_t
(brace
multiline_comment|/* eye catcher plus queueing information  */
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|next
r_struct
id|ccw_req_t
op_star
id|next
suffix:semicolon
multiline_comment|/* pointer to next ccw_req_t in queue */
DECL|member|int_next
r_struct
id|ccw_req_t
op_star
id|int_next
suffix:semicolon
multiline_comment|/* for internal queueing */
DECL|member|int_prev
r_struct
id|ccw_req_t
op_star
id|int_prev
suffix:semicolon
multiline_comment|/* for internal queueing */
multiline_comment|/* Where to execute what... */
DECL|member|device
r_void
op_star
id|device
suffix:semicolon
multiline_comment|/* index of the device the req is for */
DECL|member|req
r_void
op_star
id|req
suffix:semicolon
multiline_comment|/* pointer to originating request */
DECL|member|cpaddr
id|ccw1_t
op_star
id|cpaddr
suffix:semicolon
multiline_comment|/* address of channel program */
DECL|member|status
r_char
id|status
suffix:semicolon
multiline_comment|/* reflecting the status of this request */
DECL|member|flags
r_char
id|flags
suffix:semicolon
multiline_comment|/* see below */
DECL|member|retries
r_int
id|retries
suffix:semicolon
multiline_comment|/* A retry counter to be set when filling */
multiline_comment|/* ... and how */
DECL|member|options
r_int
id|options
suffix:semicolon
multiline_comment|/* options for execution */
DECL|member|lpm
r_char
id|lpm
suffix:semicolon
multiline_comment|/* logical path mask                      */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* pointer to data area */
DECL|member|dstat
id|devstat_t
op_star
id|dstat
suffix:semicolon
multiline_comment|/* The device status in case of an error */
multiline_comment|/* these are important for recovering erroneous requests          */
DECL|member|refers
r_struct
id|ccw_req_t
op_star
id|refers
suffix:semicolon
multiline_comment|/* Does this request refer to another one? */
DECL|member|function
r_void
op_star
id|function
suffix:semicolon
multiline_comment|/* refers to the originating ERP action */
suffix:semicolon
DECL|member|expires
r_int
r_int
r_int
id|expires
suffix:semicolon
multiline_comment|/* expiratioj period */
multiline_comment|/* these are for profiling purposes */
DECL|member|buildclk
r_int
r_int
r_int
id|buildclk
suffix:semicolon
multiline_comment|/* TOD-clock of request generation */
DECL|member|startclk
r_int
r_int
r_int
id|startclk
suffix:semicolon
multiline_comment|/* TOD-clock of request start */
DECL|member|stopclk
r_int
r_int
r_int
id|stopclk
suffix:semicolon
multiline_comment|/* TOD-clock of request interrupt */
DECL|member|endclk
r_int
r_int
r_int
id|endclk
suffix:semicolon
multiline_comment|/* TOD-clock of request termination */
multiline_comment|/* these are for internal use */
DECL|member|cplength
r_int
id|cplength
suffix:semicolon
multiline_comment|/* length of the channel program in CCWs */
DECL|member|datasize
r_int
id|datasize
suffix:semicolon
multiline_comment|/* amount of additional data in bytes */
DECL|member|cache
id|kmem_cache_t
op_star
id|cache
suffix:semicolon
multiline_comment|/* the cache this data comes from */
DECL|typedef|ccw_req_t
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|ccw_req_t
suffix:semicolon
multiline_comment|/* &n; * ccw_req_t -&gt; status can be:&n; */
DECL|macro|CQR_STATUS_EMPTY
mdefine_line|#define CQR_STATUS_EMPTY    0x00&t;/* request is empty */
DECL|macro|CQR_STATUS_FILLED
mdefine_line|#define CQR_STATUS_FILLED   0x01&t;/* request is ready to be preocessed */
DECL|macro|CQR_STATUS_QUEUED
mdefine_line|#define CQR_STATUS_QUEUED   0x02&t;/* request is queued to be processed */
DECL|macro|CQR_STATUS_IN_IO
mdefine_line|#define CQR_STATUS_IN_IO    0x03&t;/* request is currently in IO */
DECL|macro|CQR_STATUS_DONE
mdefine_line|#define CQR_STATUS_DONE     0x04&t;/* request is completed sucessfully */
DECL|macro|CQR_STATUS_ERROR
mdefine_line|#define CQR_STATUS_ERROR    0x05&t;/* request is completed with error */
DECL|macro|CQR_STATUS_FAILED
mdefine_line|#define CQR_STATUS_FAILED   0x06&t;/* request is finally failed */
DECL|macro|CQR_FLAGS_CHAINED
mdefine_line|#define CQR_FLAGS_CHAINED  0x01&t;/* request is chained by another (last CCW is TIC) */
macro_line|#ifdef __KERNEL__
DECL|macro|SMALLEST_SLAB
mdefine_line|#define SMALLEST_SLAB (sizeof(struct ccw_req_t) &lt;= 128 ? 128 :&bslash;&n; sizeof(struct ccw_req_t) &lt;= 256 ? 256 : 512 )
multiline_comment|/* SMALLEST_SLAB(1),... PAGE_SIZE(CCW_NUMBER_CACHES) */
DECL|macro|CCW_NUMBER_CACHES
mdefine_line|#define CCW_NUMBER_CACHES (sizeof(struct ccw_req_t) &lt;= 128 ? 6 :&bslash;&n; sizeof(struct ccw_req_t) &lt;= 256 ? 5 : 4 )
r_int
id|ccwcache_init
(paren
r_void
)paren
suffix:semicolon
id|ccw_req_t
op_star
id|ccw_alloc_request
(paren
r_char
op_star
id|magic
comma
r_int
id|cplength
comma
r_int
id|additional_data
)paren
suffix:semicolon
r_void
id|ccw_free_request
(paren
id|ccw_req_t
op_star
id|request
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* CCWCACHE_H */
eof
