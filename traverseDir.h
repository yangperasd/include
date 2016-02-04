/*************************************************************************
> File Name: include/traverseDir.h
> Author: yang 
> Mail: yangperasd@163.com 
> Created Time: Thu 04 Feb 2016 08:46:39 PM CST
************************************************************************/

#ifndef _RAVERSEDIR_H
#define _RAVERSEDIR_H
#include <boost/filesystem.hpp>
#include <functional>
#include <iostream>
using boost::filesystem::is_directory;using boost::filesystem::is_regular_file;using boost::filesystem::path;using boost::filesystem::recursive_directory_iterator;using boost::filesystem::exists;
using std::string;using std::function;using std::cerr;using std::endl;using std::cout;
namespace yang
{
    class traverseDir
    {/*{{{*/
     public:
     void operator()(const string& dirPathName,
                     const function<void(const string&)>& fileProcess,
                     const function<void(const string&)>& dirProcess)
     {
         const path dirPath(dirPathName);
         //check dirPathName 
         if(!is_directory(dirPath))/*{{{*/ 
         {
             cerr<<"not a directory:"<<dirPath<<endl;
             return;
         }
         else if(!exists(dirPath))
         {
             cerr<<"directory not exists:"<<dirPath<<endl;
             return ;
         }/*}}}*/

         //start recur traverse this directory 
         for(recursive_directory_iterator iter(dirPath);iter!=recursive_directory_iterator();++iter)
         {/*{{{*/
             try
             {
                 if(is_directory(*iter))
                 {
                     if(dirProcess) dirProcess(iter->path().string());
                 }
                 else if(is_regular_file(*iter))
                 {
                     if(fileProcess) fileProcess(iter->path().string());
                 }
             }
             catch(const std::exception& ex)
             {
                 cerr<<ex.what()<<endl;
                 continue;
             }
            catch(...)
            {
                cerr<<"unexpected exception"<<endl;
                std::abort();
            }
         }/*}}}*/
     }

    };/*}}}*/

}
#endif
