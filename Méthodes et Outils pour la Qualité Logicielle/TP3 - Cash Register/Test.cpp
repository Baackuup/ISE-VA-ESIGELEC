
#define BOOST_TEST_MODULE MOQL
#include <boost/test/included/unit_test.hpp>

// Module sous test
#include "Userinterface.h"

// Test-suite
BOOST_AUTO_TEST_SUITE( UT_Userinterface_parse )

	// Test-case : valeurs normales du menu
	BOOST_AUTO_TEST_CASE( menu_values )
	{
		BOOST_TEST( Userinterface_parse('b') == 1u );
	}

BOOST_AUTO_TEST_SUITE_END()
