/**
 * @file Terminal.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

#include "../Card/card.h"
#include "terminal.h"

/*
-----------------------------------------------------------------
-       GLOBAL VARIABLES
-----------------------------------------------------------------
*/

/*
-----------------------------------------------------------------
-       PUBLIC FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/

/**
 * @brief Get the Transaction Date object
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    uint8_t transactionDate[11] = {0};

    printf("\n Enter the transaction date: ");
    gets(transactionDate);

    uint8_t TransactionDateLength = strlen(transactionDate);

    if( (NULL == transactionDate) || 
        (TransactionDateLength < 10) || 
        (TransactionDateLength > 10) ||
        (transactionDate[2] != '/' || transactionDate[5] != '/') )
    {
        ThisFunction_ErrorState = WRONG_DATE;
    }
    else
    {
        strcpy(termData->transactionDate, transactionDate);
    }

    return ThisFunction_ErrorState;
}/** @end getTransactionDate */
/**
 * @brief Check if card is expired
 * 
 * @param cardData 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    uint8_t CardExpirationMonth = 
    ((cardData.cardExpirationDate[0] - '0') * 10) + (cardData.cardExpirationDate[1] - '0');
    uint8_t CardExpirationYear  = 
    ((cardData.cardExpirationDate[3] - '0') * 10) + (cardData.cardExpirationDate[4] - '0');

    uint8_t TransactionMonth = 
    ((termData.transactionDate[3] - '0') * 10) + (termData.transactionDate[4] - '0');
    uint8_t TransactionYear  = 
    ((termData.transactionDate[8] - '0') * 10) + (termData.transactionDate[9] - '0');

    if( (CardExpirationYear < TransactionYear) )
    {
        ThisFunction_ErrorState = EXPIRED_CARD;
    }
    else if( (CardExpirationYear == TransactionYear) )
    {
        if( (CardExpirationMonth < TransactionMonth) || 
            (CardExpirationMonth == TransactionMonth) )
        { ThisFunction_ErrorState = EXPIRED_CARD; }
        else {;}
    }
    else {;}

    return ThisFunction_ErrorState;
}/** @end isCardExpired */
/**
 * @brief Check the card PAN
 * 
 * @param cardData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    // TODO

    return ThisFunction_ErrorState;
}/** @end isValidCardPAN */
/**
 * @brief Get the Transaction Amount object
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    float transAmount = 0;
    printf("\n Enter transaction amount: ");
    scanf("%f", &transAmount);

    if( (0 >= transAmount) )
    {
        ThisFunction_ErrorState = INVALID_AMOUNT;
    }
    else
    {
        termData->transAmount = transAmount;
    }
    return ThisFunction_ErrorState;
}/** @end getTransactionAmount */
/**
 * @brief Check if the amount is valid
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;

    if( (termData->transAmount > termData->maxTransAmount) )
    {
        ThisFunction_ErrorState = EXCEED_MAX_AMOUNT;
    }
    else{;}

    return ThisFunction_ErrorState;
}/** @end isBelowMaxAmount */
/**
 * @brief Set the Max Amount object
 * 
 * @param termData 
 * @return EN_terminalError_t 
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ThisFunction_ErrorState = TERMINAL_OK;
    
    float maxTransAmount = 0.0f;

    printf("\n Enter transaction maximum amount: ");
    scanf("%f", &maxTransAmount);

    if( (0 >= maxTransAmount) )
    {
        ThisFunction_ErrorState = INVALID_MAX_AMOUNT;
    }
    else
    {
        termData->maxTransAmount = maxTransAmount;
    }

    return ThisFunction_ErrorState;
}/** @end setMaxAmount */

/*
-----------------------------------------------------------------
-       PRIVATE FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/

#ifdef TERMINAL_TEST_FUNCTIONS

static uint8_t TEST_MODULE_Terminal(ST_cardData_t *MyCardModuleTest,
                                    ST_terminalData_t *MyTermianlModuleTest)
{
    uint8_t ThisFunction_ErrorState = 0;

    /** @defgroup Testing get the transaction data */
    if( (1 == TEST_getTransactionDate(MyTermianlModuleTest)) )
    { printf("\n TEST_getTransactionDate: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_getTransactionDate: FAILED"); }

    /** @defgroup Testing is card expired */
    if( (1 == isCardExpired(MyCardModuleTest, MyTermianlModuleTest)) )
    { printf("\n isCardExpired: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n isCardExpired: FAILED"); }

    /** @defgroup Testing is card pan valid */
    if( (1 == isValidCardPAN(MyCardModuleTest)) )
    { printf("\n isValidCardPAN: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n isValidCardPAN: FAILED"); }

    /** @defgroup Testing get the transaction amount */
    if( (1 == getTransactionAmount(MyTermianlModuleTest)) )
    { printf("\n getTransactionAmount: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n getTransactionAmount: FAILED"); }

    /** @defgroup Testing is below max */
    if( (1 == isBelowMaxAmount(MyTermianlModuleTest)) )
    { printf("\n isBelowMaxAmount: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n isBelowMaxAmount: FAILED"); }

    /** @defgroup Testing set the max amount */
    if( (1 == setMaxAmount(MyTermianlModuleTest)) )
    { printf("\n setMaxAmount: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n setMaxAmount: FAILED"); }

    /** @note: Means that the module test is passed */
    return ThisFunction_ErrorState;
}

static uint8_t TEST_getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getTransactionDate(termData);
    
    if( (WRONG_DATE == ErrorState) )
    {
        printf("\n TEST_getTransactionDate: WRONG_DATE");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isCardExpired(cardData, termData);
    
    if( (EXPIRED_CARD == ErrorState) )
    {
        printf("\n TEST_isCardExpired: EXPIRED_CARD");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isValidCardPAN(ST_cardData_t *cardData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isValidCardPAN(cardData);
    
    if( (INVALID_CARD == ErrorState) )
    {
        printf("\n TEST_isValidCardPAN: INVALID_CARD");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_getTransactionAmount(ST_terminalData_t *termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getTransactionAmount(termData);
    
    if( (INVALID_AMOUNT == ErrorState) )
    {
        printf("\n TEST_getTransactionAmount: INVALID_AMOUNT");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isBelowMaxAmount(ST_terminalData_t *termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isBelowMaxAmount(termData);
    
    if( (EXCEED_MAX_AMOUNT == ErrorState) )
    {
        printf("\n TEST_isBelowMaxAmount: EXCEED_MAX_AMOUNT");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_setMaxAmount(ST_terminalData_t *termData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = setMaxAmount(termData);
    
    if( (INVALID_MAX_AMOUNT == ErrorState) )
    {
        printf("\n TEST_setMaxAmount: INVALID_MAX_AMOUNT");
    }
    else
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState; 
}

#endif