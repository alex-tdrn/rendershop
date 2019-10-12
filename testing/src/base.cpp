#include "catch.hpp"
#include "renderdeck/InputDataPort.hpp"
#include "renderdeck/OutputDataPort.hpp"
#include "renderdeck/InputEventPort.hpp"
#include "renderdeck/OutputEventPort.hpp"

TEST_CASE("base.ports.Connections between input and output ports")
{
	class TestOutputPort;
	class TestInputPort : public InputPort<TestOutputPort> {};
	class TestOutputPort : public OutputPort<TestInputPort> {};

	GIVEN("A disconnected input port A")
	{
		TestInputPort A;
		REQUIRE(!A.isConnected());
		AND_GIVEN("a disconnected output port B")
		{
			TestOutputPort B;
			REQUIRE(!B.isConnected());
			THEN("connecting A to B is possible")
			{
				REQUIRE(A.canConnect(&B));
			}
			THEN("connecting A to B does not throw")
			{
				REQUIRE_NOTHROW(A.connect(&B));
			}
			THEN("connecting B to A is possible")
			{
				REQUIRE(B.canConnect(&A));
			}
			THEN("connecting B to A does not throw")
			{
				REQUIRE_NOTHROW(B.connect(&A));
			}
			WHEN("B is connected to another input port C")
			{
				TestInputPort C;
				B.connect(&C);
				THEN("connecting A to B is still possible")
				{
					REQUIRE(A.canConnect(&B));
					AND_WHEN("connecting A to B")
					{
						REQUIRE_NOTHROW(A.connect(&B));
						THEN("C remains connected")
						{
							REQUIRE(C.isConnected());
						}
					}
				}
				THEN("connecting B to A is still possible")
				{
					REQUIRE(B.canConnect(&A));
					AND_WHEN("connecting B to A")
					{
						REQUIRE_NOTHROW(B.connect(&A));
						THEN("C remains connected")
						{
							REQUIRE(C.isConnected());
						}
					}
				}
			}
			WHEN("A is connected to another output port C")
			{
				TestOutputPort C;
				A.connect(&C);
				THEN("connecting A to B is still possible")
				{
					REQUIRE(A.canConnect(&B));
					AND_WHEN("connecting A to B")
					{
						REQUIRE_NOTHROW(A.connect(&B));
						THEN("C gets disconnected")
						{
							REQUIRE(!C.isConnected());
						}
					}
				}
				THEN("connecting B to A is still possible")
				{
					REQUIRE(B.canConnect(&A));
					AND_WHEN("connecting B to A")
					{
						REQUIRE_NOTHROW(B.connect(&A));
						THEN("C gets disconnected")
						{
							REQUIRE(!C.isConnected());
						}
					}
				}
			}
		}
		AND_GIVEN("a disconnected input port B")
		{
			TestInputPort B;
			REQUIRE(!B.isConnected());
			THEN("connecting A and B is not possible")
			{
				REQUIRE(!A.canConnect(&B));
			}
			THEN("connecting A and B throws an exception")
			{
				REQUIRE_THROWS(A.connect(&B));
			}
		}
	}
	GIVEN("A disconnected output port A")
	{
		TestOutputPort A;
		REQUIRE(!A.isConnected());
		AND_GIVEN("a disconnected output port B")
		{
			TestOutputPort B;
			REQUIRE(!B.isConnected());

			THEN("connecting A and B is not possible")
				REQUIRE(!A.canConnect(&B));
			THEN("connecting A and B throws an exception")
				REQUIRE_THROWS(A.connect(&B));
		}
	}
}
