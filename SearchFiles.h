#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include "ThreadPool.h"
namespace fs = std::filesystem;

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

    std::unique_ptr<ThreadPool> pool;
    std::mutex cout_mutex;
    std::mutex cerr_mutex;

    void parse_args(int argc, char *argv[], SearchConfig &config);
    void search(SearchConfig &config, std::string current_path, int depth);
};