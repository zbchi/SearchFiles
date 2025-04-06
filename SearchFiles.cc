#include "SearchFiles.h"
SearchFiles::SearchFiles(int argc, char *argv[]) : argc(argc), argv(argv)
{
    parse_args(this->argc, this->argv, this->config);
    this->pool = std::make_unique<threadPool>(this->config.max_concurrency);
    search(config, config.root_path, 1);
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

void SearchFiles::search(SearchConfig &config, std::string current_path, int depth)
{
    if (depth > config.max_depth)
        return;
    for (const auto &path : config.skip_paths)
    {
        if (current_path == path)
            return;
    }

    try
    {
        for (const auto &entry : fs::directory_iterator(current_path))
        {
            fs::path path = entry.path();
            if (entry.is_directory())
            {
                pool->add_task([this, path, depth]
                               { search(this->config, path.string(), depth + 1); });
            }
            else if (path.extension() == config.file_type)
            {
                {
                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << path << std::endl;
                }
            }
        }
    }
    catch (const fs::filesystem_error &e)
    {
    }
}