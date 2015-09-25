#ifndef __CONTRACT_HPP
#define __CONTRACT_HPP

#include <cassert>

/*!
 * \macro   REQUIRE
 * \brief   Vérifie la validité d'une précondition.
 */
#if defined(CONTRACT_NO_PRECONDITION) || defined(CONTRACT_NO_CHECK)
    #define REQUIRE(contract, text)
#else
    #define REQUIRE(contract, text) assert(contract && text)
#endif

/*!
 * \macro   ENSURE
 * \brief   Vérifie la validité d'une postcondition.
 */
#if defined(CONTRACT_NO_POSTCONDITION) || defined(CONTRACT_NO_CHECK)
    #define ENSURE(contract, text)
#else
    #define ENSURE(contract, text) assert(contract && text)
#endif

/*!
 * \macro   INVARIANT
 * \brief   Vérifie la validité d'un invariant.
 */
#if defined(CONTRACT_NO_INVARIANT) || defined(CONTRACT_NO_CHECK)
    #define INVARIANT(contract, text)
#else
    #define INVARIANT(contract, text) assert(contract && text)
#endif

/*!
 * \macro   BEGIN_INVARIANTS_BLOCK
 * \brief   Débute un bloc d'invariants de classe.
 */
#if defined(CONTRACT_NO_INVARIANT) || defined(CONTRACT_NO_CHECK)
    #define BEGIN_INVARIANTS_BLOCK
#else
    #define BEGIN_INVARIANTS_BLOCK void _contract_check_invariants() const {
#endif

/*!
 * \macro   END_INVARIANTS_BLOCK
 * \brief   Termine un bloc d'invariants de classe.
 */
#if defined(CONTRACT_NO_INVARIANT) || defined(CONTRACT_NO_CHECK)
    #define END_INVARIANTS_BLOCK
#else
    #define END_INVARIANTS_BLOCK }
#endif

/*!
 * \macro   CHECK_INVARIANTS
 * \brief   Vérifie la validité des invariants de classe.
 */
#if defined(CONTRACT_NO_INVARIANT) || defined(CONTRACT_NO_CHECK)
    #define CHECK_INVARIANTS
#else
    #define CHECK_INVARIANTS _contract_check_invariants()
#endif

#endif // __CONTRACT_HPP
