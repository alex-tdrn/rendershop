add_library(util INTERFACE)

target_sources(
	util
	INTERFACE "include/clk/util/bounded.hpp"
				"include/clk/util/color_rgb.hpp"
				"include/clk/util/color_rgba.hpp"
				"include/clk/util/data_type_name.hpp"
				"include/clk/util/timestamp.hpp"
				"include/clk/util/time_unit.hpp"
				"include/clk/util/type_list.hpp"
				"include/clk/util/predicates.hpp"
				"include/clk/util/projections.hpp"
)

target_include_directories(util INTERFACE "include")
target_link_libraries(util INTERFACE glm::glm range-v3::range-v3)

install(TARGETS util)
install(DIRECTORY include/ DESTINATION include)

add_library(clayknot::util ALIAS util)
