#pragma once
#include <iostream>

typedef struct Linker {
	void* m_pPointer;
	struct Linker* m_pNextLinker;
	struct Linker* m_pPrevLinker;
}Linker;

typedef struct List {
	struct Linker* m_pStartLinker;
	struct Linker* m_pEndLinker;
	int m_iSize;
}List;

class Link
{
public:
	Link()
	{
		m_pStartLinker = NULL;
		m_pEndLinker = NULL;
		m_iSize = 0;
	}

	~Link()
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
	void push(void* _p) {
		Linker* newlinker = (Linker*)malloc(sizeof(Linker));
		newlinker->m_pPointer = _p;
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

private:
	Linker* m_pStartLinker;
	Linker* m_pEndLinker;
	int m_iSize;
};

