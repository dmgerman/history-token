macro_line|#ifndef _ASM_PERF_H_
DECL|macro|_ASM_PERF_H_
mdefine_line|#define _ASM_PERF_H_
multiline_comment|/* ioctls */
DECL|macro|PA_PERF_ON
mdefine_line|#define PA_PERF_ON&t;_IO(&squot;p&squot;, 1)
DECL|macro|PA_PERF_OFF
mdefine_line|#define PA_PERF_OFF&t;_IOR(&squot;p&squot;, 2, unsigned int)
DECL|macro|PA_PERF_VERSION
mdefine_line|#define PA_PERF_VERSION&t;_IOR(&squot;p&squot;, 3, int)
DECL|macro|PA_PERF_DEV
mdefine_line|#define PA_PERF_DEV&t;&quot;perf&quot;
DECL|macro|PA_PERF_MINOR
mdefine_line|#define PA_PERF_MINOR&t;146
multiline_comment|/* Interface types */
DECL|macro|UNKNOWN_INTF
mdefine_line|#define UNKNOWN_INTF    255
DECL|macro|ONYX_INTF
mdefine_line|#define ONYX_INTF         0
DECL|macro|CUDA_INTF
mdefine_line|#define CUDA_INTF         1
multiline_comment|/* Common Onyx and Cuda images */
DECL|macro|CPI
mdefine_line|#define CPI                 0
DECL|macro|BUSUTIL
mdefine_line|#define BUSUTIL             1
DECL|macro|TLBMISS
mdefine_line|#define TLBMISS             2
DECL|macro|TLBHANDMISS
mdefine_line|#define TLBHANDMISS         3
DECL|macro|PTKN
mdefine_line|#define PTKN                4
DECL|macro|PNTKN
mdefine_line|#define PNTKN               5
DECL|macro|IMISS
mdefine_line|#define IMISS               6
DECL|macro|DMISS
mdefine_line|#define DMISS               7
DECL|macro|DMISS_ACCESS
mdefine_line|#define DMISS_ACCESS        8 
DECL|macro|BIG_CPI
mdefine_line|#define BIG_CPI &t;    9
DECL|macro|BIG_LS
mdefine_line|#define BIG_LS&t;&t;   10  
DECL|macro|BR_ABORT
mdefine_line|#define BR_ABORT&t;   11
DECL|macro|ISNT
mdefine_line|#define ISNT&t;&t;   12 
DECL|macro|QUADRANT
mdefine_line|#define QUADRANT           13
DECL|macro|RW_PDFET
mdefine_line|#define RW_PDFET           14
DECL|macro|RW_WDFET
mdefine_line|#define RW_WDFET           15
DECL|macro|SHLIB_CPI
mdefine_line|#define SHLIB_CPI          16
multiline_comment|/* Cuda only Images */
DECL|macro|FLOPS
mdefine_line|#define FLOPS              17
DECL|macro|CACHEMISS
mdefine_line|#define CACHEMISS          18 
DECL|macro|BRANCHES
mdefine_line|#define BRANCHES           19             
DECL|macro|CRSTACK
mdefine_line|#define CRSTACK            20 
DECL|macro|I_CACHE_SPEC
mdefine_line|#define I_CACHE_SPEC       21 
DECL|macro|MAX_CUDA_IMAGES
mdefine_line|#define MAX_CUDA_IMAGES    22 
multiline_comment|/* Onyx only Images */
DECL|macro|ADDR_INV_ABORT_ALU
mdefine_line|#define ADDR_INV_ABORT_ALU 17
DECL|macro|BRAD_STALL
mdefine_line|#define BRAD_STALL&t;   18 
DECL|macro|CNTL_IN_PIPEL
mdefine_line|#define CNTL_IN_PIPEL&t;   19 
DECL|macro|DSNT_XFH
mdefine_line|#define DSNT_XFH&t;   20 
DECL|macro|FET_SIG1
mdefine_line|#define FET_SIG1&t;   21 
DECL|macro|FET_SIG2
mdefine_line|#define FET_SIG2&t;   22 
DECL|macro|G7_1
mdefine_line|#define G7_1&t;&t;   23 
DECL|macro|G7_2
mdefine_line|#define G7_2&t;&t;   24 
DECL|macro|G7_3
mdefine_line|#define G7_3 &t;&t;   25
DECL|macro|G7_4
mdefine_line|#define G7_4&t;&t;   26
DECL|macro|MPB_LABORT
mdefine_line|#define MPB_LABORT         27
DECL|macro|PANIC
mdefine_line|#define PANIC              28
DECL|macro|RARE_INST
mdefine_line|#define RARE_INST          29 
DECL|macro|RW_DFET
mdefine_line|#define RW_DFET            30 
DECL|macro|RW_IFET
mdefine_line|#define RW_IFET            31 
DECL|macro|RW_SDFET
mdefine_line|#define RW_SDFET           32 
DECL|macro|SPEC_IFET
mdefine_line|#define SPEC_IFET          33 
DECL|macro|ST_COND0
mdefine_line|#define ST_COND0           34 
DECL|macro|ST_COND1
mdefine_line|#define ST_COND1           35 
DECL|macro|ST_COND2
mdefine_line|#define ST_COND2           36
DECL|macro|ST_COND3
mdefine_line|#define ST_COND3           37
DECL|macro|ST_COND4
mdefine_line|#define ST_COND4           38
DECL|macro|ST_UNPRED0
mdefine_line|#define ST_UNPRED0         39 
DECL|macro|ST_UNPRED1
mdefine_line|#define ST_UNPRED1         40 
DECL|macro|UNPRED
mdefine_line|#define UNPRED             41 
DECL|macro|GO_STORE
mdefine_line|#define GO_STORE           42
DECL|macro|SHLIB_CALL
mdefine_line|#define SHLIB_CALL         43
DECL|macro|MAX_ONYX_IMAGES
mdefine_line|#define MAX_ONYX_IMAGES    44
macro_line|#endif
eof
