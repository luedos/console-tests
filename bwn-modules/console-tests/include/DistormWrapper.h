#pragma once

#include <string>
#include <vector>
#include "distorm.h"

std::vector<_DInst> GetInstructions(const std::string& code, const std::vector<unsigned int>& relocs = {}, size_t prologSize = 0, size_t epilogSize = 0);
