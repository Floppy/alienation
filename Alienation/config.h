// Global settings for all files

#ifndef CONFIG_H
#define CONFIG_H

#ifdef WIN32
  #pragma warning( disable : 4786 ) // Disable stupid debugger warning
#endif

/** 
 * @mainpage Alienation Documentation
 *
 * Well, we have code documentation! There's not a lot up here on the main page yet, so
 * you're probably best off starting with the Class Hierarchy or Compound List. Oh, there 
 * is a buglist under the Related Pages section, so if you feel like fixing something...
 *
 * This documentation is generated with <a href="http://www.stack.nl/~dimitri/doxygen">Doxygen</a>, 
 * and I've picked (pretty much at random) the javadoc-style commenting standard to use. Details 
 * of how to document your code can be found 
 * <a href="http://www.stack.nl/~dimitri/doxygen/manual.html">online</a>, or just look at some 
 * that's already been done! Enjoy!
 * 
 * <h3>External Libraries</h3>
 *
 * Documentation for the external libraries we are using can be found below:
 *
 * <ul>
 * <li>SDL - <a href="http://sdldoc.csn.ul.ie/">http://sdldoc.csn.ul.ie/</a>
 * <li>SDL_image - <a href="http://jcatki.no-ip.org/SDL_image/">http://jcatki.no-ip.org/SDL_image/</a>
 * <li>SDL_mixer - <a href="http://jcatki.no-ip.org/SDL_mixer/">http://jcatki.no-ip.org/SDL_mixer/</a>
 * <li>Lua - <a href="http://www.lua.org/docs.html">http://www.lua.org/docs.html</a>
 * <li>ODE - <a href="http://opende.sourceforge.net/ode-0.039-userguide.html">http://opende.sourceforge.net/ode-0.039-userguide.html</a>
 * </ul>
 */

#ifndef NULL
#define NULL 0
#endif

#define DEG_TO_RAD(x)  ((x) * 0.0174532925f)
#define RAD_TO_DEG(x)  ((x) * 57.295779513f)


/**
 * Mathematical support classes.
 */
namespace NSDMath {}

/**
 * Sound subsystems.
 */
namespace NSDSound {}

/**
 * 2D rendering.
 */
namespace NSD2D {}

/**
 * Input/Output classes.
 */
namespace NSDIO {}

#endif // CONFIG_H
