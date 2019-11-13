//==============================================================================
/*!
 * @file macro.h
 * @brief 与dsas相关的宏
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_MARCO_H
#define DSAS_MARCO_H

#if defined(__linux__)
#define DSAS_LINUX
#elif defined(_WIN32)
#define DSAS_WIN
#else
#warning "Using time lib of std"
#endif

#endif /* ifndef DSAS_MARCO_H */
