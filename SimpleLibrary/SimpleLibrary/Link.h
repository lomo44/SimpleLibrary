#pragma once
#include <iostream>

#define SL_START namespace CL{
#define SL_END }

SL_START

template <class t_type> 
struct Linker {
	t_type m_pPointer;
	t_type m_pNextLinker;
	t_type m_pPrevLinker;
};
typedef struct Linker Linker;

template <class t_type>
struct List {
	t_type m_pStartLinker;
	t_type m_pEndLinker;
	int m_iSize;
};
typedef struct List List;

template <class T_type> class Linkedlist
{
public:
	Linkedlist()
	{
		m_pStartLinker = NULL;
		m_pEndLinker = NULL;
		m_iSize = 0;
	}
	~Linkedlist()
	{
		Linker* start_linker = m_pStartLinker;
		Linker* prior_linker = NULL;
		for (; start_linker != NULL;)
		{
			prior_linker = start_linker;
			start_linker = start_linker->m_pNextLinker;
			free(prior_linker);
		}
	}
	void push(T_type _t) {
		Linker* newlinker = (Linker*)malloc(sizeof(Linker));
		newlinker->m_pPointer = _t;
		if (m_iSize == 0)
		{
			m_pStartLinker = newlinker;
			m_pEndLinker = newlinker;
			m_pEndLinker->m_pNextLinker = NULL;
			m_pEndLinker->m_pPrevLinker = NULL;
			m_iSize += 1;
		}
		else
		{
			newlinker->m_pPrevLinker = m_pEndLinker;
			m_pEndLinker->m_pNextLinker = newlinker;
			m_pEndLinker = newlinker;
			m_pEndLinker->m_pNextLinker = NULL;
			m_iSize += 1;
		}
	}
	void pop() {
		if (m_iSize == 1)
		{
			free(m_pStartLinker);
			m_pStartLinker = NULL;
			m_pEndLinker = NULL;
			m_iSize -= 1;
		}
		else
		{
			Linker* temp = m_pStartLinker;
			m_pStartLinker = m_pStartLinker->m_pNextLinker;
			m_pStartLinker->m_pPrevLinker = NULL;
			free(temp);
			m_iSize -= 1;
		}
	}
	void pull() {
		if (m_iSize == 1)
		{
			free(m_pStartLinker);
			m_pStartLinker = NULL;
			m_pEndLinker = NULL;
		}
		else
		{
			Linker* temp = m_pEndLinker;
			m_pEndLinker = m_pEndLinker->m_pPrevLinker;
			m_pEndLinker->m_pNextLinker = NULL;
			free(temp);
			m_iSize -= 1;
		}
	}
	void movetop(int pos) {
		if (pos < 0)
		{
			return;
		}
		else if (pos == 0)
		{
			return;
		}
		else if (m_iSize == 1)
		{
			return;
		}
		else if (pos >= m_iSize)
		{
			return;
		}
		else
		{
			Linker* previous_linker = m_pStartLinker;
			Linker* current_linker = m_pStartLinker->m_pNextLinker;
			int counter;
			for (counter = 1; counter < pos; counter++)
			{
				previous_linker = current_linker;
				current_linker = current_linker->m_pNextLinker;
			}
			if (current_linker == m_pEndLinker)
			{
				m_pEndLinker = previous_linker;
			}
			previous_linker->m_pNextLinker = current_linker->m_pNextLinker;
			previous_linker->m_pNextLinker->m_pPrevLinker = previous_linker;
			current_linker->m_pNextLinker = m_pStartLinker;
			current_linker->m_pPrevLinker = NULL;
			m_pStartLinker->m_pPrevLinker = current_linker;
			m_pStartLinker = current_linker;
		}
	}
	void deleteat(const int pos) {
		if (pos == 0) {
			pop();
		}
		else if (pos == m_iSize - 1)
			pull();
		else {
			if (pos > 0 && pos < m_iSize - 1) {
				Linker* temp = m_pStartLinker;
				int count;
				for (count = 0; count != pos; count++)
					temp = temp->m_pNextLinker;
				temp->m_pPrevLinker->m_pNextLinker = temp->m_pNextLinker;
				temp->m_pNextLinker->m_pPrevLinker = temp->m_pPrevLinker;
				m_iSize--;
				free(temp);
			}
		}
	}
	Linklist* concatenate(Linkedlist* _list1, Linkedlist* _list2)
	{
		if (_list1 == NULL || _list2 == NULL) {
			return NULL;
		}
		else {
			if (_list1->m_iSize == 0) {
				_list1->m_pStartLinker = _list2->m_pStartLinker;
				_list1->m_pEndLinker = _list2->m_pEndLinker;
				_list1->m_iSize = _list2->m_iSize;
			}
			else {
				_list1->m_pEndLinker->m_pNextLinker = _list2->m_pStartLinker;
				_list2->m_pStartLinker->m_pPrevLinker = _list1->m_pEndLinker;
				_list1->m_pEndLinker = _list2->m_pEndLinker;
				_list1->m_iSize += _list2->m_iSize;
			}
			delete(_list2);
			return _list1;
		}
	}
	T_type top() {
		return m_pStartLinker.m_pPointer;
	}
	T_type bottom() {
		return m_pStartLinker.m_pPointer;
	}
private:
	Linker* m_pStartLinker;
	Linker* m_pEndLinker;
	int m_iSize;
};

SL_END