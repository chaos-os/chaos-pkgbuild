// #include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  system("rm -rf ../sos-core/x86_64/*");
  for (const auto &entry : filesystem::directory_iterator(string("x86_64"))) {
    system(("cd " + string(entry.path()) + "&& makepkg -cf --sign").c_str());
    for (const auto &pkg :
         filesystem::directory_iterator(string(entry.path()))) {
      if (string(pkg.path()).substr(string(pkg.path()).length() - 3, 3) ==
              "zst" ||
          string(pkg.path()).substr(string(pkg.path()).length() - 4, 3) ==
              "zst" ||
          string(pkg.path()).substr(string(pkg.path()).length() - 3, 3) ==
              "sig" ||
          string(pkg.path()).substr(string(pkg.path()).length() - 4, 3) ==
              "sig") {
        filesystem::rename(
            string(pkg.path()),
            "../sos-core/x86_64/" +
                string(pkg.path()).substr(string(entry.path()).length() + 1));
      }
      if (filesystem::is_directory(string(pkg.path()))) {
        filesystem::remove_all(string(pkg.path()));
      }
    }
  }
  return 0;
}
