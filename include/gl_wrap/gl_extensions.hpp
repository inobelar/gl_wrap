#pragma once

#include <string>
#include <vector>

namespace gl {

bool isExtensionSupported(const char *name);

std::vector<std::string> getExtensions();

} // namespace gl
