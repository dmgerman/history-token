multiline_comment|/*&n; * linux/include/nfsd/stats.h&n; *&n; * Statistics for NFS server.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_NFSD_STATS_H
DECL|macro|LINUX_NFSD_STATS_H
mdefine_line|#define LINUX_NFSD_STATS_H
DECL|struct|nfsd_stats
r_struct
id|nfsd_stats
(brace
DECL|member|rchits
r_int
r_int
id|rchits
suffix:semicolon
multiline_comment|/* repcache hits */
DECL|member|rcmisses
r_int
r_int
id|rcmisses
suffix:semicolon
multiline_comment|/* repcache hits */
DECL|member|rcnocache
r_int
r_int
id|rcnocache
suffix:semicolon
multiline_comment|/* uncached reqs */
DECL|member|fh_stale
r_int
r_int
id|fh_stale
suffix:semicolon
multiline_comment|/* FH stale error */
DECL|member|fh_lookup
r_int
r_int
id|fh_lookup
suffix:semicolon
multiline_comment|/* dentry cached */
DECL|member|fh_anon
r_int
r_int
id|fh_anon
suffix:semicolon
multiline_comment|/* anon file dentry returned */
DECL|member|fh_nocache_dir
r_int
r_int
id|fh_nocache_dir
suffix:semicolon
multiline_comment|/* filehandle not found in dcache */
DECL|member|fh_nocache_nondir
r_int
r_int
id|fh_nocache_nondir
suffix:semicolon
multiline_comment|/* filehandle not found in dcache */
DECL|member|io_read
r_int
r_int
id|io_read
suffix:semicolon
multiline_comment|/* bytes returned to read requests */
DECL|member|io_write
r_int
r_int
id|io_write
suffix:semicolon
multiline_comment|/* bytes passed in write requests */
DECL|member|th_cnt
r_int
r_int
id|th_cnt
suffix:semicolon
multiline_comment|/* number of available threads */
DECL|member|th_usage
r_int
r_int
id|th_usage
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* number of ticks during which n perdeciles&n;&t;&t;&t;&t;&t; * of available threads were in use */
DECL|member|th_fullcnt
r_int
r_int
id|th_fullcnt
suffix:semicolon
multiline_comment|/* number of times last free thread was used */
DECL|member|ra_size
r_int
r_int
id|ra_size
suffix:semicolon
multiline_comment|/* size of ra cache */
DECL|member|ra_depth
r_int
r_int
id|ra_depth
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* number of times ra entry was found that deep&n;&t;&t;&t;&t;&t; * in the cache (10percentiles). [10] = not found */
)brace
suffix:semicolon
multiline_comment|/* thread usage wraps very million seconds (approx one fortnight) */
DECL|macro|NFSD_USAGE_WRAP
mdefine_line|#define&t;NFSD_USAGE_WRAP&t;(HZ*1000000)
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|nfsd_stats
id|nfsdstats
suffix:semicolon
r_extern
r_struct
id|svc_stat
id|nfsd_svcstats
suffix:semicolon
r_void
id|nfsd_stat_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_stat_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_NFSD_STATS_H */
eof
