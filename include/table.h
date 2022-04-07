#include <boost/multi_array.hpp>

// 2x2 matrix types to hold the length of the cells in the table
typedef boost::multi_array<int, 2> table_type;
typedef boost::multi_array_ref<uint16_t, 2> table_type_ref;

// 2x2 matrix type to hold the text of the cells in the table
typedef boost::multi_array<std::string, 2> string_table_type;

// index type is not dependent on template parameters,
// and is identical for multi_array and multi_array_ref classes
typedef table_type::index table_index;

