/**
 * @file application.c
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

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "application.h"

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
 * @brief 
 * Function to start the application
 */
void appStart(void)
{
/** ------------------------------------
 * @defgroup: Get the card data 
 * -------------------------------------
 **/
    ST_cardData_t Card;
    /** @def: Card Holder Name */
    EN_cardError_t CardHolderName_ErrorState = getCardHolderName(&Card);
#ifdef x__FULL_ERROR_STATE__x
    if( (WRONG_NAME == CardHolderName_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Invalid Card Name.");
        EXCEPTION_RETURN();
    }else {;}
#endif
    /** @def: Card Expiration Date */
    EN_cardError_t CardExpDate_ErrorState = getCardExpiryDate(&Card);
#ifdef x__FULL_ERROR_STATE__x
    if( (WRONG_EXP_DATE == CardExpDate_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Invalid Card Expiration Date.");
        EXCEPTION_RETURN();
    }else {;}
#endif
    /** @def: Card Primary Account Number */
    EN_cardError_t CardPAN_ErrorState = getCardPAN(&Card);
#ifdef x__FULL_ERROR_STATE__x
    if( (WRONG_PAN == CardPAN_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Invalid Card PAN.");
        EXCEPTION_RETURN();
    }else {;}
#endif
/** ------------------------------------
 * @defgroup: Process the card data 
 * -------------------------------------
 **/
    ST_terminalData_t Terminal;

    /** @def: Setting the max transaction amount: USED FOR DEBUGGING */
    Terminal.transAmount = 50000.0;
    
    /** @def: Get Transaction Date */
    EN_terminalError_t GetTransDate_ErrorState = getTransactionDate(&Terminal);
#ifdef x__FULL_ERROR_STATE__x
    if( (WRONG_DATE == GetTransDate_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Invalid Transaction Date.");
        EXCEPTION_RETURN();
    }else {;}
#endif
    /** @def: Check if card is expired */
    EN_terminalError_t ExpiredCard_ErrorState = isCardExpired(Card, Terminal);
    if( (EXPIRED_CARD == ExpiredCard_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Card is expired.");
        EXCEPTION_RETURN();
    }else {;}
    /** @def: Get Transaction Amount */
    EN_terminalError_t TransAmount_ErrorState = getTransactionAmount(&Terminal);
#ifdef x__FULL_ERROR_STATE__x
    if( (INVALID_AMOUNT == TransAmount_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Invalid Transaction Amount.");
        EXCEPTION_RETURN();
    }else {;}
#endif
    /** @def: Check if exceeded limit. */
    EN_terminalError_t TransAmountLimit_ErrorState = isBelowMaxAmount(&Terminal);
    if( (EXCEED_MAX_AMOUNT == TransAmountLimit_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Transaction Amount Exceeded limit.");
        EXCEPTION_RETURN();
    }else {;}
/** ------------------------------------
 * @defgroup: Process the transaction 
 * -------------------------------------
 **/
    /** @def: Start the transaction process. */
    ST_transaction_t Transaction = {.cardHolderData = Card, 
                                    .terminalData   = Terminal,
                                    };
    EN_transState_t Transaction_ErrorState = recieveTransactionData(&Transaction);
    if( (DECLINED_STOLEN_CARD == Transaction_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Invalid Account.");
        EXCEPTION_RETURN();
    }
    else if( (DECLINED_INSUFFECIENT_FUND ==  Transaction_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Insuffecient funds.");
        EXCEPTION_RETURN();
    } 
    else if( (INTERNAL_SERVER_ERROR == Transaction_ErrorState) )
    {
        EXCEPTION_EXIT_MSG("Inernal Server Error.");
        EXCEPTION_RETURN();
    }
    else {;}
    
    SUCCESSFUL_MSG("Successfully sent transaction.");
    SUCCESSFUL_RETURN();
}/** @end appStart */

/*
-----------------------------------------------------------------
-       PRIVATE FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/
