/*
This file is part of BGSLibrary.

BGSLibrary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BGSLibrary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BGSLibrary.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <iostream>
#include <sstream>

#include "VideoCapture.h"
#include "FrameProcessor.h"

namespace bgslibrary
{
  class VideoAnalysis
  {
  private:
    VideoCapture* videoCapture;
    FrameProcessor* frameProcessor;
    bool use_file;
    std::string filename;
    bool use_camera;
    int cameraIndex;
    bool use_comp;
    long frameToStop;
    std::string imgref;

  public:
    VideoAnalysis();
    ~VideoAnalysis();

    bool setup(int argc, const char **argv);
    void start();
  };
}
