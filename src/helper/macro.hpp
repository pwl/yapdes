#pragma once
#ifndef _MACRO_HPP_
#define _MACRO_HPP_


#define ODE_MALLOC(size,type) cpp_malloc<type>(size)

template<typename T>
inline T * cpp_malloc(unsigned int n)
{
  printf("------cpp_malloc<T>(%i)\n",n);
  return (T *)calloc( n, sizeof(T));
}

template<>
inline ODE_R * cpp_malloc<ODE_R>(unsigned int n)
{
  printf("------cpp_malloc<ODE_R>(%i)\n",n);
  /* allocate memory */
  return new ODE_R[n];
}

#define ODE_FREE(ptr) cpp_free(ptr)

template<typename T>
inline void cpp_free(T * ptr)
{
  /* printf("------cpp_free<T>\n"); */
  free(ptr);
  ptr = (T*)NULL;
}

template<>
inline void cpp_free<ODE_R>(ODE_R * ptr)
{
  /* allocate memory */
  /* printf("------cpp_free<ODE_R>\n"); */
  delete[] ptr;
}

#define ODE_REALLOC(ptr,n,type,n_old) cpp_realloc(ptr,n,n_old)

template<typename T>
inline T * cpp_realloc(T * ptr,unsigned int n,unsigned int n_old)
{
  /* printf("-----cpp_realloc<>\n"); */
  return (T *)realloc((void*)ptr, (n) * sizeof(T));
}

template<>
inline ODE_R * cpp_realloc<ODE_R>(ODE_R * ptr, unsigned int n, unsigned int n_old)
{
  /* allocate memory */
  ODE_R * new_ptr = new ODE_R[n];
  /* printf("-----cpp_realloc<ODE_R>\n"); */
  /* copy data */
  for( unsigned int i = 0; i < MIN(n_old,n); i++ )
    new_ptr[i] = ptr[i];
  /* free old block */
  ODE_FREE(ptr);
  return new_ptr;
}



#endif /* _MACRO_HPP_ */
