#include "step_rkf45.h"


/**
 * Runge-Kutta-Fehlberg 4(5)
 *
 * Reference eg. Hairer, E., Norsett S.P., Wanner, G. Solving ordinary
 * differential equations I, Nonstiff Problems, 2nd revised edition,
 * Springer, 2000.
 * 
 */

/* TODO:
 * [ ] check the coefficients, see references 
 * [ ] parallelize for loops in apply function
 */

/* Runge-Kutta-Fehlberg coefficients. Zero elements left out */

static const ODE_R ah[] = { 1.0/4.0, 3.0/8.0, 12.0/13.0, 1.0, 1.0/2.0 };
static const ODE_R b3[] = { 3.0/32.0, 9.0/32.0 };
static const ODE_R b4[] = { 1932.0/2197.0, -7200.0/2197.0, 7296.0/2197.0 };
static const ODE_R b5[] = { 8341.0/4104.0, -32832.0/4104.0, 29440.0/4104.0, -845.0/4104.0 };
static const ODE_R b6[] = { -6080.0/20520.0, 41040.0/20520.0, -28352.0/20520.0, 9295.0/20520.0, -5643.0/20520.0 };

static const ODE_R c1 = 902880.0/7618050.0;
static const ODE_R c3 = 3953664.0/7618050.0;
static const ODE_R c4 = 3855735.0/7618050.0;
static const ODE_R c5 = -1371249.0/7618050.0;
static const ODE_R c6 = 277020.0/7618050.0;

/* These are the differences of fifth and fourth order coefficients
   for error estimation */

static const ODE_R ec[] = { 0.0, 1.0/360.0, 0.0, -128.0/4275.0, -2197.0/75240.0, 1.0/50.0, 2.0/55.0 };

typedef struct
{
  ODE_R *k1;
  ODE_R *k2;
  ODE_R *k3;
  ODE_R *k4;
  ODE_R *k5;
  ODE_R *k6;
  ODE_R *y0;
  ODE_R *ytmp;
}
rkf45_state_t;


/** 
 * This function returns pointer to the allocated memory area for
 * the rkf45 state
 * 
 * @param dim dimension of the ODE system
 * 
 * @return pointer to the allocated rkf45_state_t
 */
static void * rkf45_alloc ( size_t dim )
{
  rkf45_state_t *state = (rkf45_state_t *) malloc( sizeof( rkf45_state_t ) );

  /* checking memory allocation correctness */
  if( state==0 ) {
      _ODE_ERROR( " memory allocation for rkf45_state", 0 );
  }

  /* allocating memory for rkf45 state type components */
  /* k1 */
  state->k1 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->k1==0 ) {
      free( state );
      _ODE_ERROR( "memory allocation for k1", 0 );
  }

  /* k2 */
  state->k2 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->k2==0 ) {
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for k2", 0 );
  }

  /* k3 */
  state->k3 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if ( state->k3==0 ) {
      free( state->k2 );
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for k3", 0 );
  }
  
  /* k4 */
  state->k4 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->k4==0 ) {
      free( state->k3 );
      free( state->k2 );
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for k4", 0 );
  }

  /* k5 */
  state->k5 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->k5==0 ) {
      free( state->k4 );
      free( state->k3 );
      free( state->k2 );
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for k5", 0 );
  }

  /* k6 */
  state->k6 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->k6==0 ) {
      free( state->k5 );
      free( state->k4 );
      free( state->k3 );
      free( state->k2 );
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for k6", 0 );
  }

  /* y0 */
  state->y0 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->y0==0 ) {
      free( state->k6 );
      free( state->k5 );
      free( state->k4 );
      free( state->k3 );
      free( state->k2 );
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for y0", 0 );
    }
  
  /* ytmp */
  state->ytmp = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( state->ytmp==0 ) {
      free( state->y0 );
      free( state->k6 );
      free( state->k5 );
      free( state->k4 );
      free( state->k3 );
      free( state->k2 );
      free( state->k1 );
      free( state );
      _ODE_ERROR( "memory allocation for ytmp", 0 );
  }

  return state;
}

/** 
 * This function apply advances system from time t and state y(t)
 * to the time t+h and state y(t+h) (stored on output in y) using
 * RKF45 algorithm. An estimated error of step algorith is stored
 * at yerr array.
 * 
 * @param vstate pointer of type void to the rkf45_state_t struct
 * @param dim dimension of the ODE system
 * @param t actual time
 * @param h step size
 * @param y array with y_i(t) values at time t, where values of y_i(t+h) will by stored
 * @param yerr array with estimated error of the step algorithm
 * @param dydt_in array with derivatives for dydt system at time t 
 * @param dydt_out array with derivatives for dydt system at time t+h 
 * @param sys pointer to the ODE_system
 * 
 * @return If everything went successfully the function returns ODE_TRUE, otherwise tunction returns ODE_FALSE
 */
static int rkf45_apply ( void *vstate, size_t dim,
                         ODE_R t, ODE_R h,
                         ODE_R y[], ODE_R yerr[],
                         const ODE_R dydt_in[],
                         ODE_R dydt_out[], const ODE_system * sys)
{
  rkf45_state_t *state = (rkf45_state_t *) vstate;

  ODE_uint i;

  ODE_R *const k1 = state->k1;
  ODE_R *const k2 = state->k2;
  ODE_R *const k3 = state->k3;
  ODE_R *const k4 = state->k4;
  ODE_R *const k5 = state->k5;
  ODE_R *const k6 = state->k6;
  ODE_R *const ytmp = state->ytmp;
  ODE_R *const y0 = state->y0;

  _ODE_R_MEMCPY( y0, y, dim );

  /* k1 step */
  if( dydt_in != NULL ) {
      _ODE_R_MEMCPY( k1, dydt_in, dim );
  }
  else {
      int s = _ODE_FUNC_EVAL(sys, t, y, k1);

      if( s != ODE_TRUE ) {
          return s;
      }
  }
  
  for( i=0; i<dim; i++ )
      ytmp[i] = y[i] +  ah[0] * h * k1[i];
  
  /* k2 step */
  {
      int s = _ODE_FUNC_EVAL( sys, t + ah[0] * h, ytmp, k2);
      
    if( s!=ODE_TRUE ) {
        return s;
    }
  }
  
  for( i=0; i<dim; i++ )
      ytmp[i] = y[i] + h * (b3[0] * k1[i] + b3[1] * k2[i]);
  
  /* k3 step */
  {
      int s = _ODE_FUNC_EVAL( sys, t + ah[1] * h, ytmp, k3);
      
    if( s!=ODE_TRUE ) {
        return s;
    }
  }
  
  for( i=0; i<dim; i++ )
      ytmp[i] = y[i] + h * (b4[0] * k1[i] + b4[1] * k2[i] + b4[2] * k3[i]);
  
  /* k4 step */
  {
      int s = _ODE_FUNC_EVAL( sys, t + ah[2] * h, ytmp, k4);
      
    if( s!=ODE_TRUE ) {
        return s;
    }
  }
  
  for( i=0; i<dim; i++ )
      ytmp[i] =
          y[i] + h * (b5[0] * k1[i] + b5[1] * k2[i] + b5[2] * k3[i] +
                      b5[3] * k4[i]);
  
  /* k5 step */
  {
      int s = _ODE_FUNC_EVAL( sys, t + ah[3] * h, ytmp, k5);
      
    if( s!=ODE_TRUE ) {
        return s;
    }
  }
  
  for( i=0; i<dim; i++ )
      ytmp[i] =
          y[i] + h * (b6[0] * k1[i] + b6[1] * k2[i] + b6[2] * k3[i] +
                      b6[3] * k4[i] + b6[4] * k5[i]);
  
  /* k6 step and final sum */
  {
      int s = _ODE_FUNC_EVAL( sys, t + ah[4] * h, ytmp, k6 );
      
    if( s!=ODE_TRUE ) {
        return s;
    }
  }
  
  for( i=0; i<dim; i++ ) {
      const ODE_R d_i = c1 * k1[i] + c3 * k3[i] + c4 * k4[i] + c5 * k5[i] + c6 * k6[i];
      y[i] += h * d_i;
  }
  
  /* Derivatives at output */
  if( dydt_out!=NULL ) {
      int s = _ODE_FUNC_EVAL( sys, t + h, y, dydt_out );
      
      if( s!=ODE_TRUE ) {
          /* Restore initial values */
          _ODE_R_MEMCPY( y, y0, dim );
          
          return s;
      }
  }
  
  /* difference between 4th and 5th order */
  for( i=0; i<dim; i++ ) {
      yerr[i] = h * (ec[1] * k1[i] + ec[3] * k3[i] + ec[4] * k4[i] 
                     + ec[5] * k5[i] + ec[6] * k6[i]);
  }
  
  return ODE_TRUE;
}


/** 
 * This function resets memory associated eith the rkf45_state_t struct
 * 
 * @param vstate pointer of type void to the rkf45_state_t struct
 * @param dim dimension of the ODE system
 * 
 * @return ODE_TRUE
 */
static int rkf45_reset ( void *vstate, size_t dim )
{
  rkf45_state_t *state = (rkf45_state_t *) vstate;

  _ODE_R_ZERO_MEMSET( state->k1, dim );
  _ODE_R_ZERO_MEMSET( state->k2, dim );
  _ODE_R_ZERO_MEMSET( state->k3, dim );
  _ODE_R_ZERO_MEMSET( state->k4, dim );
  _ODE_R_ZERO_MEMSET( state->k5, dim );
  _ODE_R_ZERO_MEMSET( state->k6, dim );
  _ODE_R_ZERO_MEMSET( state->ytmp, dim );
  _ODE_R_ZERO_MEMSET( state->y0, dim );

  return ODE_TRUE;
}


/** 
 * This function returns RKF45 algorithm order.
 * 
 * @param vstate pointer of type void to the rkf45_state_t struct
 * 
 * @return RKF45 algorithm order
 */
static unsigned int rkf45_order ( void * vstate )
{
  rkf45_state_t *state = (rkf45_state_t *) vstate;
  state = 0; /* prevent warnings about unused parameters */
  return 5;
}


/** 
 * This function frees memory associated with the rkf45_state_t struct.
 * 
 * @param vstate pointer of type void to the rkf45_state_t struct
 */
static void rkf45_free ( void * vstate )
{
  rkf45_state_t *state = (rkf45_state_t *) vstate;

  free( state->ytmp );
  free( state->y0 );
  free( state->k6 );
  free( state->k5 );
  free( state->k4 );
  free( state->k3 );
  free( state->k2 );
  free( state->k1 );
  free( state );
}


/**
 * Defining RKF45 step type ODE_step_type
 * 
 */
static const ODE_step_type rkf45_type =
{ "rkf45",                      /**< step type name */
  1,                            /**< can use dydt_in */
  0,                            /**< gives exact dydt_out */
  &rkf45_alloc,                 /**< alloc function */
  &rkf45_apply,                 /**< apply function */
  &rkf45_reset,                 /**< reset function */
  &rkf45_free,                  /**< free function */
  &rkf45_order                  /**< order function */
};


/**
 * Defining pointer (ODE_step_rk45f) to RKF45 step type rkf45_type
 */
const ODE_step_type *ODE_step_rkf45 = &rkf45_type;
