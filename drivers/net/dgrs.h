multiline_comment|/*&n; *&t;ioctl&squot;s for the Digi Intl. RightSwitch&n; *&n; *&t;These network driver ioctl&squot;s are a bit obtuse compared to the usual&n; *&t;ioctl&squot;s for a &quot;normal&quot; device driver.  Hey, I didn&squot;t invent it.&n; *&n; *&t;Typical use:&n; *&n; *&t;struct ifreq&t;ifr;&n; *&t;DGRS_IOCTL&t;ioc;&n; *&t;int&t;&t;x;&n; *&n; *&t;strcpy(ifr.ifr_name, &quot;eth1&quot;);&n; *&t;ifr.ifr_data = (caddr_t) &amp;ioc;&n; *&t;ioc.cmd = DGRS_GETMEM;&n; *&t;ioc.len = sizeof(x);&n; *&t;ioc.data = (caddr_t) &amp;x;&n; *&t;rc = ioctl(fd, DGRSIOCTL, &amp;ifr);&n; *&t;printf(&quot;rc=%d mem=%x&bslash;n&quot;, rc, x);&n; *&n; */
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|DGRSIOCTL
mdefine_line|#define DGRSIOCTL      SIOCDEVPRIVATE
DECL|struct|dgrs_ioctl
r_typedef
r_struct
id|dgrs_ioctl
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
multiline_comment|/* Command to run */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of the data buffer */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to the data buffer */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* port number for command, if needed */
DECL|member|filter
r_int
r_int
id|filter
suffix:semicolon
multiline_comment|/* filter number for command, if needed */
DECL|typedef|DGRS_IOCTL
)brace
id|DGRS_IOCTL
suffix:semicolon
multiline_comment|/* &n; *&t;Commands for the driver &n; */
DECL|macro|DGRS_GETMEM
mdefine_line|#define&t;DGRS_GETMEM&t;&t;0x01&t;/* Get the dual port memory address */
DECL|macro|DGRS_SETFILTER
mdefine_line|#define&t;DGRS_SETFILTER&t;&t;0x02&t;/* Set a filter */
eof
