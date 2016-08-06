//
// utility.hpp
//

#ifndef __ENGINE_UTILITY_HPP__
#define __ENGINE_UTILITY_HPP__

#include <cstdio>


#define PRINT_ERROR(func, message)                                      \
printf("%s : %s\n", #func, message);

#define PRINT_INFO(func, message)                                       \
printf("%s : %s\n", #func, message);


#define SAFE_DELETE_PTR(ptr)                                            \
if(ptr)                                                                 \
{                                                                       \
  delete ptr;                                                           \
  ptr = nullptr;                                                        \
}

#define SAFE_DELETE_OBJECT(ptr)                                         \
if(ptr)                                                                 \
{                                                                       \
  ptr->deleteObject();                                                  \
  ptr = nullptr;                                                        \
}

#endif
