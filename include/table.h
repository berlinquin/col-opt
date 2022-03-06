#include <boost/multi_array.hpp>

typedef boost::multi_array<int, 2> table_type;
typedef boost::multi_array_ref<uint16_t, 2> table_type_ref;
// index type is not dependent on template parameters,
// and is identical for multi_array and multi_array_ref classes
typedef table_type::index table_index;

