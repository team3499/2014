#ifndef CONST_H
#define CONST_H

// SmartDashboard macros: n = name, x = value
#define SD_PN(n, x) SmartDashboard::PutNumber(n, x)
#define SD_GN(n)    SmartDashboard::GetNumber(n)

#define SD_PB(n, x) SmartDashboard::PutBoolean(n, x)
#define SD_GB(n)    SmartDashboard::GetBoolean(n)

#define SD_PS(n, x) SmartDashboard::PutString(n, x)
#define SD_GS(n)    SmartDashboard::GetString(n)

#define OUT(A) printf("$$FRC3499$$ - " A "\n"); fflush(stdout)
#define VOUT(A) printf("$$FRC3499$$ - %s\n", A); fflush(stdout)

#define absf(x) 	(x > 0 ? x : -x)
#define maxf(x, y)	(x > y ? x : y)

#endif // CONST_H
