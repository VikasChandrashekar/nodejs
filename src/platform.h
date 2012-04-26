// Copyright Joyent, Inc. and other Node contributors.
// Copyright (c) 2011 Hewlett-Packard Development Company, L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef NODE_PLATFORM_H_
#define NODE_PLATFORM_H_

#include <v8.h>

namespace node {

class Platform {
 public:
  static char** SetupArgs(int argc, char *argv[]);
  static void SetProcessTitle(char *title);
  static const char* GetProcessTitle(int *len);

  static int GetMemory(size_t *rss, size_t *vsize);
  static int GetExecutablePath(char* buffer, size_t* size);
  static int GetCPUInfo(v8::Local<v8::Array> *cpus);
  static double GetFreeMemory();
  static double GetTotalMemory();
#if WEBOS
  static double GetUptime(bool adjusted = false)
  {
    return adjusted ? GetUptimeImpl() - prog_start_time : GetUptimeImpl();
  }
#else
  static double GetUptime();
#endif
  static int GetLoadAvg(v8::Local<v8::Array> *loads);
#if WEBOS
  static void ResetUptimeOffset(int64_t newOffset = -1)
  {
    if (newOffset < 0)
      prog_start_time = GetUptime(false);
    else
      prog_start_time = newOffset;
  }

 private:
  static double GetUptimeImpl();
  static double prog_start_time;
#endif
};


}  // namespace node
#endif  // NODE_PLATFORM_H_
