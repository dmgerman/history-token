macro_line|#ifndef _ISOFS_FS_H
DECL|macro|_ISOFS_FS_H
mdefine_line|#define _ISOFS_FS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * The isofs filesystem constants/structures&n; */
multiline_comment|/* This part borrowed from the bsd386 isofs */
DECL|macro|ISODCL
mdefine_line|#define ISODCL(from, to) (to - from + 1)
DECL|struct|iso_volume_descriptor
r_struct
id|iso_volume_descriptor
(brace
DECL|member|type
r_char
id|type
(braket
id|ISODCL
c_func
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
c_func
(paren
l_int|2
comma
l_int|6
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
c_func
(paren
l_int|7
comma
l_int|7
)paren
)braket
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
id|ISODCL
c_func
(paren
l_int|8
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* volume descriptor types */
DECL|macro|ISO_VD_PRIMARY
mdefine_line|#define ISO_VD_PRIMARY 1
DECL|macro|ISO_VD_SUPPLEMENTARY
mdefine_line|#define ISO_VD_SUPPLEMENTARY 2
DECL|macro|ISO_VD_END
mdefine_line|#define ISO_VD_END 255
DECL|macro|ISO_STANDARD_ID
mdefine_line|#define ISO_STANDARD_ID &quot;CD001&quot;
DECL|struct|iso_primary_descriptor
r_struct
id|iso_primary_descriptor
(brace
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|2
comma
l_int|6
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|7
comma
l_int|7
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused1
r_char
id|unused1
(braket
id|ISODCL
(paren
l_int|8
comma
l_int|8
)paren
)braket
suffix:semicolon
DECL|member|system_id
r_char
id|system_id
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|40
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|volume_id
r_char
id|volume_id
(braket
id|ISODCL
(paren
l_int|41
comma
l_int|72
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|unused2
r_char
id|unused2
(braket
id|ISODCL
(paren
l_int|73
comma
l_int|80
)paren
)braket
suffix:semicolon
DECL|member|volume_space_size
r_char
id|volume_space_size
(braket
id|ISODCL
(paren
l_int|81
comma
l_int|88
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|unused3
r_char
id|unused3
(braket
id|ISODCL
(paren
l_int|89
comma
l_int|120
)paren
)braket
suffix:semicolon
DECL|member|volume_set_size
r_char
id|volume_set_size
(braket
id|ISODCL
(paren
l_int|121
comma
l_int|124
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|125
comma
l_int|128
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|logical_block_size
r_char
id|logical_block_size
(braket
id|ISODCL
(paren
l_int|129
comma
l_int|132
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|path_table_size
r_char
id|path_table_size
(braket
id|ISODCL
(paren
l_int|133
comma
l_int|140
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type_l_path_table
r_char
id|type_l_path_table
(braket
id|ISODCL
(paren
l_int|141
comma
l_int|144
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|opt_type_l_path_table
r_char
id|opt_type_l_path_table
(braket
id|ISODCL
(paren
l_int|145
comma
l_int|148
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|type_m_path_table
r_char
id|type_m_path_table
(braket
id|ISODCL
(paren
l_int|149
comma
l_int|152
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|opt_type_m_path_table
r_char
id|opt_type_m_path_table
(braket
id|ISODCL
(paren
l_int|153
comma
l_int|156
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|root_directory_record
r_char
id|root_directory_record
(braket
id|ISODCL
(paren
l_int|157
comma
l_int|190
)paren
)braket
suffix:semicolon
multiline_comment|/* 9.1 */
DECL|member|volume_set_id
r_char
id|volume_set_id
(braket
id|ISODCL
(paren
l_int|191
comma
l_int|318
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|publisher_id
r_char
id|publisher_id
(braket
id|ISODCL
(paren
l_int|319
comma
l_int|446
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|preparer_id
r_char
id|preparer_id
(braket
id|ISODCL
(paren
l_int|447
comma
l_int|574
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|application_id
r_char
id|application_id
(braket
id|ISODCL
(paren
l_int|575
comma
l_int|702
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|copyright_file_id
r_char
id|copyright_file_id
(braket
id|ISODCL
(paren
l_int|703
comma
l_int|739
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|abstract_file_id
r_char
id|abstract_file_id
(braket
id|ISODCL
(paren
l_int|740
comma
l_int|776
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|bibliographic_file_id
r_char
id|bibliographic_file_id
(braket
id|ISODCL
(paren
l_int|777
comma
l_int|813
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|creation_date
r_char
id|creation_date
(braket
id|ISODCL
(paren
l_int|814
comma
l_int|830
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|modification_date
r_char
id|modification_date
(braket
id|ISODCL
(paren
l_int|831
comma
l_int|847
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|expiration_date
r_char
id|expiration_date
(braket
id|ISODCL
(paren
l_int|848
comma
l_int|864
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|effective_date
r_char
id|effective_date
(braket
id|ISODCL
(paren
l_int|865
comma
l_int|881
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|file_structure_version
r_char
id|file_structure_version
(braket
id|ISODCL
(paren
l_int|882
comma
l_int|882
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused4
r_char
id|unused4
(braket
id|ISODCL
(paren
l_int|883
comma
l_int|883
)paren
)braket
suffix:semicolon
DECL|member|application_data
r_char
id|application_data
(braket
id|ISODCL
(paren
l_int|884
comma
l_int|1395
)paren
)braket
suffix:semicolon
DECL|member|unused5
r_char
id|unused5
(braket
id|ISODCL
(paren
l_int|1396
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Almost the same as the primary descriptor but two fields are specified */
DECL|struct|iso_supplementary_descriptor
r_struct
id|iso_supplementary_descriptor
(brace
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|2
comma
l_int|6
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|7
comma
l_int|7
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|flags
r_char
id|flags
(braket
id|ISODCL
(paren
l_int|8
comma
l_int|8
)paren
)braket
suffix:semicolon
multiline_comment|/* 853 */
DECL|member|system_id
r_char
id|system_id
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|40
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|volume_id
r_char
id|volume_id
(braket
id|ISODCL
(paren
l_int|41
comma
l_int|72
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|unused2
r_char
id|unused2
(braket
id|ISODCL
(paren
l_int|73
comma
l_int|80
)paren
)braket
suffix:semicolon
DECL|member|volume_space_size
r_char
id|volume_space_size
(braket
id|ISODCL
(paren
l_int|81
comma
l_int|88
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|escape
r_char
id|escape
(braket
id|ISODCL
(paren
l_int|89
comma
l_int|120
)paren
)braket
suffix:semicolon
multiline_comment|/* 856 */
DECL|member|volume_set_size
r_char
id|volume_set_size
(braket
id|ISODCL
(paren
l_int|121
comma
l_int|124
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|125
comma
l_int|128
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|logical_block_size
r_char
id|logical_block_size
(braket
id|ISODCL
(paren
l_int|129
comma
l_int|132
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|path_table_size
r_char
id|path_table_size
(braket
id|ISODCL
(paren
l_int|133
comma
l_int|140
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type_l_path_table
r_char
id|type_l_path_table
(braket
id|ISODCL
(paren
l_int|141
comma
l_int|144
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|opt_type_l_path_table
r_char
id|opt_type_l_path_table
(braket
id|ISODCL
(paren
l_int|145
comma
l_int|148
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|type_m_path_table
r_char
id|type_m_path_table
(braket
id|ISODCL
(paren
l_int|149
comma
l_int|152
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|opt_type_m_path_table
r_char
id|opt_type_m_path_table
(braket
id|ISODCL
(paren
l_int|153
comma
l_int|156
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|root_directory_record
r_char
id|root_directory_record
(braket
id|ISODCL
(paren
l_int|157
comma
l_int|190
)paren
)braket
suffix:semicolon
multiline_comment|/* 9.1 */
DECL|member|volume_set_id
r_char
id|volume_set_id
(braket
id|ISODCL
(paren
l_int|191
comma
l_int|318
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|publisher_id
r_char
id|publisher_id
(braket
id|ISODCL
(paren
l_int|319
comma
l_int|446
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|preparer_id
r_char
id|preparer_id
(braket
id|ISODCL
(paren
l_int|447
comma
l_int|574
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|application_id
r_char
id|application_id
(braket
id|ISODCL
(paren
l_int|575
comma
l_int|702
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|copyright_file_id
r_char
id|copyright_file_id
(braket
id|ISODCL
(paren
l_int|703
comma
l_int|739
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|abstract_file_id
r_char
id|abstract_file_id
(braket
id|ISODCL
(paren
l_int|740
comma
l_int|776
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|bibliographic_file_id
r_char
id|bibliographic_file_id
(braket
id|ISODCL
(paren
l_int|777
comma
l_int|813
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|creation_date
r_char
id|creation_date
(braket
id|ISODCL
(paren
l_int|814
comma
l_int|830
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|modification_date
r_char
id|modification_date
(braket
id|ISODCL
(paren
l_int|831
comma
l_int|847
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|expiration_date
r_char
id|expiration_date
(braket
id|ISODCL
(paren
l_int|848
comma
l_int|864
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|effective_date
r_char
id|effective_date
(braket
id|ISODCL
(paren
l_int|865
comma
l_int|881
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|file_structure_version
r_char
id|file_structure_version
(braket
id|ISODCL
(paren
l_int|882
comma
l_int|882
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused4
r_char
id|unused4
(braket
id|ISODCL
(paren
l_int|883
comma
l_int|883
)paren
)braket
suffix:semicolon
DECL|member|application_data
r_char
id|application_data
(braket
id|ISODCL
(paren
l_int|884
comma
l_int|1395
)paren
)braket
suffix:semicolon
DECL|member|unused5
r_char
id|unused5
(braket
id|ISODCL
(paren
l_int|1396
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HS_STANDARD_ID
mdefine_line|#define HS_STANDARD_ID &quot;CDROM&quot;
DECL|struct|hs_volume_descriptor
r_struct
id|hs_volume_descriptor
(brace
DECL|member|foo
r_char
id|foo
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|8
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|9
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|10
comma
l_int|14
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|15
comma
l_int|15
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|data
r_char
id|data
(braket
id|ISODCL
c_func
(paren
l_int|16
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hs_primary_descriptor
r_struct
id|hs_primary_descriptor
(brace
DECL|member|foo
r_char
id|foo
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|8
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|9
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|10
comma
l_int|14
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|15
comma
l_int|15
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused1
r_char
id|unused1
(braket
id|ISODCL
(paren
l_int|16
comma
l_int|16
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|system_id
r_char
id|system_id
(braket
id|ISODCL
(paren
l_int|17
comma
l_int|48
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|volume_id
r_char
id|volume_id
(braket
id|ISODCL
(paren
l_int|49
comma
l_int|80
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|unused2
r_char
id|unused2
(braket
id|ISODCL
(paren
l_int|81
comma
l_int|88
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|volume_space_size
r_char
id|volume_space_size
(braket
id|ISODCL
(paren
l_int|89
comma
l_int|96
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|unused3
r_char
id|unused3
(braket
id|ISODCL
(paren
l_int|97
comma
l_int|128
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|volume_set_size
r_char
id|volume_set_size
(braket
id|ISODCL
(paren
l_int|129
comma
l_int|132
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|133
comma
l_int|136
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|logical_block_size
r_char
id|logical_block_size
(braket
id|ISODCL
(paren
l_int|137
comma
l_int|140
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|path_table_size
r_char
id|path_table_size
(braket
id|ISODCL
(paren
l_int|141
comma
l_int|148
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type_l_path_table
r_char
id|type_l_path_table
(braket
id|ISODCL
(paren
l_int|149
comma
l_int|152
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|unused4
r_char
id|unused4
(braket
id|ISODCL
(paren
l_int|153
comma
l_int|180
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|root_directory_record
r_char
id|root_directory_record
(braket
id|ISODCL
(paren
l_int|181
comma
l_int|214
)paren
)braket
suffix:semicolon
multiline_comment|/* 9.1 */
)brace
suffix:semicolon
multiline_comment|/* We use this to help us look up the parent inode numbers. */
DECL|struct|iso_path_table
r_struct
id|iso_path_table
(brace
DECL|member|name_len
r_int
r_char
id|name_len
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 721 */
DECL|member|extent
r_char
id|extent
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|parent
r_char
id|parent
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 721 */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* high sierra is identical to iso, except that the date is only 6 bytes, and&n;   there is an extra reserved byte after the flags */
DECL|struct|iso_directory_record
r_struct
id|iso_directory_record
(brace
DECL|member|length
r_char
id|length
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|ext_attr_length
r_char
id|ext_attr_length
(braket
id|ISODCL
(paren
l_int|2
comma
l_int|2
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|extent
r_char
id|extent
(braket
id|ISODCL
(paren
l_int|3
comma
l_int|10
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|size
r_char
id|size
(braket
id|ISODCL
(paren
l_int|11
comma
l_int|18
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|date
r_char
id|date
(braket
id|ISODCL
(paren
l_int|19
comma
l_int|25
)paren
)braket
suffix:semicolon
multiline_comment|/* 7 by 711 */
DECL|member|flags
r_char
id|flags
(braket
id|ISODCL
(paren
l_int|26
comma
l_int|26
)paren
)braket
suffix:semicolon
DECL|member|file_unit_size
r_char
id|file_unit_size
(braket
id|ISODCL
(paren
l_int|27
comma
l_int|27
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|interleave
r_char
id|interleave
(braket
id|ISODCL
(paren
l_int|28
comma
l_int|28
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|29
comma
l_int|32
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|name_len
r_int
r_char
id|name_len
(braket
id|ISODCL
(paren
l_int|33
comma
l_int|33
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|ISOFS_BLOCK_BITS
mdefine_line|#define ISOFS_BLOCK_BITS 11
DECL|macro|ISOFS_BLOCK_SIZE
mdefine_line|#define ISOFS_BLOCK_SIZE 2048
DECL|macro|ISOFS_BUFFER_SIZE
mdefine_line|#define ISOFS_BUFFER_SIZE(INODE) ((INODE)-&gt;i_sb-&gt;s_blocksize)
DECL|macro|ISOFS_BUFFER_BITS
mdefine_line|#define ISOFS_BUFFER_BITS(INODE) ((INODE)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|ISOFS_SUPER_MAGIC
mdefine_line|#define ISOFS_SUPER_MAGIC 0x9660
macro_line|#ifdef __KERNEL__
multiline_comment|/* Number conversion inlines, named after the section in ISO 9660&n;   they correspond to. */
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;linux/iso_fs_i.h&gt;
macro_line|#include &lt;linux/iso_fs_sb.h&gt;
DECL|function|ISOFS_SB
r_static
r_inline
r_struct
id|isofs_sb_info
op_star
id|ISOFS_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
DECL|function|ISOFS_I
r_static
r_inline
r_struct
id|iso_inode_info
op_star
id|ISOFS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
r_struct
id|iso_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|isonum_711
r_static
r_inline
r_int
id|isonum_711
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_return
op_star
(paren
id|u8
op_star
)paren
id|p
suffix:semicolon
)brace
DECL|function|isonum_712
r_static
r_inline
r_int
id|isonum_712
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_return
op_star
(paren
id|s8
op_star
)paren
id|p
suffix:semicolon
)brace
DECL|function|isonum_721
r_static
r_inline
r_int
r_int
id|isonum_721
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_return
id|le16_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|isonum_722
r_static
r_inline
r_int
r_int
id|isonum_722
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_return
id|be16_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|isonum_723
r_static
r_inline
r_int
r_int
id|isonum_723
c_func
(paren
r_char
op_star
id|p
)paren
(brace
multiline_comment|/* Ignore bigendian datum due to broken mastering programs */
r_return
id|le16_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|isonum_731
r_static
r_inline
r_int
r_int
id|isonum_731
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_return
id|le32_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|isonum_732
r_static
r_inline
r_int
r_int
id|isonum_732
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_return
id|be32_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
)brace
DECL|function|isonum_733
r_static
r_inline
r_int
r_int
id|isonum_733
c_func
(paren
r_char
op_star
id|p
)paren
(brace
multiline_comment|/* Ignore bigendian datum due to broken mastering programs */
r_return
id|le32_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|iso_date
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|inode
suffix:semicolon
multiline_comment|/* To make gcc happy */
r_extern
r_int
id|parse_rock_ridge_inode
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_rock_ridge_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isofs_name_translate
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|get_joliet_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_int
r_char
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|get_acorn_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|isofs_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|nameidata
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|isofs_bread
c_func
(paren
r_struct
id|inode
op_star
comma
id|sector_t
)paren
suffix:semicolon
r_extern
r_int
id|isofs_get_blocks
c_func
(paren
r_struct
id|inode
op_star
comma
id|sector_t
comma
r_struct
id|buffer_head
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|isofs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/* Because the inode number is no longer relevant to finding the&n; * underlying meta-data for an inode, we are free to choose a more&n; * convenient 32-bit number as the inode number.  The inode numbering&n; * scheme was recommended by Sergey Vlasov and Eric Lammerts. */
DECL|function|isofs_get_ino
r_static
r_inline
r_int
r_int
id|isofs_get_ino
c_func
(paren
r_int
r_int
id|block
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|bufbits
)paren
(brace
r_return
(paren
id|block
op_lshift
(paren
id|bufbits
op_minus
l_int|5
)paren
)paren
op_or
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
)brace
multiline_comment|/* Every directory can have many redundant directory entries scattered&n; * throughout the directory tree.  First there is the directory entry&n; * with the name of the directory stored in the parent directory.&n; * Then, there is the &quot;.&quot; directory entry stored in the directory&n; * itself.  Finally, there are possibly many &quot;..&quot; directory entries&n; * stored in all the subdirectories.&n; *&n; * In order for the NFS get_parent() method to work and for the&n; * general consistency of the dcache, we need to make sure the&n; * &quot;i_iget5_block&quot; and &quot;i_iget5_offset&quot; all point to exactly one of&n; * the many redundant entries for each directory.  We normalize the&n; * block and offset by always making them point to the &quot;.&quot;  directory.&n; *&n; * Notice that we do not use the entry for the directory with the name&n; * that is located in the parent directory.  Even though choosing this&n; * first directory is more natural, it is much easier to find the &quot;.&quot;&n; * entry in the NFS get_parent() method because it is implicitly&n; * encoded in the &quot;extent + ext_attr_length&quot; fields of _all_ the&n; * redundant entries for the directory.  Thus, it can always be&n; * reached regardless of which directory entry you have in hand.&n; *&n; * This works because the &quot;.&quot; entry is simply the first directory&n; * record when you start reading the file that holds all the directory&n; * records, and this file starts at &quot;extent + ext_attr_length&quot; blocks.&n; * Because the &quot;.&quot; entry is always the first entry listed in the&n; * directories file, the normalized &quot;offset&quot; value is always 0.&n; *&n; * You should pass the directory entry in &quot;de&quot;.  On return, &quot;block&quot;&n; * and &quot;offset&quot; will hold normalized values.  Only directories are&n; * affected making it safe to call even for non-directory file&n; * types. */
r_static
r_inline
r_void
DECL|function|isofs_normalize_block_and_offset
id|isofs_normalize_block_and_offset
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_int
r_int
op_star
id|block
comma
r_int
r_int
op_star
id|offset
)paren
(brace
multiline_comment|/* Only directories are normalized. */
r_if
c_cond
(paren
id|de-&gt;flags
(braket
l_int|0
)braket
op_amp
l_int|2
)paren
(brace
op_star
id|offset
op_assign
l_int|0
suffix:semicolon
op_star
id|block
op_assign
(paren
r_int
r_int
)paren
id|isonum_733
c_func
(paren
id|de-&gt;extent
)paren
op_plus
(paren
r_int
r_int
)paren
id|isonum_711
c_func
(paren
id|de-&gt;ext_attr_length
)paren
suffix:semicolon
)brace
)brace
r_extern
r_struct
id|inode_operations
id|isofs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|isofs_dir_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|isofs_symlink_aops
suffix:semicolon
r_extern
r_struct
id|export_operations
id|isofs_export_ops
suffix:semicolon
multiline_comment|/* The following macros are used to check for memory leaks. */
macro_line|#ifdef LEAK_CHECK
DECL|macro|free_s
mdefine_line|#define free_s leak_check_free_s
DECL|macro|malloc
mdefine_line|#define malloc leak_check_malloc
DECL|macro|sb_bread
mdefine_line|#define sb_bread leak_check_bread
DECL|macro|brelse
mdefine_line|#define brelse leak_check_brelse
r_extern
r_void
op_star
id|leak_check_malloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|leak_check_free_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|leak_check_bread
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_void
id|leak_check_brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
macro_line|#endif /* LEAK_CHECK */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
