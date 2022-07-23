#pragma once

#include <ostream>

#include "CoreMinimal.h"
#include "ctl/Allocator.h"

namespace CTL
{
	template<typename VectorT>
	class VectorIterator
	{
	public:
		using ValueType = typename VectorT::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
	public:
		VectorIterator(PointerType ptr)
			: m_Ptr(ptr) {}

		VectorIterator& operator++()
		{
			m_Ptr++;
			return *this;
		}
		VectorIterator operator++(int)
		{
			VectorIterator iterator = *this;
			++(*this);
			return iterator;
		}

		VectorIterator& operator--()
		{
			m_Ptr--;
			return *this;
		}
		VectorIterator operator--(int)
		{
			VectorIterator iterator = *this;
			--(*this);
			return iterator;
		}

		ReferenceType operator[](int index) const { return *(this + index); }
		PointerType operator->() const { return m_Ptr; }
		ReferenceType operator*() const { return *this; }

		bool operator==(const VectorIterator& other) const { return m_Ptr == other.m_Ptr; }
		bool operator!=(const VectorIterator& other) const { return m_Ptr != other.m_Ptr; }
	private:
		PointerType m_Ptr;
	};

	template<typename Ty>
	class Vector : public Object
	{
	public:
		using ValueType = Ty;
		using Iterator = VectorIterator<Vector<Ty>>;
	public:
		Vector()
		{
			m_Allocator.Reserve(2);
		}
		Vector(const size_t& size)
		{
			m_Allocator.Reserve(size);
		}

		void PushBack(const Ty& data)
		{
			m_Allocator.PushBack(data);
		}

		void Insert(size_t index, const Ty& data)
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
					Ty tmp = m_Allocator.m_Buffer[i];
					m_Allocator.m_Buffer[i] = m_Allocator.m_Buffer[i - 1];
					m_Allocator.m_Buffer[i - 1] = tmp;
				}

				m_Allocator.m_Buffer[index] = data;
			}
		}

		void Remove(size_t index)
		{
			if (index >= 0 && index < m_Allocator.m_Size)
			{ 
				for (size_t i = 0, i2 = 0; i < m_Allocator.m_Size - 1; i2++)
					if (i2 != index)
						(*m_Allocator)[i++] = (*m_Allocator)[i2];
				m_Allocator.Pop();
			}
		}

		const Ty& operator[](size_t index) const
		{
			return m_Allocator[index];
		}

		Ty& operator[](size_t index)
		{
			return m_Allocator[index];
		}

		Iterator begin()
		{
			return Iterator(m_Allocator.m_Buffer);
		}

		Iterator end()
		{
			return Iterator(m_Allocator.m_Buffer + m_Allocator.m_Size);
		}

		virtual String ToString() const override
		{
			std::stringstream ss;
			ss << "[";
			if (m_Allocator.m_Size > 0)
			{
				for (uint32 i = 0; i < m_Allocator.m_Size - 1; i++)
					ss << ' ' << m_Allocator[i] << ',';
				ss << ' ' << m_Allocator[m_Allocator.m_Size - 1];
			}
			ss << " ]";

			return ss.str().c_str();
		}
	private:
		Allocator<Ty> m_Allocator;
	};
}