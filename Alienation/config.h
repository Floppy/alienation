// Global settings for all files

#ifndef CONFIG_H
#define CONFIG_H

#ifdef WIN32
  #include <windows.h>
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
 */

#ifndef NULL
#define NULL 0
#endif

#define RANDOM_FLOAT   ((float)(rand()%1000)/1000.0f)
#define DEG_TO_RAD(x)  ((x) * 0.0174532925f)
#define RAD_TO_DEG(x)  ((x) * 57.295779513f)

#endif // CONFIG_H
