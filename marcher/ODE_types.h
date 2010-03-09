#ifndef _ODE_TYPES_H_
#define _ODE_TYPES_H_

#ifndef ODE_VAR

#ifdef WIN32
#  ifdef ODE_DLL
#    ifdef DLL_EXPORT
#      define ODE_VAR extern __declspec(dllexport)
#    else
#      define ODE_VAR extern __declspec(dllimport)
#    endif
#  else
#    define ODE_VAR extern
#  endif
#else
#  define ODE_VAR extern
#endif

#endif


#endif /* _ODE_TYPES_H_ */
