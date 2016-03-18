/*************************************************************************
	> File Name: ./bash_color.h
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: Fri 18 Mar 2016 09:28:52 PM HKT
 ************************************************************************/

#ifndef _BASH_COLOR_H
#define _BASH_COLOR_H

//define some bash color 
#ifndef _WIN32
    #define BASH_RED "\033[0;31m"
    #define BASH_GREEN "\033[0;32m"
    #define BASH_YELLOW "\033[0;33m"
    #define BASH_CYAN "\033[0;36m"
    #define BASH_CLEAR "\033[0m"
#else 
    #define BASH_RED ""
    #define BASH_GREEN ""
    #define BASH_YELLOW ""
    #define BASH_CYAN ""
    #define BASH_CLEAR ""
#endif
    
#endif
