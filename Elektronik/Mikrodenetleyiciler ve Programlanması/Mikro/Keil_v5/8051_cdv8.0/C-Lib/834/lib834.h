//Function declaration for ADuC834.lib file for Keil tools.
extern char PllDly(int);
extern char PllWcd(char);
extern char PllRcd(void);
extern char PllOpd(char);
extern char PllFst(char);
extern char PllLk(void);
extern char UrtCfg(char, int);
extern char UrtBsy(void);
extern char AdcCfg(char, char, char);
extern char* AdcAdr(void);
extern char AdcGo(char);
extern long AdcRd(char);
extern char AdcErr(void);
extern long AdcGet(int*);
extern char DacCfg(char);
extern char DacOut(int);
extern char TicCfg(char);
extern char TicGo(char, char, char, char);
extern char TicHr(void);
extern char TicMin(void);
extern char TicSec(void);
extern char TicHth(void);
extern char TicVal(char, char);

//Variable declaration for ADuC834.lib file.
char data	cUrtVar;
char data	pcAdcBuf[6];

//Declaration End====================================================Declaration End