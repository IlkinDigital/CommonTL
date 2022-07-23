#include "ctlpch.h"
#include "CTL/PriorityQueue.h"

namespace CTL {

	template<typename Ty, typename PriorityTy>
	inline void PriorityQueue<Ty, PriorityTy>::Enqueue(const Ty& value, const PriorityTy& priority)
	{
		for (size_t i = 0; i < m_Allocator.m_Size; i++)
		{
			if (m_Allocator.m_Buffer[i].Priority > priority)
			{
				Insert(i, QueueStorage(value, priority));
				return;
			}
		}

		m_Allocator.PushBack(QueueStorage(value, priority));
	}

}