multiline_comment|/*&n; *&t;File with in-memory structures of old quota format&n; */
macro_line|#ifndef _LINUX_DQBLK_V1_H
DECL|macro|_LINUX_DQBLK_V1_H
mdefine_line|#define _LINUX_DQBLK_V1_H
multiline_comment|/* Id of quota format */
DECL|macro|QFMT_VFS_OLD
mdefine_line|#define QFMT_VFS_OLD 1
multiline_comment|/* Root squash turned on */
DECL|macro|V1_DQF_RSQUASH
mdefine_line|#define V1_DQF_RSQUASH 1
multiline_comment|/* Special information about quotafile */
DECL|struct|v1_mem_dqinfo
r_struct
id|v1_mem_dqinfo
(brace
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_DQBLK_V1_H */
eof
