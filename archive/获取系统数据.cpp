#include <iostream>
#include <memory>
#include <string>
std::string ExecCommand(const std::string &cmd) {
  std::string result;
  std::array<char, 1024> buffer{'\0'};
  auto fp = ::popen(cmd.c_str(), "r");
  if (fp != nullptr) {
    while (!std::feof(fp)) {
      auto bytes = std::fread(buffer.data(), 1, buffer.size(), fp);
      result.append(buffer.data(), bytes);
    }
    ::pclose(fp);
  }
  return result;
}

int main() {
  const auto &tmp_str = ExecCommand("uname -a | grep x86_64");
  if (!tmp_str.empty()) {
    const auto &cmd_ret = ExecCommand("nvidia-smi -L");
    if (std::string::npos != cmd_ret.find("3090", 0)) {
      std::cout << "get Graphics card model :" << cmd_ret;
    }
  }
  return 0;
}
// 代码格式format 开启和关闭  clang-format off  and  clang-format on
// clang-format off
//result
// get Graphics card model :GPU 0: NVIDIA GeForce RTX 3090 (UUID: GPU-448f37a5-c358-9c56-f3f2-10170ad2637b)
// clang-format on