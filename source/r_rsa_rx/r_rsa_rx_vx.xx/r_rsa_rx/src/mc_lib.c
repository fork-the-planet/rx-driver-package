/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/**********************************************************************************************************************
 * @file         mc_lib.c
 * @brief        Arbitrary Length Integer Calculation Library Source File.
 **********************************************************************************************************************/

#define MC_LIB_C

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "mc_lib.h"
#include "rsa_internal_header.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#define MASK_ON (0)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global function
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Declaration  : static void MC_init(MC_int *x)
 * Function Name: MC_init
 * Description  : Initialize Multiple length variables
 * Arguments    : x Initialization variables
 * Return Value : none.
 **********************************************************************************************************************/
/*
 static void MC_init(MC_int *x)
 {
 x->val=NULL;
 }
 */

/***********************************************************************************************************************
 * Declaration  : int16_t MC_byte2mc (uint8_t *ip, uint16_t len, MC_int *mc_op)
 * Function Name: MC_byte2mc
 * Description  : Convert 1-byte array data to MC_int type.
 * Arguments    : ip Array data in 1-byte units.
 *                len Length of array data in 1-byte units.
 *                mc_op MC_int type variable.
 * Return Value : -1 Error end.
 *                0 Normal end.
 **********************************************************************************************************************/
int16_t MC_byte2mc (uint8_t *ip, uint16_t len, MC_int *mc_op)
{
    int16_t counter;
    int16_t zeroLen;
    register uint8_t *ipr;
    register MC *valuer;

    if ((mc_op->val == NULL) || (ip == NULL) || (len > IO_DATA_BYTE_LENGTH) || (len == 0))
    {
        return -1;
    }

#if MC_BASE==16
    /* Register pointer initial value setting */
    ipr = ip;

    /* Skip 0x00 */
    zeroLen = 0;
    for (counter = 0; counter < (len - 1); ++counter)
    {
        if ( *ipr == 0x00)
        {
            ++zeroLen;
            ++ipr;
        }
        else
        {
            break;
        }
    }
    len -= zeroLen;

    mc_op->deg = ((len + 1) >> 1) - 1;

    valuer = &(mc_op->val[mc_op->deg]);

    *valuer = 0;
    for (counter = len; counter > 0; --counter)
    {
        if (counter % 2)
        {
            *valuer |= ((MC) *ipr);
            --valuer;
            ++ipr;
        }
        else
        {
            *valuer = ((MC) *ipr) << 8;
            ++ipr;
        }
    }

#else /* MC_BASE==16 */
    /* Register pointer initial value setting */
    ipr = ip;

    /* Skip 0x00 */
    zeroLen = 0;
    for (counter = 0; counter < (len - 1); ++counter)
    {
        if ((*ipr) == 0x00)
        {
            ++zeroLen;
            ++ipr;
        }
        else
        {
            break;
        }
    }

    len -= zeroLen;

    mc_op->deg = ((len + 3) >> 2) - 1;

    valuer = &(mc_op->val[mc_op->deg]);

    *valuer = 0;
    for (counter = len; counter > 0; --counter)
    {

        if ((counter % 4) == 1)
        {
            (*valuer) |= ((MC) * ipr);
            --valuer;
            ++ipr;
        }
        else if ((counter % 4) == 2)
        {
            (*valuer) |= (((MC) * ipr) << 8);
            ++ipr;
        }
        else if ((counter % 4) == 3)
        {
            (*valuer) |= (((MC) * ipr) << 16);
            ++ipr;
        }
        else
        {
            *valuer = ((MC) * ipr) << 24;
            ++ipr;
        }
    }

#endif /* MC_BASE==16 */

    return 0;

} /* End of function MC_byte2mc() */

/***********************************************************************************************************************
 * Declaration  : int16_t MC_mc2byte (MC_int *mc_ip, uint8_t *op, uint16_t *len)
 * Function Name: MC_mc2byte
 * Description  : Convert from MC_int type to 1-byte array data.
 * Arguments    : mc_ip MC_int type variable.
 *                op Array data in 1-byte units.
 *                len Length of array data in 1-byte units.
 * Return Value : -1 Error end.
 *                0 Normal end.
 **********************************************************************************************************************/
int16_t MC_mc2byte (MC_int *mc_ip, uint8_t *op, uint16_t *len)
{
    int16_t counter;
    int16_t zeroLen;
    register uint8_t *opr;
    register MC *valuer;

    if ((mc_ip->val == NULL) || (op == NULL))
    {
        return -1;
    }

#if MC_BASE==16

    if (((mc_ip->deg + 1) << 1) > IO_DATA_BYTE_LENGTH)
    {
        return -1;
    }

    /* Register pointer initial value setting */
    valuer = &(mc_ip->val[mc_ip->deg]);
    opr = op;
    zeroLen = IO_DATA_BYTE_LENGTH - ((mc_ip->deg + 1) << 1);

    for (counter = zeroLen; counter > 0; --counter)
    {
        *opr = 0x00;
        ++opr;
    }

    while (1)
    {
        if (( *valuer & 0xffff) == 0)
        {
            if (0 == mc_ip->deg)
            {
                break;
            }
            --mc_ip->deg;
            --valuer;
            opr += 2;
        }
        else
        {
            break;
        }
    }

    if (( *valuer & 0xff00) == 0)
    {
        *len = ((mc_ip->deg + 1) << 1) - 1;

        *opr = 0x00;
        ++opr;
    }
    else
    {
        *len = ((mc_ip->deg + 1) << 1);
    }

    for (counter = *len; counter > 0; --counter)
    {
        if ((counter % 2) == 0)
        {
            *opr = (uint8_t) ( *valuer >> 8);
            ++opr;
        }
        else
        {
            *opr = (uint8_t) ( *valuer);
            ++opr;
            --valuer;
        }
    }

#else /* MC_BASE==16 */

    if (((mc_ip->deg + 1) << 2) > IO_DATA_BYTE_LENGTH)
    {
        return -1;
    }

    /* Register pointer initial value setting */
    valuer = &(mc_ip->val[mc_ip->deg]);
    opr = op;
    zeroLen = IO_DATA_BYTE_LENGTH - ((mc_ip->deg + 1) << 2);

    for (counter = 0; counter < zeroLen; ++counter)
    {
        *opr = 0x00;
        ++opr;
    }

    while (1)
    {
        if (((*valuer) & 0xffffffff) == 0)
        {
            if (0 == mc_ip->deg)
            {
                break;
            }
            --mc_ip->deg;
            --valuer;
            opr += 4;
        }
        else
        {
            break;
        }
    }

    if (((*valuer) & 0xffffff00) == 0)
    {
        *len = ((mc_ip->deg + 1) << 2) - 3;

        for (counter = 0; counter < 3; ++counter)
        {
            *opr = 0x00;
            ++opr;
        }
    }
    else if (((*valuer) & 0xffff0000) == 0)
    {
        *len = ((mc_ip->deg + 1) << 2) - 2;

        for (counter = 0; counter < 2; ++counter)
        {
            *opr = 0x00;
            ++opr;
        }
    }
    else if (((*valuer) & 0xff000000) == 0)
    {
        *len = ((mc_ip->deg + 1) << 2) - 1;

        *opr = 0x00;
        ++opr;
    }
    else
    {
        *len = ((mc_ip->deg + 1) << 2);
    }

    for (counter = *len; counter > 0; --counter)
    {
        if ((counter % 4) == 0)
        {
            *opr = (uint8_t)((*valuer) >> 24);
            ++opr;
        }
        else if ((counter % 4) == 3)
        {
            *opr = (uint8_t)((*valuer) >> 16);
            ++opr;
        }
        else if ((counter % 4) == 2)
        {
            *opr = (uint8_t)((*valuer) >> 8);
            ++opr;
        }
        else
        {
            *opr = (uint8_t)(*valuer);
            ++opr;
            --valuer;
        }
    }

#endif /* MC_BASE==16 */

    return 0;
} /* End of function MC_mc2byte() */

/***********************************************************************************************************************
 * Declaration  : static void MC_movl (MC_int *x, MC_int *y)
 * Function Name: MC_movl
 * Description  : Copy a multiple-precision variable.
 * Arguments    : x Copy source of multiple-precision variable.
 *                y Copy destination of multiple-precision variable.
 * Return Value : none.
 **********************************************************************************************************************/
static void MC_movl (MC_int *x, MC_int *y)
{
    register MC *xr;
    register MC *yr;
    int16_t counter;

    /* Register variable pointer setting */
    xr = x->val;
    yr = y->val;

    /* Copy process */
    for (counter = y->deg = x->deg; counter >= 0; counter--)
    {
        *(yr++) = *(xr++);
    }
} /* End of function MC_movl() */

/***********************************************************************************************************************
 * Declaration  : int16_t MC_cmpl (MC_int *x, MC_int *y)
 * Function Name: MC_cmpl
 * Description  : Compare multiple length variables.
 * Arguments    : x Comparison source multiple length variable.
 *                y Comparison target multiple length variable.
 * Return Value : 1 The comparison destination is large.
 *                0 Equivalence.
 *                -1 The comparison destination is small.
 **********************************************************************************************************************/
int16_t MC_cmpl (MC_int *x, MC_int *y)
{
    register MC *xr;
    register MC *yr;
    int16_t counter;

    /* Most significant digit comparison */
    if (y->deg > x->deg)
    {
        return 1;
    }

    if (y->deg < x->deg)
    {
        return -1;
    }

    /* Register variable pointer setting */
    xr = x->val + x->deg;
    yr = y->val + y->deg;

    /* Comparison of the value */
    for (counter = x->deg; counter >= 0; counter--)
    {
        if ( (*yr) > (*xr))
        {
            return 1;
        }

        if ( (*(yr--)) < (*(xr--)))
        {
            return -1;
        }
    }

    return 0;
} /* End of function MC_cmpl() */

/***********************************************************************************************************************
 * Declaration  : void MC_mull (MC_int *x, MC_int *y, MC_int *z)
 * Function Name: MC_mull
 * Description  : Multiplication of multiple length variables.
 * Arguments    : x Variable x for multiplication.
 *                y Variable y for multiplication.
 *                z Multiplication result z.
 * Return Value : none.
 **********************************************************************************************************************/
void MC_mull (MC_int *x, MC_int *y, MC_int *z)
{
    register MCMC mul;
    register MC *xr;
    register MC *yr;
    register MC *zr;
    int16_t counterA;
    int16_t counterB;

    /* Register variable pointer setting */
    xr = x->val;
    yr = y->val;
    zr = z->val;

    /* If x or y is 0, the result is 0 and the process ends */
    if ((( !(x->deg)) && ( !( *xr))) || (( !(y->deg)) && ( !( *yr))))
    {
        z->deg = 0;
        *zr = 0;
        return;
    }

    /* Assign the maximum value of the most significant byte of the multiplication result to deg of variable z
       and clear variable z */
    z->deg = x->deg + y->deg + 1;
    for (counterA = z->deg; counterA >= 0; counterA--)
    {
        *(zr++) = 0;
    }

    /* Multiplication process */
    zr = z->val;
    mul = 0;
    for (counterA = x->deg; counterA >= 0; counterA--, xr++, zr -= y->deg)
    {

        mul = 0;
        yr = y->val;
        for (counterB = y->deg; counterB >= 0; counterB--)
        {

            mul += ((MCMC) ( *xr) * (MCMC) ( *(yr++)));
            mul += ( *zr);
            *(zr++) = (MC) (mul & MC_MASK);
            mul >>= MC_BASE;
        }
        *zr = (MC) mul;
    }

    /* When the most significant carry is 0, the most significant byte is reduced by 1. */
    if ( !mul)
    {
        z->deg--;
    }
} /* End of function MC_mull() */

/***********************************************************************************************************************
 * Declaration  : void MC_sqrl (MC_int *x, MC_int *z)
 * Function Name: MC_sqrl
 * Description  : Square of multiple length variables.
 * Arguments    : x Value to be squared.
 *                z Calculation result of squaring x.
 * Return Value : none.
 **********************************************************************************************************************/
void MC_sqrl (MC_int *x, MC_int *z)
{
    register MCMC mul;
    register MCMC sum;
    register MC *xr;
    register MC *yr;
    register MC *zr;
    MCMC carry;
    int16_t counterA;
    int16_t counterB;

    xr = x->val;
    zr = z->val;

    if (( !(x->deg)) && ( !( *xr)))
    {
        z->deg = 0;
        *zr = 0;
        return;
    }

    z->deg = (x->deg << 1) + 1;
    for (counterA = z->deg; counterA >= 0; counterA--)
    {
        *(zr++) = 0;
    }

    mul = 0;
    for (counterA = 0; counterA <= (int16_t) x->deg; counterA++)
    {

        mul = 0;
        carry = 0;
        yr = x->val;
        zr = z->val + counterA;

        for (counterB = counterA; counterB > 0; counterB--)
        {

            sum = (MCMC) ( *xr) * (MCMC) ( *(yr++));
            mul += (sum + ( *zr));
            sum += carry;
            if ((mul += sum) < sum)
            {
                carry = (MCMC) 1 << MC_BASE;
            }
            else
            {
                carry = 0;
            }

            *(zr++) = (MC) (mul & MC_MASK);
            mul >>= MC_BASE;
        }

        mul += ((MCMC) ( *xr++) * (MCMC) ( *yr));
        mul += (carry + ( *zr));
        *(zr++) = (MC) (mul & MC_MASK);
        mul >>= MC_BASE;
        *zr = (MC) mul;
    }

    if ( !mul)
    {
        z->deg--;
    }
}

/***********************************************************************************************************************
 * Declaration  : void MC_reml (MC_int *x, MC_int *y, MC_int *r)
 * Function Name: MC_reml
 * Description  : Surplus calculation of multiple length variables.
 * Arguments    : x Variable to divide.
 *                y Variable to be divided.
 *                r Calculation result.
 * Return Value : none.
 **********************************************************************************************************************/
void MC_reml (MC_int *x, MC_int *y, MC_int *r)
{
    register MCMC div;
    register MCMC mul;
    register MC quo;
    register MC *ar;
    register MC *br;
    int16_t counterA;
    int16_t counterB;
    uint16_t sft;
    uint16_t deg;

    /* The MC unit is smaller than the remainder x */
    if (y->deg < x->deg)
    {
        MC_movl(y, r);
        return;
    }

    deg = y->deg - x->deg;

    /* x is 1MC units remainder calculation */
    if ( !x->deg)
    {
        r->deg = 0;
        *r->val = MC_rems( *x->val, y);
        return;
    }

    /* Find the most significant bit of x for remainder calculation */
    for (sft = MC_BASE; sft > 0; sft--)
    {
        if (x->val[x->deg] & ((MC) 1 << (sft - 1)))
        {
            break;
        }
    }

    ar = x->val + x->deg;
    div = *ar;
    for (counterA = x->deg; counterA > 0; counterA--)
    {
        div <<= MC_BASE;
        div ^= (*(ar - 1));
        *(ar--) = (MC) ((div >> sft) & MC_MASK);
    }
    *ar = (MC) ((div << (MC_BASE - sft)) & MC_MASK);

    ar = y->val + y->deg;
    br = r->val + y->deg + 1;
    div = 0;
    for (counterA = y->deg; counterA >= 0; counterA--)
    {
        div ^= (*(ar--));
        *(br--) = (MC) ((div >> sft) & MC_MASK);
        div <<= MC_BASE;
    }
    *br = (MC) ((div >> sft) & MC_MASK);

    for (counterA = deg; counterA >= 0; counterA--)
    {

        ar = r->val + x->deg + counterA;
        br = x->val + x->deg;

        if ((div = *(ar + 1)) == (*br))
        {
            quo = MC_MASK;
        }
        else
        {
            div <<= MC_BASE;
            div ^= (*(ar--));
            quo = (MC) (div / ( *br));
            div -= (quo * ( *(br--))); /* Upper bits can be ignored */
            div <<= MC_BASE;
            div ^= (*ar);
            mul = (MCMC) quo * (MCMC) ( *br);
            if (mul > div)
            {
                mul -= div;
                quo--;
                div = (MCMC) *(br + 1) << MC_BASE;
                if (mul > (div + ( *br)))
                {
                    quo--;
                }
            }
        }

        ar = r->val + counterA;
        br = x->val;
        div = 0;
        mul = 0;

        for (counterB = x->deg; counterB >= 0; counterB--)
        {
            mul += ((MCMC) quo * (MCMC) ( *(br++)));
            div += (*ar);
            div -= (mul & MC_MASK);
            *(ar++) = (MC) (div & MC_MASK);
            mul >>= MC_BASE;
            div >>= MC_BASE;
            div ^= (div << MC_BASE); /* OH! MESSIVE */
        }
        div += (*ar);
        div -= (mul & MC_MASK);
        *ar = (MC) (div & MC_MASK);
        div >>= MC_BASE;

        if (div)
        {
            ar = r->val + counterA;
            br = x->val;
            div = 0;

            for (counterB = x->deg; counterB >= 0; counterB--)
            {
                div += (*ar);
                div += (*(br++));
                *(ar++) = (MC) (div & MC_MASK);
                div >>= MC_BASE;
            }
            (*ar) += (MC) div;
        }
    }

    ar = x->val + x->deg;
    div = *ar;
    *ar = (MC) ((div >> (MC_BASE - sft)) & MC_MASK);
    for (counterA = x->deg; counterA > 0; counterA--)
    {
        div <<= MC_BASE;
        div ^= (*(--ar));
        *ar = (MC) ((div >> (MC_BASE - sft)) & MC_MASK);
    }

    br = r->val;
    div = *br;
    for (counterA = x->deg; counterA > 0; counterA--)
    {
        div ^= ((MCMC) *(br + 1) << MC_BASE);
        *(br++) = (MC) (div >> (MC_BASE - sft));
        div >>= MC_BASE;
    }
    *br = (MC) (div >> (MC_BASE - sft));

    br = r->val + x->deg;
    for (counterA = x->deg; counterA > 0; counterA--)
    {
        if ( *(br--))
        {
            break;
        }
    }
    r->deg = counterA;
} /* End of function MC_reml() */

/***********************************************************************************************************************
 * Declaration  : MC MC_KWD MC_rems (MC x, MC_int *y)
 * Function Name: MC_rems
 * Description  : Surplus calculation of multiple length variables.
 * Arguments    : x the value to divide y.
 *                y The value to be divided.
 * Return Value : MC, Remainder operation result.
 **********************************************************************************************************************/
MC MC_KWD MC_rems (MC x, MC_int *y)
{
    register MCMC rem;
    register MC *yr;
    int16_t counter;
    ;

    yr = y->val + y->deg;

    rem = 0;

    for (counter = y->deg; counter >= 0; counter--)
    {
        rem ^= (*(yr--));
        rem %= x;
        rem <<= MC_BASE;
    }

    return (MC) (rem >> MC_BASE);
} /* End of function MC_rems() */

/***********************************************************************************************************************
 * Declaration  : int16_t MC_mulm(MC_int *x, MC_int *y, MC_int *z, MC_int *m)
 * Function Name: MC_mulm
 * Description  : Multi-precision variable multiplication remainder operation (z = x * y mod m).
 * Arguments    : x Variable x.
 *                y Variable y.
 *                z Operation result z.
 *                m Variable m.
 * Return Value : -3 Input value is incorrect
 *                 -1 Memory allocation failure
 *                 0 Normal end
 **********************************************************************************************************************/
#if 0
int16_t MC_mulm(MC_int *x, MC_int *y, MC_int *z, MC_int *m)
{
    MC_int t;

    /*
     MC_init(&t);
     */

    /*
     if(x->sgn||y->sgn||m->sgn){
     return -3;
     }
     */

    if (MC_cmpl(x, m) <= 0)
    {
        return -3;
    }

    if (MC_cmpl(y, m) <= 0)
    {
        return -3;
    }

    t.val = (MC *)MC_memory[0];

    /* z-> sgn = 0; */
    MC_mull(x, y, &t); /* t = x * y */
    MC_reml(m, &t, z); /* z = t mod m */

    return 0;
} /* End of function MC_mulm() */
#endif /* 0 */

/***********************************************************************************************************************
 * Declaration  : int16_t MC_powm (MC_int *x, MC_int *y, MC_int *z, MC_int *m, uint8_t *mc_memory0, uint8_t *mc_memory1)
 * Function Name: MC_powm
 * Description  : Modular exponentiation (z = x^y mod m).
 * Arguments    : x Variable x.
 *                y Variable y.
 *                z Calculation result z.
 *                m Variable m.
 * Return Value : -3 Input value is incorrect
 *                -1 Memory allocation failure
 *                0 Normal end
 **********************************************************************************************************************/
int16_t MC_powm (MC_int *x, MC_int *y, MC_int *z, MC_int *m, uint8_t *mc_memory0, uint8_t *mc_memory1)
{
    MC_int pow;
    MC_int tmp;
    MC c;
    int16_t counterA;
    int16_t counterB;

    pow.val = (MC *) mc_memory0; /* object is holds the even alignment */
    pow.len = MC_INT_ARRAY_LENGTH;

    tmp.val = (MC *) mc_memory1; /* object is holds the even alignment */
    tmp.len = MC_INT_ARRAY_LENGTH;

    MC_movl(x, &pow);

    z->deg = 0;
    z->val[0] = 1;

    for (counterA = 0; counterA < y->deg; counterA++)
    {
        for (counterB = 0; counterB < MC_BASE; counterB++)
        {

            if (y->val[counterA] & ((MC) 1 << counterB))
            {
                MC_mull(z, &pow, &tmp); /* tmp = z * pow */
                MC_reml(m, &tmp, z); /* z = tmp mod m */
            }
            MC_sqrl( &pow, &tmp); /* tmp = pow^2 */
            MC_reml(m, &tmp, &pow); /* pow = tmp mod m */
        }
    }

    for (c = y->val[y->deg]; c; c >>= 1)
    {

        if (c & 1)
        {
            MC_mull(z, &pow, &tmp); /* tmp = pow * z */
            MC_reml(m, &tmp, z); /* z = tmp mod m */
        }
        MC_sqrl( &pow, &tmp); /* tmp = pow^2 */
        MC_reml(m, &tmp, &pow); /* pow = tmp mod m */
    }

    return 0;
} /* End of function MC_powm() */


