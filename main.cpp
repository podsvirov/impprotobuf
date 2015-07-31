#include <main.pb.h>

#include <iostream>

namespace gpb = google::protobuf;

int main()
{
  imp::Message msg;

  msg.set_text("Hello from Protocol Buffers!");

  std::cout << "imp::Message {\n" << msg.DebugString() << "}" << std::endl;

  return 0;
}

