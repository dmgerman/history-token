multiline_comment|/*&n; * Copyright, 2000, Silicon Graphics, sprasad@engr.sgi.com&n; */
DECL|macro|MAXNODES
mdefine_line|#define MAXNODES                16
DECL|macro|MAXNASIDS
mdefine_line|#define MAXNASIDS               16
DECL|macro|CHUNKSZ
mdefine_line|#define CHUNKSZ                (8*1024*1024)
DECL|macro|CHUNKSHIFT
mdefine_line|#define CHUNKSHIFT              23      /* 2 ^^ CHUNKSHIFT == CHUNKSZ */
DECL|macro|CNODEID_TO_NASID
mdefine_line|#define CNODEID_TO_NASID(n)&t;n
DECL|macro|NASID_TO_CNODEID
mdefine_line|#define NASID_TO_CNODEID(n)     n
DECL|macro|MAX_CHUNKS_PER_NODE
mdefine_line|#define MAX_CHUNKS_PER_NODE     8
eof
