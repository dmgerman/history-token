macro_line|#ifndef&t;_SPARC64_OPENPROMIO_H
DECL|macro|_SPARC64_OPENPROMIO_H
mdefine_line|#define&t;_SPARC64_OPENPROMIO_H
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * SunOS and Solaris /dev/openprom definitions. The ioctl values&n; * were chosen to be exactly equal to the SunOS equivalents.&n; */
DECL|struct|openpromio
r_struct
id|openpromio
(brace
DECL|member|oprom_size
id|u_int
id|oprom_size
suffix:semicolon
multiline_comment|/* Actual size of the oprom_array. */
DECL|member|oprom_array
r_char
id|oprom_array
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Holds property names and values. */
)brace
suffix:semicolon
DECL|macro|OPROMMAXPARAM
mdefine_line|#define&t;OPROMMAXPARAM&t;4096&t;&t;/* Maximum size of oprom_array. */
DECL|macro|OPROMGETOPT
mdefine_line|#define&t;OPROMGETOPT&t;&t;0x20004F01
DECL|macro|OPROMSETOPT
mdefine_line|#define&t;OPROMSETOPT&t;&t;0x20004F02
DECL|macro|OPROMNXTOPT
mdefine_line|#define&t;OPROMNXTOPT&t;&t;0x20004F03
DECL|macro|OPROMSETOPT2
mdefine_line|#define&t;OPROMSETOPT2&t;&t;0x20004F04
DECL|macro|OPROMNEXT
mdefine_line|#define&t;OPROMNEXT&t;&t;0x20004F05
DECL|macro|OPROMCHILD
mdefine_line|#define&t;OPROMCHILD&t;&t;0x20004F06
DECL|macro|OPROMGETPROP
mdefine_line|#define&t;OPROMGETPROP&t;&t;0x20004F07
DECL|macro|OPROMNXTPROP
mdefine_line|#define&t;OPROMNXTPROP&t;&t;0x20004F08
DECL|macro|OPROMU2P
mdefine_line|#define&t;OPROMU2P&t;&t;0x20004F09
DECL|macro|OPROMGETCONS
mdefine_line|#define&t;OPROMGETCONS&t;&t;0x20004F0A
DECL|macro|OPROMGETFBNAME
mdefine_line|#define&t;OPROMGETFBNAME&t;&t;0x20004F0B
DECL|macro|OPROMGETBOOTARGS
mdefine_line|#define&t;OPROMGETBOOTARGS&t;0x20004F0C
multiline_comment|/* Linux extensions */
multiline_comment|/* Arguments in oprom_array: */
DECL|macro|OPROMSETCUR
mdefine_line|#define OPROMSETCUR&t;&t;0x20004FF0&t;/* int node - Sets current node */
DECL|macro|OPROMPCI2NODE
mdefine_line|#define OPROMPCI2NODE&t;&t;0x20004FF1&t;/* int pci_bus, pci_devfn - Sets current node to PCI device&squot;s node */
DECL|macro|OPROMPATH2NODE
mdefine_line|#define OPROMPATH2NODE&t;&t;0x20004FF2&t;/* char path[] - Set current node from fully qualified PROM path */
multiline_comment|/*&n; * Return values from OPROMGETCONS:&n; */
DECL|macro|OPROMCONS_NOT_WSCONS
mdefine_line|#define OPROMCONS_NOT_WSCONS    0
DECL|macro|OPROMCONS_STDIN_IS_KBD
mdefine_line|#define OPROMCONS_STDIN_IS_KBD  0x1     /* stdin device is kbd */
DECL|macro|OPROMCONS_STDOUT_IS_FB
mdefine_line|#define OPROMCONS_STDOUT_IS_FB  0x2     /* stdout is a framebuffer */
DECL|macro|OPROMCONS_OPENPROM
mdefine_line|#define OPROMCONS_OPENPROM      0x4     /* supports openboot */
multiline_comment|/*&n; *  NetBSD/OpenBSD /dev/openprom definitions.&n; */
DECL|struct|opiocdesc
r_struct
id|opiocdesc
(brace
DECL|member|op_nodeid
r_int
id|op_nodeid
suffix:semicolon
multiline_comment|/* PROM Node ID (value-result) */
DECL|member|op_namelen
r_int
id|op_namelen
suffix:semicolon
multiline_comment|/* Length of op_name. */
DECL|member|op_name
r_char
op_star
id|op_name
suffix:semicolon
multiline_comment|/* Pointer to the property name. */
DECL|member|op_buflen
r_int
id|op_buflen
suffix:semicolon
multiline_comment|/* Length of op_buf (value-result) */
DECL|member|op_buf
r_char
op_star
id|op_buf
suffix:semicolon
multiline_comment|/* Pointer to buffer. */
)brace
suffix:semicolon
DECL|macro|OPIOCGET
mdefine_line|#define&t;OPIOCGET&t;_IOWR(&squot;O&squot;, 1, struct opiocdesc)
DECL|macro|OPIOCSET
mdefine_line|#define&t;OPIOCSET&t;_IOW(&squot;O&squot;, 2, struct opiocdesc)
DECL|macro|OPIOCNEXTPROP
mdefine_line|#define&t;OPIOCNEXTPROP&t;_IOWR(&squot;O&squot;, 3, struct opiocdesc)
DECL|macro|OPIOCGETOPTNODE
mdefine_line|#define&t;OPIOCGETOPTNODE&t;_IOR(&squot;O&squot;, 4, int)
DECL|macro|OPIOCGETNEXT
mdefine_line|#define&t;OPIOCGETNEXT&t;_IOWR(&squot;O&squot;, 5, int)
DECL|macro|OPIOCGETCHILD
mdefine_line|#define&t;OPIOCGETCHILD&t;_IOWR(&squot;O&squot;, 6, int)
macro_line|#endif /* _SPARC64_OPENPROMIO_H */
eof
