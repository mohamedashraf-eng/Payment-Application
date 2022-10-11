/**
 * @file application.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/** @def Header Guards */
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

/*
-----------------------------------------------------------------
-       DEFINES
-----------------------------------------------------------------
*/

#define EXCEPTION_RETURN()           return;
#define EXCEPTION_EXIT_MSG(EXIT_MSG) printf("\n DECLINED: %s", EXIT_MSG); 
#define SUCCESSFUL_RETURN()          return;
#define SUCCESSFUL_MSG(EXIT_MSG)     printf("\n APPROVED: %s", EXIT_MSG); 

/*
-----------------------------------------------------------------
-       PUBLIC FUNCTION DECLARATION
-----------------------------------------------------------------
*/

void appStart(void);

#endif /* _APPLICATION_H_ */
