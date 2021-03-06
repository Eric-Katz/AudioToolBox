/************************************************************************/
/* File I/O Utilities Defs: FilUtl.h                    V2.00  07/15/94 */
/* Copyright (c) 1987-1994 Andrew J. Michalik                           */
/*                                                                      */
/************************************************************************/
#define FIOMAXNAM   256

/************************************************************************/
/*                      Extended error codes                            */
/************************************************************************/
#define FIO_E_UNK           0xffff          /* Unknown I/O error        */
#define FIO_E_ABT           0xfff0          /* I/O aborted              */

/************************************************************************/
/*                  Copy / Shift Direction Flags                        */
/************************************************************************/
typedef enum _FIODIR {
    FIODIRREV = -1,                     /* Copy back to front           */
    FIODIRUNK =  0,                     /* Unknown / don't care         */
    FIODIRFWD = +1,                     /* Copy forward to front        */
} FIODIR;

/************************************************************************/
/*                  Callback procedure definitions                      */
/************************************************************************/
#if	!defined (FIOVERNUM)
typedef enum _FIOPOL {
    FIOPOLBEG,                              /* Begin poll operation     */
    FIOPOLCNT,                              /* Continue poll operation  */
    FIOPOLPOS,                              /* Position poll operation  */
    FIOPOLEMP,                              /* Empty poll operation     */
    FIOPOLEND                               /* End poll operation       */
} FIOPOL;
typedef WORD (far pascal *FIOPOLPRC)(FIOPOL,DWORD,DWORD);
#endif

/************************************************************************/
/*              Find File Header & Records Definitions                  */
/************************************************************************/
#define LSTBUFSIZ   (WORD) 0x8000
#define LSTPTRCNT   (WORD) 0x2000

typedef int ((*FNDSRTCBK) (const void *, const void *));
typedef struct _LSTSPC {
    char   *szNamBuf;                   /* File name list / handle      */
    WORD    usBufSiz;                   /* File name list size          */
    char  **paPtrArr;                   /* File name ptrs / offsets     */
    WORD    usIdxCur;                   /* Current list selection       */
    WORD    usIdxCnt;                   /* File name ptrs max count     */
} LSTSPC;

WORD    GetFstFil (char *, WORD, char *, LSTSPC *, FNDSRTCBK);
WORD    GetNxtFil (char *, LSTSPC *);
void    EndFilLst (LSTSPC *);
char *  GetFulPth (char *, char *, char *); 
char *  GetWldNam (const char *, const char *, char *);
int     xchdir (char *);
WORD    xsetdrive (char, char *); 
char *  xgetdcwd (char *, int);

/************************************************************************/
/*                      Function Prototypes                             */
/************************************************************************/
#define BFRBKIFLG   0x0002              /* Backup inhibit flag          */
#define BFRDATFLG   0x0008              /* Date preserve flag           */

typedef BOOL  ((far pascal *BFRCHKFNC) (const char far *, void far *));
typedef DWORD ((far pascal *BFRREPFNC) (short, short, const char far *, const char far *, char far *, WORD, void far *)); 
typedef BOOL  ((far pascal *BFRENDFNC) (DWORD, void far *));
WORD    far pascal BinFilRep (char *, char *, WORD, BFRCHKFNC, BFRREPFNC, BFRENDFNC, FNDSRTCBK, void far *);
DWORD   far pascal RepSrcToD (const char *, const char *, WORD, char far *, WORD, BFRREPFNC, void far *);

/************************************************************************/
/************************************************************************/
short   far pascal FilHdlOpn (const char far *, unsigned short);
short   far pascal FilHdlCre (const char far *, unsigned short, unsigned short);
short   far pascal FilHdlCls (short);
long    far pascal FilGetPos (short);
long    far pascal FilSetPos (short, long, unsigned short);
long    far pascal FilGetLen (short);
short   far pascal FilGetSta (const char far *, struct _stat far *);

/************************************************************************/
/************************************************************************/
#define FIOENCINP   0x8000              /* Input  file encode           */ 
#define FIOENCOUT   0x2000              /* Output file encode           */ 
#define FIOENCSWP   0x0800              /* Encode type: b/n/b/w swap    */ 
#define FIOENCKEY   0x0200              /* Encode type: key encode      */ 
#define FIOENCNON   0x0000              /* No     file encode           */ 
#define FIOSWPMSK   0x00ff              /* Swap selection mask          */
#define FIOSWPBIT   0x0002              /* Swap bit    selection        */
#define FIOSWPNIB   0x0004              /* Swap nibble selection        */
#define FIOSWPBYT   0x0008              /* Swap nibble selection        */
#define FIOSWPWRD   0x0010              /* Swap nibble selection        */
#define FIOKEYMSK   0x0007              /* Encoding key selection mask  */

long far pascal FilCop (short, short, char far *, WORD, DWORD, WORD,
                unsigned int far *, FIOPOLPRC, DWORD);
long far pascal FilDup (short, short, char far *, WORD, WORD, 
                unsigned int far *, FIOPOLPRC, DWORD);
long far pascal FilMov (const char *, const char *, char far *, WORD, BOOL, 
                unsigned int far *, FIOPOLPRC, DWORD);
long far pascal FilShf (short, short, char far *, WORD, DWORD, DWORD, FIODIR, 
                unsigned int far *, FIOPOLPRC, DWORD);
long far pascal FilSiz (short, long, long, unsigned int far *, FIOPOLPRC, DWORD);

unsigned int    Rd_FilFwd (int, void far *, unsigned int, unsigned int, unsigned int far *);
unsigned int    Rd_FilRev (int, void far *, unsigned int, unsigned int, unsigned int far *);
unsigned int    Wr_FilFwd (int, void far *, unsigned int, unsigned int, unsigned int far *);
unsigned int    Wr_FilRev (int, void far *, unsigned int, unsigned int, unsigned int far *);
unsigned int    Wr_FilCom (int);
