/**
 * @file Card.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/** @def Header Guards */
#ifndef _CARD_H_
#define _CARD_H_

/*
-----------------------------------------------------------------
-       DEFINES
-----------------------------------------------------------------
*/

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, 
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;

/*
-----------------------------------------------------------------
-       PUBLIC FUNCTION DECLARATION
-----------------------------------------------------------------
*/

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* _CARD_H_ */
