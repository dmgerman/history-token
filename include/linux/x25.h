multiline_comment|/*&n; * These are the public elements of the Linux kernel X.25 implementation.&n; *&n; * &t;History&n; *&t;mar/20/00&t;Daniela Squassoni Disabling/enabling of facilities &n; *&t;&t;&t;&t;&t;  negotiation.&n; */
macro_line|#ifndef&t;X25_KERNEL_H
DECL|macro|X25_KERNEL_H
mdefine_line|#define&t;X25_KERNEL_H
DECL|macro|SIOCX25GSUBSCRIP
mdefine_line|#define&t;SIOCX25GSUBSCRIP&t;(SIOCPROTOPRIVATE + 0)
DECL|macro|SIOCX25SSUBSCRIP
mdefine_line|#define&t;SIOCX25SSUBSCRIP&t;(SIOCPROTOPRIVATE + 1)
DECL|macro|SIOCX25GFACILITIES
mdefine_line|#define&t;SIOCX25GFACILITIES&t;(SIOCPROTOPRIVATE + 2)
DECL|macro|SIOCX25SFACILITIES
mdefine_line|#define&t;SIOCX25SFACILITIES&t;(SIOCPROTOPRIVATE + 3)
DECL|macro|SIOCX25GCALLUSERDATA
mdefine_line|#define&t;SIOCX25GCALLUSERDATA&t;(SIOCPROTOPRIVATE + 4)
DECL|macro|SIOCX25SCALLUSERDATA
mdefine_line|#define&t;SIOCX25SCALLUSERDATA&t;(SIOCPROTOPRIVATE + 5)
DECL|macro|SIOCX25GCAUSEDIAG
mdefine_line|#define&t;SIOCX25GCAUSEDIAG&t;(SIOCPROTOPRIVATE + 6)
multiline_comment|/*&n; *&t;Values for {get,set}sockopt.&n; */
DECL|macro|X25_QBITINCL
mdefine_line|#define&t;X25_QBITINCL&t;&t;1
multiline_comment|/*&n; *&t;X.25 Packet Size values.&n; */
DECL|macro|X25_PS16
mdefine_line|#define&t;X25_PS16&t;&t;4
DECL|macro|X25_PS32
mdefine_line|#define&t;X25_PS32&t;&t;5
DECL|macro|X25_PS64
mdefine_line|#define&t;X25_PS64&t;&t;6
DECL|macro|X25_PS128
mdefine_line|#define&t;X25_PS128&t;&t;7
DECL|macro|X25_PS256
mdefine_line|#define&t;X25_PS256&t;&t;8
DECL|macro|X25_PS512
mdefine_line|#define&t;X25_PS512&t;&t;9
DECL|macro|X25_PS1024
mdefine_line|#define&t;X25_PS1024&t;&t;10
DECL|macro|X25_PS2048
mdefine_line|#define&t;X25_PS2048&t;&t;11
DECL|macro|X25_PS4096
mdefine_line|#define&t;X25_PS4096&t;&t;12
multiline_comment|/*&n; * An X.121 address, it is held as ASCII text, null terminated, up to 15&n; * digits and a null terminator.&n; */
r_typedef
r_struct
(brace
DECL|member|x25_addr
r_char
id|x25_addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|x25_address
)brace
id|x25_address
suffix:semicolon
multiline_comment|/*&n; *&t;Linux X.25 Address structure, used for bind, and connect mostly.&n; */
DECL|struct|sockaddr_x25
r_struct
id|sockaddr_x25
(brace
DECL|member|sx25_family
id|sa_family_t
id|sx25_family
suffix:semicolon
multiline_comment|/* Must be AF_X25 */
DECL|member|sx25_addr
id|x25_address
id|sx25_addr
suffix:semicolon
multiline_comment|/* X.121 Address */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;DTE/DCE subscription options.&n; *&n; *      As this is missing lots of options, user should expect major&n; *&t;changes of this structure in 2.5.x which might break compatibilty.&n; *      The somewhat ugly dimension 200-sizeof() is needed to maintain&n; *&t;backward compatibility.&n; */
DECL|struct|x25_subscrip_struct
r_struct
id|x25_subscrip_struct
(brace
DECL|member|device
r_char
id|device
(braket
l_int|200
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
DECL|member|global_facil_mask
r_int
r_int
id|global_facil_mask
suffix:semicolon
multiline_comment|/* 0 to disable negotiation */
DECL|member|extended
r_int
r_int
id|extended
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* values for above global_facil_mask */
DECL|macro|X25_MASK_REVERSE
mdefine_line|#define&t;X25_MASK_REVERSE&t;0x01&t;
DECL|macro|X25_MASK_THROUGHPUT
mdefine_line|#define&t;X25_MASK_THROUGHPUT&t;0x02
DECL|macro|X25_MASK_PACKET_SIZE
mdefine_line|#define&t;X25_MASK_PACKET_SIZE&t;0x04
DECL|macro|X25_MASK_WINDOW_SIZE
mdefine_line|#define&t;X25_MASK_WINDOW_SIZE&t;0x08
multiline_comment|/*&n; *&t;Routing table control structure.&n; */
DECL|struct|x25_route_struct
r_struct
id|x25_route_struct
(brace
DECL|member|address
id|x25_address
id|address
suffix:semicolon
DECL|member|sigdigits
r_int
r_int
id|sigdigits
suffix:semicolon
DECL|member|device
r_char
id|device
(braket
l_int|200
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Facilities structure.&n; */
DECL|struct|x25_facilities
r_struct
id|x25_facilities
(brace
DECL|member|winsize_in
DECL|member|winsize_out
r_int
r_int
id|winsize_in
comma
id|winsize_out
suffix:semicolon
DECL|member|pacsize_in
DECL|member|pacsize_out
r_int
r_int
id|pacsize_in
comma
id|pacsize_out
suffix:semicolon
DECL|member|throughput
r_int
r_int
id|throughput
suffix:semicolon
DECL|member|reverse
r_int
r_int
id|reverse
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Call User Data structure.&n; */
DECL|struct|x25_calluserdata
r_struct
id|x25_calluserdata
(brace
DECL|member|cudlength
r_int
r_int
id|cudlength
suffix:semicolon
DECL|member|cuddata
r_int
r_char
id|cuddata
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Call clearing Cause and Diagnostic structure.&n; */
DECL|struct|x25_causediag
r_struct
id|x25_causediag
(brace
DECL|member|cause
r_int
r_char
id|cause
suffix:semicolon
DECL|member|diagnostic
r_int
r_char
id|diagnostic
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
