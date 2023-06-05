#pragma once

class Message {
public:
	Message(std::string text, std::string sender, std::string receiver) :_text(text), _sender(sender), _receiver(receiver) {}

	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);

private:
	std::string _text;
	std::string _sender;
	std::string _receiver;
};