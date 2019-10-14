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
	static inline std::string const noMessage = "No message set";
	static inline std::string const noMessageSent = "No Message Sent";
	std::string messageToSend;

public:
	TestSource(std::string messageToSend = noMessage)
		: messageToSend(messageToSend)
	{
		getOutputData<OutputPorts::Message>() = noMessageSent;
	}

protected:
	void update() override
	{
		getOutputData<OutputPorts::Message>() = messageToSend;
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
	std::string receivedMessage = noMessageReceived;

protected:
	void update() override
	{
		receivedMessage = getInputData<InputPorts::Message>();
	}
};

TEST_CASE("base.pipes.Interactions between a sink and a source")
{
	/*GIVEN("Source A with one, message output port that always outputs 'SourceA'")
	{
		TestSource A("SourceA");
		auto& outputPort = A.getOutputDataPort<TestSource::OutputPorts::Message>();
		REQUIRE(outputPort.get() == A.noMessage);

		AND_GIVEN("test sink B with a message input port")
		{
			TestSink B;
			auto& InputPort = B.getInputDataPort<TestSink::InputPorts::Message>();
			WHEN("connecting the two ports and running B")
			{
				InputPort.connect(&outputPort);
				B.run();
				THEN("A's update method is run")
				{
					REQUIRE(outputPort.get() == A.messageToSend);
				}
				AND_THEN("A's output port message is sent to B's input port")
				{
					REQUIRE(B.receivedMessage == A.messageToSend);
				}
			}

		}
	}*/
}