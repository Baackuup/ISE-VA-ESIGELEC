/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path      : Cashregister.c
 * Author         : M.W.Richardson
 * Date           : 16/05/13
 * Copyright      : (c) 2013 Liverpool Data Research Associates
 */

#include <stdio.h>

#include "Misrac_types.h"
#include "Cashregister.h"
#include "Countedproduct.h"
#include "Productdatabase.h"
#include "Userinterface.h"

#define MAX_PRODUCTS_IN_BASKET 10U
#define MAX_STRING             64U

#define NULL_POINTER ((void *)0)

typedef enum
{
  state_Idle, state_Active
} tCashRegisterState;

static tCashRegisterState state = state_Idle;
static const struct Product* ShoppingBasket[MAX_PRODUCTS_IN_BASKET] = { 0 };
static LDRA_uint32_t theBarcode = 0U;
static LDRA_uint32_t scannedProducts = 0U;

/* Forward declarations */
/* ==================== */

static void addProduct(const struct Product * aProduct);
static void countProducts(void);
static void endSession(void);
static void generateTicket(void);
static void identifyProduct(const LDRA_uint32_t aBarcode);
static void removeLastProduct(void);
static void startSession(void);

/* Private functions */
/* ================= */

/*
 * Add product to the list of scanned products
 * Unless there are too many products in which case
 * Just ignore the product
 */
static void addProduct(const struct Product * aProduct)
{
  LDRA_char_t message[MAX_STRING];

  if (scannedProducts < MAX_PRODUCTS_IN_BASKET)
  {
    if (aProduct != NULL_POINTER)
    {
      ShoppingBasket[scannedProducts] = aProduct;
      scannedProducts++;
      (void) sprintf(message, "Adding %s", aProduct->name);
      Userinterface_show(&message[0]);
    }
  }
  else
  {
    Userinterface_show("Basket is full");
  }
}

/*
 * Count how many there are of each product
 */
static void countProducts(void)
{
  struct CountedProduct * currentCountedProduct;
  LDRA_uint32_t iProduct = 0U;
  const struct Product * currentProduct;

  Productdatabase_resetCountedProducts();
  /* iterate over each product that has been scanned */
  while (iProduct < scannedProducts)
  {
    currentProduct = ShoppingBasket[iProduct];
    if ( currentProduct != NULL_POINTER )
    {
      currentCountedProduct = Productdatabase_getCountedProduct(currentProduct);
      if (currentCountedProduct != NULL_POINTER)
      {
        (currentCountedProduct->count)++;
      }
    }
    iProduct++;
  }
}

/*
 * End the session, by clearing all counted products and scanned products
 */
static void endSession(void)
{
  scannedProducts = 0U;
  ShoppingBasket[scannedProducts] = NULL_POINTER;
  Userinterface_show(" ");
}

/*
 * Generate a ticket showing total cost etc
 */
static void generateTicket(void)
{
  LDRA_char_t msgString[MAX_STRING];
  LDRA_uint32_t sum_total = 0U;
  LDRA_char_t theSpecialoffer;
  LDRA_uint32_t thePrice;
  LDRA_uint32_t theCount;
  LDRA_uint32_t theUnitPrice;
  LDRA_uint32_t iter = 0U;
  struct CountedProduct* aCountedProduct;

  countProducts();
  Userinterface_scan("");
  Userinterface_scan("=======================================");
  Userinterface_scan("====   LDRA MISRA C  Supermarket   ====");
  Userinterface_scan("=======================================");

  /* Iterate through and print out each CountedProduct if the count +ve */

  while (iter < MAX_PRODUCTS)
  {
    aCountedProduct = Productdatabase_getSpecificCountedProduct(iter);
    if (aCountedProduct != NULL_POINTER)
    {
      theCount = aCountedProduct->count;
      if (theCount > 0U)
      {
        if (aCountedProduct->itsProduct->specialOffer == NO_OFFER)
        {
          theSpecialoffer = ' ';
        }
        else
        {
          theSpecialoffer = '*';
        }
        thePrice = Specialoffer_getPrice(aCountedProduct->count,
            aCountedProduct->itsProduct->unitPrice,
            aCountedProduct->itsProduct->specialOffer,
			aCountedProduct->itsProduct->name);
        sum_total += thePrice;

        theUnitPrice = aCountedProduct->itsProduct->unitPrice;
        (void) sprintf(msgString, "%12s %2d at %6.2f%c  %6.2f",
            aCountedProduct->itsProduct->name, aCountedProduct->count,
            (LDRA_float32_t) theUnitPrice / 100.0F, theSpecialoffer,
            (LDRA_float32_t) thePrice / 100.0F);
        Userinterface_scan(&msgString[0]);
      }
    }
    iter++;
  }
  (void) sprintf(msgString, "                    total = %6.2f",
      (LDRA_float32_t) sum_total / 100.0F);
  Userinterface_scan(&msgString[0]);
  Userinterface_scan("=======================================");
}

/*
 * Identify from the barcode, which product it is
 * If the product doesn't exist, then return null.
 */
static void identifyProduct(const LDRA_uint32_t aBarcode)
{
  const struct Product * scannedProduct;
  scannedProduct = Productdatabase_getProduct(aBarcode);

  if (NULL_POINTER == scannedProduct)
  {
    Userinterface_show("Unknown barcode");
  }
  else
  {
    addProduct(scannedProduct);
  }
}


/*
 * Remove the last product scannned
 */
static void removeLastProduct(void)
{
  LDRA_char_t lpmessage[MAX_STRING];
  const struct Product* lastProduct;

  if (scannedProducts > 0U)
  {
    scannedProducts--;
    lastProduct = ShoppingBasket[scannedProducts];
    if (lastProduct != NULL_POINTER)
    {
      (void) sprintf(lpmessage, "Removing %s", lastProduct->name);
      Userinterface_show(&lpmessage[0]);
    }
  }
}

/*
 * Start a session,
 */
static void startSession(void)
{
  /* Empty the shopping basket */
  scannedProducts = 0U;
  while (scannedProducts < MAX_PRODUCTS_IN_BASKET)
  {
    ShoppingBasket[scannedProducts] = NULL_POINTER;
    scannedProducts++;
  }
  scannedProducts = 0U;
  Userinterface_show("Ready");
}

/* Public functions */

/*
 * A barcode has been read
 */
void Cashregister_barcode(const LDRA_uint32_t aCode)
{
  if (state == state_Active)
  {
    identifyProduct(aCode);
  }
}

/*
 * The cancel key has been pressed
 */
void Cashregister_cancel(void)
{
  if (state == state_Active)
  {
    if (scannedProducts == 0U)
    {
      endSession();
      state = state_Idle;
    }
    else
    {
      removeLastProduct();
    }
  }
}

/*
 * The enter code key has been pressed
 */
void Cashregister_code(void)
{
  if (state == state_Active)
  {
    identifyProduct(theBarcode);
    theBarcode = 0U;
  }
}

/*
 * The end session key has been pressed
 */
void Cashregister_end(void)
{
  if (state == state_Idle)
  {
    generateTicket();
    endSession();
    state = state_Idle;
  }
}

/*
 * A key between 0 and 9 has been pressed
 */
void Cashregister_key(const LDRA_uint32_t aKey)
{
  if (state == state_Active)
  {
    theBarcode = (theBarcode * 10U) + aKey;
  }
}

/*
 * The start session key has been pressed
 */
void Cashregister_start(void)
{
  if (state == state_Idle)
  {
    theBarcode = 0U;
    startSession();
    state = state_Active;
  }
}
