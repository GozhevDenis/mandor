#include <cmath>

#include "planeWave.h"
#include "testConstMacros.h"


static int     m[3] = {1, 0, 0};	   ///< Wave numbers.
static vec3d_t k;                   ///< Wave vector (can be initialized
                                    ///<   numerically / physically, see
                                    ///<   'tag_EMWave.h').
static double  omega = 0;		      ///< Cyclic frequency.
static double  Dt    = 0;		      ///< Cyclic frequency modified by dispersion of Yee scheme (see tag_EMWave.h).
static vec3d_t Dr;	               ///< Wave vector modified by dispersion of Yee scheme (see tag_EMWave.h).


// ---------------------------------------------------------------------------
/// Initializes ω and k⃗ using exact physical dispersion equation;
/// sets D_r, D_t to physical values.
// ---------------------------------------------------------------------------
static void
EMWave_setPhysFrame( void )
{
   // Turns wave numbers to wave vector.
   k.r[0] = 2 * PI * m[0] / ( dx * ( cpu_max[0] - cpu_min[0] ) );
   k.r[1] = 2 * PI * m[1] / ( dy * ( cpu_max[1] - cpu_min[1] ) );
   k.r[2] = 2 * PI * m[2] / ( dz * ( cpu_max[2] - cpu_min[2] ) );

   // Gets omega from normal dispersion equation, updates numerical wave vector.
   omega = Dt = sqrt( k.dot( k ) );
   Dr    = k;
}


// ---------------------------------------------------------------------------
/// Initialize ω and k⃗ using exact numerical dispersion equation;
/// update D_r, D_t.
// ---------------------------------------------------------------------------
static void
EMWave_setYee2Frame (void)
{
   // Set k and c vectors.
   EMWave_setPhysFrame ();

   // Apply dispersion factors to the wave vector.
   Dr = vec3d_t( 2 * sin( 0.5 * k.r[0] * dx ) / dx,
                 2 * sin( 0.5 * k.r[1] * dy ) / dy,
                 2 * sin( 0.5 * k.r[2] * dz ) / dz );

   // Apply dispersion factors to the frequency.
   Dt    = sqrt( Dr.dot( Dr ) );
   omega = asin( 0.5 * dt * Dt ) * 2 / dt;
}


// ---------------------------------------------------------------------------
/// Excite uniform plane EM-wave (for periodic boundary conditions only).
// ---------------------------------------------------------------------------
void
EWaveStart ( mesh_t<vec3d_t> & E, mesh_t<vec3d_t> & H)
{
   m[0] = 1;
   m[1] = 0;
   m[2] = 0;

   // EMWave_setPhysFrame ();
   EMWave_setYee2Frame ();

   double  E0{ 1.0 };
   vec3d_t e{ 0, 1, 0 };

   double  ek  = Dr.dot( e );
   double  Dr2 = Dr.dot( Dr );
   e = e - Dr * ( ek / Dr2 );

   // Normalizes length of 'e'.
   Dr2 = sqrt( e.dot( e ) ) * ( E0 / Dr2 );

   // Sets polarization vector for H: h = - [e, Dr]/Dt.
   vec3d_t h = Dr.cross( e ) * ( 1.0 / Dt );

   volatile int type = 1;
   printf( "tag_EMWave: " );
   printf( "  - electromagnetic wave is excited using %s dispertion equation,",
           ( type ) ? "numerical" : "physical" );
   printf( "  - wave numbers are (%d, %d, %d),", m[0], m[1], m[2] );
   printf( "  - E = (%e, %e, %e), E0 = %e",  e.r[0],  e.r[1],  e.r[2], sqrt( e.dot( e ) ) );
   printf( "  - H = (%e, %e, %e), H0 = %e",  h.r[0],  h.r[1],  h.r[2], sqrt( h.dot( h ) ) );
   printf( "  - k  = (%e, %e, %e), w  = %e", k.r[0],  k.r[1],  k.r[2], omega );
   printf( "  - Dr = (%e, %e, %e), Dt = %e", Dr.r[0], Dr.r[1], Dr.r[2], Dt );

   // Scales k to work with indices directly.
   k.r[0] *= dx;
   k.r[1] *= dy;
   k.r[2] *= dz;

   for (int i = E.imin ; i <= E.imax ; ++i)
   for (int j = E.jmin ; j <= E.jmax ; ++j)
   for (int l = E.kmin ; l <= E.kmax ; ++l) {
      double phase = k.dot( vec3d_t{ i*1.0, j*1.0, l*1.0 } );

      E(i, j, l).v.x += e.r[0]*sin (phase - 0.5*k.r[0]);
      E(i, j, l).v.y += e.r[1]*sin (phase - 0.5*k.r[1]);
      E(i, j, l).v.z += e.r[2]*sin (phase - 0.5*k.r[2]);

      phase += 0.5*omega*dx;
      H( i, j, l).v.x += h.r[0]*sin (phase - 0.5*k.r[1] - 0.5*k.r[2]);
      H( i, j, l).v.y += h.r[1]*sin (phase - 0.5*k.r[0] - 0.5*k.r[2]);
      H( i, j, l).v.z += h.r[2]*sin (phase - 0.5*k.r[0] - 0.5*k.r[1]);
   }
}
