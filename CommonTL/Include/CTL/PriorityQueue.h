#pragma once

#include "Allocator.h"

namespace CTL {

	/**
	* Priority Queue - inserts values into queue based on priority
	* Usage: PriorityQueue<String, int>
	*						 ^      ^
	*			      buffType      priorityType
	*/

	template<typename Ty1, typename Ty2>
	class QueueStorage
	{
	public:
		Ty1 Value = {};
		Ty2 Priority = {};

		QueueStorage() = default;
		QueueStorage(const QueueStorage& other)
			: Value(other.Value), Priority(other.Priority) {}
		QueueStorage(const Ty1& value, const Ty2& priority)
			: Value(value), Priority(priority) {}

		QueueStorage<Ty1, Ty2>& operator =(const QueueStorage<Ty1, Ty2>& other)
		{
			Value = other.Value;
			Priority = other.Priority;
		}
	};

	template<typename Ty, typename PriorityTy>
	class PriorityQueue
	{
	public:
		using ValueTy = QueueStorage<Ty, PriorityTy>;
	public:
		PriorityQueue()
		{
			m_Allocator.Reserve(2);
		}

		void Enqueue(const Ty& value, const PriorityTy& priority);
		void Dequeue() { m_Allocator.PopFront(); }

		const Ty& Front() const { return m_Allocator.m_Buffer[0].Value; }
		const Ty& Back() const { return m_Allocator.m_Buffer[m_Allocator.m_Size - 1].Value; }
	private:
		void Insert(size_t index, const ValueTy& data)
		{
			if (index <= m_Allocator.m_Size)
			{
				if (m_Allocator.m_Capacity < m_Allocator.m_Size + 1)
					m_Allocator.Reserve(m_Allocator.m_Capacity + m_Allocator.m_Capacity / 2);

				// Push back the last element of an array
				m_Allocator.PushBack(m_Allocator.m_Buffer[m_Allocator.m_Size - 1]);

				// Swap adjacent elements from the end until the insertion index, to shift them to the left
				for (size_t i = m_Allocator.m_Size - 2; i > index; i--)
				{
					QueueStorage<Ty, PriorityTy> tmp = m_Allocator.m_Buffer[i];
					m_Allocator.m_Buffer[i] = m_Allocator.m_Buffer[i - 1];
					m_Allocator.m_Buffer[i - 1] = tmp;
				}

				m_Allocator.m_Buffer[index] = data;
			}
		}

	private:
		Allocator<ValueTy> m_Allocator;
	};

}