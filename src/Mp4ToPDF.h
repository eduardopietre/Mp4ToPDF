#pragma once

#include <opencv2/core/utils/logger.hpp>

#include "TQueue.h"
#include "Mp4FileReader.h"
#include "UniqueImageIdentifier.h"
#include "ArgParser.h"


void DoMp4ToPDF(const std::string& filename, const std::string& outfilename, int frameskip, bool verbose);
