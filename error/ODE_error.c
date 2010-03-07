#include "ODE_error.h"

/* TODO:
 * [ ] error identifiers
 * [ ] error mesages
 * [ ] exiting the program
 */


/** 
 * This function prints error reason and stops executing
 * the program.
 * 
 * @param msg the reason for the error message
 * @param errno error identifier
 */
void ODE_ERROR ( char * msg, int errno )
{
  printf(" ODE error\n");
  printf(" failed %s\n", msg);
  exit( EXIT_FAILURE );
}
