#ifndef LINKED_LIST
#define LINKED_LIST
#include <iostream>

template <class T>
struct Node
{
	Node(T value) : value(value), next(nullptr)
	{
	}
	Node *next;
	T value;
};

template <class T>
class LinkedList
{
private:
	Node<T> *head;

public:
	LinkedList()
	{
		head = nullptr;
	};

	void set_head(Node<T> *new_head)
	{
		head = new_head;
	}

	void display()
	{
		auto current = head;
		while (current != nullptr)
		{
			std::cout << current->value << "\n";
			current = current->next;
		}
	}

	int get_length()
	{
		int return_length = 0;
		auto *current = head;
		while (current != nullptr)
		{
			return_length++;
			current = current->next;
		}
		return return_length;
	}

	T access(int index)
	{
		auto *current = head;
		for (int i = 0; i <= index; i++)
		{
			if (current == nullptr)
			{
				return T();
			}
			else if (i == index)
			{
				return current->value;
			}
			else
			{
				current = current->next;
			}
		}
		return T();
	};
	void append(T value)
	{
		Node<T> *node = new Node<T>(value);
		if (head == nullptr)
		{
			head = node;
		}
		else
		{
			auto *current = head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = node;
		}
	};

	LinkedList<T> prepend(T value)
	{
		LinkedList<T> *new_list = new LinkedList<T>();
		Node<T> *new_head = new Node<T>(value);
		new_head->next = head;
		new_list->set_head(new_head);
		return *new_list;
	}

	// Returns the head, and a linked list
	// containing the rest of the items
	std::pair<T *, LinkedList<T> *> split()
	{
		if (head == nullptr)
		{
			return std::pair<T *, LinkedList<T> *>(nullptr, new LinkedList<T>());
		}
		else
		{
			T *head_value = &(head->value);
			LinkedList<T> *the_rest = new LinkedList<T>();
			the_rest->set_head(head->next);
			return std::pair<T *, LinkedList<T> *>(head_value, the_rest);
		}
	}

	T *first()
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		else
		{
			return &(head->value);
		}
	}

	LinkedList<T> *rest()
	{
		LinkedList<T> *the_rest = new LinkedList<T>();

		if (head == nullptr || head->next == nullptr)
		{
			the_rest->set_head(nullptr);
		}
		else
		{
			the_rest->set_head(head->next);
		}

		return the_rest;
	}
};

#endif