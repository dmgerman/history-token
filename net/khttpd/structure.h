macro_line|#ifndef _INCLUDE_GUARD_STRUCTURE_H_
DECL|macro|_INCLUDE_GUARD_STRUCTURE_H_
mdefine_line|#define _INCLUDE_GUARD_STRUCTURE_H_
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
r_struct
id|http_request
suffix:semicolon
DECL|struct|http_request
r_struct
id|http_request
(brace
multiline_comment|/* Linked list */
DECL|member|Next
r_struct
id|http_request
op_star
id|Next
suffix:semicolon
multiline_comment|/* Network and File data */
DECL|member|sock
r_struct
id|socket
op_star
id|sock
suffix:semicolon
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
multiline_comment|/* Raw data about the file */
DECL|member|FileLength
r_int
id|FileLength
suffix:semicolon
multiline_comment|/* File length in bytes */
DECL|member|Time
r_int
id|Time
suffix:semicolon
multiline_comment|/* mtime of the file, unix format */
DECL|member|BytesSent
r_int
id|BytesSent
suffix:semicolon
multiline_comment|/* The number of bytes already sent */
DECL|member|IsForUserspace
r_int
id|IsForUserspace
suffix:semicolon
multiline_comment|/* 1 means let Userspace handle this one */
multiline_comment|/* Wait queue */
DECL|member|sleep
id|wait_queue_t
id|sleep
suffix:semicolon
multiline_comment|/* For putting in the socket&squot;s waitqueue */
multiline_comment|/* HTTP request information */
DECL|member|FileName
r_char
id|FileName
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* The requested filename */
DECL|member|FileNameLength
r_int
id|FileNameLength
suffix:semicolon
multiline_comment|/* The length of the string representing the filename */
DECL|member|Agent
r_char
id|Agent
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* The agent-string of the remote browser */
DECL|member|IMS
r_char
id|IMS
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* If-modified-since time, rfc string format */
DECL|member|Host
r_char
id|Host
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Value given by the Host: header */
DECL|member|HTTPVER
r_int
id|HTTPVER
suffix:semicolon
multiline_comment|/* HTTP-version; 9 for 0.9,   10 for 1.0 and above */
multiline_comment|/* Derived date from the above fields */
DECL|member|IMS_Time
r_int
id|IMS_Time
suffix:semicolon
multiline_comment|/* if-modified-since time, unix format */
DECL|member|TimeS
r_char
id|TimeS
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* File mtime, rfc string representation */
DECL|member|LengthS
r_char
id|LengthS
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* File length, string representation */
DECL|member|MimeType
r_char
op_star
id|MimeType
suffix:semicolon
multiline_comment|/* Pointer to a string with the mime-type &n;&t;&t;&t;&t;&t;   based on the filename */
DECL|member|MimeLength
id|__kernel_size_t
id|MimeLength
suffix:semicolon
multiline_comment|/* The length of this string */
)brace
suffix:semicolon
multiline_comment|/*&n;&n;struct khttpd_threadinfo represents the four queues that 1 thread has to deal with.&n;It is padded to occupy 1 (Intel) cache-line, to avoid &quot;cacheline-pingpong&quot;.&n;&n;*/
DECL|struct|khttpd_threadinfo
r_struct
id|khttpd_threadinfo
(brace
DECL|member|WaitForHeaderQueue
r_struct
id|http_request
op_star
id|WaitForHeaderQueue
suffix:semicolon
DECL|member|DataSendingQueue
r_struct
id|http_request
op_star
id|DataSendingQueue
suffix:semicolon
DECL|member|LoggingQueue
r_struct
id|http_request
op_star
id|LoggingQueue
suffix:semicolon
DECL|member|UserspaceQueue
r_struct
id|http_request
op_star
id|UserspaceQueue
suffix:semicolon
DECL|member|dummy
r_char
id|dummy
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Padding for cache-lines */
)brace
suffix:semicolon
macro_line|#endif
eof
