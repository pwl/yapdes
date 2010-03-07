#include "con_std.h"


/* TODO:
 * [ ] DBL_MIN -> LDBL_MIN
 * [ ] GSL_MAX_DBL -> _ODE_MAX supporting long double precision
 * [ ] parallelize for loop in handjust function
 */ 

typedef struct
{
  ODE_R eps_abs;
  ODE_R eps_rel;
  ODE_R a_y;
  ODE_R a_dydt;
} std_step_control_state_t;


/** 
 * This function returns pointer to the allocated memory area for
 * the standard step control state type.
 * 
 * @return pointer to the allocated std_step_control_state_t
 */
static void * std_step_control_alloc ( void )
{
  std_step_control_state_t * s = 
    (std_step_control_state_t *) malloc( sizeof( std_step_control_state_t ) );

  /* checking memory allocation correctness */
  if( s==0 ) {
      ODE_ERROR( "memory allocation for std_step_control_state", 0 );
  }
  
  return s;
}


/** 
 * This function initializes the standard step control state type. 
 * 
 * @param vstate pointer of type void to the std_step_control_state_t
 * @param eps_abs absolute error
 * @param eps_rel relative error
 * @param a_y scaling factor for y
 * @param a_dydt scaling factor for derivatives
 * 
 * @return if everything went correctly routine returns ODE_TRUE
 */
static int std_step_control_init ( void * vstate, ODE_R eps_abs,
                                   ODE_R eps_rel, ODE_R a_y, ODE_R a_dydt )
{
  std_step_control_state_t * s = ( std_step_control_state_t * ) vstate;

  /* Preconditions checking */
  if( eps_abs < 0 ) {
      ODE_ERROR( "eps_abs is negative", 0 );
  }
  else if( eps_rel < 0 ) {
      ODE_ERROR( "eps_rel is negative", 0 );
  }
  else if( a_y < 0 ) {
      ODE_ERROR( "a_y is negative", 0 );
  }
  else if( a_dydt < 0 ) {
      ODE_ERROR( "a_dydt is negative", 0 );
  }
  
  /* setting control values */
  s->eps_rel = eps_rel;
  s->eps_abs = eps_abs;
  s->a_y = a_y;
  s->a_dydt = a_dydt;

  return ODE_TRUE;
}


/** 
 * This function adjusts the time step for the standard step
 * control state type.
 * 
 * @param vstate pointer of type void to the std_step_control_state_t
 * @param dim dimension of the ODE system
 * @param ord order of the stepper algorithm
 * @param y array with y values at a given time
 * @param yerr array with estimated error of the step algorithm
 * @param yp array with y' values at a given time
 * @param h pointer to the initial step size
 * 
 * @return function returns one of three values {ODE_STEP_HADJ_INC,
 * ODE_STEP_HADJ_NIL, ODE_STEP_HADJ_DEC} depending on whether the time
 * step was changed or not.
 */
static int std_step_control_hadjust ( void * vstate,
                                      size_t dim, unsigned int ord,
                                      const ODE_R y[], const ODE_R yerr[],
                                      const ODE_R yp[], ODE_R * h)
{
  std_step_control_state_t *state = ( std_step_control_state_t * ) vstate;

  const ODE_R eps_abs = state->eps_abs;
  const ODE_R eps_rel = state->eps_rel;
  const ODE_R a_y     = state->a_y;
  const ODE_R a_dydt  = state->a_dydt;

  const ODE_R S = 0.9;          /* setting safety factor */
  const ODE_R h_old = *h;       /* backup of input time step */ 

  ODE_R rmax = DBL_MIN;
  size_t i;

  for(i=0; i<dim; i++) {
      const ODE_R D0 = 
          eps_rel * (a_y * fabs(y[i]) + a_dydt * fabs(h_old * yp[i])) + eps_abs;
      const ODE_R r  = fabs(yerr[i]) / fabs(D0);
      rmax = _ODE_MAX( r, rmax );
  }

  if( rmax > 1.1 ) {
      /* decrease step, no more than factor of 5, but a fraction S more
         than scaling suggests (for better accuracy) */
      ODE_R r = S / pow( rmax, 1.0/ord );
      
      if( r < 0.2 ) r = 0.2;
      
      *h = r * h_old;
      
      return ODE_STEP_HADJ_DEC; /* time step was increased */
  }
  else if( rmax < 0.5 ) {
      /* increase step, no more than factor of 5 */
      ODE_R r = S / pow(rmax, 1.0/(ord+1.0));
      
    if( r > 5.0 ) r = 5.0;
    
    if( r < 1.0 )  /* don't allow any decrease caused by S<1 */
        r = 1.0;
    
    *h = r * h_old;
    
    return ODE_STEP_HADJ_INC; /* time step was increased */
  }
  else {
      return ODE_STEP_HADJ_NIL; /* time step stays the same */
  }
}


/** 
 * This function frees all the memory associated the standard step
 * control state type.
 *
 * @param vstate pointer of type void to the std_step_control_state_t
 */
static void std_step_control_free ( void * vstate )
{
  std_step_control_state_t *state = (std_step_control_state_t *) vstate;
  free( state );
}


/**
 * Defining standard step control type std_step_control_type
 */
static const ODE_step_control_type std_step_control_type =
{ "standard",                   /**< step control type name */
  &std_step_control_alloc,      /**< alloc function */
  &std_step_control_init,       /**< init function */
  &std_step_control_hadjust,    /**< hadjust function */ 
  &std_step_control_free };     /**< free function */

/**
 * Defining pointer (ODE_step_control_standard) to standard step control type
 * std_step_control_type
 */
const ODE_step_control_type * ODE_step_control_standard = &std_step_control_type;


/**
 * Defining standard step control ODE_step_control objects 
 */

/** 
 * The standard control object.
 * The step-size adjustment procedure for this method begins by
 * computing the desired error level D_i for each component,
 *
 *    D_i = eps_abs + eps_rel * (a_y |y_i| + a_dydt h |y'_i|)
 *
 * and comparing it with the observed error E_i = |yerr_i|. If
 * the observed error E exceeds the desired error level D by
 * more than 10% for any component then the method reduces the
 * step-size by an appropriate factor,
 *
 *     h_new = h_old * S * (E/D)^(-1/q)
 *
 * where q is the consistency order of the method (e.g. q=4 for
 * 4(5) embedded RK), and S is a safety factor of 0.9. The ratio
 * E/D is taken to be the maximum of the ratios E_i/D_i.
 *
 * If the observed error E is less than 50% of the desired error
 * level D for the maximum ratio E_i/D_i then the algorithm takes
 * the opportunity to increase the step-size to bring the error in
 * line with the desired level,
 *
 *     h_new = h_old * S * (E/D)^(-1/(q+1))
 *
 * This encompasses all the standard error scaling methods. To
 * avoid uncontrolled changes in the stepsize, the overall scaling
 * factor is limited to the range 1/5 to 5.
 *
 * ODE_step_control_standard_new is defined by (given by user): eps_abs,
 * eps_rel, a_y, a_dydt.
 * 
 * @param eps_abs absolute error
 * @param eps_rel relative error
 * @param a_y scaling factor for the system state y(t)
 * @param a_dydt scaling factor for the system derivatives y'(t)
 * 
 * @return pointer to the ODE_step_control
 */
ODE_step_control * ODE_step_control_standard_new ( ODE_R eps_abs, ODE_R eps_rel,
                                                   ODE_R a_y, ODE_R a_dydt )
{
  ODE_step_control * c =  
      ODE_step_control_alloc( ODE_step_control_standard );
  
  int status = ODE_step_control_init( c, eps_abs, eps_rel, a_y, a_dydt );
  
  if( status != ODE_TRUE ) {
      ODE_step_control_free( c );
      ODE_ERROR( "error trying to initialize control", status );
  }
  
  return c;
}


/** 
 * The standard control object defined by (given by user): eps_abs,
 * eps_rel. Scaling factors are scaling factors are defined as follows
 * a_y = 1.0, a_dydt = 0.0.
 *
 * @param eps_abs absolute error
 * @param eps_rel relative error
 * 
 * @return pointer to the ODE_step_control
 */
ODE_step_control * ODE_step_control_y_new ( ODE_R eps_abs, ODE_R eps_rel )
{
  return ODE_step_control_standard_new( eps_abs, eps_rel, 1.0, 0.0 );
}


/** 
 * The standard control object defined by (given by user): eps_abs,
 * eps_rel. Scaling factors are scaling factors are defined as follows
 * a_y = 0.0, a_dydt = 1.0.
 *
 * @param eps_abs absolute error
 * @param eps_rel relative error
 * 
 * @return pointer to the ODE_step_control
 */
ODE_step_control * ODE_step_control_yp_new ( ODE_R eps_abs, ODE_R eps_rel )
{
  return ODE_step_control_standard_new( eps_abs, eps_rel, 0.0, 1.0 );
}
