///////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iterator>
#include <memory>
#include <new>
#include <print>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////

class Allocator : private boost::noncopyable
{
public :

	Allocator(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(s_alignment));
	}

//  -------------------------------------------------------------------------------

   ~Allocator()
	{
		operator delete(m_begin, m_size, std::align_val_t(s_alignment));
	}

//  -------------------------------------------------------------------------------

	auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void *
	{
		void * begin = get_byte(m_begin) + m_offset + sizeof(header_t);

		auto free = m_size - m_offset - sizeof(header_t);

		if (begin = std::align(alignment, size, begin, free); begin)
		{
			auto header = get_header(get_byte(begin) - sizeof(header_t));

			*header = std::distance(get_byte(m_begin) + m_offset, get_byte(begin));

			m_offset = get_byte(begin) - get_byte(m_begin) + size;

			return begin;
		}
		else 
		{
			return nullptr;
		}
	}

	void deallocate(void * x)
	{
		auto header = get_header(get_byte(x) - sizeof(header_t));

		m_offset = get_byte(x) - get_byte(m_begin) - *header;
	}

//  -------------------------------------------------------------------------------

	void show() const
	{
		std::print
		(
			"Allocator::show : m_size = {} m_begin = {:018} m_offset = {:0>4}\n",

			m_size, m_begin, m_offset
		);
	}

private :

	using header_t = std::uint8_t;

//  -------------------------------------------------------------------------------

	auto get_byte(void * x) const -> std::byte *
	{
		return static_cast < std::byte * > (x);
	}

//  -------------------------------------------------------------------------------

	auto get_header(void * x) const -> header_t *
	{
		return static_cast < header_t * > (x);
	}

//  -------------------------------------------------------------------------------

	std::size_t m_size = 0, m_offset = 0;
	
	void * m_begin = nullptr;

//  -------------------------------------------------------------------------------

	static inline auto s_alignment = alignof(std::max_align_t);
};

///////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

	std::vector < void * > vector(kb, nullptr);

	for (auto element : state)
	{
		Allocator allocator(2 * gb);

		for (auto i = 0uz; i < kb; ++i)
		{
			vector[i] = allocator.allocate(mb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{
			allocator.deallocate(vector[std::size(vector) - 1 - i]);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
	auto kb = 1'024uz, mb = kb * kb;

	std::vector < void * > vector(kb, nullptr);

	for (auto element : state)
	{
		for (auto i = 0uz; i < kb; ++i)
		{
			vector[i] = operator new(mb);
		}

		for (auto i = 0uz; i < kb; ++i)
		{
			operator delete(vector[std::size(vector) - 1 - i], mb);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	Allocator allocator(1'024);

//  ----------------------------------------------------

	allocator.show();          allocator.allocate(1, 1); 
	
	allocator.show();          allocator.allocate(2, 2); 
	
	allocator.show(); auto x = allocator.allocate(4, 4); 
	
	allocator.show(); auto y = allocator.allocate(8, 8);

//  ----------------------------------------------------
	
	allocator.show(); allocator.deallocate(y);  
	
	allocator.show(); allocator.deallocate(x);
	
//  ----------------------------------------------------
	
	allocator.show(); auto z = allocator.allocate(8, 8); 
	
	allocator.show(); 

//  ----------------------------------------------------

	assert(z == x);

//  ----------------------------------------------------

	benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////