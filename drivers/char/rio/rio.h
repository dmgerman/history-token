multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 1998 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: rio.h&n;**&t;SID&t;&t;: 1.3&n;**&t;Last Modified&t;: 11/6/98 11:34:13&n;**&t;Retrieved&t;: 11/6/98 11:34:22&n;**&n;**  ident @(#)rio.h&t;1.3&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef&t;__rio_rio_h__
DECL|macro|__rio_rio_h__
mdefine_line|#define&t;__rio_rio_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_h_sccs_
r_static
r_char
op_star
id|_rio_h_sccs_
op_assign
l_string|&quot;@(#)rio.h&t;1.3&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** 30.09.1998 ARG -&n;** Introduced driver version and host card type strings&n;*/
DECL|macro|RIO_DRV_STR
mdefine_line|#define RIO_DRV_STR &quot;Specialix RIO Driver&quot;
DECL|macro|RIO_AT_HOST_STR
mdefine_line|#define RIO_AT_HOST_STR &quot;ISA&quot;
DECL|macro|RIO_PCI_HOST_STR
mdefine_line|#define RIO_PCI_HOST_STR &quot;PCI&quot;
multiline_comment|/*&n;** rio_info_store() commands (arbitary values) :&n;*/
DECL|macro|RIO_INFO_PUT
mdefine_line|#define RIO_INFO_PUT&t;0xA4B3C2D1
DECL|macro|RIO_INFO_GET
mdefine_line|#define RIO_INFO_GET&t;0xF1E2D3C4
multiline_comment|/*&n;** anything that I couldn&squot;t cram in somewhere else&n;*/
multiline_comment|/*&n;#ifndef RIODEBUG&n;#define debug&n;#else&n;#define debug rioprint&n;#endif&n;*/
multiline_comment|/*&n;**&t;Maximum numbers of things&n;*/
DECL|macro|RIO_SLOTS
mdefine_line|#define&t;RIO_SLOTS&t;4&t;/* number of configuration slots */
DECL|macro|RIO_HOSTS
mdefine_line|#define&t;RIO_HOSTS&t;4&t;/* number of hosts that can be found */
DECL|macro|PORTS_PER_HOST
mdefine_line|#define&t;PORTS_PER_HOST&t;128&t;/* number of ports per host */
DECL|macro|LINKS_PER_UNIT
mdefine_line|#define&t;LINKS_PER_UNIT&t;4&t;/* number of links from a host */
DECL|macro|RIO_PORTS
mdefine_line|#define&t;RIO_PORTS&t;(PORTS_PER_HOST * RIO_HOSTS) /* max. no. of ports */
DECL|macro|RTAS_PER_HOST
mdefine_line|#define&t;RTAS_PER_HOST&t;(MAX_RUP) /* number of RTAs per host */
DECL|macro|PORTS_PER_RTA
mdefine_line|#define&t;PORTS_PER_RTA&t;(PORTS_PER_HOST/RTAS_PER_HOST)&t;/* ports on a rta */
DECL|macro|PORTS_PER_MODULE
mdefine_line|#define&t;PORTS_PER_MODULE 4&t;/* number of ports on a plug-in module */
multiline_comment|/* number of modules on an RTA */
DECL|macro|MODULES_PER_RTA
mdefine_line|#define&t;MODULES_PER_RTA&t; (PORTS_PER_RTA/PORTS_PER_MODULE)
DECL|macro|MAX_PRODUCT
mdefine_line|#define MAX_PRODUCT&t;16&t;/* numbr of different product codes */
DECL|macro|MAX_MODULE_TYPES
mdefine_line|#define MAX_MODULE_TYPES 16&t;/* number of different types of module */
DECL|macro|RIO_CONTROL_DEV
mdefine_line|#define RIO_CONTROL_DEV&t;128&t;/* minor number of host/control device */
DECL|macro|RIO_INVALID_MAJOR
mdefine_line|#define RIO_INVALID_MAJOR 0&t;/* test first host card&squot;s major no for validity */
multiline_comment|/*&n;** number of RTAs that can be bound to a master&n;*/
DECL|macro|MAX_RTA_BINDINGS
mdefine_line|#define MAX_RTA_BINDINGS (MAX_RUP * RIO_HOSTS)
multiline_comment|/*&n;**&t;Unit types&n;*/
DECL|macro|PC_RTA16
mdefine_line|#define PC_RTA16&t;0x90000000
DECL|macro|PC_RTA8
mdefine_line|#define PC_RTA8&t;&t;0xe0000000
DECL|macro|TYPE_HOST
mdefine_line|#define TYPE_HOST&t;0
DECL|macro|TYPE_RTA8
mdefine_line|#define TYPE_RTA8&t;1
DECL|macro|TYPE_RTA16
mdefine_line|#define TYPE_RTA16&t;2
multiline_comment|/*&n;**&t;Flag values returned by functions&n;*/
DECL|macro|RIO_FAIL
mdefine_line|#define&t;RIO_FAIL&t;-1
DECL|macro|RIO_SUCCESS
mdefine_line|#define&t;RIO_SUCCESS&t;0
DECL|macro|COPYFAIL
mdefine_line|#define&t;COPYFAIL&t;-1&t;/* copy[in|out] failed */
multiline_comment|/*&n;** SysPort value for something that hasn&squot;t any ports&n;*/
DECL|macro|NO_PORT
mdefine_line|#define&t;NO_PORT&t;0xFFFFFFFF
multiline_comment|/*&n;** Unit ID Of all hosts&n;*/
DECL|macro|HOST_ID
mdefine_line|#define&t;HOST_ID&t;0
multiline_comment|/*&n;** Break bytes into nybles&n;*/
DECL|macro|LONYBLE
mdefine_line|#define&t;LONYBLE(X)&t;((X) &amp; 0xF)
DECL|macro|HINYBLE
mdefine_line|#define&t;HINYBLE(X)&t;(((X)&gt;&gt;4) &amp; 0xF)
multiline_comment|/*&n;** Flag values passed into some functions&n;*/
DECL|macro|DONT_SLEEP
mdefine_line|#define&t;DONT_SLEEP&t;0
DECL|macro|OK_TO_SLEEP
mdefine_line|#define&t;OK_TO_SLEEP&t;1
DECL|macro|DONT_PRINT
mdefine_line|#define&t;DONT_PRINT&t;1
DECL|macro|DO_PRINT
mdefine_line|#define&t;DO_PRINT&t;0
DECL|macro|PRINT_TO_LOG_CONS
mdefine_line|#define PRINT_TO_LOG_CONS&t;0
DECL|macro|PRINT_TO_CONS
mdefine_line|#define PRINT_TO_CONS&t;1
DECL|macro|PRINT_TO_LOG
mdefine_line|#define PRINT_TO_LOG&t;2
multiline_comment|/*&n;** Timeout has trouble with times of less than 3 ticks...&n;*/
DECL|macro|MIN_TIMEOUT
mdefine_line|#define&t;MIN_TIMEOUT&t;3
multiline_comment|/*&n;**&t;Generally useful constants&n;*/
DECL|macro|HALF_A_SECOND
mdefine_line|#define&t;HALF_A_SECOND&t;&t;((HZ)&gt;&gt;1)
DECL|macro|A_SECOND
mdefine_line|#define&t;A_SECOND&t;&t;(HZ)
DECL|macro|HUNDRED_HZ
mdefine_line|#define&t;HUNDRED_HZ&t;&t;((HZ/100)?(HZ/100):1)
DECL|macro|FIFTY_HZ
mdefine_line|#define&t;FIFTY_HZ&t;&t;((HZ/50)?(HZ/50):1)
DECL|macro|TWENTY_HZ
mdefine_line|#define&t;TWENTY_HZ&t;&t;((HZ/20)?(HZ/20):1)
DECL|macro|TEN_HZ
mdefine_line|#define&t;TEN_HZ&t;&t;&t;((HZ/10)?(HZ/10):1)
DECL|macro|FIVE_HZ
mdefine_line|#define&t;FIVE_HZ&t;&t;&t;((HZ/5)?(HZ/5):1)
DECL|macro|HUNDRED_MS
mdefine_line|#define&t;HUNDRED_MS&t;&t;TEN_HZ
DECL|macro|FIFTY_MS
mdefine_line|#define&t;FIFTY_MS&t;&t;TWENTY_HZ
DECL|macro|TWENTY_MS
mdefine_line|#define&t;TWENTY_MS&t;&t;FIFTY_HZ
DECL|macro|TEN_MS
mdefine_line|#define&t;TEN_MS&t;&t;&t;HUNDRED_HZ
DECL|macro|TWO_SECONDS
mdefine_line|#define&t;TWO_SECONDS&t;&t;((A_SECOND)*2)
DECL|macro|FIVE_SECONDS
mdefine_line|#define&t;FIVE_SECONDS&t;&t;((A_SECOND)*5)
DECL|macro|TEN_SECONDS
mdefine_line|#define&t;TEN_SECONDS&t;&t;((A_SECOND)*10)
DECL|macro|FIFTEEN_SECONDS
mdefine_line|#define&t;FIFTEEN_SECONDS&t;&t;((A_SECOND)*15)
DECL|macro|TWENTY_SECONDS
mdefine_line|#define&t;TWENTY_SECONDS&t;&t;((A_SECOND)*20)
DECL|macro|HALF_A_MINUTE
mdefine_line|#define&t;HALF_A_MINUTE&t;&t;(A_MINUTE&gt;&gt;1)
DECL|macro|A_MINUTE
mdefine_line|#define&t;A_MINUTE&t;&t;(A_SECOND*60)
DECL|macro|FIVE_MINUTES
mdefine_line|#define&t;FIVE_MINUTES&t;&t;(A_MINUTE*5)
DECL|macro|QUARTER_HOUR
mdefine_line|#define&t;QUARTER_HOUR&t;&t;(A_MINUTE*15)
DECL|macro|HALF_HOUR
mdefine_line|#define&t;HALF_HOUR&t;&t;(A_MINUTE*30)
DECL|macro|HOUR
mdefine_line|#define&t;HOUR&t;&t;&t;(A_MINUTE*60)
DECL|macro|SIXTEEN_MEG
mdefine_line|#define&t;SIXTEEN_MEG&t;&t;0x1000000
DECL|macro|ONE_MEG
mdefine_line|#define&t;ONE_MEG&t;&t;&t;0x100000
DECL|macro|SIXTY_FOUR_K
mdefine_line|#define&t;SIXTY_FOUR_K&t;&t;0x10000
DECL|macro|RIO_AT_MEM_SIZE
mdefine_line|#define&t;RIO_AT_MEM_SIZE&t;&t;SIXTY_FOUR_K
DECL|macro|RIO_EISA_MEM_SIZE
mdefine_line|#define&t;RIO_EISA_MEM_SIZE&t;SIXTY_FOUR_K
DECL|macro|RIO_MCA_MEM_SIZE
mdefine_line|#define&t;RIO_MCA_MEM_SIZE&t;SIXTY_FOUR_K
DECL|macro|POLL_VECTOR
mdefine_line|#define&t;POLL_VECTOR&t;&t;0x100
DECL|macro|COOK_WELL
mdefine_line|#define&t;COOK_WELL&t;&t;0
DECL|macro|COOK_MEDIUM
mdefine_line|#define&t;COOK_MEDIUM&t;&t;1
DECL|macro|COOK_RAW
mdefine_line|#define&t;COOK_RAW&t;&t;2
multiline_comment|/*&n;**&t;Pointer manipulation stuff&n;**&t;RIO_PTR takes hostp-&gt;Caddr and the offset into the DP RAM area&n;**&t;and produces a UNIX caddr_t (pointer) to the object&n;**&t;RIO_OBJ takes hostp-&gt;Caddr and a UNIX pointer to an object and&n;**&t;returns the offset into the DP RAM area.&n;*/
DECL|macro|RIO_PTR
mdefine_line|#define&t;RIO_PTR(C,O) (((caddr_t)(C))+(0xFFFF&amp;(O)))
DECL|macro|RIO_OFF
mdefine_line|#define&t;RIO_OFF(C,O) ((int)(O)-(int)(C))
multiline_comment|/*&n;**&t;How to convert from various different device number formats:&n;**&t;DEV is a dev number, as passed to open, close etc - NOT a minor&n;**&t;number!&n;**&n;**&t;Note:&t;LynxOS only gives us 8 bits for the device minor number,&n;**&t;&t;so all this crap here to deal with &squot;modem&squot; bits etc. is&n;**&t;&t;just a load of irrelevant old bunkum!&n;**&t;&t;This however does not stop us needing to define a value&n;**&t;&t;for RIO_MODEMOFFSET which is required by the &squot;riomkdev&squot;&n;**&t;&t;utility in the New Config Utilities suite.&n;*/
multiline_comment|/* 0-511: direct 512-1023: modem */
DECL|macro|RIO_MODEMOFFSET
mdefine_line|#define&t;RIO_MODEMOFFSET&t;&t;0x200&t;/* doesn&squot;t mean anything */
DECL|macro|RIO_MODEM_MASK
mdefine_line|#define&t;RIO_MODEM_MASK&t;&t;0x1FF
DECL|macro|RIO_MODEM_BIT
mdefine_line|#define&t;RIO_MODEM_BIT&t;&t;0x200
DECL|macro|RIO_UNMODEM
mdefine_line|#define&t;RIO_UNMODEM(DEV)&t;(minor(DEV) &amp; RIO_MODEM_MASK)
DECL|macro|RIO_ISMODEM
mdefine_line|#define&t;RIO_ISMODEM(DEV)&t;(minor(DEV) &amp; RIO_MODEM_BIT)
DECL|macro|RIO_PORT
mdefine_line|#define RIO_PORT(DEV,FIRST_MAJ)&t;( (major(DEV) - FIRST_MAJ) * PORTS_PER_HOST) &bslash;&n;&t;&t;&t;&t;&t;+ minor(DEV)
multiline_comment|/*&n;**&t;Min and Max&n;*/
macro_line|#ifndef min
DECL|macro|min
mdefine_line|#define&t;min(A,B)&t;((A)&lt;(B)?(A):(B))
macro_line|#endif
macro_line|#ifndef max
DECL|macro|max
mdefine_line|#define&t;max(A,B)&t;((A)&gt;(B)?(A):(B))
macro_line|#endif
DECL|macro|splrio
mdefine_line|#define&t;splrio&t;spltty
DECL|macro|RIO_IPL
mdefine_line|#define&t;RIO_IPL&t;5
DECL|macro|RIO_PRI
mdefine_line|#define&t;RIO_PRI&t;(PZERO+10)
DECL|macro|RIO_CLOSE_PRI
mdefine_line|#define RIO_CLOSE_PRI&t;PZERO-1&t;/* uninteruptible sleeps for close */
DECL|struct|DbInf
r_typedef
r_struct
id|DbInf
(brace
DECL|member|Flag
id|uint
id|Flag
suffix:semicolon
DECL|member|Name
r_char
id|Name
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|DbInf
)brace
id|DbInf
suffix:semicolon
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define&t;TRUE (1==1)
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define&t;FALSE&t;(!TRUE)
macro_line|#endif
DECL|macro|CSUM
mdefine_line|#define CSUM(pkt_ptr)  (((ushort *)(pkt_ptr))[0] + ((ushort *)(pkt_ptr))[1] + &bslash;&n;&t;&t;&t;((ushort *)(pkt_ptr))[2] + ((ushort *)(pkt_ptr))[3] + &bslash;&n;&t;&t;&t;((ushort *)(pkt_ptr))[4] + ((ushort *)(pkt_ptr))[5] + &bslash;&n;&t;&t;&t;((ushort *)(pkt_ptr))[6] + ((ushort *)(pkt_ptr))[7] + &bslash;&n;&t;&t;&t;((ushort *)(pkt_ptr))[8] + ((ushort *)(pkt_ptr))[9] )
multiline_comment|/*&n;** This happy little macro copies SIZE bytes of data from FROM to TO&n;** quite well. SIZE must be a constant.&n;*/
DECL|macro|CCOPY
mdefine_line|#define CCOPY( FROM, TO, SIZE ) { *(struct s { char data[SIZE]; } *)(TO) = *(struct s *)(FROM); }
multiline_comment|/*&n;** increment a buffer pointer modulo the size of the buffer...&n;*/
DECL|macro|BUMP
mdefine_line|#define&t;BUMP( P, I )&t;((P) = (((P)+(I)) &amp; RIOBufferMask))
DECL|macro|INIT_PACKET
mdefine_line|#define INIT_PACKET( PK, PP ) &bslash;&n;{ &bslash;&n;&t;*((uint *)PK)    = PP-&gt;PacketInfo; &bslash;&n;}
DECL|macro|RIO_LINK_ENABLE
mdefine_line|#define&t;RIO_LINK_ENABLE&t;0x80FF /* FF is a hack, mainly for Mips, to        */
multiline_comment|/* prevent a really stupid race condition.  */
DECL|macro|NOT_INITIALISED
mdefine_line|#define&t;NOT_INITIALISED&t;0
DECL|macro|INITIALISED
mdefine_line|#define&t;INITIALISED&t;1
DECL|macro|NOT_POLLING
mdefine_line|#define&t;NOT_POLLING&t;0
DECL|macro|POLLING
mdefine_line|#define&t;POLLING&t;&t;1
DECL|macro|NOT_CHANGED
mdefine_line|#define&t;NOT_CHANGED&t;0
DECL|macro|CHANGED
mdefine_line|#define&t;CHANGED&t;&t;1
DECL|macro|NOT_INUSE
mdefine_line|#define&t;NOT_INUSE&t;0
DECL|macro|DISCONNECT
mdefine_line|#define&t;DISCONNECT&t;0
DECL|macro|CONNECT
mdefine_line|#define&t;CONNECT&t;&t;1
multiline_comment|/*&n;** Machine types - these must NOT overlap with product codes 0-15&n;*/
DECL|macro|RIO_MIPS_R3230
mdefine_line|#define&t;RIO_MIPS_R3230&t;31
DECL|macro|RIO_MIPS_R4030
mdefine_line|#define&t;RIO_MIPS_R4030&t;32
DECL|macro|RIO_IO_UNKNOWN
mdefine_line|#define&t;RIO_IO_UNKNOWN&t;-2
DECL|macro|MODERN
macro_line|#undef&t;MODERN
DECL|macro|ERROR
mdefine_line|#define&t;ERROR( E )&t;do { u.u_error = E; return OPENFAIL } while ( 0 )
multiline_comment|/* Defines for MPX line discipline routines */
DECL|macro|DIST_LINESW_OPEN
mdefine_line|#define DIST_LINESW_OPEN&t;0x01
DECL|macro|DIST_LINESW_CLOSE
mdefine_line|#define DIST_LINESW_CLOSE&t;0x02
DECL|macro|DIST_LINESW_READ
mdefine_line|#define DIST_LINESW_READ&t;0x04
DECL|macro|DIST_LINESW_WRITE
mdefine_line|#define DIST_LINESW_WRITE&t;0x08
DECL|macro|DIST_LINESW_IOCTL
mdefine_line|#define DIST_LINESW_IOCTL&t;0x10
DECL|macro|DIST_LINESW_INPUT
mdefine_line|#define DIST_LINESW_INPUT&t;0x20
DECL|macro|DIST_LINESW_OUTPUT
mdefine_line|#define DIST_LINESW_OUTPUT&t;0x40
DECL|macro|DIST_LINESW_MDMINT
mdefine_line|#define DIST_LINESW_MDMINT&t;0x80
macro_line|#endif /* __rio_h__ */
eof
