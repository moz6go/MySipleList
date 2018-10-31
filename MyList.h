#pragma once

namespace MyListNamespace
{
	template<class Ttype>
	class MyList
	{
		template<class Ttype>
		class Node
		{
		public:
			Node* pnext;
			Node* pprev;
			Ttype data;
			Node(Ttype d = Ttype(), Node* nptr = nullptr, Node* pptr = nullptr)
			{
				data = d;
				pnext = nptr;
				pprev = pptr;
			}
		};
		Node<Ttype> *head;
		Node<Ttype> *tail;
		size_t size;
	public:
		class MyIterator
		{
			Node<Ttype> *ptr;
		public:
			MyIterator() { ptr = nullptr; }
			MyIterator(Node<Ttype>* _ptr) : ptr(_ptr) {}
			MyIterator& operator ++() 
			{
				ptr = ptr->pnext;
				return *this;
			}
			MyIterator& operator --()
			{
				ptr = ptr->pprev;
				return *this;
			}
			MyIterator& operator ++(int)
			{
				MyIterator tmp = *this;
				ptr = ptr->pnext;
				return tmp; 
			}
			MyIterator& operator --(int)
			{
				MyIterator tmp = *this;
				ptr = ptr->pprev;
				return tmp;
			}
			Ttype& operator *() { return ptr->data; }
			bool operator ==(MyIterator itr) { return itr.ptr == ptr; }
			bool operator !=(MyIterator itr) { return itr.ptr != ptr; }
		};
		MyList();
		MyList(const MyList<Ttype>& ls);
		~MyList();
		MyIterator begin() { return MyIterator(head); };
		MyIterator end() { return MyIterator(tail->pnext); };
		Ttype& At(size_t index)const;
		void PushFront(Ttype n_data);
		void PushBack(const Ttype n_data);
		void PopFront();
		void PopBack();
		void RemoveAt(size_t pos);
		void Insert(Ttype n_data, size_t pos);
		void Clear();
		size_t GetSize() { return size; }
		Ttype& operator[](size_t index);
		MyList<Ttype>& operator = (MyList<Ttype>& ls);
	};


	template<class Ttype>
	MyList<Ttype>::MyList()
	{
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	template<class Ttype>
	MyList<Ttype>::MyList(const MyList<Ttype>& ls)
	{
		MyList();
		for (size_t i = 0; i < ls.size; ++i)
		{
			PushBack(ls.At(i));
		}
	}

	template<class Ttype>
	MyList<Ttype>::~MyList()
	{
		Clear();
	}
	
	template<class Ttype>
	Ttype& MyList<Ttype>::At(size_t index) const
	{
		int counter = 0;
		Node<Ttype>* current = head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pnext;
			++counter;
		}
	}

	template<class Ttype>
	void MyList<Ttype>::PushFront(const Ttype n_data)
	{
		Node<Ttype>* tmp_ptr = new Node<Ttype>(n_data, head, nullptr);
		if (head != nullptr)
		{
			head->pprev = tmp_ptr;
		}
		else
		{
			tail = tmp_ptr;
		}
		head = tmp_ptr;
		++size;
	}
	
	template<class Ttype>
	void MyList<Ttype>::PushBack(Ttype n_data)
	{
		if (tail == nullptr)
		{
			tail = head = new Node<Ttype>(n_data);
		}
		else
		{
			Node<Ttype>* tmp_ptr = new Node<Ttype>(n_data, nullptr, tail);
			tail->pnext = tmp_ptr;
			tail = tmp_ptr;
		}
		++size;
	}
	
	template<class Ttype>
	void MyList<Ttype>::PopFront()
	{
		Node<Ttype> *toDelete = head;
		head = head->pnext;
		delete toDelete;
		if (head != nullptr)
		{
			head->pprev = nullptr;
		}
		else
		{
			tail = nullptr;
		}
		--size;
	}
	
	template<class Ttype>
	void MyList<Ttype>::PopBack()
	{
		Node<Ttype>* toDelete = tail;
		tail = tail->pprev;
		delete toDelete;
		if (tail != nullptr)
		{
			tail->pnext = nullptr;
		}
		else
		{
			head = nullptr;
		}
		--size;
	}
	
	template<class Ttype>
	void MyList<Ttype>::RemoveAt(size_t pos)
	{
		if (!pos)
		{
			PopFront();
		}
		else if (pos == (size - 1))
		{
			PopBack();
		}
		else
		{
			Node<Ttype>* NodeBeforeDel = head;
			for (int i = 0; i < pos - 1; ++i)
			{
				NodeBeforeDel = NodeBeforeDel->pnext;
			}
			Node<Ttype>* toDelete = NodeBeforeDel->pnext;
			Node<Ttype>* NodeAfterDel = toDelete->pnext;
			NodeAfterDel->pprev = NodeBeforeDel;
			NodeBeforeDel->pnext = toDelete->pnext;
			delete toDelete;
			--size;
		}
	}
	
	template<class Ttype>
	void MyList<Ttype>::Insert(Ttype n_data, size_t pos)
	{
		if (pos < size / 2)
		{
			if (!pos)
			{
				PushFront(n_data);
			}
			else
			{
				Node<Ttype>* NodeBeforeIns = head;
				for (int i = 0; i < pos - 1; ++i)
				{
					NodeBeforeIns = NodeBeforeIns->pnext;
				}
				Node<Ttype>* NodeAfterIns = NodeBeforeIns->pnext;
				Node<Ttype>* newNode = new Node<Ttype>(n_data, NodeAfterIns, NodeBeforeIns);
				NodeBeforeIns->pnext = newNode;
				NodeAfterIns->pprev = newNode;
				++size;
			}
		}
		else
		{
			if (pos == (size - 1))
			{
				PushBack(n_data);
			}
			else
			{
				Node<Ttype>* NodeAfterIns = tail;
				for (int i = size-1; i > pos; --i)
				{
					NodeAfterIns = NodeAfterIns->pprev;
				}
				Node<Ttype>* NodeBeforeIns = NodeAfterIns->pprev;
				Node<Ttype>* newNode = new Node<Ttype>(n_data, NodeAfterIns, NodeBeforeIns);
				NodeBeforeIns->pnext = newNode;
				NodeAfterIns->pprev = newNode;
				++size;
			}
		}
	}

	
	template<class Ttype>
	inline void MyList<Ttype>::Clear()
	{
		while (size)
		{
			PopFront();
		}
	}
	
	template<class Ttype>
	Ttype& MyList<Ttype>::operator[](size_t index)
	{
		int counter = 0;
		Node<Ttype>* current = head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pnext;
			++counter;
		}
	}
	template<class Ttype>
	MyList<Ttype>& MyList<Ttype>::operator=(MyList<Ttype>& rls)
	{
		Clear();
		for (auto& el : rls)
		{
			PushBack(el);
		}
		return *this;
	}
}
