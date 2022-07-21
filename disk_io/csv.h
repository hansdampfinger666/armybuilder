#pragma once

#include <tools/types.h>

namespace disk_io {
	
string
generate_csv(const vector<string>& column_names,
						 const Range auto&... columns);


}
