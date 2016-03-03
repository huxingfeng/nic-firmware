/**
 * Copyright (C) 2015,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file        blm_custom.h
 * @brief       A reasonable default buffer configuration file.
 *
 * This is a default header file to allow BLM for some sane default buffer
 * configurations (hopefully) for applications that do not wish to set their
 * own buffer configuration. Applications intending to customise BLM options
 * should define their own blm_custom.h and place it in a higher priority
 * include path than the libinfra provided one.
 */

#ifndef __NFP_BLM_CUSTOM_H__
#define __NFP_BLM_CUSTOM_H__

/* Explicitly enable BLM */
#ifndef BLM_BLQ_ENABLE_MASK
#define BLM_BLQ_ENABLE_MASK                     0
#endif

#define NBI8_BLQ_EMU_0_PKTBUF_SIZE              10240
#define NBI8_BLQ_EMU_1_PKTBUF_SIZE              10240
#define NBI8_BLQ_EMU_2_PKTBUF_SIZE              10240
#define NBI8_BLQ_EMU_3_PKTBUF_SIZE              10240
#define NBI9_BLQ_EMU_0_PKTBUF_SIZE              10240
#define NBI9_BLQ_EMU_1_PKTBUF_SIZE              10240
#define NBI9_BLQ_EMU_2_PKTBUF_SIZE              10240
#define NBI9_BLQ_EMU_3_PKTBUF_SIZE              10240

#define BLM_NBI8_BLQ0_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI8_BLQ1_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI8_BLQ2_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI8_BLQ3_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI9_BLQ0_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI9_BLQ1_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI9_BLQ2_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)
#define BLM_NBI9_BLQ3_EMU_Q_LOCALITY            (MU_LOCALITY_HIGH)

#define BLM_NBI8_BLQ0_EMU_Q_ISLAND              24
#define BLM_NBI8_BLQ1_EMU_Q_ISLAND              24
#define BLM_NBI8_BLQ2_EMU_Q_ISLAND              24
#define BLM_NBI8_BLQ3_EMU_Q_ISLAND              24

#define BLM_NBI9_BLQ0_EMU_Q_ISLAND              24
#define BLM_NBI9_BLQ1_EMU_Q_ISLAND              24
#define BLM_NBI9_BLQ2_EMU_Q_ISLAND              24
#define BLM_NBI9_BLQ3_EMU_Q_ISLAND              24

#if defined(__NFP_LANG_ASM)
    #ifndef BLM_BLQ_EMEM_TYPE
        #define BLM_BLQ_EMEM_TYPE               emem
    #endif
#else
    #ifndef BLM_BLQ_EMEM_TYPE
        #define BLM_BLQ_EMEM_TYPE               BLM_MEM_TYPE_EMEM
    #endif
#endif

#define BLM_NBI8_BLQ0_Q_SIZE                    8192
#define BLM_NBI8_BLQ1_Q_SIZE                    8192
#define BLM_NBI8_BLQ2_Q_SIZE                    2048
#define BLM_NBI8_BLQ3_Q_SIZE                    2048

#define BLM_NBI9_BLQ0_Q_SIZE                    2048
#define BLM_NBI9_BLQ1_Q_SIZE                    2048
#define BLM_NBI9_BLQ2_Q_SIZE                    2048
#define BLM_NBI9_BLQ3_Q_SIZE                    2048

/* EMU Rings buffers configuration */

/* NBI8 BLQs */
#define BLM_NBI8_BLQ0_LEN                       1024
#define BLM_NBI8_BLQ1_LEN                       1024
#define BLM_NBI8_BLQ2_LEN                       1024
#define BLM_NBI8_BLQ3_LEN                       1024

/* NBI9 BLQs */
#define BLM_NBI9_BLQ0_LEN                       1024
#define BLM_NBI9_BLQ1_LEN                       1024
#define BLM_NBI9_BLQ2_LEN                       1024
#define BLM_NBI9_BLQ3_LEN                       1024


/* EMU Ring 0 NBI8 */
#define BLM_NBI8_BLQ0_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI8_BLQ0_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ0_EMU_IMEM0_DENSITY         1
#define BLM_NBI8_BLQ0_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ0_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ0_EMU_IMEM1_DENSITY         0
#define BLM_NBI8_BLQ0_EMU_EMEM0_NUM_BUFS        600
#define BLM_NBI8_BLQ0_EMU_EMEM0_DENSITY         1
/* Explicitly enable BLM */
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM0_NUM_BUFS
#define BLM_NBI8_BLQ0_BDSRAM_EMEM0_NUM_BUFS     0
#endif
#ifdef USE_EMEM1
#define BLM_NBI8_BLQ0_EMU_EMEM1_NUM_BUFS        150
#define BLM_NBI8_BLQ0_EMU_EMEM1_DENSITY         1
#define BLM_NBI8_BLQ0_BDSRAM_EMEM1_NUM_BUFS     0
#else /* USE_EMEM1 */
#define BLM_NBI8_BLQ0_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ0_EMU_EMEM1_DENSITY         0
#define BLM_NBI8_BLQ0_BDSRAM_EMEM1_NUM_BUFS     0
#endif /* USE_EMEM1 */
#define BLM_NBI8_BLQ0_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI8_BLQ0_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI8_BLQ0_EMU_EMEM2_DENSITY         0


/* EMU Ring 0 NBI9 */
#define BLM_NBI9_BLQ0_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ0_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ0_EMU_IMEM0_DENSITY         0
#define BLM_NBI9_BLQ0_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ0_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ0_EMU_IMEM1_DENSITY         0
#define BLM_NBI9_BLQ0_EMU_EMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ0_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ0_EMU_EMEM0_DENSITY         0
#define BLM_NBI9_BLQ0_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ0_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ0_EMU_EMEM1_DENSITY         0
#define BLM_NBI9_BLQ0_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI9_BLQ0_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI9_BLQ0_EMU_EMEM2_DENSITY         0

/* EMU Ring 1 NBI8 */
#define BLM_NBI8_BLQ1_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI8_BLQ1_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ1_EMU_IMEM0_DENSITY         1
#define BLM_NBI8_BLQ1_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ1_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ1_EMU_IMEM1_DENSITY         0
#define BLM_NBI8_BLQ1_EMU_EMEM0_NUM_BUFS        600
#define BLM_NBI8_BLQ1_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ1_EMU_EMEM0_DENSITY         1
#ifdef USE_EMEM1
#define BLM_NBI8_BLQ1_EMU_EMEM1_NUM_BUFS        150
#define BLM_NBI8_BLQ1_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY         1
#else /* USE_EMEM1 */
#define BLM_NBI8_BLQ1_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ1_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY         0
#endif /* USE_EMEM1 */
#define BLM_NBI8_BLQ1_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI8_BLQ1_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI8_BLQ1_EMU_EMEM2_DENSITY         0

/* EMU Ring 1 NBI9 */
#define BLM_NBI9_BLQ1_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ1_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ1_EMU_IMEM0_DENSITY         0
#define BLM_NBI9_BLQ1_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ1_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ1_EMU_IMEM1_DENSITY         0
#define BLM_NBI9_BLQ1_EMU_EMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ1_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ1_EMU_EMEM0_DENSITY         0
#define BLM_NBI9_BLQ1_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ1_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ1_EMU_EMEM1_DENSITY         0
#define BLM_NBI9_BLQ1_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI9_BLQ1_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI9_BLQ1_EMU_EMEM2_DENSITY         0

/* EMU Ring 2 NBI8 */
#define BLM_NBI8_BLQ2_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI8_BLQ2_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ2_EMU_IMEM0_DENSITY         0
#define BLM_NBI8_BLQ2_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ2_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ2_EMU_IMEM1_DENSITY         0
#define BLM_NBI8_BLQ2_EMU_EMEM0_NUM_BUFS        0
#define BLM_NBI8_BLQ2_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ2_EMU_EMEM0_DENSITY         0
#define BLM_NBI8_BLQ2_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ2_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ2_EMU_EMEM1_DENSITY         0
#define BLM_NBI8_BLQ2_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI8_BLQ2_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI8_BLQ2_EMU_EMEM2_DENSITY         0
/* EMU Ring 2 NBI9 */
#define BLM_NBI9_BLQ2_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ2_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ2_EMU_IMEM0_DENSITY         0
#define BLM_NBI9_BLQ2_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ2_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ2_EMU_IMEM1_DENSITY         0
#define BLM_NBI9_BLQ2_EMU_EMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ2_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ2_EMU_EMEM0_DENSITY         0
#define BLM_NBI9_BLQ2_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ2_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ2_EMU_EMEM1_DENSITY         0
#define BLM_NBI9_BLQ2_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI9_BLQ2_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI9_BLQ2_EMU_EMEM2_DENSITY         0

/* EMU Ring 3 NBI8 */
#define BLM_NBI8_BLQ3_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI8_BLQ3_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ3_EMU_IMEM0_DENSITY         0
#define BLM_NBI8_BLQ3_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ3_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ3_EMU_IMEM1_DENSITY         0
#define BLM_NBI8_BLQ3_EMU_EMEM0_NUM_BUFS        0
#define BLM_NBI8_BLQ3_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI8_BLQ3_EMU_EMEM0_DENSITY         0
#define BLM_NBI8_BLQ3_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI8_BLQ3_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI8_BLQ3_EMU_EMEM1_DENSITY         0
#define BLM_NBI8_BLQ3_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI8_BLQ3_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI8_BLQ3_EMU_EMEM2_DENSITY         0
/* EMU Ring 3 NBI9 */
#define BLM_NBI9_BLQ3_EMU_IMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ3_BDSRAM_IMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ3_EMU_IMEM0_DENSITY         0
#define BLM_NBI9_BLQ3_EMU_IMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ3_BDSRAM_IMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ3_EMU_IMEM1_DENSITY         0
#define BLM_NBI9_BLQ3_EMU_EMEM0_NUM_BUFS        0
#define BLM_NBI9_BLQ3_BDSRAM_EMEM0_NUM_BUFS     0
#define BLM_NBI9_BLQ3_EMU_EMEM0_DENSITY         0
#define BLM_NBI9_BLQ3_EMU_EMEM1_NUM_BUFS        0
#define BLM_NBI9_BLQ3_BDSRAM_EMEM1_NUM_BUFS     0
#define BLM_NBI9_BLQ3_EMU_EMEM1_DENSITY         0
#define BLM_NBI9_BLQ3_EMU_EMEM2_NUM_BUFS        0
#define BLM_NBI9_BLQ3_BDSRAM_EMEM2_NUM_BUFS     0
#define BLM_NBI9_BLQ3_EMU_EMEM2_DENSITY         0

#endif // __NFP_BLM_CONFIG_H__