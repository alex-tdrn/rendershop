#pragma once

namespace detail
{
	inline int tag = 0;
}

template <typename T>
int typeTag()
{
	static int tag = detail::tag++;
	return tag;
}