/*************************************************************************
  > File Name: ./include/bashColorLayout.h
  > Author: yang 
  > Mail: yangperasd@163.com 
  > Created Time: Mon 21 Mar 2016 03:59:41 PM HKT
 ************************************************************************/

#ifndef _BASHCOLORLAYOUT_H
#define _BASHCOLORLAYOUT_H
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Layout.hh>
#include "bash_color.h"
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <array>
using std::string;

namespace yang
{
    /*
    class msgProxy;
    msgProxy& endL(msgProxy& proxy);
*/
    class LOG
    {
        /* 
        protected: 
        class msgProxy;
    friend msgProxy& endL(msgProxy& proxy);*/
        public:
            //a array to store priority name
            static const std::array<string,4> priorityArr;
        protected:
            //a internal class type to transform msg to log4cpp::Category
            class msgProxy
            {/*{{{*/
                public:
                    msgProxy(const string& priorityName,
                            log4cpp::Category& fileRoot,
                            log4cpp::Category& ostmRoot):
                        priorityName_(priorityName),
                        fileRoot_(fileRoot),
                        ostmRoot_(ostmRoot){}
                    template<typename T>
                        msgProxy& operator<<(const T& val);
                    msgProxy& operator<<(LOG::msgProxy& (*op)(msgProxy&)) {return (*op)(*this);}
     //        friend    msgProxy& endL(msgProxy& proxy);
                private:
                    const string priorityName_;
                    log4cpp::Category& fileRoot_;
                    log4cpp::Category& ostmRoot_;
            };/*}}}*/
        public: 
            //ctor 
        LOG(const string& logFileName="",const log4cpp::Priority::PriorityLevel& level=log4cpp::Priority::INFO,const string& rootName="Root"):
                fileRoot_(log4cpp::Category::getRoot().getInstance(string("file")+rootName)) ,
                ostmRoot_(log4cpp::Category::getRoot().getInstance(string("ostm")+rootName)),
                logFileName_(logFileName),
                INFO(priorityArr[2],fileRoot_,ostmRoot_),
                FATAL(priorityArr[0],fileRoot_,ostmRoot_),
                WARN(priorityArr[1],fileRoot_,ostmRoot_),
                DEBUG(priorityArr[3],fileRoot_,ostmRoot_),
                level_(level)
                {
                    init();
                }
            ~LOG()
            {/*{{{*/
                ostmRoot_.shutdown();
                fileRoot_.shutdown();
            }/*}}}*/
        protected:
            log4cpp::Category& ostmRoot_;
            log4cpp::Category& fileRoot_;
            string logFileName_;
            log4cpp::Priority::PriorityLevel level_;
        protected:
            //function for internal using 
            void init()
            {/*{{{*/
                log4cpp::PatternLayout* ostmLayout=new log4cpp::PatternLayout();
                ostmLayout->setConversionPattern("[%d{%m-%d %H:%M:%S,%l}:%x]%m%n");
                log4cpp::PatternLayout* fileLayout=new log4cpp::PatternLayout();
                fileLayout->setConversionPattern("[%d{%m-%d %H:%M:%S,%l}:%x][%p]%m%n");
                if(logFileName_.empty())
                    logFileName_="log.PID_"+std::to_string(getpid())+".txt";
                log4cpp::Appender* rollFileAppender=new log4cpp::RollingFileAppender("rollfileAppender",logFileName_);
                log4cpp::Appender* ostrmAppender=new log4cpp::OstreamAppender("OsAppender",&std::cout) ;
                ostrmAppender->setLayout(ostmLayout);
                rollFileAppender->setLayout(fileLayout);

                fileRoot_.addAppender(rollFileAppender);
                ostmRoot_.addAppender(ostrmAppender);
                fileRoot_.setPriority(level_);
                ostmRoot_.setPriority(level_);
            }/*}}}*/
        public:
            msgProxy INFO;
            msgProxy WARN;
            msgProxy DEBUG;
            msgProxy FATAL;
    };

}

//some impl
namespace yang
{
    const std::array<string,4> LOG:: priorityArr=
    {/*{{{*/
        "FATAL",
        "WARN",
        "INFO",
        "DEBUG"
    };/*}}}*/
    template<typename T>
        LOG::msgProxy& LOG::msgProxy::operator<<(const T& val)
        {/*{{{*/
            if(priorityName_=="INFO")
            {
                fileRoot_<<log4cpp::Priority::INFO
                    <<val;
                ostmRoot_<<log4cpp::Priority::INFO
                    <<BASH_GREEN "[INFO]" BASH_CLEAR
                    <<val;
            }
            else if(priorityName_=="WARN")
            {
                fileRoot_<<log4cpp::Priority::WARN
                    <<val;
                ostmRoot_<<log4cpp::Priority::WARN
                    <<BASH_YELLOW "[WARN]" BASH_CLEAR
                    <<val;
            }
            else if(priorityName_=="FATAL")
            {
                fileRoot_<<log4cpp::Priority::FATAL
                    <<val;
                ostmRoot_<<log4cpp::Priority::FATAL
                    <<BASH_RED "[FATAL]" BASH_CLEAR
                    <<val;
            }
            else if(priorityName_=="DEBUG")
            {
                fileRoot_<<log4cpp::Priority::DEBUG
                    <<val;
                ostmRoot_<<log4cpp::Priority::DEBUG
                    <<BASH_CYAN "[DEBUG]" BASH_CLEAR
                    <<val;
            }
            return *this;
        }/*}}}*/
    /*
    yang::LOG::msgProxy& endL(yang::LOG::msgProxy& proxy)
    {
        proxy.fileRoot_<<log4cpp::Priority::DEBUG
            <<"\n";
        proxy.ostmRoot_<<log4cpp::Priority::DEBUG
            <<"endL";
        return proxy;
    }
    */
}

namespace yang
{
    LOG Log("log.txt",log4cpp::Priority::DEBUG);
}
#endif
