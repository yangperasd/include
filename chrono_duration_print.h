/*************************************************************************
  > File Name: chrono_duration_print.h
  > Author: yang 
  > Mail: yangperasd@163.com 
  > Created Time: Fri 18 Mar 2016 09:32:21 PM HKT
 ************************************************************************/

#ifndef _CHRONO_DURATION_PRINT_H
#define _CHRONO_DURATION_PRINT_H

#include "bash_color.h"
#include <chrono>
#include <iostream>
namespace yang
{
    template<typename Rep,typename Period>
        std::ostream& operator<<(std::ostream& out,std::chrono::duration<Rep,Period>& d)
        {/*{{{*/
            using namespace std::chrono;
            hours hh=duration_cast<hours>(d);
            minutes mm=duration_cast<minutes>(d%hours(1));
            seconds ss=duration_cast<seconds>(d%minutes(1));
            milliseconds msec=duration_cast<milliseconds>(d%seconds(1));
            if(hh.count()>0)
            {
                out<<hh.count()<<BASH_GREEN "h" BASH_CLEAR
                    <<mm.count()<<BASH_GREEN "m" BASH_CLEAR;
            }
            else if(mm.count()>0)
            {
                out<<mm.count()<<BASH_GREEN "m" BASH_CLEAR
                    <<ss.count()<<BASH_GREEN "s" BASH_CLEAR;
            }
            else 
            {
                out<<(ss.count()>0?std::to_string(ss.count())+BASH_GREEN "s" BASH_CLEAR:"")
                    <<msec.count()<<BASH_GREEN "ms" BASH_CLEAR;
            }
            return out;
        }/*}}}*/

}
#endif
