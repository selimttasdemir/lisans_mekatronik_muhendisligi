//Function declaration for ADuC831.lib file for Keil tools.
extern char PllDly(int);
extern char PllWcd(char);
extern char PllRcd(void);
extern char UrtCfg(char, unsigned int);
extern char UrtBsy(void);
extern char AdcCfg(char);
extern char AdcBsy(void);
extern char AdcGo(char, char);
extern int AdcRd(void);
extern int AdcGet(char);
extern char AdcCal(char);
extern char DacCfg(char);
extern char DacOut(char, int);
extern char TicCfg(char);
extern char TicGo(char, char, char, char);
extern char TicHr(void);
extern char TicMin(void);
extern char TicSec(void);
extern char TicHth(void);
extern char TicVal(char, char);
extern char PwmCfg(char);
extern char PwmW16(char, int);
extern char PwmW8(char, char, char);

//Variable declaration for ADuC831.lib file.
char data	cUrtVar;

//Declaration End====================================================Declaration End