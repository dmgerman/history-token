multiline_comment|/*&n; *&t;A filtering function.  There are two filters/port.  Filter &quot;0&quot;&n; *&t;is the input filter, and filter &quot;1&quot; is the output filter.&n; */
DECL|typedef|FILTER_FUNC
r_typedef
r_int
(paren
id|FILTER_FUNC
)paren
(paren
id|uchar
op_star
id|pktp
comma
r_int
id|pktlen
comma
id|ulong
op_star
id|scratch
comma
r_int
id|port
)paren
suffix:semicolon
DECL|macro|NFILTERS
mdefine_line|#define&t;NFILTERS&t;2
multiline_comment|/*&n; *&t;The per port structure&n; */
r_typedef
r_struct
(brace
DECL|member|chan
r_int
id|chan
suffix:semicolon
multiline_comment|/* Channel number (0-3) */
DECL|member|portaddr
id|ulong
id|portaddr
suffix:semicolon
multiline_comment|/* address of 596 port register */
DECL|member|ca
r_volatile
id|ulong
op_star
id|ca
suffix:semicolon
multiline_comment|/* address of 596 chan attention */
DECL|member|intmask
id|ulong
id|intmask
suffix:semicolon
multiline_comment|/* Interrupt mask for this port */
DECL|member|intack
id|ulong
id|intack
suffix:semicolon
multiline_comment|/* Ack bit for this port */
DECL|member|ethaddr
id|uchar
id|ethaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet address of this port */
DECL|member|is_promisc
r_int
id|is_promisc
suffix:semicolon
multiline_comment|/* Port is promiscuous */
DECL|member|debug
r_int
id|debug
suffix:semicolon
multiline_comment|/* Debugging turned on */
DECL|member|iscpp
id|I596_ISCP
op_star
id|iscpp
suffix:semicolon
multiline_comment|/* Uncached ISCP pointer */
DECL|member|scpp
id|I596_SCP
op_star
id|scpp
suffix:semicolon
multiline_comment|/* Uncached SCP pointer */
DECL|member|scbp
id|I596_SCB
op_star
id|scbp
suffix:semicolon
multiline_comment|/* Uncached SCB pointer */
DECL|member|iscp
id|I596_ISCP
id|iscp
suffix:semicolon
DECL|member|scb
id|I596_SCB
id|scb
suffix:semicolon
multiline_comment|/* Command Queue */
DECL|member|cb0
id|I596_CB
op_star
id|cb0
suffix:semicolon
DECL|member|cbN
id|I596_CB
op_star
id|cbN
suffix:semicolon
DECL|member|cb_head
id|I596_CB
op_star
id|cb_head
suffix:semicolon
DECL|member|cb_tail
id|I596_CB
op_star
id|cb_tail
suffix:semicolon
multiline_comment|/* Receive Queue */
DECL|member|rfd0
id|I596_RFD
op_star
id|rfd0
suffix:semicolon
DECL|member|rfdN
id|I596_RFD
op_star
id|rfdN
suffix:semicolon
DECL|member|rfd_head
id|I596_RFD
op_star
id|rfd_head
suffix:semicolon
DECL|member|rfd_tail
id|I596_RFD
op_star
id|rfd_tail
suffix:semicolon
multiline_comment|/* Receive Buffers */
DECL|member|rbd0
id|I596_RBD
op_star
id|rbd0
suffix:semicolon
DECL|member|rbdN
id|I596_RBD
op_star
id|rbdN
suffix:semicolon
DECL|member|rbd_head
id|I596_RBD
op_star
id|rbd_head
suffix:semicolon
DECL|member|rbd_tail
id|I596_RBD
op_star
id|rbd_tail
suffix:semicolon
DECL|member|buf_size
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* Size of an RBD buffer */
DECL|member|buf_cnt
r_int
id|buf_cnt
suffix:semicolon
multiline_comment|/* Total RBD&squot;s allocated */
multiline_comment|/* Rx Statistics */
DECL|member|cnt_rx_cnt
id|ulong
id|cnt_rx_cnt
suffix:semicolon
multiline_comment|/* Total packets rcvd, good and bad */
DECL|member|cnt_rx_good
id|ulong
id|cnt_rx_good
suffix:semicolon
multiline_comment|/* Total good packets rcvd */
DECL|member|cnt_rx_bad
id|ulong
id|cnt_rx_bad
suffix:semicolon
multiline_comment|/* Total of all bad packets rcvd */
multiline_comment|/* Subtotals can be gotten from SCB */
DECL|member|cnt_rx_nores
id|ulong
id|cnt_rx_nores
suffix:semicolon
multiline_comment|/* No resources */
DECL|member|cnt_rx_bytes
id|ulong
id|cnt_rx_bytes
suffix:semicolon
multiline_comment|/* Total bytes rcvd */
multiline_comment|/* Tx Statistics */
DECL|member|cnt_tx_queued
id|ulong
id|cnt_tx_queued
suffix:semicolon
DECL|member|cnt_tx_done
id|ulong
id|cnt_tx_done
suffix:semicolon
DECL|member|cnt_tx_freed
id|ulong
id|cnt_tx_freed
suffix:semicolon
DECL|member|cnt_tx_nores
id|ulong
id|cnt_tx_nores
suffix:semicolon
multiline_comment|/* No resources */
DECL|member|cnt_tx_bad
id|ulong
id|cnt_tx_bad
suffix:semicolon
DECL|member|cnt_tx_err_late
id|ulong
id|cnt_tx_err_late
suffix:semicolon
DECL|member|cnt_tx_err_nocrs
id|ulong
id|cnt_tx_err_nocrs
suffix:semicolon
DECL|member|cnt_tx_err_nocts
id|ulong
id|cnt_tx_err_nocts
suffix:semicolon
DECL|member|cnt_tx_err_under
id|ulong
id|cnt_tx_err_under
suffix:semicolon
DECL|member|cnt_tx_err_maxcol
id|ulong
id|cnt_tx_err_maxcol
suffix:semicolon
DECL|member|cnt_tx_collisions
id|ulong
id|cnt_tx_collisions
suffix:semicolon
multiline_comment|/* Special stuff for host */
DECL|macro|rfd_freed
macro_line|#&t;define&t;&t;rfd_freed&t;cnt_rx_cnt
DECL|member|rbd_freed
id|ulong
id|rbd_freed
suffix:semicolon
DECL|member|host_timer
r_int
id|host_timer
suffix:semicolon
multiline_comment|/* Added after first beta */
DECL|member|cnt_tx_races
id|ulong
id|cnt_tx_races
suffix:semicolon
multiline_comment|/* Counts race conditions */
DECL|member|spanstate
r_int
id|spanstate
suffix:semicolon
DECL|member|cnt_st_tx
id|ulong
id|cnt_st_tx
suffix:semicolon
multiline_comment|/* send span tree pkts */
DECL|member|cnt_st_fail_tx
id|ulong
id|cnt_st_fail_tx
suffix:semicolon
multiline_comment|/* Failures to send span tree pkts */
DECL|member|cnt_st_fail_rbd
id|ulong
id|cnt_st_fail_rbd
suffix:semicolon
multiline_comment|/* Failures to send span tree pkts */
DECL|member|cnt_st_rx
id|ulong
id|cnt_st_rx
suffix:semicolon
multiline_comment|/* rcv span tree pkts */
DECL|member|cnt_st_rx_bad
id|ulong
id|cnt_st_rx_bad
suffix:semicolon
multiline_comment|/* bogus st packets rcvd */
DECL|member|cnt_rx_fwd
id|ulong
id|cnt_rx_fwd
suffix:semicolon
multiline_comment|/* Rcvd packets that were forwarded */
DECL|member|cnt_rx_mcast
id|ulong
id|cnt_rx_mcast
suffix:semicolon
multiline_comment|/* Multicast pkts received */
DECL|member|cnt_tx_mcast
id|ulong
id|cnt_tx_mcast
suffix:semicolon
multiline_comment|/* Multicast pkts transmitted */
DECL|member|cnt_tx_bytes
id|ulong
id|cnt_tx_bytes
suffix:semicolon
multiline_comment|/* Bytes transmitted */
multiline_comment|/*&n;&t; *&t;Packet filtering&n;&t; *&t;Filter 0: input filter&n;&t; *&t;Filter 1: output filter&n;&t; */
DECL|member|filter_space
id|ulong
op_star
id|filter_space
(braket
id|NFILTERS
)braket
suffix:semicolon
DECL|member|filter_func
id|FILTER_FUNC
op_star
id|filter_func
(braket
id|NFILTERS
)braket
suffix:semicolon
DECL|member|filter_cnt
id|ulong
id|filter_cnt
(braket
id|NFILTERS
)braket
suffix:semicolon
DECL|member|filter_len
id|ulong
id|filter_len
(braket
id|NFILTERS
)braket
suffix:semicolon
DECL|member|pad
id|ulong
id|pad
(braket
(paren
l_int|512
op_minus
l_int|300
)paren
op_div
l_int|4
)braket
suffix:semicolon
DECL|typedef|PORT
)brace
id|PORT
suffix:semicolon
multiline_comment|/*&n; *&t;Port[0]&t;&t;&t;is host interface&n; *&t;Port[1..SE_NPORTS]&t;are external 10 Base T ports.  Fewer may be in&n; *&t;&t;&t;&t;use, depending on whether this is an SE-4 or&n; *&t;&t;&t;&t;an SE-6.&n; *&t;Port[SE_NPORTS]&t;&t;Pseudo-port for Spanning tree and SNMP&n; */
r_extern
id|PORT
id|Port
(braket
l_int|1
op_plus
id|SE_NPORTS
op_plus
l_int|1
)braket
suffix:semicolon
r_extern
r_int
id|Nports
suffix:semicolon
multiline_comment|/* Number of genuine ethernet controllers */
r_extern
r_int
id|Nchan
suffix:semicolon
multiline_comment|/* ... plus one for host interface */
r_extern
r_int
id|FirstChan
suffix:semicolon
multiline_comment|/* 0 or 1, depedning on whether host is used */
r_extern
r_int
id|NumChan
suffix:semicolon
multiline_comment|/* 4 or 5 */
multiline_comment|/*&n; *&t;A few globals&n; */
r_extern
r_int
id|IsPromisc
suffix:semicolon
r_extern
r_int
id|MultiNicMode
suffix:semicolon
multiline_comment|/*&n; *&t;Functions&n; */
r_extern
r_void
id|eth_xmit_spew_on
c_func
(paren
id|PORT
op_star
id|p
comma
r_int
id|cnt
)paren
suffix:semicolon
r_extern
r_void
id|eth_xmit_spew_off
c_func
(paren
id|PORT
op_star
id|p
)paren
suffix:semicolon
r_extern
id|I596_RBD
op_star
id|alloc_rbds
c_func
(paren
id|PORT
op_star
id|p
comma
r_int
id|num
)paren
suffix:semicolon
r_extern
id|I596_CB
op_star
id|eth_cb_alloc
c_func
(paren
id|PORT
op_star
id|p
)paren
suffix:semicolon
eof
