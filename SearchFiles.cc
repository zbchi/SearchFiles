#include "SearchFiles.h"
SearchFiles::SearchFiles(int argc, char *argv[]) : argc(argc), argv(argv)
{
    parse_args(this->argc, this->argv, this->config);
}
SearchFiles::~SearchFiles() {};
void SearchFiles::parse_args(int argc, char *argv[], SearchConfig &config)
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-r" || arg == "--root")
            config.root_path = argv[++i];
        else if (arg == "-t" || arg == "--type")
            config.file_type = argv[++i];
        else if (arg == "-c" || arg == "--concurrency")
            config.max_concurrency = std::stoi(argv[++i]);
        else if (arg == "-d" || arg == "--depth")
            config.max_depth = std::stoi(argv[++i]);
        else if (arg == "--skip-hidden")
            config.skip_hidden = true;
        else if (arg == "-s" || arg == "--skip-path")
            config.skip_paths.push_back(argv[++i]);
        else
            std::cerr << "未知参数:" << arg << std::endl;
    }
}