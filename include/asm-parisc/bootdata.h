macro_line|#ifndef _PARISC_BOOTDATA_H
DECL|macro|_PARISC_BOOTDATA_H
mdefine_line|#define _PARISC_BOOTDATA_H
multiline_comment|/* structure given from bootloader... */
r_typedef
r_struct
(brace
DECL|member|data_valid_signature
r_int
id|data_valid_signature
comma
DECL|member|initrd_start
id|initrd_start
comma
DECL|member|initrd_end
id|initrd_end
suffix:semicolon
DECL|member|commandline
r_char
id|commandline
(braket
l_int|1024
)braket
suffix:semicolon
DECL|typedef|bootdata_t
)brace
id|bootdata_t
suffix:semicolon
DECL|macro|BOOTDATA_DATA_VALID_SIGNATURE
mdefine_line|#define BOOTDATA_DATA_VALID_SIGNATURE 0xC0400000
DECL|macro|BOOTDATA_PTR
mdefine_line|#define BOOTDATA_PTR ((bootdata_t*) 0xC0400000)
macro_line|#endif 
eof
