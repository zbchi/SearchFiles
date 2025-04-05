#include <iostream>
#include <thread>
#include <string>
#include <vector>
class SearchFiles
{
public:
    SearchFiles(int argc, char *argv[]);
    ~SearchFiles();

private:
    struct SearchConfig
    {
        std::string root_path;
        std::string file_type;
        int max_concurrency;
        int max_depth;
        bool skip_hidden;
        std::vector<std::string> skip_paths;
    };

    int argc;
    char **argv;
    SearchConfig config;

    void parse_args(int argc, char *argv[], SearchConfig &config);
};