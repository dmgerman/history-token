multiline_comment|/*&n; * The bios low-memory structure&n; *&n; * Some of the variables in here can be used to set parameters that&n; * are stored in NVRAM and will retain their old values the next time&n; * the card is brought up.  To use the values stored in NVRAM, the&n; * parameter should be set to &quot;all ones&quot;.  This tells the firmware to&n; * use the NVRAM value or a suitable default.  The value that is used&n; * will be stored back into this structure by the firmware.  If the&n; * value of the variable is not &quot;all ones&quot;, then that value will be&n; * used and will be stored into NVRAM if it isn&squot;t already there.&n; * The variables this applies to are the following:&n; *&t;Variable&t;Set to:&t;&t;Gets default of:&n; *&t;bc_hashexpire&t;-1&t;&t;300&t;(5 minutes)&n; *&t;bc_spantree&t;-1&t;&t;1&t;(spanning tree on)&n; *&t;bc_ipaddr&t;FF:FF:FF:FF&t;0&t;(no SNMP IP address)&n; *&t;bc_ipxnet&t;FF:FF:FF:FF&t;0&t;(no SNMP IPX net)&n; *&t;bc_iptrap&t;FF:FF:FF:FF&t;0&t;(no SNMP IP trap address)&n; *&n; * Some variables MUST have their value set after the firmware&n; * is loaded onto the board, but before the processor is released.&n; * These are:&n; *&t;bc_host&t;&t;0 means no host &quot;port&quot;, run as standalone switch.&n; *&t;&t;&t;1 means run as a switch, with a host port. (normal)&n; *&t;&t;&t;2 means run as multiple NICs, not as a switch.&n; *&t;&t;&t;-1 means run in diagnostics mode.&n; *&t;bc_nowait&n; *&t;bc_hostarea_len&n; *&t;bc_filter_len&n; *&t;&t;&t;&n; */
id|BEGIN_STRUCT
c_func
(paren
id|bios_comm
)paren
id|S4
c_func
(paren
id|ulong
comma
id|bc_intflag
)paren
multiline_comment|/* Count of all interrupts */
id|S4
c_func
(paren
id|ulong
comma
id|bc_lbolt
)paren
multiline_comment|/* Count of timer interrupts */
id|S4
c_func
(paren
id|ulong
comma
id|bc_maincnt
)paren
multiline_comment|/* Count of main loops */
id|S4
c_func
(paren
id|ulong
comma
id|bc_hashcnt
)paren
multiline_comment|/* Count of entries in hash table */
id|S4A
c_func
(paren
id|ulong
comma
id|bc_cnt
comma
l_int|8
)paren
multiline_comment|/* Misc counters, for debugging */
id|S4A
c_func
(paren
id|ulong
comma
id|bc_flag
comma
l_int|8
)paren
multiline_comment|/* Misc flags, for debugging */
id|S4
c_func
(paren
id|ulong
comma
id|bc_memsize
)paren
multiline_comment|/* Size of memory */
id|S4
c_func
(paren
id|ulong
comma
id|bc_dcache
)paren
multiline_comment|/* Size of working dcache */
id|S4
c_func
(paren
id|ulong
comma
id|bc_icache
)paren
multiline_comment|/* Size of working icache */
id|S4
c_func
(paren
r_int
comma
id|bc_status
)paren
multiline_comment|/* Firmware status */
id|S1A
c_func
(paren
r_char
comma
id|bc_file
comma
l_int|8
)paren
multiline_comment|/* File name of assertion failure */
id|S4
c_func
(paren
id|ulong
comma
id|bc_line
)paren
multiline_comment|/* Line # of assertion failure */
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_ramstart
)paren
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_ramend
)paren
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_heapstart
)paren
multiline_comment|/* Start of heap (end of loaded memory) */
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_heapend
)paren
multiline_comment|/* End of heap */
multiline_comment|/* Configurable Parameters */
id|S4
c_func
(paren
r_int
comma
id|bc_host
)paren
multiline_comment|/* 1=Host Port, 0=No Host Port, -1=Test Mode */
id|S4
c_func
(paren
r_int
comma
id|bc_nowait
)paren
multiline_comment|/* Don&squot;t wait for 2host circ buffer to empty*/
id|S4
c_func
(paren
r_int
comma
id|bc_150ohm
)paren
multiline_comment|/* 0 == 100 ohm UTP, 1 == 150 ohm STP */
id|S4
c_func
(paren
r_int
comma
id|bc_squelch
)paren
multiline_comment|/* 0 == normal squelch, 1 == reduced squelch */
id|S4
c_func
(paren
id|ulong
comma
id|bc_hashexpire
)paren
multiline_comment|/* Expiry time in seconds for hash table */
id|S4
c_func
(paren
r_int
comma
id|bc_spantree
)paren
multiline_comment|/* 1 == enable IEEE spanning tree */
id|S2A
c_func
(paren
id|ushort
comma
id|bc_eaddr
comma
l_int|3
)paren
multiline_comment|/* New ether address */
id|S2
c_func
(paren
id|ushort
comma
id|bc_dummy1
)paren
multiline_comment|/* padding for DOS compilers */
multiline_comment|/* Various debugging aids */
id|S4
c_func
(paren
r_int
comma
id|bc_debug
)paren
multiline_comment|/* Debugging is turned on */
id|S4
c_func
(paren
r_int
comma
id|bc_spew
)paren
multiline_comment|/* Spew data on port 4 for bs_spew seconds */
id|S4
c_func
(paren
r_int
comma
id|bc_spewlen
)paren
multiline_comment|/* Length of spewed data packets */
id|S4
c_func
(paren
r_int
comma
id|bc_maxrfd
)paren
multiline_comment|/* If != 0, max number of RFD&squot;s to allocate */
id|S4
c_func
(paren
r_int
comma
id|bc_maxrbd
)paren
multiline_comment|/* If != 0, max number of RBD&squot;s to allocate */
multiline_comment|/* Circular buffers for messages to/from host */
id|S4
c_func
(paren
id|ulong
comma
id|bc_2host_head
)paren
id|S4
c_func
(paren
id|ulong
comma
id|bc_2host_tail
)paren
id|S4
c_func
(paren
id|ulong
comma
id|bc_2host_mask
)paren
id|S1A
c_func
(paren
r_char
comma
id|bc_2host
comma
l_int|0x200
)paren
multiline_comment|/* Circ buff to host */
id|S4
c_func
(paren
id|ulong
comma
id|bc_2idt_head
)paren
id|S4
c_func
(paren
id|ulong
comma
id|bc_2idt_tail
)paren
id|S4
c_func
(paren
id|ulong
comma
id|bc_2idt_mask
)paren
id|S1A
c_func
(paren
r_char
comma
id|bc_2idt
comma
l_int|0x200
)paren
multiline_comment|/* Circ buff to idt */
multiline_comment|/* Pointers to structures for driver access */
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_port
)paren
multiline_comment|/* pointer to Port[] structures */
id|S4
c_func
(paren
r_int
comma
id|bc_nports
)paren
multiline_comment|/* Number of ports */
id|S4
c_func
(paren
r_int
comma
id|bc_portlen
)paren
multiline_comment|/* sizeof(PORT) */
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_hash
)paren
multiline_comment|/* Pointer to hash table */
id|S4
c_func
(paren
r_int
comma
id|bc_hashlen
)paren
multiline_comment|/* sizeof(Table) */
multiline_comment|/* SNMP agent addresses */
id|S1A
c_func
(paren
id|uchar
comma
id|bc_ipaddr
comma
l_int|4
)paren
multiline_comment|/* IP address for SNMP */
id|S1A
c_func
(paren
id|uchar
comma
id|bc_ipxnet
comma
l_int|4
)paren
multiline_comment|/* IPX net address for SNMP */
id|S4
c_func
(paren
r_int
comma
id|bc_nohostintr
)paren
multiline_comment|/* Do not cause periodic host interrupts */
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_dmaaddr
)paren
multiline_comment|/* Physical addr of host DMA buf for diags */
id|S4
c_func
(paren
id|ulong
comma
id|bc_dmalen
)paren
multiline_comment|/* Length of DMA buffer 0..2048 */
multiline_comment|/*&n;&t; *&t;Board memory allocated on startup for use by host, usually&n;&t; *&t;for the purposes of creating DMA chain descriptors.  The&n;&t; *&t;&quot;len&quot; must be set before the processor is released.  The&n;&t; *&t;address of the area is returned in bc_hostarea.  The area&n;&t; *&t;is guaranteed to be aligned on a 16 byte boundary.&n;&t; */
id|S4
c_func
(paren
id|ulong
comma
id|bc_hostarea_len
)paren
multiline_comment|/* RW: Number of bytes to allocate */
id|S4
c_func
(paren
id|uchar
op_star
comma
id|bc_hostarea
)paren
multiline_comment|/* RO: Address of allocated memory */
multiline_comment|/*&n;&t; *&t;Variables for communicating filters into the board&n;&t; */
id|S4
c_func
(paren
id|ulong
op_star
comma
id|bc_filter_area
)paren
multiline_comment|/* RO: Space to put filter into */
id|S4
c_func
(paren
id|ulong
comma
id|bc_filter_area_len
)paren
multiline_comment|/* RO: Length of area, in bytes */
id|S4
c_func
(paren
r_int
comma
id|bc_filter_cmd
)paren
multiline_comment|/* RW: Filter command, see below */
id|S4
c_func
(paren
id|ulong
comma
id|bc_filter_len
)paren
multiline_comment|/* RW: Actual length of filter */
id|S4
c_func
(paren
id|ulong
comma
id|bc_filter_port
)paren
multiline_comment|/* RW: Port # for filter 0..6 */
id|S4
c_func
(paren
id|ulong
comma
id|bc_filter_num
)paren
multiline_comment|/* RW: Filter #, 0=input, 1=output */
multiline_comment|/* more SNMP agent addresses */
id|S1A
c_func
(paren
id|uchar
comma
id|bc_iptrap
comma
l_int|4
)paren
multiline_comment|/* IP address for SNMP */
id|S4A
c_func
(paren
r_int
comma
id|bc_spare
comma
l_int|2
)paren
multiline_comment|/* spares */
id|END_STRUCT
c_func
(paren
id|bios_comm
)paren
DECL|macro|bc
mdefine_line|#define&t;bc&t;VMO(struct bios_comm, 0xa3000100)
multiline_comment|/*&n; *&t;bc_status values&n; */
DECL|macro|BC_INIT
mdefine_line|#define&t;BC_INIT&t;0
DECL|macro|BC_RUN
mdefine_line|#define&t;BC_RUN&t;100
multiline_comment|/*&n; *&t;bc_host values&n; */
DECL|macro|BC_DIAGS
mdefine_line|#define&t;BC_DIAGS&t;-1
DECL|macro|BC_SASWITCH
mdefine_line|#define BC_SASWITCH&t;0
DECL|macro|BC_SWITCH
mdefine_line|#define&t;BC_SWITCH&t;1
DECL|macro|BC_MULTINIC
mdefine_line|#define&t;BC_MULTINIC&t;2
multiline_comment|/*&n; *&t;Values for spew (debugging)&n; */
DECL|macro|BC_SPEW_ENABLE
mdefine_line|#define&t;BC_SPEW_ENABLE&t;0x80000000
multiline_comment|/*&n; *&t;filter commands&n; */
DECL|macro|BC_FILTER_ERR
mdefine_line|#define&t;BC_FILTER_ERR&t;-1
DECL|macro|BC_FILTER_OK
mdefine_line|#define&t;BC_FILTER_OK&t;0
DECL|macro|BC_FILTER_SET
mdefine_line|#define&t;BC_FILTER_SET&t;1
DECL|macro|BC_FILTER_CLR
mdefine_line|#define&t;BC_FILTER_CLR&t;2
eof
