// Лабораторная работа №4 (2 семестр) Вариант №2
// 
// Создайте односвязный список из 10000 целых чисел и реализуйте в нем операцию удаления элемента k. 
// Если элементов, равных k несколько, удалите их все. Выполните M = 1000 запросов на удаление.
// Реализуйте такую же операцию для массива.Сравните производительность.
//

#include <iostream>
#include <chrono>

#define N 1000
#define M 100

using std::cout;
using std::endl;

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

struct List
{
    List* next;
    int data;
};

void ADD(List* head, int data) 
{
	List* p = new List;
	p->data = data;

	p->next = head->next;
	head->next = p;
}

void PRINT(List* head) 
{
	List* p = head->next;
	while (p != nullptr) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void DELETE(List* head, int key)
{
	List* tmp;
	List* p = head;
	while (p->next != nullptr)
	{
		if (p->next->data == key)
		{
			tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else
			p = p->next;
	}
}

void CLEAN(List* head) 
{
	List* tmp;
	List* p = head->next;
	while (p != nullptr) {

		tmp = p;
		p = p->next;
		delete tmp;
	}
}

void DELETE_MAS(int mas[N], int key)
{
	int count = N;
	for (int i = 0; i < count; i++)
	{
		if (mas[i] == key)
		{
			for (int j = i; j < count-1; j++)
			{
				mas[j] = mas[j + 1];
			}
			mas[count-1] = 0;
			count--;
		}
	}
}

int main()
{
    srand(time(0));
	List* head = new List;
	head->next = nullptr;
	int mass[N], queries[M];
	for (int i = 0; i < N; i++)
	{
		int r = rand() % N;
		ADD(head, r);
		mass[i] = r;
	}

	for (int i = 0; i < M; i++) queries[i] = rand() % N;

	Timer list;
	for (int i = 0; i < M; i++) DELETE(head, queries[i]);
	cout << "list: " << list.elapsed() << endl;

	Timer array;
	for (int i = 0; i < M; i++) DELETE_MAS(mass, queries[i]);
	cout << "array: " << array.elapsed() << endl;

	CLEAN(head);
	delete head;
}
