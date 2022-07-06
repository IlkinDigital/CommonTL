#pragma once

#include <initializer_list>
#include <iterator>

namespace CTL
{
	template<typename Ty, size_t Sz>
	class SArray
	{
	public:
		Ty Buffer[Sz];
	public:
		class Iterator
		{
		public:
			Iterator(const Ty* arr)
				: m_Ptr(arr) {}


			Iterator& operator++()
			{
				m_Ptr++;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator iterator = *this;
				++(*this);
				return iterator;
			}

			Iterator& operator--()
			{
				m_Ptr--;
				return *this;
			}
			Iterator operator--(int)
			{
				Iterator iterator = *this;
				--(*this);
				return iterator;
			}

			const Ty& operator[](int index) const { return *(m_Ptr + index); }
			const Ty* operator->() const { return m_Ptr; }
			const Ty& operator*() const { return *m_Ptr; }

			bool operator==(const Iterator& other) const { return m_Ptr == other.m_Ptr; }
			bool operator!=(const Iterator& other) const { return m_Ptr != other.m_Ptr; }
		private:
			const Ty* m_Ptr;
		};
	public:
		SArray() = default;

		SArray(const Ty* arr)
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i] = arr[i];
		}
		SArray(const SArray<Ty, Sz>& other)
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i] = other[i];
		}
		SArray(SArray<Ty, Sz>&& other)
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i] = other[i];
		}

		~SArray()
		{
			Clear();
		}

		const size_t Size() const { return Sz; }

		void Clear()
		{
			for (size_t i = 0; i < Sz; i++)
				Buffer[i].~Ty();
		}

		const Ty& At(size_t index) const { return Buffer[index]; }
		Ty& At(size_t index) { return Buffer[index]; }

		Iterator begin() const
		{
			return Iterator(Buffer);
		}
		Iterator end() const
		{
			return Iterator(Buffer + Sz);
		}

		const Ty& operator [] (size_t index) const 
		{ 
			return Buffer[index]; 
		}
		Ty& operator [] (size_t index) 
		{ 
			return Buffer[index]; 
		}

	};
}