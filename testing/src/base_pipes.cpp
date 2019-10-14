#include "catch.hpp"
#include "renderdeck/Pipe.hpp"

#include <array>

class TestSource : public Source<TestSource, OutputList<std::string>>
{
public:
	struct OutputPorts
	{
		static inline std::array names = {
			"Message"
		};
		enum
		{
			Message,
		};
	};

public:
	static inline std::string const name = registerPipe<TestSource>("Test Source");
	
private:
	std::string message = "No message";
	int updatesRan = 0;

protected:
	void update() override
	{
		updatesRan++;
	}

public:
	std::string const& getMessage() const
	{
		return message;
	}

	void setMessage(std::string message)
	{
		this->message = message;
		getOutputData<OutputPorts::Message>() = message;
	}

	int getUpdatesRan() const
	{
		return updatesRan;
	}

};

class TestSink : public Sink<TestSink, InputList<std::string>>
{
public:
	struct InputPorts
	{
		static inline std::array names = {
			"Message"
		};
		enum
		{
			Message,
		};
	};

public:
	static inline std::string const name = registerPipe<TestSink>("Test Sink");
	static inline std::string const noMessageReceived = "No Message Received";

private:
	std::string message = noMessageReceived;
	int updatesRan = 0;

protected:
	void update() override
	{
		message = getInputData<InputPorts::Message>();
		updatesRan++;
	}

public:
	std::string const& getMessage() const
	{
		return message;
	}

	int getUpdatesRan() const
	{
		return updatesRan;
	}
};

TEST_CASE("base.pipes.Interactions between a sink and a source")
{
	GIVEN("Source A with one output port")
	{
		TestSource A;
		A.setMessage("This message comes from A");
		auto& outputPort = A.getOutputDataPort<TestSource::OutputPorts::Message>();
		AND_GIVEN("test sink B with one input port connected to A's output port")
		{
			TestSink B;
			auto& inputPort = B.getInputDataPort<TestSink::InputPorts::Message>();
			inputPort.connect(&outputPort);
			WHEN("running B")
			{
				bool updateEventTriggered = false;
				InputEventPort E([&updateEventTriggered]() {
					updateEventTriggered = true;
				});
				E.connect(&A.getOutputEventPort(AbstractPipe::OutputEvents::Updated));
				B.run();
				THEN("A's update event is triggered")
				{
					REQUIRE(updateEventTriggered);
					AND_THEN("A and B's update methods are ran once")
					{
						REQUIRE(A.getUpdatesRan() == 1);
						REQUIRE(B.getUpdatesRan() == 1);
						AND_THEN("A's output port value is sent to B's input port")
						{
							REQUIRE(B.getMessage() == A.getMessage());
						}
					}
				}
			}
		}
	}
}