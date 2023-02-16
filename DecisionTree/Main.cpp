#include <string>;
#include <iostream>;

class Node
{

public:
	Node(const std::string& description) :
		description{ description }
	{}

	virtual Node* Execute() = NULL; // <- make a pure virtual method 

protected:
	std::string description;
};

class DecisionNode : public Node
{

public:
	DecisionNode(const std::string& description) :
		Node(description)
	{}

	virtual bool IsTrue() = NULL; // <- make a pure virtual method 

	Node* Execute() override
	{
		bool isTrue = IsTrue();
		std::cout << "DECISION: " << description;
		std::cout << ((isTrue) ? " ->TRUE" : " ->FALSE");
		std::cout << std::endl;

		return (isTrue ? trueNode : falseNode);
	}

public:
	Node* trueNode = nullptr;
	Node* falseNode = nullptr;
};

class DecisionBoolNode : public DecisionNode
{
public:
	DecisionBoolNode(const std::string& description, bool condition) :
		DecisionNode{ description },
		condition{ condition }
	{}

	bool IsTrue() override
	{
		return value == condition ? true : false;
	}

public:
	bool value = true;
	bool condition = true;
};

class DecisionFloatNode : public DecisionNode
{
public:
	enum class Predicate
	{
		EQUAL,
		LESS,
		GREATER
	};

	DecisionFloatNode(const std::string& description, float condition, Predicate predicate) :
		DecisionNode{ description },
		condition{ condition },
		predicate{ predicate }
	{}

	bool IsTrue() override
	{
		switch (predicate)
		{
		case Predicate::EQUAL :
			return true;
		case Predicate::LESS :
			return false;
		case Predicate::GREATER :
			return false;
			//<return true or false for the predicates>
		}

		return false;
	}

public:
	float value = 0;
	float condition = 0;
	Predicate predicate = Predicate::EQUAL;
};

struct ActionNode : public Node
{
	ActionNode(const std::string& description) : Node{ description } {}

	virtual Node* Execute() override
	{
		std::cout << "ACTION: " << description << std::endl;
		return nullptr;
	}
};

void Traverse(Node* node)
{

	while (node != nullptr)
	{
		node = node->Execute();
	}
}

int main()
{
	DecisionBoolNode* awakeDecisionNode = new DecisionBoolNode("is awake", true);

	ActionNode* sleepActionNode = new ActionNode("sleep");
	ActionNode* eatActionNode = new ActionNode("eat");

	awakeDecisionNode->trueNode = eatActionNode;
	awakeDecisionNode->falseNode = sleepActionNode;

	awakeDecisionNode->value = false;

	Traverse(awakeDecisionNode);

}

