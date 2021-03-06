/************************************************************************/
/* Generic PCM Conversion Utility Supp Defs: CvtSup.h   V2.00  08/15/95 */
/* Copyright (c) 1987-1995 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define USEERREND          1            /* User termination exit code   */
#define FORALLVER       TRUE            /* Function avail on all ver    */
#define CVTMAXSTR         40            /* Gen purpose string length    */

/************************************************************************/
/************************************************************************/
typedef struct _CFGBLK {                /* Configuration structure      */
    long        lNamOff;                /* Dest file name counter off   */
    char        szSrcCfg[FIOMAXNAM];    /* Input  config file name      */       
    char        szGloCfg[FIOMAXNAM];    /* Global config file name      */       
} CFGBLK;

/************************************************************************/
/************************************************************************/
char *  DshPrmLod (WORD, char **, CFGBLK *, CHPBLK *);
WORD    DshPrmRel (CHPBLK FAR *);
