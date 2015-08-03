#include <main.pb.h>

#include <iostream>

#include <ctime>

namespace gpb = google::protobuf;

int main()
{
  imp::Message msg;

  msg.set_text("Hello from Protocol Buffers!");
  msg.mutable_time()->set_seconds(time(NULL));
  msg.mutable_time()->set_nanos(0);

  std::cout << "imp::Message {\n" << msg.DebugString() << "}" << std::endl;

  return 0;
}

