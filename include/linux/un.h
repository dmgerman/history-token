macro_line|#ifndef _LINUX_UN_H
DECL|macro|_LINUX_UN_H
mdefine_line|#define _LINUX_UN_H
DECL|macro|UNIX_PATH_MAX
mdefine_line|#define UNIX_PATH_MAX&t;108
DECL|struct|sockaddr_un
r_struct
id|sockaddr_un
(brace
DECL|member|sun_family
id|sa_family_t
id|sun_family
suffix:semicolon
multiline_comment|/* AF_UNIX */
DECL|member|sun_path
r_char
id|sun_path
(braket
id|UNIX_PATH_MAX
)braket
suffix:semicolon
multiline_comment|/* pathname */
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_UN_H */
eof
