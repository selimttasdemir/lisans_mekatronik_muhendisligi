//Function declaration for ADuC841.lib file for Keil tools.

//File: lib841.h

extern char AdcCfg(char);
extern char AdcGo(char, char);
extern int AdcRd(void);
extern char AdcBsy(void);
extern int AdcGet(char);
extern char AdcCal(char);
extern char DacCfg(char);
extern char DacOut(char, int);
extern char PllDly(int);
extern char PwmCfg(char);
extern char PwmW16(char,int);
extern char PwmW8(char,char,char);
extern char TicCfg(char);
extern char TicHr(void);
extern char TicMin(void);
extern char TicSec(void);
extern char TicHth(void);
extern char TicVal(char,char);
extern char TicGo(char,char,char,char);
extern char UrtCfg(char, unsigned int);
extern char UrtBsy(void);
extern char WdtCfg(char);
extern char WdtKk(void);

//Variable declaration for ADuC841.lib file.
char data	cUrtVar;
char data	cSpiFlag;


//Declaration End====================================================Declaration End


