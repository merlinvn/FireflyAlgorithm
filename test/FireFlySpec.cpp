//
// Created by Merlin on 24-Jul-15.
//


#include "catch.hpp"
#include "FireFly.h"


SCENARIO( "Firefly spec", "[firefly]" ) {

    WHEN("Create new Firefiy") {
        FireFly fireFly;
        THEN("FireFly must exist") {
            REQUIRE((&fireFly) != nullptr);
        }
    }

    WHEN("Create A new firefly with dimension") {

        FireFly fireFly(5);
        THEN("FireFly have 5 position") {
            REQUIRE(fireFly.position.size() == 5);
        }
        AND_THEN("each position is 0.0") {
            for (double d : fireFly.position) {
                REQUIRE(d == 0.0);
            }
        }

        AND_THEN("error amd intensity should be 0.0"){
            REQUIRE(fireFly.error == 0.0);
            REQUIRE(fireFly.intensity == 0.0);
        }

    }

    GIVEN("Two FireFly")
    {
        FireFly fireFly1(3), fireFly2(3);

        WHEN("firefly1's error is 3 and fireflye2's error is 2") {
            fireFly1.error = 3.0;
            fireFly2.error = 2.0;
            THEN("firefly1 should be greater than firefly2") {
                REQUIRE(fireFly1 > fireFly2);
            }
            THEN("firefly1 should be greater than or equal firefly2") {
                REQUIRE(fireFly1 >= fireFly2);
            }
        }


        WHEN("firefly1's error is 1 and fireflye2's error is 2") {
            fireFly1.error = 1.0;
            fireFly2.error = 2.0;
            THEN("firefly1 should less than firefly2") {
                REQUIRE(fireFly1 < fireFly2);
            }

            THEN("firefly1 should less than or equal firefly2") {
                REQUIRE(fireFly1 <= fireFly2);
            }
        }


        WHEN("firefly1's error is 2 and fireflye2's error is 2") {
            fireFly1.error = 2.0;
            fireFly2.error = 2.0;
            THEN("firefly1 should equal firefly2") {
                REQUIRE(fireFly1 == fireFly2);
            }

            THEN("firefly1 should less than or equal firefly2") {
                REQUIRE(fireFly1 <= fireFly2);
            }

            THEN("firefly1 should greater than or equal firefly2") {
                REQUIRE(fireFly1 >= fireFly2);
            }
        }
    }

}
