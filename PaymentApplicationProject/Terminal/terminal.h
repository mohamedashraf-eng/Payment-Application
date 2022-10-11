/**
 * @file Terminal.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/** @def Header Guards */
#ifndef _TERMINAL_H_
#define _TERMINAL_H_

/*
-----------------------------------------------------------------
-       DEFINES
-----------------------------------------------------------------
*/

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, 
    WRONG_DATE, 
    EXPIRED_CARD, 
    INVALID_CARD, 
    INVALID_AMOUNT, 
    EXCEED_MAX_AMOUNT, 
    INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*
-----------------------------------------------------------------
-       PUBLIC FUNCTION DECLARATION
-----------------------------------------------------------------
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);


#endif /* _TERMINAL_H_ */
