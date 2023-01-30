#pragma once

namespace drach
{
	namespace ecs
	{
		typedef unsigned long Entity;
		constexpr Entity nullentity = (Entity)-1L;//ULONG_MAX
	}
}

#define FORWARD_DECLARE_REG namespace drach \
{											\
	namespace ecs							\
	{										\
		class Registry;						\
	}										\
}
