// #include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>

int main(int argc, char *argv[])
{
  std::system("rm -rf ../neon-os-core-repo/x86_64/*");
  for (const auto & entry : std::filesystem::directory_iterator(std::string("x86_64")))
    {
      std::system(("cd " + std::string(entry.path()) + "&& makepkg -cf --sign").c_str());
      for (const auto & pkg : std::filesystem::directory_iterator(std::string(entry.path())))
	  {
	    if(std::string(pkg.path()).substr(std::string(pkg.path()).length()-3,3) == "zst" || std::string(pkg.path()).substr(std::string(pkg.path()).length()-4,3) == "zst" || std::string(pkg.path()).substr(std::string(pkg.path()).length()-3,3) == "sig" || std::string(pkg.path()).substr(std::string(pkg.path()).length()-4,3) == "sig" )
	      {
		std::filesystem::rename(std::string(pkg.path()),"../neon-os-core-repo/x86_64/"+std::string(pkg.path()).substr(std::string(entry.path()).length()+1));
	      }
	    if (std::filesystem::is_directory(std::string(pkg.path()))) {
	      std::filesystem::remove_all(std::string(pkg.path()));
	    }
	  }
    }
  return 0;
}
