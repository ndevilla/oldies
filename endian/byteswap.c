
/*
 * Change the following typedefs to make sure that:
 * short16     is a  signed   integer on 16 bits.
 * ushort16    is an unsigned integer on 16 bits.
 * long32      is a  signed   integer on 32 bits.
 * ulong32     is an unsigned integer on 32 bits.
 */

/* The following is valid on most 32-bit platforms */
typedef short short16 ;
typedef unsigned short ushort16 ;
typedef long long32 ;
typedef unsigned long ulong32 ;

/* The following would be valid on most 64-bit platforms */
/*
typedef short short16 ;
typedef unsigned short ushort16 ;
typedef int long32 ;
typedef unsigned int ulong32 ;
 */



/*-------------------------------------------------------------------------*/
/**
  @name     swap_2_bytes
  @memo     Swap bytes in a 16-bit number: 0x1234 becomes 0x3412.
  @param    w   16-bit number.
  @return   Swapped 16-bit value.
  @doc
 
  The input value is not modified.
 */
/*--------------------------------------------------------------------------*/
 
static short16
swap_2_bytes(short16 w)
{
    register short16 tmp ;
    tmp = (w & (ushort16)0x00FF) ;
    tmp = ((w & (ushort16)0xFF00) >> (ushort16)0x08) | (tmp << (ushort16)0x08);
    return tmp ;
}
 
/*-------------------------------------------------------------------------*/
/**
  @name     swap_4_bytes
  @memo     Swap bytes in a 32-bit number
  @param    dw  32-bit number.
  @return   Swapped 32-bit value.
  @doc
 
  The input value is not modified.
 
  Swapping means that 0x12345678 becomes 0x78563412.
 */
/*--------------------------------------------------------------------------*/
 
static long32
swap_4_bytes(long32 dw)
{
    register long32 tmp;
    tmp =  (dw & (ulong32)0x000000FF);
    tmp = ((dw & (ulong32)0x0000FF00) >> 0x08) | (tmp << (ulong32)0x08);
    tmp = ((dw & (ulong32)0x00FF0000) >> 0x10) | (tmp << (ulong32)0x08);
    tmp = ((dw & (ulong32)0xFF000000) >> 0x18) | (tmp << (ulong32)0x08);
    return tmp;
}
 

/*-------------------------------------------------------------------------*/
/**
  @name     swap_bytes
  @memo     swaps bytes in a variable of given size
 
  @param    p pointer to void (generic pointer)
  @param    s size of the element to swap, pointed to by p
 
  @return   void
 
  @doc
 
  This byte-swapper is portable and works for any even variable size.
  It is not truly the most efficient ever, but does its job fine
  everywhere this file compiles.

  This input array is modified.
 */
/*--------------------------------------------------------------------------*/
 
void swap_bytes(void * p, size_t s)
{
    unsigned char tmp, *a, *b ;
 
    a = (unsigned char*)p ;
    b = a + s ;
 
    while (a<b) {
        tmp = *a ;
        *a++ = *--b ;
        *b = tmp ;
    }
} 
