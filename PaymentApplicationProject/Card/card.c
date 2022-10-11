/**
 * @file Card.c
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
#include <stdlib.h>
#include <string.h>

#include "card.h"

/*
-----------------------------------------------------------------
-       PUBLIC FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/

/**
 * @brief Get the Card Holder Name object
 * 
 * @param cardData 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t CardHolderName[25] = {0};

    printf("\n Enter the card holder name: ");
    gets(CardHolderName);

    uint8_t NameLength = strlen(CardHolderName);

    if( (NULL == CardHolderName) || 
        (NameLength < 20) || 
        (NameLength > 24) )
    {
        ThisFunction_ErrorState = WRONG_NAME;
    }
    else 
    {
        strcpy(cardData->cardHolderName, CardHolderName);
    }

    return ThisFunction_ErrorState;
}/** @end getCardHolderName */
/**
 * @brief Get the Card Expiry Date object
 * 
 * @param cardData 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t cardExpirationDate[25] = {0};

    printf("\n Enter the card expiration date: ");
    gets(cardExpirationDate);

    uint8_t DateLength = strlen(cardExpirationDate);

    if( (NULL == cardExpirationDate) || 
        (DateLength < 5) || 
        (DateLength > 5) ||
        (cardExpirationDate[2] != '/') )
    {
        ThisFunction_ErrorState = WRONG_EXP_DATE;
    }
    else 
    {
        strcpy(cardData->cardExpirationDate, cardExpirationDate);
    }
    
    return ThisFunction_ErrorState;
}/** @end getCardExpiryDate */
/**
 * @brief Get the Card P A N object
 * 
 * @param cardData 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t cardPAN[20] = {0};

    printf("\n Enter the card primary account number: ");
    gets(cardPAN);
    
    uint8_t PANLength = strlen(cardPAN);

    if( (NULL == cardPAN) || 
        (PANLength < 16) || 
        (PANLength > 20) )
    {
        ThisFunction_ErrorState = WRONG_PAN;
    }
    else 
    {
        strcpy(cardData->primaryAccountNumber, cardPAN);
    }
    
    return ThisFunction_ErrorState;
}/** @end getCardPAN */

/*
-----------------------------------------------------------------
-       PRIVATE FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/

#ifdef CARD_TEST_FUNCTIONS

static uint8_t TEST_MODULE_Card(ST_cardData_t *MyCardModuleTest)
{
    uint8_t ThisFunction_ErrorState = 0;

    /** @defgroup Testing the card holder name */
    if( (1 == TEST_CardHolderName(MyCardModuleTest)) )
    { printf("\n TEST_CardHolderName: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_CardHolderName: FAILED"); }

    /** @defgroup Testing the primary account number */
    if( (1 == TEST_primaryAccountNumber(MyCardModuleTest)) )
    { printf("\n TEST_primaryAccountNumber: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_primaryAccountNumber: FAILED"); }

    /** @defgroup Testing the card expiration date */
    if( (1 == TEST_cardExpirationDate(MyCardModuleTest)) )
    { printf("\n TEST_cardExpirationDate: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_cardExpirationDate: FAILED"); }

    /** @note: Means that the module test is passed */
    return ThisFunction_ErrorState;
}

static uint8_t TEST_CardHolderName(ST_cardData_t *cardData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getCardHolderName(cardData);

    if( (WRONG_NAME == ErrorState) )
    {
        printf("\n TEST_CardHolderName: WRONG_NAME");
    }
    else 
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_primaryAccountNumber(ST_cardData_t *cardData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getCardPAN(cardData);

    if( (WRONG_PAN == ErrorState) )
    {
        printf("\n TEST_primaryAccountNumber: WRONG_PAN");
    }
    else 
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}


static uint8_t TEST_cardExpirationDate(ST_cardData_t *cardData);
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getCardExpiryDate(cardData);

    if( (WRONG_PAN == ErrorState) )
    {
        printf("\n TEST_cardExpirationDate: WRONG_EXP_DATE");
    }
    else 
    {
        ThisFunction_ErrorState = 1;
    }

    return ThisFunction_ErrorState;
}

#endif