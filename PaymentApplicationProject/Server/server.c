/**
 * @file Server.c
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

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

/*
-----------------------------------------------------------------
-       GLOBAL VARIABLES
-----------------------------------------------------------------
*/

static ST_transaction_t TransactionsDataBase[DB_TRANSACTIONS_MAX] = 
{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static ST_accountsDB_t AccountsDataBase[DB_ACCOUNTS_MAX] = 
{
    {45559.4, "4567 6543 1423 4321"},
    {21021.3, "4567 6543 4312 4321"},
    {3216.2,  "4567 6543 1342 4321"},
    {44625.1, "4567 6543 4213 4321"}
};

static uint16_t CurrentAccountDBIndex = 0;

/*
-----------------------------------------------------------------
-       PUBLIC FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/

/**
 * @brief This function will take all transaction data and validate its data.
 * 
 * @param transData 
 * @return EN_transState_t 
 */
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_serverError_t ThisFunction_ErrorState = APPROVED;

    if( (ACCOUNT_NOT_FOUND == isValidAccount(&(transData->cardHolderData))) )
    {
        ThisFunction_ErrorState = DECLINED_STOLEN_CARD;
        transData->transState = DECLINED_STOLEN_CARD;
    }
    else if( (LOW_BALANCE == isAmountAvailable(&(transData->terminalData))) )
    {
        ThisFunction_ErrorState = DECLINED_INSUFFECIENT_FUND;
        transData->transState = DECLINED_INSUFFECIENT_FUND;
    }
    else 
    {
        if( (SAVING_FAILED == saveTransaction(transData)) ) 
        {
            ThisFunction_ErrorState = INTERNAL_SERVER_ERROR;
        }
        else
        {
            AccountsDataBase[CurrentAccountDBIndex].balance -= transData->terminalData.transAmount;
        }
    }

    return ThisFunction_ErrorState;
}/** @end recieveTransactionData */
/**
 * @brief This function will take terminal data and validate these data.
 * 
 * @param cardData 
 * @return EN_serverError_t 
 */
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    EN_serverError_t ThisFunction_ErrorState = ACCOUNT_NOT_FOUND;

    /* Check if the PAN is valid */
    register uint8_t i = 0;
    for(i = 0; (i < DB_ACCOUNTS_MAX); ++i)
    {
        if( (0 == strcmp(cardData->primaryAccountNumber, AccountsDataBase[i].primaryAccountNumber)) )
        {
            ThisFunction_ErrorState = SERVER_OK;
            CurrentAccountDBIndex = i;
            break;
        }else {;}
    }
    
    return ThisFunction_ErrorState;
}/** @end isValidAccount */
/**
 * @brief 	
 * This function will take terminal data and validate these data.
 * 
 * @param termData 
 * @return EN_serverError_t 
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    EN_serverError_t ThisFunction_ErrorState = SERVER_OK;

    if( (termData->transAmount > AccountsDataBase[CurrentAccountDBIndex].balance) )
    {
        ThisFunction_ErrorState = LOW_BALANCE;
    }
    else {;}

    return ThisFunction_ErrorState;
}/** @end isAmountAvailable */
/**
 * @brief  	
 * This function will take all transaction data into the transactions database.
 * 
 * @param transData 
 * @return EN_serverError_t 
 */
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t ThisFunction_ErrorState = SERVER_OK;

    static uint32_t TransactionsSequenceNumber = 0;

    if( (TransactionsSequenceNumber > DB_TRANSACTIONS_MAX) )
    {
        ThisFunction_ErrorState = SAVING_FAILED;
    }
    else
    {
        TransactionsDataBase[TransactionsSequenceNumber].cardHolderData = transData->cardHolderData;
        TransactionsDataBase[TransactionsSequenceNumber].terminalData = transData->terminalData;
        TransactionsDataBase[TransactionsSequenceNumber].transState = transData->transState;
        TransactionsDataBase[TransactionsSequenceNumber].transState = TransactionsSequenceNumber;
        transData->transactionSequenceNumber = TransactionsSequenceNumber;

        ++TransactionsSequenceNumber;
    }

    return ThisFunction_ErrorState;
}/** @end saveTransaction */

/**
 * @brief	
 * This function will take all transaction data into the transactions database.
 * 
 * @param transactionSequenceNumber 
 * @param transData 
 * @return EN_serverError_t 
 */
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    EN_serverError_t ThisFunction_ErrorState = SERVER_OK;

    if( (transactionSequenceNumber > DB_TRANSACTIONS_MAX) )
    {
        ThisFunction_ErrorState = TRANSACTION_NOT_FOUND;
    }
    else
    {
        transData->cardHolderData = TransactionsDataBase[transactionSequenceNumber].cardHolderData;
        transData->terminalData = TransactionsDataBase[transactionSequenceNumber].terminalData;
        transData->transState = TransactionsDataBase[transactionSequenceNumber].transState;
        transData->transactionSequenceNumber = 
        TransactionsDataBase[transactionSequenceNumber].transactionSequenceNumber;
    }

    return ThisFunction_ErrorState;
}/** @end getTransaction */

/*
-----------------------------------------------------------------
-       PRIVATE FUNCTION IMPLEMENTATION
-----------------------------------------------------------------
*/

#ifdef SERVER_TEST_FUNCTIONS

static uint8_t TEST_MODULE_Server(uint32_t transactionSequenceNumber, 
                                  ST_transaction_t *MyServerModuleTest)
{
    uint8_t ThisFunction_ErrorState = 0;

    /** @defgroup Testing receive transactions data */
    if( (1 == TEST_recieveTransactionData(MyServerModuleTest)) )
    { printf("\n TEST_recieveTransactionData: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_recieveTransactionData: FAILED"); }
    
    /** @defgroup Testing is valid account */
    if( (1 == TEST_isValidAccount(&(MyServerModuleTest->cardHolderData))) )
    { printf("\n TEST_isValidAccount: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_isValidAccount: FAILED"); }

    /** @defgroup Testing is amount available */
    if( (1 == TEST_isAmountAvailable(&(MyServerModuleTest->terminalData))) )
    { printf("\n TEST_isAmountAvailable: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_isAmountAvailable: FAILED"); }

    /** @defgroup Testing save transaction */
    if( (1 == TEST_saveTransaction(MyServerModuleTest)) )
    { printf("\n TEST_saveTransaction: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_saveTransaction: FAILED"); }
    
    /** @defgroup Testing get transaction */
    if( (1 == TEST_getTransaction(transactionSequenceNumber, MyServerModuleTest)) )
    { printf("\n TEST_getTransaction: PASSED"); ThisFunction_ErrorState = 1;}
    else
    { printf("\n TEST_getTransaction: FAILED"); }

    /** @note: Means that the module test is passed */
    return ThisFunction_ErrorState;
}

static uint8_t TEST_recieveTransactionData(ST_transaction_t *transData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = recieveTransactionData(transData);

    if( (APPROVED == ErrorState) )
    { printf("\n TEST_recieveTransactionData: APPROVED"); }
    else if( (DECLINED_INSUFFECIENT_FUND = ErrorState) )
    { printf("\n TEST_recieveTransactionData: DECLINED_INSUFFECIENT_FUND"); }
    else if( (DECLINED_INSUFFECIENT_FUND = ErrorState) )
    { printf("\n TEST_recieveTransactionData: DECLINED_STOLEN_CARD"); }
    else if( (DECLINED_INSUFFECIENT_FUND = ErrorState) )
    { printf("\n TEST_recieveTransactionData: INTERNAL_SERVER_ERROR"); }
    else 
    { ThisFunction_ErrorState = 1; }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isValidAccount(ST_cardData_t *cardData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isValidAccount(cardData);

    if( (ACCOUNT_NOT_FOUND == ErrorState) )
    { printf("\n TEST_isValidAccount: ACCOUNT_NOT_FOUND"); }
    else
    { ThisFunction_ErrorState = 1; }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_isAmountAvailable(ST_terminalData_t *termData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = isValidAccount(termData);

    if( (LOW_BALANCE == ErrorState) )
    { printf("\n TEST_isAmountAvailable: LOW_BALANCE"); }
    else
    { ThisFunction_ErrorState = 1; }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_saveTransaction(ST_transaction_t *transData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = saveTransaction(transData);

    if( (SAVING_FAILED == ErrorState) )
    { printf("\n TEST_saveTransaction: SAVING_FAILED"); }
    else
    { ThisFunction_ErrorState = 1; }

    return ThisFunction_ErrorState;
}

static uint8_t TEST_getTransaction(uint32_t transactionSequenceNumber, 
                                   ST_transaction_t *transData)
{
    uint8_t ThisFunction_ErrorState = 0;

    uint8_t ErrorState = getTransaction(transactionSequenceNumber, transData);

    if( (TRANSACTION_NOT_FOUND == ErrorState) )
    { printf("\n TEST_getTransaction: TRANSACTION_NOT_FOUND"); }
    else
    { ThisFunction_ErrorState = 1; }

    return ThisFunction_ErrorState;
}
#endif